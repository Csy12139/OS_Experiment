#include "id.h"
#include <dirent.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include "error.h"
#include <cstring>

// 是否是ID号
bool isID(char *str) {
    size_t length = strlen(str);
    for (size_t i = 0; i < length; i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

// 获取所有进程的PID
enum ERROR_INFO GetAllPids(std::vector<int> *pids) {
    DIR *processDir = opendir("/proc");
    if (processDir != nullptr) {
        struct dirent *readDir;
        while ((readDir = readdir(processDir)) != nullptr) {
            char *processID = readDir->d_name;
            if (isID(processID)) {
                pids->push_back(std::stoi(processID));
            }
        }
    } else {
        return OPEN_DIR_FAILED;
    }
    closedir(processDir); // 关闭目录
    return OK;
}

// 获取该进程的父进程
int GetPPID(int pID) {
    std::ostringstream oss;
    oss << "/proc/" << pID << "/stat";
    std::string path = oss.str();

    std::ifstream file(path);
    if (!file.is_open()) {
        return -1;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string field;
        int index = 0;
        while (iss >> field) {
            if (index == 3) {
                return stoi(field);
            }
            index++;
        }

    }
    file.close();
    return -1;
}

// 获得所有父-子进程映射
void GetAllParent2ChildProcessMap(const std::vector<int> &pids, std::map<int, std::vector<int>> *mp) {
    std::vector<int>::const_iterator it;
    for (it = pids.begin(); it != pids.end(); it++) {
        if (*it == 2) continue; // 忽略内核空间进程
        int ppID = GetPPID(*it); // 获取父进程
        if (ppID == 2) continue; // 忽略内核空间进程
        (*mp)[ppID].push_back(*it);
    }
}

// 获取该进程下所有子线程
enum ERROR_INFO GetChildThreads(int pID, std::vector<int> *threads) {
    std::ostringstream oss;
    oss << "/proc/" << pID << "/task";
    std::string path = oss.str();

    DIR *taskDir = opendir(path.c_str());
    if (taskDir != nullptr) {
        struct dirent *readDir;
        while ((readDir = readdir(taskDir)) != nullptr) {
            char *threadID = readDir->d_name;
            if (isID(threadID)) {
                int tID = std::stoi(threadID);
                if (tID != pID) {
                    threads->push_back(tID);
                }
            }
        }
    } else {
        return OPEN_DIR_FAILED;
    }
    closedir(taskDir);
    return OK;
}

// 获取所有进程-子线程映射
void GetAllProcess2ThreadMap(const std::vector<int> &pids, std::map<int, std::vector<int>> *mp) {
    std::vector<int>::const_iterator it;
    for (it = pids.begin(); it != pids.end(); it++) {
        std::vector<int> threads;
        GetChildThreads(*it, &threads); // 获取该进程下所有子线程
        if (!threads.empty()) {
            (*mp)[*it] = threads;
        }
    }
}



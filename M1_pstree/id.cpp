#include "id.h"
#include <dirent.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
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
std::vector<int> GetAllPids() {
    std::vector<int> pids;
    DIR *processDir = opendir("/proc");
    if (processDir != nullptr) {
        struct dirent *readDir;
        while ((readDir = readdir(processDir)) != nullptr) {
            char *processID = readDir->d_name;
            if (isID(processID)) {
                pids.push_back(std::stoi(processID));
            }
        }
    }
    closedir(processDir); // 关闭目录
    return pids;
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
std::map<int, std::vector<int>> GetAllParent2ChildProcessMap(std::vector<int> pids) {
    std::map<int, std::vector<int>> mp; // 父-子进程映射

    std::vector<int>::iterator it;
    for (it = pids.begin(); it != pids.end(); it++) {
        if (*it == 2) continue; // 忽略内核空间进程
        int ppID = GetPPID(*it); // 获取父进程
        if (ppID == 2) continue; // 忽略内核空间进程
        mp[ppID].push_back(*it);
    }
    return mp;
}

// 获取该进程下所有子线程
std::vector<int> GetChildThreads(int pID) {
    std::vector<int> threads;
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
                    threads.push_back(tID);
                }
            }
        }
    }
    closedir(taskDir);
    return threads;
}

// 获取所有进程-子线程映射
std::map<int, std::vector<int>> GetAllProcess2ThreadMap(std::vector<int> pids) {
    std::map<int, std::vector<int>> mp; // 进程-子线程映射
    std::vector<int>::iterator it;
    for (it = pids.begin(); it != pids.end(); it++) {
        std::vector<int> threads = GetChildThreads(*it); // 获取该进程下所有子线程
        if (!threads.empty()) {
            mp[*it] = threads;
        }
    }
    return mp;
}
#include <dirent.h>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "id.h"


int main() {
    std::vector<int> pids = GetAllPids(); // 获取所有进程的PID

    if (!GetAllPids().empty()) {
        std::map<int, std::vector<int>> mp_p; // 父-子进程映射
        std::map<int, std::vector<int>> mp_t; // 进程-子线程映射
        mp_p = GetAllParent2ChildProcessMap(pids);
        mp_t = GetAllProcess2ThreadMap(pids);


        std::map<int, std::vector<int>>::iterator it;
        for (it = mp_p.begin(); it != mp_p.end(); it++) {
            std::cout << it->first << "的子进程为：";
            std::vector<int>::iterator x;
            for (x = it->second.begin(); x != it->second.end(); x++) {
                std::cout << *x << " ";
            }
            std::cout << std::endl;
        }

        std::map<int, std::vector<int>>::iterator itt;
        for (itt = mp_t.begin(); itt != mp_t.end(); itt++) {
            std::cout << itt->first << "的线程为：";
            std::vector<int>::iterator x;
            for (x = itt->second.begin(); x != itt->second.end(); x++) {
                std::cout << *x << " ";
            }
            std::cout << std::endl;
        }

    }


    return 0;

}
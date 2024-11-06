#include <dirent.h>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "id.h"

void showPstree(int pid, int deep, std::map<int, std::vector<int>> &mp_p,
                std::map<int, std::vector<int>> &mp_t) {
    // 打印子进程
    if (mp_p.find(pid) != mp_p.end()) {
        std::vector<int>::iterator it_p;
        for (it_p = mp_p[pid].begin(); it_p != mp_p[pid].end(); it_p++) {
            for (int i = 0; i < deep; i++) std::cout << "  ";
            std::cout << "+-" << *it_p << std::endl;
//            if (it_p != mp_p[pid].begin())std::cout << std::endl;
            showPstree(*it_p, deep + 1, mp_p, mp_t);
        }
    }
}

int main() {
    std::vector<int> pids;
    GetAllPids(&pids); // 获取所有进程的PID
    std::map<int, std::vector<int>> mp_p; // 父-子进程映射
    std::map<int, std::vector<int>> mp_t; // 进程-子线程映射

    if (!pids.empty()) {
        GetAllParent2ChildProcessMap(pids, &mp_p); // 获得所有父-子进程映射
        GetAllProcess2ThreadMap(pids, &mp_t); // 获取所有进程-子线程映射

//        std::map<int, std::vector<int>>::iterator it;
//        for (it = mp_p.begin(); it != mp_p.end(); it++) {
//            std::cout << it->first << "的子进程为：";
//            std::vector<int>::iterator x;
//            for (x = it->second.begin(); x != it->second.end(); x++) {
//                std::cout << *x << " ";
//            }
//            std::cout << std::endl;
//        }
//
//        std::map<int, std::vector<int>>::iterator itt;
//        for (itt = mp_t.begin(); itt != mp_t.end(); itt++) {
//            std::cout << itt->first << "的线程为：";
//            std::vector<int>::iterator x;
//            for (x = itt->second.begin(); x != itt->second.end(); x++) {
//                std::cout << *x << " ";
//            }
//            std::cout << std::endl;
//        }

    }

    showPstree(mp_p.begin()->first, 0, mp_p, mp_t); //递归打印


    return 0;

}
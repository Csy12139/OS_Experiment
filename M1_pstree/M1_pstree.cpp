#include <dirent.h>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "id.h"
#include "screen.h"

void showPstree(int pid, struct ScreenCursor *SCursor, std::map<int, std::vector<int>> &mp_p,
                std::map<int, std::vector<int>> &mp_t) {
    // 打印子进程
    if (mp_p.find(pid) != mp_p.end()) {
        struct ScreenCursor *SCursor_1 = SCursor;
        auto *SCursor_2 = new ScreenCursor;
        auto is_end = mp_p[pid].end();
        is_end--;
        std::vector<int>::iterator it_p;
        for (it_p = mp_p[pid].begin(); it_p != mp_p[pid].end(); it_p++) {
            Screen_Write(*SCursor_1, ("-" + std::to_string(*it_p)).c_str()); // 打印该进程
            *SCursor_2 = GetCursor();
            showPstree(*it_p, SCursor_2, mp_p, mp_t);
            if (it_p != is_end)SCursor_1->height = SCursor_2->height + 1;
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
    struct ScreenCursor SCursor{1, 1};
    initscr();
    showPstree(mp_p.begin()->first, &SCursor, mp_p, mp_t); //递归打印
    getch(); // 等待用户输入
    endwin();

    return 0;

}
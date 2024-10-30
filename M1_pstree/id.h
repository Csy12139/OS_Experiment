#ifndef OS_EXPERIMENT_ID_H
#define OS_EXPERIMENT_ID_H

#include <vector>
#include <map>

// 是否是ID号
bool isID(char *str);

// 获取所有进程的PID
std::vector<int> GetAllPids();

// 获取该进程的父进程
int GetPPID(int pID);

// 获得所有父-子进程映射
std::map<int, std::vector<int>> GetAllParent2ChildProcessMap(std::vector<int> pids);

// 获取该进程下所有子线程
std::vector<int> GetChildThreads(int pID);

// 获取所有进程-子线程映射
std::map<int, std::vector<int>> GetAllProcess2ThreadMap(std::vector<int> pids);

#endif //OS_EXPERIMENT_ID_H

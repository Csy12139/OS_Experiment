#ifndef OS_EXPERIMENT_ID_H
#define OS_EXPERIMENT_ID_H

#include <vector>
#include <map>

// 是否是ID号
bool isID(char *str);

// 获取所有进程的PID
void GetAllPids(std::vector<int> *pids);

// 获取该进程的父进程
int GetPPID(int pID);

// 获得所有父-子进程映射
void GetAllParent2ChildProcessMap(std::vector<int> pids, std::map<int, std::vector<int>> *mp);

// 获取该进程下所有子线程
void GetChildThreads(int pID, std::vector<int> *threads);

// 获取所有进程-子线程映射
void GetAllProcess2ThreadMap(std::vector<int> pids, std::map<int, std::vector<int>> *mp);


#endif //OS_EXPERIMENT_ID_H

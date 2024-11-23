#ifndef CTHREADPOOL_H
#define CTHREADPOOL_H
#include<queue>
#include<functional>
#include<vector>
#include<Windows.h>
#include<process.h>

class CThreadPool
{
public:
public:
    CThreadPool(int threadSize = 4);
    ~CThreadPool();
    CThreadPool(const CThreadPool& pool);
    CThreadPool& operator=(const CThreadPool& pool);
    void addTask(std::function<void()> task);
private:
    static HANDLE m_pushMutex;//如果涉及多线程对任务队列进行任务投递，确保互斥投入
    bool m_isStop;
    std::queue<std::function<void()>> m_taskQueue; //任务队列,每一个任务都是void()类型
    std::vector<HANDLE> m_threadPool; //线程池
    HANDLE m_tastQueueMutex; //线程池互斥访问任务队列的锁
    HANDLE m_sem; //任务队列通知空闲线程的信号量
    void destoryThreadPool(); //销毁线程池
    static unsigned WINAPI threadWorkerEntry(LPVOID arg);
    void threadWork();//每一个线程都执行的逻辑
};

#endif // CTHREADPOOL_H

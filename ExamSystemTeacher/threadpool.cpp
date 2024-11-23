#include "threadpool.h"


HANDLE CThreadPool::m_pushMutex = CreateMutex(nullptr,FALSE,nullptr);

CThreadPool::CThreadPool(int threadSize)
{
    this->m_isStop = false;
    this->m_tastQueueMutex = CreateMutex(nullptr,FALSE,nullptr);
    this->m_sem = CreateEvent(nullptr,FALSE,FALSE,nullptr);
    //同时开启n条线程
    for (int i = 0 ; i < threadSize;i++)
    {
        HANDLE thread = (HANDLE)_beginthreadex(nullptr,0,&CThreadPool::threadWorkerEntry,this,0,nullptr);
        this->m_threadPool.push_back(std::move(thread));
    }
}

CThreadPool::~CThreadPool()
{
    this->destoryThreadPool();
}

CThreadPool::CThreadPool(const CThreadPool& pool){}

CThreadPool& CThreadPool::operator=(const CThreadPool& pool) {}

void CThreadPool::addTask(std::function<void()> task)
{
    WaitForSingleObject(CThreadPool::m_pushMutex,INFINITE);
    if (task == nullptr)
    {
        return;
    }
    this->m_taskQueue.push(std::move(task));
    SetEvent(this->m_sem);
    ResetEvent(this->m_sem);
    ReleaseMutex(CThreadPool::m_pushMutex);
}

void CThreadPool::destoryThreadPool()
{
    this->m_isStop = true; //进行销毁线程池的关键变量
    //清除并等待线程池中的线程任务完成后销毁所有线程
    for (int i = 0 ; i < this->m_threadPool.size(); i++)
    {
        SetEvent(this->m_sem);
        ResetEvent(this->m_sem);
    }
}

unsigned WINAPI CThreadPool::threadWorkerEntry(LPVOID arg)
{
    CThreadPool* thiz = (CThreadPool*)arg;
    thiz->threadWork();
    _endthreadex(0);
    return 0;
}

void CThreadPool::threadWork()
{
    while (true)
    {
        WaitForSingleObject(this->m_tastQueueMutex, INFINITE);
        WaitForSingleObject(this->m_sem, INFINITE);
        if (this->m_isStop && this->m_taskQueue.size() == 0)
        {
            //释放锁并且结束线程
            ReleaseMutex(this->m_tastQueueMutex);
            return;
        }

        std::function<void()> task = this->m_taskQueue.front();
        this->m_taskQueue.pop();
        ReleaseMutex(this->m_tastQueueMutex); //记得在任务之前去进行释放锁
        if (task != nullptr)
        {
            task();
        }
    }
}

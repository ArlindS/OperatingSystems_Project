#include "schedulerFcfs.h"
#include "process.h"

#include <deque>
using namespace std;

bool CpuSchedulerFcfs::addProcess(Process process)
{
    lock_guard<mutex> lck(m_mutex);
    m_queue.push_back(process.processId());
    return true;
}

// add a process back to the scheduling queue
bool CpuSchedulerFcfs::requeueProcess(Process process)
{
    lock_guard<mutex> lck(m_mutex);
    m_queue.push_front(process.processId());
    return true;
}

// Find the next process to run and remove from data structure 
int CpuSchedulerFcfs::nextProcess()
{
    lock_guard<mutex> lck(m_mutex);

    if (!m_queue.empty())
    {
        int n = m_queue.front();
        m_queue.pop_front();
        return n;
    }
    else
    {
        return -1;
    }
}
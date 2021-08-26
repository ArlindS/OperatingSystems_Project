#include "schedulerPriorityRR.h"
#include "process.h"

#include <map>
#include <deque>

bool CpuSchedulerPriorityRr::addProcess(Process process)
{
    lock_guard<mutex> lck(m_mutex);
    // Our map has a set of queues by priority. This adds the process ID 
    // to the end of the queue associated with this process's priority
    m_priorityMap[process.priority()].push_back(process.processId());
    return true;
}

// Remove a process from the scheduling queue
bool CpuSchedulerPriorityRr::requeueProcess(Process process)
{
    lock_guard<mutex> lck(m_mutex);

    m_priorityMap[process.priority()].push_back(process.processId());
    return true;
}

// Find the next process to run
int CpuSchedulerPriorityRr::nextProcess()
{
    lock_guard<mutex> lck(m_mutex);

    // Find the first priority bucket with entries
    auto iter = m_priorityMap.begin();
    while (iter != m_priorityMap.end())
    {
        if (!iter->second.empty())
        {
            int result = iter->second.front();

            // Now pop it off the front and push it on the back
            iter->second.pop_front();
            return result;
        }
        ++iter;
    }

    return -1;
}

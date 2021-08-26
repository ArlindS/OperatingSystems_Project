#include "schedulerPriorityRR.h"

bool CpuSchedulerPriorityRoundRobin::addProcess(Process process)
{
    scheduler[process.get_priority()].push_back(process);
    return true;
}

bool CpuSchedulerPriorityRoundRobin::removeProcess(Process process)
{
    if (process.get_cpu_needed() == process.get_cpu_used())
    {
        scheduler[process.get_priority()].pop_front();
        return true;
    }
    else
    {
        scheduler[process.get_priority()].push_back(scheduler[process.get_priority()].front());
        scheduler[process.get_priority()].pop_front();
        return true;
    }
    return false;
}

int CpuSchedulerPriorityRoundRobin::nextProcess()
{
    for (int i = 0; i < scheduler.size(); i++)
        if (!scheduler[i].empty())
            return scheduler[i].front().get_pid();

    return -1;
}

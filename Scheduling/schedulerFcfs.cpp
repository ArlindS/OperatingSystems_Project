#include "schedulerFcfs.h"

bool CpuSchedulerFcfs::addProcess(Process process)
{
    scheduler.push(process);
    return true;
}

bool CpuSchedulerFcfs::removeProcess(Process process)
{
    if (!scheduler.empty() && process.get_pid() == scheduler.front().get_pid() && process.get_cpu_needed() == process.get_cpu_used())
    {
        scheduler.pop();
        return true;
    }
    return false;
}

int CpuSchedulerFcfs::nextProcess()
{
    if (scheduler.empty())
        return -1;
    return scheduler.front().get_pid();
}
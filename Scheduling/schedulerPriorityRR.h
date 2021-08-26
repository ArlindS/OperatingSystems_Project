#ifndef CPU_SCHEDULER_PRIORITY_RR_H
#define CPU_SCHEDULER_PRIORITY_RR_H

// cpu_scheduler_priority_rr.h
//
// Abstract base class of a CPU scheduler.
#include <deque>
#include <map>
#include "process.h"
#include "schedulerBase.h"

using namespace std;
class CpuSchedulerPriorityRoundRobin : public CpuSchedulerBase
{

public:
    // Add a new process to the set of processes to be
    // scheduled.
    virtual bool addProcess(Process process);

    // Remove a process from the scheduler (generally
    // because it's done).
    virtual bool removeProcess(Process process);

    // Get the process id of the next process to be scheduled
    // If no processes remain to schedule, return -1
    virtual int nextProcess();

private:

    map<int, deque<Process>> scheduler;
};

#endif // CPU_SCHEDULER_PRIORITY_RR_H

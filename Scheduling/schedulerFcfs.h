#ifndef CPU_SCHEDULER_FCFS_H
#define CPU_SCHEDULER_FCFS_H

// schedulerFcfs.h
//
// Abstract base class of a CPU scheduler.

#include "process.h"
#include "schedulerBase.h"
#include <queue>

using namespace std;

class CpuSchedulerFcfs : public CpuSchedulerBase
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
    queue<Process> scheduler;

    
};

#endif 

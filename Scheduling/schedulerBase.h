#ifndef CPU_SCHEDULER_BASE_H
#define CPU_SCHEDULER_BASE_H

// cpu_scheduler_base.h
//
// Abstract base class of a CPU scheduler.

#include "process.h"

class CpuSchedulerBase {

    public:

        // Add a new process to the set of processes to be
        // scheduled.
        virtual bool addProcess(Process process) = 0;

        
        // Remove a process from the scheduler (generally
        // because it's done).
        virtual bool removeProcess(Process process) = 0;

        // Get the process id of the next process to be scheduled
        // If no processes remain to schedule, return -1
        virtual int nextProcess() = 0;
};

#endif
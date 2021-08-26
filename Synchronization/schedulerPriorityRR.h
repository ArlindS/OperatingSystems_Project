#ifndef CPU_SCHEDULER_PRIORITY_RR_H
#define CPU_SCHEDULER_PRIORITY_RR_H

// schedulerPriorityRR.h
//
// Abstract base class of a CPU scheduler.
#include "process.h"
#include "schedulerBase.h"
#include "process.h"

#include <map>
#include <deque>
#include <mutex>

using namespace std;

class CpuSchedulerPriorityRr : public CpuSchedulerBase {

    public:

        // Add a new process to the set of processes to be
        // scheduled.
        virtual bool addProcess(Process process);

        // Put a process that was previously scheduled back
        // into the scheduler. 
        virtual bool requeueProcess(Process process);

        // Get the process id of the next process to be scheduled
        // If no processes remain to schedule, return -1.
        virtual int nextProcess();

    private:
        map<int, deque<int> > m_priorityMap;

        // This mutex should be used to synchronize access to 
        // class methods
        mutex m_mutex;
};

#endif
#ifndef PROCESS_TABLE_H
#define PROCESS_TABLE_H

// processTable.h
//
// Class definition for the process table in our operating system

#include "process.h"
#include <mutex>
#include <iostream>

class ProcessTable {
public:

    // Initialize the process table with the maximum number
    // of processes allowed
    ProcessTable(int size = 100);
    ~ProcessTable();

    // Add public member functions here
    int getSize();
    int add(const Process& p);
    int remove(int processId);
    Process& find(int processId);

    // To enable printing the object
    friend std::ostream& operator<<(std::ostream& os, const ProcessTable& t);

private:
   // Add private member variables here

    int m_tableSize;
    Process* m_processTable;

    int m_currentIdx;
    mutex m_mutex;
};

#endif
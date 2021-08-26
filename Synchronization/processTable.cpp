// processTable.cpp
//
// Implementation of the ProcessTable class

#include "processTable.h"
#include "process.h"
#include <string>
#include <iostream>

using namespace std;

ProcessTable::ProcessTable(int size) :
    m_tableSize(size), m_currentIdx(-1), m_processTable(NULL)
{
    m_processTable = new Process[m_tableSize];
}

ProcessTable::~ProcessTable()
{
    delete[] m_processTable;
}

int ProcessTable::getSize()
{
    return m_tableSize;
}

int ProcessTable::add(const Process& p)
{
    int newIdx = -1;
    lock_guard<mutex> lck(m_mutex);

    for (int i = (m_currentIdx + 1) % m_tableSize;
         i != m_currentIdx;
         i = (i + 1) % m_tableSize)
    {

        if (m_processTable[i].processId() == -1)
        {
            newIdx = i;
            break;
        }
    }
    if (newIdx == -1)
    {
        return -1;
    }

    m_processTable[newIdx] = p;
    m_processTable[newIdx].setProcessId(newIdx + 1);

    m_currentIdx = newIdx;
    return newIdx + 1;
}


int ProcessTable::remove(int processId)
{
    lock_guard<mutex> lck(m_mutex);

    if (m_processTable[processId - 1].processId() == -1)
    {
        return -1;
    }

    m_processTable[processId - 1].setProcessId(-1);
    m_processTable[processId - 1].setProcessName("");
    return 0;
}

Process& ProcessTable::find(int processId)
{
    // Return this when we don't find the process id requested
    static Process notFound("", 0, 0, -1);
    lock_guard<mutex> lck(m_mutex);

    if (m_processTable[processId - 1].processId() == -1)
    {
        return notFound;
    }

    return m_processTable[processId - 1];
}


// Friend function to print the object
std::ostream& operator<<(std::ostream& os, const ProcessTable& t)
{
    for (int i = 0; i < t.m_tableSize; ++i)
    {
        if (t.m_processTable[i].processId() != -1)
        {
            os << t.m_processTable[i] << endl;
        }
    }
    return os;
}

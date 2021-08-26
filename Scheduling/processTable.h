#ifndef PROCESS_TABLE_H
#define PROCESS_TABLE_H

// processTable.h
//
// Class definition for the process table in our operating system

#include "process.h"

#include <iostream>
using namespace std;
class ProcessTable
{
public:
    ProcessTable(int size = 100);
    ~ProcessTable();

    int add_process(const Process &p);
    int get_current_pos() const { return curr_pos; }
    int get_curr_size() const { return curr_size; }
    int get_size() const { return size - 1; }
    bool remove(Process &p);
    Process &find(const int id);

    // To enable printing the object
    friend ostream &operator<<(ostream &os, const ProcessTable &t);

private:
    int curr_pos;
    int curr_size;
    int size;
    Process *table;
};

#endif // PROCESS_TABLE_H
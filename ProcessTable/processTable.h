#ifndef PROCESS_TABLE_H
#define PROCESS_TABLE_H

// process_table.h

#include "process.h"

#include <iostream>
using namespace std;
class ProcessTable
{
public:
    ProcessTable(int size = 100);
    ~ProcessTable();

    int add_process(const Process &p);
    int get_current_size() const { return curr_add; }
    int get_size() const { return size - 1; }
    bool remove(Process &p);
    Process &find(const int id);

    // To enable printing the object
    friend ostream &operator<<(ostream &os, const ProcessTable &t);

private:
    int curr_add;
    int size;
    Process *table;
};

#endif // PROCESS_TABLE_H
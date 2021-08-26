// processTable.cpp
//
// Implementation of the ProcessTable class

#include "processTable.h"
#include "process.h"

ProcessTable::ProcessTable(int size)
    : curr_pos{1}, size{size + 1}, curr_size{0}, table{new Process[size + 1]} { table[0] = Process("Process Name \t PID \t Priority \t CPU Needed \t CPU Used"); }

ProcessTable::~ProcessTable()
{
    delete[] table;
}

int ProcessTable::add_process(const Process &p)
{
    // Check when table at last index (circular array)
    if (curr_pos == size)
        for (int i = 1; i < size; i++)
        {
            if (table[i].get_process_name() == "<empty>")
            {
                table[i].set_process_name(p.get_process_name());
                table[i].set_pid(i);
                table[i].set_priority(p.get_priority());
                table[i].set_cpu_needed(p.get_cpu_needed());
                curr_pos = i;
                curr_size++;
                return i;
            }
        }
    else if (table[curr_pos].get_process_name() == "<empty>")
    {
        table[curr_pos].set_process_name(p.get_process_name());
        table[curr_pos].set_pid(curr_pos);
        table[curr_pos].set_priority(p.get_priority());
        table[curr_pos].set_cpu_needed(p.get_cpu_needed());
        curr_pos++;
        curr_size++;
        return curr_pos;
    }

    return -1;
}

bool ProcessTable::remove(Process &p)
{
    for (int i = 1; i < size; i++)
    {
        if (table[i].get_process_name() == p.get_process_name())
        {
            table[i].set_process_name("<empty>");
            table[i].set_pid(0);
            table[i].set_priority(-1);
            table[i].set_cpu_needed(0);
            table[i].set_cpu_used(0);
            curr_size--;
            return true;
        }
    }
    return false;
}
Process &ProcessTable::find(const int id)
{
    if (id > get_size() || id < 1)
    {
        return table[0]; // returns title of table with -1 index
    }
    if (table[id].get_process_name() != "<empty>")
        return table[id];

    return table[id];
}

ostream &operator<<(ostream &os, const ProcessTable &t)
{
    for (int i = 0; i < t.size; i++)
        os << t.table[i] << endl;

    return os;
}
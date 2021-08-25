// process_table.cpp


#include "processTable.h"
#include "process.h"

ProcessTable::ProcessTable(int size)
    : curr_add{1}, size{size + 1}, table{new Process[size + 1]} { table[0] = Process("Process Name \t Process ID"); }

ProcessTable::~ProcessTable()
{
    delete[] table;
    table = NULL;
}

int ProcessTable::add_process(const Process &p)
{
    // Check when table at last index (circular array)
    if (this->curr_add == this->size)
        for (int i = 1; i < this->size; i++)
        {
            if (this->table[i].get_process_name() == "<empty>")
            {
                this->table[i].set_process_name(p.get_process_name());
                this->table[i].set_pid(i);
                this->curr_add = i;
                return i;
            }
        }
    else if (this->table[this->curr_add].get_process_name() == "<empty>")
    {
        this->table[this->curr_add].set_process_name(p.get_process_name());
        this->table[this->curr_add].set_pid(this->curr_add);
        this->curr_add++;
        return this->curr_add;
    }

    return -1;
}

bool ProcessTable::remove(Process &p)
{
    for (int i = 1; i < this->size; i++)
    {
        if (this->table[i].get_process_name() == p.get_process_name())
        {
            this->table[i].set_process_name("<empty>");
            this->table[i].set_pid(0);
            return true;
        }
    }
    return false;
}
Process &ProcessTable::find(const int id)
{
    if (id > this->get_size() || id < 1)
    {
        return this->table[0]; // returns title of table with -1 index
    }
    if (this->table[id].get_process_name() != "<empty>")
        return this->table[id];

    return this->table[id];

    /*static Process notFound("", -1);

    if (m_processTable[processId - 1].processId() == -1)
    {
        return notFound;
    }

    return m_processTable[processId - 1];*/
}

ostream &operator<<(ostream &os, const ProcessTable &t)
{
    for (int i = 0; i < t.size; i++)
        os << t.table[i] << endl;

    return os;
}
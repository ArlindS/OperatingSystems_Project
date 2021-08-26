// process.cpp
//
// Include your implementation of the Process class here.

#include "process.h"
#include "nlohmann/json.hpp"
#include <iostream>
#include <sstream>

using namespace std;

Process::Process(string name, int pid, int prior, int cn, int cu)
    : process_name{name}, process_id{pid}, priority{prior}, cpu_needed{cn}, cpu_used{cu} {}

ostream &operator<<(ostream &os, const Process &p)
{
    if (p.get_pid() > 0)
        os << p.get_process_name() << " \t " << p.get_pid() << " \t " << p.get_priority() << " \t\t " << p.get_cpu_needed() << " \t\t " << p.get_cpu_used();
    else
        os << p.get_process_name();
    return os;
}

int Process::run(int numCycles)
{
    if (cpu_needed <= numCycles || cpu_used + numCycles > cpu_needed)
    {
        cpu_used += cpu_needed;
        return cpu_used;
    }
    cpu_used += numCycles;
    return cpu_used;
}

void to_json(nlohmann::json &j, const Process &p)
{
    j["process_name"] = p.get_process_name();
    j["process_id"] = p.get_pid();
    j["priority"] = p.get_priority();
    j["cpu_needed"] = p.get_cpu_needed();
}

void from_json(const nlohmann::json &j, Process &p)
{
    if (j.contains("process_name"))
        p.set_process_name(j["process_name"]);
    else
    {
        ostringstream o;
        o << "Missing process_name in json input: " << j;
        throw(invalid_argument(o.str()));
    }

    if (j.contains("process_id"))
        p.set_pid(j["process_id"]);

    if (j.contains("priority"))
        p.set_priority(j["priority"]);

    if (j.contains("cpu_needed"))
        p.set_cpu_needed(j["cpu_needed"]);
}
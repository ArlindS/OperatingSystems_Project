// process.cpp


#include "process.h"
#include "nlohmann/json.hpp"
#include <sstream>
#include <iostream>

using namespace std;

Process::Process(string name)
    : process_name{name}, process_id{-1} {}

ostream &operator<<(ostream &os, const Process &p)
{
    if (p.get_pid() > 0)
        os << p.get_process_name() << " \t " << p.get_pid();
    else
        os << p.get_process_name();
    return os;
}

void to_json(nlohmann::json &j, const Process &p)
{
    j["process_name"] = p.get_process_name();
    j["process_id"] = p.get_pid();
}

void from_json(const nlohmann::json &j, Process &p)
{
    if (j.contains("process_name"))
    {
        p.set_process_name(j["process_name"]);
    }
    else
    {
        ostringstream o;
        o << "Missing process_name in json input: " << j;
        throw(invalid_argument(o.str()));
    }

    if (j.contains("process_id"))
    {
        p.set_pid(j["process_id"]);
    }
}
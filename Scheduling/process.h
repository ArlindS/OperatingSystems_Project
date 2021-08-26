#ifndef PROCESS_H
#define PROCESS_H

// process.h
//
// Class definition for a simulated process in our operating system
//

#include <iostream>
#include "nlohmann/json.hpp"
using namespace std;

class Process
{
public:
    Process(string name = "<empty>", int pid = -1, int prior = 100, int cn = 0, int cu = 0);

    // Class functions
    int run(int numCycles);

    // Getter functions
    string get_process_name() const { return process_name; }
    int get_pid() const { return process_id; }
    int get_priority() const { return priority; }
    int get_cpu_needed() const { return cpu_needed; }
    int get_cpu_used() const { return cpu_used; }

    // Setter Functions
    void set_process_name(const string pName) { process_name = pName; }
    void set_pid(const int pid) { process_id = pid; }
    void set_priority(const int prior) { priority = prior; }
    void set_cpu_needed(const int cn) { cpu_needed = cn; }
    void set_cpu_used(const int cu) { cpu_used = cu; }

    friend ostream &operator<<(ostream &os, const Process &p);

private:
    string process_name;
    int process_id;
    int priority;
    int cpu_needed;
    int cpu_used;
};

void to_json(nlohmann::json &j, const Process &p);
void from_json(const nlohmann::json &j, Process &p);

#endif // PROCESS_H
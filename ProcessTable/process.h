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
    // Constructors
    Process(string name = "<empty>");

    // Getter functions
    string get_process_name() const { return process_name; }
    int get_pid() const { return process_id; }

    // Setter Functions
    void set_process_name(const string pName) { process_name = pName; }
    void set_pid(const int pid) { process_id = pid; }

    friend ostream &operator<<(ostream &os, const Process &p);

private:
    string process_name;
    int process_id;
};

void to_json(nlohmann::json &j, const Process &p);
void from_json(const nlohmann::json &j, Process &p);

#endif 
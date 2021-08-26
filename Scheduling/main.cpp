// Main program for Process Scheduling
//
// This program will be run as follows:
//
// main --algorithm=<algo> <json_files>
//    Where <algo> will be either "fcfs" or "priority", and
//          <json_files> is a set of one or more processes to run

#include "schedulerBase.h"
#include "schedulerFcfs.h"
#include "schedulerPriorityRR.h"
#include "process.h"
#include "processTable.h"
#include <string>
#include <iostream>
#include <getopt.h>
#include <fstream>

using namespace std;

int main(int argc, char **argv)
{
    CpuSchedulerBase *scheduler; // Scheduler that will be used
    string algorithm;            // String choosing which scheduling algorithm to use
    int tableSize = 100;

    
    extern char *optarg;
    extern int optind, opterr, optopt;

    static struct option program_options[] = {
        {"table_size", optional_argument, 0, 's'},
        {"algorithm", required_argument, 0, 'a'},
        {0, 0, 0, 0}};

    int option_index = 0;

    int c = 0;

    while (c != -1)
    {
        // Returns the
        c = getopt_long(argc, argv, "a:s",
                        program_options, &option_index);
        switch (c)
        {
        case -1:
            // getopt_long returns -1 when it reaches the end of
            // the argument list.
            break;
        case 's':
            // table_size
            tableSize = atoi(optarg);
            if (tableSize <= 0)
            {
                cerr << "Error: --table_size must be a positive number!" << endl;
                return (1);
            }
            break;
        case 'a':
            if (string(optarg) == "fcfs" || string(optarg) == "priority")
                algorithm = string(optarg);
            else
            {
                cerr << "Error: --algorithm must be fcfs or rr" << endl;
                return (1);
            }
            break;
        case '?':
            // Unknown argument
            cerr
                << "Error: Invalid argument: "
                << argv[optind]
                << endl;
            return (3);
        }
    }
    if (algorithm == "")
    {
        cerr << "Error: --algorithm must be specified" << endl;
        return (1);
    }
    ProcessTable table(tableSize); // Will contain the processes to be scheduled

    // Allocate a scheduling object based on the
    // chosen algorithm.
    if (algorithm == "fcfs")
    {
        scheduler = (CpuSchedulerBase *)new CpuSchedulerFcfs;
    }
    else if (algorithm == "priority")
    {
        scheduler = (CpuSchedulerBase *)new CpuSchedulerPriorityRoundRobin;
    }

    // Load the processes from the input files into the process table

    for (; optind < argc; ++optind)
    {
        // Create a std::ifstream using the input file name.
        ifstream in(argv[optind]);
        if (!in)
        {
            cerr << "No input file." << endl;
            return EXIT_FAILURE;
        }

        nlohmann::json j;

        try
        {
            j = nlohmann::json::parse(in);
        }
        catch (nlohmann::json::parse_error &ex)
        {
            cerr << "parse error at byte " << ex.byte << endl;
        }

        // Iterate the contents of the input json, converting each entry into a
        // Process object. Add those Process objects into the ProcessTable.
        for (int i = 0; i < j["processes"].size(); i++)
        {
            Process p;
            from_json(j["processes"][i], p);
            table.add_process(p);
        }
    }
    cout << endl
         << "--------------------------- Table before scheduling run ---------------------------" << endl
         << table << endl;

    // Iterate the set of processes in the ProcessTable and add
    // each process to the scheduler-> Processes should be added
    // in order of process_id, from 1 to the maximum table size

    int pid = 0;
    while (pid <= table.get_curr_size())
    {
        if (table.find(pid).get_pid() != -1)
            scheduler->addProcess(table.find(pid));
        pid++;
    }

    // Run a loop to schedule one CPU cycle for each process
    // as long as there are still processes to schedule.
    cout << " --------------------------- Scheduler Running --------------------------- " << endl;
    while (table.find(scheduler->nextProcess()).get_pid() != -1)
    {
        if (table.find(scheduler->nextProcess()).get_cpu_used() < table.find(scheduler->nextProcess()).get_cpu_needed())
        {
            cout << table.find(scheduler->nextProcess()).get_process_name() << "(" << table.find(scheduler->nextProcess()).get_priority() << "): " << table.find(scheduler->nextProcess()).get_cpu_used() + 1 << "/" << table.find(scheduler->nextProcess()).get_cpu_needed() << endl;
            table.find(scheduler->nextProcess()).set_cpu_used(table.find(scheduler->nextProcess()).get_cpu_used() + 1);
        }
        scheduler->removeProcess(table.find(scheduler->nextProcess()));
    }
    cout << " --------------------------- Scheduler Finished --------------------------- " << endl;

    cout << endl
         << "--------------------------- Table after scheduling run ---------------------------" << endl
         << table << endl;
    return 0;
    // Each time a process runs, output a line of the following format:
    //
    //     <process_name>(<priority>): <total_cpu_cycles_so_far>/<total_cpu_needed>
    //
    // So if there is only one process called "process1" with priority 10 that needs 3
    // total CPU cycles, we would expect to see the following output:
    //
    // process1(10): 1/3
    // process1(10): 2/3
    // process1(10): 3/3
}
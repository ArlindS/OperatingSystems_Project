// Main program for Synchronization
//
// This program will be run as follows:
//
// run_processes --algorithm=<algo> --num_threads=<threads> <json_files>
//    Where <algo> will be either "fcfs" or "priority",
//          <threads> is the number of threads to run, and 
//          <json_files> is a set of one or more processes to run

#include "schedulerBase.h"
#include "schedulerFcfs.h"
#include "schedulerPriorityRR.h"
#include "process.h"
#include "processTable.h"

#include <getopt.h>
#include <iostream>
#include <fstream>

using namespace std;

// Thread functions take a single pointer to any data that
// they might need to use. 
struct processRunnerData {
    ProcessTable* table;
    CpuSchedulerBase* scheduler;
};


void* processRunner(void* data)
{
    struct processRunnerData* d = (struct processRunnerData*)data;

    int processToRun;
    while ((processToRun = d->scheduler->nextProcess()) != -1)
    {
        Process& p = d->table->find(processToRun);
        if (p.processId() == -1)
        {
            cerr << "Error finding process " << processToRun << " to run it!" << endl;
            //return;
        }

        p.run(1);
        cout << p.processName() << "(" << p.priority() << "): " << p.cpuUsed() << "/" << p.cpuNeeded() << endl;

        if (p.cpuUsed() < p.cpuNeeded())
        {
            // This process is done. Remove it from the scheduler
            d->scheduler->requeueProcess(p);
        }
    }

    pthread_exit(NULL);
}


int main(int argc, char** argv)
{
    ProcessTable table;             // Will contain the processes to be scheduled
    CpuSchedulerBase* scheduler;   // Scheduler that will be used 
    string algorithm;               // String choosing which scheduling algorithm to use
    int numThreads = 1;             // Number of threads to start

    extern char* optarg;
    extern int optind, opterr, optopt;

    static struct option program_options[] = {
        {"algorithm", required_argument, 0, 1},
        {"num_threads", required_argument, 0, 2},
        { 0, 0, 0, 0 }
    };

    int option_index = 0;

    int c = 0;

    while (c != -1)
    {
        c = getopt_long(argc, argv, "",
            program_options, &option_index);

        switch (c)
        {
            case -1:
                // getopt_long returns -1 when it reaches the end of
                // the argument list.
                break;
            case 1:
                // algorithm
                algorithm = optarg;
                if ((algorithm != "fcfs") && (algorithm != "priority"))
                {
                    cerr << "Error: Invalid value '" << algorithm << "' for --algorithm" << endl;
                    cerr << "       Legal values are 'fcfs' and 'priority'" << endl;
                    return(1);
                }
                break;
            case 2:
                numThreads = atoi(optarg);
                if (numThreads <= 0)
                {
                    cerr << "Error: --num_threads must be a positive number!" << endl;
                    return (1);
                }
                break;
            case '?':
                // Unknown argument
                cerr << "Error: Invalid argument: " << argv[optind] << endl;
                return(3);
        }
    }

    // Allocate a scheduling object based on the
    // chosen algorithm.
    if (algorithm == "fcfs")
    {
        scheduler = (CpuSchedulerBase*) new CpuSchedulerFcfs;
    }
    else if (algorithm == "priority")
    {
        scheduler = (CpuSchedulerBase*) new CpuSchedulerPriorityRr;
    }
    else
    {
        cerr << "No algorithm specified!" << endl;
        return(9);
    }

    for (; optind < argc; ++optind)
    {

        // Open the input file. 
        ifstream in(argv[optind]);
        if (!in.good())
        {
            cerr << "Failed to open file " << argv[optind] << endl;
            return(4);
        }

        nlohmann::json process_json;

        // Read the file into the json object.
        // If the input file is not in json format, this will
        // throw an exception

        try
        {
            in >> process_json;
        }
        catch (nlohmann::json::exception& e)
        {
            cerr << "Error: " << e.what() << endl
                << "exception id: " << e.id << endl;
            return(5);
        }


        // Iterate the entries in the input json,
        // converting each one to a Process object
        for (auto proc = process_json["processes"].begin();
            proc != process_json["processes"].end(); ++proc)
        {

            Process p;

            try
            {
                proc->get_to(p);
            }
            catch (nlohmann::json::exception& e)
            {
                // output exception information
                cerr << "Error: " << e.what() << endl
                    << "exception id: " << e.id << std::endl;
                return(6);
            }
            catch (std::invalid_argument& e)
            {
                cerr << "Error: " << e.what() << endl;
                return(7);
            }

            if (!table.add(p))
            {
                cerr << "Failed to add process: " << p.processName() << endl;
                return(8);
            }
        }
    }

    // Iterate the set of processes in the ProcessTable and add
    // each process to the scheduler. Processes are added 
    // in order of process_id, from 1 to the maximum table size

    for (int i = 1; i < table.getSize() + 1; ++i)
    {
        Process p = table.find(i);
        if (p.processId() != -1)
        {
            scheduler->addProcess(p);
        }
    }

    cout << endl << "-----------------------------------" << endl << "Process Table: " << endl << "-----------------------------------" << endl << table << endl;

    cout << "-----------------------------------" << endl << "PROCESS RUN" << endl << "-----------------------------------" << endl;
    pthread_t threads[numThreads];

    for (int i = 0; i < numThreads; ++i)
    {
        struct processRunnerData* d = new struct processRunnerData;

        d->scheduler = scheduler;
        d->table = &table;

        // This creates the thread
        pthread_create(&threads[i], NULL, processRunner, (void*)d);
    }

    void* ret;
    for (int i = 0; i < numThreads; ++i)
    {
        pthread_join(threads[i], &ret);
    }

    cout << endl << "-----------------------------------" << endl << "Process Table after process run: " << endl << "-----------------------------------" << endl << table << endl;

    return 0;
}
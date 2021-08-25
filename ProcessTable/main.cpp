// main.cpp
// Program to load the process table from one or more input files
//
// Arguments:
//    --table_size <size>

#include <getopt.h>
#include <fstream>
#include <iostream>

#include "nlohmann/json.hpp"
#include "processTable.h"
#include "process.h"

using namespace std;
int main(int argc, char **argv)
{

    // Table size defaults to 100 if not specified on the command line
    int tableSize = 100;

    // Process command line arguments
    // Use the getopt_long function to accept an optional command line
    // argument "table_size".

    int optind = 0;
    int long_index = 0;
    static struct option long_options[] = {{"table_size", required_argument, 0, 1}};
    if ((optind = getopt_long(argc, argv, "", long_options, &long_index) != -1))
    {
        tableSize = atoi(optarg);
        optind += 2;
    }

    // Initialize a ProcessTable with the table size obtained via the command-line arguments
    ProcessTable table(tableSize);

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

    // Print the contents of the table to cout

    cout << endl
         << table << endl;

    return 0;
}
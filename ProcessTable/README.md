# Process Table
A key data structure in any operating system is the process table. This table contains information about all progress in the system, and is used by other system components for such things as scheduling and process management.
# JSON
Configuration files in JSON format. The starter files include the nlohmann JSON header file
```
#include <nlohmann/json.hpp>
```
For details on how to use this json library, see https://github.com/nlohmann/json/blob/develop/README.md. 
# Process
The Process class. Each process will have the following attributes:
* Process Name (string) 
* Process ID (integer) 

# Process Table
The process table will contain all of the processes in the operating system. Implemented process table as a circular array. Process table takes the size of the process table as a parameter to the constructor, and allocates an array of that size to hold all of the processes in the system. Note that process ID's start at 1 (not 0). Processes are allocated sequentially; after reaching the end of the array, they should go back and start over with process number 1.

# Code tested in
File `test.cpp` 

# main.cpp
File `main.cpp` will read a json input file that contains a set of process definitions, and then print the resulting process table using the method implemented in the ProcessTable class.

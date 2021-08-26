# Process Scheduling

Process class enhanced to simulate a "running" process. A number of different CPU scheduling algorithms using this capability are implemented.

## Changes to the Process class

### Add new attributes

New attributes to Process class:

* `priority` - an integer value representing the scheduling priority of the process, where 0 repesents the highest priority. Assume that the default "standard-user" priority is 100.
* `cpu_needed` - the number of cpu cycles the process needs to run over its entire lifetime
* `cpu_used` - the number of cpu cycles that have actually executed for the process. This will be an internal attribute of the object.

Updated `Process` class as follows:
* Constructor can specify the new attributes at object creation time
* Appropriate set and get methods for these attributes
* Updated to_json and from_json methods to take the new attributes into account
* Updated print methods to display them

### Added `run` method

Add a new method to your Process class called `run`. 

`int run(int numCycles)`

The `run` method behaves as follows:

* The `numCycles` parameter indicates how many CPU cycles the process is allowed to use
* Calculates how many CPU cycles the process will actually use
* Update the `cpu_used` member to indicate how many cycles have been used overall
* Return the actual number of cycles used (which could be less than the value of the `numCycles` parameter)


# CPU Scheduler Classes

Implemented two different scheduling algorithms

## Base Class

A bade class for primary functions having following functions is created:
* `virtual bool addProcess(Process& process)`
* `virtual bool removeProcess(Process& process)`
* `virtual Process& nextProcess()`

## First Come, First-Served Scheduler

Implement a FCFS algorithms

## Priority round-robin scheduler

Implement a priority RR scheduler

# main

`main.cpp` is the main program that will use scheduling algorithms. The program will take the desired scheduling algorithm as a command line argument along with a set of json files defining the processes that should be run.

It will simulate running all of the processes from the input files.
# Synchronization

Implementation of multi-threaded execution of processes, which 
requires synchronization between the threads.

# Scheduler Classes

## Additions

* The `nextProcess()` method removes the process from its data structure when it returns a process to schedule.
* The `requeueProcess()` is used to put the process back into the scheduler after it has executed.

## Synchronization
Since this program will be multi-threaded, protection is added to the scheduler classes to ensure that the critical sections in classes are protected. 

The template header files define a mutex class member. `std::lock_guard` is used to protect each function in this class using the mutex. (This uses RAII to protect the critical sections)

# main
The `main.cpp` file implements thread-based execution.




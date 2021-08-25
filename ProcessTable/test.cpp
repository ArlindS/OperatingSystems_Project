// test.cpp
//
// Test program for the Process and ProcessTable classes

#include "process.h"
#include "process_table.h"
#include <getopt.h>

using namespace std;


int main(int argc, char **argv)
{
     Process p1("process1");
     cout << "Print out process : " << p1 << endl;

     Process p2("process2");
     Process p3("process3");

     ProcessTable t(3);
     int x = t.add_process(p1);
     int y = t.add_process(p2);

     cout << "Print out ProcessTable : " << endl
          << t;
     cout << "--------------------------------\n\n";
     bool rm = t.remove(p2);
     cout << "Result when value removed successfully : " << rm << endl
          << t;
     bool rm2 = t.remove(p2);
     cout << "Result when value removed UNsuccessfully : " << rm2 << endl;
     cout << "--------------------------------\n\n";
     y = t.add_process(p2);

     cout << t;
     cout << "--------------------------------\n\n";
     cout << "New value entered process3: \n";
     int z = t.add_process(p3);

     cout << t;

     Process p4("process4");
     int w = t.add_process(p4);
     cout << "Return value for process not entered in table : " << w << endl;
     Process p5 = t.find(3);
     cout << "Process in case FOUND : " << p5 << endl;
     bool rm3 = t.remove(p2);
     Process p6 = t.find(4);
     cout << "Process in case NOT found : " << p6 << endl;
     cout << "ProcessTable size = " << t.get_size() << endl;
}

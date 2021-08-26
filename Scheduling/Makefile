CPPFLAGS = -g -std=c++17 -I.

libsrc = process.cpp processTable.cpp schedulerFcfs.cpp schedulerPriorityRR.cpp
libobj = $(libsrc:.cpp=.o)

all: main $(libobj)

main: main.o $(libobj)
	$(CXX) -o $@ main.o $(libobj)

.PHONY: clean
clean:
	rm -f main main.o $(libobj)
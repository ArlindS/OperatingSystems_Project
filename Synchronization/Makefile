CPPFLAGS = -g -std=c++17 -I.
LDFLAGS = -lpthread

libsrc = process.cpp processTable.cpp schedulerFcfs.cpp schedulerPriorityRR.cpp
libobj = $(libsrc:.cpp=.o)

all: main.o $(libobj)

main: main $(libobj)
	$(CXX) -o $@ main.o $(libobj)


.PHONY: clean
clean:
	rm -f main main.o $(libobj)
CPPFLAGS = -g -I.

libsrc = process.cpp processTable.cpp
libobj = $(libsrc:.cpp=.o)

all: test main

test: test.o $(libobj)
	$(CXX) -o $@ test.o $(libobj)

main: main.o $(libobj)
	$(CXX) -o $@ main.o $(libobj)

.PHONY: clean
clean:
	rm -f $(libobj) test.o test main.o main
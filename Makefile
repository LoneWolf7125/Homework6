# Jonathan Snead
# jcs160330@utdallas.edu
# CS 3377.002

CXX = g++
CXXFLAGS = -Wall -g -Wno-write-strings

CPPFLAGS = -I/scratch/perkins/include
LDFLAGS = -L/scratch/perkins/lib

LDLIBS = -lcdk -lcurses 

EXECFILE = program6

OBJS = program6.o

all: $(EXECFILE)

clean:
	rm -f $(OBJS) $(EXECFILE) *.P *~ \#*

$(EXECFILE): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)


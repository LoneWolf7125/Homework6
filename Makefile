# Jonathan Snead
# jcs160330@utdallas.edu
# CS 3377.002

# Compiler used
CXX = g++

# All warnings and no const char * problems
CXXFLAGS = -Wall -g -Wno-write-strings

# To match his
CPPFLAGS = -I/scratch/perkins/include
LDFLAGS = -L/scratch/perkins/lib

# For CDK implementation
LDLIBS = -lcdk -lcurses 

# Executable 
EXECFILE = program6

# All .o files to make Exec work
OBJS = program6.o

# Will run with make
all: $(EXECFILE)

# Cleans up everything and removes un-needed files
clean:
	rm -f $(OBJS) $(EXECFILE) *.P *~ \#*

# To get the Exec file
$(EXECFILE): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)


# C++ compiler to use
CC = g++

# compile-time flags
CPPFLAGS = -std=c++14 -W -Werror -pedantic

# define the C++ source files
SRCS = # all source files (.cpp) 

# C++ object files 
# Replace suffix .c with .o suffix for each source file
OBJS = $(SRCS:.cpp=.o)

# define the executable file 
EXE = get_work_done

all: $(EXE)

$(EXE): $(OBJS) 
	$(CC) $(CPPFLAGS) $(OBJS) -o $(EXE)

# Suffix replacement rule, .cpp -> .o
# Automatic variables $< (.cpp) and $@ (.o)
.cpp.o:
	$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	rm *.o $(EXE)

# Object files to either reference or create
OBJECTS = daes.o main3.o
# The executable file that will be created at the end
EXEC = Daes
# The flags to use for compilation
FLAGS = -Wall
# The code compiler to use for compilation
CC = g++
#Libs
LIBS = -lcryptopp

# Perform action on all object files (May or may not exist)
all: $(OBJECTS)
	$(CC) $(FLAGS) -o $(EXEC) $(OBJECTS) $(LIBS)

XX = g++

all: main

# Compil files
main: main.cpp SequenceReader.cpp
	$(CXX) -Wall -Wextra -o main main.cpp SequenceReader.cpp

# Start the program
run: main
	./main

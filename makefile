XX = g++

all: main

# Compil files
main: main.cpp SequenceReader.cpp FastaSeq.cpp
	$(CXX) -Wall -Wextra -o main $^

# Start the program
run: main
	./main

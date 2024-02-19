XX = g++

all: main

# Compil filesgit switch <branch_name>
main: main.cpp SequenceReader.cpp FastaSeq.cpp
	$(CXX) -Wall -Wextra -o main $^

# Start the program
run: main
	./main
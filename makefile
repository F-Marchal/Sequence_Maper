XX = g++

all: main

# Compil filesgit switch <branch_name>
main: main.cpp Global/Sequence.cpp Fasta/Fasta.cpp Fasta/FastaSequence.cpp 
	$(CXX) -Wall -Wextra -o main $^

# Start the program
run: main
	./main
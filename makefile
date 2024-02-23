XX = g++

all: main

# Compil files
main: main.cpp ./Global/Header.cpp ./Global/Sequence.cpp ./Fasta/Fasta.cpp ./Fasta/FastaSequence.cpp
	$(CXX) -Wall -Wextra -o main $^

# Start the program
run: main
	./main

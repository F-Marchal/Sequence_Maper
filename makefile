XX = g++

all: main

# Compil files
main: main.cpp ./Global/*.cpp ./Fasta/*.cpp
	$(CXX) -Wall -Wextra -o main $^

# Start the program
run: main
	./main

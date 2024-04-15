XX = g++

all: main

# Compil files
main: main.cpp ./Global/*.cpp ./Fasta/FastaRelated.cpp ./Fasta/FastaHeader.cpp
	clear
	$(CXX) -Wall -Wextra -Werror -ansi -pedantic -std=c++14 -o main $^
# -ansi -pedantic

# Start the program
run: main
	./main

startDoxygen:
	doxywizard &

doxy:
	doxygen Doxyfile  
	firefox ./doc/html/index.html	
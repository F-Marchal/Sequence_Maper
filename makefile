XX = g++

all: main

# Compil files
<<<<<<< HEAD
main: main.cpp ./Global/*.cpp ./Fasta/*.cpp
	clear
	$(CXX) -Wall -Wextra -Werror -ansi -pedantic -std=c++14 -o main $^
# -ansi -pedantic
=======
main: main.cpp SequenceReader.cpp FastaSeq.cpp
	$(CXX) -Wall -Wextra -o main $^
>>>>>>> ed0cd54 (Update makefile.)

# Start the program
run: main
	./main

startDoxygen:
	doxywizard &

doxy:
	doxygen Doxyfile  
	firefox ./doc/html/index.html	
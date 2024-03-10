XX = g++

all: main

# Compil files
main: main.cpp ./Global/*.cpp
	$(CXX) -Wall -Wextra -o main $^
# -ansi -pedantic

# Start the program
run: main
	./main

startDoxygen:
	doxywizard &
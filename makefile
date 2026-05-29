CC=g++ 
FLAGS= -Wall -Wextra -pedantic-errors


%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

test: TESTS/catch_amalgamated.o TESTS/test.o connect4.o
	$(CC) $^ -o TESTS/test

TESTS/catch_amalgamated.o: TESTS/catch_amalgamated.hpp

TESTS/test.o: TESTS/catch_amalgamated.hpp connect4.h

connect4.o: connect4.h
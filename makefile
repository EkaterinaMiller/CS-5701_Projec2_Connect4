CC=g++ 
FLAGS= -Wall -Wextra -pedantic-errors


obj/%.o: src/%.cpp | obj
	$(CC) $(FLAGS) -c $< -o $@

test: TESTS/catch_amalgamated.o TESTS/test.o obj/connect4.o
	$(CC) $^ -o TESTS/test

TESTS/catch_amalgamated.o: TESTS/catch_amalgamated.hpp

TESTS/test.o: TESTS/catch_amalgamated.hpp obj/connect4.o

obj/connect4.o: src/connect4.cpp include/connect4.h

connect4_CLI: obj/main.o obj/connect4.o obj/human_player.o obj/AI_player.o obj/helpers.o
	$(CC) $^ -o connect4_CLI

obj/main.o: src/main.cpp include/connect4.h include/player.h include/human_player.h include/AI_player.h include/helpers.h
obj/connect4.o: src/connect4.cpp include/connect4.h
obj/human_player.o: src/human_player.cpp include/human_player.h include/player.h include/helpers.h
obj/AI_player.o: src/AI_player.cpp include/AI_player.h include/player.h
obj/helpers.o: src/helpers.cpp include/helpers.h

run_CLI: connect4_CLI
	./connect4_CLI

clean:
	rm -f *.o TESTS/*.o connect4_CLI TESTS/test

obj:
	mkdir -p obj
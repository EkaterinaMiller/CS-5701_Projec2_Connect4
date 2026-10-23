-include config.mk

CC=g++ 
FLAGS= -Wall -Wextra -pedantic-errors #-g
SFML_LIBS= -L$(SFML_DIR)/lib -lsfml-graphics -lsfml-window -lsfml-system
IFLAGS = -I$(SFML_DIR)/include

obj/%.o: src/%.cpp | obj
	$(CC) $(FLAGS) -c $< -o $@

run_tests: test
	./TESTS/test

test: TESTS/catch_amalgamated.o TESTS/test.o obj/connect4.o obj/human_player.o obj/AI_player.o obj/helpers.o
	$(CC) $(FLAGS) $^ -o TESTS/test

TESTS/catch_amalgamated.o: TESTS/catch_amalgamated.hpp

TESTS/test.o: TESTS/catch_amalgamated.hpp obj/connect4.o

obj/connect4.o: src/connect4.cpp include/connect4.h

connect4_CLI: obj/main.o obj/connect4.o obj/human_player.o obj/AI_player.o obj/helpers.o
	$(CC) $(FLAGS) $^ -o connect4_CLI

connect4_GUI: obj/gui_main.o obj/gui_board.o obj/gui_button.o obj/gui_game.o obj/gui_menu.o obj/connect4.o obj/AI_player.o
	$(CC) $(FLAGS) $^ -o connect4_GUI $(SFML_LIBS)

obj/main.o: src/main.cpp include/connect4.h include/player.h include/human_player.h include/AI_player.h include/helpers.h
obj/connect4.o: src/connect4.cpp include/connect4.h
obj/human_player.o: src/human_player.cpp include/human_player.h include/player.h include/helpers.h
obj/AI_player.o: src/AI_player.cpp include/AI_player.h include/player.h
obj/helpers.o: src/helpers.cpp include/helpers.h

obj/gui_%.o: src/gui_%.cpp | obj
	$(CC) $(FLAGS) $(IFLAGS) -c $< -o $@
GUI_HEADERS = include/gui_game.h include/gui_states.h include/gui_menu.h include/gui_board.h include/gui_button.h include/connect4.h include/player.h include/AI_player.h
obj/gui_main.o: src/gui_main.cpp $(GUI_HEADERS)
obj/gui_board.o:src/gui_board.cpp $(GUI_HEADERS)
obj/gui_button.o: src/gui_button.cpp $(GUI_HEADERS)
obj/gui_game.o: src/gui_game.cpp $(GUI_HEADERS)
obj/gui_menu.o:src/gui_menu.cpp $(GUI_HEADERS)

run_CLI: connect4_CLI
	./connect4_CLI

run_GUI: connect4_GUI
	./connect4_GUI

clean:
	rm -f obj/*.o connect4_CLI connect4_GUI TESTS/test 

obj:
	mkdir -p obj
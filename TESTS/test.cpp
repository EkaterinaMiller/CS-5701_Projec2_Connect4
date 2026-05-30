#include "catch_amalgamated.hpp"
#include "../connect4.h"

TEST_CASE("isWin()", "[Connect4 class]")
{
    SECTION("empty board"){                                          
        Connect4 game;
        CHECK(game.isWin('X')==false);
    }
    SECTION("horizontal win"){
        Connect4 game ({{{{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{'X', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{'X', 'O', 'X', 'X', 'X', 'X', ' '}},
                         {{'O', 'O', 'X', 'O', 'O', 'X', ' '}}}});
        CHECK(game.isWin('X')==true);
    }
    SECTION("vertical win"){
        Connect4 game ({{{{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{'X', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{'X', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{'X', 'O', 'X', 'O', 'X', 'X', ' '}},
                        {{'X', 'O', 'X', 'O', 'O', 'X', ' '}}}});
        CHECK(game.isWin('X')==true);
    }
    SECTION("main diagonal win"){
        Connect4 game ({{{{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{'X', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{'O', 'X', ' ', ' ', ' ', ' ', ' '}},
                        {{'X', 'O', 'X', 'O', 'X', 'X', ' '}},
                        {{'X', 'O', 'X', 'X', 'O', 'X', ' '}}}});
        CHECK(game.isWin('X')==true);
    }
    SECTION("main diagonal"){
        Connect4 game ({{{{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{'X', ' ', ' ', ' ', ' ', ' ', 'X'}},
                        {{'O', 'O', ' ', ' ', ' ', 'X', 'O'}},
                        {{'X', 'O', 'X', 'O', 'X', 'X', 'O'}},
                        {{'X', 'O', 'X', 'X', 'O', 'X', 'O'}}}});
        CHECK(game.isWin('X')==true);
    }
}
TEST_CASE("isFull()", "[Connect4 class]")
{
    SECTION("empty board"){                                          
        Connect4 game;
        CHECK(game.isFull()==false);
    }
    SECTION("full board"){
        Connect4 game ({{{{'X', 'O', 'X', 'O', 'X', 'O', 'X'}},
                         {{'X', 'O', 'X', 'O', 'X', 'O', 'X'}},
                         {{'X', 'O', 'X', 'O', 'X', 'O', 'X'}},
                         {{'X', 'O', 'X', 'O', 'X', 'O', 'X'}},
                         {{'X', 'O', 'X', 'O', 'X', 'O', 'X'}},
                         {{'X', 'O', 'X', 'O', 'X', 'O', 'X'}}}});
        CHECK(game.isFull()==true);
    }
}

#include "catch_amalgamated.hpp"
#include "../include/connect4.h"
#include "../include/AI_player.h"

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

TEST_CASE("countRow()", "[Connect4 class]")
{
    SECTION("empty board"){                                          
        Connect4 game;
        CHECK(game.countRow(0, 'X')==0);
    }
    SECTION("4 in the row"){
        Connect4 game ({{{{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{'X', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{'X', 'O', 'X', 'X', 'X', 'X', ' '}},
                         {{'O', 'O', 'X', 'O', 'O', 'X', ' '}}}});
        CHECK(game.countRow(4, 'X') == FOUR);
    }
    SECTION("3 in the row"){
        Connect4 game1 ({{{{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{'X', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{'X', 'O', 'X', 'X', 'X', ' ', ' '}},
                         {{'O', 'O', 'X', 'O', 'O', 'X', ' '}}}});
        CHECK(game1.countRow(4, 'X') == THREE);
        Connect4 game2 ({{{{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{'X', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{'X', 'X', 'X', 'O', 'X', ' ', ' '}},
                         {{'O', 'O', 'X', 'O', 'O', 'X', ' '}}}});
        CHECK(game2.countRow(4, 'X') == 0);
        Connect4 game3 ({{{{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{'X', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{'X', 'X', 'X', ' ', 'X', ' ', ' '}},
                         {{'O', 'O', 'X', 'O', 'O', 'X', ' '}}}});
        CHECK(game3.countRow(4, 'X') == THREE);
        Connect4 game4 ({{{{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{'X', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{'X', 'O', 'X', ' ', 'X', 'X', 'X'}},
                         {{'O', 'O', 'X', 'O', 'O', 'X', ' '}}}});
        CHECK(game4.countRow(4, 'X') == THREE);
        Connect4 game5 ({{{{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{'X', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{'X', 'X', ' ', ' ', 'X', 'X', 'X'}},
                         {{'O', 'O', 'X', 'O', 'O', 'X', ' '}}}});
        CHECK(game5.countRow(4, 'X') == THREE);
    }
    SECTION("2 in the row"){
        Connect4 game1 ({{{{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{'X', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{'X', 'O', 'X', 'X', ' ', ' ', ' '}},
                         {{'O', 'O', 'X', 'O', 'O', 'X', ' '}}}});
        CHECK(game1.countRow(4, 'X') == TWO);
        Connect4 game2 ({{{{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{'X', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{'X', 'X', ' ', 'O', 'X', ' ', ' '}},
                         {{'O', 'O', 'X', 'O', 'O', 'X', ' '}}}});
        CHECK(game2.countRow(4, 'X') == 0);
        Connect4 game3 ({{{{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{'X', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{' ', 'X', 'X', ' ', 'X', ' ', ' '}},
                         {{'O', 'O', 'X', 'O', 'O', 'X', ' '}}}});
        CHECK(game3.countRow(4, 'X') == TWO);
        Connect4 game4 ({{{{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{'X', ' ', ' ', ' ', ' ', ' ', ' '}},
                         {{'X', 'O', 'X', ' ', ' ', 'X', 'X'}},
                         {{'O', 'O', 'X', 'O', 'O', 'X', ' '}}}});
        CHECK(game4.countRow(4, 'X') == TWO);
    }
    
}

TEST_CASE("countCol()", "[Connect4 class]")
{
    SECTION("empty board"){                                          
        Connect4 game;
        CHECK(game.countRow(0, 'X')==0);
    }
    SECTION("4 in the column"){
        Connect4 game ({{{{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{'X', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{'X', ' ', ' ', 'X', ' ', ' ', ' '}},
                        {{'X', 'O', 'X', 'O', 'X', 'X', ' '}},
                        {{'X', 'O', 'X', 'O', 'O', 'X', 'X'}}}});
        CHECK(game.countCol(0, 'X') == FOUR);
        CHECK(game.countCol(3, 'X') == 0);
        CHECK(game.countCol(4, 'X') == 0);
        CHECK(game.countCol(6, 'X') == 0);
    }
    SECTION("3 in the column"){
        Connect4 game1 ({{{{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{'X', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{'X', 'O', 'X', 'O', 'X', 'X', ' '}},
                        {{'X', 'O', 'X', 'O', 'O', 'X', ' '}}}});
        CHECK(game1.countCol(0, 'X') == THREE);
        Connect4 game2 ({{{{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{'X', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{'X', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{'X', 'O', 'X', 'O', 'X', 'X', ' '}},
                        {{'O', 'O', 'X', 'O', 'O', 'X', ' '}}}});
        CHECK(game2.countCol(0, 'X') == THREE);
        Connect4 game3 ({{{{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{'O', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{'X', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{'X', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{'X', 'O', 'X', 'O', 'X', 'X', ' '}},
                        {{'O', 'O', 'X', 'O', 'O', 'X', ' '}}}});
        CHECK(game3.countCol(0, 'X') == 0);
        Connect4 game4 ({{{{'X', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{'X', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{'X', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{'O', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{'X', 'O', 'X', 'O', 'X', 'X', ' '}},
                        {{'O', 'O', 'X', 'O', 'O', 'X', ' '}}}});
        CHECK(game4.countCol(0, 'X') == 0);
        Connect4 game5 ({{{{'X', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{'X', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{'O', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{'X', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{'X', 'O', 'X', 'O', 'X', 'X', ' '}},
                        {{'X', 'O', 'X', 'O', 'O', 'X', ' '}}}});
        CHECK(game5.countCol(0, 'X') == 0);
    }
    SECTION("2 in the column"){
        Connect4 game1 ({{{{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{'X', 'O', 'X', 'O', 'X', 'X', ' '}},
                        {{'X', 'O', 'X', 'O', 'O', 'X', ' '}}}});
        CHECK(game1.countCol(0, 'X') == TWO);
        Connect4 game2 ({{{{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{'X', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{'X', 'O', 'X', 'O', 'X', 'X', ' '}},
                        {{'O', 'O', 'X', 'O', 'O', 'X', ' '}}}});
        CHECK(game2.countCol(0, 'X') == TWO);
        Connect4 game3 ({{{{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{'O', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{'X', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{'X', 'O', 'X', 'O', 'X', 'X', ' '}},
                        {{'O', 'O', 'X', 'O', 'O', 'X', ' '}}}});
        CHECK(game3.countCol(0, 'X') == 0);
    }
}

TEST_CASE("countDiag1()", "[Connect4 class]")
{
    SECTION("empty board"){                                          
        Connect4 game;
        CHECK(game.countDiag1(0, 0, 'X')==0);
    }
   
    SECTION("4 in the row"){
        Connect4 game1 ({{{{'X', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{'O', 'X', ' ', ' ', ' ', ' ', ' '}},
                        {{'X', 'O', 'X', 'X', ' ', ' ', ' '}},
                        {{'O', 'X', 'O', 'X', 'X', ' ', ' '}},
                        {{'X', 'O', 'X', 'O', 'O', 'X', ' '}},
                        {{'X', 'O', 'X', 'X', 'O', 'X', 'X'}}}});
        CHECK(game1.countDiag1(0, 0, 'X')==FOUR);
        CHECK(game1.countDiag1(2, 0, 'X')==FOUR);
        CHECK(game1.countDiag1(0, 1, 'X')==FOUR);
    }
    SECTION("3 in the row"){
        Connect4 game1 ({{{{'X', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{'O', 'X', ' ', ' ', ' ', ' ', ' '}},
                        {{'X', 'O', ' ', ' ', ' ', ' ', ' '}},
                        {{'O', 'X', 'O', 'X', 'X', ' ', ' '}},
                        {{'X', 'O', 'X', 'O', 'X', 'X', ' '}},
                        {{'X', 'O', 'X', 'O', 'O', 'X', 'X'}}}});
        CHECK(game1.countDiag1(0, 0, 'X')==THREE);
        CHECK(game1.countDiag1(2, 0, 'X')==0);
        CHECK(game1.countDiag1(0, 1, 'X')==THREE);
    }
    SECTION("2 in the row"){
        Connect4 game1 ({{{{'X', ' ', ' ', ' ', ' ', ' ', ' '}},
                        {{'O', 'X', ' ', ' ', ' ', ' ', ' '}},
                        {{'X', 'O', ' ', ' ', ' ', ' ', ' '}},
                        {{'O', 'X', ' ', ' ', ' ', ' ', ' '}},
                        {{'X', 'O', 'O', 'X', 'X', 'X', ' '}},
                        {{'X', 'O', 'X', 'O', 'X', 'O', 'X'}}}});
        CHECK(game1.countDiag1(0, 0, 'X')==TWO);
        // CHECK(game1.countDiag1(1, 0, 'X')==0);
        // CHECK(game1.countDiag1(2, 0, 'X')==0);
        // CHECK(game1.countDiag1(0, 1, 'X')==2);
    }

}

TEST_CASE("countDiag2()", "[Connect4 class]")
{
    SECTION("empty board"){                                          
        Connect4 game;
        CHECK(game.countDiag2(0, 6, 'X')==0);
    }
    
    SECTION("4 in the row"){
        Connect4 game ({{{{' ', ' ', ' ', ' ', ' ', ' ', 'X'}},
                        {{' ', ' ', ' ', ' ', ' ', 'X', ' '}},
                        {{'X', ' ', ' ', ' ', 'X', ' ', 'X'}},
                        {{'O', 'O', ' ', 'X', ' ', 'X', 'O'}},
                        {{'X', 'O', 'X', 'O', 'X', 'X', 'O'}},
                        {{'X', 'O', 'X', 'X', 'O', 'X', 'O'}}}});
        CHECK(game.countDiag2(2, 6, 'X') == FOUR);
        CHECK(game.countDiag2(0, 6, 'X')==FOUR);
    }
    SECTION("3 in the row"){
        Connect4 game ({{{{' ', ' ', ' ', ' ', ' ', ' ', 'X'}},
                        {{' ', ' ', ' ', ' ', ' ', 'X', 'X'}},
                        {{'X', ' ', ' ', ' ', 'X', 'X', ' '}},
                        {{'O', 'O', ' ', ' ', 'X', 'X', 'O'}},
                        {{'X', 'X', 'X', 'O', 'X', 'X', 'O'}},
                        {{'X', 'O', 'X', 'X', 'O', 'X', 'O'}}}});
        
        CHECK(game.countDiag2(0, 6, 'X')==THREE);
        CHECK(game.countDiag2(2, 6, 'X') == THREE);
        CHECK(game.countDiag2(1, 6, 'X') == 0);
    }
    SECTION("2 in the row"){
        Connect4 game ({{{{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                            {{' ', ' ', ' ', ' ', ' ', 'X', 'X'}},
                            {{'X', ' ', ' ', ' ', 'X', 'X', 'O'}},
                            {{'O', 'O', ' ', ' ', ' ', 'X', 'O'}},
                            {{'X', 'X', 'X', ' ', 'X', 'X', 'O'}},
                            {{'X', 'O', 'X', ' ', 'O', 'X', 'O'}}}});
        
        CHECK(game.countDiag2(0, 6, 'X')==TWO);
        CHECK(game.countDiag2(0, 5, 'X') == TWO);
        CHECK(game.countDiag2(1, 6, 'X') == TWO);
        CHECK(game.countDiag2(2, 6, 'X') == 0);
    }
}

TEST_CASE("findBestMove()", "[AI_player class]")
{
    Connect4 game ({{{{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                    {{' ', ' ', ' ', 'O', 'X', ' ', ' '}},
                    {{' ', ' ', ' ', 'X', 'O', ' ', ' '}},
                    {{' ', 'X', ' ', 'O', 'O', 'O', ' '}},
                    {{'O', 'X', ' ', 'X', 'X', 'O', ' '}},
                    {{'X', 'X', 'X', 'O', 'O', 'X', 'X'}}}});
    AI_player ai(game, 'O', 'X', 4, true);
    CHECK(ai.evaluateBoard(game)==88.0f);
}
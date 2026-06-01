#ifndef CONNECT4_H
#define CONNECT4_H

#include <iostream>
#include <vector>
#include <array>
const int NUM_COL = 7;
const int NUM_ROW = 6;

class Connect4
{
public:
    Connect4(const std::array<std::array<char, NUM_COL>, NUM_ROW> &board = {{{{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                                                    {{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                                                    {{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                                                    {{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                                                    {{' ', ' ', ' ', ' ', ' ', ' ', ' '}},
                                                    {{' ', ' ', ' ', ' ', ' ', ' ', ' '}}}});
    void printBoard() const;
    bool placeToken(char playerToken, int position);
    bool turn(char playerToken, int position);
    bool isWin(char playerToken) const;
    bool isFull() const;
    bool isDone() const {return mDone;}
    int countRow(int row, char playerToken) const;
    int countCol(int col, char playerToken) const;
    int countDiag1(int row, int col, char playerToken) const;
    int countDiag2(int row, int col, char playerToken) const;


private:
    std::array<std::array<char, NUM_COL>, NUM_ROW> mBoard;
    bool mDone = false;
};

#endif

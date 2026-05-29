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


private:
    std::array<std::array<char, NUM_COL>, NUM_ROW> mBoard;
    bool mDone = false;
};

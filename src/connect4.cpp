#include "../include/connect4.h"

Connect4::Connect4(const std::array<std::array<char, NUM_COL>, NUM_ROW> & board)
{
    mBoard = board;

}
void Connect4::printBoard() const
{
    for (int r {0}; r < NUM_ROW; r++)
    {
        for (int c{0}; c <NUM_COL; c++)
        {
            std::cout << "|" <<mBoard[r][c];
        }
        std::cout << "|\n";
    }
    std::cout << "---------------\n";
    std::cout << " 1 2 3 4 5 6 7\n";
}
/**
 * @brief Put peg into corect position on the board, starting with higher rows
 * 
 * @param player character for spesific player
 * @param position 0 <=colomn<NUM_COL
 * @param board 2D char array NUM_ROW x NUM_COL
 * @return true If peg was positiond
 * @return false if no space in the column position
 */
bool Connect4::placeToken(char playerToken, int position)
{
    //serch for the space in colomn position starting with higher row
    for (int row{NUM_ROW-1}; row > -1; row--){
        //if I found a space
        if (mBoard[row][position]==' '){
            mBoard[row][position] = playerToken;
            return true;
        }
    }
    return false;
}
bool Connect4::turn(char playerToken, int position)
{
    if (position < 0 || position > NUM_COL-1){
        return false;
    }else {
        return placeToken(playerToken, position);
    }
}

bool Connect4::isWin(char playerToken) const
{
    //search for player token starting from top-left
    for (int r{0}; r<NUM_ROW; r++)
    {
        for (int c{0}; c < NUM_COL; c++)
        {
            if (mBoard[r][c]== playerToken){
                //check right
                bool got4=true;
                for (int count{1}; count < 4; count++){
                    if (mBoard[r][c+count]!=playerToken){
                        got4 = false;
                        break;
                    }
                }
                if (got4){
                    return true;
                }

                //check down
                got4=true;
                for (int count{1}; count < 4; count++){
                    if (mBoard[r+count][c]!=playerToken){
                        got4 = false;
                        break;
                    }
                }
                if (got4){
                    return true;
                }
                //check main diagonal (down-right)
                got4=true;
                for (int count{1}; count < 4; count++){
                    if (mBoard[r+count][c+count]!=playerToken){
                        got4 = false;
                        break;
                    }
                }
                if (got4){
                    return true;
                }
                //check diagonal (down-left)
                got4=true;
                for (int count{1}; count < 4; count++){
                    if (mBoard[r+count][c-count]!=playerToken){
                        got4 = false;
                        break;
                    }
                }
                if (got4){
                    return true;
                }
            }
        }
    }
    return false;
}

bool Connect4::isFull() const
{
    for (int c{0}; c < NUM_COL; c++)
    {
        if (mBoard[0][c] == ' ')
        {
            return false;
        }
    }
    return true;
}
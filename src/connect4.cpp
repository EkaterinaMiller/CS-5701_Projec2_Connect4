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
 /* REtunr number of player tokens in the row with spaces
 * 2tokens + 2 empty = 2
 * 3tokens + 1 empty = 3
 * 4tokens + 0 empty = 4
 * else return 0
 * */
int Connect4::countRow(int row, char playerToken) const
{
    int total=0;
    for (int col = 0; col < NUM_COL; col++) {
        if (mBoard[row][col] == playerToken) {
            if (col+2 < NUM_COL && mBoard[row][col+1] == playerToken) {
                if (mBoard[row][col+2] == playerToken) {
                    if (col+3 < NUM_COL && mBoard[row][col+3] == playerToken) {
                        return 4;
                    }
                    //three tokens in a row, check for one empty space before or after
                    else if ((col+3 < NUM_COL && mBoard[row][col+3] == ' ') 
                            || (col-1>=0 && mBoard[row][col-1] == ' ')) {
                        return 3;
                    }
                }
                //two tokens in a row, check for two empty spaces before or after
                else if ((mBoard[row][col+2] == ' ' && col+3 < NUM_COL && mBoard[row][col+3] == ' ') 
                        || (col-1>=0 && mBoard[row][col-1] == ' ' && mBoard[row][col+2] == ' ') 
                        || (col-2>=0 && mBoard[row][col-2] == ' ' && mBoard[row][col-1] == ' ')) {
                    total = 2;
                }
                col+=1;
            }//two
            //check if last two with two leading empty spaces
            else if(col+1 < NUM_COL && mBoard[row][col+1] == playerToken
                            && (col-2>=0 && mBoard[row][col-1] == ' ' && mBoard[row][col-2] == ' ')) {
                    total = 2;
            }
            col+=1;
        }//one
    }
    return total;
}
int Connect4::countCol(int col, char playerToken) const
{
    int total=0;
    for (int row = 0; row < NUM_ROW; row++) {
        if (mBoard[row][col] == playerToken) {
            if (row+1 < NUM_ROW && mBoard[row+1][col] == playerToken) {
                if (row+2 < NUM_ROW && mBoard[row+2][col] == playerToken) {
                    if (row+3 < NUM_ROW && mBoard[row+3][col] == playerToken) {
                        return 4;
                    }
                    //three tokens in a row, check for one empty space above
                    else if (row-1>=0 && mBoard[row-1][col] == ' ') {
                        return 3;
                    }
                }
                //two tokens in a row, check for two empty spaces above
                else if (row-2>=0 && mBoard[row-2][col] == ' ' && mBoard[row-1][col] == ' ') {
                    return 2;
                }
                row+=1;
            }
            row+=1;//already check this one, move to next
        }//one
    }
    return total;
}
/**
 * @return number of player tokens in the diagonal with spaces
 * 2tokens + 2 empty = 2
 * 3tokens + 1 empty = 3
 * 4tokens + 0 empty = 4
 * else return 0
 */
int Connect4::countDiag1(int row, int col, char playerToken) const
{
    for (int i = 0; row+i < NUM_ROW && col+i < NUM_COL; i++) {
        if (mBoard[row+i][col+i] == playerToken) {
            //found a playerTocken, check for 4 in a row
            if (row+i+3 < NUM_ROW && col+i+3 < NUM_COL 
                && mBoard[row+i+1][col+i+1] == playerToken 
                && mBoard[row+i+2][col+i+2] == playerToken 
                && mBoard[row+i+3][col+i+3] == playerToken) {
                return 4;
            }
            //three tokens in a row, check for one empty space before or after
            else if (row+i+3 < NUM_ROW && col+i+3 < NUM_COL 
                && mBoard[row+i+1][col+i+1] == playerToken 
                && mBoard[row+i+2][col+i+2] == playerToken 
                && mBoard[row+i+3][col+i+3] == ' ') {
                return 3;
            }
            else if ( row+i+2 < NUM_ROW && col+i+2 < NUM_COL 
                && mBoard[row+i+1][col+i+1] == playerToken 
                && mBoard[row+i+2][col+i+2] == playerToken 
                && (row+i-1>=0 && col+i-1>=0 && mBoard[row+i-1][col+i-1] == ' ')  ) 
            {
                return 3;
            }
            //two tokens in a row
            else if (row+i+1 < NUM_ROW && col+i+1 < NUM_COL 
                && mBoard[row+i+1][col+i+1] == playerToken ){
                    //check for two empty spaces before 
                    if (row+i-2>=0 && col+i-2>=0 && mBoard[row+i-1][col+i-1] == ' ' && mBoard[row+i-2][col+i-2] == ' ') {
                       return 2;
                    }
                    //check for two empty spaces after 
                    else if (row+i+3 < NUM_ROW && col+i+3 < NUM_COL 
                        && mBoard[row+i+3][col+i+3] == ' ' 
                        && mBoard[row+i+2][col+i+2] == ' ') {
                        return 2;
                    }
                    //check for one before and one after
                    else if ( (row+i-1>=0 && col+i-1>=0 && mBoard[row+i-1][col+i-1] == ' ') 
                            && (row+i+2 < NUM_ROW && col+i+2 < NUM_COL && mBoard[row+i+2][col+i+2] == ' ')) {
                        return 2;
                    }
                }
                i++;//already check this one, move to next
            }
    }
    return 0;
}

int Connect4::countDiag2(int row, int col, char playerToken) const
{
    for (int i = 0; row+i < NUM_ROW && col-i >=0; i++) {
        if (mBoard[row+i][col-i] == playerToken) {
            //found a playerTocken, check for 4 in a row
            if (row+i+3 < NUM_ROW && col-i-3 >=0 
                && mBoard[row+i+1][col-i-1] == playerToken 
                && mBoard[row+i+2][col-i-2] == playerToken 
                && mBoard[row+i+3][col-i-3] == playerToken) {
                return 4;
            }
            //three tokens in a row, check for one empty space before or after
            else if (row+i+3 < NUM_ROW && col-i-3 >=0 
                && mBoard[row+i+1][col-i-1] == playerToken 
                && mBoard[row+i+2][col-i-2] == playerToken 
                && mBoard[row+i+3][col-i-3] == ' ') {
                return 3;
            }
            else if ( row+i+2 < NUM_ROW && col-i-2 >=0 
                && mBoard[row+i+1][col-i-1] == playerToken 
                && mBoard[row+i+2][col-i-2] == playerToken 
                && (row+i-1>=0 && col-i+1<NUM_COL && mBoard[row+i-1][col-i+1] == ' ')  ) 
            {
                return 3;
            }
            //two tokens in a row
            else if (row+i+1 < NUM_ROW && col-i-1 >=0 
                && mBoard[row+i+1][col-i-1] == playerToken ){
                    //check for two empty spaces before 
                    if (row+i-2>=0 && col-i+2<NUM_COL && mBoard[row+i-1][col-i+1] == ' ' && mBoard[row+i-2][col-i+2] == ' ') {
                       return 2;
                    }
                    //check for two empty spaces below (to the left) 
                    else if (row+i+3 < NUM_ROW && col-i-3 >=0 
                        && mBoard[row+i+3][col-i-3] == ' ' 
                        && mBoard[row+i+2][col-i-2] == ' ') {
                        return 2;
                    }
                    //check for one before and one after
                    else if ( (row+i-1>=0 && col-i+1<NUM_COL && mBoard[row+i-1][col-i+1] == ' ') 
                            && (row+i+2 < NUM_ROW && col-i-2 >=0 && mBoard[row+i+2][col-i-2] == ' ')) {
                        return 2;
                    }
                }
                i++;//already check this one, move to next
            }
    }
    return 0;
}
#include "../include/AI_player.h"

AI_player::AI_player(Connect4 & board, char token) : Player(board, token) {
    std::srand(time(NULL)); // Seed the random number generator with the current time
}

void AI_player::makeaMove(int min, int max){
    int move = findBestMove(min, max);
    if (!mConnectBoard.placeToken(mToken, move)) {
        throw std::runtime_error("AI failed to make a move");
    }
}

void AI_player::makeRandomMove(Connect4 &board, int min, int max, char playerToken)
{
    while(1){
        int move = rand()%(max-min+1) + min;//returns min-max
        //int move = rand()%max;
        if (board.placeToken(playerToken, move)){
            break;
        }
    }
}

float AI_player::evaluateBoard(const Connect4 & board, int turn) const 
{
    //Play 100 times at random and return the average score
    float score = 0.0f;
    for (int i = 0; i < 100; i++) {
        score += playAtRandom(board, turn);
        // Accumulate the score for averaging
    } 
    return score / 100.0f;
}

float AI_player::playAtRandom(Connect4 board, int turn) const {
    if (turn!=1 and turn !=0){
        throw std::runtime_error("Wrong argument in playAtRandom");
    }
    // Implementation for playing at random
    AI_player * player[2];
    player[0] = new AI_player(board, mToken);//assume first player is alwaysX
    player[1] = new AI_player(board, mOponentToken);//assume second player is always O
    float score = 0.0f;
    while(1){
        player[turn]->makeRandomMove(board, 0, 6, player[turn]->getToken());
        if (board.isWin(player[turn]->getToken()))
        {
            if (player[turn]->getToken() == mToken) {
                score = 1.0f; // AI wins
            } else {
                score = -1.0f; // Opponent wins
            }
            break;
        }
        if (board.isFull())
        {
            score = 0.0f;  
            break; 
        }
        turn = (turn + 1) % 2; //switch player
    }

    delete player[0];
    delete player[1];
    return score;
}

int AI_player::findBestMove(int min, int max) const
{
    int best = 0;
    float maxValue = -std::numeric_limits<float>::infinity();//very small number
    for (int col = min; col < max; col++) {
        // Create a temporary board to simulate the move
        Connect4 tempBoard = Player::mConnectBoard; 
        if (tempBoard.placeToken(Player::mToken, col)) { // Check if the move is valid
            //get move result
            float value = minMove(tempBoard, mDepth - 1); // Evaluate the move using minimax
            if (value > maxValue) {
                maxValue = value;
                best = col;
            }
        }
    }
    return best; // Return the best move column index
}

float AI_player::minMove(Connect4 &board, int depth) const
{
    if (board.isWin(mToken)) {
        return 1.0f; // AI wins
    }
    else if (board.isWin(mOponentToken)) {
        return -1.0f; // Opponent wins
    }
    else if (board.isFull() ) {
        return 0.0f; // Tie or depth limit reached
    }
    else if (depth == 0) {
        return evaluateBoard(board, 0); // Evaluate the board state
    }
    else{
        float minValue = std::numeric_limits<float>::infinity(); // Initialize minValue to a very large number
        for (int col = 0; col < NUM_COL; col++) {
            Connect4 tempBoard = board; // Create a temporary board to simulate the move
            if (tempBoard.placeToken(mOponentToken, col)) { // Check if the move is valid
                float value = maxMove(tempBoard, depth - 1); // Evaluate the move using minimax
                minValue = std::min(minValue, value); // Update minValue with the minimum score
            }
        }
        return minValue; // Return the minimum score for this move

    }
}
float AI_player::maxMove(Connect4 &board, int depth) const
{
    if (board.isWin(mToken)) {
        return 1.0f; // AI wins
    }
    else if (board.isWin(mOponentToken)) {
        return -1.0f; // Opponent wins
    }
    else if (board.isFull() ) {
        return 0.0f; // Tie or depth limit reached
    }
    else if (depth == 0) {
        return evaluateBoard(board, 1); // Evaluate the board state
    }
    else{
        float maxValue = -std::numeric_limits<float>::infinity(); // Initialize maxValue to a very small number
        for (int col = 0; col < NUM_COL; col++) {
            Connect4 tempBoard = board; // Create a temporary board to simulate the move
            if (tempBoard.placeToken(mToken, col)) { // Check if the move is valid
                float value = minMove(tempBoard, depth - 1); // Evaluate the move using minimax
                maxValue = std::max(maxValue, value); // Update maxValue with the maximum score
            }
        }
        return maxValue; // Return the maximum score for this move

    }
}
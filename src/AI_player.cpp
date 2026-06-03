#include "../include/AI_player.h"
#include <chrono>
#include <limits>
/**
 * @brief Construct a new ai player::ai player object
 * 
 * @param board refrence to the game board
 * @param token tocken for this player
 * @param oponentToken token for the opponent player
 * @param depth depth of the minimax search tree
 * @param usePruning whether to use alpha-beta pruning
 */
AI_player::AI_player(Connect4 & board, char token, char oponentToken, int depth, bool usePruning) 
: Player(board, token), mOponentToken(oponentToken), mDepth(depth), mUsePruning(usePruning) {
    //std::srand(time(NULL)); // Seed the random number generator with the current time
}
/**
 * @brief Makes desision on next move and performs the move on the board
 * 
 * @param min minimum available move column index
 * @param max maximum available move column index
 */
void AI_player::makeaMove(int min, int max){
    int numNodes = 0; // Initialize the node count for this move
    auto start = std::chrono::steady_clock::now();
    int move = findBestMove(min, max, mUsePruning, numNodes);
    if (!mConnectBoard.placeToken(mToken, move)) {
        throw std::runtime_error("AI failed to make a move");
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    mMoveTimes.push_back(elapsed.count());
    mExploredNodes.push_back(numNodes); // Store the number of nodes explored for this move
}

// void AI_player::makeRandomMove(Connect4 &board, int min, int max, char playerToken)
// {
//     while(1){
//         int move = rand()%(max-min+1) + min;//returns min-max
//         //int move = rand()%max;
//         if (board.placeToken(playerToken, move)){
//             break;
//         }
//     }
// }
/**
 * @brief Evaluates the current state of the board using a heuristic function that 
 * considers the number of tokens in a row, column, and diagonals for both the AI player 
 * and the opponent. The score is calculated based on the potential winning positions 
 * for the AI player and the opponent, with blocking opponent's winning positions 
 * being more important than creating winning positions for the AI player. 
 * The positive scores indicate favorable positions for the AI player and 
 * negative scores indicate unfavorable positions. 
 * 
 * @param board 
 * @return float 
 */
float AI_player::evaluateBoard(const Connect4 & board) const 
{
    float score = 0.0f;
    for (int row = 0; row < NUM_ROW; row++) {
        score += board.countRow(row, mToken);
        score -= 1.2 * board.countRow(row, mOponentToken);//blocking is more impotent than creating a line
    }
    for (int col = 0; col < NUM_COL; col++) {
        score += board.countCol(col, mToken);
        score -= 1.2 * board.countCol(col, mOponentToken);
    }
    for (int col = 0; col < NUM_COL-3; col++) {
        score += board.countDiag1(0,col, mToken);
        score -= 1.2 * board.countDiag1(0, col, mOponentToken);
    }
    for (int row = 1; row < NUM_ROW-3; row++) {
        score += board.countDiag1(row, 0, mToken);
        score -= 1.2 * board.countDiag1(row, 0, mOponentToken);
    }
    for (int col = 3; col < NUM_COL; col++) {
        score += board.countDiag2(0, col, mToken);
        score -= 1.2 * board.countDiag2(0, col, mOponentToken);
    }
    for (int row = 1; row < NUM_ROW-3; row++) {
        score += board.countDiag2(row, NUM_COL-1, mToken);
        score -= 1.2 * board.countDiag2(row, NUM_COL-1, mOponentToken);
    }
    return score; 
    // //Play 100 times at random and return the average score
    // float score = 0.0f;
    // for (int i = 0; i < 100; i++) {
    //     score += playAtRandom(board, turn);
    //     // Accumulate the score for averaging
    // } 
    // return score / 100.0f;
}

// float AI_player::playAtRandom(Connect4 board, int turn) const {
//     if (turn!=1 and turn !=0){
//         throw std::runtime_error("Wrong argument in playAtRandom");
//     }
//     // Implementation for playing at random
//     AI_player * player[2];
//     player[0] = new AI_player(board, mToken, mOponentToken, mDepth, mUsePruning);//assume first player is alwaysX
//     player[1] = new AI_player(board, mOponentToken, mToken, mDepth, mUsePruning );//assume second player is always O
//     float score = 0.0f;
//     while(1){
//         player[turn]->makeRandomMove(board, 0, 6, player[turn]->getToken());
//         if (board.isWin(player[turn]->getToken()))
//         {
//             if (player[turn]->getToken() == mToken) {
//                 score = 1.0f; // AI wins
//             } else {
//                 score = -1.0f; // Opponent wins
//             }
//             break;
//         }
//         if (board.isFull())
//         {
//             score = 0.0f;  
//             break; 
//         }
//         turn = (turn + 1) % 2; //switch player
//     }

//     delete player[0];
//     delete player[1];
//     return score;
// }
/**
 * @brief Finds the best move for the AI player using minimax with alpha-beta pruning
 * 
 * @param min minimum available move column index
 * @param max maximum available move column index
 * @param pruning boolean indicating whether to use alpha-beta pruning is enabled
 * @param numNodes reference to the number of nodes visited
 * @return int column index of the best move
 */
int AI_player::findBestMove(int min, int max, bool pruning, int &numNodes) const
{
    int best = 0;
    float maxValue = -std::numeric_limits<float>::infinity();//very small number
    float alpha = -std::numeric_limits<float>::infinity();
    float beta = std::numeric_limits<float>::infinity();
    for (int col = min; col <= max; col++) {
        // Create a temporary board to simulate the move
        Connect4 tempBoard = Player::mConnectBoard; 
        if (tempBoard.placeToken(Player::mToken, col)) { // Check if the move is valid
            numNodes++;
            //get move result
            float value = minMove(tempBoard, mDepth - 1, pruning, alpha, beta, numNodes); // Evaluate the move using minimax
            if (value > maxValue) {
                maxValue = value;
                best = col;
            }
            if (pruning) {
                alpha = std::max(alpha, maxValue);
            }
        }
    }

    return best; // Return the best move column index
}
/**
 * @brief Evaluates the minimum move for the AI player using minimax with alpha-beta pruning
 * 
 * @param board reference to the Connect4 board
 * @param depth remaining depth of the search
 * @param pruning boolean indicating whether to use alpha-beta pruning
 * @param alpha alpha value for alpha-beta pruning
 * @param beta beta value for alpha-beta pruning
 * @param numNodes reference to the number of nodes visited
 * @return float the minimum score for the move
 */
float AI_player::minMove(Connect4 &board, int depth, bool pruning, float alpha, float beta, int &numNodes) const
{
    if (board.isWin(mToken)) {
        return FOUR; // AI wins
    }
    else if (board.isWin(mOponentToken)) {
        return -FOUR; // Opponent wins
    }
    else if (board.isFull() ) {
        return 0.0f; // Tie or depth limit reached
    }
    else if (depth == 0) {
        return evaluateBoard(board); // Evaluate the board state
    }
    else{
        float minValue = std::numeric_limits<float>::infinity(); // Initialize minValue to a very large number
        for (int col = 0; col < NUM_COL; col++) {
            Connect4 tempBoard = board; // Create a temporary board to simulate the move
            if (tempBoard.placeToken(mOponentToken, col)) { // Check if the move is valid
                numNodes++;
                float value = maxMove(tempBoard, depth - 1, pruning, alpha, beta, numNodes); // Evaluate the move using minimax
                minValue = std::min(minValue, value); // Update minValue with the minimum score
                if (pruning) {
                    beta = std::min(beta, minValue);
                    if (beta <= alpha) {
                        break;
                    }
                }
            }
        }
        return minValue; // Return the minimum score for this move

    }
}
/**
 * @brief Evaluates the maximum move for the AI player using minimax with alpha-beta pruning
 * 
 * @param board reference to the Connect4 board
 * @param depth remaining depth of the search
 * @param pruning boolean indicating whether to use alpha-beta pruning
 * @param alpha alpha value for alpha-beta pruning
 * @param beta beta value for alpha-beta pruning
 * @param numNodes reference to the number of nodes visited
 * @return float the maximum score for the move
 */
float AI_player::maxMove(Connect4 &board, int depth, bool pruning, float alpha, float beta, int &numNodes) const
{
    if (board.isWin(mToken)) {
        return FOUR; // AI wins
    }
    else if (board.isWin(mOponentToken)) {
        return -FOUR; // Opponent wins
    }
    else if (board.isFull() ) {
        return 0.0f; // Tie or depth limit reached
    }
    else if (depth == 0) {
        return evaluateBoard(board); // Evaluate the board state
    }
    else{
        float maxValue = -std::numeric_limits<float>::infinity(); // Initialize maxValue to a very small number
        for (int col = 0; col < NUM_COL; col++) {
            Connect4 tempBoard = board; // Create a temporary board to simulate the move
            if (tempBoard.placeToken(mToken, col)) { // Check if the move is valid
                numNodes++;
                float value = minMove(tempBoard, depth - 1, pruning, alpha, beta, numNodes ); // Evaluate the move using minimax
                maxValue = std::max(maxValue, value); // Update maxValue with the maximum score
                if (pruning) {
                    alpha = std::max(alpha, maxValue);
                    if (alpha >= beta) {
                        break;
                    }
                }
            }
        }
        return maxValue; // Return the maximum score for this move

    }
}
/**
 * @brief Calculates the average number of nodes explored by the AI player
 * 
 * @return double the average number of nodes explored
 */
double AI_player::averageExploredNodes() const {
    std::cout << "Explored nodes for player " << mToken << ": ";
    if (mExploredNodes.empty()) {
        std::cout << "none\nAverage: 0 nodes" << std::endl;
        return -1.0; // Return -1 to indicate no nodes were explored
    }
    int total{0};
    for (size_t i = 0; i < mExploredNodes.size(); ++i) {
        total += mExploredNodes[i];
        std::cout << mExploredNodes[i] << " ,";
    }

    return static_cast<double>(total) / mExploredNodes.size();
}

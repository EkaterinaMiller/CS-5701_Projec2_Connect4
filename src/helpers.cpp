/**
 * @file helpers.cpp
 * @author Ekaterina Miller
 * @brief Implementation of helper functions for Connect4 game, 
 *        including user input handling and AI parameter configuration
 * @date 2026-06-02
 * 
 */
#include "../include/helpers.h"
#include <string>
/**
 * @brief Gets user input within a specified range
 * @param min minimum allowed value
 * @param max maximum allowed value
 * @return int the user input
 */
int getUserInput(int min, int max)
{
    std::string input;
    int userInput;
    while(1)
    {
        std::cin >> input;
        try {
            userInput = std::stoi(input); // Check if the input can be converted to an integer
        } catch (std::invalid_argument&) {
            std::cout << "Invalid input. Please enter a number between " << min << " and " << max << ": ";
            continue;
        }
        if (userInput >= min && userInput <= max)
        {
            return userInput;
        }
        std::cout << "Invalid input. Please enter a number between " << min << " and " << max << ": ";
    }
}
/**
 * @brief Gets the parameters for the AI player
 * @param depth reference to the depth for the AI
 * @param pruning reference to the boolean indicating whether to use alpha-beta pruning
 */
void getParameters(int &depth, bool &pruning)
{
    std::cout << "Enter the depth for the AI (1-20): ";
    depth = getUserInput(1, 20);
    std::cout << "Enable alpha-beta pruning? (1 -yes/0 -no): ";
    pruning = getUserInput(0, 1) == 1;      
}
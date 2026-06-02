#include "../include/helpers.h"
#include <string>

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
void getParameters(int &depth, bool &pruning)
{
    std::cout << "Enter the depth for the AI (1-20): ";
    depth = getUserInput(1, 20);
    std::cout << "Enable alpha-beta pruning? (1 -yes/0 -no): ";
    pruning = getUserInput(0, 1) == 1;      
}
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
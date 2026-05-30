#include "helpers.h"

int getUserInput(int min, int max)
{
    int input = 0;
    while(1)
    {
        std::cin >> input;
        if (input >= min && input <= max)
        {
            return input;
        }
        std::cout << "Invalid input. Please enter a number between " << min << " and " << max << ": ";
    }
}
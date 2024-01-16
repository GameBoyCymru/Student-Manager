#include "utilities.h"

// Function to clear the terminal using ANSI escape codes and through clearing the scrollback buffer
void utilities::clear()
{
    std::cout << "\033[H\033[2J\033[3J";
}

// Function to pause the code until the user presses enter
void utilities::continuePrompt()
{
    std::cout << "\nPress enter to return to the main menu.\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    _getch();

}

// Function to sleep the code for a specified amount of time
void utilities::sleep(unsigned short int time)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
}

// Function to add a separator between each line
void utilities::addSeparator(unsigned short int length, char separator)
{
    for (short int i = 0; i < length; i++)
    {
        std::cout << separator;
    }
    std::cout << std::endl;
}

/// Function to end the program with an animation
void utilities::exitProgram()
{
    std::string exitMessage = "Exiting";
    utilities::clear();
    utilities::addSeparator(25, '=');
    std::cout << std::setw(15) << exitMessage << std::endl;
    utilities::addSeparator(25, '=');
    std::cout << "\r\x1b[A";
    std::cout << "\r\x1b[A";
    for (unsigned short int i = 0; i < 4; ++i)
    {
        std::cout << "\r" << std::setw(15 + i) << exitMessage << std::flush;
        utilities::sleep(600);
        exitMessage += ".";
    }
    utilities::clear();
    exit(0);
}
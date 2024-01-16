#pragma once

#include <chrono>
#include <thread>
#include <string>
#include <iomanip>
#include <iostream>
#include <conio.h>

namespace utilities
{
    void clear();                                                 // Function to clear the terminal
    void continuePrompt();                                        // Function to pause the code until the user presses enter
    void sleep(unsigned short int time);                          // Function to sleep the code for a specified amount of time
    void addSeparator(unsigned short int length, char separator); // Function to add a separator between each line
    void exitProgram();                                            // Function to end the program
}
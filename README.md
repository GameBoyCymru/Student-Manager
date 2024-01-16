# Student Manager

## Overview

The Student Manager is a C++ program designed to manage student information. It provides a user-friendly interface for both general users and administrators to perform tasks such as viewing student details, adding, deleting, or updating student records. Login accounts are required to access the program, with the administrator account having access to additional features. The program is designed to be easy to use and navigate, with a simple menu system to guide the user through the program, with input validation to ensure the user enters the correct data/selections.

## File Overview

### `studentManager.cpp`

This file serves as the core functionality of the Student Manager. It includes the main program logic, such as menus and loading data from files into memory. This includes the functions to prompt for an administrator password, as well as the main menu system, and to check if the user input is valid.

### `studentManager.h`

The header file contains function declarations for both general menu systems and user/administrator-specific functions. It acts as an interface for other source files to utilize the functionality defined in `studentManager.cpp`.

### `user.cpp`

This file is responsible for implementing the functionality related to user interactions. It enables users to display student data based on a provided menu system. All of the functions responsible for displaying student data are defined in this file.

### `admin.cpp`

The `admin.cpp` file focuses on the administrator-specific functionalities. It allows administrators to modify student data by adding, deleting, or updating student records in the file, as such, all of the functions related to these actions are defined in this file. Regular users do not have access to these functions.

### `studentMarks.txt`

This file contains the data of a class of students. The format of the file is as follows:
&nbsp;

- The first line is a single integer that gives the number of students in the class.
- Each subsequent line of the file comprises a student code (between 1000 and 9999), 3 course marks (each out of 20), and an examination mark (out of 100).

### Example of a file containing 10 students:

```
10
1345,John Curry,8,15,7,45
2345,Sam Sturtivant,14,15,14,77
9876,Lee Scott,17,11,16,99
3724,Matt Thompson,19,11,15,81
1212,Ron Herrema,14,17,18,66
8439,Jake Hobbs,10,11,10,43
2344,Jo Hyde,6,15,10,55
9384,Gareth Southgate,5,6,8,33
8327,Alan Shearer,20,20,20,100
2983,Les Ferdinand,15,17,18,92
```

## Usage
Upon running the program, a menu will be displayed prompting the user to choose a login option. A regular user or an administrator are the only choices, with the administrator account prompting for a password. A regular user will have the ability to view all the data, but an administrator will have access to more menu options.


### User Options

```
1. View all student records: Displays all student records in the file.

2. View individual student record: Displays a specific student record based on the student code.

3. Show student with the highest total score: Displays the student (or students) with the highest total score.

4. Show student with the lowest total score: Displays the student (or students) with the lowest total score.

5. Sort student records: Displays a menu to sort the students by ID or Name in ascending or descending order.

0: Exit: Ends the program after displaying an animation.
```

### Additional Administrator Options
```
6. Add a student record: Adds a new student record to the file.

7. Delete a student record: Deletes a student record from the file.

8. Update a student's record: Updates a student's record in the file.

0: Exit: Ends the program after displaying an animation.
```
Simply enter the corresponding number for the action you want to perform. The `user.cpp` contains all functions to perform the menu options seen in the user menu, while `admin.cpp` contains only the functions to perform the actions only available to the administrator account.

## How to Run in Visual Studio

1. **Open Visual Studio:**
   - Launch Visual Studio on your machine.

2. **Open the Project:**
   - In the menu, go to `File` > `Open` > `Project/Solution...`.
   - Navigate to the directory where you have the Student Manager Program files.
   - Select the file `studentManager.cpp` and click `Open`.

3. **Configure the Project:**
   - Once the project is open, ensure that the project configuration is set up correctly. You may need to configure the project settings based on your system.
   - Check that the necessary compiler and linker settings are in place.

4. **Build the Project:**
   - Build the project by selecting `Build` > `Build Solution` from the menu.
   - Ensure that the build process is completed without errors.

5. **Run the Program:**
   - After a successful build, you can run the program by selecting `Debug` > `Start Without Debugging` or by pressing `Ctrl + F5`.

6. **Interact with the Program:**
   - The program will run in the console window. Follow the on-screen instructions to interact with the Student Manager.

7. **Close the Program:**
   - To exit the program, select the console window and press `Enter`. Alternatively, close the console window.


## Contributors

Joshua Thomas (`GameBoyCymru`).

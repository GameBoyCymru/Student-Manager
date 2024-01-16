#include "studentManager.h"
#include "utilities.h"

// Function to add a student record
void StudentManager::addStudentRecord(std::vector<Student> &students)
{
    utilities::clear();
    if (StudentManager::emptyVector(students))
    {
        return;
    }

    // Create a new student object with default values
    Student newStudent = {0, "", 0, 0, 0, 0};

    // Validate and get student ID
    bool invalidInput = false;
    do
    {
        // Display current details
        StudentManager::displayStudentDetails(newStudent);
        std::cout << "ID: ";
        unsigned short int id;
        std::cin >> id;
        // Check if the entered ID already exists
        auto existingStudent = find_if(students.begin(), students.end(), [id](const Student &student)
                                       { return student.id == id; });

        
        // Check if the input is a number between the specified range and if the ID already exists
        if (std::cin.fail() || id < 0 || id > 9999 || std::to_string(id).length() != 4 || std::cin.peek() != '\n' || existingStudent != students.end())
        {
            invalidInput = true;
            std::cin.clear();
            std::cout << "\nID already exists or Invalid Input! Please try again." << std::endl;
            utilities::sleep(1200);
            utilities::clear();
        }
        else
        {
            invalidInput = false;
            newStudent.id = id;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (invalidInput);

    // Validate and get student name
    do
    {
        StudentManager::displayStudentDetails(newStudent);
        std::cout << "Name: ";
        std::string newStudentName;
        std::getline(std::cin, newStudentName);
        // check if the name is empty or contains only spaces or integers
        if (newStudentName.empty() || std::all_of(newStudentName.begin(), newStudentName.end(), isspace) || std::any_of(newStudentName.begin(), newStudentName.end(), isdigit))
        {
            invalidInput = true;
            std::cout << "\nInvalid name, please try again!" << std::endl;
            utilities::sleep(1200);
            utilities::clear();
        }
        else
        {
            invalidInput = false;

            // Capitalizes the first letter of each word in the name
            for (unsigned short int i = 0; i < newStudentName.length(); ++i)
            {
                if (i == 0 || newStudentName[i - 1] == ' ')
                {
                    newStudentName[i] = toupper(newStudentName[i]);
                }
                else
                {
                    newStudentName[i] = tolower(newStudentName[i]);
                }
            }
            newStudent.fullName = newStudentName;
        }
    } while (invalidInput);

    // Validate and get Course Marks
    for (int i = 0; i < 3; i++)
    {
        while (true)
        {
            // Display current details
            StudentManager::displayStudentDetails(newStudent);
            std::cout << "Course Mark " << i + 1 << ": ";
            unsigned short int courseMark;
            std::cin >> courseMark;

            if (std::cin.fail() || std::cin.peek() != '\n' || courseMark < 0 || courseMark > 20)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter an integer between 0 and 20.\n";
                utilities::sleep(1200);
                utilities::clear();
            }
            else
            {
                utilities::clear();
                newStudent.courseMark[i] = courseMark;
                break;
            }
        }
    }

    // Validate and get exam mark
    while (true)
    {
        StudentManager::displayStudentDetails(newStudent);
        std::cout << "Exam Mark: ";
        unsigned short int examMark;
        std::cin >> examMark;

        if (std::cin.fail() || std::cin.peek() != '\n' || examMark < 0 || examMark > 100)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter an integer between 0 and 100.\n";
            utilities::sleep(1200);
            utilities::clear();
        }
        else
        {
            utilities::clear();
            newStudent.examMark = examMark;
            break;
        }
    }

    // Display final details
    StudentManager::displayStudentDetails(newStudent);

    std::ofstream file(CLASS_DATA_FILE, std::ios::app);
    if (!file.is_open())
    {
        std::cout << "Error opening the file!" << std::endl;
        return;
    }

    // Write the new student record to the file
    file << '\n'
         << newStudent.id << "," << newStudent.fullName << "," << newStudent.courseMark[0] << "," << newStudent.courseMark[1] << "," << newStudent.courseMark[2] << "," << newStudent.examMark;

    students.push_back(newStudent);

    file.close();
    std::cout << "Student record added successfully." << std::endl;

    // Increment the number of students in the file
    unsigned short int numberOfStudents = StudentManager::getNumberOfStudents() + 1;

    // Update the file with the new number of students
    StudentManager::updateNumberOfStudents(numberOfStudents);

    StudentManager::sortStudentsByIDAsc(students);
}

// Function to read the number of students from the file
unsigned short int StudentManager::getNumberOfStudents()
{
    std::ifstream file(CLASS_DATA_FILE);
    if (!file.is_open())
    {
        std::cout << "Error opening the file!" << std::endl;
        utilities::exitProgram();
    }

    unsigned short int numberOfStudents = 0;
    file >> numberOfStudents;

    file.close();
    return numberOfStudents;
}

// Function to update the number of students in the file
void StudentManager::updateNumberOfStudents(unsigned short int newNumberOfStudents)
{
    std::fstream file(CLASS_DATA_FILE, std::ios::in | std::ios::out);
    if (!file.is_open())
    {
        std::cout << "Error opening the file!" << std::endl;
        return;
    }

    file.seekp(0);               // Move the file pointer to the beginning
    file << newNumberOfStudents; // Write with fixed width

    file.close();
}

// Function to check if a student ID exists in the std::vector
bool StudentManager::doesStudentExist(const std::vector<Student> &students, unsigned short int studentId)
{
    return find_if(students.begin(), students.end(), [studentId](const Student &student)
                   { return student.id == studentId; }) != students.end();
}

// Function to delete a student record
void StudentManager::deleteStudentRecord(std::vector<Student> &students)
{
    // Display the current list of students
    unsigned short int selectedID;
    StudentManager::viewIndividualStudentRecord(students, DELETE_STUDENT_RECORD, selectedID);

    if (selectedID == 0)
    {
        return;
    }
    std::cout << "Please confirm the ID of the student you would like to DELETE or enter 0 to return to Main Menu: ";
    unsigned short int studentIdToDelete;

    // Validate the user's input to ensure it is an integer between the specified range
    if (!(std::cin >> studentIdToDelete) || studentIdToDelete != selectedID || studentIdToDelete < 0 || studentIdToDelete > 9999 || std::cin.peek() != '\n' || std::to_string(studentIdToDelete).length() != 4)
    {
        std::cout << "Student ID did not match! Returning to Main Menu." << std::endl;
        return;
    }
    else if (studentIdToDelete == 0)
    {
        return;
    }

    if (StudentManager::doesStudentExist(students, studentIdToDelete))
    {
        auto it = find_if(students.begin(), students.end(), [studentIdToDelete](const Student &student)
                          { return student.id == studentIdToDelete; });

        // Student found, erase from the std::vector
        students.erase(it);

        // Decrement the number of students in the file
        unsigned short int numberOfStudents = StudentManager::getNumberOfStudents() - 1;

        // Update the file with the modified student records
        std::ofstream file(CLASS_DATA_FILE);
        if (file.is_open())
        {
            file << numberOfStudents;
            for (const auto &student : students)
            {
                file << '\n'
                     << student.id << "," << student.fullName << ","
                     << student.courseMark[0] << "," << student.courseMark[1] << ","
                     << student.courseMark[2] << "," << student.examMark;
            }
            file.close();

            std::cout << "Student record deleted successfully." << std::endl;
        }
        else
        {
            std::cout << "Error opening the file for updating." << std::endl;
        }
    }
    else
    {
        std::cout << "Student with ID " << studentIdToDelete << " not found." << std::endl;
    }
}

// Function to update a student record
void StudentManager::updateStudentRecord(std::vector<Student> &students)
{
    unsigned short int selectedID;
    unsigned short int choice;
    StudentManager::viewIndividualStudentRecord(students, UPDATE_STUDENT_RECORD, selectedID);

    if (selectedID == 0)
    {
        return;
    }
    // Find the selected student
    auto selectedStudent = find_if(students.begin(), students.end(), [selectedID](const Student &student)
                                   { return student.id == selectedID; });

    while (true)
    {
        while (true)
        {
            // Display the current details of the selected student
            StudentManager::displayStudentDetails(*selectedStudent);

            utilities::addSeparator(46, '=');
            std::cout << std::setw(11) << "What would you like to modify?" << std::endl;
            utilities::addSeparator(46, '=');
            std::cout << "1. Student ID" << std::endl;
            std::cout << "2. Student Name" << std::endl;
            std::cout << "3. Course Mark 1" << std::endl;
            std::cout << "4. Course Mark 2" << std::endl;
            std::cout << "5. Course Mark 3" << std::endl;
            std::cout << "6. Exam Mark" << std::endl;
            std::cout << "0. Main Menu" << std::endl;
            utilities::addSeparator(46, '-');
            std::cout << "Choice: ";
            std::cin >> choice;

            if (std::cin.fail() || std::cin.peek() != '\n' || choice < 0 || choice > 6)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input, please try again!" << std::endl;
                utilities::sleep(1200);
            }
            else
            {
                break;
            }
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            while (true)
            {
                utilities::clear();
                StudentManager::displayStudentDetails(*selectedStudent);
                std::cout << "Enter the new ID for the student: ";
                int newID;
                std::cin >> newID;

                // Validate the user's input
                if (std::cin.fail() || std::cin.peek() != '\n' || newID < 1 || newID > 9999 || StudentManager::doesStudentExist(students, newID) || std::to_string(newID).length() != 4)
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "\nInvalid input or ID already exists, please try again!" << std::endl;
                    utilities::sleep(1200);
                }
                else
                {
                    selectedStudent->id = newID;
                    break;
                }
            }
            break;
        case 2:
            while (true)
            {
                utilities::clear();
                StudentManager::displayStudentDetails(*selectedStudent);
                std::cout << "Enter the new name for the student: ";
                std::string newName;
                std::getline(std::cin, newName);
                if (newName.empty() || newName.length() > 30 || newName.find_first_not_of(' ') == std::string::npos || newName.find_first_of("0123456789") != std::string::npos)
                {
                    std::cout << "Invalid name, please try again!" << std::endl;
                    utilities::sleep(1200);
                }
                else
                {
                    // Capitalizes the first letter of each word in the name
                    for (unsigned short int i = 0; i < newName.length(); ++i)
                    {
                        if (i == 0 || newName[i - 1] == ' ')
                        {
                            newName[i] = toupper(newName[i]);
                        }
                        else
                        {
                            newName[i] = tolower(newName[i]);
                        }
                    }

                    selectedStudent->fullName = newName;
                }
                break;
            }
            break;
        case 3:
            while (true)
            {
                utilities::clear();
                displayStudentDetails(*selectedStudent);
                std::cout << "Enter the new mark for Course 1: ";
                int newMark;
                std::cin >> newMark;

                // Validate the user's input
                if (std::cin.fail() || std::cin.peek() != '\n' || newMark < 0 || newMark > 20)
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "\nInvalid input, please try again!" << std::endl;
                    utilities::sleep(1200);
                }
                else
                {
                    selectedStudent->courseMark[0] = newMark;
                    break;
                }
            }
            break;
        case 4:
            while (true)
            {
                utilities::clear();
                StudentManager::displayStudentDetails(*selectedStudent);
                std::cout << "Enter the new mark for Course 2: ";
                int newMark;
                std::cin >> newMark;

                // Validate the user's input
                if (std::cin.fail() || std::cin.peek() != '\n' || newMark < 0 || newMark > 20)
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "\nInvalid input, please try again!" << std::endl;
                    utilities::sleep(1200);
                }
                else
                {
                    selectedStudent->courseMark[1] = newMark;
                    break;
                }
            }
            break;
        case 5:
            while (true)
            {
                utilities::clear();
                StudentManager::displayStudentDetails(*selectedStudent);
                std::cout << "Enter the new mark for Course 3: ";
                int newMark;
                std::cin >> newMark;

                // Validate the user's input
                if (std::cin.fail() || std::cin.peek() != '\n' || newMark < 0 || newMark > 20)
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "\nInvalid input, please try again!" << std::endl;
                    utilities::sleep(1200);
                }
                else
                {
                    selectedStudent->courseMark[2] = newMark;
                    break;
                }
            }
            break;
        case 6:
            while (true)
            {
                utilities::clear();
                StudentManager::displayStudentDetails(*selectedStudent);
                std::cout << "Enter the new Exam mark: ";
                int newMark;
                std::cin >> newMark;

                // Validate the user's input
                if (std::cin.fail() || std::cin.peek() != '\n' || newMark < 0 || newMark > 100)
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "\nInvalid input, please try again!" << std::endl;
                    utilities::sleep(1200);
                }
                else
                {
                    selectedStudent->examMark = newMark;
                    break;
                }
            }
            break;
        default:
            return;
        }

        // Display the updated details of the selected student
        StudentManager::displayStudentDetails(*selectedStudent);

        std::ofstream file(CLASS_DATA_FILE);
        if (file.is_open())
        {
            file << students.size();

            for (const auto &student : students)
            {
                file << '\n'
                     << student.id << "," << student.fullName << ","
                     << student.courseMark[0] << "," << student.courseMark[1] << ","
                     << student.courseMark[2] << "," << student.examMark;
            }

            file.close();
            std::cout << "Student details modified successfully." << std::endl;
            utilities::sleep(1500);
        }
        else
        {
            std::cout << "Error opening the file for updating." << std::endl;
        }

        while (true)
        {
            utilities::clear();
            StudentManager::displayStudentDetails(*selectedStudent);
            utilities::addSeparator(46, '=');
            std::cout << "Would you like to modify another field?" << std::endl;
            utilities::addSeparator(46, '=');
            std::cout << "1. Yes" << std::endl;
            std::cout << "2. No" << std::endl;
            utilities::addSeparator(46, '-');
            std::cout << "Choice: ";
            std::cin >> choice;

            if (std::cin.fail() || std::cin.peek() != '\n' || choice < 1 || choice > 2)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input, please try again!" << std::endl;
                utilities::sleep(1200);
            }
            else
            {
                break;
            }
        }
        if (choice == 2)
        {
            break;
        }
        else
        {
            continue;
        }
    }
}

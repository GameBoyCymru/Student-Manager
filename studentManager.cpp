#include "studentManager.h"
#include "utilities.h"

// Main function
int main()
{
    utilities::clear();
    std::vector<StudentManager::Student> students; // Vector to store the student records
    StudentManager::loadStudentRecords(students);  // Load the student records from the file
    StudentManager::sortStudentsByIDAsc(students); // Sort the student records by ID in ascending order as default
    bool admin = false;
    unsigned short int choice;
    unsigned short int incorrectPasswordAttempts = 0;
    bool accessGranted = false;

    choice = StudentManager::intValidChoice(0, 2, StudentManager::SELECT_USER);
    switch (choice)
    {
    case StudentManager::USER:
        admin = false;
        break;
    case StudentManager::ADMIN:
        admin = true;
        break;
    default:
        utilities::exitProgram();
    }

    while (true)
    {
        if (admin)
        {

            while (!accessGranted)
            {
                utilities::clear();
                std::cout << "Enter the password: ";
                std::string password = StudentManager::takePasswdFromUser();
                if (password == "admin")
                {
                    accessGranted = true;
                    break;
                }
                else if (incorrectPasswordAttempts == 2)
                {
                    std::cout << "\nToo many incorrect password attempts!\n\nPreparing to exit program." << std::endl;
                    utilities::sleep(3000);
                    utilities::exitProgram();
                }
                else
                {
                    incorrectPasswordAttempts++;
                    std::cout << "\nIncorrect password, please try again!" << std::endl;
                    utilities::sleep(1200);
                }
            }

            choice = StudentManager::intValidChoice(0, 8, StudentManager::ADMIN_MENU);
        }
        else
        {
            choice = StudentManager::intValidChoice(0, 5, StudentManager::USER_MENU);
        }

        switch (choice)
        {
        case StudentManager::VIEW_ALL_STUDENT_RECORDS: // View all student records
            StudentManager::viewAllStudentRecords(students);
            break;
        case StudentManager::VIEW_INDIVIDUAL_STUDENT_RECORD: // View individual student record
            unsigned short int selectedID;
            StudentManager::viewIndividualStudentRecord(students, StudentManager::NO_MENU, selectedID);
            utilities::continuePrompt();
            break;
        case StudentManager::SHOW_STUDENT_WITH_HIGHEST_TOTAL_SCORE: // Show student with highest total score
            StudentManager::showStudentWithHighestTotalScore(students);
            utilities::continuePrompt();
            break;
        case StudentManager::SHOW_STUDENT_WITH_LOWEST_TOTAL_SCORE: // Show student with lowest total score
            StudentManager::showStudentWithLowestTotalScore(students);
            utilities::continuePrompt();
            break;
        case StudentManager::SORT_STUDENT_RECORDS: // Sort student records
            StudentManager::sortStudentRecords(students);
            utilities::continuePrompt();
            break;
        case StudentManager::ADD_STUDENT_RECORD: // Add student record
            StudentManager::addStudentRecord(students);
            utilities::continuePrompt();
            break;
        case StudentManager::DELETE_STUDENT_RECORD: // Delete student record
            StudentManager::deleteStudentRecord(students);
            utilities::continuePrompt();
            break;
        case StudentManager::UPDATE_STUDENT_RECORD: // Update student record
            StudentManager::updateStudentRecord(students);
            utilities::continuePrompt();
            break;
        default:
            utilities::exitProgram(); // Exit the program
        }
    }
}

// Function to load the student records from the file
void StudentManager::loadStudents(std::vector<Student> &students, std::ifstream &classData)
{
    // Read and store data for each student
    for (size_t i = 0; i < students.size(); ++i)
    {
        // Read data for each student
        Student &student = students[i];

        // this is used to prevent the comma from being stored in the string
        char comma;

        // read the student ID and comma
        classData >> student.id >> comma;

        // read the full name until the comma
        std::getline(classData, student.fullName, ',');

        // read the course marks and exam mark
        classData >> student.courseMark[0] >> comma >> student.courseMark[1] >> comma >> student.courseMark[2] >> comma >> student.examMark;
    }
}

// Function to load the student records from the file
void StudentManager::loadStudentRecords(std::vector<Student> &students)
{
    try
    {
        std::ifstream classData(CLASS_DATA_FILE);

        if (!classData.is_open())
        {
            throw std::runtime_error("Error: Unable to open the file.");
        }

        unsigned short int numberOfStudents;
        classData >> numberOfStudents;

        // Resize the vector to the correct size before loading students
        students.resize(numberOfStudents);

        StudentManager::loadStudents(students, classData);

        classData.close();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

// Function to get a user input and validate it for a number based menu
unsigned short int StudentManager::intValidChoice(unsigned short int minRange, unsigned short int maxRange, const unsigned short int type)
{
    unsigned short int choice;
    bool failed = true;

    while (failed)
    {

        failed = false;
        utilities::clear();

        StudentManager::displayMenu(type);

        std::cin >> choice;

        // Validate the user's choice to ensure it is an integer between the specified range
        if (choice < minRange || choice > maxRange || std::cin.fail() || std::cin.peek() != '\n')
        {
            failed = true;
            std::cout << "\nInvalid choice, please try again!\n";
            utilities::sleep(1200);
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        if (failed == false)
        {
            break;
        }
    }

    return choice;
}

// Function to display a menu
void StudentManager::displayMenu(const unsigned short int type)
{

    switch (type)
    {
    case SELECT_USER:
        utilities::addSeparator(46, '=');
        std::cout << std::setw(23) << "User Type" << std::endl;
        utilities::addSeparator(46, '=');
        std::cout << "1. User" << std::endl;
        std::cout << "2. Admin" << std::endl;
        std::cout << "0. Exit" << std::endl;
        utilities::addSeparator(46, '-');
        std::cout << "Choice: ";
        break;
    case USER_MENU:
        utilities::addSeparator(46, '=');
        std::cout << std::setw(23) << "Menu" << std::endl;
        utilities::addSeparator(46, '=');
        std::cout << "1. View all student records" << std::endl;
        std::cout << "2. View individual student record" << std::endl;
        std::cout << "3. Show student with the highest total score" << std::endl;
        std::cout << "4. Show student with the lowest total score" << std::endl;
        std::cout << "5. Sort student records" << std::endl;
        std::cout << "0. Exit" << std::endl;
        utilities::addSeparator(46, '-');
        std::cout << "Choice: ";
        break;
    case ADMIN_MENU:
        utilities::addSeparator(46, '=');
        std::cout << std::setw(23) << "Menu" << std::endl;
        utilities::addSeparator(46, '=');
        std::cout << "1. View all student records" << std::endl;
        std::cout << "2. View individual student record" << std::endl;
        std::cout << "3. Show student with the highest total score" << std::endl;
        std::cout << "4. Show student with the lowest total score" << std::endl;
        std::cout << "5. Sort student records" << std::endl;
        std::cout << "6. Add a student record" << std::endl;
        std::cout << "7. Delete a student record" << std::endl;
        std::cout << "8. Update a student's record" << std::endl;
        std::cout << "0. Exit" << std::endl;
        utilities::addSeparator(46, '-');
        std::cout << "Choice: ";
        break;
    case SORT_STUDENT_RECORDS:
        utilities::addSeparator(50, '=');
        std::cout << " How would you like to sort the student records?" << std::endl;
        utilities::addSeparator(50, '=');
        std::cout << "1. Sort by ID (Ascending)" << std::endl;
        std::cout << "2. Sort by ID (Descending)" << std::endl;
        std::cout << "3. Sort Alphabetically (Ascending)" << std::endl;
        std::cout << "4. Sort Alphabetically (Descending)" << std::endl;
        utilities::addSeparator(50, '-');
        std::cout << "Choice: ";
        break;
    }
}

/* Function to take password from user and cover with *
Although it might be slightly modified, I originally sourced this function from: https://www.geeksforgeeks.org/taking-password-as-input-in-cpp/
*/
std::string StudentManager::takePasswdFromUser(char sp)
{
    std::string passwd = "";
    char ch_ipt;

    while (true)
    {

        // Get the input from the user
        ch_ipt = _getch(); // _getch() is used to get a single character from the user without echoing it to the console

        // If the input is enter, terminate the std::string
        if (ch_ipt == IN::RETURN)
        {
            std::cout << std::endl;
            return passwd;
        }
        // If the input is a backspace, delete the last character
        else if (ch_ipt == IN::BACKSPACE && passwd.length() != 0)
        {
            passwd.pop_back();

            std::cout << "\b \b";

            continue;
        }

        // If the input is a backspace and the std::string is empty, do nothing
        else if (ch_ipt == IN::BACKSPACE && passwd.length() == 0)
        {
            continue;
        }
        passwd.push_back(ch_ipt);
        std::cout << sp;
    }
}

// Function to check if the std::vector is empty
bool StudentManager::emptyVector(const std::vector<Student> &students)
{
    if (students.empty())
    {
        utilities::clear();
        utilities::addSeparator(45, '=');
        std::cout << "There are no students to view." << std::endl;
        utilities::addSeparator(45, '=');
        utilities::continuePrompt();

        return true;
    }

    return false;
}
#include "studentManager.h"
#include "utilities.h"


// Function to calculate the grade for a student
char StudentManager::calculateGrade(float percentage)
{
    char grade;

    // round the percentage to the nearest integer
    unsigned short int mark = static_cast<unsigned short int>(percentage + 0.5f);
    switch (mark / 10)  
    {
    case 4:
        grade = 'D';
        break;
    case 5:
        grade = 'C';
        break;
    case 6:
        grade = 'B';
        break;
    case 7:
    case 8:
    case 9:
    case 10:
        grade = 'A';
        break;
    default:
        grade = 'F';
        break;
    }

    return grade;
}

// Function to view all student records
void StudentManager::viewAllStudentRecords(const std::vector<Student> &students)
{
    utilities::clear();

    // Check if the vector is empty
    if (StudentManager::emptyVector(students))
    {
        return;
    }

    // Printf to format the output in a grid
    printf("| %-3s  | %-30s | %-7s | %-10s | %-11s | %-17s | %-6s |\n", "ID:", "Name:", "Course Total:", "Exam Mark:", "Overall Mark:", "Overall Percentage:", "Grade:");
    utilities::addSeparator(117, '=');

    float classPercentage = 0.0f;

    for (const auto &student : students)
    {
        unsigned short int total = student.courseMark[0] + student.courseMark[1] + student.courseMark[2] + student.examMark;
        unsigned short int courseMarkTotal = total - student.examMark;

        classPercentage += total / 1.6f;

        char grade = StudentManager::calculateGrade(total / 1.6f);

        // Output the rounded percentage
        printf("| %-4d | %-30s |      %-8d |    %-7d |     %-9d |        %-7.1f%%     |    %-2c  |\n",
               student.id, student.fullName.c_str(), courseMarkTotal, student.examMark, total,
               (total/1.6f), grade);
    }
    utilities::addSeparator(117, '-');
    // Output the average percentage and grade for the class
    std::cout << "Based on this class of " << students.size() << " Students, the average percentage was " << std::setprecision(1) << std::fixed << classPercentage / students.size() << " % (Grade: " << StudentManager::calculateGrade(classPercentage / students.size()) << ")." << std::endl;
    utilities::addSeparator(85, '=');

    utilities::continuePrompt();
}

// Function to display individual student details
void StudentManager::displayStudentDetails(const Student &student)
{
    utilities::clear();
    std::cout << "Student Details:" << std::endl;
    utilities::addSeparator(28, '-');
    std::cout << std::endl;
    printf("| %-3s  | %-30s | %-9s | %-9s | %-9s | %-10s | %-11s | %-17s | %-6s |\n", "ID:", "Name:", "Course Mark 1:", "Course Mark 2:", "Course Mark 3:", "Exam Mark:", "Overall Mark:", "Overall Percentage:", "Grade:");
    utilities::addSeparator(152, '=');
    unsigned short int total = student.courseMark[0] + student.courseMark[1] + student.courseMark[2] + student.examMark;

    char grade = StudentManager::calculateGrade(total / 1.6f);

    printf("| %-4d | %-30s |        %-7d |        %-7d |        %-7d |     %-6d |      %-8d |        %-7.1f%%     |    %-2c  |\n",
           student.id, student.fullName.c_str(), student.courseMark[0], student.courseMark[1], student.courseMark[2], student.examMark, total,
           (total/1.6f), grade);

    utilities::addSeparator(152, '-');
}

// Function to display student with highest or lowest overall mark
void StudentManager::displayHighestLowestRecord(const std::vector<const Student *> &maxMinStudent) {
    printf("| %-3s  | %-30s | %-9s | %-9s | %-9s | %-10s | %-11s | %-17s | %-6s |\n", "ID:", "Name:", "Course Mark 1:", "Course Mark 2:", "Course Mark 3:", "Exam Mark:", "Overall Mark:", "Overall Percentage:", "Grade:");
    utilities::addSeparator(152, '=');
    for (const auto &student : maxMinStudent)
    {
        unsigned short int total = student->courseMark[0] + student->courseMark[1] + student->courseMark[2] + student->examMark;

        char grade = StudentManager::calculateGrade(total / 1.6f);

        printf("| %-4d | %-30s |        %-7d |        %-7d |        %-7d |     %-6d |      %-8d |        %-7.1f%%     |    %-2c  |\n",
               student->id, student->fullName.c_str(), student->courseMark[0], student->courseMark[1], student->courseMark[2], student->examMark, total,
               (total/1.6f), grade);
    }

    utilities::addSeparator(152, '-');

}

// Function to view an individual student record
void StudentManager::viewIndividualStudentRecord(std::vector<Student> &students, unsigned short int type, unsigned short int &selectedID)
{
    while (true)
    {
        utilities::clear();

        if (emptyVector(students))
        {
            return;
        }

        if (type == UPDATE_STUDENT_RECORD)
        {
            std::cout << "Update a student record" << std::endl;
            utilities::addSeparator(24, '-');
        }
        else if (type == DELETE_STUDENT_RECORD)
        {
            std::cout << "Delete a student record" << std::endl;
            utilities::addSeparator(24, '-');
        }
        else
        {
            std::cout << "View an individual student record" << std::endl;
            utilities::addSeparator(34, '-');
        }

        printf("| %-3s  | %-30s |\n", "ID:", "Name:");
        utilities::addSeparator(41, '=');

        // Display the student IDs and names
        for (const auto &student : students)
        {
            printf("| %-4d | %-30s |\n", student.id, student.fullName.c_str());
        }

        utilities::addSeparator(41, '-');

        bool validInput = false;

        std::cout << "Enter the ID of the student or 0 to return to Main Menu." << std::endl;
        std::cout << "\nInput: ";
        std::cin >> selectedID;

        if (std::cin.fail() || std::cin.peek() != '\n' || selectedID < 0 || selectedID > 9999)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input, please try again!" << std::endl;
            utilities::sleep(1200);
        }
        else
        {
            // Check if the entered ID is valid
            if (find_if(students.begin(), students.end(), [selectedID](const Student &student)
                        { return student.id == selectedID; }) != students.end())
            {
                validInput = true;
            }
            else if (selectedID == 0)
            {
                return;
            }

            if (!validInput)
            {
                std::cout << "Invalid input, please try again!" << std::endl;
                utilities::sleep(1200);
                utilities::clear();
            }
            else
            {
                break;
            }
        }
    }

    // Find the selected student
    auto selectedStudent = find_if(students.begin(), students.end(), [selectedID](const Student &student)
                                   { return student.id == selectedID; });

    // Display the individual student record
    displayStudentDetails(*selectedStudent);
}

// Function to show students with the highest total score
void StudentManager::showStudentWithHighestTotalScore(const std::vector<Student> &students)
{
    utilities::clear();

    if (emptyVector(students))
    {
        return;
    }

    std::vector<const Student *> maxMinStudents;

    // Find the highest total score
    auto highestTotalScore = max_element(students.begin(), students.end(), [](const Student &a, const Student &b)
                                         { return (a.courseMark[0] + a.courseMark[1] + a.courseMark[2] + a.examMark) < (b.courseMark[0] + b.courseMark[1] + b.courseMark[2] + b.examMark); });

    for (const auto &student : students)
    {
        if (student.courseMark[0] + student.courseMark[1] + student.courseMark[2] + student.examMark == highestTotalScore->courseMark[0] + highestTotalScore->courseMark[1] + highestTotalScore->courseMark[2] + highestTotalScore->examMark)
        {
            maxMinStudents.push_back(&student);
        }
    }

    if (maxMinStudents.size() > 1)
    {
        std::cout << "Highest Performing Students" << std::endl;
        utilities::addSeparator(25, '-');
    }
    else
    {
        std::cout << "Highest Performing Student" << std::endl;
        utilities::addSeparator(25, '-');
    }
    std::cout << std::endl;

    // Display the student records that have the same highest total score
    displayHighestLowestRecord(maxMinStudents);

}

// Function to show the student with the lowest total score
void StudentManager::showStudentWithLowestTotalScore(const std::vector<Student> &students)
{

    utilities::clear();
    if (emptyVector(students))
    {
        return;
    }

    // Find the lowest total score
    auto lowestTotalScore = max_element(students.begin(), students.end(), [](const Student &a, const Student &b)
                                        { return (a.courseMark[0] + a.courseMark[1] + a.courseMark[2] + a.examMark) > (b.courseMark[0] + b.courseMark[1] + b.courseMark[2] + b.examMark); });

    // Find all students with the same highest total score
    std::vector<const Student *> minMaxStudents;

    for (const auto &student : students)
    {
        if (student.courseMark[0] + student.courseMark[1] + student.courseMark[2] + student.examMark == lowestTotalScore->courseMark[0] + lowestTotalScore->courseMark[1] + lowestTotalScore->courseMark[2] + lowestTotalScore->examMark)
        {
            minMaxStudents.push_back(&student);
        }
    }

    if (minMaxStudents.size() > 1)
    {
        std::cout << "Lowest Performing Students" << std::endl;
        utilities::addSeparator(27, '-');
    }
    else
    {
        std::cout << "Lowest Performing Student" << std::endl;
        utilities::addSeparator(27, '-');
    }
    std::cout << std::endl;

    // Display the student records that have the same lowest total score
    displayHighestLowestRecord(minMaxStudents);
}

// Function to sort the student records
void StudentManager::sortStudentRecords(std::vector<Student> &students)
{
    utilities::clear();
    if (emptyVector(students))
    {
        return;
    }

    unsigned short int choice = intValidChoice(1, 4, SORT_STUDENT_RECORDS);

    switch (choice)
    {
    case 1:
        sortStudentsByIDAsc(students);
        std::cout << "\nSorted by ID in ascending order." << std::endl;
        break;
    case 2:
        sortStudentsByIDDes(students);
        std::cout << "\nSorted by ID in descending order." << std::endl;
        break;
    case 3:
        sortStudentsAlphabeticallyAsc(students);
        std::cout << "\nSorted Alphabetically by name in ascending order." << std::endl;
        break;
    case 4:
        sortStudentsAlphabeticallyDes(students);
        std::cout << "\nSorted Alphabetically by name in descending order." << std::endl;
        break;
    }
}

// Function to sort students by ID in ascending order
void StudentManager::sortStudentsByIDAsc(std::vector<Student> &students)
{
    sort(students.begin(), students.end(), [](const Student &a, const Student &b)
         { return a.id < b.id; });
}

// Function to sort students by ID in descending order
void StudentManager::sortStudentsByIDDes(std::vector<Student> &students)
{
    sort(students.begin(), students.end(), [](const Student &a, const Student &b)
         { return a.id > b.id; });
}

// Function to sort students alphabetically by name in ascending order
void StudentManager::sortStudentsAlphabeticallyAsc(std::vector<Student> &students)
{
    sort(students.begin(), students.end(), [](const Student &a, const Student &b)
         { return a.fullName < b.fullName; });
}

// Function to sort students alphabetically by name in descending order
void StudentManager::sortStudentsAlphabeticallyDes(std::vector<Student> &students)
{
    sort(students.begin(), students.end(), [](const Student &a, const Student &b)
         { return a.fullName > b.fullName; });
}

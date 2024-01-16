#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <iterator>
#include <limits>
#include <conio.h>

class StudentManager
{
public:
    // Struct to store student data
    struct Student
    {
        unsigned short int id;
        std::string fullName;
        unsigned short int courseMark[3];
        unsigned short int examMark;
    };
    // Vector to store the student records
    std::vector<Student> students;

    std::vector<Student *> maxMinStudent; // Vector to store student with highest and lowest total score

    ~StudentManager()
    {
        students.clear();
    }

    // Loads students into vector
    static void loadStudents(std::vector<Student> &students, std::ifstream &classData);
    
    // Loads student records from file and resizes vector
    static void loadStudentRecords(std::vector<Student> &students);

    // Sorts students by ID in ascending order
    static void sortStudentsByIDAsc(std::vector<Student> &students);

    // Sorts students by ID in descending order
    static void sortStudentsByIDDes(std::vector<Student> &students);

    // Sorts students alphabetically in ascending order
    static void sortStudentsAlphabeticallyAsc(std::vector<Student> &students);

    // Sorts students alphabetically in descending order
    static void sortStudentsAlphabeticallyDes(std::vector<Student> &students);

    // Validates integer input
    static unsigned short int intValidChoice(unsigned short int minRange, unsigned short int maxRange, const unsigned short int type);

    // Calculates grade based on total score
    static char calculateGrade(float totalScore);

    // Views all student records
    static void viewAllStudentRecords(const std::vector<Student> &students);

    // Views individual student record
    static void viewIndividualStudentRecord(std::vector<Student> &students, const unsigned short int type, unsigned short int &selectedID);
    
    // Shows student with highest total score
    static void showStudentWithHighestTotalScore(const std::vector<Student> &students);

    // Shows student with lowest total score
    static void showStudentWithLowestTotalScore(const std::vector<Student> &students);

    // Sorts student records
    static void sortStudentRecords(std::vector<Student> &students);

    // Adds a student record
    static void addStudentRecord(std::vector<Student> &students);

    // Deletes a student record
    static void deleteStudentRecord(std::vector<Student> &students);

    // Updates a student record
    static void updateStudentRecord(std::vector<Student> &students);

    // Takes password from user
    static std::string takePasswdFromUser(char sp = '*');

    // Checks if vector is empty
    static bool emptyVector(const std::vector<Student> &students);

    // Gets number of students
    static unsigned short int getNumberOfStudents();

    // Updates number of students
    static void updateNumberOfStudents(unsigned short int newNumberOfStudents);

    // Checks if student exists
    static bool doesStudentExist(const std::vector<Student> &students, unsigned short int studentId);

    // Displays details of a single student
    static void displayStudentDetails(const Student &student);

    // Displays a menu based on the parameter
    static void displayMenu(const unsigned short int type);

    // Displays highest or lowest record based on the data passed in the parameter
    static void displayHighestLowestRecord(const std::vector<const Student *> &maxMinStudent);


    // Enumerator for user types for code readability
enum UserType
    {
        SELECT_USER = 0,
        USER,
        ADMIN,
        USER_MENU,
        ADMIN_MENU
    };

    // Enumerator for menu options for code readability
    enum MenuOptions
    {
        NO_MENU = 0,
        VIEW_ALL_STUDENT_RECORDS,
        VIEW_INDIVIDUAL_STUDENT_RECORD,
        SHOW_STUDENT_WITH_HIGHEST_TOTAL_SCORE,
        SHOW_STUDENT_WITH_LOWEST_TOTAL_SCORE,
        SORT_STUDENT_RECORDS,
        ADD_STUDENT_RECORD,
        DELETE_STUDENT_RECORD,
        UPDATE_STUDENT_RECORD
    };


private:
    // Enumerator for input characters
    enum IN
    {
        BACKSPACE = 8, // ASCII value of backspace key
        RETURN = 13    // ASCII value of enter key
    };
};

const std::string CLASS_DATA_FILE = "studentMarks.txt";             // File to store student records

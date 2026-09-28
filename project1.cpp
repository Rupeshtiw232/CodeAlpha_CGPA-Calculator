#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std;

// Structure for storing subject details
struct Subject
{
    string name;
    float credits;
    string grade;
    float gradePoint;
};

// Structure for storing semester details
struct Semester
{
    int semesterNumber;
    vector<Subject> subjects;
    float sgpa;
    float totalCredits;
};

// Function to convert grade into grade point
float getGradePoint(string grade)
{
    for (char &c : grade)
    {
        c = toupper(c);
    }

    if (grade == "A+")
        return 10;
    else if (grade == "A")
        return 9;
    else if (grade == "B+")
        return 8;
    else if (grade == "B")
        return 7;
    else if (grade == "C+")
        return 6;
    else if (grade == "C")
        return 5;
    else if (grade == "D")
        return 4;
    else if (grade == "F")
        return 0;
    else
        return -1;
}

// Function to calculate SGPA
float calculateSGPA(vector<Subject> &subjects)
{
    float totalCredits = 0;
    float totalPoints = 0;

    for (Subject &s : subjects)
    {
        totalCredits += s.credits;
        totalPoints += s.credits * s.gradePoint;
    }

    if (totalCredits == 0)
        return 0;

    return totalPoints / totalCredits;
}

// Function to display semester result
void displaySemester(Semester &sem)
{
    cout << "\n============================================================\n";
    cout << "                 SEMESTER " << sem.semesterNumber << " RESULT\n";
    cout << "============================================================\n";

    cout << left
         << setw(25) << "Subject"
         << setw(10) << "Credits"
         << setw(10) << "Grade"
         << setw(12) << "Grade Point"
         << "\n";

    cout << "------------------------------------------------------------\n";

    for (Subject &s : sem.subjects)
    {
        cout << left
             << setw(25) << s.name
             << setw(10) << s.credits
             << setw(10) << s.grade
             << setw(12) << s.gradePoint
             << "\n";
    }

    cout << "------------------------------------------------------------\n";

    cout << fixed << setprecision(2);
    cout << "Total Credits : " << sem.totalCredits << endl;
    cout << "SGPA          : " << sem.sgpa << endl;

    cout << "============================================================\n";
}

// Function to calculate overall CGPA
float calculateCGPA(vector<Semester> &semesters)
{
    float totalCredits = 0;
    float totalPoints = 0;

    for (Semester &sem : semesters)
    {
        for (Subject &s : sem.subjects)
        {
            totalCredits += s.credits;
            totalPoints += s.credits * s.gradePoint;
        }
    }

    if (totalCredits == 0)
        return 0;

    return totalPoints / totalCredits;
}

// Function to add a new semester
void addSemester(vector<Semester> &semesters)
{
    Semester sem;

    cout << "\nEnter semester number: ";
    cin >> sem.semesterNumber;

    int n;

    cout << "Enter number of subjects: ";
    cin >> n;

    if (n <= 0)
    {
        cout << "Invalid number of subjects!\n";
        return;
    }

    for (int i = 0; i < n; i++)
    {
        Subject s;

        cout << "\nSubject " << i + 1 << endl;

        cin.ignore();

        cout << "Enter subject name: ";
        getline(cin, s.name);

        cout << "Enter credits: ";
        cin >> s.credits;

        if (s.credits <= 0)
        {
            cout << "Invalid credits!\n";
            i--;
            continue;
        }

        while (true)
        {
            cout << "Enter grade (A+, A, B+, B, C+, C, D, F): ";
            cin >> s.grade;

            s.gradePoint = getGradePoint(s.grade);

            if (s.gradePoint != -1)
                break;

            cout << "Invalid grade! Please enter again.\n";
        }

        sem.subjects.push_back(s);
    }

    sem.sgpa = calculateSGPA(sem.subjects);

    sem.totalCredits = 0;

    for (Subject &s : sem.subjects)
    {
        sem.totalCredits += s.credits;
    }

    semesters.push_back(sem);

    cout << "\nSemester added successfully!\n";
}

// Function to display all semesters
void displayAllSemesters(vector<Semester> &semesters)
{
    if (semesters.empty())
    {
        cout << "\nNo semester data available.\n";
        return;
    }

    for (Semester &sem : semesters)
    {
        displaySemester(sem);
    }
}

// Function to display CGPA
void displayCGPA(vector<Semester> &semesters)
{
    if (semesters.empty())
    {
        cout << "\nNo semester data available.\n";
        return;
    }

    float cgpa = calculateCGPA(semesters);

    cout << "\n========================================\n";
    cout << "             OVERALL RESULT\n";
    cout << "========================================\n";

    cout << fixed << setprecision(2);

    cout << "Number of Semesters : " << semesters.size() << endl;
    cout << "Overall CGPA        : " << cgpa << endl;

    cout << "========================================\n";
}

// Function to display menu
void displayMenu()
{
    cout << "\n\n";
    cout << "==============================================\n";
    cout << "          C++ CGPA CALCULATOR\n";
    cout << "==============================================\n";

    cout << "1. Add Semester Result\n";
    cout << "2. View All Semester Results\n";
    cout << "3. Calculate Overall CGPA\n";
    cout << "4. Exit\n";

    cout << "==============================================\n";
    cout << "Enter your choice: ";
}

int main()
{
    vector<Semester> semesters;

    int choice;

    do
    {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            addSemester(semesters);
            break;

        case 2:
            displayAllSemesters(semesters);
            break;

        case 3:
            displayCGPA(semesters);
            break;

        case 4:
            cout << "\nThank you for using CGPA Calculator!\n";
            break;

        default:
            cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 4);

    return 0;
}
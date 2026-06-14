/*
    Attendance Management System
    Developed by Koushik
    Technology: C++
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function Declarations
int adminView();
int studentView();
int studentLogin();
int adminLogin();

int registerStudent();
int deleteAllStudents();
int deleteStudentByRollNo();
int checkListOfStudentsRegistered();
int checkPresenceCountByRollNo();
int getListOfStudentsWithTheirPresenceCount();

int checkStudentCredentials(string username, string password);

int markMyAttendance(string username);
int countMyAttendance(string username);
int calculateAttendancePercentage(string username);

int delay();

// Delay Function
int delay()
{
    cout << "\nSaving Records...";
    return 0;
}

// Admin Panel
int adminView()
{
    int goBack = 0;

    while (1)
    {
        system("cls");

        cout << "\n========== ADMIN PANEL ==========\n";

        cout << "\n1. Register a Student";
        cout << "\n2. Delete All Students";
        cout << "\n3. Delete Student by Roll Number";
        cout << "\n4. View Registered Students";
        cout << "\n5. Check Attendance Count by Roll Number";
        cout << "\n6. View Students with Attendance Count";
        cout << "\n0. Go Back";

        int choice;

        cout << "\n\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            registerStudent();
            break;

        case 2:
            deleteAllStudents();
            break;

        case 3:
            deleteStudentByRollNo();
            break;

        case 4:
            checkListOfStudentsRegistered();
            break;

        case 5:
            checkPresenceCountByRollNo();
            break;

        case 6:
            getListOfStudentsWithTheirPresenceCount();
            break;

        case 0:
            goBack = 1;
            break;

        default:
            cout << "\nInvalid Choice!";
            getchar();
        }

        if (goBack == 1)
            break;
    }

    return 0;
}

// Student Login
int studentLogin()
{
    system("cls");

    cout << "\n========== STUDENT LOGIN ==========\n";

    studentView();

    delay();

    return 0;
}

// Admin Login
int adminLogin()
{
    system("cls");

    cout << "\n========== ADMIN LOGIN ==========\n";

    string username;
    string password;

    cout << "\nEnter Username: ";
    cin >> username;

    cout << "Enter Password: ";
    cin >> password;

    if (username == "admin" && password == "Koushik@2026")
    {
        adminView();
    }
    else
    {
        cout << "\nInvalid Credentials!";
        cout << "\nPress any key...";
        getchar();
        getchar();
    }

    return 0;
}

// Check Student Credentials
int checkStudentCredentials(string username, string password)
{
    ifstream read("db.dat");

    string user;
    string pass;

    while (read >> user >> pass)
    {
        if (user == username && pass == password)
        {
            return 1;
        }
    }

    return 0;
}

// Student Menu
int studentView()
{
    string username;
    string password;

    cout << "\nEnter Username: ";
    cin >> username;

    cout << "Enter Password: ";
    cin >> password;

    int res = checkStudentCredentials(username, password);

    if (res == 0)
    {
        cout << "\nInvalid Credentials!";
        getchar();
        getchar();
        return 0;
    }

    int goBack = 0;

    while (1)
    {
        system("cls");

        cout << "\n========== STUDENT PANEL ==========\n";

        cout << "\n1. Mark Attendance";
        cout << "\n2. Count My Attendance";
        cout << "\n3. Calculate Attendance Percentage";
        cout << "\n0. Go Back";

        int choice;

        cout << "\n\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            markMyAttendance(username);
            break;

        case 2:
            countMyAttendance(username);
            break;

        case 3:
            calculateAttendancePercentage(username);
            break;

        case 0:
            goBack = 1;
            break;

        default:
            cout << "\nInvalid Choice!";
            getchar();
        }

        if (goBack == 1)
            break;
    }

    return 0;
}

// Register Student
int registerStudent()
{
    system("cls");

    cout << "\n========== REGISTER STUDENT ==========\n";

    string name;
    string username;
    string password;
    string rollno;
    string father;
    string mother;

    char address[100];

    cout << "\nEnter Name: ";
    cin >> name;

    cout << "Enter Username: ";
    cin >> username;

    cout << "Enter Password: ";
    cin >> password;

    cout << "Enter Roll Number: ";
    cin >> rollno;

    getchar();

    cout << "Enter Address: ";
    cin.getline(address, 100);

    cout << "Enter Father Name: ";
    cin >> father;

    cout << "Enter Mother Name: ";
    cin >> mother;

    // Check Existing Username
    ifstream read("db.dat");

    string line;

    while (getline(read, line))
    {
        if (line == username + "-" + password + ".dat")
        {
            cout << "\nUsername already exists!";
            getchar();
            getchar();
            return 0;
        }
    }

    read.close();

    // Save Username
    ofstream out("db.dat", ios::app);

    out << username << " " << password << "\n";

    out.close();

    // Save Student Data
    string filename = username + ".dat";

    ofstream studentFile(filename.c_str());

    studentFile << name << "\n";
    studentFile << username << "\n";
    studentFile << password << "\n";
    studentFile << rollno << "\n";
    studentFile << address << "\n";
    studentFile << father << "\n";
    studentFile << mother << "\n";

    studentFile.close();

    cout << "\nStudent Registered Successfully!";

    getchar();
    getchar();

    return 0;
}

// Mark Attendance
int markMyAttendance(string username)
{
    ofstream attendance;

    string filename = username + "_attendance.dat";

    attendance.open(filename.c_str(), ios::app);

    attendance << "Present\n";

    attendance.close();

    cout << "\nAttendance Marked Successfully!";

    getchar();
    getchar();

    return 0;
}

// Count Attendance
int countMyAttendance(string username)
{
    ifstream attendance;

    string filename = username + "_attendance.dat";

    attendance.open(filename.c_str());

    int count = 0;

    string line;

    while (getline(attendance, line))
    {
        count++;
    }

    attendance.close();

    cout << "\nTotal Attendance: " << count;

    getchar();
    getchar();

    return 0;
}

// Attendance Percentage
int calculateAttendancePercentage(string username)
{
    ifstream attendance;

    string filename = username + "_attendance.dat";

    attendance.open(filename.c_str());

    int attended = 0;

    string line;

    while (getline(attendance, line))
    {
        attended++;
    }

    attendance.close();

    int totalClasses = 30;

    float percentage = (attended * 100.0) / totalClasses;

    cout << "\nAttendance Percentage: " << percentage << "%";

    getchar();
    getchar();

    return 0;
}

// View Registered Students
int checkListOfStudentsRegistered()
{
    system("cls");

    cout << "\n========== REGISTERED STUDENTS ==========\n";

    ifstream read("db.dat");

    string line;

    while (getline(read, line))
    {
        cout << "\n" << line;
    }

    read.close();

    getchar();
    getchar();

    return 0;
}

// Placeholder Functions
int deleteAllStudents()
{
    cout << "\nFeature Coming Soon!";
    getchar();
    getchar();
    return 0;
}

int deleteStudentByRollNo()
{
    cout << "\nFeature Coming Soon!";
    getchar();
    getchar();
    return 0;
}

int checkPresenceCountByRollNo()
{
    cout << "\nFeature Coming Soon!";
    getchar();
    getchar();
    return 0;
}

int getListOfStudentsWithTheirPresenceCount()
{
    cout << "\nFeature Coming Soon!";
    getchar();
    getchar();
    return 0;
}

// Main Function
int main()
{
    while (1)
    {
        system("cls");

        cout << "\n====================================";
        cout << "\n     ATTENDANCE MANAGEMENT SYSTEM";
        cout << "\n====================================\n";

        cout << "\n1. Student Login";
        cout << "\n2. Admin Login";
        cout << "\n0. Exit";

        int choice;

        cout << "\n\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            studentLogin();
            break;

        case 2:
            adminLogin();
            break;

        case 0:
        {
            char ex;

            cout << "\nAre you sure you want to exit? (y/n): ";
            cin >> ex;

            if (ex == 'y' || ex == 'Y')
            {
                cout << "\nThank you for using the system.";
                exit(0);
            }

            break;
        }

        default:
            cout << "\nInvalid Choice!";
            getchar();
        }
    }

    return 0;
}
#include "CauHoi.h"
#include "DLList.h"
#include "DS.h"
#include <conio.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <unistd.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_BACKSPACE 8
#define KEY_ESC 27

using namespace std;

enum ERole {
    Teacher,
    Student
};

enum EOptions {
    Option1 = 0,
    Option2 = 1,
    Option3 = 2,
    Option4 = 3
};

enum EMenu {
    Main,
    Teacher,
    Student,
    Subject
};

/*
    - Cac ham Print... la de in cac options
    - Cac ham Menu la de chay logic chon option
 */

/*
Menu.h
    StartMenu
    StudentMenu
    TeacherMenu
    SelectSubject
    PrintMenu
    SelectChapter
    PrintSelectChapter
Test.h
    StartTest
    Test
Login.h
    Login
    LogInAnimate
    CheckValidLogin
 */

struct Menu {

    string username = "";
    string password = "";

    void StartMenu() {
        int option = 20000;
        while (true) {
            system("cls");
            cout << "===== TEST SIMULATOR =====\n";
            PrintMenu(EMenu::Main, option);
            int ex = getch();

            if (ex == KEY_ENTER) {
                switch (option % 4) {
                // Studen Login
                case Option1:
                    cout << "\nSTUDENT LOGIN\n";
                    Login(ERole::Student);
                    break;
                // Student Signup
                case Option2:
                    cout << "\nSTUDENT SIGNUP\n";
                    break;
                // Teeacher Login
                case Option3:
                    Login(ERole::Teacher);
                    break;
                case Option4:
                    system("cls");
                    Exit();
                    break;
                default:
                    break;
                }
            }
            else if (ex == KEY_UP) {
                option -= 1;
            }
            else if (ex == KEY_DOWN) {
                option += 1;
            }
            else if (ex == KEY_ESC) {
                system("cls");
                Exit();
            }
        }
    }
    // Sau khi HS da dang nhap
    void StudentMenu() {
        int option = 20000;
        while (true) {
            system("cls");
            cout << "Hello, " << username << endl;
            cout << "===============================\n";
            PrintMenu(EMenu::Student, option);
            int ex = getch();

            if (ex == KEY_ENTER) {
                switch (option % 4) {
                case Option1:
                    cout << "\nSelect test\n";
                    SelectSubject();
                    break;
                case Option2:
                    cout << "\nCheck result\n";
                    // XemDiem();
                    break;
                case Option3:
                    cout << "\nChange Password\n";
                    break;
                case Option4:
                    username.clear();
                    password.clear();
                    return;
                default:
                    break;
                }
            }
            else if (ex == KEY_UP) {
                option -= 1;
            }
            else if (ex == KEY_DOWN) {
                option += 1;
            }
            else if (ex == KEY_ESC) {
                system("cls");
                Exit();
            }
        }
    }
    void TeacherMenu() {
        int option = 20000;
        while (true) {
            system("cls");
            cout << "Hello, " << username << endl;
            cout << "===============================\n";
            PrintMenu(EMenu::Teacher, option);
            int ex = getch();

            if (ex == KEY_ENTER) {
                switch (option % 4) {
                case Option1:
                    cout << "\nCheck Students' scores\n";
                    // Hàm show score của HS
                    break;
                case Option2:
                    cout << "\nAdd chapter\n";
                    // XemDiem();
                    break;
                case Option3:
                    cout << "\nChange Password\n";
                    break;
                case Option4:
                    cout << "Log Out";
                    username.clear();
                    password.clear();
                    return;
                default:
                    break;
                }
            }
            else if (ex == KEY_UP) {
                option -= 1;
            }
            else if (ex == KEY_DOWN) {
                option += 1;
            }
            else if (ex == KEY_ESC) {
                system("cls");
                Exit();
            }
        }
    }
    // Chọn môn học
    void SelectSubject() {
        int option = 20000;
        while (true) {
            system("cls");
            cout << "Hello, " << username << endl;
            cout << "===============================\n";
            cout << "=========SELECT SUBJECT========\n";
            PrintMenu(EMenu::Subject, option);
            int ex = getch();

            if (ex == KEY_ENTER) {
                switch (option % 4) {
                case Option1:
                    cout << "\nToan\n";
                    SelectChapter("Toan");
                    break;
                case Option2:
                    cout << "\nLy\n";
                    SelectChapter("Ly");
                    break;
                case Option3:
                    cout << "\nHoa\n";
                    SelectChapter("Hoa");
                    break;
                case Option4:
                    return;
                default:
                    break;
                }
            }
            else if (ex == KEY_UP) {
                option -= 1;
            }
            else if (ex == KEY_DOWN) {
                option += 1;
            }
            else if (ex == KEY_ESC) {
                system("cls");
                Exit();
            }
        }
    }
    // Man hinh chon Chapter
    void SelectChapter(string monhoc) {
        int option = 20000;
        while (true) {
            system("cls");
            cout << "Hello, " << username << endl;
            cout << "===============================\n";
            cout << "=========SELECT CHAPTER========\n";
            PrintMenu(monhoc, option);
            int ex = getch();

            if (ex == KEY_ENTER) {
                switch (option % 4) {
                case Option1:
                    cout << "SUBJECT: " << monhoc << "\tCHAPTER " << option % 4 + 1;
                    StartTest(monhoc, 1);
                    break;
                case Option2:
                    cout << "SUBJECT: " << monhoc << "\tCHAPTER " << option % 4 + 1;
                    StartTest(monhoc, 2);
                    break;
                case Option3:
                    cout << "SUBJECT: " << monhoc << "\tCHAPTER " << option % 4 + 1;
                    StartTest(monhoc, 3);
                    break;
                case Option4:
                    return;
                default:
                    break;
                }
            }
            else if (ex == KEY_UP) {
                option -= 1;
            }
            else if (ex == KEY_DOWN) {
                option += 1;
            }
            else if (ex == KEY_ESC) {
                system("cls");
                Exit();
            }
        }
    }

    void Exit() {
        cout << "Do you want to exit? (Y/N): ";
        char o;
        cin >> o;
        if (tolower(o) == 'y') {
            exit(0);
        }
    }

    // Login.h
    void Login(ERole role);
    void LogInAnimate();
    bool CheckValidLogin(string userInp, string passInp, ERole role);
    // PrintMenu.h
    void PrintMenu(EMenu type, int option);
    void PrintMenu(string monhoc, int option);
    // Test.h
    void StartTest(string monhoc, int chapter);
    void Test(DLList Question);
};

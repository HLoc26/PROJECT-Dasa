#include "Menu.h"
#include <iostream>

void Menu::PrintMenu(EMenu type, int option) {
    cout << "OPTION: " << option % 4 << endl;
    string options[4];
    if (type == EMenu::Main) {
        string temp[] = {"Student Login",
                         "Student Register",
                         "Teacher Login",
                         "Exit"};
        copy(begin(temp), end(temp), begin(options));
    }
    else if (type == EMenu::Teacher) {
        string temp[] = {"See Students' Scores",
                         "Add Questions",
                         "Change Password",
                         "Return"};
        copy(begin(temp), end(temp), begin(options));
    }
    else if (type == EMenu::Student) {
        string temp[] = {"Start Test",
                         "See Scores",
                         "Change Password",
                         "Return"};
        copy(begin(temp), end(temp), begin(options));
    }
    else if (type == EMenu::Subject) {
        string temp[] = {"Toan",
                         "Ly",
                         "Hoa",
                         "Return"};
        copy(begin(temp), end(temp), begin(options));
    }
    for (int i = 0; i < 4; i++) {
        if (i == option % 4) {
            cout << "\x1B[34m\t> " << options[i] << " <\033[0m\n";
        }
        else {
            cout << "\t" << options[i] << "\n";
        }
    }
}

void Menu::PrintMenu(string monhoc, int option) {
    cout << "OPTION: " << option % 4 << endl;
    string options[4];
    if (monhoc == "Toan") {
        string temp[] = {"Chapter 1: Decimal Number",
                         "Chapter 2: Toan2",
                         "Chapter 3: Toan3",
                         "Return"};
        copy(begin(temp), end(temp), begin(options));
    }
    else if (monhoc == "Ly") {
        string temp[] = {"Chapter 1: Ly1",
                         "Chapter 2: Ly2",
                         "Chapter 3: Ly3",
                         "Return"};
        copy(begin(temp), end(temp), begin(options));
    }
    else if (monhoc == "Hoa") {
        string temp[] = {"Chapter 1: Oxygen",
                         "Chapter 2: Hoa2",
                         "Chapter 3: Hoa3",
                         "Return"};
        copy(begin(temp), end(temp), begin(options));
    }
    for (int i = 0; i < 4; i++) {
        if (i == option % 4) {
            cout << "\x1B[34m\t> " << options[i] << " <\033[0m\n";
        }
        else {
            cout << "\t" << options[i] << "\n";
        }
    }
}
#include "CauHoi.h"
#include "DLList.h"
#include "DS.h"
#include <conio.h>
#include <iomanip>
#include <iostream>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13

using namespace std;

enum Options {
    Option1 = 0,
    Option2 = 1,
    Option3 = 2,
    Option4 = 3
};

/*
    - Cac ham Print... la de in cac options
    - Cac ham Menu la de chay logic chon option
 */

// PROTOTYPE
void StartMenu();
void PrintStartMenu(int option);

void StudentMenu(string username);
void PrintStudentMenu(int option);
void SelectSubject(string username);
void PrintSelectSubject(int option);
void SelectChapter(string username, string monhoc);
void PrintSelectChapter(string monhoc, int option);
void XemDiem();

void StartTest(string monhoc, int chapter);
void Test(DLList Question);

void StartMenu() {
    int option = 20000;
    while (true) {
        system("cls");
        cout << "===== TEST SIMULATOR =====\n";
        PrintStartMenu(option);
        int ex = getch();

        if (ex == KEY_ENTER) {
            switch (option % 4) {
            case Option1:
                cout << "\nSTUDENT LOGIN\n";
                StudentMenu("hloc"); // Thay bằng hàm Log in
                break;
            case Option2:
                cout << "\nSTUDENT SIGNUP\n";
                break;
            case Option3:
                cout << "\nTEACHER LOGIN\n";
                break;
            case Option4:
                system("cls");
                cout << "Do you want to exit? (Y/N): ";
                char o;
                cin >> o;
                if (tolower(o) == 'y') {
                    exit(0);
                }
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
        else if (ex == 27) {
            system("cls");
            cout << "Do you want to exit? (Y/N): ";
            char o;
            cin >> o;
            if (tolower(o) == 'y') {
                exit(0);
            }
        }
    }
}
// Man hinh menu luc moi vao chuong trinh
void PrintStartMenu(int option) {
    cout << "OPTION: " << option % 4 << endl;
    const char *options[] = {"Student Login", "Student Signup", "Teacher Login", "Exit"};
    for (int i = 0; i < 4; i++) {
        if (i == option % 4) {
            cout << "\x1B[34m\t> " << options[i] << " <\033[0m\n";
        }
        else {
            cout << "\t" << options[i] << "\n";
        }
    }
}
// Sau khi HS da dang nhap
void StudentMenu(string username) {
    int option = 20000;
    while (true) {
        system("cls");
        cout << "Hello, " << username << endl;
        cout << "===============================\n";
        PrintStudentMenu(option);
        int ex = getch();

        if (ex == KEY_ENTER) {
            switch (option % 4) {
            case Option1:
                cout << "\nSelect test\n";
                SelectSubject(username);
                break;
            case Option2:
                cout << "\nCheck result\n";
                XemDiem();
                break;
            case Option3:
                cout << "\nChange Password\n";
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
        else if (ex == 27) {
            system("cls");
            cout << "Do you want to exit? (Y/N): ";
            char o;
            cin >> o;
            if (tolower(o) == 'y') {
                exit(0);
            }
        }
    }
}
// Man hinh HS
void PrintStudentMenu(int option) {
    cout << "OPTION: " << option % 4 << endl;
    const char *options[] = {"Start Test", "See Results", "Change Password", "Log Out"};
    for (int i = 0; i < 4; i++) {
        if (i == option % 4) {
            cout << "\x1B[34m\t> " << options[i] << " <\033[0m\n";
        }
        else {
            cout << "\t" << options[i] << "\n";
        }
    }
}

void SelectSubject(string username) {
    int option = 20000;
    while (true) {
        system("cls");
        cout << "Hello, " << username << endl;
        cout << "===============================\n";
        cout << "=========SELECT SUBJECT========\n";
        PrintSelectSubject(option);
        int ex = getch();

        if (ex == KEY_ENTER) {
            switch (option % 4) {
            case Option1:
                cout << "\nToan\n";
                SelectChapter(username, "Toan");
                break;
            case Option2:
                cout << "\nLy\n";
                SelectChapter(username, "Ly");
                break;
            case Option3:
                cout << "\nHoa\n";
                SelectChapter(username, "Hoa");
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
        else if (ex == 27) {
            system("cls");
            cout << "Do you want to exit? (Y/N): ";
            char o;
            cin >> o;
            if (tolower(o) == 'y') {
                exit(0);
            }
        }
    }
}

void PrintSelectSubject(int option) {
    cout << "OPTION: " << option % 4 << endl;
    const char *options[] = {"Toan", "Ly", "Hoa", "Return"};
    for (int i = 0; i < 4; i++) {
        if (i == option % 4) {
            cout << "\x1B[34m\t> " << options[i] << " <\033[0m\n";
        }
        else {
            cout << "\t" << options[i] << "\n";
        }
    }
}

// Man hinh chon Chapter
void SelectChapter(string username, string monhoc) {
    int option = 20000;
    while (true) {
        system("cls");
        cout << "Hello, " << username << endl;
        cout << "===============================\n";
        cout << "=========SELECT CHAPTER========\n";
        PrintSelectChapter(monhoc, option);
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
        else if (ex == 27) {
            system("cls");
            cout << "Do you want to exit? (Y/N): ";
            char o;
            cin >> o;
            if (tolower(o) == 'y') {
                exit(0);
            }
        }
    }
}

void PrintSelectChapter(string monhoc, int option) {
    cout << "OPTION: " << option % 4 << endl;
    std::string options[4];
    if (monhoc == "Toan") {
        std::string temp[] = {"Chapter 1: Decimal Number",
                              "Chapter 2: Toan2",
                              "Chapter 3: Toan3",
                              "Return"};
        std::copy(std::begin(temp), std::end(temp), std::begin(options));
    }
    else if (monhoc == "Ly") {
        std::string temp[] = {"Chapter 1: Ly1",
                              "Chapter 2: Ly2",
                              "Chapter 3: Ly3",
                              "Return"};
        std::copy(std::begin(temp), std::end(temp), std::begin(options));
    }
    else if (monhoc == "Hoa") {
        std::string temp[] = {"Chapter 1: Oxygen",
                              "Chapter 2: Hoa2",
                              "Chapter 3: Hoa3",
                              "Return"};
        std::copy(std::begin(temp), std::end(temp), std::begin(options));
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

void StartTest(string monhoc, int chapter) {
    DanhSach DSCH;
    srand(time(NULL));
    DSCH.DocFile(monhoc, 1);
    DLList Question = DSCH.GetQuestions();
    Question.PrintList();
    system("cls");
    Test(Question);
}

// User Hoc sinh xem diem cua minh
void XemDiem() {}

// Bat dau lam bai test
void Test(DLList Question) {
    CauHoi *chHienTai = Question.head;

    int ans_pos = 0;
    string *ans = new string[Question.size]{""};
    int choices = 20000;

    while (true) {
        system("cls");
        cout << "Press ESC to exit\n";
        cout << ans_pos + 1 << ". ";

        chHienTai->InCauHoi(abs(choices));
        cout << setw(15) << left << "Prev (<-)" << setw(18) << "Choose (^ v)" << setw(10) << "Next (->)\n";

        if (ans[ans_pos] != "") {
            cout << "\tYour prev choice: " << ans[ans_pos] << endl;
        }
        cout << "\tPress Enter to choose question\n";
        int ex = getch();

        if (ex == KEY_ENTER) {
            string answer = "";
            switch (choices % 4) {
            case Option1:
                answer = "A";
                break;
            case Option2:
                answer = "B";
                break;
            case Option3:
                answer = "C";
                break;
            case Option4:
                answer = "D";
                break;
            default:
                break;
            }
            ans[ans_pos] = answer;
        }
        else if (ex == KEY_UP) {
            choices -= 1;
        }
        else if (ex == KEY_DOWN) {
            choices += 1;
        }
        else if (ex == KEY_LEFT) {
            choices = 20000;

            if (chHienTai->prev == NULL) {
                chHienTai = Question.tail;
                ans_pos = Question.size - 1;
            }
            else {
                chHienTai = chHienTai->prev;
                ans_pos -= 1;
            }
            if (ans[ans_pos] != "") {
                choices += (ans[ans_pos][0] % 4 - 1);
            }
        }
        else if (ex == KEY_RIGHT) {
            choices = 20000;

            if (chHienTai->next == NULL) {
                chHienTai = Question.head;
                ans_pos = 0;
            }
            else {
                chHienTai = chHienTai->next;
                ans_pos += 1;
            }
            if (ans[ans_pos] != "") {
                choices += (ans[ans_pos][0] % 4 - 1);
            }
        }
        else if (ex == 27) {
            cout << "Do you want to exit? (Y/N): ";
            char o;
            cin >> o;
            if (tolower(o) == 'y') {
                exit(0);
            }
        }
    }
}
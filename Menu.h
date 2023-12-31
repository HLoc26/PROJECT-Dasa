#include "CauHoi.h"
#include "DLList.h"
#include "DS.h"

#include <chrono>
#include <conio.h>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string.h>
#include <thread>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_BACKSPACE 8
#define KEY_ESC 27

#define COLOR_RED "\x1B[31m"
#define COLOR_BLUE "\x1B[36m"
#define COLOR_GREEN "\x1B[32m"
#define COLOR_END "\033[0m"

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
    MainM,
    TeacherM,
    StudentM,
    SubjectM
};

struct StudentScore {
    string subject;
    int chapter;
    float score;
    StudentScore(string subject, int chapter, float score) {
        this->subject = subject;
        this->chapter = chapter;
        this->score = score;
    }
};

/*
    - Cac ham Print... la de in cac options
    - Cac ham Menu la de chay logic chon option
 */

/*
    StartMenu
    StudentMenu
    TeacherMenu
    SelectSubject
    PrintMenu
    SelectChapter
    PrintMenu (Chapter)

    StartTest
    Test

    Login
    LogInAnimate
    CheckValidLogin

    Register
 */

struct Menu {

    string username = "";
    string password = "";
    // Số lượng phần tử trong mảng lưu highscore trong hàm PrintHighScore
    int CHAP_COUNT = 8;

    void StartMenu() {
        int option = 20000;
        while (true) {
            system("cls");
            cout << "===== TEST SIMULATOR =====\n";
            PrintMenu(EMenu::MainM, option);
            int ex = _getch();

            if (ex == KEY_ENTER) {
                switch (option % 4) {
                    // Studen Login
                case Option1:
                    cout << "\nSTUDENT LOGIN\n";
                    Login(ERole::Student);
                    break;
                    // Student Signup
                case Option2:
                    Register();
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
            PrintMenu(EMenu::StudentM, option);
            int ex = _getch();

            if (ex == KEY_ENTER) {
                switch (option % 4) {
                case Option1:
                    cout << "\nSelect test\n";
                    SelectSubject();
                    break;
                case Option2:
                    system("cls");
                    PrintHighestScores(username);
                    break;
                case Option3:
                    ChangePass(ERole::Student);
                    break;
                case Option4:
                    cout << "Do you want to log out? (Y/N): ";
                    char o;
                    cin >> o;
                    if (tolower(o) == 'y') {
                        username.clear();
                        password.clear();
                        StartMenu();
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
            PrintMenu(EMenu::TeacherM, option);
            int ex = _getch();

            if (ex == KEY_ENTER) {
                switch (option % 4) {
                case Option1:
                    PrintStudentsScore();
                    break;
                case Option2:
                    cout << "\nAdd chapter\n";
                    AddChapter();

                    break;
                case Option3:
                    ChangePass(ERole::Teacher);
                    break;
                case Option4:
                    cout << "Do you want to log out? (Y/N): ";
                    char o;
                    cin >> o;
                    if (tolower(o) == 'y') {
                        username.clear();
                        password.clear();
                        StartMenu();
                    }
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
        string subjectList[100];
        int size = ReadSubDir(subjectList, BANK_PATH);
        int option = 1000 * size;
        while (true) {
            system("cls");
            cout << "Hello, " << username << endl;
            cout << "===============================\n";
            cout << "=========SELECT SUBJECT========\n";
            PrintMenu(EMenu::SubjectM, option);
            int ex = _getch();

            if (ex == KEY_ENTER) {
                SelectChapter(subjectList[option % size]);
            }
            else if (ex == KEY_UP) {
                option -= 1;
            }
            else if (ex == KEY_DOWN) {
                option += 1;
            }
            else if (ex == KEY_ESC) {
                system("cls");
                StudentMenu();
            }
        }
    }

    int ReadSubDir(string temp[100], string path) {

        int count = 0;
        try {
            for (const auto &entry : filesystem::directory_iterator(path)) {
                if (filesystem::is_directory(entry.path()) && count < 100) {
                    temp[count] = entry.path().filename().string();
                    count++;
                }
            }
        } catch (const filesystem::filesystem_error &ex) {
            cerr << "Error accessing the directory: " << ex.what() << endl;
            return -1;
        }
        return count;
    }

    void PrintMenu(EMenu type, int option) {
        string options[100];
        int size;
        if (type == EMenu::MainM) {
            string temp[] = {"Student Login",
                             "Student Register",
                             "Teacher Login",
                             "Exit"};
            size = 4;
            copy(begin(temp), end(temp), begin(options));
        }
        else if (type == EMenu::TeacherM) {
            string temp[] = {"See Students' Scores",
                             "Add Questions",
                             "Change Password",
                             "Log out"};
            size = 4;
            copy(begin(temp), end(temp), begin(options));
        }
        else if (type == EMenu::StudentM) {
            string temp[] = {"Practice Test",
                             "See Scores",
                             "Change Password",
                             "Log out"};
            size = 4;
            copy(begin(temp), end(temp), begin(options));
        }
        else if (type == EMenu::SubjectM) {

            string temp[100];
            size = ReadSubDir(temp, BANK_PATH);
            copy(begin(temp), end(temp), begin(options));
        }
        for (int i = 0; i < size; i++) {
            if (i == option % size) {
                cout << COLOR_BLUE << "\t> " << options[i] << " <" << COLOR_END << "\n";
            }
            else {
                cout << "\t" << options[i] << "\n";
            }
        }
    }
    // Man hinh chon Chapter
    void SelectChapter(string monhoc) {
        string chapList[100];

        int count = ReadSubDir(chapList, BANK_PATH + "/" + monhoc);

        cout << "Chap1: " << chapList[0] << endl;

        int option = count * 1000;
        while (true) {
            system("cls");
            cout << "Hello, " << username << endl;
            cout << "===============================\n";
            cout << "=========SELECT CHAPTER========\n";
            PrintMenu(monhoc, chapList, count, option);
            int ex = _getch();

            if (ex == KEY_ENTER) {
                cout << "SUBJECT: " << monhoc << "\tCHAPTER " << option % count + 1;
                StartTest(monhoc, option % count);
            }
            else if (ex == KEY_UP) {
                option -= 1;
            }
            else if (ex == KEY_DOWN) {
                option += 1;
            }
            else if (ex == KEY_ESC) {
                system("cls");
                SelectSubject();
            }
        }
    }
    void PrintMenu(string monhoc, string chapList[], int listSize, int option) {

        cout << endl
             << monhoc << endl;

        for (int i = 0; i < listSize; i++) {
            if (i == option % listSize) {
                cout << COLOR_BLUE << "\t> " << chapList[i] << " <" << COLOR_END << "\n";
            }
            else {
                cout << "\t" << chapList[i] << "\n";
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

    // Login
    void Login(ERole role) {
        string passInp;
        string userInp;
        string title = "";
        if (role == ERole::Teacher) {
            title = "TEACHER";
        }
        else {
            title = "STUDENT";
        }
        while (true) {
            system("cls");
            cout << "=========" << title << " LOGIN========\n";
            cout << "==============================\n";
            int ch;
            // Bắt đầu nhập username
            cout << "Username: ";
            while ((ch = _getch()) != KEY_ENTER) {
                // Kiểm tra xem có nhấn ESC trong lúc nhập không
                if (ch == KEY_ESC) {
                    // Nếu có thì quay về main menu
                    system("cls");
                    cout << "Return to main menu? (Y/N): ";
                    char o;
                    cin >> o;
                    if (tolower(o) == 'y') {
                        return;
                    }
                    continue;
                }
                // Nhập sai thì phải xóa
                if (ch == KEY_BACKSPACE) {
                    if (userInp.length() > 0) {
                        cout << "\b \b";
                        userInp.pop_back();
                        continue;
                    }
                    else {
                        continue;
                    }
                }
                // Thêm ký tự vừa nhập vào
                userInp += ch;
                // In ký tự vừa nhập ra
                cout << userInp[userInp.length() - 1];
            }
            cout << endl;
            // Bắt đầu nhập password
            cout << "Password: ";
            while ((ch = _getch()) != KEY_ENTER) {
                if (ch == KEY_ESC) {
                    system("cls");
                    cout << "Return to main menu? (Y/N): ";
                    char o;
                    cin >> o;
                    if (tolower(o) == 'y') {
                        return;
                    }
                    continue;
                }
                if (ch == KEY_BACKSPACE) {
                    if (passInp.length() > 0) {
                        cout << "\b \b";
                        passInp.pop_back();
                        continue;
                    }
                    else {
                        continue;
                    }
                }
                passInp += ch;
                // In ra dấu * thay vì ký tự
                cout << "*";
            }
            // Kiểm tra tài khoản mật khẩu đúng kkhông
            if (!CheckValidLogin(userInp, passInp, role)) {
                cout << "\n"
                     << COLOR_RED
                     << "Wrong password or username!"
                     << COLOR_END << "\n\n";
                passInp = "";
                userInp = "";
                _getch();
            }
            else {
                username = userInp;
                password = passInp;
                cout << endl
                     << COLOR_GREEN
                     << "Succeed!"
                     << COLOR_END << "\n";
                cout << "Press any button to continue!\n";
                _getch();
                system("cls");

                // In ra để test, sau này thêm menu teacher rồi đổi
                // ==============================================//
                // cout << username << endl
                //      << password;
                // _getch();
                // exit(0);
                // ==============================================//
                if (role == ERole::Teacher) {
                    TeacherMenu();
                }
                else {
                    StudentMenu();
                }
            }
        }
    }
    // Kiểm tra xem TK và MK có hợp lệ không
    bool CheckValidLogin(string userInp, string passInp, ERole role) {
        string folder = "";
        // Mở file với tên <username>
        if (role == ERole::Teacher) {
            folder = "Teacher";
        }
        else {
            folder = "Student";
        }
        ifstream user(FILE_PATH + "User/" + folder + "/" + userInp + ".txt", ios::in);

        // Nếu mở thành công == có tài khoản tên username
        if (!user.fail()) {
            string filePass;
            getline(user, filePass);

            // Check pass, sai thì trả về false
            if (filePass != passInp) {
                user.close();
                return false;
            }
            else {
                user.close();
                return true;
            }
        }
        // Không có tk thì trả về false
        else {
            user.close();
            return false;
        }
    }
    void StartTest(string monhoc, int chapter) {

        DanhSach DSCH;
        srand(time(NULL));

        DSCH.DocFile(monhoc, chapter);
        DLList Question = DSCH.GetQuestions();
        // Question.PrintList();

        system("cls");
        Test(Question, monhoc, chapter);
    }

    // Bat dau lam bai test
    void Test(DLList Question, string subject, int chapter) {
        CauHoi *chHienTai = Question.head;
        int ans_pos = 0;
        string *ans = new string[Question.size]{""};
        int choices = 20000;
        double totalScore = 0;
        int correctAnswers = 0;

        bool *answeredCorrectly = new bool[Question.size]{false};

        while (true) {
            system("cls");
            cout << "Press ESC to submit the test.\n";
            cout << ans_pos + 1 << ". ";

            chHienTai->InCauHoi(abs(choices));
            cout << setw(15) << left << "Prev (<-)" << setw(18) << "Choose (^ v)" << setw(10) << "Next (->)\n";
            cout << correctAnswers << endl;
            if (ans[ans_pos] != "") {
                cout << "\tYour prev choice: " << ans[ans_pos] << endl;
            }
            cout << "\tPress Enter to choose question\n";
            int ex = _getch();

            if (ex == KEY_ENTER) {
                string answer = "";
                switch (choices % 4) {
                case 0:
                    answer = "A";
                    break;
                case 1:
                    answer = "B";
                    break;
                case 2:
                    answer = "C";
                    break;
                case 3:
                    answer = "D";
                    break;
                default:
                    break;
                }
                if (chHienTai->IsCorrectAnswer(answer)) {
                    if (!answeredCorrectly[ans_pos]) {
                        correctAnswers += 1;
                        answeredCorrectly[ans_pos] = true;
                    }
                }
                else {
                    if (answeredCorrectly[ans_pos]) {
                        correctAnswers -= 1;
                    }
                    answeredCorrectly[ans_pos] = false;
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
                cout << "Do you want to end the test? (Y/N): ";
                char o;
                cin >> o;
                if (tolower(o) == 'y') {
                    totalScore = static_cast<double>(10) / Question.size * correctAnswers;
                    cout << "Your final score: " << totalScore << endl;
                    StudentScore ss = StudentScore(subject, chapter, totalScore);
                    StoreScores(ss);
                    if (ex == KEY_ESC) {
                        system("cls");
                        cout << "Return to main menu? (Y/N): ";
                        char o;
                        cin >> o;
                        if (tolower(o) == 'y') {
                            return;
                        }
                        else if (tolower(o) == 'n') {
                            exit(0);
                        }
                    }
                }
            }
        }
    }

    void Register() {
        string userInp;
        string passInp;
        string passInp2;

        // Bắt đầu nhập username
        bool isValidUser = true;
        do {
            userInp.clear();
            system("cls");
            cout << "====== STUDENT REGISTER ======\n";
            cout << "==============================\n";
            int ch;
            if (!isValidUser) {
                cout << "\x1B[31m"
                     << "Username is used!"
                     << COLOR_END << "\n";
            }
            cout << "Username: ";
            while ((ch = _getch()) != KEY_ENTER) {
                // Kiểm tra xem có nhấn ESC trong lúc nhập không
                if (ch == KEY_ESC) {
                    // Nếu có thì quay về main menu
                    system("cls");
                    cout << "Return to main menu? (Y/N): ";
                    char o;
                    cin >> o;
                    if (tolower(o) == 'y') {
                        return;
                    }
                    continue;
                }
                // Nhập sai thì phải xóa
                if (ch == KEY_BACKSPACE) {
                    if (userInp.length() > 0) {
                        cout << "\b \b";
                        userInp.pop_back();
                        continue;
                    }
                    else {
                        continue;
                    }
                }
                // Thêm ký tự vừa nhập vào
                userInp += ch;
                // In ký tự vừa nhập ra
                cout << userInp[userInp.length() - 1];
            }
            isValidUser = CheckValidUsername(userInp);
        } while (!isValidUser);

        // Password
        bool isValidPass = true;
        do {
            passInp.clear();
            system("cls");
            cout << "====== STUDENT REGISTER ======\n";
            cout << "==============================\n";
            int ch;
            cout << "Username: " << userInp << endl;
            // Bắt đầu nhập password
            if (!isValidPass) {
                cout << COLOR_RED << "Password must contain:" << COLOR_END << "\n";
                cout << COLOR_RED << "               - More than 8 character" << COLOR_END << "\n";
                cout << COLOR_RED << "               - Contains at least 1 digit" << COLOR_END << "\n";
                cout << COLOR_RED << "               - Contains at least 1 alphabetic character" << COLOR_END << "\n";
            }
            else {
                cout << "Password must contain: \n";
                cout << "               - More than 8 character\n";
                cout << "               - Contains at least 1 digit\n";
                cout << "               - Contains at least 1 alphabetic character\n";
            }
            cout << "Password: ";
            while ((ch = _getch()) != KEY_ENTER) {
                if (ch == KEY_ESC) {
                    system("cls");
                    cout << "Return to main menu? (Y/N): ";
                    char o;
                    cin >> o;
                    if (tolower(o) == 'y') {
                        return;
                    }
                    continue;
                }
                if (ch == KEY_BACKSPACE) {
                    if (passInp.length() > 0) {
                        cout << "\b \b";
                        passInp.pop_back();
                        continue;
                    }
                    else {
                        continue;
                    }
                }
                passInp += ch;
                // In ra dấu * thay vì ký tự
                cout << "*";
            }
            isValidPass = CheckValidPass(passInp);
        } while (!isValidPass);

        // Nhập lại pass
        bool isValidPass2 = true;
        do {

            passInp2.clear();
            system("cls");

            cout << "====== STUDENT REGISTER ======\n";
            cout << "==============================\n";
            int ch;
            cout << "Username: " << userInp << endl;
            // Bắt đầu nhập password
            cout << "Password must contain: \n";
            cout << "               - More than 8 character\n";
            cout << "               - Contains at least 1 digit\n";
            cout << "               - Contains at least 1 alphabetic character\n";
            cout << "Password: " << string(passInp.length(), '*') << endl;
            if (!isValidPass2) {
                cout << COLOR_RED
                     << "Password doesn't match!"
                     << COLOR_END << "\n";
            }

            cout << "Retype password: ";
            while ((ch = _getch()) != KEY_ENTER) {
                if (ch == KEY_ESC) {
                    system("cls");
                    cout << "Return to main menu? (Y/N): ";
                    char o;
                    cin >> o;
                    if (tolower(o) == 'y') {
                        return;
                    }
                    continue;
                }
                if (ch == KEY_BACKSPACE) {
                    if (passInp2.length() > 0) {
                        cout << "\b \b";
                        passInp2.pop_back();
                        continue;
                    }
                    else {
                        continue;
                    }
                }
                passInp2 += ch;
                // In ra dấu * thay vì ký tự
                cout << "*";
            }
            isValidPass2 = (passInp2 == passInp);
        } while (!isValidPass2);

        /*
        cout << userInp << endl
             << passInp << endl;
        _getch();
        */
        // Create the folder
        filesystem::create_directory(FILE_PATH + "User/Student/" + userInp);
        ofstream user(FILE_PATH + "User/Student/" + userInp + ".txt", ios::out);
        user << passInp;
        cout << COLOR_GREEN << "Successfully registered!" << COLOR_END << "\n";
        cout << "Press any button to return\n";
        user.close();

        ofstream teacher(FILE_PATH + "User/Teacher/StudentList.txt", ios::out);
        teacher << userInp << endl;
        teacher.close();
        _getch();

        return;
    }

    // Trả về true nếu tên user không tồn tại = mở file fail
    bool CheckValidUsername(string userInp) {
        if (!filesystem::exists(userInp)) {
            return true;
        }
        return false;
    }
    // Trả về true nếu password dài hơn 8 ký tự, có chứa cả chữ và số
    bool CheckValidPass(string passInp) {
        if (passInp.length() < 8) {
            return false;
        }
        bool haveDigit = false, haveAlpha = false;

        for (int i = 0; i < passInp.length(); i++) {
            if (isdigit(passInp[i])) {
                haveDigit = true;
            }
            if (isalpha(passInp[i])) {
                haveAlpha = true;
            }
        }
        return (haveDigit && haveAlpha);
    }

    void ChangePass(ERole role) {
        string oldPass;
        string newPass;
        string newPass2;

        bool isValidOld = true;
        do {

            oldPass.clear();
            system("cls");

            cout << "====== CHANGE PASSWORD  ======\n";
            cout << "==============================\n";
            int ch;
            cout << "Username: " << username << endl;
            if (!isValidOld) {
                cout << COLOR_RED
                     << "Password doesn't match!"
                     << COLOR_END << "\n";
            };
            cout << "Old password: ";
            while ((ch = _getch()) != KEY_ENTER) {
                if (ch == KEY_ESC) {
                    system("cls");
                    cout << "Return to main menu? (Y/N): ";
                    char o;
                    cin >> o;
                    if (tolower(o) == 'y') {
                        return;
                    }
                    continue;
                }
                if (ch == KEY_BACKSPACE) {
                    if (oldPass.length() > 0) {
                        cout << "\b \b";
                        oldPass.pop_back();
                        continue;
                    }
                    else {
                        continue;
                    }
                }
                oldPass += ch;
                // In ra dấu * thay vì ký tự
                cout << "*";
            }
            isValidOld = (oldPass == password);
        } while (!isValidOld);

        // New password
        bool isValidPass = true;
        do {
            newPass.clear();
            system("cls");
            cout << "====== CHANGE PASSWORD  ======\n";
            cout << "==============================\n";
            int ch;
            cout << "Username: " << username << endl;
            cout << "Old password: " << string(oldPass.length(), '*') << endl;

            // Bắt đầu nhập password
            if (!isValidPass) {
                cout << COLOR_RED << "Password must contain:" << COLOR_END << "\n";
                cout << COLOR_RED << "               - More than 8 character" << COLOR_END << "\n";
                cout << COLOR_RED << "               - Contains at least 1 digit" << COLOR_END << "\n";
                cout << COLOR_RED << "               - Contains at least 1 alphabetic character" << COLOR_END << "\n";
            }
            else {
                cout << "Password must contain: \n";
                cout << "               - More than 8 character\n";
                cout << "               - Contains at least 1 digit\n";
                cout << "               - Contains at least 1 alphabetic charater\n";
            }
            cout << "New password: ";
            while ((ch = _getch()) != KEY_ENTER) {
                if (ch == KEY_ESC) {
                    system("cls");
                    cout << "Return to main menu? (Y/N): ";
                    char o;
                    cin >> o;
                    if (tolower(o) == 'y') {
                        return;
                    }
                    continue;
                }
                if (ch == KEY_BACKSPACE) {
                    if (newPass.length() > 0) {
                        cout << "\b \b";
                        newPass.pop_back();
                        continue;
                    }
                    else {
                        continue;
                    }
                }
                newPass += ch;
                // In ra dấu * thay vì ký tự
                cout << "*";
            }
            isValidPass = CheckValidPass(newPass);
        } while (!isValidPass);

        bool isValidPass2 = true;
        do {
            newPass2.clear();
            system("cls");

            cout << "====== CHANGE PASSWORD  ======\n";
            cout << "==============================\n";
            int ch;
            cout << "Username: " << username << endl;
            // Bắt đầu nhập password
            cout << "Old password: " << string(oldPass.length(), '*') << endl;
            cout << "New password: " << string(newPass.length(), '*') << endl;

            if (!isValidPass2) {
                cout << COLOR_RED
                     << "Password doesn't match!"
                     << COLOR_END << "\n";
            }

            cout << "Retype password: ";
            while ((ch = _getch()) != KEY_ENTER) {
                if (ch == KEY_ESC) {
                    system("cls");
                    cout << "Return to main menu? (Y/N): ";
                    char o;
                    cin >> o;
                    if (tolower(o) == 'y') {
                        return;
                    }
                    continue;
                }
                if (ch == KEY_BACKSPACE) {
                    if (newPass2.length() > 0) {
                        cout << "\b \b";
                        newPass2.pop_back();
                        continue;
                    }
                    else {
                        continue;
                    }
                }
                newPass2 += ch;
                // In ra dấu * thay vì ký tự
                cout << "*";
            }
            isValidPass2 = (newPass2 == newPass);
        } while (!isValidPass2);

        password = newPass2;
        string path;
        if (role == ERole::Student) {
            path = FILE_PATH + "User/Student/" + username + "txt";
        }
        else {
            path = FILE_PATH + "User/Teacher/" + username + "txt";
        }
        ofstream user(path, ios::out);
        user.clear();
        user << password;
        user.close();
    }

    void StoreScores(const StudentScore &studentScore) {
        string filePath = FILE_PATH + "User/Student/" + username + ".txt";
        ofstream outFile(filePath, ios::app);

        if (outFile.is_open()) {
            // Lấy ngày giờ hiện tại
            auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
            tm localTime{};
            localtime_s(&localTime, &now);
            outFile << endl;
            outFile << put_time(&localTime, "%Y-%m-%d %H:%M:%S") << endl;
            outFile << setw(15) << left << "Subject" << setw(15) << "Chapter" << setw(10) << "Score" << endl;
            outFile << setw(15) << left << studentScore.subject << setw(15) << studentScore.chapter << setw(10) << studentScore.score;

            outFile.close();
        }
        else {
            cerr << "Error opening file: " << filePath << endl;
        }
    }

    void PrintHighestScores(string uName, bool FromTeacher = false) {
        string filePath = FILE_PATH + "User/Student/" + uName + ".txt";
        cout << filePath << endl;
        ifstream inFile(filePath);
        if (inFile.is_open()) {
            string highScoreSubj[CHAP_COUNT];
            int highScoreChap[CHAP_COUNT];
            double highScore[CHAP_COUNT];
            memset(highScore, 0, sizeof(highScore));

            string line;
            getline(inFile, line); // skip dòng password
            int HIndex = 0;
            while (getline(inFile, line)) {
                if (!line.empty()) {
                    getline(inFile, line);
                    // skip dòng có các cột subject, subject, .....
                    getline(inFile, line);
                    istringstream iss(line);
                    string subject;
                    int chapter;
                    double score;
                    iss >> subject >> chapter >> score;
                    if (HIndex == 0) {
                        highScoreSubj[HIndex] = subject;
                        highScoreChap[HIndex] = chapter;
                        highScore[HIndex] = score;
                        HIndex += 1;
                    }

                    else if (HIndex > 0) {
                        if (highScoreSubj[HIndex - 1] != subject || highScoreChap[HIndex - 1] != chapter) {
                            highScoreSubj[HIndex] = subject;
                            highScoreChap[HIndex] = chapter;
                            highScore[HIndex] = score;
                            HIndex += 1;
                        }
                        else {
                            highScore[HIndex] = max(highScore[HIndex], score);
                        }
                    }
                }
            }
            cout << uName << "'s high score" << endl;
            cout << "================================\n";
            if (HIndex == 0) {
                cout << "This student has not taken any test yet\n\n";
            }
            else {
                // Print the highest scores for each subject and chapter
                cout << setw(12) << left << "Subject"
                     << setw(10) << left << "Chapter"
                     << setw(10) << left << "High Score" << endl;

                for (int i = 0; i < HIndex; i++) {
                    cout << setw(12) << left << highScoreSubj[i] << setw(10) << left << highScoreChap[i] << setw(10) << left << highScore[i] << endl;
                }

                cout << CalculateGPA(uName) << endl;
                cout << "================================\n\n";
            }
            inFile.close();
        }
        else {
            cerr << "Error opening file: " << filePath << endl;
        }
        if (!FromTeacher) {
            cout << "Press any button to go back\n";
            _getch();
        }
    }

    void PrintStudentsScore() {
        system("cls");
        cout << "STUDENT'S HIGHSCORE" << endl;
        cout << "================================\n";
        ifstream list(FILE_PATH + "User/Teacher/StudentList.txt", ios::app);

        string *SList = new string[1000];
        string uName;
        int size = 0;
        while (list >> uName) {
            SList[size] = uName;
            size += 1;
        }
        list.close();

        cout << "\nSORT:\n\t1. Ascending by Username\n\t2. Ascending by GPA\n\n";

        for (int i = 0; i < size; i++) {
            string name = SList[i];
            PrintHighestScores(name, true);
        }

        cout << "Press ENTER to go back\n";

        int ex = _getch();
        switch (ex) {
        case 49:
            QuickSortName(SList, 0, size - 1);
            PrintSortedScore(SList, size);
            break;
        case 50:
            SortStudentScore(SList, size);
            break;
        case 13:
            TeacherMenu();
        default:
            break;
        }
    }

    void PrintSortedScore(string SList[], int size) {
        system("cls");
        cout << "STUDENT'S HIGHSCORE" << endl;
        cout << "================================\n";
        cout << "\nSORT:\n\t1. Ascending by Username\n\t2. Ascending by GPA\n\n";

        for (int i = 0; i < size; i++) {
            string name = SList[i];
            PrintHighestScores(name, true);
        }
        cout << "Press ENTER to go back\n";
        int ex = _getch();
        switch (ex) {
        case 49:
            QuickSortName(SList, 0, size - 1);
            PrintSortedScore(SList, size);
            break;
        case 50:
            SortStudentScore(SList, size);
            break;
        case 13:
            PrintStudentsScore();
        default:
            break;
        }
    }

    void QuickSortName(string name[], int left, int right) {
        int i, j;
        string x;
        x = name[(left + right) / 2];
        i = left;
        j = right;
        do {
            while (name[i] < x)
                i++;
            while (name[j] > x)
                j--;
            if (i <= j) {
                swap(name[i], name[j]);
                i++;
                j--;
            }
        } while (i < j);
        if (left < j) QuickSortName(name, left, j);
        if (i < right) QuickSortName(name, i, right);
    }
    void SortStudentScore(string SList[], int size) {

        int StudentCount = size;
        // Tạo một ma trận có cấu trúc:
        /* {[TenHS1, Diem],
            [TenHS2, Diem],
            ...
            }*/
        string **Student_GPA = new string *[StudentCount];

        for (int i = 0; i < StudentCount; i++) {
            Student_GPA[i] = new string[2];
        }
        for (int i = 0; i < StudentCount; i++) {
            Student_GPA[i][0] = SList[i];
            string uName = Student_GPA[i][0];
            Student_GPA[i][1] = CalculateGPA(uName);
        }

        QuickSortGPA(Student_GPA, 0, StudentCount - 1);
        system("cls");
        cout << "STUDENT'S HIGHSCORE" << endl;
        cout << "================================\n";
        cout << "\nSORT:\n\t1. Ascending by Username\n\t2. Ascending by GPA\n\n";

        for (int i = 0; i < StudentCount; i++) {
            PrintHighestScores(Student_GPA[i][0], true);
        }

        cout << "Press ENTER to go back\n";
        int ex = _getch();
        switch (ex) {
        case 49:
            QuickSortName(SList, 0, size - 1);
            PrintSortedScore(SList, size);
            break;
        case 50:
            SortStudentScore(SList, size);
            break;
        case 13:
            PrintStudentsScore();
        default:
            break;
        }
    };

    void SwapRows(string **Student_GPA, int i, int j) {
        swap(Student_GPA[i][0], Student_GPA[j][0]); // Swap Tên
        swap(Student_GPA[i][1], Student_GPA[j][1]); // Swap Điểm
    }

    void QuickSortGPA(string **Student_GPA, int left, int right) {
        int i, j;
        string x;
        x = Student_GPA[(left + right) / 2][1]; // Chọn điểm làm điểm chốt

        i = left;
        j = right;
        do {
            while (stoi(Student_GPA[i][1]) > stoi(x))
                i++;
            while (stoi(Student_GPA[j][1]) < stoi(x))
                j--;
            if (i <= j) {
                SwapRows(Student_GPA, i, j);
                i++;
                j--;
            }
        } while (i < j);

        if (left < j)
            QuickSortGPA(Student_GPA, left, j);
        if (i < right)
            QuickSortGPA(Student_GPA, i, right);
    }

    string CalculateGPA(string uName) {
        string filePath = FILE_PATH + "User/Student/" + uName + ".txt";
        ifstream inFile(filePath);
        if (inFile.is_open()) {
            string *highScoreSubj = new string[CHAP_COUNT];
            int *highScoreChap = new int[CHAP_COUNT];
            double *highScore = new double[CHAP_COUNT]{0};

            string line;
            getline(inFile, line); // skip dòng password
            int HIndex = 0;
            while (getline(inFile, line)) {
                if (!line.empty()) {
                    getline(inFile, line);
                    // skip dòng có các cột subject, subject, .....
                    getline(inFile, line);
                    istringstream iss(line);
                    string subject;
                    int chapter;
                    double score;
                    iss >> subject >> chapter >> score;
                    if (HIndex == 0) {
                        highScoreSubj[HIndex] = subject;
                        highScoreChap[HIndex] = chapter;
                        highScore[HIndex] = score;
                        HIndex += 1;
                    }

                    else if (HIndex > 0) {
                        if (highScoreSubj[HIndex - 1] != subject || highScoreChap[HIndex - 1] != chapter) {
                            highScoreSubj[HIndex] = subject;
                            highScoreChap[HIndex] = chapter;
                            highScore[HIndex] = score;
                            HIndex += 1;
                        }
                        else {
                            highScore[HIndex] = max(highScore[HIndex], score);
                        }
                    }
                }
            }

            double SumS = 0;
            for (int i = 0; i < CHAP_COUNT; i++) {
                SumS += highScore[i];
            }

            return to_string(SumS / CHAP_COUNT);
        }
        else {
            return "ERROR: COULDN'T OPEN FILE";
        }
    };
    void AddChapter() {
        int ex;
        do {
            bool addOK = false;
            do {
                system("cls");
                cout << "===== ADD QUESTION TO BANK =====\n";

                string subject;
                int chapter;
                string difficulty;
                string filePath;

                cout << "Enter subject (English, Chemistry, Math, ...): ";
                if (cin.peek() == '\n') {
                    cin.ignore();
                }
                getline(cin, subject);

                cout << "Enter chapter number: ";
                cin >> chapter;

                cout << "Enter difficulty (Easy, Medium, Hard):\n";
                cout << "\t1. Easy\n";
                cout << "\t2. Medium\n";
                cout << "\t3. Hard\n";
                int diff_opt;

                cin >> diff_opt;
                switch (diff_opt) {
                case 1:
                    difficulty = "CHDe";
                    break;
                case 2:
                    difficulty = "CHTB";
                    break;
                case 3:
                    difficulty = "CHKho";
                    break;
                default:
                    break;
                }

                cout << "Enter file path of the question: ";
                cin.ignore();
                getline(cin, filePath);

                addOK = AddQuestionToBank(subject, chapter, difficulty, filePath);
            } while (!addOK);
            cout << "Do you want to add another chapter? (Press ESC to stop, any other key to continue): ";
            ex = _getch();

        } while (ex != KEY_ESC);

        system("cls");
        cout << "Return to the main menu? (Y/N): ";
        char o;
        cin >> o;
        if (tolower(o) == 'n') {
            exit(0);
        }
    }

    string Capitalize(string s) {
        {
            istringstream iss(s);
            ostringstream oss;

            string word;
            bool isFirstWord = true;

            while (iss >> word) {
                if (!isFirstWord) {
                    oss << ' ';
                }
                else {
                    isFirstWord = false;
                }

                if (!word.empty()) {
                    word[0] = toupper(word[0]);
                    oss << word;
                }
            }

            return oss.str();
        }
    }

    bool AddQuestionToBank(string subject, int chapter, string difficulty, string filePath) {
        cout << Capitalize(subject) << endl;
        // Đường dẫn tới thư mục của môn học
        string subjectPath = BANK_PATH + Capitalize(subject) + "/";
        // Đường dẫn tới thư mục của chương
        string chapterPath = subjectPath + "Chapter_" + to_string(chapter) + "/";

        // Tạo thư mục nếu nó chưa tồn tại
        filesystem::create_directories(chapterPath);

        // Đường dẫn tới file mới
        string newFilePath = chapterPath + difficulty + ".txt";

        // Sao chép nội dung từ file nguồn sang file trong ngân hàng
        ifstream sourceFile(filePath, ios::binary);
        ofstream newFile(newFilePath, ios::binary);

        if (sourceFile.is_open() && newFile.is_open()) {

            newFile << sourceFile.rdbuf();
            cout << "Add Chapter_" + to_string(chapter) + " successfully\n";

            CHAP_COUNT++;

            sourceFile.close();
            newFile.close();
            return true;
        }
        else {
            cerr << "Error transfering the question file to Question Bank.\n";
            sourceFile.close();
            newFile.close();
            return false;
        }
    }
};
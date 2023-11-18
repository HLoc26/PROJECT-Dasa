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
#include <map>
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

// Số lượng phần tử trong mảng lưu highscore trong hàm PrintHighScore
#define CHAP_COUNT 9

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

enum ESubject {
    Math,
    Chemistry,
    English
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

    /* CONSTRUCTOR */
    Menu(string username) {
        this->username = username;
    }
    Menu() {
        this->username = "";
    }
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
                    cout << "\nCheck result\n";
                    PrintHighestScores();
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
                    cout << "\nCheck Students' scores\n";
                    // Hàm show score của HS
                    break;
                case Option2:
                    cout << "\nAdd chapter\n";
                    // XemDiem();
                    break;
                case Option3:
                    ChangePass(ERole::Teacher);
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
            PrintMenu(EMenu::SubjectM, option);
            int ex = _getch();

            if (ex == KEY_ENTER) {
                switch (option % 4) {
                case Option1:
                    SelectChapter(ESubject::Math);
                    break;
                case Option2:
                    SelectChapter(ESubject::English);
                    break;
                case Option3:
                    SelectChapter(ESubject::Chemistry);
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
    void PrintMenu(EMenu type, int option) {
        string options[4];
        int size;
        if (type == EMenu::MainM) {
            string temp[] = {"Student Login",
                             "Student Register",
                             "Teacher Login",
                             "Exit"};
            copy(begin(temp), end(temp), begin(options));
        }
        else if (type == EMenu::TeacherM) {
            string temp[] = {"See Students' Scores",
                             "Add Questions",
                             "Change Password",
                             "Log out"};
            copy(begin(temp), end(temp), begin(options));
        }
        else if (type == EMenu::StudentM) {
            string temp[] = {"Practice Test",
                             "See Scores",
                             "Change Password",
                             "Log out"};
            copy(begin(temp), end(temp), begin(options));
        }
        else if (type == EMenu::SubjectM) {
            string temp[] = {"Math",
                             "English",
                             "Chemistry",
                             "Return"};
            copy(begin(temp), end(temp), begin(options));
        }
        for (int i = 0; i < 4; i++) {
            if (i == option % 4) {
                cout << COLOR_BLUE << "\t> " << options[i] << " <" << COLOR_END << "\n";
            }
            else {
                cout << "\t" << options[i] << "\n";
            }
        }
    }
    // Man hinh chon Chapter
    void SelectChapter(ESubject monhoc) {
        int option = 20000;
        while (true) {
            system("cls");
            cout << "Hello, " << username << endl;
            cout << "===============================\n";
            cout << "=========SELECT CHAPTER========\n";
            PrintMenu(monhoc, option);
            int ex = _getch();

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
    void PrintMenu(ESubject monhoc, int option) {
        string mon;
        switch (monhoc) {
        case ESubject::Math:
            mon = "Math";
            break;
        case ESubject::English:
            mon = "English";
            break;
        case ESubject::Chemistry:
            mon = "Chemistry";
            break;

        default:
            break;
        }
        cout << endl
             << mon << endl;
        string options[4];
        if (monhoc == ESubject::Math) {
            string temp[] = {"Chapter 1: Decimal Number",
                             "Chapter 2: Math2",
                             "Chapter 3: Math3",
                             "Return"};
            copy(begin(temp), end(temp), begin(options));
        }
        else if (monhoc == ESubject::English) {
            string temp[] = {"Chapter 1: E1",
                             "Chapter 2: E2",
                             "Chapter 3: E3",
                             "Return"};
            copy(begin(temp), end(temp), begin(options));
        }
        else if (monhoc == ESubject::Chemistry) {
            string temp[] = {"Chapter 1: Oxygen",
                             "Chapter 2: Bases",
                             "Chapter 3: Acids",
                             "Return"};
            copy(begin(temp), end(temp), begin(options));
        }
        for (int i = 0; i < 4; i++) {
            if (i == option % 4) {
                cout << COLOR_BLUE << "\t> " << options[i] << " <" << COLOR_END << "\n";
            }
            else {
                cout << "\t" << options[i] << "\n";
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
    // Hiệu ứng cho chữ logging in
    void LogInAnimate() {
        srand(time(NULL));
        int time = rand() % (rand() % 10 + 8) + 4;
        for (int i = 0; i < time; i++) {
            system("cls");
            cout << COLOR_GREEN
                 << "Succeed!"
                 << COLOR_END << "\n";
            cout << "Logging in" << string((i + 1) % 4, '.');
            this_thread::sleep_for(chrono::seconds(1));
        }
        system("cls");
    }
    // Kiểm tra xem TK và MK có hợp lệ không
    bool CheckValidLogin(string userInp, string passInp, ERole role) {
        string folder = "";
        if (role == ERole::Teacher) {
            folder = "Teacher";
        }
        else {
            folder = "Student";
        }
        // Mở file với tên <username>
        ifstream user(FILE_PATH + "User/" + folder + "/" + userInp + "/" + userInp + ".txt", ios::in);
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
    void StartTest(ESubject monhoc, int chapter) {
        string mon;
        switch (monhoc) {
        case ESubject::Math:
            mon = "Toan";
            break;
        case ESubject::English:
            mon = "TiengAnh";
            break;
        case ESubject::Chemistry:
            mon = "Hoa";
            break;

        default:
            break;
        }

        DanhSach DSCH;
        srand(time(NULL));
        DSCH.DocFile(mon, 1);
        DLList Question = DSCH.GetQuestions();
        Question.PrintList();
        system("cls");
        Test(Question, mon, chapter);
    }

    // Bat dau lam bai test
    void Test(DLList Question, string subject, int chapter) {
        CauHoi *chHienTai = Question.head;
        int ans_pos = 0;
        string *ans = new string[Question.size]{""};
        int choices = 20000;
        double totalScore = 0;
        int correctAnswers = 0;
        bool answered = false;
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
                if (!answered) {
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
                    answered = true;
                }
            }
            else if (ex == KEY_UP) {
                choices -= 1;
                answered = false;
            }
            else if (ex == KEY_DOWN) {
                choices += 1;
                answered = false;
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
        ofstream user(FILE_PATH + "User/Student/" + userInp + "/" + userInp + ".txt", ios::out);
        user << passInp;
        /* cout << FILE_PATH + "User/Student/" + userInp + "/" + userInp + ".txt"; */
        cout << COLOR_GREEN << "Successfully registered!" << COLOR_END << "\n";
        cout << "Press any button to return\n";
        user.close();

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
            path = FILE_PATH + "User/Student/" + username + "/" + username + "txt";
        }
        else {
            path = FILE_PATH + "User/Teacher/" + username + "/" + username + "txt";
        }
        ofstream user(path, ios::out);
        user.clear();
        user << password;
        user.close();
    }

    void StoreScores(const StudentScore &studentScore) {
        string filePath = FILE_PATH + "User/Student/" + username + "/" + username + ".txt";
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

    void PrintHighestScores() {
        system("cls");
        string filePath = FILE_PATH + "User/Student/" + username + "/" + username + ".txt";
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
            cout << username << "'s high score" << endl;
            cout << "================================\n";
            // Print the highest scores for each subject and chapter
            cout << setw(12) << left << "Subject"
                 << setw(10) << left << "Chapter"
                 << setw(10) << left << "High Score" << endl;
            for (int i = 0; i < HIndex; i++) {
                cout << setw(12) << left << highScoreSubj[i] << setw(10) << left << highScoreChap[i] << setw(10) << left << highScore[i] << endl;
            }

            inFile.close();
        }
        else {
            cerr << "Error opening file: " << filePath << endl;
        }
        cout << "Press any button to go back\n";
        _getch();
    }
};
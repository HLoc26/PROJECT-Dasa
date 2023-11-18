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
    MainM,
    TeacherM,
    StudentM,
    SubjectM
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
 */

struct Menu {

    string username = "";
    string password = "";

    void StartMenu() {
        int option = 20000;
        while (true) {
            system("cls");
            cout << "===== TEST SIMULATOR =====\n";
            PrintMenu(EMenu::MainM, option);
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
            PrintMenu(EMenu::StudentM, option);
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
            PrintMenu(EMenu::TeacherM, option);
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
            PrintMenu(EMenu::SubjectM, option);
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
    void PrintMenu(EMenu type, int option) {
        cout << "OPTION: " << option % 4 << endl;
        string options[4];
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
                             "Return"};
            copy(begin(temp), end(temp), begin(options));
        }
        else if (type == EMenu::StudentM) {
            string temp[] = {"Start Test",
                             "See Scores",
                             "Change Password",
                             "Return"};
            copy(begin(temp), end(temp), begin(options));
        }
        else if (type == EMenu::SubjectM) {
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
    void PrintMenu(string monhoc, int option) {
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
            while ((ch = getch()) != KEY_ENTER) {
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
            while ((ch = getch()) != KEY_ENTER) {
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
                cout << "\n\x1B[31m"
                     << "Wrong password or username!"
                     << "\033[0m\n\n";
                passInp = "";
                userInp = "";
                getch();
            }
            else {
                username = userInp;
                password = passInp;
                LogInAnimate(); // Này làm cho màu mè

                // In ra để test, sau này thêm menu teacher rồi đổi
                // ==============================================//
                cout << username << endl
                     << password;
                getch();
                // exit(0);
                // ==============================================//
                if (role == ERole::Teacher) {
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
            cout << "\x1B[32m"
                 << "Successfully!"
                 << "\033[0m\n";
            cout << "Logging in" << string((i + 1) % 4, '.');
            sleep(1);
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
        ifstream user("User/" + folder + "/" + userInp + ".txt", ios::in);
        // Nếu mở thành công == có tài khoản tên username
        if (!user.fail()) {
            string filePass;
            getline(user, filePass);

            // Check pass, sai thì trả về false
            if (filePass != passInp) {
                return false;
            }
            else return true;
        }
        // Không có tk thì trả về false
        else return false;
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
    // Bat dau lam bai test
    void Test(DLList Question) {
        CauHoi *chHienTai = Question.head;

        int ans_pos = 0;
        string *ans = new string[Question.size]{""};
        int choices = 20000;
        int totalScore = 0;
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
                    totalScore = correctAnswers * 10;
                    cout << "Your final score: " << totalScore << endl;
                    exit(0);
                }
            }
        }
    }
};

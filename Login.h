#include "Menu.h"
#include <iostream>

using namespace std;

// Login
void Menu::Login(ERole role) {
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
void Menu::LogInAnimate() {
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
bool Menu::CheckValidLogin(string userInp, string passInp, ERole role) {
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
#include "CauHoi.h"
#include "DLList.h"
#include <conio.h>
#include <iomanip>
#include <iostream>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13

using namespace std;

void StartTest(DLList Question) {
    system("color 07");
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
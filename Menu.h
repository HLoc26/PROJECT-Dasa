#include "CauHoi.h"
#include "DLList.h"
#include <conio.h>
#include <iomanip>
#include <iostream>
#include "DS.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13

using namespace std;

void StartTest(DLList Question) {
    system("color 07");
    CauHoi* chHienTai = Question.head;

    int ans_pos = 0;
    string* ans = new string[Question.size]{ "" };
    int choices = 20000;
    int totalScore = 0;
    int correctAnswers = 0;  
    bool answered = false;
    bool* answeredCorrectly = new bool[Question.size] { false };

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




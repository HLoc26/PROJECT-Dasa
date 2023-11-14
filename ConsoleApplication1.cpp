// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "CauHoi.h"
#include "DLList.h"
#include "DS.h"
#include <conio.h>
#include <iostream>

#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std;

int main() {
    DanhSach DSCH;

    srand(time(NULL));

    DSCH.DocFile();
    DSCH.InDSCauHoi();
    DLList Question = DSCH.GetQuestions();

    Question.PrintList();

    system("pause");
    system("cls");

    CauHoi *chHienTai = Question.head;

    while (true) {
        system("cls");
        chHienTai->InCauHoi();
        int ex;

        switch (ex = getch()) {
        case KEY_LEFT /* M */:
            if (chHienTai->prev == NULL) {
                chHienTai = Question.tail;
            }
            else {
                chHienTai = chHienTai->prev;
            }
            break;
        case KEY_RIGHT: /* P */
            if (chHienTai->next == NULL) {
                chHienTai = Question.head;
            }
            else {
                chHienTai = chHienTai->next;
            }
            break;
        case 27:
            exit(0);
        default:
            break;
        }
    }
}

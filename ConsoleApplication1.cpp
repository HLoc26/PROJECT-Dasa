// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and
// ends there.
//

#include "CauHoi.h"
#include "DLList.h"
#include "DS.h"
#include "Menu.h"
#include <conio.h>
#include <iomanip>
#include <iostream>

using namespace std;

int main() {
    DanhSach DSCH;

    srand(time(NULL));

    DSCH.DocFile("Toan");
    DSCH.InDSCauHoi();
    DLList Question = DSCH.GetQuestions();

    Question.PrintList();

    system("pause");
    system("cls");

    StartTest(Question);
}

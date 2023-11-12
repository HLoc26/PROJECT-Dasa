// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "DS.h"
#include <iostream>

using namespace std;

int main() {
    DanhSach DSCH;
    DLList listDe, listTB, listKho;

    srand(time(NULL));

    DSCH.DocFile();
    DSCH.InDSCauHoi();
    int a, b, c;
    cout << "Nhap so luong cau hoi de: " << endl;
    cin >> a;
    cout << "\nNhap so luong cau hoi trung binh: " << endl;
    cin >> b;
    cout << "\nNhap so luong cau hoi kho: " << endl;
    cin >> c;

    for (int i = 0; i < a; i++) {
        listDe.Push(DSCH.CauHoiDe[i]);
    }
    cout << listDe.size << endl;
    cout << "Con Cac";
    CauHoi randomQuestionDe = listDe.getRandomQuestion();
    randomQuestionDe.InCauHoi();


    /*
    for (int i = 0; i < b; i++) {
        listTB.Push(DSCH.CauHoiTB[i]);
    }
    for (int i = 0; i < c; i++) {
        listKho.Push(DSCH.CauHoiKho[i]);
    }

    
    CauHoi* randomQuestionTB = listTB.getRandomQuestion();
    randomQuestionTB->InCauHoi();
    CauHoi* randomQuestionKho = listKho.getRandomQuestion();
    randomQuestionKho->InCauHoi();
    */
}

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

    //Push câu hỏi vào queue    
    for (int i = 0; i < DSCH.slch_de; i++) {
        listDe.Push(DSCH.CauHoiDe[i]);
    }
    for (int i = 0; i < DSCH.slch_tb; i++) {
        listTB.Push(DSCH.CauHoiTB[i]);
    }
    for (int i = 0; i < DSCH.slch_kho; i++) {
        listKho.Push(DSCH.CauHoiKho[i]);
    }

    //Tạo đề thi với câu hỏi ngẫu nhiên
    int slDe;
    cout << "\nNhap so luong cau hoi de muon lay ngau nhien: ";
    cin >> slDe;
    int slTB;
    cout << "\nNhap so luong cau hoi trung binh muon lay ngau nhien: ";
    cin >> slTB;
    int slKho;
    cout << "\nNhap so luong cau hoi kho muon lay ngau nhien: ";
    cin >> slKho;

    for (int i = 0; i < slDe; i++) {
        if (listDe.size > 0) {
            CauHoi randomQuestion = listDe.getRandomQuestion();
            randomQuestion.InCauHoi();
        }
        else {
            cout << "Tat ca cau hoi de da duoc chon.\n";
            break;
        }
    }
    for (int i = 0; i < slTB; i++) {
        if (listTB.size > 0) {
            CauHoi randomQuestion = listTB.getRandomQuestion();
            randomQuestion.InCauHoi();
        }
        else {
            cout << "Tat ca cau hoi TB da duoc chon.\n";
            break;
        }
    }
    for (int i = 0; i < slKho; i++) {
        if (listKho.size > 0) {
            CauHoi randomQuestion = listKho.getRandomQuestion();
            randomQuestion.InCauHoi();
        }
        else {
            cout << "Tat ca cau hoi kho da duoc chon.\n";
            break;
        }
    }
}

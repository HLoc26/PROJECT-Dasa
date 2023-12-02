#pragma once
#include "DLList.h"
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <random>
#include <string>

#define FILE_PATH string("")
#define BANK_PATH string("NganHang/")
// #define BANK_PATH string("C:/DASA/TEST PROJECT/ConsoleApplication1/NganHang/")

// #define FILE_PATH string("C:/DASA/TEST PROJECT/ConsoleApplication1/")

using namespace std;

#define MAX 100

struct DanhSach {
    CauHoi *CauHoiDe = new CauHoi[MAX];
    int slch_de = 0;
    CauHoi *CauHoiTB = new CauHoi[MAX];
    int slch_tb = 0;
    CauHoi *CauHoiKho = new CauHoi[MAX];
    int slch_kho = 0;

    void DS() {
        this->CauHoiDe = new CauHoi[MAX];
        this->CauHoiTB = new CauHoi[MAX];
        this->CauHoiKho = new CauHoi[MAX];
        this->slch_de = 0;
        this->slch_tb = 0;
        this->slch_kho = 0;
    }

    void DocFile(string monhoc, int chap) {
        string chapter = "Chapter_" + to_string(chap + 1);

        string file_de = FILE_PATH + "NganHang/" + monhoc + "/" + chapter + "/CHDe.txt";
        string file_tb = FILE_PATH + "NganHang/" + monhoc + "/" + chapter + "/CHTB.txt";
        string file_kho = FILE_PATH + "NganHang/" + monhoc + "/" + chapter + "/CHKho.txt";

        ifstream de(file_de, ios::in);
        ifstream tb(file_tb, ios::in);
        ifstream kho(file_kho, ios::in);

        if (!de.fail()) {
            int i = 0;
            while (!de.eof()) {
                getline(de, this->CauHoiDe[i].noidung);
                getline(de, this->CauHoiDe[i].a);
                getline(de, this->CauHoiDe[i].b);
                getline(de, this->CauHoiDe[i].c);
                getline(de, this->CauHoiDe[i].d);
                getline(de, this->CauHoiDe[i].dapan);
                i += 1;
            }
            slch_de = i;
        }

        if (!tb.fail()) {
            int i = 0;
            while (!tb.eof()) {
                getline(tb, this->CauHoiTB[i].noidung);
                getline(tb, this->CauHoiTB[i].a);
                getline(tb, this->CauHoiTB[i].b);
                getline(tb, this->CauHoiTB[i].c);
                getline(tb, this->CauHoiTB[i].d);
                getline(tb, this->CauHoiTB[i].dapan);
                i += 1;
            }
            slch_tb = i;
        }

        if (!kho.fail()) {
            int i = 0;
            while (!kho.eof()) {
                getline(kho, this->CauHoiKho[i].noidung);
                getline(kho, this->CauHoiKho[i].a);
                getline(kho, this->CauHoiKho[i].b);
                getline(kho, this->CauHoiKho[i].c);
                getline(kho, this->CauHoiKho[i].d);
                getline(kho, this->CauHoiKho[i].dapan);
                i += 1;
            }
            slch_kho = i;
        }

        de.close();
        tb.close();
        kho.close();
    }

    void InDSCauHoi() {
        if (slch_de != 0) {
            cout << "\n=== List of Easy Questions ===\n";
            cout << "Current number of easy questions: " << slch_de << endl;
            for (int i = 0; i < slch_de; i++) {
                cout << i + 1 << ". " << CauHoiDe[i].noidung << endl;
            }
        }

        if (slch_tb != 0) {
            cout << "\n=== List of Medium Questions ===\n";
            cout << "Current number of medium questions: " << slch_tb << endl;
            for (int i = 0; i < slch_tb; i++) {
                cout << i + 1 << ". " << CauHoiTB[i].noidung << endl;
            }
        }
        if (slch_kho != 0) {
            cout << "\n=== List of Hard Questions ===\n";
            cout << "Current number of hard questions: " << slch_kho << endl;
            for (int i = 0; i < slch_kho; i++) {
                cout << i + 1 << ". " << CauHoiKho[i].noidung << endl;
            }
        }
    }
    DLList GetQuestions() {

        cout << "\nSo luong cau hoi: \n";
        cout << "\t\tDe:         " << slch_de << endl;
        cout << "\t\tTrung binh: " << slch_tb << endl;
        cout << "\t\tKho:        " << slch_kho << endl;

        DLList Questions;
        // Tạo đề thi với câu hỏi ngẫu nhiên
        int slDe = 0;
        int slTB = 0;
        int slKho = 0;

        // Truong hop nhap 0 0 0
        do {
            do {
                cout << "\nNhap so luong cau hoi de muon lay ngau nhien: ";
                cin >> slDe;
            } while (slDe > slch_de);

            do {
                cout << "\nNhap so luong cau hoi trung binh muon lay ngau nhien: ";
                cin >> slTB;
            } while (slTB > slch_tb);

            do {
                cout << "\nNhap so luong cau hoi kho muon lay ngau nhien: ";
                cin >> slKho;
            } while (slKho > slch_kho);
        } while (slDe + slTB + slKho <= 0);

        int i = 0;
        while (i < slDe) {
            int index = rand() % slch_de;
            bool isIn = CauHoiDe[index].in(Questions.head);
            if (!isIn) {

                CauHoi ch = RandomPhuongAn(CauHoiDe[index]);
                Questions.Push(ch);
                i += 1;
            }
        }

        i = 0;
        while (i < slTB) {
            int index = rand() % slch_tb;
            bool isIn = CauHoiTB[index].in(Questions.head);
            if (!isIn) {
                CauHoi ch = RandomPhuongAn(CauHoiTB[index]);
                Questions.Push(ch);
                i += 1;
            }
        }
        i = 0;
        while (i < slKho) {
            int index = rand() % slch_kho;
            bool isIn = CauHoiKho[index].in(Questions.head);
            if (!isIn) {
                CauHoi ch = RandomPhuongAn(CauHoiKho[index]);
                Questions.Push(ch);
                i += 1;
            }
        }
        return Questions;
    }

    // Function trả về một câu hỏi đã được xáo trộn
    CauHoi RandomPhuongAn(CauHoi ch) {
        string phuongan[] = {ch.a, ch.b, ch.c, ch.d};

        string DA = "";
        if (ch.dapan == "A") {
            DA = ch.a;
        }
        else if (ch.dapan == "B") {
            DA = ch.b;
        }
        else if (ch.dapan == "C") {
            DA = ch.c;
        }
        else if (ch.dapan == "D") {
            DA = ch.d;
        }

        random_device rd;
        mt19937 g(rd());
        shuffle(begin(phuongan), end(phuongan), g);

        ch.a = phuongan[0];
        ch.b = phuongan[1];
        ch.c = phuongan[2];
        ch.d = phuongan[3];

        if (DA == ch.a) {
            ch.dapan = "A";
        }
        else if (DA == ch.b) {
            ch.dapan = "B";
        }
        else if (DA == ch.c) {
            ch.dapan = "C";
        }
        else if (DA == ch.d) {
            ch.dapan = "D";
        }
        return ch;
    }
};
typedef struct DS DS;
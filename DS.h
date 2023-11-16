#pragma once
#include "DLList.h"
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

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
        string chapter = "";
        if (chap == 1) {
            chapter = "Chapter_1";
        }
        else if (chap == 2) {
            chapter = "Chapter_2";
        }
        else if (chap == 3) {
            chapter = "Chapter_3";
        }
        string file_de = "C:/DASA/TEST PROJECT/ConsoleApplication1/NganHang/" + monhoc + "/" + chapter + "/CHDe.txt";
        string file_tb = "C:/DASA/TEST PROJECT/ConsoleApplication1/NganHang/" + monhoc + "/" + chapter + "/CHTB.txt";
        string file_kho = "C:/DASA/TEST PROJECT/ConsoleApplication1/NganHang/" + monhoc + "/" + chapter + "/CHKho.txt";
        ifstream de(file_de, ios::in);
        ifstream tb(file_tb, ios::in);
        ifstream kho(file_kho, ios::in);

        if (de.fail()) {
            cerr << "DS.h: ERROR Readfile: CHDe.txt\n";
            cout << file_de << endl;
            exit(0);
        }

        if (tb.fail()) {
            cerr << "DS.h: ERROR Readfile: CHTb.txt\n";
            cout << file_tb << endl;
            exit(0);
        }

        if (kho.fail()) {
            cerr << "DS.h: ERROR Readfile: CHKho.txt\n";
            cout << file_kho << endl;
            exit(0);
        }

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
        i = 0;
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
        i = 0;
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

    void InDSCauHoi() {
        cout << "\n=== DS Cau hoi de ===\n";
        for (int i = 0; i < slch_de; i++) {
            cout << i + 1 << ". " << CauHoiDe[i].noidung << endl;
        }

        cout << "\n=== DS Cau hoi trung binh ===\n";
        for (int i = 0; i < slch_tb; i++) {
            cout << i + 1 << ". " << CauHoiTB[i].noidung << endl;
        }

        cout << "\n=== DS Cau hoi kho ===\n";
        for (int i = 0; i < slch_kho; i++) {
            cout << i + 1 << ". " << CauHoiKho[i].noidung << endl;
        }
    }
    DLList GetQuestions() {

        DLList Questions;
        // Tạo đề thi với câu hỏi ngẫu nhiên
        int slDe = 0;
        do {
            cout << "\nNhap so luong cau hoi de muon lay ngau nhien: ";
            cin >> slDe;
        } while (slDe == 0 || slDe > slch_de);

        int slTB = 0;

        do {
            cout << "\nNhap so luong cau hoi trung binh muon lay ngau nhien: ";
            cin >> slTB;
        } while (slTB == 0 || slTB > slch_tb);

        int slKho = 0;
        do {
            cout << "\nNhap so luong cau hoi kho muon lay ngau nhien: ";
            cin >> slKho;
        } while (slKho == 0 || slKho > slch_kho);

        int i = 0;
        while (i < slDe) {
            int index = rand() % slch_de;
            bool isIn = CauHoiDe[index].in(Questions.head);
            if (!isIn) {
                CauHoi ch = CauHoiDe[index];
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

                srand(time(0));
                random_shuffle(begin(phuongan), end(phuongan)); // #include <algorithm>

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

                Questions.Push(ch);
                i += 1;
            }
        }

        i = 0;
        while (i < slTB) {
            int index = rand() % slch_tb;
            bool isIn = CauHoiTB[index].in(Questions.head);
            if (!isIn) {
                Questions.Push(CauHoiTB[index]);
                i += 1;
            }
        }
        i = 0;
        while (i < slKho) {
            int index = rand() % slch_kho;
            bool isIn = CauHoiKho[index].in(Questions.head);
            if (!isIn) {
                Questions.Push(CauHoiKho[index]);
                i += 1;
            }
        }
        return Questions;
    }
};
typedef struct DS DS;
#pragma once
#include "DLList.h"
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

    void DocFile() {
        ifstream de("C:/DASA/PROJECT/NganHang/CHDe.txt", ios::in);
        ifstream tb("C:/DASA/PROJECT/NganHang/CHTb.txt", ios::in);
        ifstream kho("C:/DASA/PROJECT/NganHang/CHKho.txt", ios::in);

        if (de.fail()) {
            cerr << "ERROR Readfile: CHDe.txt\n";
            exit(0);
        }

        if (tb.fail()) {
            cerr << "ERROR Readfile: CHTb.txt\n";
            exit(0);
        }

        if (kho.fail()) {
            cerr << "ERROR Readfile: CHKho.txt\n";
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
};
typedef struct DS DS;
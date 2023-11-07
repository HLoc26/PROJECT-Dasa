#pragma once
#include "CauHoi.h"
#include "DLList.h"
#include <bits/stdc++.h>

using namespace std;

#define MAX 100

struct DS {
    CauHoi CauHoiDe[MAX];
    int slch_de = 0;
    CauHoi CauHoiTB[MAX];
    int slch_tb = 0;
    CauHoi CauHoiKho[MAX];
    int slch_kho = 0;

    void DocFile() {
        ifstream de("./CHDe.txt", ios::in);
        ifstream tb("./CHTb.txt", ios::in);
        ifstream kho("./CHKho.txt", ios::in);

        int i = 0;
        while (!de.eof()) {
            de >> this->CauHoiDe[i].noidung;
            de >> this->CauHoiDe[i].a;
            de >> this->CauHoiDe[i].b;
            de >> this->CauHoiDe[i].c;
            de >> this->CauHoiDe[i].d;
            de >> this->CauHoiDe[i].dapan;
            i += 1;
        }
        slch_de = i;
        i = 0;
        while (!tb.eof()) {
            tb >> this->CauHoiTB[i].noidung;
            tb >> this->CauHoiTB[i].a;
            tb >> this->CauHoiTB[i].b;
            tb >> this->CauHoiTB[i].c;
            tb >> this->CauHoiTB[i].d;
            tb >> this->CauHoiTB[i].dapan;
            i += 1;
        }
        slch_tb = i;
        i = 0;
        while (!tb.eof()) {
            kho >> this->CauHoiKho[i].noidung;
            kho >> this->CauHoiKho[i].a;
            kho >> this->CauHoiKho[i].b;
            kho >> this->CauHoiKho[i].c;
            kho >> this->CauHoiKho[i].d;
            kho >> this->CauHoiKho[i].dapan;
            i += 1;
        }
        slch_kho = i;
    }

    void InDSCauHoi() {
        cout << "\n=== DS Cau hoi de ===\n";
        for (int i = 0; i < slch_de; i++) {
            cout << i + 1 << CauHoiDe[i].noidung << endl;
        }

        cout << "\n=== DS Cau hoi trung binh ===\n";
        for (int i = 0; i < slch_tb; i++) {
            cout << i + 1 << CauHoiTB[i].noidung << endl;
        }

        cout << "\n=== DS Cau hoi kho ===\n";
        for (int i = 0; i < slch_kho; i++) {
            cout << i + 1 << CauHoiKho[i].noidung << endl;
        }
    }
};
typedef struct DS DS;
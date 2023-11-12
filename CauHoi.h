#pragma once
#include <iostream>
using namespace std;

// Câu hỏi gồm nội dung, các phương án a, b, c, d, và đáp án
struct CauHoi {
    string noidung;
    string a = "";
    string b = "";
    string c = "";
    string d = "";
    string dapan;
    CauHoi* prev;
    CauHoi* next;

    CauHoi() {
        this->noidung = "";
        this->a = "";
        this->b = "";
        this->c = "";
        this->d = "";
        this->dapan = "";
        this->prev = NULL;
        this->next = NULL;
    }

    CauHoi(string noidung, string a, string b, string c, string d, string dapan) {
        this->noidung = noidung;
        this->a = a;
        this->b = b;
        this->c = c;
        this->d = d;
        this->dapan = dapan;
        this->prev = NULL;
        this->next = NULL;
    }

    void InCauHoi() {
        cout << noidung;
        cout << "\t" << a << endl;
        cout << "\t" << b << endl;
        if (c != "") {
            cout << "\t" << c << endl;
        }
        if (d != "") {
            cout << "\t" << d << endl;
        }
    }
};
typedef struct CauHoi CauHoi;
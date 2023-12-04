#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_BACKSPACE 8
#define KEY_ESC 27

#define COLOR_RED "\x1B[31m"
#define COLOR_BLUE "\x1B[36m"
#define COLOR_GREEN "\x1B[32m"
#define COLOR_END "\033[0m"

// Câu hỏi gồm nội dung, các phương án a, b, c, d, và đáp án
struct CauHoi {
    string noidung = "";
    string a = "";
    string b = "";
    string c = "";
    string d = "";
    string dapan;
    CauHoi *prev;
    CauHoi *next;

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

    void InCauHoi(int choice) {
        cout << noidung << endl;
        // cout << "CHOICE: " << choice % 4 << endl;
        int numQ = 2;
        if (c != "") {
            numQ += 1;
        }
        if (d != "") {
            numQ += 1;
        }
        switch (choice % numQ) {
        case 0:
            cout << COLOR_BLUE
                << "\t> A. " << a << " <"
                << COLOR_END << "\n"; // Set color blue for 1 row
            cout << "\tB. " << b << endl;
            if (c != "") {
                cout << "\tC. " << c << endl;
            }
            if (d != "") {
                cout << "\tD. " << d << endl;
            }
            break;
        case 1:
            cout << "\tA. " << a << endl;
            cout << COLOR_BLUE
                << "\t> B. " << b << " <"
                << COLOR_END << "\n"; // Set color blue for 1 row
            if (c != "") {
                cout << "\tC. " << c << endl;
            }
            if (d != "") {
                cout << "\tD. " << d << endl;
            }
            break;
        case 2:
            cout << "\tA. " << a << endl;
            cout << "\tB. " << b << endl;
            cout << COLOR_BLUE
                << "\t> C. " << c << " <"
                << COLOR_END << "\n"; // Set color blue for 1 row
            if (d != "") {
                cout << "\tD. " << d << endl;
            }
            break;
        case 3:
            cout << "\tA. " << a << endl;
            cout << "\tB. " << b << endl;
            cout << "\tC. " << c << endl;
            cout << COLOR_BLUE
                << "\t> D. " << d << " <"
                << COLOR_END << "\n"; // Set color blue for 1 row
            break;
        default:
            cout << "\tA. " << a << endl;
            cout << "\tB. " << b << endl;
            if (c != "") {
                cout << "\tC. " << c << endl;
            }
            if (d != "") {
                cout << "\tD. " << d << endl;
            }
            break;
        }
    }

    // Kiem tra CauHoi co nam trong Questions hay khong
    bool in(CauHoi *head) {
        CauHoi *p = head;
        while (p != NULL) {
            if (p->noidung == this->noidung) {
                return true;
            }
            p = p->next;
        }
        return false;
    }

    bool IsCorrectAnswer(string userAnswer) {
        if (dapan == userAnswer) {
            return true;
        }
        return false;
    }
       
    bool operator==(const CauHoi ch) {
        return this->noidung == ch.noidung;
    }

};
typedef struct CauHoi CauHoi;
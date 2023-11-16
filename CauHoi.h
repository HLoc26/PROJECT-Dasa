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
            cout << "\x1B[34m"
                 << "\t> A. " << a << " <"
                 << "\033[0m\n"; // Set color blue for 1 row
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
            cout << "\x1B[34m"
                 << "\t> B. " << b << " <"
                 << "\033[0m\n"; // Set color blue for 1 row
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
            cout << "\x1B[34m"
                 << "\t> C. " << c << " <"
                 << "\033[0m\n"; // Set color blue for 1 row
            if (d != "") {
                cout << "\tD. " << d << endl;
            }
            break;
        case 3:
            cout << "\tA. " << a << endl;
            cout << "\tB. " << b << endl;
            cout << "\tC. " << c << endl;
            cout << "\x1B[34m"
                 << "\t> D. " << d << " <"
                 << "\033[0m\n"; // Set color blue for 1 row
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

    // Kieem tra CauHoi co nam trong Questions hay khong
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
};
typedef struct CauHoi CauHoi;

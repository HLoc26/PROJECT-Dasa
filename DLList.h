#pragma once
#include "CauHoi.h"
#include "DLList.h"
#include <cstdlib>
#include <iostream>

using namespace std;

// Danh sách liên kết đôi chứa các câu hỏi đưọc chọn
struct DLList {
    CauHoi *head = NULL;
    CauHoi *tail = NULL;
    int size = 0;

    void Push(CauHoi ch) {
        CauHoi *temp = new CauHoi(ch.noidung, ch.a, ch.b, ch.c, ch.d, ch.dapan);
        if (head == NULL) {
            head = temp;
            tail = temp;
        }
        else {
            tail->next = temp;
            temp->prev = tail;
            tail = temp;
        }
        size++;
    }

    void Pop(CauHoi *node) {
        if (node->prev) {
            node->prev->next = node->next;
        }
        else {
            head = node->next;
        }
        if (node->next) {
            node->next->prev = node->prev;
        }
        else {
            tail = node->prev;
        }
        delete node;
        size--;
    }

    void PrintList() {
        CauHoi *p = head;
        while (p != NULL) {
            p->InCauHoi(-1);
            p = p->next;
        }
    }
};

typedef struct DLList DLList;
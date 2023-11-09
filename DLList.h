#pragma once
#include "CauHoi.h"
#include <iostream>

using namespace std;

// Danh sách liên kết đôi chứa các câu hỏi đưọc chọn
struct DLList {
    CauHoi *head;
    CauHoi *tail;
    int size;

    void Push(CauHoi ch) {}

    void Pop() {}
};
typedef struct DLList DLList;
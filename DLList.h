#pragma once
#include "CauHoi.h"
#include <iostream>
#include <cstdlib>

using namespace std;

// Danh sách liên kết đôi chứa các câu hỏi đưọc chọn
struct DLList {
	CauHoi* head;
	CauHoi* tail;
	int size;

	void Push(CauHoi ch) {
		CauHoi* temp = new CauHoi(ch.noidung, ch.a, ch.b, ch.c, ch.d, ch.dapan);
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

	void Pop() {
		if (head != NULL) {
			CauHoi* temp = head;
			head = head->next;
			delete temp;
			size--;
		}
	}

	CauHoi getRandomQuestion() {
		int index = rand() % size;
		CauHoi* current = head;
		for (int i = 0; i < index; i++) {
			current = current->next;
		}
		return *current;
	};
};
typedef struct DLList DLList;
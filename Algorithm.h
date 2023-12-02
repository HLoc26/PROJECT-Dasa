#pragma once
#include "CauHoi.h"
using namespace std;

class Algorithm {
  private:
    void merge(CauHoi *arr, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        CauHoi leftArr[n1], rightArr[n2];

        for (int i = 0; i < n1; i++) {
            leftArr[i] = arr[left + i];
        }
        for (int j = 0; j < n2; j++) {
            rightArr[j] = arr[mid + 1 + j];
        }

        int i = 0, j = 0, k = left;

        while (i < n1 && j < n2) {
            if (leftArr[i].noidung.length() <= rightArr[j].noidung.length()) {
                arr[k] = leftArr[i];
                i++;
            }
            else {
                arr[k] = rightArr[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr[k] = leftArr[i];
            i++;
            k++;
        }

        while (j < n2) {
            arr[k] = rightArr[j];
            j++;
            k++;
        }
    }
    void SwapRows(string **Student_GPA, int i, int j) {
        swap(Student_GPA[i][0], Student_GPA[j][0]); // Swap Tên
        swap(Student_GPA[i][1], Student_GPA[j][1]); // Swap Điểm
    }

  public:
    void MergeSort(CauHoi *arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;

            MergeSort(arr, left, mid);
            MergeSort(arr, mid + 1, right);

            merge(arr, left, mid, right);
        }
    }

    void QuickSortGPA(string **Student_GPA, int left, int right) {
        int i, j;
        string x;
        x = Student_GPA[(left + right) / 2][1]; // Chọn điểm làm điểm chốt

        i = left;
        j = right;
        do {
            while (stoi(Student_GPA[i][1]) > stoi(x))
                i++;
            while (stoi(Student_GPA[j][1]) < stoi(x))
                j--;
            if (i <= j) {
                SwapRows(Student_GPA, i, j);
                i++;
                j--;
            }
        } while (i < j);

        if (left < j)
            QuickSortGPA(Student_GPA, left, j);
        if (i < right)
            QuickSortGPA(Student_GPA, i, right);
    }

    void QuickSortName(string name[], int left, int right) {
        int i, j;
        string x;
        x = name[(left + right) / 2];
        i = left;
        j = right;
        do {
            while (name[i] < x)
                i++;
            while (name[j] > x)
                j--;
            if (i <= j) {
                swap(name[i], name[j]);
                i++;
                j--;
            }
        } while (i < j);
        if (left < j) QuickSortName(name, left, j);
        if (i < right) QuickSortName(name, i, right);
    }

    // BinarySearch dựa trên độ dài của câu hỏi
    bool BinarySearch(CauHoi *arr1, int size, CauHoi target) {
    }
};
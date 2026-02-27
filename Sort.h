//
// Created by dyx on 2025/12/16.
//

#ifndef TEST_SORT_H
#define TEST_SORT_H
#include <iostream>
//#include<vector>
#include "Vector.h"
#include <ctime>
using namespace std;
void swap(int &a, int &b)
{
    int val = a;
    a = b;
    b = val;
}
void BubbleSort(Vector<int> &v)
{
    for (int i = 0; i < v.size() - 1; i++) {
        for (int j = 0; j < v.size() - i - 1; j++) {
            if (v[j] > v[j + 1])
                swap(v[j], v[j + 1]);
        }
    }
}

void SelectSort(Vector<int> &v)
{
    for (int i = 0; i < v.size() - 1; i++) {
        for (int j = i + 1; j < v.size(); j++) {
            if (v[i] > v[j])
                swap(v[j], v[i]);
        }
    }
}

void InsertSort(Vector<int> &v)
{
    int size = v.size();
    for (int i = 1; i < size; i++) {
        int val = v[i];
        int j = i - 1;
        for (; j >= 0; j--) {
            if (v[j] > val)
                v[j + 1] = v[j];
            else
                break;
        }
        v[j + 1] = val;
    }
}

void ShellSort(Vector<int> &v)
{
    int size = v.size();
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            int val = v[i];
            int j = i - gap;
            for (; j >= 0; j -= gap) {
                if (v[j] > val)
                    v[j + gap] = v[j];
                else
                    break;
            }
            v[j + gap] = val;
        }
    }
}

void partation(Vector<int> &v, int begin, int end)
{
    if (begin >= end)
        return;
    int l = begin;
    int r = end;
    int val = v[l];
    while (l < r) {
        while (l < r && v[r] >= val)
            r--;
        if (l < r) {
            v[l] = v[r];
            l++;
        }
        while (l < r && v[l] <= val)
            l++;
        if (l < r) {
            v[r] = v[l];
            r--;
        }
    }
    v[l] = val;
    partation(v, begin, l - 1);
    partation(v, l + 1, end);
}

void QuickSort(Vector<int> &v)
{
    partation(v, 0, v.size() - 1);
}

void MergeFunction(Vector<int> &v, int begin, int end)
{
    if (begin == end)
        return;
    int mid = (begin + end) / 2;
    MergeFunction(v, begin, mid);
    MergeFunction(v, mid + 1, end);
    int p = begin, q = mid + 1;
    Vector<int> t;
    while (p <= mid && q <= end) {
        if (v[p] <= v[q]) {
            t.push_back(v[p]);
            p++;
        } else {
            t.push_back(v[q]);
            q++;
        }
    }
    if (p <= mid) {
        while (p <= mid) {
            t.push_back(v[p]);
            p++;
        }
    } else {
        while (q <= end) {
            t.push_back(v[q]);
            q++;
        }
    }

    for (int i = 0; i < t.size(); i++)
        v[begin + i] = t[i];
}

void MergeSort(Vector<int> &v)
{
    MergeFunction(v, 0, v.size() - 1);
}

void HeapDown(Vector<int> &v, int idx, int size)
{
    int val = v[idx];
    while (idx < size / 2) {
        int child = 2 * idx + 1;
        if (child + 1 < size && v[child] < v[child + 1])
            child += 1;
        if (val < v[child]) {
            v[idx] = v[child];
            idx = child;
        } else
            break;
    }
    v[idx] = val;
}

void HeapSort(Vector<int> &v)
{
    for (int i = v.size() / 2 - 1; i >= 0; i--)
        HeapDown(v, i, v.size());

    int last = v.size() - 1;
    do {
        swap(v[0], v[last]);
        last--;
        HeapDown(v, 0, last + 1);
    } while (last > 0);
}

#endif //TEST_SORT_H

//
// Created by dyx on 2025/12/16.
//

#ifndef TEST_HASH_H
#define TEST_HASH_H
#include <filesystem>
#include <iostream>

class HashTable
{
    enum Status { Using, Unuse, Delete };

    struct node
    {
        int data;
        Status sta;
        node(int val = 0, Status s = Unuse)
            : data(val)
            , sta(s)
        {}
    };

private:
    node *_ptr;
    int _capacity;
    int _index;
    int _size;
    double _load_factor;

    static const int ARR_SIZE = 10;
    static int arr[ARR_SIZE];

    void expand()
    {
        if (_index == ARR_SIZE - 1)
            throw "HashTable is large";
        node *p = new node[arr[_index + 1]];
        _index++;
        int cap = _capacity;
        _capacity = arr[_index];
        for (int i = 0; i < cap; i++) {
            if (_ptr[i].sta == Using) {
                int pos = Hash(_ptr[i].data);
                p[pos] = node(_ptr[i].data, Using);
            }
        }
        delete[] _ptr;
        _ptr = p;
        _load_factor = _size * 1.0 / _capacity;
    }

public:
    HashTable(int size = arr[0])
        : _load_factor(0)
        , _size(0)
    {
        if (size != arr[0]) {
            int i = 0;
            for (; i < ARR_SIZE; i++) {
                if (size < arr[i]) {
                    size = arr[i];
                    _index = i;
                    break;
                }
            }
            if (i == ARR_SIZE) {
                size = arr[ARR_SIZE - 1];
                _index = ARR_SIZE - 1;
            }
        }

        _ptr = new node[size];
        _capacity = size;
    }
    ~HashTable() { delete[] _ptr; }

    int Hash(int val) { return val % _capacity; }

    bool insert(int key)
    {
        if (_load_factor >= 0.75)
            expand();
        int idx = Hash(key);
        int i = idx;

        do {
            if (_ptr[i].sta != Using) {
                _ptr[i] = node(key, Using);
                _size++;
                _load_factor = _size * 1.0 / _capacity;
                std::cout << load_factor() << "    ";
                show();
                return true;
            }
            i = (i + 1) % _capacity;
        } while (i != idx);

        return false;
    }

    bool remove(int key)
    {
        int idx = Hash(key);
        int i = idx;
        do {
            if (_ptr[i].data == key && _ptr[i].sta == Using) {
                _ptr[i].sta = Delete;
                _size--;
                _load_factor = _size * 1.0 / _capacity;
                std::cout << load_factor() << "    ";
                show();
                return true;
            }
            i = (i + 1) % _capacity;
        } while (i != idx && _ptr[i].sta != Unuse);
        return false;
    }

    bool find(int key)
    {
        int idx = Hash(key);
        int i = idx;
        do {
            if (_ptr[i].data == key && _ptr[i].sta == Using)
                return true;
            i = (i + 1) % _capacity;
        } while (i != idx && _ptr[i].sta != Unuse);
        return false;
    }

    double load_factor() const { return _load_factor; }
    void show() const
    {
        for (int i = 0; i < _capacity; i++) {
            if (_ptr[i].sta == Using)
                std::cout << _ptr[i].data << " ";
        }
        std::cout << std::endl;
    }
};

const int HashTable::ARR_SIZE;
int HashTable::arr[ARR_SIZE] = {3, 7, 23, 47, 97, 251, 443, 991, 1471, 42773};

#endif //TEST_HASH_H

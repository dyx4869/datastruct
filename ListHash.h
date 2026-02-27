//
// Created by dyx on 2025/12/16.
//

#ifndef TEST_LISTHASH_H
#define TEST_LISTHASH_H
#include <iostream>
class ListHash
{
private:
    struct Bucket
    {
        int _key;
        Bucket *_next;
        Bucket(int k = 0)
            : _key(k)
            , _next(nullptr)
        {}
    };

    Bucket *_ptr;
    int _capacity;
    int _size;
    int _index;
    double _load_factor;

    static const int ListHashSize = 10;
    static int ListHashPrime[ListHashSize];

    void expand()
    {
        if (_index == ListHashSize - 1)
            throw "Hash is large";
        _index++;
        Bucket *p = new Bucket[ListHashPrime[_index]];
        int cap = ListHashPrime[_index];
        int size = 0;
        for (int i = 0; i < _capacity; i++) {
            if (_ptr[i]._next != nullptr) {
                Bucket *q = _ptr[i]._next;
                while (q != nullptr) {
                    int idx = q->_key % cap;
                    if (p[idx]._next == nullptr) {
                        p[idx]._next = new Bucket(q->_key);
                        size++;
                    } else {
                        Bucket *t = p[i]._next;
                        while (t->_next != nullptr)
                            t = t->_next;
                        t->_next = new Bucket(q->_key);
                    }
                    q = q->_next;
                }
            }
        }

        for (int i = 0; i < _capacity; i++) {
            if (_ptr[i]._next != nullptr) {
                Bucket *p = _ptr[i]._next;
                while (p != nullptr) {
                    Bucket *q = p;
                    p = p->_next;
                    delete q;
                }
            }
        }
        delete[] _ptr;

        _ptr = p;
        _capacity = cap;
        _size = size;
        _load_factor = _size * 1.0 / _capacity;
    }

public:
    ListHash(int cap = ListHashPrime[0])
        : _size(0)
        , _load_factor(0)
        , _index(0)
    {
        if (cap != ListHashPrime[0]) {
            int i = 0;
            for (; i < ListHashSize; i++) {
                if (cap < ListHashPrime[i]) {
                    _index = i;
                    break;
                }
            }
            if (i == ListHashSize) {
                _index = ListHashSize - 1;
            }
        }

        _capacity = ListHashPrime[_index];
        _ptr = new Bucket[_capacity];
    }
    ~ListHash()
    {
        for (int i = 0; i < _capacity; i++) {
            if (_ptr[i]._next != nullptr) {
                Bucket *p = _ptr[i]._next;
                while (p != nullptr) {
                    Bucket *q = p;
                    p = p->_next;
                    delete q;
                }
            }
        }
        delete[] _ptr;
    }

    bool insert(int key)
    {
        if (_load_factor >= 0.75)
            expand();
        int idx = key % _capacity;
        if (_ptr[idx]._next == nullptr) {
            _ptr[idx]._next = new Bucket(key);
            _size++;
            _load_factor = _size * 1.0 / _capacity;
            return true;
        } else {
            Bucket *p = _ptr[idx]._next;
            while (p->_next != nullptr)
                p = p->_next;
            p->_next = new Bucket(key);
            return true;
        }
        return false;
    }

    bool remove(int key)
    {
        int idx = key % _capacity;
        if (_ptr[idx]._next == nullptr)
            return false;
        Bucket *pre = &_ptr[idx];
        Bucket *p = pre->_next;
        while (p != nullptr) {
            if (p->_key == key) {
                pre->_next = p->_next;
                delete p;
                return true;
            } else {
                pre = p;
                p = p->_next;
            }
        }
        return false;
    }
    bool find(int key)
    {
        int idx = key % _capacity;
        if (_ptr[idx]._next == nullptr)
            return false;

        Bucket *p = _ptr[idx]._next;
        while (p != nullptr) {
            if (p->_key == key)
                return true;
            p = p->_next;
        }
        return false;
    }

    void show() const
    {
        for (int i = 0; i < _capacity; i++) {
            if (_ptr[i]._next != nullptr) {
                std::cout << "///" << i << " :  ";
                Bucket *p = _ptr[i]._next;
                while (p != nullptr) {
                    std::cout << p->_key << " ";
                    p = p->_next;
                }
            }
        }
        std::cout << std::endl;
    }

    double load_factor() const { return _load_factor; }
};
const int ListHash::ListHashSize;
int ListHash::ListHashPrime[ListHashSize] = {3, 7, 23, 47, 97, 251, 443, 991, 1471, 42773};
#endif //TEST_LISTHASH_H

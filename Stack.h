//
// Created by dyx on 2025/12/15.
//

#ifndef TEST_STACK_H
#define TEST_STACK_H

class Stack
{
private:
    int *_p;
    int _capacity;
    int _size;
    void expand(int cap)
    {
        int *ptr = new int[cap];
        for (int i = 0; i < _size; i++)
            ptr[i] = _p[i];
        delete[] _p;
        _p = ptr;
        _capacity = cap;
    }

public:
    Stack(int cap = 10)
        : _p(new int[cap])
        , _capacity(cap)
        , _size(0)
    {}
    ~Stack() { delete[] _p; }

public:
    void push(const int val)
    {
        if (_size == _capacity)
            expand(2 * _capacity);
        _p[_size++] = val;
    }
    void pop()
    {
        if (_size == 0)
            return;
        _size--;
    }
    int top()
    {
        if (_size == 0)
            throw "empty";
        return _p[_size - 1];
    }
    bool empty() const { return _size == 0; }
};
#endif //TEST_STACK_H

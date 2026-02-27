//
// Created by dyx on 2025/12/18.
//

#ifndef TEST_TEST_H
#define TEST_TEST_H

#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
using namespace std;

#define N 10

class base
{
private:
    int first;
    int second;

public:
    explicit base(int a = 0, int b = 0)
        : first(a)
        , second(b)
    {}
    explicit base(const base &val)
    {
        first = val.first;
        second = val.second;
    }
    ~base() {}
    friend ostream &operator<<(ostream &out, base &b);
    bool operator<(const base &it) { return first < it.first; }
    bool operator>(const base &it) { return first > it.first; }

    bool operator<=(const base &it) { return first <= it.first; }
    bool operator>=(const base &it) { return first >= it.first; }

    void operator=(const base &val)
    {
        first = val.first;
        second = val.second;
    }
};

ostream &operator<<(ostream &out, base &b)
{
    out << "first : " << b.first << " second : " << b.second;
    return out;
}

// void *operator new(size_t size)
// {
//     cout << "new" << endl;
//     void *ptr = malloc(size);
//     if (ptr == nullptr)
//         throw std::bad_alloc();
//     return ptr;
// }
//
// void operator delete(void *ptr)
// {
//     cout << "delete" << endl;
//     free(ptr);
// }
//
// void *operator new[](size_t size)
// {
//     cout << "new[]" << endl;
//     void *ptr = malloc(size);
//     if (ptr == nullptr)
//         throw std::bad_alloc();
//     return ptr;
// }
//
// void operator delete[](void *ptr)
// {
//     cout << "delete[]" << endl;
//     free(ptr);
// }

void ofun(const int &val)
{
    cout << "int &" << endl;
}

void ofun(int &&val)
{
    cout << "int &&" << endl;
}
template<typename Ty>
void otherfun(Ty &&val)
{
    ofun(forward<Ty>(val));
}

#endif //TEST_TEST_H

//
// Created by dyx on 2025/12/20.
//

#ifndef TEST_MYSTRING_H
#define TEST_MYSTRING_H
#include <iostream>
#include <string.h>

class Mystring
{
private:
    char *_ptr;

public:
    friend std::ostream &operator<<(std::ostream &out, Mystring &str);
    friend Mystring operator+(const Mystring &l, const Mystring &r);
    Mystring()
    {
        std::cout << "Mystring()" << std::endl;
        _ptr = new char('\0');
    }
    Mystring(const char *str)
    {
        std::cout << "Mystring(const char *)" << std::endl;
        _ptr = new char[strlen(str) + 1];
        strcpy(_ptr, str);
    }

    Mystring(const Mystring &str)
    {
        std::cout << "Mystring(const Mystring &)" << std::endl;
        _ptr = new char[strlen(str._ptr) + 1];
        strcpy(_ptr, str._ptr);
    }
    Mystring(Mystring &&str)
    {
        std::cout << "Mystring(Mystring &&)" << std::endl;
        _ptr = str._ptr;
        str._ptr = nullptr;
    }
    ~Mystring()
    {
        std::cout << "~Mystring()" << std::endl;
        delete[] _ptr;
    }

    // Mystring operator+(const Mystring &l)
    // {
    //     Mystring tep;
    //     delete tep._ptr;
    //     tep._ptr = new char[strlen(_ptr) + strlen(l._ptr) + 1];
    //     strcpy(tep._ptr, _ptr);
    //     strcat(tep._ptr, l._ptr);
    //     return tep;
    // }

    Mystring &operator=(const char *str)
    {
        delete[] _ptr;
        _ptr = new char[strlen(str) + 1];
        strcpy(_ptr, str);
        return *this;
    }

    Mystring &operator=(const Mystring &str)
    {
        if (str._ptr != _ptr) {
            delete[] _ptr;
            _ptr = new char[strlen(str._ptr) + 1];
            strcpy(_ptr, str._ptr);
            return *this;
        }
    }

    Mystring &operator=(Mystring &&str)
    {
        if (str._ptr != _ptr) {
            _ptr = str._ptr;
            str._ptr = nullptr;
            return *this;
        }
    }
};

Mystring operator+(const Mystring &l, const Mystring &r)
{
    // Mystring tep;
    // delete tep._ptr;
    // tep._ptr = new char[strlen(r._ptr) + strlen(l._ptr) + 1];
    // strcpy(tep._ptr, l._ptr);
    // strcat(tep._ptr, r._ptr);
    // return tep;

    char *p = new char[strlen(r._ptr) + strlen(l._ptr) + 1];
    strcpy(p, l._ptr);
    strcat(p, r._ptr);
    Mystring t(p);
    return t;
}

std::ostream &operator<<(std::ostream &out, Mystring &str)
{
    out << str._ptr;
    return out;
}
#endif //TEST_MYSTRING_H

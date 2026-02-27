//
// Created by dyx on 2025/12/21.
//

#ifndef TEST_SMARTPTR_H
#define TEST_SMARTPTR_H

template<typename _Ty>
class PtrCount
{
private:
    _Ty *_ptr;

public:
    int _count;
    PtrCount(_Ty *p = nullptr)
        : _count(0)
        , _ptr(p)
    {
        if (nullptr != p)
            _count = 1;
    }
    void add() { _count++; }
    int sub() { return --_count; }
};

template<typename _Ty>
class csmartptr
{
private:
    _Ty *_ptr;
    PtrCount<_Ty> *_count;

public:
    csmartptr(_Ty *p = nullptr)
        : _ptr(p)
    {
        _count = new PtrCount<_Ty>(_ptr);
    }
    csmartptr(const csmartptr &right)
    {
        _ptr = right._ptr;
        _count = right._count;
        _count->add();
    }
    csmartptr<_Ty> &operator=(const csmartptr &right)
    {
        if (this == &right)
            return *this;
        if (nullptr == _ptr)
            delete _count;
        else {
            if (0 == _count->sub()) {
                delete _ptr;
                delete _count;
            }
        }
        right._count->add();
        _ptr = right._ptr;
        _count = right._count;
        return *this;
    }
    ~csmartptr()
    {
        if (0 == _count->sub()) {
            delete _ptr;
            delete _count;
        }
    }

    int count() const { return _count->_count; }

    _Ty &operator*() { return *_ptr; }
    _Ty *operator->() { return _ptr; }
};
#endif //TEST_SMARTPTR_H

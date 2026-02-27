//
// Created by dyx on 2025/12/15.
//

#ifndef TEST_VECTOR_H
#define TEST_VECTOR_H
#include <iostream>
template<typename _Ty>
struct Allocator
{
    // 开辟空间
    _Ty *allocate(size_t size) { return (_Ty *) malloc(size * sizeof(_Ty)); }
    // 内存释放
    void deallocate(void *ptr) { free(ptr); }
    // 对象构造
    void construct(_Ty *ptr, const _Ty &val) { new (ptr) _Ty(val); }
    void construct(_Ty *ptr, _Ty &&val) { new (ptr) _Ty(std::move(val)); }
    // 对象析构
    void destroy(_Ty *ptr) { ptr->~_Ty(); }
};

template<typename _Ty, typename Alloc = Allocator<_Ty>>
class Vector
{
private:
    Alloc _allocator;
    _Ty *_first;
    _Ty *_last;
    _Ty *_end;

    void expand()
    {
        if (_first == nullptr) {
            _first = _allocator.allocate(1);
            _last = _first;
            _end = _first + 1;
            return;
        }

        int size = _last - _first;
        int cap = _end - _first;
        _Ty *ptr = _allocator.allocate(2 * cap);

        for (int i = 0; i < size; i++) {
            _allocator.construct(ptr + i, *(_first + i));
        }
        for (int i = 0; i < size; i++)
            _allocator.destroy(_first + i);
        _allocator.deallocate(_first);

        _first = ptr;
        _last = _first + size;
        _end = _first + (2 * cap);
    }

public:
    class iterator
    {
    private:
        _Ty *_ptr;

    public:
        iterator(_Ty *p = nullptr)
            : _ptr(p)
        {}
        iterator operator++() { return iterator(++_ptr); }
        iterator operator++(int) { return iterator(_ptr++); }
        bool operator==(const iterator &other) const { return _ptr == other._ptr; }
        bool operator!=(const iterator &other) const { return _ptr != other._ptr; }
        _Ty &operator*() { return *_ptr; }
    };
    _Ty &operator[](int index) { return *(_first + index); }

    Vector()
        : _first(nullptr)
        , _end(nullptr)
        , _last(nullptr)
    {}
    Vector(int cap)
    {
        _first = _allocator.allocate(cap);
        _last = _first;
        _end = _first + cap;
    }
    Vector(const Vector<_Ty> &v)
    {
        int size = v._last - v._first;
        int cap = v._end - v._first;

        _first = _allocator.allocate(cap);
        for (int i = 0; i < size; i++) {
            _allocator.construct(_first + i, *(v._first + i));
        }
        _last = _first + size;
        _end = _first + cap;
    }
    Vector(Vector<_Ty> &&v)
    {
        _first = v._first;
        _last = v._last;
        _end = v._end;
        v._first = v._last = v._end = nullptr;
        if (v._last == nullptr && v._first == nullptr && v._end == nullptr)
            std::cout << "true" << std::endl;
    }
    ~Vector()
    {
        if (_first != nullptr) {
            int size = _last - _first;
            for (int i = 0; i < size; i++)
                _allocator.destroy(_first + i);
            _allocator.deallocate(_first);
        }
    }

    iterator begin() { return iterator(_first); }

    iterator end() { return iterator(_last); }

    // void push_back(const _Ty &val)
    // {
    //     if (_first == nullptr) {
    //         expand();
    //         _allocator.construct(_last, val);
    //         _last++;
    //         return;
    //     }
    //
    //     if (_last == _end)
    //         expand();
    //     _allocator.construct(_last, val);
    //     _last++;
    // }
    //
    // void push_back(_Ty &&val)
    // {
    //     if (_first == nullptr) {
    //         expand();
    //         _allocator.construct(_last, std::move(val));
    //         _last++;
    //         return;
    //     }
    //
    //     if (_last == _end)
    //         expand();
    //     _allocator.construct(_last, std::move(val));
    //     _last++;
    // }
    template<typename ty>
    void push_back(ty &&val)
    {
        if (_first == nullptr) {
            expand();
            _allocator.construct(_last, std::forward<ty>(val));
            _last++;
            return;
        }

        if (_last == _end)
            expand();
        _allocator.construct(_last, std::forward<ty>(val));
        _last++;
    }

    void pop_back()
    {
        if (_first == _last)
            return;
        _allocator.destroy(_last - 1);
        _last--;
    }

    template<typename... A>
    void emplace_back(A &&...arg)
    {
        if (_first == nullptr) {
            expand();
            new (_last) _Ty(std::forward<A>(arg)...);
            _last++;
            return;
        }

        if (_last == _end)
            expand();
        new (_last) _Ty(std::forward<A>(arg)...);
        _last++;
    }
    // template<typename ty>
    // void emplace_back(ty &&arg)
    // {
    //     if (_first == nullptr) {
    //         expand();
    //         new (_last) _Ty(std::forward<_Ty>(arg));
    //         _last++;
    //         return;
    //     }
    //
    //     if (_last == _end)
    //         expand();
    //     new (_last) _Ty(std::forward<_Ty>(arg));
    //     _last++;
    // }

    void reserve(int inc)
    {
        int size = _last - _first;
        int cap = _end - _first;
        _Ty *ptr = _allocator.allocate(size + inc);

        for (int i = 0; i < size; i++) {
            _allocator.construct(ptr + i, *(_first + i));
        }
        for (int i = 0; i < size; i++)
            _allocator.destroy(_first + i);
        _allocator.deallocate(_first);

        _first = ptr;
        _last = _first + size;
        _end = _first + size + inc;
    }

    _Ty &back() const
    {
        if (_first == _last)
            throw "empty";
        return *(_last - 1);
    }

    int size() const
    {
        if (_first == _last)
            return 0;
        return _last - _first;
    }
    bool empty() const
    {
        if (_first == _last)
            return true;
        return false;
    }
    int capacity() const { return _end - _first; }
};
#endif //TEST_VECTOR_H

//
// Created by dyx on 2025/12/17.
//

#ifndef TEST_QUEUE_H
#define TEST_QUEUE_H
#include <iostream>
template<typename _Ty>
struct All
{
    _Ty *allocate(size_t size) { return (_Ty *) malloc(size * sizeof(_Ty)); }
    void deallocate(void *ptr) { free(ptr); }
    void construct(_Ty *ptr, const _Ty &val) { new (ptr) _Ty(val); }
    void destroy(_Ty *ptr) { ptr->~_Ty(); }
};

template<typename _Ty, typename compare = std::less<_Ty>, typename Alloc = All<_Ty>>
class Priority_Queue
{
private:
    _Ty *_first;
    _Ty *_last;
    _Ty *_end;
    Alloc _allocator;
    compare _com;

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

    void HeapUp()
    {
        int size = _last - _first;
        // if (size == 1)
        //     return;
        int child = size - 1;
        _Ty val = _first[child];

        while (child > 0) {
            int parent = (child - 1) / 2;
            if (_com(_first[parent], val)) {
                //if (_first[parent] < val) {
                _first[child] = _first[parent];
                child = parent;
            } else
                break;
        }
        _first[child] = val;
    }

    void HeapDown()
    {
        _Ty val = _first[0];
        int idx = 0;
        int size = _last - _first;
        while (idx < size / 2) {
            int child = idx * 2 + 1;
            if (child + 1 < size && _first[child] < _first[child + 1])
                child += 1;
            if (_com(val, _first[child])) {
                //if (val < _first[child]) {
                _first[idx] = _first[child];
                idx = child;
            } else
                break;
        }
        _first[idx] = val;
    }

public:
    Priority_Queue()
        : _first(nullptr)
        , _end(nullptr)
        , _last(nullptr)
    {}
    Priority_Queue(int cap)
    {
        //_first = new _Ty[cap];
        _first = _allocator.allocate(cap);
        _last = _first;
        _end = _first + cap;
    }

    Priority_Queue(const Priority_Queue &other)
    {
        if (other._first != nullptr) {
            int size = other._last - other._first;
            int cap = other._end - other._first;
            _first = _allocator.allocate(cap);
            for (int i = 0; i < size; i++)
                _allocator.construct(_first + i, *(other._first + i));
        }
    }

    ~Priority_Queue()
    {
        if (_first != _last) {
            int size = _last - _first;
            for (int i = 0; i < size; i++) {
                _allocator.destroy(_first + i);
            }
        }

        _allocator.deallocate(_first);
    }

    void push(const _Ty &val)
    {
        if (_first == _last || _last == _end)
            expand();
        _allocator.construct(_last++, val);
        HeapUp();
    }

    void pop()
    {
        int size = _last - _first;
        _first[0] = _first[size - 1];
        _allocator.destroy(--_last);
        HeapDown();
    }

    _Ty &top() const { return _first[0]; }

    bool empty() { return _first == _last; }

    void show() const
    {
        _Ty *it = _first;
        while (it != _last) {
            std::cout << *it << " ";
            it++;
        }
        std::cout << std::endl;
    }
};

#endif //TEST_QUEUE_H

//
// Created by dyx on 2025/12/15.
//

#ifndef TEST_LIST_H
#define TEST_LIST_H
#include <iostream>

static int new_count = 0;
void *operator new(size_t size)
{
    void *p = malloc(size);
    if (p == nullptr)
        throw std::bad_alloc();
    new_count++;
    //std::cout << " new : " << new_count << std::endl;
    return p;
}
void operator delete(void *p)
{
    new_count--;
    //std::cout << " delete : " << new_count << std::endl;
    free(p);
}
class ListTest
{
private:
    struct node
    {
        int m_data;
        node *m_next;
        node(int data = 0)
            : m_data(data)
            , m_next(nullptr)
        {}
    };
    node *m_head;

public:
    ListTest()
        : m_head(new node)
    {}
    ~ListTest()
    {
        node *p = m_head;
        while (p != nullptr) {
            m_head = m_head->m_next;
            delete p;
            p = m_head;
        }
    }

    void push_back(const int val)
    {
        node *cur = m_head;
        while (cur->m_next != nullptr) {
            cur = cur->m_next;
        }
        cur->m_next = new node(val);
    }

    void push_front(const int val)
    {
        node *p = new node(val);
        p->m_next = m_head->m_next;
        m_head->m_next = p;
    }

    void pop_back()
    {
        if (m_head->m_next == nullptr)
            return;
        node *pre = m_head;
        node *cur = m_head->m_next;
        while (cur->m_next != nullptr) {
            pre = cur;
            cur = cur->m_next;
        }
        pre->m_next = nullptr;
        delete cur;
    }
    void pop_front()
    {
        if (m_head->m_next == nullptr)
            return;
        node *p = m_head->m_next;
        m_head->m_next = p->m_next;
        delete p;
    }
    bool find(const int val)
    {
        node *p = m_head->m_next;
        while (p != nullptr) {
            if (p->m_data == val)
                return true;
            p = p->m_next;
        }
        return false;
    }

    void erase(const int val)
    {
        if (m_head->m_next == nullptr)
            return;
        node *pre = m_head;
        node *cur = m_head->m_next;
        while (cur != nullptr) {
            if (cur->m_data == val) {
                pre->m_next = cur->m_next;
                delete cur;
                return;
            }
            pre = cur;
            cur = cur->m_next;
        }
    }

    //单链表的逆序
    void reserve()
    {
        node *p = m_head->m_next;
        m_head->m_next = nullptr;
        while (p != nullptr) {
            node *q = p;
            p = p->m_next;
            q->m_next = m_head->m_next;
            m_head->m_next = q;
        }
    }
    //求单链表的倒数第K个元素
    //带头节点的单链表，先让两个指针都指向头节点，
    //一个指针先走k步，然后两个指针一起向前走，当第一个指针为nullptr时，第二个指针即为所求
    int getLastK(const int k)
    {
        node *pre = m_head;
        node *cur = m_head;
        for (int i = 0; i < k; i++)
            cur = cur->m_next;
        while (cur != nullptr) {
            pre = pre->m_next;
            cur = cur->m_next;
        }
        std::cout << "last k number : " << pre->m_data << std::endl;
    }

    static node *CircleList(node *m_head)
    {
        node *fast = m_head;
        node *slow = m_head;
        do {
            if (fast == nullptr)
                return nullptr;
            fast = fast->m_next->m_next;
            slow = slow->m_next;

        } while (fast != slow);
        node *p = m_head;
        while (slow != p) {
            slow = slow->m_next;
            p = p->m_next;
        }
        return p;
    }
    node *intersect(node *head1, node *head2)
    {
        node *p1 = head1->m_next;
        int size1 = 0;
        while (p1 != nullptr) {
            size1++;
            p1 = p1->m_next;
        }

        node *p2 = head2->m_next;
        int size2 = 0;
        while (p2 != nullptr) {
            size2++;
            p2 = p2->m_next;
        }

        p1 = head1;
        p2 = head2;
        if (size1 > size2) {
            for (int i = 0; i < size1 - size2; i++)
                p1 = p1->m_next;
        }

        if (size1 < size2) {
            for (int i = 0; i < size2 - size1; i++)
                p2 = p2->m_next;
        }

        while (p1 != p2) {
            if (p1 == nullptr || p2 == nullptr)
                return nullptr;
            p1 = p1->m_next;
            p2 = p2->m_next;
        }
        return p1;
    }

    void show() const
    {
        node *p = m_head->m_next;
        while (p != nullptr) {
            std::cout << p->m_data << " ";
            p = p->m_next;
        }
        std::cout << std::endl;
    }
    bool empty()
    {
        if (m_head->m_next == nullptr)
            return true;
        return false;
    }
};

//typename ListTest::node *ListTest::CircleList(node *m_head);
class CircleList
{
private:
    struct node
    {
        int _data;
        node *_pre;
        node *_next;
        node(int data = 0)
            : _data(data)
            , _pre(nullptr)
            , _next(nullptr)
        {}
    };
    node *_head;

public:
    CircleList()
        : _head(new node)
    {
        _head->_next = _head;
        _head->_pre = _head;
    }
    ~CircleList()
    {
        node *p = _head->_next;
        while (p != _head) {
            _head->_next = p->_next;
            p->_next->_pre = _head;
            delete p;
            p = _head->_next;
        }
        delete p;
    }

    void push_back(const int val)
    {
        node *p = new node(val);
        p->_next = _head;
        p->_pre = _head->_pre;
        p->_pre->_next = p;
        _head->_pre = p;
    }
    void push_front(const int val)
    {
        node *p = new node(val);
        p->_next = _head->_next;
        p->_pre = _head;
        _head->_next = p;
        p->_next->_pre = p;
    }

    void pop_back()
    {
        if (_head->_next == _head)
            return;
        node *p = _head->_pre;
        p->_pre->_next = _head;
        _head->_pre = p->_pre;
        delete p;
    }
    void pop_front()
    {
        if (_head->_next == _head)
            return;
        node *p = _head->_next;
        _head->_next = p->_next;
        p->_next->_pre = _head;
        delete p;
    }

    void show() const
    {
        node *p = _head->_next;
        while (p != _head) {
            std::cout << p->_data << " ";
            p = p->_next;
        }
        std::cout << std::endl;
    }
};

#endif // TEST_LIST_H

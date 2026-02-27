//
// Created by dyx on 2025/12/17.
//

#ifndef TEST_BSTREE_H
#define TEST_BSTREE_H
#include <functional>
#include <iostream>
#include <queue>
template<typename _Ty, typename compare = std::less<_Ty>>
class bstree
{
private:
    struct node
    {
        _Ty _data;
        node *_left;
        node *_right;
        node(_Ty data = _Ty())
            : _data(data)
            , _left(nullptr)
            , _right(nullptr)
        {}
    };

    node *_root;
    compare comp;

private:
    node *insert(node *p, const _Ty &val)
    {
        if (p == nullptr)
            return new node(val);
        if (p->_data == val)
            return p;
        if (comp(val, p->_data))
            p->_left = insert(p->_left, val);
        else
            p->_right = insert(p->_right, val);
        return p;
    }
    node *remove(node *p, const _Ty &val)
    {
        if (p == nullptr)
            return nullptr;
        if (p->_data == val) {
            if (p->_left != nullptr && p->_right != nullptr) {
                node *cur = p->_left;
                while (cur->_right != nullptr)
                    cur = cur->_right;
                p->_data = cur->_data;
                p->_left = remove(p->_left, p->_data);

            } else {
                node *child = p->_left;
                if (child == nullptr)
                    child = p->_right;
                delete p;
                return child;
            }
        } else {
            if (comp(val, p->_data))
                p->_left = remove(p->_left, val);
            else
                p->_right = remove(p->_right, val);
        }
        return p;
    }

    void preorder(node *p)
    {
        if (p == nullptr)
            return;
        std::cout << p->_data << " ";
        preorder(p->_left);
        preorder(p->_right);
    }

    void inorder(node *p)
    {
        if (p == nullptr)
            return;

        inorder(p->_left);
        std::cout << p->_data << " ";
        inorder(p->_right);
    }
    void postorder(node *p)
    {
        if (p == nullptr)
            return;

        postorder(p->_left);
        postorder(p->_right);
        std::cout << p->_data << " ";
    }

    int level(node *p)
    {
        if (p == nullptr)
            return 0;
        int l = level(p->_left);
        int r = level(p->_right);
        return l > r ? l + 1 : r + 1;
    }

    int sequence(node *p)
    {
        if (p == nullptr)
            return 0;
    }
    void sequence(node *p, int i)
    {
        if (p == nullptr)
            return;
        if (1 == i) {
            std::cout << p->_data << " ";
            return;
        }
        sequence(p->_left, i - 1);
        sequence(p->_right, i - 1);
    }

public:
    bstree()
        : _root(nullptr)
    {}

    ~bstree()
    {
        if (_root == nullptr)
            return;
        std::queue<node *> q;
        q.push(_root);
        while (!q.empty()) {
            node *p = q.front();
            q.pop();
            if (p->_left != nullptr)
                q.push(p->_left);
            if (p->_right != nullptr)
                q.push(p->_right);
            delete p;
        }
    }

    void n_insert(const _Ty &val)
    {
        if (_root == nullptr) {
            _root = new node(val);
            return;
        }
        node *pre = nullptr;
        node *p = _root;
        while (p != nullptr) {
            if (val == p->_data)
                return;
            if (comp(val, p->_data)) {
                pre = p;
                p = p->_left;
            } else {
                pre = p;
                p = p->_right;
            }
        }
        p = new node(val);
        if (comp(val, pre->_data))
            pre->_left = p;
        else
            pre->_right = p;
    }
    void n_remove(const _Ty &val)
    {
        node *pre = nullptr;
        node *p = _root;
        while (p != nullptr) {
            if (val == p->_data)
                break;
            if (comp(val, p->_data)) {
                pre = p;
                p = p->_left;
            } else {
                pre = p;
                p = p->_right;
            }
        }

        if (p->_left != nullptr && p->_right != nullptr) {
            pre = p;
            node *cur = p->_left;
            while (cur->_right != nullptr) {
                pre = cur;
                cur = cur->_right;
            }
            p->_data = cur->_data;
            p = cur;
        }

        node *child = p->_left;
        if (child == nullptr)
            child = p->_right;
        if (p == _root) {
            _root = child;
            delete p;
            return;
        }
        if (comp(pre->_data, p->_data))
            pre->_right = child;
        else
            pre->_left = child;

        delete p;
    }
    void n_preorder()
    {
        std::stack<node *> s;
        s.push(_root);
        while (!s.empty()) {
            node *p = s.top();
            s.pop();
            std::cout << p->_data << " ";
            if (p->_right != nullptr)
                s.push(p->_right);
            if (p->_left != nullptr)
                s.push(p->_left);
        }
        std::cout << std::endl;
    }
    void n_inorder()
    {
        std::stack<node *> s;
        node *p = _root;
        do {
            while (p != nullptr) {
                s.push(p);
                p = p->_left;
            }
            p = s.top();
            s.pop();
            std::cout << p->_data << " ";
            p = p->_right;
        } while (!s.empty() || p != nullptr);
        std::cout << std::endl;
    }
    void n_postorder()
    {
        std::stack<node *> s1, s2;
        s1.push(_root);
        while (!s1.empty()) {
            node *p = s1.top();
            s1.pop();
            s2.push(p);
            if (p->_left != nullptr)
                s1.push(p->_left);
            if (p->_right != nullptr)
                s1.push(p->_right);
        }

        while (!s2.empty()) {
            node *p = s2.top();
            s2.pop();
            std::cout << p->_data << " ";
        }
        std::cout << std::endl;
    }
    void n_sequence()
    {
        std::queue<node *> q;
        q.push(_root);
        while (!q.empty()) {
            node *p = q.front();
            q.pop();
            std::cout << p->_data << " ";
            if (p->_left != nullptr)
                q.push(p->_left);
            if (p->_right != nullptr)
                q.push(p->_right);
        }
        std::cout << std::endl;
    }
    void insert(const _Ty &val) { _root = insert(_root, val); }
    void remove(const _Ty &val) { _root = remove(_root, val); }

    void preorder()
    {
        preorder(_root);
        std::cout << std::endl;
    }
    void inorder()
    {
        inorder(_root);
        std::cout << std::endl;
    }
    void postorder()
    {
        postorder(_root);
        std::cout << std::endl;
    }
    void sequence() //层序遍历
    {
        for (int i = 1; i < height() + 1; i++) {
            sequence(_root, i);
        }
        std::cout << std::endl;
    }
    int height() { return level(_root); }
};
#endif //TEST_BSTREE_H

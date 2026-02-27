//
// Created by dyx on 2025/12/18.
//

#ifndef TEST_AVLTREE_H
#define TEST_AVLTREE_H
#include <functional>
#include <iostream>
#include <queue>
template<typename _Ty, typename Compare = std::less<_Ty>>
class avl
{
private:
    struct node
    {
        _Ty _data;
        node *_left;
        node *_right;
        int _height;

        node(_Ty data = _Ty())
            : _data(data)
            , _left(nullptr)
            , _right(nullptr)
            , _height(1)
        {}
    };

    node *_root;
    Compare _com;

private:
    int Height(node *p) { return p == nullptr ? 0 : p->_height; }
    node *left(node *p) { return p == nullptr ? nullptr : p->_left; }
    node *right(node *p) { return p == nullptr ? nullptr : p->_right; }

    node *LeftRotate(node *p)
    {
        node *child = p->_right;
        p->_right = child->_left;
        child->_left = p;

        p->_height = _com(Height(left(p)), Height(right(p))) ? Height(right(p)) + 1
                                                             : Height(left(p)) + 1;
        child->_height = _com(Height(left(child)), Height(right(child))) ? Height(right(child)) + 1
                                                                         : Height(left(child)) + 1;
        return child;
    }

    node *RightRotate(node *p)
    {
        node *child = p->_left;
        p->_left = child->_right;
        child->_right = p;
        p->_height = _com(Height(left(p)), Height(right(p))) ? Height(right(p)) + 1
                                                             : Height(left(p)) + 1;
        child->_height = _com(Height(left(child)), Height(right(child))) ? Height(right(child)) + 1
                                                                         : Height(left(child)) + 1;

        return child;
    }

    node *LeftBalance(node *p)
    {
        //std::cout << "LeftBalance" << std::endl;
        p->_left = LeftRotate(p->_left);
        return RightRotate(p);
    }

    node *RightBalance(node *p)
    {
        p->_right = RightRotate(p->_right);
        return LeftRotate(p);
    }

    node *insert(node *p, const _Ty &val)
    {
        if (p == nullptr)
            return new node(val);
        if (p->_data == val)
            return p;
        if (_com(val, p->_data)) {
            p->_left = insert(p->_left, val);
            if (_com(Height(p->_right), Height(p->_left) - 1)) {
                node *child = p->_left;
                if (_com(Height(child->_left), Height(child->_right)))
                    p = LeftBalance(p);
                else
                    p = RightRotate(p);
            }
        } else {
            p->_right = insert(p->_right, val);
            if (_com(Height(p->_left) + 1, Height(p->_right))) {
                node *child = p->_right;
                if (_com(Height(child->_right), Height(child->_left)))
                    p = RightBalance(p);
                else
                    p = LeftRotate(p);
            }
        }

        p->_height = _com(Height(left(p)), Height(right(p))) ? Height(right(p)) + 1
                                                             : Height(left(p)) + 1;
        return p;
    }

    node *remove(node *p, const _Ty &val)
    {
        if (p == nullptr)
            return nullptr;
        if (p->_data == val) {
            if (p->_left != nullptr && p->_right != nullptr) {
                if (_com(Height(left(p)), Height(right(p)))) {
                    node *cur = p->_right;
                    while (cur->_left != nullptr)
                        cur = cur->_left;
                    p->_data = cur->_data;
                    p->_right = remove(p->_right, p->_data);
                    if (_com(Height(p->_right) + 1, Height(p->_left))) {
                        node *child = p->_left;
                        if (_com(Height(child->_left), Height(child->_right))) {
                            p = LeftBalance(p);
                        } else {
                            p = RightRotate(p);
                        }
                    }

                } else {
                    node *cur = p->_left;
                    while (cur->_right != nullptr)
                        cur = cur->_right;
                    p->_data = cur->_data;
                    p->_left = remove(p->_left, p->_data);
                    if (_com(Height(p->_left) + 1, Height(p->_right))) {
                        node *child = p->_right;
                        if (_com(Height(child->_right), Height(child->_left))) {
                            p = RightBalance(p);
                        } else {
                            p = LeftRotate(p);
                        }
                    }
                }

            } else {
                node *child = p->_left;
                if (child == nullptr)
                    child = p->_right;
                delete p;
                return child;
            }
        } else {
            if (_com(val, p->_data)) {
                p->_left = remove(p->_left, val);
                if (_com(Height(p->_left) + 1, Height(p->_right))) {
                    node *child = p->_right;
                    if (_com(Height(child->_right), Height(child->_left))) {
                        p = RightBalance(p);
                    } else {
                        p = LeftRotate(p);
                    }
                }

            } else {
                p->_right = remove(p->_right, val);
                if (_com(Height(p->_right) + 1, Height(p->_left))) {
                    node *child = p->_left;
                    if (_com(Height(child->_left), Height(child->_right))) {
                        p = LeftBalance(p);
                    } else {
                        p = RightRotate(p);
                    }
                }
            }
        }

        p->_height = _com(Height(left(p)), Height(right(p))) ? Height(right(p)) + 1
                                                             : Height(left(p)) + 1;
        return p;
    }

public:
    avl()
        : _root(nullptr)
    {}
    ~avl()
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

    void insert(const _Ty &val) { _root = insert(_root, val); }
    void remove(const _Ty &val) { _root = remove(_root, val); }
    void sequence()
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
};
#endif //TEST_AVLTREE_H

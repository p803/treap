#include "treap.hpp"

namespace polsl
{
    std::mt19937 _Treap_priority_generator::mt = std::mt19937(time(0));

    _Treap_node_base *
    _Treap_increment(_Treap_node_base *__x)
    {
        if (__x->_M_right != 0)
        {
            __x = __x->_M_right;

            while (__x->_M_left != 0)
            {
                __x = __x->_M_left;
            }
        }
        else
        {
            _Treap_node_base *__y = __x->_M_parent;

            while (__x == __y->_M_right)
            {
                __x = __y;
                __y = __y->_M_parent;
            }

            if (__x->_M_right != __y)
            {
                __x = __y;
            }
        }

        return __x;
    }

    const _Treap_node_base *
    _Treap_increment(const _Treap_node_base *__x)
    {
        return _Treap_increment(const_cast<_Treap_node_base *>(__x));
    }

    _Treap_node_base *
    _Treap_decrement(_Treap_node_base *__x)
    {
        if (__x->_M_parent->_M_parent == __x)
        {
            __x = __x->_M_right;
        }
        else if (__x->_M_left != 0)
        {
            _Treap_node_base *__y = __x->_M_left;

            while (__y->_M_right != 0)
            {
                __y = __y->_M_right;
            }

            __x = __y;
        }
        else
        {
            _Treap_node_base *__y = __x->_M_parent;

            while (__x == __y->_M_left)
            {
                __x = __y;
                __y = __y->_M_parent;
            }

            __x = __y;
        }

        return __x;
    }

    const _Treap_node_base *
    _Treap_decrement(const _Treap_node_base *__x)
    {
        return _Treap_decrement(const_cast<_Treap_node_base *>(__x));
    }

    void
    _Treap_rotate_right(_Treap_node_base *const __x, _Treap_node_base *&__root)
    {
        _Treap_node_base *const __y = __x->_M_left;

        __x->_M_left = __y->_M_right;

        if (__y->_M_right != 0)
        {
            __y->_M_right->_M_parent = __x;
        }

        __y->_M_parent = __x->_M_parent;

        if (__x == __root)
        {
            __root = __y;
        }
        else if (__x == __x->_M_parent->_M_right)
        {
            __x->_M_parent->_M_right = __y;
        }
        else
        {
            __x->_M_parent->_M_left = __y;
        }

        __y->_M_right = __x;
        __x->_M_parent = __y;
    }

    void
    _Treap_rotate_left(_Treap_node_base *const __x, _Treap_node_base *&__root)
    {
        _Treap_node_base *const __y = __x->_M_right;

        __x->_M_right = __y->_M_left;

        if (__y->_M_left != 0)
        {
            __y->_M_left->_M_parent = __x;
        }

        __y->_M_parent = __x->_M_parent;

        if (__x == __root)
        {
            __root = __y;
        }
        else if (__x == __x->_M_parent->_M_left)
        {
            __x->_M_parent->_M_left = __y;
        }
        else
        {
            __x->_M_parent->_M_right = __y;
        }

        __y->_M_left = __x;
        __x->_M_parent = __y;
    }

    void
    _Treap_insert_and_heapify(const bool __insert_left,
                              _Treap_node_base *__x,
                              _Treap_node_base *__p,
                              _Treap_node_base &__header)
    {
        _Treap_node_base *&__root = __header._M_parent;

        __x->_M_parent = __p;
        __x->_M_left = 0;
        __x->_M_right = 0;
        __x->_M_priority = _Treap_priority_generator::_S_get();

        if (__insert_left)
        {
            __p->_M_left = __x;

            if (__p == &__header)
            {
                __header._M_parent = __x;
                __header._M_right = __x;
            }
            else if (__p == __header._M_left)
            {
                __header._M_left = __x;
            }
        }
        else
        {
            __p->_M_right = __x;

            if (__p == __header._M_right)
            {
                __header._M_right = __x;
            }
        }

        while (__x != __root)
        {
            if (__x->_M_priority < __x->_M_parent->_M_priority)
            {
                break;
            }
            else
            {
                if (__x == __x->_M_parent->_M_left)
                {
                    _Treap_rotate_right(__x->_M_parent, __root);
                }
                else
                {
                    _Treap_rotate_left(__x->_M_parent, __root);
                }
            }
        }
    }

    _Treap_node_base *
    _Treap_heapify_for_erase(_Treap_node_base *const __z, _Treap_node_base &__header)
    {
        _Treap_node_base *&__root = __header._M_parent;
        _Treap_node_base *&__leftmost = __header._M_left;
        _Treap_node_base *&__rightmost = __header._M_right;

        while (__z->_M_left || __z->_M_right)
        {
            if (__z->_M_left == 0)
            {
                _Treap_rotate_left(__z, __root);
            }
            else if (__z->_M_right == 0)
            {
                _Treap_rotate_right(__z, __root);
            }
            else
            {
                if (__z->_M_left->_M_priority > __z->_M_right->_M_priority)
                {
                    _Treap_rotate_right(__z, __root);
                }
                else
                {
                    _Treap_rotate_left(__z, __root);
                }
            }
        }

        if (__leftmost == __z)
        {
            __leftmost = __z->_M_parent;
        }

        if (__rightmost == __z)
        {
            __rightmost = __z->_M_parent;
        }

        if (__root == __z)
        {
            __root = 0;
        }
        else
        {
            if (__z == __z->_M_parent->_M_left)
            {
                __z->_M_parent->_M_left = 0;
            }
            else
            {
                __z->_M_parent->_M_right = 0;
            }
        }

        return __z;
    }

} // namespace polsl

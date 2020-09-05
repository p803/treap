#include <cstddef>
#include <memory>
#include <functional>
#include <random>

#ifndef __POLSL_TREAP_HPP
#define __POLSL_TREAP_HPP

namespace polsl
{
    struct _Treap_node_base
    {
        typedef _Treap_node_base *_Base_ptr;
        typedef const _Treap_node_base *_Const_Base_ptr;

        uint_fast32_t _M_priority;
        _Base_ptr _M_left;
        _Base_ptr _M_right;
        _Base_ptr _M_parent;

        static _Base_ptr
        _S_minimum(_Base_ptr __x)
        {
            while (__x->_M_left != 0)
            {
                __x = __x->_M_left;
            }

            return __x;
        }

        static _Const_Base_ptr
        _S_minimum(_Const_Base_ptr __x)
        {
            while (__x->_M_left != 0)
            {
                __x = __x->_M_left;
            }

            return __x;
        }

        static _Base_ptr
        _S_maximum(_Base_ptr __x)
        {
            while (__x->_M_right != 0)
            {
                __x = __x->_M_right;
            }

            return __x;
        }

        static _Const_Base_ptr
        _S_maximum(_Const_Base_ptr __x)
        {
            while (__x->_M_right != 0)
            {
                __x = __x->_M_right;
            }

            return __x;
        }
    };

    template <typename _Val>
    struct _Treap_node : public _Treap_node_base
    {
        _Val *
        _M_valptr()
        {
            return std::__addressof(_M_value_field);
        }

        const _Val *
        _M_valptr() const
        {
            return std::__addressof(_M_value_field);
        }

        _Val _M_value_field;
    };

    _Treap_node_base *
    _Treap_increment(_Treap_node_base *__x);

    const _Treap_node_base *
    _Treap_increment(const _Treap_node_base *__x);

    _Treap_node_base *
    _Treap_decrement(_Treap_node_base *__x);

    const _Treap_node_base *
    _Treap_decrement(const _Treap_node_base *__x);

    template <typename _Val>
    struct _Treap_iterator
    {
        typedef _Val value_type;
        typedef _Val &reference;
        typedef _Val *pointer;

        typedef std::bidirectional_iterator_tag iterator_category;
        typedef ptrdiff_t difference_type;

        typedef _Treap_iterator<_Val> _Self;
        typedef _Treap_node_base::_Base_ptr _Base_ptr;
        typedef _Treap_node<_Val> *_Link_type;

        _Treap_iterator()
            : _M_node()
        {
        }

        _Treap_iterator(_Base_ptr __x)
            : _M_node(__x)
        {
        }

        reference
        operator*() const
        {
            return *static_cast<_Link_type>(_M_node)->_M_valptr();
        }

        pointer
        operator->() const
        {
            return static_cast<_Link_type>(_M_node)->_M_valptr();
        }

        _Self &
        operator++()
        {
            _M_node = _Treap_increment(_M_node);

            return *this;
        }

        _Self
        operator++(int)
        {
            _Self __tmp = *this;
            _M_node = _Treap_increment(_M_node);

            return __tmp;
        }

        _Self &
        operator--()
        {
            _M_node = _Treap_decrement(_M_node);

            return *this;
        }

        _Self
        operator--(int)
        {
            _Self __tmp = *this;
            _M_node = _Treap_decrement(_M_node);

            return __tmp;
        }

        bool
        operator==(const _Self &__x) const
        {
            return _M_node == __x._M_node;
        }

        bool
        operator!=(const _Self &__x) const
        {
            return _M_node != __x._M_node;
        }

        _Base_ptr _M_node;
    };

    template <typename _Val>
    struct _Treap_const_iterator
    {
        typedef _Val value_type;
        typedef const _Val &reference;
        typedef const _Val *pointer;

        typedef _Treap_iterator<_Val> iterator;

        typedef std::bidirectional_iterator_tag iterator_category;
        typedef ptrdiff_t difference_type;

        typedef _Treap_const_iterator<_Val> _Self;
        typedef _Treap_node_base::_Const_Base_ptr _Base_ptr;
        typedef const _Treap_node<_Val> *_Link_type;

        _Treap_const_iterator()
            : _M_node()
        {
        }

        _Treap_const_iterator(_Base_ptr __x)
            : _M_node(__x)
        {
        }

        _Treap_const_iterator(const iterator &__it)
            : _M_node(__it._M_node)
        {
        }

        iterator
        _M_const_cast() const
        {
            return iterator(const_cast<typename iterator::_Base_ptr>(_M_node));
        }

        reference
        operator*() const
        {
            return *static_cast<_Link_type>(_M_node)->_M_valptr();
        }

        pointer
        operator->() const
        {
            return static_cast<_Link_type>(_M_node)->_M_valptr();
        }

        _Self &
        operator++()
        {
            _M_node = _Treap_increment(_M_node);

            return *this;
        }

        _Self
        operator++(int)
        {
            _Self __tmp = *this;
            _M_node = _Treap_increment(_M_node);

            return __tmp;
        }

        _Self &
        operator--()
        {
            _M_node = _Treap_decrement(_M_node);

            return *this;
        }

        _Self
        operator--(int)
        {
            _Self __tmp = *this;
            _M_node = _Treap_decrement(_M_node);

            return __tmp;
        }

        bool
        operator==(const _Self &__x) const
        {
            return _M_node == __x._M_node;
        }

        bool
        operator!=(const _Self &__x) const
        {
            return _M_node != __x._M_node;
        }

        _Base_ptr _M_node;
    };

    template <typename _Val>
    inline bool
    operator==(const _Treap_iterator<_Val> &__x,
               const _Treap_const_iterator<_Val> &__y)
    {
        return __x._M_node == __y._M_node;
    }

    template <typename _Val>
    inline bool
    operator!=(const _Treap_iterator<_Val> &__x,
               const _Treap_const_iterator<_Val> &__y)
    {
        return __x._M_node != __y._M_node;
    }

    class _Treap_priority_generator
    {
        static std::mt19937 mt;

    public:
        static uint_fast32_t
        _S_get()
        {
            return mt();
        }
    };

    void
    _Treap_insert_and_heapify(const bool __insert_left, _Treap_node_base *__x, _Treap_node_base *__p, _Treap_node_base &__header);

    _Treap_node_base *
    _Treap_heapify_for_erase(_Treap_node_base *const __z, _Treap_node_base &__header);

    template <typename _Key, typename _Compare = std::less<_Key>, typename _Alloc = std::allocator<_Key>>
    class treap
    {
    protected:
        typedef _Treap_node_base *_Base_ptr;
        typedef const _Treap_node_base *_Const_Base_ptr;
        typedef _Treap_node<_Key> *_Link_type;
        typedef const _Treap_node<_Key> *_Const_Link_type;

    public:
        typedef typename _Alloc::template rebind<_Treap_node<_Key>>::other _Node_allocator;

        typedef _Key _Val;
        typedef _Key key_type;
        typedef _Key value_type;
        typedef _Compare key_compare;
        typedef _Compare value_compare;
        typedef _Alloc allocator_type;

        typedef value_type *pointer;
        typedef const value_type *const_pointer;
        typedef value_type &reference;
        typedef const value_type &const_reference;

        typedef _Treap_const_iterator<value_type> iterator;
        typedef _Treap_const_iterator<value_type> const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    protected:
        typedef _Treap_iterator<value_type> _iterator;
        typedef std::reverse_iterator<_iterator> _reverse_iterator;

    public:
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;

        treap()
            : _M_node_allocator(), _M_key_cmp(), _M_header(), _M_node_count(0)
        {
            _M_initialize();
        }

        treap(const _Compare &__cmp, const allocator_type &__a = allocator_type())
            : _M_node_allocator(__a), _M_key_cmp(__cmp), _M_header(), _M_node_count(0)
        {
            _M_initialize();
        }

        template <typename _InputIterator>
        treap(_InputIterator __first, _InputIterator __last)
            : _M_node_allocator(), _M_key_cmp(), _M_header(), _M_node_count(0)
        {
            _M_initialize();
            _M_insert_unique(__first, __last);
        }

        template <class _InputIterator>
        treap(_InputIterator __first,
              _InputIterator __last,
              const _Compare &__cmp,
              const allocator_type &__a = allocator_type())
            : _M_node_allocator(__a), _M_key_cmp(__cmp), _M_header(), _M_node_count(0)
        {
            _M_initialize();
            _M_insert_unique(__first, __last);
        }

        treap(const treap &__x)
            : _M_node_allocator(__x._M_node_allocator), _M_key_cmp(__x._M_key_cmp), _M_header(), _M_node_count(0)
        {
            _M_initialize();

            if (__x._M_root() != 0)
            {
                _M_root() = _M_copy(__x._M_begin(), _M_end());
                _M_leftmost() = _S_minimum(_M_root());
                _M_rightmost() = _S_maximum(_M_root());
                _M_node_count = __x._M_node_count;
            }
        }

        treap &
        operator=(const treap &__x)
        {
            if (this != &__x)
            {
                _M_erase(_M_begin());
                _M_reset();
                _M_key_cmp = __x._M_key_cmp;

                if (__x._M_root() != 0)
                {
                    _M_root() = _M_copy(__x._M_begin(), _M_end());
                    _M_leftmost() = _S_minimum(_M_root());
                    _M_rightmost() = _S_maximum(_M_root());
                    _M_node_count = __x._M_node_count;
                }
            }
        }

        ~treap()
        {
            _M_erase(_M_begin());
        }

    protected:
        void
        _M_initialize()
        {
            _M_header._M_priority = 0;
            _M_header._M_parent = 0;
            _M_header._M_left = &_M_header;
            _M_header._M_right = &_M_header;
        }

        void
        _M_reset()
        {
            _M_header._M_parent = 0;
            _M_header._M_left = &_M_header;
            _M_header._M_right = &_M_header;
            _M_node_count = 0;
        }

        _Base_ptr &
        _M_root()
        {
            return _M_header._M_parent;
        }

        _Const_Base_ptr
        _M_root() const
        {
            return _M_header._M_parent;
        }

        _Base_ptr &
        _M_leftmost()
        {
            return _M_header._M_left;
        }

        _Const_Base_ptr
        _M_leftmost() const
        {
            return _M_header._M_left;
        }

        _Base_ptr &
        _M_rightmost()
        {
            return _M_header._M_right;
        }

        _Const_Base_ptr
        _M_rightmost() const
        {
            return _M_header._M_right;
        }

        _Link_type
        _M_begin()
        {
            return static_cast<_Link_type>(_M_header._M_parent);
        }

        _Const_Link_type
        _M_begin() const
        {
            return static_cast<_Const_Link_type>(_M_header._M_parent);
        }

        _Link_type
        _M_end()
        {
            return reinterpret_cast<_Link_type>(&_M_header);
        }

        _Const_Link_type
        _M_end() const
        {
            return reinterpret_cast<_Const_Link_type>(&_M_header);
        }

        static const_reference
        _S_value(_Const_Link_type __x)
        {
            return *__x->_M_valptr();
        }

        static const _Key &
        _S_key(_Const_Link_type __x)
        {
            return _S_value(__x);
        }

        static _Link_type
        _S_left(_Base_ptr __x)
        {
            return static_cast<_Link_type>(__x->_M_left);
        }

        static _Const_Link_type
        _S_left(_Const_Base_ptr __x)
        {
            return static_cast<_Const_Link_type>(__x->_M_left);
        }

        static _Link_type
        _S_right(_Base_ptr __x)
        {
            return static_cast<_Link_type>(__x->_M_right);
        }

        static _Const_Link_type
        _S_right(_Const_Base_ptr __x)
        {
            return static_cast<_Const_Link_type>(__x->_M_right);
        }

        static const_reference
        _S_value(_Const_Base_ptr __x)
        {
            return *static_cast<_Const_Link_type>(__x)->_M_valptr();
        }

        static const _Key &
        _S_key(_Const_Base_ptr __x)
        {
            return _S_value(__x);
        }

        static _Base_ptr
        _S_minimum(_Base_ptr __x)
        {
            return _Treap_node_base::_S_minimum(__x);
        }

        static _Const_Base_ptr
        _S_minimum(_Const_Base_ptr __x)
        {
            return _Treap_node_base::_S_minimum(__x);
        }

        static _Base_ptr
        _S_maximum(_Base_ptr __x)
        {
            return _Treap_node_base::_S_maximum(__x);
        }

        static _Const_Base_ptr
        _S_maximum(_Const_Base_ptr __x)
        {
            return _Treap_node_base::_S_maximum(__x);
        }

        _Node_allocator _M_node_allocator;
        key_compare _M_key_cmp;
        _Treap_node_base _M_header;
        size_type _M_node_count;

    public:
        //
        // Iterator methods.
        //

        iterator
        begin()
        {
            return iterator(_M_header._M_left);
        }

        reverse_iterator
        rbegin()
        {
            return reverse_iterator(end());
        }

        iterator
        end()
        {
            return iterator(&_M_header);
        }

        reverse_iterator
        rend()
        {
            return reverse_iterator(begin());
        }

    protected:
        _iterator
        _begin()
        {
            return _iterator(_M_header._M_left);
        }

        _reverse_iterator
        _rbegin()
        {
            return _reverse_iterator(_end());
        }

        _iterator
        _end()
        {
            return _iterator(&_M_header);
        }

        _reverse_iterator
        _rend()
        {
            return _reverse_iterator(_begin());
        }

    public:
        const_iterator
        begin() const
        {
            return const_iterator(_M_header._M_left);
        }

        const_reverse_iterator
        rbegin() const
        {
            return const_reverse_iterator(end());
        }

        const_iterator
        end() const
        {
            return const_iterator(&_M_header);
        }

        const_reverse_iterator
        rend() const
        {
            return const_reverse_iterator(begin());
        }

        //
        // Capacity methods.
        //

        bool
        empty() const
        {
            return _M_node_count == 0;
        }

        size_type
        size() const
        {
            return _M_node_count;
        }

        size_type
        max_size() const
        {
            return _M_node_allocator.max_size();
        }

    private:
        _Link_type
        _M_clone_node(_Const_Link_type __x)
        {
            _Link_type __y = _M_create_node(*__x->_M_valptr());

            __y->_M_priority = __x->_M_priority;
            __y->_M_left = 0;
            __y->_M_right = 0;

            return __y;
        }

        void
        _M_erase(_Link_type __x)
        {
            while (__x != 0)
            {
                _M_erase(_S_right(__x));
                _Link_type __y = _S_left(__x);
                _M_drop_node(__x);
                __x = __y;
            }
        }

        _Link_type
        _M_copy(_Const_Link_type __x, _Link_type __p)
        {
            _Link_type __top = _M_clone_node(__x);
            __top->_M_parent = __p;

            try
            {
                if (__x->_M_right)
                {
                    __top->_M_right = _M_copy(_S_right(__x), __top);
                }

                __p = __top;
                __x = _S_left(__x);

                while (__x != 0)
                {
                    _Link_type __y = _M_clone_node(__x);

                    __p->_M_left = __y;
                    __y->_M_parent = __p;

                    if (__x->_M_right)
                    {
                        __y->_M_right = _M_copy(_S_right(__x), __y);
                    }

                    __p = __y;
                    __x = _S_left(__x);
                }
            }
            catch (...)
            {
                _M_erase(__top);
                throw;
            }

            return __top;
        }

        _Link_type
        _M_get_node()
        {
            return _M_node_allocator.allocate(1);
        }

        void
        _M_put_node(_Link_type __x)
        {
            _M_node_allocator.deallocate(__x, 1);
        }

        void
        _M_construct_node(_Link_type __node, const value_type &__v)
        {
            try
            {
                get_allocator().construct(__node->_M_valptr(), __v);
            }
            catch (...)
            {
                _M_put_node(__node);
                throw;
            }
        }

        void
        _M_destroy_node(_Link_type __x)
        {
            get_allocator().destroy(__x->_M_valptr());
        }

        _Link_type
        _M_create_node(const _Val &__v)
        {
            _Link_type __x = _M_get_node();
            _M_construct_node(__x, __v);

            return __x;
        }

        void
        _M_drop_node(_Link_type __x)
        {
            _M_destroy_node(__x);
            _M_put_node(__x);
        }

        _iterator
        _M_insert(_Base_ptr __x, _Base_ptr __p, const _Val &__v)
        {
            const _Key &__k = __v;
            bool __insert_left = (__x != 0 || __p == _M_end() || _M_key_cmp(__k, _S_key(__p)));
            _Link_type __z = _M_create_node(__v);
            _Treap_insert_and_heapify(__insert_left, __z, __p, _M_header);
            ++_M_node_count;

            return _iterator(__z);
        }

        std::pair<_Base_ptr, _Base_ptr>
        _M_get_insert_unique_pos(const key_type &__k)
        {
            typedef std::pair<_Base_ptr, _Base_ptr> _Res;

            _Link_type __x = _M_begin();
            _Link_type __y = _M_end();
            bool __cmp = true;

            while (__x != 0)
            {
                __y = __x;
                __cmp = _M_key_cmp(__k, _S_key(__x));
                __x = __cmp ? _S_left(__x) : _S_right(__x);
            }

            _iterator __j = _iterator(__y);

            if (__cmp)
            {
                if (__j == begin())
                {
                    return _Res(__x, __y);
                }

                --__j;
            }

            if (_M_key_cmp(_S_key(__j._M_node), __k))
            {
                return _Res(__x, __y);
            }

            return _Res(__j._M_node, 0);
        }

        std::pair<_iterator, bool>
        _M_insert_unique(const _Val &__v)
        {
            typedef std::pair<_iterator, bool> _Res;

            std::pair<_Base_ptr, _Base_ptr> __res = _M_get_insert_unique_pos(__v);

            if (__res.second)
            {
                return _Res(_M_insert(__res.first, __res.second, __v), true);
            }

            return _Res(_iterator(__res.first), false);
        }

        std::pair<_Base_ptr, _Base_ptr>
        _M_get_insert_hint_unique_pos(const_iterator __position, const key_type &__k)
        {
            typedef std::pair<_Base_ptr, _Base_ptr> _Res;

            _iterator __pos = __position._M_const_cast();

            if (__pos._M_node == _M_end())
            {
                if (size() > 0 && _M_key_cmp(_S_key(_M_rightmost()), __k))
                {
                    return _Res(0, _M_rightmost());
                }
                else
                {
                    return _M_get_insert_unique_pos(__k);
                }
            }
            else if (_M_key_cmp(__k, _S_key(__pos._M_node)))
            {
                _iterator __before = __pos;

                if (__pos._M_node == _M_leftmost())
                {
                    return _Res(_M_leftmost(), _M_leftmost());
                }
                else if (_M_key_cmp(_S_key((--__before)._M_node), __k))
                {
                    if (_S_right(__before._M_node) == 0)
                    {
                        return _Res(0, __before._M_node);
                    }
                    else
                    {
                        return _Res(__pos._M_node, __pos._M_node);
                    }
                }
                else
                {
                    return _M_get_insert_unique_pos(__k);
                }
            }
            else if (_M_key_cmp(_S_key(__pos._M_node), __k))
            {
                _iterator __after = __pos;

                if (__pos._M_node == _M_rightmost())
                {
                    return _Res(0, _M_rightmost());
                }
                else if (_M_key_cmp(__k, _S_key((++__after)._M_node)))
                {
                    if (_S_right(__pos._M_node) == 0)
                    {
                        return _Res(0, __pos._M_node);
                    }
                    else
                    {
                        return _Res(__after._M_node, __after._M_node);
                    }
                }
                else
                {
                    return _M_get_insert_unique_pos(__k);
                }
            }
            else
            {
                return _Res(__pos._M_node, 0);
            }
        }

        _iterator
        _M_insert_hint_unique(const_iterator __hint, const _Val &__v)
        {
            std::pair<_Base_ptr, _Base_ptr> __res = _M_get_insert_hint_unique_pos(__hint, __v);

            if (__res.second)
            {
                return _M_insert(__res.first, __res.second, __v);
            }

            return _iterator(__res.first);
        }

        template <class _InputIterator>
        void
        _M_insert_unique(_InputIterator __first, _InputIterator __last)
        {
            for (; __first != __last; ++__first)
            {
                _M_insert_hint_unique(end(), *__first);
            }
        }

        _iterator
        _M_lower_bound(_Link_type __x, _Link_type __y, const _Key &__k)
        {
            while (__x != 0)
            {
                if (!_M_key_cmp(_S_key(__x), __k))
                {
                    __y = __x;
                    __x = _S_left(__x);
                }
                else
                {
                    __x = _S_right(__x);
                }
            }

            return _iterator(__y);
        }

        const_iterator
        _M_lower_bound(_Const_Link_type __x, _Const_Link_type __y, const _Key &__k) const
        {
            while (__x != 0)
            {
                if (!_M_key_cmp(_S_key(__x), __k))
                {
                    __y = __x;
                    __x = _S_left(__x);
                }
                else
                {
                    __x = _S_right(__x);
                }
            }

            return const_iterator(__y);
        }

        _iterator
        _M_upper_bound(_Link_type __x, _Link_type __y, const _Key &__k)
        {
            while (__x != 0)
            {
                if (_M_key_cmp(__k, _S_key(__x)))
                {
                    __y = __x;
                    __x = _S_left(__x);
                }
                else
                {
                    __x = _S_right(__x);
                }
            }

            return _iterator(__y);
        }

        const_iterator
        _M_upper_bound(_Const_Link_type __x, _Const_Link_type __y, const _Key &__k) const
        {
            while (__x != 0)
            {
                if (_M_key_cmp(__k, _S_key(__x)))
                {
                    __y = __x;
                    __x = _S_left(__x);
                }
                else
                {
                    __x = _S_right(__x);
                }
            }

            return const_iterator(__y);
        }

        _iterator
        _M_find(const _Key &__k)
        {
            _iterator __j = _M_lower_bound(_M_begin(), _M_end(), __k);

            if (__j == end() || _M_key_cmp(__k, _S_key(__j._M_node)))
            {
                return _end();
            }

            return __j;
        }

        const_iterator
        _M_find(const _Key &__k) const
        {
            const_iterator __j = _M_lower_bound(_M_begin(), _M_end(), __k);

            if (__j == end() || _M_key_cmp(__k, _S_key(__j._M_node)))
            {
                return end();
            }

            return __j;
        }

        void
        _M_erase_aux(const_iterator __position)
        {
            _Link_type __y = static_cast<_Link_type>(_Treap_heapify_for_erase(const_cast<_Base_ptr>(__position._M_node), _M_header));
            _M_drop_node(__y);
            --_M_node_count;
        }

        void
        _M_erase_aux(const_iterator __first, const_iterator __last)
        {
            if (__first == begin() && __last == end())
            {
                clear();
            }
            else
            {
                while (__first != __last)
                {
                    erase(__first++);
                }
            }
        }

    public:
        //
        // Modifier methods.
        //

        void
        clear()
        {
            _M_erase(_M_begin());
            _M_reset();
        }

        std::pair<iterator, bool>
        insert(const value_type &__x)
        {
            std::pair<_iterator, bool> __res = _M_insert_unique(__x);

            return std::pair<iterator, bool>(__res.first, __res.second);
        }

        iterator
        insert(iterator __hint, const value_type &__x)
        {
            return _M_insert_hint_unique(__hint, __x);
        }

        template <typename _InputIterator>
        void
        insert(_InputIterator __first, _InputIterator __last)
        {
            _M_insert_unique(__first, __last);
        }

        void
        erase(const_iterator __position)
        {
            _M_erase_aux(__position);
        }

        void
        erase(const_iterator __first, const_iterator __last)
        {
            _M_erase_aux(__first, __last);
        }

        size_type
        erase(const key_type &__k)
        {
            _iterator __j = _M_find(__k);
            const size_type __old_size = size();

            if (__j != end())
            {
                _M_erase_aux(__j);
            }

            return __old_size - size();
        }

        void
        swap(treap &__t)
        {
            if (_M_root() == 0)
            {
                if (__t._M_root() != 0)
                {
                    _M_root() = __t._M_root();
                    _M_leftmost() = __t._M_leftmost();
                    _M_rightmost() = __t._M_rightmost();
                    _M_root()->_M_parent = _M_end();
                    _M_node_count = __t._M_node_count;

                    __t._M_reset();
                }
            }
            else if (__t._M_root() == 0)
            {
                __t._M_root() = _M_root();
                __t._M_leftmost() = _M_leftmost();
                __t._M_rightmost() = _M_rightmost();
                __t._M_root()->_M_parent = __t.end();
                __t._M_node_count = _M_node_count;

                _M_reset();
            }
            else
            {
                std::swap(_M_root(), __t._M_root());
                std::swap(_M_leftmost(), __t._M_leftmost());
                std::swap(_M_rightmost(), __t._M_rightmost());

                _M_root()->_M_parent = _M_end();
                __t._M_root()->_M_parent = __t._M_end();
                std::swap(_M_node_count, __t._M_node_count);
            }

            std::swap(_M_key_cmp, __t._M_key_cmp);

            if (_M_node_allocator != __t._M_node_allocator)
            {
                std::swap(_M_node_allocator, __t._M_node_allocator);
            }
        }

        //
        // Lookup methods.
        //

        size_type
        count(const key_type &__k) const
        {
            _Const_Link_type __x = _M_begin();
            _Const_Link_type __y = _M_end();

            while (__x != 0)
            {
                if (!_M_key_cmp(_S_key(__x), __k))
                {
                    __y = __x;
                    __x = _S_left(__x);
                }
                else
                {
                    __x = _S_right(__x);
                }
            }

            return (__y == _M_end() || _M_key_cmp(__k, _S_key(__y))) ? 0 : 1;
        }

        iterator
        find(const key_type &__k)
        {
            return _M_find(__k);
        }

        const_iterator
        find(const key_type &__k) const
        {
            return _M_find(__k);
        }

        std::pair<iterator, iterator>
        equal_range(const key_type &__k)
        {
            _Link_type __x = _M_begin();
            _Link_type __y = _M_end();

            while (__x != 0)
            {
                if (_M_key_cmp(_S_key(__x), __k))
                {
                    __x = _S_right(__x);
                }
                else if (_M_key_cmp(__k, _S_key(__x)))
                {
                    __y = __x;
                    __x = _S_left(__x);
                }
                else
                {
                    return std::pair<iterator, iterator>(iterator(__x), _M_upper_bound(_S_right(__x), __y, __k));
                }
            }

            return std::pair<iterator, iterator>(iterator(__y), iterator(__y));
        }

        std::pair<const_iterator, const_iterator>
        equal_range(const key_type &__k) const
        {
            _Link_type __x = _M_begin();
            _Link_type __y = _M_end();

            while (__x != 0)
            {
                if (_M_key_cmp(_S_key(__x), __k))
                {
                    __x = _S_right(__x);
                }
                else if (_M_key_cmp(__k, _S_key(__x)))
                {
                    __y = __x;
                    __x = _S_left(__x);
                }
                else
                {
                    return std::pair<iterator, iterator>(iterator(__x), _M_upper_bound(_S_right(__x), __y, __k));
                }
            }

            return std::pair<iterator, iterator>(iterator(__y), iterator(__y));
        }

        iterator
        lower_bound(const key_type &__k)
        {
            return _M_lower_bound(_M_begin(), _M_end(), __k);
        }

        const_iterator
        lower_bound(const key_type &__k) const
        {
            return _M_lower_bound(_M_begin(), _M_end(), __k);
        }

        iterator
        upper_bound(const key_type &__k)
        {
            return _M_upper_bound(_M_begin(), _M_end(), __k);
        }

        const_iterator
        upper_bound(const key_type &__k) const
        {
            return _M_upper_bound(_M_begin(), _M_end(), __k);
        }

        //
        // Observers methods.
        //

        key_compare
        key_comp() const
        {
            return _M_key_cmp;
        }

        value_compare
        value_comp() const
        {
            return _M_key_cmp;
        }

        allocator_type
        get_allocator() const
        {
            return allocator_type(_M_node_allocator);
        }
    };
} // namespace polsl

#endif

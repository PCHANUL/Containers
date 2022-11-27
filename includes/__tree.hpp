/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __tree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 13:39:02 by cpak              #+#    #+#             */
/*   Updated: 2022/11/26 19:31:39 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef __TREE_HPP__
#define	__TREE_HPP__
#include <string>
#include <limits.h>
#include "utility.hpp"
#include "pair.hpp"

namespace ft
{

enum dir_t {
	LEFT,
	RIGHT
};

enum color_t {
	BLACK,
	RED
};

#define __left					child[LEFT]
#define __right					child[RIGHT]
#define __rotate_left(node)		__rotate_dir(node, LEFT)
#define __rotate_right(node)	__rotate_dir(node, RIGHT)

// tree에서 다음 node의 주소를 반환합니다.
template <class _NodePtr>
_NodePtr 
__tree_get_next(_NodePtr node)
{
	if (node->__right != nullptr)
		return (__tree_get_min(node->__right));
	while (node != node->parent->__left)
		node = node->parent;
	return (node->parent);
}

// tree에서 이전 node의 주소를 반환합니다.
template <class _NodePtr>
_NodePtr
__tree_get_prev(_NodePtr node)
{
	if (node->__left != nullptr)
		return (__tree_get_max(node->__left));
	while (node != node->parent->__right)
		node = node->parent;
	return (node->parent);
}

// tree에서 가장 왼쪽에 있는 node 주소를 반환합니다.
template <class _NodePtr>
_NodePtr
__tree_get_min(_NodePtr tree)
{
	_NodePtr	node = tree;

	while (node != nullptr && node->__left != nullptr)
		node = node->__left;
	return (node);
}

// tree에서 가장 오른쪽에 있는 node 주소를 반환합니다.
template <class _NodePtr>
_NodePtr
__tree_get_max(_NodePtr tree)
{
	_NodePtr	node = tree;

	while (node != nullptr && node->__right != nullptr)
		node = node->__right;
	return (node);
}

template <class _NodePtr>
int
__child_dir(_NodePtr __n)
{
	return (__n == __n->parent->__right ? RIGHT : LEFT);
}

template <class _NodePtr>
int
__node_color(_NodePtr __n)
{
	if (__n == nullptr)
		return (BLACK);
	else
		return (__n->color);
}

// 두 node의 부모가 교체되어 연결됩니다.
template <class _NodePtr>
_NodePtr
__tree_transplant(_NodePtr __u, _NodePtr __v)
{
	_NodePtr	__u_p = __u->parent;
	_NodePtr	__v_p = __v->parent;
	int			__u_dir = __child_dir(__u);
	int			__v_dir = __child_dir(__v);

	__u_p->child[__u_dir] = __v;
	__v_p->child[__v_dir] = __u; 
	
	__v->parent = __u_p;
	__u->parent = __v_p;
	return (__v);
}

template <class T>
struct __tree_node 
{	 
	__tree_node*	parent;
	__tree_node*	child[2];
	int				color;
	T				key;
};

template <class T, bool B>
class __tree_iter
{

protected:
	typedef	__tree_node<T>										__node;
	typedef typename choose<B, const __node&, __node&>::type	__node_reference;
	typedef typename choose<B, const __node*, __node*>::type	__node_pointer;

public:
	typedef T													value_type;
	typedef typename choose<B, const T&, T&>::type				reference;
	typedef typename choose<B, const T*, T*>::type				pointer;
	typedef ptrdiff_t											difference_type;
	typedef std::bidirectional_iterator_tag						iterator_category;

protected:
	__node_pointer	__n;

public:
	__tree_iter();
	__tree_iter(__node_pointer __x);
	__tree_iter(const __tree_iter<T, false>& __x);
	~__tree_iter();
	__tree_iter&	operator =	(const __tree_iter& __x);

	__node_pointer	base() const;
	reference		operator *	() const;
	pointer			operator ->	() const;
	__tree_iter& 	operator ++	();
	__tree_iter		operator ++	(int);
	__tree_iter&	operator -- ();
	__tree_iter		operator -- (int);
};

template <class T, bool B>
ft::__tree_iter<T, B>::__tree_iter() : __n(nullptr)
{
}

template <class T, bool B>
ft::__tree_iter<T, B>::__tree_iter(__node_pointer __x) : __n(__x)
{
}

template <class T, bool B>
ft::__tree_iter<T, B>::__tree_iter(const __tree_iter<T, false>& __x) : __n(__x.base())
{
}

template <class T, bool B>
ft::__tree_iter<T, B>::~__tree_iter()
{
}

template <class T, bool B>
typename ft::__tree_iter<T, B>::__node_pointer
ft::__tree_iter<T, B>::base() const
{
	return (this->__n);
}

template <class T, bool B>
ft::__tree_iter<T, B>&
ft::__tree_iter<T, B>::operator = (const __tree_iter& __x)
{
	if (__x.__n != this->__n)
		this->__n = __x.__n;
	return (*this);
}

template <class T, bool B>
typename ft::__tree_iter<T, B>::reference
ft::__tree_iter<T, B>::operator *	() const
{
	return (this->__n->key);
}

template <class T, bool B>
typename ft::__tree_iter<T, B>::pointer
ft::__tree_iter<T, B>::operator ->	() const
{
	return (&(this->__n->key));
}

template <class T, bool B>
ft::__tree_iter<T, B>&
ft::__tree_iter<T, B>::operator ++	()
{
	this->__n = __tree_get_next(this->__n);
	return (*this);
}

template <class T, bool B>
ft::__tree_iter<T, B>
ft::__tree_iter<T, B>::operator ++	(int)
{
	ft::__tree_iter<T, B>	tmp(*this);
	++(*this);
	return (tmp);
}

template <class T, bool B>
ft::__tree_iter<T, B>&
ft::__tree_iter<T, B>::operator --	()
{
	this->__n = __tree_get_prev(this->__n);
	return (*this);
}

template <class T, bool B>
ft::__tree_iter<T, B>
ft::__tree_iter<T, B>::operator --	(int)
{
	__tree_iter	tmp(*this);
	--(*this);
	return (tmp);
}

template <class T1, class T2, bool B1, bool B2>
bool
operator == (const ft::__tree_iter<T1, B1>& lhs, const ft::__tree_iter<T2, B2>& rhs)
{
	return (lhs.base() == rhs.base());
}

template <class T1, class T2, bool B1, bool B2>
bool
operator != (const ft::__tree_iter<T1, B1>& lhs, const ft::__tree_iter<T2, B2>& rhs)
{
	return (lhs.base() != rhs.base());
}

template <class T, class Compare, class Alloc>
class __tree
{
	typedef std::allocator_traits<Alloc>								__alloc_traits;
	
public:
	typedef T															value_type;
	typedef	Alloc														allocator_type;
	typedef Compare														key_compare;
	typedef __tree_iter<T, false>										iterator;
	typedef __tree_iter<T, true>										const_iterator;
	typedef	typename __alloc_traits::size_type							size_type;
	typedef	typename __alloc_traits::difference_type					difference_type;
	
private:
	typedef __tree_node<T>												__node;
	typedef __tree_node<const T>										__const_node;
	typedef __node*														__node_pointer;
	typedef __node&														__node_reference;
	typedef typename allocator_type::template rebind<__node>::other		__node_alloc;
	typedef std::allocator_traits<__node_alloc>							__node_alloc_traits;
	
	allocator_type	__alloc;
	__node_alloc	__alloc_node;
	key_compare		__key_comp;
	__node_pointer	__begin_node;
	__node_pointer	__end_node;
	size_type		__size;

public:
	__tree();
	__tree(const key_compare& comp, const allocator_type& alloc);
	__tree(const __tree& __x);
	~__tree();
	__tree&										operator = (const __tree& __x);
	
	iterator									begin();
	const_iterator								begin() const;
	iterator									end();
	const_iterator								end() const;
	void										print() const;
	int											size() const;
	key_compare									get_compare() const;
	ft::pair<iterator, bool>					insert(const value_type& val);
	ft::pair<iterator, bool>					insert(iterator iter, const value_type& val);
	iterator									find(const value_type& val);
	const_iterator								find(const value_type& val) const;
	void										erase(iterator position);
	size_type									erase(const value_type& val);
	void										erase(iterator first, iterator last);
	void										clear();
	void										destroy_node(__node_pointer& __n);
	void										swap(__tree& x);
	size_type									max_size() const;
	iterator									lower_bound(const value_type& val);
	const_iterator								lower_bound(const value_type& val) const;
	iterator									upper_bound(const value_type& val);
	const_iterator								upper_bound(const value_type& val) const;
	ft::pair<iterator, iterator>				equal_range(const value_type& val);
	ft::pair<const_iterator, const_iterator>	equal_range(const value_type& val) const;

private:
	__node*				__root() const;
	__node* 			__create_node(const value_type& val);
	void 				__locate_node(__node_pointer parent, __node_pointer& child, __node_pointer new_node);
	void				__print_tree(const std::string& prefix, const __node* node, bool isLeft) const;
	void				__print_tree(const __node* node) const;
	__node_pointer&		__find_node(__node_pointer& parent, const value_type& val) const;
	__node_pointer&		__find_node(iterator iter, __node_pointer& parent, const value_type& val) const;
	__node_pointer		__delete_node(__node_pointer __n);
	void				__destroy_node(__node_pointer __n);
	void				__destroy_pointer(__node_pointer x, __node_pointer y);

	__node_pointer		__get_grandparent(__node_pointer node) const;
	__node_pointer		__get_uncle(__node_pointer node) const;
	__node_pointer		__get_sibling(__node_pointer node) const;
	__node_pointer		__get_min() const;
	__node_pointer		__get_max() const;
	
	__node_pointer		__rotate_dir(__node_pointer node, int dir);
	void				__swap_node(__node_pointer __x, __node_pointer __y);
	void				__swap_pointer(__node_pointer& __x, __node_pointer& __y);

	void				__insert_fixup_0(__node_pointer node);
	void				__insert_fixup_1(__node_pointer node);
	void				__insert_fixup_2(__node_pointer node);
	void				__insert_fixup_3(__node_pointer node);
	void				__insert_fixup_4(__node_pointer node);

	void				__delete_fixup_0(__node_pointer __n);
	void				__delete_fixup_1(__node_pointer __n);
	void				__delete_fixup_2(__node_pointer __n);
	void				__delete_fixup_3(__node_pointer __n);
	void				__delete_fixup_4(__node_pointer __n);
	void				__delete_fixup_5(__node_pointer __n);
};


template <class T, class Compare, class Alloc>
__tree<T, Compare, Alloc>::__tree() 
	: __alloc(allocator_type()), __alloc_node(__node_alloc()), __key_comp(key_compare()), __size(0)
{
	__end_node = __create_node(value_type());
	__begin_node = __end_node;
}

template <class T, class Compare, class Alloc>
__tree<T, Compare, Alloc>::__tree(const key_compare& comp, const allocator_type& alloc) 
	: __alloc(alloc), __alloc_node(__alloc_node), __key_comp(comp), __size(0)
{
	__end_node = __create_node(value_type());
	__begin_node = __end_node;
}

template <class T, class Compare, class Alloc>
__tree<T, Compare, Alloc>::__tree(const __tree& __x) 
	: __alloc(__x.alloc), __alloc_node(__x.__alloc_node), __key_comp(__x.comp), __size(0)
{
	*this = __x;
}

template <class T, class Compare, class Alloc>
__tree<T, Compare, Alloc>::~__tree() 
{
	destroy_node(__end_node);
}

template <class T, class Compare, class Alloc>
__tree<T, Compare, Alloc>&							
__tree<T, Compare, Alloc>::operator = (const __tree& __x)
{
	this->__alloc = __x.__alloc;
	this->__alloc_node = __x.__alloc_node;
	this->__key_comp = __x.__key_comp;
	clear();
	insert(__x.begin(), __x.end());
}

template <class T, class Compare, class Alloc>
typename __tree<T, Compare, Alloc>::__node_pointer
__tree<T, Compare, Alloc>::__root() const
{
	return (__end_node->__left);
}

template <class T, class Compare, class Alloc>
typename __tree<T, Compare, Alloc>::__node_pointer
__tree<T, Compare, Alloc>::__create_node(const value_type& val)
{
	__node* new_node = __node_alloc_traits::allocate(this->__alloc_node, sizeof(__node));
		
	__alloc_traits::construct(this->__alloc, &new_node->key, val);
	new_node->color = RED;
	new_node->parent = nullptr;
	new_node->__left = nullptr;
	new_node->__right = nullptr;
	return (new_node);
}

template <class T, class Compare, class Alloc>
typename __tree<T, Compare, Alloc>::__node_pointer&
__tree<T, Compare, Alloc>::__find_node(__node_pointer& parent, const value_type& val) const
{
	__node_pointer	node = __root();

	parent = __end_node;
	if (node == nullptr)
		return (parent->__left);
	while (true)
	{
		if (key_compare()(val, node->key))
		{
			if (node->__left == nullptr)
			{
				parent = node;
				return (parent->__left);
			}
			else
				node = node->__left;
		}
		else if (key_compare()(node->key, val))
		{
			if (node->__right == nullptr)
			{
				parent = node;
				return (parent->__right);
			}
			else
				node = node->__right;
		}
		else
		{
			parent = node;
			return (parent);
		}
	}
}

// iter의 전/후의 값이 삽입되어야하는 위치인지 확인하고 아니라면 root에서 시작하여 탐색한다.
template <class T, class Compare, class Alloc>
typename __tree<T, Compare, Alloc>::__node_pointer&
__tree<T, Compare, Alloc>::__find_node(iterator iter, __node_pointer& parent, const value_type& val) const
{
	if (iter == end() || key_compare()(val, *iter))
	{
		iterator	prev = iter;
		if (prev == begin() || key_compare()(*(--prev), val))
		{
			if (iter.base()->__left == nullptr)
			{
				parent = iter.base();
				return (parent->__left);
			}
			else
			{
				parent = prev.base();
				return (parent->__right);
			}
		}
		return (__find_node(parent, val));
	}
	else if (key_compare()(*iter, val))
	{
		iterator	next = iter;
		if (next == --end() || key_compare()(val, *(++next)))
		{
			if (iter.base()->__right == nullptr)
			{
				parent = iter.base();
				return (parent->__right);
			}
			else
			{
				parent = next.base();
				return (parent->__left);
			}
		}
		return (__find_node(parent, val));
	}
	parent = iter.base();
	return (parent);
}

template <class T, class Compare, class Alloc>
void
__tree<T, Compare, Alloc>::__locate_node(__node_pointer parent, __node_pointer& child, __node_pointer new_node)
{
	new_node->__left = nullptr;
	new_node->__right = nullptr;
	new_node->parent = parent;
	child = new_node;
}

template <class T, class Compare, class Alloc>
ft::pair<typename __tree<T, Compare, Alloc>::iterator, bool>
__tree<T, Compare, Alloc>::insert(const value_type& val)
{
	return (insert(end(), val));
}

template <class T, class Compare, class Alloc>
ft::pair<typename __tree<T, Compare, Alloc>::iterator, bool>
__tree<T, Compare, Alloc>::insert(iterator iter, const value_type& val)
{
	__node_pointer	parent = __end_node;
	__node_pointer&	child = __find_node(iter, parent, val);
	__node_pointer 	new_node;
	
	if (child != nullptr)
		return (ft::pair<iterator, bool>(iterator(child), false));
	new_node = __create_node(val);	
	__locate_node(parent, child, new_node);
	if (this->__begin_node->__left != nullptr)
		this->__begin_node = this->__begin_node->__left;
	this->__size++;
	__insert_fixup_0(new_node);
	return (ft::pair<iterator, bool>(iterator(new_node), true));
}

/// @param val 
/// @return val 값을 가진 node의 iterator
template <class T, class Compare, class Alloc>
typename __tree<T, Compare, Alloc>::iterator
__tree<T, Compare, Alloc>::find(const value_type& val)
{
	__node_pointer	__n;

	if (__find_node(__n, val) == nullptr)
		return (iterator(end()));
	return (iterator(__n));
}

template <class T, class Compare, class Alloc>
typename __tree<T, Compare, Alloc>::const_iterator
__tree<T, Compare, Alloc>::find(const value_type& val) const
{
	__node_pointer	__n;

	if (__find_node(__n, val) == nullptr)
		return (const_iterator(end()));
	return (const_iterator(__n));
}

/// @brief __n을 자식 노드로 치환하고, 자식 노드를 반환합니다. 
/// @param __n
/// @return __node_pointer
template <class T, class Compare, class Alloc>
typename __tree<T, Compare, Alloc>::__node_pointer
__tree<T, Compare, Alloc>::__delete_node(__node_pointer __n)
{
	int				__n_dir = __child_dir(__n);
	int				__c_dir = (__n->__right == nullptr ? LEFT : RIGHT);
	__node_pointer	__c = __n->child[__c_dir];

	__n->parent->child[__n_dir] = __c;
	if (__c != nullptr)
		__c->parent = __n->parent;
	return (__c);
}

/// @brief 레드-블랙 트리 규칙에 맞게 tree를 수정합니다.
/// @param __n 삭제된 자리를 대체한 node의 포인터
template <class T, class Compare, class Alloc>
void
__tree<T, Compare, Alloc>::__delete_fixup_0(__node_pointer __n)
{
	if (__n->parent != this->__end_node)
		__delete_fixup_1(__n);
}

template <class T, class Compare, class Alloc>
void
__tree<T, Compare, Alloc>::__delete_fixup_1(__node_pointer __n)
{
	__node_pointer	__s = __get_sibling(__n);
	
	if (__node_color(__s) == RED)
	{
		__n->parent->color = RED;
		__s->color = BLACK;
		if (__n == __n->parent->__left)
			__rotate_left(__n->parent);
		else
			__rotate_right(__n->parent);
	}
	__delete_fixup_2(__n);
}

template <class T, class Compare, class Alloc>
void
__tree<T, Compare, Alloc>::__delete_fixup_2(__node_pointer __n)
{
	__node_pointer	__s = __get_sibling(__n);
	
	if ((__node_color(__n->parent) == BLACK) &&
		(__node_color(__s) == BLACK) &&
		(__node_color(__s->__left) == BLACK) &&
		(__node_color(__s->__right) == BLACK))
	{
		__s->color = RED;
		__delete_fixup_0(__n->parent);	
	}
	else
		__delete_fixup_3(__n);
}

template <class T, class Compare, class Alloc>
void
__tree<T, Compare, Alloc>::__delete_fixup_3(__node_pointer __n)
{
	__node_pointer	__s = __get_sibling(__n);
	
	if ((__node_color(__n->parent) == RED) &&
        (__node_color(__s) == BLACK) &&
        (__node_color(__s->__left) == BLACK) &&
        (__node_color(__s->__right) == BLACK)) 
	{
        __s->color = RED;
        __n->parent->color = BLACK;
    } 
	else
        __delete_fixup_4(__n);
}

template <class T, class Compare, class Alloc>
void
__tree<T, Compare, Alloc>::__delete_fixup_4(__node_pointer __n)
{
	__node_pointer	__s = __get_sibling(__n);
	
	if  (__node_color(__s) == BLACK) 
	{
        if ((__n == __n->parent->__left) &&
            (__node_color(__s->__right) == BLACK) &&
            (__node_color(__s->__left) == RED)) 
		{
            __s->color = RED;
            __s->__left->color = BLACK;
            __rotate_right(__s);
        } 
		else if ((__n == __n->parent->__right) &&
            (__node_color(__s->__left) == BLACK) &&
            (__node_color(__s->__right) == RED)) 
		{
            __s->color = RED;
            __s->__right->color = BLACK;
            __rotate_left(__s);
        }
    }
    __delete_fixup_5(__n);
}

template <class T, class Compare, class Alloc>
void
__tree<T, Compare, Alloc>::__delete_fixup_5(__node_pointer __n)
{
    __node_pointer	__s = __get_sibling(__n);

    __s->color = __n->parent->color;
    __n->parent->color = BLACK;

    if (__n == __n->parent->__left) 
	{
        __s->__right->color = BLACK;
        __rotate_left(__n->parent);
    } 
	else 
	{
        __s->__left->color = BLACK;
        __rotate_right(__n->parent);
    }
}


template <class T, class Compare, class Alloc>
void
__tree<T, Compare, Alloc>::__swap_node(__node_pointer __x, __node_pointer __y)
{
	int	color = __x->color;

	__x->color = __y->color;
	__y->color = color;
	__tree_transplant(__x, __y);

	for (int i=0; i<2; i++)
	{
		__node_pointer	tmp = __x->child[i];
		__x->child[i] = __y->child[i];
		__y->child[i] = tmp;

		if (__x->child[i] != nullptr)
			__x->child[i]->parent = __x;
		if (__y->child[i] != nullptr)
			__y->child[i]->parent = __y;
	}
}

template <class T, class Compare, class Alloc>
void
__tree<T, Compare, Alloc>::erase(iterator position)
{
	__node_pointer	__m = position.base();
	__node_pointer	__c;

	if (__m->__left != nullptr && __m->__right != nullptr)
	{
		__node_pointer	tmp = __tree_get_min(__m->__right);
		__swap_node(__m, tmp);
	}

	__c = __m->child[__m->__right == nullptr ? LEFT : RIGHT];
	if (__c != nullptr)
		__delete_node(__m);
	
	if (__m->color == BLACK)
	{
		if (__c != nullptr && __c->color == RED)
			__c->color = BLACK;
		else
			__delete_fixup_0(__m);
	}

	if (__c == nullptr)
		__delete_node(__m);

	if (__m == this->__begin_node)
		this->__begin_node = __tree_get_min(__end_node);
	__alloc_traits::destroy(this->__alloc, &__m->key);
	__node_alloc_traits::deallocate(this->__alloc_node, __m, 1);
	this->__size--;
}

template <class T, class Compare, class Alloc>
typename __tree<T, Compare, Alloc>::size_type
__tree<T, Compare, Alloc>::erase(const value_type& val)
{
	iterator	iter = find(val);
	if (iter == end())
		return (0);
	erase(iter);
	return (1);
}

template <class T, class Compare, class Alloc>
void
__tree<T, Compare, Alloc>::erase(iterator first, iterator last)
{
	iterator	iter = first;
	
	while (iter != last)
	{
		iter++;
		erase(first);
		first = iter;
	}
}

template <class T, class Compare, class Alloc>
void
__tree<T, Compare, Alloc>::clear()
{
	if (__end_node->__left != nullptr)
	{
		destroy_node(__end_node->__left);
		this->__size = 0;
		this->__begin_node = this->__end_node;
	}
}

template <class T, class Compare, class Alloc>
void
__tree<T, Compare, Alloc>::__swap_pointer(__node_pointer& x, __node_pointer& y)
{
	__node_pointer	tmp = x;
	x = y;
	y = tmp;
}

template <class T, class Compare, class Alloc>
void
__tree<T, Compare, Alloc>::swap(__tree& x)
{
	allocator_type	__tmp_alloc = this->__alloc;
	__node_alloc	__tmp_alloc_node = this->__alloc_node;
	key_compare		__tmp_compare = this->__key_comp;
	size_type		__tmp_size = this->__size;

	this->__alloc = x.__alloc;
	x.__alloc = __tmp_alloc;
	this->__alloc_node = x.__alloc_node;
	x.__alloc_node = __tmp_alloc_node;
	this->__key_comp = x.__key_comp;
	x.__key_comp = __tmp_compare;
	this->__size = x.__size;
	x.__size = __tmp_size;
	__swap_pointer(this->__begin_node, x.__begin_node);
	__swap_pointer(this->__end_node, x.__end_node);
}

template <class T, class Compare, class Alloc>
typename __tree<T, Compare, Alloc>::size_type
__tree<T, Compare, Alloc>::max_size() const
{
	size_type	max = __node_alloc_traits::max_size(this->__alloc_node);
	size_type	diff_max = std::numeric_limits<difference_type>::max();

	return (max < diff_max ? max : diff_max);
}

template <class T, class Compare, class Alloc>
void
__tree<T, Compare, Alloc>::destroy_node(__node_pointer& __n)
{
	if (__n == nullptr)
		return ;
	destroy_node(__n->__left);
	destroy_node(__n->__right);
	__alloc_traits::destroy(this->__alloc, &__n->key);
	__node_alloc_traits::deallocate(this->__alloc_node, __n, 1);
	__n = nullptr;
}

// // 이진 트리를 출력합니다.
// template <class T, class Compare, class Alloc>
// void
// __tree<T, Compare, Alloc>::__print_tree(const std::string& prefix, const __node* node, bool isLeft) const
// {
// 	if(node != nullptr)
// 	{
// 		std::cout << prefix;

// 		std::cout << (isLeft ? "├──" : "└──" );

// 		if (node->color == RED)
// 			std::cout << "\033[1;31m" << node->key.first << "\033[0m" << std::endl;
// 		else
// 			std::cout << node->key.first << std::endl;

// 		__print_tree( prefix + (isLeft ? "│   " : "    "), node->__left, true);
// 		__print_tree( prefix + (isLeft ? "│   " : "    "), node->__right, false);
// 	}
// }

// template <class T, class Compare, class Alloc>
// void
// __tree<T, Compare, Alloc>::__print_tree(const __node* node) const
// {
// 	__print_tree("", node, false);
// }

template <class T, class Compare, class Alloc>
typename __tree<T, Compare, Alloc>::__node*
__tree<T, Compare, Alloc>::__get_grandparent(__node* node) const
{
	if ((node != nullptr) && (node->parent != nullptr))
		return (node->parent->parent);
	else
		return (nullptr);
}

template <class T, class Compare, class Alloc>
typename __tree<T, Compare, Alloc>::__node*
__tree<T, Compare, Alloc>::__get_uncle(__node* node) const
{
	__node*	g_node = __get_grandparent(node);

	if (g_node == nullptr)
		return (nullptr);
	if (node->parent == g_node->__left)
		return (g_node->__right);
	else
		return (g_node->__left);
}

template <class T, class Compare, class Alloc>
typename __tree<T, Compare, Alloc>::__node*
__tree<T, Compare, Alloc>::__get_sibling(__node* node) const
{
	if ((node == nullptr) || (node->parent == nullptr))
		return (nullptr);
	if (node == node->parent->__left)
		return (node->parent->__right);
	else
		return (node->parent->__left);
}

template <class T, class Compare, class Alloc>
typename __tree<T, Compare, Alloc>::__node*
__tree<T, Compare, Alloc>::__get_min() const
{
	if (__end_node->__left == nullptr)
		return (__end_node);
	return (__tree_get_min(__root()));
}

template <class T, class Compare, class Alloc>
typename __tree<T, Compare, Alloc>::__node*
__tree<T, Compare, Alloc>::__get_max() const
{
	if (__end_node->__left == nullptr)
		return (__end_node);
	return (__tree_get_max(__root()));
}

template <class T, class Compare, class Alloc>
typename __tree<T, Compare, Alloc>::__node*
__tree<T, Compare, Alloc>::__rotate_dir(__node* node, int dir)
{
	__node*	p_node = node->parent;
	__node*	c_node = node->child[1-dir];
	__node* gc_node = nullptr;

	if (c_node == nullptr)
		return (node);
	gc_node = c_node->child[dir];
	node->child[1-dir] = gc_node;
	if (gc_node != nullptr)
		gc_node->parent = node;

	c_node->child[dir] = node;
	node->parent = c_node;

	c_node->parent = p_node;
	if (p_node != nullptr)
		p_node->child[node == p_node->__left ? LEFT : RIGHT] = c_node;
	else
	{
		__end_node->__left = c_node;
		c_node->parent = __end_node;
	}
	return (c_node);
}

// node가 root인 경우 : node color를 BLACK으로 변경
template <class T, class Compare, class Alloc>
void
__tree<T, Compare, Alloc>::__insert_fixup_0(__node_pointer node)
{
	if (node->parent == __end_node)
		node->color = BLACK;
	else
		__insert_fixup_1(node);
}

// parent color가 BLACK인 경우 : 종료
template <class T, class Compare, class Alloc>
void
__tree<T, Compare, Alloc>::__insert_fixup_1(__node_pointer node)
{
	if (node->parent->color == BLACK)
		return ;
	else
		__insert_fixup_2(node);
}

// uncle node color가 RED인 경우 : parent, uncle node의 color를 BLACK으로 변경, grand를 RED로 변경
template <class T, class Compare, class Alloc>
void
__tree<T, Compare, Alloc>::__insert_fixup_2(__node_pointer node)
{
	__node_pointer g_node = __get_grandparent(node);
	__node_pointer	u_node = __get_uncle(node);

	if ((u_node != nullptr) && (u_node->color == RED))
	{
		node->parent->color = BLACK;
		u_node->color = BLACK;
		g_node->color = RED;
		__insert_fixup_0(g_node);
	}
	else
		__insert_fixup_3(node);
}

// uncle node color가 BLACK이고, node 연결 형태가 triangle인 경우 : parent node 회전
template <class T, class Compare, class Alloc>
void
__tree<T, Compare, Alloc>::__insert_fixup_3(__node_pointer node)
{
	__node_pointer	g_node = __get_grandparent(node);

	if ((node == node->parent->__right) && (node->parent == g_node->__left))
	{
		__rotate_left(node->parent);
		node = node->__left;
	} 
	else if ((node == node->parent->__left) && (node->parent == g_node->__right))
	{
		__rotate_right(node->parent);
		node = node->__right;
	}
	__insert_fixup_4(node);
}

// uncle node color가 Black이고, node 연결 형태가 line인 경우 : grand node 회전
template <class T, class Compare, class Alloc>
void
__tree<T, Compare, Alloc>::__insert_fixup_4(__node_pointer node)
{
	__node_pointer	g_node = __get_grandparent(node);

	g_node->color = RED;
	node->parent->color = BLACK;
	if (node == node->parent->__right)
		__rotate_left(g_node);
	else
		__rotate_right(g_node);
}

template <class T, class Compare, class Alloc>
typename  __tree<T, Compare, Alloc>::iterator
__tree<T, Compare, Alloc>::begin()
{
	return (iterator(__get_min()));
}

template <class T, class Compare, class Alloc>
typename  __tree<T, Compare, Alloc>::const_iterator
__tree<T, Compare, Alloc>::begin() const
{
	return (const_iterator((__get_min())));
}

template <class T, class Compare, class Alloc>
typename  __tree<T, Compare, Alloc>::iterator
__tree<T, Compare, Alloc>::end()
{
	return (iterator(__end_node));
}

template <class T, class Compare, class Alloc>
typename  __tree<T, Compare, Alloc>::const_iterator
__tree<T, Compare, Alloc>::end() const
{
	return (const_iterator((__end_node)));
}

template <class T, class Compare, class Alloc>
void
__tree<T, Compare, Alloc>::print() const
{
	__print_tree(__end_node);
}

template <class T, class Compare, class Alloc>
int
__tree<T, Compare, Alloc>::size() const
{
	return (__size);
}

template <class T, class Compare, class Alloc>
typename __tree<T, Compare, Alloc>::key_compare
__tree<T, Compare, Alloc>::get_compare() const
{
	return (__key_comp);
}

template <class T, class Compare, class Alloc>
typename __tree<T, Compare, Alloc>::iterator
__tree<T, Compare, Alloc>::lower_bound(const value_type& val)
{
	__node_pointer	__n = __root();
	__node_pointer	__r = __end_node;
	if (__n != nullptr)
	{
		while (__n != nullptr)
		{
			if (!key_compare()(__n->key, val))
			{
				__r = __n;
				__n = __n->__left;
			}
			else
				__n = __n->__right;
		}
	}
	return (iterator(__r));
}

template <class T, class Compare, class Alloc>
typename __tree<T, Compare, Alloc>::const_iterator
__tree<T, Compare, Alloc>::lower_bound(const value_type& val) const
{
	__node_pointer	__n = __root();
	__node_pointer	__r = __end_node;
	if (__n != nullptr)
	{
		while (__n != nullptr)
		{
			if (!key_compare()(__n->key, val))
			{
				__r = __n;
				__n = __n->__left;
			}
			else
				__n = __n->__right;
		}
	}
	return (const_iterator(__r));
}

template <class T, class Compare, class Alloc>
typename __tree<T, Compare, Alloc>::iterator
__tree<T, Compare, Alloc>::upper_bound(const value_type& val)
{
	__node_pointer	__n = __root();
	__node_pointer	__r = __end_node;
	if (__n != nullptr)
	{
		while (__n != nullptr)
		{
			if (key_compare()(val, __n->key))
			{
				__r = __n;
				__n = __n->__left;
			}
			else
				__n = __n->__right;
		}
	}
	return (iterator(__r));
}

template <class T, class Compare, class Alloc>
typename __tree<T, Compare, Alloc>::const_iterator
__tree<T, Compare, Alloc>::upper_bound(const value_type& val) const
{
	__node_pointer	__n = __root();
	__node_pointer	__r = __end_node;
	if (__n != nullptr)
	{
		while (__n != nullptr)
		{
			if (key_compare()(val, __n->key))
			{
				__r = __n;
				__n = __n->__left;
			}
			else
				__n = __n->__right;
		}
	}
	return (const_iterator(__r));
}

template <class T, class Compare, class Alloc>
ft::pair<typename __tree<T, Compare, Alloc>::iterator, typename __tree<T, Compare, Alloc>::iterator>
__tree<T, Compare, Alloc>::equal_range (const value_type& val)
{
	__node_pointer 	__n = __root();
	__node_pointer	__r = __end_node;

	if (__n != nullptr)
	{
		while (__n != nullptr)
		{
			if (key_compare()(val, __n->key))
			{
				__r = __n;
				__n = __n->__left;
			}
			else if (key_compare()(__n->key, val))
				__n = __n->__right;
			else
				return (ft::pair<iterator, iterator>(__n, __r));
		}
	}
	return (ft::pair<iterator, iterator>(__r, __r));
}

template <class T, class Compare, class Alloc>
ft::pair<typename __tree<T, Compare, Alloc>::const_iterator, typename __tree<T, Compare, Alloc>::const_iterator>
__tree<T, Compare, Alloc>::equal_range (const value_type& val) const
{
	__node_pointer 	__n = __root();
	__node_pointer	__r = __end_node;

	if (__n != nullptr)
	{
		while (__n != nullptr)
		{
			if (key_compare()(val, __n->key))
			{
				__r = __n;
				__n = __n->__left;
			}
			else if (key_compare()(__n->key, val))
				__n = __n->__right;
			else
				return (ft::pair<const_iterator, const_iterator>(__n, __r));
		}
	}
	return (ft::pair<const_iterator, const_iterator>(__r, __r));
}

template <class T, class Compare, class Alloc>
bool 
operator == (const __tree<T, Compare, Alloc>& lhs, const __tree<T, Compare, Alloc>& rhs)
{
	return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class T, class Compare, class Alloc>
bool 
operator != (const __tree<T, Compare, Alloc>& lhs, const __tree<T, Compare, Alloc>& rhs)
{
	return (lhs.size() != rhs.size() || !ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class T, class Compare, class Alloc>
bool 
operator <  (const __tree<T, Compare, Alloc>& lhs, const __tree<T, Compare, Alloc>& rhs)
{
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <class T, class Compare, class Alloc>
bool 
operator >  (const __tree<T, Compare, Alloc>& lhs, const __tree<T, Compare, Alloc>& rhs)
{
	return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
}

template <class T, class Compare, class Alloc>
bool 
operator <= (const __tree<T, Compare, Alloc>& lhs, const __tree<T, Compare, Alloc>& rhs)
{
	return (!ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
}

template <class T, class Compare, class Alloc>
bool 
operator >= (const __tree<T, Compare, Alloc>& lhs, const __tree<T, Compare, Alloc>& rhs)
{
	return (!ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

}	// ft

#endif	// __TREE_HPP__

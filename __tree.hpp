/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __tree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 13:39:02 by cpak              #+#    #+#             */
/*   Updated: 2022/11/13 23:56:43 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef __TREE_HPP__
#define	__TREE_HPP__
#include <string>

namespace ft
{

#define LEFT					0
#define RIGHT					1
#define left					child[LEFT]
#define right					child[RIGHT]
#define __rotate_left(node)		__rotate_dir(node, LEFT)
#define __rotate_right(node)	__rotate_dir(node, RIGHT)

enum color_t {
	BLACK,
	RED
};

// tree에서 다음 node의 주소를 반환합니다.
template <class _NodePtr>
_NodePtr 
__tree_next(_NodePtr node)
{
	if (node->right != nullptr)
		return (__tree_min(node->right));
	while (node != node->parent->left)
		node = node->parent;
	return (node->parent);
}

// tree에서 이전 node의 주소를 반환합니다.
template <class _NodePtr>
_NodePtr
__tree_prev(_NodePtr node)
{
	if (node->left != nullptr)
		return (__tree_max(node->left));
	while (node != node->parent->right)
		node = node->parent;
	return (node->parent);
}

// tree에서 가장 왼쪽에 있는 node 주소를 반환합니다.
template <class _NodePtr>
_NodePtr
__tree_min(_NodePtr tree)
{
	_NodePtr	node = tree;

	while (node != nullptr && node->left != nullptr)
		node = node->left;
	return (node);
}

// tree에서 가장 오른쪽에 있는 node 주소를 반환합니다.
template <class _NodePtr>
_NodePtr
__tree_max(_NodePtr tree)
{
	_NodePtr	node = tree;

	while (node != nullptr && node->right != nullptr)
		node = node->right;
	return (node);
}

template <class T>
struct __tree_node 
{	 
	__tree_node*	parent;
	__tree_node*	child[2];
	enum color_t	color;
	T				key;
};

template <class T>
class __tree_iter
{

protected:
	typedef	__tree_node<T>					__node;
	typedef __node*							__node_pointer;
	typedef __node&							__node_reference;

public:
	typedef T								value_type;
	typedef T&								reference;
	typedef T*								pointer;
	typedef ptrdiff_t						difference_type;
	typedef ft::bidirectional_iterator_tag	iterator_category;

protected:
	__node_pointer	__n;

public:
	__tree_iter();
	__tree_iter(__node_pointer __x);
	__tree_iter(const __tree_iter& __x);

	__node_pointer	base() const;
	__tree_iter&	operator =	(const __tree_iter& __x);
	reference		operator *	() const;
	pointer			operator ->	() const;
	__tree_iter& 	operator ++	();
	__tree_iter		operator ++	(int);
	__tree_iter&	operator -- ();
	__tree_iter		operator -- (int);
};

template <class T>
ft::__tree_iter<T>::__tree_iter() : __n(nullptr)
{
}

template <class T>
ft::__tree_iter<T>::__tree_iter(__node_pointer __x) : __n(__x)
{
}

template <class T>
ft::__tree_iter<T>::__tree_iter(const __tree_iter& __x) : __n(__x.__n)
{
}

template <class T>
typename ft::__tree_iter<T>::__node_pointer
ft::__tree_iter<T>::base() const
{
	return (__n);
}

template <class T>
ft::__tree_iter<T>&
ft::__tree_iter<T>::operator = (const __tree_iter& __x)
{
	if (__x.__n != __n)
		__n = __x.__n;
	return (*this);
}

template <class T>
typename ft::__tree_iter<T>::reference
ft::__tree_iter<T>::operator *	() const
{
	return (__n->key);
}

template <class T>
typename ft::__tree_iter<T>::pointer
ft::__tree_iter<T>::operator ->	() const
{
	return (&(__n->key));
}

template <class T>
ft::__tree_iter<T>&
ft::__tree_iter<T>::operator ++	()
{
	__n = __tree_next(__n);
	return (*this);
}

template <class T>
ft::__tree_iter<T>
ft::__tree_iter<T>::operator ++	(int)
{
	ft::__tree_iter<T>	tmp(*this);
	++(*this);
	return (tmp);
}

template <class T>
ft::__tree_iter<T>&
ft::__tree_iter<T>::operator --	()
{
	__n = __tree_prev(__n);
	return (*this);
}

template <class T>
ft::__tree_iter<T>
ft::__tree_iter<T>::operator --	(int)
{
	ft::__tree_iter<T>	tmp(*this);
	--(*this);
	return (tmp);
}

template <class T>
bool
operator == (const ft::__tree_iter<T>& lhs, const ft::__tree_iter<T>& rhs)
{
	return (lhs.base() == rhs.base());
}

template <class T>
bool
operator != (const ft::__tree_iter<T>& lhs, const ft::__tree_iter<T>& rhs)
{
	return (lhs.base() != rhs.base());
}


template <class T, class Compare, class Alloc>
class __tree
{
	
public:
	typedef T															value_type;
	typedef	Alloc														allocator_type;
	typedef Compare														key_compare;
	typedef __tree_iter<T>												iterator;
	typedef __tree_iter<const T>										const_iterator;
	
private:
	typedef std::allocator_traits<allocator_type>						__alloc_traits;
	typedef __tree_node<T>												__node;
	typedef __node*														__node_pointer;
	typedef typename allocator_type::template rebind<__node>::other		__node_alloc;
	typedef std::allocator_traits<__node_alloc>							__node_alloc_traits;
	
	allocator_type	__alloc;
	__node_alloc	__alloc_node;
	key_compare		__key_comp;
	__node_pointer	__end_node;

public:
	__tree();
	__tree(const key_compare& comp, const allocator_type& alloc);
	__tree(const __tree& __x);
	~__tree();
	__tree&						operator = (const __tree& __x);
	
	iterator					begin();
	iterator					end();
	void						print();
	ft::pair<iterator, bool>	insert(const value_type& val);
	ft::pair<iterator, bool>	insert(iterator iter, const value_type& val);
	__node_pointer&				find_node(__node_pointer& parent, const value_type& val);
	__node_pointer&				find_node(iterator iter, __node_pointer& parent, const value_type& val);

	void		delete_node(iterator iter)
	{
		// 
	}

	__node*		__root();
private:
	
	__node* 	__create_node(const value_type& val);
	void 		__locate_node(__node_pointer parent, __node_pointer& child, __node_pointer new_node);
	void		__print_tree(const std::string& prefix, const __node* node, bool isLeft);
	void		__print_tree(const __node* node);

	__node*		__get_grandparent(__node* node);
	__node*		__get_uncle(__node* node);
	__node*		__get_sibling(__node* node);
	__node*		__get_min();
	__node*		__get_max();
	
	__node*		__rotate_dir(__node* node, int dir);

	void		__validate_tree_0(__node* node);
	void		__validate_tree_1(__node* node);
	void		__validate_tree_2(__node* node);
	void		__validate_tree_3(__node* node);
	void		__validate_tree_4(__node* node);
};


template <class T, class Compare, class Alloc>
__tree<T, Compare, Alloc>::__tree() 
	: __alloc(allocator_type()), __alloc_node(__node_alloc()), __key_comp(key_compare())
{
	__end_node = __create_node(T());
}

template <class T, class Compare, class Alloc>
__tree<T, Compare, Alloc>::__tree(const key_compare& comp, const allocator_type& alloc) 
	: __alloc(alloc), __alloc_node(__alloc_node), __key_comp(comp)
{
	__end_node = __create_node(T());
}

template <class T, class Compare, class Alloc>
__tree<T, Compare, Alloc>::~__tree() 
{
	// destroy all nodes
	// 
}

template <class T, class Compare, class Alloc>
typename __tree<T, Compare, Alloc>::__node*
__tree<T, Compare, Alloc>::__root()
{
	return (__end_node->left);
}

template <class T, class Compare, class Alloc>
typename __tree<T, Compare, Alloc>::__node*
__tree<T, Compare, Alloc>::__create_node(const value_type& val)
{
	__node* new_node = __node_alloc_traits::allocate(this->__alloc_node, sizeof(__node));
		
	__alloc_traits::construct(this->__alloc, &new_node->key, val);
	new_node->color = RED;
	return (new_node);
}

template <class T, class Compare, class Alloc>
typename __tree<T, Compare, Alloc>::__node_pointer&
__tree<T, Compare, Alloc>::find_node(__node_pointer& parent, const value_type& val)
{
	__node_pointer	node = __root();

	parent = __end_node;
	if (node == nullptr)
		return (parent->left);
	while (true)
	{
		if (key_compare()(val, node->key))
		{
			if (node->left == nullptr)
			{
				parent = node;
				return (parent->left);
			}
			else
				node = node->left;
		}
		else if (key_compare()(node->key, val))
		{
			if (node->right == nullptr)
			{
				parent = node;
				return (parent->right);
			}
			else
				node = node->right;
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
__tree<T, Compare, Alloc>::find_node(iterator iter, __node_pointer& parent, const value_type& val)
{
	if (iter == end() || key_compare()(val, *iter))
	{
		iterator	prev = iter;
		if (prev == begin() || key_compare()(*(--prev), val))
		{
			if (iter.base()->left == nullptr)
			{
				parent = iter.base();
				return (parent->left);
			}
			else
			{
				parent = prev.base();
				return (parent->right);
			}
		}
		return (find_node(parent, val));
	}
	else if (key_compare()(*iter, val))
	{
		iterator	next = iter;
		if (next == --end() || key_compare()(val, *(++next)))
		{
			if (iter.base()->right == nullptr)
			{
				parent = iter.base();
				return (parent->right);
			}
			else
			{
				parent = next.base();
				return (parent->left);
			}
		}
		return (find_node(parent, val));
	}
	parent = iter.base();
	return (parent);
}

template <class T, class Compare, class Alloc>
void
__tree<T, Compare, Alloc>::__locate_node(__node_pointer parent, __node_pointer& child, __node_pointer new_node)
{
	new_node->left = nullptr;
	new_node->right = nullptr;
	new_node->parent = parent;
	child = new_node;
}

template <class T, class Compare, class Alloc>
ft::pair<typename __tree<T, Compare, Alloc>::iterator, bool>
__tree<T, Compare, Alloc>::insert(const value_type& val)
{
	__node_pointer	parent = __end_node;
	__node_pointer&	child = find_node(parent, val);
	__node_pointer 	new_node;
	
	if (child != nullptr)
		return (ft::pair<iterator, bool>(iterator(child), false));
	new_node = __create_node(val);	
	__locate_node(parent, child, new_node);
	__validate_tree_0(new_node);
	return (ft::pair<iterator, bool>(iterator(new_node), true));
}

template <class T, class Compare, class Alloc>
ft::pair<typename __tree<T, Compare, Alloc>::iterator, bool>
__tree<T, Compare, Alloc>::insert(iterator iter, const value_type& val)
{
	__node_pointer	parent = __end_node;
	__node_pointer&	child = find_node(iter, parent, val);
	__node_pointer 	new_node;
	
	if (child != nullptr)
		return (ft::pair<iterator, bool>(iterator(child), false));
	new_node = __create_node(val);	
	__locate_node(parent, child, new_node);
	__validate_tree_0(new_node);
	return (ft::pair<iterator, bool>(iterator(new_node), true));
}

template <class T, class Compare, class Alloc>
void
__tree<T, Compare, Alloc>::__print_tree(const std::string& prefix, const __node* node, bool isLeft)
{
	if(node != nullptr)
	{
		std::cout << prefix;

		std::cout << (isLeft ? "├──" : "└──" );

		if (node->color == RED)
			std::cout << "\033[1;31m" << node->key.first << "\033[0m" << std::endl;
		else
			std::cout << node->key.first << std::endl;

		__print_tree( prefix + (isLeft ? "│   " : "    "), node->left, true);
		__print_tree( prefix + (isLeft ? "│   " : "    "), node->right, false);
	}
}

template <class T, class Compare, class Alloc>
void
__tree<T, Compare, Alloc>::__print_tree(const __node* node)
{
	__print_tree("", node, false);
}

template <class T, class Compare, class Alloc>
typename __tree<T, Compare, Alloc>::__node*
__tree<T, Compare, Alloc>::__get_grandparent(__node* node)
{
	if ((node != nullptr) && (node->parent != nullptr))
		return (node->parent->parent);
	else
		return (nullptr);
}

template <class T, class Compare, class Alloc>
typename __tree<T, Compare, Alloc>::__node*
__tree<T, Compare, Alloc>::__get_uncle(__node* node)
{
	__node*	g_node = __get_grandparent(node);

	if (g_node == nullptr)
		return (nullptr);
	if (node->parent == g_node->left)
		return (g_node->right);
	else
		return (g_node->left);
}

template <class T, class Compare, class Alloc>
typename __tree<T, Compare, Alloc>::__node*
__tree<T, Compare, Alloc>::__get_sibling(__node* node)
{
	if ((node == nullptr) || (node->parent == nullptr))
		return (nullptr);
	if (node == node->parent->left)
		return (node->parent->right);
	else
		return (node->parent->left);
}

template <class T, class Compare, class Alloc>
typename __tree<T, Compare, Alloc>::__node*
__tree<T, Compare, Alloc>::__get_min()
{
	if (__end_node->left == nullptr)
		return (__end_node);
	return (__tree_min(__root()));
}

template <class T, class Compare, class Alloc>
typename __tree<T, Compare, Alloc>::__node*
__tree<T, Compare, Alloc>::__get_max()
{
	if (__end_node->left == nullptr)
		return (__end_node);
	return (__tree_max(__root()));
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
		p_node->child[node == p_node->left ? LEFT : RIGHT] = c_node;
	else
	{
		__end_node->left = c_node;
		c_node->parent = __end_node;
	}
	return (c_node);
}

// node가 root인 경우 : node color를 BLACK으로 변경
template <class T, class Compare, class Alloc>
void
__tree<T, Compare, Alloc>::__validate_tree_0(__node* node)
{
	if (node->parent == __end_node)
		node->color = BLACK;
	else
		__validate_tree_1(node);
}

// parent color가 BLACK인 경우 : 종료
template <class T, class Compare, class Alloc>
void
__tree<T, Compare, Alloc>::__validate_tree_1(__node* node)
{
	if (node->parent->color == BLACK)
		return ;
	else
		__validate_tree_2(node);
}

// uncle node color가 RED인 경우 : parent, uncle node의 color를 BLACK으로 변경, grand를 RED로 변경
template <class T, class Compare, class Alloc>
void
__tree<T, Compare, Alloc>::__validate_tree_2(__node* node)
{
	__node* g_node = __get_grandparent(node);
	__node*	u_node = __get_uncle(node);

	if ((u_node != nullptr) && (u_node->color == RED))
	{
		node->parent->color = BLACK;
		u_node->color = BLACK;
		g_node->color = RED;
		__validate_tree_0(g_node);
	}
	else
		__validate_tree_3(node);
}

// uncle node color가 BLACK이고, node 연결 형태가 triangle인 경우 : parent node 회전
template <class T, class Compare, class Alloc>
void
__tree<T, Compare, Alloc>::__validate_tree_3(__node* node)
{
	__node*	g_node = __get_grandparent(node);

	if ((node == node->parent->right) && (node->parent == g_node->left))
	{
		__rotate_left(node->parent);
		node = node->left;
	} 
	else if ((node == node->parent->left) && (node->parent == g_node->right))
	{
		__rotate_right(node->parent);
		node = node->right;
	}
	__validate_tree_4(node);
}

// uncle node color가 Black이고, node 연결 형태가 line인 경우 : grand node 회전
template <class T, class Compare, class Alloc>
void
__tree<T, Compare, Alloc>::__validate_tree_4(__node* node)
{
	__node*	g_node = __get_grandparent(node);

	g_node->color = RED;
	node->parent->color = BLACK;
	if (node == node->parent->right)
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
typename  __tree<T, Compare, Alloc>::iterator
__tree<T, Compare, Alloc>::end()
{
	return (iterator(__end_node));
}

template <class T, class Compare, class Alloc>
void
__tree<T, Compare, Alloc>::print()
{
	__print_tree(__end_node);
}

}	// ft

#endif	// __TREE_HPP__

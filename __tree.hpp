/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __tree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 13:39:02 by cpak              #+#    #+#             */
/*   Updated: 2022/11/06 13:56:37 by cpak             ###   ########seoul.kr  */
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

template <class T, class Compare, class Alloc>
class __tree
{

public:
	struct __node {
		__node*			parent;
		__node*			child[2];
		enum color_t	color;
		T				data;
	};

	typedef T															value_type;
	typedef	Alloc														allocator_type;
	typedef Compare														key_compare;
	typedef std::allocator_traits<allocator_type>						__alloc_traits;
	typedef typename allocator_type::template rebind<__node>::other		__node_alloc;
	typedef std::allocator_traits<__node_alloc>							__node_alloc_traits;
	
	allocator_type	__alloc;
	__node_alloc	__alloc_node;
	key_compare		__key_comp;

	__node*			__root;

	__tree();
	__tree(const key_compare& comp, const allocator_type& alloc);

	__node* 	__create_node(const value_type& val);
	void 		__locate_node(__node* new_node);
	void		__print_tree(const std::string& prefix, const __node* node, bool isLeft);
	void		__print_tree(const __node* node);

	__node*		__get_grandparent(__node* node);
	__node*		__get_uncle(__node* node);
	__node*		__get_sibling(__node* node);
	
	__node*		__rotate_dir(__node* node, int dir);

	void		__validate_tree_0(__node* node);
	void		__validate_tree_1(__node* node);
	void		__validate_tree_2(__node* node);
	void		__validate_tree_3(__node* node);
	void		__validate_tree_4(__node* node);
	
	void		insert(const value_type& val);
};


template <class T, class Compare, class Alloc>
__tree<T, Compare, Alloc>::__tree() 
	: __root(nullptr), __alloc(allocator_type()), __alloc_node(__node_alloc()), __key_comp(key_compare())
{}

template <class T, class Compare, class Alloc>
__tree<T, Compare, Alloc>::__tree(const key_compare& comp, const allocator_type& alloc) 
	: __root(nullptr), __alloc(alloc), __alloc_node(__alloc_node), __key_comp(comp)
{}

template <class T, class Compare, class Alloc>
typename __tree<T, Compare, Alloc>::__node*
__tree<T, Compare, Alloc>::__create_node(const value_type& val)
{
	__node* new_node = __node_alloc_traits::allocate(this->__alloc_node, sizeof(__node));
		
	__alloc_traits::construct(this->__alloc, &new_node->data, val);
	new_node->color = RED;
	new_node->parent = NULL;
	return (new_node);
}

template <class T, class Compare, class Alloc>
void
__tree<T, Compare, Alloc>::__locate_node(__node* new_node)
{
	__node* tmp_node = this->__root;

	if (this->__root == nullptr)
		this->__root = new_node;
	else
	{
		int dir = __key_comp(tmp_node->data, new_node->data);
		
		while (tmp_node->child[dir] != nullptr)
		{
			tmp_node = tmp_node->child[dir];
			dir = __key_comp(tmp_node->data, new_node->data);
		}
		tmp_node->child[dir] = new_node;
		new_node->parent = tmp_node;
	}
}

template <class T, class Compare, class Alloc>
void
__tree<T, Compare, Alloc>::__print_tree(const std::string& prefix, const __node* node, bool isLeft)
{
	if( node != nullptr )
	{
		std::cout << prefix;

		std::cout << (isLeft ? "├──" : "└──" );

		if (node->color == RED)
			std::cout << "\033[1;31m" << node->data.first << "\033[0m" << std::endl;
		else
			std::cout << node->data.first << std::endl;

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
__tree<T, Compare, Alloc>::__rotate_dir(__node* node, int dir)
{
	// left
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
		__root = c_node;
	return (c_node);
}

// node가 root인 경우 : node color를 BLACK으로 변경
template <class T, class Compare, class Alloc>
void
__tree<T, Compare, Alloc>::__validate_tree_0(__node* node)
{
	if (node->parent == nullptr)
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
void
__tree<T, Compare, Alloc>::insert(const value_type& val)
{
	__node* new_node = __create_node(val);

	__locate_node(new_node);
	__validate_tree_0(new_node);
	__print_tree(__root);
}


}	// ft

#endif	// __TREE_HPP__

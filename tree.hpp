/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:18:41 by cpak              #+#    #+#             */
/*   Updated: 2022/11/01 19:34:19 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef __TREE_HPP__
#define __TREE_HPP__
#include <memory>
#include "pair.hpp"
#include "utility.hpp"

namespace ft
{

enum color_t {
    BLACK,
    RED
};


template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
class RBtree 
{
private:
    typedef std::allocator_traits<Alloc>        						__alloc_traits;

public:
    struct __node {
        __node*         parent;
        __node*         child[2];
        enum color_t    color;
        T               key;
    };

	typedef T															value_type;
    typedef Compare                             						key_compare;
    typedef Alloc                               						allocator_type;
    typedef __node														node_type;
    typedef typename allocator_type::template rebind<node_type>::other	node_alloc;
	typedef std::allocator_traits<node_alloc>							node_alloc_traits;

    
private:
    node_type*		__root;
    node_alloc		__alloc;

public:
    RBtree(const allocator_type& alloc) : __alloc(alloc)
    {
    }

    void insert(const T& new_value)
    {
        // new_value로 node 생성
        // tree를 확인하며 위치이동
        // RBtree 조건 확인

        node_type* new_node = node_alloc_traits::allocate(this->__alloc, sizeof(node_type));
        new_node->key = new_value;
		new_node->color = RED;

	
		// node의 위치찾기
		node_type* node = this->__root;

		if (!node)
			this->__root = new_node;
		else
		{
			// 현재 노드와 값을 비교하고, 오른쪽 또는 왼쪽을 확인한다.
			// 만약에 확인한 곳이 비어있으면 그곳으로 포인터를 옮긴다.
			// 이를 반복하여 확인한 곳이 null일 때까지 확인한다.

			int dir = value_compare(node->key.first, new_node->key.first);
			
			while (node->child[dir] == nullptr)
			{
				node = node->child[dir];
				dir = value_compare(node->key->first, new_node->key->first);
			}
			node->child[dir] = new_node;
		}


    }

    // void delete(RBnode *tar_node)
    // {
    // }

    // get all items
    // print all items

    // rotate
    // insert
    // delete
    // check



};

} // ft



#endif // __TREE_HPP__

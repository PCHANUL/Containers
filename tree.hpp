/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:18:41 by cpak              #+#    #+#             */
/*   Updated: 2022/10/31 18:27:16 by cpak             ###   ########seoul.kr  */
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


template <class T, class Compare = ft::less<T>, class Alloc = std::allocator<T> >
class RBtree 
{
    
public:
    struct __node {
        __node*         parent;
        __node*         child[2];
        enum color_t    color;
        T               key;
    };

    typedef std::allocator_traits<Alloc>        						__alloc_traits;
    typedef Compare                             						key_compare;
    typedef Alloc                               						allocator_type;
    typedef __node														node_type;
    typedef typename allocator_type::template rebind<node_type>::other	__node_alloc;
	typedef std::allocator_traits<__node_alloc>							__node_alloc_traits;

    
private:
    node_type*		__root;
    __node_alloc	__alloc;

public:
    RBtree(const allocator_type& alloc = allocator_type()) : __alloc(alloc)
    {
    }


    void insert(const T& new_value)
    {
        // new_value로 node 생성
        // tree를 확인하며 위치이동
        // RBtree 조건 확인

        __node* new_node = __node_alloc_traits::allocate(this->__alloc, sizeof(__node));
        new_node->key = new_value;
		new_node->color = RED;


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
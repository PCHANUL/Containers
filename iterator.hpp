/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:03:31 by cpak              #+#    #+#             */
/*   Updated: 2022/10/11 19:35:11 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ITERATOR_HPP__
#define __ITERATOR_HPP__
#include <cstddef>
#include "iterator_traits.hpp"

namespace ft
{

template <class Category, class T, class Distance = ptrdiff_t, 
			class Pointer = T*, class Reference = T&>
struct iterator 
{
	typedef T			value_type;
	typedef Distance	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
	typedef Category	iterator_category;
};

template <class T>
class v_iter
{

public:
	typedef T								value_type;
	typedef ptrdiff_t						difference_type;
	typedef T*								pointer;
	typedef T&								reference;
	typedef ft::random_access_iterator_tag	iterator_category;

protected:
	pointer	__i;

public:
	v_iter(pointer x) : __i(x) {}
	v_iter(const v_iter& iter) : __i(iter.__i) {}
	v_iter& 	operator ++ () { ++__i; return *this; }
	v_iter		operator ++ (int) { v_iter tmp(*this); operator++(); return tmp; }
	bool		operator == (const v_iter& rhs) const { return __i == rhs.__i; }
	bool		operator !=	(const v_iter& rhs) const { return __i != rhs.__i; }
	reference	operator * () { return *__i; }

};

} // namespace ft

#endif // __ITERATOR_HPP__

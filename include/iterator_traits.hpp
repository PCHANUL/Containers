/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:12:08 by cpak              #+#    #+#             */
/*   Updated: 2022/11/24 13:22:49 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ITERATOR_TRAITS_HPP__
#define __ITERATOR_TRAITS_HPP__
#include "type_traits.hpp"

namespace ft
{

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag       : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class _Iter> 
struct iterator_traits
{
	typedef typename _Iter::difference_type		difference_type;
	typedef typename _Iter::value_type			value_type;
	typedef typename _Iter::pointer				pointer;
	typedef typename _Iter::reference			reference;
	typedef typename _Iter::iterator_category	iterator_category;
};

template <class T> 
struct iterator_traits<T*>
{
	typedef ptrdiff_t						difference_type;
	typedef T								value_type;
	typedef T*								pointer;
	typedef T&								reference;
	typedef	ft::random_access_iterator_tag	iterator_category;
};

template <class T> 
struct iterator_traits<const T*>
{
	typedef ptrdiff_t						difference_type;
	typedef T								value_type;
	typedef const T*						pointer;
	typedef const T&						reference;
	typedef	ft::random_access_iterator_tag	iterator_category;
};

template <class T>	struct __ft_is_iterator									: public false_type {};
template <>			struct __ft_is_iterator<input_iterator_tag>				: public true_type {};
template <>			struct __ft_is_iterator<output_iterator_tag>			: public true_type {};
template <>			struct __ft_is_iterator<forward_iterator_tag>			: public true_type {};
template <>			struct __ft_is_iterator<bidirectional_iterator_tag>		: public true_type {};
template <>			struct __ft_is_iterator<random_access_iterator_tag>		: public true_type {};


template <class T>
struct is_iterator
{

private:
	struct __two { char c[2]; };
	template <class __T> static __two __test(...);
	template <class __T> static char __test(typename __T::iterator_category* = 0);
	
public:
	static const bool value = sizeof(__test<T>(0)) == 1;

};

} // namespace ft

#endif // __ITERATOR_TRAITS_HPP__

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:12:08 by cpak              #+#    #+#             */
/*   Updated: 2022/10/14 17:37:52 by cpak             ###   ########seoul.kr  */
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

template <class T>	struct is_iterator	: public __ft_is_iterator< typename itarator_traits<T>::iterator_category > {};

// template <class T> 
// struct is_iterator 
// {
// 	typedef typename T::iterator_category	tag;	// 오류가 발생된다.

// 	// 맴버를 확인하지 않고 확인하는 방법은 sizeof()


// };


// iterator인지 확인
// iterator_traits 클래스에 템플릿 인자를 넣어서 iterator_category 타입이 정의되어 있는지 확인한다. 그러나 만약에 iterator가 아니라면 iterator_category가 정의되어 있지 않으므로 오류가 발생된다.
// 

} // namespace ft
#endif // __ITERATOR_TRAITS_HPP__

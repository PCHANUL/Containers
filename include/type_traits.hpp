/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 18:04:49 by cpak              #+#    #+#             */
/*   Updated: 2022/10/24 17:33:08 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef __TYPE_TRAITS_HPP__
#define __TYPE_TRAITS_HPP__

namespace ft
{

template <class T, T v>
struct integral_constant 
{
	typedef T value_type;
	typedef integral_constant<T, v> type;
	operator T() { return v; }
};

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

template <class T>	struct __ft_is_integral				: public false_type {};
template <>			struct __ft_is_integral<int> 		: public true_type {};
template <>			struct __ft_is_integral<double> 	: public true_type {};

template <class T> struct is_integral : public __ft_is_integral<T> {};


template <bool, typename T = void>
struct enable_if
{};

template <typename T>
struct enable_if<true, T> 
{
    typedef T type;
};

} // namespace ft

#endif // __TYPE_TRAITS_HPP__

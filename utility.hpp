/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:39:29 by cpak              #+#    #+#             */
/*   Updated: 2022/10/31 15:40:41 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef __UTILITY_HPP__
#define __UTILITY_HPP__

namespace ft
{

template <class Arg1, class Arg2, class Result>
struct binary_function {
  typedef Arg1 first_argument_type;
  typedef Arg2 second_argument_type;
  typedef Result result_type;
};

template <class T> 
struct less : binary_function <T, T, bool> {
	bool operator() (const T& x, const T& y) const {
		return (x < y);
	}
};



} // ft

#endif // __UTILITY_HPP__

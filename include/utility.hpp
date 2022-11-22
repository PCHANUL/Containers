/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:39:29 by cpak              #+#    #+#             */
/*   Updated: 2022/11/22 11:27:34 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef __UTILITY_HPP__
#define __UTILITY_HPP__
#include "iterator_traits.hpp"

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


// 범위 [first1, last1)의 요소를 first2에서 시작하는 범위의 요소와 비교합니다.
// 범위 안의 요소가 모두 같은 경우에 true를 반환합니다.
template <class InputIterator1, class InputIterator2>  
bool 
equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2,
		typename ft::enable_if<ft::is_iterator<InputIterator1>::value, InputIterator1>::type* = 0,
		typename ft::enable_if<ft::is_iterator<InputIterator2>::value, InputIterator2>::type* = 0)
{
	for (; first1 != last1; ++first1, ++first2)
		if (!(*first1 == *first2))
			return (false);
	return (true);
}

// 범위 [first1, last1)의 요소를 first2에서 시작하는 범위의 요소와 비교합니다.
// 범위 안의 요소가 모두 같은 경우에 true를 반환합니다.
template <class InputIterator1, class InputIterator2, class BinaryPredicate>
bool 
equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred,
		typename ft::enable_if<ft::is_iterator<InputIterator1>::value, InputIterator1>::type* = 0,
		typename ft::enable_if<ft::is_iterator<InputIterator2>::value, InputIterator2>::type* = 0)
{
	for (; first1 != last1; ++first1, ++first2)
		if (!pred(*first1, *first2))
			return (false);
	return (true);
}

// [first1,last1) 범위가 사전순으로 [first2,last2) 범위보다 작으면 true를 반환합니다.
template <class InputIterator1, class InputIterator2>  
bool 
lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2,
						typename ft::enable_if<ft::is_iterator<InputIterator1>::value, InputIterator1>::type* = 0,
						typename ft::enable_if<ft::is_iterator<InputIterator2>::value, InputIterator2>::type* = 0)
{
	for (; first2 != last2; ++first1, ++first2)
	{
		if (first1 == last1 || *first1 < *first2) 
			return (true);
		else if (*first2 < *first1) 
			return (false);
	}
	return (false);
}

// [first1,last1) 범위가 사전순으로 [first2,last2) 범위보다 작으면 true를 반환합니다.
template <class InputIterator1, class InputIterator2, class Compare>
bool 
lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp,
						typename ft::enable_if<ft::is_iterator<InputIterator1>::value, InputIterator1>::type* = 0,
						typename ft::enable_if<ft::is_iterator<InputIterator2>::value, InputIterator2>::type* = 0)
{
	for (; first2 != last2; ++first1, ++first2)
	{
		if (first1 == last1 || comp(*first1, *first2)) 
			return (true);
		else if (comp(*first2, *first1)) 
			return (false);
	}
	return (false);
}



} // ft

#endif // __UTILITY_HPP__

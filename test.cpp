/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:06:22 by cpak              #+#    #+#             */
/*   Updated: 2022/10/18 19:38:38 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "iterator.hpp"
#include "iterator_traits.hpp"

#include <vector>
#include <memory>

#include "vector.hpp"

void then(bool is_succeed)
{
	if (is_succeed)
		std::cout << "\033[1;32mSucceed\033[0m\n";
	else
		std::cout << "\033[1;31mFailed\033[0m\n";
}

int main(void) {
	std::cout << "< vector >" << std::endl;

	std::cout << "- Default constructor : ";
	{
		ft::vector<int> ft_empty;
		ft::vector<int>::iterator ft_begin = ft_empty.begin();
		ft::vector<int>::iterator ft_end = ft_empty.end();

		then(ft_begin == ft_end);
	}

	std::cout << "- Fill constructor (without val) : ";
	{
		int len = 10;
		ft::vector<int> ft_filled(len);
		ft::vector<int>::iterator ft_begin = ft_filled.begin();
		ft::vector<int>::iterator ft_end = ft_filled.end();
		ft::vector<int>::iterator it = ft_begin;

		for (; it!=ft_end; it++, len--);

		then(ft_begin != ft_end && len == 0);
	}

	std::cout << "- Fill constructor (with val) : ";
	{
		int val = 5;
		int len = 10;
		ft::vector<int> ft_filled(len, val);
		ft::vector<int>::iterator ft_begin = ft_filled.begin();
		ft::vector<int>::iterator ft_end = ft_filled.end();
		ft::vector<int>::iterator it = ft_begin;

		for (; it!=ft_end; it++, len--)
		{
			if (*it != val) 
				break ;
		}

		then(it == ft_end && len == 0);
	} 
	
	std::cout << "- Range constructor : ";
	{
		const int val = 5;
		const int len = 10;
		const int offset = 3;
		ft::vector<int> nums(len, val);
		ft::vector<int> other(10, 7);
		ft::vector<int>::iterator begin = nums.begin();
		ft::vector<int>::iterator end = nums.end() - offset;
		ft::vector<int>::iterator other_end = other.end();

		{
			ft::vector<int> range_nums(begin, end);
			ft::vector<int>::iterator range_begin = range_nums.begin();
			ft::vector<int>::iterator range_end = range_nums.end();
			ft::vector<int>::iterator it = range_begin;
			int	idx = 0;
			
			for (; it!=range_end; it++, idx++)
			{
				if (*it != val) 
					break ;
			}
			
			then(it == range_end && idx == len - offset);
		}
		{
			std::cout << "-- Exception : first가 last보다 뒤에 있는 경우(ft::length_error : vector) : ";
			try
			{
				ft::vector<int> range_nums(end, begin);
				then(false);
			}
			catch(const ft::length_error& e)
			{
				then(std::string(e.what()) == "vector");
			}
		}
	}

	std::cout << "- Copy constructor : ";
	{
		ft::vector<int>			v(5, 5);
		std::cout << '\n' << v.capacity() << ' ' << v.size();
		
		ft::vector<int>			v_copy(v);
		std::cout << '\n' << v.capacity() << ' ' << v.size();
		std::cout << '\n' << v_copy.capacity() << ' ' << v_copy.size();

		ft::vector<int>::iterator it = v_copy.begin();
		ft::vector<int>::iterator range_end = v_copy.end();
		int	idx = 0;
		
		for (; it!=range_end; it++, idx++)
		{
			std::cout << *it << ' ';
		}
	}

	return 0;
}

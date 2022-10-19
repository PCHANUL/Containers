/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:06:22 by cpak              #+#    #+#             */
/*   Updated: 2022/10/19 12:52:56 by cpak             ###   ########seoul.kr  */
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

class Test
{

private:
	int*	__p;

public:
	Test(int* p) : __p(p) { *(__p) += 1; }
	Test(const Test& x) : __p(x.__p) { *(__p) += 1; }
	~Test() { *(__p) -= 1; }
	
};

int main(void) 
{
	
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
		int					val = 1;
		ft::vector<int>		v(3, val);
		v.push_back(val);

		ft::vector<int>				v_copy(v);
		ft::vector<int>::iterator	it = v_copy.begin();
		ft::vector<int>::iterator	range_end = v_copy.end();
		
		for (; it!=range_end; it++)
		{
			if (*it != val)
				break ;
		}

		then(it == range_end 
			&& v_copy.capacity() == v.size()
			&& v_copy.size() == v.size());
	}

	std::cout << "- Destructor : ";
	{
		int	num = 0;
		{
			ft::vector<Test>	tests;
			Test				obj(&num);

			tests.push_back(obj);
			tests.push_back(obj);
			std::cout << "vector size(" << tests.size() << ") ";
		}
		then(num == 0);
	}

	std::cout << "- Copy assginment : ";
	{
		int					a_size = 10;
		int 				b_size = 20;
		std::vector<int>	a(a_size, 1);
		std::vector<int>	b(b_size, 1);

		b = a;

		then(b.capacity() == b_size);
	}



	return 0;
}

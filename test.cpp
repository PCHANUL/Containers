/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:06:22 by cpak              #+#    #+#             */
/*   Updated: 2022/10/20 16:04:40 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "iterator.hpp"
#include "iterator_traits.hpp"

#include <vector>
#include <memory>

#include "vector.hpp"

class Test
{

private:
	int*	__p;

public:
	Test(int* p) : __p(p) { *(__p) += 1; }
	Test(const Test& x) : __p(x.__p) { *(__p) += 1; }
	~Test() { *(__p) -= 1; }
	Test&	operator =	(const Test& x) { this->__p = x.__p; *(__p) += 1; return (*this); }
};

class Testing
{

private:
	bool			__result_main;
	bool			__result_sub;
	std::string		__msg_main;
	std::string		__msg_sub;

	void __print(bool is_succeed) {
		if (is_succeed)
			std::cout << "\033[1;32mSucceed\033[0m" << std::endl;
		else
			std::cout << "\033[1;31mFailed\033[0m" << std::endl; 
	}

public:

	Testing() { 
		__result_main = true; 
		__result_sub = true;
		__msg_main = "";
		__msg_sub = "";
	}

	void main(std::string str) { 
		__msg_main = str;
		__result_main = true;
	}
	void main_end() {
		std::cout << "- " << __msg_main << " : ";
		__print(__result_main);
	}
	void main_then(bool is_true) {
		if (__result_main)
			__result_main = is_true;
	}

	void sub(std::string str) { 
		__msg_sub = str; 
		__result_sub = true;
	}
	void sub_end() {
		std::cout << "-- " << __msg_sub << " : ";
		__print(__result_sub);
	}
	void sub_then(bool is_true) {
		if (__result_sub)
			__result_sub = is_true;
	}
};





int main(void) 
{
	Testing	test;

	std::cout << "< vector >" << std::endl;

	test.main("Default constructor");
	{
		ft::vector<int> ft_empty;
		ft::vector<int>::iterator ft_begin = ft_empty.begin();
		ft::vector<int>::iterator ft_end = ft_empty.end();

		test.main_then(ft_begin == ft_end);
		test.main_end();
	}

	test.main("Fill constructor (without val)");
	{
		int len = 10;
		ft::vector<int> ft_filled(len);
		ft::vector<int>::iterator ft_begin = ft_filled.begin();
		ft::vector<int>::iterator ft_end = ft_filled.end();
		ft::vector<int>::iterator it = ft_begin;

		for (; it!=ft_end; it++, len--);

		test.main_then(ft_begin != ft_end && len == 0);
		test.main_end();
	}

	test.main("Fill constructor (with val)");
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

		test.main_then(it == ft_end && len == 0);
		test.main_end();
	} 
	
	test.main("Range constructor");
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
			
			test.main_then(it == range_end && idx == len - offset);
		}
		{
			test.sub("Exception : first가 last보다 뒤에 있는 경우(ft::length_error : vector)");
			try
			{
				ft::vector<int> range_nums(end, begin);
				test.sub_then(false);
			}
			catch(const ft::length_error& e)
			{
				test.sub_then(std::string(e.what()) == "vector");
			}
			test.sub_end();
		}
		test.main_end();
	}

	test.main("Copy constructor");
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

		test.main_then(it == range_end 
			&& v_copy.capacity() == v.size()
			&& v_copy.size() == v.size());
		test.main_end();
	}

	test.main("Destructor");
	{
		int	num = 0;
		{
			ft::vector<Test>	tests;
			Test				obj(&num);

			tests.push_back(obj);
			tests.push_back(obj);
		}
		test.main_then(num == 0);
		test.main_end();
	}

	test.main("Copy assginment");
	{
		int					a_size = 10;
		int 				b_size = 20;
		ft::vector<int>	a(a_size, 1);
		ft::vector<int>	b(b_size, 1);

		b = a;

		test.main_then(b.capacity() == b_size);
		test.main_end();
	}
	
	test.main("push_back");
	{
		ft::vector<int>	vec;

		test.main_then(vec.size() == 0 && vec.capacity() == 0);

		vec.push_back(10);
		test.main_then(vec.size() == 1 && vec.capacity() == 1);

		vec.push_back(10);
		test.main_then(vec.size() == 2 && vec.capacity() == 2);

		vec.push_back(10);
		test.main_then(vec.size() == 3 && vec.capacity() == 4);

		vec.push_back(10);
		test.main_then(vec.size() == 4 && vec.capacity() == 4);
		
		vec.push_back(10);
		test.main_then(vec.size() == 5 && vec.capacity() == 8);

		test.main_end();
	}

	test.main("erase");
	{
		std::vector<int>	vec(100, 1);
		std::vector<int>	vec2(10, 1);

		vec.swap(vec2);
	}

	return 0;
}

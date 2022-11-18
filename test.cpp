/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:06:22 by cpak              #+#    #+#             */
/*   Updated: 2022/11/18 23:54:21 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <algorithm>
#include <memory>
#include <vector>
#include <map>

#include "vector.hpp"
#include "map.hpp"

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
		std::cout << " " << __msg_main << " --> ";
	}
	void main_end() {
		__print(__result_main);
	}
	void main_then(bool is_true) {
		if (is_true)
			std::cout << "✓" << ' ';
		else
			std::cout << "✕" << ' ';
		if (__result_main)
			__result_main = is_true;
	}

	void sub(std::string str) { 
		__msg_sub = str; 
		__result_sub = true;
		std::cout << "\t" << __msg_sub << " --> ";
	}
	void sub_end() {
		__print(__result_sub);
	}
	void sub_then(bool is_true) {
		if (is_true)
			std::cout << "✓" << ' ';
		else
			std::cout << "✕" << ' ';
		if (__result_sub)
			__result_sub = is_true;
	}

	template<class Iterator>
	void print_iter(Iterator begin, 
					typename ft::enable_if<ft::is_iterator<Iterator>::value, 
					Iterator>::type end)
	{
		for (; begin!=end; begin++)
			std::cout << *begin << ' ';
		std::cout << '\n';
	}

	template<class T>
	void print_std(std::vector<T> std_v)
	{
		print_iter(std_v.begin(), std_v.end());
	}

	template<class T>
	void print_ft(ft::vector<T> ft_v)
	{
		print_iter(ft_v.begin(), ft_v.end());
	}

	template<class Iter1, class Iter2>
	bool compare_iter(Iter1 a_begin, typename ft::enable_if<ft::is_iterator<Iter1>::value, Iter1>::type a_end, 
					Iter2 b_begin, typename ft::enable_if<ft::is_iterator<Iter2>::value, Iter2>::type b_end)
	{
		if (a_begin > a_end || b_begin > b_end)
			return (false);
		for (; a_begin!=a_end; a_begin++, b_begin++)
		{
			if (*a_begin != *b_begin)
				return (false);
		}
		if (b_begin != b_end)
			return (false);
		return (true);
	}

	template<class T>
	bool compare_vector(std::vector<T> std_v, ft::vector<T> ft_v)
	{
		return (compare_iter(std_v.begin(), std_v.end(), ft_v.begin(), ft_v.end()));
	}

	template<class T>
	bool compare_size(std::vector<T> std_v, ft::vector<T> ft_v)
	{
		return (std_v.size() == ft_v.size() && std_v.capacity() == ft_v.capacity());
	}

};


int main(void) 
{
	Testing	test;

	std::cout << "< vector >" << std::endl;
	{

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
			test.main_end();
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
	
	test.main("resize");
	{
		std::vector<int>	std_v(10, 1);
		ft::vector<int>		ft_v(10, 1);
		test.main_then(test.compare_iter(std_v.begin(), std_v.end(), ft_v.begin(), ft_v.end()));

		std_v.resize(5, 10);
		ft_v.resize(5, 10);
		test.main_then(test.compare_iter(std_v.begin(), std_v.end(), ft_v.begin(), ft_v.end()));
		test.main_then(std_v.capacity() == ft_v.capacity());

		std_v.resize(21, 7);
		ft_v.resize(21, 7);
		test.main_then(test.compare_iter(std_v.begin(), std_v.end(), ft_v.begin(), ft_v.end()));
		test.main_then(std_v.capacity() == ft_v.capacity());

		test.main_end();
	}

	test.main("reserve");
	{
		std::vector<int>	std_v(10, 1);
		ft::vector<int>		ft_v(10, 1);

		std_v.reserve(11);
		ft_v.reserve(11);
		test.main_then(test.compare_size(std_v, ft_v)); 

		std_v.reserve(20);
		ft_v.reserve(20);
		test.main_then(test.compare_size(std_v, ft_v)); 
			
		std_v.reserve(1);
		ft_v.reserve(1);
		test.main_then(test.compare_size(std_v, ft_v)); 

		test.main_end();
	}

	test.main("operator []");
	{
		const std::vector<int> 	std_v(10, 1);
		const ft::vector<int>	ft_v(10, 1);

		test.main_then(std_v[0] == ft_v[0]);
		test.main_then(std_v[9] == ft_v[9]);

		try
		{
			ft_v[10];
		}
		catch(const std::exception& e)
		{
			test.main_then(false);
		}

		test.main_end();
	}

	test.main("at");
	{
		std::vector<int>	std_v(10, 1);
		ft::vector<int>		ft_v(10, 1);

		test.main_then(std_v.at(0) == ft_v.at(0));
		test.main_then(std_v.at(9) == ft_v.at(9));

		try
		{
			ft_v.at(10);
		}
		catch(const std::exception& e)
		{
			test.main_then(std::string(e.what()) == "vector");
		}
		
		test.main_end();
	}

	test.main("assign(iterator)");
	{
		std::vector<int>	std_v(10, 1);
		std::vector<int>	std_under(2, 3);
		std::vector<int>	std_over(33, 7);
		
		ft::vector<int>		ft_v(10, 1);
		std::vector<int>	ft_under(2, 3);
		ft::vector<int>		ft_over(33, 7);

		std_v.assign(std_under.begin(), std_under.end());
		ft_v.assign(ft_under.begin(), ft_under.end());
		test.main_then(test.compare_iter(std_v.begin(), std_v.end(), ft_v.begin(), ft_v.end()));
		test.main_then(test.compare_size(std_v, ft_v));

		std_v.assign(std_over.begin(), std_over.end());
		ft_v.assign(ft_over.begin(), ft_over.end());
		test.main_then(test.compare_iter(std_v.begin(), std_v.end(), ft_v.begin(), ft_v.end()));
		test.main_then(test.compare_size(std_v, ft_v));
		test.main_end();
	}

	test.main("assign(size, value)");
	{
		std::vector<int>	std_v(10, 1);
		ft::vector<int>		ft_v(10, 1);

		std_v.assign(2, 3);
		ft_v.assign(2, 3);
		test.main_then(test.compare_iter(std_v.begin(), std_v.end(), ft_v.begin(), ft_v.end()));
		test.main_then(test.compare_size(std_v, ft_v));

		std_v.assign(20, 7);
		ft_v.assign(20, 7);
		test.main_then(test.compare_iter(std_v.begin(), std_v.end(), ft_v.begin(), ft_v.end()));
		test.main_then(test.compare_size(std_v, ft_v));

		try
		{
			ft_v.assign(-10, 1);
			test.main_then(false);
		}
		catch(const std::exception& e)
		{
			test.main_then(std::string(e.what()) == "vector");
		}
		
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

	test.main("pop_back");
	{
		std::vector<int>	std_v(10, 1);
		ft::vector<int>		ft_v(10, 1);

		std_v.pop_back();
		ft_v.pop_back();

		test.main_then(test.compare_iter(std_v.begin(), std_v.end(), ft_v.begin(), ft_v.end()));
		test.main_then(test.compare_size(std_v, ft_v));
		test.main_end();
	}

	test.main("insert(a value)");
	{
		std::vector<int>	std_v(10, 1);
		ft::vector<int>		ft_v(10, 1);

		std::vector<int>::iterator	std_iter = std_v.insert(std_v.end() - 5, 7);
		ft::vector<int>::iterator	ft_iter = ft_v.insert(ft_v.end() - 5, 7);

		test.main_then(*std_iter == *ft_iter);
		test.main_then(test.compare_vector(std_v, ft_v));
		test.main_then(test.compare_size(std_v, ft_v));
		
		std_iter = std_v.insert(std_v.begin(), 9);
		ft_iter = ft_v.insert(ft_v.begin(), 9);

		test.main_then(*std_iter == *ft_iter);
		test.main_then(test.compare_vector(std_v, ft_v));
		test.main_then(test.compare_size(std_v, ft_v));

		test.main_end();
	}

	test.main("insert(size, value)");
	{
		std::vector<int>	std_v(10, 1);
		ft::vector<int>		ft_v(10, 1);
		
		std_v.insert(std_v.end() - 5, 2, 7);
		ft_v.insert(ft_v.end() - 5, 2, 7);

		test.main_then(test.compare_vector(std_v, ft_v));
		test.main_then(test.compare_size(std_v, ft_v));
		
		std_v.insert(std_v.begin(), 10, 9);
		ft_v.insert(ft_v.begin(), 10, 9);

		test.main_then(test.compare_vector(std_v, ft_v));
		test.main_then(test.compare_size(std_v, ft_v));

		test.main_end();
	}

	test.main("insert(iterator)");
	{
		std::vector<int>	std_v(10, 1);
		ft::vector<int>		ft_v(10, 1);
		std::vector<int>	tmp1(20, 7);
		
		std_v.insert(std_v.end() - 5, tmp1.begin(), tmp1.end());
		ft_v.insert(ft_v.end() - 5, tmp1.begin(), tmp1.end());
		test.main_then(test.compare_vector(std_v, ft_v));
		test.main_then(test.compare_size(std_v, ft_v));

		std_v.insert(std_v.begin(), tmp1.begin(), tmp1.end());
		ft_v.insert(ft_v.begin(), tmp1.begin(), tmp1.end());
		test.main_then(test.compare_vector(std_v, ft_v));
		test.main_then(test.compare_size(std_v, ft_v));

		test.main_end();
	}

	test.main("erase(a value)");
	{
		std::vector<int>	std_v(99, 1);
		ft::vector<int>		ft_v(99, 1);

		std_v.insert(std_v.begin() + 30, 2, 99);
		ft_v.insert(ft_v.begin() + 30, 2, 99);

		std::vector<int>::iterator std_iter = std_v.erase(std_v.begin() + 30);
		ft::vector<int>::iterator ft_iter = ft_v.erase(ft_v.begin() + 30);

		test.main_then(test.compare_iter(std_iter, std_v.end(), ft_iter, ft_v.end()));
		test.main_then(test.compare_vector(std_v, ft_v));
		test.main_then(test.compare_size(std_v, ft_v));
		test.main_end();
	}

	test.main("erase(iterator)");
	{
		std::vector<int>	std_v(99, 1);
		ft::vector<int>		ft_v(99, 1);

		std_v.insert(std_v.begin() + 30, 5, 99);
		ft_v.insert(ft_v.begin() + 30, 5, 99);

		std::vector<int>::iterator std_iter = std_v.erase(std_v.begin() + 30, std_v.begin() + 33);
		ft::vector<int>::iterator ft_iter = ft_v.erase(ft_v.begin() + 30, ft_v.begin() + 33);

		test.main_then(test.compare_iter(std_iter, std_v.end(), ft_iter, ft_v.end()));
		test.main_then(test.compare_vector(std_v, ft_v));
		test.main_then(test.compare_size(std_v, ft_v));
		test.main_end();
	}

	test.main("swap");
	{
		std::vector<int>	std_v(10, 1);
		std::vector<int>	std_tmp(20, 8);
		ft::vector<int>		ft_v(10, 1);
		ft::vector<int>		ft_tmp(20, 8);

		std::vector<int>::iterator	std_iter = std_v.begin();
		ft::vector<int>::iterator	ft_iter = ft_v.begin();
		
		std_v.swap(std_tmp);
		ft_v.swap(ft_tmp);
		test.main_then(test.compare_vector(std_v, ft_v));
		test.main_then(test.compare_vector(std_tmp, ft_tmp));
		test.main_then(*std_iter == *ft_iter);
		test.main_then(test.compare_size(std_v, ft_v));
		test.main_then(test.compare_size(std_tmp, ft_tmp));
		test.main_end();
	}

	test.main("clear");
	{
		std::vector<int>	std_v(10, 1);
		ft::vector<int>		ft_v(10, 1);

		std_v.clear();
		ft_v.clear();
		test.main_then(test.compare_vector(std_v, ft_v));
		test.main_then(test.compare_size(std_v, ft_v));
		test.main_end();
	}

	test.main("operator =");
	{
		std::vector<int>	std_v(10, 1);
		std::vector<int>	std_tmp(20, 8);
		ft::vector<int>		ft_v(10, 1);
		ft::vector<int>		ft_tmp(20, 8);

		std_tmp.push_back(10);
		ft_tmp.push_back(10);

		std_v = std_tmp;
		ft_v = ft_tmp;

		test.main_then(test.compare_vector(std_v, ft_v));
		test.main_then(test.compare_vector(std_tmp, ft_tmp));
		test.main_then(test.compare_size(std_v, ft_v));
		test.main_end();
	}

	test.main("equal");
	{
		bool				std_result;
		bool				ft_result;
		std::vector<int>	std_v(10, 1);
		std::vector<int>	std_tmp(10, 1);
		std_tmp.push_back(8);
		
		std_result = std::equal(std_v.begin(), std_v.end(), std_tmp.begin());
		ft_result = ft::equal(std_v.begin(), std_v.end(), std_tmp.begin());
		test.main_then(std_result == ft_result);

		std_result = std::equal(std_tmp.begin(), std_tmp.end(), std_v.begin());
		ft_result = ft::equal(std_tmp.begin(), std_tmp.end(), std_v.begin());
		test.main_then(std_result == ft_result);
		test.main_end();
	}

	test.main("operator ==, !=");
	{
		ft::vector<int>		ft_v(10, 1);
		ft::vector<int>		ft_tmp(10, 1);

		test.main_then(ft_v == ft_tmp);
		ft_tmp.push_back(1);
		test.main_then(ft_v != ft_tmp);
		ft_tmp.pop_back();
		test.main_then(ft_v == ft_tmp);
		test.main_end();
	}

	test.main("lexicographical_compare");
	{
		bool				std_result;
		bool				ft_result;
		std::vector<int>	std_v(10, 1);
		std::vector<int>	std_tmp(10, 1);
		std_tmp.push_back(8);
		
		std_result = std::equal(std_v.begin(), std_v.end(), std_tmp.begin());
		ft_result = ft::equal(std_v.begin(), std_v.end(), std_tmp.begin());
		test.main_then(std_result == ft_result);

		std_result = std::equal(std_tmp.begin(), std_tmp.end(), std_v.begin());
		ft_result = ft::equal(std_tmp.begin(), std_tmp.end(), std_v.begin());
		test.main_then(std_result == ft_result);
		test.main_end();
	}

	test.main("operator <, <=");
	{
		std::vector<int>	std_v(10, 1);
		std::vector<int>	std_tmp(10, 1);
		ft::vector<int>		ft_v(10, 1);
		ft::vector<int>		ft_tmp(10, 1);

		bool std_result = std_v < std_tmp;
		bool ft_result = ft_v < ft_tmp;
		test.main_then(std_result == ft_result);

		std_result = std_v <= std_tmp;
		ft_result = ft_v <= ft_tmp;
		test.main_then(std_result == ft_result);

		std_tmp.push_back(11);
		ft_tmp.push_back(11);

		std_result = std_v < std_tmp;
		ft_result = ft_v < ft_tmp;
		test.main_then(std_result == ft_result);

		std_result = std_v <= std_tmp;
		ft_result = ft_v <= ft_tmp;
		test.main_then(std_result == ft_result);

		test.main_end();
	}

	test.main("operator >, >=");
	{
		std::vector<int>	std_v(10, 1);
		std::vector<int>	std_tmp(10, 1);
		ft::vector<int>		ft_v(10, 1);
		ft::vector<int>		ft_tmp(10, 1);

		bool std_result = std_v > std_tmp;
		bool ft_result = ft_v > ft_tmp;
		test.main_then(std_result == ft_result);

		std_result = std_v >= std_tmp;
		ft_result = ft_v >= ft_tmp;
		test.main_then(std_result == ft_result);

		std_tmp.push_back(11);
		ft_tmp.push_back(11);

		std_result = std_v > std_tmp;
		ft_result = ft_v > ft_tmp;
		test.main_then(std_result == ft_result);

		std_result = std_v >= std_tmp;
		ft_result = ft_v >= ft_tmp;
		test.main_then(std_result == ft_result);

		test.main_end();
	}

	test.main("iterator");
	{
		std::vector<int>	std_v;
		ft::vector<int>		ft_v;

		std_v.push_back(10);
		std_v.push_back(20);
		std_v.push_back(30);
		std_v.push_back(40);
		std_v.push_back(40);

		ft_v.push_back(10);
		ft_v.push_back(20);
		ft_v.push_back(30);
		ft_v.push_back(40);
		ft_v.push_back(40);

		std::vector<int>::iterator	std_iter = std_v.begin();
		ft::vector<int>::iterator	ft_iter = ft_v.begin();

		test.main_then(*std_iter == *ft_iter);

		++std_iter;
		++ft_iter;

		std_iter += 1;
		ft_iter += 1;

		test.main_then(*(std_iter++) == *(ft_iter++));
		test.main_then(*std_iter == *ft_iter);
		
		test.main_then((ft_v.end() - 2) == (ft_v.end() - 1) == false);
		test.main_then((ft_v.end() - 1) == (ft_v.end() - 1) == true);
		
		test.main_end();
	}

	test.main("reverse_iterator");
	{
		std::vector<int>	std_v;
		std_v.push_back(10);
		std_v.push_back(20);
		std_v.push_back(30);
		std_v.push_back(40);
		std_v.push_back(50);
		std_v.push_back(60);

		ft::vector<int>	ft_v;
		ft_v.push_back(10);
		ft_v.push_back(20);
		ft_v.push_back(30);
		ft_v.push_back(40);
		ft_v.push_back(50);
		ft_v.push_back(60);

		std::vector<int>::iterator			std_iter = std_v.begin();
		std::vector<int>::reverse_iterator	std_riter = std::vector<int>::reverse_iterator(std_iter);

		ft::vector<int>::iterator			ft_iter = ft_v.begin();
		ft::vector<int>::reverse_iterator	ft_riter = ft::vector<int>::reverse_iterator(ft_iter);

		test.main_then(*(std_iter - 1) == *std_riter);
		test.main_then(*(ft_iter - 1) == *ft_riter);

		std_riter -= 1;
		ft_riter -= 1;

		std_riter = std_riter - 1;
		ft_riter = ft_riter - 1;

		std_riter = 1 + std_riter;
		ft_riter = 1 + ft_riter;

		--std_riter;
		--ft_riter;

		test.main_then(*(std_iter + 1) == *(std_riter--));
		test.main_then(*(ft_iter + 1) == *(ft_riter--));

		test.main_then(*(std_iter + 2) == *std_riter);
		test.main_then(*(ft_iter + 2) == *ft_riter);

		test.main_then(std_riter[0] == ft_riter[0]);
		test.main_then(std_riter[1] == ft_riter[1]);
		test.main_then(std_riter[2] == ft_riter[2]);
		test.main_then(std_riter.operator->()[0] == ft_riter.operator->()[0]);

		test.main_then((std_riter - (std_riter - 2)) == (ft_riter - (ft_riter - 2)));

		test.main_end();
	}

	test.main("rbegin, rend");
	{
		std::vector<int>	std_v;
		std_v.push_back(10);
		std_v.push_back(20);
		std_v.push_back(30);
		std_v.push_back(40);
		std_v.push_back(50);
		std_v.push_back(60);

		ft::vector<int>		ft_v;
		ft_v.push_back(10);
		ft_v.push_back(20);
		ft_v.push_back(30);
		ft_v.push_back(40);
		ft_v.push_back(50);
		ft_v.push_back(60);

		test.main_then(*std_v.rbegin() == *ft_v.rbegin());
		test.main_then(*(std_v.rend()-1) == *(ft_v.rend()-1));
		test.main_end();
	}

	}

	std::cout << "< map >" << std::endl;
	{

	test.main("pair");
	{
		std::pair <std::string, double>	std1;                  
		std::pair <std::string, double>	std2 ("tomatoes", 2.30);
		std::pair <std::string, double>	std3 (std2);

		ft::pair <std::string, double>	ft1;                  
		ft::pair <std::string, double>	ft2 ("tomatoes", 2.30);
		ft::pair <std::string, double>	ft3 (ft2);       

		std2.first = "shoes";
		std2.second = 39.90;
		ft2.first = "shoes";
		ft2.second = 39.90;

		test.main_then(std1.first == ft1.first);
		test.main_then(std1.second == ft1.second);
		test.main_then(std2.first == ft2.first);
		test.main_then(std2.second == ft2.second);
		test.main_then(std3.first == ft3.first);
		test.main_then(std3.second == ft3.second);

		ft::pair<int, int>	ft_a;
		ft::pair<int, int>	ft_b;

		ft_a = ft::make_pair(10, 11);
		ft_b = ft::make_pair(10, 10);

		test.main_then((ft_a < ft_b) == false);

		ft_a.first = 9;
		test.main_then((ft_a < ft_b) == true);

		test.main_end();
	}

	test.main("insert(val)");
	{
		ft::map<int, int>	ft_map;
	
		ft_map.insert(ft::pair<int, int>(10, 10));
		ft_map.insert(ft::pair<int, int>(20, 10));
		ft_map.insert(ft::pair<int, int>(30, 10));
		ft_map.insert(ft::pair<int, int>(5, 10));
		ft_map.insert(ft::pair<int, int>(15, 10));
		ft_map.insert(ft::pair<int, int>(8, 10));
		ft_map.insert(ft::pair<int, int>(7, 10));
		ft_map.insert(ft::pair<int, int>(2, 10));
		ft_map.insert(ft::pair<int, int>(1, 10));
		ft_map.insert(ft::pair<int, int>(6, 10));

		test.main_end();
	}

	test.main("insert(hint)");
	{
		ft::map<int, int>	std_map;
		ft::pair<int, int>	std_pair(10, 10);
		int					nums[] = {1, 2, 4, 7, 10, 30, 55, 71, 200, 456};

		for (int i=0; i<10; i++)
		{
			std_pair.first = nums[i];
			std_map.insert(std_pair);
		}

		ft::map<int, int>::iterator	iter = std_map.begin();
		std_pair.first = 500;
		ft::map<int, int>::iterator	new_iter = std_map.insert(iter, std_pair);

		ft::map<int, int>::iterator	std_iter = std_map.begin();
		ft::map<int, int>::iterator	std_end = std_map.end();
		std_end--;
		for (int i=0; std_iter!=std_end; std_iter++, i++)
		{
			test.main_then((*std_iter).first == nums[i]);
		}
		test.main_then((*std_iter).first == (*std_end).first);
		test.main_end();
	}

	test.main("insert(range)");
	{
		ft::map<int, int>	ft_map;
		ft::pair<int, int>	ft_pair(10, 10);
		int					nums[] = {1, 2, 4, 7, 10, 30, 55, 71, 200, 456};

		for (int i=0; i<10; i++)
		{
			ft_pair.first = nums[i];
			ft_map.insert(ft_pair);
		}

		ft::map<int, int>	range_map(ft_map.begin(), ft_map.end());
		
		ft::map<int, int>::iterator	ft_begin = ft_map.begin();
		ft::map<int, int>::iterator	range_begin = range_map.begin();
		ft::map<int, int>::iterator	range_end = range_begin;
		range_end++;
		range_end++;
		range_end++;
		for (; range_begin!=range_end; range_begin++, ft_begin++)
		{
			test.main_then((*range_begin).first == (*ft_begin).first);
		}
		test.main_end();
	}

	test.main("iterator");
	{
		ft::map<int, int>	ft_map;
		ft::pair<int, int>	ft_pair(0, 10);
		int					nums[] = {1, 2, 4, 7, 10, 30, 55, 71, 200, 456};

		for (int i=0; i<10; i++)
		{
			ft_pair.first = nums[i];
			ft_map.insert(ft_pair);
		}

		ft::map<int, int>::iterator	ft_iter = ft_map.begin();
		for (int i=0; i<10; i++, ft_iter++)
		{
			test.main_then((*ft_iter).first == nums[i]);
		}
		test.main_end();
	}

	test.main("Constructor");
	{
		ft::map<int, int>				std_map;
		ft::map<int, int>::iterator		std_end = std_map.end();
		ft::map<int, int>::iterator		std_begin = std_map.begin();

		test.main_then(std_begin == std_end);
		std_map.insert(ft::pair<int, int>(10, 10));
		std_begin = std_map.begin();
		std_begin++;
		test.main_then(std_begin == std_end);
		test.main_end();
	}

	test.main("find");
	{
		ft::map<int, int>	ft_map;
		ft_map.insert(ft::pair<int, int>(10, 1));
		ft_map.insert(ft::pair<int, int>(20, 1));

		ft::map<int, int>::iterator	iter;
		iter = ft_map.find(10);
		test.main_then((*iter).first == 10);
		iter = ft_map.find(20);
		test.main_then((*iter).first == 20);
		iter = ft_map.find(30);
		test.main_then((*iter).first == (*ft_map.end()).first);
		iter = ft_map.find(10000);
		test.main_then((*iter).first == (*ft_map.end()).first);
		test.main_end();
	}

	test.main("operator []");
	{
		ft::map<int, int>	ft_map;

		ft_map[10];
		ft_map[20];
		ft_map[30];
		test.main_then(ft_map.size() == 3);
		ft_map[10] = 100;
		ft_map[20] = 100;
		ft_map[30] = 100;
		ft_map[40] = 100;
		test.main_then(ft_map.size() == 4);
		test.main_then(ft_map[10] == 100 || ft_map[20] == 100 || ft_map[30] == 100 || ft_map[40] == 100);
		test.main_end();
	}

	test.main("at");
	{
		ft::map<int, int>	ft_map;

		try
		{
			ft_map.at(10);
			test.main_then(false);
		}
		catch(const std::exception& e)
		{
			test.main_then(std::string(e.what()) == "map::at:  key not found");
			test.main_then(true);
		}

		ft_map[10] = 10;

		try
		{
			test.main_then(ft_map.at(10) == 10);
			test.main_then(true);
		}
		catch(const std::exception& e)
		{
			test.main_then(false);
		}
		test.main_end();
	}

	test.main("lower_bound");
	{
		std::map<int, int>	std_map;
		ft::map<int, int>	ft_map;

		std_map[10] = 10;
		std_map[20] = 20;
		std_map[30] = 30;
		ft_map[10] = 10;
		ft_map[20] = 20;
		ft_map[30] = 30;
		test.main_then((*std_map.lower_bound(8)).first == (*ft_map.lower_bound(8)).first);
		test.main_then((*std_map.lower_bound(13)).first == (*ft_map.lower_bound(13)).first);
		test.main_then((*std_map.lower_bound(20)).first == (*ft_map.lower_bound(20)).first);
		test.main_then((*std_map.lower_bound(21)).first == (*ft_map.lower_bound(21)).first);
		test.main_then(std_map.lower_bound(35) == std_map.end());
		test.main_then(ft_map.lower_bound(35) == ft_map.end());
		test.main_end();
	}
	
	test.main("upper_bound");
	{
		std::map<int, int>	std_map;
		ft::map<int, int>	ft_map;

		std_map[10] = 10;
		std_map[20] = 20;
		std_map[30] = 30;
		ft_map[10] = 10;
		ft_map[20] = 20;
		ft_map[30] = 30;
		test.main_then((*std_map.upper_bound(8)).first == (*ft_map.upper_bound(8)).first);
		test.main_then((*std_map.upper_bound(13)).first == (*ft_map.upper_bound(13)).first);
		test.main_then((*std_map.upper_bound(20)).first == (*ft_map.upper_bound(20)).first);
		test.main_then((*std_map.upper_bound(21)).first == (*ft_map.upper_bound(21)).first);
		test.main_then(std_map.upper_bound(35) == std_map.end());
		test.main_then(ft_map.upper_bound(35) == ft_map.end());
		test.main_end();
	}

	test.main("equal_range");
	{
		typedef std::map<int, int>::iterator	std_iterator;
		typedef ft::map<int, int>::iterator		ft_iterator;

		std::map<int, int>						std_map;
		std::pair<std_iterator, std_iterator>	std_p;
		ft::map<int, int>						ft_map;
		ft::pair<ft_iterator, ft_iterator>		ft_p;

		std_map.insert(std::pair<int, int>(10, 10));
		std_map.insert(std::pair<int, int>(20, 10));
		std_map.insert(std::pair<int, int>(30, 10));

		ft_map.insert(ft::pair<int, int>(10, 10));
		ft_map.insert(ft::pair<int, int>(20, 10));
		ft_map.insert(ft::pair<int, int>(30, 10));

		std_p = std_map.equal_range(9);
		ft_p = ft_map.equal_range(9);
		test.main_then((*std_p.first).first == (*ft_p.first).first);
		test.main_then((*std_p.second).first == (*ft_p.second).first);


		std_p = std_map.equal_range(10);
		ft_p = ft_map.equal_range(10);
		test.main_then((*std_p.first).first == (*ft_p.first).first);
		test.main_then((*std_p.second).first == (*ft_p.second).first);

		std_p = std_map.equal_range(11);
		ft_p = ft_map.equal_range(11);
		test.main_then((*std_p.first).first == (*ft_p.first).first);
		test.main_then((*std_p.second).first == (*ft_p.second).first);

		std_p = std_map.equal_range(30);
		ft_p = ft_map.equal_range(30);
		test.main_then((*std_p.first).first == (*ft_p.first).first);
		test.main_then((*std_p.second) == *std_map.end());
		test.main_then((*ft_p.second) == *ft_map.end());
		
		test.main_end();
	}

	test.main("operator ==");
	{
		std::map<int, int>	std_map1;
		std::map<int, int>	std_map2;
		bool				std_result;
		std_map1[10] = 10;
		std_map1[20] = 20;
		std_map2[10] = 10;
		std_map2[20] = 20;
	
		ft::map<int, int>	ft_map1;
		ft::map<int, int>	ft_map2;
		bool				ft_result;
		ft_map1[10] = 10;
		ft_map1[20] = 20;
		ft_map2[10] = 10;
		ft_map2[20] = 20;

		std_result = (std_map1 == std_map2);
		ft_result = (ft_map1 == ft_map2);
		test.main_then(std_result == ft_result);

		std_map1[20] = 10;
		ft_map1[20] = 10;
		std_result = (std_map1 == std_map2);
		ft_result = (ft_map1 == ft_map2);
		test.main_then(std_result == ft_result);
		
		std_result = (std_map1 != std_map2);
		ft_result = (ft_map1 != ft_map2);
		test.main_then(std_result == ft_result);

		test.main_end();
	}

	test.main("operator <, >");
	{
		std::map<int, int>	std_map1;
		std::map<int, int>	std_map2;
		bool				std_result;
		std_map1[10] = 10;
		std_map1[20] = 20;
		std_map2[10] = 10;
		std_map2[20] = 20;
	
		ft::map<int, int>	ft_map1;
		ft::map<int, int>	ft_map2;
		bool				ft_result;
		ft_map1[10] = 10;
		ft_map1[20] = 20;
		ft_map2[10] = 10;
		ft_map2[20] = 20;

		std_result = (std_map1 < std_map2);
		ft_result = (ft_map1 < ft_map2);
		test.main_then(std_result == ft_result);

		std_map1[20] = 10;
		ft_map1[20] = 10;
		std_result = (std_map1 < std_map2);
		ft_result = (ft_map1 < ft_map2);
		test.main_then(std_result == ft_result);
		
		std_result = (std_map1 > std_map2);
		ft_result = (ft_map1 > ft_map2);
		test.main_then(std_result == ft_result);

		test.main_end();
	}



	}	// map

	
	std::cout << "< __tree >" << std::endl;
	{

	typedef ft::pair<const int, int>											__value_type;
	typedef	ft::__map_compare<__value_type, ft::less<int> >						__compare;
	typedef	ft::__tree<__value_type, __compare, std::allocator<__value_type> >	__tree_type;

	
	test.main("__tree_iterator");
	{
		__tree_type			tree;

		ft::pair<int, int>	ft_pair(10, 10);
		int					nums[] = {1, 2, 4, 7, 10, 30, 55, 71, 200, 456};
		for (int i=0; i<10; i++)
		{
			ft_pair.first = nums[i];
			tree.insert(ft_pair);
		}

		__tree_type::iterator	iter = tree.begin();
		__tree_type::iterator	iter_end = tree.end();
		for (int i = 0; iter!=iter_end; iter++, i++)
		{
			test.main_then((*iter).first == nums[i]);
		}
		
		test.main_end();
		std::cout << "\n";
		tree.print();
		std::cout << "\n";
	}

	test.main("__tree::erase");
	{
		__tree_type	tree;

		ft::pair<int, int>	ft_pair(10, 10);
		for (int i=0; i<20; i++)
		{
			ft_pair.first = i;
			tree.insert(ft_pair);
		}

		std::cout << "\n" << std::endl;
		tree.print();

		ft_pair.first = 16;
		tree.erase(ft_pair);
		tree.print();

		ft_pair.first = 13;
		tree.erase(ft_pair);
		tree.print();
		
		ft_pair.first = 14;
		tree.erase(ft_pair);
		tree.print();
		
		// ft_pair.first = 19;
		// tree.erase(ft_pair);
		// tree.print();
		
		// ft_pair.first = 9;
		// tree.erase(ft_pair);
		// tree.print();

		// ft_pair.first = 10;
		// tree.erase(ft_pair);
		// tree.print();
		
		// ft_pair.first = 8;
		// tree.erase(ft_pair);
		// tree.print();






	}

	}	// __tree

	return (0);
}



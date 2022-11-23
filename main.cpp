/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:06:20 by cpak              #+#    #+#             */
/*   Updated: 2022/11/23 22:05:53 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <deque>
#include <map>
#include <stack>
#include <vector>

#include "map.hpp"
#include "stack.hpp"
#include "vector.hpp"

#include <stdlib.h>
#include <time.h>
#include <iomanip>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

int main(int argc, char** argv) {
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	clock_t	start, end;
	const int seed = atoi(argv[1]);
	srand(seed);

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	ft::map<int, int> map_int;

	start = clock();
	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}
	end = clock();
	std::cout << "ft_push_back(Buffer) : " << (end - start) << "ms" << std::endl;

	std::vector<Buffer> std_vector_buffer;
	start = clock();
	for (int i = 0; i < COUNT; i++)
	{
		std_vector_buffer.push_back(Buffer());
	}
	end = clock();
	std::cout << "std_push_back(Buffer) : " << (end - start) << "ms" << std::endl;


	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	ft::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
	
	start = clock();
	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
	}
	end = clock();
	std::cout << std::setw(20) << "ft_map.insert : " << std::setw(10) << (end - start) << "ms" << std::endl;
	
	std::map<int, int> std_map_int;
	start = clock();
	for (int i = 0; i < COUNT; ++i)
	{
		std_map_int.insert(std::make_pair(rand(), rand()));
	}
	end = clock();
	std::cout << std::setw(20) << "std_map.insert : " << std::setw(10) << (end - start) << "ms" << std::endl;

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	start = clock();
	{
		ft::map<int, int> copy = map_int;
	}
	end = clock();
	std::cout << "ft_copy : " << (end - start) << "ms" << std::endl;

	start = clock();
	{
		std::map<int, int> copy = std_map_int;
	}
	end = clock();
	std::cout << "std_copy : " << (end - start) << "ms" << std::endl;



	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;
	return (0);
}

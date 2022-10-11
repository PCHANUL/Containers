/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:06:22 by cpak              #+#    #+#             */
/*   Updated: 2022/10/11 23:36:36 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "iterator.hpp"
#include "iterator_traits.hpp"

namespace ft
{

template <class T, class Alloc = std::allocator<T> >
class vector
{
    typedef ft::v_iter<T>	iterator;

};

}

#include <vector>
#include <memory>

int main(void) {
    {
        int numbers[] = { 10,20,30,40,50 };
        
        ft::v_iter<int> from(numbers);
        ft::v_iter<int> until(numbers + 5);
        
        for (ft::v_iter<int> it=from; it!=until; it++)
            std::cout << *it << ' ';
        std::cout << '\n';
    }
    {
        std::vector<int> nums;
        nums.push_back(10);
        nums.push_back(20);
        nums.push_back(30);
        nums.push_back(40);
        nums.push_back(50);

        
        std::vector<int>::iterator from = nums.begin();
        std::vector<int>::iterator until = nums.end();
        
        for (std::vector<int>::iterator it=from; it!=until; it++)
            std::cout << *it << ' ';
        std::cout << '\n';
    }

    return 0;
}

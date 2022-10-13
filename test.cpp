/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:06:22 by cpak              #+#    #+#             */
/*   Updated: 2022/10/13 19:34:54 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "iterator.hpp"
#include "iterator_traits.hpp"

#include <vector>
#include <memory>

#include "vector.hpp"

int main(void) {
    {   
        ft::vector<int> nums(10, 5);

        ft::vector<int>::iterator from = nums.begin();
        ft::vector<int>::iterator until = nums.end();

        for (ft::vector<int>::iterator it=from; it!=until; it++)
            std::cout << *it << ' ';
        std::cout << '\n';
    }
    {
        ft::vector<int> nums(10, 1);
        
        ft::vector<int>::iterator from = nums.begin();
        ft::vector<int>::iterator until = nums.end();
        
        for (ft::vector<int>::iterator it=from; it!=until; it++)
            std::cout << *it << ' ';
        std::cout << '\n';

        ft::vector<int> __nums(from, until - 5);
        ft::vector<int>::iterator __from = __nums.begin();
        ft::vector<int>::iterator __until = __nums.end();
        for (ft::vector<int>::iterator it=__from; it!=__until; it++)
            std::cout << *it << ' ';
        std::cout << '\n';
    }

    return 0;
}

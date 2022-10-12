/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:06:22 by cpak              #+#    #+#             */
/*   Updated: 2022/10/12 18:14:29 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "iterator.hpp"
#include "iterator_traits.hpp"

#include <vector>
#include <memory>

#include "vector.hpp"

// std::vector와 비교하며 구현

int main(void) {
    {   
        ft::vector<int> nums(10, 1);
        
    }
    {
        std::vector<int> nums(10);
        // nums.push_back(10);
        // nums.push_back(20);
        // nums.push_back(30);
        // nums.push_back(40);
        // nums.push_back(50);

        
        std::vector<int>::iterator from = nums.begin();
        std::vector<int>::iterator until = nums.end();
        
        for (std::vector<int>::iterator it=from; it!=until; it++)
            std::cout << *it << ' ';
        std::cout << '\n';
    }

    return 0;
}

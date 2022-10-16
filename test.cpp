/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:06:22 by cpak              #+#    #+#             */
/*   Updated: 2022/10/16 18:26:33 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "iterator.hpp"
#include "iterator_traits.hpp"

#include <vector>
#include <memory>

#include "vector.hpp"

int main(void) {
    std::cout << "vector" << std::endl;
    // {   
    //     ft::vector<int> nums(10, 5);

    //     ft::vector<int>::iterator from = nums.begin();
    //     ft::vector<int>::iterator until = nums.end();

    //     for (ft::vector<int>::iterator it=from; it!=until; it++)
    //         std::cout << *it << ' ';
    //     std::cout << '\n';
    // }
    {
        ft::vector<int> nums(10, 5);
        
        ft::vector<int>::iterator from = nums.begin();
        ft::vector<int>::iterator until = nums.end();
        
        for (ft::vector<int>::iterator it=from; it!=until; it++)
            std::cout << *it << ' ';
        std::cout << '\n';

        ft::vector<int> new_nums(nums.begin(), nums.end() - 5);
        ft::vector<int>::iterator new_from = new_nums.begin();
        ft::vector<int>::iterator new_until = new_nums.end();
        
        for (ft::vector<int>::iterator it=new_from; it!=new_until; it++)
            std::cout << *it << ' ';
        std::cout << '\n';
    }

    return 0;
}

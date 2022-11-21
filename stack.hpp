/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:58:11 by cpak              #+#    #+#             */
/*   Updated: 2022/11/21 18:09:08 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef __STACK_HPP__
#define __STACK_HPP__

#include "vector.hpp"

namespace ft
{

template<class T, class Container = ft::vector<T> >
class stack
{

public:
    typedef Container                   container_type;
    typedef Container::value_type       value_type;
    typedef Container::size_type        size_type;

    stack() : stack(Container()) {}
    stack(const container_type& ctnr = container_type());
    ~stack();
    bool empty() const;
    size_type size() const;
    value_type& top();
    const value_type& top() const;
    void push (const value_type& val);
    void pop();

}





}   // ft




#endif  // __STACK_HPP__
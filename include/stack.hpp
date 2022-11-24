/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:58:11 by cpak              #+#    #+#             */
/*   Updated: 2022/11/24 14:13:53 by cpak             ###   ########seoul.kr  */
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
    typedef Container                       container_type;
    typedef typename Container::value_type  value_type;
    typedef typename Container::size_type   size_type;

    stack(const container_type& ctnr = container_type());
    stack(const stack& other);
    ~stack();
    stack&              operator = (const stack& other);
    
    bool                empty() const;
    size_type           size() const;
    value_type&         top();
    const value_type&   top() const;
    void                push (const value_type& val);
    void                pop();

protected:
    Container   c;

};

template <class T, class Container>  
ft::stack<T, Container>::stack(const container_type& ctnr) : c(ctnr)
{
}

template <class T, class Container>  
ft::stack<T, Container>::stack(const stack& other) : c(other.c)
{
}

template <class T, class Container>  
ft::stack<T, Container>::~stack()
{
}

template <class T, class Container>  
ft::stack<T, Container>&
ft::stack<T, Container>::operator = (const stack& other)
{
    this->c = other;
    return (*this);
}

template <class T, class Container>  
bool
ft::stack<T, Container>::empty() const
{
    return (this->c.empty());
}

template <class T, class Container>  
typename ft::stack<T, Container>::size_type
ft::stack<T, Container>::size() const
{
    return (this->c.size());
}

template <class T, class Container>  
const typename ft::stack<T, Container>::value_type&
ft::stack<T, Container>::top() const
{
    return (this->c.top());
}

template <class T, class Container>  
void
ft::stack<T, Container>::push(const value_type& val)
{
    return (this->c.push_back(val));
}

template <class T, class Container>  
void
ft::stack<T, Container>::pop()
{
    return (this->c.pop_back());
}

template <class T, class Container>  
bool 
operator == (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
{
	return (lhs.c == rhs.c);
}

template <class T, class Container>  
bool 
operator != (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
{
	return (lhs.c != rhs.c);
}

template <class T, class Container>  
bool 
operator <  (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
{
	return (lhs.c < rhs.c);
}

template <class T, class Container>  
bool 
operator >  (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
{
	return (lhs.c > rhs.c);
}

template <class T, class Container>  
bool 
operator <= (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
{
	return (lhs.c <= rhs.c);
}

template <class T, class Container>  
bool 
operator >= (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
{
	return (lhs.c >= rhs.c);
}

}   // ft

#endif  // __STACK_HPP__
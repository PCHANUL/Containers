/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:12:08 by cpak              #+#    #+#             */
/*   Updated: 2022/10/06 15:15:57 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ITERATOR_TRAITS_HPP__
#define __ITERATOR_TRAITS_HPP__

namespace ft
{

template <class Iterator> 
class iterator_traits
{
    private:

    public:

};

template <class T> 
class iterator_traits<T*>
{
    private:

    public:
};


template <class T> 
class iterator_traits<const T*>
{
    private:

    public:
};



} // namespace ft
#endif // __ITERATOR_TRAITS_HPP__







#endif // __ITERATOR_TRAITS_HPP__
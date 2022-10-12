/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 18:04:49 by cpak              #+#    #+#             */
/*   Updated: 2022/10/12 18:06:13 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef __TYPE_TRAITS_HPP__
#define __TYPE_TRAITS_HPP__

namespace ft
{

template <bool, typename T = void>
struct enable_if {};

template <typename T>
struct enable_if<true, T> {
    typedef T type;
};

} // namespace ft

#endif // __TYPE_TRAITS_HPP__
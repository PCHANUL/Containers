/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftexcept.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 18:53:26 by cpak              #+#    #+#             */
/*   Updated: 2022/10/21 11:49:32 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FTEXCEPT_HPP__
#define __FTEXCEPT_HPP__
#include <exception>

namespace ft
{

class logic_error : public std::exception
{
private:
	const char*	__str;

public:
	logic_error(const char* str) : __str(str) {}

	virtual const char* what() const throw() { return (this->__str); }
};

class length_error : public logic_error
{
public:
	length_error(const char* str) : logic_error(str) {}
};

class out_of_range : public logic_error
{
public:
	out_of_range(const char* str) : logic_error(str) {}
};

};

#endif // __FTEXCEPT_HPP__

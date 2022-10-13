/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:03:31 by cpak              #+#    #+#             */
/*   Updated: 2022/10/13 19:01:36 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ITERATOR_HPP__
#define __ITERATOR_HPP__
#include <cstddef>
#include "iterator_traits.hpp"

namespace ft
{

template <class Category, class T, class Distance = ptrdiff_t, 
			class Pointer = T*, class Reference = T&>
struct iterator 
{
	typedef T			value_type;
	typedef Distance	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
	typedef Category	iterator_category;
};

template <class T>
class v_iter
{

public:
	typedef T								value_type;
	typedef ptrdiff_t						difference_type;
	typedef T*								pointer;
	typedef T&								reference;
	typedef ft::random_access_iterator_tag	iterator_category;

protected:
	pointer	__i;

public:
	v_iter();
	v_iter(T* __i);
	v_iter(const v_iter& __x);
	v_iter&		operator =	(const v_iter& __x);
	reference	operator *	() const;
	pointer		operator ->	() const;
	v_iter& 	operator ++	();
	v_iter		operator ++	(int);
	v_iter&		operator -- ();
	v_iter		operator -- (int);
	v_iter		operator +	(difference_type n) const;
	v_iter		operator +=	(difference_type n);
	v_iter		operator -	(difference_type n) const;
	v_iter		operator -=	(difference_type n);
	reference	operator []	(difference_type n) const;
	bool		operator ==	(const v_iter& rhs) const;
	bool		operator !=	(const v_iter& rhs) const;
	bool		operator <	(const v_iter& rhs) const;
	bool		operator <=	(const v_iter& rhs) const;
	bool		operator >	(const v_iter& rhs) const;
	bool		operator >=	(const v_iter& rhs) const;
};

template<class T>
ft::v_iter<T>::v_iter(T* __i) : __i(__i)
{
}

template<class T>
ft::v_iter<T>::v_iter(const ft::v_iter<T>& __x) : __i(__x.__i)
{
}

template<class T>
ft::v_iter<T>&
ft::v_iter<T>::operator = (const ft::v_iter<T>& __x)
{
	if (__x.__i != __i)
		__i = __x.__i;
	return (*this);
}

template<class T>
T&
ft::v_iter<T>::operator * () const
{
	return (*__i);
}

template<class T>
T*
ft::v_iter<T>::operator -> () const
{
	return (__i);
}

template<class T>
ft::v_iter<T>&
ft::v_iter<T>::operator ++	() 
{ 
	++__i; 
	return (*this); 
}

template<class T>
ft::v_iter<T>
ft::v_iter<T>::operator ++	(int) 
{ 
	v_iter tmp(*this);
	operator++();
	return (tmp);
}

template<class T>
ft::v_iter<T>&
ft::v_iter<T>::operator --	() 
{ 
	--__i; 
	return (*this); 
}

template<class T>
ft::v_iter<T>
ft::v_iter<T>::operator --	(int) 
{ 
	v_iter tmp(*this);
	operator--();
	return (tmp);
}

template<class T>
bool
ft::v_iter<T>::operator ==	(const v_iter& rhs) const
{
	return (__i == rhs.__i);
}

template<class T>
bool
ft::v_iter<T>::operator !=	(const v_iter& rhs) const
{
	return (__i != rhs.__i);
}


} // namespace ft

#endif // __ITERATOR_HPP__

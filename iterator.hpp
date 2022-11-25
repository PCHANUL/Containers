/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:03:31 by cpak              #+#    #+#             */
/*   Updated: 2022/11/25 19:05:45 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ITERATOR_HPP__
#define __ITERATOR_HPP__
#include <cstddef>
#include "iterator_traits.hpp"
#include "ftexcept.hpp"
#include "utility.hpp"

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

template <class TreeIter, bool B>
class m_iter
{
	typedef typename TreeIter::value_type								__node_type;

public:
	typedef typename TreeIter::value_type								value_type;
	typedef typename TreeIter::difference_type							difference_type;
	typedef std::bidirectional_iterator_tag								iterator_category;
	typedef typename choose<B, const value_type*, value_type*>::type	pointer;
	typedef typename choose<B, const value_type&, value_type&>::type	reference;

private:
	pointer	__i;

public:
	m_iter();
	m_iter(pointer __x);
	m_iter(const m_iter<TreeIter, false>& __x);
	~m_iter();
	m_iter&		operator =	(const m_iter& __x);

	pointer		base() const;
	reference	operator *	() const;
	pointer		operator ->	() const;
	m_iter& 	operator ++	();
	m_iter		operator ++	(int);
	m_iter&		operator -- ();
	m_iter		operator -- (int);
	reference	operator []	(difference_type n) const;
};

template <class TreeIter, bool B>
ft::m_iter<TreeIter, B>::m_iter() : __i(nullptr)
{
}

template <class TreeIter, bool B>
ft::m_iter<TreeIter, B>::m_iter(pointer __x) : __i(__x)
{
}

template <class TreeIter, bool B>
ft::m_iter<TreeIter, B>::m_iter(const m_iter<TreeIter, false>& __x) : __i(__x.__i)
{
}

template <class TreeIter, bool B>
ft::m_iter<TreeIter, B>::~m_iter()
{
}

template <class TreeIter, bool B>
typename ft::m_iter<TreeIter, B>::pointer
ft::m_iter<TreeIter, B>::base() const
{
	return (this->__i);
}

template <class TreeIter, bool B>
ft::m_iter<TreeIter, B>&		
ft::m_iter<TreeIter, B>::operator = (const m_iter& __x)
{
	if (__x.__i != this->__i)
		this->__i = __x.__i;
	return (*this);
}

template <class TreeIter, bool B>
typename ft::m_iter<TreeIter, B>::reference
ft::m_iter<TreeIter, B>::operator * () const
{
	return (*(this->__i));
}

template <class TreeIter, bool B>
typename ft::m_iter<TreeIter, B>::pointer		
ft::m_iter<TreeIter, B>::operator -> () const
{
	return (this->__i.base());
}

template <class TreeIter, bool B>
ft::m_iter<TreeIter, B>& 	
ft::m_iter<TreeIter, B>::operator ++ ()
{
	++__i;
	return (*this);
}

template <class TreeIter, bool B>
ft::m_iter<TreeIter, B>
ft::m_iter<TreeIter, B>::operator ++ (int)
{
	m_iter	tmp(*this);
	__i++;
	return (tmp);
}

template <class TreeIter, bool B>
ft::m_iter<TreeIter, B>& 	
ft::m_iter<TreeIter, B>::operator -- ()
{
	--__i;
	return (*this);
}

template <class TreeIter, bool B>
ft::m_iter<TreeIter, B>
ft::m_iter<TreeIter, B>::operator -- (int)
{
	m_iter	tmp(*this);
	__i--;
	return (tmp);
}

template <class T1, class T2, bool B1, bool B2>
bool
operator == (const ft::m_iter<T1, B1>& lhs, const ft::m_iter<T2, B2>& rhs)
{
	return (lhs.base() == rhs.base());
}

template <class T1, class T2, bool B1, bool B2>
bool
operator != (const ft::m_iter<T1, B1>& lhs, const ft::m_iter<T2, B2>& rhs)
{
	return (lhs.base() != rhs.base());
}

template <class T, bool B>
class v_iter
{

public:
	typedef T										value_type;
	typedef ptrdiff_t								difference_type;
	typedef typename choose<B, const T&, T&>::type	reference;
	typedef typename choose<B, const T*, T*>::type	pointer;
	typedef std::random_access_iterator_tag			iterator_category;

protected:
	pointer	__i;

public:
	v_iter();
	v_iter(pointer __x);
	v_iter(const v_iter<T, false>& __x);
	~v_iter();

	pointer			base() const;
	v_iter&			operator =	(const v_iter& __x);
	reference		operator *	() const;
	pointer			operator ->	() const;
	v_iter& 		operator ++	();
	v_iter			operator ++	(int);
	v_iter&			operator -- ();
	v_iter			operator -- (int);
	v_iter			operator +	(difference_type n) const;
	v_iter&			operator +=	(difference_type n);
	v_iter			operator -	(difference_type n) const;
	v_iter&			operator -=	(difference_type n);
	reference		operator []	(difference_type n) const;
};

template <class T, bool B>
ft::v_iter<T, B>::v_iter() : __i(nullptr)
{
}

template <class T, bool B>
ft::v_iter<T, B>::v_iter(pointer __x) : __i(__x)
{
}

template <class T, bool B>
ft::v_iter<T, B>::v_iter(const v_iter<T, false>& __x) : __i(__x.base())
{
}

template <class T, bool B>
ft::v_iter<T, B>::~v_iter()
{
}

template <class T, bool B>
typename ft::v_iter<T, B>::pointer
ft::v_iter<T, B>::base() const
{
	return (__i);
}

template <class T, bool B>
ft::v_iter<T, B>&
ft::v_iter<T, B>::operator = (const ft::v_iter<T, B>& __x)
{
	if (__x.__i != this->__i)
		this->__i = __x.__i;
	return (*this);
}

template <class T, bool B>
typename ft::v_iter<T, B>::reference
ft::v_iter<T, B>::operator * () const
{
	return (*(this->__i));
}

template <class T, bool B>
typename ft::v_iter<T, B>::pointer
ft::v_iter<T, B>::operator -> () const
{
	return (this->__i);
}

template <class T, bool B>
ft::v_iter<T, B>&
ft::v_iter<T, B>::operator ++ () 
{ 
	++this->__i; 
	return (*this); 
}

template <class T, bool B>
ft::v_iter<T, B>
ft::v_iter<T, B>::operator ++ (int) 
{ 
	v_iter tmp(*this);
	++(*this);
	return (tmp);
}

template <class T, bool B>
ft::v_iter<T, B>&
ft::v_iter<T, B>::operator -- () 
{ 
	this->__i--; 
	return (*this); 
}

template <class T, bool B>
ft::v_iter<T, B>
ft::v_iter<T, B>::operator -- (int) 
{ 
	v_iter tmp(*this);
	--(*this);
	return (tmp);
}

template <class T, bool B>
ft::v_iter<T, B>
ft::v_iter<T, B>::operator + (difference_type n) const
{ 
	v_iter tmp(*this);
	tmp += n;
	return (tmp);
}

template <class T, bool B>
ft::v_iter<T, B>&
ft::v_iter<T, B>::operator += (difference_type n)
{ 
	this->__i += n;
	return (*this);
}

template <class T, bool B>
ft::v_iter<T, B>
ft::v_iter<T, B>::operator - (difference_type n) const
{ 
	v_iter tmp(base() - n);
	return (tmp);
}

template <class T, bool B>
ft::v_iter<T, B>&
ft::v_iter<T, B>::operator -= (difference_type n)
{ 
	this->__i -= n;
	return (*this);
}

template <class T, bool B>
typename ft::v_iter<T, B>::reference
ft::v_iter<T, B>::operator [] (difference_type n) const
{
	return (__i[n]);
}

template <class T1, class T2, bool B1, bool B2>
bool
operator == (const ft::v_iter<T1, B1>& lhs, const ft::v_iter<T2, B2>& rhs)
{
	return (lhs.base() == rhs.base());
}

template <class T1, class T2, bool B1, bool B2>
bool
operator != (const ft::v_iter<T1, B1>& lhs, const ft::v_iter<T2, B2>& rhs)
{
	return (lhs.base() != rhs.base());
}

template <class T1, class T2, bool B1, bool B2>
bool
operator < (const ft::v_iter<T1, B1>& lhs, const ft::v_iter<T2, B2>& rhs)
{
	return (lhs.base() < rhs.base());
}

template <class T1, class T2, bool B1, bool B2>
bool
operator <= (const ft::v_iter<T1, B1>& lhs, const ft::v_iter<T2, B2>& rhs)
{
	return (lhs.base() <= rhs.base());
}

template <class T1, class T2, bool B1, bool B2>
bool
operator > (const ft::v_iter<T1, B1>& lhs, const ft::v_iter<T2, B2>& rhs)
{
	return (lhs.base() > rhs.base());
}

template <class T1, class T2, bool B1, bool B2>
bool
operator >= (const ft::v_iter<T1, B1>& lhs, const ft::v_iter<T2, B2>& rhs)
{
	return (lhs.base() >= rhs.base());
}

template <class T, bool B>  
ft::v_iter<T, B> 
operator + (typename ft::v_iter<T, B>::difference_type n, const ft::v_iter<T, B>& it)
{
	ft::v_iter<T, B>	tmp(it.base() + n);
	return (tmp);
}

// lhs와 rhs 사이의 거리를 반환합니다. 이 함수는 rhs의 기본 반복기에서 lhs의 기본 반복기를 빼는 것과 동일한 값을 반환합니다.
template <class T1, class T2, bool B1, bool B2>  
typename ft::v_iter<T1, B1>::difference_type 
operator - (const ft::v_iter<T1, B1>& lhs, const ft::v_iter<T2, B2>& rhs)
{
	return (lhs.base() - rhs.base());
}

template <class It>
typename iterator_traits<It>::difference_type
__distance (It first, It last, std::random_access_iterator_tag)
{
	return (last.base() - first.base());
}

template <class It>
typename iterator_traits<It>::difference_type
__distance (It first, It last, std::input_iterator_tag)
{
	typename ft::iterator_traits<It>::difference_type result = 0;

    while (first != last) 
	{
        ++first;
        ++result;
    }

    return result;
}

// first와 last의 거리를 반환
// - Exception : first 메모리 주소가 last보다 크다면 ft::lenth_error: vector
template <class It>  
typename iterator_traits<It>::difference_type    
distance (It first, It last,
			typename ft::enable_if<ft::is_iterator<It>::value, It>::type* = 0)
{
	return (ft::__distance(first, last, typename ft::iterator_traits<It>::iterator_category()));
}

template <class Iterator>
class reverse_iterator
{

public:
	typedef Iterator													iterator_type;
	typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
	typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
	typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
	typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
	typedef typename ft::iterator_traits<Iterator>::reference			reference;

protected:
	iterator_type	__iter;

public:
	reverse_iterator();
	explicit reverse_iterator (iterator_type it);
	template <class Iter>  reverse_iterator (const reverse_iterator<Iter>& rev_it);
	
	iterator_type 		base() const;

	reference			operator *	() const;
	reverse_iterator&	operator +=	(difference_type n);
	reverse_iterator	operator +	(difference_type n) const;
	reverse_iterator&	operator ++	();
	reverse_iterator 	operator ++	(int);
	reverse_iterator&	operator -=	(difference_type n);
	reverse_iterator	operator -	(difference_type n) const;
	reverse_iterator&	operator --	();
	reverse_iterator 	operator --	(int);
	pointer				operator ->	() const;
	reference			operator []	(difference_type n) const;

};

// 객체를 가리키지 않는 역방향 반복기를 생성합니다.
// 내부 base iterator는 값으로 초기화됩니다.
template <class Iterator>
ft::reverse_iterator<Iterator>::reverse_iterator() : __iter()
{
}

// 원래의 반복자로부터 역방향 반복자를 생성합니다. 생성된 객체의 동작은 포인트 요소를 역순으로 반복한다는 점을 제외하고 원본을 복제합니다.
// it : 생성된 객체에서 반복의 의미가 반전된 반복자입니다. 멤버 유형 iterator_type은 기본 양방향 반복기 유형(클래스 템플릿 매개변수: Iterator)입니다.
template <class Iterator>
ft::reverse_iterator<Iterator>::reverse_iterator (iterator_type it) : __iter(it)
{
}

// 다른 역방향 반복자로부터 역방향 반복자를 생성합니다. 생성된 객체는 rev_it과 동일한 반복 감각을 유지합니다.
// rev_it : 유지되는 reverse_iterator 유형의 반복자입니다.
template <class Iterator>
template <class Iter>  
ft::reverse_iterator<Iterator>::reverse_iterator (const reverse_iterator<Iter>& rev_it) : __iter(rev_it.base())
{
}

// base_itertor 복사본을 반환합니다.
// 기본 반복자는 reverse_iterator를 구성하는 데 사용된 것과 동일한 유형의 반복자이지만 
// reverse_iterator가 현재 가리키는 요소 옆에 있는 요소를 가리킵니다.
// (reverse_iterator는 기본 반복자와 관련하여 항상 오프셋이 -1입니다.)
// return : 반대 방향으로 반복되는 기본 반복기의 복사본입니다. 멤버 유형 iterator_type은 기본 양방향 반복기 유형(클래스 템플릿 매개변수: Iterator)입니다.
template <class Iterator>
typename ft::reverse_iterator<Iterator>::iterator_type 
ft::reverse_iterator<Iterator>::base() const
{
	return (__iter);
}

// 반복자가 가리키는 요소에 대한 참조를 반환합니다.
template <class Iterator>
typename ft::reverse_iterator<Iterator>::reference 
ft::reverse_iterator<Iterator>::operator * () const
{
	reverse_iterator tmp(__iter);
	return (*(--tmp.__iter));
}

// n 요소 위치만큼 reverse_iterator를 진행합니다.
// 내부적으로 함수는 객체가 유지하는 기본 반복자를 n만큼 감소합니다(연산자-=를 적용하는 것처럼).
template <class Iterator>
ft::reverse_iterator<Iterator>&
ft::reverse_iterator<Iterator>::operator += (difference_type n)
{
	__iter -= n;
	return (*this);
}

// 현재 반복자가 가리키는 요소에서 n 위치 떨어진 요소를 가리키는 역방향 반복자를 반환합니다.
// 내부적으로 이 함수는 기본 반복기에 연산자 - 를 적용하고 결과 반복기 값으로 구성된 역방향 반복기를 반환합니다.
template <class Iterator>
ft::reverse_iterator<Iterator>
ft::reverse_iterator<Iterator>::operator + (difference_type n) const
{
	reverse_iterator tmp(__iter - n);
	return (tmp);
}

// reverse_iterator를 하나 진행합니다.
// 내부적으로 객체에 의해 유지되는 기본 반복자를 감소시킵니다. 연산자-- 와 같습니다.
template <class Iterator>
ft::reverse_iterator<Iterator>&
ft::reverse_iterator<Iterator>::operator ++ ()
{
	--__iter;
	return (*this);
}

// reverse_iterator를 하나 진행합니다.
// 내부적으로 기본 반복자를 반환하여, 기본 반복자를 감소시킵니다.
template <class Iterator>
ft::reverse_iterator<Iterator>
ft::reverse_iterator<Iterator>::operator ++ (int)
{
	reverse_iterator tmp(*this);
	__iter--;
	return tmp;
}

// n 요소 위치만큼 reverse_iterator를 줄입니다.
// 내부적으로 함수는 객체가 유지하는 기본 반복자를 n만큼 증가시킵니다(연산자+=를 적용하는 것처럼).
template <class Iterator>
ft::reverse_iterator<Iterator>& 
ft::reverse_iterator<Iterator>::operator -= (difference_type n)
{
	__iter += n;
	return (*this);
}

// 반복자가 현재 가리키는 요소보다 n 위치에 있는 요소를 가리키는 역방향 반복자를 반환합니다.
// 내부적으로 이 함수는 기본 반복기에 이진 연산자+를 적용하고 결과 반복기 값으로 구성된 역방향 반복기를 반환합니다.
template <class Iterator>
ft::reverse_iterator<Iterator>
ft::reverse_iterator<Iterator>::operator - (difference_type n) const
{
	reverse_iterator tmp(__iter + n);
	return (tmp);
}

// reverse_iterator를 한 위치만큼 감소시킵니다.
// 내부적으로 사전 감소 버전(1)은 (연산자++를 적용하는 것처럼) 객체가 유지하는 기본 반복자를 증가시킵니다.
template <class Iterator>
ft::reverse_iterator<Iterator>& 
ft::reverse_iterator<Iterator>::operator -- ()
{
	++__iter;
	return (*this);
}

// reverse_iterator를 한 위치만큼 감소시킵니다.
// 내부적으로 기본 반복자를 반환하여, 기본 반복자를 증가시킵니다.
template <class Iterator>
ft::reverse_iterator<Iterator>  
ft::reverse_iterator<Iterator>::operator -- (int)
{
	reverse_iterator tmp = *this;
	__iter++;
	return (tmp);
}

// 반복자가 가리키는 요소에 대한 포인터를 반환합니다(구성원 중 하나에 액세스하기 위해).
// 내부적으로 함수는 연산자*를 호출하고 다음과 같이 구현된 것처럼 주소를 반환합니다.
template <class Iterator>
typename ft::reverse_iterator<Iterator>::pointer 
ft::reverse_iterator<Iterator>::operator -> () const
{
	return (&(operator*()));
}

// 반복자가 현재 가리키는 요소에서 n 위치 떨어진 요소에 액세스합니다.
// 이러한 요소가 없으면 정의되지 않은 동작이 발생합니다. 
// 내부적으로 함수는 기본 반복자의 적절한 요소에 액세스하여 base()[-n-1]과 동일한 결과를 반환합니다.
template <class Iterator>
typename ft::reverse_iterator<Iterator>::reference 
ft::reverse_iterator<Iterator>::operator [] (difference_type n) const
{
	return (*(*this + n));
}

// reverse_iterator 개체 lhs와 rhs 간에 적절한 비교 작업을 수행합니다. 
// 내부적으로 함수는 반사적으로 동등한 관계 연산자를 사용하여 기본 반복자를 직접 비교합니다.
template <class Iterator1, class Iterator2>
bool 
operator == (const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
{
	return (lhs.base() == rhs.base());
}

template <class Iterator1, class Iterator2>  
bool 
operator != (const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
{
	return (lhs.base() != rhs.base());
}

template <class Iterator1, class Iterator2>
bool 
operator <  (const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
{
	return (lhs.base() > rhs.base());
}

template <class Iterator1, class Iterator2>
bool 
operator <= (const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
{
	return (lhs.base() >= rhs.base());
}

template <class Iterator1, class Iterator2>
bool 
operator >  (const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
{
	return (lhs.base() < rhs.base());
}

template <class Iterator1, class Iterator2>
bool 
operator >= (const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
{
	return (lhs.base() <= rhs.base());
}

// rev_it가 가리키는 요소에서 n 위치 떨어진 요소를 가리키는 역방향 반복자를 반환합니다. 
// 이 함수는 rev_it+n과 동일한 결과를 반환합니다(reverse_iterator::operator+ 참조). 
// 이 연산자는 -n 요소 위치만큼 역방향 반복기 오프셋을 반환하는 멤버 함수로도 오버로드됩니다(reverse_iterator::operator- 참조).
template <class Iterator>  
ft::reverse_iterator<Iterator> 
operator + (typename ft::reverse_iterator<Iterator>::difference_type n, const ft::reverse_iterator<Iterator>& rev_it)
{
	ft::reverse_iterator<Iterator>	tmp(rev_it.base() - n);
	return (tmp);
}

// lhs와 rhs 사이의 거리를 반환합니다. 이 함수는 rhs의 기본 반복기에서 lhs의 기본 반복기를 빼는 것과 동일한 값을 반환합니다.
template <class Iterator1, class Iterator2>
typename ft::reverse_iterator<Iterator1>::difference_type 
operator - (const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
{
	return (rhs.base() - lhs.base());
}

} // ft

#endif // __ITERATOR_HPP__

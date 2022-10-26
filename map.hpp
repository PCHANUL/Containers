/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:42:13 by cpak              #+#    #+#             */
/*   Updated: 2022/10/26 18:26:28 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <memory>
#include "type_traits.hpp"
#include "iterator.hpp"

#include <utility>

namespace ft
{

template <class T> 
struct less {
    bool operator() (const T& x, const T& y) const {return x<y;}
    typedef T first_argument_type;
    typedef T second_argument_type;
    typedef bool result_type;
};


template <class T1, class T2>
struct pair
{

public:
    typedef T1      first_type;
    typedef T2      second_type;


    first_type      first;
    second_type     second;

    pair();
    pair (const first_type& a, const second_type& b);
    template<class U, class V> pair (const pair<U,V>& pr);
    pair& operator =  (const pair& pr);
};

// 요소 값으로 초기화된 쌍 개체를 생성합니다.
template <class T1, class T2>
ft::pair<T1, T2>::pair() : first(), second()
{
}

// first 맴버는 a로 구성되고, second 맴버는 b로 구성됩니다.
template <class T1, class T2>
ft::pair<T1, T2>::pair (const first_type& a, const second_type& b) : first(a), second(b)
{
}

// 개체는 pr 개체의 내용으로 초기화됩니다.
template <class T1, class T2>
template<class U, class V> 
ft::pair<T1, T2>::pair (const pair<U,V>& pr) : first(pr.first), second(pr.second)
{
}

// 개체가 복사되어 할당됩니다.
template <class T1, class T2>
ft::pair<T1, T2>& 
ft::pair<T1, T2>::operator = (const pair& pr)
{
    if ((pr.first != first) && (pr.second != second))
    {
        first = pr.first;
        second = pr.second;
    }
    return (*this);
}

template <class T1, class T2>
bool 
operator == (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
{
    return ((lhs.first == rhs.first) && (lhs.second == rhs.second));
}

template <class T1, class T2>
bool 
operator != (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
{
    return ((lhs.first != rhs.first) || (lhs.second != rhs.second));
}

template <class T1, class T2>
bool 
operator < (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
{
    return ((lhs.first < rhs.first) || (lhs.second < rhs.second));
}

template <class T1, class T2>
bool 
operator <= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
{
    return ((lhs.first <= rhs.first) || (lhs.second <= rhs.second));
}

template <class T1, class T2>
bool 
operator > (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
{
    return ((lhs.first > rhs.first) || (lhs.second > rhs.second));
}

template <class T1, class T2>
bool 
operator >= ( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
{
    return ((lhs.first >= rhs.first) || (lhs.second >= rhs.second));
}

template <class T1, class T2>
ft::pair<T1, T2>
make_pair(T1 t, T2 u)
{
    return (ft::pair<T1, T2>(t, u));
}

    
template <class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T>> >
class map
{

protected:
    typedef std::allocator_traits<Alloc>                __alloc_traits;

public:
    typedef Key                                         key_type;
    typedef T                                           mapped_type;
    typedef ft::pair<const key_type, mapped_type>       value_type;
    typedef typename __alloc_traits::size_type          size_type;
    typedef typename __alloc_traits::difference_type	difference_type;
	typedef Compare										key_compare;
	typedef Alloc										allocator_type;
	typedef value_type&									reference;
	typedef const value_type&							const_reference;
	typedef typename __alloc_traits::pointer			pointer;
	typedef typename __alloc_traits::const_pointer		const_pointer;
	typedef ft::m_iter<value_type>						iterator;
	typedef ft::m_iter<const value_type>				const_iterator;
	typedef ft::reverse_iterator<iterator>				reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;


	explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
	template <class InputIterator>
	map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
	map (const map& x);
	~map();
	
	map& operator =	(const map& x);

	iterator				begin();
	const_iterator			begin() const;
	iterator				end();
	const_iterator			end() const;
	reverse_iterator 		begin();
	const_reverse_iterator	rbegin() const;

	bool 					empty() const;
	size_type 				size() const;
	size_type 				max_size() const;


};

// 요소가 없는 빈 컨테이너를 생성합니다.
template <class Key, class T, class Compare, class Alloc>
ft::map<Key, T, Compare, Alloc>::map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
{}

// 범위 [first,last)만큼 많은 요소가 있는 컨테이너를 생성하고, 각 요소는 해당 범위의 해당 요소로 구성됩니다.
template <class Key, class T, class Compare, class Alloc>
template <class InputIterator>
ft::map<Key, T, Compare, Alloc>::map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
{}

// x의 각 요소의 복사본으로 컨테이너를 생성합니다.
template <class Key, class T, class Compare, class Alloc>
ft::map<Key, T, Compare, Alloc>::map (const map& x)
{}

// 이것은 모든 컨테이너 요소를 파괴하고 할당자를 사용하여 맵 컨테이너에 의해 할당된 모든 저장 용량을 할당 해제합니다.
template <class Key, class T, class Compare, class Alloc>
ft::map<Key, T, Compare, Alloc>::~map ()
{}

// 현재 콘텐츠를 대체하여 컨테이너에 새 콘텐츠를 할당합니다.
// x 의 모든 요소를 ​​컨테이너에 복사하여 그에 따라 크기 를 변경합니다 .
// 호출 전에 컨테이너에 저장된 요소는 할당되거나 소멸됩니다.
template <class Key, class T, class Compare, class Alloc>
ft::map<Key, T, Compare, Alloc>& 
ft::map<Key, T, Compare, Alloc>::operator = (const map& x)
{}

// 맵 컨테이너의 첫 번째 요소를 참조하는 반복자를 반환합니다. 
// 맵 컨테이너는 요소의 순서를 항상 유지하기 때문에 begin은 컨테이너의 정렬 기준으로 다음에 오는 요소를 가리킵니다. 
// 컨테이너가 비어있으면 반환된 반복기 값은 역참조되지 않습니다. 
template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::iterator
ft::map<Key, T, Compare, Alloc>::begin()
{}

// 객체가 const로 한정된 경우 const_iterator를 반환합니다.
template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::const_iterator
ft::map<Key, T, Compare, Alloc>::begin() const
{}

// 맵 컨테이너의 마지막 다음 요소를 참조하는 반복자를 반환합니다. 
// 마지막 다음 요소는 이론적인 요소이며, 맵 컨테이너 마지막 다음에 위치합니다.
template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::iterator
ft::map<Key, T, Compare, Alloc>::end()
{}

// 객체가 const로 한정된 경우 const_iterator를 반환합니다.
template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::const_iterator
ft::map<Key, T, Compare, Alloc>::end() const
{}

// 컨테이너의 마지막 요소를 가리키는 역방향 반복자를 반환합니다.
// 역방향 반복자는 반대로 진행합니다.
template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::reverse_iterator
ft::map<Key, T, Compare, Alloc>::rbegin()
{}

// 객체가 const로 한정된 경우 const_reverse_iterator를 반환합니다.
template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::const_reverse_iterator
ft::map<Key, T, Compare, Alloc>::rbegin() const
{}

// 컨테이너의 첫번째 요소를 가리키는 역방향 반복자를 반환합니다.
// 역방향 반복자의 끝으로 간주되는 이론적 요소를 가리킵니다.
template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::reverse_iterator
ft::map<Key, T, Compare, Alloc>::rend()
{}

// 객체가 const로 한정된 경우 const_reverse_iterator를 반환합니다.
template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::const_reverse_iterator
ft::map<Key, T, Compare, Alloc>::rend() const
{}

// 컨테이너가 비어있는지 확인하고 bool 값을 반환합니다.
template <class Key, class T, class Compare, class Alloc>
bool 
ft::map<Key, T, Compare, Alloc>::empty() const
{}

// 컨테이너의 요소 개수를 반환합니다.
template <class Key, class T, class Compare, class Alloc>
bool 
ft::map<Key, T, Compare, Alloc>::size() const
{}

// 컨테이너가 보유할 수 있는 최대 요소의 수를 반환합니다.
template <class Key, class T, class Compare, class Alloc>
bool 
ft::map<Key, T, Compare, Alloc>::size() const
{}





} // ft

#endif // __MAP_HPP__
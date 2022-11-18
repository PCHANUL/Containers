/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:29:39 by cpak              #+#    #+#             */
/*   Updated: 2022/11/18 14:44:58 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PAIR_HPP__
#define __PAIR_HPP__

namespace ft
{

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
    first = pr.first;
    second = pr.second;
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

template <class T1, class T2>
std::ostream&	operator << (std::ostream& os, const ft::pair<T1, T2>& origin)
{
    T1  first = origin.first;
    T2  second = origin.second;

    os << "{";
    if (first != T1()) { os << first; }
    else { os << "null"; }
    os << ": ";
    if (second != T2()) { os << second; }
    else { os << "null"; }
    os << "}";
    return (os);
}
   
}

#endif // __PAIR_HPP__

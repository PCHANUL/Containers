/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:31:14 by cpak              #+#    #+#             */
/*   Updated: 2022/10/05 16:20:59 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__
#include <memory>

namespace ft {
	
template <class T, class Alloc = std::allocator<T>>
class vector 
{
	
private:

	/* data */
public:
	typedef T											value_type;
	typedef Alloc										allocator_type;
	typedef allocator_type::reference					reference;
	typedef allocator_type::const_reference				const_reference;
	typedef allocator_type::pointer						pointer;
	typedef allocator_type::const_pointer				const_pointer;
	typedef 											iterator;
	typedef 											const_iterator;
	typedef reverse_iterator<iterator>              	reverse_iterator;
	typedef reverse_iterator<const_iterator>        	const_reverse_iterator;
	typedef 											difference_type;
	typedef 											size_type;

	explicit vector (const allocator_type& alloc = allocator_type());
	explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
	template <class InputIterator> vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
	vector (const vector& x);
	~vector();
	
	vector& operator = (const vector& x);

	iterator 				begin();
	const_iterator 			begin() const;
	iterator 				end();
	const_iterator 			end() const;
	reverse_iterator 		rbegin();
	const_reverse_iterator 	rbegin() const;
	reverse_iterator 		rend();
	const_reverse_iterator 	rend() const;

	size_type	size() const;
	size_type	max_size() const;
	void		resize (size_type n, value_type val = value_type());
	size_type	capacity() const;
	bool		empty() const;
	void		reserve (size_type n);



	
};

template<class T, class Alloc>
ft::vector<T, Alloc>::vector(const allocator_type& alloc = allocator_type())
{
	// Constructs an empty container, with no elements.
	// 요소가 없는 빈 컨테이너를 생성합니다.
}

template<class T, class Alloc>
ft::vector<T, Alloc>::vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
{
	// Constructs a container with n elements. Each element is a copy of val.
	// n개의 요소 가 있는 컨테이너를 생성합니다. 각 요소는 val 의 복사본입니다 .
}

template<class T, class Alloc>
template <class InputIterator>
ft::vector<T, Alloc>::vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
{
	// Constructs a container with as many elements as the range [first,last), 
	// with each element constructed from its corresponding element in that range, in the same order.
	// [first,last) 범위만큼 많은 요소가 있는 컨테이너를 구성하고 , 각 요소는 해당 범위의 해당 요소에서 동일한 순서로 구성됩니다.
	// - first, last : 범위의 처음과 마지막 위치이다. first는 첫 요소를 가리키지만 last는 마지막 요소를 가리키지 않는다. 
}

template<class T, class Alloc>
ft::vector<T, Alloc>::vector (const vector& x)
{
	// Constructs a container with a copy of each of the elements in x, in the same order.
	// 동일한 순서로 x 의 각 요소 복사본을 사용하여 컨테이너를 생성합니다.
}


template<class T, class Alloc>
ft::vector<T, Alloc>::~vector()
{
	// This destroys all container elements, and deallocates all the storage capacity allocated by the vector using its allocator.
	// 이것은 모든 컨테이너 요소를 파괴하고 할당자를 사용하여 벡터에 의해 할당된 모든 저장 용량 을 할당 해제 합니다 .
}

template<class T, class Alloc>
ft::vector<T, Alloc>& 
ft::vector<T, Alloc>::operator = (const vector& x)
{
	// Copies all the elements from x into the container.
	// The container preserves its current allocator, which is used to allocate storage in case of reallocation.
	// x 의 모든 요소를 ​​컨테이너에 복사합니다. 컨테이너 는 재할당의 경우 스토리지를 할당하는 데 사용되는 현재 할당자를 유지합니다.
}

template<class T, class Alloc>
typename ft::vector<T, Alloc>::iterator 
ft::vector<T, Alloc>::begin()
{
	// Returns an iterator pointing to the first element in the vector.
	// 벡터 의 첫 번째 요소를 가리키는 반복자를 반환합니다 . 
}

template<class T, class Alloc>
typename ft::vector<T, Alloc>::const_iterator 
ft::vector<T, Alloc>::begin() const
{
	// If the vector object is const-qualified, the function returns a const_iterator. Otherwise, it returns an iterator.
	// 객체가 const로 한정된 경우 함수는 const_iterator 를 반환합니다 . 그렇지 않으면 iterator 를 반환합니다 . 멤버 유형 iterator 및 const_iterator 는 임의 액세스 반복기 유형입니다(각각 요소 및 const 요소를 가리킴).
}

template<class T, class Alloc>
typename ft::vector<T, Alloc>::iterator 
ft::vector<T, Alloc>::end()
{
	// Returns an iterator referring to the past-the-end element in the vector container.
	// 벡터 컨테이너 의 과거 끝 요소를 참조하는 반복자를 반환합니다 .

	// past-the-end 요소는 벡터의 마지막 요소 뒤에 오는 이론적 요소이다. 어떤 요소도 가리키지 않으므로 역참조되지 않는다.
	// 만약에 컨테이너가 비어있다면 함수는 vector::begin과 같은 값을 반환한다.
}

template<class T, class Alloc>
typename ft::vector<T, Alloc>::const_iterator 
ft::vector<T, Alloc>::end() const
{
	// If the vector object is const-qualified, the function returns a const_iterator. Otherwise, it returns an iterator.
	// 객체가 const로 한정된 경우 함수는 const_iterator 를 반환합니다 . 그렇지 않으면 iterator 를 반환합니다 . 멤버 유형 iterator 및 const_iterator 는 임의 액세스 반복기 유형입니다(각각 요소 및 const 요소를 가리킴).
}

template<class T, class Alloc>
typename ft::vector<T, Alloc>::reverse_iterator 
ft::vector<T, Alloc>::rbegin()
{
	// Returns a reverse iterator pointing to the last element in the vector (i.e., its reverse beginning).

	// 벡터의 마지막을 가리키는 역방향 반복자를 반환한다. 역방향 반복자는 뒤로 반복한다. 
	// rbegin은 end가 가리키는 요소 바로 앞의 요소를 가리킨다. 
}

template<class T, class Alloc>
typename ft::vector<T, Alloc>::const_reverse_iterator 
ft::vector<T, Alloc>::rbegin() const
{
	// If the vector object is const-qualified, the function returns a const_iterator. Otherwise, it returns an iterator.
	// 객체가 const로 한정된 경우 함수는 const_iterator 를 반환합니다 . 그렇지 않으면 iterator 를 반환합니다 . 멤버 유형 iterator 및 const_iterator 는 임의 액세스 반복기 유형입니다(각각 요소 및 const 요소를 가리킴).
}

template<class T, class Alloc>
typename ft::vector<T, Alloc>::reverse_iterator 
ft::vector<T, Alloc>::rend()
{
	// Returns a reverse iterator pointing to the theoretical element preceding the first element in the vector (which is considered its reverse end).

	// 벡터의 첫번째 요소 앞에 있는 이론적인 요소를 가리키는 역방향 iterator를 반환한다.
}

template<class T, class Alloc>
typename ft::vector<T, Alloc>::const_reverse_iterator 
ft::vector<T, Alloc>::rend() const
{
	// If the vector object is const-qualified, the function returns a const_iterator. Otherwise, it returns an iterator.
	// 객체가 const로 한정된 경우 함수는 const_iterator 를 반환합니다 . 그렇지 않으면 iterator 를 반환합니다 . 멤버 유형 iterator 및 const_iterator 는 임의 액세스 반복기 유형입니다(각각 요소 및 const 요소를 가리킴).
}

template<class T, class Alloc>
typename ft::vector<T, Alloc>::size_type
ft::vector<T, Alloc>::size() const
{
	// vector가 가지고 있는 실제 개체의 수를 반환한다. 저장공간의 크기과 같을 필요가 없다. 
}

template<class T, class Alloc>
typename ft::vector<T, Alloc>::size_type
ft::vector<T, Alloc>::max_size() const
{
	// vector가 가질 수 있는 최대 요소의 갯수을 반환한다.
	// 시스템 또는 라이브러리 구현 제한으로 인해 컨테이너가 닿을 수 있는 최대 사이즈를 반환한다.
	// 그러나 최대 사이즈에 닿을 수 있음을 보장하지 않는다. 
}

template<class T, class Alloc>
void
ft::vector<T, Alloc>::resize (size_type n, value_type val = value_type())
{
	// 컨테이너가 n개의 요소를 포함하도록 크기를 조정한다.
	// n이 현재 컨테이너의 크기보다 작다면 초과되는 요소를 제거하고 파괴한다. 
	// n이 현재 컨테이너의 크기보다 크다면 n 크기까지 필요한 요소를 채운다.
	// val이 명시된다면, val의 복사본이 빈 공간을 채운다.
}

template<class T, class Alloc>
typename ft::vector<T, Alloc>::size_type
ft::vector<T, Alloc>::capacity() const
{
	// vector에 할당된 저장공간을 반환한다. 
}

template<class T, class Alloc>
bool
ft::vector<T, Alloc>::empty() const
{
	
}

template<class T, class Alloc>
void
ft::vector<T, Alloc>::reserve (size_type n)
{
	
}



} // namespace ft

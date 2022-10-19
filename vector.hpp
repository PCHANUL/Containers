/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:31:14 by cpak              #+#    #+#             */
/*   Updated: 2022/10/19 10:28:16 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__
#include <memory>
#include <limits>
#include "type_traits.hpp"

namespace ft {
	
template <class T, class Alloc = std::allocator<T> >
class vector 
{

protected:
	typedef std::allocator_traits<Alloc>					__alloc_traits;

public:
	typedef T												value_type;
	typedef Alloc											allocator_type;
	typedef value_type&										reference;
	typedef const value_type&								const_reference;
	typedef typename __alloc_traits::pointer				pointer;
	typedef typename __alloc_traits::const_pointer			const_pointer;
	typedef ft::v_iter<T>									iterator;
	typedef ft::v_iter<T>									const_iterator;
	// typedef ft::reverse_iterator<iterator>					reverse_iterator;
	// typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
	typedef typename __alloc_traits::difference_type		difference_type;
	typedef typename __alloc_traits::size_type				size_type;

protected:
	pointer													__begin;
	pointer													__end;
	pointer													__end_mem;
	allocator_type											__alloc;

public:
	vector (const allocator_type& alloc = allocator_type());
	vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());

	template <class InputIterator>
	vector(InputIterator first,
			typename ft::enable_if<ft::is_iterator<InputIterator>::value, InputIterator>::type last, 
			const allocator_type& alloc = allocator_type());
	vector (const vector& x);
	~vector();
	
	vector& operator = (const vector& x);

	iterator 				begin();
	const_iterator 			begin() const;
	iterator 				end();
	const_iterator 			end() const;
	// reverse_iterator 		rbegin();
	// const_reverse_iterator 	rbegin() const;
	// reverse_iterator 		rend();
	// const_reverse_iterator 	rend() const;

	size_type				size() const;
	size_type				max_size() const;
	void					resize (size_type n, value_type val = value_type());
	size_type				capacity() const;
	bool					empty() const;
	void					reserve (size_type n);

	reference 				operator[] (size_type n);
	const_reference 		operator[] (size_type n) const;
	reference 				at (size_type n);
	const_reference 		at (size_type n) const;
	reference 				front();
	const_reference 		front() const;
	reference 				back();
	const_reference 		back() const;
	value_type* 			data();
	const value_type* 		data() const;

	template <class InputIterator> 
	void					assign (InputIterator first, InputIterator last);
	void					assign (size_type n, const value_type& val);
	void					push_back (const value_type& val);
	void					pop_back();
	iterator				insert (iterator position, const value_type& val);
    void					insert (iterator position, size_type n, const value_type& val);
	template <class InputIterator> 
	void					insert (iterator position, InputIterator first, InputIterator last);
	iterator				erase (iterator position);
	iterator				erase (iterator first, iterator last);
	void					swap (vector& x);
	void					clear();

	allocator_type			get_allocator() const;

	bool					operator ==	(vector& rhs) const;
	bool					operator !=	(vector& rhs) const;
	bool					operator <	(vector& rhs) const;
	bool					operator <=	(vector& rhs) const;
	bool					operator >	(vector& rhs) const;
	bool					operator >=	(vector& rhs) const;

private:
	size_type	__calc_new_size(size_type new_size) const;

};

// Constructs an empty container, with no elements.
// 요소가 없는 빈 컨테이너를 생성합니다.
template<class T, class Alloc>
ft::vector<T, Alloc>::vector(const allocator_type& alloc)
{
	this->__begin = 0;
	this->__end = 0;
	this->__end_mem = 0;
	this->__alloc = alloc;
}

// Constructs a container with n elements. Each element is a copy of val.
// n개의 요소 가 있는 컨테이너를 생성합니다. 각 요소는 val 의 복사본입니다.
template<class T, class Alloc>
ft::vector<T, Alloc>::vector(size_type n, const_reference val, const allocator_type& alloc) : __alloc(alloc)
{
	this->__begin = this->__alloc.allocate(n);
	this->__end = this->__begin + n;
	this->__end_mem = this->__end;

	for (int i=0; i<n; i++)
	{
		const_pointer __new_end = this->__begin + i;
		__alloc_traits::construct(this->__alloc, __new_end, val);
	}
}

// Constructs a container with as many elements as the range [first,last), 
// with each element constructed from its corresponding element in that range, in the same order.
// [first,last) 범위만큼 많은 요소가 있는 컨테이너를 구성하고 , 각 요소는 해당 범위의 해당 요소에서 동일한 순서로 구성됩니다.
// - first, last : 범위의 처음과 마지막 위치이다. first는 첫 요소를 가리키지만 last는 마지막 요소를 가리키지 않는다. 
// - exception : first의 메모리 주소가 last보다 뒤에 있다면 ft::length_error : vector
template<class T, class Alloc>
template <class InputIterator>
ft::vector<T, Alloc>::vector(InputIterator first,
							typename ft::enable_if<ft::is_iterator<InputIterator>::value, 
							InputIterator>::type last, 
							const allocator_type& alloc)
{
	difference_type	n = ft::distance(first, last);
	
	this->__alloc = alloc;
	this->__begin = this->__alloc.allocate(n);
	this->__end = this->__begin + n;
	this->__end_mem = this->__end;

	for (int i=0; i<n; i++)
		__alloc_traits::construct(this->__alloc, this->__begin + i, *(first + i));
}

// Constructs a container with a copy of each of the elements in x, in the same order.
// 동일한 순서로 x 의 각 요소 복사본을 사용하여 컨테이너를 생성합니다.
// 인자의 데이터 크기만큼의 메모리 크기를 가집니다.
template<class T, class Alloc>
ft::vector<T, Alloc>::vector (const vector& x)
{
	size_type	size = x.size();
	this->__alloc = x.__alloc;
	this->__begin = this->__alloc.allocate(size);
	this->__end = this->__begin + size;
	this->__end_mem = this->__end;

	for (int i=0; i<size; i++)
	{
		const_pointer __new_end = this->__begin + i;
		const_pointer __x_end = x.__begin + i;
		__alloc_traits::construct(this->__alloc, __new_end, *__x_end);
	}
}

// This destroys all container elements, and deallocates all the storage capacity allocated by the vector using its allocator.
// 이것은 모든 컨테이너 요소를 파괴하고 할당자를 사용하여 벡터에 의해 할당된 모든 저장 용량 을 할당 해제 합니다 .
template<class T, class Alloc>
ft::vector<T, Alloc>::~vector()
{
	difference_type	idx = 0;
	while (this->__begin + idx != this->__end)
	{
		__alloc_traits::destroy(this->__alloc, this->__begin + idx);
		idx += 1;
	}
	__alloc_traits::deallocate(this->__alloc, this->__begin, this->size());
}

// Copies all the elements from x into the container.
// The container preserves its current allocator, which is used to allocate storage in case of reallocation.
// x 의 모든 요소를 ​​컨테이너에 복사합니다. 컨테이너 는 재할당의 경우 스토리지를 할당하는 데 사용되는 현재 할당자를 유지합니다.
template<class T, class Alloc>
ft::vector<T, Alloc>& 
ft::vector<T, Alloc>::operator = (const vector& x)
{
}

// Returns an iterator pointing to the first element in the vector.
// 벡터의 첫 번째 요소를 가리키는 반복자를 반환합니다 . 
template<class T, class Alloc>
typename ft::vector<T, Alloc>::iterator 
ft::vector<T, Alloc>::begin()
{
	return (iterator(__begin));
}

// If the vector object is const-qualified, the function returns a const_iterator. Otherwise, it returns an iterator.
// 객체가 const로 한정된 경우 함수는 const_iterator 를 반환합니다 . 그렇지 않으면 iterator 를 반환합니다 . 멤버 유형 iterator 및 const_iterator 는 임의 액세스 반복기 유형입니다(각각 요소 및 const 요소를 가리킴).
// T가 const인지 확인하고, 반환한다.
template<class T, class Alloc>
typename ft::vector<T, Alloc>::const_iterator 
ft::vector<T, Alloc>::begin() const
{
}

// Returns an iterator referring to the past-the-end element in the vector container.
// 벡터 컨테이너 의 과거 끝 요소를 참조하는 반복자를 반환합니다 .

// past-the-end 요소는 벡터의 마지막 요소 뒤에 오는 이론적 요소이다. 어떤 요소도 가리키지 않으므로 역참조되지 않는다.
// 만약에 컨테이너가 비어있다면 함수는 vector::begin과 같은 값을 반환한다.
template<class T, class Alloc>
typename ft::vector<T, Alloc>::iterator 
ft::vector<T, Alloc>::end()
{

	return (iterator(__end));
}

// If the vector object is const-qualified, the function returns a const_iterator. Otherwise, it returns an iterator.
// 객체가 const로 한정된 경우 함수는 const_iterator 를 반환합니다 . 그렇지 않으면 iterator 를 반환합니다 . 멤버 유형 iterator 및 const_iterator 는 임의 액세스 반복기 유형입니다(각각 요소 및 const 요소를 가리킴).
template<class T, class Alloc>
typename ft::vector<T, Alloc>::const_iterator 
ft::vector<T, Alloc>::end() const
{
}

// template<class T, class Alloc>
// typename ft::vector<T, Alloc>::reverse_iterator 
// ft::vector<T, Alloc>::rbegin()
// {
// 	// Returns a reverse iterator pointing to the last element in the vector (i.e., its reverse beginning).

// 	// 벡터의 마지막을 가리키는 역방향 반복자를 반환한다. 역방향 반복자는 뒤로 반복한다. 
// 	// rbegin은 end가 가리키는 요소 바로 앞의 요소를 가리킨다. 
// }

// template<class T, class Alloc>
// typename ft::vector<T, Alloc>::const_reverse_iterator 
// ft::vector<T, Alloc>::rbegin() const
// {
// 	// If the vector object is const-qualified, the function returns a const_iterator. Otherwise, it returns an iterator.
// 	// 객체가 const로 한정된 경우 함수는 const_iterator 를 반환합니다 . 그렇지 않으면 iterator 를 반환합니다 . 멤버 유형 iterator 및 const_iterator 는 임의 액세스 반복기 유형입니다(각각 요소 및 const 요소를 가리킴).
// }

// template<class T, class Alloc>
// typename ft::vector<T, Alloc>::reverse_iterator 
// ft::vector<T, Alloc>::rend()
// {
// 	// Returns a reverse iterator pointing to the theoretical element preceding the first element in the vector (which is considered its reverse end).

// 	// 벡터의 첫번째 요소 앞에 있는 이론적인 요소를 가리키는 역방향 iterator를 반환한다.
// }

// template<class T, class Alloc>
// typename ft::vector<T, Alloc>::const_reverse_iterator 
// ft::vector<T, Alloc>::rend() const
// {
// 	// If the vector object is const-qualified, the function returns a const_iterator. Otherwise, it returns an iterator.
// 	// 객체가 const로 한정된 경우 함수는 const_iterator 를 반환합니다 . 그렇지 않으면 iterator 를 반환합니다 . 멤버 유형 iterator 및 const_iterator 는 임의 액세스 반복기 유형입니다(각각 요소 및 const 요소를 가리킴).
// }

// vector가 가지고 있는 실제 개체의 수를 반환한다. 저장공간의 크기과 같을 필요가 없다. 
template<class T, class Alloc>
typename ft::vector<T, Alloc>::size_type
ft::vector<T, Alloc>::size() const
{
	return (this->__end - this->__begin);
}

// vector가 가질 수 있는 최대 요소의 갯수을 반환한다.
// 시스템 또는 라이브러리 구현 제한으로 인해 컨테이너가 닿을 수 있는 최대 사이즈를 반환한다.
// 그러나 최대 사이즈에 닿을 수 있음을 보장하지 않는다. 
template<class T, class Alloc>
typename ft::vector<T, Alloc>::size_type
ft::vector<T, Alloc>::max_size() const
{
	size_type		max = __alloc_traits::max_size(this->__alloc);
	size_type	diff_max = std::numeric_limits<difference_type>::max();

	return (max < diff_max ? max : diff_max);
}

template<class T, class Alloc>
typename ft::vector<T, Alloc>::size_type
 ft::vector<T, Alloc>::__calc_new_size(size_type new_size) const
{
	size_type	max = max_size();
	if (new_size > max)
		throw ft::length_error("vector");
	size_type	cap = capacity();
	if (cap >= max / 2)
		return (max);
	return (cap * 2 > new_size ? cap * 2 : new_size);
}

// 컨테이너가 n개의 요소를 포함하도록 크기를 조정한다.
// n이 현재 컨테이너의 크기보다 작다면 초과되는 요소를 제거하고 파괴한다. 
// n이 현재 컨테이너의 크기보다 크다면 n 크기까지 필요한 요소를 채운다.
// val이 명시된다면, val의 복사본이 빈 공간을 채운다.
template<class T, class Alloc>
void
ft::vector<T, Alloc>::resize (size_type n, value_type val)
{
}

// vector에 할당된 저장공간을 반환한다. 
template<class T, class Alloc>
typename ft::vector<T, Alloc>::size_type
ft::vector<T, Alloc>::capacity() const
{
	return (this->__end_mem - this->__begin);
}

// vector가 비어있는지 반환한다.
template<class T, class Alloc>
bool
ft::vector<T, Alloc>::empty() const
{
}

template<class T, class Alloc>
void
ft::vector<T, Alloc>::reserve (size_type n)
{
	// vector 용량이 최소한 n개의 요소를 포함할 수 있도록 한다.
	// 만약에 n이 현재 vector 용량보다 크다면 저장공간을 재할당하여 용량을 n또는 그 이상으로 늘린다.
	// 아니라면 재할당을 하지 않으며 vector 용량에 영향을 주지 않는다. 
}

template<class T, class Alloc>
typename ft::vector<T, Alloc>::reference
ft::vector<T, Alloc>::operator [] (size_type n)
{
	// vector 컨테이너의 n위치에 있는 요소에 대한 참조를 반환한다.
	// vector::at과 다르게 범위를 벗어난 경우에 out_of_range를 throw하지 않는다.
}

template<class T, class Alloc>
typename ft::vector<T, Alloc>::const_reference 
ft::vector<T, Alloc>::operator [] (size_type n) const
{
	// 
}

template<class T, class Alloc>
typename ft::vector<T, Alloc>::reference 
ft::vector<T, Alloc>::at (size_type n)
{
	// vector의 n위치에 있는 요소에 대한 참조를 반환한다. 
	// n이 vector의 유효한 요소 범위 내에 있는지 여부를 확인하고 그렇지 않은 경우 out_of_range 예외를 throw한다.
}

template<class T, class Alloc>
typename ft::vector<T, Alloc>::const_reference 
ft::vector<T, Alloc>::at (size_type n) const
{
	// 객체가 const로 한정된 경우 함수는 const_reference를 반환한다.
}

template<class T, class Alloc>
typename ft::vector<T, Alloc>::reference 
ft::vector<T, Alloc>::front()
{
	// vector의 첫번째 요소에 대한 참조를 반환한다.
	// vector::begin과 달리 직접 참조를 반환한다. 
	// 빈 컨테이너에어 함수를 호출하면 정의되지 않은 동작이 발생한다.

}

template<class T, class Alloc>
typename ft::vector<T, Alloc>::const_reference 
ft::vector<T, Alloc>::front() const
{

}

template<class T, class Alloc>
typename ft::vector<T, Alloc>::reference 
ft::vector<T, Alloc>::back()
{
	// vector의 마지막 요소에 대한 참조를 반환한다. 
	// vector::end와 달리 직접 참조를 반환한다.
}

template<class T, class Alloc>
typename ft::vector<T, Alloc>::const_reference 
ft::vector<T, Alloc>::back() const
{

}

template<class T, class Alloc>
typename ft::vector<T, Alloc>::value_type* 
ft::vector<T, Alloc>::data()
{
	// vector가 소유한 요소를 저장하기 위해 내부적으로 사용하는 메모리 배열에 대한 직접 포인터를 반환한다.
	// 내부적으로 사용하는 배열의 첫 번째 요소에 대한 포인터를 반환한다.
}

template<class T, class Alloc>
const typename ft::vector<T, Alloc>::value_type*
ft::vector<T, Alloc>::data() const
{
	// 객체가 const로 한정된 경우 함수는 const value_type에 대한 포인터를 반환한다.
}

template<class T, class Alloc>
template <class InputIterator> 
void 
ft::vector<T, Alloc>::assign (InputIterator first, InputIterator last)
{
	// vector에 새 내용을 할당하고 현재 내용을 바꾸고 그에 따라 크기를 수정한다.
	// 재할당이 발생되면 내부 할당자를 사용하여 필요한 저장공간이 할당된다.
	// first와 last 사이의 범위에 있는 각 요소에서 동일한 순서로 구성된 요소이다.
}

template<class T, class Alloc>
void 
ft::vector<T, Alloc>::assign (size_type n, const value_type& val)
{
	// vector에 새 내용을 할당하고 현재 내용을 바꾸고 그에 따라 크기를 수정한다.
	// 재할당이 발생되면 내부 할당자를 사용하여 필요한 저장공간이 할당된다.
	// n개의 요소가 val의 복사본으로 초기화된다. 
}

// vector의 마지막 요소 다음에 요소를 추가한다.
// val의 내용이 새 요소로 복사 또는 이동된다.
// 현재 벡터 용량을 초과하는 경우에는 저장 공간이 자동으로 재할당된다.
template<class T, class Alloc>
void 
ft::vector<T, Alloc>::push_back (const value_type& val)
{	
	if (size() < capacity())
	{
		__alloc_traits::construct(this->__alloc, this->__end, val);
		this->__end += 1;
	}
	else
	{
		size_type	old_size = this->size();
		size_type	new_size = __calc_new_size(old_size + 1);
		pointer		new_begin = this->__alloc.allocate(new_size);
		pointer		new_end = new_begin + new_size;

		difference_type	idx = 0;
		while (this->__begin + idx != this->__end)
		{
			__alloc_traits::construct(this->__alloc, new_begin + idx, *(this->__begin + idx));
			__alloc_traits::destroy(this->__alloc, this->__begin + idx);
			idx += 1;
		}
		__alloc_traits::construct(this->__alloc, new_begin + idx, val);

		__alloc_traits::deallocate(this->__alloc, this->__begin, old_size);
		this->__begin = new_begin;
		this->__end = this->__begin + old_size + 1;
		this->__end_mem = this->__begin + new_size;
	}
}

template<class T, class Alloc>
void 
ft::vector<T, Alloc>::pop_back()
{
	// vector의 마지막 요소를 제거하고 컨테이너 크기 1을 효과적으로 줄인다. 제거된 요소는 파괴된다.
}

template<class T, class Alloc>
typename ft::vector<T, Alloc>::iterator 
ft::vector<T, Alloc>::insert (iterator position, const value_type& val)
{
	// 지정된 위치의 요소 앞에 새 요소를 삽입하여 확장한다.
	// 새 vector의 크기가 현재 vector의 용량을 초과하는 경우에는 저장 공간이 자동으로 재할당된다.
	// val은 복사 또는 이동되어 삽입될 요소이다. 
}

template<class T, class Alloc>
void 
ft::vector<T, Alloc>::insert (iterator position, size_type n, const value_type& val)
{
	// n은 삽입할 요소의 수이다.
	// 각각의 요소는 val의 복사본이다. 
}

template<class T, class Alloc>
template <class InputIterator> 
void 
ft::vector<T, Alloc>::insert (iterator position, InputIterator first, InputIterator last)
{
	// first와 last 범위에 있는 요소의 복사본이 동일한 순서로 position에 삽입된다. 
	// 
}

template<class T, class Alloc>
typename ft::vector<T, Alloc>::iterator 
ft::vector<T, Alloc>::erase (iterator position)
{
	// vector에서 position에 있는 요소를 제거한다.
	// 제거된 요소의 수만큼 컨테이너 크기를 효과적으로 줄여 파괴한다.
	// vector 끝이 아닌 위치에서 요소를 지우면 컨테이너가 세그먼트가 지워진 후 새 위치로 모든 요소를 재배치하게 된다.
}

template<class T, class Alloc>
typename ft::vector<T, Alloc>::iterator 
ft::vector<T, Alloc>::erase (iterator first, iterator last)
{
	// vector에서 first와 last 범위에 있는 요소를 제거한다.
	// 제거된 요소의 수만큼 컨테이너 크기를 효과적으로 줄여 파괴한다.
	// vector 끝이 아닌 위치에서 요소를 지우면 컨테이너가 세그먼트가 지워진 후 새 위치로 모든 요소를 재배치하게 된다.
}

template<class T, class Alloc>
void 
ft::vector<T, Alloc>::swap (vector& x)
{
	// 동일한 유형의 다른 vector 객체인 x의 내용으로 컨테이너 내용을 교환한다.
	// 크기가 다를 수 있다.
	// 모든 반복자, 참조 및 포인터는 교환된 개체에 대해 유효한 상태로 유지된다.
}

template<class T, class Alloc>
void
ft::vector<T, Alloc>::clear()
{
	// vector의 모든 요소를 제거하고 컨테이너의 크기를 0으로 유지한다.
	// 재할당이 보장되지 않으며 vector 용량이 변경된다는 보장이 없다. 
	// 

}

template<class T, class Alloc>
typename ft::vector<T, Alloc>::allocator_type
ft::vector<T, Alloc>::get_allocator() const
{
	// vector와 관련된 allocator의 복사본을 반환한다.

}

// 관계 연산자
// vector 컨테이너 lhs 및 rhs 간에 적절한 비교 작업을 수행한다.
// 순차적으로 요소를 비교하고, 첫 번째 불일치에서 중지한다.

template <class T, class Alloc>  
bool 
ft::vector<T, Alloc>::operator == (ft::vector<T, Alloc>& rhs) const
{
	// 
}


template <class T, class Alloc>  
bool 
ft::vector<T, Alloc>::operator != (ft::vector<T, Alloc>& rhs) const
{
	// 
}


template <class T, class Alloc>  
bool 
ft::vector<T, Alloc>::operator <  (ft::vector<T, Alloc>& rhs) const
{
	// 
}


template <class T, class Alloc>  
bool 
ft::vector<T, Alloc>::operator <= (ft::vector<T, Alloc>& rhs) const
{
	// 
}


template <class T, class Alloc>  
bool 
ft::vector<T, Alloc>::operator >  (ft::vector<T, Alloc>& rhs) const
{
	// 
}


template <class T, class Alloc>  
bool 
ft::vector<T, Alloc>::operator >= (ft::vector<T, Alloc>& rhs) const
{
	// 
}





} // namespace ft

#endif // __VECTOR_HPP__

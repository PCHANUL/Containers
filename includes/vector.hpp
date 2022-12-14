/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:31:14 by cpak              #+#    #+#             */
/*   Updated: 2022/11/23 14:16:915:54 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__
#include <memory>
#include <limits>
#include "type_traits.hpp"
#include "iterator.hpp"
#include "iterator_traits.hpp"
#include "utility.hpp"

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
	typedef ft::v_iter<T, false>							iterator;
	typedef ft::v_iter<T, true>								const_iterator;
	typedef ft::reverse_iterator<iterator>					reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
	typedef typename __alloc_traits::difference_type		difference_type;
	typedef typename __alloc_traits::size_type				size_type;

protected:
	pointer													__begin;
	pointer													__end;
	pointer													__end_mem;
	allocator_type											__alloc;

public:
	vector(const allocator_type& alloc = allocator_type());
	vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());

	template <class InputIterator>
	vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<ft::is_iterator<InputIterator>::value, InputIterator>::type* = 0);
	vector(const vector& x);
	~vector();
	vector&					operator = (const vector& x);

	iterator 				begin();
	const_iterator 			begin() const;
	iterator 				end();
	const_iterator 			end() const;
	reverse_iterator 		rbegin();
	const_reverse_iterator 	rbegin() const;
	reverse_iterator 		rend();
	const_reverse_iterator 	rend() const;

	size_type				size() const;
	size_type				max_size() const;
	void					resize(size_type n, value_type val = value_type());
	size_type				capacity() const;
	bool					empty() const;
	void					reserve(size_type n);

	reference 				operator[](size_type n);
	const_reference 		operator[](size_type n) const;
	reference 				at(size_type n);
	const_reference 		at(size_type n) const;
	reference 				front();
	const_reference 		front() const;
	reference 				back();
	const_reference 		back() const;
	value_type* 			data();
	const value_type* 		data() const;

	template <class InputIterator> 
	void					assign(InputIterator first, InputIterator last,
								typename ft::enable_if<ft::is_iterator<InputIterator>::value, InputIterator>::type* = 0);
	void					assign(size_type n, const value_type& val);
	void					push_back(const value_type& val);
	void					pop_back();
	iterator				insert(iterator position, const value_type& val);
    void					insert(iterator position, size_type n, const value_type& val);
	template <class InputIterator> 
	void					insert(iterator position, InputIterator first, InputIterator last,
								typename ft::enable_if<ft::is_iterator<InputIterator>::value, InputIterator>::type* = 0);
	iterator				erase(iterator position);
	iterator				erase(iterator first, iterator last);
	void					swap(vector& x);
	void					clear();

	allocator_type			get_allocator() const;


private:
	template <class _P>
	void					__ftmemcpy(_P* __src, size_t __n);
	size_type				__calc_new_size(size_type new_size) const;
	void					__allocate(size_type n, const allocator_type& alloc);
	void					__destroy_end(pointer new_end);
	template <class InputIterator>
	void					__destroy_mid(InputIterator first, InputIterator last,
								typename ft::enable_if<ft::is_iterator<InputIterator>::value, InputIterator>::type* = 0);
	void					__construct_end(size_type n, const_reference val);
	template <class InputIterator>
	void					__construct_end(InputIterator first, InputIterator last,
								typename ft::enable_if<ft::is_iterator<InputIterator>::value, InputIterator>::type* = 0);
	template <class InputIterator>
	void					__construct_end(InputIterator first, InputIterator last, size_type n,
								typename ft::enable_if<ft::is_iterator<InputIterator>::value, InputIterator>::type* = 0);
	void					__construct_mid(iterator position, size_type n, const_reference val);
	template <class InputIterator>
	void					__construct_mid(iterator position, InputIterator first, InputIterator last,
								typename ft::enable_if<ft::is_iterator<InputIterator>::value, InputIterator>::type* = 0);
	template <class _P>
	void					__construct_range(_P __begin_s, _P __end_s, std::random_access_iterator_tag);
	template <class _P>
	void					__construct_range(_P __begin_s, _P __end_s, std::input_iterator_tag);
	void					__move_end_forward(iterator start, size_type n);
	void					__move_end_backward(iterator start, size_type n);
	void					__swap_ptr(pointer& p1, pointer& p2);
	template<class Iter1, class Iter2>
	bool 					__compare_vector(Iter1 a_begin, Iter1 a_end, Iter2 b_begin, Iter2 b_end,
								typename ft::enable_if<ft::is_iterator<Iter1>::value, Iter1>::type* = 0,
								typename ft::enable_if<ft::is_iterator<Iter2>::value, Iter2>::type* = 0) const;
	class _TmpVector
	{

	private:
		pointer			__begin;
		pointer			__end;
		pointer 		__end_mem;
		allocator_type	__alloc;

		_TmpVector() : __begin(nullptr), __end(nullptr), __end_mem(nullptr), __alloc(allocator_type())
		{
		}

		_TmpVector(const _TmpVector& __x) 
		{
			*this = __x;
		}
		
		_TmpVector& operator = (const _TmpVector& __x) 
		{
			this->__alloc = __x.alloc;
			this->__begin = __alloc_traits::allocate(this->__alloc, __x.size());
			this->__end_mem = this->__begin + __x.size();
			this->__end = this->__begin;
			return (*this);
		}

	public:
		_TmpVector(allocator_type& alloc, size_type n)
		{
			this->__alloc = alloc;
			this->__begin = __alloc_traits::allocate(this->__alloc, n);
			this->__end_mem = this->__begin + n;
			this->__end = this->__begin;
		}

		~_TmpVector()
		{
			pointer	__p = this->__end;
			
			while (__p-- != this->__begin)
				__alloc_traits::destroy(this->__alloc, __p);
			if (size() != 0)
				__alloc_traits::deallocate(this->__alloc, this->__begin, this->__end - this->__begin);
		}

		size_type	size() 
		{ 
			return (this->__end - this->__begin); 
		}

		size_type	capacity() 
		{ 
			return (this->__end_mem - this->__begin); 
		}

		void	insert_end(value_type val)
		{
			if (size() + 1 > capacity())
				return ;
			*(this->__end) = val;
			this->__end += 1;
		}

		void	insert_end(size_type n, value_type val)
		{
			if (size() + n > capacity())
				return ;
			for (size_type i=0; i<n; i++, this->__end++)
				__alloc_traits::construct(this->__alloc, this->__end, val);
		}

		template <class InputIterator>
		void	insert_end(InputIterator first, InputIterator last,
							typename ft::enable_if<ft::is_iterator<InputIterator>::value, InputIterator>::type* = 0)
		{
			size_type	n = ft::distance(first, last);

			if (size() + n > capacity())
				return ;
			for (InputIterator iter=first; iter!=last; iter++, this->__end++)
				__alloc_traits::construct(this->__alloc, this->__end, *iter);
		}

		void	insert_end(iterator first, iterator last)
		{
			size_type	n = ft::distance(first, last);

			if (size() + n > capacity())
				return ;
			for (iterator iter=first; iter!=last; iter++, this->__end++)
				__alloc_traits::construct(this->__alloc, this->__end, *iter);
		}

		void	swap(pointer& p1, pointer& p2)
		{
			pointer	tmp = p1;
			p1 = p2;
			p2 = tmp;
		}

		void	move(vector& __v)
		{
			swap(this->__begin, __v.__begin);
			swap(this->__end, __v.__end);
			swap(this->__end_mem, __v.__end_mem);
		}
	};
	
};

// Constructs an empty container, with no elements.
// ????????? ?????? ??? ??????????????? ???????????????.
template<class T, class Alloc>
ft::vector<T, Alloc>::vector(const allocator_type& alloc)
{
	__begin = nullptr;
	__end = nullptr;
	__end_mem = nullptr;
	__alloc = alloc;
}

// Constructs a container with n elements. Each element is a copy of val.
// n?????? ?????? ??? ?????? ??????????????? ???????????????. ??? ????????? val ??? ??????????????????.
template<class T, class Alloc>
ft::vector<T, Alloc>::vector(size_type n, const_reference val, const allocator_type& alloc)
{
	__allocate(n, alloc);
	__construct_end(n, val);
}

// Constructs a container with as many elements as the range [first,last), 
// with each element constructed from its corresponding element in that range, in the same order.
// [first,last) ???????????? ?????? ????????? ?????? ??????????????? ???????????? , ??? ????????? ?????? ????????? ?????? ???????????? ????????? ????????? ???????????????.
// - first, last : ????????? ????????? ????????? ????????????. first??? ??? ????????? ??????????????? last??? ????????? ????????? ???????????? ?????????. 
// - exception : first??? ????????? ????????? last?????? ?????? ????????? ft::length_error : vector
template<class T, class Alloc>
template <class InputIterator>
ft::vector<T, Alloc>::vector(InputIterator first, InputIterator last, const allocator_type& alloc,
								typename ft::enable_if<ft::is_iterator<InputIterator>::value, InputIterator>::type*)
{
	__allocate(ft::distance(first, last), alloc);
	__construct_end(first, last);
}

// Constructs a container with a copy of each of the elements in x, in the same order.
// ????????? ????????? x ??? ??? ?????? ???????????? ???????????? ??????????????? ???????????????.
// ????????? ????????? ??????????????? ????????? ????????? ????????????.
template<class T, class Alloc>
ft::vector<T, Alloc>::vector(const vector& x)
{
	__allocate(x.size(), x.__alloc);
	__construct_end(x.begin(), x.end(), x.size());
}

// Copies all the elements from x into the container.
// The container preserves its current allocator, which is used to allocate storage in case of reallocation.
// x ??? ?????? ????????? ????????????????????? ???????????????. ???????????? ??? ???????????? ?????? ??????????????? ???????????? ??? ???????????? ?????? ???????????? ???????????????.
// ?????? ???????????? size??? ??? ??? ????????? size?????? ??????????????????.
template<class T, class Alloc>
ft::vector<T, Alloc>& 
ft::vector<T, Alloc>::operator = (const vector& x)
{
	if (this->__alloc != x.__alloc)
	{
		__destroy_end(this->__begin);
		this->__alloc = x.__alloc;
	}
	assign(x.begin(), x.end());
	return (*this);
}

template<class T, class Alloc>
void
ft::vector<T, Alloc>::__allocate(size_type n, const allocator_type& alloc)
{
	if (n > max_size() || n < 0)
		throw std::length_error("vector");
	this->__alloc = alloc;
	this->__begin = __alloc_traits::allocate(this->__alloc, n);
	this->__end = this->__begin;
	this->__end_mem = this->__end + n;
}

// new_end????????? ????????? ????????????.
template<class T, class Alloc>
void
ft::vector<T, Alloc>::__destroy_end(pointer new_end)
{	
	while (this->__end != new_end && this->__end != this->__begin && this->__end--)
		__alloc_traits::destroy(this->__alloc, this->__end);
	this->__end = new_end;
}

// first?????? last????????? ????????? ????????????.
template<class T, class Alloc>
template <class InputIterator>
void
ft::vector<T, Alloc>::__destroy_mid(InputIterator first, InputIterator last,
									typename ft::enable_if<ft::is_iterator<InputIterator>::value, InputIterator>::type*)
{	
	for (; first!=last; first++)
		__alloc_traits::destroy(this->__alloc, &(*first));
}

// ????????? ????????? first?????? last?????? ????????? ??????
template<class T, class Alloc>
template<class InputIterator>
void
ft::vector<T, Alloc>::__construct_end(InputIterator first, InputIterator last,
										typename ft::enable_if<ft::is_iterator<InputIterator>::value, InputIterator>::type*)
{
	for (; first!=last; first++, this->__end++)
		__alloc_traits::construct(this->__alloc, this->__end, *first);
}

// ????????? ????????? n?????? val??? ??????
template<class T, class Alloc>
void
ft::vector<T, Alloc>::__construct_end(size_type n, const_reference val)
{
	for (size_type i=0; i<n; i++, this->__end++)
		__alloc_traits::construct(this->__alloc, this->__end, val);
}

template <class T, class Alloc>
template <class _P>
void
ft::vector<T, Alloc>::__ftmemcpy(_P* __src, size_t __n)
{
	std::memcpy(this->__begin, __src, __n);
}

template <class T, class Alloc>
template <class _P>
void
ft::vector<T, Alloc>::__construct_range(_P __begin_s, _P __end_s, std::random_access_iterator_tag)
{
	ptrdiff_t n = &(*__end_s) - &(*__begin_s);
	if (n > 0)
		__ftmemcpy(&(*__begin_s), n * sizeof(T));
	this->__end = this->__begin + n;
}

template <class T, class Alloc>
template <class _P>
void
ft::vector<T, Alloc>::__construct_range(_P __begin_s, _P __end_s, std::input_iterator_tag)
{
	iterator	__p = this->begin();
	for (; __begin_s!=__end_s; __begin_s++, __p++)
		*__p = *__begin_s;
}

// ????????? ????????? n?????? pointer??? ??????
template <class T, class Alloc>
template <class InputIterator>
void
ft::vector<T, Alloc>::__construct_end(InputIterator first, InputIterator last, size_type n,
										typename ft::enable_if<ft::is_iterator<InputIterator>::value, InputIterator>::type*)
{
	(void)n;
	__construct_range(first, last, typename ft::iterator_traits<InputIterator>::iterator_category());
}

template<class T, class Alloc>
template<class InputIterator>
void
ft::vector<T, Alloc>::__construct_mid(iterator position, InputIterator first, InputIterator last,
										typename ft::enable_if<ft::is_iterator<InputIterator>::value, InputIterator>::type*)
{
	for (InputIterator	iter=first; iter!=last; iter++, position++)
		__alloc_traits::construct(this->__alloc, &(*position), *iter);
}

template<class T, class Alloc>
void					
ft::vector<T, Alloc>::__construct_mid(iterator position, size_type n, const_reference val)
{
	for (size_type i=0; i<n; i++, position++)
		__alloc_traits::construct(this->__alloc, &(*position), val);
}

// ????????? ???????????? position????????? ????????? ?????? ????????????.
template<class T, class Alloc>
void
ft::vector<T, Alloc>::__move_end_backward(iterator start, size_type n)
{
	size_type	len = iterator(__end) - start;

	for (size_type i=0; i<=len; i++)
		*(start + len - i + n) = *(start + len - i);
	this->__end += n;
}

// ????????? ???????????? position????????? ????????? ????????? ????????????.
template<class T, class Alloc>
void
ft::vector<T, Alloc>::__move_end_forward(iterator start, size_type n)
{
	iterator	last = iterator(__end) - n;

	for (; start != last; start++)
		*(start) = *(start + n);
	this->__end -= n;
}

// This destroys all container elements, and deallocates all the storage capacity allocated by the vector using its allocator.
// ????????? ?????? ???????????? ????????? ???????????? ???????????? ???????????? ????????? ?????? ????????? ?????? ?????? ?????? ??? ?????? ?????? ????????? .
template<class T, class Alloc>
ft::vector<T, Alloc>::~vector()
{
	__destroy_end(this->__begin);
	__alloc_traits::deallocate(this->__alloc, this->__begin, this->capacity());
}

// Returns an iterator pointing to the first element in the vector.
// ????????? ??? ?????? ????????? ???????????? ???????????? ??????????????? . 
template<class T, class Alloc>
typename ft::vector<T, Alloc>::iterator 
ft::vector<T, Alloc>::begin()
{
	return (iterator(__begin));
}

// If the vector object is const-qualified, the function returns a const_iterator. Otherwise, it returns an iterator.
// ????????? const??? ????????? ?????? ????????? const_iterator ??? ??????????????? . ????????? ????????? iterator ??? ??????????????? . ?????? ?????? iterator ??? const_iterator ??? ?????? ????????? ????????? ???????????????(?????? ?????? ??? const ????????? ?????????).
// T??? const?????? ????????????, ????????????.
template<class T, class Alloc>
typename ft::vector<T, Alloc>::const_iterator 
ft::vector<T, Alloc>::begin() const
{
	return (const_iterator(__begin));
}

// Returns an iterator referring to the past-the-end element in the vector container.
// ?????? ???????????? ??? ?????? ??? ????????? ???????????? ???????????? ??????????????? .

// past-the-end ????????? ????????? ????????? ?????? ?????? ?????? ????????? ????????????. ?????? ????????? ???????????? ???????????? ??????????????? ?????????.
// ????????? ??????????????? ??????????????? ????????? vector::begin??? ?????? ?????? ????????????.
template<class T, class Alloc>
typename ft::vector<T, Alloc>::iterator 
ft::vector<T, Alloc>::end()
{
	return (iterator(__end));
}

// If the vector object is const-qualified, the function returns a const_iterator. Otherwise, it returns an iterator.
// ????????? const??? ????????? ?????? ????????? const_iterator ??? ??????????????? . ????????? ????????? iterator ??? ??????????????? . ?????? ?????? iterator ??? const_iterator ??? ?????? ????????? ????????? ???????????????(?????? ?????? ??? const ????????? ?????????).
template<class T, class Alloc>
typename ft::vector<T, Alloc>::const_iterator 
ft::vector<T, Alloc>::end() const
{
	return (const_iterator(__end));
}

// ????????? ???????????? ???????????? ????????? ???????????? ????????????. ????????? ???????????? ?????? ????????????. 
// rbegin??? end??? ???????????? ?????? ?????? ?????? ????????? ????????????. 
template<class T, class Alloc>
typename ft::vector<T, Alloc>::reverse_iterator 
ft::vector<T, Alloc>::rbegin()
{
	return (reverse_iterator(end()));
}

// ????????? const??? ????????? ?????? ????????? const_iterator ??? ??????????????? . ????????? ????????? iterator ??? ??????????????? . 
// ?????? ?????? iterator ??? const_iterator ??? ?????? ????????? ????????? ???????????????(?????? ?????? ??? const ????????? ?????????).
template<class T, class Alloc>
typename ft::vector<T, Alloc>::const_reverse_iterator 
ft::vector<T, Alloc>::rbegin() const
{
	return (const_reverse_iterator(end()));
}

// ????????? ????????? ?????? ?????? ?????? ???????????? ????????? ???????????? ????????? iterator??? ????????????.
template<class T, class Alloc>
typename ft::vector<T, Alloc>::reverse_iterator 
ft::vector<T, Alloc>::rend()
{
	return (reverse_iterator(begin()));
}

// ????????? const??? ????????? ?????? ????????? const_iterator ??? ??????????????? . ????????? ????????? iterator ??? ??????????????? . 
// ?????? ?????? iterator ??? const_iterator ??? ?????? ????????? ????????? ???????????????(?????? ?????? ??? const ????????? ?????????).
template<class T, class Alloc>
typename ft::vector<T, Alloc>::const_reverse_iterator 
ft::vector<T, Alloc>::rend() const
{
	return (const_reverse_iterator(begin()));
}

// vector??? ????????? ?????? ?????? ????????? ?????? ????????????. ??????????????? ????????? ?????? ????????? ??????. 
template<class T, class Alloc>
typename ft::vector<T, Alloc>::size_type
ft::vector<T, Alloc>::size() const
{
	return (this->__end - this->__begin);
}

// vector??? ?????? ??? ?????? ?????? ????????? ????????? ????????????.
// ????????? ?????? ??????????????? ?????? ???????????? ?????? ??????????????? ?????? ??? ?????? ?????? ???????????? ????????????.
// ????????? ?????? ???????????? ?????? ??? ????????? ???????????? ?????????. 
template<class T, class Alloc>
typename ft::vector<T, Alloc>::size_type
ft::vector<T, Alloc>::max_size() const
{
	size_type	max = __alloc_traits::max_size(this->__alloc);
	size_type	diff_max = std::numeric_limits<difference_type>::max();

	return (max < diff_max ? max : diff_max);
}

template<class T, class Alloc>
typename ft::vector<T, Alloc>::size_type
 ft::vector<T, Alloc>::__calc_new_size(size_type new_size) const
{
	size_type	max = max_size();
	if (new_size > max)
		throw std::length_error("vector");
	size_type	cap = capacity();
	if (cap >= max / 2)
		return (max);
	return (cap * 2 > new_size ? cap * 2 : new_size);
}

// ??????????????? n?????? ????????? ??????????????? ????????? ????????????.
// n??? ?????? ??????????????? ???????????? ????????? ???????????? ????????? ???????????? ????????????. 
// n??? ?????? ??????????????? ???????????? ????????? n ???????????? ????????? ????????? ?????????.
// val??? ???????????????, val??? ???????????? ??? ????????? ?????????.
// ?????? : n??? max_size?????? ????????? length_error (strong guarantee)
template<class T, class Alloc>
void
ft::vector<T, Alloc>::resize (size_type n, value_type val)
{
	if (n > capacity())
	{
		_TmpVector	tmp(this->__alloc, __calc_new_size(n));

		tmp.insert_end(begin(), end());
		tmp.move(*this);
	}
	if (n > size())
		__construct_end(n - size(), val);
	else
		__destroy_end(__begin + n);
}

// vector??? ????????? ??????????????? ????????????. 
template<class T, class Alloc>
typename ft::vector<T, Alloc>::size_type
ft::vector<T, Alloc>::capacity() const
{
	return (this->__end_mem - this->__begin);
}

// vector??? ??????????????? ????????????.
template<class T, class Alloc>
bool
ft::vector<T, Alloc>::empty() const
{
	return (size() == 0);
}

// vector ????????? ????????? n?????? ????????? ????????? ??? ????????? ??????.
// ????????? n??? ?????? vector ???????????? ????????? ??????????????? ??????????????? ????????? n?????? ??? ???????????? ?????????.
// ???????????? ???????????? ?????? ????????? vector ????????? ????????? ?????? ?????????. 
// ?????? : n??? max_size?????? ????????? length_error??? ???????????????. (strong guarantee)
template<class T, class Alloc>
void
ft::vector<T, Alloc>::reserve (size_type n)
{
	if (n > capacity())
	{
		if (n > max_size())
			throw length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
		_TmpVector	tmp(this->__alloc, n);

		tmp.insert_end(begin(), end());
		tmp.move(*this);
	}
}

// vector ??????????????? n????????? ?????? ????????? ?????? ????????? ????????????.
// vector::at??? ????????? ????????? ????????? ????????? out_of_range??? throw?????? ?????????.
template<class T, class Alloc>
typename ft::vector<T, Alloc>::reference
ft::vector<T, Alloc>::operator [] (size_type n)
{
	return (*(this->__begin + n));
}

template<class T, class Alloc>
typename ft::vector<T, Alloc>::const_reference 
ft::vector<T, Alloc>::operator [] (size_type n) const
{
	return (*(this->__begin + n));
}

// vector??? n????????? ?????? ????????? ?????? ????????? ????????????. 
// n??? vector??? ????????? ?????? ?????? ?????? ????????? ????????? ???????????? ????????? ?????? ?????? out_of_range ????????? throw??????.
template<class T, class Alloc>
typename ft::vector<T, Alloc>::reference 
ft::vector<T, Alloc>::at (size_type n)
{
	if (n >= size())
		throw std::out_of_range("vector");
	return (*(this->__begin + n));
}

// ????????? const??? ????????? ?????? ????????? const_reference??? ????????????.
template<class T, class Alloc>
typename ft::vector<T, Alloc>::const_reference 
ft::vector<T, Alloc>::at (size_type n) const
{
	if (n >= size())
		throw std::out_of_range("vector");
	return (*(this->__begin + n));
}

// vector??? ????????? ????????? ?????? ????????? ????????????.
// vector::begin??? ?????? ?????? ????????? ????????????. 
// ??? ?????????????????? ????????? ???????????? ???????????? ?????? ????????? ????????????.
template<class T, class Alloc>
typename ft::vector<T, Alloc>::reference 
ft::vector<T, Alloc>::front()
{
	return (*(this->__begin));
}

template<class T, class Alloc>
typename ft::vector<T, Alloc>::const_reference 
ft::vector<T, Alloc>::front() const
{
	return (*(this->__begin));
}

// vector??? ????????? ????????? ?????? ????????? ????????????. 
// vector::end??? ?????? ?????? ????????? ????????????.
template<class T, class Alloc>
typename ft::vector<T, Alloc>::reference 
ft::vector<T, Alloc>::back()
{
	return (*(this->__end - 1));
}

template<class T, class Alloc>
typename ft::vector<T, Alloc>::const_reference 
ft::vector<T, Alloc>::back() const
{
	return (*(this->__end - 1));
}

// vector??? ????????? ????????? ???????????? ?????? ??????????????? ???????????? ????????? ????????? ?????? ?????? ???????????? ????????????.
// ??????????????? ???????????? ????????? ??? ?????? ????????? ?????? ???????????? ????????????.
template<class T, class Alloc>
typename ft::vector<T, Alloc>::value_type* 
ft::vector<T, Alloc>::data()
{
	return (this->__begin);
}

// ????????? const??? ????????? ?????? ????????? const value_type??? ?????? ???????????? ????????????.
template<class T, class Alloc>
const typename ft::vector<T, Alloc>::value_type*
ft::vector<T, Alloc>::data() const
{
	return (this->__begin);
}

// vector??? ??? ????????? ???????????? ?????? ????????? ????????? ?????? ?????? ????????? ????????????.
// ???????????? ???????????? ?????? ???????????? ???????????? ????????? ??????????????? ????????????.
// first??? last ????????? ????????? ?????? ??? ???????????? ????????? ????????? ????????? ????????????.
template<class T, class Alloc>
template <class InputIterator> 
void 
ft::vector<T, Alloc>::assign (InputIterator first, InputIterator last,
								typename ft::enable_if<ft::is_iterator<InputIterator>::value, InputIterator>::type*)
{
	size_type	n = ft::distance(first, last);

	if (n <= capacity())
	{
		InputIterator	iter = last;
		bool			is_growing = false;

		if (n > size())
		{
			is_growing = true;
			iter = first;
			ft::advance(iter, size() + 1);
		}
		
		__construct_range(
			first, iter, 
			typename ft::iterator_traits<InputIterator>::iterator_category());

		if (is_growing)
			__construct_end(iter, last);
		else
			__destroy_end(this->__end);
	}
	else 
	{
		_TmpVector	tmp(this->__alloc, n);
		tmp.move(*this);
		__construct_end(first, last);
	}
}

// vector??? ??? ????????? ???????????? ?????? ????????? ????????? ?????? ?????? ????????? ????????????.
// ???????????? ???????????? ?????? ???????????? ???????????? ????????? ??????????????? ????????????.
// n?????? ????????? val??? ??????????????? ???????????????. 
template<class T, class Alloc>
void
ft::vector<T, Alloc>::assign (size_type n, const value_type& val)
{
	if (capacity() < n)
	{
		_TmpVector	tmp(this->__alloc, __calc_new_size(n));
		tmp.move(*this);
	}
	else 
		__destroy_end(__begin);
	__construct_end(n, val);
}

// vector??? ????????? ?????? ????????? ????????? ????????????.
// val??? ????????? ??? ????????? ?????? ?????? ????????????.
// ?????? ?????? ????????? ???????????? ???????????? ?????? ????????? ???????????? ???????????????.
// ?????? : ?????? ??????/??????, ?????????/???????????? ?????? ????????? ??? ??????. (strong guarantee)
// push_back?????? ??????????????? ????????? max_size??? ???????????? ?????? length_error??? ???????????????.
template<class T, class Alloc>
void 
ft::vector<T, Alloc>::push_back (const value_type& val)
{	
	if (size() == capacity())
	{
		_TmpVector	tmp(this->__alloc, __calc_new_size(size() + 1));

		tmp.insert_end(begin(), end());
		tmp.move(*this);
	}
	__alloc_traits::construct(this->__alloc, this->__end++, val);
}

// vector??? ????????? ????????? ???????????? ???????????? ?????? 1??? ??????????????? ?????????. ????????? ????????? ????????????.
template<class T, class Alloc>
void 
ft::vector<T, Alloc>::pop_back()
{
	this->__destroy_end(this->__end - 1);
}

// ????????? ????????? ?????? ?????? ??? ????????? ???????????? ????????????.
// ??? vector??? ????????? ?????? vector??? ????????? ???????????? ???????????? ?????? ????????? ???????????? ???????????????.
// val??? ?????? ?????? ???????????? ????????? ????????????. 
// ?????? : end??? ????????? ????????? ????????? ????????????, 
template<class T, class Alloc>
typename ft::vector<T, Alloc>::iterator 
ft::vector<T, Alloc>::insert (iterator position, const value_type& val)
{
	size_type n = position - iterator(__begin);
	if (size() + 1 > capacity())
	{
		_TmpVector	tmp(this->__alloc, __calc_new_size(size() + 1));
		tmp.insert_end(begin(), position);
		tmp.insert_end(1, val);
		tmp.insert_end(position, end());
		tmp.move(*this);
		return (__begin + n);
	}
	__move_end_backward(position, 1);
	*position = val;
	return (position);
}

// n??? ????????? ????????? ?????????.
// ????????? ????????? val??? ???????????????. 
template<class T, class Alloc>
void 
ft::vector<T, Alloc>::insert (iterator position, size_type n, const value_type& val)
{
	if (size() + n > capacity())
	{
		_TmpVector	tmp(this->__alloc, __calc_new_size(size() + n));

		tmp.insert_end(begin(), position);
		tmp.insert_end(n, val);
		tmp.insert_end(position, end());
		tmp.move(*this);
		return ;
	}
	__move_end_backward(position, n);
	__construct_mid(position, n, val);
}

// first??? last ????????? ?????? ????????? ???????????? ????????? ????????? position??? ????????????. 
template<class T, class Alloc>
template <class InputIterator> 
void 
ft::vector<T, Alloc>::insert (iterator position, InputIterator first, InputIterator last,
								typename ft::enable_if<ft::is_iterator<InputIterator>::value, InputIterator>::type*)
{
	size_type	n = ft::distance(first, last);
	
	if (size() + n > capacity())
	{
		_TmpVector	tmp(this->__alloc, __calc_new_size(size() + n));

		tmp.insert_end(begin(), position);
		tmp.insert_end(first, last);
		tmp.insert_end(position, end());
		tmp.move(*this);
		return ;
	}
	__move_end_backward(position, n);
	__construct_mid(position, first, last);
}

// vector?????? position??? ?????? ????????? ????????????.
// ????????? ????????? ????????? ???????????? ????????? ??????????????? ?????? ????????????.
// vector ?????? ?????? ???????????? ????????? ????????? ??????????????? ??????????????? ????????? ??? ??? ????????? ?????? ????????? ??????????????? ??????.
template<class T, class Alloc>
typename ft::vector<T, Alloc>::iterator 
ft::vector<T, Alloc>::erase (iterator position)
{
	__alloc_traits::destroy(this->__alloc, &(*position));
	__move_end_forward(position, 1);
	return (position);
}

// vector?????? first??? last ????????? ?????? ????????? ????????????.
// ????????? ????????? ????????? ???????????? ????????? ??????????????? ?????? ????????????.
// vector ?????? ?????? ???????????? ????????? ????????? ??????????????? ??????????????? ????????? ??? ??? ????????? ?????? ????????? ??????????????? ??????.
template<class T, class Alloc>
typename ft::vector<T, Alloc>::iterator 
ft::vector<T, Alloc>::erase (iterator first, iterator last)
{
	size_type	n = ft::distance(first, last);

	__destroy_mid(first, last);
	__move_end_forward(first, n);
	return (first);
}

template<class T, class Alloc>
void 
ft::vector<T, Alloc>::__swap_ptr(pointer& p1, pointer& p2)
{
	pointer	tmp = p1;
	p1 = p2;
	p2 = tmp;
}

// ????????? ????????? ?????? vector ????????? x??? ???????????? ???????????? ????????? ????????????.
// ????????? ?????? ??? ??????.
// ?????? ?????????, ?????? ??? ???????????? ????????? ????????? ?????? ????????? ????????? ????????????.
template<class T, class Alloc>
void 
ft::vector<T, Alloc>::swap (vector& x)
{
	allocator_type	alloc = x.__alloc;

	x.__alloc = this->__alloc;
	this->__alloc = alloc;
	__swap_ptr(this->__begin, x.__begin);
	__swap_ptr(this->__end, x.__end);
	__swap_ptr(this->__end_mem, x.__end_mem);
}

// vector??? ?????? ????????? ???????????? ??????????????? ????????? 0?????? ????????????.
// ???????????? ???????????? ????????? vector ????????? ??????????????? ????????? ??????. 
// 
template<class T, class Alloc>
void
ft::vector<T, Alloc>::clear()
{
	__destroy_end(__begin);
}

// vector??? ????????? allocator??? ???????????? ????????????.
template<class T, class Alloc>
typename ft::vector<T, Alloc>::allocator_type
ft::vector<T, Alloc>::get_allocator() const
{
	return (__alloc);
}

// ?????? ?????????
// vector ???????????? lhs ??? rhs ?????? ????????? ?????? ????????? ????????????.
// ??????????????? ????????? ????????????, ??? ?????? ??????????????? ????????????.
template <class T, class Alloc>  
bool 
operator == (const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
{
	return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class T, class Alloc>  
bool 
operator != (const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
{
	return (lhs.size() != rhs.size() || !ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class T, class Alloc>  
bool 
operator <  (const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
{
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <class T, class Alloc>  
bool 
operator >  (const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
{
	return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
}

template <class T, class Alloc>  
bool 
operator <= (const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
{
	return (!ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
}

template <class T, class Alloc>  
bool 
operator >= (const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
{
	return (!ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <class T, class Alloc>
void 
swap(std::vector<T, Alloc>& lhs, std::vector<T,Alloc>& rhs)
{
	lhs.swap(rhs);
}

} // namespace ft

#endif // __VECTOR_HPP__

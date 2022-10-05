/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:25:38 by cpak              #+#    #+#             */
/*   Updated: 2022/10/05 12:18:47 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ALLOCATOR_HPP__
#define __ALLOCATOR_HPP__

namespace ft {
	template<typename T>
	class allocator {
		public :
			T			value_type;
			T*			pointer;
			T&			reference;
			const T*	const_pointer;
			const T&	const_reference;
			size_t		size_type;
			ptrdiff_t	difference_type;

			allocator(void);
			~allocator(void);
			T*			address(T&) const;
			const T*	address(const T&) const;
			T*			allocate(size_type n, const void* hint = 0);
			void		deallocate(T* p, size_type n);
			size_type	max_size(void) const throw();
			void		construct(T* p, const T& val);
			void		destroy(T* p);

			template<class U>
			struct rebind 
			{
				typedef allocator<U> other;
			};
	};
}

#endif //__ALLOCATOR_HPP__

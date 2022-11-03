/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:42:13 by cpak              #+#    #+#             */
/*   Updated: 2022/11/03 19:24:46 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <memory>
#include "type_traits.hpp"
#include "iterator.hpp"
#include "pair.hpp"
#include "utility.hpp"

#include <utility>

namespace ft
{

enum color_t {
	BLACK,
	RED
};

template <class T>
class m_iter
{
	
};

template <class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
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

	class value_compare : public ft::binary_function<value_type, value_type, bool>
	{
		friend class map;

	protected:
		key_compare comp;
	
		value_compare(key_compare c) : comp(c) {}
		
	public:
		bool operator() (const value_type& lhs, const value_type& rhs) const
		{ return comp(lhs.first, rhs.first); }
	};

private:
	struct __node {
		__node*			parent;
		__node*			child[2];
		enum color_t	color;
		value_type		data;
	};

	#define LEFT	0
	#define RIGHT	1
	#define left	child[LEFT]
	#define right	child[RIGHT]
	
	typedef typename allocator_type::template rebind<__node>::other		__node_alloc;
	typedef std::allocator_traits<__node_alloc>							__node_alloc_traits;

	key_compare		__key_comp;
	value_compare	__value_comp;
	allocator_type	__alloc;
	__node_alloc	__alloc_node;
	__node*			__tree;

	void __print_tree(const std::string& prefix, const __node* node, bool isLeft)
	{
		if( node != nullptr )
		{
			std::cout << prefix;

			std::cout << (isLeft ? "├──" : "└──" );

			if (node->color == RED)
				std::cout << "\033[1;31m" << node->data.first << "\033[0m" << std::endl;
			else
				std::cout << node->data.first << std::endl;

			__print_tree( prefix + (isLeft ? "│   " : "    "), node->left, true);
			__print_tree( prefix + (isLeft ? "│   " : "    "), node->right, false);
		}
	}

	void __print_tree(const __node* node)
	{
		__print_tree("", node, false);    
	}

	__node*	__get_grandparent(__node* node)
	{
		if ((node != nullptr) && (node->parent != nullptr))
			return (node->parent->parent);
		else
			return (nullptr);
	}

	__node*	__get_uncle(__node* node)
	{
		__node*	g_node = __get_grandparent(node);

		if (g_node == nullptr)
			return (nullptr);
		if (node->parent == g_node->left)
			return (g_node->right);
		else
			return (g_node->left);
	}

	__node* __get_sibling(__node* node)
	{
		if ((node == nullptr) || (node->parent == nullptr))
			return (nullptr);
		if (node == node->parent->left)
			return (node->parent->right);
		else
			return (node->parent->left);
	}

	__node*	__rotate_left(__node* node)
	{
		// rotate node left
		__node*	p_node = node->parent;
		__node*	c_node = node->right;
		__node* gc_node = nullptr;

		if (c_node != nullptr)
			return (node);

		gc_node = c_node->left;
		node->right = gc_node;
		if (gc_node != nullptr)
			gc_node->parent = node;

		c_node->left = node;
		node->parent = c_node;

		c_node->parent = p_node;
		if (p_node != nullptr)
			p_node->left = c_node;
		else
			__tree = c_node;
		return (c_node);
	}

	void	insert_case1(__node* node)
	{
		if (node->parent == nullptr)
			node->color = BLACK;
		else
			insert_case2(node);
	}

	void	insert_case2(__node* node)
	{
		if (node->parent->color == BLACK)
			return ;
		else
			insert_case3_recoloring(node);
	}

	void	insert_case3_recoloring(__node* node)
	{
		__node* g_node = __get_grandparent(node);
		__node*	u_node = __get_uncle(node);

		if ((u_node != nullptr) && (u_node->color == RED))
		{
			node->parent->color = BLACK;
			u_node->color = BLACK;
			g_node->color = RED;
			insert_case1(g_node);
		}
		else
			insert_case4(node);
	}

	void	insert_case4(__node* node)
	{
		__node*	g_node = __get_grandparent(node);

		if ((node == node->parent->right) && (node->parent == g_node->left))
		{
			__rotate_left(node->parent);
			node = node->left;
		} 
		else if ((node == node->parent->left) && (node->parent == g_node->right))
		{
			// __rotate_right(node->parent);
			node = node->right;
		}
	}


		
public:
	explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
	template <class InputIterator>
	map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
	map (const map& x);
	~map();

	map& 								operator =	(const map& x);
	allocator_type 						get_allocator() const;

	iterator							begin();
	const_iterator						begin() const;
	iterator							end();
	const_iterator						end() const;
	reverse_iterator 					rbegin();
	const_reverse_iterator				rbegin() const;
	reverse_iterator 					rend();
	const_reverse_iterator				rend() const;

	bool 								empty() const;
	size_type 							size() const;
	size_type 							max_size() const;

	mapped_type&            			operator[] (const key_type& k);
	mapped_type&            			at (const key_type& k);
	const mapped_type&      			at (const key_type& k) const;

	pair<iterator, bool>    			insert (const value_type& val);
	iterator                			insert (iterator position, const value_type& val);
	template <class InputIterator>  
	void                    			insert (InputIterator first, InputIterator last);
	void                    			erase (iterator position);
	size_type               			erase (const key_type& k);
	void                    			erase (iterator first, iterator last);
	void                    			swap (map& x);
	void                    			clear();

	key_compare 						key_comp() const;
	value_compare 						value_comp() const;

	iterator 							find (const key_type& k);
	const_iterator 						find (const key_type& k) const;
	size_type 							count (const key_type& k) const;
	iterator 							lower_bound (const key_type& k);
	const_iterator 						lower_bound (const key_type& k) const;
	iterator 							upper_bound (const key_type& k);
	const_iterator 						upper_bound (const key_type& k) const;
	pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
	pair<iterator,iterator>             equal_range (const key_type& k);

};

// 요소가 없는 빈 컨테이너를 생성합니다.
template <class Key, class T, class Compare, class Alloc>
ft::map<Key, T, Compare, Alloc>::map (const key_compare& comp, const allocator_type& alloc) :
	__tree(nullptr), __alloc(alloc), __alloc_node(__alloc_node), __key_comp(comp), __value_comp(value_compare(comp))
{}

// 범위 [first,last)만큼 많은 요소가 있는 컨테이너를 생성하고, 각 요소는 해당 범위의 해당 요소로 구성됩니다.
template <class Key, class T, class Compare, class Alloc>
template <class InputIterator>
ft::map<Key, T, Compare, Alloc>::map (InputIterator first, InputIterator last, const key_compare& comp, const allocator_type& alloc)
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

// 컨테이너와 연결된 할당자 객체 복사본을 반환합니다.
template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::allocator_type 						
ft::map<Key, T, Compare, Alloc>::get_allocator() const
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
typename ft::map<Key, T, Compare, Alloc>::size_type
ft::map<Key, T, Compare, Alloc>::size() const
{}

// 컨테이너가 보유할 수 있는 최대 요소의 수를 반환합니다.
template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::size_type
ft::map<Key, T, Compare, Alloc>::max_size() const
{}

// k가 컨테이너에 있는 요소의 키와 일치하면 함수는 매핑된 값에 대한 참조를 반환합니다.
// 일치하지 않는다면 해당 키가 있는 새 요소를 삽입하고 매핑된 값에 대한 참조를 반환합니다.
// 이때마다 항상 컨테이너 크기는 하나씩 증가한다.
template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::mapped_type& 
ft::map<Key, T, Compare, Alloc>::operator[] (const key_type& k)
{}

// 키 k로 식별된 요소의 매핑된 값에 대한 참조를 반환합니다.
// k가 컨테이너에 있는 요소의 키와 일치하지 않으면 함수는 out_of_range 예외를 throw합니다.
template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::mapped_type& 
ft::map<Key, T, Compare, Alloc>::at (const key_type& k)
{}

template <class Key, class T, class Compare, class Alloc>
const typename ft::map<Key, T, Compare, Alloc>::mapped_type& 
ft::map<Key, T, Compare, Alloc>::at (const key_type& k) const
{}



// 새 요소를 삽입하여 컨테이너를 확장하고 삽입된 요소 수만큼 컨테이너 크기를 효과적으로 늘립니다.
// 맵의 요소 키는 고유하기 때문에 컨테이너에 동일한 키를 가진 요소가 있는지 확인합니다.
// 이미 존재한다면 요소가 삽입되지 않고 기존 요소에 대한 반복자를 반환합니다.
// 내부적으로 요소들은 key 값을 comparsion 개체로 비교한 순서대로 정렬되어 있습니다.
// 요소는 이 순서에 따라 항상 해당 위치에 삽입됩니다.
template <class Key, class T, class Compare, class Alloc>
ft::pair<typename ft::map<Key, T, Compare, Alloc>::iterator, bool> 
ft::map<Key, T, Compare, Alloc>::insert (const value_type& val)
{
	// Create new node
	__node* new_node = __node_alloc_traits::allocate(this->__alloc_node, sizeof(__node));
	__alloc_traits::construct(this->__alloc, &new_node->data, val);
	new_node->color = RED;
	new_node->parent = NULL;


	// Locate new node
	__node* tmp_node = this->__tree;
	if (this->__tree == nullptr)
		this->__tree = new_node;
	else
	{
		int dir = __value_comp(tmp_node->data, new_node->data);
		
		while (tmp_node->child[dir] != nullptr)
		{
			tmp_node = tmp_node->child[dir];
			dir = __value_comp(tmp_node->data, new_node->data);
		}
		tmp_node->child[dir] = new_node;
		new_node->parent = tmp_node;
	}

	insert_case1(new_node);

	__print_tree(__tree);



}


// position : 요소를 삽압할 수 있는 위치에 대한 힌트
// 힌트일 뿐이며 맵 컨테이너 내의 해당 위치에 새 요소를 강제로 삽입하지 않습니다. (맵의 요소는 항상 키에 따라 특정 순서를 따릅니다.)
template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::iterator
ft::map<Key, T, Compare, Alloc>::insert (iterator position, const value_type& val)
{}

// first, last : 요소 범위를 지정하는 반복자. 
// [first, last) 범위에 있는 요소의 복사본이 컨테이너에 삽입됩니다. 
// 범위에는 first와 last 사이의 모든 요소가 포함되며, 여기에는 first가 가리키는 요소가 포함되지만 last가 가리키는 요소는 포함되지 않습니다. 
template <class Key, class T, class Compare, class Alloc>
template <class InputIterator>  
void 
ft::map<Key, T, Compare, Alloc>::insert (InputIterator first, InputIterator last)
{}


// 맵 컨테이너에서 단일 요소 또는 요소 범위를 제거합니다. 제거된 요소의 수만큼 컨테이너 크기를 효과적으로 줄여 파괴됩니다. 
// position : 맵에서 제거할 단일 요소를 가리키는 반복자. 역참조 가능한 요소를 가리켜야 합니다. 
template <class Key, class T, class Compare, class Alloc>
void 
ft::map<Key, T, Compare, Alloc>::erase (iterator position)
{}

// k : 맵에서 제거할 요소의 키입니다.
template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::size_type 
ft::map<Key, T, Compare, Alloc>::erase (const key_type& k)
{}

// 제거할 맵 컨테이너 내 범위를 지정하는 반복자. first와 last 사이의 모든 요소가 포함되며 first가 가리키는 요소는 포함되지만 last가 가리키는 요소는 포함되지 않습니다. 
template <class Key, class T, class Compare, class Alloc>
void 
ft::map<Key, T, Compare, Alloc>::erase (iterator first, iterator last)
{}


// 같은 유형의 다른 맵인 x의 내용으로 컨테이너의 내용을 교환합니다. 크기가 다를 수 있습니다. 
// 모든 반복자, 참조 및 포인터는 교환된 개체에 대해 유효한 상태로 유지됩니다. 
// x : 동일한 유형의 다른 맵 컨테이너(즉, 동일한 템플릿 매개변수)
template <class Key, class T, class Compare, class Alloc>
void
ft::map<Key, T, Compare, Alloc>::swap (map& x)
{}

// 맵 컨테이너 에서 모든 요소 (파기됨)를 제거하고 컨테이너의 크기 는 0 으로 유지 합니다.
template <class Key, class T, class Compare, class Alloc>
void
ft::map<Key, T, Compare, Alloc>::clear ()
{}

// 키를 비교하는 함수를 반환합니다.
// 키를 비교하기 위해 컨테이너에서 사용하는 비교 객체의 복사본을 반환합니다. 
// 비교 객체는 컨테이너에 있는 요소의 순서를 결정합니다. 
template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::key_compare 			
ft::map<Key, T, Compare, Alloc>::key_comp() const
{}

// value_type 유형의 객체에서 키를 비교하는 함수를 반환합니다.
// 두 요소를 비교하는 데 사용할 수 있는 비교 개체를 반환하여 첫 번째 요소의 키가 두 번째 요소보다 먼저 이동하는지 여부를 확인합니다.
template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::value_compare 			
ft::map<Key, T, Compare, Alloc>::value_comp() const
{}

// 컨테이너에서 k에 해당하는 키가 있는 요소를 검색하고 발견되면 반복자를 반환하고, 그렇지 않으면 map::end에 대한 반복자를 반환합니다.
// 컨테이너의 비교 객체가 반사적으로 false를 반환하는 경우(즉, 요소가 인수로 전달되는 순서에 관계없이) 두 개의 키는 동일한 것으로 간주됩니다.
template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::iterator
ft::map<Key, T, Compare, Alloc>::find (const key_type& k)
{}

template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::const_iterator
ft::map<Key, T, Compare, Alloc>::find (const key_type& k) const
{}

// 컨테이너에서 k에 해당하는 키가 있는 요소를 검색하고 일치 항목 수를 반환합니다.
// 맵 컨테이너의 요소는 고유하기 때문에 함수는 1과 0만 반환할 수 있습니다. 
template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::size_type 
ft::map<Key, T, Compare, Alloc>::count (const key_type& k) const
{}


// 키가 k보다 앞서는 것으로 간주되지 않는 컨테이너의 첫 번째 요소를 가리키는 반복자를 반환합니다. 
// 함수는 내부 비교 객체(key_comp)를 사용하여 이를 결정하고, key_comp가 false를 반환하는 첫 번째 요소에 대한 반복자를 반환합니다.
// 만약에 맵 클래스가 기본 비교 유형(less)으로 인스턴스화되면 함수는 키가 k보다 작지 않은 첫 번째 요소에 대한 반복자를 반환합니다.
// k : 검색할 키입니다. 
template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::iterator 
ft::map<Key, T, Compare, Alloc>::lower_bound (const key_type& k)
{}

// 지도 개체가 const로 한정된 경우 함수는 const_iterator를 반환합니다. 그렇지 않으면 반복자를 반환합니다.
template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::const_iterator 
ft::map<Key, T, Compare, Alloc>::lower_bound (const key_type& k) const
{}

// 키가 k 다음에 오는 것으로 간주되는 컨테이너의 첫 번째 요소를 가리키는 반복자를 반환합니다.
// 이 함수는 내부 비교 객체(key_comp)를 사용하여 이를 결정하고 key_comp(k,element_key)가 true를 반환하는 첫 번째 요소에 대한 반복자를 반환합니다.
// 만약에 맵 클래스가 기본 비교 유형(less)으로 인스턴스화되면 함수는 키가 k보다 큰 첫 번째 요소에 대한 반복자를 반환합니다.
// k : 검색할 키입니다. 
template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::iterator 
ft::map<Key, T, Compare, Alloc>::upper_bound (const key_type& k)
{}

// 지도 개체가 const로 한정된 경우 함수는 const_iterator를 반환합니다. 그렇지 않으면 반복자를 반환합니다.
template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::const_iterator 
ft::map<Key, T, Compare, Alloc>::upper_bound (const key_type& k) const
{}


// k에 해당하는 키가 있는 컨테이너의 모든 요소를 ​​포함하는 범위의 경계를 반환합니다.
// 맵 컨테이너의 요소에는 고유 키가 있으므로 반환되는 범위에는 최대 단일 요소가 포함됩니다.
// 일치하는 항목이 없으면 반환된 범위의 길이는 0이고 두 반복자는 컨테이너의 내부 비교 개체(key_comp)에 따라 k 다음에 오는 것으로 간주되는 키가 있는 첫 번째 요소를 가리킵니다.
// template <class Key, class T, class Compare, class Alloc>
// ft::pair<const_iterator,const_iterator> 
// ft::map<Key, T, Compare, Alloc>::equal_range (const key_type& k) const
// {}

// // 지도 개체가 const로 한정된 경우 함수는 const_iterator를 반환합니다. 그렇지 않으면 반복자를 반환합니다.
// template <class Key, class T, class Compare, class Alloc>
// ft::pair<iterator,iterator>
// ft::map<Key, T, Compare, Alloc>::equal_range (const key_type& k)
// {}

// lhs의 내용과 rhs의 내용이 동일한지 확인합니다. 동일한 수의 요소를 갖고, 각 요소가 동일한 위치에 있는 lhs의 요소와 동일한지 확인합니다. 
template <class Key, class T, class Compare, class Alloc>
bool 
operator == (const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{}

// lhs의 내용과 rhs의 내용이 다른지 확인합니다.
template <class Key, class T, class Compare, class Alloc>
bool 
operator != (const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{}

// rhs의 내용을 사전 순으로 lhs와 비교합니다. 비교는 std::lexicographical_compare 함수에 의해 수행됩니다. 
template <class Key, class T, class Compare, class Alloc>
bool 
operator < (const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{}

// rhs의 내용을 사전 순으로 lhs와 비교합니다. 비교는 std::lexicographical_compare 함수에 의해 수행됩니다. 
template <class Key, class T, class Compare, class Alloc>
bool 
operator <= (const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{}

// rhs의 내용을 사전 순으로 lhs와 비교합니다. 비교는 std::lexicographical_compare 함수에 의해 수행됩니다. 
template <class Key, class T, class Compare, class Alloc>
bool 
operator > (const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{}

// rhs의 내용을 사전 순으로 lhs와 비교합니다. 비교는 std::lexicographical_compare 함수에 의해 수행됩니다. 
template <class Key, class T, class Compare, class Alloc>
bool 
operator >= (const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{}

// map에 대한 swap 알고리즘을 전문화합니다. lhs와 rhs의 내용을 바꿉니다. lhs.swap(rhs) 함수 호출
template< class Key, class T, class Compare, class Alloc >
void 
swap(std::map<Key, T, Compare, Alloc>& lhs, std::map<Key, T, Compare, Alloc>& rhs)
{}


} // ft

#endif // __MAP_HPP__

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <stdexcept>
#include <cmath>
#include <memory>

#include "../iterators/vector_iterator.hpp"
#include "../iterators/reverse_iterator.hpp"
#include "../utils/utils.hpp"
#include <cstdio>

namespace ft
{
	template <typename T, class Alloc = std::allocator<T>>
	class vector
	{
		public:
		/* -------------------------- ALIASES -------------------------- */
		typedef T			value_type;
		typedef Alloc		allocator_type;
		typedef long int	difference_type;
		typedef size_t	 	size_type;

		typedef T&			reference;
		typedef const T&	const_reference;
		typedef T*			pointer;
		typedef const T*	const_pointer;
		
		typedef typename ft::iterator<T>		iterator;
		typedef const typename ft::iterator<T>  const_iterator;

		typedef typename ft::reverse_iterator<T>		reverse_iterator;
		typedef const typename ft::reverse_iterator<T>  const_reverse_iterator;

		/* ------------------------- ATTRIBUTES ------------------------ */
		private:	
		
		Alloc		_alloc;	// Copy of allocator_type object
		pointer		_array;	// Pointer on an array of T values
		size_type	_size;	// Number of T values inside the vector
		size_type	_capacity;	// Capacity allocated (can be greater than size)

		void	destroy_tmp(vector &tmp)
		{
			for (iterator it = tmp.begin(); it != tmp.end(); ++it)
				tmp._alloc.destroy(&(*it));
			tmp._alloc.deallocate(tmp._array, tmp._capacity);
		}

		public:
		//default constructor - creates a vector with a size of 0.
		explicit vector(const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(0), _capacity(0)
		{ _array = _alloc.allocate(_capacity); }

		//filling constructor - creates a container with n elems
		explicit vector(size_type n, const value_type& val = value_type(),
					const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(n), _capacity(n)
		{
			_array = _alloc.allocate(_capacity);
			for (size_type i = 0; i < _size; ++i)
				_alloc.construct(&_array[i], val);
		}

		//range constructor - creates a container with as many elems, as in the range [first,last]
		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) : _alloc(alloc), _size(0)
		{
			InputIterator tmp(first);
			while (tmp++ != last)
				_size++;
			_capacity = _size;
			_array = _alloc.allocate(_capacity);
			for (int i = 0; first != last; ++first, ++i)
				_alloc.construct(&_array[i], *first);
		}

		//copy constructor - creates a vector with the same size and copy/construct
		//all x values to the new area allocated.
		vector(const vector& copy)
		{ *this = copy; }

		~vector()
		{
			for (iterator it = begin(); it != end(); ++it)
				_alloc.destroy(&(*it));
			_alloc.deallocate(_array, _capacity);
		}

		vector& operator= (const vector& object)
		{
			if (this = &object)
				return (*this);
			if (_array) //maybe not needed
			{
				for (size_t i = 0; i < _size; i++)
					_alloc.destroy(&_array[i]);
				_alloc.deallocate(_array, _capacity);
			}
			iterator	it = object.begin();
			_alloc = object._alloc;
			_size = object._size;
			_capacity = object._capacity;
			_array = _alloc.allocate(_capacity);
			for (size_t i = 0; it != object.end(); i++, it++)
				_alloc.construct(&_array[i], *it);
		}

		/* ------------------------- ITERATORS ------------------------- */
	
		//end iterators point to smth after the last element in array
		//accessing them will cause undefined behaviour (same for rend for reverse_it)
		iterator		begin()
		{ return iterator(_array); }
		iterator		end()
		{ return iterator(_array + _size); }
	
		const_iterator  begin() const
		{ return const_iterator(_array); }
		const_iterator  end() const
		{ return const_iterator(_array + _size); }

		reverse_iterator rbegin()
		{ return reverse_iterator(_array + _size - 1); }
		reverse_iterator rend()
		{ return reverse_iterator(_array - 1); }

		const_reverse_iterator rbegin() const
		{ return const_reverse_iterator(_array + _size - 1); }
		const_reverse_iterator rend() const	
		{ return const_reverse_iterator(_array - 1); }
		
		/* -------------------------- CAPACITY ------------------------- */

		size_type	size() const
		{ return _size; }
		size_type	max_size() const
		{ return (_alloc.max_size()); }
		size_type	capacity() const
		{ return _capacity; }
		
		void resize(size_type n, value_type val = value_type())
		{
			if (n > _capacity)
			{
				reserve(n);
				for (; _size < n; _size++)
					_alloc.construct(&_array[_size], val);
				_size = n;
			}
			else if (n > _size && n < _capacity)
			{
				for (size_t i = _size; i < n; i++)
					_alloc.construct(&_array[i], val);
				_size = n;
			}
			else if (n < _size)
				while (n < _size)
					pop_back();
		}

		bool	empty() const
		{
			switch (_size)
			{
			case 0:
				return true;
				break;
			default:
				return false;
				break;
			}
		}

		//	Requests that the vector capacity be at least enough to contain n elements. If the
		//	actual capacity is greater than n, nothing happen. If the capacity requested 
		//	is > than max size, a lenght_error exception is thrown.
		void	reserve(size_type n)
		{
			if (n > max_size())
				throw std::length_error("vector");
			if (n > _capacity)
			{
				try
				{
					vector	tmp(this);
					for (size_type i = 0; i < _size; i++)
						_alloc.destroy(&_array[i]);
					_alloc.deallocate(_array, _capacity);
					_array = _alloc.allocate(_array, n);
					for (size_type i = 0; i < _size; i++)
						_alloc.construct(&_array[i], tmp[i]);
					destroy_tmp(tmp);
					_capacity = n;
				}
				catch(const std::exception& e)
				{
					std::cerr << e.what() << '\n';
				}
			}
		}

		/* ---------------------- ELEMENTS ACCESS ---------------------- */
		reference operator[] (size_type n)
		{ return _array[n]; }
		const_reference operator[] (size_type n) const
		{ return _array[n]; }

		//returns a reference to the elem at position n, it checks if n is out of bounds
		//operator[] doesn't check
		reference at(size_type n)
		{
			if (!(n < _size))
				throw std::out_of_range("vector");
			return _array[n];
		}
		const_reference at(size_type n) const
		{
			if (!(n < _size))
				throw std::out_of_range("vector");
			return _array[n];
		}

		//returns a reference to the first elem in the vector
		reference front()
		{ return _array[0]; }
		const_reference front() const
		{ return _array[0]; }
		//returns a reference to the last elem in the vector
		reference back()
		{ return _array[_size - 1]; }
		const_reference back() const
		{ return _array[_size - 1]; }

		/* ------------------------- MODIFIERS ------------------------- */
		
		//assigns new contents to the vector, replacing its current content, 
		//and modifying its size accordingly. The new contents are elements constructed 
		//from each of the elements in the range between first and last iterators

		template <class InputIterator>
		void assign (InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
		{
			clear();
			size_type n = static_cast<size_type>(last - first);
			if (n > _capacity)
			{
				_alloc.deallocate(_array, _capacity);
				_array = _alloc.allocate(n);
			}
			size_type i = 0;
			for (; first != last; ++i, ++first)
				_alloc.construct(&_array[i], *first);
			_size = i;
		}
 
		void assign (size_type n, const value_type& val)
		{
			clear();
			if (n > _capacity)
			{
				_alloc.deallocate(_array, _capacity);
				_array = _alloc.allocate(n);
			}
			for (size_type i = 0; i < n; ++i)
				_alloc.construct(&_array[i], val);
			_size = n;
		}

		//adds a new element at the end of the vector, after its current last element.
		//size is increased and a reallocation happen if actual capacity isn't enough.
		void push_back (const value_type &val)
		{
			if (_size + 1 > _capacity)
				reserve(_size + 1);
			_size += 1;
			_alloc.construct(&_array[_size], val);
		}

		//removes the last element in the vector, reducing the container size by one.
		//this destroys the removed element. Does nothing if the vector is empty.
		void pop_back()
		{
			if (_size)
			{
				_alloc.destroy(&_array[_size - 1]);
				_size -= 1;
			}
		}

		//inserts 1 element with a value of val at a position, and increases the vector' size
		//reallocation will occured only if vector's capacity isn't enough
		iterator	insert(iterator position, const value_type &val)
		{
			//we save position in case of realloc happened, because array will
			//point to another address then
			difference_type index = position - begin();
			insert(position, 1, val);
			return iterator(&_array[index]);
		}

		//inserts n elements with a value of val at a position, and increases the vector' size
		void	insert(iterator position, size_type n, const value_type& val)
		{
			//we save position in case of realloc happened, because array will
			//point to another address then
			difference_type index = position - begin();
			if (_size + n > _capacity)
				reserve(_size + n);
			//if realloc happened we create new iterator pointing to correct address
			iterator newPosition(&_array[index]);
			//move at (newPosition + n) all elements after newPosition if nP isn't the last elem
			if (newPosition != end())
				move_elems_right(newPosition, n);
			//insert new elems to this space
			for (size_type i = 0; i < n; ++i)
				_alloc.construct(&(*newPosition++), val);
			_size += n;
		}

		//inserts all elements between first and last, and increases the vector' size
		template <class InputIterator>
		void	insert(iterator position, InputIterator first, InputIterator last, 
					typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
		{
			size_type n = 0;
			InputIterator tmp(first);
			while (tmp++ != last)
				++n;
			difference_type index = position - begin();

			if (_size + n > _capacity)
				reserve(_size + n);
			iterator newPosition(&_array[index]);
			if (newPosition != end())
				move_elems_right(newPosition, n);
			//constructing n new elements from the iterator's range
			for (size_type i = 0; i < n; ++i)
				_alloc.construct(&(*newPosition++), *first++);
			_size += n;
		}

		//removes from the vector a single element and reduces vector' size by 1
		//erasing elements other than vector.end() will occured a reallocation
		iterator erase (iterator position)
		{ return erase(position, position + 1); }

		//removes from the vector all elements between first and last, and reduces vector' size
		//erasing elements other than from vector.end() to vector.end() will occured a reallocation
		iterator erase (iterator first, iterator last)
		{
			if (first == end() || first == last)
				return first;
			difference_type index = first - begin();
			//If there are elements after the iterators range, we need to move them at first position
			if (last < end())
			{
				move_elems_left(first, last);
				_size -= static_cast<size_type>(last - first);
			}
			else
			{
				size_type newSize = _size - static_cast<size_type>(last - first);
				while (_size != newSize)
					pop_back();
			}
			return iterator(&_array[index]);
		}

		void	clear()
		{
			while (_size)
				pop_back();
			_size = 0;
		}

		void	swap(vector &x)
		{
			vector	tmp(this);
			_alloc = x._alloc;
			_size = x._size;
			_capacity = x._capacity;
			_array = x._array;

			x._alloc = tmp._alloc;
			x._size = tmp._size;
			x._capacity = tmp._capacity;
			x._array = tmp._array;
			destroy_tmp(tmp);
		}

		/* --------------- NON-MEMBER FUNCTION OVERLOADS --------------- */

		friend bool operator==(const vector &lhs, const vector &rhs)
		{
			if (lhs.size() != rhs.size())
				return false;
			for (ft::pair<const_iterator, const_iterator> it(lhs.begin(), rhs.begin());
					it.first != lhs.end(); ++it.first, ++it.second)
				if (*(it.first) != *(it.second))
					return false;
			return true;
		}

		friend bool operator!=(const vector& lhs, const vector& rhs)
		{ return !(lhs == rhs); }

		friend bool operator<(const vector& lhs, const vector& rhs)
		{
			for (ft::pair<const_iterator, const_iterator> it(lhs.begin(), rhs.begin());
					it.first != lhs.end() && it.second != rhs.end(); ++it.first, ++it.second)
				if (*(it.first) < *(it.second))
					return true;
			return (lhs.size() < rhs.size());
		}

		friend bool operator>(const vector& lhs, const vector& rhs)
		{ return rhs < lhs; }

		friend bool operator<=(const vector& lhs, const vector& rhs)
		{ return !(rhs < lhs); }
	
		friend bool operator>=(const vector& lhs, const vector& rhs)
		{ return !(lhs < rhs); }

		friend void swap (vector &x, vector &y)
		{ x.swap(y); }

		/* ------------------ PRIVATE MEMBER FUNCTIONS ----------------- */
		private:

		//Move to the right all elements from a certain position until the end 
		//of the array. Each element will be constructed/copied to his new position,
		//and destructed at his previous position.
		void move_elems_right(iterator pos, size_type lenMove)
		{
			// Starting from the end, until it meets pos iterator
			for (ft::pair<iterator, iterator> it(end() - 1, end());
				it.second != pos; --it.first, --it.second)
			{
				_alloc.construct(&(*(it.first + lenMove)), *it.first);
				_alloc.destroy(&(*it.first));
			}
		}

		//Move to the left all elements from a certain position until the end 
		//of the array. Each element will be constructed/copied to his new position,
		//and destructed at his previous position.
		// first Iterator pointing to the new range's beginning, elements will be
		// moved to this position.
		// last Iterator pointing to the first element to move. Every element after
		//this one until the end will be moved.
		void move_elems_left(iterator first, iterator last)
		{
			// destructing the previous element to replace it by a new one,
			// first will destroy all the element until the end.
			// then moving a new element to the left at first position, only if there is
			// still element to move
			for (; first != end(); ++first, ++last)
			{
				_alloc.destroy(&(*first));
				if (last < end())
					_alloc.construct(&(*(first)), *last);
			}
		}
			
	};
}

#endif
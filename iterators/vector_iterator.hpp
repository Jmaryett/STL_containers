#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include <iostream>
#include "../utils/type1_ot_type2.hpp"

#define ADD 1
#define SUBSTRACT 0

namespace ft
{
	template <typename T, bool B>
	class reverse_iterator;
	
	template <typename T, bool B>
	class iterator
	{
		public:
			typedef long int										difference_type;
			typedef T												value_type;
			typedef size_t											size_type;

			typedef std::random_access_iterator_tag					iterator_category;
			typedef typename chooseConst<B, T&, const T&>::type		reference;
			typedef typename chooseConst<B, T&, const T&>::type		pointer;
			typedef T*												elemPtr;

		private:
			elemPtr	_val;
 
		public:

				/**
				*   Default constructor, creates a vector_iterator pointing to val.
				*
				*   @param val  A pointer to a T element. Value initialized if not provided.
				*/
				iterator(elemPtr val = 0) : _val(val) {}
						
				/**
				*   Copy constructor : creates a const iterator pointing to the same T element.
				*   Convert constructor : creates a iterator from a const iterator,
				*   pointing to the same T element.
				*   
				*   @param copy     The iterator that will be copied.
				*/
				iterator(const iterator<T, false>& copy)
				{ _val = copy.getElemPtr(); }

				~iterator() {}

				/**
				*   Assign a iterator to this iterator. Both iterators will point to the
				*   same T element.
				*   
				*   @param x        The iterator that will be assigned.
				*/
				iterator& operator=(const iterator& assign)
				{
					if (this != &assign)
						_val = assign._val;
					return (*this);
				}


				/* ------------------------------------------------------------- */
				/* --------------------------- GETTERS ------------------------- */

				/**
				*   @return A non constant pointer to the actual element that the iterator is 
				*           pointing to.
				*/
				elemPtr getElemPtr() const      { return _val; }


				/* ------------------------------------------------------------- */
				/* --------------------- OPERATOR OVERLOADS -------------------- */

				reference operator*() const         { return (*_val); }
				pointer operator->() const          { return (_val); }

				iterator& operator++()       { ++_val; return (*this); }
				iterator& operator--()       { --_val; return (*this); }
				
				iterator operator++(int)
				{
					iterator res(*this);
					++(*this);
					return (res);
				}
				
				iterator operator--(int)
				{
					iterator res(*this);
					--(*this);
					return (res);
				}
				
				bool operator==(const iterator& it) const
				{ return (it._val == _val); }
				bool operator!=(const iterator& it) const
				{ return (it._val != _val); }
				bool operator<(const iterator& it) const
				{ return (it._val > this->_val); }
				bool operator>(const iterator& it) const
				{ return (it._val < this->_val); }
				bool operator<=(const iterator& it) const
				{ return (it._val >= this->_val); }
				bool operator>=(const iterator& it) const
				{ return (it._val <= this->_val); }
				
				/**
				*   Increments 1 time iterator position.
				*/
				iterator& operator+=(int nb)
				{
					movePtr(this->_val, nb, ADD);
					return (*this);
				}

				/**
				*   Increments nb times iterator position.
				*/
				iterator operator+(int nb) const
				{
					iterator it(*this);
					
					movePtr(it._val, nb, ADD);
					return (it);
				}
				
				/**
				*   Decrements 1 time iterator position.
				*/
				iterator& operator-=(int nb)
				{
					movePtr(this->_val, nb, SUBSTRACT);
					return (*this);
				}

				/**
				*   Decrements nb times iterator position.
				*/
				iterator operator-(int nb) const
				{
					iterator it(*this);
					
					movePtr(it._val, nb, SUBSTRACT);
					return (it);
				}

				/**
				*   @return     A reference to iterator + nb. Undefined behavior if the reference
				*               returned is out of container's range.
				*/
				reference operator[](int nb) const
				{
					value_type* tmp(this->_val);

					movePtr(tmp, nb, ADD);
					return (*tmp);
				}

				/**
				*   @return     The range's lenght between this iterator and another one.
				*/
				difference_type operator-(iterator it) const
				{
					return (this->_val - it._val);
				}
				
				/* --------------- NON-MEMBER OPERATOR OVERLOADS --------------- */ 
				
				friend iterator operator+(int nb, const iterator& it)
				{
					iterator newIt(it);
					return (newIt += nb);
				}

				friend iterator operator-(int nb, const iterator& it)
				{
					iterator newIt(it);
					return (newIt -= nb);
				}

				/* ------------------ PRIVATE MEMBER FUNCTIONS ----------------- */

			private:

				/**
				*   Moves random_acces_iterator's pointer. Adapt between addition / substraction
				*   operation. 
				*
				*   @param val  The pointer to move.
				*   @param nb   Number of time the pointer will be increased / decreased.
				*   @param sign Indicate if it's an addition or a substraction.
				*/
				void movePtr(elemPtr& val, long nb, bool sign) const
				{
					int mov;

					// If addtion, mov will be positive. If substraction, negative.
					if (sign == ADD)
						mov = nb > 0 ? mov = 1: mov = -1;
					else
						mov = nb > 0 ? mov = -1: mov = 1;

					if (nb < 0)
						nb *= -1;
					for (; nb > 0; --nb)
						val += mov;
				}
	};
} // namespace ft


#endif
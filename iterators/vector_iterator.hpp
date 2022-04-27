#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include <iostream>
#include "reverse_iterator.hpp"

namespace ft
{
	template <class T>
	class reverse_iterator;
	
	template <class T>
	class iterator
	{
	private:
		T	*current; 
	public:
		//default and copy constructor
		iterator(T*	first = 0)
		{ current = first; }
		iterator(const iterator<T> &copy)
		{ *this = copy; }
		iterator&	operator=(const iterator &object)
		{
			if (this == &object)
				return (*this);
			current = object.current;
			return (*this);
		}

		//getter
		T*	getValue() const
		{ return (current); }

		//overloads
		iterator	operator+(int n)
		{
			current += n;
			return (*this);
		}
		iterator	operator-(int n)
		{
			current -= n;
			return (*this);
		}
		iterator&	operator+=(int nb)
		{ 
			int	move = 1;

			if (nb < 0)
				nb *= -1;
			for (; nb > 0; --nb)
				current += move;
			return (*this);
		}
		iterator&	operator-=(int nb)
		{ 
			int	move = -1;

			if (nb < 0)
				nb *= -1;
			for (; nb > 0; --nb)
				current += move;
			return (*this);
		}

		iterator	operator++(int)
		{ iterator tmp = *this; ++(*this); return tmp; }
		iterator	operator--(int)
		{ iterator tmp = *this; --(*this); return tmp; }
		iterator&	operator++()
		{ current++; return (*this); }
		iterator&	operator--()
		{ current--; return (*this); }
	
		bool	operator!=(const iterator &it)
		{ return current != it.current; }
		bool	operator==(const iterator &it)
		{ return !(current != it.current); }
		bool	operator<=(const iterator &it)
		{ return (current <= it.current); }
		bool	operator>=(const iterator &it)
		{ return (current >= it.current); }
		bool	operator<(const iterator &it)
		{ return !(current >= it.current); }
		bool	operator>(const iterator &it)
		{ return !(current <= it.current); }

		T&	operator*() const
		{ return *current; }
		T*	operator->()
		{ return current; }


		iterator&	operator[](int nb) const
		{
			T*	tmp(this->current);
			tmp += nb;
			return (*tmp);
		}

		~iterator(){};
	};
} // namespace ft


#endif
#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "vector_iterator.hpp"

namespace ft
{
	template <typename T>
	class reverse_iterator
	{
	private:
		T	*reverse; 
	public:
		//default and copy constructor
		reverse_iterator(T*	first = 0)
		{ reverse = first; }
		reverse_iterator(const reverse_iterator<T> &copy)
		{ this = copy; }
		reverse_iterator&	operator=(const reverse_iterator &object)
		{
			if (this == &object)
				return (*this);
			reverse = object.reverse;
			return (*this);
		}
		//initialize constructor to create a reverse_iterator from original one
		explicit reverse_iterator(const iterator<T> &copy)
		{ reverse = copy.getValue() - 1; }
		
		~reverse_iterator(){};

		//getter
		T*	getValue() const
		{ return (reverse); }

		//returns base iterator pointing next elem after reverse points to
		iterator	base() const
		{
			iterator it(reverse + 1);
			return (it);
		}

		//overloads will be vice-versa
		reverse_iterator operator+(int n)
		{
			reverse += n;
			return (*this);
		}
		reverse_iterator operator-(int n)
		{
			reverse -= n;
			return (*this);
		}
		reverse_iterator&	operator+=(int nb)
		{ 
			int	move = -1;

			if (nb < 0)
				nb *= -1;
			for (; nb > 0; --nb)
				reverse += move;
			return (*this);
		}
		reverse_iterator&	operator-=(int nb)
		{ 
			int	move = 1;

			if (nb < 0)
				nb *= -1;
			for (; nb > 0; --nb)
				reverse += move;
			return (*this);
		}

		reverse_iterator	operator++(int)
		{ reverse_iterator tmp = *this; --(*this); return tmp; }
		reverse_iterator	operator--(int)
		{ reverse_iterator tmp = *this; ++(*this); return tmp; }
		reverse_iterator&	operator++()
		{ reverse--; return (*this); }
		reverse_iterator&	operator--()
		{ reverse++; return (*this); }
	
		bool	operator!=(const reverse_iterator &it)
		{ return reverse != it.reverse; }
		bool	operator==(const reverse_iterator &it)
		{ return !(reverse != it.reverse); }
		bool	operator<=(const reverse_iterator &it)
		{ return (reverse <= it.reverse); }
		bool	operator>=(const reverse_iterator &it)
		{ return (reverse >= it.reverse); }
		bool	operator<(const reverse_iterator &it)
		{ return !(reverse >= it.reverse); }
		bool	operator>(const reverse_iterator &it)
		{ return !(reverse <= it.reverse); }

		T&	operator*() const
		{ return *reverse; }
		T*	operator->()
		{ return reverse; }

		reverse_iterator&	operator[](int nb) const
		{
			T*	tmp(this->reverse);
			tmp += nb;
			return (*tmp);
		}
	};

	template <typename T>
	reverse_iterator<T> operator+(int nb, const reverse_iterator<T>& rev_it)
	{
		reverse_iterator	ret(rev_it);
		return (ret += nb);
	}

	template <typename T>
	reverse_iterator<T> operator-(int nb, const reverse_iterator<T>& rev_it)
	{
		reverse_iterator	ret(rev_it);
		return (ret -= nb);
	}		
}

#endif
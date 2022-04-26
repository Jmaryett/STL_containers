#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>

namespace ft
{
	//will check if type will be true then will replace type with int
	//in func we called enable_if
	template <bool B>
	struct enable_if {};
	template <>
	struct enable_if<true> 
	{
		typedef int type;
	};
	
	//is_integral----------------------------------------------//
	template <typename>
	struct is_integral : std::false_type {};
	
	template <>
	struct is_integral<bool> : std::true_type {};

	template <>
	struct is_integral<char> : std::true_type {};

	template <>
	struct is_integral<char16_t> : std::true_type {};

	template <>
	struct is_integral<char32_t> : std::true_type {};

	template <>
	struct is_integral<wchar_t> : std::true_type {};

	template <>
	struct is_integral<signed char> : std::true_type {};

	template <>
	struct is_integral<short int> : std::true_type {};

	template <>
	struct is_integral<int> : std::true_type {};

	template <>
	struct is_integral<int> : std::true_type {};

	template <>
	struct is_integral<long int> : std::true_type {};

	template <>
	struct is_integral<long long int> : std::true_type {};

	template <>
	struct is_integral<unsigned char> : std::true_type {};

	template <>
	struct is_integral<unsigned short int> : std::true_type {};

	template <>
	struct is_integral<unsigned int> : std::true_type {};

	template <>
	struct is_integral<unsigned long int> : std::true_type {};

	template <>
	struct is_integral<unsigned long long int> : std::true_type {};
	//-------------------------------------------------------------//

	//pair class--------------------------------------------------//
	template <class T1, class T2>
	class pair
	{
	private:
		T1	first;
		T2	second;
	public:
		pair() : first(), second() {};

		template<class U, class V>
		pair(const pair<U,V> &pr)
		{
			first = pr.first;
			second = pr.second;
		}
		pair(const T1 &a, const T2 &b) : first(a), second(b) {};

		pair(const pair<T1,T2> &pr)
		{ this = pr; }

		pair&	operator=(const pair &pr)
		{
			if (this == pr)
				return (*this);
			first = pr.first;
			second = pr.second;
			return (*this);
		}

		~pair() {};

		bool	operator!=(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
		{ return !(lhs == rhs); }

		bool	operator==(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
		{ return lhs.first ==rhs.first && lhs.second ==rhs.second; }
		
		bool	operator<=(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
		{ return !(rhs < lhs); }
		
		bool	operator>=(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
		{ return !(lhs < rhs); }
		
		bool	operator<(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
		{ return lhs.first < rhs,first || (!(rhs.first < lhs.first) && lhs.second < rhs.second); }
		
		bool	operator>(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
		{ return rhs < lhs; }

		//----------------------------------------------------------------------------------//

		template <class T1, class T2>
		pair<T1,T2> make_pair(T1 x, T2 y)
		{
			return (pair<T1,T2>(x,y));
		}

		//---------------------------------------------------------------------------------//

	};
	
}
#endif
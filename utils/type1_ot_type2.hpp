#ifndef TYPE1_OR_TYPE2
#define TYPE1_OR_TYPE2

namespace ft
{
	//using boolean type if cont or not
	template <bool isConst, typename isFalse, typename isTrue>
	struct chooseConst {};

	//typedef: pointer, ref
	template <typename isFalse, typename isTrue>
	struct chooseConst<false, isFalse, isTrue>
	{
		typedef isFalse type;
	};
	
	//typedef: const_pointer, const_ref
	template <typename isFalse, typename isTrue>
	struct chooseConst<true, isFalse, isTrue>
	{
		typedef isTrue type;
	};
}

#endif

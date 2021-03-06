#pragma once 

#include <memory>
#include "TypeTraits.h"
#include "Iterator.h"
#include "Construct.h"

template <class InputIterator, class ForwardIterator>
inline ForwardIterator
__Uninitialized_Copy_Aux(InputIterator first, InputIterator last,
                         ForwardIterator result, __TrueType) 
{
	return copy(first, last, result);
}


template <class InputIterator, class ForwardIterator>
ForwardIterator __Uninitialized_Copy_Aux(InputIterator first, InputIterator last,
                                         ForwardIterator result, __FalseType)

{
	//return copy(first, last, result);
	ForwardIterator cur = result;
	for (; cur != last; ++first, ++cur)
	{
		Construct(&*cur, *first);
	}

	return cur;
}

template <class InputIterator, class ForwardIterator, class T>
inline ForwardIterator
__UninitializedCopy(InputIterator first, InputIterator last,
ForwardIterator result, T*)
{
	return __UninitializedCopyAux(first, last, result, __TypeTraits<T>::IsPODType());
}

template <class InputIterator, class ForwardIterator>
inline ForwardIterator
UninitializedCopy(InputIterator first, InputIterator last, ForwardIterator result)
{
	return __UninitializedCopy(first, last, result, ValueType(result));
}

// �ػ�
inline char*
UninitializedCopy(const char* first, const char* last, char* result)
{
	memmove(result, first, last - first);
	return result + (last - first);
}

inline wchar_t*
UninitializedCopy(const wchar_t* first, const wchar_t* last, wchar_t* result)
{
	memmove(result, first, sizeof(wchar_t)* (last - first));
	return result + (last - first);
}

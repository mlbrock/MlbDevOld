//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
/*	C++ Support Library Include File														*/
//	////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the 'InterlockedValue' class.

	Revision History	:	2004-05-12 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2004 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
//	////////////////////////////////////////////////////////////////////////////

#ifndef HH__MLB__CPPSupp__InterlockedValue_h__HH

#define HH__MLB__CPPSupp__InterlockedValue_h__HH	1

//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
// Necessary include files...
//	////////////////////////////////////////////////////////////////////////////

#ifdef _Windows
# pragma warning(disable:4710 4786)
# if _MSC_VER >= 1300
#  pragma warning(disable:4217 4251 4555)
# endif // # if _MSC_VER >= 1300
# pragma warning(disable:4018 4100 4146 4244 4245 4511 4512 4663)
# include <Windows.h>
# if _MSC_VER >= 1300
#  pragma warning(default:4217 4251 4555)
# endif // # if _MSC_VER >= 1300
# pragma warning(default:4018 4100 4146 4244 4245 4511 4512 4663)
#else
#endif // #ifdef _Windows

#include "ScopedLock.h"

//	////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace CPPSupp {

//	////////////////////////////////////////////////////////////////////////////
template <class ValueType, class LockType> class InterlockedValue {
	public:
		InterlockedValue(ValueType in_value = static_cast<ValueType>(0)) :
			value_data(in_value), lock_data() { }

		volatile ValueType Increment() {
			MyLockWriter my_lock(lock_data);
			value_data += static_cast<ValueType>(1);
			return(value_data);
		}

		volatile ValueType Decrement() {
			MyLockWriter my_lock(lock_data);
			value_data -= static_cast<ValueType>(1);
			return(value_data);
		}

		volatile ValueType GetValue() const {
			MyLockReader my_lock(lock_data);
			return(value_data);
		}

		volatile ValueType SetValue(ValueType new_value) {
			MyLockWriter my_lock(lock_data);
			ValueType old_value = value_data;
			value_data = new_value;
			return(old_value);
		}

		volatile ValueType CompareSetValue(ValueType new_value,
			ValueType comperand) {
			MyLockWriter my_lock(lock_data);
			if (value_data != comperand)
				return(value_data);
			ValueType old_value = value_data;
			value_data = new_value;
			return(old_value);
		}

		// Need to add pre- and post-fix increment and decrement.

	private:
		typedef MLB::CPPSupp::ScopedLockReader<LockType> MyLockReader;
		typedef MLB::CPPSupp::ScopedLockWriter<LockType> MyLockWriter;

		// Copy ctor and assignment op not implemented.
		InterlockedValue(const InterlockedValue &src);
		InterlockedValue & operator = (const InterlockedValue &src);

		volatile ValueType value_data;
		mutable LockType   lock_data;
};
//	////////////////////////////////////////////////////////////////////////////

} // namespace CPPSupp

} // namespace MLB

#endif // #ifndef HH__MLB__CPPSupp__InterlockedValue_h__HH


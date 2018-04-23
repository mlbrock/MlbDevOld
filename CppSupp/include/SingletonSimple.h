//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
/*	C++ Support Library Include File														*/
//	////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the 'SingletonSimple' class.

	Revision History	:	2004-05-12 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2004 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
//	////////////////////////////////////////////////////////////////////////////

#ifndef HH__MLB__CPPSupp__SingletonSimple_h__HH

#define HH__MLB__CPPSupp__SingletonSimple_h__HH	1

//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
// Necessary include files...
//	////////////////////////////////////////////////////////////////////////////

#include "LocalLock.h"

//	////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace CPPSupp {

//	////////////////////////////////////////////////////////////////////////////
template <class SingletonType> class SingletonSimple {
	public:
		static SingletonType& Instance() {
			if (the_ptr == NULL) {
				the_lock.Lock();
				if (the_ptr == NULL) {
/*
					the_ptr = new SingletonType;
					atexit(&DestroySingletonSimple);
*/
					SingletonTypePtr tmp_ptr = new SingletonType;
					if (tmp_ptr != NULL) {
						the_ptr = tmp_ptr;
						atexit(&DestroySingletonSimple);
					}
				}
				the_lock.Unlock();
			}
			return const_cast<SingletonType &>(*the_ptr);
		}
	
	private:
		static void DestroySingletonSimple() {
			the_lock.Lock();
			if (the_ptr != NULL) {
				delete the_ptr;
				the_ptr = NULL;
			}
			the_lock.Unlock();
		}

		typedef typename SingletonType *SingletonTypePtr;

		static SingletonTypePtr        the_ptr;
		static MLB::CPPSupp::LocalLock the_lock;
};
template <class SingletonType>
	typename SingletonSimple<SingletonType>::SingletonTypePtr
		SingletonSimple<SingletonType>::the_ptr;
template <class SingletonType>
	MLB::CPPSupp::LocalLock
		SingletonSimple<SingletonType>::the_lock;
//	////////////////////////////////////////////////////////////////////////////

} // namespace CPPSupp

} // namespace MLB

#endif // #ifndef HH__MLB__CPPSupp__SingletonSimple_h__HH


/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	C++ Support Library Include File														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include and implementation file for the NullLock class.

	Revision History	:	1998-04-08 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef HH__MLB__CPPSupp__NullLock_h__HH

#define HH__MLB__CPPSupp__NullLock_h__HH	1

namespace MLB {

namespace CPPSupp {

/*	***********************************************************************	*/
class NullLock {
	public:
		NullLock() { }
		~NullLock() { }

		int  Lock()       const { return(0); }
		int  LockReader() const { return(Lock()); }
		int  LockWriter() const { return(Lock()); }
		int  Unlock()     const { return(0); }

	private:
		NullLock(const NullLock &other);
		NullLock & operator=(const NullLock &other);
};
/*	***********************************************************************	*/

} // namespace CPPSupp

} // namespace MLB

#endif // #ifndef HH__MLB__CPPSupp__NullLock_h__HH


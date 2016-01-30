//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
/*	C++ Support Library Include File														*/
//	////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the 'LocalLock' class.

	Revision History	:	2004-05-12 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2004 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
//	////////////////////////////////////////////////////////////////////////////

#ifndef HH__MLB__CPPSupp__LocalLock_h__HH

#define HH__MLB__CPPSupp__LocalLock_h__HH	1

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

//	////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace CPPSupp {

#ifdef _Windows
//	////////////////////////////////////////////////////////////////////////////
class Win32CriticalSection {
	public:
		Win32CriticalSection() {
			InitializeCriticalSection(&critical_section);
		}
		~Win32CriticalSection() {
			DeleteCriticalSection(&critical_section);
		}

		int Lock() const {
			EnterCriticalSection(&critical_section);
			return(0);
		}
		int LockReader() const {
			return(Lock());
		}
		int LockWriter() const {
			return(Lock());
		}
		int Unlock() const {
			LeaveCriticalSection(&critical_section);
			return(0);
		}

	private:
		Win32CriticalSection(const Win32CriticalSection &other);
		Win32CriticalSection & operator=(const Win32CriticalSection &other);

		mutable CRITICAL_SECTION critical_section;
};
//	////////////////////////////////////////////////////////////////////////////
typedef Win32CriticalSection LocalLock;
#else
# include <MTIF_MtrO.h>
typedef MLB::MTIF::MtrO LocalLock;
#endif // #ifdef _Windows

} // namespace CPPSupp

} // namespace MLB

#endif // #ifndef HH__MLB__CPPSupp__LocalLock_h__HH


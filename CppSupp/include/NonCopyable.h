//	//////////////////////////////////////////////////////////////////////////
//	//////////////////////////////////////////////////////////////////////////
//	C++ Support Library Include File
//	//////////////////////////////////////////////////////////////////////////
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include and implementation file for the NonCopyable
								class.

	Revision History	:	1999-12-08 --- Creation.
									Michael L. Brock

								Based upon the work of Philippe Elie and John Levon
								for Boost.

		Copyright Michael L. Brock 1999 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
//	//////////////////////////////////////////////////////////////////////////

#ifndef HH__MLB__CPPSupp__NonCopyable_h__HH

#define HH__MLB__CPPSupp__NonCopyable_h__HH	1

namespace MLB {

namespace CPPSupp {

//	//////////////////////////////////////////////////////////////////////////
//	//////////////////////////////////////////////////////////////////////////
// Macros for use in your classes. Note that the access is changed to
//	to 'private' by these macros.
//	//////////////////////////////////////////////////////////////////////////
#define MLB_CPPSupp_NonCopyable_MacroCopyCTor(type_name)			\
	private: type_name (const type_name &other)
#define MLB_CPPSupp_NonCopyable_MacroAssignment(type_name)		\
	private: type_name & operator = (const type_name &other)
#define MLB_CPPSupp_NonCopyable_Macro(type_name)					\
	MLB_CPPSupp_NonCopyable_MacroCopyCTor(type_name);				\
	MLB_CPPSupp_NonCopyable_MacroAssignment(type_name)				\
//	//////////////////////////////////////////////////////////////////////////

//	//////////////////////////////////////////////////////////////////////////
class NonCopyable {
	protected:
		NonCopyable() { }
		~NonCopyable() { }

	MLB_CPPSupp_NonCopyable_Macro(NonCopyable);
};
//	//////////////////////////////////////////////////////////////////////////

} // namespace CPPSupp

} // namespace MLB

#endif // #ifndef HH__MLB__CPPSupp__NonCopyable_h__HH


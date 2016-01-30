//	//////////////////////////////////////////////////////////////////////////
//	//////////////////////////////////////////////////////////////////////////
//	C++ Support Library Include File
//	//////////////////////////////////////////////////////////////////////////
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include and implementation file for generalized
								exceptions.

	Revision History	:	1998-04-08 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
//	//////////////////////////////////////////////////////////////////////////

#ifndef HH__MLB__CPPSupp__ExceptionGeneral_h__HH

#define HH__MLB__CPPSupp__ExceptionGeneral_h__HH	1

//	//////////////////////////////////////////////////////////////////////////
//	//////////////////////////////////////////////////////////////////////////
//	Required include files . . .
//	//////////////////////////////////////////////////////////////////////////

#include <mbcompat.h>

#ifdef _Windows
# pragma warning(disable:4018 4100 4146 4244 4290 4511 4512 4663)
# include <exception>
# include <iostream>
# include <ostream>
# include <sstream>
# include <string>
# pragma warning(default:4018 4100 4146 4244 4290 4511 4512 4663)
#else
# include <exception>
# include <iostream>
# include <ostream>
# include <sstream>
# include <string>
#endif // #ifdef _Windows
//	//////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace CPPSupp {

//	//////////////////////////////////////////////////////////////////////////
template <class CharType = char>
	class ExceptionGeneralType : public std::exception {
	public:
		typedef std::basic_string<CharType>        ThisStringType;
		typedef std::basic_ostringstream<CharType> ThisOStreamType;

		ExceptionGeneralType() throw()
			: std::exception("Unspecified exception."),
			except_string("Unspecified exception.") { }
		ExceptionGeneralType(const CharType *in_except_string) throw()
			: std::exception(in_except_string),
			except_string(in_except_string) { }
		ExceptionGeneralType(const ThisStringType &in_except_string) throw()
			: std::exception(in_except_string.c_str()),
			except_string(in_except_string) { }
		ExceptionGeneralType(const ThisOStreamType &in_except_string) throw()
			: std::exception(in_except_string.str().c_str()),
			except_string(in_except_string.str()) { }
		~ExceptionGeneralType() throw() { }

	private:
		ThisStringType except_string;
};
//	//////////////////////////////////////////////////////////////////////////

//	//////////////////////////////////////////////////////////////////////////
typedef ExceptionGeneralType<char> ExceptionGeneral;
//	//////////////////////////////////////////////////////////////////////////

//	//////////////////////////////////////////////////////////////////////////
template <class CharType = char>
	class ExceptionWithCodeType : public ExceptionGeneralType<CharType> {
	public:
		typedef ExceptionGeneralType<CharType> ParentNick;
		ExceptionWithCodeType() throw() :
			ExceptionGeneralType(GetErrorString()),
			error_code(GetLastErrorCode()) { }

		ExceptionWithCodeType(int in_error_code) throw() :
			ExceptionGeneralType<CharType>(GetErrorString(in_error_code)),
			error_code(in_error_code) { }
		ExceptionWithCodeType(const CharType *in_except_string) throw() :
			ExceptionGeneralType<CharType>(GetErrorString(in_except_string)),
			error_code(GetLastErrorCode()) { }
		ExceptionWithCodeType(const ThisStringType &in_except_string) throw() :
			ExceptionGeneralType<CharType>(GetErrorString(in_except_string.
			c_str())), error_code(GetLastErrorCode()) { }
		ExceptionWithCodeType(const ThisOStreamType &in_except_string) throw() :
			ExceptionGeneralType<CharType>(GetErrorString(in_except_string.str().
			c_str())), error_code(GetLastErrorCode()) { }

		ExceptionWithCodeType(int in_error_code, const CharType *in_except_string)
			throw() :
			ExceptionGeneralType<CharType>(GetErrorString(in_error_code,
			in_except_string)), error_code(in_error_code) { }
		ExceptionWithCodeType(int in_error_code, ThisStringType &in_except_string)
			throw() :
			ExceptionGeneralType<CharType>(GetErrorString(in_error_code,
			in_except_string.c_str())), error_code(in_error_code) { }
		ExceptionWithCodeType(int in_error_code,
			ThisOStreamType  &in_except_string) throw() :
			ExceptionGeneralType<CharType>(GetErrorString(in_error_code,
			in_except_string.str().c_str())), error_code(in_error_code) { }

		~ExceptionWithCodeType() throw() { }

		virtual int GetErrorCode() {
			return(error_code);
		}

	protected:

		virtual int GetLastErrorCode() {
#ifdef _Windows
			return(GetLastError());
#else
# include <errno.h>
			return(errno);	
#endif // #ifdef _Windows
		}

		virtual std::string GetErrorString(const char *error_text = NULL) {
			return(GetErrorString(GetLastErrorCode(), error_text));
		}
		virtual std::string GetErrorString(int error_code,
			const char *error_text = NULL) {
			std::stringstream out_string;
			if (error_text != NULL)
				out_string << error_text << ": ";
			out_string << "Error code = " << error_code;
			return(out_string.str());
		}

		int error_code;
};
//	//////////////////////////////////////////////////////////////////////////

//	//////////////////////////////////////////////////////////////////////////
typedef ExceptionWithCodeType<char> ExceptionWithCode;
//	//////////////////////////////////////////////////////////////////////////

} // namespace CPPSupp

} // namespace MLB

namespace std {

//	//////////////////////////////////////////////////////////////////////////
template <class CharType>
	inline std::ostream & operator << (std::ostream &o_str,
	const MLB::CPPSupp::ExceptionGeneralType<CharType> &datum) 
{
	return(o_str << datum.what());
}
//	//////////////////////////////////////////////////////////////////////////

//	//////////////////////////////////////////////////////////////////////////
template <class CharType>
	inline std::ostream & operator << (std::ostream &o_str,
	const MLB::CPPSupp::ExceptionWithCodeType<CharType> &datum) 
{
	return(o_str << datum.what());
}
//	//////////////////////////////////////////////////////////////////////////

} // namespace std

#endif // #ifndef HH__MLB__CPPSupp__ExceptionGeneral_h__HH


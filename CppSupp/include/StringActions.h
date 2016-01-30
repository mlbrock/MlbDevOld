//	//////////////////////////////////////////////////////////////////////////
//	//////////////////////////////////////////////////////////////////////////
//	C++ Support Library Include File
//	//////////////////////////////////////////////////////////////////////////
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for string actions logic.

	Revision History	:	1998-04-08 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
//	//////////////////////////////////////////////////////////////////////////

#ifndef HH__MLB__CPPSupp__StringActions_h__HH

#define HH__MLB__CPPSupp__StringActions_h__HH	1

//	//////////////////////////////////////////////////////////////////////////
//	//////////////////////////////////////////////////////////////////////////
//	Required include files . . .
//	//////////////////////////////////////////////////////////////////////////

#include <mbcompat.h>

#ifdef _Windows
# pragma warning(disable:4018 4100 4146 4244 4290 4511 4512 4663)
# include <cctype>
# include <deque>
# include <exception>
# include <iostream>
# include <ostream>
# include <sstream>
# include <string>
# pragma warning(default:4018 4100 4146 4244 4290 4511 4512 4663)
#else
# include <cctype>
# include <deque>
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
inline std::string &UpperCase(std::string &src_string) {
	std::transform(src_string.begin(), src_string.end(), src_string.begin(),
		std::toupper);
	return(src_string);
}
//	//////////////////////////////////////////////////////////////////////////

//	//////////////////////////////////////////////////////////////////////////
inline std::string &LowerCase(std::string &src_string) {
	std::transform(src_string.begin(), src_string.end(), src_string.begin(),
		std::tolower);
	return(src_string);
}
//	//////////////////////////////////////////////////////////////////////////

//	//////////////////////////////////////////////////////////////////////////
inline std::string &TrimRight(std::string &src_string,
	const std::string &trim_char_list = " \t\r\n\v\f") {
	return(src_string.erase(src_string.find_last_not_of(trim_char_list) + 1));
}
//	//////////////////////////////////////////////////////////////////////////

//	//////////////////////////////////////////////////////////////////////////
inline std::string &TrimLeft(std::string &src_string,
	const std::string &trim_char_list = " \t\r\n\v\f") {
	return(src_string.erase(0, src_string.find_first_not_of(trim_char_list)));
}
//	//////////////////////////////////////////////////////////////////////////

//	//////////////////////////////////////////////////////////////////////////
inline std::string &Trim(std::string &src_string,
	const std::string &trim_char_list = " \t\r\n\v\f") {
	return(TrimLeft(TrimRight(src_string, trim_char_list), trim_char_list));
}
//	//////////////////////////////////////////////////////////////////////////

//	//////////////////////////////////////////////////////////////////////////
struct CharWideToMultiByte_char {
	explicit CharWideToMultiByte_char(const std::wostringstream &in_string) :
		string_datum(Convert(in_string.str().c_str())) {
	}
	explicit CharWideToMultiByte_char(const std::wstring &in_string) :
		string_datum(Convert(in_string.c_str())) {
	}
	explicit CharWideToMultiByte_char(const wchar_t *in_string) :
		string_datum(Convert(in_string)) {
	}
	~CharWideToMultiByte_char() {
		if (string_datum != NULL) {
			free(string_datum);
			string_datum = NULL;
		}
	}

	const char *Get() const {
		return(string_datum);
	}

	char *string_datum;

	static char *Convert(const wchar_t *in_string) {
		int   in_length = (in_string == NULL) ? 1 :
			(wcstombs(NULL, in_string, 0) + 1);
		char *out_string;

		if (in_length < 1)
			throw std::invalid_argument("Wide-character string can not be: \
converted: One or more invalid characters were encountered.");
			
		out_string = static_cast<char *>(calloc(in_length, sizeof(char)));
		if (out_string == NULL)
			throw std::bad_alloc("Wide-character string can not be converted: \
Couldn't allocate memory for the destination string.");

		wcstombs(out_string, in_string, in_length);
		return(out_string);
	}
};
//	//////////////////////////////////////////////////////////////////////////

//	//////////////////////////////////////////////////////////////////////////
struct CharWideToMultiByte_string {
	explicit CharWideToMultiByte_string(const std::wostringstream &in_string) :
		string_datum(Convert(in_string.str().c_str())) {
	}
	explicit CharWideToMultiByte_string(const std::wstring &in_string) :
		string_datum(Convert(in_string.c_str())) {
	}
	explicit CharWideToMultiByte_string(const wchar_t *in_string) :
		string_datum(Convert(in_string)) {
	}
	~CharWideToMultiByte_string() {
	}

	const std::string Get() const {
		return(string_datum);
	}

	std::string string_datum;

	static std::string Convert(const wchar_t *in_string) {
		return(CharWideToMultiByte_char(in_string).Get());
	}
};
//	//////////////////////////////////////////////////////////////////////////

//	//////////////////////////////////////////////////////////////////////////
struct CharMultiByteToWide_char {
	explicit CharMultiByteToWide_char(const std::ostringstream &in_string) :
		string_datum(Convert(in_string.str().c_str())) {
	}
	explicit CharMultiByteToWide_char(const std::string &in_string) :
		string_datum(Convert(in_string.c_str())) {
	}
	explicit CharMultiByteToWide_char(const char *in_string) :
		string_datum(Convert(in_string)) {
	}
	~CharMultiByteToWide_char() {
		if (string_datum != NULL) {
			free(string_datum);
			string_datum = NULL;
		}
	}

	const wchar_t *Get() const {
		return(string_datum);
	}

	wchar_t *string_datum;

	static wchar_t *Convert(const char *in_string) {
		int   in_length = (in_string == NULL) ? 1 :
			(mbstowcs(NULL, in_string, 0) + 1);
		wchar_t *out_string;

		if (in_length < 1)
			throw std::invalid_argument("MBCS-character string can not be: \
converted: One or more invalid characters were encountered.");
			
		out_string = static_cast<wchar_t *>(calloc(in_length, sizeof(wchar_t)));
		if (out_string == NULL)
			throw std::bad_alloc("MBCS-character string can not be converted: \
Couldn't allocate memory for the destination string.");

		mbstowcs(out_string, in_string, in_length);
		return(out_string);
	}
};
//	//////////////////////////////////////////////////////////////////////////

//	//////////////////////////////////////////////////////////////////////////
struct CharMultiByteToWide_string {
	explicit CharMultiByteToWide_string(const std::ostringstream &in_string) :
		string_datum(Convert(in_string.str().c_str())) {
	}
	explicit CharMultiByteToWide_string(const std::string &in_string) :
		string_datum(Convert(in_string.c_str())) {
	}
	explicit CharMultiByteToWide_string(const char *in_string) :
		string_datum(Convert(in_string)) {
	}
	~CharMultiByteToWide_string() {
	}

	const std::wstring Get() const {
		return(string_datum);
	}

	std::wstring string_datum;

	static std::wstring Convert(const char *in_string) {
		return(CharMultiByteToWide_char(in_string).Get());
	}
};
//	//////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
inline void Split(const std::string &in_string, const std::string &find_string,
	std::deque<std::string> &out_list, std::string::size_type start_pos = 0,
	bool discard_empty_sections = false)
{
	std::string::size_type  in_length   = in_string.size();
	std::string::size_type  find_length = find_string.size();

	//	Append to the list any separator-delimited sub-string sections.
	while (start_pos < in_length) {
		std::string::size_type found_pos = in_string.find(find_string, start_pos);
		if (found_pos == std::string::npos)
			break;
		if ((!discard_empty_sections) || (found_pos != start_pos))
			out_list.push_back(in_string.substr(start_pos, found_pos - start_pos));
		start_pos = found_pos + find_length;
	}

	//	There may be a trailing sub-string; if so, grab it...
	if ((start_pos <= in_length) &&
		((!discard_empty_sections) || (start_pos < in_length)))
		out_list.push_back(in_string.substr(start_pos));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
inline std::deque<std::string> GetSplit(const std::string &in_string,
	const std::string &find_string, std::string::size_type start_pos = 0,
	bool discard_empty_sections_flag = false)
{
	std::deque<std::string> out_list;

	Split(in_string, find_string, out_list, start_pos,
		discard_empty_sections_flag);

	return(out_list);
}
//	////////////////////////////////////////////////////////////////////////////

} // namespace CPPSupp

} // namespace MLB

#endif // #ifndef HH__MLB__CPPSupp__StringActions_h__HH


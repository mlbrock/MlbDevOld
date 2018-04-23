//	//////////////////////////////////////////////////////////////////////////
//	//////////////////////////////////////////////////////////////////////////
//	C++ Support Library Unit Test Module File
//	//////////////////////////////////////////////////////////////////////////
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Unit test for string actions logic.

	Revision History	:	1998-04-08 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
//	//////////////////////////////////////////////////////////////////////////

//	//////////////////////////////////////////////////////////////////////////
//	//////////////////////////////////////////////////////////////////////////
//	Required include files . . .
//	//////////////////////////////////////////////////////////////////////////

#include "StringActions.h"

#include <iomanip>

//	//////////////////////////////////////////////////////////////////////////

//	//////////////////////////////////////////////////////////////////////////
static const std::string  TEST_SplitStringList[] = {
	"0|1|2",
	"|0|1|2",
	"0|1|2|",
	"||0|1|2",
	"0|1|2||",
	"0||1|2",
	"INT:30.172.65.3:20000:S017:S017|\
INT:30.172.65.3:20001:S018:S018|\
INT:30.172.65.3:21000:S019:S019|\
INT:30.172.65.3:21001:S020:S020|\
CAST:30.172.65.3:50000:S021:S021|\
CAST:30.172.65.3:51000:S022:S022|\
CAST:30.172.65.3:50000:S023:S023|\
CAST:30.172.65.3:51000:S024:S024",
};
static const unsigned int TEST_SplitStringCount  =
	sizeof(TEST_SplitStringList) / sizeof(TEST_SplitStringList[0]);
//	//////////////////////////////////////////////////////////////////////////

//	//////////////////////////////////////////////////////////////////////////
static const wchar_t      *TEST_WideCharList[] = {
	L"Line one",
	L"Line two",
	L"Line three",
	L"Line four",
	L"Line five",
	L"Line six",
	L"Line seven",
};
static const unsigned int  TEST_WideCharCount  =
	sizeof(TEST_WideCharList) / sizeof(TEST_WideCharList[0]);
//	//////////////////////////////////////////////////////////////////////////

//	//////////////////////////////////////////////////////////////////////////
int TEST_SplitString();
int TEST_WideChar();
//	//////////////////////////////////////////////////////////////////////////

//	//////////////////////////////////////////////////////////////////////////
int main()
{
	int return_code = EXIT_SUCCESS;

	if (TEST_SplitString() != EXIT_SUCCESS)
		return_code = EXIT_FAILURE;

	if (TEST_WideChar() != EXIT_SUCCESS)
		return_code = EXIT_FAILURE;

	return(return_code);
}
//	//////////////////////////////////////////////////////////////////////////

//	//////////////////////////////////////////////////////////////////////////
int TEST_SplitString()
{
	int          return_code = EXIT_SUCCESS;
	unsigned int count_1;

	for (count_1 = 0; count_1 < TEST_SplitStringCount; count_1++) {
		std::deque<std::string> out_list;
		std::cout << std::setfill('=') << std::setw(79) << "" <<
			std::setfill(' ') << std::endl;
		std::cout << std::right << std::setw(5) << count_1 << std::left <<
			":[" << TEST_SplitStringList[count_1] << "]" << std::endl;
		MLB::CPPSupp::Split(TEST_SplitStringList[count_1], "|", out_list, 0, false);
		while (!out_list.empty()) {
			std::cout << ">>> [" << out_list.front() << "]" << std::endl;
			out_list.pop_front();
		}
		std::cout << std::setfill('-') << std::setw(79) << "" <<
			std::setfill(' ') << std::endl;
		MLB::CPPSupp::Split(TEST_SplitStringList[count_1], "|", out_list, 0, true);
		while (!out_list.empty()) {
			std::cout << ">>> [" << out_list.front() << "]" << std::endl;
			out_list.pop_front();
		}
		std::cout << std::setfill('=') << std::setw(79) << "" <<
			std::setfill(' ') << std::endl;
	}

	return(return_code);
}
//	//////////////////////////////////////////////////////////////////////////

//	//////////////////////////////////////////////////////////////////////////
int TEST_WideChar()
{
	int          return_code = EXIT_SUCCESS;
	unsigned int count_1;

	for (count_1 = 0; count_1 < TEST_WideCharCount; count_1++) {
		const wchar_t     *src_ptr   = TEST_WideCharList[count_1];
		const std::string  dst_ptr_s =
			MLB::CPPSupp::CharWideToMultiByte_string(src_ptr).Get();
		const std::wstring dst_ptr_w =
			MLB::CPPSupp::CharMultiByteToWide_char(dst_ptr_s).Get();
		std::cout << std::setw(3) << std::right << count_1 << ":" << std::left <<
			"[" << dst_ptr_s << "] ---> ";
		if (wcslen(src_ptr) != dst_ptr_w.length()) {
			std::cout << "ERROR: Lengths differ (" << wcslen(src_ptr) <<
				" versus " << dst_ptr_w.length() << ")";
			return_code = EXIT_FAILURE;
		}
		else if (memcmp(src_ptr, dst_ptr_w.c_str(),
			dst_ptr_w.length() * sizeof(wchar_t))) {
			std::cout << "ERROR: Contents differ.";
			return_code = EXIT_FAILURE;
		}
		else
			std::cout << "OK";
		std::cout << std::endl;
	}

	return(return_code);
}
//	//////////////////////////////////////////////////////////////////////////


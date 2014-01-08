/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	STL Support Library Test Harness Module File										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Test harness module for template class multiset_LC<>.

	Revision History	:	1998-04-08 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Required include files . . .															*/
/*	***********************************************************************	*/

#ifdef _Windows
# pragma warning(disable:4710 4786)
# if _MSC_VER >= 1300
#  pragma warning(disable:4217 4251 4555)
# endif /* # if _MSC_VER >= 1300 */
# pragma warning(disable:4018 4100 4146 4244 4245 4511 4512 4663)
# include <iomanip>
# include <iostream>
# include <sstream>
# if _MSC_VER >= 1300
#  pragma warning(default:4217 4251 4555)
# endif /* # if _MSC_VER >= 1300 */
# pragma warning(default:4018 4100 4146 4244 4245 4511 4512 4663)
#else
# include <iomanip>
# include <iostream>
# include <sstream>
#endif /* #ifdef _Windows */

#include <strfuncs.h>
#include <sdtif.h>

#include "multiset_LC.h"

#include <MTIF_MtrO.h>

/*	***********************************************************************	*/

/*	***********************************************************************	*/
typedef std::multiset<int>                                       BaseCollType;
typedef MLB::CPPSupp::STLSupp::multiset_LC<int>                  NullCollType;
typedef MLB::CPPSupp::STLSupp::multiset_LC<int, MLB::MTIF::MtrO> ThisCollType;
typedef BaseCollType::iterator                              Iter;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static int  TEST_SUPP_GetArgUInt(const char *arg_name, const char *in_arg_value,
   unsigned int *out_arg_value, std::string &error_text);
static void TEST_SUPP_GetFuncNameMax(void);
static ThisCollType TEST_SUPP_CreateThis(unsigned int index_start = 0,
	unsigned int element_count = 100);
static BaseCollType TEST_SUPP_CreateBase(unsigned int index_start = 0,
	unsigned int element_count = 100);
static ThisCollType TEST_SUPP_CreateThisSpec(unsigned int element_count = 100,
	int element_value = 12345);
static BaseCollType TEST_SUPP_CreateBaseSpec(unsigned int element_count = 100,
	int element_value = 12345);
static void TEST_SUPP_FillCollThis(unsigned int index_start,
	unsigned int element_count, ThisCollType &in_coll);
static void TEST_SUPP_FillCollBase(unsigned int index_start,
	unsigned int element_count, BaseCollType &in_coll);
static void TEST_SUPP_FillCollThisSpec(unsigned int element_count,
	int element_value, ThisCollType &in_coll);
static void TEST_SUPP_FillCollBaseSpec(unsigned int element_count,
	int element_value, BaseCollType &in_coll);
static void TEST_SUPP_EmitBarEqual(void);
static void TEST_SUPP_EmitBar(char in_char);
static bool TEST_SUPP_EmitResults(const char *func_name, const char *test_name,
	bool in_ok_flag, bool this_ok_flag, const char *failure_text);
static void TEST_SUPP_SpeedTest(unsigned int speed_test_count);
static bool TEST_ScopedLocks(const char *func_name, unsigned int element_count);
static bool TEST_Cons_1_A(const char *func_name, unsigned int element_count);
static bool TEST_Cons_InputIterator(const char *func_name, unsigned int element_count);
static bool TEST_Cons_BaseCollType(const char *func_name, unsigned int element_count);
static bool TEST_ConsCopy(const char *func_name, unsigned int element_count);
static bool TEST_ConsAssign(const char *func_name, unsigned int element_count);
static bool TEST_Op_Eq(const char *func_name, unsigned int element_count);
static bool TEST_Begin(const char *func_name, unsigned int element_count);
static bool TEST_Clear(const char *func_name, unsigned int element_count);
static bool TEST_Empty(const char *func_name, unsigned int element_count);
static bool TEST_End(const char *func_name, unsigned int element_count);
static bool TEST_Erase_1(const char *func_name, unsigned int element_count);
static bool TEST_Erase_2(const char *func_name, unsigned int element_count);
static bool TEST_Insert_1(const char *func_name, unsigned int element_count);
static bool TEST_Insert_2(const char *func_name, unsigned int element_count);
static bool TEST_Insert_3(const char *func_name, unsigned int element_count);
static bool TEST_Max_Size(const char *func_name, unsigned int element_count);
static bool TEST_Rbegin(const char *func_name, unsigned int element_count);
static bool TEST_Rend(const char *func_name, unsigned int element_count);
static bool TEST_Swap(const char *func_name, unsigned int element_count);
static bool TEST_GetData_1(const char *func_name, unsigned int element_count);
static bool TEST_GetData_2(const char *func_name, unsigned int element_count);
static bool TEST_GetDataRef(const char *func_name, unsigned int element_count);
static bool TEST_GetDataPtr(const char *func_name, unsigned int element_count);
static bool TEST_GetLockRef(const char *func_name, unsigned int element_count);
static bool TEST_GetLockPtr(const char *func_name, unsigned int element_count);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
typedef struct {
	const char  *func_name;
	bool       (*func_ptr)(const char *func_name, unsigned int element_count);
} TEST_CONTROL;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#define TEST_MAKE_FUNC_ENTRY(func_name)	\
	{	#func_name, func_name	}
static const TEST_CONTROL TEST_FuncList[] = {
	TEST_MAKE_FUNC_ENTRY(TEST_ScopedLocks),
	TEST_MAKE_FUNC_ENTRY(TEST_Cons_1_A),
	TEST_MAKE_FUNC_ENTRY(TEST_Cons_InputIterator),
	TEST_MAKE_FUNC_ENTRY(TEST_Cons_BaseCollType),
	TEST_MAKE_FUNC_ENTRY(TEST_ConsCopy),
	TEST_MAKE_FUNC_ENTRY(TEST_ConsAssign),
	TEST_MAKE_FUNC_ENTRY(TEST_Begin),
	TEST_MAKE_FUNC_ENTRY(TEST_Clear),
	TEST_MAKE_FUNC_ENTRY(TEST_Empty),
	TEST_MAKE_FUNC_ENTRY(TEST_End),
	TEST_MAKE_FUNC_ENTRY(TEST_Erase_1),
	TEST_MAKE_FUNC_ENTRY(TEST_Erase_2),
	TEST_MAKE_FUNC_ENTRY(TEST_Insert_1),
	TEST_MAKE_FUNC_ENTRY(TEST_Insert_2),
	TEST_MAKE_FUNC_ENTRY(TEST_Insert_3),
	TEST_MAKE_FUNC_ENTRY(TEST_Max_Size),
	TEST_MAKE_FUNC_ENTRY(TEST_Rbegin),
	TEST_MAKE_FUNC_ENTRY(TEST_Rend),
	TEST_MAKE_FUNC_ENTRY(TEST_Swap),
	TEST_MAKE_FUNC_ENTRY(TEST_Op_Eq),
	TEST_MAKE_FUNC_ENTRY(TEST_GetData_1),
	TEST_MAKE_FUNC_ENTRY(TEST_GetData_2),
	TEST_MAKE_FUNC_ENTRY(TEST_GetDataRef),
	TEST_MAKE_FUNC_ENTRY(TEST_GetDataPtr),
	TEST_MAKE_FUNC_ENTRY(TEST_GetLockRef),
	TEST_MAKE_FUNC_ENTRY(TEST_GetLockPtr)
};
static const unsigned int TEST_FuncCount  =
	sizeof(TEST_FuncList) / sizeof(TEST_FuncList[0]);
#undef TEST_MAKE_FUNC_ENTRY
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static unsigned int TEST_FuncNameMax = 0;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int main(int argc, char **argv)
{
	int                return_code      = EXIT_SUCCESS;
	unsigned int       iteration_count  = 1;
	unsigned int       element_count    = 100;
	unsigned int       speed_test_count = 100000;
	unsigned int       failure_count    = 0;
	unsigned int       count_1;
	unsigned int       count_2;
	std::ostringstream o_str;
	std::string        error_text;

	std::cerr << "Test harness for MLB::CPPSupp::STLSupp::multiset_LC<>" <<
		std::endl << std::endl;

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if ((!stricmp(argv[count_1], "-h")) ||
			(!stricmp(argv[count_1], "-help"))) {
			std::cerr << std::endl << std::endl << "USAGE: " <<
				extract_file_name(argv[0]) << " " <<
				"[ -h | -help ] | " <<
				"[ <iteration-count> [ <element-count> [ <speed-test-count> ] ] ]"
				<< std::endl << std::endl;
			goto EXIT_FUNCTION;
		}
	}

	if (argc > 4) {
		o_str << "Invalid number of command line parameters --- " <<
			"use '-h' for help.";
		error_text  = o_str.str();
		return_code = EXIT_FAILURE;
		goto EXIT_FUNCTION;
	}
	else {
		if ((argc > 1) && ((return_code = TEST_SUPP_GetArgUInt("iteration count",
			argv[1], &iteration_count, error_text)) != EXIT_SUCCESS))
			goto EXIT_FUNCTION;
		if ((argc > 2) && ((return_code = TEST_SUPP_GetArgUInt("element count",
			argv[2], &element_count, error_text)) != EXIT_SUCCESS))
			goto EXIT_FUNCTION;
		if ((argc > 3) && ((return_code = TEST_SUPP_GetArgUInt("speed test count",
			argv[3], &speed_test_count, error_text)) != EXIT_SUCCESS))
			goto EXIT_FUNCTION;
	}

	TEST_SUPP_EmitBarEqual();
	TEST_SUPP_EmitBarEqual();
	std::cout << "Test harness for MLB::CPPSupp::STLSupp::multiset_LC<>" <<
		std::endl;
	TEST_SUPP_EmitBarEqual();
	std::cout << "Test Iteration Count            : " <<
		std::setw(10) << iteration_count << std::endl;
	std::cout << "Number of Tests Per Iteration   : " <<
		std::setw(10) << TEST_FuncCount << std::endl;
	std::cout << "Number of Elements Per Test     : " <<
		std::setw(10) << element_count << std::endl;
	std::cout << "Number of Speed Tests Iterations: " <<
		std::setw(10) << speed_test_count << std::endl;
	TEST_SUPP_EmitBarEqual();

	TEST_SUPP_GetFuncNameMax();

	for (count_1 = 0; count_1 < iteration_count; count_1++) {
		for (count_2 = 0; count_2 < TEST_FuncCount; count_2++) {
			if (!(*TEST_FuncList[count_2].func_ptr)
				(TEST_FuncList[count_2].func_name, element_count)) {
				failure_count++;
				return_code = EXIT_FAILURE;
			}
		}
	}

	TEST_SUPP_EmitBarEqual();

	o_str << "A total of " << failure_count << " out of " << TEST_FuncCount <<
		" regression tests failed.";
	error_text = o_str.str();

	std::cout <<
		((return_code == EXIT_SUCCESS) ? "SUCCESS: " : "ERROR  : ") <<
		error_text << std::endl;

	TEST_SUPP_EmitBarEqual();
	TEST_SUPP_EmitBarEqual();

	if (return_code == EXIT_SUCCESS)
		TEST_SUPP_SpeedTest(speed_test_count);

EXIT_FUNCTION:

	if (return_code != EXIT_SUCCESS)
		std::cerr << std::endl << std::endl << "ERROR  : " << error_text <<
			std::endl << std::endl;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static int TEST_SUPP_GetArgUInt(const char *arg_name, const char *in_arg_value,
   unsigned int *out_arg_value, std::string &error_text)
{
	int                return_code;
	std::ostringstream o_str;

 	if ((str_digit(in_arg_value, 0) == NULL) && (atof(in_arg_value) >= 1.0) &&
		(atof(in_arg_value) <= double(UINT_MAX))) {
		*out_arg_value = atoi(in_arg_value);
		return_code    = EXIT_SUCCESS;
	}
	else {
		o_str << "Invalid " << arg_name << " parameter encountered ('" <<
			in_arg_value <<
			"') --- expected an integral value in the range 1 to " <<
			UINT_MAX << ", inclusive.";
		error_text  = o_str.str();
		return_code = EXIT_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static void TEST_SUPP_GetFuncNameMax()
{
	unsigned int count_1;

	TEST_FuncNameMax = 0;

	for (count_1 = 0; count_1 < TEST_FuncCount; count_1++)
		TEST_FuncNameMax =
			(TEST_FuncNameMax >= strlen(TEST_FuncList[count_1].func_name)) ?
			TEST_FuncNameMax : strlen(TEST_FuncList[count_1].func_name);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static ThisCollType TEST_SUPP_CreateThis(unsigned int index_start,
	unsigned int element_count)
{
	ThisCollType new_coll;

	TEST_SUPP_FillCollThis(index_start, element_count, new_coll);

	return(new_coll);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static BaseCollType TEST_SUPP_CreateBase(unsigned int index_start,
	unsigned int element_count)
{
	BaseCollType new_coll;

	TEST_SUPP_FillCollBase(index_start, element_count, new_coll);

	return(new_coll);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static ThisCollType TEST_SUPP_CreateThisSpec(unsigned int element_count,
	int element_value)
{
	ThisCollType new_coll;

	TEST_SUPP_FillCollThisSpec(element_count, element_value, new_coll);

	return(new_coll);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static BaseCollType TEST_SUPP_CreateBaseSpec(unsigned int element_count,
	int element_value)
{
	BaseCollType new_coll;

	TEST_SUPP_FillCollBaseSpec(element_count, element_value, new_coll);

	return(new_coll);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static void TEST_SUPP_FillCollThis(unsigned int index_start,
	unsigned int element_count, ThisCollType &in_coll)
{
	TEST_SUPP_FillCollBase(index_start, element_count, in_coll.GetDataRef());
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static void TEST_SUPP_FillCollBase(unsigned int index_start,
	unsigned int element_count, BaseCollType &in_coll)
{
	while (element_count--)
		in_coll.insert(index_start++);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static void TEST_SUPP_FillCollThisSpec(unsigned int element_count,
	int element_value, ThisCollType &in_coll)
{
	TEST_SUPP_FillCollBaseSpec(element_count, element_value, in_coll.GetDataRef());
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static void TEST_SUPP_FillCollBaseSpec(unsigned int element_count,
	int element_value, BaseCollType &in_coll)
{
	while (element_count--)
		in_coll.insert(element_value);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static void TEST_SUPP_EmitBarEqual()
{
	TEST_SUPP_EmitBar('=');
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static void TEST_SUPP_EmitBar(char in_char)
{
	std::cout << std::setfill(in_char) << std::setw(78) <<
		"" << std::setfill(' ') << std::endl;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_SUPP_EmitResults(const char *func_name, const char *test_name,
	bool in_ok_flag, bool this_ok_flag, const char *failure_text)
{
	std::cout << "RESULTS | " << std::left << std::setw(TEST_FuncNameMax) <<
		func_name << " | " << test_name << " | " <<
		((this_ok_flag) ? "OK" : "FAILURE: ") <<
		((this_ok_flag) ? "" : failure_text) << std::endl;

	return((!in_ok_flag) ? in_ok_flag : this_ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static void TEST_SUPP_SpeedTest(unsigned int speed_test_count)
{
	unsigned int    count_1;
	BaseCollType    base_coll;
	NullCollType    this_coll_1;
	ThisCollType    this_coll_2;
	SDTIF_STAT_TVAL stat_data;
	char            buffer_1[SDTIF_FMTI_TIME_LEN_TIMEVAL + 1];
	char            buffer_2[SDTIF_FMTI_TIME_LEN_TIMEVAL + 1];

	std::cout << std::endl;
	TEST_SUPP_EmitBarEqual();
	TEST_SUPP_EmitBarEqual();
	std::cout << "Speed Comparison Test" << std::endl;
	TEST_SUPP_EmitBarEqual();

	std::cout << std::left << std::setw(30) << "Test Name" << " " <<
		std::left << std::setw(10) << "Test Count" << " " <<
		std::left <<
		std::setw(SDTIF_FMTI_TIME_LEN_TIMEVAL - 11) << "Total Time" << " " <<
		std::left <<
		std::setw(SDTIF_FMTI_TIME_LEN_TIMEVAL - 11) << "Average Time" <<
		std::endl;
	std::cout << std::string(30, '-') << " " << std::string(10, '-') << " " <<
		std::string(SDTIF_FMTI_TIME_LEN_TIMEVAL - 11, '-') << " " <<
		std::string(SDTIF_FMTI_TIME_LEN_TIMEVAL - 11, '-') << std::endl;

	SDTIF_STAT_TVAL_Init(&stat_data);
	SDTIF_STAT_TVAL_StartTime(&stat_data);
	for (count_1 = 0; count_1 < speed_test_count; count_1++)
		base_coll.insert(count_1);
	SDTIF_STAT_TVAL_EndTime(&stat_data, speed_test_count);
	std::cout << std::left << std::setw(30) <<
		"multiset::insert()" << " " <<
		std::right << std::setw(10) << speed_test_count << " " <<
		(SDTIF_STAT_TVAL_FmtTotalInterval(&stat_data, buffer_1) + 11) << " " <<
		(SDTIF_STAT_TVAL_FmtTotalAverage(&stat_data, buffer_2) + 11) << std::endl;

	SDTIF_STAT_TVAL_Init(&stat_data);
	SDTIF_STAT_TVAL_StartTime(&stat_data);
	for (count_1 = 0; count_1 < speed_test_count; count_1++)
		this_coll_1.Insert(count_1);
	SDTIF_STAT_TVAL_EndTime(&stat_data, speed_test_count);
	std::cout << std::left << std::setw(30) <<
		"multiset_LC::Insert() (NullO)" << " " <<
		std::right << std::setw(10) << speed_test_count << " " <<
		(SDTIF_STAT_TVAL_FmtTotalInterval(&stat_data, buffer_1) + 11) << " " <<
		(SDTIF_STAT_TVAL_FmtTotalAverage(&stat_data, buffer_2) + 11) << std::endl;

	SDTIF_STAT_TVAL_Init(&stat_data);
	SDTIF_STAT_TVAL_StartTime(&stat_data);
	for (count_1 = 0; count_1 < speed_test_count; count_1++)
		this_coll_2.Insert(count_1);
	SDTIF_STAT_TVAL_EndTime(&stat_data, speed_test_count);
	std::cout << std::left << std::setw(30) <<
		"multiset_LC::Insert() (MtrO)" << " " <<
		std::right << std::setw(10) << speed_test_count << " " <<
		(SDTIF_STAT_TVAL_FmtTotalInterval(&stat_data, buffer_1) + 11) << " " <<
		(SDTIF_STAT_TVAL_FmtTotalAverage(&stat_data, buffer_2) + 11) << std::endl;

	std::cout << std::string(30, '-') << " " << std::string(10, '-') << " " <<
		std::string(SDTIF_FMTI_TIME_LEN_TIMEVAL - 11, '-') << " " <<
		std::string(SDTIF_FMTI_TIME_LEN_TIMEVAL - 11, '-') << std::endl;

	SDTIF_STAT_TVAL_Init(&stat_data);
	SDTIF_STAT_TVAL_StartTime(&stat_data);
	for (count_1 = 0; count_1 < speed_test_count; count_1++)
		base_coll.erase(count_1);
	SDTIF_STAT_TVAL_EndTime(&stat_data, speed_test_count);
	std::cout << std::left << std::setw(30) <<
		"multiset::erase()" << " " <<
		std::right << std::setw(10) << speed_test_count << " " <<
		(SDTIF_STAT_TVAL_FmtTotalInterval(&stat_data, buffer_1) + 11) << " " <<
		(SDTIF_STAT_TVAL_FmtTotalAverage(&stat_data, buffer_2) + 11) << std::endl;
	base_coll.clear();

	SDTIF_STAT_TVAL_Init(&stat_data);
	SDTIF_STAT_TVAL_StartTime(&stat_data);
	for (count_1 = 0; count_1 < speed_test_count; count_1++)
		this_coll_1.Erase(count_1);
	SDTIF_STAT_TVAL_EndTime(&stat_data, speed_test_count);
	std::cout << std::left << std::setw(30) <<
		"multiset_LC::Erase() (NullO)" << " " <<
		std::right << std::setw(10) << speed_test_count << " " <<
		(SDTIF_STAT_TVAL_FmtTotalInterval(&stat_data, buffer_1) + 11) << " " <<
		(SDTIF_STAT_TVAL_FmtTotalAverage(&stat_data, buffer_2) + 11) << std::endl;
	this_coll_1.Clear();

	SDTIF_STAT_TVAL_Init(&stat_data);
	SDTIF_STAT_TVAL_StartTime(&stat_data);
	for (count_1 = 0; count_1 < speed_test_count; count_1++)
		this_coll_2.Erase(count_1);
	SDTIF_STAT_TVAL_EndTime(&stat_data, speed_test_count);
	std::cout << std::left << std::setw(30) <<
		"multiset_LC::Erase() (MtrO)" << " " <<
		std::right << std::setw(10) << speed_test_count << " " <<
		(SDTIF_STAT_TVAL_FmtTotalInterval(&stat_data, buffer_1) + 11) << " " <<
		(SDTIF_STAT_TVAL_FmtTotalAverage(&stat_data, buffer_2) + 11) << std::endl;
	this_coll_2.Clear();

	TEST_SUPP_EmitBarEqual();
	TEST_SUPP_EmitBarEqual();
}
/*	***********************************************************************	*/

//	////////////////////////////////////////////////////////////////////////////
static bool TEST_ScopedLocks(const char *func_name, unsigned int element_count)
{
	bool         ok_flag     = true;
	bool         reader_test = true;
	ThisCollType this_coll(TEST_SUPP_CreateThis(0, element_count));

	try {
		{
			ThisCollType::MyLockReader reader_lock(this_coll);
			TEST_SUPP_EmitResults(func_name,
				"multiset_LC::MyLockReader()", ok_flag,
				true,
				"CATCH BLOCK NOT EXITED");
		}
		reader_test = false;
		{
			ThisCollType::MyLockWriter reader_lock(this_coll);
			TEST_SUPP_EmitResults(func_name,
				"multiset_LC::MyLockWriter()", ok_flag,
				true,
				"CATCH BLOCK NOT ENTERED");
		}
	}
	catch (std::exception &except) {
		std::ostringstream error_string;
		error_string << "CATCH BLOCK ENTERED: " << except.what();
		TEST_SUPP_EmitResults(func_name,
			((reader_test) ? "multiset_LC::MyLockReader()" : "multiset_LC::MyLockWriter()"),
			ok_flag, false, error_string.str().c_str());
		ok_flag = false;
	}

	return(ok_flag);
}
//	////////////////////////////////////////////////////////////////////////////

/*	***********************************************************************	*/
static bool TEST_Cons_1_A(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll;
	BaseCollType base_coll;

	if ((ok_flag = TEST_SUPP_EmitResults(func_name, "multiset_LC::multiset_LC()",
		ok_flag,
		(this_coll == base_coll),
		"(this_coll == base_coll)")) == true) {
		TEST_SUPP_FillCollThis(0, element_count, this_coll);
		TEST_SUPP_FillCollBase(0, element_count, base_coll);
		ok_flag = TEST_SUPP_EmitResults(func_name,
			"multiset_LC::multiset_LC() --- with data", ok_flag,
			(this_coll == base_coll),
			"(this_coll.GetDataRef() == base_coll)");
	}

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_Cons_InputIterator(const char *func_name,
	unsigned int element_count)
{
	bool         ok_flag = true;
	BaseCollType base_coll(TEST_SUPP_CreateBase(0, element_count));
	ThisCollType this_coll(base_coll.begin(), base_coll.end());

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"multiset_LC::multiset_LC(multiset<>::begin(), multiset<>::end())", ok_flag,
		(this_coll == base_coll),
		"(this_coll == base_coll)");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_Cons_BaseCollType(const char *func_name,
	unsigned int element_count)
{
	bool         ok_flag = true;
	BaseCollType base_coll(TEST_SUPP_CreateBase(0, element_count));
	ThisCollType this_coll(base_coll);

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"multiset_LC::multiset_LC(const multiset<> &)", ok_flag,
		(this_coll == base_coll),
		"(this_coll == base_coll)");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_ConsCopy(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll;

	TEST_SUPP_FillCollThis(0, element_count, this_coll);

	ThisCollType copy_coll(this_coll);

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"multiset_LC::multiset_LC(const multiset_LC<> &)", ok_flag,
		(this_coll == copy_coll),
		"(this_coll == copy_coll)");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_ConsAssign(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll;

	TEST_SUPP_FillCollThis(0, element_count, this_coll);

//	ThisCollType copy_coll = this_coll;
	ThisCollType copy_coll;

	copy_coll = this_coll;

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"multiset_LC::multiset_LC(const multiset_LC<> &)", ok_flag,
		(this_coll == copy_coll),
		"(this_coll == copy_coll)");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_Begin(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll;

	TEST_SUPP_FillCollThis(0, element_count, this_coll);

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"multiset_LC::Begin()",
		ok_flag,
		(*this_coll.Begin() == 0),
		"(*this_coll.Begin() == *expected-value*)");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_Clear(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll;

	TEST_SUPP_FillCollThis(0, element_count, this_coll);

	this_coll.Clear();

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"multiset_LC::Clear()",
		ok_flag,
		(this_coll.Size() == 0),
		"(this_coll.Size() == 0)");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_Empty(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll;

	TEST_SUPP_FillCollThis(0, element_count, this_coll);

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"multiset_LC::Empty() --- before multiset_LC::Clear()",
		ok_flag,
		(this_coll.Empty() == false),
		"(this_coll.Empty() == false)");

	this_coll.Clear();

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"multiset_LC::Empty() --- after multiset_LC::Clear()",
		ok_flag,
		(this_coll.Empty() == true),
		"(this_coll.Empty() == true)");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_End(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll;

	TEST_SUPP_FillCollThis(0, element_count, this_coll);

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"multiset_LC::End()",
		ok_flag,
		(this_coll.End() == this_coll.GetDataRef().end()),
		"(this_coll.End() == this_coll.GetDataRef().end())");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_Erase_1(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	unsigned int count_1;
	ThisCollType this_coll;
	BaseCollType base_coll;
	Iter         this_iter;
	Iter         base_iter;

	element_count = (element_count >= 3) ? element_count : 3;

	TEST_SUPP_FillCollThis(0, element_count, this_coll);
	TEST_SUPP_FillCollBase(0, element_count, base_coll);

	this_iter = this_coll.Begin();
	base_iter = base_coll.begin();

	for (count_1 = 0; count_1 < (element_count / 2); count_1++) {
		this_iter++;
		base_iter++;
	}

	this_coll.Erase(this_iter);
	base_coll.erase(base_iter);

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"multiset_LC::Erase(Iter *middle-of-container*)",
		ok_flag,
		(this_coll == base_coll),
		"(this_coll == base_coll)");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_Erase_2(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll;
	BaseCollType base_coll;

	TEST_SUPP_FillCollThis(0, element_count, this_coll);
	TEST_SUPP_FillCollBase(0, element_count, base_coll);

	this_coll.Erase(this_coll.Begin(), this_coll.End());
	base_coll.erase(base_coll.begin(), base_coll.end());

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"multiset_LC::Erase(multiset_LC::Begin(), multiset_LC::End())",
		ok_flag,
		(this_coll == base_coll),
		"(this_coll == base_coll)");

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"multiset_LC::Erase(multiset_LC::Begin(), multiset_LC::End())",
		ok_flag,
		(this_coll.Empty() == true),
		"(this_coll.Empty() == true)");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_Insert_1(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll;
	BaseCollType base_coll;

	TEST_SUPP_FillCollThis(0, element_count, this_coll);
	TEST_SUPP_FillCollBase(0, element_count, base_coll);

	this_coll.Insert(this_coll.Begin(), -1);
	base_coll.insert(base_coll.begin(), -1);

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"multiset_LC::Insert(Iter position = multiset_LC::Begin(), -1)",
		ok_flag,
		(this_coll == base_coll),
		"(multiset_LC<> == multiset<>)");

	this_coll.Insert(this_coll.End(), -2);
	base_coll.insert(base_coll.end(), -2);

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"multiset_LC::Insert(Iter position = multiset_LC::End(), -2)",
		ok_flag,
		(this_coll == base_coll),
		"(multiset_LC<> == multiset<>)");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_Insert_2(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll;
	BaseCollType base_coll;

	TEST_SUPP_FillCollThis(0, element_count, this_coll);
	TEST_SUPP_FillCollBase(0, element_count, base_coll);

	this_coll.Insert(this_coll.Begin(), -1);
	base_coll.insert(base_coll.begin(), -1);

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"multiset_LC::Insert(Iter position = multiset_LC::Begin(), element_count, -1)",
		ok_flag,
		(this_coll == base_coll),
		"(multiset_LC<> == multiset<>)");

	this_coll.Insert(this_coll.End(), -2);
	base_coll.insert(base_coll.end(), -2);

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"multiset_LC::Insert(Iter position = multiset_LC::End(), element_count, -2)",
		ok_flag,
		(this_coll == base_coll),
		"(multiset_LC<> == multiset<>)");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_Insert_3(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll;
	BaseCollType base_coll;
	BaseCollType src_coll_1;
	BaseCollType src_coll_2;

	TEST_SUPP_FillCollThis(0, element_count, this_coll);
	TEST_SUPP_FillCollBase(0, element_count, base_coll);

	TEST_SUPP_FillCollBase(element_count + 1, element_count, src_coll_1);
	TEST_SUPP_FillCollBase(element_count * 2 + 1, element_count, src_coll_2);

	this_coll.Insert(src_coll_1.begin(), src_coll_1.end());
//	MSC version 6.0 doesn't support this multiset::insert() correctly.
#ifdef _MSC_VER
# if _MSC_VER >= 1300
			base_coll.insert(src_coll_1.begin(), src_coll_1.end());
# else
			std::copy(src_coll_1.begin(), src_coll_1.end(),
				std::inserter(base_coll, base_coll.begin()));
# endif // # if _MSC_VER >= 1300
#else
			base_coll.insert(src_coll_1.begin(), src_coll_1.end());
#endif // #ifdef _MSC_VER
 
	ok_flag = TEST_SUPP_EmitResults(func_name,
		"multiset_LC::Insert(Iter position = multiset_LC::Begin(), \
multiset<>::begin(), multiset<>::end())",
		ok_flag,
		(this_coll == base_coll),
		"(multiset_LC<> == multiset<>)");

	this_coll.Insert(src_coll_2.begin(), src_coll_2.end());
//	MSC version 6.0 doesn't support this multiset::insert() correctly.
#ifdef _MSC_VER
# if _MSC_VER >= 1300
			base_coll.insert(src_coll_2.begin(), src_coll_2.end());
# else
			std::copy(src_coll_2.begin(), src_coll_2.end(),
				std::inserter(base_coll, base_coll.begin()));
# endif // # if _MSC_VER >= 1300
#else
			base_coll.insert(src_coll_2.begin(), src_coll_2.end());
#endif // #ifdef _MSC_VER
 
	ok_flag = TEST_SUPP_EmitResults(func_name,
		"multiset_LC::Insert(Iter position = multiset_LC::End(), \
multiset<>::begin(), multiset<>::end())",
		ok_flag,
		(this_coll == base_coll),
		"(multiset_LC<> == multiset<>)");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_Max_Size(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll(TEST_SUPP_CreateThis(0, element_count));
	BaseCollType base_coll(TEST_SUPP_CreateBase(0, element_count));

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"multiset_LC::Max_Size()",
		ok_flag,
		(this_coll.Max_Size() == base_coll.max_size()),
		"(this_coll.Max_Size() == base_coll.max_size())");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_Rbegin(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll;

	TEST_SUPP_FillCollThis(0, element_count, this_coll);

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"multiset_LC::Rbegin()",
		ok_flag,
		(*this_coll.Rbegin() == ((int) (element_count - 1))),
		"(*this_coll.RBegin() == *expected-value*)");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_Rend(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll;

	TEST_SUPP_FillCollThis(0, element_count, this_coll);

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"multiset_LC::Rend()",
		ok_flag,
		(this_coll.Rend() == this_coll.GetDataRef().rend()),
		"(this_coll.Rend() == this_coll.GetDataRef().rend())");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_Swap(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
/*
	ThisCollType this_coll_1(element_count, 123);
	ThisCollType this_coll_2(element_count, 456);
	ThisCollType this_coll_3(element_count, 789);
	BaseCollType base_coll_1(element_count, 123);
	BaseCollType base_coll_2(element_count, 456);
	BaseCollType base_coll_3(element_count, 789);
*/

	ThisCollType this_coll_1(TEST_SUPP_CreateThis(123, element_count));
	ThisCollType this_coll_2(TEST_SUPP_CreateThis(456, element_count));
	ThisCollType this_coll_3(TEST_SUPP_CreateThis(789, element_count));
	BaseCollType base_coll_1(TEST_SUPP_CreateBase(123, element_count));
	BaseCollType base_coll_2(TEST_SUPP_CreateBase(456, element_count));
	BaseCollType base_coll_3(TEST_SUPP_CreateBase(789, element_count));




	this_coll_1.Swap(this_coll_2);
	base_coll_1.swap(base_coll_2);
	ok_flag = TEST_SUPP_EmitResults(func_name,
		"multiset_LC::Swap(multiset_LC<>)",
		ok_flag,
		(this_coll_1 == base_coll_1) && (this_coll_2 == base_coll_2),
		"(this_coll_1 == base_coll_1) && (this_coll_2 == base_coll_2)");

	base_coll_1 = base_coll_3;
	this_coll_1.Swap(base_coll_3);
	ok_flag = TEST_SUPP_EmitResults(func_name,
		"multiset_LC::Swap(multiset<>)",
		ok_flag,
		(this_coll_1 == base_coll_1),
		"(this_coll_1 == base_coll_1)");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_Op_Eq(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll_1(TEST_SUPP_CreateThis(12345, element_count));
	ThisCollType this_coll_2(TEST_SUPP_CreateThis(12345, element_count));
	ThisCollType this_coll_3(TEST_SUPP_CreateThis(54321, element_count));
	ThisCollType this_coll_4(TEST_SUPP_CreateThis(12345, element_count + 1));
	BaseCollType base_coll(TEST_SUPP_CreateBase(12345, element_count));

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"multiset_LC<element_count, 12345> == multiset_LC<element_count, 12345>",
		ok_flag,
		(this_coll_1 == this_coll_2),
		"(multiset_LC<> == multiset_LC<>)");

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"!(multiset_LC<element_count, 12345> == multiset_LC<element_count, 54321>)",
		ok_flag,
		!(this_coll_1 == this_coll_3),
		"!(multiset_LC<> == multiset_LC<>)");

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"!(multiset_LC<element_count, 12345> == multiset_LC<element_count + 1, 12345>)",
		ok_flag,
		!(this_coll_1 == this_coll_4),
		"!(multiset_LC<> == multiset_LC<>)");

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"multiset_LC<element_count, 12345> == multiset<element_count, 12345>",
		ok_flag,
		(this_coll_1 == base_coll),
		"(multiset_LC<> == multiset<>)");

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"multiset<element_count, 12345> == multiset_LC<element_count, 12345>",
		ok_flag,
		(base_coll == this_coll_1),
		"(multiset<> == multiset_LC<>)");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_GetData_1(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll(TEST_SUPP_CreateThis(0, element_count));
	BaseCollType base_coll(TEST_SUPP_CreateBase(0, element_count));

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"multiset_LC<> multiset_LC::GetData()", ok_flag,
		(this_coll.GetData() == base_coll),
		"this_coll.GetData() == base_coll");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_GetData_2(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll(TEST_SUPP_CreateThis(0, element_count));
	BaseCollType base_coll(TEST_SUPP_CreateBase(0, element_count));
	BaseCollType tmp_base_coll;

	this_coll.GetData(tmp_base_coll);

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"void multiset_LC::GetData(multiset_LC<> &)", ok_flag,
		(tmp_base_coll == base_coll),
		"this_coll.GetData(tmp_base_coll) == base_coll");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_GetDataRef(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll(TEST_SUPP_CreateThis(0, element_count));
	BaseCollType base_coll(TEST_SUPP_CreateBase(0, element_count));

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"multiset_LC<> &multiset_LC::GetDataRef()", ok_flag,
		(this_coll.GetDataRef() == base_coll),
		"this_coll.GetDataRef() == base_coll");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_GetDataPtr(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll(TEST_SUPP_CreateThis(0, element_count));
	BaseCollType base_coll(TEST_SUPP_CreateBase(0, element_count));

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"multiset_LC<> *multiset_LC::GetDataPtr()", ok_flag,
		(*this_coll.GetDataPtr() == base_coll),
		"*this_coll.GetDataPtr() == base_coll)");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_GetLockRef(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll(TEST_SUPP_CreateThis(0, element_count));

	if ((ok_flag = TEST_SUPP_EmitResults(func_name,
		"LockType &multiset_LC::GetLockRef().LockReader()", ok_flag,
		(this_coll.GetLockRef().LockReader() == MTIF_SUCCESS),
		"this_coll.GetLockRef().LockReader() == MTIF_SUCCESS)")) == true)
		ok_flag = TEST_SUPP_EmitResults(func_name,
			"LockType &multiset_LC::GetLockRef().Unlock()", ok_flag,
			(this_coll.GetLockRef().Unlock() == MTIF_SUCCESS),
			"this_coll.GetLockRef().Unlock() == MTIF_SUCCESS)");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_GetLockPtr(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll(TEST_SUPP_CreateThis(0, element_count));

	if ((ok_flag = TEST_SUPP_EmitResults(func_name,
		"LockType *multiset_LC::GetLockPtr()->LockReader()", ok_flag,
		(this_coll.GetLockPtr()->LockReader() == MTIF_SUCCESS),
		"this_coll.GetLockPtr()->LockReader() == MTIF_SUCCESS)")) == true)
		ok_flag = TEST_SUPP_EmitResults(func_name,
			"LockType *multiset_LC::GetLockPtr()->Unlock()", ok_flag,
			(this_coll.GetLockPtr()->Unlock() == MTIF_SUCCESS),
			"this_coll.GetLockPtr()->Unlock() == MTIF_SUCCESS)");

	return(ok_flag);
}
/*	***********************************************************************	*/























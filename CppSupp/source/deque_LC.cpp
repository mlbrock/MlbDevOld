/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	STL Support Library Test Harness Module File										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Test harness module for template class deque_LC<>.

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

#include "deque_LC.h"

#include <MTIF_MtrO.h>

/*	***********************************************************************	*/

/*	***********************************************************************	*/
typedef std::deque<int>                                        BaseCollType;
typedef MLB::CPPSupp::STLSupp::deque_LC<int>                   NullCollType;
typedef MLB::CPPSupp::STLSupp::deque_LC<int, MLB::MTIF::MtrO>  ThisCollType;
typedef BaseCollType::iterator                                 Iter;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static int  TEST_SUPP_GetArgUInt(const char *arg_name, const char *in_arg_value,
   unsigned int *out_arg_value, std::string &error_text);
static void TEST_SUPP_GetFuncNameMax(void);
static void TEST_SUPP_FillCollThis(unsigned int index_start,
	unsigned int element_count, ThisCollType &in_coll);
static void TEST_SUPP_FillCollBase(unsigned int index_start,
	unsigned int element_count, BaseCollType &in_coll);
static void TEST_SUPP_EmitBarEqual(void);
static void TEST_SUPP_EmitBar(char in_char);
static bool TEST_SUPP_EmitResults(const char *func_name, const char *test_name,
	bool in_ok_flag, bool this_ok_flag, const char *failure_text);
static void TEST_SUPP_SpeedTest(unsigned int speed_test_count);
static bool TEST_ScopedLocks(const char *func_name, unsigned int element_count);
static bool TEST_PopBackWithGet(const char *func_name,
	unsigned int element_count);
static bool TEST_PopFrontWithGet(const char *func_name,
	unsigned int element_count);
static bool TEST_Cons_1_A(const char *func_name, unsigned int element_count);
static bool TEST_Cons_1_B(const char *func_name, unsigned int element_count);
static bool TEST_Cons_2_A(const char *func_name, unsigned int element_count);
static bool TEST_Cons_2_B(const char *func_name, unsigned int element_count);
static bool TEST_Cons_InputIterator(const char *func_name, unsigned int element_count);
static bool TEST_Cons_BaseCollType(const char *func_name, unsigned int element_count);
static bool TEST_ConsCopy(const char *func_name, unsigned int element_count);
static bool TEST_ConsAssign(const char *func_name, unsigned int element_count);
static bool TEST_Op_Eq(const char *func_name, unsigned int element_count);
static bool TEST_Assign_1(const char *func_name, unsigned int element_count);
static bool TEST_Assign_2(const char *func_name, unsigned int element_count);
static bool TEST_At(const char *func_name, unsigned int element_count);
static bool TEST_Back(const char *func_name, unsigned int element_count);
static bool TEST_Begin(const char *func_name, unsigned int element_count);
static bool TEST_Clear(const char *func_name, unsigned int element_count);
static bool TEST_Empty(const char *func_name, unsigned int element_count);
static bool TEST_End(const char *func_name, unsigned int element_count);
static bool TEST_Erase_1(const char *func_name, unsigned int element_count);
static bool TEST_Erase_2(const char *func_name, unsigned int element_count);
static bool TEST_Front(const char *func_name, unsigned int element_count);
static bool TEST_Insert_1(const char *func_name, unsigned int element_count);
static bool TEST_Insert_2(const char *func_name, unsigned int element_count);
static bool TEST_Insert_3(const char *func_name, unsigned int element_count);
static bool TEST_Max_Size(const char *func_name, unsigned int element_count);
static bool TEST_Pop_Back(const char *func_name, unsigned int element_count);
static bool TEST_Pop_Front(const char *func_name, unsigned int element_count);
static bool TEST_Push_Back(const char *func_name, unsigned int element_count);
static bool TEST_Push_Front(const char *func_name, unsigned int element_count);
static bool TEST_Rbegin(const char *func_name, unsigned int element_count);
static bool TEST_Rend(const char *func_name, unsigned int element_count);
static bool TEST_Resize(const char *func_name, unsigned int element_count);
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
	TEST_MAKE_FUNC_ENTRY(TEST_PopBackWithGet),
	TEST_MAKE_FUNC_ENTRY(TEST_PopFrontWithGet),
	TEST_MAKE_FUNC_ENTRY(TEST_Cons_1_A),
	TEST_MAKE_FUNC_ENTRY(TEST_Cons_1_B),
	TEST_MAKE_FUNC_ENTRY(TEST_Cons_2_A),
	TEST_MAKE_FUNC_ENTRY(TEST_Cons_2_B),
	TEST_MAKE_FUNC_ENTRY(TEST_Cons_InputIterator),
	TEST_MAKE_FUNC_ENTRY(TEST_Cons_BaseCollType),
	TEST_MAKE_FUNC_ENTRY(TEST_ConsCopy),
	TEST_MAKE_FUNC_ENTRY(TEST_ConsAssign),
	TEST_MAKE_FUNC_ENTRY(TEST_Assign_1),
	TEST_MAKE_FUNC_ENTRY(TEST_Assign_2),
	TEST_MAKE_FUNC_ENTRY(TEST_At),
	TEST_MAKE_FUNC_ENTRY(TEST_Back),
	TEST_MAKE_FUNC_ENTRY(TEST_Begin),
	TEST_MAKE_FUNC_ENTRY(TEST_Clear),
	TEST_MAKE_FUNC_ENTRY(TEST_Empty),
	TEST_MAKE_FUNC_ENTRY(TEST_End),
	TEST_MAKE_FUNC_ENTRY(TEST_Erase_1),
	TEST_MAKE_FUNC_ENTRY(TEST_Erase_2),
	TEST_MAKE_FUNC_ENTRY(TEST_Front),
	TEST_MAKE_FUNC_ENTRY(TEST_Insert_1),
	TEST_MAKE_FUNC_ENTRY(TEST_Insert_2),
	TEST_MAKE_FUNC_ENTRY(TEST_Insert_3),
	TEST_MAKE_FUNC_ENTRY(TEST_Max_Size),
	TEST_MAKE_FUNC_ENTRY(TEST_Pop_Back),
	TEST_MAKE_FUNC_ENTRY(TEST_Pop_Front),
	TEST_MAKE_FUNC_ENTRY(TEST_Push_Back),
	TEST_MAKE_FUNC_ENTRY(TEST_Push_Front),
	TEST_MAKE_FUNC_ENTRY(TEST_Rbegin),
	TEST_MAKE_FUNC_ENTRY(TEST_Rend),
	TEST_MAKE_FUNC_ENTRY(TEST_Resize),
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

	std::cerr << "Test harness for MLB::CPPSupp::STLSupp::deque_LC<>" <<
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
	std::cout << "Test harness for MLB::CPPSupp::STLSupp::deque_LC<>" <<
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
		in_coll.push_back(index_start++);
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
		base_coll.push_back(count_1);
	SDTIF_STAT_TVAL_EndTime(&stat_data, speed_test_count);
	std::cout << std::left << std::setw(30) <<
		"deque::push_back()" << " " <<
		std::right << std::setw(10) << speed_test_count << " " <<
		(SDTIF_STAT_TVAL_FmtTotalInterval(&stat_data, buffer_1) + 11) << " " <<
		(SDTIF_STAT_TVAL_FmtTotalAverage(&stat_data, buffer_2) + 11) << std::endl;
	base_coll.clear();

	SDTIF_STAT_TVAL_Init(&stat_data);
	SDTIF_STAT_TVAL_StartTime(&stat_data);
	for (count_1 = 0; count_1 < speed_test_count; count_1++)
		this_coll_1.Push_Back(count_1);
	SDTIF_STAT_TVAL_EndTime(&stat_data, speed_test_count);
	std::cout << std::left << std::setw(30) <<
		"deque_LC::Push_Back() (NullO)" << " " <<
		std::right << std::setw(10) << speed_test_count << " " <<
		(SDTIF_STAT_TVAL_FmtTotalInterval(&stat_data, buffer_1) + 11) << " " <<
		(SDTIF_STAT_TVAL_FmtTotalAverage(&stat_data, buffer_2) + 11) << std::endl;
	this_coll_1.Clear();

	SDTIF_STAT_TVAL_Init(&stat_data);
	SDTIF_STAT_TVAL_StartTime(&stat_data);
	for (count_1 = 0; count_1 < speed_test_count; count_1++)
		this_coll_2.Push_Back(count_1);
	SDTIF_STAT_TVAL_EndTime(&stat_data, speed_test_count);
	std::cout << std::left << std::setw(30) <<
		"deque_LC::Push_Back() (MtrO)" << " " <<
		std::right << std::setw(10) << speed_test_count << " " <<
		(SDTIF_STAT_TVAL_FmtTotalInterval(&stat_data, buffer_1) + 11) << " " <<
		(SDTIF_STAT_TVAL_FmtTotalAverage(&stat_data, buffer_2) + 11) << std::endl;
	this_coll_2.Clear();

	std::cout << std::string(30, '-') << " " << std::string(10, '-') << " " <<
		std::string(SDTIF_FMTI_TIME_LEN_TIMEVAL - 11, '-') << " " <<
		std::string(SDTIF_FMTI_TIME_LEN_TIMEVAL - 11, '-') << std::endl;

	SDTIF_STAT_TVAL_Init(&stat_data);
	SDTIF_STAT_TVAL_StartTime(&stat_data);
	for (count_1 = 0; count_1 < speed_test_count; count_1++)
		base_coll.push_front(count_1);
	SDTIF_STAT_TVAL_EndTime(&stat_data, speed_test_count);
	std::cout << std::left << std::setw(30) <<
		"deque::push_front()" << " " <<
		std::right << std::setw(10) << speed_test_count << " " <<
		(SDTIF_STAT_TVAL_FmtTotalInterval(&stat_data, buffer_1) + 11) << " " <<
		(SDTIF_STAT_TVAL_FmtTotalAverage(&stat_data, buffer_2) + 11) << std::endl;
	base_coll.clear();

	SDTIF_STAT_TVAL_Init(&stat_data);
	SDTIF_STAT_TVAL_StartTime(&stat_data);
	for (count_1 = 0; count_1 < speed_test_count; count_1++)
		this_coll_1.Push_Back(count_1);
	SDTIF_STAT_TVAL_EndTime(&stat_data, speed_test_count);
	std::cout << std::left << std::setw(30) <<
		"deque_LC::Push_Back() (NullO)" << " " <<
		std::right << std::setw(10) << speed_test_count << " " <<
		(SDTIF_STAT_TVAL_FmtTotalInterval(&stat_data, buffer_1) + 11) << " " <<
		(SDTIF_STAT_TVAL_FmtTotalAverage(&stat_data, buffer_2) + 11) << std::endl;
	this_coll_1.Clear();

	SDTIF_STAT_TVAL_Init(&stat_data);
	SDTIF_STAT_TVAL_StartTime(&stat_data);
	for (count_1 = 0; count_1 < speed_test_count; count_1++)
		this_coll_2.Push_Back(count_1);
	SDTIF_STAT_TVAL_EndTime(&stat_data, speed_test_count);
	std::cout << std::left << std::setw(30) <<
		"deque_LC::Push_Back() (MtrO)" << " " <<
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
	ThisCollType this_coll(element_count);

	try {
		{
			ThisCollType::MyLockReader reader_lock(this_coll);
			TEST_SUPP_EmitResults(func_name,
				"deque_LC::MyLockReader()", ok_flag,
				true,
				"CATCH BLOCK NOT EXITED");
		}
		reader_test = false;
		{
			ThisCollType::MyLockWriter reader_lock(this_coll);
			TEST_SUPP_EmitResults(func_name,
				"deque_LC::MyLockWriter()", ok_flag,
				true,
				"CATCH BLOCK NOT ENTERED");
		}
	}
	catch (std::exception &except) {
		std::ostringstream error_string;
		error_string << "CATCH BLOCK ENTERED: " << except.what();
		TEST_SUPP_EmitResults(func_name,
			((reader_test) ? "deque_LC::MyLockReader()" : "deque_LC::MyLockWriter()"),
			ok_flag, false, error_string.str().c_str());
		ok_flag = false;
	}

	return(ok_flag);
}
//	////////////////////////////////////////////////////////////////////////////

/*	***********************************************************************	*/
static bool TEST_PopBackWithGet(const char *func_name,
	unsigned int element_count)
{
	bool               ok_flag = true;
	ThisCollType       this_coll;
	int                count_1;
	int                datum;
	std::ostringstream failure_text;

	TEST_SUPP_FillCollThis(0, element_count, this_coll);

	for (count_1 = (element_count - 1); count_1 >= 0; count_1--) {
		if (!this_coll.PopBackWithGet(datum)) {
			failure_text << "(this_coll.PopBackWithGet(" << count_1 << ") == " <<
				"true" << ")";
			ok_flag = false;
			break;
		}
		if (datum != count_1) {
			failure_text << "this_coll.PopBackWithGet(" << count_1 <<
				") resulted in container value " << datum;
			ok_flag = false;
			break;
		}
	}

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"deque_LC::PopBackWithGet(*for-each-element*)",
		ok_flag,
		ok_flag,
		((ok_flag == true) ? "this_coll.PopBackWithGet(*ANY*)" :
		failure_text.str().c_str()));

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_PopFrontWithGet(const char *func_name,
	unsigned int element_count)
{
	bool               ok_flag = true;
	ThisCollType       this_coll;
	int                count_1;
	int                datum;
	std::ostringstream failure_text;

	TEST_SUPP_FillCollThis(0, element_count, this_coll);

	for (count_1 = 0; count_1 < ((int) element_count); count_1++) {
		if (!this_coll.PopFrontWithGet(datum)) {
			failure_text << "(this_coll.PopFrontWithGet(" << count_1 << ") == " <<
				"true" << ")";
			ok_flag = false;
			break;
		}
		if (datum != count_1) {
			failure_text << "this_coll.PopFrontWithGet(" << count_1 <<
				") resulted in container value " << datum;
			ok_flag = false;
			break;
		}
	}

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"deque_LC::PopFrontWithGet(*for-each-element*)",
		ok_flag,
		ok_flag,
		((ok_flag == true) ? "this_coll.PopFrontWithGet(*ANY*)" :
		failure_text.str().c_str()));

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_Cons_1_A(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll;
	BaseCollType base_coll;

	if ((ok_flag = TEST_SUPP_EmitResults(func_name, "deque_LC::deque_LC()",
		ok_flag,
		(this_coll == base_coll),
		"(this_coll == base_coll)")) == true) {
		TEST_SUPP_FillCollThis(0, element_count, this_coll);
		TEST_SUPP_FillCollBase(0, element_count, base_coll);
		ok_flag = TEST_SUPP_EmitResults(func_name,
			"deque_LC::deque_LC() --- with data", ok_flag,
			(this_coll == base_coll),
			"(this_coll.GetDataRef() == base_coll)");
	}

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_Cons_1_B(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll(ThisCollType().get_allocator());
//	An attempt to access the deque<> get_allocator() member using STL Port
//	version 0x460 under MSC version 6.0 doesn't work because deque<> is derived
//	using protected inheritance from _Deque_base<>. Hence this work-around.
#if defined(_STLPORT_VERSION) && (_STLPORT_VERSION <= 0x460)
	BaseCollType base_coll(this_coll.Get_Allocator());
#else
	BaseCollType base_coll(BaseCollType().get_allocator());
#endif // #if _STLPORT_VERSION <= 0x460

	if ((ok_flag = TEST_SUPP_EmitResults(func_name,
		"deque_LC::deque_LC(allocator<int>())", ok_flag,
		(this_coll == base_coll),
		"(this_coll == base_coll)")) == true) {
		TEST_SUPP_FillCollThis(0, element_count, this_coll);
		TEST_SUPP_FillCollBase(0, element_count, base_coll);
		ok_flag = TEST_SUPP_EmitResults(func_name,
			"deque_LC::deque_LC(allocator<int>()) --- with data", ok_flag,
			(this_coll == base_coll),
			"(this_coll == base_coll)");
	}

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_Cons_2_A(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll(element_count);
	BaseCollType base_coll(element_count);

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"deque_LC::deque_LC(element_count)", ok_flag,
		(this_coll == base_coll),
		"(this_coll == base_coll)");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_Cons_2_B(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll(element_count, 666);
	BaseCollType base_coll(element_count, 666);

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"deque_LC::deque_LC(element_count, 666)", ok_flag,
		(this_coll == base_coll),
		"(this_coll == base_coll)");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_Cons_InputIterator(const char *func_name,
	unsigned int element_count)
{
	bool         ok_flag = true;
	BaseCollType base_coll(element_count, 666);
	ThisCollType this_coll(base_coll.begin(), base_coll.end());

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"deque_LC::deque_LC(deque<>::begin(), deque<>::end())", ok_flag,
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
	BaseCollType base_coll(element_count, 666);
	ThisCollType this_coll(base_coll);

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"deque_LC::deque_LC(const deque<> &)", ok_flag,
		(this_coll == base_coll),
		"(this_coll == base_coll)");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_ConsCopy(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll(element_count, 12345);
	ThisCollType copy_coll(this_coll);

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"deque_LC::deque_LC(const deque_LC<> &)", ok_flag,
		(this_coll == copy_coll),
		"(this_coll == copy_coll)");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_ConsAssign(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll(element_count, 12345);
	ThisCollType copy_coll;

	copy_coll = this_coll;

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"deque_LC::deque_LC(const deque_LC<> &)", ok_flag,
		(this_coll == copy_coll),
		"(this_coll == copy_coll)");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_Assign_1(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	BaseCollType base_coll;
	ThisCollType this_coll_1;
	ThisCollType this_coll_2;

	TEST_SUPP_FillCollBase(0, element_count, base_coll);

	this_coll_1.Assign(base_coll.begin(), base_coll.end());
	ok_flag = TEST_SUPP_EmitResults(func_name,
		"deque_LC::Assign(deque<>::iterator first, deque<>::iterator last)",
		ok_flag,
		(this_coll_1 == base_coll),
		"(this_coll_1 == base_coll)");

	this_coll_2.Assign(this_coll_1.begin(), this_coll_1.end());
	ok_flag = TEST_SUPP_EmitResults(func_name,
"deque_LC::Assign(deque_LC<>::iterator first, deque<>_LC::iterator last)",
		ok_flag,
		(this_coll_1 == this_coll_2),
		"(this_coll_1 == this_coll_2)");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_Assign_2(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	BaseCollType base_coll(element_count, 123);
	ThisCollType this_coll_1;
	ThisCollType this_coll_2;

	this_coll_1.Assign(base_coll.size(), *base_coll.begin());
	ok_flag = TEST_SUPP_EmitResults(func_name,
		"deque_LC::Assign(deque<>::size_type count, deque<>::value_type data)",
		ok_flag,
		(this_coll_1 == base_coll),
		"(this_coll_1 == base_coll)");

	this_coll_2.Assign(this_coll_1.size(), *this_coll_1.begin());
	ok_flag = TEST_SUPP_EmitResults(func_name,
"deque_LC::Assign(deque_LC<>::size_type count, deque_LC<>::value_type data)",
		ok_flag,
		(this_coll_1 == this_coll_2),
		"(this_coll_1 == this_coll_2)");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_At(const char *func_name, unsigned int element_count)
{
	bool               ok_flag = true;
	ThisCollType       this_coll;
	int                count_1;
	std::ostringstream failure_text;

	TEST_SUPP_FillCollThis(0, element_count, this_coll);

	for (count_1 = 0; count_1 < ((int) element_count); count_1++) {
		if (this_coll.At(count_1) != count_1) {
			failure_text << "(this_coll.At(" << count_1 << ") == " <<
				count_1 << ")";
			ok_flag = false;
			break;
		}
	}

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"deque_LC::At(deque_LC<>::size_type in_index)",
		ok_flag,
		ok_flag,
		((ok_flag == true) ? "(this_coll.At(*ANY*) == *ANY*)" :
		failure_text.str().c_str()));

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_Back(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll;

	TEST_SUPP_FillCollThis(0, element_count, this_coll);

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"deque_LC::Back()",
		ok_flag,
		(this_coll.Back() == ((int) (element_count - 1))),
		"(this_coll.Back() == *expected-value*)");

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
		"deque_LC::Begin()",
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
	ThisCollType this_coll(element_count);

	this_coll.Clear();

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"deque_LC::Clear()",
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
	ThisCollType this_coll(element_count);

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"deque_LC::Empty() --- before deque_LC::Clear()",
		ok_flag,
		(this_coll.Empty() == false),
		"(this_coll.Empty() == false)");

	this_coll.Clear();

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"deque_LC::Empty() --- after deque_LC::Clear()",
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
		"deque_LC::End()",
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
		"deque_LC::Erase(Iter *middle-of-container*)",
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
		"deque_LC::Erase(deque_LC::Begin(), deque_LC::End())",
		ok_flag,
		(this_coll == base_coll),
		"(this_coll == base_coll)");

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"deque_LC::Erase(deque_LC::Begin(), deque_LC::End())",
		ok_flag,
		(this_coll.Empty() == true),
		"(this_coll.Empty() == true)");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_Front(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll;

	TEST_SUPP_FillCollThis(0, element_count, this_coll);

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"deque_LC::Front()",
		ok_flag,
		(this_coll.Front() == 0),
		"(this_coll.Front() == *expected-value*)");

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
		"deque_LC::Insert(Iter position = deque_LC::Begin(), -1)",
		ok_flag,
		(this_coll == base_coll),
		"(deque_LC<> == deque<>)");

	this_coll.Insert(this_coll.End(), -2);
	base_coll.insert(base_coll.end(), -2);

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"deque_LC::Insert(Iter position = deque_LC::End(), -2)",
		ok_flag,
		(this_coll == base_coll),
		"(deque_LC<> == deque<>)");

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

	this_coll.Insert(this_coll.Begin(), element_count, -1);
	base_coll.insert(base_coll.begin(), element_count, -1);

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"deque_LC::Insert(Iter position = deque_LC::Begin(), element_count, -1)",
		ok_flag,
		(this_coll == base_coll),
		"(deque_LC<> == deque<>)");

	this_coll.Insert(this_coll.End(), element_count, -2);
	base_coll.insert(base_coll.end(), element_count, -2);

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"deque_LC::Insert(Iter position = deque_LC::End(), element_count, -2)",
		ok_flag,
		(this_coll == base_coll),
		"(deque_LC<> == deque<>)");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_Insert_3(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll;
	BaseCollType base_coll;
	BaseCollType src_coll_1(element_count, -1);
	BaseCollType src_coll_2(element_count, -2);

	TEST_SUPP_FillCollThis(0, element_count, this_coll);
	TEST_SUPP_FillCollBase(0, element_count, base_coll);

	this_coll.Insert(this_coll.Begin(), src_coll_1.begin(), src_coll_1.end());
	base_coll.insert(base_coll.begin(), src_coll_1.begin(), src_coll_1.end());

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"deque_LC::Insert(Iter position = deque_LC::Begin(), \
deque<>::begin(), deque<>::end())",
		ok_flag,
		(this_coll == base_coll),
		"(deque_LC<> == deque<>)");

	this_coll.Insert(this_coll.End(), src_coll_2.begin(), src_coll_2.end());
	base_coll.insert(base_coll.end(), src_coll_2.begin(), src_coll_2.end());

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"deque_LC::Insert(Iter position = deque_LC::End(), \
deque<>::begin(), deque<>::end())",
		ok_flag,
		(this_coll == base_coll),
		"(deque_LC<> == deque<>)");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_Max_Size(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll(element_count);
	BaseCollType base_coll(element_count);

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"deque_LC::Max_Size()",
		ok_flag,
		(this_coll.Max_Size() == base_coll.max_size()),
		"(this_coll.Max_Size() == base_coll.max_size())");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_Pop_Back(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll;
	BaseCollType base_coll;

	TEST_SUPP_FillCollThis(0, element_count, this_coll);
	TEST_SUPP_FillCollBase(0, element_count, base_coll);

	this_coll.Pop_Back();
	base_coll.pop_back();

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"deque_LC::Pop_Back()",
		ok_flag,
		(this_coll == base_coll),
		"(deque_LC<> == deque<>)");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_Pop_Front(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll;
	BaseCollType base_coll;

	TEST_SUPP_FillCollThis(0, element_count, this_coll);
	TEST_SUPP_FillCollBase(0, element_count, base_coll);

	this_coll.Pop_Front();
	base_coll.pop_front();

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"deque_LC::Pop_Front()",
		ok_flag,
		(this_coll == base_coll),
		"(deque_LC<> == deque<>)");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_Push_Back(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll;
	BaseCollType base_coll;

	TEST_SUPP_FillCollThis(0, element_count, this_coll);
	TEST_SUPP_FillCollBase(0, element_count, base_coll);

	this_coll.Push_Back(-2);
	base_coll.push_back(-2);

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"deque_LC::Push_Back()",
		ok_flag,
		(this_coll == base_coll),
		"(deque_LC<> == deque<>)");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_Push_Front(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll;
	BaseCollType base_coll;

	TEST_SUPP_FillCollThis(0, element_count, this_coll);
	TEST_SUPP_FillCollBase(0, element_count, base_coll);

	this_coll.Push_Front(-2);
	base_coll.push_front(-2);

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"deque_LC::Push_Front()",
		ok_flag,
		(this_coll == base_coll),
		"(deque_LC<> == deque<>)");

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
		"deque_LC::Rbegin()",
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
		"deque_LC::Rend()",
		ok_flag,
		(this_coll.Rend() == this_coll.GetDataRef().rend()),
		"(this_coll.Rend() == this_coll.GetDataRef().rend())");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_Resize(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll;
	BaseCollType base_coll;

	element_count = (element_count >= 2) ? element_count : 2;

	this_coll.Assign(element_count, 123);
	base_coll.assign(element_count, 123);

	this_coll.Resize(this_coll.size() * 2, 456);
	base_coll.resize(base_coll.size() * 2, 456);

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"deque_LC::Size(deque_LC::size() * 2, 456)",
		ok_flag,
		(this_coll == base_coll),
		"(this_coll == base_coll)");

	this_coll.Resize(this_coll.size() / 4, 789);
	base_coll.resize(base_coll.size() / 4, 789);

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"deque_LC::Size(deque_LC::size() / 4, 789)",
		ok_flag,
		(this_coll == base_coll),
		"(this_coll == base_coll)");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_Swap(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll_1(element_count, 123);
	ThisCollType this_coll_2(element_count, 456);
	ThisCollType this_coll_3(element_count, 789);
	BaseCollType base_coll_1(element_count, 123);
	BaseCollType base_coll_2(element_count, 456);
	BaseCollType base_coll_3(element_count, 789);

	this_coll_1.Swap(this_coll_2);
	base_coll_1.swap(base_coll_2);
	ok_flag = TEST_SUPP_EmitResults(func_name,
		"deque_LC::Swap(deque_LC<>)",
		ok_flag,
		(this_coll_1 == base_coll_1) && (this_coll_2 == base_coll_2),
		"(this_coll_1 == base_coll_1) && (this_coll_2 == base_coll_2)");

	base_coll_1 = base_coll_3;
	this_coll_1.Swap(base_coll_3);
	ok_flag = TEST_SUPP_EmitResults(func_name,
		"deque_LC::Swap(deque<>)",
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
	ThisCollType this_coll_1(element_count, 12345);
	ThisCollType this_coll_2(element_count, 12345);
	ThisCollType this_coll_3(element_count, 54321);
	ThisCollType this_coll_4(element_count + 1, 12345);
	BaseCollType base_coll(element_count, 12345);

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"deque_LC<element_count, 12345> == deque_LC<element_count, 12345>",
		ok_flag,
		(this_coll_1 == this_coll_2),
		"(deque_LC<> == deque_LC<>)");

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"!(deque_LC<element_count, 12345> == deque_LC<element_count, 54321>)",
		ok_flag,
		!(this_coll_1 == this_coll_3),
		"!(deque_LC<> == deque_LC<>)");

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"!(deque_LC<element_count, 12345> == deque_LC<element_count + 1, 12345>)",
		ok_flag,
		!(this_coll_1 == this_coll_4),
		"!(deque_LC<> == deque_LC<>)");

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"deque_LC<element_count, 12345> == deque<element_count, 12345>",
		ok_flag,
		(this_coll_1 == base_coll),
		"(deque_LC<> == deque<>)");

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"deque<element_count, 12345> == deque_LC<element_count, 12345>",
		ok_flag,
		(base_coll == this_coll_1),
		"(deque<> == deque_LC<>)");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_GetData_1(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll(element_count);
	BaseCollType base_coll(element_count);

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"deque_LC<> deque_LC::GetData()", ok_flag,
		(this_coll.GetData() == base_coll),
		"this_coll.GetData() == base_coll");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_GetData_2(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll(element_count);
	BaseCollType base_coll(element_count);
	BaseCollType tmp_base_coll;

	this_coll.GetData(tmp_base_coll);

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"void deque_LC::GetData(deque_LC<> &)", ok_flag,
		(tmp_base_coll == base_coll),
		"this_coll.GetData(tmp_base_coll) == base_coll");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_GetDataRef(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll(element_count);
	BaseCollType base_coll(element_count);

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"deque_LC<> &deque_LC::GetDataRef()", ok_flag,
		(this_coll.GetDataRef() == base_coll),
		"this_coll.GetDataRef() == base_coll");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_GetDataPtr(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll(element_count);
	BaseCollType base_coll(element_count);

	ok_flag = TEST_SUPP_EmitResults(func_name,
		"deque_LC<> *deque_LC::GetDataPtr()", ok_flag,
		(*this_coll.GetDataPtr() == base_coll),
		"*this_coll.GetDataPtr() == base_coll)");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_GetLockRef(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll(element_count);

	if ((ok_flag = TEST_SUPP_EmitResults(func_name,
		"LockType &deque_LC::GetLockRef().LockReader()", ok_flag,
		(this_coll.GetLockRef().LockReader() == MTIF_SUCCESS),
		"this_coll.GetLockRef().LockReader() == MTIF_SUCCESS)")) == true)
		ok_flag = TEST_SUPP_EmitResults(func_name,
			"LockType &deque_LC::GetLockRef().Unlock()", ok_flag,
			(this_coll.GetLockRef().Unlock() == MTIF_SUCCESS),
			"this_coll.GetLockRef().Unlock() == MTIF_SUCCESS)");

	return(ok_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static bool TEST_GetLockPtr(const char *func_name, unsigned int element_count)
{
	bool         ok_flag = true;
	ThisCollType this_coll(element_count);

	if ((ok_flag = TEST_SUPP_EmitResults(func_name,
		"LockType *deque_LC::GetLockPtr()->LockReader()", ok_flag,
		(this_coll.GetLockPtr()->LockReader() == MTIF_SUCCESS),
		"this_coll.GetLockPtr()->LockReader() == MTIF_SUCCESS)")) == true)
		ok_flag = TEST_SUPP_EmitResults(func_name,
			"LockType *deque_LC::GetLockPtr()->Unlock()", ok_flag,
			(this_coll.GetLockPtr()->Unlock() == MTIF_SUCCESS),
			"this_coll.GetLockPtr()->Unlock() == MTIF_SUCCESS)");

	return(ok_flag);
}
/*	***********************************************************************	*/



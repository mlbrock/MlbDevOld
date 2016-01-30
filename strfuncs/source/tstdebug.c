/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Ensures compilation of macros.

	Revision History	:	2001-03-10 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2001 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/*	*********************************************************************** */
/*	*********************************************************************** */
/* 	Necessary include files . . .														*/
/*	*********************************************************************** */

#include <limits.h>
#include <memory.h>
#include <stdio.h>

#include "strfunci.h"

/*	*********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Function prototypes for functions private to this module . . .				*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(int STR_TEST_DoAlignMacros, (void));
/*	*********************************************************************** */

/*	*********************************************************************** */
#ifndef NARGS
int STR_TEST_DoMacros(void)
#else
int STR_TEST_DoMacros()
#endif /* #ifndef NARGS */
{
	return(STR_TEST_DoAlignMacros());
}
/*	*********************************************************************** */

/*	*********************************************************************** */
#ifndef NARGS
static int STR_TEST_DoAlignMacros(void)
#else
static int STR_TEST_DoAlignMacros()
#endif /* #ifndef NARGS */
{
	int             return_code  = STRFUNCS_SUCCESS;

	signed char     val_schar_1  = 1;
	unsigned char   val_uchar_1  = 2;
	signed short    val_sshort_1 = 4;
	unsigned short  val_ushort_1 = 5;
	signed int      val_sint_1   = 6;
	unsigned int    val_uint_1   = 7;
	signed long     val_slong_1  = 8L;
	unsigned long   val_ulong_1  = 9L;
	float           val_float_1  = ((float) 10.123);
	double          val_double_1 = 20.456;

	signed char     val_schar_2  = CHAR_MAX;
	unsigned char   val_uchar_2  = UCHAR_MAX;
	signed short    val_sshort_2 = SHRT_MAX;
	unsigned short  val_ushort_2 = USHRT_MAX;
	signed int      val_sint_2   = INT_MAX;
	unsigned int    val_uint_2   = UINT_MAX;
	signed long     val_slong_2  = LONG_MAX;
	unsigned long   val_ulong_2  = ULONG_MAX;
	float           val_float_2  = ((float) 1234567890.0987654321);
	double          val_double_2 = 9876543210.0123456789;

	void           *ptr_1;
	void           *ptr_2;

	char            tmp_schar[sizeof(signed char)     + 1];
	char            tmp_uchar[sizeof(unsigned char)   + 1];
	char            tmp_sshort[sizeof(signed short)   + 1];
	char            tmp_ushort[sizeof(unsigned short) + 1];
	char            tmp_sint[sizeof(signed int)       + 1];
	char            tmp_uint[sizeof(unsigned int)     + 1];
	char            tmp_slong[sizeof(signed long)     + 1];
	char            tmp_ulong[sizeof(unsigned long )  + 1];
	char            tmp_float[sizeof(float)           + 1];
	char            tmp_double[sizeof(double)         + 1];

	ptr_1 = STR_ALIGN_SET_SCHAR(&val_schar_1, tmp_schar + 1);
	if (memcmp(ptr_1,
		ptr_2 = STR_ALIGN_GET_SCHAR(tmp_schar + 1, &val_schar_2),
		sizeof(val_schar_1))) {
		fprintf(stderr, "PTR DIFF signed char    : %20p | %20p\n", ptr_1, ptr_2);
		return_code = STRFUNCS_FAILURE;
	}
	else if (val_schar_1 != val_schar_2) {
		fprintf(stderr, "ERROR ON signed char    : %20d | %20d\n",
			((signed int) val_schar_1), ((signed int) val_schar_2));
		return_code = STRFUNCS_FAILURE;
	}

	ptr_1 = STR_ALIGN_SET_UCHAR(&val_uchar_1, tmp_uchar + 1);
	if (memcmp(ptr_1,
		ptr_2 = STR_ALIGN_GET_UCHAR(tmp_uchar + 1, &val_uchar_2),
		sizeof(val_uchar_1))) {
		fprintf(stderr, "PTR DIFF unsigned char  : %20p | %20p\n", ptr_1, ptr_2);
		return_code = STRFUNCS_FAILURE;
	}
	else if (val_uchar_1 != val_uchar_2) {
		fprintf(stderr, "ERROR ON unsigned char  : %20u | %20u\n",
			((unsigned int) val_uchar_1), ((unsigned int) val_uchar_2));
		return_code = STRFUNCS_FAILURE;
	}

	ptr_1 = STR_ALIGN_SET_SSHORT(&val_sshort_1, tmp_sshort + 1);
	if (memcmp(ptr_1,
		ptr_2 = STR_ALIGN_GET_SSHORT(tmp_sshort + 1, &val_sshort_2),
		sizeof(val_sshort_1))) {
		fprintf(stderr, "PTR DIFF signed short   : %20p | %20p\n", ptr_1, ptr_2);
		return_code = STRFUNCS_FAILURE;
	}
	else if (val_sshort_1 != val_sshort_2) {
		fprintf(stderr, "ERROR ON signed short   : %20d | %20d\n",
			((signed int) val_sshort_1), ((signed int) val_sshort_2));
		return_code = STRFUNCS_FAILURE;
	}

	ptr_1 = STR_ALIGN_SET_USHORT(&val_ushort_1, tmp_ushort + 1);
	if (memcmp(ptr_1,
		ptr_2 = STR_ALIGN_GET_USHORT(tmp_ushort + 1, &val_ushort_2),
		sizeof(val_ushort_1))) {
		fprintf(stderr, "PTR DIFF unsigned short : %20p | %20p\n", ptr_1, ptr_2);
		return_code = STRFUNCS_FAILURE;
	}
	else if (val_ushort_1 != val_ushort_2) {
		fprintf(stderr, "ERROR ON unsigned short : %20u | %20u\n",
			((unsigned int) val_ushort_1), ((unsigned int) val_ushort_2));
		return_code = STRFUNCS_FAILURE;
	}

	ptr_1 = STR_ALIGN_SET_SINT(&val_sint_1, tmp_sint + 1);
	if (memcmp(ptr_1,
		ptr_2 = STR_ALIGN_GET_SINT(tmp_sint + 1, &val_sint_2),
		sizeof(val_sint_1))) {
		fprintf(stderr, "PTR DIFF signed int     : %20p | %20p\n", ptr_1, ptr_2);
		return_code = STRFUNCS_FAILURE;
	}
	else if (val_sint_1 != val_sint_2) {
		fprintf(stderr, "ERROR ON signed int     : %20d | %20d\n",
			val_sint_1, val_sint_2);
		return_code = STRFUNCS_FAILURE;
	}

	ptr_1 = STR_ALIGN_SET_UINT(&val_uint_1, tmp_uint + 1);
	if (memcmp(ptr_1,
		ptr_2 = STR_ALIGN_GET_UINT(tmp_uint + 1, &val_uint_2),
		sizeof(val_uint_1))) {
		fprintf(stderr, "PTR DIFF unsigned int   : %20p | %20p\n", ptr_1, ptr_2);
		return_code = STRFUNCS_FAILURE;
	}
	else if (val_uint_1 != val_uint_2) {
		fprintf(stderr, "ERROR ON unsigned int   : %20u | %20u\n",
			val_uint_1, val_uint_2);
		return_code = STRFUNCS_FAILURE;
	}

	ptr_1 = STR_ALIGN_SET_SLONG(&val_slong_1, tmp_slong + 1);
	if (memcmp(ptr_1,
		ptr_2 = STR_ALIGN_GET_SLONG(tmp_slong + 1, &val_slong_2),
		sizeof(val_slong_1))) {
		fprintf(stderr, "PTR DIFF signed long    : %20p | %20p\n", ptr_1, ptr_2);
		return_code = STRFUNCS_FAILURE;
	}
	else if (val_slong_1 != val_slong_2) {
		fprintf(stderr, "ERROR ON signed long    : %20ld | %20ld\n",
			val_slong_1, val_slong_2);
		return_code = STRFUNCS_FAILURE;
	}

	ptr_1 = STR_ALIGN_SET_ULONG(&val_ulong_1, tmp_ulong + 1);
	if (memcmp(ptr_1,
		ptr_2 = STR_ALIGN_GET_ULONG(tmp_ulong + 1, &val_ulong_2),
		sizeof(val_ulong_1))) {
		fprintf(stderr, "PTR DIFF unsigned long  : %20p | %20p\n", ptr_1, ptr_2);
		return_code = STRFUNCS_FAILURE;
	}
	else if (val_ulong_1 != val_ulong_2) {
		fprintf(stderr, "ERROR ON unsigned long  : %20lu | %20lu\n",
			val_ulong_1, val_ulong_2);
		return_code = STRFUNCS_FAILURE;
	}

	ptr_1 = STR_ALIGN_SET_FLOAT(&val_float_1, tmp_float + 1);
	if (memcmp(ptr_1,
		ptr_2 = STR_ALIGN_GET_FLOAT(tmp_float + 1, &val_float_2),
		sizeof(val_float_1))) {
		fprintf(stderr, "PTR DIFF float          : %20p | %20p\n", ptr_1, ptr_2);
		return_code = STRFUNCS_FAILURE;
	}
	else if (val_float_1 != val_float_2) {
		fprintf(stderr, "ERROR ON float          : %20.6f | %20.6f\n",
			((double) val_float_1), ((double) val_float_2));
		return_code = STRFUNCS_FAILURE;
	}

	ptr_1 = STR_ALIGN_SET_DOUBLE(&val_double_1, tmp_double + 1);
	if (memcmp(ptr_1,
		ptr_2 = STR_ALIGN_GET_DOUBLE(tmp_double + 1, &val_double_2),
		sizeof(val_double_1))) {
		fprintf(stderr, "PTR DIFF double         : %20p | %20p\n", ptr_1, ptr_2);
		return_code = STRFUNCS_FAILURE;
	}
	else if (val_double_1 != val_double_2) {
		fprintf(stderr, "ERROR ON double         : %20.6f | %20.6f\n",
			val_double_1, val_double_2);
		return_code = STRFUNCS_FAILURE;
	}

	return(return_code);
}
/*	*********************************************************************** */

#ifdef TEST_MAIN

COMPAT_FN_DECL(int main, (void));

int main()
{
	int return_code;

	fprintf(stderr, "Test harness for STRFUNCS macros\n");
	fprintf(stderr, "---- ------- --- -------- ------\n\n");

	return_code = STR_TEST_DoMacros();

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */


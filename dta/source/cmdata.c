/* *********************************************************************** */
/* *********************************************************************** */
/*	Data Type Alignment (DTA) Functions Library Source Module					*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	DTA comparison functions.

	Revision History	:	1992-02-23 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Include necessary header files . . .											*/
/* *********************************************************************** */

#include <string.h>

#include "dtai.h"

/* *********************************************************************** */

/*
	ADF NOTE: No ADF.
*/
/* *********************************************************************** */
#ifndef NARGS
int DTA_CompareList(DTA_CMP *align_cmp_ptr, const void *data_ptr_1,
	const void *data_ptr_2, size_t data_length)
#else
int DTA_CompareList(align_cmp_ptr, data_ptr_1, data_ptr_2, data_length)
DTA_CMP    *align_cmp_ptr;
const void *data_ptr_1;
const void *data_ptr_2;
size_t      data_length;
#endif /* #ifndef NARGS */
{
	int             cmp        = 0;
	unsigned int    type_count = 0;
	const DTA_TYPE *type_list  = NULL;
	unsigned int    count_1;

	type_count = align_cmp_ptr->type_count;
	type_list  = align_cmp_ptr->type_list;
	DTA_GetTypeInfo(&type_count, &type_list);

	for (count_1 = 0; count_1 < align_cmp_ptr->align_count; count_1++) {
		if ((align_cmp_ptr->align_list[count_1].type >= type_count) ||
			((cmp = (*type_list[align_cmp_ptr->align_list[count_1].type].
			compare_method)(align_cmp_ptr->align_list + count_1,
			((char *) data_ptr_1) + align_cmp_ptr->align_list[count_1].offset,
			((char *) data_ptr_2) + align_cmp_ptr->align_list[count_1].offset,
			data_length)) != 0))
			break;
	}

	return(cmp);
}
/* *********************************************************************** */

/*
	ADF NOTE: No ADF.
*/
#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/* *********************************************************************** */
#ifndef NARGS
int DTA_SCMP_ubyte(DTA *align_ptr, const unsigned char *ptr_1,
	const unsigned char *ptr_2, size_t data_length)
#else
int DTA_SCMP_ubyte(align_ptr, ptr_1, ptr_2, data_length)
DTA                 *align_ptr;
const unsigned char *ptr_1;
const unsigned char *ptr_2;
size_t               data_length;
#endif /* #ifndef NARGS */
{
	return(memcmp(ptr_1, ptr_2, align_ptr->array_length * sizeof(*ptr_1)));
}
/* *********************************************************************** */
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

/*
	ADF NOTE: No ADF.
*/
#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/* *********************************************************************** */
#ifndef NARGS
int DTA_SCMP_char(DTA *align_ptr, const char *ptr_1, const char *ptr_2,
	size_t data_length)
#else
int DTA_SCMP_char(align_ptr, ptr_1, ptr_2, data_length)
DTA        *align_ptr;
const char *ptr_1;
const char *ptr_2;
size_t      data_length;
#endif /* #ifndef NARGS */
{
	return(strncmp(ptr_1, ptr_2, align_ptr->array_length * sizeof(*ptr_1)));
}
/* *********************************************************************** */
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

/*
	ADF NOTE: No ADF.
*/
#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/* *********************************************************************** */
#ifndef NARGS
int DTA_SCMP_uchar(DTA *align_ptr, const unsigned char *ptr_1,
	const unsigned char *ptr_2, size_t data_length)
#else
int DTA_SCMP_uchar(align_ptr, ptr_1, ptr_2, data_length)
DTA                 *align_ptr;
const unsigned char *ptr_1;
const unsigned char *ptr_2;
size_t               data_length;
#endif /* #ifndef NARGS */
{
	return(strncmp(((const char *) ptr_1), ((const char *) ptr_2),
		align_ptr->array_length * sizeof(*ptr_1)));
}
/* *********************************************************************** */
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

/*
	ADF NOTE: No ADF.
*/
#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/* *********************************************************************** */
#ifndef NARGS
int DTA_SCMP_short(DTA *align_ptr, const short *ptr_1, const short *ptr_2,
	size_t data_length)
#else
int DTA_SCMP_short(align_ptr, ptr_1, ptr_2, data_length)
DTA         *align_ptr;
const short *ptr_1;
const short *ptr_2;
size_t       data_length;
#endif /* #ifndef NARGS */
{
	int          cmp = 0;
	unsigned int count_1;

	for (count_1 = 0; count_1 < align_ptr->array_length; count_1++) {
		if ((cmp =
			((int) ((*ptr_1 > *ptr_2) ? 1 : (*ptr_1 < *ptr_2) ? -1 : 0))) != 0)
			break;
	}

	return(cmp);
}
/* *********************************************************************** */
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

/*
	ADF NOTE: No ADF.
*/
#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/* *********************************************************************** */
#ifndef NARGS
int DTA_SCMP_ushort(DTA *align_ptr, const unsigned short *ptr_1,
	const unsigned short *ptr_2, size_t data_length)
#else
int DTA_SCMP_ushort(align_ptr, ptr_1, ptr_2, data_length)
DTA                  *align_ptr;
const unsigned short *ptr_1;
const unsigned short *ptr_2;
size_t                data_length;
#endif /* #ifndef NARGS */
{
	int          cmp = 0;
	unsigned int count_1;

	for (count_1 = 0; count_1 < align_ptr->array_length; count_1++) {
		if ((cmp =
			((int) ((*ptr_1 > *ptr_2) ? 1 : (*ptr_1 < *ptr_2) ? -1 : 0))) != 0)
			break;
	}

	return(cmp);
}
/* *********************************************************************** */
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

/*
	ADF NOTE: No ADF.
*/
#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/* *********************************************************************** */
#ifndef NARGS
int DTA_SCMP_int(DTA *align_ptr, const int *ptr_1, const int *ptr_2,
	size_t data_length)
#else
int DTA_SCMP_int(align_ptr, ptr_1, ptr_2, data_length)
DTA       *align_ptr;
const int *ptr_1;
const int *ptr_2;
size_t     data_length;
#endif /* #ifndef NARGS */
{
	int          cmp = 0;
	unsigned int count_1;

	for (count_1 = 0; count_1 < align_ptr->array_length; count_1++) {
		if ((cmp =
			((int) ((*ptr_1 > *ptr_2) ? 1 : (*ptr_1 < *ptr_2) ? -1 : 0))) != 0)
			break;
	}

	return(cmp);
}
/* *********************************************************************** */
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

/*
	ADF NOTE: No ADF.
*/
#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/* *********************************************************************** */
#ifndef NARGS
int DTA_SCMP_uint(DTA *align_ptr, const unsigned int *ptr_1,
	const unsigned int *ptr_2, size_t data_length)
#else
int DTA_SCMP_uint(align_ptr, ptr_1, ptr_2, data_length)
DTA                *align_ptr;
const unsigned int *ptr_1;
const unsigned int *ptr_2;
size_t              data_length;
#endif /* #ifndef NARGS */
{
	int          cmp = 0;
	unsigned int count_1;

	for (count_1 = 0; count_1 < align_ptr->array_length; count_1++) {
		if ((cmp =
			((int) ((*ptr_1 > *ptr_2) ? 1 : (*ptr_1 < *ptr_2) ? -1 : 0))) != 0)
			break;
	}

	return(cmp);
}
/* *********************************************************************** */
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

/*
	ADF NOTE: No ADF.
*/
#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/* *********************************************************************** */
#ifndef NARGS
int DTA_SCMP_long(DTA *align_ptr, const long *ptr_1, const long *ptr_2,
	size_t data_length)
#else
int DTA_SCMP_long(align_ptr, ptr_1, ptr_2, data_length)
DTA        *align_ptr;
const long *ptr_1;
const long *ptr_2;
size_t      data_length;
#endif /* #ifndef NARGS */
{
	int          cmp = 0;
	unsigned int count_1;

	for (count_1 = 0; count_1 < align_ptr->array_length; count_1++) {
		if ((cmp =
			((int) ((*ptr_1 > *ptr_2) ? 1 : (*ptr_1 < *ptr_2) ? -1 : 0))) != 0)
			break;
	}

	return(cmp);
}
/* *********************************************************************** */
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

/*
	ADF NOTE: No ADF.
*/
#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/* *********************************************************************** */
#ifndef NARGS
int DTA_SCMP_ulong(DTA *align_ptr, const unsigned long *ptr_1,
	const unsigned long *ptr_2, size_t data_length)
#else
int DTA_SCMP_ulong(align_ptr, ptr_1, ptr_2, data_length)
DTA                 *align_ptr;
const unsigned long *ptr_1;
const unsigned long *ptr_2;
size_t               data_length;
#endif /* #ifndef NARGS */
{
	int          cmp = 0;
	unsigned int count_1;

	for (count_1 = 0; count_1 < align_ptr->array_length; count_1++) {
		if ((cmp =
			((int) ((*ptr_1 > *ptr_2) ? 1 : (*ptr_1 < *ptr_2) ? -1 : 0))) != 0)
			break;
	}

	return(cmp);
}
/* *********************************************************************** */
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

/*
	ADF NOTE: No ADF.
*/
#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/* *********************************************************************** */
#ifndef NARGS
int DTA_SCMP_float(DTA *align_ptr, const float *ptr_1, const float *ptr_2,
	size_t data_length)
#else
int DTA_SCMP_float(align_ptr, ptr_1, ptr_2, data_length)
DTA         *align_ptr;
const float *ptr_1;
const float *ptr_2;
size_t       data_length;
#endif /* #ifndef NARGS */
{
	int          cmp = 0;
	unsigned int count_1;

	for (count_1 = 0; count_1 < align_ptr->array_length; count_1++) {
		if ((cmp =
			((int) ((*ptr_1 > *ptr_2) ? 1 : (*ptr_1 < *ptr_2) ? -1 : 0))) != 0)
			break;
	}

	return(cmp);
}
/* *********************************************************************** */
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

/*
	ADF NOTE: No ADF.
*/
#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/* *********************************************************************** */
#ifndef NARGS
int DTA_SCMP_double(DTA *align_ptr, const double *ptr_1, const double *ptr_2,
	size_t data_length)
#else
int DTA_SCMP_double(align_ptr, ptr_1, ptr_2, data_length)
DTA          *align_ptr;
const double *ptr_1;
const double *ptr_2;
size_t        data_length;
#endif /* #ifndef NARGS */
{
	int          cmp = 0;
	unsigned int count_1;

	for (count_1 = 0; count_1 < align_ptr->array_length; count_1++) {
		if ((cmp =
			((int) ((*ptr_1 > *ptr_2) ? 1 : (*ptr_1 < *ptr_2) ? -1 : 0))) != 0)
			break;
	}

	return(cmp);
}
/* *********************************************************************** */
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */


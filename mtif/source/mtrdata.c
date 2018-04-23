/* *********************************************************************** */
/* *********************************************************************** */
/*	Multi-Threading Interface Facility (MTIF) Library Source File				*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Manages recursive mutex data access.

	Revision History	:	2000-05-14 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2000 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/*	Necessary include files . . .															*/
/* *********************************************************************** */

#include <memory.h>

#include <sdtif.h>

#include "mtifi.h"

/* *********************************************************************** */

/*	***********************************************************************	*/
#ifndef NARGS
int MTIF_MTR_InitDataSInt(MTIF_MTR_DATA_SINT *data_ptr, MTIF_MTR_FLAG flags,
	const char *name, int new_value, char *error_text)
#else
int MTIF_MTR_InitDataSInt(data_ptr, flags, name, new_value, error_text)
MTIF_MTR_DATA_SINT *data_ptr;
MTIF_MTR_FLAG       flags;
const char         *name;
int                 new_value;
char               *error_text;
#endif /* #ifndef NARGS */
{
	return(MTIF_MTR_InitDataBasic(&data_ptr->lock_data, flags, name,
		&data_ptr->value, sizeof(data_ptr->value), &new_value, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MTIF_MTR_DestroyDataSInt(MTIF_MTR_DATA_SINT *data_ptr, char *error_text)
#else
int MTIF_MTR_DestroyDataSInt(data_ptr, error_text)
MTIF_MTR_DATA_SINT *data_ptr;
char               *error_text;
#endif /* #ifndef NARGS */
{
	return(MTIF_MTR_DestroyDataBasic(&data_ptr->lock_data, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MTIF_MTR_GetDataSInt(MTIF_MTR_DATA_SINT *data_ptr)
#else
int MTIF_MTR_GetDataSInt(data_ptr)
MTIF_MTR_DATA_SINT *data_ptr;
#endif /* #ifndef NARGS */
{
	int old_value;

	MTIF_MTR_GetDataSIntBasic(data_ptr, &old_value, NULL);

	return(old_value);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MTIF_MTR_GetDataSIntBasic(MTIF_MTR_DATA_SINT *data_ptr,
	int *old_value_ptr, char *error_text)
#else
int MTIF_MTR_GetDataSIntBasic(data_ptr, old_value_ptr, error_text)
MTIF_MTR_DATA_SINT *data_ptr;
int                *old_value_ptr;
char               *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (((return_code = MTIF_MTR_GetDataBasic(&data_ptr->lock_data,
		&data_ptr->value, sizeof(data_ptr->value), old_value_ptr, error_text)) !=
		MTIF_SUCCESS) && (old_value_ptr != NULL))
		*old_value_ptr = 0;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MTIF_MTR_SetDataSInt(MTIF_MTR_DATA_SINT *data_ptr, int new_value)
#else
int MTIF_MTR_SetDataSInt(data_ptr, new_value)
MTIF_MTR_DATA_SINT *data_ptr;
int                 new_value;
#endif /* #ifndef NARGS */
{
	int old_value;

	MTIF_MTR_SetDataSIntBasic(data_ptr, new_value, &old_value, NULL);

	return(old_value);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MTIF_MTR_SetDataSIntBasic(MTIF_MTR_DATA_SINT *data_ptr, int new_value,
	int *old_value_ptr, char *error_text)
#else
int MTIF_MTR_SetDataSIntBasic(data_ptr, new_value, old_value_ptr, error_text)
MTIF_MTR_DATA_SINT *data_ptr;
int                 new_value;
int                *old_value_ptr;
char               *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (((return_code = MTIF_MTR_SetDataBasic(&data_ptr->lock_data,
		&data_ptr->value, sizeof(data_ptr->value), &new_value, old_value_ptr,
		error_text)) != MTIF_SUCCESS) && (old_value_ptr != NULL))
		*old_value_ptr = 0;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MTIF_MTR_InitDataUInt(MTIF_MTR_DATA_UINT *data_ptr, MTIF_MTR_FLAG flags,
	const char *name, unsigned int new_value, char *error_text)
#else
int MTIF_MTR_InitDataUInt(data_ptr, flags, name, new_value, error_text)
MTIF_MTR_DATA_UINT *data_ptr;
MTIF_MTR_FLAG       flags;
const char         *name;
unsigned int        new_value;
char               *error_text;
#endif /* #ifndef NARGS */
{
	return(MTIF_MTR_InitDataBasic(&data_ptr->lock_data, flags, name,
		&data_ptr->value, sizeof(data_ptr->value), &new_value, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MTIF_MTR_DestroyDataUInt(MTIF_MTR_DATA_UINT *data_ptr, char *error_text)
#else
int MTIF_MTR_DestroyDataUInt(data_ptr, error_text)
MTIF_MTR_DATA_UINT *data_ptr;
char               *error_text;
#endif /* #ifndef NARGS */
{
	return(MTIF_MTR_DestroyDataBasic(&data_ptr->lock_data, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
unsigned int MTIF_MTR_GetDataUInt(MTIF_MTR_DATA_UINT *data_ptr)
#else
unsigned int MTIF_MTR_GetDataUInt(data_ptr)
MTIF_MTR_DATA_UINT *data_ptr;
#endif /* #ifndef NARGS */
{
	unsigned int old_value;

	MTIF_MTR_GetDataUIntBasic(data_ptr, &old_value, NULL);

	return(old_value);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MTIF_MTR_GetDataUIntBasic(MTIF_MTR_DATA_UINT *data_ptr,
	unsigned int *old_value_ptr, char *error_text)
#else
int MTIF_MTR_GetDataUIntBasic(data_ptr, old_value_ptr, error_text)
MTIF_MTR_DATA_UINT *data_ptr;
unsigned int       *old_value_ptr;
char               *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (((return_code = MTIF_MTR_GetDataBasic(&data_ptr->lock_data,
		&data_ptr->value, sizeof(data_ptr->value), old_value_ptr, error_text)) !=
		MTIF_SUCCESS) && (old_value_ptr != NULL))
		*old_value_ptr = 0;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
unsigned int MTIF_MTR_SetDataUInt(MTIF_MTR_DATA_UINT *data_ptr,
	unsigned int new_value)
#else
unsigned int MTIF_MTR_SetDataUInt(data_ptr, new_value)
MTIF_MTR_DATA_UINT *data_ptr;
unsigned int        new_value;
#endif /* #ifndef NARGS */
{
	unsigned int old_value;

	MTIF_MTR_SetDataUIntBasic(data_ptr, new_value, &old_value, NULL);

	return(old_value);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MTIF_MTR_SetDataUIntBasic(MTIF_MTR_DATA_UINT *data_ptr,
	unsigned int new_value, unsigned int *old_value_ptr, char *error_text)
#else
int MTIF_MTR_SetDataUIntBasic(data_ptr, new_value, old_value_ptr, error_text)
MTIF_MTR_DATA_UINT *data_ptr;
unsigned int        new_value;
unsigned int       *old_value_ptr;
char               *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (((return_code = MTIF_MTR_SetDataBasic(&data_ptr->lock_data,
		&data_ptr->value, sizeof(data_ptr->value), &new_value, old_value_ptr,
		error_text)) != MTIF_SUCCESS) && (old_value_ptr != NULL))
		*old_value_ptr = 0;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MTIF_MTR_InitDataSLong(MTIF_MTR_DATA_SLONG *data_ptr, MTIF_MTR_FLAG flags,
	const char *name, long new_value, char *error_text)
#else
int MTIF_MTR_InitDataSLong(data_ptr, flags, name, new_value, error_text)
MTIF_MTR_DATA_SLONG *data_ptr;
MTIF_MTR_FLAG        flags;
const char          *name;
long                 new_value;
char                *error_text;
#endif /* #ifndef NARGS */
{
	return(MTIF_MTR_InitDataBasic(&data_ptr->lock_data, flags, name,
		&data_ptr->value, sizeof(data_ptr->value), &new_value, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MTIF_MTR_DestroyDataSLong(MTIF_MTR_DATA_SLONG *data_ptr, char *error_text)
#else
int MTIF_MTR_DestroyDataSLong(data_ptr, error_text)
MTIF_MTR_DATA_SLONG *data_ptr;
char                *error_text;
#endif /* #ifndef NARGS */
{
	return(MTIF_MTR_DestroyDataBasic(&data_ptr->lock_data, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
long MTIF_MTR_GetDataSLong(MTIF_MTR_DATA_SLONG *data_ptr)
#else
long MTIF_MTR_GetDataSLong(data_ptr)
MTIF_MTR_DATA_SLONG *data_ptr;
#endif /* #ifndef NARGS */
{
	long old_value;

	MTIF_MTR_GetDataSLongBasic(data_ptr, &old_value, NULL);

	return(old_value);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MTIF_MTR_GetDataSLongBasic(MTIF_MTR_DATA_SLONG *data_ptr,
	long *old_value_ptr, char *error_text)
#else
int MTIF_MTR_GetDataSLongBasic(data_ptr, old_value_ptr, error_text)
MTIF_MTR_DATA_SLONG *data_ptr;
long                *old_value_ptr;
char                *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (((return_code = MTIF_MTR_GetDataBasic(&data_ptr->lock_data,
		&data_ptr->value, sizeof(data_ptr->value), old_value_ptr, error_text)) !=
		MTIF_SUCCESS) && (old_value_ptr != NULL))
		*old_value_ptr = 0;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
long MTIF_MTR_SetDataSLong(MTIF_MTR_DATA_SLONG *data_ptr, long new_value)
#else
long MTIF_MTR_SetDataSLong(data_ptr, new_value)
MTIF_MTR_DATA_SLONG *data_ptr;
long                 new_value;
#endif /* #ifndef NARGS */
{
	long old_value;

	MTIF_MTR_SetDataSLongBasic(data_ptr, new_value, &old_value, NULL);

	return(old_value);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MTIF_MTR_SetDataSLongBasic(MTIF_MTR_DATA_SLONG *data_ptr,
	long new_value, long *old_value_ptr, char *error_text)
#else
int MTIF_MTR_SetDataSLongBasic(data_ptr, new_value, old_value_ptr, error_text)
MTIF_MTR_DATA_SLONG *data_ptr;
long                 new_value;
long                *old_value_ptr;
char                *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (((return_code = MTIF_MTR_SetDataBasic(&data_ptr->lock_data,
		&data_ptr->value, sizeof(data_ptr->value), &new_value, old_value_ptr,
		error_text)) != MTIF_SUCCESS) && (old_value_ptr != NULL))
		*old_value_ptr = 0;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MTIF_MTR_InitDataULong(MTIF_MTR_DATA_ULONG *data_ptr, MTIF_MTR_FLAG flags,
	const char *name, unsigned long new_value, char *error_text)
#else
int MTIF_MTR_InitDataULong(data_ptr, flags, name, new_value, error_text)
MTIF_MTR_DATA_ULONG *data_ptr;
MTIF_MTR_FLAG        flags;
const char          *name;
unsigned long        new_value;
char                *error_text;
#endif /* #ifndef NARGS */
{
	return(MTIF_MTR_InitDataBasic(&data_ptr->lock_data, flags, name,
		&data_ptr->value, sizeof(data_ptr->value), &new_value, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MTIF_MTR_DestroyDataULong(MTIF_MTR_DATA_ULONG *data_ptr, char *error_text)
#else
int MTIF_MTR_DestroyDataULong(data_ptr, error_text)
MTIF_MTR_DATA_ULONG *data_ptr;
char                *error_text;
#endif /* #ifndef NARGS */
{
	return(MTIF_MTR_DestroyDataBasic(&data_ptr->lock_data, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
unsigned long MTIF_MTR_GetDataULong(MTIF_MTR_DATA_ULONG *data_ptr)
#else
unsigned long MTIF_MTR_GetDataULong(data_ptr)
MTIF_MTR_DATA_ULONG *data_ptr;
#endif /* #ifndef NARGS */
{
	unsigned long old_value;

	MTIF_MTR_GetDataULongBasic(data_ptr, &old_value, NULL);

	return(old_value);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MTIF_MTR_GetDataULongBasic(MTIF_MTR_DATA_ULONG *data_ptr,
	unsigned long *old_value_ptr, char *error_text)
#else
int MTIF_MTR_GetDataULongBasic(data_ptr, old_value_ptr, error_text)
MTIF_MTR_DATA_ULONG *data_ptr;
unsigned long       *old_value_ptr;
char                *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (((return_code = MTIF_MTR_GetDataBasic(&data_ptr->lock_data,
		&data_ptr->value, sizeof(data_ptr->value), old_value_ptr, error_text)) !=
		MTIF_SUCCESS) && (old_value_ptr != NULL))
		*old_value_ptr = 0;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
unsigned long MTIF_MTR_SetDataULong(MTIF_MTR_DATA_ULONG *data_ptr,
	unsigned long new_value)
#else
unsigned long MTIF_MTR_SetDataULong(data_ptr, new_value)
MTIF_MTR_DATA_ULONG *data_ptr;
unsigned long        new_value;
#endif /* #ifndef NARGS */
{
	unsigned long old_value;

	MTIF_MTR_SetDataULongBasic(data_ptr, new_value, &old_value, NULL);

	return(old_value);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MTIF_MTR_SetDataULongBasic(MTIF_MTR_DATA_ULONG *data_ptr,
	unsigned long new_value, unsigned long *old_value_ptr, char *error_text)
#else
int MTIF_MTR_SetDataULongBasic(data_ptr, new_value, old_value_ptr, error_text)
MTIF_MTR_DATA_ULONG *data_ptr;
unsigned long        new_value;
unsigned long       *old_value_ptr;
char                *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (((return_code = MTIF_MTR_SetDataBasic(&data_ptr->lock_data,
		&data_ptr->value, sizeof(data_ptr->value), &new_value, old_value_ptr,
		error_text)) != MTIF_SUCCESS) && (old_value_ptr != NULL))
		*old_value_ptr = 0;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MTIF_MTR_InitDataDouble(MTIF_MTR_DATA_DOUBLE *data_ptr, MTIF_MTR_FLAG flags,
	const char *name, double new_value, char *error_text)
#else
int MTIF_MTR_InitDataDouble(data_ptr, flags, name, new_value, error_text)
MTIF_MTR_DATA_DOUBLE *data_ptr;
MTIF_MTR_FLAG         flags;
const char           *name;
double                new_value;
char                 *error_text;
#endif /* #ifndef NARGS */
{
	return(MTIF_MTR_InitDataBasic(&data_ptr->lock_data, flags, name,
		&data_ptr->value, sizeof(data_ptr->value), &new_value, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MTIF_MTR_DestroyDataDouble(MTIF_MTR_DATA_DOUBLE *data_ptr, char *error_text)
#else
int MTIF_MTR_DestroyDataDouble(data_ptr, error_text)
MTIF_MTR_DATA_DOUBLE *data_ptr;
char                 *error_text;
#endif /* #ifndef NARGS */
{
	return(MTIF_MTR_DestroyDataBasic(&data_ptr->lock_data, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
double MTIF_MTR_GetDataDouble(MTIF_MTR_DATA_DOUBLE *data_ptr)
#else
double MTIF_MTR_GetDataDouble(data_ptr)
MTIF_MTR_DATA_DOUBLE *data_ptr;
#endif /* #ifndef NARGS */
{
	double old_value;

	MTIF_MTR_GetDataDoubleBasic(data_ptr, &old_value, NULL);

	return(old_value);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MTIF_MTR_GetDataDoubleBasic(MTIF_MTR_DATA_DOUBLE *data_ptr,
	double *old_value_ptr, char *error_text)
#else
int MTIF_MTR_GetDataDoubleBasic(data_ptr, old_value_ptr, error_text)
MTIF_MTR_DATA_DOUBLE *data_ptr;
double               *old_value_ptr;
char                 *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (((return_code = MTIF_MTR_GetDataBasic(&data_ptr->lock_data,
		&data_ptr->value, sizeof(data_ptr->value), old_value_ptr, error_text)) !=
		MTIF_SUCCESS) && (old_value_ptr != NULL))
		*old_value_ptr = 0;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
double MTIF_MTR_SetDataDouble(MTIF_MTR_DATA_DOUBLE *data_ptr, double new_value)
#else
double MTIF_MTR_SetDataDouble(data_ptr, new_value)
MTIF_MTR_DATA_DOUBLE *data_ptr;
double                new_value;
#endif /* #ifndef NARGS */
{
	double old_value;

	MTIF_MTR_SetDataDoubleBasic(data_ptr, new_value, &old_value, NULL);

	return(old_value);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MTIF_MTR_SetDataDoubleBasic(MTIF_MTR_DATA_DOUBLE *data_ptr,
	double new_value, double *old_value_ptr, char *error_text)
#else
int MTIF_MTR_SetDataDoubleBasic(data_ptr, new_value, old_value_ptr, error_text)
MTIF_MTR_DATA_DOUBLE *data_ptr;
double                new_value;
double               *old_value_ptr;
char                 *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (((return_code = MTIF_MTR_SetDataBasic(&data_ptr->lock_data,
		&data_ptr->value, sizeof(data_ptr->value), &new_value, old_value_ptr,
		error_text)) != MTIF_SUCCESS) && (old_value_ptr != NULL))
		*old_value_ptr = 0;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MTIF_MTR_InitDataBasic(MTIF_MTR_HANDLE *lock_ptr, MTIF_MTR_FLAG flags,
	const char *name, void *value_ptr, unsigned int value_length,
	const void *new_data_ptr, char *error_text)
#else
int MTIF_MTR_InitDataBasic(lock_ptr, flags, name, value_ptr, value_length,
	new_data_ptr, error_text)
MTIF_MTR_HANDLE *lock_ptr;
MTIF_MTR_FLAG    flags;
const char      *name;
void            *value_ptr;
unsigned int     value_length;
const void      *new_data_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = MTIF_MTR_Init(flags, name,  lock_ptr, error_text)) ==
		MTIF_SUCCESS)
		return_code = MTIF_MTR_SetDataBasic(lock_ptr, value_ptr, value_length,
			new_data_ptr, NULL, error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MTIF_MTR_DestroyDataBasic(MTIF_MTR_HANDLE *lock_ptr, char *error_text)
#else
int MTIF_MTR_DestroyDataBasic(lock_ptr, error_text)
MTIF_MTR_HANDLE *lock_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	return(MTIF_MTR_Destroy(lock_ptr, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MTIF_MTR_GetDataBasic(MTIF_MTR_HANDLE *lock_ptr, void *value_ptr,
	unsigned int value_length, void *old_value_ptr, char *error_text)
#else
int MTIF_MTR_GetDataBasic(lock_ptr, value_ptr, value_length, old_value_ptr,
	error_text)
MTIF_MTR_HANDLE *lock_ptr;
void            *value_ptr;
unsigned int     value_length;
void            *old_value_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = MTIF_MTR_Lock(lock_ptr, error_text)) == MTIF_SUCCESS) {
		if (old_value_ptr != NULL)
			memcpy(old_value_ptr, value_ptr, value_length);
		MTIF_MTR_Unlock(lock_ptr, NULL);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MTIF_MTR_SetDataBasic(MTIF_MTR_HANDLE *lock_ptr, void *value_ptr,
	unsigned int value_length, const void *new_value_ptr, void *old_value_ptr,
	char *error_text)
#else
int MTIF_MTR_SetDataBasic(lock_ptr, value_ptr, value_length, new_value_ptr,
	old_value_ptr, error_text)
MTIF_MTR_HANDLE *lock_ptr;
void            *value_ptr;
unsigned int     value_length;
const void      *new_value_ptr;
void            *old_value_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = MTIF_MTR_Lock(lock_ptr, error_text)) == MTIF_SUCCESS) {
		if (value_length) {
			if (old_value_ptr != NULL)
				memcpy(old_value_ptr, value_ptr, value_length);
			if (new_value_ptr != NULL)
				memcpy(value_ptr, new_value_ptr, value_length);
		}
		MTIF_MTR_Unlock(lock_ptr, NULL);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MTIF_MTR_SpinOnDataSIntUSecs(MTIF_MTR_DATA_SINT *data_ptr, int test_value,
	unsigned int spin_count, unsigned long spin_usecs)
#else
int MTIF_MTR_SpinOnDataSIntUSecs(data_ptr, test_value, spin_count, spin_usecs)
MTIF_MTR_DATA_SINT *data_ptr;
int                 test_value;
unsigned int        spin_count;
unsigned long       spin_usecs;
#endif /* #ifndef NARGS */
{
	int return_value = 0;

	MTIF_MTR_SpinOnDataUSecsBasic(&data_ptr->lock_data, &data_ptr->value,
		sizeof(data_ptr->value), &test_value, &return_value, spin_count,
		spin_usecs, MTIF_FALSE, NULL);

	return(return_value);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MTIF_MTR_SpinOnNotDataSIntUSecs(MTIF_MTR_DATA_SINT *data_ptr,
	int test_value, unsigned int spin_count, unsigned long spin_usecs)
#else
int MTIF_MTR_SpinOnNotDataSIntUSecs(data_ptr, test_value, spin_count,
	spin_usecs)
MTIF_MTR_DATA_SINT *data_ptr;
int                 test_value;
unsigned int        spin_count;
unsigned long       spin_usecs;
#endif /* #ifndef NARGS */
{
	int return_value = 0;

	MTIF_MTR_SpinOnDataUSecsBasic(&data_ptr->lock_data, &data_ptr->value,
		sizeof(data_ptr->value), &test_value, &return_value, spin_count,
		spin_usecs, MTIF_TRUE, NULL);

	return(return_value);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MTIF_MTR_SpinOnDataUSecsBasic(MTIF_MTR_HANDLE *lock_ptr,
	const void *value_ptr, unsigned int value_length, const void *test_value_ptr,
	void *old_value_ptr, unsigned int spin_count, unsigned long spin_usecs,
	int not_flag, char *error_text)
#else
int MTIF_MTR_SpinOnDataUSecsBasic(lock_ptr, value_ptr, value_length,
	test_value_ptr, old_value_ptr, spin_count, spin_usecs, not_flag, error_text)
MTIF_MTR_HANDLE *lock_ptr;
const void      *value_ptr;
unsigned int     value_length;
const void      *test_value_ptr;
void            *old_value_ptr;
unsigned int     spin_count;
unsigned long    spin_usecs;
int              not_flag;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;
	int cmp;

	do {
		if ((return_code = MTIF_MTR_TryLock(lock_ptr, error_text)) ==
			MTIF_SUCCESS) {
			memcpy(old_value_ptr, value_ptr, value_length);
			MTIF_MTR_Unlock(lock_ptr, NULL);
			cmp = memcmp(test_value_ptr, old_value_ptr, value_length);
			if (((!not_flag) && (!cmp)) || (not_flag && cmp))
				break;
		}
		else if (return_code != MTIF_LOCK_ACQ_FAILURE)
			break;
		if ((spin_count != MTIF_SPIN_ON_DATA_FOREVER) && (!--spin_count))
			break;
		if (spin_usecs)
			SDTIF_usleep(spin_usecs);
	} while ((spin_count != MTIF_SPIN_ON_DATA_FOREVER) && spin_count);

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <stdio.h>
#include <stdlib.h>

#include <strfuncs.h>
#include <sdtif.h>

#define TEST_ITERATION_COUNT				10
#define TEST_THREAD_COUNT					100

typedef struct {
	unsigned int        thread_index;
	int                 get_flag;
	unsigned long       sleep_usecs;
	MTIF_MTR_DATA_SINT *data_ptr;
} TEST_DATA;

COMPAT_FN_DECL(       int   main,
	(int argc, char **argv));
COMPAT_FN_DECL_STATIC(int   TEST_DoIterations,
	(unsigned int iteration_count, unsigned int thread_count,
	MTIF_THR_HANDLE *thread_list, TEST_DATA *data_list, MTIF_THR_FLAG flags,
	unsigned long sleep_modulus, MTIF_MTR_DATA_SINT *data_ptr,
	char *error_text));
COMPAT_FN_DECL_STATIC(void *TEST_StartFunc,
	(TEST_DATA *start_data));
COMPAT_FN_DECL_STATIC(void  TEST_ShowData,
	(const TEST_DATA *start_data));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int                 return_code     = MTIF_SUCCESS;
	unsigned int        iteration_count = TEST_ITERATION_COUNT;
	unsigned int        thread_count    = TEST_THREAD_COUNT;
	unsigned long       sleep_modulus   = 10L;
	MTIF_THR_HANDLE    *thread_list     = NULL;
	TEST_DATA          *data_list       = NULL;
	MTIF_THR_FLAG       flags           = MTIF_THR_FLAG_DEFAULT;
	MTIF_MTR_DATA_SINT  data_static     = MTIF_MTR_DATA_SINT_STATIC_INIT(54321);
	MTIF_MTR_DATA_SINT  data_dynamic;
	unsigned int        count_1;
	char                error_text[MTIF_MAX_ERROR_TEXT];

	fprintf(stderr, "Test harness routine for 'MTIF_MTR_InitSInt()'\n");
	fprintf(stderr, "                         'MTIF_MTR_GetSIntBasic()'\n");
	fprintf(stderr, "                         'MTIF_MTR_SetSIntBasic()'\n");
	fprintf(stderr, "                         'MTIF_MTR_DestroySInt()'\n");
	fprintf(stderr, "                         'MTIF_MTR_InitBasic()'\n");
	fprintf(stderr, "                         'MTIF_MTR_GetBasic()'\n");
	fprintf(stderr, "                         'MTIF_MTR_SetBasic()'\n");
	fprintf(stderr, "                         'MTIF_MTR_DestroyBasic()'\n");
	fprintf(stderr, "---- ------- ------- --- -------------------------\n\n");

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if ((!stricmp(argv[count_1], "-HELP")) ||
			(!stricmp(argv[count_1], "-H"))) {
			fprintf(stderr, "\n\nUSAGE:\n   %s [%s=%u [%s=%u]]\n\n",
				argv[0],
				"<iteration-count>", TEST_ITERATION_COUNT,
				"<thread-count>", TEST_THREAD_COUNT);
			goto EXIT_FUNCTION;
		}
	}

	if (argc > 1) {
		if (atoi(argv[1]) < 1) {
			sprintf(error_text, "%s ('%-.500s') --- %s.",
				"Invalid <iteration-count> command-line parameter", argv[1],
				"use '-HELP' to get usage");
			return_code = MTIF_BAD_ARGS_FAILURE;
			goto EXIT_FUNCTION;
		}
		iteration_count = atoi(argv[1]);
	}

	if (argc > 2) {
		if (atoi(argv[2]) < 1) {
			sprintf(error_text, "%s ('%-.500s') --- %s.",
				"Invalid <thread-count> command-line parameter", argv[2],
				"use '-HELP' to get usage");
			return_code = MTIF_BAD_ARGS_FAILURE;
			goto EXIT_FUNCTION;
		}
		thread_count = atoi(argv[2]);
	}

	sleep_modulus = (thread_count < 100) ? ((unsigned long) thread_count) :
		10L;

	printf("================ ==========\n");
	printf("Iteration Count: %10u\n",  iteration_count);
	printf("Thread Count   : %10u\n",  thread_count);
	printf("Sleep Modulus  : %10lu\n", sleep_modulus);
	printf("================ ==========\n\n");

	if ((thread_list = ((MTIF_THR_HANDLE *) calloc(thread_count,
		sizeof(MTIF_THR_HANDLE)))) == NULL) {
		STR_AllocMsgList(thread_count, sizeof(MTIF_THR_HANDLE), error_text,
			"Unable to allocate thread handle list");
		return_code = MTIF_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((data_list = ((TEST_DATA *) calloc(thread_count,
		sizeof(TEST_DATA)))) == NULL) {
		STR_AllocMsgList(thread_count, sizeof(TEST_DATA), error_text,
			"Unable to allocate the per-thread test data list");
		return_code = MTIF_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((return_code = MTIF_MTR_InitDataSInt(&data_dynamic,
		MTIF_MTR_FLAG_DEFAULT, NULL, 12345, error_text)) != MTIF_SUCCESS)
		goto EXIT_FUNCTION;

	/*	*****************************************************************
		*****************************************************************
		Dynamic process mutex tests . . .
		*****************************************************************	*/
	flags &= (~MTIF_THR_FLAG_DETACHED);
	if ((return_code = TEST_DoIterations(iteration_count, thread_count,
		thread_list, data_list, flags, sleep_modulus, &data_dynamic,
		error_text)) != MTIF_SUCCESS) {
		MTIF_MTR_DestroyDataSInt(&data_dynamic, NULL);
		goto EXIT_FUNCTION;
	}
	return_code = MTIF_MTR_DestroyDataSInt(&data_dynamic, error_text);
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Static process mutex tests . . .
		*****************************************************************	*/
	flags &= (~MTIF_THR_FLAG_DETACHED);
	if ((return_code = TEST_DoIterations(iteration_count, thread_count,
		thread_list, data_list, flags, sleep_modulus, &data_static,
		error_text)) != MTIF_SUCCESS)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

EXIT_FUNCTION:

	if (thread_list != NULL)
		free(thread_list);

	if (data_list != NULL)
		free(data_list);

	if (return_code != MTIF_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#ifndef NARGS
static int TEST_DoIterations(unsigned int iteration_count,
	unsigned int thread_count, MTIF_THR_HANDLE *thread_list,
	TEST_DATA *data_list, MTIF_THR_FLAG flags, unsigned long sleep_modulus,
	MTIF_MTR_DATA_SINT *data_ptr, char *error_text)
#else
static int TEST_DoIterations(iteration_count, thread_count, thread_list,
	data_list, flags, sleep_modulus, data_ptr, error_text)
unsigned int        iteration_count;
unsigned int        thread_count;
MTIF_THR_HANDLE    *thread_list;
TEST_DATA          *data_list;
MTIF_THR_FLAG       flags;
unsigned long       sleep_modulus;
MTIF_MTR_DATA_SINT *data_ptr;
char               *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = MTIF_SUCCESS;
	unsigned int count_1;
	unsigned int count_2;
	char         tmp_error_text[MTIF_MAX_ERROR_TEXT];

	flags &= (~MTIF_THR_FLAG_DETACHED);

	for (count_1 = 0; count_1 < iteration_count; count_1++) {
		fprintf(stderr, "Iteration %5u:\n", count_1 + 1);
		for (count_2 = 0; count_2 < thread_count; count_2++) {
			data_list[count_2].thread_index = count_2;
			data_list[count_2].get_flag     = rand() % thread_count;
			data_list[count_2].sleep_usecs  =
				((rand() % sleep_modulus) + 1L) * 1000000L;
			data_list[count_2].data_ptr     = data_ptr;
			if ((return_code = MTIF_THR_Create(flags, 0,
				((MTIF_THR_StartFunc) TEST_StartFunc), data_list + count_2,
				thread_list + count_2, tmp_error_text)) != MTIF_SUCCESS) {
				sprintf(error_text, "%s (index %u) failed: %s",
					"Attempt to create new thread", count_2, tmp_error_text);
fprintf(stderr, "********** Created only %u of %u threads: %s\n",
	count_2, thread_count, error_text);
thread_count = count_2;
break;
				goto EXIT_FUNCTION;
			}
		}
		for (count_2 = 0; count_2 < thread_count; count_2++) {
			if ((return_code = MTIF_THR_Join(thread_list + count_2,
				NULL, tmp_error_text)) != MTIF_SUCCESS) {
TEST_ShowData(data_list + count_2);
				sprintf(error_text, "%s %lu (index %u) failed: %s",
					"Attempt to join on thread id",
					((unsigned long) MTIF_THR_GET_OS_ID(thread_list + count_2)),
					count_2, tmp_error_text);
				goto EXIT_FUNCTION;
			}
		}
		fprintf(stderr, "********** All %u threads have been joined.\n",
			thread_count);
	}

EXIT_FUNCTION:

	return(return_code);
}

#ifndef NARGS
static void *TEST_StartFunc(TEST_DATA *start_data)
#else
static void *TEST_StartFunc(start_data)
TEST_DATA *start_data;
#endif /* #ifndef NARGS */
{
	int  return_code;
	int  old_value;
	int  new_value;
	char error_text[MTIF_MAX_ERROR_TEXT];

	SDTIF_usleep(start_data->sleep_usecs);

	new_value = ((int) MTIF_THR_Self());

	if (start_data->get_flag &&
		((return_code = MTIF_MTR_GetDataSIntBasic(start_data->data_ptr,
		&old_value, error_text)) == MTIF_SUCCESS))
		fprintf(stderr, "%s %5u (id = %10lu) got data value %10d\n",
			"Thread index", start_data->thread_index,
			((unsigned long) MTIF_THR_Self()), old_value);
	else if ((!start_data->get_flag) &&
		((return_code = MTIF_MTR_SetDataSIntBasic(start_data->data_ptr,
		new_value, &old_value, error_text)) == MTIF_SUCCESS))
		fprintf(stderr, "%s %5u (id = %10lu) set data value %10d (was %10d)\n",
			"Thread index", start_data->thread_index,
			((unsigned long) MTIF_THR_Self()), new_value, old_value);
	else {
		fprintf(stderr, "Error on %s %s %5u (id = %10lu): %s\n",
			(start_data->get_flag) ? "get" : "set", "attempt for thread index",
			start_data->thread_index, ((unsigned long) MTIF_THR_Self()),
			error_text);
		TEST_ShowData(start_data);
		exit(-1);
	}

	return(start_data);
}

#ifndef NARGS
static void TEST_ShowData(const TEST_DATA *start_data)
#else
static void TEST_ShowData(start_data)
const TEST_DATA *start_data;
#endif /* #ifndef NARGS */
{
	char buffer[STR_VAL2STR_MAX_LEN + 1];

	fprintf(stderr, "********** signature   =  0x%08lX = 0b%s\n",
		start_data->data_ptr->lock_data.signature,
		val2str_ulong(start_data->data_ptr->lock_data.signature,
		2, "0", buffer));
	fprintf(stderr, "********** init_flags  =  0x%08lX = 0b%s\n",
		start_data->data_ptr->lock_data.init_flags,
		val2str_ulong(start_data->data_ptr->lock_data.init_flags,
		2, "0", buffer));
	fprintf(stderr, "********** static_flag = %11d\n",
		start_data->data_ptr->lock_data.static_flag);
	fprintf(stderr, "********** process_id  = %11lu\n",
		start_data->data_ptr->lock_data.process_id);
	fprintf(stderr, "********** thread_id   = %11lu\n",
		((unsigned long) start_data->data_ptr->lock_data.thread_id));
#ifdef _Windows
	fprintf(stderr, "********** mtr_data    = %11lu\n",
		((unsigned long) start_data->data_ptr->lock_data.mtr_data));
	fprintf(stderr, "********** mtr_name    =  %s\n",
		(start_data->data_ptr->lock_data.mtr_name == NULL) ? "*** NONE ***" :
		start_data->data_ptr->lock_data.mtr_name);
#else
	fprintf(stderr, "********** mtr_data    = %11lu\n",
		((unsigned long) &start_data->data_ptr->lock_data.mtr_data));
#endif /* #ifdef _Windows */
}

#endif /* #ifdef TEST_MAIN */



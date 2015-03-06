/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Multi-Threading Interface Facility (MTIF) Library Source File				*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Implementation file for the 'MLB::MTIF::RwlO' class.

	Revision History	:	2000-03-02 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2000 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Include necessary header files . . .												*/
/*	***********************************************************************	*/

#include "MTIF_RwlO.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	The parent namespace for the object implemented by these methods . . .	*/
/*	***********************************************************************	*/
using namespace MLB::MTIF;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
RwlO::RwlO(MTIF_RWL_FLAG flags) :
	ready_flag(false)
{
	if (MTIF_RWL_Init(flags, NULL, &lock_data, NULL) == MTIF_SUCCESS)
		ready_flag = true;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
RwlO::~RwlO()
{
	Destroy();
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RwlO::Check(char *error_text) const
{
	int return_code;

	if ((return_code = CheckReady(error_text)) == MTIF_SUCCESS)
		return_code = MTIF_RWL_Check(&lock_data, error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RwlO::CheckReady(char *error_text) const
{
	int return_code;

	if (IsReady() == true)
		return_code = MTIF_SUCCESS;
	else {
		if (error_text != NULL)
			strcpy(error_text, "The 'MLB::MTIF::RwlO' object is not constructed.");
		return_code = MTIF_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RwlO::Destroy(char *error_text)
{
	int return_code;

	if ((return_code = CheckReady(error_text)) == MTIF_SUCCESS) {
		if (Lock(error_text) == MTIF_SUCCESS) {
			ready_flag = false;
			if ((return_code = UnlockInternal(error_text)) == MTIF_SUCCESS)
				return_code = MTIF_RWL_Destroy(&lock_data, error_text);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
bool RwlO::IsReady() const
{
	return(ready_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RwlO::Lock(char *error_text) const
{
	int return_code;

	if ((return_code = CheckReady(error_text)) == MTIF_SUCCESS)
		return_code = MTIF_RWL_LockWriter(&lock_data, error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RwlO::LockReader(char *error_text) const
{
	return(LockReader(error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RwlO::LockWriter(char *error_text) const
{
	return(LockWriter(error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RwlO::TryLock(char *error_text) const
{
	int return_code;

	if ((return_code = CheckReady(error_text)) == MTIF_SUCCESS)
		return_code = MTIF_RWL_TryLockWriter(&lock_data, error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RwlO::TryLockReader(char *error_text) const
{
	return(TryLockReader(error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RwlO::TryLockWriter(char *error_text) const
{
	return(TryLockWriter(error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RwlO::Unlock(char *error_text) const
{
	int return_code;

	if ((return_code = CheckReady(error_text)) == MTIF_SUCCESS)
		return_code = UnlockInternal(error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RwlO::UnlockInternal(char *error_text) const
{
	return(MTIF_RWL_Unlock(&lock_data, error_text));
}
/*	***********************************************************************	*/


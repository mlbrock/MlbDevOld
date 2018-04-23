/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Multi-Threading Interface Facility (MTIF) Library Source File				*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Implementation file for the 'MLB::MTIF::MtrO' class.

	Revision History	:	2000-03-02 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2000 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Include necessary header files . . .												*/
/*	***********************************************************************	*/

#include "MTIF_MtrO.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	The parent namespace for the object implemented by these methods . . .	*/
/*	***********************************************************************	*/
using namespace MLB::MTIF;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
MtrO::MtrO(MTIF_MTR_FLAG flags) :
	ready_flag(false)
{
	if (MTIF_MTR_Init(flags, NULL, &lock_data, NULL) == MTIF_SUCCESS)
		ready_flag = true;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
MtrO::~MtrO()
{
	Destroy();
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MtrO::Check(char *error_text) const
{
	int return_code;

	if ((return_code = CheckReady(error_text)) == MTIF_SUCCESS)
		return_code = MTIF_MTR_Check(&lock_data, error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MtrO::CheckReady(char *error_text) const
{
	int return_code;

	if (IsReady() == true)
		return_code = MTIF_SUCCESS;
	else {
		if (error_text != NULL)
			strcpy(error_text, "The 'MLB::MTIF::MtrO' object is not constructed.");
		return_code = MTIF_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MtrO::Destroy(char *error_text)
{
	int return_code;

	if ((return_code = CheckReady(error_text)) == MTIF_SUCCESS) {
		if (Lock(error_text) == MTIF_SUCCESS) {
			ready_flag = false;
			if ((return_code = UnlockInternal(error_text)) == MTIF_SUCCESS)
				return_code = MTIF_MTR_Destroy(&lock_data, error_text);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
bool MtrO::IsReady() const
{
	return(ready_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MtrO::Lock(char *error_text) const
{
	int return_code;

	if ((return_code = CheckReady(error_text)) == MTIF_SUCCESS)
		return_code = MTIF_MTR_Lock(&lock_data, error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MtrO::LockReader(char *error_text) const
{
	return(Lock(error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MtrO::LockWriter(char *error_text) const
{
	return(Lock(error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MtrO::TryLock(char *error_text) const
{
	int return_code;

	if ((return_code = CheckReady(error_text)) == MTIF_SUCCESS)
		return_code = MTIF_MTR_TryLock(&lock_data, error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MtrO::TryLockReader(char *error_text) const
{
	return(TryLock(error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MtrO::TryLockWriter(char *error_text) const
{
	return(TryLock(error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MtrO::Unlock(char *error_text) const
{
	int return_code;

	if ((return_code = CheckReady(error_text)) == MTIF_SUCCESS)
		return_code = UnlockInternal(error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MtrO::UnlockInternal(char *error_text) const
{
	return(MTIF_MTR_Unlock(&lock_data, error_text));
}
/*	***********************************************************************	*/


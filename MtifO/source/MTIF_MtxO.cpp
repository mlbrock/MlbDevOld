/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Multi-Threading Interface Facility (MTIF) Library Source File				*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Implementation file for the 'MLB::MTIF::MtxO' class.

	Revision History	:	2000-03-02 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2000 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Include necessary header files . . .												*/
/*	***********************************************************************	*/

#include "MTIF_MtxO.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	The parent namespace for the object implemented by these methods . . .	*/
/*	***********************************************************************	*/
using namespace MLB::MTIF;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
MtxO::MtxO(MTIF_MTX_FLAG flags) :
	ready_flag(false)
{
	if (MTIF_MTX_Init(flags, NULL, &lock_data, NULL) == MTIF_SUCCESS)
		ready_flag = true;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
MtxO::~MtxO()
{
	Destroy();
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MtxO::Check(char *error_text) const
{
	int return_code;

	if ((return_code = CheckReady(error_text)) == MTIF_SUCCESS)
		return_code = MTIF_MTX_Check(&lock_data, error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MtxO::CheckReady(char *error_text) const
{
	int return_code;

	if (IsReady() == true)
		return_code = MTIF_SUCCESS;
	else {
		if (error_text != NULL)
			strcpy(error_text, "The 'MLB::MTIF::MtxO' object is not constructed.");
		return_code = MTIF_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MtxO::Destroy(char *error_text)
{
	int return_code;

	if ((return_code = CheckReady(error_text)) == MTIF_SUCCESS) {
		if (Lock(error_text) == MTIF_SUCCESS) {
			ready_flag = false;
			if ((return_code = UnlockInternal(error_text)) == MTIF_SUCCESS)
				return_code = MTIF_MTX_Destroy(&lock_data, error_text);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
bool MtxO::IsReady() const
{
	return(ready_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MtxO::Lock(char *error_text) const
{
	int return_code;

	if ((return_code = CheckReady(error_text)) == MTIF_SUCCESS)
		return_code = MTIF_MTX_Lock(&lock_data, error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MtxO::LockReader(char *error_text) const
{
	return(Lock(error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MtxO::LockWriter(char *error_text) const
{
	return(Lock(error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MtxO::TryLock(char *error_text) const
{
	int return_code;

	if ((return_code = CheckReady(error_text)) == MTIF_SUCCESS)
		return_code = MTIF_MTX_TryLock(&lock_data, error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MtxO::TryLockReader(char *error_text) const
{
	return(TryLock(error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MtxO::TryLockWriter(char *error_text) const
{
	return(TryLock(error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MtxO::Unlock(char *error_text) const
{
	int return_code;

	if ((return_code = CheckReady(error_text)) == MTIF_SUCCESS)
		return_code = UnlockInternal(error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MtxO::UnlockInternal(char *error_text) const
{
	return(MTIF_MTX_Unlock(&lock_data, error_text));
}
/*	***********************************************************************	*/


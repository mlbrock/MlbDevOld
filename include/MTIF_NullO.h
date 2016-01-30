/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Multi-Threading Interface Facility (MTIF) Library Include File				*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the 'MLB::MTIF::NullO' class.

	Revision History	:	2000-03-02 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2000 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef HH__MLB__MTIF__NullO_h__HH

#define HH__MLB__MTIF__NullO_h__HH		1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Include necessary header files . . .												*/
/*	***********************************************************************	*/

#include "mtif.h"

/*	***********************************************************************	*/

namespace MLB {

namespace MTIF {

/*	***********************************************************************	*/
class NullO {

	public:

		/*	***********************************************************
			***********************************************************
			Constructor and destructor methods . . .
			***********************************************************	*/
		NullO(MTIF_FLAG flags = 0L) :
			ready_flag(true), start_flags(flags) { }
		virtual ~NullO() { Destroy(); }
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Core functionality methods . . .
			***********************************************************	*/
		virtual int  Check(char *error_text = NULL) const
			{ return(CheckReady(error_text)); }
		virtual int  CheckReady(char *error_text = NULL) const {
			int return_code;
			if (ready_flag)
				return_code = MTIF_SUCCESS;
			else {
				if (error_text != NULL)
					strcpy(error_text,
						"The 'MLB::MTIF::NullO' object is not constructed.");
				return_code = MTIF_FAILURE;
			}
			return(return_code);
		}
		virtual int  Destroy(char *error_text = NULL) {
			int return_code = CheckReady(error_text);
			if (return_code == MTIF_SUCCESS)
				ready_flag = false;
			return(return_code);
		}
		virtual bool IsReady() const
			{ return(ready_flag); }
		virtual int  Lock(char *error_text = NULL) const
			{ return(CheckReady(error_text)); }
		virtual int  LockReader(char *error_text = NULL) const
			{ return(CheckReady(error_text)); }
		virtual int  LockWriter(char *error_text = NULL) const
			{ return(CheckReady(error_text)); }
		virtual int  TryLock(char *error_text = NULL) const
			{ return(CheckReady(error_text)); }
		virtual int  TryLockReader(char *error_text = NULL) const
			{ return(CheckReady(error_text)); }
		virtual int  TryLockWriter(char *error_text = NULL) const
			{ return(CheckReady(error_text)); }
		virtual int  Unlock(char *error_text = NULL) const
			{ return(CheckReady(error_text)); }
		/*	***********************************************************	*/

	protected:

		/*	***********************************************************
			***********************************************************
			Used internally only at the time of destruction.
			***********************************************************	*/
		virtual int UnlockInternal(char *error_text) const
			{ return(CheckReady(error_text)); }
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			The following protected members are provided as a courtesy
			to those implementing classes derived from this one.

			Use at your own risk . . .
			***********************************************************	*/
		bool      ready_flag;
		MTIF_FLAG start_flags;
		/*	***********************************************************	*/

	private:

		/*	***********************************************************
			***********************************************************
			These declarations are present only to prevent generation by
			the compiler. They are never defined . . .

			Nobody gets to see these because a copy or assignment of an
			active mutex will ruin your day for sure . . .
			***********************************************************	*/
		NullO(const NullO &source);
		NullO& operator=(const NullO &source);
		/*	***********************************************************	*/
};
/*	***********************************************************************	*/

} // namespace MTIF

} // namespace MLB

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	For compatibility with code developed before C++ namespaces . . .			*/
/*	***********************************************************************	*/
typedef MLB::MTIF::NullO MTIF_NullO;
/*	***********************************************************************	*/

#endif /* #ifndef HH__MLB__MTIF__NullO_h__HH */


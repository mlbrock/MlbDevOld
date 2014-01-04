/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Multi-Threading Interface Facility (MTIF) Library Include File				*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the 'MLB::MTIF::MtrO' class.

	Revision History	:	2000-03-02 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2000 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef HH__MLB__MTIF__MtrO_h__HH

#define HH__MLB__MTIF__MtrO_h__HH		1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Include necessary header files . . .												*/
/*	***********************************************************************	*/

#include "mtif.h"

/*	***********************************************************************	*/

namespace MLB {

namespace MTIF {

/*	***********************************************************************	*/
class MtrO {

	public:

		/*	***********************************************************
			***********************************************************
			Constructor and destructor methods . . .
			***********************************************************	*/
		MtrO(MTIF_MTR_FLAG flags = MTIF_MTR_FLAG_DEFAULT);
		virtual ~MtrO();
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Core functionality methods . . .
			***********************************************************	*/
		virtual int  Check(char *error_text = NULL) const;
		virtual int  CheckReady(char *error_text = NULL) const;
		virtual int  Destroy(char *error_text = NULL);
		virtual bool IsReady() const;
		virtual int  Lock(char *error_text = NULL) const;
		virtual int  LockReader(char *error_text = NULL) const;
		virtual int  LockWriter(char *error_text = NULL) const;
		virtual int  TryLock(char *error_text = NULL) const;
		virtual int  TryLockReader(char *error_text = NULL) const;
		virtual int  TryLockWriter(char *error_text = NULL) const;
		virtual int  Unlock(char *error_text = NULL) const;
		/*	***********************************************************	*/

	protected:

		/*	***********************************************************
			***********************************************************
			The following protected members are provided as a courtesy
			to those implementing classes derived from this one.

			Use at your own risk . . .
			***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Used internally only at the time of destruction.
			***********************************************************	*/
		virtual int UnlockInternal(char *error_text) const;
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Data members . . .
			***********************************************************	*/
		bool                    ready_flag;
		mutable MTIF_MTR_HANDLE lock_data;
		/*	***********************************************************	*/

	private:

		/*	***********************************************************
			***********************************************************
			These declarations are present only to prevent generation by
			the compiler. They are never defined . . .

			Nobody gets to see these because a copy or assignment of an
			active mutex will ruin your day for sure . . .
			***********************************************************	*/
		MtrO(const MtrO &source);
		MtrO& operator=(const MtrO &source);
		/*	***********************************************************	*/
};
/*	***********************************************************************	*/

} // namespace MTIF

} // namespace MLB

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	For compatibility with code developed before C++ namespaces . . .			*/
/*	***********************************************************************	*/
typedef MLB::MTIF::MtrO MTIF_MtrO;
/*	***********************************************************************	*/

#endif /* #ifndef HH__MLB__MTIF__MtrO_h__HH */


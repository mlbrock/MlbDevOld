/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the 'MLB::RVUtil::EnvO_TC' class.

	Revision History	:	2001-10-18 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 2001 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef HH__MLB__RVUtil__EnvO_TC_h__HH

#define HH__MLB__RVUtil__EnvO_TC_h__HH			1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Include necessary header files . . .											*/
/*	***********************************************************************	*/

#ifdef _Windows
# pragma warning(disable:4710 4786)
# if _MSC_VER >= 1300
#  pragma warning(disable:4217 4251 4555 4668)
# endif /* # if _MSC_VER >= 1300 */
# pragma warning(disable:4018 4100 4146 4244 4245 4511 4512 4663)
# include <string>
# include <map>
# if _MSC_VER >= 1300
#  pragma warning(default:4217 4251 4555 4668)
# endif /* # if _MSC_VER >= 1300 */
# pragma warning(default:4018 4100 4146 4244 4245 4511 4512 4663)
#else
# include <string>
# include <map>
#endif /* #ifdef _Windows */

#include <strfuncs.h>
#include <mtif.h>
#include <MLogO.h>

#include "RVUtilEnvO.h"

/*	***********************************************************************	*/

namespace MLB {

namespace Rendezvous_Utility {

/*	***********************************************************************	*/
class EnvO_TC {

	public:

		/*	***********************************************************
			***********************************************************
			Constructor and destructor methods . . .
			***********************************************************	*/
		EnvO_TC(const char *service = NULL, const char *network = NULL,
			const char *daemon = NULL, rv_Callback call_back = NULL,
			rv_Opaque closure = NULL, MLogO *mlogo_ptr = NULL);
		EnvO_TC(const RVUTIL_ENV *env_ptr, MLogO *mlogo_ptr = NULL);
		EnvO_TC(const EnvO *env_ptr, MLogO *mlogo_ptr = NULL);
		~EnvO_TC();
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Core functionality methods . . .
			***********************************************************	*/
		EnvO         *Find() const;
		EnvO         *Add();
		void          Remove();
		unsigned int  GetCount() const;
		unsigned int  GetHighWaterMark() const;
		/*	***********************************************************	*/

	protected:

		/*	***********************************************************
			***********************************************************
			Locking methods . . .
			***********************************************************	*/
		int Lock(char *error_text = NULL) const;
		int TryLock(char *error_text = NULL) const;
		int UnLock(char *error_text = NULL) const;
		/*	***********************************************************	*/

	private:

		/*	***********************************************************
			***********************************************************
			These declarations are present only to prevent generation
			by the compiler. They are never defined . . .
			***********************************************************	*/
		EnvO_TC(const EnvO_TC &source);
		EnvO_TC& operator=(const EnvO_TC &source);
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Some private internal methods . . .
			***********************************************************	*/
		EnvO         *FindInternal(MTIF_THR_ID thread_id = MTIF_THR_Self()) const;
		EnvO         *Create(EnvO *env_ptr);
		unsigned int  SetHighWaterMark() {
			high_water_mark = (high_water_mark > env_map.size()) ?
				high_water_mark : env_map.size();
			return(high_water_mark);
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Data members . . .
			***********************************************************	*/
		bool                           ready_flag;
		mutable MTIF_MTR_HANDLE        lock_data;
		EnvO                          *env_source;
		std::map<MTIF_THR_ID, EnvO *>  env_map;
		unsigned int                   high_water_mark;
		MLogO                          mlogo_data;
		/*	***********************************************************	*/
};
/*	***********************************************************************	*/

} // namespace Rendezvous_Utility (and RVUtil)

// Namespace 'Rendezvous_Utility' is aliased to 'RVUtil' for brevity . . .
namespace RVUtil = Rendezvous_Utility;

} // namespace MLB

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	For compatibility with code developed before C++ namespaces . . .			*/
/*	***********************************************************************	*/
typedef MLB::RVUtil::EnvO_TC RVUtilEnvO_TC;
/*	***********************************************************************	*/

#endif /* #ifndef HH__MLB__RVUtil__EnvO_TC_h__HH */


/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the 'MLB::RVUtil::rvmsg_Msg_TC' class.

	Revision History	:	2001-10-18 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 2001 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef HH__MLB__RVUtil__rvmsg_Msg_TC_h__HH

#define HH__MLB__RVUtil__rvmsg_Msg_TC_h__HH			1

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

#include "RVUtilEnvO_TC.h"

/*	***********************************************************************	*/

namespace MLB {

namespace Rendezvous_Utility {

/*	***********************************************************************	*/
class rvmsg_Msg_TC_KeyInternal {

	public:

		/*	***********************************************************
			***********************************************************
			Constructor and destructor methods . . .
			***********************************************************	*/
		rvmsg_Msg_TC_KeyInternal(const rv_Session in_session_handle = NULL,
			MTIF_THR_ID in_thread_id = MTIF_THR_Self()) :
			session_handle(in_session_handle), thread_id(in_thread_id) { }
		~rvmsg_Msg_TC_KeyInternal() { }
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Comparison operators . . .
			***********************************************************	*/
		bool operator< (const rvmsg_Msg_TC_KeyInternal &rhs) const {
			return(compare(this, &rhs) < 0);
		}
		static int compare(const rvmsg_Msg_TC_KeyInternal &lhs,
			const rvmsg_Msg_TC_KeyInternal &rhs) {
			return(compare(&lhs, &rhs));
		}
		static int compare(const rvmsg_Msg_TC_KeyInternal *lhs,
			const rvmsg_Msg_TC_KeyInternal *rhs) {
			int cmp;

			if ((cmp = ((lhs->thread_id > rhs->thread_id) ? 1 :
				((lhs->thread_id < rhs->thread_id) ? -1 : 0))) == 0)
				cmp = ((lhs->session_handle > rhs->session_handle) ? 1 :
					((lhs->session_handle < rhs->session_handle) ? -1 : 0));

			return(cmp);
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Data members . . .
			***********************************************************	*/
		MTIF_THR_ID thread_id;
		rv_Session  session_handle;
		/*	***********************************************************	*/
};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
class rvmsg_Msg_TC {

	public:

		/*	***********************************************************
			***********************************************************
			Constructor and destructor methods . . .
			***********************************************************	*/
		rvmsg_Msg_TC(rvmsg_Size in_size, MLogO *mlogo_ptr = NULL);
		rvmsg_Msg_TC(unsigned int in_size, MLogO *mlogo_ptr = NULL);
		~rvmsg_Msg_TC();
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Core functionality methods . . .
			***********************************************************	*/
		rvmsg_Msg    Find(EnvO_TC *envo_tc) const;
		rvmsg_Msg    Find(EnvO_TC &envo_tc) const;
		rvmsg_Msg    Find(const EnvO *envo) const;
		rvmsg_Msg    Find(const EnvO &envo) const;
		rvmsg_Msg    Find(const RVUTIL_ENV *env) const;
		rvmsg_Msg    Find(const RVUTIL_ENV &env) const;
		rvmsg_Msg    Find(const rv_Session session_handle) const;
		rvmsg_Msg    Add(EnvO_TC *envo_tc);
		rvmsg_Msg    Add(EnvO_TC &envo_tc);
		rvmsg_Msg    Add(const EnvO *envo);
		rvmsg_Msg    Add(const EnvO &envo);
		rvmsg_Msg    Add(const RVUTIL_ENV *env);
		rvmsg_Msg    Add(const RVUTIL_ENV &env);
		rvmsg_Msg    Add(const rv_Session session_handle);
		void         Remove(EnvO_TC *envo_tc);
		void         Remove(EnvO_TC &envo_tc);
		void         Remove(const EnvO *envo);
		void         Remove(const EnvO &envo);
		void         Remove(const RVUTIL_ENV *env);
		void         Remove(const RVUTIL_ENV &env);
		void         Remove(const rv_Session session_handle);
		unsigned int GetCount() const;
		unsigned int GetHighWaterMark() const;
		rvmsg_Size   GetMsgSize() const { return(msg_size); }
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
		rvmsg_Msg_TC(const rvmsg_Msg_TC &source);
		rvmsg_Msg_TC& operator=(const rvmsg_Msg_TC &source);
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Some private internal methods . . .
			***********************************************************	*/
		rvmsg_Msg    FindInternal(const rv_Session session_handle,
			MTIF_THR_ID thread_id = MTIF_THR_Self()) const;
		rvmsg_Msg    Create(const rv_Session session_handle, char *error_text);
		unsigned int SetHighWaterMark() {
			high_water_mark = (high_water_mark > msg_map.size()) ?
				high_water_mark : msg_map.size();
			return(high_water_mark);
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Data members . . .
			***********************************************************	*/
		bool                                          ready_flag;
		mutable MTIF_MTR_HANDLE                       lock_data;
		rvmsg_Size                                    msg_size;
		std::map<rvmsg_Msg_TC_KeyInternal, rvmsg_Msg> msg_map;
		unsigned int                                  high_water_mark;
		MLogO                                         mlogo_data;
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
typedef MLB::RVUtil::rvmsg_Msg_TC_KeyInternal RVUtilrvmsg_Msg_TC_KeyInternal;
typedef MLB::RVUtil::rvmsg_Msg_TC             RVUtilrvmsg_Msg_TC;
/*	***********************************************************************	*/

#endif /* #ifndef HH__MLB__RVUtil__rvmsg_Msg_TC_h__HH */


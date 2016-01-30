/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the 'MLB::RVUtil::EnvO' class.

	Revision History	:	2001-10-18 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 2001 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef HH__MLB__RVUtil__EnvO_h__HH

#define HH__MLB__RVUtil__EnvO_h__HH					1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include "rvutil.h"

/*	***********************************************************************	*/

namespace MLB {

namespace Rendezvous_Utility {

/*	***********************************************************************	*/
class EnvO {

	public:

		/*	***********************************************************
			***********************************************************
			Constructor and destructor methods . . .
			***********************************************************	*/
		EnvO(const char *service = NULL, const char *network = NULL,
			const char *daemon = NULL, const char *subject_name = NULL,
			rv_Callback call_back = NULL, rv_Opaque closure = NULL);
		EnvO(const RVUTIL_ENV *env_ptr);
		EnvO(const EnvO *env_ptr);
		virtual ~EnvO();
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Copy and assignment constructors . . .
			***********************************************************	*/
		EnvO(const EnvO &source) {
			source.Copy(this);
		}
		EnvO& operator= (const EnvO &source) {
			source.Copy(this);
			return(*this);
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			The core methods . . .
			***********************************************************	*/
		virtual int AddSub(const char *subject_name, rv_Callback call_back,
			unsigned int *sub_index = NULL, char *error_text = NULL);
		virtual int AddSubList(unsigned int subject_count, char **subject_list,
			rv_Callback call_back, char *error_text = NULL);
		virtual int AddSubListen(const char *subject_name, rv_Callback call_back,
			rv_Opaque closure, unsigned int *sub_index = NULL,
			char *error_text = NULL);
		virtual int AddSubListListen(unsigned int subject_count,
			char **subject_list, rv_Callback call_back, rv_Opaque closure = NULL,
			char *error_text = NULL);
		virtual int BeginListenEnv(void *user_data_ptr = NULL,
			char *error_text = NULL);
		virtual int ListenSub(rv_Opaque closure, unsigned int sub_index,
			char *error_text = NULL);
		virtual int RemoveSub(unsigned int sub_index, char *error_text = NULL);
		virtual int StartSessionEnv(char *error_text = NULL);
		virtual int StartSessionEnvContext(rvevm_Context context,
			char *error_text = NULL);
		virtual int StartSessionEnvMakeContext(char *error_text = NULL);
		virtual int StartSignalHandling(RVUTIL_SIGNAL_SPEC *signal_spec,
			rvevm_EventCallback event_call_back, void *user_data_ptr = NULL,
			char *error_text = NULL);
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Various close methods . . .
			***********************************************************	*/
		virtual void CloseEnv(bool expedite_flag = false);
		virtual int  CloseSub(unsigned int sub_index, char *error_text = NULL);
		virtual void EndEnv(bool expedite_flag = false);
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Subscription find methods . . .
			***********************************************************	*/
		virtual const RVUTIL_SUB *FindSubByListenID(rv_ListenId listen_id,
			unsigned int *found_index = NULL) const;
		virtual const RVUTIL_SUB *FindSubByName(const char *subject_name,
			unsigned int *found_index = NULL) const;
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Some accessor methods . . .
			***********************************************************	*/
		virtual unsigned int   GetSubCount() const;
		virtual rv_Opaque      GetDefaultClosure() const;
		virtual rvevm_Context  GetContext() const;
		virtual rv_Session     GetSession() const;
		virtual RVUTIL_ENV    *GetEnvPtr() const;
		virtual rv_Opaque      SetDefaultClosure(rv_Opaque closure = NULL);
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Accessor methods for getting the list of environment subjects.
			***********************************************************	*/
		int        GetSubList(unsigned int *sub_count, RVUTIL_SUB **sub_list,
			char *error_text) const;
		static int GetSubList(const EnvO *env_ptr,
			unsigned int *sub_count, RVUTIL_SUB **sub_list,
			char *error_text);
		static int GetSubList(const RVUTIL_ENV *env_ptr,
			unsigned int *sub_count, RVUTIL_SUB **sub_list,
			char *error_text);
		int        GetSubNameList(unsigned int *sub_count, char ***sub_list,
			char *error_text) const;
		static int GetSubNameList(const EnvO *env_ptr,
			unsigned int *sub_count, char ***sub_list, char *error_text);
		static int GetSubNameList(const RVUTIL_ENV *env_ptr,
			unsigned int *sub_count, char ***sub_list, char *error_text);
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Copy methods --- note the latter two are static . . .
			***********************************************************	*/
		       int Copy(EnvO *destination, char *error_text = NULL) const;
		static int Copy(const EnvO *source, EnvO *destination,
			char *error_text = NULL);
		static int Copy(const RVUTIL_ENV *source, EnvO *destination,
			char *error_text = NULL);
		/*	***********************************************************	*/

	private:

		/*	***********************************************************
			***********************************************************
			Useful as default arguments . . .
			***********************************************************	*/
		char *UseDefaultErrorText(char *error_text = NULL) const {
			return((error_text != NULL) ? error_text :
				const_cast<char *>(my_error_text));
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Data members . . .
			***********************************************************	*/
		bool       ready_flag;
		rv_Opaque  my_closure;
		RVUTIL_ENV env_data;
		char       my_error_text[RVUTIL_MAX_ERROR_TEXT];
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
typedef MLB::RVUtil::EnvO RVUtilEnvO;
/*	***********************************************************************	*/

#endif /* #ifndef HH__MLB__RVUtil__EnvO_h__HH */


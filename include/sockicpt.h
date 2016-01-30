/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Socket Interception Library Include File											*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Socket interception library include file.

	Revision History	:	1998-04-18 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef HH__sockicpt_h__HH

#define HH__sockicpt_h__HH					1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Required include files . . .															*/
/*	***********************************************************************	*/

#include <npsl.h>
#include <sdtif.h>

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   BASE NAME   :	SOCKICPT Return Codes

   NAME        :  SOCKICPT Return Codes

   DESCRIPTION :  The SOCKICPT return codes have the following meanings:

						(.) ''SOCKICPT_SUCCESS'' means that the function invoked
						completed without error. ''SOCKICPT_SUCCESS'' is guaranteed
						to be equal to zero (''0'').

						(.) ''SOCKICPT_FAILURE'' indicates that the function invoked
						encountered a general operation failure. This is the
						'catch-all' error code for those errors which do not fit
						into category of one the other SOCKICPT error codes.

						(.) ''SOCKICPT_BAD_ARGS_FAILURE'' indicates that the
						arguments passed to a function invoked were invalid.

						(.) ''SOCKICPT_MEMORY_FAILURE'' indicates that the memory
						required for operation of the function invoked could not be
						allocated.

						(.) ''SOCKICPT_SYSTEM_FAILURE'' indicates that the function
						invoked encountered a failure of a standard library
						function or a system call.

						(.) ''SOCKICPT_LOCK_ACQ_FAILURE'' indicates that a lock
						could not be acquired on a resource.

						(.) ''SOCKICPT_INVALID_SIDE_FAILURE'' indicates that a GL API
						side code is invalid or a message cannot be processed from
						or for the specified side.

						(.) ''SOCKICPT_INVALID_FACILITY_FAILURE'' indicates that
						a GL API facility code is invalid or a message cannot be
						processed from the specified facility.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1998 - 2016 Michael L. Brock

   OUTPUT INDEX:  SOCKICPT_SUCCESS
						SOCKICPT_FAILURE
						SOCKICPT_BAD_ARGS_FAILURE
						SOCKICPT_MEMORY_FAILURE
						SOCKICPT_SYSTEM_FAILURE
						SOCKICPT_LOCK_ACQ_FAILURE
						SOCKICPT Return Codes:SOCKICPT_SUCCESS
						SOCKICPT Return Codes:SOCKICPT_FAILURE
						SOCKICPT Return Codes:SOCKICPT_BAD_ARGS_FAILURE
						SOCKICPT Return Codes:SOCKICPT_MEMORY_FAILURE
						SOCKICPT Return Codes:SOCKICPT_SYSTEM_FAILURE
						SOCKICPT Return Codes:SOCKICPT_LOCK_ACQ_FAILURE
						SOCKICPT Manifest Constants:SOCKICPT_SUCCESS
						SOCKICPT Manifest Constants:SOCKICPT_FAILURE
						SOCKICPT Manifest Constants:SOCKICPT_BAD_ARGS_FAILURE
						SOCKICPT Manifest Constants:SOCKICPT_MEMORY_FAILURE
						SOCKICPT Manifest Constants:SOCKICPT_SYSTEM_FAILURE
						SOCKICPT Manifest Constants:SOCKICPT_LOCK_ACQ_FAILURE
						SOCKICPT Defines:SOCKICPT_SUCCESS
						SOCKICPT Defines:SOCKICPT_FAILURE
						SOCKICPT Defines:SOCKICPT_BAD_ARGS_FAILURE
						SOCKICPT Defines:SOCKICPT_MEMORY_FAILURE
						SOCKICPT Defines:SOCKICPT_SYSTEM_FAILURE
						SOCKICPT Defines:SOCKICPT_LOCK_ACQ_FAILURE
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:  SOCKICPT_SUCCESS
						SOCKICPT_FAILURE
						SOCKICPT_BAD_ARGS_FAILURE
						SOCKICPT_MEMORY_FAILURE
						SOCKICPT_SYSTEM_FAILURE
						SOCKICPT_LOCK_ACQ_FAILURE
						SOCKICPT Return Codes
						SOCKICPT Return Code
						SOCKICPT return codes
						SOCKICPT return code
						SOCKICPT Status Codes
						SOCKICPT Status Code
						SOCKICPT status codes
						SOCKICPT status code
						SOCKICPT Error Codes
						SOCKICPT Error Code
						SOCKICPT error codes
						SOCKICPT error code

   PUBLISH NAME:	SOCKICPT Return Codes
						SOCKICPT return codes
						SOCKICPT_SUCCESS
						SOCKICPT_FAILURE
						SOCKICPT_BAD_ARGS_FAILURE
						SOCKICPT_MEMORY_FAILURE
						SOCKICPT_SYSTEM_FAILURE
						SOCKICPT_LOCK_ACQ_FAILURE

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define SOCKICPT_SUCCESS					 0
#define SOCKICPT_FAILURE					-1
#define SOCKICPT_BAD_ARGS_FAILURE		-2
#define SOCKICPT_MEMORY_FAILURE			-3
#define SOCKICPT_SYSTEM_FAILURE		   -4
#define SOCKICPT_LOCK_ACQ_FAILURE	   -5
/*	***********************************************************************	*/

/*
	ADF NOTE:No ADF.
*/
/*	***********************************************************************	*/
typedef enum {
	SOCKICPT_FLAG_RECV = 0,
	SOCKICPT_FLAG_SEND = 1,
	SOCKICPT_FLAG_OOB	 = 2
} SOCKICPT_FLAG;
/*	***********************************************************************	*/

/*
	ADF NOTE:No ADF.
*/
/*	***********************************************************************	*/
typedef enum {
	SOCKICPT_SIDE_NEAR = 1,
	SOCKICPT_SIDE_FAR  = 2,
	SOCKICPT_SIDE_BOTH = (SOCKICPT_SIDE_NEAR | SOCKICPT_SIDE_FAR)
} SOCKICPT_SIDE;
/*	***********************************************************************	*/

/*
	ADF NOTE:No ADF.
*/
/*	***********************************************************************	*/
typedef enum {
	SOCKICPT_OPER_RECV = 1,
	SOCKICPT_OPER_SEND = 2,
	SOCKICPT_OPER_BOTH = (SOCKICPT_OPER_RECV | SOCKICPT_OPER_SEND)
} SOCKICPT_OPER;
/*	***********************************************************************	*/

/*
	ADF NOTE:No ADF.
*/
/*	***********************************************************************	*/
#ifdef _Windows
typedef __int64 SOCKICPT_Counter;
#define SOCKICPT_CounterPrintfFormat	"%20I64u"
#elif SOCKICPT_HAS_NO_LONG_LONG
typedef double SOCKICPT_Counter;
#define SOCKICPT_CounterPrintfFormat	"%20.0f"
#else
typedef unsigned long long SOCKICPT_Counter;
#define SOCKICPT_CounterPrintfFormat	"%20U"
#endif /* #ifdef _Windows */
/*	***********************************************************************	*/

/*
	ADF NOTE:No ADF.
*/
/*	***********************************************************************	*/
class SOCKICPT_TransId {

	public:

		/*	***********************************************************
			***********************************************************
			Constructor and destructor methods . . .
			***********************************************************	*/
		SOCKICPT_TransId(unsigned long low_order = 0L,
			unsigned long high_order = 0L) :
			low_order_(low_order), high_order_(high_order) {
		}
		~SOCKICPT_TransId() { }
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Auto-increment of a request tag . . .
			***********************************************************	*/
		SOCKICPT_TransId &operator++()    {
			Increment();
			return(*this);
		}
		const SOCKICPT_TransId operator++(int) {
			SOCKICPT_TransId tmp_tag = *this;
			Increment();
			return(tmp_tag);
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Test for equivalence of a request tag . . .
			***********************************************************	*/
		bool operator==(const SOCKICPT_TransId &other) const {
			return((this->low_order_ == other.low_order_) &&
				(this->high_order_ == other.high_order_));
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Increment a request tag . . .
			***********************************************************	*/
		void Increment() {
			if (low_order_ < ULONG_MAX)
				low_order_++;
			else {
				low_order_ = 0L;
				high_order_++;
			}
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Output formatting . . .
			***********************************************************	*/
		friend std::ostream& operator << (std::ostream &o_str,
			const SOCKICPT_TransId &datum) {
			o_str <<
				std::setw(10) << datum.high_order_ << "." <<
				std::setw(10) << datum.low_order_;
			return(o_str);
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Data members . . .
			***********************************************************	*/
		unsigned long low_order_;
		unsigned long high_order_;
		/*	***********************************************************	*/
};
/*	***********************************************************************	*/

/*
	ADF NOTE:No ADF.
*/
/*	***********************************************************************	*/
struct SOCKICPT_LOG_ENTRY_HEADER {
	unsigned int     total_length;
	unsigned long    this_offset;
	unsigned long    next_offset;
	struct timespec  log_time;
	struct timespec  action_time;
	SOCKICPT_OPER    oper;
	SOCKICPT_SIDE    side;
	struct in_addr   near_addr;
	int              near_port;
	struct in_addr   far_addr;
	int              far_port;
	SOCKICPT_TransId trans_id;
	unsigned int     send_segment;
	unsigned int     data_length;

	friend std::ostream& operator << (std::ostream &o_str,
		const struct timespec &datum) {
		char buffer[SDTIF_FMT_TIME_LEN_TIMESPEC + 1];
		o_str << SDTIF_Format_timespec(&datum, buffer);
		return(o_str);
	}

	friend std::ostream& operator << (std::ostream &o_str,
		const struct timespec *datum) {
		char buffer[SDTIF_FMT_TIME_LEN_TIMESPEC + 1];
		o_str << SDTIF_Format_timespec(datum, buffer);
		return(o_str);
	}

	friend std::ostream& operator << (std::ostream &o_str,
		const struct in_addr &datum) {
		char buffer[NPSL_MAX_IPV4_ADDR_STR + 1];
		o_str << NPSL_AddrStructToINet(&datum, buffer);
		return(o_str);
	}
	friend std::ostream& operator << (std::ostream &o_str,
		const struct in_addr *datum) {
		char buffer[NPSL_MAX_IPV4_ADDR_STR + 1];
		o_str << NPSL_AddrStructToINet(datum, buffer);
		return(o_str);
	}

	friend std::ostream& operator << (std::ostream &o_str,
		const SOCKICPT_LOG_ENTRY_HEADER &datum) {
		o_str <<
			std::setw(10) << datum.total_length << " " <<
			std::setw(10) << datum.this_offset << " " <<
			std::setw(10) << datum.next_offset << " " <<
			std::setw(SDTIF_FMT_TIME_LEN_TIMESPEC) << &datum.log_time << " " <<
			std::setw(SDTIF_FMT_TIME_LEN_TIMESPEC) << &datum.action_time << " " <<
			std::setw(10) << datum.oper << " " <<
			std::setw(10) << datum.side << " " <<
			std::setw((4 * 3) + 3) << &datum.near_addr << " " <<
			std::setw(5) << datum.near_port << " " <<
			std::setw((4 * 3) + 3) << &datum.far_addr << " " <<
			std::setw(5) << datum.far_port << " " <<
			std::setw(10) << datum.trans_id << " " <<
			std::setw(10) << datum.send_segment << " " <<
			std::setw(10) << datum.data_length;
		return(o_str);
	}
};
/*	***********************************************************************	*/

/*
	ADF NOTE:No ADF.
*/
/*	***********************************************************************	*/
typedef struct {
	SOCKICPT_LOG_ENTRY_HEADER log_entry;
	std::string               log_data;
} SOCKICPT_LOG_ENTRY_HEADER_DATA;
/*	***********************************************************************	*/

#endif /* #ifndef HH__sockicpt_h__HH */


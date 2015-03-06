/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLB Executable Module Source File													*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Intercepts socket connections with logging.

	Revision History	:	1998-04-18 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Required include files . . .															*/
/*	***********************************************************************	*/

#include <stdio.h>

#include <mbcompat.h>

#ifdef _Windows
# pragma warning(disable:4710 4786)
# if _MSC_VER >= 1300
#  pragma warning(disable:4217 4251 4555)
# endif /* # if _MSC_VER >= 1300 */
# pragma warning(disable:4018 4100 4146 4244 4245 4511 4512 4663)
# include <iomanip>
# include <iostream>
# include <sstream>
# if _MSC_VER >= 1300
#  pragma warning(default:4217 4251 4555)
# endif /* # if _MSC_VER >= 1300 */
# pragma warning(default:4018 4100 4146 4244 4245 4511 4512 4663)
#else
# include <iomanip>
# include <iostream>
# include <sstream>
#endif /* #ifdef _Windows */

#include <mfile.h>
#include <MTIF_MtrO.h>
#include <MTIF_RwlO.h>
#include <MLogO.h>

#include <deque_LC.h>

#include "sockicpt.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
static MTIF_RWL_DATA_SINT  SOCKICPT_ExitFlag =
	MTIF_RWL_DATA_SINT_STATIC_INIT(0);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#define SOCKICPT_WAKEUP_USECS				50000L
/*	***********************************************************************	*/

/*	***********************************************************************	*/
class SOCKICPT_SocketStats {

	public:

		SOCKICPT_SocketStats(SOCKICPT_Counter action_count = 0,
			SOCKICPT_Counter action_bytes = 0, unsigned int min_bytes = UINT_MAX,
			unsigned int max_bytes = 0) :
			action_count_(action_count), action_bytes_(action_bytes),
			min_bytes_(min_bytes), max_bytes_(max_bytes) { }

		void AddAction(unsigned int action_bytes = 0) {
			action_count_++;
			action_bytes_ += ((SOCKICPT_Counter) action_bytes);
			if (action_bytes < min_bytes_)
				min_bytes_ = action_bytes;
			if (action_bytes > max_bytes_)
				max_bytes_ = action_bytes;
		}

		SOCKICPT_Counter GetCount() const {
			return(action_count_);
		}
		SOCKICPT_Counter GetBytes() const {
			return(action_bytes_);
		}
		double           GetAverage() const {
			return((action_count_) ?
				(((double) action_bytes_) / ((double) action_count_)) : 0.0);
		}
		unsigned int     GetMinimum() const {
			return((min_bytes_ != UINT_MAX) ? min_bytes_ : 0);
		}
		unsigned int     GetMaximum() const {
			return(max_bytes_);
		}

		SOCKICPT_SocketStats &operator += (const SOCKICPT_SocketStats &other) {
			*this = *this + other;
			return(*this);
		}

	private:

		friend SOCKICPT_SocketStats operator + (const SOCKICPT_SocketStats &lhs,
			const SOCKICPT_SocketStats &rhs) {
			return(SOCKICPT_SocketStats(lhs.action_count_ + rhs.action_count_,
				lhs.action_bytes_ + rhs.action_bytes_,
				std::min(lhs.min_bytes_, rhs.min_bytes_),
				std::max(lhs.max_bytes_, rhs.max_bytes_)));
		}

		SOCKICPT_Counter action_count_;
		SOCKICPT_Counter action_bytes_;
		unsigned int     min_bytes_;
		unsigned int     max_bytes_;
};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
class SOCKICPT_SocketStatsSide {

	public:

		SOCKICPT_SocketStatsSide() :
			recv_stats_(), send_stats_() { }

		SOCKICPT_SocketStats  GetStats(SOCKICPT_OPER oper = SOCKICPT_OPER_BOTH)
			const {
			SOCKICPT_SocketStats tmp_stats;
			return(GetStats(oper, tmp_stats));
		}
		SOCKICPT_SocketStats &GetStats(SOCKICPT_OPER oper,
			SOCKICPT_SocketStats &out_stats) const {
			out_stats = ((oper == SOCKICPT_OPER_RECV) ? recv_stats_ :
				((oper == SOCKICPT_OPER_SEND) ? send_stats_ :
				(recv_stats_ + send_stats_)));
			return(out_stats);
		}

		SOCKICPT_Counter GetCount(SOCKICPT_OPER oper = SOCKICPT_OPER_BOTH) const {
			SOCKICPT_SocketStats tmp_stats;
			return(GetStats(oper, tmp_stats).GetCount());
		}
		SOCKICPT_Counter GetBytes(SOCKICPT_OPER oper = SOCKICPT_OPER_BOTH) const {
			SOCKICPT_SocketStats tmp_stats;
			return(GetStats(oper, tmp_stats).GetBytes());
		}

		double       GetAverage(SOCKICPT_OPER oper = SOCKICPT_OPER_BOTH) const {
			SOCKICPT_SocketStats tmp_stats;
			return(GetStats(oper, tmp_stats).GetAverage());
		}
		unsigned int GetMinimum(SOCKICPT_OPER oper = SOCKICPT_OPER_BOTH) const {
			SOCKICPT_SocketStats tmp_stats;
			return(GetStats(oper, tmp_stats).GetMinimum());
		}
		unsigned int GetMaximum(SOCKICPT_OPER oper = SOCKICPT_OPER_BOTH) const {
			SOCKICPT_SocketStats tmp_stats;
			return(GetStats(oper, tmp_stats).GetMaximum());
		}

		void AddActionRecv(unsigned int action_bytes = 0) {
			recv_stats_.AddAction(action_bytes);
		}
		void AddActionSend(unsigned int action_bytes = 0) {
			send_stats_.AddAction(action_bytes);
		}

		void AddStats(const SOCKICPT_SocketStatsSide &other) {
			this->recv_stats_ += other.recv_stats_;
			this->send_stats_ += other.send_stats_;
		}
		SOCKICPT_SocketStatsSide &operator +=
			(const SOCKICPT_SocketStatsSide &other) {
			this->AddStats(other);
			return(*this);
		}

	private:

		SOCKICPT_SocketStats recv_stats_;
		SOCKICPT_SocketStats send_stats_;
};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
class SOCKICPT_SocketStatsConn {

	public:

		SOCKICPT_SocketStatsConn() :
			near_stats_(), far_stats_() { }

		SOCKICPT_SocketStats  GetStats(SOCKICPT_SIDE side = SOCKICPT_SIDE_BOTH,
			SOCKICPT_OPER oper = SOCKICPT_OPER_BOTH) const {
			SOCKICPT_SocketStats tmp_stats;
			return(GetStats(side, oper, tmp_stats));
		}
		SOCKICPT_SocketStats &GetStats(SOCKICPT_SIDE side, SOCKICPT_OPER oper,
			SOCKICPT_SocketStats &out_stats) const {
			out_stats = ((side == SOCKICPT_SIDE_NEAR) ?
				near_stats_.GetStats(oper) :
				((side == SOCKICPT_SIDE_FAR) ? far_stats_.GetStats(oper) :
				(near_stats_.GetStats(oper) + far_stats_.GetStats(oper))));
			return(out_stats);
		}

		SOCKICPT_Counter GetCount(SOCKICPT_SIDE side = SOCKICPT_SIDE_BOTH,
			SOCKICPT_OPER oper = SOCKICPT_OPER_BOTH) const {
			SOCKICPT_SocketStats tmp_stats;
			return(GetStats(side, oper, tmp_stats).GetCount());
		}
		SOCKICPT_Counter GetBytes(SOCKICPT_SIDE side = SOCKICPT_SIDE_BOTH,
			SOCKICPT_OPER oper = SOCKICPT_OPER_BOTH) const {
			SOCKICPT_SocketStats tmp_stats;
			return(GetStats(side, oper, tmp_stats).GetBytes());
		}

		double       GetAverage(SOCKICPT_SIDE side = SOCKICPT_SIDE_BOTH,
			SOCKICPT_OPER oper = SOCKICPT_OPER_BOTH) const {
			SOCKICPT_SocketStats tmp_stats;
			return(GetStats(side, oper, tmp_stats).GetAverage());
		}
		unsigned int GetMinimum(SOCKICPT_SIDE side = SOCKICPT_SIDE_BOTH,
			SOCKICPT_OPER oper = SOCKICPT_OPER_BOTH) const {
			SOCKICPT_SocketStats tmp_stats;
			return(GetStats(side, oper, tmp_stats).GetMinimum());
		}
		unsigned int GetMaximum(SOCKICPT_SIDE side = SOCKICPT_SIDE_BOTH,
			SOCKICPT_OPER oper = SOCKICPT_OPER_BOTH) const {
			SOCKICPT_SocketStats tmp_stats;
			return(GetStats(side, oper, tmp_stats).GetMaximum());
		}

		void AddStats(SOCKICPT_SIDE side,
			const SOCKICPT_SocketStatsSide &side_stats) {
			if (side == SOCKICPT_SIDE_NEAR)
				this->near_stats_ += side_stats;
			else if (side == SOCKICPT_SIDE_FAR)
				this->far_stats_ += side_stats;
		}

	private:

		SOCKICPT_SocketStatsSide near_stats_;
		SOCKICPT_SocketStatsSide far_stats_;
};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
const unsigned int SOCKICPT_PADDING_LEN         = sizeof(double);
const unsigned int SOCKICPT_DEFAULT_NETWORK_MTU = 1500;
const unsigned int SOCKICPT_DEFAULT_DATUM_SIZE  =
	sizeof(SOCKICPT_LOG_ENTRY_HEADER) + SOCKICPT_DEFAULT_NETWORK_MTU +
	(SOCKICPT_PADDING_LEN - 1);
const unsigned int SOCKICPT_DEFAULT_DATUM_COUNT = 1024;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
class SOCKICPT_HostPortSpec {

	public:

		SOCKICPT_HostPortSpec() :
			host_name_(), host_addr_(), port_name_(), port_number_() { }
		SOCKICPT_HostPortSpec(const char *host_name,
			const struct in_addr *host_addr, const char *port_name,
			int port_number) :
			host_name_(host_name), host_addr_(*host_addr), port_name_(port_name),
			port_number_(port_number) { }
		SOCKICPT_HostPortSpec(const SOCKICPT_HostPortSpec &other) {
			if (this != &other) {
				host_name_   = other.host_name_;
				host_addr_   = other.host_addr_;
				port_name_   = other.port_name_;
				port_number_ = other.port_number_;
			}
		}
		~SOCKICPT_HostPortSpec() { }

		std::string    host_name_;
		struct in_addr host_addr_;
		std::string    port_name_;
		int            port_number_;
};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static int SOCKICPT_GetLogNames(const char *log_dir, std::string &text_name,
	std::string &data_name, std::string *error_text = NULL);
static int SOCKICPT_GetLogNameBase(const char *log_dir,
	std::string &file_name_base, 	std::string *error_text = NULL);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
class SOCKICPT_Buffer {

	public:

		/*	***********************************************************
			***********************************************************
			***********************************************************	*/
		SOCKICPT_Buffer(unsigned int buffer_length) :
			buffer_length_(0), buffer_ptr_(NULL), data_length_(0), trans_id_() {
			buffer_length_ = (buffer_length) ? buffer_length :
				SOCKICPT_DEFAULT_DATUM_SIZE;
			buffer_ptr_    = ((char *) calloc(buffer_length_, sizeof(char)));
		}
		~SOCKICPT_Buffer() {
			if (buffer_ptr_ != NULL)
				free(buffer_ptr_);
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Get accessors . . .
			***********************************************************	*/
		unsigned int  GetBufferLength() const {
			return(buffer_length_);
		}
		char         *GetBufferPtr(unsigned int at_offset = 0) const {
			return((at_offset < buffer_length_) ? (buffer_ptr_ + at_offset) : NULL);
		}
		unsigned int  GetDataLength() const {
			return(data_length_);
		}
		SOCKICPT_TransId GetTransId() const {
			return(trans_id_);
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Set accessors . . .
			***********************************************************	*/
		bool SetDataLength(unsigned int data_length) {
			if (data_length <= buffer_length_) {
				data_length_ = data_length;
				return(true);
			}
			else
				return(false);
		}
		void SetTransId(const SOCKICPT_TransId &trans_id) {
			trans_id_ = trans_id;
		}
		/*	***********************************************************	*/

	private:

		/*	***********************************************************
			***********************************************************
			Data members . . .
			***********************************************************	*/
		unsigned int      buffer_length_;
		char             *buffer_ptr_;
		unsigned int      data_length_;
		SOCKICPT_TransId  trans_id_;
		/*	***********************************************************	*/
};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
class SOCKICPT_LogBuffer {

	public:

		SOCKICPT_LogBuffer(const struct timespec &action_time,
			SOCKICPT_OPER oper, SOCKICPT_SIDE side, struct in_addr near_addr,
			int near_port, struct in_addr far_addr, int far_port,
			unsigned int send_segment, bool release_buffer_flag,
			unsigned int data_length, unsigned int data_offset,
			SOCKICPT_Buffer *buffer_ptr) :
			action_time_(action_time), side_(side), oper_(oper),
			near_addr_(near_addr), near_port_(near_port), far_addr_(far_addr),
			far_port_(far_port), send_segment_(send_segment),
			release_buffer_flag_(release_buffer_flag), data_length_(data_length),
			data_offset_(data_offset), buffer_ptr_(buffer_ptr) { }
		SOCKICPT_LogBuffer() :
			action_time_(), side_(), oper_(), near_addr_(), near_port_(),
			far_addr_(), far_port_(), send_segment_(0),
			release_buffer_flag_(false), data_length_(0), data_offset_(0),
			buffer_ptr_(NULL) { }
		~SOCKICPT_LogBuffer() { }

		struct timespec   action_time_;
		SOCKICPT_OPER     oper_;
		SOCKICPT_SIDE     side_;
		struct in_addr    near_addr_;
		int               near_port_;
		struct in_addr    far_addr_;
		int               far_port_;
		unsigned int      send_segment_;
		bool              release_buffer_flag_;
		unsigned int      data_length_;
		unsigned int      data_offset_;
		SOCKICPT_Buffer  *buffer_ptr_;
};
/*	***********************************************************************	*/

typedef std::deque<SOCKICPT_Buffer *>
	SOCKICPT_BufferQueueBase;
typedef MLB::CPPSupp::STLSupp::deque_LC<SOCKICPT_Buffer *, MLB::MTIF::MtrO>
	SOCKICPT_BufferQueueType;
typedef MLB::CPPSupp::ScopedLockReader<SOCKICPT_BufferQueueType>
	SOCKICPT_ScopedLockR;
typedef MLB::CPPSupp::ScopedLockWriter<SOCKICPT_BufferQueueType>
	SOCKICPT_ScopedLockW;
/*	***********************************************************************	*/
class SOCKICPT_BufferQueue {

	public:

		/*	***********************************************************
			***********************************************************
			Constructors and destructors . . .
			***********************************************************	*/
		SOCKICPT_BufferQueue(unsigned int buffer_count = 0,
			unsigned int buffer_size = 0) :
			buffer_count_(buffer_count), buffer_size_(buffer_size),
			queue_data_(buffer_count_) {
			unsigned int count_1;
			for (count_1 = 0; count_1 < buffer_count_; count_1++)
				queue_data_[count_1] = new SOCKICPT_Buffer(buffer_size_);
		}
		~SOCKICPT_BufferQueue() {
			unsigned int count_1;
			for (count_1 = 0; count_1 < queue_data_.size(); count_1++) {
				if (queue_data_[count_1] != NULL) {
					delete queue_data_[count_1];
					queue_data_[count_1] = NULL;
				}
			}
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Buffer queue buffer management . . .
			***********************************************************	*/
		void             Add(SOCKICPT_Buffer *buffer_ptr) {
			if (buffer_ptr != NULL)
				queue_data_.Push_Back(buffer_ptr);
		}
		void             Add(SOCKICPT_BufferQueue &buffer_queue) {
			Add(buffer_queue.queue_data_);
		}
		void             Add(SOCKICPT_BufferQueueType &buffer_queue) {
			SOCKICPT_ScopedLockW in_lock(buffer_queue);
			Add(buffer_queue.GetDataRef());
		}
		void             Add(SOCKICPT_BufferQueueBase &buffer_queue) {
			SOCKICPT_ScopedLockW my_lock(queue_data_);
			queue_data_.insert(queue_data_.end(), buffer_queue.begin(),
				buffer_queue.end());
			buffer_queue.clear();
		}
		SOCKICPT_Buffer *Remove() {
			SOCKICPT_Buffer *buffer_ptr = NULL;
			return((queue_data_.PopFrontWithGet(buffer_ptr)) ? buffer_ptr : NULL);
		}
		unsigned int     GetQueueCount() const {
			return(queue_data_.Size());
		}
		unsigned int     GetBufferSize() const {
			return(buffer_size_);
		}
		/*	***********************************************************	*/

	private:

		/*	***********************************************************
			***********************************************************
			Data members . . .
			***********************************************************	*/
		unsigned int                     buffer_count_;
		unsigned int                     buffer_size_;
		mutable SOCKICPT_BufferQueueType queue_data_;
		/*	***********************************************************	*/
};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
class SOCKICPT_FreeList : public SOCKICPT_BufferQueue {

	public:

		/*	***********************************************************
			***********************************************************
			Constructors and destructors . . .
			***********************************************************	*/
		SOCKICPT_FreeList(
			unsigned int buffer_count = SOCKICPT_DEFAULT_DATUM_COUNT,
			unsigned int buffer_size = SOCKICPT_DEFAULT_DATUM_SIZE) :
			SOCKICPT_BufferQueue(buffer_count, buffer_size) {
		}
		~SOCKICPT_FreeList() { }
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Gets a buffer. First attempts to get one from the top of the
			free list buffer queue. If that fails, creates a new buffer.
			***********************************************************	*/
		SOCKICPT_Buffer *GetBuffer() {
			SOCKICPT_Buffer *buffer_ptr;
			if ((buffer_ptr  = Remove()) == NULL)
				buffer_ptr = new SOCKICPT_Buffer(GetBufferSize());
			return(buffer_ptr);
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Releases buffers into the free list . . .
			***********************************************************	*/
		void ReleaseBuffer(SOCKICPT_Buffer *buffer_ptr) {
			SOCKICPT_BufferQueue::Add(buffer_ptr);
		}
		void ReleaseBuffer(SOCKICPT_BufferQueue &buffer_queue) {
			SOCKICPT_BufferQueue::Add(buffer_queue);
		}
		void ReleaseBuffer(SOCKICPT_BufferQueueType &buffer_queue) {
			SOCKICPT_BufferQueue::Add(buffer_queue);
		}
		void ReleaseBuffer(SOCKICPT_BufferQueueBase &buffer_queue) {
			SOCKICPT_BufferQueue::Add(buffer_queue);
		}
		/*	***********************************************************	*/
};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
class SOCKICPT_Logger {

	public:

		/*	***********************************************************
			***********************************************************
			Constructors and destructors . . .
			***********************************************************	*/
		SOCKICPT_Logger(MFILE *mfile_ptr = NULL,
			SOCKICPT_FreeList *free_list_ptr = NULL) :
				mfile_ptr_(mfile_ptr), my_mfile_ptr_(NULL), queue_data_(),
				free_list_ptr_(free_list_ptr) { }
		~SOCKICPT_Logger() {
			queue_data_.LockWriter();
			mfile_ptr_ = NULL;
			queue_data_.Clear();
			if (my_mfile_ptr_ != NULL) {
				mclose(my_mfile_ptr_);
				my_mfile_ptr_ = NULL;
			}
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Log buffer queue buffer management . . .
			***********************************************************	*/
		void         AddRecvToLog(const struct timespec &action_time,
			SOCKICPT_SIDE side, struct in_addr near_addr,
			int near_port, struct in_addr far_addr, int far_port,
			bool release_buffer_flag, unsigned int data_length,
			unsigned int data_offset, SOCKICPT_Buffer *buffer_ptr) {
			AddToLog(action_time, SOCKICPT_OPER_RECV, side, near_addr, near_port,
				far_addr, far_port, 0, release_buffer_flag, data_length,
				data_offset, buffer_ptr);
		}
		void         AddSendToLog(const struct timespec &action_time,
			SOCKICPT_SIDE side, struct in_addr near_addr,
			int near_port, struct in_addr far_addr, int far_port,
			unsigned int send_segment, bool release_buffer_flag,
			unsigned int data_length, unsigned int data_offset,
			SOCKICPT_Buffer *buffer_ptr) {
			AddToLog(action_time, SOCKICPT_OPER_SEND, side, near_addr, near_port,
				far_addr, far_port, send_segment, release_buffer_flag, data_length,
				data_offset, buffer_ptr);
		}
		unsigned int GetQueueCount() const {
			return(queue_data_.Size());
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			***********************************************************	*/
		int Open(MLogO *mlogo_ptr, const char *log_dir,
			const std::string &file_name, std::string *error_text = NULL) {
			return(Open(mlogo_ptr, log_dir, file_name.c_str(), error_text));
		}
		int Open(MLogO *mlogo_ptr, const char *log_dir,
			const char *file_name = NULL, std::string *error_text = NULL) {
			int         return_code = SOCKICPT_SUCCESS;
			std::string file_name_base;
			std::string data_name;
			char        gen_error_text[GENFUNCS_MAX_ERROR_TEXT];

			mlogo_data_ = *mlogo_ptr;

			if (mfile_ptr_ != NULL) {
				if (error_text != NULL)
					*error_text = "Log file is already open.";
				return_code = SOCKICPT_FAILURE;
			}
			else if ((file_name == NULL) && ((return_code =
				SOCKICPT_GetLogNameBase(log_dir, file_name_base, error_text)) ==
				SOCKICPT_SUCCESS)) {
				data_name = file_name_base + "DATA.log";
				file_name = data_name.c_str();
			}

			if (return_code == SOCKICPT_SUCCESS) {
				if ((my_mfile_ptr_ = mopen(file_name, "wb")) != NULL) {
					mlogo_data_.LogInfo("Opened data log file '%s'.\n", file_name);
					mfile_ptr_  = my_mfile_ptr_;
					return_code = SOCKICPT_SUCCESS;
				}
				else {
					std::ostringstream o_str;
					if (error_text != NULL) {
						o_str << "Unable to open SOCKICPT data log file '" <<
							file_name << "' for writing: " <<
							GEN_GetLastErrorString(0, GENFUNCS_MAX_ERROR_TEXT,
							gen_error_text);
						*error_text = o_str.str();
					}
					return_code = SOCKICPT_FAILURE;
				}
			}

			return(return_code);
		}
		/*	***********************************************************	*/

	private:

		void LogItem() {
			SOCKICPT_LogBuffer        log_buffer;
			SOCKICPT_LOG_ENTRY_HEADER log_header;
			unsigned int              data_length;
			char                      padding_string[SOCKICPT_PADDING_LEN];
			unsigned int              padding_length;

			if (mfile_ptr_ == NULL) {
				if (Remove(log_buffer) && log_buffer.release_buffer_flag_)
					free_list_ptr_->Add(log_buffer.buffer_ptr_);
			}
			else if (Remove(log_buffer)) {
				data_length    = log_buffer.data_length_;
				padding_length = (data_length % SOCKICPT_PADDING_LEN) ?
					(SOCKICPT_PADDING_LEN - (data_length % SOCKICPT_PADDING_LEN)) :
					0;
				if (padding_length)
					memset(padding_string, '\0', padding_length);
				memset(&log_header, '\0', sizeof(log_header));
				log_header.total_length  = sizeof(log_header) +
					data_length + padding_length;
				log_header.this_offset   = mtell(mfile_ptr_);
				log_header.next_offset   = log_header.this_offset +
					log_header.total_length;
				log_header.action_time   = log_buffer.action_time_;
				log_header.oper          = log_buffer.oper_;
				log_header.side          = log_buffer.side_;
				log_header.near_addr     = log_buffer.near_addr_;
				log_header.near_port     = log_buffer.near_port_;
				log_header.far_addr      = log_buffer.far_addr_;
				log_header.far_port      = log_buffer.far_port_;
				log_header.trans_id      = log_buffer.buffer_ptr_->GetTransId();
				log_header.send_segment  = log_buffer.send_segment_;
				log_header.data_length   = data_length;
				SDTIF_GetTimeNSecs(&log_header.log_time);
				mwrite(&log_header, sizeof(log_header), 1, mfile_ptr_);
				mwrite(log_buffer.buffer_ptr_->GetBufferPtr(log_buffer.data_offset_),
					data_length, 1, mfile_ptr_);
				if (padding_length)
					mwrite(padding_string, padding_length, 1, mfile_ptr_);
				if (log_buffer.release_buffer_flag_)
					free_list_ptr_->Add(log_buffer.buffer_ptr_);
			}
		}

		bool Remove(SOCKICPT_LogBuffer &log_buffer) const {
			return(queue_data_.PopFrontWithGet(log_buffer));
		}

		void         AddToLog(const struct timespec &action_time,
			SOCKICPT_OPER oper, SOCKICPT_SIDE side, struct in_addr near_addr,
			int near_port, struct in_addr far_addr, int far_port,
			unsigned int send_segment, bool release_buffer_flag,
			unsigned int data_length, unsigned int data_offset,
			SOCKICPT_Buffer *buffer_ptr) {
			SOCKICPT_LogBuffer tmp_log_buffer(action_time, oper, side, near_addr,
				near_port, far_addr, far_port, send_segment, release_buffer_flag,
				data_length, data_offset, buffer_ptr);
			queue_data_.Push_Back(tmp_log_buffer);
LogItem();
		}

		/*	***********************************************************
			***********************************************************
			Data members . . .
			***********************************************************	*/
		MFILE                                    *mfile_ptr_;
		MFILE                                    *my_mfile_ptr_;
		MLogO                                     mlogo_data_;
		SOCKICPT_FreeList                        *free_list_ptr_;
		mutable MLB::CPPSupp::STLSupp::deque_LC
			<SOCKICPT_LogBuffer, MLB::MTIF::MtrO>  queue_data_;
		/*	***********************************************************	*/
};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
class SOCKICPT_Control {

	public:

		SOCKICPT_Control() :
			near_host_ptr_(NULL), far_host_ptr_(NULL), buffer_count_(0),
			buffer_size_(0), free_list_ptr_(NULL), mlogo_ptr_(NULL),
			mlogo_data_(), logger_ptr_(NULL), log_detail_flag_(false),
			trans_id_(), conn_stats_() { }
		~SOCKICPT_Control() {
			LogStats();
			delete logger_ptr_;
			delete mlogo_ptr_;
			delete near_host_ptr_;
			delete far_host_ptr_;
			delete free_list_ptr_;
		}

		int Create(const SOCKICPT_HostPortSpec &near_host,
			const SOCKICPT_HostPortSpec &far_host, bool no_log_flag = false,
			bool debug_flag = false, bool log_detail_flag = false,
			const char *log_dir = NULL,
			unsigned int buffer_count = SOCKICPT_DEFAULT_DATUM_SIZE,
			unsigned int buffer_size = SOCKICPT_DEFAULT_DATUM_COUNT,
			std::string *error_text = NULL) {

			int         return_code = SOCKICPT_SUCCESS;
			std::string text_log_name;
			std::string data_log_name;

			near_host_ptr_   = new SOCKICPT_HostPortSpec(near_host);
			far_host_ptr_    = new SOCKICPT_HostPortSpec(far_host);
			buffer_count_    = buffer_count;
			buffer_size_     = buffer_size;
			free_list_ptr_   = new SOCKICPT_FreeList(buffer_count, buffer_size);
			log_detail_flag_ = log_detail_flag;

			if ((!no_log_flag) && ((return_code = SOCKICPT_GetLogNames(log_dir,
				text_log_name, data_log_name, error_text)) == EXIT_SUCCESS)) {
				mlogo_ptr_   = new MLogO(text_log_name, false, true);
				mlogo_data_  = *mlogo_ptr_;
				mlogo_data_.SetPDebug(debug_flag);
				mlogo_data_.DoSepStart();
				logger_ptr_  = new SOCKICPT_Logger(NULL, free_list_ptr_);
				return_code  = logger_ptr_->Open(mlogo_ptr_, log_dir, data_log_name,
					error_text);
			}

			return(return_code);
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Forwarding functions to get buffers from and release buffers
			to the free list . . .
			***********************************************************	*/
		SOCKICPT_Buffer *GetBuffer() {
			return((free_list_ptr_ != NULL) ? free_list_ptr_->GetBuffer() : NULL);
		}
		void ReleaseBuffer(SOCKICPT_Buffer *buffer_ptr) {
			if (free_list_ptr_ != NULL)
				free_list_ptr_->Add(buffer_ptr);
		}
		void ReleaseBuffer(SOCKICPT_BufferQueue &buffer_queue) {
			if (free_list_ptr_ != NULL)
				free_list_ptr_->Add(buffer_queue);
		}
		void ReleaseBuffer(SOCKICPT_BufferQueueType &buffer_queue) {
			if (free_list_ptr_ != NULL)
				free_list_ptr_->Add(buffer_queue);
		}
		void ReleaseBuffer(SOCKICPT_BufferQueueBase &buffer_queue) {
			if (free_list_ptr_ != NULL)
				free_list_ptr_->Add(buffer_queue);
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Log buffer queue buffer management . . .
			***********************************************************	*/
		void AddRecvToLog(const struct timespec &action_time,
			SOCKICPT_SIDE side, struct in_addr near_addr,
			int near_port, struct in_addr far_addr, int far_port,
			bool release_buffer_flag, unsigned int data_length,
			unsigned int data_offset, SOCKICPT_Buffer *buffer_ptr) {
			if (logger_ptr_ != NULL)
				logger_ptr_->AddRecvToLog(action_time, side, near_addr, near_port,
					far_addr, far_port, release_buffer_flag, data_length,
					data_offset, buffer_ptr);
			else if (release_buffer_flag)
				ReleaseBuffer(buffer_ptr);
		}
		void AddSendToLog(const struct timespec &action_time,
			SOCKICPT_SIDE side, struct in_addr near_addr,
			int near_port, struct in_addr far_addr, int far_port,
			unsigned int send_segment, bool release_buffer_flag,
			unsigned int data_length, unsigned int data_offset,
			SOCKICPT_Buffer *buffer_ptr) {
			if (logger_ptr_ != NULL)
				logger_ptr_->AddSendToLog(action_time, side, near_addr, near_port,
					far_addr, far_port, send_segment, release_buffer_flag,
					data_length, data_offset, buffer_ptr);
			else if (release_buffer_flag)
				ReleaseBuffer(buffer_ptr);
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Gets a new transaction identifier . . .
			***********************************************************	*/
/*
	CODE NOTE: Must add locking to this to ensure thread-safety.
*/
		SOCKICPT_TransId RequestTransId() {
			return(trans_id_++);
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Forwarding functions to handle detailed test logging . . .
			***********************************************************	*/
		bool DetailLogIsOn() const {
			return(log_detail_flag_);
		}
#ifdef __GNUC__
		int LogDetail(const char *in_format, ...);
			__attribute__ ((format (printf, 1, 2))) const {
#else
		int LogDetail(const char *in_format, ...) const {
#endif /* #ifdef __GNUC__ */
			int     return_code;
			va_list arg_list;

			if (mlogo_data_.GetCanAndMayLog() == true) {
				va_start(arg_list, in_format);
				return_code = LogDetailVA(in_format, arg_list);
				va_end(arg_list);
			}
			else
				return_code = MLOG_SUCCESS;

			return(return_code);
		}
		int LogDetail(const std::string &in_string) const {
			return(LogDetail("%s\n", in_string.c_str()));
		}
		int LogDetail(const std::ostringstream &in_stream) const {
			return(LogDetail(in_stream.str()));
		}
		int LogDetailVA(const char *in_format, va_list arg_list) const {
			return((mlogo_data_.GetCanAndMayLog() == true) ?
				mlogo_data_.LogIfVA(log_detail_flag_, in_format, arg_list) :
				MLOG_SUCCESS);
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Forwarding functions to add per-connection statistics to the
			total statistics data . . .
			***********************************************************	*/
/*
	CODE NOTE: Must add locking to this to ensure thread-safety.
*/
		void AddStats(SOCKICPT_SIDE side,
			const SOCKICPT_SocketStatsSide &side_stats) {
			conn_stats_.AddStats(side, side_stats);
		}
		/*	***********************************************************	*/

		const MLogO           &GetMLogO() const { return(mlogo_data_); }
		SOCKICPT_HostPortSpec &GetNearHost() const { return(*near_host_ptr_); }
		SOCKICPT_HostPortSpec &GetFarHost() const { return(*far_host_ptr_); }

		unsigned long          GetWakeUpUSecs() const {
			return(SOCKICPT_WAKEUP_USECS);
		}
		struct timeval        *GetWakeUpUSecs(struct timeval &time_val) const {
			SDTIF_SET_TIMEVAL(&time_val, SOCKICPT_WAKEUP_USECS / 1000000L,
				SOCKICPT_WAKEUP_USECS % 1000000L);
			return(&time_val);
		}

	private:

		/*	***********************************************************
			***********************************************************
			Socket statistics reporting . . .
			***********************************************************	*/
		void LogStats() const {
			char               buffer[127 + 1];
			std::ostringstream format_string;

			nstrset(buffer, '-', sizeof(buffer) - 1);
			format_string << "%-16.16s " << SOCKICPT_CounterPrintfFormat << " " <<
				SOCKICPT_CounterPrintfFormat << " %10u %10u %20.6f\n";

			mlogo_data_.DoSepEqual();
			mlogo_data_.DoSepEqual();
			mlogo_data_.LogInfo("Socket Statistics Report\n");
			mlogo_data_.DoSepEqual();

			mlogo_data_.LogInfo(
				"%-16.16s %-20.20s %-20.20s %-10.10s %-10.10s %-20.20s\n",
				"Stat Type", "Action Count", "Total Bytes", "Min Bytes",
				"Max Bytes", "Average Bytes");
			mlogo_data_.LogInfo(
				"%-16.16s %-20.20s %-20.20s %-10.10s %-10.10s %-20.20s\n",
				buffer, buffer, buffer, buffer, buffer, buffer);

			LogStatsLine(format_string, "Near Recv Stats",
				SOCKICPT_SIDE_NEAR, SOCKICPT_OPER_RECV);
			LogStatsLine(format_string, "Near Send Stats",
				SOCKICPT_SIDE_NEAR, SOCKICPT_OPER_SEND);
			LogStatsLine(format_string, "Far Recv Stats",
				SOCKICPT_SIDE_FAR, SOCKICPT_OPER_RECV);
			LogStatsLine(format_string, "Far Send Stats",
				SOCKICPT_SIDE_FAR, SOCKICPT_OPER_SEND);
			LogStatsLine(format_string, "All Near Stats",
				SOCKICPT_SIDE_NEAR, SOCKICPT_OPER_BOTH);
			LogStatsLine(format_string, "All Far Stats",
				SOCKICPT_SIDE_FAR, SOCKICPT_OPER_BOTH);
			LogStatsLine(format_string, "All Recv Stats",
				SOCKICPT_SIDE_BOTH, SOCKICPT_OPER_RECV);
			LogStatsLine(format_string, "All Send Stats",
				SOCKICPT_SIDE_BOTH, SOCKICPT_OPER_SEND);

			mlogo_data_.LogInfo(
				"%-16.16s %-20.20s %-20.20s %-10.10s %-10.10s %-20.20s\n",
				buffer, buffer, buffer, buffer, buffer, buffer);

			LogStatsLine(format_string, "Cumulative Stats",
				SOCKICPT_SIDE_BOTH, SOCKICPT_OPER_BOTH);

			mlogo_data_.DoSepEqual();
		}
		void LogStatsLine(const std::ostringstream &format_string,
			const char *stats_name, SOCKICPT_SIDE side, SOCKICPT_OPER oper) const {
			mlogo_data_.LogInfo(format_string.str().c_str(),
				stats_name,
				conn_stats_.GetCount(side, oper),
				conn_stats_.GetBytes(side, oper),
				conn_stats_.GetMinimum(side, oper),
				conn_stats_.GetMaximum(side, oper),
				conn_stats_.GetAverage(side, oper));
		}
		/*	***********************************************************	*/

		SOCKICPT_HostPortSpec    *near_host_ptr_;
		SOCKICPT_HostPortSpec    *far_host_ptr_;
		unsigned int              buffer_count_;
		unsigned int              buffer_size_;
		SOCKICPT_FreeList        *free_list_ptr_;
		MLogO                    *mlogo_ptr_;
		MLogO                     mlogo_data_;
		SOCKICPT_Logger          *logger_ptr_;
		bool                      log_detail_flag_;
		SOCKICPT_TransId          trans_id_;
		SOCKICPT_SocketStatsConn  conn_stats_;
};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
typedef struct {
	NPSL_SOCKET_HANDLE  client_socket_handle;
	NPSL_SOCKADDR       client_name;
	NPSL_SOCKLEN_T      client_addrlen;
	struct in_addr      client_socket_addr;
	int                 client_port;
	SOCKICPT_Control   *control_ptr;
} SOCKICPT_ThreadData;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
       int   main(int argc, char **argv);
static int   SOCKICPT_StartServer(SOCKICPT_Control *control_ptr,
	std::string &error_text);
static void *SOCKICPT_DoClientThread(SOCKICPT_ThreadData *thread_data_ptr);
std::string &SOCKICPT_GetConnString(const char *host_name,
	const struct in_addr &host_addr, int spec_port, const int *real_port,
	std::string &conn_string);
static int   SOCKICPT_ParamNear(unsigned int argv_index, char **argv,
	SOCKICPT_HostPortSpec **out_host_ptr, std::string &error_text);
static int   SOCKICPT_ParamFar(unsigned int argv_index, char **argv,
	SOCKICPT_HostPortSpec **out_host_ptr, std::string &error_text);
static int   SOCKICPT_ParamPort(const char *arg_name, const char *arg_value,
	const char *port_string, int &out_port, std::string &error_text);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(void SOCKICPT_SignalSet, (void));
COMPAT_FN_DECL_STATIC(void SOCKICPT_SignalDefault, (void));
#ifdef __MSDOS__
COMPAT_FN_DECL_STATIC(void SOCKICPT_SignalHandler,
	(int signal_number));
#elif _Windows
COMPAT_FN_DECL_STATIC(void SOCKICPT_SignalHandler,
	(int signal_number));
#elif _MSC_VER
COMPAT_FN_DECL_STATIC(void SOCKICPT_SignalHandler,
	(int signal_number));
#else
# ifdef __SVR4
COMPAT_FN_DECL_STATIC(void SOCKICPT_SignalHandler,
	(int signal_number, siginfo_t *siginfo_ptr, void *signal_address));
# else
COMPAT_FN_DECL_STATIC(void SOCKICPT_SignalHandler,
	(int signal_number, signal_code, struct sigcontext *signal_context,
	char *signal_address));
# endif /* # ifdef __SVR4 */
#endif /* ifdef __MSDOS__ */
/*	***********************************************************************	*/

#include <pcff.h>

/*	***********************************************************************	*/
int main(int argc, char **argv)
{
	int                    return_code     = SOCKICPT_SUCCESS;
	bool                   socket_lib_open = false;
	SOCKICPT_HostPortSpec *near_ptr        = NULL;
	SOCKICPT_HostPortSpec *far_ptr         = NULL;
	const char            *log_dir_ptr     = NULL;
	const char            *no_log_ptr      = NULL;
	unsigned int           buffer_count    = SOCKICPT_DEFAULT_DATUM_COUNT;
	unsigned int           buffer_size     = SOCKICPT_DEFAULT_DATUM_SIZE;
	char                  *log_dir         = NULL;
	bool                   no_log_flag     = false;
	bool                   log_debug_flag  = false;
	bool                   log_detail_flag = false;
	SOCKICPT_Control      *control_ptr     = NULL;
	unsigned int           count_1;
	std::string            text_log_name;
	std::string            data_log_name;
	std::ostringstream     o_str;
	std::string            error_text;
	char                   npsl_error_text[NPSL_MAX_ERROR_TEXT];
	char                   pcff_error_text[PCFF_MAX_ERROR_TEXT];

	/*	*****************************************************************
		*****************************************************************
		First, scan the command line parameters for a help request . . .
		*****************************************************************	*/
	if (PCFF_CMLPARAM_LocateHelp(argc, argv, NULL)) {
		std::cerr << std::endl << std::endl << "USAGE:" << std::endl <<
			"   " << extract_file_name(argv[0]) <<
			"[ -h | -help ] " <<
			"-near <port-number> " <<
			"-far [<host-name-or-IP-address>:]<port-number> " <<
			"[ -buffer_count <initial-buffer-count> ] " <<
			"[ -buffer_size <size-of-each-buffer> ] " <<
			"[ -log_dir <log-file-directory> ] " <<
			"[ -no_log ] " <<
			"[ -debug ] " <<
			"[ -detail ]" <<
			std::endl << std::endl;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Now scan the command line parameters to pick up the parameters . . .
		*****************************************************************	*/
	for (count_1 = 1; count_1 < ((unsigned int) argc); ++count_1) {
		if (!stricmp(argv[count_1], "-near")) {
			if (PCFF_CMLPARAM_Check(argc, count_1, argv, (near_ptr != NULL),
				pcff_error_text) != PCFF_SUCCESS) {
				error_text  = pcff_error_text;
				return_code = SOCKICPT_BAD_ARGS_FAILURE;
				goto EXIT_FUNCTION;
			}
			else if ((return_code = SOCKICPT_ParamNear(count_1, argv, &near_ptr,
				error_text)) != SOCKICPT_SUCCESS)
				goto EXIT_FUNCTION;
			++count_1;
		}
		else if (!stricmp(argv[count_1], "-far")) {
			if (PCFF_CMLPARAM_Check(argc, count_1, argv, (far_ptr != NULL),
				pcff_error_text) != PCFF_SUCCESS) {
				error_text  = pcff_error_text;
				return_code = SOCKICPT_BAD_ARGS_FAILURE;
				goto EXIT_FUNCTION;
			}
			else if ((return_code = SOCKICPT_ParamFar(count_1, argv, &far_ptr,
				error_text)) != SOCKICPT_SUCCESS)
				goto EXIT_FUNCTION;
			++count_1;
		}
		else if (PCFF_CMLPARAM_FindVA(argv[count_1], NULL, "-buffer_count",
			"-buffercount", "-count", NULL)) {
			if (PCFF_CMLPARAM_GetFollowing(argc, count_1, argv,
				PCFF_FLD_TYPE_UINT, 0, NULL, pcff_error_text) != PCFF_SUCCESS) {
				error_text  = pcff_error_text;
				return_code = SOCKICPT_BAD_ARGS_FAILURE;
				goto EXIT_FUNCTION;
			}
			buffer_count = atoi(argv[++count_1]);
		}
		else if (PCFF_CMLPARAM_FindVA(argv[count_1], NULL, "-buffer_size",
			"-buffersize", "-size", NULL)) {
			if (PCFF_CMLPARAM_GetFollowing(argc, count_1, argv,
				PCFF_FLD_TYPE_UINT, 0, NULL, pcff_error_text) != PCFF_SUCCESS) {
				error_text  = pcff_error_text;
				return_code = SOCKICPT_BAD_ARGS_FAILURE;
				goto EXIT_FUNCTION;
			}
			buffer_size = atoi(argv[++count_1]);
		}
		else if (PCFF_CMLPARAM_FindVA(argv[count_1], NULL, "-logging_directory",
			"-loggingdirectory", "-log_directory", "-logdirectory", "-logging_dir", 
			"-loggingdir", "-log_dir", "-logdir", NULL)) {
			if (PCFF_CMLPARAM_GetFollowing(argc, count_1, argv,
				PCFF_FLD_TYPE_PATH_NAME, (log_dir != NULL), &log_dir,
				pcff_error_text) != PCFF_SUCCESS) {
				error_text  = pcff_error_text;
				return_code = SOCKICPT_BAD_ARGS_FAILURE;
				goto EXIT_FUNCTION;
			}
			else if (no_log_flag == true) {
				o_str << "Invalid command line encountered: both the '" <<
					no_log_ptr << "' parameter and the '" << argv[count_1] <<
					"'parameter were specified.";
				error_text  = o_str.str();
				return_code = SOCKICPT_FAILURE;
				goto EXIT_FUNCTION;
			}
			log_dir_ptr = argv[count_1++];
		}
		else if (PCFF_CMLPARAM_FindVA(argv[count_1], NULL, "-no_logging", 
			"-nologging", "-no_log", "-nolog", NULL)) {
			if (log_dir != NULL) {
				o_str << "Invalid command line encountered: both the '" <<
					log_dir << "' parameter and the '" << argv[count_1] <<
					"'parameter were specified.";
				error_text  = o_str.str();
				return_code = SOCKICPT_FAILURE;
				goto EXIT_FUNCTION;
			}
			no_log_flag = true;
			no_log_ptr  = argv[count_1];
		}
		else if (PCFF_CMLPARAM_FindVA(argv[count_1], NULL, "-log_debug", 
			"-log_dbg", "-log_debugging", "-logdebug", "-logdbg", "-logdebugging", 
			"-debug_logging", "-dbg_logging", "-debugging_logging",
			"-debuglogging", "-dbglogging", "-debugginglogging", "-debug_log", 
			"-dbg_log", "-debugging_log", "-debuglog", "-dbglog", "-debugginglog", 
			"-debug", "-dbg", "-debugging", NULL))
			log_debug_flag = true;
		else if (PCFF_CMLPARAM_FindVA(argv[count_1], NULL, "-log_detail", 
			"-logdetail", "-detail_logging", "-detaillogging", "-detail_log", 
			"-detaillog", "-detail", NULL))
			log_detail_flag = true;
		else {
			o_str << "Invalid command line parameter encountered ('" <<
				argv[count_1] << "') --- use '-h' for help.";
			error_text  = o_str.str();
			return_code = SOCKICPT_FAILURE;
			goto EXIT_FUNCTION;
		}
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Ensure that the required parameters have been specified . . .
		*****************************************************************	*/
	if ((near_ptr == NULL) || (far_ptr == NULL)) {
		o_str << "The required parameter '" <<
			((near_ptr == NULL) ? "-near" : "-far") <<
			"' was not specified on the command line --- use '-h' for help.";
		error_text  = o_str.str();
		return_code = SOCKICPT_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Ensure the socket library is started (needed for Win32) . . .
		*****************************************************************	*/
	if (NPSL_SocketLibStartUp(NULL, npsl_error_text) != NPSL_SUCCESS) {
		error_text  = npsl_error_text;
		return_code = SOCKICPT_FAILURE;
		goto EXIT_FUNCTION;
	}
	socket_lib_open = true;
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Synthesize the log file names . . .
		*****************************************************************	*/
	if ((no_log_flag == false) && ((return_code = SOCKICPT_GetLogNames(log_dir,
		text_log_name, data_log_name, &error_text)) != EXIT_SUCCESS))
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Create the control object . . .
		*****************************************************************	*/
	control_ptr = new SOCKICPT_Control();
	if ((return_code = control_ptr->Create(*near_ptr, *far_ptr, no_log_flag,
		log_debug_flag, log_detail_flag, log_dir, buffer_count, buffer_size,
		&error_text)) != SOCKICPT_SUCCESS)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	return_code = SOCKICPT_StartServer(control_ptr, error_text);

EXIT_FUNCTION:

	delete near_ptr;
	delete far_ptr;

	if (log_dir != NULL)
		free(log_dir);

	if ((control_ptr != NULL) && (return_code != SOCKICPT_SUCCESS))
		control_ptr->GetMLogO().LogErr(error_text);

	delete control_ptr;

	if (socket_lib_open)
		NPSL_SocketLibCleanUp(NULL, npsl_error_text);

	if (return_code != SOCKICPT_SUCCESS)
		std::cerr << std::endl << std::endl << "ERROR: " << error_text <<
			std::endl << std::endl;

	return((return_code == SOCKICPT_SUCCESS) ? EXIT_SUCCESS : EXIT_FAILURE);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static int SOCKICPT_StartServer(SOCKICPT_Control *control_ptr,
	std::string &error_text)
{
	int                    return_code          = SOCKICPT_SUCCESS;
	bool                   while_flag           = true;
	NPSL_SOCKET_HANDLE     socket_handle        = NPSL_INVALID_SOCKET;
	NPSL_SOCKET_HANDLE     client_socket_handle = NPSL_INVALID_SOCKET;
	SOCKICPT_ThreadData   *thread_data_ptr      = NULL;
	int                    npsl_code;
	unsigned int           count_1;
	SOCKICPT_HostPortSpec  near_host;
	NPSL_SOCKADDR_IN       this_address;
	NPSL_SOCKADDR_IN       client_address;
	NPSL_SOCKLEN_T         client_address_size;
	unsigned int           ready_fd_count;
	fd_set                 read_fd_set;
	struct timeval         time_out;
	NPSL_SOCKADDR          client_name;
	NPSL_SOCKLEN_T         client_addrlen;
	char                   inet_buffer[NPSL_MAX_IPV4_ADDR_STR + 1];
	char                   npsl_error_text[NPSL_MAX_ERROR_TEXT];
	char                   mtif_error_text[MTIF_MAX_ERROR_TEXT];

	near_host = control_ptr->GetNearHost();

	if (NPSL_Socket(AF_INET, SOCK_STREAM, 0, &socket_handle, npsl_error_text) !=
		NPSL_SUCCESS) {
		error_text   = "Unable to create SOCKICPT server socket: ";
		error_text  += npsl_error_text;
		return_code  = SOCKICPT_FAILURE;
		goto EXIT_FUNCTION;
	}

	memset(&this_address, '\0', sizeof(this_address));

	this_address.sin_family      = AF_INET;
	this_address.sin_port        = htons(((unsigned short) near_host.port_number_));
	this_address.sin_addr.s_addr = INADDR_ANY;

	if (NPSL_Bind(socket_handle, ((const NPSL_SOCKADDR *) &this_address),
		sizeof(NPSL_SOCKADDR), npsl_error_text) != NPSL_SUCCESS) {
		NPSL_CloseSocket(socket_handle, NULL);
		socket_handle  = NPSL_INVALID_SOCKET;
		error_text     = "Unable to bind SOCKICPT server socket: ";
		error_text    += npsl_error_text;
		return_code    = SOCKICPT_FAILURE;
		goto EXIT_FUNCTION;
	}

	if (NPSL_Listen(socket_handle, 10, npsl_error_text) != NPSL_SUCCESS) {
		NPSL_CloseSocket(socket_handle, NULL);
		socket_handle  = NPSL_INVALID_SOCKET;
		error_text     = "Unable to start listen on SOCKICPT server socket: ";
		error_text    += npsl_error_text;
		return_code    = SOCKICPT_FAILURE;
		goto EXIT_FUNCTION;
	}

	control_ptr->GetMLogO().DoSepEqual();
	control_ptr->GetMLogO().LogInfo("Started SOCKICPT server on port %d.\n",
		near_host.port_number_);
	control_ptr->GetMLogO().DoSepEqual();

	SOCKICPT_SignalSet();					// We catch signals within the loop . . .

	while (while_flag) {
		FD_ZERO(&read_fd_set);
#ifdef _MSC_VER
# pragma warning(disable:4127)
#endif /* # ifdef _MSC_VER */
		FD_SET(socket_handle, &read_fd_set);
#ifdef _MSC_VER
# pragma warning(default:4127)
#endif /* # ifdef _MSC_VER */
		control_ptr->GetWakeUpUSecs(time_out);
//		SOCKICPT_WAKEUP_USECS_SET(&time_out);
//		SDTIF_SET_TIMEVAL(&time_out, 0L, 100000L);
		if (NPSL_Select(socket_handle + 1, &read_fd_set, NULL, NULL, &time_out,
			&ready_fd_count, npsl_error_text) != NPSL_SUCCESS) {
			error_text  = npsl_error_text;
			return_code = SOCKICPT_FAILURE;
			goto EXIT_FUNCTION;
		}
		else if (ready_fd_count) {
			client_address_size = sizeof(client_address);
			NPSL_SetBlockingModeOff(socket_handle, NULL);
			if ((npsl_code = NPSL_Accept(socket_handle, &client_socket_handle,
				((NPSL_SOCKADDR *) &client_address), &client_address_size,
				npsl_error_text)) == NPSL_EWOULDBLOCK) {
				NPSL_SetBlockingModeOn(socket_handle, NULL);
				continue;
			}
			else if (npsl_code != NPSL_SUCCESS) {
				error_text  = npsl_error_text;
				return_code = SOCKICPT_FAILURE;
				goto EXIT_FUNCTION;
			}
			NPSL_SetBlockingModeOn(socket_handle, NULL);
			if (MTIF_RWL_GetDataSInt(&SOCKICPT_ExitFlag) != 0)
				break;
			client_addrlen = sizeof(client_name);
			if (NPSL_GetPeerName(client_socket_handle, &client_name,
				&client_addrlen, npsl_error_text) != NPSL_SUCCESS) {
				control_ptr->GetMLogO().LogWarn("%s %d failed: %s\n",
					"Attempt to accept connection on port", near_host.port_number_,
					npsl_error_text);
			}
			else if ((thread_data_ptr = new SOCKICPT_ThreadData()) == NULL) {
				error_text  = "Unable to allocate the client handler thread data.";
				return_code = SOCKICPT_FAILURE;
				goto EXIT_FUNCTION;
			}
			else {
				thread_data_ptr->client_socket_handle = client_socket_handle;
				thread_data_ptr->client_name          = client_name;
				thread_data_ptr->client_addrlen       = client_addrlen;
				thread_data_ptr->client_socket_addr   =
					((struct sockaddr_in *) &client_name)->sin_addr;
				thread_data_ptr->client_port          =
					ntohs(((struct sockaddr_in *) &client_name)->sin_port);
				thread_data_ptr->control_ptr          = control_ptr;
				control_ptr->GetMLogO().LogInfo("%s %d from %s, port %d.\n",
					"Accepted connection on port", near_host.port_number_,
					NPSL_AddrStructToINet(&thread_data_ptr->client_socket_addr,
					inet_buffer), thread_data_ptr->client_port);
				if (MTIF_THR_Create(MTIF_THR_FLAG_DETACHED, 0,
					((MTIF_THR_StartFunc) SOCKICPT_DoClientThread), thread_data_ptr,
					NULL, mtif_error_text) == MTIF_SUCCESS)
					client_socket_handle = NPSL_INVALID_SOCKET;
				else {
					delete thread_data_ptr;
					error_text   = "Unable to start client handler thread: ";
					error_text  += npsl_error_text;
					return_code  = SOCKICPT_FAILURE;
					goto EXIT_FUNCTION;
				}
			}
			if (client_socket_handle != NPSL_INVALID_SOCKET) {
				NPSL_ShutDown(client_socket_handle, NPSL_SHUTDOWN_FLAG_BOTH,
					npsl_error_text);
				NPSL_CloseSocket(client_socket_handle, npsl_error_text);
				client_socket_handle = NPSL_INVALID_SOCKET;
			}
		}
		if (MTIF_RWL_GetDataSInt(&SOCKICPT_ExitFlag) != 0)
			break;
	}

EXIT_FUNCTION:

	MTIF_RWL_SetDataSInt(&SOCKICPT_ExitFlag, -1);

	SOCKICPT_SignalDefault();				// Signals once again kill . . .

	control_ptr->GetMLogO().LogInfo(
		"Shutting-down SOCKICPT server on port %d.\n", near_host.port_number_);

	if (socket_handle != NPSL_INVALID_SOCKET)
		NPSL_CloseSocket(socket_handle, NULL);

	for (count_1 = 0; count_1 < 10; count_1++)
		SDTIF_usleep(control_ptr->GetWakeUpUSecs());
//		SDTIF_usleep(SOCKICPT_WAKEUP_USECS);
//		SDTIF_usleep(100000L);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
class SOCKICPT_Connection {

	public:

		SOCKICPT_Connection(SOCKICPT_Control *control_ptr,
			std::string side_string, NPSL_SOCKET_HANDLE socket_handle,
			SOCKICPT_SIDE side, struct in_addr &near_addr, int near_port,
			struct in_addr &far_addr, int far_port) :
			control_ptr_(control_ptr), side_string_(side_string),
			socket_handle_(socket_handle), side_(side), near_addr_(near_addr),
			near_port_(near_port), far_addr_(far_addr), far_port_(far_port),
			recv_buffer_ptr_(NULL), recv_length_(0), send_buffer_ptr_(NULL),
			send_length_(0), send_offset_(0), send_segment_(0), send_queue_(),
			correspondent_ptr_(NULL), side_stats_() {
			this_addr_ = (side == SOCKICPT_SIDE_NEAR) ? near_addr_ : far_addr_;
			this_port_ = (side == SOCKICPT_SIDE_NEAR) ? near_port_ : far_port_;
		}
		~SOCKICPT_Connection() {
			if (send_queue_.size() || (send_buffer_ptr_ != NULL)) {
				control_ptr_->GetMLogO().LogWarn("A total of %u %s %s (%s) %s.\n",
					send_queue_.size() + ((send_buffer_ptr_ != NULL) ? 1 : 0),
					"enqueued messages pending for sending to the",
					(side_ == SOCKICPT_SIDE_NEAR) ? "near-side" : "far-side",
					side_string_.c_str(), "will be discarded");
				if (send_queue_.size())
					control_ptr_->ReleaseBuffer(send_queue_);
			}
			if (recv_buffer_ptr_ != NULL)
				control_ptr_->ReleaseBuffer(recv_buffer_ptr_);
			if (send_buffer_ptr_ != NULL)
				control_ptr_->ReleaseBuffer(send_buffer_ptr_);
		}

		bool IsValid() const {
			return(socket_handle_ != NPSL_INVALID_SOCKET);
		}

		void SetCorrespondent(SOCKICPT_Connection *correspondent_ptr) {
			correspondent_ptr_ = correspondent_ptr;
		}

		void SetFD(fd_set &recv_fd_set, fd_set &send_fd_set) {
#ifdef _MSC_VER
# pragma warning(disable:4127)
#endif /* # ifdef _MSC_VER */
			if (socket_handle_ != NPSL_INVALID_SOCKET) {
				FD_SET(socket_handle_, &recv_fd_set);
				if (GetSendBuffer())
					FD_SET(socket_handle_, &send_fd_set);
			}
#ifdef _MSC_VER
# pragma warning(default:4127)
#endif /* # ifdef _MSC_VER */
		}

		void ClearCorrespondent() {
			correspondent_ptr_ = NULL;
		}

		void ClearSocket() {
			socket_handle_ = NPSL_INVALID_SOCKET;
		}

		int RecvBuffer(fd_set &recv_fd_set) {
			unsigned int    recv_bytes;
			int             npsl_code;
			struct timespec action_time;
			char            inet_buffer[NPSL_MAX_IPV4_ADDR_STR + 1];
			char            npsl_error_text[NPSL_MAX_ERROR_TEXT];

			if (socket_handle_ == NPSL_INVALID_SOCKET)
				return(SOCKICPT_SUCCESS);
			if (!FD_ISSET(socket_handle_, &recv_fd_set))
				return(SOCKICPT_SUCCESS);
			GetRecvBuffer();
			NPSL_SetBlockingModeOff(socket_handle_, NULL);
			if ((npsl_code = NPSL_Recv(socket_handle_,
				recv_buffer_ptr_->GetBufferPtr(),
				recv_buffer_ptr_->GetBufferLength(), 0, &recv_bytes,
				npsl_error_text)) != NPSL_SUCCESS) {
				NPSL_SetBlockingModeOn(socket_handle_, NULL);
				if (npsl_code == NPSL_EWOULDBLOCK)
					return(SOCKICPT_SUCCESS);
				control_ptr_->GetMLogO().LogWarn("%s %lu (%s %s, %s %d): %s\n",
					"Error occurred on 'read()' attempt for socket",
					((unsigned long) socket_handle_),
					"IP address", NPSL_AddrStructToINet(&this_addr_, inet_buffer),
					"port number", this_port_, npsl_error_text);
				if (correspondent_ptr_ != NULL)
					control_ptr_->GetMLogO().LogWarn("%s (%s) %s %u %s.\n",
						"The other",
						(side_ == SOCKICPT_SIDE_NEAR) ? "far" : "near",
						"has a total of",
						correspondent_ptr_->send_queue_.size() +
						((correspondent_ptr_->send_buffer_ptr_ != NULL) ? 1 : 0),
						"messages enqueued for sending");
				Invalidate();
				return(SOCKICPT_FAILURE);
			}
			NPSL_SetBlockingModeOn(socket_handle_, NULL);
			if (recv_bytes) {
				SDTIF_GetTimeNSecs(&action_time);
				recv_buffer_ptr_->SetDataLength(recv_bytes);
				recv_buffer_ptr_->SetTransId(control_ptr_->RequestTransId());
				if (control_ptr_->DetailLogIsOn())
					control_ptr_->LogDetail("%s %u byte%s %s %lu (%s %s, %s %d).\n",
						"Received", recv_bytes, (recv_bytes != 1) ? "s" : "",
						"on socket", ((unsigned long) socket_handle_),
						"IP address", NPSL_AddrStructToINet(&this_addr_, inet_buffer),
						"port number", this_port_);
				if (correspondent_ptr_ != NULL) {
					control_ptr_->AddRecvToLog(action_time, side_, near_addr_,
						near_port_, far_addr_, far_port_, false,
						recv_buffer_ptr_->GetDataLength(), 0, recv_buffer_ptr_);
					correspondent_ptr_->send_queue_.push_back(recv_buffer_ptr_);
				}
				else
					control_ptr_->AddRecvToLog(action_time, side_, near_addr_,
						near_port_, far_addr_, far_port_, true,
						recv_buffer_ptr_->GetDataLength(), 0, recv_buffer_ptr_);
				recv_buffer_ptr_ = NULL;
				side_stats_.AddActionRecv(recv_bytes);
			}
			else {
				control_ptr_->GetMLogO().LogWarn("%s %lu (%s %s, %s %d): %s.\n",
					"Connection broken on socket", ((unsigned long) socket_handle_),
					"IP address", NPSL_AddrStructToINet(&this_addr_, inet_buffer),
					"port number", this_port_, "'read()' attempt returned 0");
				Invalidate();
				return(SOCKICPT_FAILURE);
			}
			return(SOCKICPT_SUCCESS);
		}

		int SendBuffer(fd_set &send_fd_set) {
			unsigned int    send_bytes;
			unsigned int    sent_offset;
			int             npsl_code;
			struct timespec action_time;
			char            inet_buffer[NPSL_MAX_IPV4_ADDR_STR + 1];
			char            npsl_error_text[NPSL_MAX_ERROR_TEXT];

			if (socket_handle_ == NPSL_INVALID_SOCKET)
				return(SOCKICPT_SUCCESS);
			if ((!GetSendBuffer()) || (!FD_ISSET(socket_handle_, &send_fd_set)))
				return(SOCKICPT_SUCCESS);

			NPSL_SetBlockingModeOff(socket_handle_, NULL);
			if ((npsl_code = NPSL_Send(socket_handle_,
				send_buffer_ptr_->GetBufferPtr(send_offset_), send_length_, 0,
				&send_bytes, npsl_error_text)) != NPSL_SUCCESS) {
				NPSL_SetBlockingModeOn(socket_handle_, NULL);
				if (npsl_code == NPSL_EWOULDBLOCK)
					return(SOCKICPT_SUCCESS);
				control_ptr_->GetMLogO().LogWarn("%s %lu (%s %s, %s %d): %s\n",
					"Error occurred on 'send()' attempt for socket",
					((unsigned long) socket_handle_),
					"IP address", NPSL_AddrStructToINet(&this_addr_, inet_buffer),
					"port number", this_port_, npsl_error_text);
				Invalidate();
				return(SOCKICPT_FAILURE);
			}
			NPSL_SetBlockingModeOn(socket_handle_, NULL);
			if (send_bytes) {
				SDTIF_GetTimeNSecs(&action_time);
				sent_offset   = send_offset_;
				send_offset_ += send_bytes;
				send_length_ -= send_bytes;
				if (control_ptr_->DetailLogIsOn())
					control_ptr_->LogDetail("%s %u byte%s %s %lu (%s %s, %s %d).\n",
						"Sent", send_bytes, (send_bytes != 1) ? "s" : "",
						"on socket", ((unsigned long) socket_handle_),
						"IP address", NPSL_AddrStructToINet(&this_addr_, inet_buffer),
						"port number", this_port_);
				if (send_length_)
					control_ptr_->AddSendToLog(action_time, side_, near_addr_,
						near_port_, far_addr_, far_port_, send_segment_++, false,
						send_bytes, sent_offset, send_buffer_ptr_);
				else {
					control_ptr_->AddSendToLog(action_time, side_, near_addr_,
						near_port_, far_addr_, far_port_, send_segment_, true,
						send_bytes, sent_offset, send_buffer_ptr_);
					send_buffer_ptr_ = NULL;
				}
				side_stats_.AddActionSend(send_bytes);
			}

			return(SOCKICPT_SUCCESS);
		}

		void AddStats() const {
			control_ptr_->AddStats(side_, side_stats_);
		}

	private:

		void GetRecvBuffer() {
			if (recv_buffer_ptr_ == NULL)
				recv_buffer_ptr_ = control_ptr_->GetBuffer();
			recv_buffer_ptr_->SetDataLength(0);
		}
		bool GetSendBuffer() {
			if (send_buffer_ptr_ == NULL) {
				send_length_     = 0;
				send_offset_     = 0;
				send_segment_    = 0;
				if (send_queue_.size()) {
					send_buffer_ptr_ = send_queue_[0];
					send_length_     = send_buffer_ptr_->GetDataLength();
					send_queue_.pop_front();
				}
				else if (correspondent_ptr_ == NULL)
					Invalidate();
			}
			return(send_buffer_ptr_ != NULL);
		}
		void Invalidate() {
			socket_handle_ = NPSL_INVALID_SOCKET;
			if (correspondent_ptr_ != NULL)
				correspondent_ptr_->ClearCorrespondent();
		}

		SOCKICPT_Control         *control_ptr_;
		std::string               side_string_;
		NPSL_SOCKET_HANDLE        socket_handle_;
		SOCKICPT_SIDE             side_;
		struct in_addr            near_addr_;
		int                       near_port_;
		struct in_addr            far_addr_;
		int                       far_port_;
		SOCKICPT_Buffer          *recv_buffer_ptr_;
		unsigned int              recv_length_;
		SOCKICPT_Buffer          *send_buffer_ptr_;
		unsigned int              send_length_;
		unsigned int              send_offset_;
		unsigned int              send_segment_;
		SOCKICPT_BufferQueueBase  send_queue_;
		SOCKICPT_Connection      *correspondent_ptr_;
		SOCKICPT_SocketStatsSide  side_stats_;
		struct in_addr            this_addr_;
		int                       this_port_;
};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static void *SOCKICPT_DoClientThread(SOCKICPT_ThreadData *thread_data_ptr)
{
	SOCKICPT_Control      *control_ptr       = thread_data_ptr->control_ptr;
	NPSL_SOCKET_HANDLE     far_socket_handle = NPSL_INVALID_SOCKET;
	bool                   conn_ok           = false;
	SOCKICPT_Connection   *near_conn_ptr     = NULL;
	SOCKICPT_Connection   *far_conn_ptr      = NULL;
	NPSL_SOCKET_HANDLE     max_socket_handle;
	NPSL_SOCKADDR_IN       far_addr;
	SOCKICPT_HostPortSpec  far_host;
	int                    far_port;
	std::string            near_string;
	std::string            far_string;
	std::ostringstream     o_str_1;
	std::ostringstream     o_str_2;
	NPSL_SOCKADDR          client_name;
	NPSL_SOCKLEN_T         client_addrlen;
	unsigned int           ready_fd_count;
	fd_set                 recv_fd_set;
	fd_set                 send_fd_set;
	struct timeval         time_out;
	char                   npsl_error_text[NPSL_MAX_ERROR_TEXT];

	far_host = control_ptr->GetFarHost();

	SOCKICPT_GetConnString(NULL, thread_data_ptr->client_socket_addr,
		control_ptr->GetNearHost().port_number_, &thread_data_ptr->client_port,
		near_string);

	SOCKICPT_GetConnString(far_host.host_name_.c_str(), far_host.host_addr_,
		far_host.port_number_, NULL, far_string);

	control_ptr->GetMLogO().LogPDebug("%s %s.\n",
		"Started near-side connection thread for", near_string.c_str());

	if (NPSL_Socket(AF_INET, SOCK_STREAM, 0, &far_socket_handle,
		npsl_error_text) != NPSL_SUCCESS) {
		control_ptr->GetMLogO().LogErr("%s %s %s (%s): %s\n",
			"Near-side connection thread for", near_string.c_str(),
			"failed to open far-side", far_string.c_str(), npsl_error_text);
		goto EXIT_FUNCTION;
	}

	if (MTIF_RWL_GetDataSInt(&SOCKICPT_ExitFlag) != 0)
		goto EXIT_FUNCTION;

	memset(&far_addr, '\0', sizeof(far_addr));

	far_addr.sin_family = AF_INET;
	far_addr.sin_port   = htons(((unsigned short) far_host.port_number_));
	far_addr.sin_addr   =
		*((struct in_addr *) ((void *) &far_host.host_addr_));

	if (NPSL_Connect(far_socket_handle, ((const NPSL_SOCKADDR *) &far_addr),
		sizeof(NPSL_SOCKADDR), npsl_error_text) != NPSL_SUCCESS) {
		control_ptr->GetMLogO().LogErr("%s %s %s (%s): %s\n",
			"Near-side connection thread for", near_string.c_str(),
			"failed to open far-side", far_string.c_str(), npsl_error_text);
		goto EXIT_FUNCTION;
	}

	conn_ok = true;

	if (MTIF_RWL_GetDataSInt(&SOCKICPT_ExitFlag) != 0)
		goto EXIT_FUNCTION;

	client_addrlen = sizeof(client_name);
	if (NPSL_GetPeerName(far_socket_handle, &client_name,
		&client_addrlen, npsl_error_text) != NPSL_SUCCESS) {
		control_ptr->GetMLogO().LogErr("%s %s %s (%s): %s\n",
			"Near-side connection thread for", near_string.c_str(),
			"failed to open far-side", far_string.c_str(), npsl_error_text);
		goto EXIT_FUNCTION;
	}

	if (MTIF_RWL_GetDataSInt(&SOCKICPT_ExitFlag) != 0)
		goto EXIT_FUNCTION;

	far_port = ntohs(((struct sockaddr_in *) &client_name)->sin_port);
	SOCKICPT_GetConnString(far_host.host_name_.c_str(), far_host.host_addr_,
		far_host.port_number_, &far_port, far_string);

	control_ptr->GetMLogO().LogInfo("%s %s %s %s.\n",
		"Near-side connection for", near_string.c_str(),
		"is connected to its corresponding far-side", far_string.c_str());

	max_socket_handle = std::max(thread_data_ptr->client_socket_handle,
		far_socket_handle);

	near_conn_ptr = new SOCKICPT_Connection(control_ptr, near_string,
		thread_data_ptr->client_socket_handle, SOCKICPT_SIDE_NEAR,
		thread_data_ptr->client_socket_addr, thread_data_ptr->client_port,
		far_host.host_addr_, far_port);
	far_conn_ptr  = new SOCKICPT_Connection(control_ptr, far_string,
		far_socket_handle, SOCKICPT_SIDE_FAR,
		thread_data_ptr->client_socket_addr, thread_data_ptr->client_port,
		far_host.host_addr_, far_port);

	near_conn_ptr->SetCorrespondent(far_conn_ptr);
	far_conn_ptr->SetCorrespondent(near_conn_ptr);

	while (near_conn_ptr->IsValid() || far_conn_ptr->IsValid()) {
		FD_ZERO(&recv_fd_set);
		FD_ZERO(&send_fd_set);
		near_conn_ptr->SetFD(recv_fd_set, send_fd_set);
		far_conn_ptr->SetFD(recv_fd_set, send_fd_set);
		control_ptr->GetWakeUpUSecs(time_out);
		if (NPSL_Select(max_socket_handle + 1, &recv_fd_set, &send_fd_set, NULL,
			&time_out, &ready_fd_count, npsl_error_text) != NPSL_SUCCESS) {
			control_ptr->GetMLogO().LogErr("%s %s, %s %s %s: %s\n",
				"Near-side connection thread for", near_string.c_str(),
				"far-side", far_string.c_str(), "failed on 'select()'",
				npsl_error_text);
			goto EXIT_FUNCTION;
		}
		if (MTIF_RWL_GetDataSInt(&SOCKICPT_ExitFlag) != 0)
			break;
		if (ready_fd_count) {
			near_conn_ptr->RecvBuffer(recv_fd_set);
			far_conn_ptr->RecvBuffer(recv_fd_set);
			near_conn_ptr->SendBuffer(send_fd_set);
			far_conn_ptr->SendBuffer(send_fd_set);
			if (MTIF_RWL_GetDataSInt(&SOCKICPT_ExitFlag) != 0)
				break;
		}
	}

	near_conn_ptr->AddStats();
	far_conn_ptr->AddStats();

EXIT_FUNCTION:

	if (conn_ok) {
		control_ptr->GetMLogO().LogPDebug("%s %s %s (%s).\n",
			"Shutting-down near-side", near_string.c_str(),
			"far-side socket connection", far_string.c_str());
		NPSL_ShutDown(far_socket_handle, NPSL_SHUTDOWN_FLAG_BOTH,
			npsl_error_text);
	}

	if (far_socket_handle != NPSL_INVALID_SOCKET) {
		control_ptr->GetMLogO().LogPDebug("%s %s %s (%s).\n",
			"Closing near-side", near_string.c_str(),
			"far-side socket connection", far_string.c_str());
		NPSL_CloseSocket(far_socket_handle, npsl_error_text);
	}

	control_ptr->GetMLogO().LogPDebug("%s %s.\n",
		"Shutting-down near-side socket connection", near_string.c_str());
	NPSL_ShutDown(thread_data_ptr->client_socket_handle, NPSL_SHUTDOWN_FLAG_BOTH,
		npsl_error_text);
	control_ptr->GetMLogO().LogPDebug("%s %s.\n",
		"Closing near-side socket connection", near_string.c_str());
	NPSL_CloseSocket(thread_data_ptr->client_socket_handle, npsl_error_text);

	control_ptr->GetMLogO().LogInfo("%s %s.\n",
		"Exiting connection thread for", near_string.c_str());

	delete near_conn_ptr;
	delete far_conn_ptr;
	delete thread_data_ptr;

	return(NULL);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
std::string &SOCKICPT_GetConnString(const char *host_name,
	const struct in_addr &host_addr, int spec_port, const int *real_port,
	std::string &conn_string)
{
	char               inet_buffer[NPSL_MAX_IPV4_ADDR_STR + 1];
	std::ostringstream o_str;

	if ((host_name != NULL) && (!isdigit(*host_name)))
		o_str << "host name '" << host_name << "'=";

	o_str << "IP address " << 
		NPSL_AddrStructToINet(&host_addr, inet_buffer) <<
		", port number " << spec_port;

	if (real_port != NULL)
		o_str << "=" << *real_port;

	conn_string = o_str.str();

	return(conn_string);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static void SOCKICPT_SignalSet()
{
#ifdef __MSDOS__
	signal(SIGINT,    SOCKICPT_SignalHandler);
	signal(SIGTERM,   SOCKICPT_SignalHandler);
#elif _Windows
	signal(SIGINT,    SOCKICPT_SignalHandler);
	signal(SIGTERM,   SOCKICPT_SignalHandler);
#elif _MSC_VER
	signal(SIGINT,    SOCKICPT_SignalHandler);
	signal(SIGTERM,   SOCKICPT_SignalHandler);
#elif __SVR4
	signal(SIGHUP,    SIG_IGN);
	signal(SIGINT,    ((void (*)(int)) SOCKICPT_SignalHandler));
	signal(SIGQUIT,   SIG_IGN);
	signal(SIGPIPE,   SIG_IGN);
	signal(SIGALRM,   SIG_IGN);
	signal(SIGTERM,   ((void (*)(int)) SOCKICPT_SignalHandler));
	signal(SIGXCPU,   SIG_IGN);
	signal(SIGXFSZ,   SIG_IGN);
	signal(SIGVTALRM, SIG_IGN);
	signal(SIGUSR1,   SIG_IGN);
	signal(SIGUSR2,   SIG_IGN);
#else
	signal(SIGHUP,    SIG_IGN);
	signal(SIGINT,    SOCKICPT_SignalHandler);
	signal(SIGQUIT,   SIG_IGN);
	signal(SIGPIPE,   SIG_IGN);
	signal(SIGALRM,   SIG_IGN);
	signal(SIGTERM,   SOCKICPT_SignalHandler);
	signal(SIGXCPU,   SIG_IGN);
	signal(SIGXFSZ,   SIG_IGN);
	signal(SIGVTALRM, SIG_IGN);
	signal(SIGUSR1,   SIG_IGN);
	signal(SIGUSR2,   SIG_IGN);
#endif /* #ifdef __MSDOS__ */
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void SOCKICPT_SignalDefault(void)
#else
void SOCKICPT_SignalDefault()
#endif /* #ifndef NARGS */
{
#ifdef __MSDOS__
	signal(SIGINT,    SIG_DFL);
	signal(SIGTERM,   SIG_DFL);
#elif _Windows
	signal(SIGINT,    SIG_DFL);
	signal(SIGTERM,   SIG_DFL);
#elif _MSC_VER
	signal(SIGINT,    SIG_DFL);
	signal(SIGTERM,   SIG_DFL);
#else
	signal(SIGHUP,    SIG_DFL);
	signal(SIGINT,    SIG_DFL);
	signal(SIGQUIT,   SIG_DFL);
	signal(SIGPIPE,   SIG_DFL);
	signal(SIGALRM,   SIG_DFL);
	signal(SIGTERM,   SIG_DFL);
	signal(SIGXCPU,   SIG_DFL);
	signal(SIGXFSZ,   SIG_DFL);
	signal(SIGVTALRM, SIG_DFL);
	signal(SIGUSR1,   SIG_DFL);
	signal(SIGUSR2,   SIG_DFL);
#endif /* #ifdef __MSDOS__ */
}
/*	***********************************************************************	*/

/* *********************************************************************** */
#ifdef __MSDOS__
static void SOCKICPT_SignalHandler(int signal_number)
#elif _Windows
static void SOCKICPT_SignalHandler(int signal_number)
#elif _MSC_VER
static void SOCKICPT_SignalHandler(int signal_number)
#else
# ifdef __SVR4
static void SOCKICPT_SignalHandler(int signal_number, siginfo_t *siginfo_ptr,
	void *signal_address)
# else
static void SOCKICPT_SignalHandler(int signal_number, signal_code,
	struct sigcontext *signal_context, char *signal_address)
# endif /* # ifdef __SVR4 */
#endif /* ifdef __MSDOS__ */
{
	if ((signal_number == SIGINT) || (signal_number == SIGTERM)) {
		MTIF_RWL_SetDataSInt(&SOCKICPT_ExitFlag, -1);
		SOCKICPT_SignalSet();
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static int SOCKICPT_ParamNear(unsigned int argv_index, char **argv,
	SOCKICPT_HostPortSpec **out_host_ptr, std::string &error_text)
{
	int                 return_code;
	std::ostringstream  o_str;
	int                 tmp_port;
	NPSL_HOSTENT        hent_data;
	char                buffer[8192];
	char                npsl_error_text[NPSL_MAX_ERROR_TEXT];

	*out_host_ptr = NULL;

	if (NPSL_GetHostByString("localhost", &hent_data, buffer, sizeof(buffer),
		npsl_error_text) == NPSL_SUCCESS) {
		if ((return_code = SOCKICPT_ParamPort(argv[argv_index],
			argv[argv_index + 1], argv[argv_index + 1], tmp_port, error_text)) ==
			SOCKICPT_SUCCESS)
			*out_host_ptr = new SOCKICPT_HostPortSpec(hent_data.h_name,
				((struct in_addr *) hent_data.h_addr_list[0]), argv[argv_index + 1],
				tmp_port);
	}
	else {
		o_str << "Invalid '" << argv[argv_index] <<
			"' parameter encountered on the command line ('" <<
			argv[argv_index + 1] << "'): the host specification ('" <<
			"localhost" << "') could not be resolved: " << npsl_error_text;
		error_text  = o_str.str();
		return_code = SOCKICPT_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static int SOCKICPT_ParamFar(unsigned int argv_index, char **argv,
	SOCKICPT_HostPortSpec **out_host_ptr, std::string &error_text)
{
	int                 return_code;
	std::string         host_string;
	const char         *port_ptr;
	std::ostringstream  o_str;
	int                 tmp_port;
	NPSL_HOSTENT        hent_data;
	char                buffer[8192];
	char                npsl_error_text[NPSL_MAX_ERROR_TEXT];

	*out_host_ptr = NULL;

	if ((port_ptr = strchr(argv[argv_index + 1], ':')) != NULL) {
		if (port_ptr == argv[argv_index + 1]) {
			o_str << "Invalid '" << argv[argv_index] <<
				"' parameter encountered on the command line ('" <<
				argv[argv_index + 1] << "'): the host specification is empty.";
			error_text  = o_str.str();
			return_code = SOCKICPT_FAILURE;
		}
		else {
			host_string = std::string(argv[argv_index + 1],
				((unsigned int) (port_ptr - argv[argv_index + 1])));
			if (NPSL_GetHostByString(host_string.c_str(), &hent_data, buffer,
				sizeof(buffer), npsl_error_text) == NPSL_SUCCESS) {
				if ((return_code = SOCKICPT_ParamPort(argv[argv_index],
					argv[argv_index + 1], port_ptr + 1, tmp_port, error_text)) ==
					SOCKICPT_SUCCESS)
					*out_host_ptr = new SOCKICPT_HostPortSpec(hent_data.h_name,
						((struct in_addr *) hent_data.h_addr_list[0]), port_ptr + 1,
						tmp_port);
			}
			else {
				o_str << "Invalid '" << argv[argv_index] <<
					"' parameter encountered on the command line ('" <<
					argv[argv_index + 1] << "'): the host specification ('" <<
					host_string << "') could not be resolved: " << npsl_error_text;
				error_text  = o_str.str();
				return_code = SOCKICPT_FAILURE;
			}
		}
	}
	else
		return_code = SOCKICPT_ParamNear(argv_index, argv, out_host_ptr,
			error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static int SOCKICPT_ParamPort(const char *arg_name, const char *arg_value,
	const char *port_string, int &out_port, std::string &error_text)
{
	int                return_code;
	char               npsl_error_text[NPSL_MAX_ERROR_TEXT];
	std::ostringstream o_str;

	if (!(*port_string)) {
		o_str << "Invalid '" << arg_name <<
			"' parameter encountered on the command line ('" << arg_value <<
			"'): the service specification ('" << port_string << "') is empty.";
		error_text  = o_str.str();
		return_code = SOCKICPT_FAILURE;
	}
	else if (NPSL_ResolveServToPort(port_string, isdigit(*port_string) ? NULL :
		"tcp", &out_port, npsl_error_text) != NPSL_SUCCESS) {
		o_str << "Invalid '" << arg_name <<
			"' parameter encountered on the command line ('" << arg_value <<
			"'): the service specification ('" << port_string <<
			"') could not be resolved: " << npsl_error_text;
		error_text  = o_str.str();
		return_code = SOCKICPT_FAILURE;
	}
	else
		return_code = SOCKICPT_SUCCESS;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static int SOCKICPT_GetLogNames(const char *log_dir, std::string &text_name,
	std::string &data_name, std::string *error_text)
{
	int         return_code;
	std::string file_name_base;

	if ((return_code = SOCKICPT_GetLogNameBase(log_dir, file_name_base,
		error_text)) == SOCKICPT_SUCCESS) {
		text_name = file_name_base + "TEXT.log";
		data_name = file_name_base + "DATA.log";
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static int SOCKICPT_GetLogNameBase(const char *log_dir,
	std::string &file_name_base, std::string *error_text)
{
	int  return_code;
	char host_name[GEN_MAX_HOST_NAME_LEN + 1];
	char date_buffer[SDTIF_FMT_TIME_LEN_TIMEVAL + 1];
	char gen_error_text[GENFUNCS_MAX_ERROR_TEXT];

	if (GEN_DetermineHostName(host_name, gen_error_text) == GENFUNCS_SUCCESS) {
		std::ostringstream o_str;
		SDTIF_Format_timeval(NULL, date_buffer);
		date_buffer[10] = '.';
		date_buffer[13] = '.';
		date_buffer[16] = '.';
		log_dir         = (log_dir != NULL) ? log_dir : ".";
		o_str << log_dir << "/" << date_buffer << ".SockICPT.LOG." <<
			host_name << MTIF_THR_SelfProcess() << ".";
		file_name_base = o_str.str();
		return_code    = SOCKICPT_SUCCESS;
	}
	else {
		if (error_text != NULL)
			*error_text = gen_error_text;
		return_code = SOCKICPT_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/



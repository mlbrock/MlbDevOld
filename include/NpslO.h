//	//////////////////////////////////////////////////////////////////////////
//	//////////////////////////////////////////////////////////////////////////
//	Network Programming Support Library (NPSL) Source Module
//	//////////////////////////////////////////////////////////////////////////
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for object-based NPSL support.

	Revision History	:	2002-01-26 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 2002 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
//	//////////////////////////////////////////////////////////////////////////

#ifndef HH__MLB__NpslO__NpslO_h__HH

#define HH__MLB__NpslO__NpslO_h__HH		1

//	//////////////////////////////////////////////////////////////////////////
//	//////////////////////////////////////////////////////////////////////////
//	Include necessary header files . . .
//	//////////////////////////////////////////////////////////////////////////

#include <mbcompat.h>

#ifdef _Windows
# pragma warning(disable:4710 4786)
# if _MSC_VER >= 1300
#  pragma warning(disable:4217 4251 4555)
# endif // # if _MSC_VER >= 1300
# pragma warning(disable:4018 4100 4146 4244 4245 4511 4512 4663)
# pragma warning(disable:4663)
# include <limits>
# if _MSC_VER >= 1300
#  pragma warning(default:4217 4251 4555)
# endif // # if _MSC_VER >= 1300
# pragma warning(default:4018 4100 4146 4244 4245 4511 4512 4663)
#else
# include <limits>
#endif // #ifdef _Windows

#include "ExceptionGeneral.h"
#include "NonCopyable.h"
 
#include "npsl.h"

//	//////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace NpslO {

//	//////////////////////////////////////////////////////////////////////////
enum AddressFamily {
	AddressFamily_NONE      = AF_UNSPEC,
	AddressFamily_Unix      = AF_UNIX,
	AddressFamily_Internet  = AF_INET,
	AddressFamily_Implink   = AF_IMPLINK,
	AddressFamily_Pup       = AF_PUP,
	AddressFamily_Chaos     = AF_CHAOS,
	AddressFamily_Ns        = AF_NS,
	AddressFamily_Ipx       = AF_IPX,
	AddressFamily_Iso       = AF_ISO,
	AddressFamily_Osi       = AF_OSI,
	AddressFamily_Ecma      = AF_ECMA,
	AddressFamily_Datakit   = AF_DATAKIT,
	AddressFamily_Ccitt     = AF_CCITT,
	AddressFamily_Sna       = AF_SNA,
	AddressFamily_Decnet    = AF_DECnet,
	AddressFamily_Dli       = AF_DLI,
	AddressFamily_Lat       = AF_LAT,
	AddressFamily_Hylink    = AF_HYLINK,
	AddressFamily_Appletalk = AF_APPLETALK,
	AddressFamily_Netbios   = AF_NETBIOS,
	AddressFamily_Voiceview = AF_VOICEVIEW,
	AddressFamily_Firefox   = AF_FIREFOX,
	AddressFamily_Unknown1  = AF_UNKNOWN1,
	AddressFamily_Ban       = AF_BAN,
//	AddressFamily_Atm       = AF_ATM,
//	AddressFamily_Inet6     = AF_INET6,
//	AddressFamily_Cluster   = AF_CLUSTER,
//	AddressFamily_12844     = AF_12844,
	AddressFamily_DEFAULT   = AF_INET
};
//	//////////////////////////////////////////////////////////////////////////

//	//////////////////////////////////////////////////////////////////////////
enum SocketType {
	SocketType_Stream     = SOCK_STREAM,
	SocketType_DataGram   = SOCK_DGRAM,
	SocketType_Raw        = SOCK_RAW,
	SocketType_RDM        = SOCK_RDM,
	SocketType_SseqPacket = SOCK_SEQPACKET,
	SocketType_DEFAULT    = SOCK_STREAM
};
//	//////////////////////////////////////////////////////////////////////////

//	//////////////////////////////////////////////////////////////////////////
enum ProtocolType {
	ProtocolType_DEFAULT = 0
};
//	//////////////////////////////////////////////////////////////////////////

//	//////////////////////////////////////////////////////////////////////////
template <class CharType = char> class ExceptionNpslType :
	public MLB::CPPSupp::ExceptionGeneralType<CharType> {
	private:
		typedef MLB::CPPSupp::ExceptionGeneralType<CharType> ParentNick;
	public:
		ExceptionNpslType() throw() :
			MLB::CPPSupp::ExceptionGeneralType("Unknown exception."),
			error_code(GetLastSocketLibErrorCode()) { }
		ExceptionNpslType(int in_error_code) throw() :
			MLB::CPPSupp::ExceptionGeneralType<CharType>(),
			error_code(in_error_code) { }
		ExceptionNpslType(const CharType *in_except_string) throw() :
			MLB::CPPSupp::ExceptionGeneralType<CharType>(in_except_string),
			error_code(GetLastSocketLibErrorCode()) { }
		ExceptionNpslType(const ThisStringType &in_except_string) throw() :
			MLB::CPPSupp::ExceptionGeneralType<CharType>(in_except_string),
			error_code(GetLastSocketLibErrorCode()) { }
		ExceptionNpslType(const ThisOStreamType &in_except_string) throw() :
			MLB::CPPSupp::ExceptionGeneralType<CharType>(in_except_string),
			error_code(GetLastSocketLibErrorCode()) { }
		~ExceptionNpslType() throw() { }

		int GetErrorCode() {
			return(error_code);
		}

	private:

		static int GetLastSocketLibErrorCode() {
#ifdef _Windows
			return(WSAGetLastError());
#else
# include <errno.h>
			return(errno);	
#endif // #ifdef _Windows
		}

		int error_code;
};
//	//////////////////////////////////////////////////////////////////////////

//	//////////////////////////////////////////////////////////////////////////
typedef ExceptionNpslType<char> ExceptionNpsl;
//	//////////////////////////////////////////////////////////////////////////

//	//////////////////////////////////////////////////////////////////////////
template <class CharType = char> class ExceptionNpslTimeOutType :
	public ExceptionNpslType<CharType> {
	private:
		typedef ExceptionNpslType<CharType> ParentNick;
	public:
		ExceptionNpslTimeOutType() throw() :
			ExceptionNpslType() { }
		ExceptionNpslTimeOutType(const struct timeval *time_out_ptr) throw() :
			ExceptionNpslType<CharType>(FormatError(NULL, time_out_ptr)) { }
		ExceptionNpslTimeOutType(const CharType *in_except_string,
			const struct timeval *time_out_ptr = NULL) throw() :
			ExceptionNpslType<CharType>(FormatError(in_except_string,
			time_out_ptr)) { }
		ExceptionNpslTimeOutType(const ThisStringType &in_except_string,
			const struct timeval *time_out_ptr = NULL) throw() :
			ExceptionNpslType<CharType>(FormatError(in_except_string.c_str(),
			time_out_ptr)) { }
		ExceptionNpslTimeOutType(const ThisOStreamType &in_except_string,
			const struct timeval *time_out_ptr = NULL) throw() :
			ExceptionNpslType<CharType>(FormatError(in_except_string.str().c_str(),
			time_out_ptr)) { }
		~ExceptionNpslTimeOutType() throw() { }

	private:

		std::string FormatError(const char *error_text = NULL,
			const struct timeval *time_out_ptr = NULL) {
			char               buffer[SDTIF_FMTI_TIME_LEN_TIMEVAL + 1];
			std::ostringstream error_string;
			error_string << "NPSL select() time-out occurred for time-out " <<
				((time_out_ptr == NULL) ? "(time-out period unspecified)" :
				SDTIF_FormatInterval_timeval(time_out_ptr, buffer)) << ": " <<
				(((error_text != NULL) && (*error_text)) ? error_text :
				"(further exception description not available).");
			return(error_string.str());
		}
};
//	//////////////////////////////////////////////////////////////////////////

//	//////////////////////////////////////////////////////////////////////////
typedef ExceptionNpslTimeOutType<char> ExceptionNpslTimeOut;
//	//////////////////////////////////////////////////////////////////////////

//	//////////////////////////////////////////////////////////////////////////
class SocketLib {
	public:
		SocketLib() : is_initilized(false) {
			char npsl_error_text[NPSL_MAX_ERROR_TEXT];
			if (NPSL_SocketLibStartUp(NULL, npsl_error_text) != NPSL_SUCCESS)
//				throw MLB::CPPSupp::ExceptionGeneral(npsl_error_text);
				throw ExceptionNpsl(npsl_error_text);
			is_initilized = true;
		}
		~SocketLib() {
			is_initilized = false;
			NPSL_SocketLibCleanUp(NULL, NULL);
		}

		bool IsReady() const { return(is_initilized); }
		void EnsureReady()
			const MBCOMPAT_EXCEPT_CANTHROW(ExceptionNpsl) {
			if (!IsReady())
				throw ExceptionNpsl(
					"Socket library not yet initialized.");
		}

		static unsigned int Select(NPSL_SOCKET_HANDLE socket_handle,
			NPSL_FD_SET_T *read_fd_set, NPSL_FD_SET_T *write_fd_set,
			NPSL_FD_SET_T *error_fd_set,
			const struct timeval *time_out_ptr = NULL) {
			unsigned int ready_fd_count;
			char         npsl_error_text[NPSL_MAX_ERROR_TEXT];
			if (NPSL_Select(socket_handle + 1, read_fd_set, write_fd_set,
				error_fd_set, time_out_ptr, &ready_fd_count, npsl_error_text) !=
				NPSL_SUCCESS)
				throw ExceptionNpsl(npsl_error_text);
			return(ready_fd_count);
		}
		static unsigned int SelectRead(NPSL_SOCKET_HANDLE socket_handle,
			const struct timeval *time_out_ptr = NULL) {
			NPSL_FD_SET_T tmp_fd_set = GetFDSet(socket_handle);
			return(Select(socket_handle, &tmp_fd_set, NULL, NULL, time_out_ptr));
		}
		static unsigned int SelectWrite(NPSL_SOCKET_HANDLE socket_handle,
			const struct timeval *time_out_ptr = NULL) {
			NPSL_FD_SET_T tmp_fd_set = GetFDSet(socket_handle);
			return(Select(socket_handle, NULL, &tmp_fd_set, NULL, time_out_ptr));
		}
		static unsigned int SelectError(NPSL_SOCKET_HANDLE socket_handle,
			const struct timeval *time_out_ptr = NULL) {
			NPSL_FD_SET_T tmp_fd_set = GetFDSet(socket_handle);
			return(Select(socket_handle, NULL, NULL, &tmp_fd_set, time_out_ptr));
		}
		static NPSL_FD_SET_T GetFDSet(NPSL_SOCKET_HANDLE socket_handle) {
			NPSL_FD_SET_T tmp_fd_set;
			FD_ZERO(&tmp_fd_set);
#ifdef _MSC_VER
# pragma warning(disable:4127)
#endif // # ifdef _MSC_VER
			FD_SET(socket_handle, &tmp_fd_set);
#ifdef _MSC_VER
# pragma warning(default:4127)
#endif // # ifdef _MSC_VER
			return(tmp_fd_set);
		}

	private:
		bool is_initilized;
};
//	//////////////////////////////////////////////////////////////////////////

//	//////////////////////////////////////////////////////////////////////////
class AddressIP {
	public:
		AddressIP() : host_name() {
			memset(ip_address, '\0', sizeof(ip_address));
		}
		explicit AddressIP(long in_address) : host_name() {
			SetAddress(in_address);
		}
		explicit AddressIP(unsigned long in_address) : host_name() {
			SetAddress(in_address);
		}
		explicit AddressIP(const unsigned char *in_address) : host_name() {
			SetAddress(in_address);
		}
		explicit AddressIP(const char *in_address) : host_name() {
			SetAddress(in_address);
		}
		explicit AddressIP(const std::string &in_address) : host_name() {
			SetAddress(in_address.c_str());
		}

		void SetAddress(long in_address) {
			memcpy(ip_address, &in_address, sizeof(ip_address));
		}
		void SetAddress(unsigned long in_address) {
			memcpy(ip_address, &in_address, sizeof(ip_address));
		}
		void SetAddress(const unsigned char *in_address) {
			memcpy(ip_address, in_address, sizeof(ip_address));
		}
		void SetAddress(const char *in_address) {
			struct in_addr tmp_in_addr;
			char           tmp_host_name[NPSL_MAX_HOST_NAME_LEN + 1];
			char           npsl_error_text[NPSL_MAX_ERROR_TEXT];
			if (NPSL_ResolveHostBasic(in_address, tmp_host_name,
				&tmp_in_addr, NULL, NULL, npsl_error_text) != NPSL_SUCCESS)
				throw ExceptionNpsl(npsl_error_text);
			host_name = tmp_host_name;
			memcpy(&ip_address, &tmp_in_addr.S_un.S_un_b, sizeof(ip_address));
		}
		void SetAddress(const std::string &in_address) {
			SetAddress(in_address.c_str());
		}

		std::string GetHostName() const {
			return(host_name);
		}
		struct in_addr GetInAddr() const {
			struct in_addr tmp_addr;
			memset(&tmp_addr, '\0', sizeof(tmp_addr));
			memcpy(&tmp_addr.S_un.S_un_b, ip_address, sizeof(tmp_addr.S_un.S_un_b));
			return(tmp_addr);
		}
		NPSL_SOCKADDR_IN GetSockaddrIn() const {
			NPSL_SOCKADDR_IN tmp_addr;
			memset(&tmp_addr, '\0', sizeof(tmp_addr));
			tmp_addr.sin_addr = GetInAddr();
			return(tmp_addr);
		}
		NPSL_SOCKADDR_IN GetSockaddrIn(AddressFamily address_family) const {
			NPSL_SOCKADDR_IN tmp_addr;
			memset(&tmp_addr, '\0', sizeof(tmp_addr));
			tmp_addr.sin_addr = GetInAddr();
			tmp_addr.sin_family = static_cast<short>(address_family);
			return(tmp_addr);
		}
		NPSL_SOCKADDR GetSockaddr() const {
			NPSL_SOCKADDR_IN tmp_sockaddr_in = GetSockaddrIn();
			NPSL_SOCKADDR    tmp_sockaddr;
			memset(&tmp_sockaddr, '\0', sizeof(tmp_sockaddr));
			memcpy(&tmp_sockaddr, &tmp_sockaddr_in,
				std::min(sizeof(tmp_sockaddr), sizeof(tmp_sockaddr_in)));
			return(tmp_sockaddr);
		}
		NPSL_SOCKADDR GetSockaddr(AddressFamily address_family) const {
			NPSL_SOCKADDR tmp_sockaddr = GetSockaddr();
			tmp_sockaddr.sa_family = static_cast<unsigned short>(address_family);
			return(tmp_sockaddr);
		}

	private:
		std::string   host_name;
		unsigned char ip_address[4];
};
//	//////////////////////////////////////////////////////////////////////////

//	//////////////////////////////////////////////////////////////////////////
class EndPointIP {
	public:
		EndPointIP() : address(), port(0) { }
		EndPointIP(const NPSL_SOCKADDR &in_sockaddr) :
			address(), port(0) {
			SetAddressAndPort(in_sockaddr);
		}
		EndPointIP(const NPSL_SOCKADDR_IN &in_sockaddr_in) :
			address(), port(0) {
			SetAddressAndPort(in_sockaddr_in);
		}
		EndPointIP(const AddressIP &in_address, int in_port) :
			address(), port(0) {
			SetAddressAndPort(in_address, in_port);
		}
		EndPointIP(const AddressIP &in_address, const char *in_port) :
			address(), port(0) {
			SetAddressAndPort(in_address, in_port);
		}
		EndPointIP(const AddressIP &in_address, const std::string &in_port) :
			address(), port(0) {
			SetAddressAndPort(in_address, in_port);
		}

		void SetAddressAndPort(const AddressIP &in_address, int in_port) {
			SetAddress(in_address);
			SetPort(in_port);
		}
		void SetAddressAndPort(const AddressIP &in_address, const char *in_port) {
			SetAddress(in_address);
			SetPort(in_port);
		}
		void SetAddressAndPort(const AddressIP &in_address,
			const std::string &in_port){
			SetAddress(in_address);
			SetPort(in_port);
		}
		void SetAddressAndPort(const NPSL_SOCKADDR &in_sockaddr) {
			NPSL_SOCKADDR_IN tmp_addr;
			memcpy(&tmp_addr, &in_sockaddr, sizeof(tmp_addr));
//			SetAddressAndPort(tmp_addr.sin_addr.S_un_b, ntohs(tmp_addr.sin_port));
			SetAddressAndPort(tmp_addr);
		}
		void SetAddressAndPort(const NPSL_SOCKADDR_IN &in_sockaddr_in) {
			SetAddress(in_sockaddr_in.sin_addr);
			SetPort(ntohs(in_sockaddr_in.sin_port));
		}

		void SetAddress(long in_address) {
			AddressIP tmp_address(in_address);
			address = tmp_address;
		}
		void SetAddress(unsigned long in_address) {
			AddressIP tmp_address(in_address);
			address = tmp_address;
		}
		void SetAddress(const unsigned char *in_address) {
			AddressIP tmp_address(in_address);
			address = tmp_address;
		}
		void SetAddress(const char *in_address) {
			AddressIP tmp_address(in_address);
			address = tmp_address;
		}
		void SetAddress(const std::string &in_address) {
			AddressIP tmp_address(in_address);
			address = tmp_address;
		}
		void SetAddress(const AddressIP &in_address) {
			address = in_address;
		}
		void SetAddress(const struct in_addr &in_addr_in) {
			SetAddress(&in_addr_in.S_un.S_un_b.s_b1);
		}
		void SetPort(int in_port) {
			if ((port < 0) ||
				(port > std::numeric_limits<unsigned short>::max())) {
				std::ostringstream error_string;
				error_string << "Invalid IP port/service specified (" << in_port <<
					") --- valid range is 0 to " <<
					std::numeric_limits<unsigned short>::max() << ", inclusive.";
				throw ExceptionNpsl(error_string);
			}
			port = in_port;
		}
		void SetPort(const char *in_port) {
			int  tmp_port;
			char npsl_error_text[NPSL_MAX_ERROR_TEXT];
			if (NPSL_ResolveServToPort(in_port, NULL, &tmp_port,
				npsl_error_text) != NPSL_SUCCESS)
				throw ExceptionNpsl(npsl_error_text);
			SetPort(tmp_port);
		}
		void SetPort(const std::string &in_port) {
			SetPort(in_port.c_str());
		}

		AddressIP GetAddress() const {
			return(address);
		}
		std::string GetHostName() const {
			return(address.GetHostName());
		}
		int GetPort() const {
			return(port);
		}
		short GetPortInNetworkOrder() const {
			return(htons(static_cast<unsigned short>(port)));
		}
		struct in_addr   GetInAddr() const {
			return(address.GetInAddr());
		}
		NPSL_SOCKADDR_IN GetSockaddrIn() const {
			return(GetSockaddrIn(AddressFamily_NONE));
		}
		NPSL_SOCKADDR_IN GetSockaddrIn(AddressFamily address_family) const {
			NPSL_SOCKADDR_IN tmp_addr = address.GetSockaddrIn(address_family);
			tmp_addr.sin_port = GetPortInNetworkOrder();
			return(tmp_addr);
		}
		NPSL_SOCKADDR    GetSockaddr() const {
			return(GetSockaddr(AddressFamily_NONE));
		}
		NPSL_SOCKADDR    GetSockaddr(AddressFamily address_family) const {
			NPSL_SOCKADDR tmp_sockaddr = address.GetSockaddr(address_family);
			reinterpret_cast<NPSL_SOCKADDR_IN *>(&tmp_sockaddr)->sin_port =
				GetPortInNetworkOrder();
			return(tmp_sockaddr);
		}

	private:

		AddressIP address;
		int       port;
};
//	//////////////////////////////////////////////////////////////////////////

//	//////////////////////////////////////////////////////////////////////////
class Socket {
	public:
		Socket(NPSL_SOCKET_HANDLE in_socket_handle,
			const NPSL_SOCKADDR &in_end_point,
			AddressFamily in_address_family = AddressFamily_Internet,
			SocketType in_socket_type = SocketType_Stream,
			ProtocolType in_protocol_type = ProtocolType_DEFAULT) :
			address_family(in_address_family), socket_type(in_socket_type),
			protocol_type(in_protocol_type), socket_handle(NPSL_INVALID_SOCKET),
			end_point(in_end_point), is_connected(false) {
			if (in_socket_handle != NPSL_INVALID_SOCKET) {
				socket_handle  = in_socket_handle;
				is_connected   = true;
				end_point_addr = GetSockaddr();
			}
			else
				Connect(end_point);
		}
		Socket(NPSL_SOCKET_HANDLE in_socket_handle,
			const NPSL_SOCKADDR_IN &in_end_point,
			AddressFamily in_address_family = AddressFamily_Internet,
			SocketType in_socket_type = SocketType_Stream,
			ProtocolType in_protocol_type = ProtocolType_DEFAULT) :
			address_family(in_address_family), socket_type(in_socket_type),
			protocol_type(in_protocol_type), socket_handle(NPSL_INVALID_SOCKET),
			end_point(in_end_point), is_connected(false) {
			if (in_socket_handle != NPSL_INVALID_SOCKET) {
				socket_handle  = in_socket_handle;
				is_connected   = true;
				end_point_addr = GetSockaddr();
			}
			else
				Connect(end_point);
		}
		Socket(NPSL_SOCKET_HANDLE in_socket_handle,
			const EndPointIP &in_end_point,
			AddressFamily in_address_family = AddressFamily_Internet,
			SocketType in_socket_type = SocketType_Stream,
			ProtocolType in_protocol_type = ProtocolType_DEFAULT) :
			address_family(in_address_family), socket_type(in_socket_type),
			protocol_type(in_protocol_type), socket_handle(NPSL_INVALID_SOCKET),
			end_point(in_end_point), is_connected(false) {
			if (in_socket_handle != NPSL_INVALID_SOCKET) {
				socket_handle  = in_socket_handle;
				is_connected   = true;
				end_point_addr = GetSockaddr();
			}
			else
				Connect(in_end_point);
		}
		Socket(const EndPointIP &in_end_point,
			AddressFamily in_address_family = AddressFamily_Internet,
			SocketType in_socket_type = SocketType_Stream,
			ProtocolType in_protocol_type = ProtocolType_DEFAULT) :
			address_family(in_address_family), socket_type(in_socket_type),
			protocol_type(in_protocol_type), socket_handle(NPSL_INVALID_SOCKET),
			end_point(), is_connected(false) {
			Connect(in_end_point);
		}
		Socket(AddressFamily in_address_family = AddressFamily_Internet,
			SocketType in_socket_type = SocketType_Stream,
			ProtocolType in_protocol_type = ProtocolType_DEFAULT) :
			address_family(in_address_family), socket_type(in_socket_type),
			protocol_type(in_protocol_type), socket_handle(NPSL_INVALID_SOCKET),
			end_point(), is_connected(false) {
		}
		~Socket() {
			Close();
		}

		Socket(const Socket &other) {
			address_family = other.address_family;
			socket_type    = other.socket_type;
			protocol_type  = other.protocol_type;
			socket_handle  = other.socket_handle;
			end_point      = other.end_point;
			end_point_addr = other.end_point_addr;
			is_connected   = other.is_connected;
			if (other.socket_handle != NPSL_INVALID_SOCKET) {
				const_cast<Socket *>(&other)->socket_handle = NPSL_INVALID_SOCKET;
				const_cast<Socket *>(&other)->is_connected  = false;
			}
		}
		Socket & operator = (const Socket &other) {
			address_family = other.address_family;
			socket_type    = other.socket_type;
			protocol_type  = other.protocol_type;
			socket_handle  = other.socket_handle;
			end_point      = other.end_point;
			end_point_addr = other.end_point_addr;
			is_connected   = other.is_connected;
			if (other.socket_handle != NPSL_INVALID_SOCKET) {
				const_cast<Socket *>(&other)->socket_handle = NPSL_INVALID_SOCKET;
				const_cast<Socket *>(&other)->is_connected  = false;
			}
			return(*this);
		}

		void Create() {
			if (IsCreated())
				throw ExceptionNpsl("Socket is already created.");
			char npsl_error_text[NPSL_MAX_ERROR_TEXT];
			if (NPSL_Socket(address_family, socket_type, protocol_type,
				&socket_handle, npsl_error_text) != NPSL_SUCCESS)
				throw ExceptionNpsl(npsl_error_text);
		}
		void Connect(const EndPointIP &in_end_point) {
			if (!IsCreated())
				Create();
			if (IsConnected())
				throw ExceptionNpsl("Socket is already connected.");
			end_point      = in_end_point;
/*
			end_point_addr = GetSockaddrIn();
			char npsl_error_text[NPSL_MAX_ERROR_TEXT];
			if (NPSL_Connect(socket_handle,
				reinterpret_cast<NPSL_SOCKADDR *>(&end_point_addr),
				sizeof(NPSL_SOCKADDR), npsl_error_text) != NPSL_SUCCESS)
					throw ExceptionNpsl(npsl_error_text);
			is_connected = true;
*/
			end_point_addr = GetSockaddr();
			char npsl_error_text[NPSL_MAX_ERROR_TEXT];
			if (NPSL_Connect(socket_handle, &end_point_addr,
				sizeof(end_point_addr), npsl_error_text) != NPSL_SUCCESS)
					throw ExceptionNpsl(npsl_error_text);
			is_connected = true;
		}
		//	/////////////////////////////////////////////////////////////////
		//	/////////////////////////////////////////////////////////////////
		//
		// Notes:
		//		1) No harm is done if this method is called on a socket instance
		//			which has not been created or connected.
		//		2)	Any exceptions are suppressed until after the socket close.
		//	/////////////////////////////////////////////////////////////////
		void Close() {
/*
			if (!IsCreated())
				return;
			bool               error_flag = false;
			std::ostringstream error_string;
			char               npsl_error_text[NPSL_MAX_ERROR_TEXT];
			if (IsConnected()) {
				if (NPSL_ShutDown(socket_handle, NPSL_SHUTDOWN_FLAG_BOTH,
					npsl_error_text) != NPSL_SUCCESS) {
					error_string << "Error(s) on socket shut-down: " <<
						npsl_error_text;
					error_flag = true;
				}
				is_connected = false;
			}
			if (NPSL_CloseSocket(socket_handle, npsl_error_text) != NPSL_SUCCESS) {
				if (error_flag)
					error_string << std::endl;
				error_string << "Error(s) on socket close: " << npsl_error_text;
				error_flag = true;
			}
			socket_handle = NPSL_INVALID_SOCKET;
			if (error_flag)
				throw ExceptionNpsl(error_string);
*/
			if (!IsCreated())
				return;
			bool               error_flag = false;
			std::ostringstream error_string;
			char               npsl_error_text[NPSL_MAX_ERROR_TEXT];
			//	///////////////////////////////////////////////////////////
			//	///////////////////////////////////////////////////////////
			// If we are at present connected, we must first disconnect
			//	the socket. We'll catch any exception for later reporting...
			//	///////////////////////////////////////////////////////////
			if (IsConnected()) {
				try {
					Disconnect();
				}
				catch (std::exception &except) {
					error_flag = true;
					error_string << except.what();
				}
			}
			//	///////////////////////////////////////////////////////////
			//	///////////////////////////////////////////////////////////
			// Now close the socket...
			//	///////////////////////////////////////////////////////////
			if (NPSL_CloseSocket(socket_handle, npsl_error_text) != NPSL_SUCCESS) {
				if (error_flag)
					error_string << std::endl;
				error_string << "Error(s) on socket close: " << npsl_error_text;
				error_flag = true;
			}
			socket_handle = NPSL_INVALID_SOCKET;
			//	///////////////////////////////////////////////////////////
			//	///////////////////////////////////////////////////////////
			// (Re-)throw an exception if an error occurred.
			//	///////////////////////////////////////////////////////////
			if (error_flag)
				throw ExceptionNpsl(error_string);
			//	///////////////////////////////////////////////////////////
		}
		//	/////////////////////////////////////////////////////////////////
		//	/////////////////////////////////////////////////////////////////
		// Disconnects the socket.
		//
		// Notes:
		//		1) No harm is done if this method is called on a socket instance
		//			which has not been connected.
		//		2)	Any exceptions are suppressed until after the socket has
		//			been disconnected.
		//	/////////////////////////////////////////////////////////////////
		void Disconnect() {
			if (IsConnected()) {
				std::ostringstream error_string;
				char               npsl_error_text[NPSL_MAX_ERROR_TEXT];
				if (NPSL_ShutDown(socket_handle, NPSL_SHUTDOWN_FLAG_BOTH,
					npsl_error_text) != NPSL_SUCCESS) {
					// Some kind of problem... Indicate no connection.
					is_connected = false;
					error_string << "Error(s) on socket shut-down: " <<
						npsl_error_text;
					throw ExceptionNpsl(error_string);
				}
				is_connected = false;
			}
		}
		//	/////////////////////////////////////////////////////////////////

		//	/////////////////////////////////////////////////////////////////
		//	/////////////////////////////////////////////////////////////////
		//	/////////////////////////////////////////////////////////////////
		void         Accept(NPSL_SOCKET_HANDLE *out_socket_handle,
			NPSL_SOCKADDR *addr = NULL, NPSL_SOCKLEN_T *addrlen = NULL) const {
			CheckConnected();
			char npsl_error_text[NPSL_MAX_ERROR_TEXT];
			if (NPSL_Accept(socket_handle, out_socket_handle, addr, addrlen,
				npsl_error_text) != NPSL_SUCCESS)
				throw ExceptionNpsl(npsl_error_text);
		}
		void         Bind(const NPSL_SOCKADDR *addr,
			NPSL_SOCKLEN_T addrlen) const {
			CheckConnected();
			char npsl_error_text[NPSL_MAX_ERROR_TEXT];
			if (NPSL_Bind(socket_handle, addr, addrlen, npsl_error_text) !=
				NPSL_SUCCESS)
				throw ExceptionNpsl(npsl_error_text);
		}
		void         CloseSocket() {
			Close();
		}
		void         GetSockOpt(int opt_level, int opt_name, void *opt_value,
			int *opt_length) {
			CheckConnected();
			char         npsl_error_text[NPSL_MAX_ERROR_TEXT];
			if (NPSL_GetSockOpt(socket_handle, opt_level, opt_name, opt_value,
				opt_length, npsl_error_text) != NPSL_SUCCESS)
				throw ExceptionNpsl(npsl_error_text);
		}
		unsigned int Recv(char *buffer_ptr, unsigned int buffer_length,
			int flags = 0) const {
			CheckConnected();
			unsigned int recv_count;
			char         npsl_error_text[NPSL_MAX_ERROR_TEXT];
			if (NPSL_Recv(socket_handle, buffer_ptr, buffer_length, flags,
				&recv_count, npsl_error_text) != NPSL_SUCCESS)
				throw ExceptionNpsl(npsl_error_text);
			return(recv_count);
		}
		unsigned int RecvFrom(char *buffer_ptr, unsigned int buffer_length,
			int flags = 0, NPSL_SOCKADDR *addr = NULL,
			NPSL_SOCKLEN_T *addrlen = NULL) const {
			CheckConnected();
			unsigned int recv_count;
			char         npsl_error_text[NPSL_MAX_ERROR_TEXT];
			if (NPSL_RecvFrom(socket_handle, buffer_ptr, buffer_length, flags,
				addr, addrlen, &recv_count, npsl_error_text) != NPSL_SUCCESS)
				throw ExceptionNpsl(npsl_error_text);
			return(recv_count);
		}
		unsigned int Select(NPSL_FD_SET_T *read_fd_set,
			NPSL_FD_SET_T *write_fd_set, NPSL_FD_SET_T *error_fd_set,
			const struct timeval *time_out_ptr = NULL) const {
			CheckConnected();
			unsigned int ready_fd_count;
			char         npsl_error_text[NPSL_MAX_ERROR_TEXT];
			if (NPSL_Select(socket_handle + 1, read_fd_set, write_fd_set,
				error_fd_set, time_out_ptr, &ready_fd_count, npsl_error_text) !=
				NPSL_SUCCESS)
				throw ExceptionNpsl(npsl_error_text);
			return(ready_fd_count);
		}
		unsigned int SelectRead(const struct timeval *time_out_ptr = NULL) const {
			NPSL_FD_SET_T tmp_fd_set = GetFDSet();
			return(Select(&tmp_fd_set, NULL, NULL, time_out_ptr));
		}
		unsigned int SelectWrite(const struct timeval *time_out_ptr = NULL) const{
			NPSL_FD_SET_T tmp_fd_set = GetFDSet();
			return(Select(NULL, &tmp_fd_set, NULL, time_out_ptr));
		}
		unsigned int SelectError(const struct timeval *time_out_ptr = NULL) const{
			NPSL_FD_SET_T tmp_fd_set = GetFDSet();
			return(Select(NULL, NULL, &tmp_fd_set, time_out_ptr));
		}
		unsigned int Send(const char *buffer_ptr, unsigned int buffer_length,
			int flags = 0) const {
			CheckConnected();
			unsigned int send_count;
			char         npsl_error_text[NPSL_MAX_ERROR_TEXT];
			if (NPSL_Send(socket_handle, buffer_ptr, buffer_length, flags,
				&send_count, npsl_error_text) != NPSL_SUCCESS)
				throw ExceptionNpsl(npsl_error_text);
			return(send_count);
		}
		unsigned int SendTo(const char *buffer_ptr, unsigned int buffer_length,
			int flags = 0, const NPSL_SOCKADDR *addr = NULL,
			NPSL_SOCKLEN_T addrlen = 0) const {
			CheckConnected();
			unsigned int send_count;
			char         npsl_error_text[NPSL_MAX_ERROR_TEXT];
			if (NPSL_SendTo(socket_handle, buffer_ptr, buffer_length, flags,
				addr, addrlen, &send_count, npsl_error_text) != NPSL_SUCCESS)
				throw ExceptionNpsl(npsl_error_text);
			return(send_count);
		}
		void         SetSockOpt(int opt_level, int opt_name,
			const void *opt_value, int opt_length) {
			CheckConnected();
			char         npsl_error_text[NPSL_MAX_ERROR_TEXT];
			if (NPSL_SetSockOpt(socket_handle, opt_level, opt_name, opt_value,
				opt_length, npsl_error_text) != NPSL_SUCCESS)
				throw ExceptionNpsl(npsl_error_text);
		}
		void         ShutDown(int shut_down_flag) const {
			CheckConnected();
			char npsl_error_text[NPSL_MAX_ERROR_TEXT];
			if (NPSL_ShutDown(socket_handle, shut_down_flag, npsl_error_text) !=
				NPSL_SUCCESS)
				throw ExceptionNpsl(npsl_error_text);
		}
		//	/////////////////////////////////////////////////////////////////

		//	/////////////////////////////////////////////////////////////////
		//	/////////////////////////////////////////////////////////////////
		//	Some specialized select methods...
		//	/////////////////////////////////////////////////////////////////
		unsigned int SelectWait(NPSL_FD_SET_T *read_fd_set,
			NPSL_FD_SET_T *write_fd_set, NPSL_FD_SET_T *error_fd_set,
			const struct timeval *time_out_ptr = NULL) const {
			return(Select(read_fd_set, write_fd_set, error_fd_set, time_out_ptr));
		}
		unsigned int SelectWaitOnRead(const struct timeval *time_out_ptr = NULL)
			const {
			NPSL_FD_SET_T read_fd_set  = GetFDSet();
			return(Select(&read_fd_set, NULL, NULL, time_out_ptr));
		}
		unsigned int SelectWaitOnWrite(const struct timeval *time_out_ptr = NULL)
			const {
			NPSL_FD_SET_T write_fd_set = GetFDSet();
			return(Select(NULL, &write_fd_set, NULL, time_out_ptr));
		}
		unsigned int SelectWaitOnError(const struct timeval *time_out_ptr = NULL)
			const {
			NPSL_FD_SET_T error_fd_set = GetFDSet();
			return(Select(NULL, NULL, &error_fd_set, time_out_ptr));
		}
		unsigned int SelectWaitOnAny(const struct timeval *time_out_ptr = NULL)
			const {
			NPSL_FD_SET_T read_fd_set  = GetFDSet();
			NPSL_FD_SET_T write_fd_set = GetFDSet();
			NPSL_FD_SET_T error_fd_set = GetFDSet();
			return(Select(&read_fd_set, &write_fd_set, &error_fd_set,
				time_out_ptr));
		}
		//	/////////////////////////////////////////////////////////////////

		//	/////////////////////////////////////////////////////////////////
		//	/////////////////////////////////////////////////////////////////
		// Some specialized {get|set} socket option methods...
		//	/////////////////////////////////////////////////////////////////
		unsigned int GetRecvBufferSize() {
			CheckCreated();
			unsigned int buffer_size;
			char         npsl_error_text[NPSL_MAX_ERROR_TEXT];
			if (NPSL_GetSockOpt_RcvBuf(socket_handle, &buffer_size,
				npsl_error_text) != NPSL_SUCCESS)
				throw ExceptionNpsl(npsl_error_text);
			return(buffer_size);
		}
		unsigned int GetSendBufferSize() {
			CheckCreated();
			unsigned int buffer_size;
			char         npsl_error_text[NPSL_MAX_ERROR_TEXT];
			if (NPSL_GetSockOpt_SndBuf(socket_handle, &buffer_size,
				npsl_error_text) != NPSL_SUCCESS)
				throw ExceptionNpsl(npsl_error_text);
			return(buffer_size);
		}
		void SetRecvBufferSize(unsigned int buffer_size) {
			CheckCreated();
			char npsl_error_text[NPSL_MAX_ERROR_TEXT];
			if (NPSL_SetSockOpt_RcvBuf(socket_handle, buffer_size,
				npsl_error_text) != NPSL_SUCCESS)
				throw ExceptionNpsl(npsl_error_text);
		}
		void SetSendBufferSize(unsigned int buffer_size) {
			CheckCreated();
			char npsl_error_text[NPSL_MAX_ERROR_TEXT];
			if (NPSL_SetSockOpt_SndBuf(socket_handle, buffer_size,
				npsl_error_text) != NPSL_SUCCESS)
				throw ExceptionNpsl(npsl_error_text);
		}
		//	/////////////////////////////////////////////////////////////////

		//	/////////////////////////////////////////////////////////////////
		//	/////////////////////////////////////////////////////////////////
		// Some supporting bit players...
		//	/////////////////////////////////////////////////////////////////
		NPSL_FD_SET_T GetFDSet() const {
			CheckConnected();
			NPSL_FD_SET_T tmp_fd_set;
			FD_ZERO(&tmp_fd_set);
#ifdef _MSC_VER
# pragma warning(disable:4127)
#endif // # ifdef _MSC_VER
			FD_SET(socket_handle, &tmp_fd_set);
#ifdef _MSC_VER
# pragma warning(default:4127)
#endif // # ifdef _MSC_VER
			return(tmp_fd_set);
		}
		void SetBlockingMode(bool blocking_mode_flag) const {
			CheckCreated();
			char npsl_error_text[NPSL_MAX_ERROR_TEXT];
			if (NPSL_SetBlockingMode(socket_handle, (blocking_mode_flag) ? 1 : 0,
				npsl_error_text) != NPSL_SUCCESS)
				throw ExceptionNpsl(npsl_error_text);
		}
		void SetBlockingModeOn() const {
			SetBlockingMode(true);
		}
		void SetBlockingModeOff() const {
			SetBlockingMode(false);
		}
		//	/////////////////////////////////////////////////////////////////

		//	/////////////////////////////////////////////////////////////////
		//	/////////////////////////////////////////////////////////////////
		//	Get socket status...
		//	/////////////////////////////////////////////////////////////////
		bool IsCreated() const {
			return(socket_handle != NPSL_INVALID_SOCKET);
		}
		bool IsConnected() const {
			return(IsCreated() && is_connected);
		}
		bool IsReadyReadOrWrite() const {
			NPSL_FD_SET_T  read_fd_set  = GetFDSet();
			NPSL_FD_SET_T  write_fd_set = GetFDSet();
			struct timeval time_out     = { 0, 0 };
			return(IsConnected() && Select(&read_fd_set, &write_fd_set, NULL,
				&time_out));
		}
		bool IsReadyRead() const {
			struct timeval time_out = { 0, 0 };
			return(IsConnected() && SelectRead(&time_out));
		}
		bool IsReadyWrite() const {
			struct timeval time_out = { 0, 0 };
			return(IsConnected() && SelectWrite(&time_out));
		}
		//	/////////////////////////////////////////////////////////////////

		//	/////////////////////////////////////////////////////////////////
		//	/////////////////////////////////////////////////////////////////
		// Run-time assertion of socket status...
		//	/////////////////////////////////////////////////////////////////
		void CheckCreated() const {
			if (!IsCreated())
				throw ExceptionNpsl("Socket has not been created.");
		}
		void CheckConnected() const {
			CheckCreated();
			if (!IsConnected())
				throw ExceptionNpsl("Socket has not been connected.");
		}
		//	/////////////////////////////////////////////////////////////////

		//	/////////////////////////////////////////////////////////////////
		//	/////////////////////////////////////////////////////////////////
		// Various get accessors...
		//	/////////////////////////////////////////////////////////////////
		NPSL_SOCKET_HANDLE GetSocket() const {
			return(socket_handle);
		}
		AddressFamily      GetAddressFamily() const {
			return(address_family);
		}
		SocketType         GetSocketType() const {
			return(socket_type);
		}
		ProtocolType       GetProtocolType() const {
			return(protocol_type);
		}
		std::string        GetHostName() const {
			return(end_point.GetHostName());
		}
		int                GetPort() const {
			return(end_point.GetPort());
		}
		EndPointIP         GetEndPointIP() const {
			return(end_point);
		}
		NPSL_SOCKADDR_IN   GetSockaddrIn() const {
			return(end_point.GetSockaddrIn(address_family));
		}
		NPSL_SOCKADDR      GetSockaddr() const {
			return(end_point.GetSockaddr(address_family));
		}
		//	/////////////////////////////////////////////////////////////////

	private:
		AddressFamily      address_family;
		SocketType         socket_type;
		ProtocolType       protocol_type;

		NPSL_SOCKET_HANDLE socket_handle;
		EndPointIP         end_point;
		NPSL_SOCKADDR      end_point_addr;
		bool               is_connected;
};
//	//////////////////////////////////////////////////////////////////////////

} // namespace NpslO

} // namespace MLB

#endif // #ifndef HH__MLB__NpslO__NpslO_h__HH


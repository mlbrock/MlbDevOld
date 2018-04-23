//	//////////////////////////////////////////////////////////////////////////
//	//////////////////////////////////////////////////////////////////////////
//	Network Programming Support Library (NPSL) Source Module
//	//////////////////////////////////////////////////////////////////////////
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Implementation file for object-based NPSL support.

	Revision History	:	2002-01-26 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 2002 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
//	//////////////////////////////////////////////////////////////////////////

//	//////////////////////////////////////////////////////////////////////////
//	//////////////////////////////////////////////////////////////////////////
//	Include necessary header files . . .
//	//////////////////////////////////////////////////////////////////////////

#include "NpslO.h"

//	//////////////////////////////////////////////////////////////////////////

#ifdef TEST_MAIN

# include <iostream>

using namespace MLB::NpslO;

//	//////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
	const char *host;
	const char *port;

	host = (argc > 1) ? argv[1] : "localhost";
//	host = (argc > 1) ? argv[1] : "ldndwm233140";
//	host = (argc > 1) ? argv[1] : "30.254.31.125";
	port = (argc > 2) ? argv[2] : "8500";
//	port = (argc > 2) ? argv[2] : "23";
//	port = (argc > 2) ? argv[2] : "smtp";

	try {
		SocketLib  socket_lib;
		std::cout << "Attempting to connect...";
		Socket my_socket(EndPointIP(AddressIP(host), port));
//std::cout << "GET 1: recv size: " << my_socket.GetRecvBufferSize() << std::endl;
//my_socket.SetRecvBufferSize(1);
//std::cout << "GET 2: recv size: " << my_socket.GetRecvBufferSize() << std::endl;
		std::cout << "done (Host = " << my_socket.GetHostName() << ", Port = " <<
			my_socket.GetPort() << ")" << std::endl;
std::cout << "Read/Write: " << my_socket.IsReadyReadOrWrite() << std::endl;
std::cout << "Read      : " << my_socket.IsReadyRead()        << std::endl;
std::cout << "Write     : " << my_socket.IsReadyWrite()       << std::endl;
		my_socket.Disconnect();
		my_socket.Close();
	}
	catch (std::exception &except) {
		std::cout << std::endl << "MLB::NpslO::Socket error: " << except.what() <<
			std::endl;
	}

	std::cout << "Test completed." << std::endl;

	return(0);
}
//	//////////////////////////////////////////////////////////////////////////

#endif // #ifdef TEST_MAIN


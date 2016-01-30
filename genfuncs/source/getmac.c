/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	GENFUNCS General Functions Library Source Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Determines the machine Ethernet Media Access Control
								(MAC) address.

	Revision History	:	1994-02-25 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include "genfunci.h"

#ifdef _Windows
# include <windows.h>
# include <wincon.h>
# include <nb30.h>
#elif __MSDOS__
# include <memory.h>
#else
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#endif /* #ifdef _Windows */

/*	***********************************************************************	*/

#ifdef __MSDOS__
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_GetMAC(GEN_ADDR_MAC *ethernet_address, char *error_text)
#else
int GEN_GetMAC(ethernet_address, error_text)
GEN_ADDR_MAC *ethernet_address;
char         *error_text;
#endif /* #ifndef NARGS */
{
	memset(ethernet_address, '\0', sizeof(*ethernet_address));

	return(GENFUNCS_SUCCESS);
}
/*	***********************************************************************	*/

#elif _Windows
/*	***********************************************************************	*/
typedef struct {
	ADAPTER_STATUS adapter_status;
	NAME_BUFFER    name_buffer[30];
} GEN_GetMAC_WIN32;

#ifndef NARGS
int GEN_GetMAC(GEN_ADDR_MAC *ethernet_address, char *error_text)
#else
int GEN_GetMAC(ethernet_address, error_text)
GEN_ADDR_MAC *ethernet_address;
char         *error_text;
#endif /* #ifndef NARGS */
{
	int              return_code = GENFUNCS_SUCCESS;
	UCHAR            netbios_code;
	NCB              ncb_data;
	GEN_GetMAC_WIN32 status;

	memset(ethernet_address, '\0', sizeof(*ethernet_address));

	memset(&ncb_data, '\0', sizeof(ncb_data));
	ncb_data.ncb_command  = NCBRESET;
	ncb_data.ncb_lana_num = 0;

	if ((netbios_code = Netbios(&ncb_data)) == 0) {
		memset(&ncb_data, '\0', sizeof(ncb_data));
		strpadr(chrcpy(((char *) ncb_data.ncb_callname), '*'),
			sizeof(ncb_data.ncb_callname));
		ncb_data.ncb_command  = NCBASTAT;
		ncb_data.ncb_lana_num = 0;
		ncb_data.ncb_buffer   = ((unsigned char *) &status);
		ncb_data.ncb_length   = sizeof(status);
		if ((netbios_code = Netbios(&ncb_data)) == 0)
			memcpy(ethernet_address, status.adapter_status.adapter_address,
				sizeof(*ethernet_address));
		else {
			sprintf(error_text,
				"Function 'Netbios()' returned '%u' on 'NCASTAT' attempt.",
				((unsigned int) netbios_code));
			return_code = GENFUNCS_SYSTEM_FAILURE;
		}
	}
	else {
		sprintf(error_text,
			"Function 'Netbios()' returned '%u' on 'NCBRESET' attempt.",
			((unsigned int) netbios_code));
		return_code = GENFUNCS_SYSTEM_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

#else
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_GetMAC(GEN_ADDR_MAC *ethernet_address, char *error_text)
#else
int GEN_GetMAC(ethernet_address, error_text)
GEN_ADDR_MAC *ethernet_address;
char         *error_text;
#endif /* #ifndef NARGS */
{
	int               return_code;
	char              host_name[GEN_MAX_HOST_NAME_LEN + 1];
	struct ether_addr ether_addr;

	memset(ethernet_address, '\0', sizeof(*ethernet_address));

	if ((return_code = GEN_DetermineHostName(host_name, error_text)) ==
		GENFUNCS_SUCCESS) {
		if (!ether_hostton(host_name, &ether_addr))
			memcpy(ethernet_address, &ether_addr, sizeof(*ethernet_address));
		else {
			GEN_AppendLastErrorString(0, GENFUNCS_MAX_ERROR_TEXT - 100,
				strcat(strcat(strcpy(error_text,
				"Call to 'ether_hostton()' for host name '"), host_name),
				"' failed: "));
			return_code = GENFUNCS_SYSTEM_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/
#endif /* #ifdef __MSDOS__ */

#ifdef TEST_MAIN

COMPAT_FN_DECL(int main, (void));

int main()
{
	int          return_code;
	GEN_ADDR_MAC ethernet_address;
	char         error_text[GENFUNCS_MAX_ERROR_TEXT];

	fprintf(stderr, "Test harness for function 'GEN_GetMAC()'\n");
	fprintf(stderr, "---- ------- --- -------- --------------\n\n");

	if ((return_code = GEN_GetMAC(&ethernet_address, error_text)) ==
		GENFUNCS_SUCCESS)
		printf("Ethernet Address: %02X-%02X-%02X-%02X-%02X-%02X\n",
			ethernet_address.octet[0],
			ethernet_address.octet[1],
			ethernet_address.octet[2],
			ethernet_address.octet[3],
			ethernet_address.octet[4],
			ethernet_address.octet[5]);
	else
		fprintf(stderr, "ERROR: %s\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */


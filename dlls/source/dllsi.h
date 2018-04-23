/* *********************************************************************** */
/* *********************************************************************** */
/*	Doubly-Linked List Support (DLLS) Library Internal Include File			*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Internal include file for the Doubly-Linked List
								Support (DLLS) library.

	Revision History	:	1987-03-11 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1987 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

#ifndef h__DLLSI_H__h

#define h__DLLSI_H__h							1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Necessary include files . . .															*/
/*	***********************************************************************	*/

#include "dlls.h"

/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#define DLLS_SIGNATURE_VALID				((DLLS_SIGNATURE) 0x3d7b9353)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Internal functions provided in library 'dlls.{a|lib}' . . .					*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Structures and functions used for testing . . .									*/
/*	***********************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Test structure definitions . . .
		*****************************************************************	*/
typedef struct {
	unsigned long highest_instance;
	DLLS          dlls_data;
} TEST_DLLS;

typedef struct {
	unsigned long instance;
	DLLS_NODE     node_data;
} TEST_NODE;
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Test function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int  DLLS_TEST_AddNodes, (TEST_DLLS *dlls_ptr,
	unsigned int count, int random_flag, char *error_text));
COMPAT_FN_DECL(int DLLS_TEST_CreateNodesList, (TEST_DLLS *dlls_ptr,
	unsigned int count, int random_flag, unsigned int *node_count,
	TEST_NODE **node_list, char *error_text));
COMPAT_FN_DECL(int  DLLS_TEST_AllocateNode, (TEST_DLLS *dlls_ptr,
	TEST_NODE **node_ptr, char *error_text));
COMPAT_FN_DECL(int  DLLS_TEST_AllocateNodeBasic, (unsigned long instance,
	TEST_NODE **node_ptr, char *error_text));
COMPAT_FN_DECL(void DLLS_TEST_SetNode, (TEST_DLLS *dlls_ptr,
	TEST_NODE *node_ptr));
COMPAT_FN_DECL(void DLLS_TEST_SetNodeBasic, (unsigned long instance,
	TEST_NODE *node_ptr));
COMPAT_FN_DECL(int  DLLS_TEST_Check, (const TEST_DLLS *dlls_ptr,
	char *error_text));
COMPAT_FN_DECL(int  DLLS_TEST_CompareFunc, (void *control_ptr,
	const DLLS_NODE *node_ptr_1, const DLLS_NODE *node_ptr_2,
	size_t data_length));
COMPAT_FN_DECL(void DLLS_TEST_Destroy, (TEST_DLLS *dlls_ptr));
COMPAT_FN_DECL(void DLLS_TEST_EmitDLLS, (const TEST_DLLS *dlls_ptr));
COMPAT_FN_DECL(void DLLS_TEST_EmitNode, (const TEST_NODE *node_ptr));
COMPAT_FN_DECL(int  DLLS_TEST_GetList, (DLLS *dlls_ptr, int random_flag,
	unsigned int *out_count, DLLS_NODE ***out_list, char *error_text));
COMPAT_FN_DECL(void DLLS_TEST_Init, (TEST_DLLS *dlls_ptr));
	/*	*****************************************************************	*/

/*	***********************************************************************	*/

#endif /* #ifndef h__DLLSI_H__h */


/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Manages the clearing and setting of ancilliary cache
								SQL clauses to be used when retrieving data from the
								database.

	Revision History	:	1994-12-28 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dcr.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Function prototypes for functions local to this module . . .			*/
/*	***********************************************************************	*/

#ifndef NARGS
static int DCR_SetSQLClause(const char *sql_clause_type,
	const char *in_sql_clause, char **out_sql_clause, char *error_text);
#else
static int DCR_SetSQLClause();
#endif /* #ifndef NARGS */

/*	***********************************************************************	*/

int DCR_ClearSQLWhereClause(cache_ptr, error_text)
DCR_CACHE *cache_ptr;
char      *error_text;
{
	return(DCR_SetSQLClause("WHERE", NULL, &cache_ptr->sql_where_clause,
		error_text));
}
/*	***********************************************************************	*/

int DCR_ClearSQLGroupByClause(cache_ptr, error_text)
DCR_CACHE *cache_ptr;
char      *error_text;
{
	return(DCR_SetSQLClause("GROUP BY", NULL,
		&cache_ptr->sql_group_by_clause, error_text));
}
/*	***********************************************************************	*/

int DCR_ClearSQLOrderByClause(cache_ptr, error_text)
DCR_CACHE *cache_ptr;
char      *error_text;
{
	return(DCR_SetSQLClause("ORDER BY", NULL,
		&cache_ptr->sql_order_by_clause, error_text));
}
/*	***********************************************************************	*/

int DCR_SetSQLWhereClause(cache_ptr, sql_where_clause, error_text)
DCR_CACHE  *cache_ptr;
const char *sql_where_clause;
char       *error_text;
{
	return(DCR_SetSQLClause("WHERE", sql_where_clause,
		&cache_ptr->sql_where_clause, error_text));
}
/*	***********************************************************************	*/

int DCR_SetSQLGroupByClause(cache_ptr, sql_group_by_clause, error_text)
DCR_CACHE  *cache_ptr;
const char *sql_group_by_clause;
char       *error_text;
{
	return(DCR_SetSQLClause("GROUP BY", sql_group_by_clause,
		&cache_ptr->sql_group_by_clause, error_text));
}
/*	***********************************************************************	*/

int DCR_SetSQLOrderByClause(cache_ptr, sql_order_by_clause, error_text)
DCR_CACHE  *cache_ptr;
const char *sql_order_by_clause;
char       *error_text;
{
	return(DCR_SetSQLClause("ORDER BY", sql_order_by_clause,
		&cache_ptr->sql_order_by_clause, error_text));
}
/*	***********************************************************************	*/

static int DCR_SetSQLClause(sql_clause_type, in_sql_clause,
	out_sql_clause, error_text)
const char  *sql_clause_type;
const char  *in_sql_clause;
char       **out_sql_clause;
char        *error_text;
{
	int   return_code    = DCR_SUCCESS;
	char *tmp_sql_clause = NULL;

	if ((in_sql_clause != NULL) && *in_sql_clause &&
		((tmp_sql_clause = strdup(in_sql_clause)) == NULL)) {
		sprintf(error_text, "%s '%s' clause (%u bytes required).",
			"Unable to allocate memory for the SQL", sql_clause_type,
			strlen(in_sql_clause) + 1);
		return_code = DCR_MEMORY_FAILURE;
	}
	else {
		if (*out_sql_clause != NULL)
			free(*out_sql_clause);
		*out_sql_clause = tmp_sql_clause;
	}

	return(return_code);
}
/*	***********************************************************************	*/


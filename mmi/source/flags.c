/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MMI Memory-mapped Interface Library Source Code Module						*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts MMI flag values to strings.

	Revision History	:	1992-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include <limits.h>
#include <string.h>

#include <strfuncs.h>

#include "mmii.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MMI Advice Flag Names																	*/
/*	***********************************************************************	*/
static const MMI_FLAG_DEF MMI_MADV_FlagList[] = {
	{	"MMI_FLAG_MADV_NORMAL",			MMI_FLAG_MADV_NORMAL			},
	{	"MMI_FLAG_MADV_RANDOM",			MMI_FLAG_MADV_RANDOM			},
	{	"MMI_FLAG_MADV_SEQUENTIAL",	MMI_FLAG_MADV_SEQUENTIAL	},
	{	"MMI_FLAG_MADV_WILLNEED",		MMI_FLAG_MADV_WILLNEED		},
	{	"MMI_FLAG_MADV_DONTNEED",		MMI_FLAG_MADV_DONTNEED		}
};
static const unsigned int MMI_MADV_FlagCount  =
	sizeof(MMI_MADV_FlagList) / sizeof(MMI_MADV_FlagList[0]);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MMI Protection Flag Names																*/
/*	***********************************************************************	*/
static const MMI_FLAG_DEF MMI_PROT_FlagList[] = {
	{	"MMI_FLAG_PROT_NONE",	MMI_FLAG_PROT_NONE	},
	{	"MMI_FLAG_PROT_READ",	MMI_FLAG_PROT_READ	},
	{	"MMI_FLAG_PROT_WRITE",	MMI_FLAG_PROT_WRITE	},
	{	"MMI_FLAG_PROT_EXEC",	MMI_FLAG_PROT_EXEC	},
	{	"MMI_FLAG_PROT_USER",	MMI_FLAG_PROT_USER	}
};
static const unsigned int MMI_PROT_FlagCount  =
	sizeof(MMI_PROT_FlagList) / sizeof(MMI_PROT_FlagList[0]);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MMI Memory-Mapping Flag Names															*/
/*	***********************************************************************	*/
static const MMI_FLAG_DEF MMI_MMAP_FlagList[] = {
	{	"MMI_FLAG_MMAP_SHARED",		MMI_FLAG_MMAP_SHARED		},
	{	"MMI_FLAG_MMAP_PRIVATE",	MMI_FLAG_MMAP_PRIVATE	},
	{	"MMI_FLAG_MMAP_FIXED",		MMI_FLAG_MMAP_FIXED		},
	{	"MMI_FLAG_MMAP_NORESERVE",	MMI_FLAG_MMAP_NORESERVE	},
	{	"MMI_FLAG_MMAP_RENAME",		MMI_FLAG_MMAP_RENAME		}
};
static const unsigned int MMI_MMAP_FlagCount  =
	sizeof(MMI_MMAP_FlagList) / sizeof(MMI_MMAP_FlagList[0]);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MMI Synchronization Flag Names														*/
/*	***********************************************************************	*/
static const MMI_FLAG_DEF MMI_SYNC_FlagList[] = {
	{	"MMI_FLAG_SYNC_ASYNC",			MMI_FLAG_SYNC_ASYNC			},
	{	"MMI_FLAG_SYNC_SYNC",			MMI_FLAG_SYNC_SYNC			},
	{	"MMI_FLAG_SYNC_INVALIDATE",	MMI_FLAG_SYNC_INVALIDATE	}
};
static const unsigned int MMI_SYNC_FlagCount  =
	sizeof(MMI_SYNC_FlagList) / sizeof(MMI_SYNC_FlagList[0]);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MMI Control Flag Names																	*/
/*	***********************************************************************	*/
static const MMI_FLAG_DEF MMI_MCTL_FlagList[] = {
	{	"MMI_FLAG_MCTL_LOCK",		MMI_FLAG_MCTL_LOCK		},
	{	"MMI_FLAG_MCTL_LOCKAS",		MMI_FLAG_MCTL_LOCKAS		},
	{	"MMI_FLAG_MCTL_SYNC",		MMI_FLAG_MCTL_SYNC		},
	{	"MMI_FLAG_MCTL_UNLOCK",		MMI_FLAG_MCTL_UNLOCK		},
	{	"MMI_FLAG_MCTL_UNLOCKAS",	MMI_FLAG_MCTL_UNLOCKAS	}
};
static const unsigned int MMI_MCTL_FlagCount  =
	sizeof(MMI_MCTL_FlagList) / sizeof(MMI_MCTL_FlagList[0]);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *MMI_MADVFlags(MMI_FLAG in_flags, char *out_string)
#else
char *MMI_MADVFlags(in_flags, out_string)
MMI_FLAG  in_flags;
char     *out_string;
#endif /* #ifndef NARGS */
{
	return(MMI_GetEnumFlag(in_flags, "MMI MADV", MMI_MADV_FlagCount,
		MMI_MADV_FlagList, out_string));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *MMI_PROTFlags(MMI_FLAG in_flags, char *out_string)
#else
char *MMI_PROTFlags(in_flags, out_string)
MMI_FLAG  in_flags;
char     *out_string;
#endif /* #ifndef NARGS */
{
	return(MMI_GetORedFlag(in_flags, "MMI PROT", MMI_PROT_FlagCount,
		MMI_PROT_FlagList, out_string));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *MMI_MMAPFlags(MMI_FLAG in_flags, char *out_string)
#else
char *MMI_MMAPFlags(in_flags, out_string)
MMI_FLAG  in_flags;
char     *out_string;
#endif /* #ifndef NARGS */
{
	return(MMI_GetORedFlag(in_flags, "MMI MMAP", MMI_MMAP_FlagCount,
		MMI_MMAP_FlagList, out_string));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *MMI_SYNCFlags(MMI_FLAG in_flags, char *out_string)
#else
char *MMI_SYNCFlags(in_flags, out_string)
MMI_FLAG  in_flags;
char     *out_string;
#endif /* #ifndef NARGS */
{
	return(MMI_GetEnumFlag(in_flags, "MMI SYNC", MMI_SYNC_FlagCount,
		MMI_SYNC_FlagList, out_string));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *MMI_MCTLFlags(MMI_FLAG in_flags, char *out_string)
#else
char *MMI_MCTLFlags(in_flags, out_string)
MMI_FLAG  in_flags;
char     *out_string;
#endif /* #ifndef NARGS */
{
	return(MMI_GetEnumFlag(in_flags, "MMI MCTL", MMI_MCTL_FlagCount,
		MMI_MCTL_FlagList, out_string));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *MMI_GetEnumFlag(MMI_FLAG in_flags, const char *in_name,
	unsigned int count, const MMI_FLAG_DEF *list, char *out_string)
#else
char *MMI_GetEnumFlag(in_flags, in_name, count, list, out_string)
MMI_FLAG            in_flags;
const char         *in_name;
unsigned int        count;
const MMI_FLAG_DEF *list;
char               *out_string;
#endif /* #ifndef NARGS */
{
	char buffer[STR_VAL2STR_MAX_LEN + 1];

	*out_string = '\0';

	for (; count; count--, list++) {
		if (in_flags == list->value) {
			strcpy(out_string, list->name);
			break;
		}
	}

	if (!(*out_string))
		strcat(strcat(strcat(strcat(strcpy(out_string,
			"*** INVALID "),
			in_name),
			" FLAG = 0x"),
			val2str(((unsigned long) in_flags), 0, 16, "", buffer)),
			" ***");

	return(out_string);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *MMI_GetORedFlag(MMI_FLAG in_flags, const char *in_name,
	unsigned int count, const MMI_FLAG_DEF *list, char *out_string)
#else
char *MMI_GetORedFlag(in_flags, in_name, count, list, out_string)
MMI_FLAG            in_flags;
const char         *in_name;
unsigned int        count;
const MMI_FLAG_DEF *list;
char               *out_string;
#endif /* #ifndef NARGS */
{
	char buffer[STR_VAL2STR_MAX_LEN + 1];

	*out_string = '\0';

	for (; count; count--, list++) {
		if (in_flags & list->value) {
			strcat(strcat(out_string, (*out_string) ? " | " : ""), list->name);
			in_flags -= list->value;
		}
	}

	if ((in_flags) || (!(*out_string)))
		strcat(strcat(strcat(strcat(strcat(strcat(out_string,
			(*out_string) ? " | " : ""),
			"*** INVALID "),
			in_name),
			" FLAG = 0x"),
			val2str(((unsigned long) in_flags), 0, 16, "", buffer)),
			" ***");

	return(out_string);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

COMPAT_FN_DECL(int main, (void));

COMPAT_FN_DECL_STATIC(void TEST_DoEnumFlag,
	(const char *in_name, unsigned int count, const MMI_FLAG_DEF *list));
COMPAT_FN_DECL_STATIC(void TEST_DoORedFlag,
	(const char *in_name, unsigned int count, const MMI_FLAG_DEF *list));

/*	***********************************************************************	*/
int main()
{
	TEST_DoEnumFlag("MMI MADV", MMI_MADV_FlagCount, MMI_MADV_FlagList);
	TEST_DoORedFlag("MMI PROT", MMI_PROT_FlagCount, MMI_PROT_FlagList);
	TEST_DoORedFlag("MMI MMAP", MMI_MMAP_FlagCount, MMI_MMAP_FlagList);
	TEST_DoEnumFlag("MMI SYNC", MMI_SYNC_FlagCount, MMI_SYNC_FlagList);
	TEST_DoEnumFlag("MMI MCTL", MMI_MCTL_FlagCount, MMI_MCTL_FlagList);

	return(MMI_SUCCESS);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void TEST_DoEnumFlag(const char *in_name, unsigned int count,
	const MMI_FLAG_DEF *list)
#else
static void TEST_DoEnumFlag(in_name, count, list)
const char         *in_name;
unsigned int        count;
const MMI_FLAG_DEF *list;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;
	char         buffer[512];

	for (count_1 = 0; count_1 < count; count_1++)
		printf("%10lu = 0x%08lx: %s\n",
			list[count_1].value, list[count_1].value,
			MMI_GetEnumFlag(list[count_1].value, in_name, count, list, buffer));

	printf("%10lu = 0x%08lx: %s\n",
		((unsigned long) 0XFFFFFFFF), ((unsigned long) 0XFFFFFFFF),
		MMI_GetEnumFlag(0xFFFFFFFF, in_name, count, list, buffer));

	STR_EMIT_CharLine('-', 78, NULL, NULL);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void TEST_DoORedFlag(const char *in_name, unsigned int count,
	const MMI_FLAG_DEF *list)
#else
static void TEST_DoORedFlag(in_name, count, list)
const char         *in_name;
unsigned int        count;
const MMI_FLAG_DEF *list;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;
	unsigned int count_2;
	unsigned int count_3;
	char         buffer[512];

	for (count_1 = 0; count_1 < count; count_1++) {
		printf("%10lu = 0x%08lx: %s\n",
			list[count_1].value, list[count_1].value,
			MMI_GetORedFlag(list[count_1].value, in_name, count, list, buffer));
		for (count_2 = 0; count_2 < count; count_2++) {
			if (count_1 == count_2)
				continue;
			printf("%10lu = 0x%08lx: %s\n",
				list[count_1].value | list[count_2].value,
				list[count_1].value | list[count_2].value,
				MMI_GetORedFlag(list[count_1].value | list[count_2].value,
				in_name, count, list, buffer));
		}
		if (count < 3)
			continue;
		for (count_2 = 0; count_2 < count; count_2++) {
			if (count_1 == count_2)
				continue;
			for (count_3 = 0; count_3 < count; count_3++) {
				if ((count_1 == count_3) || (count_2 == count_3))
					continue;
				printf("%10lu = 0x%08lx: %s\n",
			list[count_1].value | list[count_2].value | list[count_3].value,
			list[count_1].value | list[count_2].value | list[count_3].value,
			MMI_GetORedFlag(list[count_1].value | list[count_2].value |
				list[count_3].value,
					in_name, count, list, buffer));
			}
		}
	}

	printf("%10lu = 0x%08lx: %s\n",
		((unsigned long) 0XFFFFFFFF), ((unsigned long) 0XFFFFFFFF),
		MMI_GetORedFlag(0xFFFFFFFF, in_name, count, list, buffer));

	STR_EMIT_CharLine('-', 78, NULL, NULL);
}
/*	***********************************************************************	*/

#endif /* #ifdef TEST_MAIN */


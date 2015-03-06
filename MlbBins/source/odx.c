/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLB Executable Module Source File													*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Emits binary files in a format similar to 'od'.

	Revision History	:	1988-08-22 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1988 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Required include files . . .															*/
/*	***********************************************************************	*/

#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <strfuncs.h>
#include <genfuncs.h>

/*	***********************************************************************	*/

/*
	32 + 1 + (16 * (8 + 1)) + 1 + 1 + 16 + 1 =
	32 + 1 + (16 * 9) + 1 + 1 + 16 + 1       =
	32 + 1 + 144 + 1 + 1 + 16 + 1            =
	33 + 144 + 19                            =
	177 + 19                                 = 186
*/

/*	***********************************************************************	*/
#define ODX_DEFAULT_ADDR_RADIX			16
#define ODX_DEFAULT_CHAR_RADIX			16

#ifndef __MSDOS__
#define ODX_READ_BUFFER_LENGTH			65536
#else
#define ODX_READ_BUFFER_LENGTH			 4096
#endif /* #ifndef __MSDOS__ */

#define ODX_WRITE_LINE_CHAR_COUNT		16

#define ODX_WRITE_MAX_LINE_LENGTH				\
	((sizeof(unsigned long) * CHAR_BIT) + 1 + \
	(ODX_WRITE_LINE_CHAR_COUNT * (CHAR_BIT + 1)) + 1 + 1 + 16 + 1)

#define ODX_WRITE_BUFFER_LENGTH												\
	((((ODX_READ_BUFFER_LENGTH / ODX_WRITE_LINE_CHAR_COUNT) + 2) *	\
	ODX_WRITE_MAX_LINE_LENGTH) + 2)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
typedef struct {
	unsigned int radix;
	unsigned int value_length;
	unsigned int offset_length;
} ODX_RADIX_ITEM;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static const ODX_RADIX_ITEM ODX_RadixList[35] = {
	{	 2,	8,	32	},							/*	Radix =      2							*/
	{	 3,	6,	21	},							/*	Radix =      3							*/
	{	 4,	4,	16	},							/*	Radix =      4							*/
	{	 5,	4,	14	},							/*	Radix =      5							*/
	{	 6,	4,	13	},							/*	Radix =      6							*/
	{	 7,	3,	12	},							/*	Radix =      7							*/
	{	 8,	3,	11	},							/*	Radix =      8							*/
	{	 9,	3,	11	},							/*	Radix =      9							*/
	{	10,	3,	10	},							/*	Radix =     10							*/
	{	11,	3,	10	},							/*	Radix =     11							*/
	{	12,	3,	 9	},							/*	Radix =     12							*/
	{	13,	3,	 9	},							/*	Radix =     13							*/
	{	14,	3,	 9	},							/*	Radix =     14							*/
	{	15,	3,	 9	},							/*	Radix =     15							*/
	{	16,	2,	 8	},							/*	Radix =     16							*/
	{	17,	2,	 8	},							/*	Radix =     17							*/
	{	18,	2,	 8	},							/*	Radix =     18							*/
	{	19,	2,	 8	},							/*	Radix =     19							*/
	{	20,	2,	 8	},							/*	Radix =     20							*/
	{	21,	2,	 8	},							/*	Radix =     21							*/
	{	22,	2,	 8	},							/*	Radix =     22							*/
	{	23,	2,	 8	},							/*	Radix =     23							*/
	{	24,	2,	 7	},							/*	Radix =     24							*/
	{	25,	2,	 7	},							/*	Radix =     25							*/
	{	26,	2,	 7	},							/*	Radix =     26							*/
	{	27,	2,	 7	},							/*	Radix =     27							*/
	{	28,	2,	 7	},							/*	Radix =     28							*/
	{	29,	2,	 7	},							/*	Radix =     29							*/
	{	30,	2,	 7	},							/*	Radix =     30							*/
	{	31,	2,	 7	},							/*	Radix =     31							*/
	{	32,	2,	 7	},							/*	Radix =     32							*/
	{	33,	2,	 7	},							/*	Radix =     33							*/
	{	34,	2,	 7	},							/*	Radix =     34							*/
	{	35,	2,	 7	},							/*	Radix =     35							*/
	{	36,	2,	 7	}							/*	Radix =     36							*/
};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static const char *ODX_RadixCharList = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
/*	***********************************************************************	*/

/*	***********************************************************************	*/
COMPAT_FN_DECL(int         main, (int, char **));
COMPAT_FN_DECL_STATIC(void ODX_DoRadix, (const ODX_RADIX_ITEM *radix_ptr,
	unsigned long in_data_offset, unsigned int in_data_length,
	const unsigned char *in_data_ptr, unsigned char *out_data_ptr));
COMPAT_FN_DECL_STATIC(void ODX_val2str, (unsigned long in_u_long,
	unsigned int in_radix, unsigned int max_length,
	unsigned char *out_data_ptr));
COMPAT_FN_DECL_STATIC(void DoUsage, (char *, int, char *));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int                   return_code      = 0;
	FILE                 *file_ptr         = NULL;
	unsigned char        *read_buffer_ptr  = NULL;
	unsigned char        *write_buffer_ptr = NULL;
	unsigned int          count_1;
	unsigned long         file_size;
   unsigned long         byte_count;
	unsigned int          fread_size;
	const ODX_RADIX_ITEM *radix_ptr;
	char                  error_text[GENFUNCS_MAX_ERROR_TEXT];

	radix_ptr = ODX_RadixList + (16 - 2);

	if (argc == 1)
		DoUsage(argv[0], 1, "Invalid invocation.");

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if ((!stricmp(argv[count_1], "-HELP")) ||
			(!stricmp(argv[count_1], "-H")))
			DoUsage(argv[0], 1, "Help request with '-HELP' noted.");
	}

	if ((read_buffer_ptr = ((unsigned char *) malloc(ODX_READ_BUFFER_LENGTH *
		sizeof(unsigned char)))) == NULL) {
		STR_AllocMsgItem(ODX_READ_BUFFER_LENGTH * sizeof(unsigned char),
			error_text, "Unable to allocate the input buffer");
		return_code = 1;
		goto EXIT_FUNCTION;
	}

	if ((write_buffer_ptr = ((unsigned char *) malloc(ODX_WRITE_BUFFER_LENGTH *
		sizeof(char)))) == NULL) {
		STR_AllocMsgItem(ODX_WRITE_BUFFER_LENGTH * sizeof(unsigned char),
			error_text, "Unable to allocate the output buffer");
		return_code = 1;
		goto EXIT_FUNCTION;
	}

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if ((file_ptr = fopen(argv[count_1], "rb")) == NULL) {
			sprintf(error_text,
				"Unable to open file '%-.500s' for reading --- ",
				argv[count_1]);
			GEN_AppendLastErrorString(0, GENFUNCS_MAX_ERROR_TEXT, error_text);
			return_code = 1;
			goto EXIT_FUNCTION;
		}
      printf("File Name: %s\n", argv[count_1]);
		byte_count = 0;
		fseek(file_ptr, 0L, SEEK_END);
		file_size = ftell(file_ptr);
		fseek(file_ptr, 0L, SEEK_SET);
		while (file_size) {
			fread_size =
				((int) ((file_size > ((unsigned long) ODX_READ_BUFFER_LENGTH)) ?
				((unsigned long) ODX_READ_BUFFER_LENGTH) : file_size));
			fread(read_buffer_ptr, 1, fread_size, file_ptr);
			ODX_DoRadix(radix_ptr, byte_count, fread_size,
				read_buffer_ptr, write_buffer_ptr);
			file_size  -= ((unsigned long) fread_size);
			byte_count += ((unsigned long) fread_size);
		}
		fclose(file_ptr);
		file_ptr = NULL;
		printf("\n");
	}

EXIT_FUNCTION:

	if (read_buffer_ptr != NULL)
		free(read_buffer_ptr);

	if (write_buffer_ptr != NULL)
		free(write_buffer_ptr);

	if (file_ptr != NULL)
		fclose(file_ptr);

	if (return_code)
		fprintf(stderr, "\n\nERROR: %s\n", error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ODX_DoRadix(const ODX_RADIX_ITEM *radix_ptr,
	unsigned long in_data_offset, unsigned int in_data_length,
	const unsigned char *in_data_ptr, unsigned char *out_data_ptr)
#else
static void ODX_DoRadix(radix_ptr, in_data_offset, in_data_length,
	in_data_ptr, out_data_ptr)
const ODX_RADIX_ITEM *radix_ptr;
unsigned long         in_data_offset;
unsigned int          in_data_length;
const unsigned char  *in_data_ptr;
unsigned char        *out_data_ptr;
#endif /* #ifndef NARGS */
{
	unsigned int   count_1;
	unsigned int   tmp_data_length;
	unsigned char *tmp_out_data_ptr;
	unsigned char  tmp_buffer[ODX_WRITE_LINE_CHAR_COUNT];

	if (in_data_length) {
		tmp_out_data_ptr = out_data_ptr;
		if (in_data_offset % ((unsigned long) ODX_WRITE_LINE_CHAR_COUNT)) {
			tmp_data_length = ((unsigned int) (in_data_offset %
				((unsigned long) ODX_WRITE_LINE_CHAR_COUNT)));
			memset(tmp_buffer, ' ', sizeof(tmp_buffer));
			memcpy(tmp_buffer + (ODX_WRITE_LINE_CHAR_COUNT - tmp_data_length),
				in_data_ptr, tmp_data_length);
			ODX_DoRadix(radix_ptr, in_data_offset -
				(((unsigned long) ODX_WRITE_LINE_CHAR_COUNT) +
				((unsigned long) (ODX_WRITE_LINE_CHAR_COUNT - tmp_data_length))),
				tmp_data_length, tmp_buffer, out_data_ptr);
			memset(out_data_ptr + radix_ptr->offset_length + 1, ' ',
				(radix_ptr->value_length + 1) * (ODX_WRITE_LINE_CHAR_COUNT -
				tmp_data_length));
			in_data_offset += ((unsigned long) tmp_data_length);
			in_data_length -= tmp_data_length;
			in_data_ptr    += tmp_data_length;
			if (!(in_data_offset % ((unsigned long) (ODX_WRITE_LINE_CHAR_COUNT *
				ODX_WRITE_LINE_CHAR_COUNT))))
				*out_data_ptr++ = '\n';
		}
		while (in_data_length) {
			tmp_data_length = (in_data_length > ODX_WRITE_LINE_CHAR_COUNT) ?
				ODX_WRITE_LINE_CHAR_COUNT : in_data_length;
			ODX_val2str(in_data_offset, radix_ptr->radix,
				radix_ptr->offset_length,
				out_data_ptr += radix_ptr->offset_length);
			for (count_1 = 0;  count_1 < tmp_data_length; count_1++) {
				*out_data_ptr++  = ' ';
			ODX_val2str(((unsigned long) in_data_ptr[count_1]), radix_ptr->radix,
				radix_ptr->value_length,
				out_data_ptr += radix_ptr->value_length);
			}
			if (tmp_data_length < ODX_WRITE_LINE_CHAR_COUNT) {
				memset(out_data_ptr, ' ', (radix_ptr->value_length + 1) *
					(ODX_WRITE_LINE_CHAR_COUNT - tmp_data_length));
				out_data_ptr += (radix_ptr->value_length + 1) *
					(ODX_WRITE_LINE_CHAR_COUNT - tmp_data_length);
			}
			*out_data_ptr++ = ' ';
			*out_data_ptr++ = '|';
			*out_data_ptr++ = ' ';
			for (count_1 = 0; count_1 < tmp_data_length;
				count_1++, out_data_ptr++)
				*out_data_ptr = (isprint(in_data_ptr[count_1])) ?
					in_data_ptr[count_1] : '.';
			for (count_1 = tmp_data_length; count_1 < ODX_WRITE_LINE_CHAR_COUNT;
				count_1++)
				*out_data_ptr++ = ' ';
			*out_data_ptr++  = '\n';
			in_data_offset  += ((unsigned long) tmp_data_length);
			in_data_length  -= tmp_data_length;
			in_data_ptr     += tmp_data_length;
			if (!(in_data_offset % ((unsigned long) (ODX_WRITE_LINE_CHAR_COUNT *
				ODX_WRITE_LINE_CHAR_COUNT))))
				*out_data_ptr++ = '\n';
		}
		fwrite(tmp_out_data_ptr, 1,
			((unsigned int) (out_data_ptr - tmp_out_data_ptr)), stdout);
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ODX_val2str(unsigned long in_u_long, unsigned int in_radix,
	unsigned int max_length, unsigned char *out_data_ptr)
#else
static void ODX_val2str(in_u_long, in_radix, max_length, out_data_ptr)
unsigned long  in_u_long;
unsigned int   in_radix;
unsigned int   max_length;
unsigned char *out_data_ptr;
#endif /* #ifndef NARGS */
{
	unsigned int  length = 1;
	unsigned long power_value;
	unsigned long old_power_value;

	power_value      = in_radix;
	old_power_value  = 0;

	*out_data_ptr-- = '\0';
	*out_data_ptr-- = ODX_RadixCharList[((unsigned int) (in_u_long %
		((unsigned long) in_radix)))];

	while ((power_value > old_power_value) && (length < max_length)) {
		if (in_u_long >= power_value)
			*out_data_ptr-- =
				ODX_RadixCharList[((unsigned int) ((in_u_long /
					power_value) % ((unsigned long) in_radix)))];
		else
			*out_data_ptr-- = '0';
		length++;
		if ((ULONG_MAX / power_value) < ((unsigned long) in_radix))
        	break;
		old_power_value  = power_value;
		power_value     *= ((unsigned long) in_radix);
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void DoUsage(char *prog, int exit_code, char *exit_text)
#else
static void DoUsage(prog, exit_code, exit_text)
char *prog;
int   exit_code;
char *exit_text;
#endif /* #ifndef NARGS */
{
	FILE *file_ptr = (exit_code) ? stderr : stdout;

	fprintf(file_ptr, "%s\n", exit_text);
	fprintf(file_ptr, "USAGE:\n   %s <file-name> [<file-name> . . .]\n\n",
		extract_file_name(prog));

	exit(exit_code);
}
/*	***********************************************************************	*/


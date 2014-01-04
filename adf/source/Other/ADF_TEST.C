/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	BASE NAME	:	ADF Test

	NAME			:	ADF Test

	SYNOPSIS		:	element_count = SPS_CACHE_BasicGetCountTMP(cache_ptr,
							index_method, record_align_cmp_ptr, index_align_cmp_ptr,
							compare_type, compare_anchor, record_search_flag,
							entry_count, entry_list, in_record_ptr,
							out_index_element, out_record_element);

						unsigned int   element_count;

						SPS_CACHE     *cache_ptr;

						unsigned int   index_method;

						GEN_ALIGN_CMP *record_align_cmp_ptr;

						GEN_ALIGN_CMP *index_align_cmp_ptr;

						unsigned int   compare_type;

						int            compare_anchor;

						int            record_search_flag;

						unsigned int   entry_count;

						const void    *entry_list;

						const void    *in_record_ptr;

						unsigned int  *out_index_element;

						unsigned int  *out_record_element;

	DESCRIPTION:	Paragraph 1.0.0.0 of the description.

						Paragraph 2.0.0.0 of the description.

						This is a paragraph with a number of different character
						formatting attributes. This text is ''bold''. This text is
						``italic``. This text is under-@_lined@_. This text is
						over-@-lined@-. This text is strike-@#through@#. This text
						is is super-'`scripted'`. This text is sub-`'scripted`'.
						The last occurrence of the phrase ``embedded index`` in this
						sentence is an embedded index --- @~embedded index@~.

	PARAMETERS	:	Paragraph 1.0.0.0 of the parameter description. This
						paragraph will be the basic bulleted paragraph test.

						(.)	BB 1.1.0.0
						(..)	BB 1.1.1.0
						(...)	BB 1.1.1.1
						(..)	BB 1.1.2.0
						(...)	BB 1.1.2.1
						(...) BB 1.1.2.2
						(...) BB 1.1.2.3
						(..)	BB 1.1.3.0
						(...)	BB 1.1.3.1
						(...) BB 1.1.3.2
						(.)	BB 1.2.0.0
						(..)	BB 1.2.1.0
						(...)	BB 1.2.1.1
						(..)	BB 1.2.2.0
						(...)	BB 1.2.2.1
						(...) BB 1.2.2.2
						(...) BB 1.2.2.3
						(..)	BB 1.2.3.0
						(...)	BB 1.2.3.1
						(...) BB 1.2.3.2

						Paragraph 2.0.0.0 of the parameter description. This
						paragraph will be the basic numbered paragraph test.

						(+)	NM 2.1.0.0
						(++)	NM 2.1.1.0
						(+++)	NM 2.1.1.1
						(++)	NM 2.1.2.0
						(+++)	NM 2.1.2.1
						(+++) NM 2.1.2.2
						(+++) NM 2.1.2.3
						(++)	NM 2.1.3.0
						(+++)	NM 2.1.3.1
						(+++) NM 2.1.3.2
						(+)	NM 2.2.0.0
						(++)	NM 2.2.1.0
						(+++)	NM 2.2.1.1
						(++)	NM 2.2.2.0
						(+++)	NM 2.2.2.1
						(+++) NM 2.2.2.2
						(+++) NM 2.2.2.3
						(++)	NM 2.2.3.0
						(+++)	NM 2.2.3.1
						(+++) NM 2.2.3.2

						Paragraph 3.0.0.0 of the parameter description. This
						paragraph will be the numbered paragraph test with mixed
						bulleted and indented paragraphs.

						(+)	NM 3.1.0.0
						(++)	NM 3.1.1.0
						(...)	BB 3.1.1.0
						(...)	BB 3.1.2.0
						(+++)	NM 3.1.1.1
						(---)	IN 3.1.1.1
						(---)	IN 3.1.1.2
						(---)	IN 3.1.1.3
						(++)	NM 3.1.2.0
						(+++)	NM 3.1.2.1
						(+++) NM 3.1.2.2
						(+++) NM 3.1.2.3
						(++)	NM 3.1.3.0
						(+++)	NM 3.1.3.1
						(+++) NM 3.1.3.2
						(+)	NM 3.2.0.0
						(++)	NM 3.2.1.0
						(+++)	NM 3.2.1.1
						(++)	NM 3.2.2.0
						(+++)	NM 3.2.2.1
						(+++) NM 3.2.2.2
						(+++) NM 3.2.2.3
						(++)	NM 3.2.3.0
						(+++)	NM 3.2.3.1
						(+++) NM 3.2.3.2

   RETURNS     :  Now we're going to try a number of paragraphs surrounded
						by horizontal rules.

						(|@)A ``formatted`` normal-font paragraph with
						a beginning rule only.

						(@|)A ``formatted`` normal-font paragraph with
						an ending rule only.

						(|@|)A ``formatted`` normal-font paragraph with
						both beginning and ending rules.

{|@}An ``unformatted`` normal-font paragraph with
a beginning rule only.

{@|}An ``unformatted`` normal-font paragraph with
an ending rule only.

{|@|}An ``unformatted`` normal-font paragraph with
both beginning and ending rules.

						<|@>A ``formatted`` small-font paragraph with
						a beginning rule only.

						<@|>A ``formatted`` small-font paragraph with
						an ending rule only.

						<|@|>A ``formatted`` small-font paragraph with
						both beginning and ending rules.

{|@}An ``unformatted`` small-font paragraph with
a beginning rule only.

{@|}An ``unformatted`` small-font paragraph with
an ending rule only.

{|@|}An ``unformatted`` small-font paragraph with
both beginning and ending rules.

						Now for the bulleted, indented, and numbered formatted
						paragraphs with both beginning and ending rules.

						(|.|)	BB 1.1.0.0
						(|..|)	BB 1.1.1.0
						(|...|)	BB 1.1.1.1
						(|..|)	BB 1.1.2.0
						(|...|)	BB 1.1.2.1
						(|...|) BB 1.1.2.2
						(|...|) BB 1.1.2.3
						(|..|)	BB 1.1.3.0
						(|...|)	BB 1.1.3.1
						(|...|) BB 1.1.3.2
						(|.|)	BB 1.2.0.0
						(|..|)	BB 1.2.1.0
						(|...|)	BB 1.2.1.1
						(|..|)	BB 1.2.2.0
						(|...|)	BB 1.2.2.1
						(|...|) BB 1.2.2.2
						(|...|) BB 1.2.2.3
						(|..|)	BB 1.2.3.0
						(|...|)	BB 1.2.3.1
						(|...|) BB 1.2.3.2

						Paragraph 2.0.0.0 of the parameter description. This
						paragraph will be the basic numbered paragraph test.

						(|+|)	NM 2.1.0.0
						(|++|)	NM 2.1.1.0
						(|+++|)	NM 2.1.1.1
						(|++|)	NM 2.1.2.0
						(|+++|)	NM 2.1.2.1
						(|+++|) NM 2.1.2.2
						(|+++|) NM 2.1.2.3
						(|++|)	NM 2.1.3.0
						(|+++|)	NM 2.1.3.1
						(|+++|) NM 2.1.3.2
						(|+|)	NM 2.2.0.0
						(|++|)	NM 2.2.1.0
						(|+++|)	NM 2.2.1.1
						(|++|)	NM 2.2.2.0
						(|+++|)	NM 2.2.2.1
						(|+++|) NM 2.2.2.2
						(|+++|) NM 2.2.2.3
						(|++|)	NM 2.2.3.0
						(|+++|)	NM 2.2.3.1
						(|+++|) NM 2.2.3.2

						Paragraph 3.0.0.0 of the parameter description. This
						paragraph will be the numbered paragraph test with mixed
						bulleted and indented paragraphs.

						(|+|)	NM 3.1.0.0
						(|++|)	NM 3.1.1.0
						(|...|)	BB 3.1.1.0
						(|...|)	BB 3.1.2.0
						(|+++|)	NM 3.1.1.1
						(|---|)	IN 3.1.1.1
						(|---|)	IN 3.1.1.2
						(|---|)	IN 3.1.1.3
						(|++|)	NM 3.1.2.0
						(|+++|)	NM 3.1.2.1
						(|+++|) NM 3.1.2.2
						(|+++|) NM 3.1.2.3
						(|++|)	NM 3.1.3.0
						(|+++|)	NM 3.1.3.1
						(|+++|) NM 3.1.3.2
						(|+|)	NM 3.2.0.0
						(|++|)	NM 3.2.1.0
						(|+++|)	NM 3.2.1.1
						(|++|)	NM 3.2.2.0
						(|+++|)	NM 3.2.2.1
						(|+++|) NM 3.2.2.2
						(|+++|) NM 3.2.2.3
						(|++|)	NM 3.2.3.0
						(|+++|)	NM 3.2.3.1
						(|+++|) NM 3.2.3.2

	NOTES			:	Here's an unformatted area test to check wrapping:

                  The ''MICADS_DC_AREA'' structure is declared as follows:

{|@|}typedef struct {
   char          name[MICADS_DC_MAX_AREA_DESC_NAME + 1];
   unsigned long offset;
   unsigned int  item_size;
   unsigned int  item_count;
   unsigned long total_size;
} MICADS_DC_AREA;

	CAVEATS		:	

	SEE ALSO		:	See Also Item Number One
						See Also Item Number Two

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995, Michael L. Brock

	OUTPUT INDEX:	ADF Test

	PUBLISH XREF:	ADF Test

	PUBLISH NAME:	ADF Test

EOH */
/* *********************************************************************** */


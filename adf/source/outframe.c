/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Emits an ADF entry in 'FRAME' format.

	Revision History	:	1995-12-31 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <memory.h>
#include <stdlib.h>
#include <string.h>

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#define ADF_FRAME_PFORMAT_NAME_LENGTH	(3 + 1 + 2 + 1 + 1 + 1 + 1 + 1 + 1)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
COMPAT_EXTERN_DATA_DECL const ADF_AREA ADF_AreaNameList[];
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
static const char         *ADF_FRAME_BasicHeaderList[] = {
	"<MIFFile 1.01>",
	"#",
	"include(mif_read.m4)",
	"",
	"<Units Uin>",
	"",
	"<ColorCatalog",
	"> # end of ColorCatalog",
	"",
	"<ConditionCatalog",
	"> # end of ConditionCatalog",
	"",
	"<Catalog",
	"> # end of Catalog",
	"",
	"<Page",
	" <PageType ReferencePage>",
	" <PageTag `Reference'>",
	" <PageSize  8.5\" 11.0\">",
	" <PageOrientation Portrait >",
	" <Frame",
	"  <Pen 15>",
	"  <Fill 7>",
	"  <PenWidth  0.5 pt>",
	"  <Separation 0>",
	"  <BRect  0.75\" 4.0\" 7.0\" 0.25\">",
	"  <FrameType NotAnchored >",
	"  <Tag `ADF_LN_2'>",
	"  <PolyLine",
	"   <Pen 0>",
	"   <HeadCap Square >",
	"   <TailCap Square >",
	"   <NumPoints 2>",
	"   <Point  1.0\" 0.125\">",
	"   <Point  7.0\" 0.125\">",
	"  > # end of PolyLine",
	" > # end of Frame",
	" <Frame",
	"  <Pen 15>",
	"  <PenWidth  0.5 pt>",
	"  <BRect  0.75\" 2.5\" 7.0\" 0.25\">",
	"  <FrameType NotAnchored >",
	"  <Tag `ADF_LN_0'>",
	"  <PolyLine",
	"   <Pen 0>",
	"   <NumPoints 2>",
	"   <Point  0.25\" 0.125\">",
	"   <Point  7.0\" 0.125\">",
	"  > # end of PolyLine",
	" > # end of Frame",
	" <Frame",
	"  <Pen 15>",
	"  <BRect  0.75\" 3.25\" 7.0\" 0.25\">",
	"  <FrameType NotAnchored >",
	"  <Tag `ADF_LN_1'>",
	"  <PolyLine",
	"   <Pen 0>",
	"   <NumPoints 2>",
	"   <Point  0.625\" 0.125\">",
	"   <Point  7.0\" 0.125\">",
	"  > # end of PolyLine",
	" > # end of Frame",
	" <Frame",
	"  <Pen 15>",
	"  <BRect  0.75\" 4.75\" 7.0\" 0.25\">",
	"  <FrameType NotAnchored >",
	"  <Tag `ADF_LN_3'>",
	"  <PolyLine",
	"   <Pen 0>",
	"   <NumPoints 2>",
	"   <Point  1.375\" 0.125\">",
	"   <Point  7.0\" 0.125\">",
	"  > # end of PolyLine",
	" > # end of Frame",
	"> # end of Page",
	"<PgfCatalog",
	" <Pgf",
	"  <PgfTag `ADF_Name'>",
	"  <PgfUseNextTag No>",
	"  <PgfNextTag `'>",
	"  <PgfAlignment LeftRight>",
	"  <PgfFIndent  0.25\">",
	"  <PgfLIndent  0.25\">",
	"  <PgfRIndent  0.0\">",
	"  <PgfTopSeparator `'>",
	"  <PgfBotSeparator `'>",
	"  <PgfPlacement Anywhere>",
	"  <PgfSpBefore  5.0 pt>",
	"  <PgfSpAfter  5.0 pt>",
	"  <PgfWithPrev No>",
	"  <PgfWithNext No>",
	"  <PgfBlockSize 3>",
	"  <PgfFont",
	"   <FTag `'>",
	"   <FFamily `NewCenturySchlbk'>",
	"   <FVar `Regular'>",
	"   <FWeight `Regular'>",
	"   <FAngle `Regular'>",
	"   <FSize  10.0 pt>",
	"   <FUnderline No>",
	"   <FOverline No>",
	"   <FStrike No>",
	"   <FSupScript No>",
	"   <FSubScript No>",
	"   <FChangeBar No>",
	"   <FOutline No>",
	"   <FShadow No>",
	"   <FPairKern No>",
	"   <FDoubleUnderline No>",
	"   <FNumericUnderline No>",
	"   <FDX  0.0 pt>",
	"   <FDY  0.0 pt>",
	"   <FDW  0.0 pt>",
	"   <FSeparation 0>",
	"  > # end of PgfFont",
	"  <PgfLineSpacing Fixed>",
	"  <PgfLeading  1.0 pt>",
	"  <PgfAutoNum No>",
	"  <PgfNumTabs 0>",
	"  <PgfHyphenate Yes>",
	"  <HyphenMaxLines 2>",
	"  <HyphenMinPrefix 2>",
	"  <HyphenMinSuffix 2>",
	"  <HyphenMinWord 5>",
	"  <PgfLetterSpace No>",
	"  <PgfMinWordSpace 75>",
	"  <PgfOptWordSpace 100>",
	"  <PgfMaxWordSpace 125>",
	"  <PgfLanguage USEnglish>",
	"  <PgfCellAlignment Top>",
	"  <PgfCellMargins  0.0 pt 0.0 pt 0.0 pt 0.0 pt>",
	"  <PgfCellLMarginFixed No>",
	"  <PgfCellTMarginFixed No>",
	"  <PgfCellRMarginFixed No>",
	"  <PgfCellBMarginFixed No>",
	" > # end of Pgf",
	" <Pgf",
	"  <PgfTag `ADF_Section'>",
	"  <PgfUseNextTag Yes>",
	"  <PgfNextTag `Body'>",
	"  <PgfAlignment LeftRight>",
	"  <PgfFIndent  0.0\">",
	"  <PgfLIndent  0.0\">",
	"  <PgfRIndent  0.0\">",
	"  <PgfTopSeparator `'>",
	"  <PgfBotSeparator `'>",
	"  <PgfPlacement Anywhere>",
	"  <PgfSpBefore  10.0 pt>",
	"  <PgfSpAfter  2.0 pt>",
	"  <PgfWithPrev No>",
	"  <PgfWithNext Yes>",
	"  <PgfBlockSize 1>",
	"  <PgfFont",
	"   <FTag `'>",
	"   <FFamily `NewCenturySchlbk'>",
	"   <FVar `Regular'>",
	"   <FWeight `Bold'>",
	"   <FAngle `Regular'>",
	"   <FSize  10.0 pt>",
	"   <FUnderline No>",
	"   <FOverline No>",
	"   <FStrike No>",
	"   <FSupScript No>",
	"   <FSubScript No>",
	"   <FChangeBar No>",
	"   <FOutline No>",
	"   <FShadow No>",
	"   <FPairKern No>",
	"   <FDoubleUnderline No>",
	"   <FNumericUnderline No>",
	"   <FDX  0.0 pt>",
	"   <FDY  0.0 pt>",
	"   <FDW  0.0 pt>",
	"   <FSeparation 0>",
	"  > # end of PgfFont",
	"  <PgfLineSpacing Fixed>",
	"  <PgfLeading  0.0 pt>",
	"  <PgfAutoNum Yes>",
	"  <PgfNumFormat `'>",
	"  <PgfNumberFont `Numbering'>",
	"  <PgfNumAtEnd No>",
	"  <PgfNumTabs 0>",
	"  <PgfHyphenate Yes>",
	"  <HyphenMaxLines 2>",
	"  <HyphenMinPrefix 2>",
	"  <HyphenMinSuffix 2>",
	"  <HyphenMinWord 5>",
	"  <PgfLetterSpace No>",
	"  <PgfMinWordSpace 75>",
	"  <PgfOptWordSpace 100>",
	"  <PgfMaxWordSpace 125>",
	"  <PgfLanguage USEnglish>",
	"  <PgfCellAlignment Top>",
	"  <PgfCellMargins  0.0 pt 0.0 pt 0.0 pt 0.0 pt>",
	"  <PgfCellLMarginFixed No>",
	"  <PgfCellTMarginFixed No>",
	"  <PgfCellRMarginFixed No>",
	"  <PgfCellBMarginFixed No>",
	" > # end of Pgf",
	" <Pgf",
	"  <PgfTag `ADF_Start'>",
	"  <PgfUseNextTag Yes>",
	"  <PgfNextTag `Body'>",
	"  <PgfAlignment LeftRight>",
	"  <PgfFIndent  0.0\">",
	"  <PgfLIndent  0.0\">",
	"  <PgfRIndent  0.0\">",
	"  <PgfTopSeparator `'>",
	"  <PgfBotSeparator `'>",
	"  <PgfPlacement PageTop>",
	"  <PgfSpBefore  10.0 pt>",
	"  <PgfSpAfter  2.0 pt>",
	"  <PgfWithPrev No>",
	"  <PgfWithNext Yes>",
	"  <PgfBlockSize 1>",
	"  <PgfFont",
	"   <FTag `'>",
	"   <FFamily `NewCenturySchlbk'>",
	"   <FVar `Regular'>",
	"   <FWeight `Bold'>",
	"   <FAngle `Regular'>",
	"   <FSize  10.0 pt>",
	"   <FUnderline No>",
	"   <FOverline No>",
	"   <FStrike No>",
	"   <FSupScript No>",
	"   <FSubScript No>",
	"   <FChangeBar No>",
	"   <FOutline No>",
	"   <FShadow No>",
	"   <FPairKern No>",
	"   <FDoubleUnderline No>",
	"   <FNumericUnderline No>",
	"   <FDX  0.0 pt>",
	"   <FDY  0.0 pt>",
	"   <FDW  0.0 pt>",
	"   <FSeparation 0>",
	"  > # end of PgfFont",
	"  <PgfLineSpacing Fixed>",
	"  <PgfLeading  0.0 pt>",
	"  <PgfAutoNum Yes>",
	"  <PgfNumFormat `'>",
	"  <PgfNumberFont `Numbering'>",
	"  <PgfNumAtEnd No>",
	"  <PgfNumTabs 0>",
	"  <PgfHyphenate Yes>",
	"  <HyphenMaxLines 2>",
	"  <HyphenMinPrefix 2>",
	"  <HyphenMinSuffix 2>",
	"  <HyphenMinWord 5>",
	"  <PgfLetterSpace No>",
	"  <PgfMinWordSpace 75>",
	"  <PgfOptWordSpace 100>",
	"  <PgfMaxWordSpace 125>",
	"  <PgfLanguage USEnglish>",
	"  <PgfCellAlignment Top>",
	"  <PgfCellMargins  0.0 pt 0.0 pt 0.0 pt 0.0 pt>",
	"  <PgfCellLMarginFixed No>",
	"  <PgfCellTMarginFixed No>",
	"  <PgfCellRMarginFixed No>",
	"  <PgfCellBMarginFixed No>",
	" > # end of Pgf",
	" <Pgf",
	"  <PgfTag `ADF_NameTOC'>",
	"  <PgfUseNextTag No>",
	"  <PgfNextTag `'>",
	"  <PgfAlignment LeftRight>",
	"  <PgfFIndent  0.0\">",
	"  <PgfLIndent  0.0\">",
	"  <PgfRIndent  0.0\">",
	"  <PgfTopSeparator `'>",
	"  <PgfBotSeparator `'>",
	"  <PgfPlacement Anywhere>",
	"  <PgfRunInDefaultPunct `. '>",
	"  <PgfSpBefore  0.0 pt>",
	"  <PgfSpAfter  0.0 pt>",
	"  <PgfWithPrev No>",
	"  <PgfWithNext No>",
	"  <PgfBlockSize 1>",
	"  <PgfFont",
	"   <FTag `'>",
	"   <FFamily `NewCenturySchlbk'>",
	"   <FVar `Regular'>",
	"   <FWeight `Regular'>",
	"   <FAngle `Regular'>",
	"   <FSize  10.0 pt>",
	"   <FUnderline No>",
	"   <FOverline No>",
	"   <FStrike No>",
	"   <FSupScript No>",
	"   <FSubScript No>",
	"   <FChangeBar No>",
	"   <FOutline No>",
	"   <FShadow No>",
	"   <FPairKern No>",
	"   <FDoubleUnderline No>",
	"   <FNumericUnderline No>",
	"   <FDX  0.0 pt>",
	"   <FDY  0.0 pt>",
	"   <FDW  0.0 pt>",
	"   <FSeparation 0>",
	"  > # end of PgfFont",
	"  <PgfLineSpacing Fixed>",
	"  <PgfLeading  2.0 pt>",
	"  <PgfAutoNum No>",
	"  <PgfNumTabs 1>",
	"  <TabStop",
	"   <TSX  7.0\">",
	"   <TSType Right>",
	"   <TSLeaderStr `.'>",
	"  > # end of TabStop",
	"  <PgfHyphenate Yes>",
	"  <HyphenMaxLines 2>",
	"  <HyphenMinPrefix 2>",
	"  <HyphenMinSuffix 2>",
	"  <HyphenMinWord 5>",
	"  <PgfLetterSpace No>",
	"  <PgfMinWordSpace 75>",
	"  <PgfOptWordSpace 100>",
	"  <PgfMaxWordSpace 125>",
	"  <PgfLanguage USEnglish>",
	"  <PgfCellAlignment Top>",
	"  <PgfCellMargins  0.0 pt 0.0 pt 0.0 pt 0.0 pt>",
	"  <PgfCellLMarginFixed No>",
	"  <PgfCellTMarginFixed No>",
	"  <PgfCellRMarginFixed No>",
	"  <PgfCellBMarginFixed No>",
	" > # end of Pgf",
	" <Pgf",
	"  <PgfTag `ADF_NameAPL'>",
	"  <PgfUseNextTag No >",
	"  <PgfNextTag `'>",
	"  <PgfAlignment LeftRight >",
	"  <PgfFIndent  0.0\">",
	"  <PgfLIndent  0.0\">",
	"  <PgfRIndent  0.0\">",
	"  <PgfTopSeparator `'>",
	"  <PgfBotSeparator `'>",
	"  <PgfPlacement Anywhere >",
	"  <PgfSpBefore  0.0 pt>",
	"  <PgfSpAfter  0.0 pt>",
	"  <PgfWithPrev No >",
	"  <PgfWithNext No >",
	"  <PgfBlockSize 1>",
	"  <PgfFont",
	"   <FTag `'>",
	"   <FFamily `NewCenturySchlbk'>",
	"   <FVar `Regular'>",
	"   <FWeight `Regular'>",
	"   <FAngle `Regular'>",
	"   <FSize  10.0 pt>",
	"   <FUnderline No >",
	"   <FOverline No >",
	"   <FStrike No >",
	"   <FSupScript No >",
	"   <FSubScript No >",
	"   <FChangeBar No >",
	"   <FOutline No >",
	"   <FShadow No >",
	"   <FPairKern No >",
	"   <FDoubleUnderline No >",
	"   <FNumericUnderline No >",
	"   <FDX  0.0 pt>",
	"   <FDY  0.0 pt>",
	"   <FDW  0.0 pt>",
	"   <FSeparation 0>",
	"  > # end of PgfFont",
	"  <PgfLineSpacing Fixed >",
	"  <PgfLeading  2.0 pt>",
	"  <PgfAutoNum No >",
	"  <PgfNumTabs 1>",
	"  <TabStop",
	"   <TSX  7.0\">",
	"   <TSType Right >",
	"   <TSLeaderStr `.'>",
	"  > # end of TabStop",
	"  <PgfHyphenate Yes >",
	"  <HyphenMaxLines 2>",
	"  <HyphenMinPrefix 2>",
	"  <HyphenMinSuffix 2>",
	"  <HyphenMinWord 5>",
	"  <PgfLetterSpace No >",
	"  <PgfMinWordSpace 75>",
	"  <PgfOptWordSpace 100>",
	"  <PgfMaxWordSpace 125>",
	"  <PgfLanguage USEnglish >",
	"  <PgfCellAlignment Top >",
	"  <PgfCellMargins  0.0 pt 0.0 pt 0.0 pt 0.0 pt>",
	"  <PgfCellLMarginFixed No >",
	"  <PgfCellTMarginFixed No >",
	"  <PgfCellRMarginFixed No >",
	"  <PgfCellBMarginFixed No >",
	" > # end of Pgf"
};
static const unsigned int  ADF_FRAME_BasicHeaderCount  =
	sizeof(ADF_FRAME_BasicHeaderList) / sizeof(ADF_FRAME_BasicHeaderList[0]);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static const char         *ADF_FRAME_VariableHeaderList[] = {
	" <VariableFormat",
	"  <VariableName `Page Count'>",
	"  <VariableDef `<$lastpagenum\\>'>",
	" > # end of VariableFormat",
	" <VariableFormat",
	"  <VariableName `Current Date (Long)'>",
	"  <VariableDef `<$monthname\\> <$daynum\\>, <$year\\>'>",
	" > # end of VariableFormat",
	" <VariableFormat",
	"  <VariableName `Current Date (Short)'>",
	"  <VariableDef `<$monthnum\\>/<$daynum\\>/<$shortyear\\>'>",
	" > # end of VariableFormat",
	" <VariableFormat",
	"  <VariableName `Modification Date (Long)'>",
	"  <VariableDef `<$monthname\\> <$daynum\\>, <$year\\> <$hour\\>:<$minute00\\> <$ampm\\>'>",
	" > # end of VariableFormat",
	" <VariableFormat",
	"  <VariableName `Modification Date (Short)'>",
	"  <VariableDef `<$monthnum\\>/<$daynum\\>/<$shortyear\\>'>",
	" > # end of VariableFormat",
	" <VariableFormat",
	"  <VariableName `Creation Date (Long)'>",
	"  <VariableDef `<$monthname\\> <$daynum\\>, <$year\\>'>",
	" > # end of VariableFormat",
	" <VariableFormat",
	"  <VariableName `Creation Date (Short)'>",
	"  <VariableDef `<$monthnum\\>/<$daynum\\>/<$shortyear\\>'>",
	" > # end of VariableFormat",
	" <VariableFormat",
	"  <VariableName `Filename (Long)'>",
	"  <VariableDef `<$fullfilename\\>'>",
	" > # end of VariableFormat",
	" <VariableFormat",
	"  <VariableName `Filename (Short)'>",
	"  <VariableDef `<$filename\\>'>",
	" > # end of VariableFormat",
	" <VariableFormat",
	"  <VariableName `Running H/F 1'>",
	"  <VariableDef `<$paratext[ADF_Name]\\>'>",
	" > # end of VariableFormat",
	" <VariableFormat",
	"  <VariableName `Running H/F 2'>",
	"  <VariableDef `<$paranum[Level_1_Head,Level_2_Head,Appendix]\\>'>",
	" > # end of VariableFormat",
	" <VariableFormat",
	"  <VariableName `Current Page #'>",
	"  <VariableDef `<$curpagenum\\>'>",
	" > # end of VariableFormat",
	" <VariableFormat",
	"  <VariableName `Running H/F 3'>",
	"  <VariableDef `<$paratext[ADF_Name]'>",
	" > # end of VariableFormat",
	" <VariableFormat",
	"  <VariableName `Running H/F 4'>",
	"  <VariableDef `<$paranum[Appendix]\\>'>",
	" > # end of VariableFormat",
	" <VariableFormat",
	"  <VariableName `Table Continuation'>",
	"  <VariableDef ` (Continued)'>",
	" > # end of VariableFormat",
	" <VariableFormat",
	"  <VariableName `Table Sheet'>",
	"  <VariableDef ` (Sheet <$tblsheetnum\\> of <$tblsheetcount\\>)'>",
	" > # end of VariableFormat",
	" <VariableFormat",
	"  <VariableName `Left Page Footer'>",
	"  <VariableDef `Last Revised: $monthname $daynum, $year'>",
	" > # end of VariableFormat"
};
static const unsigned int  ADF_FRAME_VariableHeaderCount  =
	sizeof(ADF_FRAME_VariableHeaderList) /
	sizeof(ADF_FRAME_VariableHeaderList[0]);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(void  ADF_FRAME_DoHeaderByEntry,
	(ADF_CONTROL *control_ptr, const ADF_ENTRY *entry_ptr,
	ADF_ENTRY_DATA *entry_data_list, const time_t *output_date,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL_STATIC(void  ADF_FRAME_DoHeaderByFile,
	(const ADF_CONTROL *control_ptr, unsigned int entry_index,
	const time_t *output_date, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL_STATIC(int   ADF_FRAME_OutputBasic,
	(ADF_CONTROL *control_ptr, const ADF_ENTRY *entry_ptr,
	ADF_ENTRY_DATA *entry_data_list, const time_t *output_date,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text));
COMPAT_FN_DECL_STATIC(int   ADF_FRAME_OutputSection,
	(ADF_CONTROL *control_ptr, const ADF_ENTRY *entry_ptr,
	ADF_ENTRY_DATA *entry_data_ptr, int format_flag,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text));
COMPAT_FN_DECL_STATIC(int   ADF_FRAME_OutputCodeSyntax,
	(ADF_CONTROL *control_ptr, const ADF_ENTRY *entry_ptr,
	ADF_ENTRY_DATA *entry_data_ptr, STR_FUNC_TYPE_fprintf output_function,
	void *output_control, char *error_text));
COMPAT_FN_DECL_STATIC(int   ADF_FRAME_OutputSeeAlso,
	(ADF_CONTROL *control_ptr, const ADF_ENTRY *entry_ptr,
	ADF_ENTRY_DATA *entry_data_ptr, STR_FUNC_TYPE_fprintf output_function,
	void *output_control, char *error_text));
COMPAT_FN_DECL_STATIC(int   ADF_FRAME_EmitParaText,
	(ADF_CONTROL *control_ptr, const ADF_ENTRY *entry_ptr,
	unsigned int para_line_count, const ADF_PARA_TEXT *para_line_list,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text));
COMPAT_FN_DECL_STATIC(int   ADF_FRAME_EmitPlainParaText,
	(ADF_CONTROL *control_ptr, const ADF_ENTRY *entry_ptr,
	unsigned int para_line_count, const ADF_PARA_TEXT *para_line_list,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text));
COMPAT_FN_DECL_STATIC(int   ADF_FRAME_OutputIndexRange,
	(ADF_CONTROL *control_ptr, const ADF_ENTRY *entry_ptr,
	ADF_ENTRY_DATA *entry_data_ptr, unsigned int area_index,
	int start_range_flag, int frame_index_type,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text));
COMPAT_FN_DECL_STATIC(void  ADF_FRAME_OutputIndexString,
	(const char *out_text, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL_STATIC(void  ADF_FRAME_OutputIndexText,
	(unsigned int out_length, const char *out_text,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL_STATIC(void  ADF_FRAME_EmitString,
	(const char *out_text, unsigned int padding, int exact_flag,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL_STATIC(void  ADF_FRAME_EmitText,
	(unsigned int out_length, const char *out_text, unsigned int padding,
	int exact_flag, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL_STATIC(void ADF_FRAME_OutputString,
	(const char *out_text, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL_STATIC(void  ADF_FRAME_OutputText,
	(unsigned int out_length, const char *out_text,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL_STATIC(int   ADF_FRAME_EmitAnchor,
	(ADF_CONTROL *control_ptr, const ADF_ENTRY *entry_ptr,
	unsigned int htext_index, int external_flag,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text));
COMPAT_FN_DECL_STATIC(int   ADF_FRAME_GetXRefSrcFile,
	(ADF_CONTROL *control_ptr, const ADF_ENTRY *entry_ptr,
	unsigned int htext_index, int external_flag, char *error_text));
COMPAT_FN_DECL_STATIC(void  ADF_FRAME_DoComment,
	(const char *in_string, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL_STATIC(void  ADF_FRAME_DoCommentsFloating,
	(const char *in_string_1, const char *in_string_2,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL_STATIC(void  ADF_FRAME_DoBorder,
	(STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL_STATIC(char *ADF_FRAME_GetParaName,
	(unsigned int pformat_index, char *pformat_name));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_FRAME_OutputByEntry(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, char *error_text)
#else
int ADF_FRAME_OutputByEntry(control_ptr, entry_ptr, error_text)
ADF_CONTROL     *control_ptr;
const ADF_ENTRY *entry_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code;
	unsigned int   alloc_length;
	ADF_ENTRY_DATA entry_data_list[ADF_AREA_COUNT];

	if (control_ptr->quiet_flag != ADF_TRUE)
		fprintf(stderr, "%s(%s) --- ", entry_ptr->base_name,
			entry_ptr->file_name);

	alloc_length = ((control_ptr->output_dir == NULL) ? 0 :
		strlen(control_ptr->output_dir)) + strlen(entry_ptr->base_name) + 256;

	if ((return_code = ADF_OUT_AllocFileString(control_ptr, alloc_length,
		error_text)) == ADF_SUCCESS) {
		sprintf(control_ptr->output_file_name, "%s%s%s.mif",
			(control_ptr->output_dir == NULL) ? "" : control_ptr->output_dir,
			(control_ptr->output_dir == NULL) ? "" : "/", entry_ptr->base_name);
		ADF_OUT_CleanName(control_ptr->output_file_name);
		if ((return_code = ADF_OUT_OpenOutputFile(control_ptr,
			error_text)) == ADF_SUCCESS) {
			if ((return_code = ADF_GetEntry(control_ptr, entry_ptr,
				entry_data_list, error_text)) == ADF_SUCCESS) {
				return_code = ADF_FRAME_OutputBasic(control_ptr, entry_ptr,
					entry_data_list, NULL, STR_FUNC_TYPE_fprintf_CAST(fprintf),
					control_ptr->output_file_ptr, error_text);
				ADF_INIT_AreaDataList(entry_data_list);
			}
			fclose(control_ptr->output_file_ptr);
			control_ptr->output_file_ptr = NULL;
			if ((control_ptr->log_flag == ADF_TRUE) &&
				(return_code == ADF_SUCCESS))
				ADF_OUT_LogOutputFile(control_ptr, entry_ptr,
					control_ptr->output_file_name);
		}
	}

	if (control_ptr->quiet_flag != ADF_TRUE) {
		if (return_code != ADF_SUCCESS)
			fprintf(stderr, "ERROR: %s\n", error_text);
		else
			fprintf(stderr, "OK\n");
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_FRAME_OutputToStdout(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, const time_t *output_date, char *error_text)
#else
int ADF_FRAME_OutputToStdout(control_ptr, entry_ptr, output_date, error_text)
ADF_CONTROL     *control_ptr;
const ADF_ENTRY *entry_ptr;
const time_t    *output_date;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code;
	ADF_ENTRY_DATA entry_data_list[ADF_AREA_COUNT];

	if (control_ptr->quiet_flag != ADF_TRUE)
		fprintf(stderr, "%s(%s) --- ", entry_ptr->base_name,
			entry_ptr->file_name);

	if ((return_code = ADF_GetEntry(control_ptr, entry_ptr, entry_data_list,
		error_text)) == ADF_SUCCESS) {
		return_code = ADF_FRAME_OutputBasic(control_ptr, entry_ptr,
			entry_data_list, output_date, STR_FUNC_TYPE_fprintf_CAST(fprintf),
			stdout, error_text);
		ADF_INIT_AreaDataList(entry_data_list);
		if ((control_ptr->log_flag == ADF_TRUE) && (return_code == ADF_SUCCESS))
			ADF_OUT_LogOutputFile(control_ptr, entry_ptr, NULL);
	}

	if (control_ptr->quiet_flag != ADF_TRUE) {
		if (return_code != ADF_SUCCESS)
			fprintf(stderr, "ERROR: %s\n", error_text);
		else
			fprintf(stderr, "OK\n");
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_FRAME_OutputByFile(ADF_CONTROL *control_ptr, unsigned int *entry_index,
	char *error_text)
#else
int ADF_FRAME_OutputByFile(control_ptr, entry_index, error_text)
ADF_CONTROL  *control_ptr;
unsigned int *entry_index;
char         *error_text;
#endif /* #ifndef NARGS */
{
	int             return_code = ADF_SUCCESS;
	char           *core_name;
	unsigned int    in_entry_index;
	unsigned int    alloc_length;
	ADF_ENTRY      *entry_ptr;
	ADF_ENTRY_DATA  entry_data_list[ADF_AREA_COUNT];
	time_t          output_date;

	in_entry_index = *entry_index;
	entry_ptr      = control_ptr->in_entry_order_list[*entry_index];
	core_name      = entry_ptr->core_name;

	alloc_length   = ((control_ptr->output_dir == NULL) ? 0 :
		strlen(control_ptr->output_dir)) + strlen(core_name) + 256;

	for ( ; (*entry_index < control_ptr->in_entry_order_count) &&
		(!strcmp(control_ptr->in_entry_order_list[*entry_index]->core_name,
		core_name)); (*entry_index)++) {
		entry_ptr = control_ptr->in_entry_order_list[*entry_index];
		if (control_ptr->quiet_flag != ADF_TRUE)
			fprintf(stderr, "%s(%s) --- ", entry_ptr->file_name,
				entry_ptr->base_name);
		if (*entry_index == in_entry_index) {
			if ((return_code = ADF_OUT_AllocFileString(control_ptr, alloc_length,
				error_text)) != ADF_SUCCESS)
				break;
			sprintf(control_ptr->output_file_name, "%s%s%s.mif",
				(control_ptr->output_dir == NULL) ? "" : control_ptr->output_dir,
				(control_ptr->output_dir == NULL) ? "" : "/", core_name);
			ADF_OUT_CleanName(control_ptr->output_file_name);
			if ((return_code = ADF_OUT_OpenOutputFile(control_ptr,
				error_text)) != ADF_SUCCESS)
				break;
			time(&output_date);
			if (control_ptr->output_comment_flag == ADF_TRUE)
				ADF_FRAME_DoHeaderByFile(control_ptr, *entry_index, &output_date,
					STR_FUNC_TYPE_fprintf_CAST(fprintf), control_ptr->output_file_ptr);
		}
		else
			fprintf(control_ptr->output_file_ptr, "\n");
		if ((return_code = ADF_GetEntry(control_ptr, entry_ptr, entry_data_list,
			error_text)) != ADF_SUCCESS)
			break;
		return_code = ADF_FRAME_OutputBasic(control_ptr, entry_ptr,
			entry_data_list, &output_date, STR_FUNC_TYPE_fprintf_CAST(fprintf),
			control_ptr->output_file_ptr, error_text);
		ADF_INIT_AreaDataList(entry_data_list);
		if (return_code != ADF_SUCCESS)
			break;
		if (control_ptr->quiet_flag != ADF_TRUE)
			fprintf(stderr, "OK\n");
		if ((control_ptr->log_flag == ADF_TRUE) && (return_code == ADF_SUCCESS))
			ADF_OUT_LogOutputFile(control_ptr, entry_ptr,
				control_ptr->output_file_name);
	}

	if (control_ptr->output_file_ptr != NULL) {
		fclose(control_ptr->output_file_ptr);
		control_ptr->output_file_ptr = NULL;
	}

	if ((control_ptr->quiet_flag != ADF_TRUE) && (return_code != ADF_SUCCESS))
		fprintf(stderr, "ERROR: %s\n", error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_FRAME_OutputStart(ADF_CONTROL *control_ptr, const char *output_name,
	const time_t *output_date, STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
void ADF_FRAME_OutputStart(control_ptr, output_name, output_date,
	output_function, output_control)
ADF_CONTROL           *control_ptr;
const char            *output_name;
const time_t          *output_date;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	unsigned int           count_1;
	const ADF_PFORMAT_DEF *pformat_ptr;
	unsigned int           para_level;
	double                 first_margin;
	double                 left_margin;
	char                   pformat_name[ADF_FRAME_PFORMAT_NAME_LENGTH + 1];

	STR_EMIT_SetDefaults(&output_function, &output_control);

	for (count_1 = 0; count_1 < ADF_FRAME_BasicHeaderCount; count_1++)
		(*output_function)(output_control, "%s\n",
			ADF_FRAME_BasicHeaderList[count_1]);

	for (count_1 = 0; count_1 < ADF_PFORMAT_COUNT; count_1++) {
		pformat_ptr = ADF_GetParaFormat(count_1);
		if ((pformat_ptr->supported_flag != ADF_TRUE) ||
			(pformat_ptr->begin_rule_flag == ADF_TRUE) ||
			(pformat_ptr->end_rule_flag == ADF_TRUE))
			continue;
		para_level   = pformat_ptr->indent_level;
		first_margin = (pformat_ptr->format_type == ADF_PFORMAT_TYPE_IN) ?
			(0.250 + (((double) para_level) * 0.375)) :
			(pformat_ptr->format_type == ADF_PFORMAT_TYPE_NM) ?
			(0.250 + (((double) (para_level - 1)) * 0.375)) :
			(pformat_ptr->format_type == ADF_PFORMAT_TYPE_BB) ?
			(0.250 + (((double) (para_level - 1)) * 0.375)) :
			(0.250 + ((double) para_level * 0.375));
		left_margin  = first_margin +
			((pformat_ptr->format_type == ADF_PFORMAT_TYPE_NONE) ? 0.0 :
			(pformat_ptr->format_type == ADF_PFORMAT_TYPE_IN) ? 0.0 :
			(pformat_ptr->format_type == ADF_PFORMAT_TYPE_NM) ? 0.375 :
			(pformat_ptr->format_type == ADF_PFORMAT_TYPE_BB) ? 0.375 : 0.250);
		(*output_function)(output_control, " <Pgf\n");
		(*output_function)(output_control, "  <PgfTag `%s'>\n",
			ADF_FRAME_GetParaName(count_1, pformat_name));
		(*output_function)(output_control, "  <PgfUseNextTag No>\n");
		(*output_function)(output_control, "  <PgfNextTag `'>\n");
		(*output_function)(output_control, "  <PgfAlignment LeftRight>\n");
		(*output_function)(output_control, "  <PgfFIndent %lf\">\n",
			first_margin);
		(*output_function)(output_control, "  <PgfLIndent %lf\">\n",
			left_margin);
		(*output_function)(output_control, "  <PgfRIndent 0.0>\n");
		(*output_function)(output_control, "  <PgfTopSeparator `'>\n");
		(*output_function)(output_control, "  <PgfBotSeparator `'>\n");
		(*output_function)(output_control, "  <PgfPlacement Anywhere>\n");
		(*output_function)(output_control, "  <PgfSpBefore  %s pt>\n",
			(pformat_ptr->small_font_flag == ADF_TRUE) ? "2.0" : "5.0");
		(*output_function)(output_control, "  <PgfSpAfter  %s pt>\n",
			(pformat_ptr->small_font_flag == ADF_TRUE) ? "2.0" : "5.0");
		(*output_function)(output_control, "  <PgfWithPrev No>\n");
		(*output_function)(output_control, "  <PgfWithNext No>\n");
		(*output_function)(output_control, "  <PgfBlockSize 1>\n");
		(*output_function)(output_control, "  <PgfFont\n");
		(*output_function)(output_control, "   <FTag `'>\n");
		(*output_function)(output_control, "   <FFamily  `%s'>\n",
			(pformat_ptr->small_font_flag == ADF_TRUE) ? "Courier" :
			"NewCenturySchlbk");
		(*output_function)(output_control, "   <FVar `Regular'>\n");
		(*output_function)(output_control, "   <FWeight `Regular'>\n");
		(*output_function)(output_control, "   <FAngle `Regular'>\n");
		(*output_function)(output_control, "   <FSize  %s pt>\n",
			(pformat_ptr->small_font_flag == ADF_TRUE) ? "8.0" : "10.0");
		(*output_function)(output_control, "   <FUnderline No>\n");
		(*output_function)(output_control, "   <FOverline No>\n");
		(*output_function)(output_control, "   <FStrike No>\n");
		(*output_function)(output_control, "   <FSupScript No>\n");
		(*output_function)(output_control, "   <FSubScript No>\n");
		(*output_function)(output_control, "   <FChangeBar No>\n");
		(*output_function)(output_control, "   <FOutline No>\n");
		(*output_function)(output_control, "   <FShadow No>\n");
		(*output_function)(output_control, "   <FPairKern No>\n");
		(*output_function)(output_control, "   <FDoubleUnderline No>\n");
		(*output_function)(output_control, "   <FNumericUnderline No>\n");
		(*output_function)(output_control, "   <FDX  0.0 pt>\n");
		(*output_function)(output_control, "   <FDY  0.0 pt>\n");
		(*output_function)(output_control, "   <FDW  0.0 pt>\n");
		(*output_function)(output_control, "   <FSeparation 0>\n");
		(*output_function)(output_control, "  > # end of PgfFont\n");
		(*output_function)(output_control, "  <PgfLineSpacing Fixed>\n");
		(*output_function)(output_control, "  <PgfLeading  1.0 pt>\n");
		(*output_function)(output_control, "  <PgfAutoNum Yes>\n");
		(*output_function)(output_control, "  <PgfNumFormat `%s'>\n",
			(pformat_ptr->format_type == ADF_PFORMAT_TYPE_BB) ?
			"\\t\\xa5 \\t" : "");
		(*output_function)(output_control, "  <PgfNumberFont `'>\n");
		(*output_function)(output_control, "  <PgfNumAtEnd No>\n");
		if (pformat_ptr->format_type == ADF_PFORMAT_TYPE_NM) {
			(*output_function)(output_control, "  <PgfNumTabs 2>\n");
			(*output_function)(output_control, "  <TabStop <TSX %lf\"> %s>\n",
				first_margin + 0.250,
				"<TSType Decimal> <TSLeaderStr ` '> <TSDecimalChar 46>");
			(*output_function)(output_control, "  <TabStop <TSX %lf\"> %s>\n",
				first_margin + 0.375, "<TSType Left> <TSLeaderStr ` '>");
		}
		else if (pformat_ptr->format_type == ADF_PFORMAT_TYPE_BB) {
			(*output_function)(output_control, "  <PgfNumTabs 2>\n");
			(*output_function)(output_control, "  <TabStop <TSX %lf\"> %s>\n",
				first_margin + 0.125, "<TSType Left> <TSLeaderStr ` '>");
			(*output_function)(output_control, "  <TabStop <TSX %lf\"> %s>\n",
				first_margin + 0.375, "<TSType Left> <TSLeaderStr ` '>");
		}
		else
			(*output_function)(output_control, "  <PgfNumTabs 0>\n");
		(*output_function)(output_control, "  <PgfHyphenate Yes>\n");
		(*output_function)(output_control, "  <HyphenMaxLines 2>\n");
		(*output_function)(output_control, "  <HyphenMinPrefix 2>\n");
		(*output_function)(output_control, "  <HyphenMinSuffix 2>\n");
		(*output_function)(output_control, "  <HyphenMinWord 5>\n");
		(*output_function)(output_control, "  <PgfLetterSpace No>\n");
		(*output_function)(output_control, "  <PgfMinWordSpace 75>\n");
		(*output_function)(output_control, "  <PgfOptWordSpace 100>\n");
		(*output_function)(output_control, "  <PgfMaxWordSpace 125>\n");
		(*output_function)(output_control, "  <PgfLanguage USEnglish>\n");
		(*output_function)(output_control, "  <PgfCellAlignment Top>\n");
		(*output_function)(output_control,
			"  <PgfCellMargins  0.0 pt 0.0 pt 0.0 pt 0.0 pt>\n");
		(*output_function)(output_control, "  <PgfCellLMarginFixed No>\n");
		(*output_function)(output_control, "  <PgfCellTMarginFixed No>\n");
		(*output_function)(output_control, "  <PgfCellRMarginFixed No>\n");
		(*output_function)(output_control, "  <PgfCellBMarginFixed No>\n");
		(*output_function)(output_control, " > # end of Pgf\n");
	}

	(*output_function)(output_control, "> # end of PgfCatalog\n");
	(*output_function)(output_control, "\n");

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Emit the font catalog . . .												*/
	/*	*****************************************************************	*/
	(*output_function)(output_control, "%s\n", "<FontCatalog");
	(*output_function)(output_control, "%s\n", " <Font");
	(*output_function)(output_control, "%s\n", "  <FTag `HyperText_ON'>");
	(*output_function)(output_control, "%s\n", "  <FLocked No>");
	(*output_function)(output_control, "%s\n", "  <FSeparation 4>");
	(*output_function)(output_control, "%s\n", "  <FColor `Blue'>");
	(*output_function)(output_control, "%s\n", " > # end of Font");
	(*output_function)(output_control, "%s\n", " <Font");
	(*output_function)(output_control, "%s\n", "  <FTag `HyperText_OFF'>");
	(*output_function)(output_control, "%s\n", "  <FLocked No>");
	(*output_function)(output_control, "%s\n", "  <FSeparation 4>");
	(*output_function)(output_control, "%s\n", "  <FColor `Black'>");
	(*output_function)(output_control, "%s\n", " > # end of Font");
	(*output_function)(output_control, "%s\n", "> # end of FontCatalog");
	(*output_function)(output_control, "\n");
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Emit variable formats and definitions . . .							*/
	/*	*****************************************************************	*/
	(*output_function)(output_control, "%s\n", "<VariableFormats");
	for (count_1 = 0; count_1 < ADF_FRAME_VariableHeaderCount; count_1++)
		(*output_function)(output_control, "%s\n",
			ADF_FRAME_VariableHeaderList[count_1]);

	(*output_function)(output_control, "%s\n",
		" <VariableFormat");
	(*output_function)(output_control, "%s\n",
		"  <VariableName `DocumentName'>");
	(*output_function)(output_control, "  <VariableDef `%s'>\n",
		(control_ptr->frame_data.document_name == NULL) ?
		"*** DOCUMENT NAME ***" : control_ptr->frame_data.document_name);
	(*output_function)(output_control, "%s\n",
		" > # end of VariableFormat");
	(*output_function)(output_control, "%s\n",
		" <VariableFormat");
	(*output_function)(output_control, "%s\n",
		"  <VariableName `OwnerName'>");
	(*output_function)(output_control, "  <VariableDef `%s'>\n",
		(control_ptr->frame_data.owner_name == NULL) ?
		"*** OWNER NAME ***" : control_ptr->frame_data.owner_name);
	(*output_function)(output_control, "%s\n",
		" > # end of VariableFormat");
	(*output_function)(output_control, "%s\n",
		" <VariableFormat");
	(*output_function)(output_control, "%s\n",
		"  <VariableName `CopyrightName'>");
	(*output_function)(output_control, "  <VariableDef `%s'>\n",
		(control_ptr->frame_data.copyright == NULL) ?
		"*** COPYRIGHT ***" : control_ptr->frame_data.copyright);
	(*output_function)(output_control, "%s\n",
		" > # end of VariableFormat");
	(*output_function)(output_control, "%s\n",
		" <VariableFormat");
	(*output_function)(output_control, "%s\n",
		"  <VariableName `CoverName_1'>");
	(*output_function)(output_control, "  <VariableDef `%s'>\n",
		(control_ptr->frame_data.cover_name_1 == NULL) ?
		"*** COVER NAME  1 ***" : control_ptr->frame_data.cover_name_1);
	(*output_function)(output_control, "%s\n",
		" > # end of VariableFormat");
	(*output_function)(output_control, "%s\n",
		" <VariableFormat");
	(*output_function)(output_control, "%s\n",
		"  <VariableName `CoverName_2'>");
	(*output_function)(output_control, "  <VariableDef `%s'>\n",
		(control_ptr->frame_data.cover_name_2 == NULL) ?
		"*** COVER NAME 2 ***" : control_ptr->frame_data.cover_name_2);
	(*output_function)(output_control, "%s\n",
		" > # end of VariableFormat");
	(*output_function)(output_control, "%s\n",
		" <VariableFormat");
	(*output_function)(output_control, "%s\n",
		"  <VariableName `LongDocumentName'>");
	(*output_function)(output_control, "  <VariableDef `%s'>\n",
		(control_ptr->frame_data.long_name == NULL) ?
		"*** LONG NAME ***" : control_ptr->frame_data.long_name);
	(*output_function)(output_control, "%s\n",
		" > # end of VariableFormat");
	(*output_function)(output_control, "%s\n",
		" <VariableFormat");
	(*output_function)(output_control, "%s\n",
		"  <VariableName `ShortDocumentName'>");
	(*output_function)(output_control, "  <VariableDef `%s'>\n",
		(control_ptr->frame_data.short_name == NULL) ?
		"*** SHORT NAME ***" : control_ptr->frame_data.short_name);
	(*output_function)(output_control, "%s\n",
		" > # end of VariableFormat");
	(*output_function)(output_control, "%s\n", "> # end of VariableFormats");
	(*output_function)(output_control, "\n");
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Emit the cross-reference definitions . . .							*/
	/*	*****************************************************************	*/
	(*output_function)(output_control, "<XRefFormats\n");
	(*output_function)(output_control, " <XRefFormat\n");
	(*output_function)(output_control, "  <XRefName `Name_X_Ref'>\n");
	(*output_function)(output_control, "%s%s\n",
		"  <XRefDef `\\<HyperText_ON\\>\\<$paratext\\>",
		"\\<HyperText_OFF\\> on page \\<$pagenum\\>'>");
	(*output_function)(output_control, " > # end of XRefFormat\n");
	(*output_function)(output_control, "> # end of XRefFormats\n");
	(*output_function)(output_control, "\n");
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Emit document section . . .												*/
	/*	*****************************************************************	*/
	(*output_function)(output_control, "<Document \n");
	(*output_function)(output_control, " <DViewRect 24 26 612 766 >\n");
	(*output_function)(output_control, " <DWindowRect 0 0 656 869 >\n");
	(*output_function)(output_control, " <DViewScale  100.0%>\n");
	(*output_function)(output_control, " <DPageSize  8.5\" 11.0\">\n");
	(*output_function)(output_control, " <DStartPage 1>\n");
	(*output_function)(output_control, " <DPageNumStyle Arabic>\n");
	(*output_function)(output_control, " <DPagePointStyle Arabic>\n");
	(*output_function)(output_control, " <DTwoSides Yes>\n");
	(*output_function)(output_control, " <DParity FirstRight>\n");
	(*output_function)(output_control, " <DFrozenPages No>\n");
	(*output_function)(output_control, " <DPageRounding DeleteEmptyPages>\n");
	(*output_function)(output_control, " <DLinebreakChars `/ - \xd0  \xd1 _'>\n");
	(*output_function)(output_control, " <DPunctuationChars `:;,.\xc9 !?'>\n");
	(*output_function)(output_control, " <DShowAllConditions Yes>\n");
	(*output_function)(output_control, " <DViewOnly No>\n");
	(*output_function)(output_control, " <DGridOn Yes>\n");
	(*output_function)(output_control, " <DPageGrid  0.25\">\n");
	(*output_function)(output_control, " <DSnapGrid  0.125\">\n");
	(*output_function)(output_control, " <DSnapRotation  0.0>\n");
	(*output_function)(output_control, " <DRulersOn Yes>\n");
	(*output_function)(output_control, " <DFullRulers Yes>\n");
	(*output_function)(output_control, " <DGraphicsOff No>\n");
	(*output_function)(output_control, " <DCurrentView 1>\n");
	(*output_function)(output_control, " <DBordersOn Yes>\n");
	(*output_function)(output_control, " <DSymbolsOn No>\n");
	(*output_function)(output_control, " <DSmartQuotesOn No>\n");
	(*output_function)(output_control, " <DSmartSpacesOn No>\n");
	(*output_function)(output_control, " <DLanguage USEnglish>\n");
	(*output_function)(output_control, " <DSuperscriptSize  80.0%>\n");
	(*output_function)(output_control, " <DSubscriptSize  80.0%>\n");
	(*output_function)(output_control, " <DSmallCapsSize  80.0%>\n");
	(*output_function)(output_control, " <DSuperscriptShift  40.0%>\n");
	(*output_function)(output_control, " <DSubscriptShift  25.0%>\n");
	(*output_function)(output_control, " <DPrintSkipBlankPages No>\n");
	(*output_function)(output_control, " <DPrintSeparations No>\n");
	(*output_function)(output_control, " <DNoPrintSepColor `White'>\n");
	(*output_function)(output_control, "> # end of Document\n");
	(*output_function)(output_control, "\n");
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	(*output_function)(output_control, "<BookComponent \n");
	(*output_function)(output_control, " <FileName `<c\\>%sAIX.doc'>\n",
		(control_ptr->frame_data.document_name == NULL) ? "doc-name" :
		control_ptr->frame_data.document_name);
	(*output_function)(output_control, " <FileNameSuffix `AIX'>\n");
	(*output_function)(output_control, " <DeriveLinks Yes>\n");
	(*output_function)(output_control, " <DeriveType IOA>\n");
	(*output_function)(output_control, " <DeriveTag `Author'>\n");
	(*output_function)(output_control, "> # end of BookComponent\n");
	(*output_function)(output_control, "<BookComponent \n");
	(*output_function)(output_control, " <FileName `<c\\>%sIX.doc'>\n",
		(control_ptr->frame_data.document_name == NULL) ? "doc-name" :
		control_ptr->frame_data.document_name);
	(*output_function)(output_control, " <FileNameSuffix `IX'>\n");
	(*output_function)(output_control, " <DeriveLinks Yes>\n");
	(*output_function)(output_control, " <DeriveType IDX>\n");
	(*output_function)(output_control, " <DeriveTag `Index'>\n");
	(*output_function)(output_control, "> # end of BookComponent\n");
	(*output_function)(output_control, "<BookComponent \n");
	(*output_function)(output_control, " <FileName `<c\\>%sTOC.doc'>\n",
		(control_ptr->frame_data.document_name == NULL) ? "doc-name" :
		control_ptr->frame_data.document_name);
	(*output_function)(output_control, " <FileNameSuffix `TOC'>\n");
	(*output_function)(output_control, " <DeriveLinks Yes>\n");
	(*output_function)(output_control, " <DeriveType TOC>\n");
	(*output_function)(output_control, " <DeriveTag `ADF_Name'>\n");
	(*output_function)(output_control, "> # end of BookComponent\n");
	(*output_function)(output_control, "<BookComponent \n");
	(*output_function)(output_control, " <FileName `<c\\>%sIOM.doc'>\n",
		(control_ptr->frame_data.document_name == NULL) ? "doc-name" :
		control_ptr->frame_data.document_name);
	(*output_function)(output_control, " <FileNameSuffix `IOM'>\n");
	(*output_function)(output_control, " <DeriveLinks Yes>\n");
	(*output_function)(output_control, " <DeriveType IOM>\n");
	(*output_function)(output_control, " <DeriveTag `Type 25'>\n");
	(*output_function)(output_control, "> # end of BookComponent\n");
	(*output_function)(output_control, "\n");
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Begin the actual document text . . .									*/
	/*	*****************************************************************	*/
	(*output_function)(output_control, "<TextFlow\n");
	(*output_function)(output_control, " <TFTag `A'>\n");
	(*output_function)(output_control, " <TFAutoConnect Yes >\n");
	(*output_function)(output_control, " <Notes\n");
	(*output_function)(output_control, " > # end Notes\n");
	(*output_function)(output_control, "\n");
	/*	*****************************************************************	*/
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_FRAME_OutputEnd(ADF_CONTROL *control_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void ADF_FRAME_OutputEnd(control_ptr, output_function, output_control)
ADF_CONTROL  *control_ptr;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	STR_EMIT_SetDefaults(&output_function, &output_control);

	(*output_function)(output_control, "> # end TextFlow\n");
	(*output_function)(output_control, "\n");

	(*output_function)(output_control, "# End of MIFFile\n");
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_FRAME_DoHeaderByEntry(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_list,
	const time_t *output_date, STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
static void ADF_FRAME_DoHeaderByEntry(control_ptr, entry_ptr, entry_data_list,
	output_date, output_function, output_control)
ADF_CONTROL           *control_ptr;
const ADF_ENTRY       *entry_ptr;
ADF_ENTRY_DATA        *entry_data_list;
const time_t          *output_date;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	unsigned int   tmp_count = 0;
	char         **tmp_list  = NULL;
	unsigned int   count_1;
	time_t         tmp_output_date;
	time_t         time_t_data;
	struct tm      tm_data;
   char           date_data[100];
	char           time_zone_data[100];
	char           error_text[ADF_MAX_ERROR_TEXT];

	STR_EMIT_SetDefaults(&output_function, &output_control);

	tmp_output_date = (output_date == NULL) ? time(NULL)   : *output_date;

	ADF_FRAME_DoBorder(output_function, output_control);
	ADF_FRAME_DoBorder(output_function, output_control);
	ADF_FRAME_DoCommentsFloating("Documentation for ", entry_ptr->base_name,
		output_function, output_control);
	ADF_FRAME_DoComment("", output_function, output_control);
	ADF_FRAME_DoComment(
		"   Created by the Automated Documentation Facility (ADF)",
		output_function, output_control);
	ADF_FRAME_DoBorder(output_function, output_control);

	ADF_FRAME_DoComment("", output_function, output_control);
	ADF_FRAME_DoCommentsFloating("Entry Name          : ",
		entry_ptr->base_name, output_function, output_control);
	ADF_FRAME_DoComment("", output_function, output_control);
	ADF_FRAME_DoCommentsFloating("Source File Name    : ",
		entry_ptr->file_name, output_function, output_control);

	ADF_FRAME_DoComment("", output_function, output_control);
	ADF_FRAME_DoCommentsFloating("Source File Date    : ",
		strcat(SDTIF_Format_time_t_GMT(&entry_ptr->file_date, date_data),
		" GMT/UTC"), output_function, output_control);
	time_t_data = entry_ptr->file_date;

	tm_data     = *SDTIF_GetTimeLocal(&time_t_data, &tm_data);
	strftime(time_zone_data, sizeof(time_zone_data) - 1, " %Z", &tm_data);
	ADF_FRAME_DoCommentsFloating("                    : ",
		strcat(SDTIF_Format_time_t(&entry_ptr->file_date, date_data),
		time_zone_data), output_function, output_control);

	ADF_FRAME_DoComment("", output_function, output_control);
	ADF_FRAME_DoCommentsFloating("ADF Preparation Date: ",
		strcat(SDTIF_Format_time_t_GMT(&entry_ptr->prep_date, date_data),
		" GMT/UTC"), output_function, output_control);
	time_t_data = entry_ptr->prep_date;
	tm_data     = *SDTIF_GetTimeLocal(&time_t_data, &tm_data);
	strftime(time_zone_data, sizeof(time_zone_data) - 1, " %Z", &tm_data);
	ADF_FRAME_DoCommentsFloating("                    : ",
		strcat(SDTIF_Format_time_t(&entry_ptr->prep_date, date_data),
		time_zone_data), output_function, output_control);

	ADF_FRAME_DoComment("", output_function, output_control);
	ADF_FRAME_DoCommentsFloating("Output Date         : ",
		strcat(SDTIF_Format_time_t_GMT(&tmp_output_date, date_data), " GMT/UTC"),
		output_function, output_control);
	tm_data = *SDTIF_GetTimeLocal(&tmp_output_date, &tm_data);
	strftime(time_zone_data, sizeof(time_zone_data) - 1, " %Z", &tm_data);
	ADF_FRAME_DoCommentsFloating("                    : ",
		strcat(SDTIF_Format_time_t(&tmp_output_date, date_data), time_zone_data),
		output_function, output_control);

	ADF_FRAME_DoComment("", output_function, output_control);
	ADF_FRAME_DoBorder(output_function, output_control);
	(*output_function)(output_control, "\n");

	if ((ADF_GetAreaList(control_ptr, entry_ptr, entry_data_list +
		ADF_AREA_COPYRIGHTS, &tmp_count, &tmp_list, error_text) ==
		ADF_SUCCESS) && tmp_count) {
		ADF_FRAME_DoBorder(output_function, output_control);
		ADF_FRAME_DoBorder(output_function, output_control);
		for (count_1 = 0; count_1 < tmp_count; count_1++)
			ADF_FRAME_DoCommentsFloating("", tmp_list[count_1],
				output_function, output_control);
		ADF_FRAME_DoBorder(output_function, output_control);
		strl_remove_all(&tmp_count, &tmp_list);
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_FRAME_DoHeaderByFile(const ADF_CONTROL *control_ptr,
	unsigned int entry_index, const time_t *output_date,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
static void ADF_FRAME_DoHeaderByFile(control_ptr, entry_index, output_date,
	output_function, output_control)
const ADF_CONTROL     *control_ptr;
unsigned int           entry_index;
const time_t          *output_date;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;
	time_t       tmp_output_date;
	struct tm    tm_data;
   char         date_data[100];
	char         time_zone_data[100];

	STR_EMIT_SetDefaults(&output_function, &output_control);

	tmp_output_date = (output_date == NULL) ? time(NULL) : *output_date;

	ADF_FRAME_DoBorder(output_function, output_control);
	ADF_FRAME_DoBorder(output_function, output_control);
	ADF_FRAME_DoCommentsFloating("Documentation for Entries in Source File ",
		control_ptr->in_entry_order_list[entry_index]->file_name,
		output_function, output_control);
	ADF_FRAME_DoComment("", output_function, output_control);
	ADF_FRAME_DoComment(
		"   Created by the Automated Documentation Facility (ADF)",
		output_function, output_control);
	ADF_FRAME_DoBorder(output_function, output_control);
	ADF_FRAME_DoComment("", output_function, output_control);
	ADF_FRAME_DoCommentsFloating("Output Date: ",
		strcat(SDTIF_Format_time_t_GMT(&tmp_output_date, date_data), " GMT/UTC"),
		output_function, output_control);
	tm_data = *SDTIF_GetTimeLocal(&tmp_output_date, &tm_data);
	strftime(time_zone_data, sizeof(time_zone_data) - 1, " %Z", &tm_data);
	ADF_FRAME_DoCommentsFloating("           : ",
		strcat(SDTIF_Format_time_t(&tmp_output_date, date_data), time_zone_data),
		output_function, output_control);
	ADF_FRAME_DoComment("", output_function, output_control);

	for (count_1 = entry_index;
		(count_1 < control_ptr->in_entry_order_count) &&
		(!strcmp(control_ptr->in_entry_order_list[entry_index]->file_name,
		control_ptr->in_entry_order_list[count_1]->file_name)); count_1++)
		ADF_FRAME_DoCommentsFloating((!count_1) ?
			"Entry Name : " : "           : ",
			control_ptr->in_entry_order_list[count_1]->base_name,
			output_function, output_control);
	ADF_FRAME_DoComment("", output_function, output_control);
	ADF_FRAME_DoBorder(output_function, output_control);
	(*output_function)(output_control, "\n");
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_FRAME_OutputBasic(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_list,
	const time_t *output_date, STR_FUNC_TYPE_fprintf output_function,
	void *output_control, char *error_text)
#else
static int ADF_FRAME_OutputBasic(control_ptr, entry_ptr, entry_data_list,
	output_date, output_function, output_control, error_text)
ADF_CONTROL           *control_ptr;
const ADF_ENTRY       *entry_ptr;
ADF_ENTRY_DATA        *entry_data_list;
const time_t          *output_date;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	int              return_code     = ADF_SUCCESS;
	unsigned int     area_name_count = 0;
	const ADF_AREA  *last_area_ptr   = NULL;
	unsigned int     count_1;
	ADF_ENTRY_DATA  *entry_data_ptr;
	const ADF_AREA  *area_ptr;
	ADF_ENTRY_DATA   index_data;
	char             area_name[ADF_AREA_NAME_LENGTH + 1];

	STR_EMIT_SetDefaults(&output_function, &output_control);

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Emit descriptive comments for the entry . . .						*/
	/*	*****************************************************************	*/
	if (control_ptr->output_comment_flag == ADF_TRUE)
		ADF_FRAME_DoHeaderByEntry(control_ptr, entry_ptr, entry_data_list,
			output_date, output_function, output_control);
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Order the sections of the entry as specified, but first save	*/
	/*	the output index and publish areas . . .									*/
	/*	*****************************************************************	*/
	index_data = entry_data_list[ADF_AREA_OUTPUT_INDEX];
	if (control_ptr->area_order_type != ADF_AREA_ORDER_TYPE_INTERNAL)
		ADF_SORT_EntrySections(control_ptr->area_order_type, entry_data_list);
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Find the last area to be output for this entry . . .				*/
	/*	*****************************************************************	*/
	for (count_1 = ADF_AREA_COUNT; count_1; ) {
		count_1--;
		if (entry_data_list[count_1].para_count &&
			(ADF_AreaNameList[entry_data_list[count_1].area_index].output_flag ==
			ADF_TRUE)) {
			last_area_ptr =
				ADF_AreaNameList + entry_data_list[count_1].area_index;
			break;
		}
	}
	/*	*****************************************************************	*/

	for (count_1 = 0; count_1 < ADF_AREA_COUNT; count_1++) {
		entry_data_ptr = entry_data_list + count_1;
		area_ptr       = ADF_AreaNameList + entry_data_ptr->area_index;
		if ((area_ptr->output_flag != ADF_TRUE) ||
			(!entry_data_ptr->para_count))
			continue;
		/* *** Emit the section name *** */
		ADF_GetOutputAreaName(control_ptr->area_name_type,
			entry_data_ptr->area_index, control_ptr->area_name_list,
			entry_data_ptr->section_name, sizeof(area_name) - 1, area_name);
		if (!area_name_count++) {
			(*output_function)(output_control, " <Para\n");
			(*output_function)(output_control, "  <PgfTag `ADF_Section'>\n");
			(*output_function)(output_control, "  <PgfPlacement PageTop>\n");
			(*output_function)(output_control, "  <ParaLine\n");
			if ((return_code != ADF_FRAME_OutputIndexRange(control_ptr,
				entry_ptr, entry_data_list + ADF_AREA_OUTPUT_INDEX,
				ADF_AREA_OUTPUT_INDEX, ADF_TRUE, 2, output_function,
				output_control, error_text)) != ADF_SUCCESS)
				break;
			if ((return_code != ADF_FRAME_OutputIndexRange(control_ptr,
				entry_ptr, entry_data_list + ADF_AREA_PUBLISH_XREF,
				ADF_AREA_PUBLISH_XREF, ADF_TRUE, 4, output_function,
				output_control, error_text)) != ADF_SUCCESS)
				break;
			if ((return_code != ADF_FRAME_OutputIndexRange(control_ptr,
				entry_ptr, entry_data_list + ADF_AREA_AUTHORS,
				ADF_AREA_AUTHORS, ADF_TRUE, 5, output_function, output_control,
				error_text)) != ADF_SUCCESS)
				break;
			(*output_function)(output_control,
				"   <Marker <MType 8> <MText `newlink ");
			ADF_FRAME_OutputIndexString(entry_ptr->base_name, output_function,
				output_control);
			(*output_function)(output_control, "'>>\n");
			(*output_function)(output_control,
				"   <Marker <MType 25> <MText `");
			ADF_FRAME_OutputIndexString(entry_ptr->file_name, output_function,
				output_control);
			(*output_function)(output_control, "\\:");
			ADF_FRAME_OutputIndexString(entry_ptr->base_name, output_function,
				output_control);
			(*output_function)(output_control, " \\<$startrange\\>'>>\n");
			(*output_function)(output_control, "  > # end ParaLine\n");
			(*output_function)(output_control, "  <ParaLine\n");
			ADF_FRAME_EmitString(area_name, 3, ADF_FALSE, output_function,
				output_control);
			(*output_function)(output_control, "  > # end ParaLine\n");
			(*output_function)(output_control, " > # end Para\n");
		}
		else if (area_ptr == last_area_ptr) {
			(*output_function)(output_control, " <Para\n");
			(*output_function)(output_control, "  <PgfTag `ADF_Section'>\n");
			(*output_function)(output_control, "  <ParaLine\n");
			if ((return_code != ADF_FRAME_OutputIndexRange(control_ptr,
				entry_ptr, entry_data_list + ADF_AREA_OUTPUT_INDEX,
				ADF_AREA_OUTPUT_INDEX, ADF_FALSE, 2, output_function,
				output_control, error_text)) != ADF_SUCCESS)
				break;
			if ((return_code != ADF_FRAME_OutputIndexRange(control_ptr,
				entry_ptr, entry_data_list + ADF_AREA_PUBLISH_XREF,
				ADF_AREA_PUBLISH_XREF, ADF_FALSE, 4, output_function,
				output_control, error_text)) != ADF_SUCCESS)
				break;
			if ((return_code != ADF_FRAME_OutputIndexRange(control_ptr,
				entry_ptr, entry_data_list + ADF_AREA_AUTHORS,
				ADF_AREA_AUTHORS, ADF_FALSE, 5, output_function,
				output_control, error_text)) != ADF_SUCCESS)
				break;
			(*output_function)(output_control,
				"   <Marker <MType 25> <MText `");
			ADF_FRAME_OutputIndexString(entry_ptr->file_name, output_function,
				output_control);
			(*output_function)(output_control, "\\:");
			ADF_FRAME_OutputIndexString(entry_ptr->base_name, output_function,
				output_control);
			(*output_function)(output_control, " \\<$endrange\\>'>>\n");
			ADF_FRAME_EmitString(area_name, 3, ADF_FALSE, output_function,
				output_control);
			(*output_function)(output_control, "  > # end ParaLine\n");
			(*output_function)(output_control, " > # end Para\n");
		}
		else {
			(*output_function)(output_control, " <Para\n");
			(*output_function)(output_control, "  <PgfTag `ADF_Section'>\n");
			(*output_function)(output_control, "  <ParaLine\n");
			ADF_FRAME_EmitString(area_name, 3, ADF_FALSE, output_function,
				output_control);
			(*output_function)(output_control, "  > # end ParaLine\n");
			(*output_function)(output_control, " > # end Para\n");
		}
		if (entry_data_ptr->area_index == ADF_AREA_NAME) {
			(*output_function)(output_control, " <Para\n");
			(*output_function)(output_control, "  <PgfTag `ADF_Name'>\n");
			(*output_function)(output_control, "  <ParaLine\n");
			(*output_function)(output_control,
				"   <Marker <MType 9> <MText `");
			ADF_FRAME_OutputIndexString(entry_ptr->base_name, output_function,
				output_control);
			(*output_function)(output_control, "'>>\n");
			ADF_FRAME_EmitString(entry_ptr->base_name, 3, ADF_FALSE,
				output_function, output_control);
			(*output_function)(output_control, "  > # end ParaLine\n");
			(*output_function)(output_control, " > # end Para\n");
		}
		else if (entry_data_ptr->area_index == ADF_AREA_CODE_SYNTAX) {
			if ((return_code = ADF_FRAME_OutputCodeSyntax(control_ptr, entry_ptr,
				entry_data_ptr, output_function, output_control, error_text)) !=
				ADF_SUCCESS)
				break;
		}
		else if (entry_data_ptr->area_index == ADF_AREA_SEE_ALSO) {
			if ((return_code = ADF_FRAME_OutputSeeAlso(control_ptr, entry_ptr,
				entry_data_ptr, output_function, output_control, error_text)) !=
				ADF_SUCCESS)
				break;
		}
		else if ((return_code = ADF_FRAME_OutputSection(control_ptr, entry_ptr,
			entry_data_ptr, area_ptr->pformat_flag, output_function,
			output_control, error_text)) != ADF_SUCCESS)
			break;
	}

	if (return_code == ADF_SUCCESS) {
		if (control_ptr->output_comment_flag == ADF_TRUE) {
			(*output_function)(output_control, "\n");
			ADF_FRAME_DoBorder(output_function, output_control);
			ADF_FRAME_DoCommentsFloating("End of FrameMaker MIF Script for ",
				entry_ptr->base_name, output_function, output_control);
			ADF_FRAME_DoBorder(output_function, output_control);
			ADF_FRAME_DoBorder(output_function, output_control);
			(*output_function)(output_control, "\n");
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_FRAME_OutputSection(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_ptr,
	int format_flag, STR_FUNC_TYPE_fprintf output_function,
	void *output_control, char *error_text)
#else
static int ADF_FRAME_OutputSection(control_ptr, entry_ptr, entry_data_ptr,
	format_flag, output_function, output_control, error_text)
ADF_CONTROL           *control_ptr;
const ADF_ENTRY       *entry_ptr;
ADF_ENTRY_DATA        *entry_data_ptr;
int                    format_flag;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	int                    return_code = ADF_SUCCESS;
	unsigned int           count_1;
	unsigned int           cformat_type;
	int                    char_format_flag;
	ADF_PARA_DATA         *para_ptr;
	const ADF_PFORMAT_DEF *pfmt_def_ptr;
	ADF_PFORMAT           *pfmt_ptr;
	char                   pfmt_name[ADF_FRAME_PFORMAT_NAME_LENGTH + 1];

	cformat_type = (format_flag == ADF_TRUE) ? ADF_FRAME_CFORMAT_TYPE :
		((control_ptr->hyper_text_flag != ADF_TRUE) ? 0 :
		ADF_CFORMAT_TYPE_HTEXT);

	if ((cformat_type & ADF_CFORMAT_TYPE_HTEXT) &&
		(control_ptr->hyper_text_flag != ADF_TRUE))
		cformat_type ^= ADF_CFORMAT_TYPE_HTEXT;

	for (count_1 = 0; count_1 < entry_data_ptr->para_count; count_1++) {
		para_ptr     = entry_data_ptr->para_list + count_1;
		pfmt_ptr     = &para_ptr->para_format;
		pfmt_def_ptr = ADF_GetParaFormat(pfmt_ptr->pformat_index);
		if ((pfmt_def_ptr->supported_flag != ADF_TRUE) ||
			(pfmt_ptr->pformat_flag != ADF_TRUE) || (format_flag != ADF_TRUE) ||
			(!(*ADF_FRAME_GetParaName(pfmt_ptr->pformat_index, pfmt_name)))) {
			pfmt_ptr->pformat_index = 0;
			ADF_FRAME_GetParaName(pfmt_ptr->pformat_index, pfmt_name);
		}
		if ((return_code = ADF_FixParagraph(control_ptr, entry_ptr, para_ptr,
			cformat_type, error_text)) != ADF_SUCCESS)
			break;
		(*output_function)(output_control, " <Para\n");
		(*output_function)(output_control, "  <PgfTag `%s'>\n", pfmt_name);
		if (pfmt_ptr->begin_rule_flag == ADF_TRUE)
			(*output_function)(output_control,
				"  <PgfTopSeparator `ADF_LN_%u'>\n", pfmt_ptr->indent_level -
				(((pfmt_def_ptr->format_type == ADF_PFORMAT_TYPE_NM) ||
				(pfmt_def_ptr->format_type == ADF_PFORMAT_TYPE_BB)) ? 1 : 0));
		if (pfmt_ptr->end_rule_flag == ADF_TRUE)
			(*output_function)(output_control,
				"  <PgfBotSeparator `ADF_LN_%u'>\n", pfmt_ptr->indent_level -
				(((pfmt_def_ptr->format_type == ADF_PFORMAT_TYPE_NM) ||
				(pfmt_def_ptr->format_type == ADF_PFORMAT_TYPE_BB)) ? 1 : 0));
		(*output_function)(output_control, "  <ParaLine\n");
		if (pfmt_ptr->format_type == ADF_PFORMAT_TYPE_NM)
		(*output_function)(output_control,
			"   <Char Tab><String `%lu'><Char Tab>\n",
			pfmt_ptr->numeric_value);
		char_format_flag = (pfmt_ptr->pformat_flag != ADF_TRUE) ? ADF_TRUE :
			pfmt_ptr->char_format_flag;
		if (char_format_flag == ADF_TRUE) {
			if ((return_code = ADF_FRAME_EmitParaText(control_ptr, entry_ptr,
				control_ptr->current_para_line_count,
				control_ptr->in_para_line_list, output_function, output_control,
				error_text)) != ADF_SUCCESS)
				goto EXIT_FUNCTION;
		}
		else if ((return_code = ADF_FRAME_EmitPlainParaText(control_ptr,
			entry_ptr, control_ptr->current_para_line_count,
			control_ptr->in_para_line_list, output_function, output_control,
			error_text)) != ADF_SUCCESS)
			goto EXIT_FUNCTION;
		(*output_function)(output_control, "  > # end ParaLine\n");
		(*output_function)(output_control, " > # end Para\n");
	}

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_FRAME_OutputCodeSyntax(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text)
#else
static int ADF_FRAME_OutputCodeSyntax(control_ptr, entry_ptr, entry_data_ptr,
	output_function, output_control, error_text)
ADF_CONTROL           *control_ptr;
const ADF_ENTRY       *entry_ptr;
ADF_ENTRY_DATA        *entry_data_ptr;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	int                  return_code = ADF_SUCCESS;
	unsigned int         count_1;
	unsigned int         count_2;
	ADF_PARA_DATA       *para_ptr;
	const ADF_PARA_TEXT *para_line_ptr;

const char   *tmp_ptr;
unsigned int  count_3;

	for (count_1 = 0; count_1 < entry_data_ptr->para_count; count_1++) {
		para_ptr = entry_data_ptr->para_list + count_1;
		if ((return_code = ADF_FixParagraphWrap(control_ptr, entry_ptr,
			para_ptr, (control_ptr->hyper_text_flag != ADF_TRUE) ? 0 :
			ADF_CFORMAT_TYPE_HTEXT, 100, 3, 0, error_text)) != ADF_SUCCESS)
			break;
		(*output_function)(output_control, " <Para\n");
		(*output_function)(output_control, "  <PgfTag `ADF_NO_US_0'>\n");
		(*output_function)(output_control, "  <PgfTopSeparator `%s'>\n",
			(!count_1) ? "ADF_LN_0" : "");
		(*output_function)(output_control, "  <PgfBotSeparator `%s'>\n",
			(count_1 == (entry_data_ptr->para_count - 1)) ? "ADF_LN_0" : "");
		(*output_function)(output_control, "  <PgfLIndent 0.500>\n");
		(*output_function)(output_control, "  <PgfAlignment Left>\n");
		(*output_function)(output_control, "  <PgfSpBefore  0.0 pt>\n");
		(*output_function)(output_control, "  <PgfSpAfter   0.0 pt>\n");
		(*output_function)(output_control, "  <PgfHyphenate No>\n");
		(*output_function)(output_control, "  <PgfLetterSpace No>\n");
		(*output_function)(output_control, "  <PgfLanguage None>\n");
		(*output_function)(output_control, "  <ParaLine\n");
		para_line_ptr = control_ptr->in_para_line_list;
		for (count_2 = 0; count_2 < control_ptr->current_para_line_count;
			count_2++, para_line_ptr++) {
			if (para_line_ptr->cformat_type == ADF_CFORMAT_CHAR_HTEXT_1) {
				(*output_function)(output_control, "%s\n",
					"   <Font <FTag `HyperText_ON'>>");
				if ((return_code = ADF_FRAME_EmitAnchor(control_ptr, entry_ptr,
					para_line_ptr->htext_index, ADF_FALSE, output_function,
					output_control, error_text)) != ADF_SUCCESS)
					goto EXIT_FUNCTION;
				continue;
			}
			else if (para_line_ptr->cformat_type == ADF_CFORMAT_CHAR_HTEXT_2) {
				(*output_function)(output_control, "%s\n",
				"   <Font <FTag `HyperText_OFF'>>");
				continue;
			}
			(*output_function)(output_control, "   <String `");
			for (count_3 = 0, tmp_ptr = para_line_ptr->ptr;
				count_3 < para_line_ptr->length; count_3++, tmp_ptr++) {
				if ((*tmp_ptr == '\\') || (*tmp_ptr == '<') ||
					(*tmp_ptr == '>') || (*tmp_ptr == '\'') ||
					(*tmp_ptr == '`'))
					(*output_function)(output_control, "\\%c", *tmp_ptr);
				else if (*tmp_ptr == '\t')
					(*output_function)(output_control,
						"'>\n   <Char Tab>\n   <String `");
				else if (*((unsigned char *) tmp_ptr) > 0x7F)
					(*output_function)(output_control, "\\x%02u ",
						((unsigned int) *((unsigned char *) tmp_ptr)));
				else if (*tmp_ptr == '\n') {
					(*output_function)(output_control, "'>\n");
					(*output_function)(output_control, "   <Char HardReturn>\n");
					(*output_function)(output_control, "  > # end ParaLine\n");
					(*output_function)(output_control, "  <ParaLine\n");
					(*output_function)(output_control, "   <String `");
				}
				else if (*tmp_ptr == ' ') {
					(*output_function)(output_control, "'>\n");
					(*output_function)(output_control, "   <Char HardSpace>\n");
					(*output_function)(output_control, "   <String `");
				}
				else
					(*output_function)(output_control, "%c", *tmp_ptr);
			}
			(*output_function)(output_control, "'>\n");
		}
		(*output_function)(output_control, "  > # end ParaLine\n");
		(*output_function)(output_control, " > # end Para\n");
	}

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_FRAME_OutputSeeAlso(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text)
#else
static int ADF_FRAME_OutputSeeAlso(control_ptr, entry_ptr, entry_data_ptr,
	output_function, output_control, error_text)
ADF_CONTROL           *control_ptr;
const ADF_ENTRY       *entry_ptr;
ADF_ENTRY_DATA        *entry_data_ptr;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	int             return_code = ADF_SUCCESS;
	unsigned int    count_1;
	ADF_PARA_DATA  *para_ptr;
   unsigned int    found_index;
	ADF_ENTRY      *htext_entry_ptr;
	char            buffer[1024];

	(*output_function)(output_control, " <Para\n");
	(*output_function)(output_control, "  <PgfTag `ADF_NO_FN_0'>\n");

	for (count_1 = 0; count_1 < entry_data_ptr->para_count; count_1++) {
		para_ptr = entry_data_ptr->para_list + count_1;
		if ((return_code = ADF_FixParagraph(control_ptr, entry_ptr, para_ptr,
			ADF_CFORMAT_TYPE_NONE, error_text)) != ADF_SUCCESS)
			break;
		(*output_function)(output_control, "  <ParaLine\n");
		nstrcpy(buffer, control_ptr->in_para_line_list->ptr,
			(control_ptr->in_para_line_list->length >= sizeof(buffer)) ?
			(sizeof(buffer) - 1) : control_ptr->in_para_line_list->length);
		if ((control_ptr->hyper_text_flag == ADF_TRUE) &&
			(ADF_FIND_FindHTextByText(control_ptr->in_htext_count,
			control_ptr->in_htext_list, buffer, &found_index) ==
			STRFUNCS_ITEM_FOUND)) {
			htext_entry_ptr = control_ptr->in_entry_list +
				control_ptr->in_htext_list[found_index].entry_index;
			(*output_function)(output_control, "   <Marker\n");
			(*output_function)(output_control, "    <MType 8>\n");
			(*output_function)(output_control, "    <MText `gotolink ");
			ADF_FRAME_OutputString(htext_entry_ptr->base_name,
				output_function, output_control);
			(*output_function)(output_control, "'>\n");
			(*output_function)(output_control, "   > # end Marker\n");
			if ((return_code = ADF_FRAME_GetXRefSrcFile(control_ptr,
				entry_ptr, found_index, ADF_FALSE, error_text)) !=
				ADF_SUCCESS)
				break;
			else {
				(*output_function)(output_control, "   <XRef\n");
				(*output_function)(output_control,
					"    <XRefName `Name_X_Ref'>\n");
				(*output_function)(output_control, "    <XRefSrcText `");
				ADF_FRAME_OutputString(htext_entry_ptr->base_name,
					output_function, output_control);
				(*output_function)(output_control, "'>\n");
				(*output_function)(output_control, "    <XRefSrcFile `%s'>\n",
					control_ptr->htext_link_name);
				(*output_function)(output_control, "   > # end XRef\n");
			}
		}
		else
			ADF_FRAME_EmitText(control_ptr->in_para_line_list->length,
				control_ptr->in_para_line_list->ptr, 3, ADF_FALSE,
				output_function, output_control);
		if (count_1 < (entry_data_ptr->para_count - 1))
			(*output_function)(output_control, "   <Char HardReturn>\n");
		(*output_function)(output_control, "  > # end ParaLine\n");
	}

	(*output_function)(output_control, " > # end Para\n");

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_FRAME_EmitParaText(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, unsigned int para_line_count,
	const ADF_PARA_TEXT *para_line_list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control, char *error_text)
#else
static int ADF_FRAME_EmitParaText(control_ptr, entry_ptr, para_line_count,
	para_line_list, output_function, output_control, error_text)
ADF_CONTROL           *control_ptr;
const ADF_ENTRY       *entry_ptr;
unsigned int           para_line_count;
const ADF_PARA_TEXT   *para_line_list;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code = ADF_SUCCESS;
	unsigned int  count_1;
	unsigned int  in_length;
	char         *in_ptr;

	for (count_1 = 0; count_1 < para_line_count; count_1++) {
		in_length = para_line_list[count_1].length;
		in_ptr    = para_line_list[count_1].ptr;
		if (para_line_list[count_1].cformat_type != ADF_CFORMAT_CHAR_NONE) {
			switch (para_line_list[count_1].cformat_type) {
				case ADF_CFORMAT_CHAR_BOLD_1			:
					(*output_function)(output_control, "   %s\n",
						"<Font <FWeight `Bold'>>");
					break;
				case ADF_CFORMAT_CHAR_ITALIC_1		:
					(*output_function)(output_control, "   %s\n",
						"<Font <FAngle `Italic'>>");
					break;
				case ADF_CFORMAT_CHAR_ULINED_1		:
					(*output_function)(output_control, "   %s\n",
						"<Font <FUnderline Yes>>");
					break;
				case ADF_CFORMAT_CHAR_OLINED_1		:
					(*output_function)(output_control, "   %s\n",
						"<Font <FOverline Yes>>");
					break;
				case ADF_CFORMAT_CHAR_STHRU_1			:
					(*output_function)(output_control, "   %s\n",
						"<Font <FStrike Yes>>");
					break;
				case ADF_CFORMAT_CHAR_EINDEX_1		:
					(*output_function)(output_control, "   %s",
						"<Marker <MType 2> <MText `");
					ADF_FRAME_OutputIndexText(para_line_list[count_1 + 1].length,
						para_line_list[count_1 + 1].ptr, output_function,
						output_control);
					(*output_function)(output_control, "'>>\n");
					break;
				case ADF_CFORMAT_CHAR_SUBSCRIPT_1	:
					(*output_function)(output_control, "   %s\n",
						"<Font <FSubScript Yes>>");
					break;
				case ADF_CFORMAT_CHAR_SUPERSCRIPT_1	:
					(*output_function)(output_control, "   %s\n",
						"<Font <FSupScript Yes>>");
					break;
				case ADF_CFORMAT_CHAR_HTEXT_1			:
					(*output_function)(output_control, "%s\n",
						"   <Font <FTag `HyperText_ON'>>");
					if ((return_code = ADF_FRAME_EmitAnchor(control_ptr, entry_ptr,
						para_line_list[count_1].htext_index, ADF_FALSE,
						output_function, output_control, error_text)) !=
						ADF_SUCCESS)
						goto EXIT_FUNCTION;
					break;
				case ADF_CFORMAT_CHAR_BOLD_2			:
					(*output_function)(output_control, "   %s\n",
						"<Font <FWeight `Regular'>>");
					break;
				case ADF_CFORMAT_CHAR_ITALIC_2		:
					(*output_function)(output_control, "   %s\n",
						"<Font <FAngle `Regular'>>");
					break;
				case ADF_CFORMAT_CHAR_ULINED_2		:
					(*output_function)(output_control, "   %s\n",
						"<Font <FUnderline No>>");
					break;
				case ADF_CFORMAT_CHAR_OLINED_2		:
					(*output_function)(output_control, "   %s\n",
						"<Font <FOverline No>>");
					break;
				case ADF_CFORMAT_CHAR_STHRU_2			:
					(*output_function)(output_control, "   %s\n",
						"<Font <FStrike No>>");
					break;
				case ADF_CFORMAT_CHAR_EINDEX_2		:
					break;
				case ADF_CFORMAT_CHAR_SUBSCRIPT_2	:
					(*output_function)(output_control, "   %s\n",
						"<Font <FSubScript No>>");
					break;
				case ADF_CFORMAT_CHAR_SUPERSCRIPT_2	:
					(*output_function)(output_control, "   %s\n",
						"<Font <FSupScript No>>");
					break;
				case ADF_CFORMAT_CHAR_HTEXT_2			:
					(*output_function)(output_control, "%s\n",
						"   <Font <FTag `HyperText_OFF'>>");
					break;
				default										:
					break;
			}
			continue;
		}
		else if ((in_length) && (in_ptr != NULL))
			ADF_FRAME_EmitText(in_length, in_ptr, 3, ADF_FALSE, output_function,
				output_control);
	}

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_FRAME_EmitPlainParaText(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, unsigned int para_line_count,
	const ADF_PARA_TEXT *para_line_list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control, char *error_text)
#else
static int ADF_FRAME_EmitPlainParaText(control_ptr, entry_ptr,
	para_line_count, para_line_list, output_function, output_control,
	error_text)
ADF_CONTROL           *control_ptr;
const ADF_ENTRY       *entry_ptr;
unsigned int           para_line_count;
const ADF_PARA_TEXT   *para_line_list;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code = ADF_SUCCESS;
	unsigned int  current_col = 0;
	unsigned int  space_count;
	unsigned int  count_1;
	unsigned int  in_length;
	char         *in_ptr;

/*
	CODE NOTE: Should use the value in the ADF database entry.
*/
unsigned int tab_setting = 3;

	for (count_1 = 0; count_1 < para_line_count; count_1++) {
		in_length = para_line_list[count_1].length;
		in_ptr    = para_line_list[count_1].ptr;
		if (para_line_list[count_1].cformat_type ==
			ADF_CFORMAT_CHAR_HTEXT_1) {
			(*output_function)(output_control, "%s\n",
				"   <Font <FTag `HyperText_ON'>>");
			if ((return_code = ADF_FRAME_EmitAnchor(control_ptr, entry_ptr,
				para_line_list[count_1].htext_index, ADF_FALSE,
				output_function, output_control, error_text)) !=
				ADF_SUCCESS)
				break;
			continue;
		}
		else if (para_line_list[count_1].cformat_type ==
			ADF_CFORMAT_CHAR_HTEXT_2) {
			(*output_function)(output_control, "%s\n",
				"   <Font <FTag `HyperText_OFF'>>");
			continue;
		}
		else if ((!in_length) || (in_ptr == NULL) ||
			(para_line_list[count_1].cformat_type != ADF_CFORMAT_CHAR_NONE))
			continue;
		(*output_function)(output_control, "   <String `");
		for ( ; in_length; in_length--, in_ptr++) {
			if ((*in_ptr == '\\') || (*in_ptr == '<') || (*in_ptr == '>') ||
				(*in_ptr == '\'') || (*in_ptr == '`')) {
				(*output_function)(output_control, "\\%c", *in_ptr);
				current_col++;
			}
			else if (*in_ptr == '\n') {
				(*output_function)(output_control, "'>\n");
				(*output_function)(output_control, "   <Char HardReturn>\n");
				(*output_function)(output_control, "  > # end ParaLine\n");
				(*output_function)(output_control, "  <ParaLine\n");
				(*output_function)(output_control, "   <String `");
				current_col = 0;
			}
			else if (*in_ptr == ' ') {
				STR_EMIT_String("\\x4 ", 1, output_function, output_control);
				current_col++;
			}
			else if (*in_ptr == '\t') {
				space_count  = tab_setting - (current_col % tab_setting);
				current_col += space_count;
				(*output_function)(output_control, "%c", *in_ptr);
				STR_EMIT_String("\\x4 ", space_count, output_function,
					output_control);
			}
			else if (*((unsigned char *) in_ptr) > 0x7F) {
				(*output_function)(output_control, "\\x%02u",
					((unsigned int) *((unsigned char *) in_ptr)));
				current_col++;
			}
			else {
				(*output_function)(output_control, "%c", *in_ptr);
				current_col++;
			}
		}
		(*output_function)(output_control, "'>\n");
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_FRAME_OutputIndexRange(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_ptr,
	unsigned int area_index, int start_range_flag, int frame_index_type,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text)
#else
static int ADF_FRAME_OutputIndexRange(control_ptr, entry_ptr, entry_data_ptr,
	area_index, start_range_flag, frame_index_type, output_function,
	output_control, error_text)
ADF_CONTROL           *control_ptr;
const ADF_ENTRY       *entry_ptr;
ADF_ENTRY_DATA        *entry_data_ptr;
unsigned int           area_index;
int                    start_range_flag;
int                    frame_index_type;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code = ADF_SUCCESS;
	unsigned int   count_1;
	unsigned int   count_2;
	ADF_PARA_DATA *para_ptr;
	char          *tmp_ptr;
	char           buffer[1024];

	for (count_1 = 0; count_1 < entry_data_ptr->para_count; count_1++) {
		para_ptr = entry_data_ptr->para_list + count_1;
		if ((return_code = ADF_FixParagraph(control_ptr, entry_ptr, para_ptr,
			ADF_CFORMAT_TYPE_NONE, error_text)) != ADF_SUCCESS)
			break;
		for (count_2 = 0; count_2 < control_ptr->current_para_line_count;
			count_2++) {
			if (area_index == ADF_AREA_OUTPUT_INDEX) {
				nstrcpy(buffer, control_ptr->in_para_line_list[count_2].ptr,
					(control_ptr->in_para_line_list[count_2].length >=
					sizeof(buffer)) ? (sizeof(buffer) - 1) :
					control_ptr->in_para_line_list[count_2].length);
				if ((tmp_ptr = strrchr(buffer, ':')) == NULL)
					tmp_ptr = buffer;
				else
					tmp_ptr++;
				if (ADF_FIND_FindHTextByText(control_ptr->in_htext_count,
					control_ptr->in_htext_list, tmp_ptr, NULL) !=
					STRFUNCS_ITEM_FOUND) {
					if (start_range_flag) {
						(*output_function)(output_control,
							"   <Marker <MType %d> <MText `", frame_index_type);
						ADF_FRAME_OutputIndexText(
							control_ptr->in_para_line_list[count_2].length,
							control_ptr->in_para_line_list[count_2].ptr,
							output_function, output_control);
						(*output_function)(output_control, " \\<$nopage\\>'>>\n");
					}
					continue;
				}
			}
			(*output_function)(output_control, "   <Marker <MType %d> <MText `",
				frame_index_type);
			ADF_FRAME_OutputIndexText(
				control_ptr->in_para_line_list[count_2].length,
				control_ptr->in_para_line_list[count_2].ptr, output_function,
				output_control);
			(*output_function)(output_control, " \\<$%srange\\>'>>\n",
				(start_range_flag) ? "start" : "end");
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_FRAME_OutputIndexString(const char *out_text,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
static void ADF_FRAME_OutputIndexString(out_text, output_function,
	output_control)
const char            *out_text;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	ADF_FRAME_OutputIndexText(strlen(out_text), out_text, output_function,
		output_control);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_FRAME_OutputIndexText(unsigned int out_length,
	const char *out_text, STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
static void ADF_FRAME_OutputIndexText(out_length, out_text, output_function,
	output_control)
unsigned int           out_length;
const char            *out_text;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	for ( ; out_length; out_length--, out_text++) {
		if ((*out_text == '\\') || (*out_text == '<') || (*out_text == '>') ||
			(*out_text == '\'') || (*out_text == '`') || (*out_text == '[') ||
			(*out_text == ']') || (*out_text == ':') || (*out_text == ';'))
			(*output_function)(output_control, "\\%c", *out_text);
		else if (*out_text == '\t')
			(*output_function)(output_control, "<Char Tab>");
		else if (*((unsigned char *) out_text) > 0x7F)
			(*output_function)(output_control, "\\x%02u ",
				((unsigned int) *((unsigned char *) out_text)));
		else
			(*output_function)(output_control, "%c", *out_text);
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_FRAME_EmitString(const char *out_text, unsigned int padding,
	int exact_flag, STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
static void ADF_FRAME_EmitString(out_text, padding, exact_flag,
	output_function, output_control)
const char            *out_text;
unsigned int           padding;
int                    exact_flag;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	ADF_FRAME_EmitText(strlen(out_text), out_text, padding, exact_flag,
		output_function, output_control);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_FRAME_EmitText(unsigned int out_length, const char *out_text,
	unsigned int padding, int exact_flag, STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
static void ADF_FRAME_EmitText(out_length, out_text, padding, exact_flag,
	output_function, output_control)
unsigned int           out_length;
const char            *out_text;
unsigned int           padding;
int                    exact_flag;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	unsigned int text_length = 0;

	(*output_function)(output_control, "%-*.*s<String `",
		padding, padding, " ");

	for ( ; out_length; out_length--, out_text++) {
		if ((*out_text == '\\') || (*out_text == '<') || (*out_text == '>') ||
			(*out_text == '\'') || (*out_text == '`'))
			(*output_function)(output_control, "\\%c", *out_text);
		else if (*out_text == '\t')
			(*output_function)(output_control, "<Char Tab>");
		else if (*((unsigned char *) out_text) > 0x7F)
			(*output_function)(output_control, "\\x%02u ",
				((unsigned int) *((unsigned char *) out_text)));
		else if (exact_flag && (*out_text == ' '))
			(*output_function)(output_control, "\\x4 ");
		else
			(*output_function)(output_control, "%c", *out_text);
		if ((++text_length > 60) && (*out_text == ' ') && (out_length > 1)) {
			(*output_function)(output_control, "'>\n");
			(*output_function)(output_control, "%-*.*s<String `",
				padding, padding, " ");
			text_length = 0;
		}
	}

	(*output_function)(output_control, "'>\n");
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_FRAME_OutputString(const char *out_text,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
static void ADF_FRAME_OutputString(out_text, output_function, output_control)
const char            *out_text;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	ADF_FRAME_OutputText(strlen(out_text), out_text, output_function,
		output_control);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_FRAME_OutputText(unsigned int out_length, const char *out_text,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
static void ADF_FRAME_OutputText(out_length, out_text, output_function,
	output_control)
unsigned int           out_length;
const char            *out_text;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	for ( ; out_length; out_length--, out_text++) {
		if ((*out_text == '\\') || (*out_text == '<') || (*out_text == '>') ||
			(*out_text == '\'') || (*out_text == '`'))
			(*output_function)(output_control, "\\%c", *out_text);
		else if (*out_text == '\t')
			(*output_function)(output_control, "<Char Tab>");
		else if (*((unsigned char *) out_text) > 0x7F)
			(*output_function)(output_control, "\\x%02u ",
				((unsigned int) *((unsigned char *) out_text)));
		else
			(*output_function)(output_control, "%c", *out_text);
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_FRAME_EmitAnchor(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, unsigned int htext_index, int external_flag,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text)
#else
static int ADF_FRAME_EmitAnchor(control_ptr, entry_ptr, htext_index,
	external_flag, output_function, output_control, error_text)
ADF_CONTROL           *control_ptr;
const ADF_ENTRY       *entry_ptr;
unsigned int           htext_index;
int                    external_flag;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	int        return_code = ADF_SUCCESS;
	ADF_HTEXT *htext_ptr;
	ADF_ENTRY *htext_entry_ptr;

	htext_ptr       = control_ptr->in_htext_list + htext_index;
	htext_entry_ptr = control_ptr->in_entry_list +
		htext_ptr->in_entry_index;

	(*output_function)(output_control,
		"   <Marker <MType 8> <MText `gotolink ");
	ADF_FRAME_OutputString(htext_entry_ptr->base_name, output_function,
		output_control);
	(*output_function)(output_control, "'>>\n");

/*
	CODE NOTE: To be removed.
	if ((return_code = ADF_FRAME_GetXRefSrcFile(control_ptr, entry_ptr,
		htext_index, external_flag, error_text)) == ADF_SUCCESS) {
		htext_ptr       = control_ptr->in_htext_list + htext_index;
		htext_entry_ptr = control_ptr->in_entry_list +
			htext_ptr->in_entry_index;
		(*output_function)(output_control, "   <XRef\n");
		(*output_function)(output_control, "    <XRefName `Name_X_Ref'>\n");
		(*output_function)(output_control, "    <XRefSrcText `");
		ADF_FRAME_OutputString(htext_entry_ptr->base_name, output_function,
			output_control);
		(*output_function)(output_control, "'>\n");
		(*output_function)(output_control, "    <XRefSrcFile `%s'>\n",
			control_ptr->htext_link_name);
		(*output_function)(output_control, "   > # end of XRef\n");
	}
*/

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_FRAME_GetXRefSrcFile(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, unsigned int htext_index, int external_flag,
	char *error_text)
#else
static int ADF_FRAME_GetXRefSrcFile(control_ptr, entry_ptr, htext_index,
	external_flag, error_text)
ADF_CONTROL     *control_ptr;
const ADF_ENTRY *entry_ptr;
unsigned int     htext_index;
int              external_flag;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code = ADF_SUCCESS;
	const char   *link_file   = NULL;
	unsigned int  alloc_length;
	ADF_HTEXT    *htext_ptr;
	ADF_ENTRY    *htext_entry_ptr;

	htext_ptr       = control_ptr->in_htext_list + htext_index;
	htext_entry_ptr = control_ptr->in_entry_list + htext_ptr->in_entry_index;

	if ((external_flag != ADF_TRUE) &&
		((control_ptr->output_to_stdout_flag == ADF_TRUE) ||
		((entry_ptr->file_index == htext_entry_ptr->file_index) &&
		(!strcmp(entry_ptr->file_name, htext_entry_ptr->file_name)) &&
		(control_ptr->output_by_file_flag == ADF_TRUE))))
		link_file = NULL;
	else if (htext_entry_ptr->file_index == entry_ptr->file_index)
		link_file = NULL;
	else
		link_file =
			control_ptr->in_file_list[htext_entry_ptr->file_index].href_string;

	alloc_length = ((link_file == NULL) ? 1 : (strlen(link_file) +
		((chrcnt(link_file, '/') + chrcnt(link_file, '\\') +
		chrcnt(link_file, '.')) * 5))) + 256;

	if ((return_code = ADF_OUT_AllocHTextString(control_ptr, alloc_length,
		error_text)) == ADF_SUCCESS) {
		control_ptr->htext_link_name[0] = '\0';
		if ((link_file != NULL) && *link_file) {
			if ((*link_file == '/') || (*link_file == '\\')) {
				strcat(control_ptr->htext_link_name, "\\<r\\>\\<c\\>");
				link_file++;
			}
			else if ((*link_file == '.') &&
				((*(link_file + 1) == '/') || (*(link_file + 1) == '\\'))) {
				strcat(control_ptr->htext_link_name, "\\<c\\>");
				link_file++;
			}
			while (*link_file) {
				if ((*link_file == '/') || (*link_file == '\\'))
					strcat(control_ptr->htext_link_name, "\\<c\\>");
				else if ((*link_file == '.') && (*(link_file + 1) == '.'))
					strcat(control_ptr->htext_link_name, "\\<u\\>");
				else if ((*link_file == '<') || (*link_file == '>') ||
					(*link_file == '\'') || (*link_file == '`'))
					chrcat(chrcat(control_ptr->htext_link_name, '\\'), *link_file);
				else
					chrcat(control_ptr->htext_link_name, *link_file);
				link_file++;
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_FRAME_DoComment(const char *in_string,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
static void ADF_FRAME_DoComment(in_string, output_function, output_control)
const char            *in_string;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	(*output_function)(output_control, "# %-*.*s #\n", 74, 74, in_string);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_FRAME_DoCommentsFloating(const char *in_string_1,
	const char *in_string_2, STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
static void ADF_FRAME_DoCommentsFloating(in_string_1, in_string_2,
	output_function, output_control)
const char            *in_string_1;
const char            *in_string_2;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	char buffer[74 + 1];

	if ((strlen(in_string_1) + strlen(in_string_2)) <= 74)
		ADF_FRAME_DoComment(strcat(strcpy(buffer, in_string_1), in_string_2),
			output_function, output_control);
	else
		(*output_function)(output_control, "# %s%s #\n", in_string_1,
			in_string_2);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_FRAME_DoBorder(STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
static void ADF_FRAME_DoBorder(output_function, output_control)
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	(*output_function)(output_control, "# ");
	STR_EMIT_Char('#', 74, output_function, output_control);
	(*output_function)(output_control, " #\n");
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static char *ADF_FRAME_GetParaName(unsigned int pformat_index,
	char *pformat_name)
#else
static char *ADF_FRAME_GetParaName(pformat_index, pformat_name)
unsigned int  pformat_index;
char         *pformat_name;
#endif /* #ifndef NARGS */
{
	const ADF_PFORMAT_DEF *pformat_ptr;

	if (pformat_index < ADF_PFORMAT_COUNT) {
		pformat_ptr = ADF_GetParaFormat(pformat_index);
		sprintf(pformat_name, "ADF_%s_%s%s_%u",
			(pformat_ptr->format_type == ADF_PFORMAT_TYPE_BB) ? "BB" :
			(pformat_ptr->format_type == ADF_PFORMAT_TYPE_IN) ? "IN" :
			(pformat_ptr->format_type == ADF_PFORMAT_TYPE_NM) ? "NM" : "NO",
			(pformat_ptr->char_format_flag == ADF_TRUE)       ? "F"  : "U",
			(pformat_ptr->small_font_flag == ADF_TRUE)        ? "S"  : "N",
			pformat_ptr->indent_level);
	}
	else
		*pformat_name = '\0';

	return(pformat_name);

}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#ifdef __MSDOS__
COMPAT_EXTERN_DATA_DECL unsigned int _stklen = 24000;
#endif /* __MSDOS__ */

COMPAT_FN_DECL(int main, (int argc, char **argv));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int          return_code = ADF_SUCCESS;
	unsigned int count_1;
	ADF_CONTROL  control_data;
	char         error_text[ADF_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'ADF_FRAME_OutputToStdout()'\n");
	fprintf(stderr, "---- ------- --- ----------------------------\n\n");

	ADF_INIT_Control(&control_data);

	control_data.cont_on_error_flag     = ADF_TRUE;
	control_data.sort_order_type        = ADF_SORT_ENTRY_BASE_NAME;
	control_data.hyper_text_flag        = ADF_FALSE;
	control_data.keep_bad_see_also_flag = ADF_TRUE;
	control_data.area_name_type         = ADF_AREA_NAME_TYPE_INTERNAL;
	control_data.area_order_type        = ADF_AREA_ORDER_TYPE_INTERNAL;
	control_data.hyper_text_flag        = ADF_TRUE;

	if (argc < 2) {
		sprintf(error_text, "Invalid command line encountered.");
		fprintf(stderr,
			"USAGE:\n   %s <adf-db-file-name> [<adf-db-file-name>...]\n",
			argv[0]);
		return_code = ADF_BAD_ARGS_FAILURE;
	}
	else {
		for (count_1 = 1; count_1 < argc; count_1++) {
			fprintf(stderr, "File: %s\n", argv[count_1]);
			if ((return_code = ADF_OpenADFFileIn(&control_data, argv[count_1],
				error_text)) != ADF_SUCCESS) {
				if (return_code != ADF_PARSE_FAILURE)
					break;
				fprintf(stderr, "%s\n", error_text);
				return_code = ADF_SUCCESS;
			}
		}
		if (return_code == ADF_SUCCESS) {
			if ((return_code = ADF_FinalizeEntries(&control_data, error_text)) !=
				ADF_SUCCESS)
				goto EXIT_FUNCTION;
			ADF_FRAME_OutputStart(&control_data, "Output to <stdout>", NULL,
				NULL, NULL);
			for (count_1 = 0; count_1 < control_data.in_entry_order_count;
				count_1++) {
				if ((return_code = ADF_FRAME_OutputToStdout(&control_data,
					control_data.in_entry_order_list[count_1], NULL,
					error_text)) != ADF_SUCCESS)
					goto EXIT_FUNCTION;
			}
			ADF_FRAME_OutputEnd(&control_data, NULL, NULL);
		}
	}

EXIT_FUNCTION:

	ADF_FREE_Control(&control_data);

	if (return_code != ADF_SUCCESS)
		fprintf(stderr, "ERROR: %s\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */


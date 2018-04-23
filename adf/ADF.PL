#!/usr/local/bin/taintperl
# ###########################################################################
# ###########################################################################
# Automated Documentation Facility (ADF)
# ###########################################################################
#
#    Module Name			:	adf
#
#    Module Version     :	1.103
#
#    Last Extracted		:	93/06/11   03:32:58
#
#    Last Updated			:	93/05/08   16:38:35
#
#    Module Description	:	Contains the entire thing.
#
#    Revision History	:	1992-01-16 --- Creation.
#										Michael L. Brock
#
#
#		Copyright Michael L. Brock 1992 - 2018.
#		Distributed under the Boost Software License, Version 1.0.
#		(See accompanying file LICENSE_1_0.txt or copy at
#		http://www.boost.org/LICENSE_1_0.txt)
#
# ###########################################################################

# Support for the following file types:
#    .c / .cpp / .cc / .cxx / .h / .hxx / .hpp / .hh / .pl / .S / .s / .asm
#
# Add support for specified file types as follows:
#    /* BOH [.<file-type>]
#    # BOH [.<file-type>]
#

	$|           = 1;
	$ENV{"PATH"} = "/bin:/usr/bin:/usr/etc:/usr/local/bin:/usr/sccs:/usr/ucb";
	$ENV{"IFS"}  = "";
	$ENV{"PWD"}  = &do_untaint($ENV{"PWD"});

	&ADF_InitVariables();

	if ($ADF_ProgramName eq "adfprep") {
		$ADF_ProgramType = "PREP";
	}
	elsif ($ADF_ProgramName eq "adfget") {
		$ADF_ProgramType = "GET";
	}
	elsif ($ADF_ProgramName eq "adfchk") {
		$ADF_ProgramType = "CHK";
	}
	elsif ($ADF_ProgramName eq "adfcomb") {
		$ADF_ProgramType = "COMB";
	}
	elsif ($ADF_ProgramName eq "adfout") {
		$ADF_ProgramType = "OUT";
	}
	else {
		$ADF_ProgramType = "ALL";
	}

	if (grep(/^\-HELP$/i, @ARGV)) {
		&ADF_DoUsage(0, $ADF_ProgramName, $ADF_ProgramType,
			"Help request with \'-HELP\' noted . . .");
	}
	elsif (grep(/^\-DESCRIBE_?DOMAINS?$/i, @ARGV)) {
		print STDERR "Request to show arguments with \'",
			(grep(/^\-DESCRIBE_?DOMAINS?$/i, @ARGV))[0],
			"\' noted.\n\n";
		&ADF_DescribeDomains();
		exit(0);
	}

	if (grep(/^\-SHOW_?SETS?$|\-SHOW_?SETTINGS?$/i, @ARGV)) {
		print STDERR "Request to show arguments with \'",
			(grep(/^\-SHOW_?SETS?$|\-SHOW_?SETTINGS?$/i, @ARGV))[0],
			"\' noted.\n\n";
	}

	&ADF_GetArgs($ADF_ProgramName, $ADF_ProgramType);

	if (grep(/^\-SHOW_?SETS?$|\-SHOW_?SETTINGS?$/i, @ARGV)) {
		@ARGV = grep(!/^\-SHOW_?SETS?$|\-SHOW_?SETTINGS?$/i, @ARGV);
		&ADF_ShowArgs($#ARGV + 1, $ADF_ProgramType);
		if ($#ARGV == -1) { exit(0); }
	}

	if (!($#ARGV + 1)) {
		&ADF_DoUsage(-1, $ADF_ProgramName, $ADF_ProgramType,
			"No input files specified on the command-line.");
	}

	foreach $perl_code_item (@ADF_PerlCodeList) {
		if (!open(IN_PERL_CODE, "<$perl_code_item")) {
			print STDERR "Unable to open \'-PERL_CODE\' file ",
				"\'$perl_code_item\' for reading.\n\n";
			exit(1);
		}
		$/              = "";
		$perl_code_list = <IN_PERL_CODE>;
		$/              = "\n";
		close(IN_PERL_CODE);
		if ((!defined($tmp_string = eval($perl_code_list))) || ($@ ne "")) {
			print STDERR "Error occurred while evaluating the \'-PERL_CODE\' ",
				"file \'$perl_code_item\'", ($@ ne "") ? " --- $@\n\n" : ".\n\n";
			exit(1);

		}
		$perl_code_list = "";
	}

	if ($return_code = &ADF_DoOperation($error_text, $ADF_ProgramType,
		@ARGV)) {
		print STDERR "ERROR: $error_text\n\n";
	}

	exit($return_code);

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_InitVariables {
	local($count_1, @tmp_array);

	$SizeOfLong                  = length(pack("L", 0));

	$ADF_ProgramName            = $0;
	$ADF_ProgramName            =~ s/^.+\/(\S+)/\1/;

	$ADF_FileSigText            = "[[[((({{{<<<ADF_DATABASE_FILE>>>}}})))]]]";
	$ADF_FileSigFormat          = $ADF_FileSigText." %s %s %010u %-10.10s\n";
	$ADF_FileSigLength          =
		length($ADF_FileSigText) + 1 + 10 + 1 + 8 + 1 + 10 + 1 + 10 + 1;
	$ADF_FileEndSigText         = "END_OF_ADF_FILE";
	$ADF_FileEndSigFormat       =
		$ADF_FileEndSigText." %010u %010u %010u %010u %010u %010u\n";
	$ADF_FileEndSigLength       = length($ADF_FileEndSigText) +
		1 + 10 + 1 + 10 + 1 + 10 + 1 + 10 + 1 + 10 + 1 + 10 + 1;
	$ADF_FileMinimumLength      = $ADF_FileSigLength + $ADF_FileEndSigLength;

	$ADF_TempFileBase           = `/bin/hostname`; chop($ADF_TempFileBase);
	$ADF_TempFileBase           = "/tmp/ADF_".$ADF_TempFileBase."_".$$;

	%ADF_RegisteredParseDomains = ();

	$DATA_NAME                   = 0;
	$DATA_FLAG                   = 1;
	$DATA_REQUIRED               = 2;
	$DATA_WRAP                   = 3;
	$DATA_LTRIM                  = 4;
	$DATA_RTRIM                  = 5;
	$DATA_SQUEEZE                = 6;
	$DATA_PARA_FORMAT            = 7;
	$DATA_CHAR_FORMAT            = 8;
	$DATA_PATTERN                = 9;

	$ADF_ParseComponentCount    = $DATA_PATTERN + 1;

	$FDB_DATA_NAME               = 0;
	$FDB_DATA_FLAG               = 1;
	$FDB_DATA_REQUIRED           = 2;
	$FDB_DATA_WRAP               = 3;
	$FDB_DATA_LTRIM              = 4;
	$FDB_DATA_RTRIM              = 5;
	$FDB_DATA_SQUEEZE            = 6;
	$FDB_DATA_PARA_FORMAT        = 7;
	$FDB_DATA_CHAR_FORMAT        = 8;

	$ADF_FDBParseComponentCount = $FDB_DATA_CHAR_FORMAT + 1;

	$ADF_ManMarginPadding       = "   ";

	$ADF_CheckCommentFlag       = "NO";
	$ADF_DefaultAuthor          = "";
	$ADF_DefaultCopyright       = "";
	$ADF_DefaultSection         = "3";
	$ADF_ErrorOnNoComment       = "NO";
	$ADF_ForcedAuthor           = "";
	$ADF_ForcedCopyright        = "";
	$ADF_ForcedSection          = "";
	@ADF_PerlCodeList           = ();
	$ADF_PrepSortFlag           = "NO";
	$ADF_NoRequiredSectionsFlag = "YES";
	$ADF_TabSetting             = 3;

	$ADF_SortGetDataFlag        = "NO";
	$ADF_GetDataSeparator       = " ";
	@ADF_GetDataNameList        = ();
	@ADF_GetDataIndexList       = ();

	$ADF_IgnoreBadXRefsFlag     = "NO";

	$ADF_SortCombinedFiles      = "NO";
	$ADF_RemoveBadXRefsFlag     = "NO";

	%ADF_ExternalRefFileList    = ();
	$ADF_FrameFMHOME            = $ENV{"FMHOME"};
	$ADF_FrameHyperText         = "NO";
	$ADF_KeepBadXRefsFlag       = "NO";
	$ADF_ListFrameXRefs         = "NO";
	$ADF_ManDirectory           = "./";
	$ADF_FormatSortFlag         = "NO";
	$ADF_OutputTypeFlag         = "ASCII";

	$ADF_ZeroDataFlag           = "NO";

	$ADF_XRefTreeFlag           = "NO";

	$ADF_FirstDuplicateName     = "NO";  # From -FIRST_DUPLICATE_NAME
	$ADF_LastDuplicateName      = "NO";  # From -LAST_DUPLICATE_NAME

	$ADF_IncludeFileFlag        = "NO";
	$ADF_IncludeNameFlag        = "NO";
	$ADF_IncludeTypeFlag        = "NO";
	$ADF_ExcludeFileFlag        = "NO";
	$ADF_ExcludeNameFlag        = "NO";
	$ADF_ExcludeTypeFlag        = "NO";

	%ADF_IncludeFileArray       = ();
	%ADF_IncludeNameArray       = ();
	%ADF_IncludeTypeArray       = ();
	%ADF_ExcludeFileArray       = ();
	%ADF_ExcludeNameArray       = ();
	%ADF_ExcludeTypeArray       = ();

	$MaxLabelLength              = 0;
	$LineLength                  = 75;
	$LineLengthSynopsis          = 60;

	# ##################################################################	#
	# ##################################################################	#
	#    The following describe the fields in an ADF database directory	#
	# entry as it appears in the database.											#
	# ##################################################################	#
	$ADF_DB_BASE_NAME      = 0;
	$ADF_DB_TYPE           = 1;
	$ADF_DB_FILE_NAME      = 2;
	$ADF_DB_FULL_FILE_NAME = 3;
	$ADF_DB_OFFSET         = 4;
	$ADF_DB_LENGTH         = 5;
	$ADF_DB_NEXT_OFFSET    = 6;
	# ##################################################################	#

	# ##################################################################	#
	# ##################################################################	#
	#    The following describe the fields in an ADF database directory	#
	# entry as it appears after being loaded by the ADF function			#
	# 'ADF_MultipleLoadDatabase()'.													#
	# ##################################################################	#
	$ADF_LD_FILE_INDEX     = 0;
	$ADF_LD_BASE_NAME      = 1;
	$ADF_LD_TYPE           = 2;
	$ADF_LD_FILE_NAME      = 3;
	$ADF_LD_FULL_FILE_NAME = 4;
	$ADF_LD_OFFSET         = 5;
	$ADF_LD_LENGTH         = 6;
	$ADF_LD_NEXT_OFFSET    = 7;
	# ##################################################################	#

	# ##################################################################	#
	# ##################################################################	#
	# ##################################################################	#
	$ADF_ParaFormatSig          = "\002[*[{(ADF_PARA_FORMAT)}]*]";

	$ADF_ParaFormatLength       = 2 + 1 + 1 + 1 + 3 + 1 + 6 + 1 + 3;

	%ADF_ParaFormatPatternArray = (
		'^\(\|\)',       "LN|0|000|------|NO ",
		'^\(\|\|\)',     "LN|1|000|------|NO ",
		'^\(\|\|\|\)',   "LN|2|000|------|NO ",
		'^\(\|\|\|\|\)', "LN|3|000|------|NO ",
		'^\(\@\)',       "IN|0|000|NORMAL|YES",
		'^\(\-\)',       "IN|1|000|NORMAL|YES",
		'^\(\-\-\)',     "IN|2|000|NORMAL|YES",
		'^\(\-\-\-\)',   "IN|3|000|NORMAL|YES",
		'^\(\.\)',       "BB|1|000|NORMAL|YES",
		'^\(\.\.\)',     "BB|2|000|NORMAL|YES",
		'^\(\.\.\.\)',   "BB|3|000|NORMAL|YES",
		'^\[\@\]',       "IN|0|000|NORMAL|NO ",
		'^\[\-\]',       "IN|1|000|NORMAL|NO ",
		'^\[\-\-\]',     "IN|2|000|NORMAL|NO ",
		'^\[\-\-\-\]',   "IN|3|000|NORMAL|NO ",
		'^\<\|\>',       "LN|0|000|------|NO ",
		'^\<\|\|\>',     "LN|1|000|------|NO ",
		'^\<\|\|\|\>',   "LN|2|000|------|NO ",
		'^\<\|\|\|\|\>', "LN|3|000|------|NO ",
		'^\<\@\>',       "IN|0|000|SMALL |YES",
		'^\<\-\>',       "IN|1|000|SMALL |YES",
		'^\<\-\-\>',     "IN|2|000|SMALL |YES",
		'^\<\-\-\-\>',   "IN|3|000|SMALL |YES",
		'^\<\.\>',       "BB|1|000|SMALL |YES",
		'^\<\.\.\>',     "BB|2|000|SMALL |YES",
		'^\<\.\.\.\>',   "BB|3|000|SMALL |YES",
		'^\{\@\}',       "IN|0|000|SMALL |NO ",
		'^\{\-\}',       "IN|1|000|SMALL |NO ",
		'^\{\-\-\}',     "IN|2|000|SMALL |NO ",
		'^\{\-\-\-\}',   "IN|3|000|SMALL |NO "
	);

	$ADF_ParaFormatNMPatternString = '^\(\+{1,3}\d+\)|^\<\+{1,3}\d+\>';
	$ADF_ParaFormatPatternString   = $ADF_ParaFormatNMPatternString;
	foreach $this_one (keys(%ADF_ParaFormatPatternArray)) {
		$ADF_ParaFormatPatternString .= "|".$this_one;
	}
	# ##################################################################	#

	# ##################################################################	#
	# ##################################################################	#
	#    The following code defines the master list of ADF components.	#
	# The string which comprises each of the elements of the array			#
	# 'ADF_FlagNameList' is separated by the spaces in the string into	#
	# the following three fields:														#
	#																							#
	#    1) The name of master component.											#
	#    2) Whether the master component is required to be present.		#
	#    3) Whether the master component is to be output.						#
	# ##################################################################	#
	@ADF_FlagNameList = (
		"FLAG_BASE_NAME Y N",
		"FLAG_FILE_TYPE Y N",
		"FLAG_NAME Y Y",
		"FLAG_SYNOPSIS N Y",
		"FLAG_CODE_SYNTAX N Y",
		"FLAG_DESCRIPTION N Y",
		"FLAG_DEFINITIONS N Y",
		"FLAG_TERMINOLOGY N Y",
		"FLAG_OPTIONS N Y",
		"FLAG_PARAMETERS N Y",
		"FLAG_COMMANDS N Y",
		"FLAG_MEMBERS N Y",
		"FLAG_RETURNS N Y",
		"FLAG_ERROR_MESSAGES N Y",
		"FLAG_ENVIRONMENT N Y",
		"FLAG_FILES N Y",
		"FLAG_ALGORITHMS N Y",
		"FLAG_DEBUGGING N Y",
		"FLAG_DIAGNOSTICS N Y",
		"FLAG_NOTES N Y",
		"FLAG_CAVEATS N Y",
		"FLAG_DEFAULTS N Y",
		"FLAG_BUGS N Y",
		"FLAG_LIMITATIONS N Y",
		"FLAG_COMPATIBILITY N Y",
		"FLAG_IDIOSYNCRACIES N Y",
		"FLAG_SEE_ALSO N Y",
		"FLAG_EXAMPLES N Y",
		"FLAG_CODE_EXAMPLES N Y",
		"FLAG_AUTHORS N Y",
		"FLAG_CONTRIBUTORS N Y",
		"FLAG_ACKNOWLEDGMENTS N Y",
		"FLAG_CREDITS N Y",
		"FLAG_REFERENCES N Y",
		"FLAG_RESTRICTIONS N Y",
		"FLAG_DISCLAIMERS N Y",
		"FLAG_COPYING N Y",
		"FLAG_COPYRIGHTS N Y",
		"FLAG_TRADEMARKS N Y",
		"FLAG_SOURCE_FILE_NAME N Y",
		"FLAG_SOURCE_FILE_DATE N Y",
		"FLAG_MAN_SECTION N N",
		"FLAG_TAB_SETTING N N",
		"FLAG_OUTPUT_INDEX N N",
		"FLAG_PUBLISH_XREF N N",
		"FLAG_PUBLISH_NAME N N"
	);

	%ADF_FlagNameArray      = ();
	@ADF_MasterRequiredFlag = ();
	@ADF_MasterDisplayFlag  = ();

	for ($count_1 = 0; $count_1 <= $#ADF_FlagNameList; $count_1++) {
		@tmp_array                         =
			split(/\s+/, $ADF_FlagNameList[$count_1]);
		$ADF_FlagNameArray{$tmp_array[0]} =  $count_1;
		$ADF_FlagNameList[$count_1]       = $tmp_array[0];
		$ADF_MasterRequiredFlag[$count_1] = $tmp_array[1];
		$ADF_MasterDisplayFlag[$count_1]  = $tmp_array[2];
		eval "\$$tmp_array[0] = $count_1;";
	}
	# ##################################################################	#

	%ADF_FrameCharFormatSpecs = (
		"B", "<Font <FWeight `Bold'>>",
		"b", "<Font <FWeight `Regular'>>",
		"I", "<Font <FAngle `Italic'>>",
		"i", "<Font <FAngle `Regular'>>",
		"O", "<Font <FOverline Yes>>",
		"o", "<Font <FOverline No>>",
		"T", "<Font <FStrike Yes>>",
		"t", "<Font <FStrike No>>",
		"U", "<Font <FUnderline Yes>>",
		"u", "<Font <FUnderline No>>",
		"Y", "<Font <FSupScript Yes>>",
		"y", "<Font <FSupScript No>>",
		"Z", "<Font <FSubScript Yes>>",
		"z", "<Font <FSubScript No>>",
	);

	$ADF_FrameCharFormatsOff = "   <Font <FFamily `Symbol'>>\n";

	foreach $tmp_string (sort(grep(/[a-z]/, keys(%ADF_FrameCharFormatSpecs)))) {
		$ADF_FrameCharFormatsOff .= 
			"   ".$ADF_FrameCharFormatSpecs{$tmp_string}."\n";
	}

	$ADF_FrameCharFormatSpecs{"N"} = $ADF_FrameCharFormatsOff;
	$ADF_FrameCharFormatSpecs{"n"} = $ADF_FrameCharFormatsOff;

	&ADF_InitUsageLists();

	&ADF_InitDataTypes();

	&DATFUNCS_InitData();
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_InitUsageLists {

	@ADF_PREPUsageList = (
		"-CHECK[_]ONLY",
		"Not implemented in this version.",
		"-DEFAULT[_]AUTHOR[S]=[\"|\'|\`]<author-name>[\"|\'|\`]",
		"If the parse domain supports the 'AUTHOR'component and no 'AUTHOR' ".
		"component is encountered in an ADF comment entry, then ".
		"<author-name> will be inserted.",
		"-DEFAULT[_]COPYRIGHT[S]=[\"|\'|\`]<copyright-text>[\"|\'|\`]",
		"If the parse domain supports the 'COPYRIGHT'component and no ".
		"'COPYRIGHT' component is encountered in an ADF comment entry, then ".
		"<copyright-text> will be inserted.",
		"-DEFAULT[_]SECTION[S]=<section-name>",
		"If no 'man' page section is specified, then <section-name> will be ".
		"used.\n\n".
		"<section-name> must be structured according to the rules for naming ".
		"'man' page files --- that is, as follows:\n\n".
		"   {1|2|3|4|5|6|7|8|9|l|n|o|p}[<optional-text>]\n\n".
		"The default 'man' page section is '3'.",
		"-ERROR[S][_]ON[_]NO[_]COMMENT[S]",
		"If this parameter is set then any source files given to ADF which do ".
		"not have an ADF comment entry will result in an error.",
		"-FORCE[D][_]AUTHOR[S]=[\"|\'|\`]<author-name>[\"|\'|\`]",
		"If the parse domain supports the 'AUTHOR'component <author-name> ".
		"will be inserted.",
		"-FORCE[D][_]COPYRIGHT[S]=[\"|\'|\`]<copyright-text>[\"|\'|\`]",
		"If the parse domain supports the 'COPYRIGHT'component then ".
		"<copyright-text> will be inserted.",
		"-FORCE[D][_]SECTION[S]=<section-name>",
		"This parameter overrides any specified 'man' page section with ".
		"<section-name>.\n\n".
		"<section-name> must be structured according to the rules for naming ".
		"'man' page files --- that is, as follows:\n\n".
		"   {1|2|3|4|5|6|7|8|9|l|n|o|p}[<optional-text>]",
		"-PERL[_]CODE[S]=<file-name>",
		"Each <file-name> specified by an instance of this parameter will be ".
		"read and 'eval'ed as a perl script by the program.",
		"-PREP[_]SORT[S|ING]",
		"If this this parameter is used on the command-line, the database ".
		"of ADF comment entries will be sorted by the base name.",
		"-NO[_]REQUIRED[_]SECTION[S]",
		"If this parameter is set, errors which would otherwise be generated ".
		"for missing or empty components which are required by the parse ".
		"domain are ignored.",
		"-TAB[S][_]SET[TING][S]=<number>",
		"This parameter sets the value used for tab expansion to <number>. ".
		"Valid values for number may range from 0 to 8, inclusive.\n\n".
		"The default tab setting is 3.",
		"-ZERO[_]DATE[S]",
		"This parameter forces the date/time stamp of any ADF database files ".
		"created to be zero (date = \'0000-00-00\', time = '00:00:00').\n\n".
		"This parameter is included to allow ADF database files to be compared ".
		"using the Unix system utility \'diff\'."
	);

	@ADF_GETUsageList = (
		"-SORT[_]GET[_]DATA",
		"",
		"-GET[_]DATA[_]NAME[S]=<name-list>",
		"",
		"-GET[_]DATA[_]SEPARATOR[S]=<string>",
		""
	);

	@ADF_CHKUsageList = (
		"-IGNORE[_]BAD[_]XREF[S]",
		"Not implemented in this version.",
	);

	@ADF_COMBUsageList = (
		"-REMOVE[_]BAD[_]XREF[S]",
		"Not implemented in this version.",
		"-SORT[_]COMBINE[D][_]FILE[S]",
		"If this this parameter is used on the command-line, the database ".
		"of ADF comment entries will be sorted by the base name.",
		"-ZERO[_]DATE[S]",
		"This parameter forces the date/time stamp of any ADF database files ".
		"created to be zero (date = \'0000-00-00\', time = '00:00:00').\n\n".
		"This parameter is included to allow ADF database files to be compared ".
		"using the Unix system utility \'diff\'."
	);

	@ADF_OUTUsageList = (
		"-EXTERN[AL]_REF[S]=<adf-db-file-name>[=<frame-doc-file-name>]",
		"This parameter tells ADF how to resolve external cross-references ".
		"and produce embedded hypertext entries for FrameMaker output.\n\n".
		"<adf-db-file-name> is the name of the ADF database file in which ".
		"reside the external references.\n\n".
		"The optional <frame-doc-file-name> is the FrameMaker file name of ".
		"the FrameMaker document to which the cross-references are to be ".
		"resolved.\n\n".
		"Note that if <frame-doc-file-name> resides in the current directory, ".
		"it must be specified as ./<frame-doc-file-name>.",
#		"-FRAME[_][MAKER[_]]FMHOME=<directory-name>",
#		"",
		"-FRAME[_]HYPER[_]TEXT",
		"Embeds a FrameMaker hypertext reference where the base names of ".
		"ADF entries are encountered.",
		"-KEEP[_]BAD[_]XREF[S]",
		"Any cross-references which not resolved at the time FrameMaker ".
		"output is performed are usually removed. This parameter prevents ".
		"that. If you use this parameter, you may therefore have to manually ".
		"fix-up unresolved cross-references within your FrameMaker document.",
#		"-LIST[_]FRAME[_][MAKER[_]]XREF[S]",
#		"",
		"-MAN[_][DIR[ECTORY]]=<directory-name>",
		"This parameted specifies the directory in which 'man' pages will be ".
		"created.\n\n".
		"If the directory does not exist, it is created.\n\n".
		"The default directory used for man pages if this parameter is not ".
		"specified is './man'.",
		"-FORMAT[_]SORT[S|ING]",
		"If this parameter is specified, then all entries in the ADF input ".
		"files will be sorted by their 'BASE_NAME' component before being ".
		"formatted for output.",
		"-OUTPUT={ASCII|MAN[[_]PAGE[S]|FRAME[[_]MAKER]}",
		"This parameter specifies the type of output formatting to be ".
		"performed.\n\n".
		"For 'ASCII', some 'bare-bones' formatting is done. No special ".
		"formatting such as bold-facing, italics, underlining, et cetera ".
		"is available. 'ASCII' output is sent to 'stdout'.\n\n".
		"For 'MAN', a man page is created with the formatting attributes ".
		"available within the 'man' macro package. 'MAN' output is sent to ".
		"the directory specified by the '-MAN_DIRECTORY=' parameter, the ".
		"'man' page section being created, and the base name of the ADF ".
		"ADF comment entry.\n\n".
		"For 'FRAME_MAKER', a FrameMaker MIF is emitted to 'stdout'. Final ".
		"FrameMaker formatting must be done by using all but the paragraph ".
		"formats from an existing FrameMaker file.\n\n".
		"Note that the default output type is 'ASCII'."
	);

	@ADF_ANYUsageList = (
		"-HELP",
		"Emits this help text to the standard output.\n\n".
		"Note, however, that if the help text is being emitted because of ".
		"an error in the command-line parameters, the help text is sent to ".
		"standard error.",
		"-SHOW[_][SET][TING][S]",
		"Emits the settings (both the defaults and those settings overridden ".
		"explicitly by command-line parameters) to the standard output.",
		"-DESCRIBE[_]DOMAIN[S]",
		"Emits a listing of the loaded ADF parse domains to the standard ".
		"output.",
		"-XREF[_]TREE[S]",
		"If this parameter is specified on the command-line, then any entries".
		"excluded (or not included) will be re-included if they are cross-".
		"referenced by any other entries.",
		"-FIRST_DUPLICATE_NAME",
		"If this parameter is specified on the command-line, then duplicate ".
		"entry names (which usually cause an error) will be ignored.",
		"-LAST_DUPLICATE_NAME",
		"If this parameter is specfied on the command-line, then duplicate ".
		"entry names (which usually cause and error) will result in the last".
		"instance of the entry becoming effective.",
		"-INCLUDE[_]FILE[S]=<file-name>",
		"The file names listed in <file-name> will be the only ones included ".
		"by the ADF operation.\n\n".
		"Note that this parameter may occur multiple times; if it does, then ".
		"the contents of the <file-name> portions of the parameters will be ".
		"concatenated uniquely.",
		"-INCLUDE[_]NAME[S]=<file-name>",
		"The names listed in <file-name> will be the only ones included ".
		"by the ADF operation.\n\n".
		"Note that this parameter may occur multiple times; if it does, then ".
		"the contents of the <file-name> portions of the parameters will be ".
		"concatenated uniquely.",
		"-INCLUDE[_]TYPE[S]=<file-name>",
		"The extensions listed in <file-name> will be the only ones included ".
		"by the ADF operation.\n\n".
		"Note that this parameter may occur multiple times; if it does, then ".
		"the contents of the <file-name> portions of the parameters will be ".
		"concatenated uniquely.",
		"-EXCLUDE[_]FILE[S]=<file-name>",
		"The file names listed in <file-name> will not be included ".
		"by the ADF operation.\n\n".
		"Note that this parameter may occur multiple times; if it does, then ".
		"the contents of the <file-name> portions of the parameters will be ".
		"concatenated uniquely.",
		"-EXCLUDE[_]NAME[S]=<file-name>",
		"The names listed in <file-name> will not be included ".
		"by the ADF operation.\n\n".
		"Note that this parameter may occur multiple times; if it does, then ".
		"the contents of the <file-name> portions of the parameters will be ".
		"concatenated uniquely.",
		"-EXCLUDE[_]TYPE[S]=<file-name>",
		"The extensions listed in <file-name> will not be included ".
		"by the ADF operation.\n\n".
		"Note that this parameter may occur multiple times; if it does, then ".
		"the contents of the <file-name> portions of the parameters will be ".
		"concatenated uniquely."
	);
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_GetArgs {
	local($program_name, $program_type) = @_;

	if ($program_type =~ /PREP|ALL/) {
		&ADF_GetPREPArgs($program_name, $program_type);
		&ADF_GetOtherArgs($program_name, $program_type);
	}

	if ($program_type =~ /GET/) {
		&ADF_GetGETArgs($program_name, $program_type);
		&ADF_GetOtherArgs($program_name, $program_type);
	}

	if ($program_type =~ /CHK|ALL/) {
		&ADF_GetCHKArgs($program_name, $program_type);
		&ADF_GetOtherArgs($program_name, $program_type);
	}

	if ($program_type =~ /COMB|ALL/) {
		&ADF_GetCOMBArgs($program_name, $program_type);
		&ADF_GetOtherArgs($program_name, $program_type);
	}

	if ($program_type =~ /OUT|ALL/) {
		&ADF_GetOUTArgs($program_name, $program_type);
		&ADF_GetOtherArgs($program_name, $program_type);
	}

}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_GetPREPArgs {
	local($program_name, $program_type) = @_;
	local(@tmp_list);

	if (grep(/^\-DEFAULT_?AUTHORS?=/,  @ARGV) &&
		grep(/^\-FORCED?_?AUTHORS?=/,  @ARGV)) {
		&ADF_DoUsage(-1, $program_name, $program_type,
			"Mixed \''-DEFAULT_AUTHOR=\' and \'-FORCED_AUTHOR=\' ".
			"parameters encountered.");
	}

	if (grep(/^\-DEFAULT_?COPYRIGHTS?=/,  @ARGV) &&
		grep(/^\-FORCED?_?COPYRIGHTS?=/,  @ARGV)) {
		&ADF_DoUsage(-1, $program_name, $program_type,
			"Mixed \''-DEFAULT_COPYRIGHT=\' and \'-FORCED_COPYRIGHT=\' ".
			"parameters encountered.");
	}

	if (grep(/^\-DEFAULT_?SECTIONS?=/,  @ARGV) &&
		grep(/^\-FORCED?_?SECTIONS?=/,  @ARGV)) {
		&ADF_DoUsage(-1, $program_name, $program_type,
			"Mixed \''-DEFAULT_SECTION=\' and \'-FORCED_SECTION=\' ".
			"parameters encountered.");
	}

	if (grep(/^\-CHECKS?$|^\-CHECKS?_?ONLY$/i, @ARGV)) {
		@ARGV = grep(!/^\-CHECKS?$|^\-CHECKS?_?ONLY$/i, @ARGV);
		$ADF_CheckCommentFlag = "YES";
	}

	if (@tmp_list = grep(/^\-DEFAULT_?AUTHORS?=/i, @ARGV)) {
		if (grep(/^\-DEFAULT_?AUTHORS?=$/i, @ARGV)) {
			&ADF_DoUsage(-1, $program_name, $program_type, "Invalid \'".
				(grep(/^\-DEFAULT_?AUTHORS?=$/i, @ARGV))[0]."\' parameter.");
		}
		@ARGV = grep(!/^\-DEFAULT_?AUTHORS?=/i, @ARGV);
		grep(
			do {
				$_ =~ s/^.*=//;
				$_ =~ s/^\"+|^\'+|^\`+|\"+$|\'+$|\`+$//g;
				$_ =~ s/^\s+|\s+$//g;
				$_ =~ s/\s+/ /g;
				0;
			}, @tmp_list);
		&do_uniq(@tmp_list);
		if ($#tmp_list > 0) {
			&ADF_DoUsage(-1, $program_name, $program_type,
				"Multiple \'-DEFAULT_AUTHOR=\' parameters encountered.");
		}
		$ADF_DefaultAuthor = $tmp_list[0];
	}

	if (@tmp_list = grep(/^\-DEFAULT_?COPYRIGHTS?=/i, @ARGV)) {
		if (grep(/^\-DEFAULT_?COPYRIGHTS?=$/i, @ARGV)) {
			&ADF_DoUsage(-1, $program_name, $program_type, "Invalid \'".
				(grep(/^\-DEFAULT_?COPYRIGHTS?=$/i, @ARGV))[0]."\' parameter.");
		}
		@ARGV = grep(!/^\-DEFAULT_?COPYRIGHTS?=/i, @ARGV);
		grep(
			do {
				$_ =~ s/^.*=//;
				$_ =~ s/^\"+|^\'+|^\`+|\"+$|\'+$|\`+$//g;
				$_ =~ s/^\s+|\s+$//g;
				$_ =~ s/\s+/ /g;
				0;
			}, @tmp_list);
		&do_uniq(@tmp_list);
		if ($#tmp_list > 0) {
			&ADF_DoUsage(-1, $program_name, $program_type,
				"Multiple \'-DEFAULT_COPYRIGHT=\' parameters encountered.");
		}
		$ADF_DefaultCopyright = $tmp_list[0];
	}

	if (@tmp_list = grep(/^\-DEFAULT_?SECTIONS?=/i, @ARGV)) {
		if (grep(/^\-DEFAULT_?SECTIONS?=$/i, @ARGV)) {
			&ADF_DoUsage(-1, $program_name, $program_type, "Invalid \'".
				(grep(/^\-DEFAULT_?SECTIONS?=$/i, @ARGV))[0]."\' parameter.");
		}
		@ARGV = grep(!/^\-DEFAULT_?SECTIONS?=/i, @ARGV);
		grep(do { $_ =~ s/^.*=//i; 0; }, @tmp_list);
		&do_uniq(@tmp_list);
		if ($#tmp_list > 0) {
			&ADF_DoUsage(-1, $program_name, $program_type,
				"Multiple \'-DEFAULT_SECTION=\' parameters encountered.");
		}
		elsif ($tmp_list[0] =~ /\W/) {
			&ADF_DoUsage(-1, $program_name, $program_type,
				"Invalid \'-DEFAULT_SECTION=\' parameter encountered --- ".
				"the section name contains non-alphanumeric characters ".
				"(\'$tmp_list[0]\').");
		}
		elsif (index("123456789lnop", substr($tmp_list[0], 0, 1)) == -1) {
			&ADF_DoUsage(-1, $program_name, $program_type,
				"Invalid \'-DEFAULT_SECTION=\' parameter encountered --- ".
				"the section name has a first character (\'".
				substr($man_section, 0, 1)."\') which is not one of ".
				"\'1\', \'2\', \'3\', \'4\', \'5\', \'6\', \'7\', ".
				"\'8\', \'9\', \'l\', \'n\', \'o\', or \'p\' ".
				"(\'$tmp_list[0]\').");
		}
		$ADF_DefaultSection =  $tmp_list[0];
		$ADF_DefaultSection =~ s/\s+//g;
	}

	if (grep(/^\-ERRORS?_?ON_?NO_?COMMENTS?$/i, @ARGV)) {
		@ARGV = grep(!/^\-ERRORS?_?ON_?NO_?COMMENTS?$/i, @ARGV);
		$ADF_ErrorOnNoComment = "YES";
	}

	if (@tmp_list = grep(/^\-FORCED?_?AUTHORS?=/i, @ARGV)) {
		if (grep(/^\-FORCED?_?AUTHORS?=$/i, @ARGV)) {
			&ADF_DoUsage(-1, $program_name, $program_type, "Invalid \'".
				(grep(/^\-FORCED?_?AUTHORS?=$/i, @ARGV))[0]."\' parameter.");
		}
		@ARGV = grep(!/^\-FORCED?_?AUTHORS?=/i, @ARGV);
		grep(
			do {
				$_ =~ s/^.*=//;
				$_ =~ s/^\"+|^\'+|^\`+|\"+$|\'+$|\`+$//g;
				$_ =~ s/^\s+|\s+$//g;
				$_ =~ s/\s+/ /g;
				0;
			}, @tmp_list);
		&do_uniq(@tmp_list);
		if ($#tmp_list > 0) {
			&ADF_DoUsage(-1, $program_name, $program_type,
				"Multiple \'-FORCED_AUTHOR=\' parameters encountered.");
		}
		$ADF_ForcedAuthor = $tmp_list[0];
	}

	if (@tmp_list = grep(/^\-FORCED?_?COPYRIGHTS?=/i, @ARGV)) {
		if (grep(/^\-FORCED?_?COPYRIGHTS?=$/i, @ARGV)) {
			&ADF_DoUsage(-1, $program_name, $program_type, "Invalid \'".
				(grep(/^\-FORCED?_?COPYRIGHTS?=$/i, @ARGV))[0]."\' parameter.");
		}
		@ARGV = grep(!/^\-FORCED?_?COPYRIGHTS?=/i, @ARGV);
		grep(
			do {
				$_ =~ s/^.*=//;
				$_ =~ s/^\"+|^\'+|^\`+|\"+$|\'+$|\`+$//g;
				$_ =~ s/^\s+|\s+$//g;
				$_ =~ s/\s+/ /g;
				0;
			}, @tmp_list);
		&do_uniq(@tmp_list);
		if ($#tmp_list > 0) {
			&ADF_DoUsage(-1, $program_name, $program_type,
				"Multiple \'-FORCED_COPYRIGHT=\' parameters encountered.");
		}
		$ADF_ForcedCopyright = $tmp_list[0];
	}

	if (@tmp_list = grep(/^\-FORCED?_?SECTIONS?=/i, @ARGV)) {
		if (grep(/^\-FORCED?_?SECTIONS?=$/i, @ARGV)) {
			&ADF_DoUsage(-1, $program_name, $program_type, "Invalid \'".
				(grep(/^\-FORCED?_?SECTIONS?=$/i, @ARGV))[0]."\' parameter.");
		}
		@ARGV = grep(!/^\-FORCED?_?SECTIONS?=/i, @ARGV);
		grep(do { $_ =~ s/^.*=//; 0; }, @tmp_list);
		&do_uniq(@tmp_list);
		if ($#tmp_list > 0) {
			&ADF_DoUsage(-1, $program_name, $program_type,
				"Multiple \'-FORCED_SECTION=\' parameters encountered.");
		}
		elsif ($tmp_list[0] =~ /\W/) {
			&ADF_DoUsage(-1, $program_name, $program_type,
				"Invalid \'-FORCED_SECTION=\' parameter encountered --- ".
				"the section name contains non-alphanumeric characters ".
				"(\'$tmp_list[0]\').");
		}
		elsif (index("123456789lnop", substr($tmp_list[0], 0, 1)) == -1) {
			&ADF_DoUsage(-1, $program_name, $program_type,
				"Invalid \'-FORCED_SECTION=\' parameter encountered --- ".
				"the section name has a first character (\'".
				substr($man_section, 0, 1)."\') which is not one of ".
				"\'1\', \'2\', \'3\', \'4\', \'5\', \'6\', \'7\', ".
				"\'8\', \'9\', \'l\', \'n\', \'o\', or \'p\' ".
				"(\'$tmp_list[0]\').");
		}
		$ADF_ForcedSection =  $tmp_list[0];
		$ADF_ForcedSection =~ s/\s+//g;
	}

	if (@tmp_list = grep(/^\-PERL_?CODES?=/i, @ARGV)) {
		if (grep(/^\-PERL_?CODES?=$/i, @ARGV)) {
			&ADF_DoUsage(-1, $program_name, $program_type, "Invalid \'".
				(grep(/^\-PERL_?CODES?=$/i, @ARGV))[0]."\' parameter.");
		}
		@ARGV = grep(!/^\-PERL_?CODES?=/i, @ARGV);
		grep(do { $_ =~ s/^.*=//; 0; }, @tmp_list);
		&do_uniq(@tmp_list);
		@ADF_PerlCodeList = @tmp_list;
	}

	if (grep(/^\-PREP_?SORTS?$|^\-PREP_?SORTING$/i, @ARGV)) {
		@ARGV = grep(!/^\-PREP_?SORTS?$|^\-PREP_?SORTING$/i, @ARGV);
		$ADF_PrepSortFlag = "YES";
	}

	if (grep(/^\-NO_REQUIRED_SECTIONS?$/i, @ARGV)) {
		@ARGV = grep(!/^\-NO_REQUIRED_SECTIONS?$/i, @ARGV);
		$ADF_NoRequiredSectionsFlag = "YES";
	}

	if (@tmp_list = grep(/^\-TABS?_?SETS?=|^\-TABS?_?SETTINGS?=/i, @ARGV)) {
		if (grep(/^\-TABS?_?SETS?=$|^\-TABS?_?SETTINGS?=$/i, @ARGV)) {
			&ADF_DoUsage(-1, $program_name, $program_type, "Invalid \'".
				(grep(/^\-TAB_?SETS?=$|^\-TAB_?SETTINGS?=$/i, @ARGV))[0].
				"\' parameter.");
		}
		@ARGV = grep(!/^\-TABS?_?SETS?=|^\-TABS?_?SETTINGS?=/i, @ARGV);
		grep(do { $_ =~ s/^.*=//; 0; }, @tmp_list);
		&do_uniq(@tmp_list);
		if ($#tmp_list > 0) {
			&ADF_DoUsage(-1, $program_name, $program_type,
				"Multiple \'-TAB_SETTING=\' parameters encountered.");
		}
		elsif (($tmp_list[0] !~ /^\d+$/) ||
			($tmp_list[0] < 1) || ($tmp_list[0] > 8)) {
			&ADF_DoUsage(-1, $program_name, $program_type,
				"The \'-TAB_SETTING=\' value must be between 1 and 8, inclusive.");
		}
		$ADF_TabSetting = $tmp_list[0];
	}
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_GetGETArgs {
	local($program_name, $program_type) = @_;
	local(@tmp_list_1, @tmp_list_2, $this_type);

	if (grep(/^\-SORT_?GET?_?DATAS?$/i, @ARGV)) {
		@ARGV = grep(!/^\-SORT_?GET?_?DATAS?$/i, @ARGV);
		$ADF_SortGetDataFlag = "YES";
	}

	if (@tmp_list_1 = grep(/^\-GET_?DATA_?NAMES?=/i, @ARGV)) {
		if (grep(/^\-GET_?DATA_?NAMES?=$/i, @ARGV)) {
			&ADF_DoUsage(-1, $program_name, $program_type, "Invalid \'".
				(grep(/^\-GET_?DATA_?NAMES?=$/i, @ARGV))[0]."\' parameter.");
		}
		@ARGV = grep(!/^\-GET_?DATA_NAMES?=/i, @ARGV);
		grep(do { $_ =~ s/^\-GET_?DATA_?NAMES?=//i; 0; }, @tmp_list_1);
		grep(do { push(@tmp_list_2, split(/,|\s+/, $_)); 0; }, @tmp_list_1);
		grep(do { $_ =~ s/^\s+|\s+$//g; 0; }, @tmp_list_2);
		@tmp_list_2 = grep(!/^\s*$/, @tmp_list_2);
		foreach $this_type (@tmp_list_2) {
			$this_type =~ s/^BASE_?NAMES?$|^NAMES?$/NAME/i;
			$this_type =~ s/^TYPES?$/TYPE/i;
			$this_type =~ s/^FILE_?NAMES?$/FILE_NAME/i;
			$this_type =~ s/^FULL_?FILE_?NAMES?$/FULL_FILE_NAME/i;
			push (@ADF_GetDataNameList, $this_type);
			if ($this_type =~ /^BASE_?NAMES?$|^NAMES?$/i) {
				push (@ADF_GetDataIndexList, $ADF_LD_BASE_NAME); }
			elsif ($this_type =~ /^TYPES?$/i) {
				push (@ADF_GetDataIndexList, $ADF_LD_TYPE); }
			elsif ($this_type =~ /^FILE_?NAMES?$/i) {
				push (@ADF_GetDataIndexList, $ADF_LD_FILE_NAME); }
			elsif ($this_type =~ /^FULL_?FILE_?NAMES?$/i) {
				push (@ADF_GetDataIndexList, $ADF_LD_FULL_FILE_NAME); }
			else {
				&ADF_DoUsage(-1, $program_name, $program_type,
					"Invalid \'-GET_DATA_NAME=\' parameter encountered --- ".
					"component named \'$this_type\' should be one of ".
					"\'NAME\', \'TYPE\', \'FILE_NAME\', or \'FULL_FILE_NAME\'.");
			}
		}
	}

	if (@tmp_list_1 = grep(/^\-GET_?DATAS?_?SEPARATORS?=/i, @ARGV)) {
		if (grep(/^\-GET_?DATAS?_?SEPARATORS?=$/i, @ARGV)) {
			&ADF_DoUsage(-1, $program_name, $program_type, "Invalid \'".
				(grep(/^\-GET_?DATAS?_?SEPARATORS?=$/i, @ARGV))[0].
				"\' parameter.");
		}
		@ARGV = grep(!/^\-GET_?DATAS?_?SEPARATORS?=/i, @ARGV);
		grep(do { $_ =~ s/^\-GET_?DATAS?_?SEPARATORS?=$//i; 0; }, @tmp_list_1);
		&do_uniq(@tmp_list_1);
		if ($#tmp_list > 0) {
			&ADF_DoUsage(-1, $program_name, $program_type,
				"Multiple \'-GET_DATA_SEPARATOR=\' parameters encountered.");
		}
		$ADF_GetDataSeparator = $tmp_list[0];
	}
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_GetCHKArgs {
	local($program_name, $program_type) = @_;

	if (grep(/^\-IGNORE_?BAD_?XREFS?$/i, @ARGV)) {
		@ARGV = grep(!/^\-IGNORE_BAD_XREFS?$/i, @ARGV);
		$ADF_IgnoreBadXRefsFlag = "YES";
	}
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_GetCOMBArgs {
	local($program_name, $program_type) = @_;

	if (grep(/^\-SORT_?COMBINED?_?FILES?$/i, @ARGV)) {
		@ARGV = grep(!/^\-SORT_?COMBINED?_?FILES?$/i, @ARGV);
		$ADF_SortCombinedFiles = "YES";
	}

	if (grep(/^\-REMOVE_?BAD_?XREFS?$/i, @ARGV)) {
		@ARGV = grep(!/^\-REMOVE_?BAD_?XREFS?$/i, @ARGV);
		$ADF_RemoveBadXRefsFlag = "YES";
	}

	if (grep(/^\-ZERO_?DATES?$/i, @ARGV)) {
		@ARGV = grep(!/^\-ZERO_?DATES?$/i, @ARGV);
		$ADF_ZeroDataFlag = "YES";
	}
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_GetOUTArgs {
	local($program_name, $program_type) = @_;
	local($tmp_string, @tmp_list);

	if (@tmp_list = grep(/^\-EXTERN_?REFS?=|^\-EXTERNAL_?REFS?=/i, @ARGV)) {
		if (grep(/^\-EXTERN_?REFS?=$|^\-EXTERNAL_?REFS?=$/i, @ARGV)) {
			&ADF_DoUsage(-1, $program_name, $program_type, "Invalid \'".
				(grep(/^\-EXTERN_?REFS?=$|^\-EXTERNAL_?REFS?=$/i, @ARGV))[0].
				"\' parameter.");
		}
		@ARGV = grep(!/^\-EXTERN_?REFS?=|^\-EXTERNAL_?REFS?=/i, @ARGV);
		grep(do { $_ =~ s/^\-EXTERN_?REFS?=|^\-EXTERNAL_?REFS?=//i; 0; },
			@tmp_list);
		foreach $tmp_string (@tmp_list) {
			$tmp_string                           =~ s/^(.*)=(.*)$/\1/;
			$ADF_ExternalRefFileList{$tmp_string} =  $2;
			$ADF_ExternalRefFileList{$tmp_string} =~ s/\\/\\\\/g;
			$ADF_ExternalRefFileList{$tmp_string} =~ s/(\<|\>|\'|\`)/\\\1/g;
			$ADF_ExternalRefFileList{$tmp_string} =~ s/^\.\//\\\<c\\\>/;
			$ADF_ExternalRefFileList{$tmp_string} =~ s/^\//\\\<r\\\>\\\<c\\\>/;
			$ADF_ExternalRefFileList{$tmp_string} =~ s/\//\\\<c\\\>/g;
		}
	}

	if (@tmp_list = grep(/^\-FRAME_?FMHOME=|^\-FRAME_?MAKER_?FMHOME=/i, @ARGV)) {
		if (grep(/^\-FRAME_?FMHOME=$|^\-FRAME_?MAKER_?FMHOME=$/i, @ARGV)) {
			&ADF_DoUsage(-1, $program_name, $program_type, "Invalid \'".
				(grep(/^\-FRAME_?FMHOME=$|^\-FRAME_?MAKER_?FMHOME=$/i,
				@ARGV))[0]."\' parameter.");
		}
		@ARGV = grep(!/^\-FRAME_?FMHOME=|^\-FRAME_?MAKER_?FMHOME=/i, ARGV);
		grep(do { $_ =~ s/^.*=//; 0; }, @tmp_list);
		&do_uniq(@tmp_list);
		if ($#tmp_list > 0) {
			&ADF_DoUsage(-1, $program_name, $program_type,
				 "Multiple \'-FRAME_MAKER_FMHOME=\' parameters encountered.");
		}
		$ADF_FrameFMHOME  =  $tmp_list[0];
		$ADF_FrameFMHOME  =~ s/\/+/\//g;
		$ADF_FrameFMHOME  =~ s/^(\S+)\/$/\1/;
		$ADF_FrameFMHOME .= "/";
	}

	if (grep(/^\-FRAME_?HYPER_?TEXT$/i, @ARGV)) {
		@ARGV = grep(!/^\-FRAME_?HYPER_?TEXT$/i, @ARGV);
		$ADF_FrameHyperText = "YES";
	}
	
	if (grep(/^\-LIST_?FRAME_?XREFS?$|^\-LIST_?FRAME_?MAKER_?XREFS?$/i,
		@ARGV)) {
		@ARGV = grep(!/^\-LIST_?FRAME_?XREFS?$|^\-LIST_?FRAME_?MAKER_?XREFS?$/i,
			@ARGV);
		$ADF_ListFrameXRefs = "YES";
	}
	
	if (@tmp_list = grep(/^\-MAN_?DIR=|^\-MAN_?DIRECTORY=/i, @ARGV)) {
		if (grep(/^\-MAN_?DIR=$|^\-MAN_?DIRECTORY=$/i, @ARGV)) {
			&ADF_DoUsage(-1, $program_name, $program_type, "Invalid \'".
				(grep(/^\-MAN_DIRECTORY=$/i, @ARGV))[0]."\' parameter.");
		}
		@ARGV = grep(!/^\-MAN_?DIR=$|^\-MAN_?DIRECTORY=/i, ARGV);
		grep(do { $_ =~ s/^.*=//; 0; }, @tmp_list);
		&do_uniq(@tmp_list);
		if ($#tmp_list > 0) {
			&ADF_DoUsage(-1, $program_name, $program_type,
				"Multiple \'-MAN_DIRECTORY=\' parameters encountered.");
		}
		$ADF_ManDirectory  =  $tmp_list[0];
		$ADF_ManDirectory  =~ s/\/+/\//g;
		$ADF_ManDirectory  =~ s/^(\S+)\/$/\1/;
		$ADF_ManDirectory .= "/";
	}

	if (grep(/^\-FORMAT_?SORTS?$|^\-FORMAT_?SORTING$/i, @ARGV)) {
		@ARGV = grep(!/^\-FORMAT_?SORTS?$|^\-FORMAT_?SORTING$/i, @ARGV);
		$ADF_FormatSortFlag = "YES";
	}

	if (@tmp_list = grep(/^\-OUTPUT=/i, @ARGV)) {
		if (grep(/^\-OUTPUT=$/i, @ARGV)) {
			&ADF_DoUsage(-1, $program_name, $program_type, "Invalid \'".
				(grep(/^\-OUTPUT=$/i, @ARGV))[0]."\' parameter.");
		}
		@ARGV = grep(!/^\-OUTPUT=/i, @ARGV);
		grep(do { $_ =~ s/^.*=//; }, @tmp_list);
		grep(do { $_ =~ s/^MAN$|^MAN_?PAGES?$/MAN_PAGES/i; 0; }, @tmp_list);
		grep(do { $_ =~ s/^FRAME$|^FRAME_?MAKER$/FRAME_MAKER/i; 0; }, @tmp_list);
		$tmp_string =  join("\177", @tmp_list);
		$tmp_string =~ tr/[a-z]/[A-Z]/;
		@tmp_list   =  split(/\177/, $tmp_string);
		&do_uniq(@tmp_list);
		if ($#tmp_list > 0) {
			&ADF_DoUsage(-1, $program_name, $program_type,
				"Multiple \'-OUTPUT=\' parameters encountered.");
		}
		elsif (($tmp_list[0] ne "ASCII") && ($tmp_list[0] ne "MAN_PAGES") &&
			($tmp_list[0] ne "FRAME_MAKER")) {
			&ADF_DoUsage(-1, $program_name, $program_type,
				"Invalid \'OUTPUT=\' parameter encountered --- should be one of ".
				"\'ASCII\', \'MAN_PAGES\' or \'FRAME_MAKER\'.");
		}
		$ADF_OutputTypeFlag = $tmp_list[0];
	}

	if (($ADF_OutputTypeFlag ne "FRAME_MAKER") &&
		($ADF_FrameHyperText eq "YES")) {
		&ADF_DoUsage(-1, $program_name, $program_type,
			"A \'-FRAME_HYPER_TEXT\' parameter was encountered, but the ",
			"\'OUTPUT=\' parameter does not specify Frame Maker.");
	}

	if (grep(/^\-KEEP_?BAD_?XREFS?$/i, @ARGV)) {
		@ARGV = grep(!/^\-REMOVE_?BAD_?XREFS?$/i, @ARGV);
		$ADF_KeepBadXRefsFlag = "YES";
	}
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_GetOtherArgs {
	local($program_name, $program_type) = @_;
	local($tmp_string, @tmp_list, $file_name, @in_list);

	if (grep(/^\-XREF_?TREES?$/i, @ARGV)) {
		@ARGV = grep(!/^\-XREF_?TREES?$/i, @ARGV);
		$ADF_XRefTreeFlag = "YES";
	}

	if (grep(/^\-FIRST_?DUPLICATE_?NAMES?$/i, @ARGV)) {
		@ARGV = grep(!/^\-FIRST_?DUPLICATE_?NAMES?$/i, @ARGV);
		$ADF_FirstDuplicateName = "YES";
	}

	if (grep(/^\-LAST_?DUPLICATE_?NAMES?$/i, @ARGV)) {
		@ARGV = grep(!/^\-LAST_?DUPLICATE_?NAMES?$/i, @ARGV);
		if ($ADF_FirstDuplicateName eq "YES") {
			&ADF_DoUsage(-1, $program_name, $program_type, "Conflicting ".
				"parameters \'-FIRST_DUPLICATE_NAME\' and ".
				"\'-LAST_DUPLICATE_NAME\' encountered.");
		}
		$ADF_LastDuplicateName = "YES";
	}

	foreach $this_order ("Include", "Exclude") {
		foreach $this_type ("File", "Name", "Type") {
			$tmp_string =  "^\\-".$this_order."_?".$this_type."S?=";
			$tmp_string =~ y/[a-z]/[A-Z]/;
			if (@tmp_list = grep(/$tmp_string/i, @ARGV)) {
				if (grep(/$tmp_string$/i, @ARGV)) {
					&ADF_DoUsage(-1, $program_name, $program_type, "Invalid \'".
						(grep(/$tmp_string$/i, @ARGV))[0].
						"\' parameter.");
				}
				@ARGV = grep(!/$tmp_string/i, @ARGV);
				foreach $tmp_string (@tmp_list) {
					$tmp_string =~ s/^(.*)=(.*)$/\1/;
					$file_name  =  $2;
					if (!open(CLUSION_FH, "<$file_name")) {
						&ADF_DoUsage(-1, $program_name, $program_type,
							"Unable to open \'$tmp_string\' parameter input file ".
							"\'$file_name\' for reading.");
					}
					@in_list = <CLUSION_FH>;
					close(CLUSION_FH);
					chop(@in_list);
					@in_list = grep(!/^\s*$|^\s*#/, @in_list);
					grep(do {
						$_ =~ s/^\s+|\s+$//g;
						$_ =~ s/\s+/ /g;
						eval "\$ADF_$this_order$this_type"."Array{\"$_\"} = \"\";";
						0;
					}, @in_list);
				}
				eval "\$ADF_$this_order$this_type"."Flag = \"YES\";";
			}
		}
	}
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_ShowArgs {
	local($in_file_count, $program_type) = @_;
	local(@arg_list);

	if ($program_type =~ /PREP|ALL/) {
		push(@arg_list, "CHECK ONLY              : $ADF_CheckCommentFlag");
		push(@arg_list, "DEFAULT AUTHOR          : $ADF_DefaultAuthor");
		push(@arg_list, "DEFAULT COPYRIGHT       : $ADF_DefaultCopyright");
		push(@arg_list, "DEFAULT SECTION         : $ADF_DefaultSection");
		push(@arg_list, "ERRORS ON NO COMMENTS   : $ADF_ErrorOnNoComment");
		push(@arg_list, "FORCED AUTHOR           : $ADF_ForcedAuthor");
		push(@arg_list, "FORCED COPYRIGHT        : $ADF_ForcedCopyright");
		push(@arg_list, "FORCED SECTION          : $ADF_ForcedSection");
		push(@arg_list, "PERL CODE LIST          : ".
			join("\n                        : ", @ADF_PerlCodeList));
		push(@arg_list, "PREP SORTING            : $ADF_PrepSortFlag");
		push(@arg_list, "NO REQUIRED SECTIONS    : $ADF_NoRequiredSectionsFlag");
		push(@arg_list, "TAB SETTING             : $ADF_TabSetting");
		push(@arg_list, "ZERO DATABASE DATE/TIME : $ADF_ZeroDataFlag");
	}

	if ($program_type =~ /GET/) {
		push(@arg_list, "SORT GET DATA           : $ADF_SortGetDataFlag");
		push(@arg_list, "GET DATA SEPARATOR      : $ADF_GetDataSeparator");
		push(@arg_list, "GET DATA NAMES          : ".
			($#ADF_GetDataNameList == -1) ? "NAME" :
			join("\n                        : ", @ADF_GetDataNameList));
	}

	if ($program_type =~ /CHK|ALL/) {
		push(@arg_list, "IGNORE BAD XREFS        : $ADF_IgnoreBadXRefsFlag");
	}

	if ($program_type =~ /COMB|ALL/) {
		push(@arg_list, "REMOVE BAD XREFS        : $ADF_RemoveBadXRefsFlag");
		push(@arg_list, "SORT COMBINED FILES     : $ADF_SortCombinedFiles");
		push(@arg_list, "ZERO DATABASE DATE/TIME : $ADF_ZeroDataFlag");
	}

	if ($program_type =~ /OUT|ALL/) {
		push(@arg_list, "EXTERNAL REFERENCE FILES: ".
			join("\n                        : ",
			sort(keys(%ADF_ExternalRefFileList))));
		push(@arg_list, "FRAME MAKER FMHOME      : $ADF_FrameFMHOME");
		push(@arg_list, "FRAME MAKER HYPERTEXT   : $ADF_FrameHyperText");
		push(@arg_list, "KEEP BAD XREFS          : $ADF_KeepBadXRefsFlag");
		push(@arg_list, "LIST FRAME MAKER XREFS  : $ADF_ListFrameXRefs");
		push(@arg_list, "MAN DIRECTORY           : $ADF_ManDirectory");
		push(@arg_list, "FORMAT SORTING          : $ADF_FormatSortFlag");
		push(@arg_list, "OUTPUT                  : $ADF_OutputTypeFlag");
	}

	push(@arg_list, "CREATE X-REFERENCE TREE : $ADF_XRefTreeFlag");
	push(@arg_list, "USE FIRST DUPLICATE NAME: $ADF_FirstDuplicateName");
	push(@arg_list, "USE LAST DUPLICATE NAME : $ADF_LastDuplicateName");
	push(@arg_list, "INCLUDE FILES LIST      : $ADF_IncludeFileFlag");
	push(@arg_list, "INCLUDE NAMES LIST      : $ADF_IncludeNameFlag");
	push(@arg_list, "INCLUDE TYPES LIST      : $ADF_IncludeTypeFlag");
	push(@arg_list, "EXCLUDE FILES LIST      : $ADF_ExcludeFileFlag");
	push(@arg_list, "EXCLUDE NAMES LIST      : $ADF_ExcludeNameFlag");
	push(@arg_list, "EXCLUDE TYPES LIST      : $ADF_ExcludeTypeFlag");

#print STDERR join("\n", @arg_list), "\n\n";
	@arg_list = sort(@arg_list);

	push(@arg_list, "Number of input files   : $in_file_count");

	print STDERR join("\n", @arg_list), "\n\n";
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_DescribeDomains {
	local($domain_name, $tmp_string, @tmp_array, $count_1, $this_order);

	print "=" x 78; print "\n";

	foreach $domain_name (sort(keys(%ADF_RegisteredParseDomains))) {
		&ADF_SetFileTypeData($domain_name);
		$tmp_string =  "ADF Parse Domain \'$domain_name\'";
		print $tmp_string, "\n";
		$tmp_string =~ s/\S/-/g;
		print $tmp_string, "\n";
		@tmp_array = ();
		grep(do {
			if ($FileTypeList{$_} eq $domain_name) {
				push(@tmp_array, $_);
			}
			0;
		}, keys(%FileTypeList));
		print "   Domain file extension(s)                    : .",
			join(", .", sort(@tmp_array)), "\n";
		print "   Beginning of the ADF comment section pattern: ",
			$BOH_Pattern, "\n";
		print "   Ending of the ADF comment section pattern   : ",
			$EOH_Pattern, "\n";
		print "   ADF empty line pattern                      : ",
			$EmptyLinePattern, "\n";
		print "   Beginning of line strip pattern             : ",
			$BOL_StripPattern, "\n";
		print "   Ending of line strip pattern                : ",
			$EOL_StripPattern, "\n";
		print "   Parse domain component count                : ",
			$#DataOrderList + 1, "\n";
		print "   "; print "-" x 75; print "\n";
		$count_1 = 0;
		foreach $this_order (@DataOrderList) {
			$tmp_string = sprintf("%05u", $count_1++);
			print "   Component $tmp_string name                 : ",
				$DataNameList[$this_order], "\n";
			print "   Component $tmp_string type                 : ",
				$DataFlagList[$this_order], " (index = $this_order)\n";
			print "   Component $tmp_string required flag        : ",
				$DataRequiredList[$this_order], "\n";
			print "   Component $tmp_string word-wrapping flag   : ",
				$DataWrapList[$this_order], "\n";
			print "   Component $tmp_string left space trim flag : ",
				$DataLTrimList[$this_order], "\n";
			print "   Component $tmp_string right space trim flag: ",
				$DataRTrimList[$this_order], "\n";
			print "   Component $tmp_string space squeeze flag   : ",
				$DataSqueezeList[$this_order], "\n";
			print "   Component $tmp_string paragraph format flag: ",
				$DataParaFormatList[$this_order], "\n";
			print "   Component $tmp_string character format flag: ",
				$DataCharFormatList[$this_order], "\n";
			print "   Component $tmp_string match patterns       : ",
				join("\n                                        : ",
				split(/\|/, $DataPatternList[$this_order])), "\n";
			print "   "; print "-" x 75; print "\n";
		}
		print "=" x 78; print "\n\f";
	}
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_DoOperation {
	local($all_error_text, $program_type, @in_arg_list) = @_;

	if ($program_type eq "PREP") {
		$return_code = &ADF_DoPREPOperation($all_error_text, @in_arg_list);
	}
	elsif ($program_type eq "GET") {
		$return_code = &ADF_DoGETOperation($all_error_text, @in_arg_list);
	}
	elsif ($program_type eq "CHK") {
		$return_code = &ADF_DoCHKOperation($all_error_text, @in_arg_list);
	}
	elsif ($program_type eq "COMB") {
		$return_code = &ADF_DoCOMBOperation($all_error_text, @in_arg_list);
	}
	elsif ($program_type eq "OUT") {
		$return_code = &ADF_DoOUTOperation($all_error_text, @in_arg_list);
	}
	else {
		if (!open(TMP_FRAME_FILE_000, ">$ADF_TempFileBase.000")) {
			$all_error_text = "Unable to open output file ".
				"\'$ADF_TempFileBase.000\'.";
			$return_code    = -1;
		}
		else {
			if ($return_code = &ADF_ParseInputFile("TMP_FRAME_FILE_000",
				$all_error_text, @in_arg_list)) {
				close(TMP_FRAME_FILE_000);
			}
			else {
				close(TMP_FRAME_FILE_000);
				if (!($return_code = &ADF_DoCHKOperation($all_error_text,
					"$ADF_TempFileBase.000"))) {
					$return_code = &ADF_DoOUTOperation($all_error_text,
						"$ADF_TempFileBase.000");
				}
			}
			unlink("$ADF_TempFileBase.000");
		}
	}

	$_[0] = $all_error_text;

	return($return_code);
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_DoPREPOperation {
	local($prep_error_text, @in_arg_list) = @_;
	local($return_code, $prep_error_text);

	$return_code = &ADF_ParseInputFile("STDOUT", $prep_error_text,
		@in_arg_list);
	$_[0]       = $prep_error_text;

	return($return_code);
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_DoGETOperation {
	local($get_error_text, @in_arg_list) = @_;
	local($return_code, @adf_fh_list, %hyper_name_array, %item_name_array,
		@item_name_list, @tmp_index_list, $this_item, @tmp_list, $tmp_string,
		@out_list, $count_1, $tmp_string);

	$return_code = 0;
	@adf_fh_list = ();

	if (!($return_code = &ADF_MultipleLoadDatabase($get_error_text,
		"item_name_list", "item_name_array", "hyper_name_array", "adf_fh_list",
		@in_arg_list))) {
		@tmp_index_list = ($#ADF_GetDataIndexList == -1) ? ($ADF_LD_BASE_NAME) :
			@ADF_GetDataIndexList;
		%hyper_name_array = ();
		grep(do { close($_); 0; }, @adf_fh_list);
		foreach $this_item (@item_name_list) {
			@tmp_list   = split(/\177/, $item_name_array{$this_item});
			$tmp_string = "";
			for ($count_1 = 0; $count_1 <= $#tmp_index_list; $count_1++) {
				$tmp_string .= ($count_1) ? $ADF_GetDataSeparator : "";
				$tmp_string .= $tmp_list[$tmp_index_list[$count_1]];
			}
			push(@out_list, $tmp_string);
		}
		if ($ADF_SortGetDataFlag eq "YES") {
			@out_list = sort(@out_list);
		}
		print join("\n", @out_list), "\n";
	}

	$_[0] = $get_error_text;

	return($return_code);
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_DoCHKOperation {
	local($chk_error_text, @in_arg_list) = @_;
	local($return_code, @adf_fh_list,
		%hyper_name_array,
		%item_name_array, @item_name_list, @tmp_list, $tmp_string,
		$order_string, $component_string, %item_xref_array,
		@tmp_xref_list, $this_xref, $this_unres, $unres_name, $unres_file);

	if (!($return_code = &ADF_MultipleLoadDatabase($chk_error_text,
		"item_name_list", "item_name_array", "hyper_name_array", "adf_fh_list",
		@in_arg_list))) {
		@item_name_list = sort(@item_name_list);
		foreach $this_item (@item_name_list) {
			@tmp_list = split(/\177/, $item_name_array{$this_item});
			seek($adf_fh_list[$tmp_list[$ADF_LD_FILE_INDEX]],
				$tmp_list[$ADF_LD_OFFSET], 0);
			sysread($adf_fh_list[$tmp_list[$ADF_LD_FILE_INDEX]],
				$tmp_string, $tmp_list[$ADF_LD_LENGTH], 0);
			($order_string, $component_string, @tmp_list) =
				split(/\177/, $tmp_string);
			if ($tmp_list[$FLAG_SEE_ALSO] !~ /^\s*$/) {
				@tmp_xref_list = split(/\n/, $tmp_list[$FLAG_SEE_ALSO]);
				foreach $this_xref (@tmp_xref_list) {
					if (defined($item_xref_array{$this_xref})) {
						$item_xref_array{$this_xref} .= "\177";
					}
					$item_xref_array{$this_xref} .=
						$tmp_list[$FLAG_BASE_NAME]."\176".
						$tmp_list[$FLAG_SOURCE_FILE_NAME];
				}
			}
		}
		for $this_xref (@item_name_list) {
			delete $item_xref_array{$this_xref};
		}
		@tmp_xrefs = sort(keys(%item_xref_array));
		if ($#tmp_xrefs > -1) {
			$chk_error_text = sprintf("%u unresolved cross-reference%s %s ".
				"encountered.", $#tmp_xrefs + 1,
				(!$#tmp_xrefs) ? "" : "s", (!$#tmp_xrefs) ? "was" : "were");
			$return_code    = -1;
			print STDERR "UNRESOLVED CROSS-REFERENCES ENCOUNTERED\n";
			for $this_xref (@tmp_xrefs) {
				print STDERR "   Cross-reference to \'$this_xref\' in:\n";
				for $this_unres (split(/\177/, $item_xref_array{$this_xref})) {
					($unres_name, $unres_file) = split(/\176/, $this_unres);
					print STDERR "      \'$unres_name\' in file \'$unres_file\'\n";
				}
			}
		}
		grep(do { close($_); 0; }, @adf_fh_list);
	}

	$_[0] = $chk_error_text;

	return($return_code);
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_DoCOMBOperation {
	local($comb_error_text, @in_arg_list) = @_;
	local($return_code, @adf_fh_list, %hyper_name_array, %item_name_array,
		@item_name_list, @tmp_list, $tmp_string, $current_offset, @data_list,
		$dir_string, %comb_hyper_array, @comb_name_list, @comb_dir_list);

	$return_code = 0;
	@adf_fh_list = ();

	if (!($return_code = &ADF_MultipleLoadDatabase($comb_error_text,
		"item_name_list", "item_name_array", "hyper_name_array", "adf_fh_list",
		@in_arg_list))) {
		%hyper_name_array = ();
		if ($ADF_SortCombinedFiles eq "YES") {
			@item_name_list = sort(@item_name_list);
		}
		$current_offset = &ADF_WriteDBHeader("STDOUT");
		foreach $this_item (@item_name_list) {
			print STDERR "COMB:", $this_item;
			@tmp_list = split(/\177/, $item_name_array{$this_item});
			seek($adf_fh_list[$tmp_list[$ADF_LD_FILE_INDEX]],
				$tmp_list[$ADF_LD_OFFSET], 0);
			sysread($adf_fh_list[$tmp_list[$ADF_LD_FILE_INDEX]],
				$tmp_string, $tmp_list[$ADF_LD_LENGTH], 0);
			($order_string, $component_string, @data_list) =
				split(/\177/, $tmp_string);
			&ADF_WriteDBData("STDOUT", $tmp_list[$ADF_LD_FULL_FILE_NAME],
				$tmp_list[$ADF_LD_FILE_NAME], $current_offset, $order_string,
				$component_string, $dir_string, @data_list);
			if ($data_list[$FLAG_PUBLISH_NAME] ne "") {
				$comb_hyper_array{$data_list[$FLAG_BASE_NAME]} =
					$data_list[$FLAG_PUBLISH_NAME];
			}
			push(@comb_name_list,  $data_list[$FLAG_BASE_NAME]."\177".
				join("\177", split(/\n/, $data_list[$FLAG_PUBLISH_NAME])));
			push(@comb_dir_list, $dir_string);
			print STDERR " .\n";
		}
		&ADF_WriteDBTrailer("STDOUT", $current_offset, "comb_hyper_array",
			"comb_name_list", "comb_dir_list");
		grep(do { close($_); 0; }, @adf_fh_list);
	}

	$_[0] = $comb_error_text;

	return($return_code);
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_DoOUTOperation {
	local($out_error_text, @in_arg_list) = @_;
	local($return_code, @adf_fh_list, %hyper_name_array, %item_name_array,
		@item_name_list, @hyper_name_list, @tmp_list, @ref_list, $man_item_name,
		$man_name);

	$return_code = 0;
	@adf_fh_list = ();

	if (!($return_code = &ADF_MultipleLoadDatabase($out_error_text,
		"item_name_list", "item_name_array", "hyper_name_array", "adf_fh_list",
		@in_arg_list))) {
		if (($ADF_FrameHyperText ne "YES") && ($ADF_KeepBadXRefsFlag eq "YES")) {
			%hyper_name_array = ();
		}
		if (($ADF_FrameHyperText eq "YES") || ($ADF_KeepBadXRefsFlag ne "YES")) {
			$return_code = &ADF_LoadExternalRefs($out_error_text,
				"hyper_name_array");
		}
		if ($ADF_FormatSortFlag eq "YES") {
			@item_name_list = sort(@item_name_list);
		}
		if ($ADF_OutputTypeFlag eq "FRAME_MAKER") {
			if ($ADF_FrameHyperText eq "YES") {
				@hyper_name_list = reverse(sort(keys(%hyper_name_array)));
				if ($ADF_KeepBadXRefsFlag eq "YES") {
					%hyper_name_array = ();
				}
			}
			&ADF_EmitFrameHeader("STDOUT");
		}
		foreach $this_item (@item_name_list) {
			print STDERR "OUT:", $this_item;
			@tmp_list = split(/\177/, $item_name_array{$this_item});
			if (&ADF_SetFileTypeDataFromFDB($item_name_array{$this_item},
				$adf_fh_list[$tmp_list[$ADF_LD_FILE_INDEX]],
				$tmp_list[$ADF_LD_OFFSET], $tmp_list[$ADF_LD_LENGTH],
					"tmp_list")) {
				next;
			}
			if (($ADF_KeepBadXRefsFlag ne "YES") &&
				($tmp_list[$FLAG_SEE_ALSO] ne /^\s*$/)) {
				@ref_list = split(/\n/, $tmp_list[$FLAG_SEE_ALSO]);
				grep(do {
					if (!defined($hyper_name_array{$_})) {
						$_ = "";
					}
					0;
				}, @ref_list);
				$tmp_list[$FLAG_SEE_ALSO] = join("\n", grep(!/^\s*$/, @ref_list));
			}
			if ($ADF_OutputTypeFlag eq "ASCII") {
				&ADF_EmitOneAscii($this_item, @tmp_list);
				print "\f";
			}
			elsif ($ADF_OutputTypeFlag eq "MAN_PAGES") {
				$man_item_name =  $this_item;
				$man_item_name =~ s/\W/_/g;
				$man_name      =  $ADF_ManDirectory."man/man".
					$tmp_list[$FLAG_MAN_SECTION];
				if ((-e $man_name) && (!(-d $man_name))) {
					print STDERR "\n";
					$out_error_text = "Man page directory \'$man_name\' exists, ".
						"but is not a directory.";
					$return_code    = -1;
					last;
				}
				elsif ((!(-e $man_name)) && (!mkdir($man_name, 0777))) {
					print STDERR "\n";
					$out_error_text = "Unable to create man page directory ".
						"\'$man_name\' ($!).";
					$return_code    = -1;
					last;
				}
				elsif (!open(TMP_MAN_FH, ">".$man_name."/".$man_item_name.".".
					$tmp_list[$FLAG_MAN_SECTION])) {
					print STDERR "\n";
					$out_error_text = "Unable to open the man page file ".
						"\'$man_name/$man_item_name.$tmp_list[$FLAG_MAN_SECTION]\' ".
						"for output.";
					$return_code    = -1;
					last;
				}
				&ADF_EmitOneManPage("TMP_MAN_FH", $this_item, @tmp_list);
				close(TMP_MAN_FH);
			}
			else {				# -OUTPUT=FRAME_MAKER
				if ($ADF_FrameHyperText eq "YES") {
					&ADF_InsertEmbeddedHyperText("tmp_list", "hyper_name_list");
				}
				&ADF_EmitOneFrame("STDOUT", $this_item, "hyper_name_array", @tmp_list);
			}
			print STDERR " .\n";
		}
		grep(do { close($_); 0; }, @adf_fh_list);
	}

	$_[0] = $out_error_text;

	return($return_code);
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_MultipleLoadDatabase {
	local($load_error_text, *all_item_name_list, *all_item_name_array,
		*all_hyper_name_array, *all_adf_fh_list, @in_adf_db_file_list) = @_;
	local($return_code, $adf_file_name, $adf_fh, %name_publish_array,
		@tmp_name_list, @tmp_locate_list, $count_1, $count_2, @tmp_item_name_list,
		$this_file, $other_index, $other_file, @tmp_list, $tmp_string,
		$delete_flag, %used_name_array, %used_publish_array, %full_publish_array,
		$order_string, $component_string, $this_item, $this_publish, $this_name,
		@tmp_publish_list, %full_synonyms);

	$return_code            = 0;
	@all_item_name_list     = ();
	%all_item_name_array    = ();
	%all_hyper_name_array   = ();
	@all_adf_fh_list        = ();
	%used_name_array        = ();
	%used_publish_array     = ();
	%full_publish_array     = ();

	# #####################################################################	#
	# #####################################################################	#
	#    Load the names from each of the specified ADF database files.		#
	# #####################################################################	#
	foreach $adf_file_name (@in_adf_db_file_list) {
		print STDERR "Reading ADF database \'$adf_file_name\' . . .";
		# Create a unique file handle
		$adf_fh = "IN_ADF_DB_".sprintf("%05u", $#all_adf_fh_list + 1);
		if ($return_code = &ADF_LoadDatabaseFile($adf_file_name,
			$adf_fh, "tmp_name_list", "tmp_locate_list", "all_hyper_name_array",
			"name_publish_array", $load_error_text)) {
			last;
		}
		push(@all_adf_fh_list, $adf_fh);
		# ##################################################################	#
		# ##################################################################	#
		#    For each of the names loaded from the ADF database file, check	#
		# to see whether we've already encountered it . . .						#
		# ##################################################################	#
		for ($count_1 = 0; $count_1 <= $#tmp_name_list; $count_1++) {
			if (defined($all_item_name_array{$tmp_name_list[$count_1]})) {
				# ############################################################	#
				# ############################################################	#
				#    If we've been to told to use the first instance of any		#
				# duplicate names, we just ignore subsequent instances . . .	#
				# ############################################################	#
				if ($ADF_FirstDuplicateName eq "YES") {
					next;
				}
				# ############################################################	#
				# ############################################################	#
				#    If we've been told to use the last instance of any			#
				# duplicate names, we delete the previous entry. The new entry	#
				# will be appended below.													#
				# ############################################################	#
				elsif ($ADF_LastDuplicateName eq "YES") {
					for ($count_2 = 0; $count_2 < $#tmp_item_name_list;
						$count_2++) {
						if ($tmp_item_name_list[$count_2] eq
							$tmp_name_list[$count_1]) {
							splice(@tmp_item_name_list, $count_2, 1);
							last;
						}
					}
				}
				# ############################################################	#
				# ############################################################	#
				#    Otherwise, the duplicate name is an error.						#
				# ############################################################	#
				else {
					$this_file       = (split(/\177/,
						$tmp_locate_list[count_1]))[$ADF_DB_FULL_FILE_NAME];
					$other_index     = (split(/\177/,
						$all_item_name_array{$tmp_name_list[$count_1]}))
						[$ADF_LD_FILE_INDEX];
					$other_file      = (split(/\177/,
						$all_item_name_array{$tmp_name_list[$count_1]}))
						[$ADF_LD_FULL_FILE_NAME];
					$load_error_text = "Item \'".$tmp_name_list[$count_1]."\' in ".
						"file \'$this_file' (ADF database \'$adf_file_name\') ".
						"was previously defined in file \'$other_file' ".
						"(ADF database \'$in_adf_db_file_list[$other_index]\').";
					$return_code     = -1;
					last;
				}
				# ############################################################	#
			}
			# ###############################################################	#
			# ###############################################################	#
			#    Add the name to our lists . . .										#
			# ###############################################################	#
			push(@tmp_item_name_list, $tmp_name_list[$count_1]);
			$all_item_name_array{$tmp_name_list[$count_1]} =
				sprintf("%05u", $#all_adf_fh_list)."\177".
				$tmp_locate_list[$count_1];
			# ###############################################################	#
		}
		if ($return_code) {
			last;
		}
		print STDERR "\n";
	}
	if (!$return_code) {
		print STDERR "Fix-up of the ", $#all_adf_fh_list + 1,
			" database", ($#all_adf_fh_list == 0) ? "" : "s", " loaded . . .";
	}
	# #####################################################################	#

	# #####################################################################	#
	# #####################################################################	#
	#    Here we apply any inclusion or exclusion specifications to the		#
	# loaded names.																			#
	# #####################################################################	#
	if ((!$return_code) && (($ADF_IncludeNameFlag eq "YES") ||
		($ADF_ExcludeNameFlag eq "YES") || ($ADF_IncludeFileFlag eq "YES") ||
		($ADF_ExcludeFileFlag eq "YES") || ($ADF_IncludeTypeFlag eq "YES") ||
		($ADF_ExcludeTypeFlag eq "YES"))) {
		%used_name_array = %all_item_name_array;
		@tmp_name_array  = keys(%used_name_array);
		foreach $this_item (@tmp_name_array) {
			$delete_flag = 0;
			if (($ADF_IncludeNameFlag eq "YES") &&
				(!defined($ADF_IncludeNameArray{$this_item}))) {
				$delete_flag = 1;
			}
			elsif (($ADF_ExcludeNameFlag eq "YES") &&
				(defined($ADF_ExcludeNameArray{$this_item}))) {
				$delete_flag = 1;
			}
			else {
				@tmp_list = split(/\177/, $used_name_array{$this_item});
				if (($ADF_IncludeFileFlag eq "YES") &&
					(!defined($ADF_IncludeFileArray{$tmp_list[ADF_DB_FILE_NAME]}))) {
					$delete_flag = 1;
				}
				elsif (($ADF_ExcludeFileFlag eq "YES") &&
					(defined($ADF_ExcludeFileArray{$tmp_list[ADF_DB_FILE_NAME]}))) {
					$delete_flag = 1;
				}
				elsif (($ADF_IncludeTypeFlag eq "YES") &&
					(!defined($ADF_IncludeTypeArray{$tmp_list[ADF_DB_TYPE]}))) {
					$delete_flag = 1;
				}
				elsif (($ADF_ExcludeTypeFlag eq "YES") &&
					(defined($ADF_ExcludeTypeArray{$tmp_list[ADF_DB_TYPE]}))) {
					$delete_flag = 1;
				}
			}
			if ($delete_flag) {
				delete $used_name_array{$this_item};
				foreach $this_publish (split(/\n/,
					$name_publish_array{$this_item})) {
					delete $all_hyper_name_array{$this_publish};
				}
			}
		}
		if ($ADF_XRefTreeFlag ne "YES") {
			%all_item_name_array = %used_name_array;
		}
	}
	# #####################################################################	#

	# #####################################################################	#
	# #####################################################################	#
	#    Here we build a tree structure which represents any names which		#
	# meet the following criteria:														#
	#																								#
	#    1) Included (or not excluded) names											#
	#																								#
	#    2) Names referenced by included names.										#
	#																								#
	#    The operation is recursive, so any names referenced, if loaded		#
	# initially, will end up being included.											#
	# #####################################################################	#
	if ((!$return_code) && ($ADF_XRefTreeFlag eq "YES")) {
		foreach $this_item (keys(%all_item_name_array)) {
			@tmp_list = split(/\177/, $all_item_name_array{$this_item});
			seek($all_adf_fh_list[$tmp_list[$ADF_LD_FILE_INDEX]],
				$tmp_list[$ADF_LD_OFFSET], 0);
			sysread($all_adf_fh_list[$tmp_list[$ADF_LD_FILE_INDEX]],
				$tmp_string, $tmp_list[$ADF_LD_LENGTH], 0);
			($order_string, $component_string, @tmp_list) =
				split(/\177/, $tmp_string);
			for $this_publish (split(/\n/, $tmp_list[$FLAG_PUBLISH_NAME])) {
				if (defined($used_name_array{$this_item})) {
					$used_publish_array{$this_publish} = $this_item."\n".
						$tmp_list[$FLAG_SEE_ALSO];
				}
				else {
					$full_publish_array{$this_publish} = $this_item."\n".
						$tmp_list[$FLAG_SEE_ALSO];
					$full_synonyms{$this_publish}      =
						$tmp_list[$FLAG_PUBLISH_NAME];
				}
			}
		}
		@tmp_publish_list = keys(%used_publish_array);
		while ($#tmp_publish_list > -1) {
			($this_name, @tmp_list) =
				split(/\n/, $used_publish_array{$tmp_publish_list[0]});
			for $this_item (@tmp_list) {
				if (defined($full_publish_array{$this_item})) {
					$used_publish_array{$this_item} =
						$full_publish_array{$this_item};
					delete $full_publish_array{$this_item};
					grep(do { $all_hyper_name_array{$_} = ""; 0; },
						split(/\n/, $full_synonyms{$this_item}));
				}
				if (defined($all_item_name_array{$this_item})) {
					$used_name_array{$this_item} = $all_item_name_array{$this_item};
				}
			}
			delete $used_publish_array{$tmp_publish_list[0]};
			@tmp_publish_list = keys(%used_publish_array);
		}
		%all_item_name_array = %used_name_array;
	}
	# #####################################################################	#

	print STDERR "\n";

	# #####################################################################	#
	# #####################################################################	#
	# #####################################################################	#
	if (!$return_code) {
		grep(do {
			if (defined($all_item_name_array{$_})) {
				push(@all_item_name_list, $_);
			} 0;
		}, @tmp_item_name_list);
	}
	else {
		grep(do { close($_); 0; }, @all_adf_fh_list);
		@all_item_name_list   = ();
		%all_item_name_array  = ();
		%all_hyper_name_array = ();
		@all_adf_fh_list      = ();
		$_[0]                 = $load_error_text;
	}
	# #####################################################################	#

	return($return_code);
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_LoadExternalRefs {
	local($ref_error_text, *in_hyper_name_array) = @_;
	local($return_code, $adf_file_name, $adf_fh, @tmp_name_list,
		@tmp_locate_list, %tmp_hyper_name_array);

	$return_code = 0;

	foreach $adf_file_name (keys(%ADF_ExternalRefFileList)) {
		$adf_fh = "IN_ADF_DB_TMP_".sprintf("%05u", $$);
		if ($return_code = &ADF_LoadDatabaseFile($adf_file_name,
			$adf_fh, "tmp_name_list", "tmp_locate_list", "tmp_hyper_name_array",
			"name_publish_array", ref_error_text)) {
			last;
		}
		close($adf_fh);
		@tmp_name_list   = ();
		@tmp_locate_list = ();
		grep(do {
			$in_hyper_name_array{$_} =
				$ADF_ExternalRefFileList{$adf_file_name};
			0;
		}, keys(%tmp_hyper_name_array));
		%tmp_hyper_name_array = ();
	}

	if ($return_code) {
		%in_hyper_name_array = ();
		$_[0]                = $ref_error_text;
	}

	return($return_code);
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_InsertEmbeddedHyperText {
	local(*in_data_list, *in_hyper_list) = @_;
	local(%exclude_array, $hyper_ref, $hyper_length, $order_index, $old_index,
		$new_index);

	grep(do { $exclude_array{$_} = ""; 0; },
		split(/\n/, $in_data_list[$FLAG_PUBLISH_NAME]));

#	NOTE: If 'HYPER_TEXT is "YES"
	foreach $hyper_ref (@in_hyper_list) {
		if (defined($exclude_array{$hyper_ref})) {
			next;
		}
		$hyper_length = length($hyper_ref);
		foreach $order_index (@DataOrderList) {
			if (($order_index != $FLAG_SEE_ALSO) &&
				($order_index != $FLAG_NAME) &&
				($in_data_list[$order_index] ne "") &&
				($DataParaFormatList[$order_index] eq "Y")) {
				$old_index = 0;
				while (($new_index = index($in_data_list[$order_index], $hyper_ref,
					$old_index)) > -1) {
					$old_index = $new_index + $hyper_length;
					if ((($new_index == 0) || (substr($in_data_list[$order_index],
						$new_index - 1, 1) =~ /\W/) ||
						(substr($in_data_list[$order_index], $new_index - 2, 2) =~
						/\001./)) && ((($new_index + $hyper_length + 1) ==
						length($in_data_list[$order_index])) ||
						(substr($in_data_list[$order_index], $old_index, 1) =~
						/\W/) || (substr($in_data_list[$order_index],
						$old_index, 2) =~ /\001./))) {
						substr($in_data_list[$order_index], $new_index,
							$hyper_length) = "\001H".$hyper_ref."\001h";
						$old_index += 4;
					}
				}
			}
		}
	}
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_LoadDatabaseFile {
	local($in_file_name, $in_adf_fh, *in_name_list, *in_locate_list,
		*in_hyper_name_array, *in_name_array) = @_;
	local($return_code, @file_stat, $tmp_string, @end_dir_list, @tmp_list,
		$current_offset, $tmp_length);

	$return_code    = 0;
	@in_name_list   = ();
	@in_locate_list = ();
	@file_stat      = stat($in_file_name);

	if (!(-f $in_file_name)) {
		$_[6]        = "Unable to locate the ADF database file ".
			"\'$in_file_name\'.";
		$return_code = -1;
	}
	elsif ($file_stat[7] < $ADF_FileMinimumLength) {
		$_[6]        = "The size of the ADF database file \'$in_file_name\' ".
			"($file_stat[7]) is less than the minimum ($ADF_FileMinimumLength).";
		$return_code = -1;
	}
	elsif (!open($in_adf_fh, "<$in_file_name")) {
		$_[6]        = "Unable to open the ADF database file ".
			"\'$in_file_name\' for reading.";
		$return_code = -1;
	}
	else {
		sysread($in_adf_fh, $tmp_string, $ADF_FileSigLength, 0);
		chop($tmp_string);
		$tmp_string =~ s/^\s+|\s+$//g;
		@tmp_list   =  split(/\s+/, $tmp_string);
		if (($#tmp_list != 4) || ($tmp_list[0] ne $ADF_FileSigText)) {
			$_[6]        = "The ADF database file \'$in_file_name\' does ".
				"not have a valid beginning signature.";
			$return_code = -1;
		}
		elsif ($tmp_list[1] !~ /^\d{4}\-\d{2}\-\d{2}$/) {
			$_[6]        = "The ADF database file \'$in_file_name\' has ".
				"an invalid date (\'$tmp_list[1]\').";
			$return_code = -1;
		}
		elsif ($tmp_list[2] !~ /^\d{2}\:\d{2}\:\d{2}$/) {
			$_[6]        = "The ADF database file \'$in_file_name\' has ".
				"an invalid time (\'$tmp_list[2]\').";
			$return_code = -1;
		}
		elsif ($tmp_list[3] != ($#ADF_FlagNameList + 1)) {
			$_[6]        = sprintf("%s %s %u %s --- %s %s.",
				"The ADF database file \'$in_file_name\' has",
				"an invalid number of parse domain components ($tmp_list[3])",
				$#ADF_FlagNameList + 1, "were expected",
				"the database file may have been built with an older",
				"ADF version");
			$return_code = -1;
		}
		elsif (($tmp_list[4] ne "DATA") && ($tmp_list[4] ne "CHECK")) {
			$_[6]        = "The ADF database file \'$in_file_name\' does ".
				"not have a valid type (either \'DATA\' or \'CHECK\' ".
				"was expected).";
			$return_code = -1;
		}
		else {
			seek($in_adf_fh, $file_stat[7] - $ADF_FileEndSigLength, 0);
			sysread($in_adf_fh, $tmp_string, $ADF_FileEndSigLength, 0);
			$tmp_string   =~ s/^\s+|\s+$//g;
			@end_dir_list =  split(/\s+/, $tmp_string);
			if (($#end_dir_list != 6) ||
				($end_dir_list[0] ne $ADF_FileEndSigText)) {
				$_[6]        = "The ADF database file \'$in_file_name\' does ".
					"not have a valid ending signature.";
				$return_code = -1;
			}
			seek($in_adf_fh, $end_dir_list[1], 0);
			sysread($in_adf_fh, $tmp_string, $end_dir_list[2], 0);
			grep(do { $in_hyper_name_array{$_} = ""; 0; },
				split(/\n/, $tmp_string)); 
			seek($in_adf_fh, $end_dir_list[3], 0);
			sysread($in_adf_fh, $tmp_string, $end_dir_list[4], 0);
			grep(do {
				@tmp_list                    = split(/\177/, $_);
				$in_name_array{$tmp_list[0]} =
					join("\n", @tmp_list[1..$#tmp_list]);
				0;
			}, split(/\n/, $tmp_string));
			seek($in_adf_fh, $end_dir_list[5], 0);
			sysread($in_adf_fh, $tmp_string, $end_dir_list[6], 0);
			grep(do {
				@tmp_list = split(/\177/, $_);
				push(@in_locate_list, $_);
				push(@in_name_list, (split(/\177/, $_))[0]);
				0;
			}, split(/\n/, $tmp_string));
#print STDERR "LOCATE:", join("\nLOCATE:", @in_locate_list), "\n";
#print STDERR "NAME  :", join("\nNAME  :", @in_name_list), "\n";
#print STDERR "HYPER :", join("\nHYPER :", keys(%in_hyper_name_array)), "\n";
		}
	}

	return($return_code);
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_ParseInputFile {
	local($out_adf_fh, $local_error_text, @in_arg_list) = @_;
	local($return_code, $this_file, $file_name, $file_type, @file_date_data,
		$this_file_date, @in_lines, $found_bof_flag, $found_eof_flag, 
		$tmp_string, $man_section, $tab_setting, $present_type, $current_type,
		$current_offset, %out_hyper_array, @out_name_list, @out_dir_list,
		%item_name_array, $tmp_error_area);

	$return_code      = 0;
	$local_error_text = "";
	$tmp_error_area   = "";
	%out_hyper_array  = ();
	@out_name_list    = ();
	@out_dir_list     = ();
	%item_name_array  = ();

	$current_offset   = &ADF_WriteDBHeader($out_adf_fh);

	for $this_file (@in_arg_list) {
		print STDERR "PREP:", $this_file, " ";
		$file_name =  $this_file;
		$file_name =~ s/.*\/(\S+)$/\1/;
		if ($this_file !~ /\.\S+$/) {
			print STDERR " ---> ";
			$local_error_text = "File \'$this_file\' does not have a file type.";
			$return_code      = -1;
			last;
		}
		$file_type    =  $this_file;
		$file_type    =~ s/^\S+\.(\S+)$/\1/;
		$present_type =  $file_type;
		$current_type =  $file_type;
		if (!defined($FileTypeList{$file_type})) {
			print STDERR " ---> ";
			$local_error_text = "File \'$this_file\' has an unknown file type ".
				"(\'.$file_type\').\n";
			$return_code      = -1;
			last;
		}
		if (!open(IN_TO_DO, "<$this_file")) {
			print STDERR " ---> ";
			$local_error_text = "Unable to open input file \'$this_file\'.";
			$return_code      = -1;
			last;
		}
		&ADF_SetFileTypeData($FileTypeList{$file_type});
		@file_date_data  = localtime((stat($this_file))[9]);
		$this_file_date  = sprintf("%4u-%02u-%02u", $file_date_data[5] + 1900,
			$file_date_data[4] + 1, $file_date_data[3]);
		$found_bof_flag  = 0;
		while (<IN_TO_DO>) {
			chop;
			if (/$BOH_Pattern/) {
				$after_bof_flag =  1;
				$continue_code  =  1;
				$found_bof_flag =  1;
				$found_eof_flag =  0;
				@in_lines       =  ($_);
				$tmp_string     =  $in_lines[0];
				$tmp_string     =~ s/$BOH_Pattern//;
				$current_type   =  $file_type;
				$man_section    =  $ADF_DefaultSection;
				if ($tmp_string !~ /^\s*$/) {
					$tmp_string                                 =~ s/\s+//g;
					$current_type                               =  "";
					$man_section                                =  "";
					$tab_setting                                =  "";
					($current_type, $man_section, $tab_setting) =
						split(/,/, $tmp_string);
					$current_type                               =~ s/^\.\s*//;
					if ($current_type eq "") {
						$current_type = $file_type;
					}
					elsif (!defined($FileTypeList{$current_type})) {
						print STDERR " ---> File \'$this_file\' contains a ",
							"section which specifies an unknown file type ",
							"override (\'.$current_type\').";
						$continue_code = 0;
					}
					elsif (($man_section ne "") && ($man_section =~ /\W/)) {
						print STDERR " ---> File \'$this_file\' contains a ",
							"section which specifies a man page section name ",
							"which contains non-alphanumeric characters ",
							"(\'$man_section\').";
						$continue_code = 0;
					}
					elsif (index("123456789lnop", substr($man_section, 0, 1)) ==
						-1) {
						print STDERR " ---> File \'$this_file\' contains a ",
							"section which specifies a man page section name ",
							"in which the first character (\'",
							substr($man_section, 0, 1), "\') is not one of ",
							"\'1\', \'2\', \'3\', \'4\', \'5\', \'6\', \'7\', ",
							"\'8\', \'9\', \'l\', \'n\', \'o\', or \'p\' ",
							"(\'$man_section\').";
						$continue_code = 0;
					}
				}
				if ($continue_code) {
					if ($current_type ne $present_type) {
						&ADF_SetFileTypeData($FileTypeList{$current_type});
						$present_type = $current_type;
					}
					while (<IN_TO_DO>) {
						chop;
						if ($after_bof_flag && ($_ =~ $EmptyLinePattern)) {
							next;
						}
						$after_bof_flag = 0;
						push(@in_lines, $_);
						if (/$EOH_Pattern/) {
							$found_eof_flag = 1;
							last;
						}
					}
					if (!$found_eof_flag) {
						print STDERR "Unable to locate the end of the descriptive ",
							"header in file \'$this_file\'.";
						last;
					}
					else {
						if (&ADF_ExtractDataLines($current_type, $this_file,
							$file_name,
							$this_file_date, $out_adf_fh, $current_offset,
							$man_section, $tab_setting, "out_hyper_array",
							"out_name_list", "out_dir_list", "item_name_array",
							@in_lines)) {
							$local_error_text = "Errors occurred while extracting ".
								"one or more ADF comment entries.";
							$return_code      = -1;
						}
					}
				}
			}
			if ($return_code) { last; }
		}
		close(IN_TO_DO);
		if (($ADF_ErrorOnNoComment eq "YES") && (!$found_bof_flag)) {
			print STDERR "\n>>> Unable to locate descriptive header in file ".
				"\'$this_file\'.";
			$local_error_text = "Errors occurred while extracting one or more ".
				"ADF comment entries.";
			$return_code      = -1;
		}
		print STDERR "\n";
	}

	if (!$return_code) {
		@out_name_list = ($ADF_PrepSortFlag eq "YES") ? sort(@out_name_list) :
			@out_name_list;
		@out_dir_list  = ($ADF_PrepSortFlag eq "YES") ? sort(@out_dir_list) :
			@out_dir_list;
		&ADF_WriteDBTrailer($out_adf_fh, $current_offset, "out_hyper_array",
			"out_name_list", "out_dir_list");
	}
	else {
		$_[1] = $local_error_text;
	}

	return($return_code);
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_ExtractDataLines {
	local($file_type, $file_name, $base_file_name, $file_date, $out_adf_fh,
		$out_adf_offset, $in_man_section, $in_tab_setting, *in_hyper_array,
		*in_name_list, *in_dir_list, *in_item_name_array, @in_list) = @_;
	local($return_code, @data_list, $this_item, $this_datum, @data_lines,
		$file_year, $file_month, $file_day, $write_data_flag, @tmp_list);
	local($data_string, $dir_length, $data_offset, $data_length, $dir_string);

	$return_code                   = 0;
	@data_list                     = ();
	$data_list[$#ADF_FlagNameList] = "";	# Set number of elements in list

	# #####################################################################	#
	# #####################################################################	#
	# #####################################################################	#
#	if ($ADF_CheckCommentFlag eq "YES") {
#		&ADF_GetAreaData($FLAG_NAME, $data_list[$FLAG_NAME]);
#		&ADF_GetAreaData($FLAG_SEE_ALSO, $data_list[$FLAG_SEE_ALSO]);
#	}
#	else {
		$in_tab_setting = (($in_tab_setting < 1) || ($in_tab_setting > 8)) ?
			$ADF_TabSetting : $in_tab_setting;
		$data_list[$FLAG_FILE_TYPE]   = $file_type;
		$data_list[$FLAG_MAN_SECTION] = $in_man_section;
		$data_list[$FLAG_AUTHORS]     =
			(($DataNameList[$FLAG_AUTHORS] ne "") &&
			($ADF_DefaultAuthor ne "")) ? $ADF_DefaultAuthor : "";
		$data_list[$FLAG_COPYRIGHTS]  =
			(($DataNameList[$FLAG_COPYRIGHTS] ne "") &&
			($ADF_DefaultCopyright ne "")) ? $ADF_DefaultCopyright : "";
		foreach $this_item (@DataOrderList) {
				$data_list[$this_item] = &ADF_GetAreaData($this_item, "in_list");
			# ###############################################################	#
			# ###############################################################	#
			#    If there are only two elements remaining in the array of		#
			# comment lines, they are the BOH (beginning-of-header) and EOH	#
			# (ending-of-header) lines, so we can stop searching.					#
			# ###############################################################	#
			if ($#in_list == 1) {
				last;
			}
			# ###############################################################	#
		}
#	}
	# #####################################################################	#

	# #####################################################################	#
	# #####################################################################	#
	# #####################################################################	#
	if (!$return_code) {
		if ($data_list[$FLAG_BASE_NAME] =~ /^\s*$/) {
			$data_list[$FLAG_BASE_NAME] =  $data_list[$FLAG_NAME];
			$data_list[$FLAG_BASE_NAME] =~ s/\001.//g;
			$data_list[$FLAG_BASE_NAME] =~ s/^\s+|\s+$//g;
			$data_list[$FLAG_BASE_NAME] =~ s/\s+/ /g;
			$data_list[$FLAG_BASE_NAME] =~ s/^(\S+)\s+.*$/\1/;
		}
		$data_list[$FLAG_FILE_TYPE]        = $file_type;
		$data_list[$FLAG_SEE_ALSO]         =  join("\n",
			sort(&do_uniq(split(/\n/, $data_list[$FLAG_SEE_ALSO]))));
		$data_list[$FLAG_AUTHORS]          =
			(($DataNameList[$FLAG_AUTHORS] ne "") &&
			($ADF_ForcedAuthor ne "")) ? $ADF_ForcedAuthor :
			$data_list[$FLAG_AUTHORS];
		$data_list[$FLAG_COPYRIGHTS]       =
			(($DataNameList[$FLAG_COPYRIGHTS] ne "") &&
			($ADF_ForcedCopyright ne "")) ? $ADF_ForcedCopyright :
			$data_list[$FLAG_COPYRIGHTS];
		$data_list[$FLAG_SOURCE_FILE_NAME] =
			(($DataNameList[$FLAG_SOURCE_FILE_NAME] ne "") &&
			($data_list[$FLAG_SOURCE_FILE_NAME] =~ /^\s*$/)) ?
			$base_file_name : $data_list[$FLAG_SOURCE_FILE_NAME];
		if ($data_list[$FLAG_SOURCE_FILE_DATE] =~ /^\s*$/) {
			$data_list[$FLAG_SOURCE_FILE_DATE] = $file_date;
		}
		elsif (&DATFUNCS_ParseDate($data_list[$FLAG_SOURCE_FILE_DATE],
			$file_year, $file_month, $file_day)) {
			$data_list[$FLAG_SOURCE_FILE_DATE] = $file_date;
		}
		else {
			$data_list[$FLAG_SOURCE_FILE_DATE] =
				sprintf("%4u-%02u-%02u", $file_year, $file_month,
				$file_day);
		}
		$data_list[$FLAG_MAN_SECTION]  = ($ADF_ForcedSection ne "") ?
			$ADF_ForcedSection : ($data_list[$FLAG_MAN_SECTION] =~ /^\s*$/) ?
			$ADF_DefaultSection : $data_list[$FLAG_MAN_SECTION];
		$data_list[$FLAG_TAB_SETTING]  = $in_tab_setting;
		$data_list[$FLAG_OUTPUT_INDEX] = join("\n",
			sort(&do_uniq(split(/\n/, $data_list[$FLAG_OUTPUT_INDEX]))));
		$data_list[$FLAG_PUBLISH_XREF] =
			($data_list[$FLAG_PUBLISH_XREF] =~ /^\s*$/) ?
			$data_list[$FLAG_BASE_NAME] :
			$data_list[$FLAG_BASE_NAME]."\n".$data_list[$FLAG_PUBLISH_XREF];
		$data_list[$FLAG_PUBLISH_XREF] = join("\n", 
			sort(&do_uniq(split(/\n/, $data_list[$FLAG_PUBLISH_XREF]))));
		$data_list[$FLAG_PUBLISH_NAME] = join("\n", 
			sort(&do_uniq(split(/\n/, $data_list[$FLAG_PUBLISH_NAME]))));
		for $this_datum (@data_list) {
			@data_lines = split(/\n/, $this_datum);
			while (($#data_lines > -1) &&
				($data_lines[$#data_lines] =~ /^\s*$/)) {
				pop(@data_lines);
			}
			while (($#data_lines > -1) &&
				($data_lines[0] =~ /^\s*$/)) {
				shift(@data_lines);
			}
			$this_datum = join("\n", @data_lines);
		}
	}
	# #####################################################################	#

	# #####################################################################	#
	# #####################################################################	#
	# #####################################################################	#
	if (!$return_code) {
		for ($this_item = 0; $this_item <= $#ADF_MasterRequiredFlag;
			$this_item++) {
			if (($ADF_MasterRequiredFlag[$this_item] eq "Y") &&
				($data_list[$this_item] eq "")) {
				print STDERR "\n>>> The component \'".
					$ADF_FlagNameList[$this_item]."\' is required by ADF, but ".
					"was not found in an ADF comment entry in the file \'".
					"$file_name\'.";
				$return_code = -1;
				last;
			}
		}
		if ((!$return_code) && ($ADF_NoRequiredSectionsFlag ne "YES")) {
			foreach $this_item (@DataOrderList) {
				if (($DataRequiredList[$this_item] eq "Y") &&
					($data_list[$this_item] eq "")) {
					print STDERR "\n>>> The component \'".
						$ADF_FlagNameList[$this_item]."\' is required by this ".
						"parse domain \'$ADF_CurrentParseDomain\', but was not ".
						"found in an ADF comment entry in the file \'$file_name\'.";
					$return_code = -1;
					last;
				}
			}
		}
	}
	# #####################################################################	#

	# #####################################################################	#
	# #####################################################################	#
	# #####################################################################	#
	if (!$return_code) {
		$write_data_flag = 1;
		if (defined($in_item_name_array{$data_list[$FLAG_BASE_NAME]})) {
			if ($ADF_FirstDuplicateName eq "YES") {
				$write_data_flag = 0;
			}
			elsif ($ADF_LastDuplicateName eq "YES") {
				@tmp_list = split(/\177/,
					$in_item_name_array{$data_list[$FLAG_BASE_NAME]});
				splice(@in_name_list, $tmp_list[1], 1);
				splice(@in_dir_list, $tmp_list[1], 1);
				delete $in_hyper_array{$data_list[$FLAG_BASE_NAME]};
				delete $in_item_name_array{$data_list[$FLAG_BASE_NAME]};
			}
			else {
				@tmp_list = split(/\177/,
					$in_item_name_array{$data_list[$FLAG_BASE_NAME]});
				print STDERR "\n>>> ADF comment entry named \'".
					"$data_list[$FLAG_BASE_NAME]\' in file \'$file_name\' was ".
					"previously defined in file \'$tmp_list[0]\'.";
				$return_code = -1;
			}
		}
		if ((!$return_code) && $write_data_flag) {
			&ADF_WriteDBData($out_adf_fh, $file_name, $base_file_name,
				$out_adf_offset, $DataOrderString, $DataComponentString,
				$dir_string, @data_list);
			if ($data_list[$FLAG_PUBLISH_NAME] ne "") {
				$in_hyper_array{$data_list[$FLAG_BASE_NAME]} =
					$data_list[$FLAG_PUBLISH_NAME];
			}
			$in_item_name_array{$data_list[$FLAG_BASE_NAME]} =
				$file_name.sprintf("\177%u", $#in_dir_list + 1);
			push(@in_name_list,  $data_list[$FLAG_BASE_NAME]."\177".
				join("\177", split(/\n/, $data_list[$FLAG_PUBLISH_NAME])));
			push(@in_dir_list, $dir_string);
			$_[5] = $out_adf_offset;
		}
	}
	# #####################################################################	#

	if (!$return_code) {
		print STDERR ".";
	}

	return($return_code);
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_WriteDBHeader {
	local($db_file_handle) = @_;
	local($current_date, $current_time, $current_date_time);

	if ($ADF_ZeroDataFlag ne "YES") {
		&ADF_GetDateTime($current_date, $current_time, $current_date_time);
	}
	else {
		print STDERR "********** FAKED THE DB FILE DATE AND TIME **********\n";
		$current_date = "0000-00-00";
		$current_time = "00:00:00";
	}

	syswrite($db_file_handle, sprintf($ADF_FileSigFormat,
		$current_date, $current_time, $#ADF_FlagNameList + 1,
		(!$CheckFlag) ? "DATA" : "CHECK"), $ADF_FileSigLength, 0);

	return($ADF_FileSigLength);
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_WriteDBData {
	local($in_adf_fh, $long_file_name, $short_file_name, $in_adf_offset,
		$data_order_string, $data_component_string, $in_dir_string,
		@in_data_list) = @_;
	local($data_string, $dir_length, $data_offset, $data_length);

	$data_string   = $data_order_string."\177".$data_component_string."\177".
		join("\177", @in_data_list);
	$dir_length    = length($in_data_list[$FLAG_BASE_NAME]) + 1 +
		length($in_data_list[$FLAG_FILE_TYPE]) + 1 + length($short_file_name) +
		1 + length($long_file_name) + 1 + 10 + 1 + 10 + 1 + 10 + 1;
	$data_offset   = $in_adf_offset + $dir_length;
	$data_length   = length($data_string);
	$in_dir_string = $in_data_list[$FLAG_BASE_NAME]."\177".
		$in_data_list[$FLAG_FILE_TYPE]."\177".$short_file_name."\177".
		$long_file_name."\177".sprintf("%010lu\177%010lu\177%010lu",
		$data_offset, $data_length, $data_offset + $data_length)."\n";
	$in_adf_offset = $data_offset + $data_length;
	$_[3]          = $in_adf_offset;
	$_[6]          = $in_dir_string;

	syswrite($in_adf_fh, $in_dir_string, $dir_length, 0);
	syswrite($in_adf_fh, $data_string, $data_length, 0);
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_WriteDBTrailer {
	local($in_db_handle, $in_db_offset, *in_hyper_array, *in_name_list,
		*in_dir_list) = @_;
	local($hyper_name_string, $base_name_string, $dir_list_string);

	$hyper_name_string = join("\n", sort(&do_uniq(values(%in_hyper_array)))).
		"\n";
	$base_name_string  = join("\n", @in_name_list)."\n";
	$dir_list_string   = ($#in_dir_list == -1) ? "" : join("", @in_dir_list);
	print $in_db_handle $hyper_name_string;
	print $in_db_handle $base_name_string;
	print $in_db_handle $dir_list_string;
	printf $in_db_handle $ADF_FileEndSigFormat,
		$in_db_offset, length($hyper_name_string),
		$in_db_offset + length($hyper_name_string), length($base_name_string),
		$in_db_offset + length($hyper_name_string) + length($base_name_string),
		length($dir_list_string);
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_DoUsage {
	local($exit_code, $program_name, $program_type, $exit_message) = @_;
	local($out_usage_fh);

	$out_usage_fh = ($exit_code) ? "STDERR" : "STDOUT";

	if ($exit_message ne "") {
		print $out_usage_fh ($exit_code) ? "ERROR: " : "", $exit_message, "\n";
	}

	if ($program_type =~ /ALL/) {
		print $out_usage_fh "Options for the program \'adv\'\n";
		&ADF_EmitUsageData($out_usage_fh, "adf", "ALL");
		print $out_usage_fh "\f";
		print $out_usage_fh "Options for the program \'advprep\'\n";
		&ADF_EmitUsageData($out_usage_fh, "adfprep", "PREP");
		print $out_usage_fh "\f";
		print $out_usage_fh "Options for the program \'advchk\'\n";
		&ADF_EmitUsageData($out_usage_fh, "adfchk", "CHK");
		print $out_usage_fh "\f";
		print $out_usage_fh "Options for the program \'advget\'\n";
		&ADF_EmitUsageData($out_usage_fh, "adfget", "GET");
		print $out_usage_fh "\f";
		print $out_usage_fh "Options for the program \'advcomb\'\n";
		&ADF_EmitUsageData($out_usage_fh, "adfcomb", "COMB");
		print $out_usage_fh "\f";
		print $out_usage_fh "Options for the program \'advout\'\n";
		&ADF_EmitUsageData($out_usage_fh, "adfout", "OUT");
	}
	else {
		&ADF_EmitUsageData($out_usage_fh, $program_name, $program_type);
	}

	exit($exit_code);
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_EmitUsageData {
	local($usage_fh, $program_name, $program_type) = @_;
	local(@tmp_list, $count_1, %tmp_array, $this_arg, $this_line);

	@tmp_list = ();
	push(@tmp_list, ($program_type =~ /PREP|ALL/) ? @ADF_PREPUsageList : ());
	push(@tmp_list, ($program_type =~ /CHK|ALL/)  ? @ADF_CHKUsageList  : ());
	push(@tmp_list, ($program_type =~ /GET/)      ? @ADF_GETUsageList  : ());
	push(@tmp_list, ($program_type =~ /COMB/)     ? @ADF_COMBUsageList : ());
	push(@tmp_list, ($program_type =~ /OUT|ALL/)  ? @ADF_OUTUsageList  : ());
	push(@tmp_list, @ADF_ANYUsageList);

	for ($count_1 = 0; $count_1 <= $#tmp_list; $count_1 += 2) {
		$tmp_array{$tmp_list[$count_1]} = $tmp_list[$count_1 + 1];
	}

	print $usage_fh "USAGE:\n   $program_name <options> ",
		($program_type =~ /PREP|ALL/) ?
		"<source-file-name> [<source-file-name> . . .]" :
		"<adf-db-file-name> [<adf-db-file-name> . . .]", "\n\n";

	print $usage_fh
		"   Where <options> are a combination of the following:\n\n";

	foreach $this_arg (sort(keys(%tmp_array))) {
		print $usage_fh "   ", $this_arg, "\n";
		foreach $this_line (split(/\n/,
			&ADF_wraptext(8, 76 - 6, $tmp_array{$this_arg}))) {
			print $usage_fh "      ", $this_line, "\n";
		}
		print $usage_fh "\n";
	}
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_GetAreaData {
	local($current_index, *work_lines) = @_;
	local($current_data, $count_1, $next_flag, $rtrim_flag, $squeeze_flag,
		$wrap_flag, $this_line, $para_format, @storage);

	$current_data = "";

	if (!grep(/$DataPatternList[$current_index]/, @work_lines)) {
		return($current_data);
	}

	for ($count_1 = 0; $count_1 <= $#work_lines; $count_1++) {
		if ($work_lines[$count_1] =~ /$DataPatternList[$current_index]/) {
			$work_lines[$count_1] =~ s/$DataPatternList[$current_index]//;
			$next_flag = 1;
			while (($count_1 <= $#work_lines) &&
				($work_lines[$count_1] !~ /$DataExcludeList[$current_index]/)) {
				$rtrim_flag   =  $DataRTrimList[$current_index];
				$squeeze_flag =  $DataSqueezeList[$current_index];
				$wrap_flag    =  $DataWrapList[$current_index];
				$this_line    =  (splice(@work_lines, $count_1, 1))[0];
				$this_line    =~ s/\000|\001|\002|\177/ /g;
				($BOL_StripPattern ne "") ?
					$this_line =~ s/$BOL_StripPattern//g : 0;
				($EOL_StripPattern ne "") ?
					$this_line =~ s/$EOL_StripPattern//g : 0;
				($DataLTrimList[$current_index] eq "Y") ?
					$this_line =~ s/^\s+//g : 0;
				$para_format = "";
				if (($DataParaFormatList[$current_index] eq "Y") &&
					($this_line =~ /$ADF_ParaFormatPatternString/)) {
					$this_line   =~ s/($ADF_ParaFormatPatternString)(.*)$/\2/;
					$para_format =  $1;
					if ($para_format =~ /^\[|^\{/) {
						$rtrim_flag   = "N";
						$squeeze_flag = "N";
						$wrap_flag    = "N";
					}
					else {
						$rtrim_flag   = $DataRTrimList[$current_index];
						$squeeze_flag = $DataSqueezeList[$current_index];
						$wrap_flag    = $DataWrapList[$current_index];
						($DataLTrimList[$current_index] eq "Y") ?
							$this_line =~ s/^\s+//g : 0;
					}
				}
				($rtrim_flag eq "Y")   ? $this_line =~ s/\s+$//g : 0;
				($squeeze_flag eq "Y") ? $this_line =~ s/\s+/ /g : 0;
				$this_line = $para_format.$this_line;
				if ($wrap_flag ne "Y") {
					push(@storage, $this_line);
				}
				else {
					if ($next_flag) {
						if ($this_line ne "") {
							push(@storage, $this_line);
							$next_flag = 0;
						}
					}
					else {
						if ($this_line eq "") {
							$next_flag = 1;
						}
						elsif (($DataParaFormatList[$current_index] eq "Y") &&
							($this_line =~ /$ADF_ParaFormatPatternString/)) {
							push(@storage, $this_line);
						}
						else {
							$storage[$#storage] .= " ".$this_line;
						}
					}
				}
			}
			if ($DataParaFormatList[$current_index] eq "Y") {
				&ADF_FormatParagraph($DataLTrimList[$current_index], "storage");
			}
			if ($DataCharFormatList[$current_index] eq "Y") {
				&ADF_FormatCharacter("storage");
			}
			$current_data = join("\n", @storage);
			$current_data = ($current_data =~ /^\s*$/) ? "" : $current_data;
			last;
		}
	}

	return($current_data);
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_FormatParagraph {
	local($in_ltrim_flag, *section_lines_list) = @_;
	local($this_para, $tmp_string, $para_level, $para_number, $font_type,
		$format_flag, $this_format);

	for $this_para (@section_lines_list) {
		if ($this_para =~ /$ADF_ParaFormatNMPatternString/) {
			$tmp_string  =  $this_para;
			$tmp_string  =~ s/^(.)(\+{1,3})(\d+).(.*)$/\1/;
			$para_level  =  length($2);
			$para_number =  ($3 < 0) ? 0 : ($3 > 999) ? 999 : $3;
			$font_type   =  (($1 eq "(") || ($1 eq "[")) ? "NORMAL" : "SMALL ";
			$format_flag =  (($1 eq "(") || ($1 eq "<")) ? "NO " : "YES";
			$tmp_string  =  $ADF_ParaFormatSig."NM|".$para_level."|".
				sprintf("%03u", $para_number)."|".$font_type."|".$format_flag;
			$this_para   =  $4;
			if (($in_ltrim_flag eq "Y") && ($format_flag eq "YES")) {
				$this_para =~ s/^\s+//g;
			}
			$this_para = $tmp_string.$this_para;
		}
		elsif ($this_para =~ /$ADF_ParaFormatPatternString/) {
			for $this_format (keys(%ADF_ParaFormatPatternArray)) {
				if ($this_para =~ $this_format) {
					$this_para =~ s/$this_format//;
					if (($in_ltrim_flag eq "Y") &&
						($ADF_ParaFormatPatternArray{$this_format} =~ /YES$/)) {
						$this_para =~ s/^\s+//g;
					}
					$this_para = $ADF_ParaFormatSig.
						$ADF_ParaFormatPatternArray{$this_format}.$this_para;
					last;
				}
			}
		}
	}

	return(@section_lines_list);
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_FormatCharacter {
	local(*section_lines_list) = @_;
	local($section_item, $level, $replace_string, $index, $index_1, $index_2);

	for $section_item (@section_lines_list) {
		$section_item =~ s/\'\'/\@\'/g;		# Convert from old-style bold
		$section_item =~ s/\`\`/\@\`/g;		# Convert from old-style italic
		$section_item =~ s/\'\`/\@\>/g;		# Convert from old-style superscript
		$section_item =~ s/\`\'/\@\</g;		# Convert from old-style subscript
		while ($section_item =~ /\@\'/) {	# Bold characters
			$section_item =~ s/\@\'/\000B/;
			if ($section_item =~ /\@\'/) {
				$section_item =~ s/\@\'/\000b/;
			}
			else {
				$section_item .= "\000b";
			}
		}
		while ($section_item =~ /\@\`/) {	# Italic characters
			$section_item =~ s/\@\`/\000I/;
			if ($section_item =~ /\@\`/) {
				$section_item =~ s/\@\`/\000i/;
			}
			else {
				$section_item .= "\000i";
			}
		}
		while ($section_item =~ /\@\_/) {	# Underlined characters
			$section_item =~ s/\@\_/\000U/;
			if ($section_item =~ /\@\_/) {
				$section_item =~ s/\@\_/\000u/;
			}
			else {
				$section_item .= "\000u";
			}
		}
		while ($section_item =~ /\@\-/) {	# Overlined characters
			$section_item =~ s/\@\-/\000O/;
			if ($section_item =~ /\@\-/) {
				$section_item =~ s/\@\-/\000o/;
			}
			else {
				$section_item .= "\000o";
			}
		}
		while ($section_item =~ /\@\#/) {	# Strike-through characters
			$section_item =~ s/\@\#/\000T/;
			if ($section_item =~ /\@\#/) {
				$section_item =~ s/\@#/\000t/;
			}
			else {
				$section_item .= "\000t";
			}
		}
		while ($section_item =~ /\@\~/) {	# Embedded indices
			$section_item =~ s/\@\~/\000X/;
			if ($section_item =~ /\@\~/) {
				$section_item =~ s/\@~/\000x/;
			}
			else {
				$section_item .= "\000x";
			}
		}
		$level = 0;
		while (1) {
			$index_1 = index($section_item, "@>");
			$index_2 = index($section_item, "@<");
			if ($index_1 == $index_2) { last; }
			$replace_string = "";
			$index          = ($index_1 == -1) ? $index_2 : ($index_2 == -1) ?
				$index_1 : ($index_1 < $index_2) ? $index_1 : $index_2;
			if (($index == $index_1) && ($level <= 0)) {
				$replace_string = (!$level) ? "\000Y" : "\000z";
				$level++;
			}
			elsif (($index == $index_2) && ($level >= 0)) {
				$replace_string = (!$level) ? "\000Z" : "\000y";
				$level--;
			}
			substr($section_item, $index, 2) = $replace_string;
		}
		$replace_string .=  ($level > 0) ? "\000y" : ($level < 0) ? "\000z" : "";
		$section_item    =~ s/\000/\001/g;
	}

	return(@section_lines_list);
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_EmitOneAscii {
	local($this_item, @data_list) = @_;
	local($return_code, $this_datum, @this_section, $section_line, $this_line,
		$wrap_line, $indent_padding, $tmp_format, @tmp_array, $indent_count,
		$indent_head);

	$return_code = 0;
	
	foreach $this_datum (@DataOrderList) {
		if (($ADF_MasterDisplayFlag[$this_datum] eq "Y") &&
			($data_list[$this_datum] ne "")) {
			print $DataNameList[$this_datum], "\n";
			$data_list[$this_datum] =~ s/\001.//g;
			@this_section           =  split(/\n/, $data_list[$this_datum]);
			$section_line           =  0;
			if ($this_datum == $FLAG_CODE_SYNTAX) {
				print $ADF_ManMarginPadding;
				print "_" x (80 - (length($ADF_ManMarginPadding) + 1));
				print "\n";
				for $this_line (@this_section) {
					&ADF_wraptext($data_list[$FLAG_TAB_SETTING],
						80 - (length($ADF_ManMarginPadding) + 1), $this_line);
					print $ADF_ManMarginPadding, join("\n".$ADF_ManMarginPadding,
						split(/\n/, $this_line)), "\n";
				}
				print $ADF_ManMarginPadding;
				print "_" x (80 - (length($ADF_ManMarginPadding) + 1));
				print "\n\n";
				next;
			}
			if ($this_datum == $FLAG_CODE_EXAMPLES) {
				print "_" x 79;
				print "\n";
				for $this_line (@this_section) {
					&ADF_tabtospc($this_line, $data_list[$FLAG_TAB_SETTING]);
					print $this_line, "\n";
				}
				print "_" x 79;
				print "\n\n";
				next;
			}
			for $this_line (@this_section) {
				$wrap_line      = $this_line;
				$indent_padding = "";
				$indent_head    = "";
				$line_length    = $LineLength;
				$line_length    = 80 - (length($ADF_ManMarginPadding) + 1);
				if (substr($wrap_line, 0, length($ADF_ParaFormatSig)) eq
					$ADF_ParaFormatSig) {
					$tmp_format =  substr($wrap_line, length($ADF_ParaFormatSig),
						$ADF_ParaFormatLength);
					$wrap_line  =  substr($wrap_line,
						length($ADF_ParaFormatSig) + $ADF_ParaFormatLength,
						length($wrap_line));
					@tmp_array  = split(/\|/, $tmp_format);
					if ($tmp_array[0] eq "NM") {
						$indent_count  = ($tmp_array[1] - 1) * 4;
						$indent_head   = " " x $indent_count;
						$indent_head  .= sprintf("%3u ", $tmp_array[2]);
					}
					elsif ($tmp_array[0] eq "BB") {
						$indent_count  = ($tmp_array[1] - 1) * 4;
						$indent_head   = " " x $indent_count;
						$indent_head  .= " o  ";
					}
					elsif ($tmp_array[0] eq "LN") {
						$indent_count = $tmp_array[1] * 4;
						$indent_head  = " " x $indent_count;
						print $ADF_ManMarginPadding;
						print " " x length($indent_head);
						print "_" x ($line_length - length($indent_head));
						print "\n";
					}
					else {
						$indent_count = $tmp_array[1] * 4;
						$indent_head  = " " x $indent_count;
					}
					$indent_padding  = " " x length($indent_head);
					$line_length    -= length($indent_head);
					if ($tmp_array[4] eq "YES") {
						&ADF_wraptext($data_list[$FLAG_TAB_SETTING], $line_length,
							$wrap_line);
					}
				}
				else {
					&ADF_wraptext($data_list[$FLAG_TAB_SETTING], $line_length,
						$wrap_line);
				}
				$wrap_line = $indent_head.$wrap_line;
				print $ADF_ManMarginPadding, join("\n".$ADF_ManMarginPadding.
					$indent_padding, split(/\n/, $wrap_line)),
					"\n\n";
				$section_line++;
			}
		}
	}

	return($return_code);
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_EmitOneManPage {
	local($OUT_FH, $this_item, @data_list) = @_;
	local($return_code, $current_date, $current_time, $current_date_time,
		$man_doc_date, $this_datum, @this_section, $this_line, $section_line,
		$wrap_line, $tmp_format, @tmp_array, $indent_count, $indent_head,
		$bullet_flag);

	$return_code = 0;

	&ADF_GetDateTime($current_date, $current_time, $current_date_time);

	$man_doc_date =  ($data_list[$FLAG_SOURCE_FILE_DATE] =~ /^\s*$/) ?
		$current_date : $data_list[$FLAG_SOURCE_FILE_DATE];
	$man_doc_date =~ s/^(\d{4})\-(\d{2})\-(\d{2})$/\1/;
	$man_doc_date =  substr($DATFUNCS_MonthList[$2 - 1], 0, 1);
	$man_doc_date =~ y/[a-z]/[A-Z]/;
	$man_doc_date =  $3." ".$man_doc_date.substr($DATFUNCS_MonthList[$2 - 1],
		1)." ".$1;

	print $OUT_FH ".\\\" * "; print $OUT_FH "*" x 66; print $OUT_FH " *\n";
	print $OUT_FH ".\\\" * "; print $OUT_FH "*" x 66; print $OUT_FH " *\n";
	print $OUT_FH ".\\\" *\n";
	print $OUT_FH ".\\\" * Created by the Automated Documentation Facility ",
		"(ADF)\n";
	print $OUT_FH ".\\\" *\n";
	print $OUT_FH ".\\\" * Creation Date: $current_date\n";
	print $OUT_FH ".\\\" * Creation Time:   $current_time\n";
	print $OUT_FH ".\\\" *\n";
	print $OUT_FH ".\\\" * Document Date: $data_list[$FLAG_SOURCE_FILE_DATE]\n";
	print $OUT_FH ".\\\" *                $man_doc_date\n";
	print $OUT_FH ".\\\" *\n";
	print $OUT_FH ".\\\" * "; print $OUT_FH "*" x 66; print $OUT_FH " *\n";

	print $OUT_FH ".TH $data_list[$FLAG_BASE_NAME] ",
		$data_list[$FLAG_MAN_SECTION], " ", "\"$man_doc_date\"\n";

	foreach $this_datum (@DataOrderList) {
		if (($ADF_MasterDisplayFlag[$this_datum] eq "Y") &&
			($data_list[$this_datum] ne "")) {
			print $OUT_FH ".SH \"", $DataNameList[$this_datum], "\"\n";
			if ($this_datum == $FLAG_CODE_SYNTAX) {
				$data_list[$this_datum] =~ s/\\/\\\\/g;
				$data_list[$this_datum] =~ s/\\\-/\0377/g;
				$data_list[$this_datum] =~ s/\-/\\\-/g;
				$data_list[$this_datum] =~ s/\0377/\\\-/g;
				@this_section = split(/\n/, $data_list[$this_datum]);
				print $OUT_FH ".cs 1 18\n";
				print $OUT_FH ".nf\n";
				print $OUT_FH ".cu\n";
				print $OUT_FH "_" x 75; print $OUT_FH "\n";
				for $this_line (@this_section) {
					$this_line =~ s/^\s+|\s+$//g;
					&ADF_wraptext($data_list[$FLAG_TAB_SETTING], 74, $this_line);
					# #########################################################	#
					# #########################################################	#
					#    Fix-up {n|t}roff request/command characters . . .		#
					# #########################################################	#
					$this_line =~ s/^(\.|\')/\\\&\1/;
					$this_line =~ s/\n(\.|\')/\n\\\&\1/g;
					# #########################################################	#
					$this_line =~ s/ /\\ /g;
					print $OUT_FH $this_line, "\n";
				}
				print $OUT_FH ".cu\n";
				print $OUT_FH "_" x 75; print $OUT_FH "\n";
				print $OUT_FH ".LP\n";
				print $OUT_FH ".cs 1\n";
				print $OUT_FH ".fi\n";
				print $OUT_FH "\n";
			}
			elsif ($this_datum == $FLAG_CODE_EXAMPLES) {
				$data_list[$this_datum] =~ s/\\/\\\\/g;
				$data_list[$this_datum] =~ s/\\\-/\0377/g;
				$data_list[$this_datum] =~ s/\-/\\\-/g;
				$data_list[$this_datum] =~ s/\0377/\\\-/g;
				# #########################################################	#
				# #########################################################	#
				#    Fix-up {n|t}roff request/command characters . . .		#
				# #########################################################	#
				$this_line =~ s/^(\.|\')/\\\&\1/;
				$this_line =~ s/\n(\.|\')/\n\\\&\1/g;
				# #########################################################	#
				@this_section = split(/\n/, $data_list[$this_datum]);
				print $OUT_FH ".cs 1 18\n";
				print $OUT_FH ".nf\n";
				print $OUT_FH ".cu\n";
				print $OUT_FH "_" x 75; print $OUT_FH "\n";
				for $this_line (@this_section) {
					&ADF_tabtospc($this_line, $data_list[$FLAG_TAB_SETTING]);
					# #########################################################	#
					# #########################################################	#
					#    Fix-up {n|t}roff request/command characters . . .		#
					# #########################################################	#
					$this_line =~ s/^(\.|\')/\\\&\1/;
					$this_line =~ s/\n(\.|\')/\n\\\&\1/g;
					# #########################################################	#
					$this_line =~ s/ /\\ /g;
					print $OUT_FH $this_line, "\n";
				}
				print $OUT_FH ".cu\n";
				print $OUT_FH "_" x 75; print $OUT_FH "\n";
				print $OUT_FH ".LP\n";
				print $OUT_FH ".cs 1\n";
				print $OUT_FH ".fi\n";
				print $OUT_FH "\n";
			}
			else {
				@this_section = split(/\n/, $data_list[$this_datum]);
				$section_line = 0;
				for $this_line (@this_section) {
					$wrap_line   = $this_line;
					$bullet_flag = "";
					@tmp_array   = ();
					if (substr($wrap_line, 0, length($ADF_ParaFormatSig)) eq
						$ADF_ParaFormatSig) {
						$tmp_format =  substr($wrap_line,
							length($ADF_ParaFormatSig), $ADF_ParaFormatLength);
						$wrap_line  =  substr($wrap_line,
							length($ADF_ParaFormatSig) + $ADF_ParaFormatLength,
							length($wrap_line));
						@tmp_array  = split(/\|/, $tmp_format);
						if ($tmp_array[0] eq "NM") {
							$indent_count = ($tmp_array[1] - 1) * 4;
							$tmp_array[2] = sprintf("%u", $tmp_array[2] % 999);
							$indent_head  = "\\0" x (3 - length($tmp_array[2]));
							$indent_head  = ".RS $indent_count\n".
								".IP ".$indent_head.$tmp_array[2]."\n";
						}
						elsif ($tmp_array[0] eq "BB") {
							$indent_count = ($tmp_array[1] - 1) * 4;
							$indent_head  = ".RS $indent_count\n".".IP o\n";
						}
						elsif ($tmp_array[0] eq "LN") {
							print $OUT_FH ".RE\n";
							print $OUT_FH ".RS ", $tmp_array[1] * 4, "\n";
							print $OUT_FH ".cu\n";
							print $OUT_FH "_" x (75 - ($tmp_array[1] * 4));
							print $OUT_FH "\n";
							print $OUT_FH ".LP\n";
							print $OUT_FH ".LP\n";
						}
						else {
							$indent_count = $tmp_array[1] * 4;
							$indent_head  = ".RS $indent_count\n";
						}
						$bullet_flag  = "Y";
						if ($tmp_array[4] ne "YES") {
							&ADF_tabtospc($this_line, $data_list[$FLAG_TAB_SETTING]);
						}
						$wrap_line =~ s/\\/\\\\/g;
						$wrap_line =~ s/\\\-/\0377/g;
						$wrap_line =~ s/\-/\\\-/g;
						$wrap_line =~ s/\0377/\\\-/g;
						# ######################################################	#
						# ######################################################	#
						#    Fix-up {n|t}roff request/command characters . . .	#
						# ######################################################	#
						$wrap_line =~ s/^((\001.)*)(\.|\')/\1\\\&\3/;
						# ######################################################	#
						if ($tmp_array[4] ne "YES") {
							$this_line =~ s/ /\\ /g;
						}
					}
					else {
						$wrap_line =~ s/\\/\\\\/g;
						$wrap_line =~ s/\\\-/\0377/g;
						$wrap_line =~ s/\-/\\\-/g;
						$wrap_line =~ s/\0377/\\\-/g;
						# ######################################################	#
						# ######################################################	#
						#    Fix-up {n|t}roff request/command characters . . .	#
						# ######################################################	#
						$wrap_line =~ s/^((\001.)*)(\.|\')/\1\\\&\3/;
						# ######################################################	#
					}
					if ($this_datum == $FLAG_SEE_ALSO) {
						print $OUT_FH ".LP\n";
						print $OUT_FH ".BR ",
							join("\n.BR ", split(/\n/, $wrap_line)), "\n.LP\n";
					}
					else {
						$this_line =~ s/^\./\\\&\./;
						$this_line =~ s/^\'/\\\&\'/;
						$this_line =~ s/\n\./\n\\\&\./g;
						$this_line =~ s/\n\'/\n\\\&\'/g;
						$wrap_line =~ s/\001B/\\fB/g;
						$wrap_line =~ s/\001b/\\fP/g;
						$wrap_line =~ s/\001I/\\fI/g;
						$wrap_line =~ s/\001i/\\fP/g;
# NOTE: Underline not supported as of yet . . .
						$wrap_line =~ s/\001U//gi; # <--- NEED TO FIX
						$wrap_line =~ s/\001Y|\001z/\\u/g;
						$wrap_line =~ s/\001y|\001Z/\\d/g;
						# ##### Remove any unsupported format specifications
						$wrap_line  =~ s/\001.//g;
						$wrap_line .=  "\n\.ft R\n";
#print $OUT_FH ".BI\n.BR\n.IB\n.IR\n.RB\n.RI\n";
						if ($tmp_array[4] eq "NO ") {
							$wrap_line =~ s/ /\\ /g;
							print $OUT_FH ".cs 1 18\n";
							print $OUT_FH ".nf\n";
							print $OUT_FH $wrap_line, "\n";
							print $OUT_FH ".cs 1\n";
							print $OUT_FH ".fi\n";
						}
						elsif ($bullet_flag eq "") {
							print $OUT_FH ".RE\n";
							print $OUT_FH join("\n", split(/\n/, $wrap_line)),
								"\n.LP\n";
						}
						else {
							print $OUT_FH ".RE\n";
							print $OUT_FH $indent_head;
							print $OUT_FH join("\n", split(/\n/, $wrap_line)),
								"\n.LP\n";
						}
					}
					$section_line++;
				}
				if ($return_code) {
					last;
				}
			}
		}
	}

	return($return_code);
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_EmitFrameHeader {
	local($OUT_FH) = @_;
	local($current_date, $current_time, $current_date_time, $this_format,
		@tmp_array);

	&ADF_GetDateTime($current_date, $current_time, $current_date_time);

	print $OUT_FH "<MIFFile 1.01>\n";
	print $OUT_FH "# "; print $OUT_FH "#" x 74; print $OUT_FH " #\n";
	print $OUT_FH "# "; print $OUT_FH "#" x 74; print $OUT_FH " #\n";
	print $OUT_FH "#\n";
	print $OUT_FH "# Created by the Automated Documentation Facility (ADF)\n";
	print $OUT_FH "#\n";
	print $OUT_FH "# Creation Date: $current_date\n";
	print $OUT_FH "# Creation Time:   $current_time\n";
	print $OUT_FH "#\n";
	print $OUT_FH "# "; print $OUT_FH "#" x 74; print $OUT_FH " #\n";
	print $OUT_FH "\n";

	print $OUT_FH "include(mif_read.m4)\n";
	print $OUT_FH "\n";

	print $OUT_FH "<Units Uin>\n";
	print $OUT_FH "\n";

	print $OUT_FH "<Catalog\n";
	print $OUT_FH "> # end of Catalog\n";
	print $OUT_FH "\n";

	print $OUT_FH "<Page \n";
	print $OUT_FH " <PageType ReferencePage >\n";
	print $OUT_FH " <PageTag `Reference'>\n";
	print $OUT_FH " <PageSize  8.5\" 11.0\">\n";
	print $OUT_FH " <PageOrientation Portrait >\n";
	print $OUT_FH " <Frame \n";
	print $OUT_FH "  <Pen 15>\n";
	print $OUT_FH "  <Fill 7>\n";
	print $OUT_FH "  <PenWidth  0.5 pt>\n";
	print $OUT_FH "  <Separation 0>\n";
	print $OUT_FH "  <BRect  0.75\" 4.0\" 7.0\" 0.25\">\n";
	print $OUT_FH "  <FrameType NotAnchored >\n";
	print $OUT_FH "  <Tag `ADF_LN_2'>\n";
	print $OUT_FH "  <PolyLine \n";
	print $OUT_FH "   <Pen 0>\n";
	print $OUT_FH "   <HeadCap Square >\n";
	print $OUT_FH "   <TailCap Square >\n";
	print $OUT_FH "   <NumPoints 2>\n";
	print $OUT_FH "   <Point  1.0\" 0.125\">\n";
	print $OUT_FH "   <Point  7.0\" 0.125\">\n";
	print $OUT_FH "  > # end of PolyLine\n";
	print $OUT_FH " > # end of Frame\n";
	print $OUT_FH " <Frame \n";
	print $OUT_FH "  <Pen 15>\n";
	print $OUT_FH "  <PenWidth  0.5 pt>\n";
	print $OUT_FH "  <BRect  0.75\" 2.5\" 7.0\" 0.25\">\n";
	print $OUT_FH "  <FrameType NotAnchored >\n";
	print $OUT_FH "  <Tag `ADF_LN_0'>\n";
	print $OUT_FH "  <PolyLine \n";
	print $OUT_FH "   <Pen 0>\n";
	print $OUT_FH "   <NumPoints 2>\n";
	print $OUT_FH "   <Point  0.25\" 0.125\">\n";
	print $OUT_FH "   <Point  7.0\" 0.125\">\n";
	print $OUT_FH "  > # end of PolyLine\n";
	print $OUT_FH " > # end of Frame\n";
	print $OUT_FH " <Frame \n";
	print $OUT_FH "  <Pen 15>\n";
	print $OUT_FH "  <BRect  0.75\" 3.25\" 7.0\" 0.25\">\n";
	print $OUT_FH "  <FrameType NotAnchored >\n";
	print $OUT_FH "  <Tag `ADF_LN_1'>\n";
	print $OUT_FH "  <PolyLine \n";
	print $OUT_FH "   <Pen 0>\n";
	print $OUT_FH "   <NumPoints 2>\n";
	print $OUT_FH "   <Point  0.625\" 0.125\">\n";
	print $OUT_FH "   <Point  7.0\" 0.125\">\n";
	print $OUT_FH "  > # end of PolyLine\n";
	print $OUT_FH " > # end of Frame\n";
	print $OUT_FH " <Frame \n";
	print $OUT_FH "  <Pen 15>\n";
	print $OUT_FH "  <BRect  0.75\" 4.75\" 7.0\" 0.25\">\n";
	print $OUT_FH "  <FrameType NotAnchored >\n";
	print $OUT_FH "  <Tag `ADF_LN_3'>\n";
	print $OUT_FH "  <PolyLine \n";
	print $OUT_FH "   <Pen 0>\n";
	print $OUT_FH "   <NumPoints 2>\n";
	print $OUT_FH "   <Point  1.375\" 0.125\">\n";
	print $OUT_FH "   <Point  7.0\" 0.125\">\n";
	print $OUT_FH "  > # end of PolyLine\n";
	print $OUT_FH " > # end of Frame\n";
	print $OUT_FH "> # end of Page\n";

	print $OUT_FH "<PgfCatalog\n";

	print $OUT_FH " <Pgf \n";
	print $OUT_FH "  <PgfTag `ADF_Name'>\n";
	print $OUT_FH "  <PgfUseNextTag No>\n";
	print $OUT_FH "  <PgfNextTag `'>\n";
	print $OUT_FH "  <PgfAlignment LeftRight>\n";
	print $OUT_FH "  <PgfFIndent  0.25\">\n";
	print $OUT_FH "  <PgfLIndent  0.25\">\n";
	print $OUT_FH "  <PgfRIndent  0.0\">\n";
	print $OUT_FH "  <PgfTopSeparator `'>\n";
	print $OUT_FH "  <PgfBotSeparator `'>\n";
	print $OUT_FH "  <PgfPlacement Anywhere>\n";
	print $OUT_FH "  <PgfSpBefore  5.0 pt>\n";
	print $OUT_FH "  <PgfSpAfter  5.0 pt>\n";
	print $OUT_FH "  <PgfWithPrev No>\n";
	print $OUT_FH "  <PgfWithNext No>\n";
	print $OUT_FH "  <PgfBlockSize 3>\n";
	print $OUT_FH "  <PgfFont \n";
	print $OUT_FH "   <FTag `'>\n";
	print $OUT_FH "   <FFamily `NewCenturySchlbk'>\n";
	print $OUT_FH "   <FVar `Regular'>\n";
	print $OUT_FH "   <FWeight `Regular'>\n";
	print $OUT_FH "   <FAngle `Regular'>\n";
	print $OUT_FH "   <FSize  12.0 pt>\n";
	print $OUT_FH "   <FUnderline No>\n";
	print $OUT_FH "   <FOverline No>\n";
	print $OUT_FH "   <FStrike No>\n";
	print $OUT_FH "   <FSupScript No>\n";
	print $OUT_FH "   <FSubScript No>\n";
	print $OUT_FH "   <FChangeBar No>\n";
	print $OUT_FH "   <FOutline No>\n";
	print $OUT_FH "   <FShadow No>\n";
	print $OUT_FH "   <FPairKern No>\n";
	print $OUT_FH "   <FDoubleUnderline No>\n";
	print $OUT_FH "   <FNumericUnderline No>\n";
	print $OUT_FH "   <FDX  0.0 pt>\n";
	print $OUT_FH "   <FDY  0.0 pt>\n";
	print $OUT_FH "   <FDW  0.0 pt>\n";
	print $OUT_FH "   <FSeparation 0>\n";
	print $OUT_FH "  > # end of PgfFont\n";
	print $OUT_FH "  <PgfLineSpacing Fixed>\n";
	print $OUT_FH "  <PgfLeading  1.0 pt>\n";
	print $OUT_FH "  <PgfAutoNum No>\n";
	print $OUT_FH "  <PgfNumTabs 0>\n";
	print $OUT_FH "  <PgfHyphenate Yes>\n";
	print $OUT_FH "  <HyphenMaxLines 2>\n";
	print $OUT_FH "  <HyphenMinPrefix 2>\n";
	print $OUT_FH "  <HyphenMinSuffix 2>\n";
	print $OUT_FH "  <HyphenMinWord 5>\n";
	print $OUT_FH "  <PgfLetterSpace No>\n";
	print $OUT_FH "  <PgfMinWordSpace 75>\n";
	print $OUT_FH "  <PgfOptWordSpace 100>\n";
	print $OUT_FH "  <PgfMaxWordSpace 125>\n";
	print $OUT_FH "  <PgfLanguage USEnglish>\n";
	print $OUT_FH "  <PgfCellAlignment Top>\n";
	print $OUT_FH "  <PgfCellMargins  0.0 pt 0.0 pt 0.0 pt 0.0 pt>\n";
	print $OUT_FH "  <PgfCellLMarginFixed No>\n";
	print $OUT_FH "  <PgfCellTMarginFixed No>\n";
	print $OUT_FH "  <PgfCellRMarginFixed No>\n";
	print $OUT_FH "  <PgfCellBMarginFixed No>\n";
	print $OUT_FH " > # end of Pgf\n";
	print $OUT_FH " <Pgf \n";
	print $OUT_FH "  <PgfTag `ADF_Section'>\n";
	print $OUT_FH "  <PgfUseNextTag Yes>\n";
	print $OUT_FH "  <PgfNextTag `Body'>\n";
	print $OUT_FH "  <PgfAlignment LeftRight>\n";
	print $OUT_FH "  <PgfFIndent  0.0\">\n";
	print $OUT_FH "  <PgfLIndent  0.0\">\n";
	print $OUT_FH "  <PgfRIndent  0.0\">\n";
	print $OUT_FH "  <PgfTopSeparator `'>\n";
	print $OUT_FH "  <PgfBotSeparator `'>\n";
	print $OUT_FH "  <PgfPlacement Anywhere>\n";
	print $OUT_FH "  <PgfSpBefore  10.0 pt>\n";
	print $OUT_FH "  <PgfSpAfter  2.0 pt>\n";
	print $OUT_FH "  <PgfWithPrev No>\n";
	print $OUT_FH "  <PgfWithNext Yes>\n";
	print $OUT_FH "  <PgfBlockSize 1>\n";
	print $OUT_FH "  <PgfFont \n";
	print $OUT_FH "   <FTag `'>\n";
	print $OUT_FH "   <FFamily `NewCenturySchlbk'>\n";
	print $OUT_FH "   <FVar `Regular'>\n";
	print $OUT_FH "   <FWeight `Bold'>\n";
	print $OUT_FH "   <FAngle `Regular'>\n";
	print $OUT_FH "   <FSize  12.0 pt>\n";
	print $OUT_FH "   <FUnderline No>\n";
	print $OUT_FH "   <FOverline No>\n";
	print $OUT_FH "   <FStrike No>\n";
	print $OUT_FH "   <FSupScript No>\n";
	print $OUT_FH "   <FSubScript No>\n";
	print $OUT_FH "   <FChangeBar No>\n";
	print $OUT_FH "   <FOutline No>\n";
	print $OUT_FH "   <FShadow No>\n";
	print $OUT_FH "   <FPairKern No>\n";
	print $OUT_FH "   <FDoubleUnderline No>\n";
	print $OUT_FH "   <FNumericUnderline No>\n";
	print $OUT_FH "   <FDX  0.0 pt>\n";
	print $OUT_FH "   <FDY  0.0 pt>\n";
	print $OUT_FH "   <FDW  0.0 pt>\n";
	print $OUT_FH "   <FSeparation 0>\n";
	print $OUT_FH "  > # end of PgfFont\n";
	print $OUT_FH "  <PgfLineSpacing Fixed>\n";
	print $OUT_FH "  <PgfLeading  0.0 pt>\n";
	print $OUT_FH "  <PgfAutoNum Yes>\n";
	print $OUT_FH "  <PgfNumFormat `'>\n";
	print $OUT_FH "  <PgfNumberFont `Numbering'>\n";
	print $OUT_FH "  <PgfNumAtEnd No>\n";
	print $OUT_FH "  <PgfNumTabs 0>\n";
	print $OUT_FH "  <PgfHyphenate Yes>\n";
	print $OUT_FH "  <HyphenMaxLines 2>\n";
	print $OUT_FH "  <HyphenMinPrefix 2>\n";
	print $OUT_FH "  <HyphenMinSuffix 2>\n";
	print $OUT_FH "  <HyphenMinWord 5>\n";
	print $OUT_FH "  <PgfLetterSpace No>\n";
	print $OUT_FH "  <PgfMinWordSpace 75>\n";
	print $OUT_FH "  <PgfOptWordSpace 100>\n";
	print $OUT_FH "  <PgfMaxWordSpace 125>\n";
	print $OUT_FH "  <PgfLanguage USEnglish>\n";
	print $OUT_FH "  <PgfCellAlignment Top>\n";
	print $OUT_FH "  <PgfCellMargins  0.0 pt 0.0 pt 0.0 pt 0.0 pt>\n";
	print $OUT_FH "  <PgfCellLMarginFixed No>\n";
	print $OUT_FH "  <PgfCellTMarginFixed No>\n";
	print $OUT_FH "  <PgfCellRMarginFixed No>\n";
	print $OUT_FH "  <PgfCellBMarginFixed No>\n";
	print $OUT_FH " > # end of Pgf\n";
	print $OUT_FH " <Pgf \n";
	print $OUT_FH "  <PgfTag `ADF_Start'>\n";
	print $OUT_FH "  <PgfUseNextTag Yes>\n";
	print $OUT_FH "  <PgfNextTag `Body'>\n";
	print $OUT_FH "  <PgfAlignment LeftRight>\n";
	print $OUT_FH "  <PgfFIndent  0.0\">\n";
	print $OUT_FH "  <PgfLIndent  0.0\">\n";
	print $OUT_FH "  <PgfRIndent  0.0\">\n";
	print $OUT_FH "  <PgfTopSeparator `'>\n";
	print $OUT_FH "  <PgfBotSeparator `'>\n";
	print $OUT_FH "  <PgfPlacement PageTop>\n";
	print $OUT_FH "  <PgfSpBefore  10.0 pt>\n";
	print $OUT_FH "  <PgfSpAfter  2.0 pt>\n";
	print $OUT_FH "  <PgfWithPrev No>\n";
	print $OUT_FH "  <PgfWithNext Yes>\n";
	print $OUT_FH "  <PgfBlockSize 1>\n";
	print $OUT_FH "  <PgfFont \n";
	print $OUT_FH "   <FTag `'>\n";
	print $OUT_FH "   <FFamily `NewCenturySchlbk'>\n";
	print $OUT_FH "   <FVar `Regular'>\n";
	print $OUT_FH "   <FWeight `Bold'>\n";
	print $OUT_FH "   <FAngle `Regular'>\n";
	print $OUT_FH "   <FSize  12.0 pt>\n";
	print $OUT_FH "   <FUnderline No>\n";
	print $OUT_FH "   <FOverline No>\n";
	print $OUT_FH "   <FStrike No>\n";
	print $OUT_FH "   <FSupScript No>\n";
	print $OUT_FH "   <FSubScript No>\n";
	print $OUT_FH "   <FChangeBar No>\n";
	print $OUT_FH "   <FOutline No>\n";
	print $OUT_FH "   <FShadow No>\n";
	print $OUT_FH "   <FPairKern No>\n";
	print $OUT_FH "   <FDoubleUnderline No>\n";
	print $OUT_FH "   <FNumericUnderline No>\n";
	print $OUT_FH "   <FDX  0.0 pt>\n";
	print $OUT_FH "   <FDY  0.0 pt>\n";
	print $OUT_FH "   <FDW  0.0 pt>\n";
	print $OUT_FH "   <FSeparation 0>\n";
	print $OUT_FH "  > # end of PgfFont\n";
	print $OUT_FH "  <PgfLineSpacing Fixed>\n";
	print $OUT_FH "  <PgfLeading  0.0 pt>\n";
	print $OUT_FH "  <PgfAutoNum Yes>\n";
	print $OUT_FH "  <PgfNumFormat `'>\n";
	print $OUT_FH "  <PgfNumberFont `Numbering'>\n";
	print $OUT_FH "  <PgfNumAtEnd No>\n";
	print $OUT_FH "  <PgfNumTabs 0>\n";
	print $OUT_FH "  <PgfHyphenate Yes>\n";
	print $OUT_FH "  <HyphenMaxLines 2>\n";
	print $OUT_FH "  <HyphenMinPrefix 2>\n";
	print $OUT_FH "  <HyphenMinSuffix 2>\n";
	print $OUT_FH "  <HyphenMinWord 5>\n";
	print $OUT_FH "  <PgfLetterSpace No>\n";
	print $OUT_FH "  <PgfMinWordSpace 75>\n";
	print $OUT_FH "  <PgfOptWordSpace 100>\n";
	print $OUT_FH "  <PgfMaxWordSpace 125>\n";
	print $OUT_FH "  <PgfLanguage USEnglish>\n";
	print $OUT_FH "  <PgfCellAlignment Top>\n";
	print $OUT_FH "  <PgfCellMargins  0.0 pt 0.0 pt 0.0 pt 0.0 pt>\n";
	print $OUT_FH "  <PgfCellLMarginFixed No>\n";
	print $OUT_FH "  <PgfCellTMarginFixed No>\n";
	print $OUT_FH "  <PgfCellRMarginFixed No>\n";
	print $OUT_FH "  <PgfCellBMarginFixed No>\n";
	print $OUT_FH " > # end of Pgf\n";
	print $OUT_FH " <Pgf \n";
	print $OUT_FH "  <PgfTag `ADF_NameTOC'>\n";
	print $OUT_FH "  <PgfUseNextTag No>\n";
	print $OUT_FH "  <PgfNextTag `'>\n";
	print $OUT_FH "  <PgfAlignment LeftRight>\n";
	print $OUT_FH "  <PgfFIndent  0.0\">\n";
	print $OUT_FH "  <PgfLIndent  0.0\">\n";
	print $OUT_FH "  <PgfRIndent  0.0\">\n";
	print $OUT_FH "  <PgfTopSeparator `'>\n";
	print $OUT_FH "  <PgfBotSeparator `'>\n";
	print $OUT_FH "  <PgfPlacement Anywhere>\n";
	print $OUT_FH "  <PgfSpBefore  8.0 pt>\n";
	print $OUT_FH "  <PgfSpAfter  0.0 pt>\n";
	print $OUT_FH "  <PgfWithPrev No>\n";
	print $OUT_FH "  <PgfWithNext No>\n";
	print $OUT_FH "  <PgfBlockSize 1>\n";
	print $OUT_FH "  <PgfFont \n";
	print $OUT_FH "   <FTag `'>\n";
	print $OUT_FH "   <FFamily `NewCenturySchlbk'>\n";
	print $OUT_FH "   <FVar `Regular'>\n";
	print $OUT_FH "   <FWeight `Regular'>\n";
	print $OUT_FH "   <FAngle `Regular'>\n";
	print $OUT_FH "   <FSize  12.0 pt>\n";
	print $OUT_FH "   <FUnderline No>\n";
	print $OUT_FH "   <FOverline No>\n";
	print $OUT_FH "   <FStrike No>\n";
	print $OUT_FH "   <FSupScript No>\n";
	print $OUT_FH "   <FSubScript No>\n";
	print $OUT_FH "   <FChangeBar No>\n";
	print $OUT_FH "   <FOutline No>\n";
	print $OUT_FH "   <FShadow No>\n";
	print $OUT_FH "   <FPairKern No>\n";
	print $OUT_FH "   <FDoubleUnderline No>\n";
	print $OUT_FH "   <FNumericUnderline No>\n";
	print $OUT_FH "   <FDX  0.0 pt>\n";
	print $OUT_FH "   <FDY  0.0 pt>\n";
	print $OUT_FH "   <FDW  0.0 pt>\n";
	print $OUT_FH "   <FSeparation 0>\n";
	print $OUT_FH "  > # end of PgfFont\n";
	print $OUT_FH "  <PgfLineSpacing Fixed>\n";
	print $OUT_FH "  <PgfLeading  2.0 pt>\n";
	print $OUT_FH "  <PgfAutoNum No>\n";
	print $OUT_FH "  <PgfNumTabs 1>\n";
	print $OUT_FH "  <TabStop \n";
	print $OUT_FH "   <TSX  7.0\">\n";
	print $OUT_FH "   <TSType Right>\n";
	print $OUT_FH "   <TSLeaderStr `.'>\n";
	print $OUT_FH "  > # end of TabStop\n";
	print $OUT_FH "  <PgfHyphenate Yes>\n";
	print $OUT_FH "  <HyphenMaxLines 2>\n";
	print $OUT_FH "  <HyphenMinPrefix 2>\n";
	print $OUT_FH "  <HyphenMinSuffix 2>\n";
	print $OUT_FH "  <HyphenMinWord 5>\n";
	print $OUT_FH "  <PgfLetterSpace No>\n";
	print $OUT_FH "  <PgfMinWordSpace 75>\n";
	print $OUT_FH "  <PgfOptWordSpace 100>\n";
	print $OUT_FH "  <PgfMaxWordSpace 125>\n";
	print $OUT_FH "  <PgfLanguage USEnglish>\n";
	print $OUT_FH "  <PgfCellAlignment Top>\n";
	print $OUT_FH "  <PgfCellMargins  0.0 pt 0.0 pt 0.0 pt 0.0 pt>\n";
	print $OUT_FH "  <PgfCellLMarginFixed No>\n";
	print $OUT_FH "  <PgfCellTMarginFixed No>\n";
	print $OUT_FH "  <PgfCellRMarginFixed No>\n";
	print $OUT_FH "  <PgfCellBMarginFixed No>\n";
	print $OUT_FH " > # end of Pgf\n";
	print $OUT_FH " <Pgf \n";
	print $OUT_FH "  <PgfTag `ADF_NameAPL'>\n";
	print $OUT_FH "  <PgfUseNextTag No >\n";
	print $OUT_FH "  <PgfNextTag `'>\n";
	print $OUT_FH "  <PgfAlignment LeftRight >\n";
	print $OUT_FH "  <PgfFIndent  0.0\">\n";
	print $OUT_FH "  <PgfLIndent  0.0\">\n";
	print $OUT_FH "  <PgfRIndent  0.0\">\n";
	print $OUT_FH "  <PgfTopSeparator `'>\n";
	print $OUT_FH "  <PgfBotSeparator `'>\n";
	print $OUT_FH "  <PgfPlacement Anywhere >\n";
	print $OUT_FH "  <PgfSpBefore  8.0 pt>\n";
	print $OUT_FH "  <PgfSpAfter  0.0 pt>\n";
	print $OUT_FH "  <PgfWithPrev No >\n";
	print $OUT_FH "  <PgfWithNext No >\n";
	print $OUT_FH "  <PgfBlockSize 1>\n";
	print $OUT_FH "  <PgfFont \n";
	print $OUT_FH "   <FTag `'>\n";
	print $OUT_FH "   <FFamily `NewCenturySchlbk'>\n";
	print $OUT_FH "   <FVar `Regular'>\n";
	print $OUT_FH "   <FWeight `Regular'>\n";
	print $OUT_FH "   <FAngle `Regular'>\n";
	print $OUT_FH "   <FSize  12.0 pt>\n";
	print $OUT_FH "   <FUnderline No >\n";
	print $OUT_FH "   <FOverline No >\n";
	print $OUT_FH "   <FStrike No >\n";
	print $OUT_FH "   <FSupScript No >\n";
	print $OUT_FH "   <FSubScript No >\n";
	print $OUT_FH "   <FChangeBar No >\n";
	print $OUT_FH "   <FOutline No >\n";
	print $OUT_FH "   <FShadow No >\n";
	print $OUT_FH "   <FPairKern No >\n";
	print $OUT_FH "   <FDoubleUnderline No >\n";
	print $OUT_FH "   <FNumericUnderline No >\n";
	print $OUT_FH "   <FDX  0.0 pt>\n";
	print $OUT_FH "   <FDY  0.0 pt>\n";
	print $OUT_FH "   <FDW  0.0 pt>\n";
	print $OUT_FH "   <FSeparation 0>\n";
	print $OUT_FH "  > # end of PgfFont\n";
	print $OUT_FH "  <PgfLineSpacing Fixed >\n";
	print $OUT_FH "  <PgfLeading  2.0 pt>\n";
	print $OUT_FH "  <PgfAutoNum No >\n";
	print $OUT_FH "  <PgfNumTabs 1>\n";
	print $OUT_FH "  <TabStop \n";
	print $OUT_FH "   <TSX  7.0\">\n";
	print $OUT_FH "   <TSType Right >\n";
	print $OUT_FH "   <TSLeaderStr `.'>\n";
	print $OUT_FH "  > # end of TabStop\n";
	print $OUT_FH "  <PgfHyphenate Yes >\n";
	print $OUT_FH "  <HyphenMaxLines 2>\n";
	print $OUT_FH "  <HyphenMinPrefix 2>\n";
	print $OUT_FH "  <HyphenMinSuffix 2>\n";
	print $OUT_FH "  <HyphenMinWord 5>\n";
	print $OUT_FH "  <PgfLetterSpace No >\n";
	print $OUT_FH "  <PgfMinWordSpace 75>\n";
	print $OUT_FH "  <PgfOptWordSpace 100>\n";
	print $OUT_FH "  <PgfMaxWordSpace 125>\n";
	print $OUT_FH "  <PgfLanguage USEnglish >\n";
	print $OUT_FH "  <PgfCellAlignment Top >\n";
	print $OUT_FH "  <PgfCellMargins  0.0 pt 0.0 pt 0.0 pt 0.0 pt>\n";
	print $OUT_FH "  <PgfCellLMarginFixed No >\n";
	print $OUT_FH "  <PgfCellTMarginFixed No >\n";
	print $OUT_FH "  <PgfCellRMarginFixed No >\n";
	print $OUT_FH "  <PgfCellBMarginFixed No >\n";
	print $OUT_FH " > # end of Pgf\n";

	foreach $this_format (sort(grep(/YES$/,
		values(%ADF_ParaFormatPatternArray)), "NM|1|000|NORMAL|YES",
		"NM|2|000|NORMAL|YES", "NM|3|000|NORMAL|YES", "NM|1|000|SMALL |YES",
		"NM|2|000|SMALL |YES", "NM|3|000|SMALL |YES")) {
		@tmp_array    = split(/\|/, $this_format);
		&ADF_CreateFrameParagraphType($tmp_array[0], $tmp_array[1],
			$tmp_array[3]);
	}

	print $OUT_FH " > # end of PgfCatalog\n";
	print $OUT_FH "\n";

	print $OUT_FH "# Start of the Document section\n";
	print $OUT_FH "<XRefFormats\n";
	print $OUT_FH " <XRefFormat\n";
	print $OUT_FH "  <XRefName `Name_X_Ref'>\n";
	print $OUT_FH "  <XRefDef `\\<HyperText_Ref\\>\\<\$paratext\\>".
		"\\<Default \\xa6 Font\\> on page \\<\$pagenum\\>'>\n";
#	print $OUT_FH "  <XRefDef `\\<\$paratext\\> cross-reference to page \\<\$pagenum\\> ***** IS TO BE REPLACED BY CROSS-REFERENCE FORMATS LOADED FROM THE MASTER DOCUMENT *****'>\n";
	print $OUT_FH " > # end of XRefFormat\n";
	print $OUT_FH "> # end of XRefFormats\n";
	print $OUT_FH "\n";

	print $OUT_FH "<TextFlow\n";
	print $OUT_FH " <TFTag `A'>\n";
	print $OUT_FH " <TFAutoConnect Yes >\n";
	print $OUT_FH " <Notes\n";
	print $OUT_FH " > # end Notes\n";
	print $OUT_FH "\n";
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_CreateFrameParagraphType {
	local($para_type, $para_level, $para_font) = @_;
	local($first_margin, $left_margin);

	$first_margin = ($para_type eq "IN") ?
		0.250 + ($para_level * 0.375) :
		($para_type eq "NM") ? 0.250 + (($para_level - 1) * 0.375) :
		$para_level * 0.375;
	$left_margin  = $first_margin + (($para_type eq "IN") ? 0.0 :
		($para_type eq "NM") ? 0.375 : 0.250);
	print $OUT_FH " <Pgf\n";
	print $OUT_FH "  <PgfTag `ADF_", $para_type, $para_level,
		substr($para_font, 0, 1), "'>\n";
	print $OUT_FH "  <PgfUseNextTag No>\n";
	print $OUT_FH "  <PgfNextTag `'>\n";
	print $OUT_FH "  <PgfAlignment LeftRight>\n";
	print $OUT_FH "  <PgfFIndent $first_margin\">\n";
	print $OUT_FH "  <PgfLIndent $left_margin\">\n";
	print $OUT_FH "  <PgfRIndent 0.0>\n";
	print $OUT_FH "  <PgfTopSeparator `'>\n";
	print $OUT_FH "  <PgfBotSeparator `'>\n";
	print $OUT_FH "  <PgfPlacement Anywhere>\n";
	print $OUT_FH ($para_font eq "NORMAL") ?
		"  <PgfSpBefore  5.0 pt>\n" : "  <PgfSpBefore  2.0 pt>\n";
	print $OUT_FH ($para_font eq "NORMAL") ?
		"  <PgfSpAfter  5.0 pt>\n" : "  <PgfSpAfter  2.0 pt>\n";
	print $OUT_FH "  <PgfWithPrev No>\n";
	print $OUT_FH "  <PgfWithNext No>\n";
	print $OUT_FH "  <PgfBlockSize 1>\n";
	print $OUT_FH "  <PgfFont \n";
	print $OUT_FH "   <FTag `'>\n";
	print $OUT_FH ($para_font eq "NORMAL") ?
		"   <FFamily `NewCenturySchlbk'>\n" : "   <FFamily `Courier'>\n";
	print $OUT_FH "   <FVar `Regular'>\n";
	print $OUT_FH "   <FWeight `Regular'>\n";
	print $OUT_FH "   <FAngle `Regular'>\n";
	print $OUT_FH ($para_font eq "NORMAL") ?
		"   <FSize  12.0 pt>\n" : "   <FSize  10.0 pt>\n";
	print $OUT_FH "   <FUnderline No>\n";
	print $OUT_FH "   <FOverline No>\n";
	print $OUT_FH "   <FStrike No>\n";
	print $OUT_FH "   <FSupScript No>\n";
	print $OUT_FH "   <FSubScript No>\n";
	print $OUT_FH "   <FChangeBar No>\n";
	print $OUT_FH "   <FOutline No>\n";
	print $OUT_FH "   <FShadow No>\n";
	print $OUT_FH "   <FPairKern No>\n";
	print $OUT_FH "   <FDoubleUnderline No>\n";
	print $OUT_FH "   <FNumericUnderline No>\n";
	print $OUT_FH "   <FDX  0.0 pt>\n";
	print $OUT_FH "   <FDY  0.0 pt>\n";
	print $OUT_FH "   <FDW  0.0 pt>\n";
	print $OUT_FH "   <FSeparation 0>\n";
	print $OUT_FH "  > # end of PgfFont\n";
	print $OUT_FH "  <PgfLineSpacing Fixed>\n";
	print $OUT_FH "  <PgfLeading  1.0 pt>\n";
	print $OUT_FH "  <PgfAutoNum Yes>\n";
	print $OUT_FH ($para_type eq "BB") ?
		"  <PgfNumFormat `\\xa5 \\t'>\n" :  "  <PgfNumFormat `'>\n";
	print $OUT_FH "  <PgfNumberFont `'>\n";
	print $OUT_FH "  <PgfNumAtEnd No>\n";
	if ($para_type eq "NM") {
		print $OUT_FH "  <PgfNumTabs 2>\n";
		print $OUT_FH "  <TabStop <TSX ", $first_margin + 0.250, "\"> ",
			"<TSType Decimal> <TSLeaderStr ` '> <TSDecimalChar 46>>\n";
		print $OUT_FH "  <TabStop <TSX ", $first_margin + 0.375, "\"> ",
			"<TSType Left> <TSLeaderStr ` '>>\n";
	}
	elsif ($para_type eq "BB") {
		print $OUT_FH "  <PgfNumTabs 1>\n";
		print $OUT_FH "  <TabStop <TSX ", $first_margin + 0.250, "\"> ",
			"<TSType Left> <TSLeaderStr ` '>>\n";
	}
	else {
		print $OUT_FH "  <PgfNumTabs 0>\n";
	}
	print $OUT_FH "  <PgfHyphenate Yes>\n";
	print $OUT_FH "  <HyphenMaxLines 2>\n";
	print $OUT_FH "  <HyphenMinPrefix 2>\n";
	print $OUT_FH "  <HyphenMinSuffix 2>\n";
	print $OUT_FH "  <HyphenMinWord 5>\n";
	print $OUT_FH "  <PgfLetterSpace No>\n";
	print $OUT_FH "  <PgfMinWordSpace 75>\n";
	print $OUT_FH "  <PgfOptWordSpace 100>\n";
	print $OUT_FH "  <PgfMaxWordSpace 125>\n";
	print $OUT_FH "  <PgfLanguage USEnglish>\n";
	print $OUT_FH "  <PgfCellAlignment Top>\n";
	print $OUT_FH "  <PgfCellMargins  0.0 pt 0.0 pt 0.0 pt 0.0 pt>\n";
	print $OUT_FH "  <PgfCellLMarginFixed No>\n";
	print $OUT_FH "  <PgfCellTMarginFixed No>\n";
	print $OUT_FH "  <PgfCellRMarginFixed No>\n";
	print $OUT_FH "  <PgfCellBMarginFixed No>\n";
	print $OUT_FH " > # end of Pgf\n";
}

# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_EmitOneFrame {
	local($OUT_FH, $this_item, *in_hyper_name_array, @data_list) = @_;
	local($start_index_range, $end_index_range, $tmp_start_range,
		$tmp_end_range, $tmp_string, $this_datum, @this_section, $section_line, $this_line,
		$wrap_line, $para_name, $para_modifier, $split_line, $tmp_format,
		@tmp_array, $this_xref, @split_list, $split_line, $line_flag);

	&ADF_CreateFrameIndexEntries($data_list[$FLAG_OUTPUT_INDEX], 2,
		$tmp_start_range, $tmp_end_range);
	$start_index_range = $tmp_start_range;
	$end_index_range   = $tmp_end_range;

	&ADF_CreateFrameIndexEntries($data_list[$FLAG_PUBLISH_XREF], 4,
		$tmp_start_range, $tmp_end_range);
	$start_index_range .= $tmp_start_range;
	$end_index_range   .= $tmp_end_range;

	&ADF_CreateFrameIndexEntries($data_list[$FLAG_AUTHORS], 5,
		$tmp_start_range, $tmp_end_range);
	$start_index_range .= $tmp_start_range;
	$end_index_range   .= $tmp_end_range;

	foreach $this_datum (@DataOrderList) {
		if (($ADF_MasterDisplayFlag[$this_datum] eq "Y") &&
			($data_list[$this_datum] ne "")) {
			$data_list[$this_datum] =~ s/\\/\\\\/g;
			$data_list[$this_datum] =~ s/\</\\\</g;
			$data_list[$this_datum] =~ s/\>/\\\>/g;
			$data_list[$this_datum] =~ s/\'/\\\'/g;
			$data_list[$this_datum] =~ s/\`/\\\`/g;
			if ($this_datum == $FLAG_NAME) {
				$tmp_string = $data_list[$FLAG_BASE_NAME];
				print $OUT_FH " <Para\n";
				print $OUT_FH "  <PgfTag `ADF_Start'>\n";
				print $OUT_FH "  <ParaLine\n";
				print $OUT_FH "   <String `$DataNameList[$this_datum]'>\n";
				print $OUT_FH "  > # end ParaLine\n";
				print $OUT_FH " > # end Para\n";
				print $OUT_FH " <Para\n";
				print $OUT_FH "  <PgfTag `ADF_Name'>\n";
				print $OUT_FH "  <ParaLine\n";
				print $OUT_FH $start_index_range;
				print $OUT_FH "   <Marker <MType 8> <MText `newlink ",
					join("'>>\n   <Marker <MType 8> <MText `newlink ",
					split(/\n/, $data_list[$FLAG_PUBLISH_NAME])), "'>>\n";
				print $OUT_FH "   <Marker <MType 9> <MText `",
					join("'>>\n   <Marker <MType 9> <MText `",
					split(/\n/, $data_list[$FLAG_PUBLISH_XREF])), "'>>\n";
				print $OUT_FH &ADF_ApplyFrameFormats(split(/\n/,
					$data_list[$this_datum]));
				print $OUT_FH " > # end Para\n";
				next;
			}
			print $OUT_FH " <Para\n";
			print $OUT_FH "  <PgfTag `ADF_Section'>\n";
			print $OUT_FH "  <ParaLine\n";
			print $OUT_FH "   <String `$DataNameList[$this_datum]'>\n";
			print $OUT_FH "  > # end ParaLine\n";
			print $OUT_FH " > # end Para\n";
			@this_section = split(/\n/, $data_list[$this_datum]);
			$section_line = 0;
			$line_flag    = "";
			for ($this_line = 0; $this_line <= $#this_section; $this_line++) {
				$wrap_line = $this_section[$this_line];
				if ($this_datum == $FLAG_CODE_SYNTAX) {
					$wrap_line =~ s/^\s+|\s+$//g;
					&ADF_wraptext($data_list[$FLAG_TAB_SETTING], 75, $wrap_line);
					$wrap_line =~ s/ /\\x4 /g;
					$wrap_line =~ s/\n/\\x09 /g;
					print $OUT_FH " <Para\n";
					print $OUT_FH "  <PgfTag `ADF_IN0S'>\n";
					print $OUT_FH ((!$#this_section) || (!$section_line)) ?
						"  <PgfTopSeparator `ADF_LN_0'>\n" : "";
					print $OUT_FH ($section_line == $#this_section) ?
						"  <PgfBotSeparator `ADF_LN_0'>\n" : "";
					print $OUT_FH "  <PgfLIndent 0.500>\n";
					print $OUT_FH "  <PgfAlignment Left>\n";
					print $OUT_FH ((!$section_line) && $#this_section) ?
						"  <PgfSpBefore  0.0 pt>\n  <PgfSpAfter  5.0 pt>\n" :
						"  <PgfSpBefore  0.0 pt>\n  <PgfSpAfter  0.0 pt>\n";
					print $OUT_FH "  <PgfHyphenate No>\n";
					print $OUT_FH "  <HyphenMaxLines 1>\n";
					print $OUT_FH "  <HyphenMinPrefix 500>\n";
					print $OUT_FH "  <HyphenMinSuffix 500>\n";
					print $OUT_FH "  <HyphenMinWord 100>\n";
					print $OUT_FH "  <PgfLetterSpace No>\n";
					print $OUT_FH "  <PgfMinWordSpace 100>\n";
					print $OUT_FH "  <PgfOptWordSpace 100>\n";
					print $OUT_FH "  <PgfMaxWordSpace 100>\n";
					print $OUT_FH "  <PgfLanguage None>\n";
					print $OUT_FH "  <ParaLine\n";
					foreach $split_line (split(/\n/, $wrap_line)) {
						print $OUT_FH "   <String `$split_line'>\n";
					}
					print $OUT_FH "  > # end ParaLine\n";
					print $OUT_FH " > # end Para\n";
				}
				elsif ($this_datum == $FLAG_SEE_ALSO) {
					foreach $this_xref (split(/\n/, $wrap_line)) {
						print $OUT_FH " <Para\n";
						print $OUT_FH "  <PgfTag `ADF_IN0N'>\n";
						print $OUT_FH "  <ParaLine\n";
						print $OUT_FH "   <Marker\n";
						print $OUT_FH "    <MType 8>\n";
						print $OUT_FH "    <MText `gotolink $this_xref'>\n";
						print $OUT_FH "   > # end Marker\n";
						print $OUT_FH "   <XRef\n";
						print $OUT_FH "    <XRefName `Name_X_Ref'>\n";
						print $OUT_FH "    <XRefSrcText `$this_xref'>\n";
						if ($in_hyper_name_array{$this_xref} ne "") {
							print $OUT_FH "    <XRefSrcFile `",
								$in_hyper_name_array{$this_xref}, "'>\n";
						}
						else {
							print $OUT_FH "    <XRefSrcFile `'>\n";
						}
						print $OUT_FH "   > # end XRef\n";
						print $OUT_FH "  > # end ParaLine\n";
						print $OUT_FH " > # end Para\n";
					}
				}
				elsif ($this_datum == $FLAG_CODE_EXAMPLES) {
					&ADF_tabtospc($wrap_line, $data_list[$FLAG_TAB_SETTING]);
					$wrap_line =~ s/ /\\x4 /g;
					$wrap_line =~ s/^\s*$/\\x4 /;
					print $OUT_FH " <Para\n";
					print $OUT_FH "  <PgfTag `$para_name'>\n";
					print $OUT_FH ((!$#this_section) || (!$section_line)) ?
						"  <PgfTopSeparator `ADF_LN_0'>\n" : "";
					print $OUT_FH ($section_line == $#this_section) ?
						"  <PgfBotSeparator `ADF_LN_0'>\n" : "";
					print $OUT_FH "  <PgfAlignment Left>\n";
					print $OUT_FH "  <PgfSpBefore  0.0 pt>\n";
					print $OUT_FH "  <PgfSpAfter  0.0 pt>\n";
					print $OUT_FH "  <PgfHyphenate No>\n";
					print $OUT_FH "  <HyphenMaxLines 1>\n";
					print $OUT_FH "  <HyphenMinPrefix 500>\n";
					print $OUT_FH "  <HyphenMinSuffix 500>\n";
					print $OUT_FH "  <HyphenMinWord 1000>\n";
					print $OUT_FH "  <PgfLetterSpace No>\n";
					print $OUT_FH "  <PgfMinWordSpace 100>\n";
					print $OUT_FH "  <PgfOptWordSpace 100>\n";
					print $OUT_FH "  <PgfMaxWordSpace 100>\n";
					print $OUT_FH "  <PgfLanguage None>\n";
					print $OUT_FH "  <ParaLine\n";
					print $OUT_FH "   <String `$wrap_line'>\n";
					print $OUT_FH "  > # end ParaLine\n";
					print $OUT_FH " > # end Para\n";
				}
				else {
					$para_name     = "ADF_IN0N";
					$para_modifier = "";
					if (substr($wrap_line, 0, length($ADF_ParaFormatSig)) eq
						$ADF_ParaFormatSig) {
						$tmp_format   =  substr($wrap_line,
							length($ADF_ParaFormatSig), $ADF_ParaFormatLength);
						$wrap_line    =  substr($wrap_line,
							length($ADF_ParaFormatSig) + $ADF_ParaFormatLength,
							length($wrap_line));
						@tmp_array    = split(/\|/, $tmp_format);
						if ($tmp_array[0] eq "LN") {
							print $OUT_FH " <Para\n";
							print $OUT_FH "  <PgfTag `$para_name'>\n";
							print $OUT_FH
								"  <PgfTopSeparator `ADF_LN_$tmp_array[1]'>\n";
							print $OUT_FH "  <PgfSpBefore  0.0 pt>\n";
							print $OUT_FH "  <PgfSpAfter  0.0 pt>\n";
							print $OUT_FH "  <PgfLeading  0.0 pt>\n";
							print $OUT_FH "  <PgfFont <FSize 4.0 pt>>\n";
							print $OUT_FH "  <ParaLine>\n";
							print $OUT_FH " > #end Para\n";
							next;
						}
						else {
							$para_name    = "ADF_".$tmp_array[0].$tmp_array[1].
								substr($tmp_array[3], 0, 1);
							if ($tmp_array[0] eq "NM") {
								$wrap_line = sprintf("\t%u\t",
									$tmp_array[2]).$wrap_line;
							}
							if ($tmp_array[4] ne "YES") {
								$para_modifier =
									"  <PgfAlignment Left>\n".
									"  <PgfSpBefore  0.0 pt>\n".
									"  <PgfSpAfter  0.0 pt>\n".
									"  <PgfHyphenate No>\n".
									"  <HyphenMaxLines 1>\n".
									"  <HyphenMinPrefix 500>\n".
									"  <HyphenMinSuffix 500>\n".
									"  <HyphenMinWord 100>\n".
									"  <PgfLetterSpace No>\n".
									"  <PgfMinWordSpace 100>\n".
									"  <PgfOptWordSpace 100>\n".
									"  <PgfMaxWordSpace 100>\n".
									"  <PgfLanguage None>\n";
							}
						}
					}
					&ADF_tabtospc($wrap_line, $data_list[$FLAG_TAB_SETTING]);
					print $OUT_FH " <Para\n";
					print $OUT_FH "  <PgfTag `$para_name'>\n";
					print $OUT_FH $para_modifier;
					print $OUT_FH "  <ParaLine\n";
					print $OUT_FH &ADF_ApplyFrameFormats(split(/\n/, $wrap_line));
					print $OUT_FH " > # end Para\n";
					$line_flag = "";
				}
				$section_line++;
			}
		}
	}

	if ($end_index_range ne "") {
		print $OUT_FH " <Para\n";
		print $OUT_FH "  <PgfTag `ADF_IN0N'>\n";
		print $OUT_FH "  <ParaLine\n";
		print $OUT_FH $end_index_range;
		print $OUT_FH "  > # end ParaLine\n";
		print $OUT_FH " > # end Para\n";
	}

	return($return_code);
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_CreateFrameIndexEntries {
	local($index_component, $index_type, $in_start_index, $in_end_index) = @_;
	local($index_line, $tmp_line);

	$in_start_index = "";
	$in_end_index   = "";

	if ($index_component !~ /^\s*$/) {
		$index_component =~ s/\<\$nopage\>/\0010/g;
		$index_component =~ s/\\/\\\\/g;
		$index_component =~ s/(\<|\>|\'|\`|\;)/\\\1/g;
		$index_component =~ s/\001B/\\\<bold\\\>/g;
		$index_component =~ s/\001b/\\\<nobold\\\>/g;
		$index_component =~ s/\001I/\\\<italic\\\>/g;
		$index_component =~ s/\001i/\\\<noitalic\\\>/g;
		$index_component =~ s/\001U/\\\<underline\\\>/g;
		$index_component =~ s/\001u/\\\<nounderline\\\>/g;
		foreach $index_line (sort(&do_uniq(split(/\n/, $index_component)))) {
			if ($index_line !~ /^\s*$/) {
				$tmp_line =  $index_line;
				$tmp_line =~ s/^\s+|\s+$//g;
				$tmp_line =~ s/\s+/ /g;
#				$tmp_line =~ s/\[|\]|\:|\;/\\\1/g;	# Escape special index chars
				if (substr($tmp_line, 0, length($ADF_ParaFormatSig)) eq
					$ADF_ParaFormatSig) {
					substr($tmp_line, 0, length($ADF_ParaFormatSig) +
						$ADF_ParaFormatLength) = "";
				}
				if ($tmp_line =~ /\0010/) {
					$tmp_line        =~ s/\0010/\\\<\$nopage\\\>/g;
					$tmp_line        =~ s/\001.//g;
					$in_start_index .=  "   <Marker <MType $index_type> ".
						"<MText `$tmp_line'>>\n";
				}
				else {
					$tmp_line        =~ s/\001.//g;
					$in_start_index .=  "   <Marker <MType $index_type> ".
						"<MText `$tmp_line \\<\$startrange\\>'>>\n";
					$in_end_index   .=  "   <Marker <MType $index_type> ".
						"<MText `$tmp_line \\<\$endrange\\>'>>\n";
				}
			}
		}
	}

	$_[2] = $in_start_index;
	$_[3] = $in_end_index;
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_ApplyFrameFormats {
	local(@split_list) = @_;
	local($first_flag, $out_line, $split_line, $char_format,
		$char_format_index, $tab_index, $other_ref);

	$first_flag = 1;

	foreach $split_line (@split_list) {
		$out_line   .= ($first_flag) ? "" : "  <ParaLine\n";
		$first_flag  = 0;
		while ($split_line ne "") {
			while ($split_line =~ /^\001(.)/) {
				$char_format = $1;
				if ($char_format eq "H") {
					$other_ref   = substr($split_line, 2, index($split_line,
						"\001h", 2) - 2);
					$split_line  = substr($split_line, length($other_ref) + 2);
					$split_line  = $split_line;
					$out_line   .= "   <Font <FTag `HyperText_Ref'>>\n".
						"   <Marker <MType 8> <MText `gotolink $other_ref'>>\n".
						"   <String `$other_ref'>\n".
						"   <Font <FTag `NoHyperText_Ref'>>\n";
				}
				elsif (($char_format eq "N") || ($char_format eq "n")) {
				}
				elsif ($char_format eq "X") {
					$other_ref   =  substr($split_line, 2, index($split_line,
						"\001x", 2) - 2);
					# Escape special index marker characters . . .
					$split_line  =  substr($split_line, length($other_ref) + 2);
					$other_ref   =~ s/\[|\]|\:|\;/\\\1/g;
					$split_line  =  $split_line;
					$out_line   .=  "   <Marker <MType 2> <MText `$other_ref'>>\n".
						"   <String `$other_ref'>\n";
				}
				elsif (index("hnx", $char_format) == -1) {
					$out_line .= "   ".$ADF_FrameCharFormatSpecs{$char_format}."\n";
				}
				$split_line = substr($split_line, 2);
			}
			if ($split_line ne "") {
				$char_format_index = index($split_line, "\001");
				$tab_index         = index($split_line, "\t");
				if (($char_format_index == -1) && ($tab_index == -1)) {
					$out_line   .= "   <String `$split_line'>\n";
					$split_line  = "";
				}
				elsif (substr($split_line, 0, 1) eq "\t") {
					$out_line                                  .= "   <Char Tab>\n";
					substr($split_line, 0, 1)                   = "";
				}
				else {
					$char_format_index                          =
						($tab_index == -1) ? $char_format_index : $tab_index;
					$out_line                                  .= "   <String `".
						substr($split_line, 0, $char_format_index)."'>\n";
					substr($split_line, 0, $char_format_index)  = "";
				}
			}
		}
		# ###################################################	#
		# ###################################################	#
		#    We do the following because of a strange Frame	#
		# Maker bug in versions 3.0X and prior. If every		#
		# character in a paragraph has the same character		#
		# format, a 'Use Formats...' command which includes	#
		# paragraph formats will hide the character format		#
		# characteristics.												#
		#																		#
		#    Hence, at the end of every paragraph which has	#
		# character formats, we reset the all character			#
		# formats to their default value, and append a space.	#
		# ###################################################	#
		$out_line .= $ADF_FrameCharFormatsOff;
		$out_line .= "   <String ` '>\n";
		# ###################################################	#
		$out_line .= "  > # end ParaLine\n";
	}

	$out_line = ($#split_list == -1) ? "  > # end ParaLine\n" : $out_line;

	return($out_line);
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub do_uniq {
	local(%done_elements_list);
	grep(!$done_elements_list{$_}++, @_);
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub do_untaint {
	local($variable_to_untaint) = @_;
 
	$variable_to_untaint =~ s/\n/\377/g;
	$variable_to_untaint =~ s/^(.*)$/\1/;
	$variable_to_untaint =  $1;
	$variable_to_untaint =~ s/\377/\n/g;
 
	return($variable_to_untaint);
}
# ###########################################################################

# ###########################################################################
sub ADF_wraptext {
	local($in_tab_setting, $max_length, $in_string) = @_;
	local($adj_length, @work_lines, @new_lines, $this_one, $tmp_string,
		$tmp_length, $this_length, $last_space, $last_punct, $last_nword,
		$last_cmark, $count_1, $tmp_char);

	$max_length = ($max_length < 3) ? 3 : $max_length;
	$adj_length = $max_length / 1.1;
	@work_lines = split(/\n/, $in_string);
	@new_lines  = ();

	grep(do { $_ =~ s/\s+$//g; 0; }, @work_lines);

	for $this_one (@work_lines) {
		$tmp_string =  &ADF_tabtospc($this_one, $in_tab_setting);
		$tmp_string =~ s/\001.//g;
		$tmp_length =  length($tmp_string);
		if (($tmp_length = length($tmp_string)) <= $max_length) {
			push(@new_lines, $this_one);
		}
		else {
			while ($tmp_length > $max_length) {
				$this_length =  length($this_one);
				$last_space  =  -1;
				$last_punct  =  -1;
				$last_nword  =  -1;
				$last_cmark  =  -1;
				for ($count_1 = 0; $count_1 < $max_length; $count_1++) {
					$tmp_char = substr($this_one, $count_1, 1);
					if ($tmp_char eq "\001") {
						$count_1++;
						next;
					}
					elsif ($tmp_char eq " ") {
						$last_space = $count_1;
					}
					elsif (index(",;:.?!-", $tmp_char) > -1) {
						$last_punct = $count_1;
					}
					elsif ($tmp_char =~ /\W/) {
						$last_nword = $count_1;
					}
					if ($tmp_char eq "\001") {
						$last_cmark = $count_1;
					}
				}
				if (($last_space == -1) && ($last_punct == -1) &&
					($last_nword == -1)) {
					if ($last_cmark > -1) {
						push(@new_lines, substr($this_one, 0, $last_cmark));
						$this_one = substr($this_one, $last_cmark, $this_length);
					}
					else {
						push(@new_lines, substr($this_one, 0, $adj_length));
						$this_one = substr($this_one, $adj_length, $this_length);
					}
				}
				elsif (($last_space == -1) && ($last_punct == -1) &&
					($last_nword > -1)) {
					push(@new_lines, substr($this_one, 0, $last_nword));
					$this_one = substr($this_one, $last_nword, $this_length);
				}
				elsif ($last_space > $last_punct) {
					push(@new_lines, substr($this_one, 0, $last_space));
					$this_one = substr($this_one, $last_space + 1, $this_length);
				}
				else {
					push(@new_lines, substr($this_one, 0, $last_punct + 1));
					$this_one = substr($this_one, $last_punct + 1, $this_length);
				}
				$this_one    =~ s/^\s+|\s+$//g;
				$tmp_string  =  $this_one; 
				$tmp_string  =~ s/\001.//g;
				$tmp_length  =  length($tmp_string);
				if ($tmp_length <= $max_length) {
					push(@new_lines, $this_one);
					last;
				}
			}
		}
	}

	grep(do { $_ =~ s/\s+$//g; }, @new_lines);
	$in_string   = join("\n", @new_lines);
	$_[2]        = $in_string;

	return($in_string);
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_tabtospc {
	local($in_string, $tab_setting) = @_;
	local($current_col);

	if ($tab_setting < 0) {
		$in_string = "";
	}
	elsif (!$tab_setting) {
		$in_string =~ s/\t//g;
	}
	elsif ($tab_setting == 1) {
		$in_string =~ s/\t/ /g;
	}
	else {
		while (($current_col = index($in_string, "\t", 0)) > -1) {
			substr($in_string, $current_col, 1) =
				" " x ($tab_setting - ($current_col % $tab_setting));
		}
		$_[0] = $in_string;
	}

	return($in_string);
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_IgnoreCaseCompare {
	local($tmp_a, $tmp_b);

	$tmp_a =  $a;
	$tmp_a =~ y/[a-z]/[A-Z]/;
	$tmp_b =  $b;
	$tmp_b =~ y/[a-z]/[A-Z]/;

	return($a <=> $b);
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
#
#    NAME      :	
#
#    SYNOPSIS  :	
#
#    PARAMETERS:	
#
#    RETURNS	:	
#
#    NOTE(S)   :	
#
# ###########################################################################
sub ADF_GetDateTime {
	$_[0] = $_[1] = $_[2] = "";
	&ADF_FormatDateTime(time(), $_[0], $_[1], $_[2]);
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
#
#    NAME      :	
#
#    SYNOPSIS  :	
#
#    PARAMETERS:	
#
#    RETURNS	:	
#
#    NOTE(S)   :	
#
# ###########################################################################
sub ADF_FormatDateTime {
	local($in_time_seconds) = @_;
	local(@time_array);

	@time_array = localtime($in_time_seconds);
	$_[1]       = sprintf("%04.04u-%02.02u-%02.02u",
		$time_array[5] + 1900, $time_array[4] + 1, $time_array[3]);
	$_[2]       = sprintf("%02.02u:%02.02u:%02.02u",
		$time_array[2], $time_array[1], $time_array[0]);
	$_[3]       = sprintf("%04.04u%02.02u%02.02u%02.02u%02.02u%02.02u",
		$time_array[5] + 1900, $time_array[4] + 1, $time_array[3],
		$time_array[2], $time_array[1], $time_array[0]);
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_InitDataTypes {

	# #####################################################################	#
	# #####################################################################	#
	#    Input type is '.c' . . .
	# #####################################################################	#
	$FileTypeList{"c"}   = "C";
	$FileTypeList{"cc"}  = "C";
	$FileTypeList{"c++"} = "C";
	$FileTypeList{"cxx"} = "C";
	$FileTypeList{"cpp"} = "C";
	$C_EmptyLinePattern  = "^\\s*\$";
	$C_BOH_Pattern       = "^\\s*\\/\\*\\s+BOH";
	$C_EOH_Pattern       = "^EOH\\s+\\*/";
	$C_BOL_StripPattern  = "";
	$C_EOL_StripPattern  = "";
	@C_NeededData        = (
		"BASE_NAME        FLAG_BASE_NAME        N Y Y Y Y N N ".
			"^\\s*BASE\\s+NAME\\s*:\\s*",
		"Name             FLAG_NAME             Y Y Y Y Y Y Y ".
			"^\\s*NAME\\s*:\\s*",
		"Synopsis         FLAG_CODE_SYNTAX      Y Y Y Y N N N ".
			"^\\s*SYNOPSIS\\s*:\\s*",
		"Description      FLAG_DESCRIPTION      Y Y Y Y Y Y Y ".
			"^\\s*DESCRIPTION\\s*:\\s*",
		"Parameters       FLAG_PARAMETERS       N Y Y Y Y Y Y ".
			"^\\s*PARAMETERS?\\s*:\\s*|".
			"^\\s*PARAMETER\\(S\\)\\s*:\\s*",
		"Returns          FLAG_RETURNS          Y Y Y Y Y Y Y ".
			"^\\s*RETURNS?\\s*:\\s*|".
			"^\\s*RETURN\\(S\\)\\s*:\\s*",
		"Environment      FLAG_ENVIRONMENT      N Y Y Y Y Y Y ".
			"^\\s*ENVIRONMENTS?\\s*:\\s*|".
			"^\\s*ENVIRONMENT\\(S\\)\\s*:\\s*|".
			"^\\s*ENVIRONMENT\\s+VARIABLES?\\s*:\\s*|".
			"^\\s*ENVIRONMENT\\s+VARIABLE\\(S\\)\\s*:\\s*",
		"Notes            FLAG_NOTES            N Y Y Y Y Y Y ".
			"^\\s*NOTES?\\s*:\\s*|".
			"^\\s*NOTE\\(S\\)\\s*:\\s*|".
			"^\\s*COMMENTS?\\s*:\\s*|".
			"^\\s*COMMENT\\(S\\)\\s*:\\s*",
		"Caveats          FLAG_CAVEATS          N Y Y Y Y Y Y ".
			"^\\s*CAVEATS?\\s*:\\s*|".
			"^\\s*CAVEAT\\(S\\)\\s*:\\s*|".
			"^\\s*CAUTIONS?\\s*:\\s*|".
			"^\\s*CAUTION\\(S\\)\\s*:\\s*|".
			"^\\s*WARNINGS?\\s*:\\s*|".
			"^\\s*WARNING\\(S\\)\\s*:\\s*|".
			"^\\s*DANGERS?\\s*:\\s*|".
			"^\\s*DANGER\\(S\\)\\s*:\\s*",
		"See_Also         FLAG_SEE_ALSO         N N Y Y Y N N ".
			"^\\s*SEE\\s+ALSO\\s*:\\s*",
		"Examples         FLAG_EXAMPLES         N Y Y Y N Y Y ".
			"^\\s*EXAMPLES?\\s*:\\s*|".
			"^\\s*EXAMPLE\\(S\\)\\s*:\\s*",
		"Code_Examples     FLAG_CODE_EXAMPLES   N N N N N N N ".
			"^\\s*CODE\\s+EXAMPLES?\\s*:\\s*|".
			"^\\s*CODE\\s+EXAMPLE\\(S\\)\\s*:\\s*",
		"Authors          FLAG_AUTHORS          N Y Y Y Y Y Y ".
			"^\\s*AUTHORS?\\s*:\\s*|".
			"^\\s*AUTHOR\\(S\\)\\s*:\\s*|".
			"^\\s*PROGRAMMERS?\\s*:\\s*|".
			"^\\s*PROGRAMMER\\(S\\)\\s*:\\s*|".
			"^\\s*AUTHORED\\s+BY\\s*:\\s*|".
			"^\\s*PROGRAMMED\\s+BY\\s*:\\s*|".
			"^\\s*WRITTEN\\s+BY\\s*:\\s*|".
			"^\\s*CREATED\\s+BY\\s*:\\s*",
		"Copyrights       FLAG_COPYRIGHTS       N Y Y Y Y Y Y ".
			"^\\s*COPYRIGHTS?\\s*:\\s*|".
			"^\\s*COPYRIGHT\\(S\\)\\s*:\\s*|".
			"^\\s*COPYRIGHTED\\s+BY\\s*:\\s*",
		"Source_File_Name FLAG_SOURCE_FILE_NAME N N Y Y Y N N ".
			"^\\s*SOURCES?\\s*:\\s*|".
			"^\\s*SOURCE\\(S\\)\\s*:\\s*|".
			"^\\s*SOURCE\\s+FILES?\\s*:\\s*|".
			"^\\s*SOURCE\\s+FILE\\(S\\)\\s*:\\s*|".
			"^\\s*SOURCE\\s+NAMES?\\s*:\\s*|".
			"^\\s*SOURCE\\s+NAME\\(S\\)\\s*:\\s*|".
			"^\\s*SOURCE\\s+FILE\\s+NAMES?\\s*:\\s*|".
			"^\\s*SOURCE\\s+FILE\\s+NAME\\(S\\)\\s*:\\s*",
		"Source_File_Date FLAG_SOURCE_FILE_DATE N N Y Y Y N N ".
			"^\\s*DATES?\\s*:\\s*|".
			"^\\s*DATE\\(S\\)\\s*:\\s*|".
			"^\\s*SOURCE\\s+DATES?\\s*:\\s*|".
			"^\\s*SOURCE\\s+DATE\\(S\\)\\s*:\\s*|".
			"^\\s*SOURCE\\s+FILE\\s+DATES?\\s*:\\s*|".
			"^\\s*SOURCE\\s+FILE\\s+DATE\\(S\\)\\s*:\\s*",
		"OUTPUT_INDEX     FLAG_OUTPUT_INDEX     N N Y Y Y N N ".
			"^\\s*INDEXS?\\s*:\\s*|".
			"^\\s*INDEX\\(S\\)\\s*:\\s*|".
			"^\\s*INDICES\\s*:\\s*|".
			"^\\s*OUTPUT\\s+INDEXS?\\s*:\\s*|".
			"^\\s*OUTPUT\\s+INDEX\\(S\\)\\s*:\\s*|".
			"^\\s*OUTPUT\\s+INDICES\\s*:\\s*",
		"PUBLISH_XREF    FLAG_PUBLISH_XREF    N N Y Y Y N N ".
			"^\\s*PUBLISH\\s+XREFS?\\s*:\\s*",
		"PUBLISH_NAME    FLAG_PUBLISH_NAME    N N Y Y Y N N ".
			"^\\s*PUBLISH\\s+NAMES?\\s*:\\s*"
	);
	&ADF_InitParseData("C", "C_DataNameList", "C_DataFlagList",
		"C_DataRequiredList", "C_DataWrapList", "C_DataLTrimList",
		"C_DataRTrimList", "C_DataSqueezeList", "C_ParaFormatList",
		"C_CharFormatList", "C_DataPatternList", "C_DataExcludeList",
		"C_DataComponentList", "C_DataOrderList", $C_EOH_Pattern,
		@C_NeededData);
	# #####################################################################	#

	# #####################################################################	#
	# #####################################################################	#
	#    Input file type is '.pl' . . .
	# #####################################################################	#
	$FileTypeList{"pl"}  = "PL";
	$PL_EmptyLinePattern = "^\\s*\$|^\\s*#\\s*\$";
	$PL_BOH_Pattern      = "^\\s*\\#\\s+BOH";
	$PL_EOH_Pattern      = "^\\s*\\#\\s+EOH";
	$PL_BOL_StripPattern = "^\\s*#";
	$PL_EOL_StripPattern = "";
	@PL_NeededData       = (
		"BASE_NAME   FLAG_BASE_NAME     N Y Y Y Y N N ".
			"^\\s*\\#\\s*BASE\\s+NAME\\s*:\\s*",
		"Name        FLAG_NAME          Y Y Y Y Y Y Y ".
			"^\\s*\\#\\s*NAME\\s*:\\s*",
		"Synopsis    FLAG_CODE_SYNTAX   Y Y Y Y N N N ".
			"^\\s*\\#\\s*SYNOPSIS\\s*:\\s*",
		"Description FLAG_DESCRIPTION   Y Y Y Y Y Y Y ".
			"^\\s*\\#\\s*DESCRIPTION\\s*:\\s*",
		"Parameters  FLAG_PARAMETERS    N Y Y Y Y Y Y ".
			"^\\s*\\#\\s*PARAMETERS?\\s*:\\s*|".
			"^\\s*\\#\\s*PARAMETER\\(S\\)\\s*:\\s*",
		"Returns     FLAG_RETURNS       Y Y Y Y Y Y Y ".
			"^\\s*\\#\\s*RETURNS?\\s*:\\s*|".
			"^\\s*\\#\\s*RETURN\\(S\\)\\s*:\\s*",
		"Environment FLAG_ENVIRONMENT   N Y Y Y Y Y Y ".
			"^\\s*\\#\\s*ENVIRONMENTS?\\s*:\\s*|".
			"^\\s*\\#\\s*ENVIRONMENT\\(S\\)\\s*:\\s*|".
			"^\\s*\\#\\s*ENVIRONMENT\\s+VARIABLES?\\s*:\\s*|".
			"^\\s*\\#\\s*ENVIRONMENT\\s+VARIABLE\\(S\\)\\s*:\\s*",
		"Notes       FLAG_NOTES         N Y Y Y Y Y Y ".
			"^\\s*\\#\\s*NOTES?\\s*:\\s*|".
			"^\\s*\\#\\s*NOTE\\(S\\)\\s*:\\s*|".
			"^\\s*\\#\\s*COMMENTS?\\s*:\\s*|".
			"^\\s*\\#\\s*COMMENT\\(S\\)\\s*:\\s*",
		"Caveats     FLAG_CAVEATS       N Y Y Y Y Y Y ".
			"^\\s*\\#\\s*CAVEATS?\\s*:\\s*|".
			"^\\s*\\#\\s*CAVEAT\\(S\\)\\s*:\\s*|".
			"^\\s*\\#\\s*CAUTIONS?\\s*:\\s*|".
			"^\\s*\\#\\s*CAUTION\\(S\\)\\s*:\\s*|".
			"^\\s*\\#\\s*WARNINGS?\\s*:\\s*|".
			"^\\s*\\#\\s*WARNING\\(S\\)\\s*:\\s*|".
			"^\\s*\\#\\s*DANGERS?\\s*:\\s*|".
			"^\\s*\\#\\s*DANGER\\(S\\)\\s*:\\s*",
		"See_Also    FLAG_SEE_ALSO      N N Y Y Y N N ".
			"^\\s*\\#\\s*SEE\\s+ALSO\\s*:\\s*",
		"Examples    FLAG_EXAMPLES      N Y Y Y N Y Y ".
			"^\\s*\\#\\s*EXAMPLES?\\s*:\\s*|".
			"^\\s*\\#\\s*EXAMPLE\\(S\\)\\s*:\\s*",
		"Code_Examples     FLAG_CODE_EXAMPLES   N N N N N N N ".
			"^\\s*\\#\\s*CODE\\s+EXAMPLES?\\s*:\\s*|".
			"^\\s*\\#\\s*CODE\\s+EXAMPLE\\(S\\)\\s*:\\s*",
		"Authors     FLAG_AUTHORS               N Y Y Y Y Y Y ".
			"^\\s*\\#\\s*AUTHORS?\\s*:\\s*|".
			"^\\s*\\#\\s*AUTHOR\\(S\\)\\s*:\\s*|".
			"^\\s*\\#\\s*PROGRAMMERS?\\s*:\\s*|".
			"^\\s*\\#\\s*PROGRAMMER\\(S\\)\\s*:\\s*|".
			"^\\s*\\#\\s*AUTHORED\\s+BY\\s*:\\s*|".
			"^\\s*\\#\\s*PROGRAMMED\\s+BY\\s*:\\s*|".
			"^\\s*\\#\\s*WRITTEN\\s+BY\\s*:\\s*|".
			"^\\s*\\#\\s*CREATED\\s+BY\\s*:\\s*",
		"Copyrights  FLAG_COPYRIGHTS            N Y Y Y Y Y Y ".
			"^\\s*\\#\\s*COPYRIGHTS?\\s*:\\s*|".
			"^\\s*\\#\\s*COPYRIGHT\\(S\\)\\s*:\\s*|".
			"^\\s*\\#\\s*COPYRIGHTED\\s+BY\\s*:\\s*",
		"Source_File_Name FLAG_SOURCE_FILE_NAME N N Y Y Y N N ".
			"^\\s*\\#\\s*SOURCES?\\s*:\\s*|".
			"^\\s*\\#\\s*SOURCE\\(S\\)\\s*:\\s*|".
			"^\\s*\\#\\s*SOURCE\\s+FILES?\\s*:\\s*|".
			"^\\s*\\#\\s*SOURCE\\s+FILE\\(S\\)\\s*:\\s*|".
			"^\\s*\\#\\s*SOURCE\\s+NAMES?\\s*:\\s*|".
			"^\\s*\\#\\s*SOURCE\\s+NAME\\(S\\)\\s*:\\s*|".
			"^\\s*\\#\\s*SOURCE\\s+FILE\\s+NAMES?\\s*:\\s*|".
			"^\\s*\\#\\s*SOURCE\\s+FILE\\s+NAME\\(S\\)\\s*:\\s*",
		"Source_File_Date FLAG_SOURCE_FILE_DATE N N Y Y Y N N ".
			"^\\s*\\#\\s*DATES?\\s*:\\s*|".
			"^\\s*\\#\\s*DATE\\(S\\)\\s*:\\s*|".
			"^\\s*\\#\\s*SOURCE\\s+DATES?\\s*:\\s*|".
			"^\\s*\\#\\s*SOURCE\\s+DATE\\(S\\)\\s*:\\s*|".
			"^\\s*\\#\\s*SOURCE\\s+FILE\\s+DATES?\\s*:\\s*|".
			"^\\s*\\#\\s*SOURCE\\s+FILE\\s+DATE\\(S\\)\\s*:\\s*",
		"OUTPUT_INDEX     FLAG_OUTPUT_INDEX     N N Y Y Y N N ".
			"^\\s*\\#\\s*INDEXS?\\s*:\\s*|".
			"^\\s*\\#\\s*INDEX\\(S\\)\\s*:\\s*|".
			"^\\s*\\#\\s*INDICES\\s*:\\s*|".
			"^\\s*\\#\\s*OUTPUT\\s+INDEXS?\\s*:\\s*|".
			"^\\s*\\#\\s*OUTPUT\\s+INDEX\\(S\\)\\s*:\\s*|".
			"^\\s*\\#\\s*OUTPUT\\s+INDICES\\s*:\\s*",
		"PUBLISH_XREF    FLAG_PUBLISH_XREF    N N Y Y Y N N ".
			"^\\s*\\#\\s*PUBLISH\\s+XREFS?\\s*:\\s*",
		"PUBLISH_NAME    FLAG_PUBLISH_NAME    N N Y Y Y N N ".
			"^\\s*\\#\\s*PUBLISH\\s+NAMES?\\s*:\\s*"
	);
	&ADF_InitParseData("PL", "PL_DataNameList", "PL_DataFlagList",
		"PL_DataRequiredList", "PL_DataWrapList", "PL_DataLTrimList",
		"PL_DataRTrimList", "PL_DataSqueezeList", "PL_ParaFormatList",
		"PL_CharFormatList", "PL_DataPatternList", "PL_DataExcludeList",
		"PL_DataComponentList", "PL_DataOrderList", $PL_EOH_Pattern,
		@PL_NeededData);
	# #####################################################################	#

	# #####################################################################	#
	# #####################################################################	#
	#    Input type is '.h' . . .
	# #####################################################################	#
	$FileTypeList{"h"}   = "H";
	$FileTypeList{"hh"}  = "H";
	$FileTypeList{"h++"} = "H";
	$FileTypeList{"hxx"} = "H";
	$FileTypeList{"hpp"} = "H";
	$H_EmptyLinePattern  = "^\\s*\$";
	$H_BOH_Pattern       = "^\\s*\\/\\*\\s+BOH";
	$H_EOH_Pattern       = "^EOH\\s+\\*/";
	$H_BOL_StripPattern  = "";
	$H_EOL_StripPattern  = "";
	@H_NeededData        = (
		"BASE_NAME   FLAG_BASE_NAME     N Y Y Y Y N N ".
			"^\\s*BASE\\s+NAME\\s*:\\s*",
		"Name        FLAG_NAME          Y Y Y Y Y Y Y ".
			"^\\s*NAME\\s*:\\s*",
		"Description FLAG_DESCRIPTION   Y Y Y Y Y Y Y ".
			"^\\s*DESCRIPTION\\s*:\\s*",
		"Members     FLAG_MEMBERS       N Y Y Y Y Y Y ".
			"^\\s*MEMBERS?\\s*:\\s*|".
			"^\\s*MEMBER\\(S\\)\\s*:\\s*",
		"Notes       FLAG_NOTES         N Y Y Y Y Y Y ".
			"^\\s*NOTES?\\s*:\\s*|".
			"^\\s*NOTE\\(S\\)\\s*:\\s*|".
			"^\\s*COMMENTS?\\s*:\\s*|".
			"^\\s*COMMENT\\(S\\)\\s*:\\s*",
		"Caveats     FLAG_CAVEATS       N Y Y Y Y Y Y ".
			"^\\s*CAVEATS?\\s*:\\s*|".
			"^\\s*CAVEAT\\(S\\)\\s*:\\s*|".
			"^\\s*CAUTIONS?\\s*:\\s*|".
			"^\\s*CAUTION\\(S\\)\\s*:\\s*|".
			"^\\s*WARNINGS?\\s*:\\s*|".
			"^\\s*WARNING\\(S\\)\\s*:\\s*|".
			"^\\s*DANGERS?\\s*:\\s*|".
			"^\\s*DANGER\\(S\\)\\s*:\\s*",
		"See_Also    FLAG_SEE_ALSO      N N Y Y Y N N ".
			"^\\s*SEE\\s+ALSO\\s*:\\s*",
		"Examples    FLAG_EXAMPLES      N Y Y Y N Y Y ".
			"^\\s*EXAMPLES?\\s*:\\s*|".
			"^\\s*EXAMPLE\\(S\\)\\s*:\\s*",
		"Code_Examples     FLAG_CODE_EXAMPLES   N N N N N N N ".
			"^\\s*CODE\\s+EXAMPLES?\\s*:\\s*|".
			"^\\s*CODE\\s+EXAMPLE\\(S\\)\\s*:\\s*",
		"Authors     FLAG_AUTHORS       N Y Y Y Y Y Y ".
			"^\\s*AUTHORS?\\s*:\\s*|".
			"^\\s*AUTHOR\\(S\\)\\s*:\\s*|".
			"^\\s*PROGRAMMERS?\\s*:\\s*|".
			"^\\s*PROGRAMMER\\(S\\)\\s*:\\s*|".
			"^\\s*AUTHORED\\s+BY\\s*:\\s*|".
			"^\\s*PROGRAMMED\\s+BY\\s*:\\s*|".
			"^\\s*WRITTEN\\s+BY\\s*:\\s*|".
			"^\\s*CREATED\\s+BY\\s*:\\s*",
		"Copyrights  FLAG_COPYRIGHTS    N Y Y Y Y Y Y ".
			"^\\s*COPYRIGHTS?\\s*:\\s*|".
			"^\\s*COPYRIGHT\\(S\\)\\s*:\\s*|".
			"^\\s*COPYRIGHTED\\s+BY\\s*:\\s*",
		"Source_File_Name FLAG_SOURCE_FILE_NAME N N Y Y Y N N ".
			"^\\s*SOURCES?\\s*:\\s*|".
			"^\\s*SOURCE\\(S\\)\\s*:\\s*|".
			"^\\s*SOURCE\\s+FILES?\\s*:\\s*|".
			"^\\s*SOURCE\\s+FILE\\(S\\)\\s*:\\s*|".
			"^\\s*SOURCE\\s+NAMES?\\s*:\\s*|".
			"^\\s*SOURCE\\s+NAME\\(S\\)\\s*:\\s*|".
			"^\\s*SOURCE\\s+FILE\\s+NAMES?\\s*:\\s*|".
			"^\\s*SOURCE\\s+FILE\\s+NAME\\(S\\)\\s*:\\s*",
		"Source_File_Date FLAG_SOURCE_FILE_DATE N N Y Y Y N N ".
			"^\\s*DATES?\\s*:\\s*|".
			"^\\s*DATE\\(S\\)\\s*:\\s*|".
			"^\\s*SOURCE\\s+DATES?\\s*:\\s*|".
			"^\\s*SOURCE\\s+DATE\\(S\\)\\s*:\\s*|".
			"^\\s*SOURCE\\s+FILE\\s+DATES?\\s*:\\s*|".
			"^\\s*SOURCE\\s+FILE\\s+DATE\\(S\\)\\s*:\\s*",
		"OUTPUT_INDEX     FLAG_OUTPUT_INDEX     N N Y Y Y N N ".
			"^\\s*INDEXS?\\s*:\\s*|".
			"^\\s*INDEX\\(S\\)\\s*:\\s*|".
			"^\\s*INDICES\\s*:\\s*|".
			"^\\s*OUTPUT\\s+INDEXS?\\s*:\\s*|".
			"^\\s*OUTPUT\\s+INDEX\\(S\\)\\s*:\\s*|".
			"^\\s*OUTPUT\\s+INDICES\\s*:\\s*",
		"PUBLISH_XREF    FLAG_PUBLISH_XREF    N N Y Y Y N N ".
			"^\\s*PUBLISH\\s+XREFS?\\s*:\\s*",
		"PUBLISH_NAME    FLAG_PUBLISH_NAME    N N Y Y Y N N ".
			"^\\s*PUBLISH\\s+NAMES?\\s*:\\s*"
	);
	&ADF_InitParseData("H", "H_DataNameList", "H_DataFlagList",
		"H_DataRequiredList", "H_DataWrapList", "H_DataLTrimList",
		"H_DataRTrimList", "H_DataSqueezeList", "H_ParaFormatList",
		"H_CharFormatList", "H_DataPatternList", "H_DataExcludeList",
		"H_DataComponentList", "H_DataOrderList", $H_EOH_Pattern,
		@H_NeededData);
	# #####################################################################	#

	# #####################################################################	#
	# #####################################################################	#
	#    Input file type is '.ph' . . .
	# #####################################################################	#
	$FileTypeList{"ph"}  = "PH";
	$PH_EmptyLinePattern = "^\\s*\$|^\\s*#\\s*\$";
	$PH_BOH_Pattern      = "^\\s*\\#\\s+BOH";
	$PH_EOH_Pattern      = "^\\s*\\#\\s+EOH";
	$PH_BOL_StripPattern = "^\\s*#";
	$PH_EOL_StripPattern = "";
	@PH_NeededData       = (
		"BASE_NAME   FLAG_BASE_NAME     N Y Y Y Y N N ".
			"^\\s*\\#\\s*BASE\\s+NAME\\s*:\\s*",
		"Name        FLAG_NAME          Y Y Y Y Y Y Y ".
			"^\\s*\\#\\s*NAME\\s*:\\s*",
		"Description FLAG_DESCRIPTION   Y Y Y Y Y Y Y ".
			"^\\s*\\#\\s*DESCRIPTION\\s*:\\s*",
		"Notes       FLAG_NOTES         N Y Y Y Y Y Y ".
			"^\\s*\\#\\s*NOTES?\\s*:\\s*|".
			"^\\s*\\#\\s*NOTE\\(S\\)\\s*:\\s*|".
			"^\\s*\\#\\s*COMMENTS?\\s*:\\s*|".
			"^\\s*\\#\\s*COMMENT\\(S\\)\\s*:\\s*",
		"Caveats     FLAG_CAVEATS       N Y Y Y Y Y Y ".
			"^\\s*\\#\\s*CAVEATS?\\s*:\\s*|".
			"^\\s*\\#\\s*CAVEAT\\(S\\)\\s*:\\s*|".
			"^\\s*\\#\\s*CAUTIONS?\\s*:\\s*|".
			"^\\s*\\#\\s*CAUTION\\(S\\)\\s*:\\s*|".
			"^\\s*\\#\\s*WARNINGS?\\s*:\\s*|".
			"^\\s*\\#\\s*WARNING\\(S\\)\\s*:\\s*|".
			"^\\s*\\#\\s*DANGERS?\\s*:\\s*|".
			"^\\s*\\#\\s*DANGER\\(S\\)\\s*:\\s*",
		"See_Also    FLAG_SEE_ALSO      N N Y Y Y N N ".
			"^\\s*\\#\\s*SEE\\s+ALSO\\s*:\\s*",
		"Examples    FLAG_EXAMPLES      N Y Y Y N Y Y ".
			"^\\s*\\#\\s*EXAMPLES?\\s*:\\s*|".
			"^\\s*\\#\\s*EXAMPLE\\(S\\)\\s*:\\s*",
		"Code_Examples     FLAG_CODE_EXAMPLES   N N N N N N N ".
			"^\\s*\\#\\s*CODE\\s+EXAMPLES?\\s*:\\s*|".
			"^\\s*\\#\\s*CODE\\s+EXAMPLE\\(S\\)\\s*:\\s*",
		"Authors     FLAG_AUTHORS       N Y Y Y Y Y Y ".
			"^\\s*\\#\\s*AUTHORS?\\s*:\\s*|".
			"^\\s*\\#\\s*AUTHOR\\(S\\)\\s*:\\s*|".
			"^\\s*\\#\\s*PROGRAMMERS?\\s*:\\s*|".
			"^\\s*\\#\\s*PROGRAMMER\\(S\\)\\s*:\\s*|".
			"^\\s*\\#\\s*AUTHORED\\s+BY\\s*:\\s*|".
			"^\\s*\\#\\s*PROGRAMMED\\s+BY\\s*:\\s*|".
			"^\\s*\\#\\s*WRITTEN\\s+BY\\s*:\\s*|".
			"^\\s*\\#\\s*CREATED\\s+BY\\s*:\\s*",
		"Copyrights  FLAG_COPYRIGHTS    N Y Y Y Y Y Y ".
			"^\\s*\\#\\s*COPYRIGHTS?\\s*:\\s*|".
			"^\\s*\\#\\s*COPYRIGHT\\(S\\)\\s*:\\s*|".
			"^\\s*\\#\\s*COPYRIGHTED\\s+BY\\s*:\\s*",
		"Source_File_Name FLAG_SOURCE_FILE_NAME N N Y Y Y N N ".
			"^\\s*\\#\\s*SOURCES?\\s*:\\s*|".
			"^\\s*\\#\\s*SOURCE\\(S\\)\\s*:\\s*|".
			"^\\s*\\#\\s*SOURCE\\s+FILES?\\s*:\\s*|".
			"^\\s*\\#\\s*SOURCE\\s+FILE\\(S\\)\\s*:\\s*|".
			"^\\s*\\#\\s*SOURCE\\s+NAMES?\\s*:\\s*|".
			"^\\s*\\#\\s*SOURCE\\s+NAME\\(S\\)\\s*:\\s*|".
			"^\\s*\\#\\s*SOURCE\\s+FILE\\s+NAMES?\\s*:\\s*|".
			"^\\s*\\#\\s*SOURCE\\s+FILE\\s+NAME\\(S\\)\\s*:\\s*",
		"Source_File_Date FLAG_SOURCE_FILE_DATE N N Y Y Y N N ".
			"^\\s*\\#\\s*DATES?\\s*:\\s*|".
			"^\\s*\\#\\s*DATE\\(S\\)\\s*:\\s*|".
			"^\\s*\\#\\s*SOURCE\\s+DATES?\\s*:\\s*|".
			"^\\s*\\#\\s*SOURCE\\s+DATE\\(S\\)\\s*:\\s*|".
			"^\\s*\\#\\s*SOURCE\\s+FILE\\s+DATES?\\s*:\\s*|".
			"^\\s*\\#\\s*SOURCE\\s+FILE\\s+DATE\\(S\\)\\s*:\\s*",
		"OUTPUT_INDEX     FLAG_OUTPUT_INDEX     N N Y Y Y N N ".
			"^\\s*\\#\\s*INDEXS?\\s*:\\s*|".
			"^\\s*\\#\\s*INDEX\\(S\\)\\s*:\\s*|".
			"^\\s*\\#\\s*INDICES\\s*:\\s*|".
			"^\\s*\\#\\s*OUTPUT\\s+INDEXS?\\s*:\\s*|".
			"^\\s*\\#\\s*OUTPUT\\s+INDEX\\(S\\)\\s*:\\s*|".
			"^\\s*\\#\\s*OUTPUT\\s+INDICES\\s*:\\s*",
		"PUBLISH_XREF    FLAG_PUBLISH_XREF    N N Y Y Y N N ".
			"^\\s*\\#\\s*PUBLISH\\s+XREFS?\\s*:\\s*",
		"PUBLISH_NAME    FLAG_PUBLISH_NAME    N N Y Y Y N N ".
			"^\\s*\\#\\s*PUBLISH\\s+NAMES?\\s*:\\s*"
	);
	&ADF_InitParseData("PH", "PH_DataNameList", "PH_DataFlagList",
		"PH_DataRequiredList", "PH_DataWrapList", "PH_DataLTrimList",
		"PH_DataRTrimList", "PH_DataSqueezeList", "PH_ParaFormatList",
		"PH_CharFormatList", "PH_DataPatternList", "PH_DataExcludeList",
		"PH_DataComponentList", "PH_DataOrderList", $PH_EOH_Pattern,
		@PH_NeededData);
	# #####################################################################	#

	# #####################################################################	#
	# #####################################################################	#
	#    Input type is '.bin' . . .
	# #####################################################################	#
	$FileTypeList{"bin"}   = "BIN";
	$FileTypeList{"exe"}   = "BIN";
	$BIN_EmptyLinePattern  = "^\\s*\$";
	$BIN_BOH_Pattern       = "^\\s*\\/\\*\\s+BOH|^\\s*\\#\\s+BOH";
	$BIN_EOH_Pattern       = "^EOH\\s+\\*/|^\\s*\\#\\s+EOH";
	$BIN_BOL_StripPattern  = "^\\s*#";
	$BIN_EOL_StripPattern  = "";
	@BIN_NeededData        = (
		"BASE_NAME        FLAG_BASE_NAME        N Y Y Y Y N N ".
			"^\\s*BASE\\s+NAME\\s*:\\s*",
		"Name             FLAG_NAME             Y Y Y Y Y Y Y ".
			"^\\s*NAME\\s*:\\s*",
		"Synopsis         FLAG_SYNOPSIS         Y Y Y Y Y Y Y ".
			"^\\s*SYNOPSIS\\s*:\\s*",
		"Description      FLAG_DESCRIPTION      Y Y Y Y Y Y Y ".
			"^\\s*DESCRIPTION\\s*:\\s*",
		"Parameters       FLAG_PARAMETERS       N Y Y Y Y Y Y ".
			"^\\s*OPTIONS?\\s*:\\s*|".
			"^\\s*OPTION\\(S\\)\\s*:\\s*".
			"^\\s*PARAMETERS?\\s*:\\s*|".
			"^\\s*PARAMETER\\(S\\)\\s*:\\s*",
		"Returns          FLAG_RETURNS          Y Y Y Y Y Y Y ".
			"^\\s*RETURNS?\\s*:\\s*|".
			"^\\s*RETURN\\(S\\)\\s*:\\s*",
		"Environment      FLAG_ENVIRONMENT      N Y Y Y Y Y Y ".
			"^\\s*ENVIRONMENTS?\\s*:\\s*|".
			"^\\s*ENVIRONMENT\\(S\\)\\s*:\\s*|".
			"^\\s*ENVIRONMENT\\s+VARIABLES?\\s*:\\s*|".
			"^\\s*ENVIRONMENT\\s+VARIABLE\\(S\\)\\s*:\\s*",
		"Notes            FLAG_NOTES            N Y Y Y Y Y Y ".
			"^\\s*NOTES?\\s*:\\s*|".
			"^\\s*NOTE\\(S\\)\\s*:\\s*|".
			"^\\s*COMMENTS?\\s*:\\s*|".
			"^\\s*COMMENT\\(S\\)\\s*:\\s*",
		"Caveats          FLAG_CAVEATS          N Y Y Y Y Y Y ".
			"^\\s*CAVEATS?\\s*:\\s*|".
			"^\\s*CAVEAT\\(S\\)\\s*:\\s*|".
			"^\\s*CAUTIONS?\\s*:\\s*|".
			"^\\s*CAUTION\\(S\\)\\s*:\\s*|".
			"^\\s*WARNINGS?\\s*:\\s*|".
			"^\\s*WARNING\\(S\\)\\s*:\\s*|".
			"^\\s*DANGERS?\\s*:\\s*|".
			"^\\s*DANGER\\(S\\)\\s*:\\s*",
		"See_Also         FLAG_SEE_ALSO         N N Y Y Y N N ".
			"^\\s*SEE\\s+ALSO\\s*:\\s*",
		"Examples         FLAG_EXAMPLES         N Y Y Y N Y Y ".
			"^\\s*EXAMPLES?\\s*:\\s*|".
			"^\\s*EXAMPLE\\(S\\)\\s*:\\s*",
		"Authors          FLAG_AUTHORS          N Y Y Y Y Y Y ".
			"^\\s*AUTHORS?\\s*:\\s*|".
			"^\\s*AUTHOR\\(S\\)\\s*:\\s*|".
			"^\\s*PROGRAMMERS?\\s*:\\s*|".
			"^\\s*PROGRAMMER\\(S\\)\\s*:\\s*|".
			"^\\s*AUTHORED\\s+BY\\s*:\\s*|".
			"^\\s*PROGRAMMED\\s+BY\\s*:\\s*|".
			"^\\s*WRITTEN\\s+BY\\s*:\\s*|".
			"^\\s*CREATED\\s+BY\\s*:\\s*",
		"Copyrights       FLAG_COPYRIGHTS       N Y Y Y Y Y Y ".
			"^\\s*COPYRIGHTS?\\s*:\\s*|".
			"^\\s*COPYRIGHT\\(S\\)\\s*:\\s*|".
			"^\\s*COPYRIGHTED\\s+BY\\s*:\\s*",
		"Source_File_Name FLAG_SOURCE_FILE_NAME N N Y Y Y N N ".
			"^\\s*SOURCES?\\s*:\\s*|".
			"^\\s*SOURCE\\(S\\)\\s*:\\s*|".
			"^\\s*SOURCE\\s+FILES?\\s*:\\s*|".
			"^\\s*SOURCE\\s+FILE\\(S\\)\\s*:\\s*|".
			"^\\s*SOURCE\\s+NAMES?\\s*:\\s*|".
			"^\\s*SOURCE\\s+NAME\\(S\\)\\s*:\\s*|".
			"^\\s*SOURCE\\s+FILE\\s+NAMES?\\s*:\\s*|".
			"^\\s*SOURCE\\s+FILE\\s+NAME\\(S\\)\\s*:\\s*",
		"Source_File_Date FLAG_SOURCE_FILE_DATE N N Y Y Y N N ".
			"^\\s*DATES?\\s*:\\s*|".
			"^\\s*DATE\\(S\\)\\s*:\\s*|".
			"^\\s*SOURCE\\s+DATES?\\s*:\\s*|".
			"^\\s*SOURCE\\s+DATE\\(S\\)\\s*:\\s*|".
			"^\\s*SOURCE\\s+FILE\\s+DATES?\\s*:\\s*|".
			"^\\s*SOURCE\\s+FILE\\s+DATE\\(S\\)\\s*:\\s*",
		"OUTPUT_INDEX     FLAG_OUTPUT_INDEX     N N Y Y Y N N ".
			"^\\s*INDEXS?\\s*:\\s*|".
			"^\\s*INDEX\\(S\\)\\s*:\\s*|".
			"^\\s*INDICES\\s*:\\s*|".
			"^\\s*OUTPUT\\s+INDEXS?\\s*:\\s*|".
			"^\\s*OUTPUT\\s+INDEX\\(S\\)\\s*:\\s*|".
			"^\\s*OUTPUT\\s+INDICES\\s*:\\s*",
		"PUBLISH_XREF    FLAG_PUBLISH_XREF    N N Y Y Y N N ".
			"^\\s*PUBLISH\\s+XREFS?\\s*:\\s*",
		"PUBLISH_NAME    FLAG_PUBLISH_NAME    N N Y Y Y N N ".
			"^\\s*PUBLISH\\s+NAMES?\\s*:\\s*"
	);
	&ADF_InitParseData("BIN", "BIN_DataNameList", "BIN_DataFlagList",
		"BIN_DataRequiredList", "BIN_DataWrapList", "BIN_DataLTrimList",
		"BIN_DataRTrimList", "BIN_DataSqueezeList", "BIN_ParaFormatList",
		"BIN_CharFormatList", "BIN_DataPatternList", "BIN_DataExcludeList",
		"BIN_DataComponentList", "BIN_DataOrderList", $BIN_EOH_Pattern,
		@BIN_NeededData);
	# #####################################################################	#
}

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_InitParseData {
	local($parse_domain, *name_list, *flag_list, *required_list, *wrap_list,
		*ltrim_list, *rtrim_list, *squeeze_list, *para_format_list,
		*char_format_list, *pattern_list, *exclude_list, *component_list,
		*order_list, $eoh_pattern, @needed_data) = @_;
	local($count_1, $count_2, $this_item, $this_index, @tmp_data);

	@name_list        = ();	# The name of component as it should be output
	@flag_list        = (); # Right-padded name of component
	@required_list    = (); # Required flag
	@wrap_list        = (); # Wrap flag
	@ltrim_list       = (); # Left-trim of spaces flag
	@rtrim_list       = (); # Right-trim of spaces flag
	@squeeze_list     = (); # Squeeze internal spaces flag
	@para_format_list = (); # Perform paragraph formatting flag
	@char_format_list = (); # Perform character formatting flag
	@pattern_list     = (); # Pattern to locate the component
	@exclude_list     = (); # Pattern to locate the component boundaries
	@order_list       = (); # Lists the desired order of the components
	@component_list   = "";

	# #####################################################################	#
	# #####################################################################	#
	# #####################################################################	#
	for ($this_item = 0; $this_item <= $#needed_data; $this_item++) {
		@tmp_data = split(/\s+/, $needed_data[$this_item]);
		if ($#tmp_data < $DATA_FLAG) {
			print STDERR "Invalid number of components in parse domain ".
				"\'$parse_domain\' (", $ADF_ParseComponentCount, " ",
				"expected, ", $#tmp_data + 1, " found).\n";
			exit(1);
		}
		elsif (!defined($ADF_FlagNameArray{$tmp_data[$DATA_FLAG]})) {
			print STDERR "Invalid section name in parse domain ".
				"\'$parse_domain\' (\'$tmp_data[$DATA_FLAG]\').\n";
			exit(1);
		}
		elsif (($#tmp_data + 1) != $ADF_ParseComponentCount) {
			print STDERR "Invalid number of components in parse domain ".
				"\'$parse_domain\', section name \'$tmp_data[$DATA_FLAG]\' ".
				"($ADF_ParseComponentCount expected, ", $#tmp_data + 1,
				" found).\n";
			exit(1);
		}
		elsif ($tmp_data[$DATA_NAME] =~ /^_+$/) {
			print STDERR "Invalid component name in parse domain ",
				"\'$parse_domain\', section name \'$tmp_data[$DATA_FLAG]\' ",
				"--- name consists of underscores which will be mapped to ",
				"spaces and is therefore a NULL name.\n";
			exit(1);
		}
		$this_index = $ADF_FlagNameArray{$tmp_data[$DATA_FLAG]};
		if ($name_list[$this_index] ne "") {
			print STDERR "Duplicate \'$tmp_data[$DATA_FLAG]\' sections were ",
				"found in parse domain \'$parse_domain\'.\n";
			exit(1);
		}
		$name_list[$this_index]        =  $tmp_data[$DATA_NAME];
		$name_list[$this_index]        =~ s/_/ /g;
		$flag_list[$this_index]        =  $tmp_data[$DATA_FLAG];
		$required_list[$this_index]    =  $tmp_data[$DATA_REQUIRED];
		$wrap_list[$this_index]        =  $tmp_data[$DATA_WRAP];
		$ltrim_list[$this_index]       =  $tmp_data[$DATA_LTRIM];
		$rtrim_list[$this_index]       =  $tmp_data[$DATA_RTRIM];
		$squeeze_list[$this_index]     =  $tmp_data[$DATA_SQUEEZE];
		$para_format_list[$this_index] =  $tmp_data[$DATA_PARA_FORMAT];
		$char_format_list[$this_index] =  $tmp_data[$DATA_CHAR_FORMAT];
		$pattern_list[$this_index]     =  $tmp_data[$DATA_PATTERN];
		$order_list[$this_item]        =  $this_index;
		$MaxLabelLength                =
			(length($tmp_data[$DATA_NAME]) > $MaxLabelLength) ?
			length($tmp_data[$DATA_NAME]) : $MaxLabelLength;
		# ###############################################################	#
		# ###############################################################	#
		#    If paragraph formatting is turned on, then we turn one the	#
		# flags for word-wrapping, left-trimming, 'right-trimming, and		#
		# space-squeezing.																#
		# ###############################################################	#
		if ($para_format_list[$this_index] eq "Y") {
			$wrap_list[$this_index]    = "Y";
			$ltrim_list[$this_index]   = "Y";
			$rtrim_list[$this_index]   = "Y";
			$squeeze_list[$this_index] = "Y";
		}
		# ###############################################################	#
		# ###############################################################	#
		# ###############################################################	#
		#    Create the component list for this file type --- it is to		#
		# be stored in the ADF database file for each comment entry of	#
		# this file-type.																	#
		# ###############################################################	#
		$component_list[$this_index] =
			$tmp_data[$DATA_NAME]." ".
			$flag_list[$this_index]." ".
			$required_list[$this_index]." ".
			$wrap_list[$this_index]." ".
			$ltrim_list[$this_index]." ".
			$rtrim_list[$this_index]." ".
			$squeeze_list[$this_index]." ".
			$para_format_list[$this_index]." ".
			$char_format_list[$this_index];
		# ###############################################################	#
	}
	# #####################################################################	#

	# #####################################################################	#
	# #####################################################################	#
	# #####################################################################	#
	for ($count_1 = 0; $count_1 <= $#ADF_FlagNameList; $count_1++) {
		if ($name_list[$count_1] ne "") {
			for ($count_2 = 0; $count_2 <= $#ADF_FlagNameList; $count_2++) {
				if (($count_2 != $count_1) && ($name_list[$count_2] ne "")) {
					$exclude_list[$count_1] .= $pattern_list[$count_2]."|";
				}
			}
			$exclude_list[$count_1] .= $eoh_pattern;
		}
	}
	# #####################################################################	#

	# #####################################################################	#
	# #####################################################################	#
	# #####################################################################	#
#	for $this_item (@label_list) {
#		$this_item .= " " x ($MaxLabelLength - length($this_item));
#	}
	# #####################################################################	#

	$ADF_RegisteredParseDomains{$parse_domain}++;
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_SetFileTypeData {
	local($in_file_type) = @_;

	$ADF_CurrentParseDomain = $in_file_type;

	$BOH_Pattern        = "";
	$EOH_Pattern        = "";
	$BOL_StripPattern   = "";
	$EOL_StripPattern   = "";
	@NeededData         = ();
	@DataNameList       = ();
	@DataFlagList       = ();
	@DataRequiredList   = ();
	@DataWrapList       = ();
	@DataLTrimList      = ();
	@DataRTrimList      = ();
	@DataSqueezeList    = ();
	@DataParaFormatList = ();
	@DataCharFormatList = ();
	@DataPatternList    = ();
	@DataExcludeList    = ();
	@DataComponentList  = ();
	@DataOrderList      = ();

	eval "\$EmptyLinePattern   = \$".$in_file_type."_EmptyLinePattern;";
	eval "\$BOH_Pattern        = \$".$in_file_type."_BOH_Pattern;";
	eval "\$EOH_Pattern        = \$".$in_file_type."_EOH_Pattern;";
	eval "\$BOL_StripPattern   = \$".$in_file_type."_BOL_StripPattern;";
	eval "\$EOL_StripPattern   = \$".$in_file_type."_EOL_StripPattern;";
	eval "\@NeededData         = \@".$in_file_type."_NeededData;";
	eval "\@DataNameList       = \@".$in_file_type."_DataNameList;";
	eval "\@DataFlagList       = \@".$in_file_type."_DataFlagList;";
	eval "\@DataRequiredList   = \@".$in_file_type."_DataRequiredList;";
	eval "\@DataWrapList       = \@".$in_file_type."_DataWrapList;";
	eval "\@DataLTrimList      = \@".$in_file_type."_DataLTrimList;";
	eval "\@DataRTrimList      = \@".$in_file_type."_DataRTrimList;";
	eval "\@DataSqueezeList    = \@".$in_file_type."_DataSqueezeList;";
	eval "\@DataParaFormatList = \@".$in_file_type."_ParaFormatList;";
	eval "\@DataCharFormatList = \@".$in_file_type."_CharFormatList;";
	eval "\@DataPatternList    = \@".$in_file_type."_DataPatternList;";
	eval "\@DataExcludeList    = \@".$in_file_type."_DataExcludeList;";
	eval "\@DataComponentList  = \@".$in_file_type."_DataComponentList;";
	eval "\@DataOrderList      = \@".$in_file_type."_DataOrderList;";

	$DataOrderString     = join("\n", @DataOrderList);
	$DataComponentString = join("\n", @DataComponentList);
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub ADF_SetFileTypeDataFromFDB {
	local($source_name, $file_handle, $entry_offset, $entry_length,
		*in_data_list) = @_;
	local($return_code, $tmp_string, $order_string, $component_string,
		$count_1, $this_item, $this_index, @tmp_data);

	seek($file_handle, $entry_offset, 0);
	sysread($file_handle, $tmp_string, $entry_length, 0);
	($order_string, $component_string, @in_data_list) =
		split(/\177/, $tmp_string);

	$return_code        = 0;
   @DataNameList       = ();
   @DataFlagList       = ();
   @DataRequiredList   = ();
   @DataWrapList       = ();
   @DataLTrimList      = ();
   @DataRTrimList      = ();
   @DataSqueezeList    = ();
   @DataParaFormatList = ();
   @DataCharFormatList = ();
	@DataComponentList  = split(/\n/, $component_string);
	@DataOrderList      = split(/\n/, $order_string);

	# #####################################################################	#
	# #####################################################################	#
	# #####################################################################	#
	foreach $this_item (@DataOrderList) {
		if (($this_item < 0) || ($this_item > $#ADF_FlagNameList)) {
			print STDERR "Invalid component index in the order list from ",
				"item \'$source_name\' (valid range is from 0 to ",
				$#ADF_FlagNameList, ", inclusive).\n";
			return(-1);
		}
	}
	# #####################################################################	#

	# #####################################################################	#
	# #####################################################################	#
	# #####################################################################	#
	for ($this_item = 0; $this_item <= $#DataComponentList; $this_item++) {
		if ($DataComponentList[$this_item] =~ /^\s*$/) {
			next;
		}
		@tmp_data = split(/\s+/, $DataComponentList[$this_item]);
		if ($#tmp_data < $FDB_DATA_FLAG) {
			print STDERR "Invalid number of components in component list from ".
				"item \'$source_name\' (", $ADF_FDBParseComponentCount, " ",
				"expected, ", $#tmp_data + 1, " found).\n";
			$return_code = -1;
		}
		elsif (!defined($ADF_FlagNameArray{$tmp_data[$FDB_DATA_FLAG]})) {
			print STDERR "Invalid section name in component list from  ".
				"item \'$source_name\' (\'$tmp_data[$FDB_DATA_FLAG]\').\n";
			$return_code = -1;
		}
		elsif (($#tmp_data + 1) != $ADF_FDBParseComponentCount) {
			print STDERR "Invalid number of components in component list from ".
				"\'$source_name\', section name \'$tmp_data[$FDB_DATA_FLAG]\' ".
				"($ADF_FDBParseComponentCount expected, ", $#tmp_data + 1,
				" found).\n";
			$return_code = -1;
		}
		$this_index                      =
			$ADF_FlagNameArray{$tmp_data[$FDB_DATA_FLAG]};
		$tmp_data[$FDB_DATA_NAME]        =~ s/_/ /g;
		$DataNameList[$this_index]       =  $tmp_data[$FDB_DATA_NAME];
		$DataFlagList[$this_index]       =  $tmp_data[$FDB_DATA_FLAG];
		$DataRequiredList[$this_index]   =  $tmp_data[$FDB_DATA_REQUIRED];
		$DataWrapList[$this_index]       =  $tmp_data[$FDB_DATA_WRAP];
		$DataLTrimList[$this_index]      =  $tmp_data[$FDB_DATA_LTRIM];
		$DataRTrimList[$this_index]      =  $tmp_data[$FDB_DATA_RTRIM];
		$DataSqueezeList[$this_index]    =  $tmp_data[$FDB_DATA_SQUEEZE];
		$DataParaFormatList[$this_index] =  $tmp_data[$FDB_DATA_PARA_FORMAT];
		$DataCharFormatList[$this_index] =  $tmp_data[$FDB_DATA_CHAR_FORMAT];
	}
	# #####################################################################	#

	# #####################################################################	#
	# #####################################################################	#
	# #####################################################################	#
	if ((!$return_code) && ($DataOrderList[0] != $FLAG_NAME)) {
		for ($this_item = 0; $this_item <= $#DataOrderList; $this_item++) {
			$data_order_array{"$DataOrderList[$this_item]"} = $this_item;
		}
		if (defined($data_order_array{"$FLAG_NAME"})) {
			unshift(@DataOrderList, splice(@DataOrderList,
				$data_order_array{"$FLAG_NAME"}, 1));
		}
		else {
			unshift(@DataOrderList     , $FLAG_NAME);
			$in_data_list[$FLAG_NAME]       = $in_data_list[$FLAG_BASE_NAME];
			$DataNameList[$FLAG_NAME]       = "Name";
			$DataFlagList[$FLAG_NAME]       = "FLAG_NAME";
			$DataRequiredList[$FLAG_NAME]   = "Y";
			$DataWrapList[$FLAG_NAME]       = "Y";
			$DataLTrimList[$FLAG_NAME]      = "Y";
			$DataRTrimList[$FLAG_NAME]      = "Y";
			$DataSqueezeList[$FLAG_NAME]    = "Y";
			$DataParaFormatList[$FLAG_NAME] = "Y";
			$DataCharFormatList[$FLAG_NAME] = "Y";
			$DataComponentList[$FLAG_NAME]  = $DataNameList[$FLAG_NAME]." ".
				$DataFlagList[$FLAG_NAME]." ".
				$DataRequiredList[$FLAG_NAME]." ".
				$DataWrapList[$FLAG_NAME]." ".
				$DataLTrimList[$FLAG_NAME]." ".
				$DataRTrimList[$FLAG_NAME]." ".
				$DataSqueezeList[$FLAG_NAME]." ".
				$DataParaFormatList[$FLAG_NAME]." ".
				$DataCharFormatList[$FLAG_NAME]." ";
		}
	}
	# #####################################################################	#

	$DataOrderString     = join("\n", @DataOrderList);
	$DataComponentString = join("\n", @DataComponentList);

	return($return_code);
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub DATFUNCS_InitData {
	local($this_month);

	%DATFUNCS_MonthArray = (
		"jan",       1,
		"january",   1,
		"feb",       2,
		"february",  2,
		"mar",       3,
		"march",     3,
		"apr",       4,
		"april",     4,
		"may",       5,
		"may",       5,
		"jun",       6,
		"june",      6,
		"jul",       7,
		"july",      7,
		"aug",       8,
		"august",    8,
		"sep",       9,
		"sept",      9,
		"september", 9,
		"oct",       10,
		"october",   10,
		"nov",       11,
		"november",  11,
		"dec",       12,
		"december",  12
	);

	foreach $this_month (keys(%DATFUNCS_MonthArray)) {
		$DATFUNCS_MonthList[$DATFUNCS_MonthArray{$this_month} - 1] =
			(length($this_month) >	
			length($DATFUNCS_MonthList[$DATFUNCS_MonthArray{$this_month} - 1])) ?
			$this_month :
			$DATFUNCS_MonthList[$DATFUNCS_MonthArray{$this_month} - 1];
	}

	@DATFUNCS_MonthLength = (31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31);
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub DATFUNCS_ParseDate {
	local($in_date, $out_year, $out_month, $out_day) = @_;
	local($return_code, @date_list, $out_year, $out_month, $out_day);

	$return_code =  -1;

	$in_date =~ s/^\s+|\s+$//g;
	$in_date =~ s/\s+/ /g;
	@date_list =  split(/ |\-|\//, $in_date);

	if ($#date_list == 2) {
		grep(do { $_ =~ s/^0+//g; 0; }, @date_list);
		$in_date = $date_list[0]." ".$date_list[1]." ".$date_list[2];
		if ($in_date =~ /^(\d{1,2}) ([A-Za-z]{3,}) (\d{2}(\d{2})?)$/) {
			$out_month =  $2;
			$out_month =~ tr/[A_Z]/[a-z]/;
			if (defined($DATFUNCS_MonthArray{$out_month})) {
				$out_year = (length($3) == 4) ? $3 : "19".$3;
				$in_date  = $out_year." ".$DATFUNCS_MonthArray{$out_month}.
					" ".$1;
			}
		}
		elsif ($in_date =~ /^(\d{1,2}) (\d{1,2}) (\d{2}(\d{2})?)$/) {
			if ($in_date =~ /^(\d{1,2}) (\d{1,2}) (\d{2})$/) {
				if ($1 > 31) {
					$in_date = "19".$1." ".$2." ".$3;
				}
				elsif ($3 > 31) {
					$in_date = $1." ".$2." "."19".$3;
				}
			}
			if ($in_date =~ /^(\d{1,2}) (\d{1,2}) (\d{4})$/) {
				if (($1 <= 12) && (($2 > 12) && ($2 <= 31))) {
					$in_date = $3." ".$1." ".$2;
				}
				if (($2 <= 12) && (($1 > 12) && ($1 <= 31))) {
					$in_date = $3." ".$2." ".$1;
				}
			}
		}
		if ($in_date =~ /^(\d{4}) (\d{1,2}) (\d{1,2})$/) {
			$out_year  = $1;
			$out_month = $2;
			$out_day   = $3;
			if (($out_month >= 1) && ($out_month <= 12) && ($out_day >= 1)) {
				if ($out_day <= &DATFUNCS_DaysInMonth($out_year, $out_month)) {
					$_[1]        = $out_year;
					$_[2]        = $out_month;
					$_[3]        = $out_day;
					$return_code = 0;
				}
			}
		}
	}

	return($return_code);
}
# ###########################################################################

# ###########################################################################
# ###########################################################################
# ###########################################################################
sub DATFUNCS_DaysInMonth {
	local($in_year, $in_month) = @_;
	local($days_in_month);

	$days_in_month = 0;

	if (($in_month >= 1) && ($in_month <= 12)) {
		$days_in_month = $DATFUNCS_MonthLength[$in_month - 1];
		if (($in_month == 2) && (((!($in_year % 4)) && ($in_year % 100)) ||
			((!($in_year % 4)) && (!($in_year % 400))))) {
			$days_in_month = 29;
		}
	}

	return($days_in_month);
}
# ###########################################################################


/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts between ASCII and EBCDIC representations.

	Revision History	:	1993-07-07 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Include necessary header files . . .											*/
/* *********************************************************************** */

#include <limits.h>

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */

static const unsigned int ASCII_To_EBCDIC_List[256] = {
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	    0X37,	/* ASCII=EBCDIC decimal:004=055, octal:004=067, hex:0X04=0X37 */
	    0X2D,	/* ASCII=EBCDIC decimal:005=045, octal:005=055, hex:0X05=0X2D */
		 0X2E,	/* ASCII=EBCDIC decimal:006=046, octal:006=056, hex:0X06=0X2E */
	    0X2F,	/* ASCII=EBCDIC decimal:007=047, octal:007=057, hex:0X07=0X2F */
	    0X16,	/* ASCII=EBCDIC decimal:008=022, octal:010=026, hex:0X08=0X16 */
	    0X05,	/* ASCII=EBCDIC decimal:009=005, octal:011=005, hex:0X09=0X05 */
	    0X25,	/* ASCII=EBCDIC decimal:010=037, octal:012=045, hex:0X0A=0X25 */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	    0X3C,	/* ASCII=EBCDIC decimal:020=060, octal:024=074, hex:0X14=0X3C */
	    0X3D,	/* ASCII=EBCDIC decimal:021=061, octal:025=075, hex:0X15=0X3D */
	    0X32,	/* ASCII=EBCDIC decimal:022=050, octal:026=062, hex:0X16=0X32 */
	    0X26,	/* ASCII=EBCDIC decimal:023=038, octal:027=046, hex:0X17=0X26 */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	    0X3F,	/* ASCII=EBCDIC decimal:026=063, octal:032=077, hex:0X1A=0X3F */
		 0X27,	/* ASCII=EBCDIC decimal:027=039, octal:033=047, hex:0X1B=0X27 */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	    0X40,	/* ASCII=EBCDIC decimal:032=064, octal:040=100, hex:0X20=0X40 */
	    0X5A,	/* ASCII=EBCDIC decimal:033=090, octal:041=132, hex:0X21=0X5A */
	    0X7F,	/* ASCII=EBCDIC decimal:034=127, octal:042=177, hex:0X22=0X7F */
	    0X7B,	/* ASCII=EBCDIC decimal:035=123, octal:043=173, hex:0X23=0X7B */
	    0X5B,	/* ASCII=EBCDIC decimal:036=091, octal:044=133, hex:0X24=0X5B */
	    0X6C,	/* ASCII=EBCDIC decimal:037=108, octal:045=154, hex:0X25=0X6C */
	    0X50,	/* ASCII=EBCDIC decimal:038=080, octal:046=120, hex:0X26=0X50 */
	    0X7D,	/* ASCII=EBCDIC decimal:039=125, octal:047=175, hex:0X27=0X7D */
	    0X4D,	/* ASCII=EBCDIC decimal:040=077, octal:050=115, hex:0X28=0X4D */
	    0X5D,	/* ASCII=EBCDIC decimal:041=093, octal:051=135, hex:0X29=0X5D */
	    0X5C,	/* ASCII=EBCDIC decimal:042=092, octal:052=134, hex:0X2A=0X5C */
	    0X4E,	/* ASCII=EBCDIC decimal:043=078, octal:053=116, hex:0X2B=0X4E */
	    0X6B,	/* ASCII=EBCDIC decimal:044=107, octal:054=153, hex:0X2C=0X6B */
	    0X60,	/* ASCII=EBCDIC decimal:045=096, octal:055=140, hex:0X2D=0X60 */
	    0X4B,	/* ASCII=EBCDIC decimal:046=075, octal:056=113, hex:0X2E=0X4B */
	    0X61,	/* ASCII=EBCDIC decimal:047=097, octal:057=141, hex:0X2F=0X61 */
		 0XF0,	/* ASCII=EBCDIC decimal:048=240, octal:060=360, hex:0X30=0XF0 */
	    0XF1,	/* ASCII=EBCDIC decimal:049=241, octal:061=361, hex:0X31=0XF1 */
	    0XF2,	/* ASCII=EBCDIC decimal:050=242, octal:062=362, hex:0X32=0XF2 */
	    0XF3,	/* ASCII=EBCDIC decimal:051=243, octal:063=363, hex:0X33=0XF3 */
	    0XF4,	/* ASCII=EBCDIC decimal:052=244, octal:064=364, hex:0X34=0XF4 */
	    0XF5,	/* ASCII=EBCDIC decimal:053=245, octal:065=365, hex:0X35=0XF5 */
	    0XF6,	/* ASCII=EBCDIC decimal:054=246, octal:066=366, hex:0X36=0XF6 */
	    0XF7,	/* ASCII=EBCDIC decimal:055=247, octal:067=367, hex:0X37=0XF7 */
	    0XF8,	/* ASCII=EBCDIC decimal:056=248, octal:070=370, hex:0X38=0XF8 */
	    0XF9,	/* ASCII=EBCDIC decimal:057=249, octal:071=371, hex:0X39=0XF9 */
	    0X7A,	/* ASCII=EBCDIC decimal:058=122, octal:072=172, hex:0X3A=0X7A */
	    0X5E,	/* ASCII=EBCDIC decimal:059=094, octal:073=136, hex:0X3B=0X5E */
	    0X4C,	/* ASCII=EBCDIC decimal:060=076, octal:074=114, hex:0X3C=0X4C */
	    0X7E,	/* ASCII=EBCDIC decimal:061=126, octal:075=176, hex:0X3D=0X7E */
	    0X6E,	/* ASCII=EBCDIC decimal:062=110, octal:076=156, hex:0X3E=0X6E */
	    0X6F,	/* ASCII=EBCDIC decimal:063=111, octal:077=157, hex:0X3F=0X6F */
	    0X7C,	/* ASCII=EBCDIC decimal:064=124, octal:100=174, hex:0X40=0X7C */
	    0XC1,	/* ASCII=EBCDIC decimal:065=193, octal:101=301, hex:0X41=0XC1 */
	    0XC2,	/* ASCII=EBCDIC decimal:066=194, octal:102=302, hex:0X42=0XC2 */
	    0XC3,	/* ASCII=EBCDIC decimal:067=195, octal:103=303, hex:0X43=0XC3 */
	    0XC4,	/* ASCII=EBCDIC decimal:068=196, octal:104=304, hex:0X44=0XC4 */
		 0XC5,	/* ASCII=EBCDIC decimal:069=197, octal:105=305, hex:0X45=0XC5 */
	    0XC6,	/* ASCII=EBCDIC decimal:070=198, octal:106=306, hex:0X46=0XC6 */
	    0XC7,	/* ASCII=EBCDIC decimal:071=199, octal:107=307, hex:0X47=0XC7 */
	    0XC8,	/* ASCII=EBCDIC decimal:072=200, octal:110=310, hex:0X48=0XC8 */
	    0XC9,	/* ASCII=EBCDIC decimal:073=201, octal:111=311, hex:0X49=0XC9 */
	    0XD1,	/* ASCII=EBCDIC decimal:074=209, octal:112=321, hex:0X4A=0XD1 */
	    0XD2,	/* ASCII=EBCDIC decimal:075=210, octal:113=322, hex:0X4B=0XD2 */
	    0XD3,	/* ASCII=EBCDIC decimal:076=211, octal:114=323, hex:0X4C=0XD3 */
	    0XD4,	/* ASCII=EBCDIC decimal:077=212, octal:115=324, hex:0X4D=0XD4 */
	    0XD5,	/* ASCII=EBCDIC decimal:078=213, octal:116=325, hex:0X4E=0XD5 */
	    0XD6,	/* ASCII=EBCDIC decimal:079=214, octal:117=326, hex:0X4F=0XD6 */
	    0XD7,	/* ASCII=EBCDIC decimal:080=215, octal:120=327, hex:0X50=0XD7 */
	    0XD8,	/* ASCII=EBCDIC decimal:081=216, octal:121=330, hex:0X51=0XD8 */
	    0XD9,	/* ASCII=EBCDIC decimal:082=217, octal:122=331, hex:0X52=0XD9 */
	    0XE2,	/* ASCII=EBCDIC decimal:083=226, octal:123=342, hex:0X53=0XE2 */
	    0XE3,	/* ASCII=EBCDIC decimal:084=227, octal:124=343, hex:0X54=0XE3 */
	    0XE4,	/* ASCII=EBCDIC decimal:085=228, octal:125=344, hex:0X55=0XE4 */
	    0XE5,	/* ASCII=EBCDIC decimal:086=229, octal:126=345, hex:0X56=0XE5 */
	    0XE6,	/* ASCII=EBCDIC decimal:087=230, octal:127=346, hex:0X57=0XE6 */
	    0XE7,	/* ASCII=EBCDIC decimal:088=231, octal:130=347, hex:0X58=0XE7 */
	    0XE8,	/* ASCII=EBCDIC decimal:089=232, octal:131=350, hex:0X59=0XE8 */
		 0XE9,	/* ASCII=EBCDIC decimal:090=233, octal:132=351, hex:0X5A=0XE9 */
	    0X4A,	/* ASCII=EBCDIC decimal:091=074, octal:133=112, hex:0X5B=0X4A */
	    0XE0,	/* ASCII=EBCDIC decimal:092=224, octal:134=340, hex:0X5C=0XE0 */
	    0X5A,	/* ASCII=EBCDIC decimal:093=090, octal:135=132, hex:0X5D=0X5A */
	    0X5F,	/* ASCII=EBCDIC decimal:094=095, octal:136=137, hex:0X5E=0X5F */
	    0X6D,	/* ASCII=EBCDIC decimal:095=109, octal:137=155, hex:0X5F=0X6D */
	    0X79,	/* ASCII=EBCDIC decimal:096=121, octal:140=171, hex:0X60=0X79 */
	    0X81,	/* ASCII=EBCDIC decimal:097=129, octal:141=201, hex:0X61=0X81 */
	    0X82,	/* ASCII=EBCDIC decimal:098=130, octal:142=202, hex:0X62=0X82 */
	    0X83,	/* ASCII=EBCDIC decimal:099=131, octal:143=203, hex:0X63=0X83 */
	    0X84,	/* ASCII=EBCDIC decimal:100=132, octal:144=204, hex:0X64=0X84 */
	    0X85,	/* ASCII=EBCDIC decimal:101=133, octal:145=205, hex:0X65=0X85 */
	    0X86,	/* ASCII=EBCDIC decimal:102=134, octal:146=206, hex:0X66=0X86 */
	    0X87,	/* ASCII=EBCDIC decimal:103=135, octal:147=207, hex:0X67=0X87 */
	    0X88,	/* ASCII=EBCDIC decimal:104=136, octal:150=210, hex:0X68=0X88 */
	    0X89,	/* ASCII=EBCDIC decimal:105=137, octal:151=211, hex:0X69=0X89 */
	    0X91,	/* ASCII=EBCDIC decimal:106=145, octal:152=221, hex:0X6A=0X91 */
	    0X92,	/* ASCII=EBCDIC decimal:107=146, octal:153=222, hex:0X6B=0X92 */
	    0X93,	/* ASCII=EBCDIC decimal:108=147, octal:154=223, hex:0X6C=0X93 */
	    0X94,	/* ASCII=EBCDIC decimal:109=148, octal:155=224, hex:0X6D=0X94 */
	    0X95,	/* ASCII=EBCDIC decimal:110=149, octal:156=225, hex:0X6E=0X95 */
		 0X96,	/* ASCII=EBCDIC decimal:111=150, octal:157=226, hex:0X6F=0X96 */
	    0X97,	/* ASCII=EBCDIC decimal:112=151, octal:160=227, hex:0X70=0X97 */
	    0X98,	/* ASCII=EBCDIC decimal:113=152, octal:161=230, hex:0X71=0X98 */
	    0X99,	/* ASCII=EBCDIC decimal:114=153, octal:162=231, hex:0X72=0X99 */
	    0XA2,	/* ASCII=EBCDIC decimal:115=162, octal:163=242, hex:0X73=0XA2 */
	    0XA3,	/* ASCII=EBCDIC decimal:116=163, octal:164=243, hex:0X74=0XA3 */
	    0XA4,	/* ASCII=EBCDIC decimal:117=164, octal:165=244, hex:0X75=0XA4 */
	    0XA5,	/* ASCII=EBCDIC decimal:118=165, octal:166=245, hex:0X76=0XA5 */
	    0XA6,	/* ASCII=EBCDIC decimal:119=166, octal:167=246, hex:0X77=0XA6 */
	    0XA7,	/* ASCII=EBCDIC decimal:120=167, octal:170=247, hex:0X78=0XA7 */
	    0XA8,	/* ASCII=EBCDIC decimal:121=168, octal:171=250, hex:0X79=0XA8 */
	    0XA9,	/* ASCII=EBCDIC decimal:122=169, octal:172=251, hex:0X7A=0XA9 */
	    0XC0,	/* ASCII=EBCDIC decimal:123=192, octal:173=300, hex:0X7B=0XC0 */
	    0X4F,	/* ASCII=EBCDIC decimal:124=079, octal:174=117, hex:0X7C=0X4F */
	    0XD0,	/* ASCII=EBCDIC decimal:125=208, octal:175=320, hex:0X7D=0XD0 */
	    0XA1,	/* ASCII=EBCDIC decimal:126=161, octal:176=241, hex:0X7E=0XA1 */
	    0X07,	/* ASCII=EBCDIC decimal:127=007, octal:177=007, hex:0X7F=0X07 */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX,	/* NO TRANSLATION TO EBCDIC */
	UINT_MAX 	/* NO TRANSLATION TO EBCDIC */
};

static const unsigned int EBCDIC_To_ASCII_List[256] = {
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	    0X09,	/* EBCDIC=ASCII decimal:005=009, octal:005=011, hex:0X05=0X09 */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	    0X7F,	/* EBCDIC=ASCII decimal:007=127, octal:007=177, hex:0X07=0X7F */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	    0X08,	/* EBCDIC=ASCII decimal:022=008, octal:026=010, hex:0X16=0X08 */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	    0X0A,	/* EBCDIC=ASCII decimal:037=010, octal:045=012, hex:0X25=0X0A */
	    0X17,	/* EBCDIC=ASCII decimal:038=023, octal:046=027, hex:0X26=0X17 */
	    0X1B,	/* EBCDIC=ASCII decimal:039=027, octal:047=033, hex:0X27=0X1B */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	    0X05,	/* EBCDIC=ASCII decimal:045=005, octal:055=005, hex:0X2D=0X05 */
	    0X06,	/* EBCDIC=ASCII decimal:046=006, octal:056=006, hex:0X2E=0X06 */
	    0X07,	/* EBCDIC=ASCII decimal:047=007, octal:057=007, hex:0X2F=0X07 */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	    0X16,	/* EBCDIC=ASCII decimal:050=022, octal:062=026, hex:0X32=0X16 */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	    0X04,	/* EBCDIC=ASCII decimal:055=004, octal:067=004, hex:0X37=0X04 */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	    0X14,	/* EBCDIC=ASCII decimal:060=020, octal:074=024, hex:0X3C=0X14 */
	    0X15,	/* EBCDIC=ASCII decimal:061=021, octal:075=025, hex:0X3D=0X15 */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	    0X1A,	/* EBCDIC=ASCII decimal:063=026, octal:077=032, hex:0X3F=0X1A */
	    0X20,	/* EBCDIC=ASCII decimal:064=032, octal:100=040, hex:0X40=0X20 */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	    0X5B,	/* EBCDIC=ASCII decimal:074=091, octal:112=133, hex:0X4A=0X5B */
	    0X2E,	/* EBCDIC=ASCII decimal:075=046, octal:113=056, hex:0X4B=0X2E */
	    0X3C,	/* EBCDIC=ASCII decimal:076=060, octal:114=074, hex:0X4C=0X3C */
	    0X28,	/* EBCDIC=ASCII decimal:077=040, octal:115=050, hex:0X4D=0X28 */
	    0X2B,	/* EBCDIC=ASCII decimal:078=043, octal:116=053, hex:0X4E=0X2B */
	    0X7C,	/* EBCDIC=ASCII decimal:079=124, octal:117=174, hex:0X4F=0X7C */
	    0X26,	/* EBCDIC=ASCII decimal:080=038, octal:120=046, hex:0X50=0X26 */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	    0X5D,	/* EBCDIC=ASCII decimal:090=093, octal:132=135, hex:0X5A=0X5D */
	    0X24,	/* EBCDIC=ASCII decimal:091=036, octal:133=044, hex:0X5B=0X24 */
	    0X2A,	/* EBCDIC=ASCII decimal:092=042, octal:134=052, hex:0X5C=0X2A */
	    0X29,	/* EBCDIC=ASCII decimal:093=041, octal:135=051, hex:0X5D=0X29 */
	    0X3B,	/* EBCDIC=ASCII decimal:094=059, octal:136=073, hex:0X5E=0X3B */
	    0X5E,	/* EBCDIC=ASCII decimal:095=094, octal:137=136, hex:0X5F=0X5E */
	    0X2D,	/* EBCDIC=ASCII decimal:096=045, octal:140=055, hex:0X60=0X2D */
	    0X2F,	/* EBCDIC=ASCII decimal:097=047, octal:141=057, hex:0X61=0X2F */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	    0X2C,	/* EBCDIC=ASCII decimal:107=044, octal:153=054, hex:0X6B=0X2C */
	    0X25,	/* EBCDIC=ASCII decimal:108=037, octal:154=045, hex:0X6C=0X25 */
	    0X5F,	/* EBCDIC=ASCII decimal:109=095, octal:155=137, hex:0X6D=0X5F */
	    0X3E,	/* EBCDIC=ASCII decimal:110=062, octal:156=076, hex:0X6E=0X3E */
	    0X3F,	/* EBCDIC=ASCII decimal:111=063, octal:157=077, hex:0X6F=0X3F */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	    0X60,	/* EBCDIC=ASCII decimal:121=096, octal:171=140, hex:0X79=0X60 */
	    0X3A,	/* EBCDIC=ASCII decimal:122=058, octal:172=072, hex:0X7A=0X3A */
	    0X23,	/* EBCDIC=ASCII decimal:123=035, octal:173=043, hex:0X7B=0X23 */
	    0X40,	/* EBCDIC=ASCII decimal:124=064, octal:174=100, hex:0X7C=0X40 */
		 0X27,	/* EBCDIC=ASCII decimal:125=039, octal:175=047, hex:0X7D=0X27 */
	    0X3D,	/* EBCDIC=ASCII decimal:126=061, octal:176=075, hex:0X7E=0X3D */
	    0X22,	/* EBCDIC=ASCII decimal:127=034, octal:177=042, hex:0X7F=0X22 */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	    0X61,	/* EBCDIC=ASCII decimal:129=097, octal:201=141, hex:0X81=0X61 */
	    0X62,	/* EBCDIC=ASCII decimal:130=098, octal:202=142, hex:0X82=0X62 */
	    0X63,	/* EBCDIC=ASCII decimal:131=099, octal:203=143, hex:0X83=0X63 */
	    0X64,	/* EBCDIC=ASCII decimal:132=100, octal:204=144, hex:0X84=0X64 */
	    0X65,	/* EBCDIC=ASCII decimal:133=101, octal:205=145, hex:0X85=0X65 */
	    0X66,	/* EBCDIC=ASCII decimal:134=102, octal:206=146, hex:0X86=0X66 */
	    0X67,	/* EBCDIC=ASCII decimal:135=103, octal:207=147, hex:0X87=0X67 */
	    0X68,	/* EBCDIC=ASCII decimal:136=104, octal:210=150, hex:0X88=0X68 */
	    0X69,	/* EBCDIC=ASCII decimal:137=105, octal:211=151, hex:0X89=0X69 */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	    0X6A,	/* EBCDIC=ASCII decimal:145=106, octal:221=152, hex:0X91=0X6A */
		 0X6B,	/* EBCDIC=ASCII decimal:146=107, octal:222=153, hex:0X92=0X6B */
	    0X6C,	/* EBCDIC=ASCII decimal:147=108, octal:223=154, hex:0X93=0X6C */
	    0X6D,	/* EBCDIC=ASCII decimal:148=109, octal:224=155, hex:0X94=0X6D */
	    0X6E,	/* EBCDIC=ASCII decimal:149=110, octal:225=156, hex:0X95=0X6E */
	    0X6F,	/* EBCDIC=ASCII decimal:150=111, octal:226=157, hex:0X96=0X6F */
	    0X70,	/* EBCDIC=ASCII decimal:151=112, octal:227=160, hex:0X97=0X70 */
	    0X71,	/* EBCDIC=ASCII decimal:152=113, octal:230=161, hex:0X98=0X71 */
	    0X72,	/* EBCDIC=ASCII decimal:153=114, octal:231=162, hex:0X99=0X72 */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	    0X7E,	/* EBCDIC=ASCII decimal:161=126, octal:241=176, hex:0XA1=0X7E */
	    0X73,	/* EBCDIC=ASCII decimal:162=115, octal:242=163, hex:0XA2=0X73 */
	    0X74,	/* EBCDIC=ASCII decimal:163=116, octal:243=164, hex:0XA3=0X74 */
	    0X75,	/* EBCDIC=ASCII decimal:164=117, octal:244=165, hex:0XA4=0X75 */
	    0X76,	/* EBCDIC=ASCII decimal:165=118, octal:245=166, hex:0XA5=0X76 */
	    0X77,	/* EBCDIC=ASCII decimal:166=119, octal:246=167, hex:0XA6=0X77 */
		 0X78,	/* EBCDIC=ASCII decimal:167=120, octal:247=170, hex:0XA7=0X78 */
	    0X79,	/* EBCDIC=ASCII decimal:168=121, octal:250=171, hex:0XA8=0X79 */
	    0X7A,	/* EBCDIC=ASCII decimal:169=122, octal:251=172, hex:0XA9=0X7A */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	    0X7B,	/* EBCDIC=ASCII decimal:192=123, octal:300=173, hex:0XC0=0X7B */
	    0X41,	/* EBCDIC=ASCII decimal:193=065, octal:301=101, hex:0XC1=0X41 */
	    0X42,	/* EBCDIC=ASCII decimal:194=066, octal:302=102, hex:0XC2=0X42 */
	    0X43,	/* EBCDIC=ASCII decimal:195=067, octal:303=103, hex:0XC3=0X43 */
	    0X44,	/* EBCDIC=ASCII decimal:196=068, octal:304=104, hex:0XC4=0X44 */
	    0X45,	/* EBCDIC=ASCII decimal:197=069, octal:305=105, hex:0XC5=0X45 */
	    0X46,	/* EBCDIC=ASCII decimal:198=070, octal:306=106, hex:0XC6=0X46 */
	    0X47,	/* EBCDIC=ASCII decimal:199=071, octal:307=107, hex:0XC7=0X47 */
	    0X48,	/* EBCDIC=ASCII decimal:200=072, octal:310=110, hex:0XC8=0X48 */
	    0X49,	/* EBCDIC=ASCII decimal:201=073, octal:311=111, hex:0XC9=0X49 */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	    0X7D,	/* EBCDIC=ASCII decimal:208=125, octal:320=175, hex:0XD0=0X7D */
		 0X4A,	/* EBCDIC=ASCII decimal:209=074, octal:321=112, hex:0XD1=0X4A */
	    0X4B,	/* EBCDIC=ASCII decimal:210=075, octal:322=113, hex:0XD2=0X4B */
	    0X4C,	/* EBCDIC=ASCII decimal:211=076, octal:323=114, hex:0XD3=0X4C */
	    0X4D,	/* EBCDIC=ASCII decimal:212=077, octal:324=115, hex:0XD4=0X4D */
	    0X4E,	/* EBCDIC=ASCII decimal:213=078, octal:325=116, hex:0XD5=0X4E */
	    0X4F,	/* EBCDIC=ASCII decimal:214=079, octal:326=117, hex:0XD6=0X4F */
	    0X50,	/* EBCDIC=ASCII decimal:215=080, octal:327=120, hex:0XD7=0X50 */
	    0X51,	/* EBCDIC=ASCII decimal:216=081, octal:330=121, hex:0XD8=0X51 */
	    0X52,	/* EBCDIC=ASCII decimal:217=082, octal:331=122, hex:0XD9=0X52 */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	    0X5C,	/* EBCDIC=ASCII decimal:224=092, octal:340=134, hex:0XE0=0X5C */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	    0X53,	/* EBCDIC=ASCII decimal:226=083, octal:342=123, hex:0XE2=0X53 */
	    0X54,	/* EBCDIC=ASCII decimal:227=084, octal:343=124, hex:0XE3=0X54 */
	    0X55,	/* EBCDIC=ASCII decimal:228=085, octal:344=125, hex:0XE4=0X55 */
	    0X56,	/* EBCDIC=ASCII decimal:229=086, octal:345=126, hex:0XE5=0X56 */
		 0X57,	/* EBCDIC=ASCII decimal:230=087, octal:346=127, hex:0XE6=0X57 */
	    0X58,	/* EBCDIC=ASCII decimal:231=088, octal:347=130, hex:0XE7=0X58 */
	    0X59,	/* EBCDIC=ASCII decimal:232=089, octal:350=131, hex:0XE8=0X59 */
	    0X5A,	/* EBCDIC=ASCII decimal:233=090, octal:351=132, hex:0XE9=0X5A */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	    0X30,	/* EBCDIC=ASCII decimal:240=048, octal:360=060, hex:0XF0=0X30 */
	    0X31,	/* EBCDIC=ASCII decimal:241=049, octal:361=061, hex:0XF1=0X31 */
	    0X32,	/* EBCDIC=ASCII decimal:242=050, octal:362=062, hex:0XF2=0X32 */
	    0X33,	/* EBCDIC=ASCII decimal:243=051, octal:363=063, hex:0XF3=0X33 */
	    0X34,	/* EBCDIC=ASCII decimal:244=052, octal:364=064, hex:0XF4=0X34 */
	    0X35,	/* EBCDIC=ASCII decimal:245=053, octal:365=065, hex:0XF5=0X35 */
	    0X36,	/* EBCDIC=ASCII decimal:246=054, octal:366=066, hex:0XF6=0X36 */
	    0X37,	/* EBCDIC=ASCII decimal:247=055, octal:367=067, hex:0XF7=0X37 */
	    0X38,	/* EBCDIC=ASCII decimal:248=056, octal:370=070, hex:0XF8=0X38 */
	    0X39,	/* EBCDIC=ASCII decimal:249=057, octal:371=071, hex:0XF9=0X39 */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX,	/* NO TRANSLATION TO ASCII */
	UINT_MAX 	/* NO TRANSLATION TO ASCII */
};

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	ascii_to_ebcdic

	SYNOPSIS		:	return_ptr = ascii_to_ebcdic(in_ascii_ptr, in_ascii_length,
							out_ebcdic_ptr, missing_value);

						char       *return_ptr;

						const char *in_ascii_ptr;

						size_t      in_ascii_length;

						char       *out_ebcdic_ptr;

						const char *missing_value;

	DESCRIPTION	:	Converts an ASCII string to an EBCDIC string.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_ascii_ptr`` points to the ASCII string to be
						converted.

						(.) ``in_ascii_length`` is the length of the ASCII string
						in ``in_ascii_ptr`` to be converted.

						(.) ``out_ebcdic_ptr`` points to the string into which are
						to be placed the converted characters.

						(.) ``missing_value`` points to the character to be used
						in the output EBCDIC string for ASCII characters which have
						no corresponding EBCDIC equivalent. If this parameter is
						''NULL'', this function will abort the conversion upon
						encountering such characters with an error.

   RETURNS     :  Returns from this function are as follow:

						(.) If the conversion succeeds, a pointer to the string
						``out_ebcdic_ptr`` is returned.

						(.) If this function fails, a ''NULL'' pointer is returned.

	NOTES			:	Note that this function can fail only if the string to
						which the ``in_ascii_ptr`` parameter contains an ASCII
						character for which there is no EBCDIC equivalent and the
						``missing_value`` parameter was passed as ''NULL''.
						
	CAVEATS		:

	SEE ALSO		:	ebcdic_to_ascii

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2018 Michael L. Brock
 
	OUTPUT INDEX:	ascii_to_ebcdic
						ASCII/EBCDIC Conversion Functions:ascii_to_ebcdic
						STRFUNCS:ASCII/EBCDIC Conversion Functions:ascii_to_ebcdic
						String Functions:See STRFUNCS

	PUBLISH XREF:	ascii_to_ebcdic

	PUBLISH NAME:	ascii_to_ebcdic

	ENTRY CLASS	:	ASCII/EBCDIC Conversion Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *ascii_to_ebcdic(const char *in_ascii_ptr, size_t in_ascii_length,
	char *out_ebcdic_ptr, const char *missing_value)
#else
char *ascii_to_ebcdic(in_ascii_ptr, in_ascii_length, out_ebcdic_ptr,
	missing_value)
const char *in_ascii_ptr;
size_t      in_ascii_length;
char       *out_ebcdic_ptr;
const char *missing_value;
#endif /* #ifndef NARGS */
{
	unsigned char *tmp_ptr = ((unsigned char *) out_ebcdic_ptr);

	while (in_ascii_length) {
		if (ASCII_To_EBCDIC_List[*((unsigned char *) in_ascii_ptr)] ==
			UINT_MAX) {
			if (missing_value == NULL) {
				*out_ebcdic_ptr = '\0';
				break;
			}
			*tmp_ptr++ = *missing_value;
		}
		else
			*tmp_ptr++ = ((unsigned char)
				ASCII_To_EBCDIC_List[*((unsigned char *) in_ascii_ptr)]);
		in_ascii_length--;
		in_ascii_ptr++;
	}

	return(out_ebcdic_ptr);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	ebcdic_to_ascii

	SYNOPSIS		:	return_ptr = ebcdic_to_ascii(in_ebcdic_ptr,
							in_ebcdic_length, out_ascii_ptr, missing_value);

						char       *return_ptr;

						const char *in_ebcdic_ptr;

						size_t      in_ebcdic_length;

						char       *out_ascii_ptr;

						const char *missing_value;

	DESCRIPTION	:	Converts an EBCDIC string to an ASCII string.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_ebcdic_ptr`` points to the EBCDIC string to be
						converted.

						(.) ``in_ebcdic_length`` is the length of the EBCDIC string
						in``in_ebcdic_ptr`` to be converted.

						(.) ``out_ascii_ptr`` points to the string into which are
						to be placed the converted characters.

						(.) ``missing_value`` points to the character to be used
						in the output ASCII string for EBCDIC characters which have
						no corresponding ASCII equivalent. If this parameter is
						''NULL'', this function will abort the conversion upon
						encountering such characters with an error.

   RETURNS     :  Returns from this function are as follow:

						(.) If the conversion succeeds, a pointer to the string
						``out_ascii_ptr`` is returned.

						(.) If this function fails, a ''NULL'' pointer is returned.

	NOTES			:	Note that this function can fail only if the string to
						which the ``in_ascii_ptr`` parameter contains an EBCDIC
						character for which there is no ASCII equivalent and the
						``missing_value`` parameter was passed as ''NULL''.

	CAVEATS		:

	SEE ALSO		:	ascii_to_ebcdic

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2018 Michael L. Brock
 
	OUTPUT INDEX:	ebcdic_to_ascii
						ASCII/EBCDIC Conversion Functions:ebcdic_to_ascii
						STRFUNCS:ASCII/EBCDIC Conversion Functions:ebcdic_to_ascii
						String Functions:See STRFUNCS

	PUBLISH XREF:	ebcdic_to_ascii

	PUBLISH NAME:	ebcdic_to_ascii

	ENTRY CLASS	:	ASCII/EBCDIC Conversion Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *ebcdic_to_ascii(const char *in_ebcdic_ptr, size_t in_ebcdic_length,
	char *out_ascii_ptr, const char *missing_value)
#else
char *ebcdic_to_ascii(in_ebcdic_ptr, in_ebcdic_length, out_ascii_ptr,
	missing_value)
const char *in_ebcdic_ptr;
size_t      in_ebcdic_length;
char       *out_ascii_ptr;
const char *missing_value;
#endif /* #ifndef NARGS */
{
	unsigned char *tmp_ptr = ((unsigned char *) out_ascii_ptr);

	while (in_ebcdic_length) {
		if (EBCDIC_To_ASCII_List[*((unsigned char *) in_ebcdic_ptr)] ==
			UINT_MAX) {
			if (missing_value == NULL) {
				*out_ascii_ptr = '\0';
				break;
			}
			*tmp_ptr++ = *missing_value;
		}
		else
			*tmp_ptr++ = ((unsigned char)
				EBCDIC_To_ASCII_List[*((unsigned char *) in_ebcdic_ptr)]);
		in_ebcdic_length--;
		in_ebcdic_ptr++;
	}

	return(out_ascii_ptr);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>
#include <string.h>

#define PROMPT_STRING	"ENTER ASCII>"

COMPAT_FN_DECL(int main, (int argc, char **argv));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;
	char         buffer[512];
	char         ebcdic_buffer[1024];

	fprintf(stderr, "Test routine for function 'ascii_to_ebcdic()'\n");
	fprintf(stderr, "---- ------- --- -------- -------------------\n\n");

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if ((!STRFUNCS_stricmp(argv[count_1], "-h")) ||
			(!STRFUNCS_stricmp(argv[count_1], "-help"))) {
			fprintf(stderr, "USAGE: cat <test-file> | %s\n\n", argv[0]);
			goto EXIT_FUNCTION;
		}
	}

	while ((!feof(stdin)) && (!ferror(stdin))) {
		printf("%s", PROMPT_STRING);
		if (fgets(buffer, sizeof(buffer) - 1, stdin) == NULL)
			break;
		while (*buffer && ((buffer[strlen(buffer) - 1] == '\r') ||
			(buffer[strlen(buffer) - 1] == '\n')))
			buffer[strlen(buffer) - 1] = '\0';
		if ((!STRFUNCS_stricmp(buffer, "QUIT")) ||
			 (!STRFUNCS_stricmp(buffer, "EXIT")))
			break;
		ascii_to_ebcdic(buffer, strlen(buffer), ebcdic_buffer, "?");
		printf("ASCII RESULT: [%s]\n",
			ebcdic_to_ascii(ebcdic_buffer, strlen(buffer), buffer, "@"));
	}

EXIT_FUNCTION:

	return(0);
}

#endif /* #ifdef TEST_MAIN */

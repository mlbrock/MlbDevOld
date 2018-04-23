# ##########################################################################
# ##########################################################################
# Multiple Architecture Source Code Production System (MASCaPS) Version 3
# 	DATFUNCS Library Makefile
# ##########################################################################
#
# File Name       : datfuncs/source/Makefile
#
# File Description: Datfuncs library make file.
#
# Revision History:  1993-07-07 --- Creation.
#                       Michael L. Brock
#                   2015-12-12 --- Modified for use with MASCaPS Version 3.
#                       Michael L. Brock
#
#       Copyright Michael L. Brock 1993 - 2018.
#       Distributed under the Boost Software License, Version 1.0.
#       (See accompanying file LICENSE_1_0.txt or copy at
#       http://www.boost.org/LICENSE_1_0.txt)
#
# ##########################################################################

include ../../.MASCaPS/MakePrefixFirst.mk

CPPFLAGS_ADDED	:=	-I ../../include

TARGET_LIBS	=	libdatfuncs.a

ADF_INCS	=	../../datfuncs.h

SRCS		=	\
			ckstring.c \
			cndaycnt.c \
			cndaymax.c \
			dattojul.c \
			dayofmon.c \
			dc30360.c \
			dcactact.c \
			downame.c \
			dtadj.c \
			dtcmp.c \
			dtformat.c \
			dtnow.c \
			dtok.c \
			dttimev.c \
			dttojul.c \
			dtymdhms.c \
			fixulong.c \
			fixyear.c \
			get0101.c \
			get1231.c \
			getcent.c \
			getday.c \
			getdow.c \
			gethour.c \
			gethsec.c \
			getmdata.c \
			getmin.c \
			getmonth.c \
			getmsec.c \
			getqtr.c \
			getsec.c \
			gettsec.c \
			getweek.c \
			getyear.c \
			hourok.c \
			ingtojul.c \
			isleapyr.c \
			jdateok.c \
			juladj.c \
			julianok.c \
			jultodat.c \
			jultodt.c \
			jultofmt.c \
			jultoing.c \
			jultolon.c \
			jultostr.c \
			jultosyb.c \
			jultoymd.c \
			lontodat.c \
			lontojul.c \
			millisok.c \
			minok.c \
			mndaycnt.c \
			mndaymax.c \
			mnend.c \
			mnstart.c \
			monthok.c \
			nowtojul.c \
			qtrend.c \
			qtrstart.c \
			secok.c \
			ulongnow.c \
			ulongok.c \
			version.c \
			wkend.c \
			wkstart.c \
			yearok.c \
			ymdok.c \
			ymdtojul.c \
			yrdaycnt.c \
			yrdaymax.c \
			yrend.c \
			yrstart.c

# Only the libraries below are needed for TEST_MAIN unit tests in this library.
MLB_LIB_NAMES	=	datfuncs strfuncs

include ../../.MASCaPS/MakeSuffixFirst.mk

# #############################################################################


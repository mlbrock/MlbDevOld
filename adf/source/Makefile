# ##########################################################################
# ##########################################################################
# Multiple Architecture Source Code Production System (MASCaPS) Version 3
# 	Automated Documentation Facility (ADF) Makefile
# ##########################################################################
#
# File Name       : adf/source/Makefile
#
# File Description: Automated Documentation Facility (ADF) library makefile.
#
# Revision History: 1993-07-07 --- Creation.
#                       Michael L. Brock
#                   2026-09-30 --- Modified for use with MASCaPS Version 3.
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

TARGET_LIBS	=	libadf.a

ADF_INCS	=	../../adf.h

SRCS		=	\
			adfcntrl.c \
			adfentry.c \
			adferror.c \
			adffile.c \
			adfrun.c \
			areaname.c \
			argbasic.c \
			argframe.c \
			arghtml.c \
			argman.c \
			argout.c \
			argprep.c \
			cmentryd.c \
			cpdomain.c \
			cpentryd.c \
			cpparad.c \
			cppat.c \
			cpsec.c \
			datframe.c \
			dathtml.c \
			datman.c \
			defspec.c \
			delentry.c \
			docludes.c \
			doindex.c \
			dosrc.c \
			emdef.c \
			emdefc.c \
			emdomain.c \
			empat.c \
			emsec.c \
			entrydat.c \
			fdarea.c \
			fddomain.c \
			fixpara.c \
			fptrsout.c \
			frdomain.c \
			frentryd.c \
			frparad.c \
			frpat.c \
			frsec.c \
			getentry.c \
			getotype.c \
			getparam.c \
			indomain.c \
			inentryd.c \
			infile.c \
			inparad.c \
			inpat.c \
			insec.c \
			logmessg.c \
			matchlst.c \
			matchpat.c \
			optpat.c \
			outascii.c \
			outframe.c \
			outhtml.c \
			outman.c \
			outps.c \
			outrtf.c \
			paany.c \
			paarea.c \
			padomain.c \
			pamain.c \
			papat.c \
			paraform.c \
			pasec.c \
			prepfile.c \
			readdef.c \
			readfile.c \
			readsrc.c \
			strpair.c \
			suppout.c \
			usage.c \
			usebasic.c \
			useframe.c \
			usehtml.c \
			useman.c \
			useout.c \
			useprep.c \
			valmanpg.c

# Only the libraries below are needed for TEST_MAIN unit tests in this library.
MLB_LIB_NAMES	=	adf mlog mtif mfile spffuncs tfread sdtif genfuncs datfuncs strfuncs

include ../../.MASCaPS/MakeSuffixFirst.mk

# ############################################################################


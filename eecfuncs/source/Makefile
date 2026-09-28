# ############################################################################
# ############################################################################
# Multiple Architecture Source Code Production System (MASCaPS) Version 3
# 	Expression Evaluation Calculator (EECFUNCS) Library Makefile
# ############################################################################
#
# File Name       : eecfuncs/source/Makefile
#
# File Description: EECFUNCS library make file.
#
# Revision History: 1996-01-31 --- Creation.
#                       Michael L. Brock
#                   2026-09-28 --- Modified for use with MASCaPS Version 3.
#                       Michael L. Brock
#
#       Copyright Michael L. Brock 1996 - 2018.
#       Distributed under the Boost Software License, Version 1.0.
#       (See accompanying file LICENSE_1_0.txt or copy at
#       http://www.boost.org/LICENSE_1_0.txt)
#
# ############################################################################

include ../../.MASCaPS/MakePrefixFirst.mk

CPPFLAGS_ADDED	:=	-I ../../include

TARGET_LIBS	=	libeecfuncs.a

ADF_INCS	=	../../eecfuncs.h

SRCS		=	\
			cpdatum.c \
			cpfncdef.c \
			cpfncrsv.c \
			cpopalia.c \
			cppfix.c \
			cpsymbol.c \
			cpsymrsv.c \
			crcontrl.c \
			emdatum.c \
			empfix.c \
			emstring.c \
			emsubexp.c \
			evalcore.c \
			form2val.c \
			frcontrl.c \
			frdatum.c \
			frevdata.c \
			frfncdef.c \
			frfncrsv.c \
			fropalia.c \
			frpfix.c \
			frsubexp.c \
			frsymbol.c \
			funccore.c \
			funcdata.c \
			getinfix.c \
			parsedat.c \
			parseit0.c \
			strcnvt.c \
			tstdebug.c

# Only the libraries below are needed for TEST_MAIN unit tests in this library.
MLB_LIB_NAMES	=	eecfuncs strfuncs

include ../../.MASCaPS/MakeSuffixFirst.mk

# ############################################################################


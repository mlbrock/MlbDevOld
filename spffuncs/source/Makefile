# ##########################################################################
# ##########################################################################
# Multiple Architecture Source Code Production System (MASCaPS) Version 3
# 	Specification Parse Facility (SPF) Library Makefile
# ##########################################################################
#
# File Name       : spffuncs/source/Makefile
#
# File Description: Specification parse facility (SPF) library makefile.
#
# Revision History: 1995-08-21 --- Creation.
#                       Michael L. Brock
#                   2026-09-28 --- Modified for use with MASCaPS Version 3.
#                       Michael L. Brock
#
#       Copyright Michael L. Brock 1995 - 2018.
#       Distributed under the Boost Software License, Version 1.0.
#       (See accompanying file LICENSE_1_0.txt or copy at
#       http://www.boost.org/LICENSE_1_0.txt)
#
# ##########################################################################

include ../../.MASCaPS/MakePrefixFirst.mk

CPPFLAGS_ADDED	:=	-I ../../include

TARGET_LIBS	=	libspffuncs.a

ADF_INCS	=	../../spffuncs.h

SRCS		=	\
			alparse.c \
			cpparse.c \
			cpspec.c \
			fdspec.c \
			frcontxt.c \
			frparse.c \
			frspec.c \
			getlocat.c \
			getlstpa.c \
			getsubpa.c \
			incontxt.c \
			inparse.c \
			insfuncs.c \
			inspec.c \
			mlinestr.c \
			pabasic.c \
			pabool.c \
			pacomplx.c \
			pacstr.c \
			pacstrml.c \
			paenum.c \
			pafile.c \
			panumber.c \
			pastr.c \
			pastrml.c \
			pastrver.c \
			patext.c \
			patextml.c \
			rdfile.c \
			setparse.c

# Only the libraries below are needed for TEST_MAIN unit tests in this library.
#MLB_LIB_NAMES	=	mlog mtif mfile sdtif genfuncs strfuncs
MLB_LIB_NAMES	=	spffuncs tfread sdtif genfuncs strfuncs

include ../../.MASCaPS/MakeSuffixFirst.mk

# ############################################################################


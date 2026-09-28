# ############################################################################
# ############################################################################
# Multiple Architecture Source Code Production System (MASCaPS) Version 3
# 	Data Type Alignment (DTA) Library Makefile
# ############################################################################
#
# File Name       : dta/source/Makefile
#
# File Description: Data type Alignment (DTA) library make file.
#
# Revision History: 1993-07-07 --- Creation.
#                       Michael L. Brock
#                   2026-09-28 --- Modified for use with MASCaPS Version 3.
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

TARGET_LIBS	=	libdta.a

ADF_INCS	=	../../dta.h

SRCS		=	\
			allst.c \
			alstr.c \
			alstrlst.c \
			ckmem.c \
			ckstr.c \
			ckstrlst.c \
			cmdata.c \
			cnstrlap.c \
			cnstrlst.c \
			cnstrstr.c \
			cptype.c \
			dtadata.c \
			emdta.c \
			fdtype.c \
			inalign.c \
			lsstr.c \
			lsstralc.c \
			lsstrlen.c \
			normlst.c \
			typeptr.c \
			version.c

# Only the libraries below are needed for TEST_MAIN unit tests in this library.
MLB_LIB_NAMES	=	dta genfuncs strfuncs

include ../../.MASCaPS/MakeSuffixFirst.mk

# ############################################################################


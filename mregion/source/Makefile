# ##########################################################################
# ##########################################################################
# Multiple Architecture Source Code Production System (MASCaPS) Version 3
# 	Memory-mapped Region (MREGION) Library Makefile
# ##########################################################################
#
# File Name       : mregion/source/Makefile
#
# File Description: Memory-mapped region (MREGION) library makefile.
#
# Revision History: 1992-03-23 --- Creation.
#                       Michael L. Brock
#                   2026-09-29 --- Modified for use with MASCaPS Version 3.
#                       Michael L. Brock
#
#       Copyright Michael L. Brock 1992 - 2018.
#       Distributed under the Boost Software License, Version 1.0.
#       (See accompanying file LICENSE_1_0.txt or copy at
#       http://www.boost.org/LICENSE_1_0.txt)
#
# ##########################################################################

include ../../.MASCaPS/MakePrefixFirst.mk

CPPFLAGS_ADDED	:=	-I ../../include

TARGET_LIBS	=	libmregion.a

ADF_INCS	=	../../mregion.h

SRCS		=	\
			alarray.c \
			alctl.c \
			alctlary.c \
			alfil.c \
			alfilary.c \
			alitem.c \
			alreg.c \
			ckctl.c \
			ckfil.c \
			ckreg.c \
			clctl.c \
			clfil.c \
			clreg.c \
			filelen.c \
			filemode.c \
			fopen.c \
			frctl.c \
			frfil.c \
			frreg.c \
			inctl.c \
			infil.c \
			inreg.c \
			mapfil.c \
			mapfopen.c \
			mapopen.c \
			mapreg.c \
			open.c \
			version.c

# Only the libraries below are needed for TEST_MAIN unit tests in this library.
MLB_LIB_NAMES	=	mregion mmi genfuncs strfuncs

include ../../.MASCaPS/MakeSuffixFirst.mk

# ############################################################################


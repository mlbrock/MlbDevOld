# ##########################################################################
# ##########################################################################
# Multiple Architecture Source Code Production System (MASCaPS) Version 3
# 	Memory-mapped Interface (MMI) Library Makefile
# ##########################################################################
#
# File Name       : mmi/source/Makefile
#
# File Description: Memory-mapped Interface (MMI) library makefile.
#
# Revision History: 1998-07-01 --- Creation.
#                       Michael L. Brock
#                   2026-09-29 --- Modified for use with MASCaPS Version 3.
#                       Michael L. Brock
#
#       Copyright Michael L. Brock 1998 - 2018.
#       Distributed under the Boost Software License, Version 1.0.
#       (See accompanying file LICENSE_1_0.txt or copy at
#       http://www.boost.org/LICENSE_1_0.txt)
#
# ##########################################################################

include ../../.MASCaPS/MakePrefixFirst.mk

CPPFLAGS_ADDED	:=	-I ../../include

TARGET_LIBS	=	libmmi.a

ADF_INCS	=	../../mmi.h

SRCS		=	\
			advise.c \
			check.c \
			flags.c \
			lock.c \
			map.c \
			protect.c \
			support.c \
			sync.c \
			unlock.c \
			unmap.c \
			version.c

# Only the libraries below are needed for TEST_MAIN unit tests in this library.
MLB_LIB_NAMES	=	mmi genfuncs strfuncs

include ../../.MASCaPS/MakeSuffixFirst.mk

# ############################################################################


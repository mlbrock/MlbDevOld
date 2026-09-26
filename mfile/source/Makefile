# ##########################################################################
# ##########################################################################
# Multiple Architecture Source Code Production System (MASCaPS) Version 3
# 	Memory-Mapped File (MFILE) Library Makefile
# ##########################################################################
#
# File Name       : sdtif/source/Makefile
#
# File Description: SDTIF library make file.
#
# Revision History: 1993-07-07 --- Creation.
#                       Michael L. Brock
#                   2026--0-26 --- Modified for use with MASCaPS Version 3.
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

TARGET_LIBS	=	libmfile.a

ADF_INCS	=	../../mfile.h

SRCS		=	\
			getstate.c \
			lockfile.c \
			lockglob.c \
			mclose.c \
			mfileval.c \
			mflush.c \
			mgetc.c \
			mgets.c \
			mlogms.c \
			mlogmscn.c \
			mmodeval.c \
			mopen.c \
			mprintf.c \
			mputc.c \
			mputs.c \
			mread.c \
			mremap.c \
			mrewind.c \
			mseek.c \
			msetbuf.c \
			msetflag.c \
			mtell.c \
			mtmpfile.c \
			mtruncat.c \
			munlink.c \
			mwrite.c \
			support.c \
			version.c \
			vmprintf.c

# Only the libraries below are needed for TEST_MAIN unit tests in this library.
MLB_LIB_NAMES	=	mfile strfuncs

include ../../.MASCaPS/MakeSuffixFirst.mk

# #############################################################################


# ##########################################################################
# ##########################################################################
# Multiple Architecture Source Code Production System (MASCaPS) Version 3
# 	System Date/Time Interface Facility (SDTIF) Library Makefile
# ##########################################################################
#
# File Name       : sdtif/source/Makefile
#
# File Description: SDTIF library make file.
#
# Revision History:  1995-11-02 --- Creation.
#                       Michael L. Brock
#                   2015-12-12 --- Modified for use with MASCaPS Version 3.
#                       Michael L. Brock
#
#       Copyright Michael L. Brock 1995 - 2015.
#       Distributed under the Boost Software License, Version 1.0.
#       (See accompanying file LICENSE_1_0.txt or copy at
#       http://www.boost.org/LICENSE_1_0.txt)
#
# ##########################################################################

include ../../.MASCaPS/MakePrefixFirst.mk

CPPFLAGS_ADDED	:=	-I ../../include

TARGET_LIBS	=	libsdtif.a

ADF_INCS	=	../../sdtif.h

SRCS		=	\
			cmtimet.c \
			cmtm.c \
			cmtspec.c \
			cmtval.c \
			cmulong.c \
			fmitimet.c \
			fmitm.c \
			fmitspec.c \
			fmitval.c \
			fmiulong.c \
			fmtimet.c \
			fmtm.c \
			fmtspec.c \
			fmtval.c \
			fmulong.c \
			gettime.c \
			ittspec.c \
			ittval.c \
			sleep.c \
			sttval.c \
			tstdebug.c \
			version.c

# Only the libraries below are needed for TEST_MAIN unit tests in this library.
MLB_LIB_NAMES	=	sdtif strfuncs

include ../../.MASCaPS/MakeSuffixFirst.mk

# #############################################################################


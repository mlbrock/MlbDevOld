# ##########################################################################
# ##########################################################################
# Multiple Architecture Source Code Production System (MASCaPS) Version 3
# 	Multi-Threading Interface Facility (MTIF) Library Makefile
# ##########################################################################
#
# File Name       : mlog/source/Makefile
#
# File Description: Multi-threading interface facility (MTIF) library makefile.
#
# Revision History: 1994-09-09 --- Creation.
#                       Michael L. Brock
#                   2026-09-28 --- Modified for use with MASCaPS Version 3.
#                       Michael L. Brock
#
#       Copyright Michael L. Brock 1994 - 2018.
#       Distributed under the Boost Software License, Version 1.0.
#       (See accompanying file LICENSE_1_0.txt or copy at
#       http://www.boost.org/LICENSE_1_0.txt)
#
# ##########################################################################

include ../../.MASCaPS/MakePrefixFirst.mk

CPPFLAGS_ADDED	:=	-I ../../include

TARGET_LIBS	=	libmtif.a

ADF_INCS	=	../../mtif.h

SRCS		=	\
			mtrcheck.c \
			mtrdata.c \
			mtrdest.c \
			mtrinit.c \
			mtrlock.c \
			mtrtlock.c \
			mtrulock.c \
			mtxcheck.c \
			mtxdata.c \
			mtxdest.c \
			mtxinit.c \
			mtxlock.c \
			mtxtlock.c \
			mtxulock.c \
			onccheck.c \
			onconce.c \
			rwlcheck.c \
			rwldata.c \
			rwldest.c \
			rwlinit.c \
			rwllock.c \
			rwltlock.c \
			rwlulock.c \
			support.c \
			thrcreat.c \
			threqual.c \
			threxit.c \
			thrjoin.c \
			thrprio.c \
			thrself.c \
			thrselfp.c \
			thryield.c

# Only the libraries below are needed for TEST_MAIN unit tests in this library.
MLB_LIB_NAMES	=	mtif sdtif genfuncs strfuncs

include ../../.MASCaPS/MakeSuffixFirst.mk

# ############################################################################


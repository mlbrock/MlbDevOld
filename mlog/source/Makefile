# ##########################################################################
# ##########################################################################
# Multiple Architecture Source Code Production System (MASCaPS) Version 3
# 	Memory-mapped Logging (MLOG) Library Makefile
# ##########################################################################
#
# File Name       : mlog/source/Makefile
#
# File Description: Memory-mapped logging (MLOG) library makefile.
#
# Revision History: 1992-03-23 --- Creation.
#                       Michael L. Brock
#                   2026-09-28 --- Modified for use with MASCaPS Version 3.
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

TARGET_LIBS	=	libmlog.a

ADF_INCS	=	../../mlog.h

SRCS		=	\
			check.c \
			close.c \
			complete.c \
			domisc.c \
			fopendef.c \
			free.c \
			getstate.c \
			init.c \
			locking.c \
			logbasic.c \
			logdebug.c \
			logerr.c \
			logif.c \
			loginfo.c \
			loglead.c \
			logline.c \
			logpdbug.c \
			logtext.c \
			logwarn.c \
			open.c \
			openlog.c \
			setlgfmt.c \
			setstate.c \
			sync.c

# Only the libraries below are needed for TEST_MAIN unit tests in this library.
MLB_LIB_NAMES	=	mlog mtif mfile sdtif genfuncs strfuncs

include ../../.MASCaPS/MakeSuffixFirst.mk

# ############################################################################


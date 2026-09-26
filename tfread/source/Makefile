# ##########################################################################
# ##########################################################################
# Multiple Architecture Source Code Production System (MASCaPS) Version 3
# 	Text File Reader (TFREAD) Library Makefile
# ##########################################################################
#
# File Name       : tfread/source/Makefile
#
# File Description: TFREAD library make file.
#
# Revision History: 1993-07-07 --- Creation.
#                       Michael L. Brock
#                   2026-09-26 --- Modified for use with MASCaPS Version 3.
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

TARGET_LIBS	=	libtfread.a

ADF_INCS	=	../../tfread.h

SRCS		=	\
			buff.c \
			bufff.c \
			buffm.c \
			buffraw.c \
			buffrawf.c \
			buffrawm.c \
			buffxnl.c \
			buffxnlf.c \
			buffxnlfm.c \
			defdataf.c \
			defdatam.c \
			line.c \
			linef.c \
			linem.c \
			linenoa.c \
			linenoaf.c \
			linenoam.c

# Only the libraries below are needed for TEST_MAIN unit tests in this library.
MLB_LIB_NAMES	=	tfread genfuncs strfuncs

include ../../.MASCaPS/MakeSuffixFirst.mk

# #############################################################################


# ############################################################################
# ############################################################################
# Multiple Architecture Source Code Production System (MASCaPS) Version 3
# 	Doubly-Linked List Support (DLLS) Library Makefile
# ############################################################################
#
# File Name       : dlls/source/Makefile
#
# File Description: Doubly-linked list support (DLLS) library make file.
#
# Revision History: 1993-03-11 --- Creation.
#                       Michael L. Brock
#                   2026-09-28 --- Modified for use with MASCaPS Version 3.
#                       Michael L. Brock
#
#       Copyright Michael L. Brock 1993 - 2018.
#       Distributed under the Boost Software License, Version 1.0.
#       (See accompanying file LICENSE_1_0.txt or copy at
#       http://www.boost.org/LICENSE_1_0.txt)
#
# ############################################################################

include ../../.MASCaPS/MakePrefixFirst.mk

CPPFLAGS_ADDED	:=	-I ../../include

TARGET_LIBS	=	libdlls.a

ADF_INCS	=	../../dlls.h

SRCS		=	\
			addfirst.c \
			addlast.c \
			addnext.c \
			addprev.c \
			check.c \
			create.c \
			delfirst.c \
			dellast.c \
			delnext.c \
			delprev.c \
			delself.c \
			destroy.c \
			getfirst.c \
			getlast.c \
			getlist.c \
			getnext.c \
			getprev.c \
			init.c \
			remfirst.c \
			remlast.c \
			remnext.c \
			remprev.c \
			remself.c \
			reverse.c \
			sort.c \
			swap.c \
			tstdebug.c

# Only the libraries below are needed for TEST_MAIN unit tests in this library.
MLB_LIB_NAMES	=	dlls strfuncs

include ../../.MASCaPS/MakeSuffixFirst.mk

# ############################################################################
 

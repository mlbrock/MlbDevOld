# ############################################################################
# ############################################################################
# Multiple Architecture Source Code Production System (MASCaPS) Version 3
# 	Keyword Matching Logic (KMLFUNCS) Library Makefile
# ############################################################################
#
# File Name       : kmlfuncs/source/Makefile
#
# File Description: Keyword matching logic (KMLFUNCS) library make file.
#
# Revision History: 1998-03-19 --- Creation.
#                       Michael L. Brock
#                   2026-09-28 --- Modified for use with MASCaPS Version 3.
#                       Michael L. Brock
#
#       Copyright Michael L. Brock 1998 - 2018.
#       Distributed under the Boost Software License, Version 1.0.
#       (See accompanying file LICENSE_1_0.txt or copy at
#       http://www.boost.org/LICENSE_1_0.txt)
#
# ############################################################################
#

include ../../.MASCaPS/MakePrefixFirst.mk

CPPFLAGS_ADDED	:=	-I ../../include

TARGET_LIBS	=	libkmlfuncs.a

ADF_INCS	=	../../kmlfuncs.h

SRCS		=	\
			addmatch.c \
			almatch.c \
			buildidx.c \
			catmatch.c \
			clmatch.c \
			cmmatch.c \
			cpblock.c \
			cpcommnt.c \
			cpdomain.c \
			cpkeywrd.c \
			cpmatch.c \
			cpname.c \
			cpoperat.c \
			cpstring.c \
			cpsymbol.c \
			fddomain.c \
			frblock.c \
			frcommnt.c \
			frcontrl.c \
			frdomain.c \
			frkeywrd.c \
			frmatch.c \
			frname.c \
			froperat.c \
			frstring.c \
			frsymbol.c \
			geteol.c \
			getlines.c \
			inblock.c \
			incommnt.c \
			incontrl.c \
			indomain.c \
			inindex.c \
			inkeywrd.c \
			inmatch.c \
			inname.c \
			inoperat.c \
			instring.c \
			insymbol.c \
			mtall.c \
			outhppl.c \
			outhtml.c \
			outstrng.c \
			rmmatch.c \
			stmatch.c \
			testdata.c \
			typename.c

# Only the libraries below are needed for TEST_MAIN unit tests in this library.
MLB_LIB_NAMES	=	kmlfuncs tfread sdtif genfuncs strfuncs

include ../../.MASCaPS/MakeSuffixFirst.mk

# ############################################################################
 

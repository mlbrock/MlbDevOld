# ##########################################################################
# ##########################################################################
# Multiple Architecture Source Code Production System (MASCaPS) Version 3
# 	Member Data Definition Library (MDDL) Library Makefile
# ##########################################################################
#
# File Name       : mddl/source/Makefile
#
# File Description: Member data definition (MDDL) library makefile.
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

TARGET_LIBS	=	libmddl.a

ADF_INCS	=	../../mddl.h

SRCS		=	\
			apmddl.c \
			cpmddl.c \
			displen.c \
			dispname.c \
			dmfld.c \
			dmhead.c \
			dmrec.c \
			dmtrail.c \
			dmtxt.c \
			dmtxtbas.c \
			dmtxtind.c \
			emmddl.c \
			fixalign.c \
			frmddl.c \
			inmddl.c \
			setalign.c \
			speclst.c \
			specstr.c

# Only the libraries below are needed for TEST_MAIN unit tests in this library.
MLB_LIB_NAMES	=	mddl dta strfuncs

include ../../.MASCaPS/MakeSuffixFirst.mk

# ############################################################################


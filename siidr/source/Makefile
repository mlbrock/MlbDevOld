# ##########################################################################
# ##########################################################################
# Multiple Architecture Source Code Production System (MASCaPS) Version 3
# 	Single Index Internal Data Repository (SIIDR) Library Makefile
# Single Index Internal Data Repository Library Makefile
# ##########################################################################
#
# File Name       : siidr/source/Makefile
#
# File Description: Single Index Internal Data Repo library makefile.
#
# Revision History: 1996-04-10 --- Creation.
#                       Michael L. Brock
#                   2026-09-28 --- Modified for use with MASCaPS Version 3.
#                       Michael L. Brock
#
#       Copyright Michael L. Brock 1996 - 2018.
#       Distributed under the Boost Software License, Version 1.0.
#       (See accompanying file LICENSE_1_0.txt or copy at
#       http://www.boost.org/LICENSE_1_0.txt)
#
# ##########################################################################

include ../../.MASCaPS/MakePrefixFirst.mk

CPPFLAGS_ADDED	:=	-I ../../include

TARGET_LIBS	=	libsiidr.a

ADF_INCS	=	../../siidr.h

SRCS		=	\
			alidr.c \
			bularray.c \
			bullist.c \
			ckctl.c \
			ckdata.c \
			ckidr.c \
			ckrelop.c \
			cmbulk.c \
			cmrecord.c \
			cpidr.c \
			cridr.c \
			delall.c \
			delete.c \
			deleteat.c \
			delmatch.c \
			delspec.c \
			fdrecord.c \
			fridr.c \
			getarray.c \
			getat.c \
			getcount.c \
			getfirst.c \
			getlast.c \
			getlist.c \
			getnext.c \
			getprev.c \
			getrec.c \
			idrget.c \
			idrlock.c \
			idrset.c \
			idrtlock.c \
			idrulock.c \
			inidr.c \
			insert.c \
			insertat.c \
			matarray.c \
			match.c \
			matcount.c \
			matlist.c \
			sort.c \
			touch.c \
			tstdebug.c \
			update.c \
			updateat.c

# Only the libraries below are needed for TEST_MAIN unit tests in this library.
#MLB_LIB_NAMES	=	mlog mtif mfile sdtif genfuncs strfuncs
MLB_LIB_NAMES	=	siidr mtif genfuncs sdtif strfuncs

include ../../.MASCaPS/MakeSuffixFirst.mk

# ############################################################################


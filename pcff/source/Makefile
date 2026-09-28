# ##########################################################################
# ##########################################################################
# Multiple Architecture Source Code Production System (MASCaPS) Version 3
# 	Parse Configuration File Facility (PCFF) Library Makefile
# ##########################################################################
#
# File Name       : pcff/source/Makefile
#
# File Description: Parse configuration file facility library makefile.
#
# Revision History: 1993-04-12 --- Creation.
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

TARGET_LIBS	=	libpcff.a

ADF_INCS	=	../../pcff.h

SRCS		=	\
			aditem.c \
			ckdelim.c \
			ckparam.c \
			ckparams.c \
			ckrequir.c \
			ckunknow.c \
			cmitem.c \
			cmlparam.c \
			cmparam.c \
			cpcfg.c \
			cpitem.c \
			cpiphsp.c \
			cpparam.c \
			cpparams.c \
			cpsrc.c \
			crparams.c \
			dlitem.c \
			doparams.c \
			emadf.c \
			emparamd.c \
			fditem.c \
			fixdelim.c \
			flatten.c \
			frcfg.c \
			fritem.c \
			friphsp.c \
			fromfile.c \
			fromlist.c \
			frparam.c \
			frparams.c \
			frsrc.c \
			getlong.c \
			getptext.c \
			gtunknow.c \
			incfg.c \
			initem.c \
			iniphsp.c \
			inparam.c \
			inparams.c \
			inparse.c \
			insrc.c \
			postproc.c \
			procfile.c \
			proclist.c \
			stcfg.c \
			stparam.c \
			tstdebug.c

# Only the libraries below are needed for TEST_MAIN unit tests in this library.
MLB_LIB_NAMES	=	pcff npsl mlog mfile mtif tfread genfuncs sdtif datfuncs strfuncs

include ../../.MASCaPS/MakeSuffixFirst.mk

# ############################################################################


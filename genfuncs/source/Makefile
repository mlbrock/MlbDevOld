# ##########################################################################
# ##########################################################################
# Multiple Architecture Source Code Production System (MASCaPS) Version 3
# 	GENFUNCS Library Makefile
# ##########################################################################
#
# File Name       : genfuncs/source/Makefile
#
# File Description: GENFUNCS library make file.
#
# Revision History:  1993-07-07 --- Creation.
#                       Michael L. Brock
#                   2015-12-12 --- Modified for use with MASCaPS Version 3.
#                       Michael L. Brock
#
#       Copyright Michael L. Brock 1993 - 2016.
#       Distributed under the Boost Software License, Version 1.0.
#       (See accompanying file LICENSE_1_0.txt or copy at
#       http://www.boost.org/LICENSE_1_0.txt)
#
# ##########################################################################

include ../../.MASCaPS/MakePrefixFirst.mk

CPPFLAGS_ADDED	:=	-I ../../include

TARGET_LIBS	=	libgenfuncs.a

ADF_INCS	=	../../genfuncs.h

SRCS		=	\
			align.c \
			alignbas.c \
			allocmsg.c \
			argbasic.c \
			argparse.c \
			cmptimes.c \
			cmptimev.c \
			currdir.c \
			emgalign.c \
			emitbuff.c \
			expandir.c \
			expfpath.c \
			exphostl.c \
			exphosts.c \
			fmtgroce.c \
			fmtitime.c \
			fmttime.c \
			generror.c \
			getmac.c \
			getparam.c \
			getpid.c \
			getpmap.c \
			gettid.c \
			gettime.c \
			hostname.c \
			membr.c \
			membrdmp.c \
			pagesize.c \
			readexlk.c \
			rlimit.c \
			rusage.c \
			sighandl.c \
			sigtext.c \
			textread.c \
			timespec.c \
			timeval.c \
			tostring.c \
			touchmem.c \
			tvalstat.c \
			usage.c \
			usebasic.c \
			usleep.c \
			validptr.c \
			version.c


# Only the libraries below are needed for TEST_MAIN unit tests in this library.
MLB_LIB_NAMES	=	genfuncs sdtif strfuncs

include ../../.MASCaPS/MakeSuffixFirst.mk

# #############################################################################


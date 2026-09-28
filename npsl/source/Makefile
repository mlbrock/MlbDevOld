# ##########################################################################
# ##########################################################################
# Multiple Architecture Source Code Production System (MASCaPS) Version 3
# 	Network Programming Support (NPSL) Library Makefile
# ##########################################################################
#
# File Name       : npsl/source/Makefile
#
# File Description: Network programming support (NPSL) library makefile.
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

TARGET_LIBS	=	libnpsl.a

ADF_INCS	=	../../npsl.h

SRCS		=	\
			accept.c \
			addrinet.c \
			bind.c \
			ckhentp.c \
			ckpentp.c \
			cksentp.c \
			cksock.c \
			cleanup.c \
			close.c \
			connect.c \
			cphent.c \
			cppent.c \
			cpsent.c \
			errortxt.c \
			exphostl.c \
			exphosts.c \
			frhent.c \
			frpent.c \
			frsent.c \
			gethent.c \
			gethentb.c \
			getmac.c \
			getpent.c \
			getpentb.c \
			getpname.c \
			getsent.c \
			getsentb.c \
			getsname.c \
			getsopt.c \
			hostname.c \
			inetaddr.c \
			inhent.c \
			inpent.c \
			insent.c \
			lenshent.c \
			lenspent.c \
			lenssent.c \
			listen.c \
			recv.c \
			recvfrom.c \
			rslvhost.c \
			rslvhsp.c \
			rslvprot.c \
			rslvserv.c \
			select.c \
			send.c \
			sendto.c \
			setbmode.c \
			setsopt.c \
			shutdown.c \
			socket.c \
			startup.c \
			support.c

# Only the libraries below are needed for TEST_MAIN unit tests in this library.
MLB_LIB_NAMES	=	npsl genfuncs strfuncs

include ../../.MASCaPS/MakeSuffixFirst.mk

# ############################################################################


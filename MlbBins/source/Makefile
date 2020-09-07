# #############################################################################
# #############################################################################
# MLB Utilities Executable Programs Make File
# #############################################################################
#
# File Description: Executable programs make file for miscellaneous MLB
#                   utilities.
#
# Revision History: 1993-04-12 --- Creation.
#                       Michael L. Brock
#                   2020-09-07 --- Modified for use with MASCaPS Version 3.
#                       Michael L. Brock
#
#       Copyright Michael L. Brock 1993 - 2020.
#       Distributed under the Boost Software License, Version 1.0.
#       (See accompanying file LICENSE_1_0.txt or copy at
#       http://www.boost.org/LICENSE_1_0.txt)
#
# #############################################################################

include ../../.MASCaPS/MakePrefixFirst.mk

CPPFLAGS_ADDED	:=	-I ../../include -I ../../CppSupp/include

TARGET_BINS	=	\
			sockicpt

SRCS		=

#LINK_STATIC	=	${LINK_STATIC_STD}

# Only the MLB libraries below are needed for the executables in this Makefile.
MLB_LIB_NAMES	=	npsl genfuncs sdtif strfuncs

LDLIBS		:=	-L${LIB_PCAP_DIR} -lpcap ${LDLIBS}

include ../../.MASCaPS/MakeSuffixFirst.mk


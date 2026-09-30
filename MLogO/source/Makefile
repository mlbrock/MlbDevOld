# ##########################################################################
# ##########################################################################
# Multiple Architecture Source Code Production System (MASCaPS) Version 3
# 	Memory-mapped Logging C++ (MLogO) Library Makefile
# ##########################################################################
#
# File Name       : MLogO/source/Makefile
#
# File Description: Memory-mapped logging C++ (MLogO)  makefile.
#
# Revision History: 2001-10-10 --- Creation.
#                       Michael L. Brock
#                   2026-09-30 --- Modified for use with MASCaPS Version 3.
#                       Michael L. Brock
#
#       Copyright Michael L. Brock 2001 - 2018.
#       Distributed under the Boost Software License, Version 1.0.
#       (See accompanying file LICENSE_1_0.txt or copy at
#       http://www.boost.org/LICENSE_1_0.txt)
#
# ##########################################################################

include ../../.MASCaPS/MakePrefixFirst.mk

CPPFLAGS_ADDED	:=	-I ../../include

TARGET_LIBS	=	libmlogo.a

ADF_INCS	=       ../../include/MLogO.hpp

SRCS		=	\
			MLogO.cpp

# Only the libraries below are needed for TEST_MAIN unit tests in this library.
MLB_LIB_NAMES	=	mlogo mlog mtifo mtif sdtif genfuncs strfuncs

include ../../.MASCaPS/MakeSuffixFirst.mk

# ############################################################################


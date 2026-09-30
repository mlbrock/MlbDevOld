# ##########################################################################
# ##########################################################################
# Multiple Architecture Source Code Production System (MASCaPS) Version 3
# 	Network Programming Support C++ Library (NpslO) Makefile
# ##########################################################################
#
# File Name       : NpslO/source/Makefile
#
# File Description: Network programming support C++ library (NpslO) makefile.
#
# Revision History: 2002-01-26 --- Creation.
#                       Michael L. Brock
#                   2026-09-30 --- Modified for use with MASCaPS Version 3.
#                       Michael L. Brock
#
#       Copyright Michael L. Brock 2002 - 2018.
#       Distributed under the Boost Software License, Version 1.0.
#       (See accompanying file LICENSE_1_0.txt or copy at
#       http://www.boost.org/LICENSE_1_0.txt)
#
# ##########################################################################

include ../../.MASCaPS/MakePrefixFirst.mk

CPPFLAGS_ADDED	:=	-I ../../include \
			-I ../../CppSupp/include

TARGET_LIBS	=	libnpslo.a

ADF_INCS	=       ../../include/NpslO.hpp

SRCS		=	\
			NpslO.cpp

# Only the libraries below are needed for TEST_MAIN unit tests in this library.
MLB_LIB_NAMES	=	npslo npsl mlogo mlog mtifo mtif sdtif genfuncs strfuncs

include ../../.MASCaPS/MakeSuffixFirst.mk

# ############################################################################


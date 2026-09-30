# ##########################################################################
# ##########################################################################
# Multiple Architecture Source Code Production System (MASCaPS) Version 3
# 	Multi-Threading Interface Facility C++ (MtifO) Library Makefile
# ##########################################################################
#
# File Name       : MtifO/source/Makefile
#
# File Description: Multi-threading interface facility C++ (MtifO) makefile.
#
# Revision History: 2000-03-02 --- Creation.
#                       Michael L. Brock
#                   2026-09-30 --- Modified for use with MASCaPS Version 3.
#                       Michael L. Brock
#
#       Copyright Michael L. Brock 2000 - 2018.
#       Distributed under the Boost Software License, Version 1.0.
#       (See accompanying file LICENSE_1_0.txt or copy at
#       http://www.boost.org/LICENSE_1_0.txt)
#
# ##########################################################################

include ../../.MASCaPS/MakePrefixFirst.mk

CPPFLAGS_ADDED	:=	-I ../../include

TARGET_LIBS	=	libmtifo.a

ADF_INCS	=	\
			../../include/MTIF_MtrO.hpp \
			../../include/MTIF_MtxO.hpp \
			../../include/MTIF_NullO.hpp \
			../../include/MTIF_RwlO.hpp

SRCS		=	\
			MTIF_MtrO.cpp \
			MTIF_MtxO.cpp \
			MTIF_NullO.cpp \
			MTIF_RwlO.cpp

# Only the libraries below are needed for TEST_MAIN unit tests in this library.
MLB_LIB_NAMES	=	mtifo mtif sdtif genfuncs strfuncs

include ../../.MASCaPS/MakeSuffixFirst.mk

# ############################################################################


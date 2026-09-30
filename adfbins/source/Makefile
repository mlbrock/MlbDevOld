# ##########################################################################
# ##########################################################################
# Multiple Architecture Source Code Production System (MASCaPS) Version 3
# 	Automated Documentation Facility (ADF) Binaries Makefile
# ##########################################################################
#
# File Name       : adfbins/source/Makefile
#
# File Description: Automated Documentation Facility (ADF) binaries makefile.
#
# Revision History: 1993-07-07 --- Creation.
#                       Michael L. Brock
#                   2026-09-30 --- Modified for use with MASCaPS Version 3.
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

ADF_INCS	=	../../adf.h

TARGET_BINS	=	\
			adfcomb \
			adfdefc \
			adfdefd \
			adfdiff \
			adfout  \
			adfprep \
			adfrefsa \
			adfsize

# Only the libraries below are needed for TEST_MAIN unit tests in this library.
MLB_LIB_NAMES	=	adf mlog mfile spffuncs tfread mtif sdtif genfuncs datfuncs strfuncs

include ../../.MASCaPS/MakeSuffixFirst.mk

# ############################################################################


# ############################################################################
# ############################################################################
# Expression Evaluation Calculator Library (EECFUNCS) Makefile
# ############################################################################
#
#    File Name          :  %M%
#
#    File Version       :  %I%
#
#    Last Extracted     :  %D%	%T%
#
#    Last Updated       :  %E%	%U%
#
#    File Description   :  This is the make file for the EECFUNCS library.
#
#    Revision History   :  1996-01-31 --- Creation.
#                             Michael L. Brock
#
#       Copyright Michael L. Brock 1996 - 2014.
#       Distributed under the Boost Software License, Version 1.0.
#       (See accompanying file LICENSE_1_0.txt or copy at
#       http://www.boost.org/LICENSE_1_0.txt)
#
# ############################################################################
#

.KEEP_STATE:

# Paths necessary to find the 'local' makefile . . .
THIS_HOME:sh				=	echo $HOME
 
# Include directive for the 'local' makefile . . .
include ${THIS_HOME}/src/.MASCAPS/premake.mk
 
#This is the the list of targets for this makefile . . .
TARGET_LIBS					=	eecfuncs.a

TARGET_BINS					=	\
									tstcalc1 \
									tstcalc2 \
									tstcalc3

ADF_INCS						=	${INCLUDE_DIR}/eecfuncs.h

# source
SRCS							=	\
									cpdatum.c \
									cpfncdef.c \
									cpfncrsv.c \
									cpopalia.c \
									cppfix.c \
									cpsymbol.c \
									cpsymrsv.c \
									crcontrl.c \
									emdatum.c \
									empfix.c \
									emstring.c \
									emsubexp.c \
									evalcore.c \
									form2val.c \
									frcontrl.c \
									frdatum.c \
									frevdata.c \
									frfncdef.c \
									frfncrsv.c \
									fropalia.c \
									frpfix.c \
									frsubexp.c \
									frsymbol.c \
									funccore.c \
									funcdata.c \
									getinfix.c \
									parsedat.c \
									parseit0.c \
									strcnvt.c \
									tstdebug.c

TEST_LIST					=	\
									test_evalcore \
									test_getinfix \
									test_parseit0

LIBS							=	${TARGET_LIBS} ${LOCAL_LIBS}

# Here's how we make the targets . . .
all							: ${TARGET_LIBS} ${TARGET_BINS}

# Here's how we make the target executables . . .
tstcalc1						:	${LIBS} tstcalc1.o
	$(LINK.c) -o $@ $@.o $(LIBS)

tstcalc2						:	${LIBS} tstcalc2.o
	$(LINK.c) -o $@ $@.o $(LIBS)

tstcalc3						:	${LIBS} tstcalc3.o
	$(LINK.c) -o $@ $@.o $(LIBS)

# Here's how we make the target library . . .
eecfuncs.a	          	: ${OBJS}
	@${AR} ${ARFLAGS} $@ ${OBJS}
	@ranlib $@
	@cp -p $@ ${LOCAL_LIB_DIR}/.
 
# We include some useful ancillary targets here . . .
include ${THIS_HOME}/src/.MASCAPS/postmake.mk
#
# ############################################################################
 

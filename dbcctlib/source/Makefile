# ############################################################################
# ############################################################################
# DBC Sybase CT-Library Support Functions Library (DBCCTLIB) Makefile
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
#    File Description   :  This is the make file for the DBCCTLIB library.
#
#    Revision History   :  1996-06-19 --- Creation.
#                             Michael L. Brock
#
#       Copyright Michael L. Brock 1996 - 2015.
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
TARGET_LIBS					=	dbcctlib.a

# ########## Sybase include files aren't all they could be . . .
POST_GCC_CFLAGS			=	-Wno-strict-prototypes

ADF_INCS						=	${INCLUDE_DIR}/dbcctlib.h

# source
SRCS							=	\
									attach.c \
									attachme.c \
									bind.c \
									cancel.c \
									close.c \
									dosql.c \
									getid.c \
									getrows.c \
									getvend.c \
									handler.c \
									init.c \
									open.c \
									version.c

LIBS							=	${TARGET_LIBS} ${LOCAL_LIBS}

# Here's how we make the targets . . .
all							: ${TARGET_LIBS} ${TARGET_BINS}

# Here's how we make the target library . . .
${TARGET_LIBS}         	: ${OBJS}
	@${AR} ${ARFLAGS} $@ ${OBJS}
	@ranlib $@
	@cp -p $@ ${LOCAL_LIB_DIR}/.
 
# We include some useful ancillary targets here . . .
include ${THIS_HOME}/src/.MASCAPS/postmake.mk
#
# ############################################################################
 

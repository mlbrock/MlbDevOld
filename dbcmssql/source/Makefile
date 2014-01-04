# ############################################################################
# ############################################################################
# DBC Micosoft SQL Server Support Functions Library (DBCMSSQL) Makefile
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
#    File Description   :  This is the make file for the DBCMSSQL library.
#
#    Revision History   :  1995-01-29 --- Creation.
#                             Michael L. Brock
#
#       Copyright Michael L. Brock 1995 - 2014.
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
TARGET_LIBS					=	NEW_dbcmssql.a

# ########## Sybase include files aren't all they could be . . .
POST_GCC_CFLAGS			=	-Wno-strict-prototypes

PRE_INCLUDES				=	-I../NEW_dbcfuncs/ -I../NEW_dbcsyb

ADF_INCS						=	${INCLUDE_DIR}/dbcmssql.h

# source
SRCS							=	\
									attach.c \
									attachme.c \
									bind.c \
									cancel.c \
									close.c \
									connect.c \
									dosql.c \
									getid.c \
									getrows.c \
									getvend.c \
									handler.c \
									init.c \
									open.c \
									version.c

LIBS							=	${TARGET_LIBS} \
									../NEW_dbcfuncs/NEW_dbcfuncs.a \
									../NEW_dbcsyb/NEW_dbcsyb.a \
									../NEW_dbcfuncs/NEW_dbcfuncs.a \
									${LOCAL_LIBS}

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
 

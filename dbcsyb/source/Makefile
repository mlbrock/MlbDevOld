# ############################################################################
# ############################################################################
# DBC Generic Sybase Support Functions Library (DBCSYB) Makefile
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
#    File Description   :  This is the make file for the DBCSYB library.
#
#    Revision History   :  1993-07-07 --- Creation.
#                             Michael L. Brock
#
#       Copyright Michael L. Brock 1993 - 2015.
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
TARGET_LIBS					=	dbcsyb.a

# ########## Sybase include files aren't all they could be . . .
POST_GCC_CFLAGS			=	-Wno-strict-prototypes

ADF_INCS						=	${INCLUDE_DIR}/dbcsyb.h

# source
SRCS							=	\
									brknames.c \
									cmdate.c \
									cmdbdate.c \
									cmnumber.c \
									cmtime.c \
									cndbdate.c \
									cnmoney.c \
									coltomem.c \
									date2dt.c \
									datemisc.c \
									dbl2num.c \
									defnames.c \
									dt2date.c \
									dt2time.c \
									dufld.c \
									emcol.c \
									emdb.c \
									emdbcol.c \
									emdbdb.c \
									emdbidx.c \
									emidx.c \
									fdtype.c \
									fmtsql.c \
									fmttype.c \
									getcol.c \
									getdb.c \
									getdbcol.c \
									getdbdb.c \
									getdbidx.c \
									getdname.c \
									getidx.c \
									getname.c \
									gettname.c \
									issysdb.c \
									issystbl.c \
									maptype.c \
									num2dbl.c \
									nummisc.c \
									paconn.c \
									setdlen.c \
									tbltomem.c \
									time2dt.c \
									timemisc.c \
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
 

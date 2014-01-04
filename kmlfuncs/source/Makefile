# ############################################################################
# ############################################################################
# Keyword Matching Logic (KMLFUNCS) Library (KMLFUNCS) Makefile
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
#    File Description   :  This is the make file for the KMLFUNCS libraries
#			   and executables. It conforms to the MASCaPS
#			   standard.
#
#    Revision History   :  1998-03-19 --- Creation.
#                             Michael L. Brock
#
#       Copyright Michael L. Brock 1998 - 2014.
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
TARGET_LIBS					=	kmlfuncs.a

ADF_INCS						=	${INCLUDE_DIR}/kmlfuncs.h

# source
SRCS							=	\
									addmatch.c \
									almatch.c \
									buildidx.c \
									catmatch.c \
									clmatch.c \
									cmmatch.c \
									cpblock.c \
									cpcommnt.c \
									cpdomain.c \
									cpkeywrd.c \
									cpmatch.c \
									cpname.c \
									cpoperat.c \
									cpstring.c \
									cpsymbol.c \
									fddomain.c \
									frblock.c \
									frcommnt.c \
									frcontrl.c \
									frdomain.c \
									frkeywrd.c \
									frmatch.c \
									frname.c \
									froperat.c \
									frstring.c \
									frsymbol.c \
									geteol.c \
									getlines.c \
									inblock.c \
									incommnt.c \
									incontrl.c \
									indomain.c \
									inindex.c \
									inkeywrd.c \
									inmatch.c \
									inname.c \
									inoperat.c \
									instring.c \
									insymbol.c \
									mtall.c \
									outhppl.c \
									outhtml.c \
									outstrng.c \
									rmmatch.c \
									stmatch.c \
									testdata.c \
									typename.c

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
 

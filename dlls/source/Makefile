# ############################################################################
# ############################################################################
# Doubly-Linked List Support (DLLS) Library Makefile
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
#    File Description   :  This is the make file for the DLLS library.
#
#    Revision History   :  1993-03-11 --- Creation.
#                             Michael L. Brock
#
#       Copyright Michael L. Brock 1993 - 2014.
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
TARGET_LIBS					=	dlls.a

# ########## Sybase include files aren't all they could be . . .
POST_GCC_CFLAGS			=	-Wno-strict-prototypes

ADF_INCS						=	${INCLUDE_DIR}/dlls.h

# source
SRCS							=	\
									addfirst.c \
									addlast.c \
									addnext.c \
									addprev.c \
									check.c \
									create.c \
									delfirst.c \
									dellast.c \
									delnext.c \
									delprev.c \
									delself.c \
									destroy.c \
									getfirst.c \
									getlast.c \
									getlist.c \
									getnext.c \
									getprev.c \
									init.c \
									remfirst.c \
									remlast.c \
									remnext.c \
									remprev.c \
									remself.c \
									reverse.c \
									sort.c \
									swap.c \
									tstdebug.c

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
 

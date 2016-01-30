# ##########################################################################
# ##########################################################################
# MMAP Library Makefile
# ##########################################################################
#
#    File Name          :  %M%
#
#    File Version       :  %I%
#
#    Last Extracted     :  %D%	%T%
#
#    Last Updated       :  %E%	%U%
#
#    File Description   :  This is the make file for the MMI library.
#
#    Revision History   :  1998-07-01 --- Creation.
#                             Michael L. Brock
#
#       Copyright Michael L. Brock 1998 - 2016.
#       Distributed under the Boost Software License, Version 1.0.
#       (See accompanying file LICENSE_1_0.txt or copy at
#       http://www.boost.org/LICENSE_1_0.txt)
#
# ##########################################################################

.KEEP_STATE:

THIS_HOME:sh				=	echo $HOME

include ${THIS_HOME}/src/.MASCAPS/premake.mk

TARGET_LIBS					=	mmi.a

#ADF_INCS						=	${INCLUDE_DIR}/mmi.h

SRCS							=	\
									advise.c \
									check.c \
									flags.c \
									lock.c \
									map.c \
									protect.c \
									support.c \
									sync.c \
									unlock.c \
									unmap.c \
									version.c

LIBS							=	${TARGET_LIBS} ${LOCAL_LIBS}

${TARGET_LIBS}				:	${OBJS}
	@${AR} ${ARFLAGS} $@ ${OBJS}
	@ranlib $@
	@cp -p $@ ${LOCAL_LIB_DIR}/.

include ${THIS_HOME}/src/.MASCAPS/postmake.mk


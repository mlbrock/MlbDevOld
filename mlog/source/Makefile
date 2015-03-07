# ##########################################################################
# ##########################################################################
# MLOG Memory-mapped Logging Library Makefile
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
#    File Description   :  This is the make file for the MLOG library.
#
#    Revision History   :  1992-03-23 --- Creation.
#                             Michael L. Brock
#
#       Copyright Michael L. Brock 1992 - 2015.
#       Distributed under the Boost Software License, Version 1.0.
#       (See accompanying file LICENSE_1_0.txt or copy at
#       http://www.boost.org/LICENSE_1_0.txt)
#
# ##########################################################################

.KEEP_STATE:

THIS_HOME:sh				=	echo $HOME

include ${THIS_HOME}/src/.MASCAPS/premake.mk

TARGET_LIBS					=	mlog.a

ADF_INCS						=	${INCLUDE_DIR}/mlog.h

SRCS							=	\
									check.c \
									close.c \
									complete.c \
									domisc.c \
									fopendef.c \
									free.c \
									getstate.c \
									init.c \
									locking.c \
									logbasic.c \
									logdebug.c \
									logerr.c \
									logif.c \
									loginfo.c \
									loglead.c \
									logline.c \
									logpdbug.c \
									logtext.c \
									logwarn.c \
									open.c \
									openlog.c \
									setlgfmt.c \
									setstate.c \
									sync.c

LIBS							=	${TARGET_LIBS} ${LOCAL_LIBS}

${TARGET_LIBS}				:	${OBJS}
	@${AR} ${ARFLAGS} $@ ${OBJS}
	@ranlib $@
	@cp -p $@ ${LOCAL_LIB_DIR}/.

include ${THIS_HOME}/src/.MASCAPS/postmake.mk


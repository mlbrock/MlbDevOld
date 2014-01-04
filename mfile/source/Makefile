# ##########################################################################
# ##########################################################################
# MFILE Library Makefile
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
#    File Description   :  This is the make file for the MFILE library.
#
#    Revision History   :  1993-07-07 --- Creation.
#                             Michael L. Brock
#
#       Copyright Michael L. Brock 1993 - 2014.
#       Distributed under the Boost Software License, Version 1.0.
#       (See accompanying file LICENSE_1_0.txt or copy at
#       http://www.boost.org/LICENSE_1_0.txt)
#
# ##########################################################################

.KEEP_STATE:

THIS_HOME:sh				=	echo $HOME

include ${THIS_HOME}/src/.MASCAPS/premake.mk

TARGET_LIBS					=	mfile.a

ADF_INCS						=	${INCLUDE_DIR}/mfile.h

SRCS							=	\
									getstate.c \
									lockfile.c \
									lockglob.c \
									mclose.c \
									mfileval.c \
									mflush.c \
									mgetc.c \
									mgets.c \
									mlogms.c \
									mlogmscn.c \
									mmodeval.c \
									mopen.c \
									mprintf.c \
									mputc.c \
									mputs.c \
									mread.c \
									mremap.c \
									mrewind.c \
									mseek.c \
									msetbuf.c \
									msetflag.c \
									mtell.c \
									mtmpfile.c \
									mtruncat.c \
									munlink.c \
									mwrite.c \
									support.c \
									version.c \
									vmprintf.c

#LIBS							=	${TARGET_LIBS} ${LOCAL_LIBS}
LIBS							=	${TARGET_LIBS} ../lib/genfuncs.a ../lib/strfuncs.a

${TARGET_LIBS}				:	${OBJS}
	@${AR} ${ARFLAGS} $@ ${OBJS}
	@ranlib $@
	@cp -p $@ ${LOCAL_LIB_DIR}/.

include ${THIS_HOME}/src/.MASCAPS/postmake.mk


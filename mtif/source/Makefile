# ##########################################################################
# ##########################################################################
# MTIF Library Makefile
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
#    File Description   :  This is the make file for the MTIF library.
#
#    Revision History   :  1994-09-09 --- Creation.
#                             Michael L. Brock
#
#       Copyright Michael L. Brock 1994 - 2018.
#       Distributed under the Boost Software License, Version 1.0.
#       (See accompanying file LICENSE_1_0.txt or copy at
#       http://www.boost.org/LICENSE_1_0.txt)
#
# ##########################################################################

.KEEP_STATE:

THIS_HOME:sh				=	echo $HOME

include ${THIS_HOME}/src/.MASCAPS/premake.mk

TARGET_LIBS					=	mtif.a

ADF_INCS						=  ${INCLUDE_DIR}/mtif.h

SRCS							=	\
									mtrcheck.c \
									mtrdata.c \
									mtrdest.c \
									mtrinit.c \
									mtrlock.c \
									mtrtlock.c \
									mtrulock.c \
									mtxcheck.c \
									mtxdata.c \
									mtxdest.c \
									mtxinit.c \
									mtxlock.c \
									mtxtlock.c \
									mtxulock.c \
									onccheck.c \
									onconce.c \
									rwlcheck.c \
									rwldata.c \
									rwldest.c \
									rwlinit.c \
									rwllock.c \
									rwltlock.c \
									rwlulock.c \
									support.c \
									thrcreat.c \
									threqual.c \
									threxit.c \
									thrjoin.c \
									thrprio.c \
									thrself.c \
									thrselfp.c \
									thryield.c

LIBS							=	${TARGET_LIBS} ${LOCAL_LIBS} \
									-lpthread \
									${LDFLAGS}

${TARGET_LIBS}				:	${OBJS}
	@${AR} ${ARFLAGS} $@ ${OBJS}
	@ranlib $@
	@cp -p $@ ${LOCAL_LIB_DIR}/.

include ${THIS_HOME}/src/.MASCAPS/postmake.mk


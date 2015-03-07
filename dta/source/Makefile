# ##########################################################################
# ##########################################################################
# DTA Library Makefile
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
#    File Description   :  This is the make file for the DTA library.
#
#    Revision History   :  1993-07-07 --- Creation.
#                             Michael L. Brock
#
#       Copyright Michael L. Brock 1993 - 2015.
#       Distributed under the Boost Software License, Version 1.0.
#       (See accompanying file LICENSE_1_0.txt or copy at
#       http://www.boost.org/LICENSE_1_0.txt)
#
# ##########################################################################

.KEEP_STATE:

THIS_HOME:sh				=	echo $HOME

include ${THIS_HOME}/src/.MASCAPS/premake.mk

TARGET_LIBS					=	dta.a

ADF_INCS						=  ${INCLUDE_DIR}/dta.h

SRCS							=	\
									allst.c \
									alstr.c \
									alstrlst.c \
									ckmem.c \
									ckstr.c \
									ckstrlst.c \
									cmdata.c \
									cnstrlap.c \
									cnstrlst.c \
									cnstrstr.c \
									cptype.c \
									dtadata.c \
									emdta.c \
									fdtype.c \
									inalign.c \
									lsstr.c \
									lsstralc.c \
									lsstrlen.c \
									normlst.c \
									typeptr.c \
									version.c

LIBS							=	${TARGET_LIBS} ${LOCAL_LIBS}

${TARGET_LIBS}				:	${OBJS}
	@${AR} ${ARFLAGS} $@ ${OBJS}
	@ranlib $@
	@cp -p $@ ${LOCAL_LIB_DIR}/.

include ${THIS_HOME}/src/.MASCAPS/postmake.mk


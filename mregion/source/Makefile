# ##########################################################################
# ##########################################################################
# MREGION Memory-mapped Region Library Makefile
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
#    File Description   :  This is the make file for the MREGION library.
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

TARGET_LIBS					=	mregion.a

#ADF_INCS						=	${INCLUDE_DIR}/mregion.h
ADF_INCS						=	mregion.h

CFLAGS                 += -I../mmi

SRCS							=	\
									alarray.c \
									alctl.c \
									alctlary.c \
									alfil.c \
									alfilary.c \
									alitem.c \
									alreg.c \
									ckctl.c \
									ckfil.c \
									ckreg.c \
									clctl.c \
									clfil.c \
									clreg.c \
									filelen.c \
									filemode.c \
									fopen.c \
									frctl.c \
									frfil.c \
									frreg.c \
									inctl.c \
									infil.c \
									inreg.c \
									mapfil.c \
									mapfopen.c \
									mapopen.c \
									mapreg.c \
									open.c \
									version.c

LIBS							=	${TARGET_LIBS} ${LOCAL_LIBS}

${TARGET_LIBS}				:	${OBJS}
	@${AR} ${ARFLAGS} $@ ${OBJS}
	@ranlib $@
	@cp -p $@ ${LOCAL_LIB_DIR}/.

include ${THIS_HOME}/src/.MASCAPS/postmake.mk


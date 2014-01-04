# ##########################################################################
# ##########################################################################
# TFREAD Library Makefile
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
#    File Description   :  This is the make file for the TFREAD library.
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

TARGET_LIBS					=	tfread.a

ADF_INCS						=  ${INCLUDE_DIR}/tfread.h

SRCS							=	\
									buff.c \
									bufff.c \
									buffm.c \
									buffraw.c \
									buffrawf.c \
									buffrawm.c \
									buffxnl.c \
									buffxnlf.c \
									buffxnlfm.c \
									defdataf.c \
									defdatam.c \
									line.c \
									linef.c \
									linem.c \
									linenoa.c \
									linenoaf.c \
									linenoam.c

LIBS							=	${TARGET_LIBS} ${LOCAL_LIBS}

${TARGET_LIBS}				:	${OBJS}
	@${AR} ${ARFLAGS} $@ ${OBJS}
	@ranlib $@
	@cp -p $@ ${LOCAL_LIB_DIR}/.

include ${THIS_HOME}/src/.MASCAPS/postmake.mk


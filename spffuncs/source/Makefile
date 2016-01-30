# ##########################################################################
# ##########################################################################
# SPFFUNCS Library Makefile
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
#    File Description   :  This is the make file for the SPFFUNCS library.
#
#    Revision History   :  1993-07-07 --- Creation.
#                             Michael L. Brock
#
#       Copyright Michael L. Brock 1993 - 2016.
#       Distributed under the Boost Software License, Version 1.0.
#       (See accompanying file LICENSE_1_0.txt or copy at
#       http://www.boost.org/LICENSE_1_0.txt)
#
# ##########################################################################

.KEEP_STATE:

THIS_HOME:sh				=	echo $HOME

include ${THIS_HOME}/src/.MASCAPS/premake.mk

TARGET_LIBS					=	spffuncs.a

ADF_INCS						=	${INCLUDE_DIR}/spffuncs.h

SRCS							=	\
									alparse.c \
									cpparse.c \
									cpspec.c \
									fdspec.c \
									frcontxt.c \
									frparse.c \
									frspec.c \
									getlocat.c \
									getlstpa.c \
									getsubpa.c \
									incontxt.c \
									inparse.c \
									insfuncs.c \
									inspec.c \
									mlinestr.c \
									pabasic.c \
									pabool.c \
									pacomplx.c \
									pacstr.c \
									pacstrml.c \
									paenum.c \
									pafile.c \
									panumber.c \
									pastr.c \
									pastrml.c \
									pastrver.c \
									patext.c \
									patextml.c \
									rdfile.c \
									setparse.c

LIBS							=	${TARGET_LIBS} ${LOCAL_LIBS}

${TARGET_LIBS}				:	${OBJS}
	@${AR} ${ARFLAGS} $@ ${OBJS}
	@ranlib $@
	@cp -p $@ ${LOCAL_LIB_DIR}/.

include ${THIS_HOME}/src/.MASCAPS/postmake.mk


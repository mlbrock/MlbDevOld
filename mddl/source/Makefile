# ##########################################################################
# ##########################################################################
# MDDL Library Makefile
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
#    File Description   :  This is the make file for the MDDL library.
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

TARGET_LIBS					=	mddl.a

ADF_INCS						=  ${INCLUDE_DIR}/mddl.h

SRCS							=	\
									apmddl.c \
									cpmddl.c \
									displen.c \
									dispname.c \
									dmfld.c \
									dmhead.c \
									dmrec.c \
									dmtrail.c \
									dmtxt.c \
									dmtxtbas.c \
									dmtxtind.c \
									emmddl.c \
									fixalign.c \
									frmddl.c \
									inmddl.c \
									setalign.c \
									speclst.c \
									specstr.c

LIBS							=	${TARGET_LIBS} ${LOCAL_LIBS}

${TARGET_LIBS}				:	${OBJS}
	@${AR} ${ARFLAGS} $@ ${OBJS}
	@ranlib $@
	@cp -p $@ ${LOCAL_LIB_DIR}/.

include ${THIS_HOME}/src/.MASCAPS/postmake.mk


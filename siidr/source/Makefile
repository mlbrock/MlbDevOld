# ##########################################################################
# ##########################################################################
# Single Index Internal Data Repository Library Makefile
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
#    File Description   :  This is the make file for the SIIDR library.
#
#    Revision History   :  1996-04-10 --- Creation.
#                             Michael L. Brock
#
#       Copyright Michael L. Brock 1996 - 2016.
#       Distributed under the Boost Software License, Version 1.0.
#       (See accompanying file LICENSE_1_0.txt or copy at
#       http://www.boost.org/LICENSE_1_0.txt)
#
# ##########################################################################

.KEEP_STATE:

THIS_HOME:sh				=	echo $HOME

include ${THIS_HOME}/src/.MASCAPS/premake.mk

TARGET_LIBS					=	siidr.a

ADF_INCS						=	${INCLUDE_DIR}/siidr.h

SRCS							=	\
									alidr.c \
									bularray.c \
									bullist.c \
									ckctl.c \
									ckdata.c \
									ckidr.c \
									ckrelop.c \
									cmbulk.c \
									cmrecord.c \
									cpidr.c \
									cridr.c \
									delall.c \
									delete.c \
									deleteat.c \
									delmatch.c \
									delspec.c \
									fdrecord.c \
									fridr.c \
									getarray.c \
									getat.c \
									getcount.c \
									getfirst.c \
									getlast.c \
									getlist.c \
									getnext.c \
									getprev.c \
									getrec.c \
									idrget.c \
									idrlock.c \
									idrset.c \
									idrtlock.c \
									idrulock.c \
									inidr.c \
									insert.c \
									insertat.c \
									matarray.c \
									match.c \
									matcount.c \
									matlist.c \
									sort.c \
									touch.c \
									tstdebug.c \
									update.c \
									updateat.c

LIBS							=	${TARGET_LIBS} ${LOCAL_LIBS}

${TARGET_LIBS}				:	${OBJS}
	@${AR} ${ARFLAGS} $@ ${OBJS}
	@ranlib $@
	@cp -p $@ ${LOCAL_LIB_DIR}/.

include ${THIS_HOME}/src/.MASCAPS/postmake.mk


# ##########################################################################
# ##########################################################################
# System Date/Time Interface Facility (SDTIF) Library Makefile
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
#    File Description   :  This is the make file for the SDTIF library.
#
#    Revision History   :  1995-11-02 --- Creation.
#                             Michael L. Brock
#
#       Copyright Michael L. Brock 1995 - 2015.
#       Distributed under the Boost Software License, Version 1.0.
#       (See accompanying file LICENSE_1_0.txt or copy at
#       http://www.boost.org/LICENSE_1_0.txt)
#
# ##########################################################################

.KEEP_STATE:

THIS_HOME:sh				=	echo $HOME

include ${THIS_HOME}/src/.MASCAPS/premake.mk

TARGET_LIBS					=	sdtif.a

TARGET_BINS					=

ADF_INCS						=  ${INCLUDE_DIR}/sdtif.h

SRCS							=	\
									cmtimet.c \
									cmtm.c \
									cmtspec.c \
									cmtval.c \
									cmulong.c \
									fmitimet.c \
									fmitm.c \
									fmitspec.c \
									fmitval.c \
									fmiulong.c \
									fmtimet.c \
									fmtm.c \
									fmtspec.c \
									fmtval.c \
									fmulong.c \
									gettime.c \
									ittspec.c \
									ittval.c \
									sleep.c \
									sttval.c \
									tstdebug.c \
									version.c

LIBS							=	${TARGET_LIBS} ${LOCAL_LIBS}

all							:	${TARGET_LIBS} ${TARGET_BINS}

${TARGET_LIBS}				:	${OBJS}
	@${AR} ${ARFLAGS} $@ ${OBJS}
	@ranlib $@
	@cp -p $@ ${LOCAL_LIB_DIR}/.

include ${THIS_HOME}/src/.MASCAPS/postmake.mk


# ##########################################################################
# ##########################################################################
# GENFUNCS Library Makefile
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
#    File Description   :  This is the make file for the GENFUNCS library.
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

TARGET_LIBS					=	genfuncs.a

ADF_INCS						=  ${INCLUDE_DIR}/genfuncs.h

SRCS							=	\
									align.c \
									alignbas.c \
									allocmsg.c \
									argbasic.c \
									argparse.c \
									cmptimes.c \
									cmptimev.c \
									currdir.c \
									emgalign.c \
									emitbuff.c \
									expandir.c \
									expfpath.c \
									exphostl.c \
									exphosts.c \
									fmtgroce.c \
									fmtitime.c \
									fmttime.c \
									generror.c \
									getmac.c \
									getparam.c \
									getpid.c \
									getpmap.c \
									gettid.c \
									gettime.c \
									hostname.c \
									membr.c \
									membrdmp.c \
									pagesize.c \
									readexlk.c \
									rlimit.c \
									rusage.c \
									sighandl.c \
									sigtext.c \
									textread.c \
									timespec.c \
									timeval.c \
									tostring.c \
									touchmem.c \
									tvalstat.c \
									usage.c \
									usebasic.c \
									usleep.c \
									validptr.c \
									version.c

LIBS							=	${TARGET_LIBS} ${LOCAL_LIBS}

${TARGET_LIBS}				:	${OBJS}
	@${AR} ${ARFLAGS} $@ ${OBJS}
	@ranlib $@
	@cp -p $@ ${LOCAL_LIB_DIR}/.

include ${THIS_HOME}/src/.MASCAPS/postmake.mk


# ##########################################################################
# ##########################################################################
# Tib/Rendezvous Utility Library Makefile
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
#    File Description   :  Makefile for the Tib/Rendezvous Utility Library.
#
#    Revision History   :  1996-01-02 --- Creation.
#                             Michael L. Brock
#
#       Copyright Michael L. Brock 1996 - 2015.
#       Distributed under the Boost Software License, Version 1.0.
#       (See accompanying file LICENSE_1_0.txt or copy at
#       http://www.boost.org/LICENSE_1_0.txt)
#
# ##########################################################################

.KEEP_STATE:

THIS_HOME:sh				=	echo $HOME

include ${THIS_HOME}/src/.MASCAPS/premake.mk

TARGET_LIBS					=	rvutil.a

TARGET_BINS					=	canread \
									canstats \
									canwrite

ADF_INCS						=  ${INCLUDE_DIR}/rvutil.h

SRCS							=	\
									adsub.c \
									adsubli.c \
									cdbasic.c \
									cdrv.c \
									cdrvadv.c \
									cdrvcm.c \
									cdrvevm.c \
									cdrvft.c \
									cdrvmsg.c \
									ckelem.c \
									ckenv.c \
									ckftenv.c \
									cksig.c \
									cksname.c \
									clenv.c \
									clftenv.c \
									clsub.c \
									cmsubnam.c \
									crack.c \
									crenv.c \
									crftenv.c \
									defsig.c \
									enenv.c \
									enftenv.c \
									evmevent.c \
									evmiotyp.c \
									fdsublid.c \
									fdsubnam.c \
									fmrv.c \
									fmrvadv.c \
									fmrvcm.c \
									fmrvevm.c \
									fmrvft.c \
									fmrvmsg.c \
									fnrv.c \
									fnrvevm.c \
									fnrvft.c \
									fnrvmsg.c \
									frenv.c \
									frftenv.c \
									frsub.c \
									ftaction.c \
									inenv.c \
									inftenv.c \
									insub.c \
									jgftenv.c \
									lienv.c \
									liftenv.c \
									lisub.c \
									makepat.c \
									matchpat.c \
									msgtype.c \
									paramstr.c \
									rmsub.c \
									sigactnm.c \
									sndtostr.c \
									ssenv.c \
									ssftenv.c \
									tstdebug.c \
									version.c \
									wrktoflt.c

LIBS							=	${TARGET_LIBS} ${LOCAL_LIBS}

all							:	${TARGET_LIBS} ${TARGET_BINS}

${TARGET_LIBS}				:	${OBJS}
	@${AR} ${ARFLAGS} $@ ${OBJS}
	@ranlib $@
	@cp -p $@ ${LOCAL_LIB_DIR}/.

canread						:	canread.o ${LIBS}
	${LINK.c} -o $@ canread.o ${LDFLAGS} ${LDLIBS} -lsocket -lgen -lnsl ${LIBS}

canstats					:	canstats.o ${LIBS}
	${LINK.c} -o $@ canstats.o ${LDFLAGS} ${LDLIBS} -lsocket -lgen -lnsl ${LIBS}

canwrite					:	canwrite.o ${LIBS}
	${LINK.c} -o $@ canwrite.o ${LDFLAGS} ${LDLIBS} -lsocket -lgen -lnsl ${LIBS}

include ${THIS_HOME}/src/.MASCAPS/postmake.mk


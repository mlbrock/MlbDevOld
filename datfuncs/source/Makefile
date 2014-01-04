# ##########################################################################
# ##########################################################################
# DATFUNCS Library Makefile
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
#    File Description   :  This is the make file for the DATFUNCS library.
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

TARGET_LIBS					=	datfuncs.a

ADF_INCS						=  ${INCLUDE_DIR}/datfuncs.h

SRCS							=	\
									ckstring.c \
									cndaycnt.c \
									cndaymax.c \
									dattojul.c \
									dayofmon.c \
									dc30360.c \
									dcactact.c \
									downame.c \
									dtadj.c \
									dtcmp.c \
									dtformat.c \
									dtnow.c \
									dtok.c \
									dttimev.c \
									dttojul.c \
									dtymdhms.c \
									fixulong.c \
									fixyear.c \
									get0101.c \
									get1231.c \
									getcent.c \
									getday.c \
									getdow.c \
									gethour.c \
									gethsec.c \
									getmdata.c \
									getmin.c \
									getmonth.c \
									getmsec.c \
									getqtr.c \
									getsec.c \
									gettsec.c \
									getweek.c \
									getyear.c \
									hourok.c \
									ingtojul.c \
									isleapyr.c \
									jdateok.c \
									juladj.c \
									julianok.c \
									jultodat.c \
									jultodt.c \
									jultofmt.c \
									jultoing.c \
									jultolon.c \
									jultostr.c \
									jultosyb.c \
									jultoymd.c \
									lontodat.c \
									lontojul.c \
									millisok.c \
									minok.c \
									mndaycnt.c \
									mndaymax.c \
									mnend.c \
									mnstart.c \
									monthok.c \
									nowtojul.c \
									qtrend.c \
									qtrstart.c \
									secok.c \
									ulongnow.c \
									ulongok.c \
									version.c \
									wkend.c \
									wkstart.c \
									yearok.c \
									ymdok.c \
									ymdtojul.c \
									yrdaycnt.c \
									yrdaymax.c \
									yrend.c \
									yrstart.c

LIBS							=	${TARGET_LIBS} ${LOCAL_LIBS} 

${TARGET_LIBS}				:	${OBJS}
	@${AR} ${ARFLAGS} $@ ${OBJS}
	@ranlib $@
	@cp -p $@ ${LOCAL_LIB_DIR}/.

include ${THIS_HOME}/src/.MASCAPS/postmake.mk


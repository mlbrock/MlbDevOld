# ##########################################################################
# ##########################################################################
# ADF Library and Executable Makefile
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
#    File Description   :  This is the make file for the ADF library and
#    			   executables.
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

BINS							=	\
									adfcomb \
									adfdefc \
									adfdefd \
									adfdiff \
									adfout  \
									adfprep \
									adfrefsa \
									adfsize

SRCS							=	\
									adfcntrl.c \
									adfentry.c \
									adferror.c \
									adffile.c \
									adfrun.c \
									areaname.c \
									argbasic.c \
									argframe.c \
									arghtml.c \
									argman.c \
									argout.c \
									argprep.c \
									cmentryd.c \
									cpdomain.c \
									cpentryd.c \
									cpparad.c \
									cppat.c \
									cpsec.c \
									datframe.c \
									dathtml.c \
									datman.c \
									defspec.c \
									delentry.c \
									docludes.c \
									doindex.c \
									dosrc.c \
									emdef.c \
									emdefc.c \
									emdomain.c \
									empat.c \
									emsec.c \
									entrydat.c \
									fdarea.c \
									fddomain.c \
									fixpara.c \
									fptrsout.c \
									frdomain.c \
									frentryd.c \
									frparad.c \
									frpat.c \
									frsec.c \
									getentry.c \
									getotype.c \
									getparam.c \
									indomain.c \
									inentryd.c \
									infile.c \
									inparad.c \
									inpat.c \
									insec.c \
									logmessg.c \
									matchlst.c \
									matchpat.c \
									optpat.c \
									outascii.c \
									outframe.c \
									outhtml.c \
									outman.c \
									outps.c \
									outrtf.c \
									paany.c \
									paarea.c \
									padomain.c \
									pamain.c \
									papat.c \
									paraform.c \
									pasec.c \
									prepfile.c \
									readdef.c \
									readfile.c \
									readsrc.c \
									strpair.c \
									usage.c \
									usebasic.c \
									useframe.c \
									usehtml.c \
									useman.c \
									useout.c \
									useprep.c \
									valmanpg.c

LIBS							=	\
									adf.a \
									${LOCAL_LIB_DIR}/spffuncs.a \
									${LOCAL_LIB_DIR}/mfile.a \
									${LOCAL_LIB_DIR}/genfuncs.a \
									${LOCAL_LIB_DIR}/datfuncs.a \
									${LOCAL_LIB_DIR}/strfuncs.a

all							:	adf.a ${BINS}

adf.a							:	${OBJS}
	@${AR} ${ARFLAGS} $@ ${OBJS}
	@ranlib $@
	@cp -p $@ ../lib/.

adfcomb						:	adfcomb.o ${LIBS}
	${LINK.c} -o $@ adfcomb.o ${LDFLAGS} ${LDLIBS} ${LIBS} ${LDFLAGS}

adfdefc						:	adfdefc.o ${LIBS}
	${LINK.c} -o $@ adfdefc.o ${LDFLAGS} ${LDLIBS} ${LIBS} ${LDFLAGS}

adfdefd						:	adfdefd.o ${LIBS}
	${LINK.c} -o $@ adfdefd.o ${LDFLAGS} ${LDLIBS} ${LIBS} ${LDFLAGS}

adfdiff						:	adfdiff.o ${LIBS}
	${LINK.c} -o $@ adfdiff.o ${LDFLAGS} ${LDLIBS} ${LIBS} ${LDFLAGS}

adfout						:	adfout.o ${LIBS}
	${LINK.c} -o $@ adfout.o  ${LDFLAGS} ${LDLIBS} ${LIBS} ${LDFLAGS}

adfprep						:	adfprep.o ${LIBS}
	${LINK.c} -o $@ adfprep.o ${LDFLAGS} ${LDLIBS} ${LIBS} ${LDFLAGS}

adfrefsa						:	adfrefsa.o ${LIBS}
	${LINK.c} -o $@ adfrefsa.o ${LDFLAGS} ${LDLIBS} ${LIBS} ${LDFLAGS}

adfsize						:	adfsize.o ${LIBS}
	${LINK.c} -o $@ adfsize.o ${LDFLAGS} ${LDLIBS} ${LIBS} ${LDFLAGS}

include ${THIS_HOME}/src/.MASCAPS/postmake.mk


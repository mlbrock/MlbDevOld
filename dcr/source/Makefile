# ############################################################################
# ############################################################################
# Data Cache Repository Library (DCR) Makefile
# ############################################################################
#
#    File Name          :  %M%
#
#    File Version       :  %I%
#
#    Last Extracted     :  %D%	%T%
#
#    Last Updated       :  %E%	%U%
#
#    File Description   :  This is the make file for the DCR libraries and
#			   executables. It conforms to the MASCaPS standard.
#
#    Revision History   :  1994-04-12 --- Creation.
#                             Michael L. Brock
#
#       Copyright Michael L. Brock 1994 - 2016.
#       Distributed under the Boost Software License, Version 1.0.
#       (See accompanying file LICENSE_1_0.txt or copy at
#       http://www.boost.org/LICENSE_1_0.txt)
#
# ############################################################################
#

.KEEP_STATE:

# Paths necessary to find the 'local' makefile . . .
THIS_HOME:sh				=	echo $HOME
 
# Include directive for the 'local' makefile . . .
include ${THIS_HOME}/src/.MASCAPS/premake.mk
 
#This is the the list of targets for this makefile . . .
TARGET_LIBS					=	dcr.a

TARGET_BINS					=	\
									cpycache	\
									prtcache \
									runcache

#ADF_INCS						=	${INCLUDE_DIR}/dcr.h
ADF_INCS						=	./dcr.h

# source
SRCS							=	\
									accessnm.c \
									addfldl.c \
									allocrow.c \
									allocscf.c \
									areacnt.c \
									arealist.c \
									areaname.c \
									assertit.c \
									basicarg.c \
									basicuse.c \
									bindhead.c \
									bindinit.c \
									cachemem.c \
									cacheupd.c \
									calcsize.c \
									callback.c \
									cbname.c \
									chkheadr.c \
									chkidxof.c \
									chkpoint.c \
									chkrecof.c \
									chkslist.c \
									closeall.c \
									closeone.c \
									closeraw.c \
									cmcolnam.c \
									cmfield.c \
									cmfldnam.c \
									cmidxnam.c \
									cmpname.c \
									cmprecs.c \
									createit.c \
									dcrerror.c \
									dcrlock.c \
									deletrec.c \
									doload.c \
									doreload.c \
									doupdate.c \
									emitbin.c \
									emitcb.c \
									emitctrl.c \
									emitdata.c \
									emitflds.c \
									emithead.c \
									emitrec.c \
									emitstat.c \
									emitstr.c \
									fdcolnam.c \
									fdfldnam.c \
									fdidxnam.c \
									findflds.c \
									findrecu.c \
									findrele.c \
									frecache.c \
									getcount.c \
									gethigh.c \
									getlist.c \
									getlow.c \
									getnext.c \
									getprev.c \
									getrel.c \
									getukeys.c \
									idxcache.c \
									idxcheck.c \
									idxchke.c \
									idxchki.c \
									idxcmpe.c \
									idxcmpi.c \
									idxdele.c \
									idxembed.c \
									idxfind.c \
									idxfinde.c \
									idxfindi.c \
									idxlist.c \
									idxlocat.c \
									idxsort.c \
									idxsorte.c \
									idxsorti.c \
									indexkey.c \
									instbulk.c \
									instrec.c \
									instsupp.c \
									isaccess.c \
									isstatus.c \
									lockrec.c \
									lockscf.c \
									makehead.c \
									makepkey.c \
									makesql.c \
									mapboth.c \
									mapdata.c \
									mapindex.c \
									maxsize.c \
									openraw.c \
									openread.c \
									openscf.c \
									openwrit.c \
									refresh.c \
									remap.c \
									resize.c \
									searbulk.c \
									searrec.c \
									specfldl.c \
									sqlclaus.c \
									statname.c \
									stattime.c \
									statusnm.c \
									truncate.c \
									ulockrec.c \
									ulockscf.c \
									updatedt.c \
									updatrec.c \
									userdptr.c \
									valcmpty.c \
									valindex.c \
									valrecfl.c \
									version.c

LIBS							=	${TARGET_LIBS} ${LOCAL_LIBS}

# Here's how we make the targets . . .
all							: ${TARGET_LIBS} ${TARGET_BINS}

# Here's how we make the target executables . . .
cpycache						:	${LIBS} cpycache.o
	$(LINK.c) -o $@ $@.o $(LIBS)

prtcache						:	${LIBS} prtcache.o
	$(LINK.c) -o $@ $@.o $(LIBS)

runcache						:	${LIBS} runcache.o
	$(LINK.c) -o $@ $@.o $(LIBS)

# Here's how we make the target library . . .
dcr.a			          	: ${OBJS}
	@${AR} ${ARFLAGS} $@ ${OBJS}
	@ranlib $@
	@cp -p $@ ${LOCAL_LIB_DIR}/.
 
# We include some useful ancillary targets here . . .
include ${THIS_HOME}/src/.MASCAPS/postmake.mk
#
# ############################################################################
 

# ##########################################################################
# ##########################################################################
# STRFUNCS Library Makefile
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
#    File Description   :  This is the make file for the STRFUNCS library.
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

TARGET_LIBS					=	strfuncs.a

ADF_INCS						=	${INCLUDE_DIR}/strfuncs.h

SRCS							=	\
									allocmsg.c \
									asctobcd.c \
									asctorad.c \
									bcdtoasc.c \
									cardinal.c \
									ccmntend.c \
									center.c \
									centerit.c \
									charcnt.c \
									charicnt.c \
									charspan.c \
									checkrad.c \
									chrcat.c \
									chrcnt.c \
									chrcpy.c \
									chricnt.c \
									chriindx.c \
									chrindx.c \
									chrinstr.c \
									chrncnt.c \
									chrnicnt.c \
									cknumber.c \
									cnormal.c \
									cstr2mem.c \
									cstring.c \
									ctltospc.c \
									doubltxt.c \
									ebcdic.c \
									emchr.c \
									emdefs.c \
									emstr.c \
									getfname.c \
									getnstr.c \
									groupk.c \
									idxchr.c \
									idxichr.c \
									idxistr.c \
									idxistrn.c \
									idxnchr.c \
									idxnichr.c \
									idxnistr.c \
									idxnstr.c \
									idxnstrn.c \
									idxrchr.c \
									idxrichr.c \
									idxristr.c \
									idxrnchr.c \
									idxrnstr.c \
									idxrstr.c \
									idxrstrn.c \
									idxstr.c \
									idxstrn.c \
									initcaps.c \
									initrad.c \
									isnumber.c \
									ljust.c \
									lower.c \
									ltrim.c \
									ltrimx.c \
									lttrim.c \
									mem2cstr.c \
									mema2l.c \
									memaadd.c \
									memaapp.c \
									memacmls.c \
									memacopy.c \
									memad.c \
									memadlt.c \
									memaid.c \
									memains.c \
									memaisd.c \
									memarem.c \
									memasd.c \
									memasdlt.c \
									membms.c \
									memcnt.c \
									memdup.c \
									memibms.c \
									memicmp.c \
									memicnt.c \
									memimem.c \
									meml2a.c \
									memladd.c \
									memlallc.c \
									memlapp.c \
									memlcm.c \
									memlcmls.c \
									memlcopy.c \
									memld.c \
									memldlt.c \
									memlicm.c \
									memlid.c \
									memlins.c \
									memlisd.c \
									memlrem.c \
									memlrv.c \
									memlsd.c \
									memlsdlt.c \
									memlvap.c \
									memmem.c \
									memmvdel.c \
									memmvins.c \
									memrimem.c \
									memrmem.c \
									noblank.c \
									nocontrl.c \
									nospace.c \
									nstrcat.c \
									nstrcpy.c \
									nstrset.c \
									oneblank.c \
									ordfull.c \
									ordinal.c \
									paramstr.c \
									qstrend.c \
									radtoasc.c \
									rjust.c \
									rtrim.c \
									rtrimx.c \
									rttrim.c \
									sepwordc.c \
									sepwordl.c \
									sepwords.c \
									sepwordx.c \
									spctotab.c \
									stalnum.c \
									stalpha.c \
									stascii.c \
									stbdigit.c \
									stcntrl.c \
									stcsym.c \
									stcsymf.c \
									stdigit.c \
									stgraph.c \
									stlower.c \
									stodigit.c \
									stprint.c \
									stpunct.c \
									strabser.c \
									stradele.c \
									strafind.c \
									strarev.c \
									strasear.c \
									strasort.c \
									strauniq.c \
									strchr.c \
									strcnt.c \
									strdele.c \
									strdup.c \
									strescap.c \
									strichr.c \
									stricmp.c \
									stricnt.c \
									striindx.c \
									strindx.c \
									strins.c \
									strinst.c \
									stristr.c \
									stristrn.c \
									strjoin.c \
									strladd.c \
									strlapp.c \
									strlbser.c \
									strlcm.c \
									strlcmls.c \
									strlcopy.c \
									strld.c \
									strldele.c \
									strldl.c \
									strlfd.c \
									strlfind.c \
									strlicm.c \
									strlid.c \
									strlidl.c \
									strlifd.c \
									strlins.c \
									strlisd.c \
									strlise.c \
									strlist.c \
									strliun.c \
									strlmax.c \
									strlmin.c \
									strlnadd.c \
									strlnapp.c \
									strlncm.c \
									strlnd.c \
									strlndl.c \
									strlnfd.c \
									strlnicm.c \
									strlnid.c \
									strlnidl.c \
									strlnifd.c \
									strlnins.c \
									strlnisd.c \
									strlnise.c \
									strlnist.c \
									strlniun.c \
									strlnsd.c \
									strlnse.c \
									strlnst.c \
									strlnun.c \
									strlnvap.c \
									strlrem.c \
									strlrev.c \
									strlrv.c \
									strlsd.c \
									strlse.c \
									strlsear.c \
									strlsort.c \
									strlst.c \
									strlun.c \
									strluniq.c \
									strlvap.c \
									strlwrap.c \
									strmask.c \
									strnchr.c \
									strncnt.c \
									strndup.c \
									strnichr.c \
									strnicmp.c \
									strnicnt.c \
									strniidx.c \
									strninst.c \
									strnistr.c \
									strnrepl.c \
									strnset.c \
									strnstr.c \
									strnstrn.c \
									strnvacp.c \
									strnvact.c \
									strnvcp.c \
									strnvct.c \
									strpadl.c \
									strpadr.c \
									strrchr.c \
									strrepl.c \
									strrev.c \
									strrichr.c \
									strristr.c \
									strrnchr.c \
									strrnstr.c \
									strrstr.c \
									strrstrn.c \
									strset.c \
									strstr.c \
									strstrn.c \
									strvacp.c \
									strvact.c \
									strvcp.c \
									strvct.c \
									strwrap.c \
									stspace.c \
									stupper.c \
									stxdigit.c \
									tabtospc.c \
									tstdebug.c \
									trim.c \
									trimx.c \
									ttrim.c \
									ulongtxt.c \
									upper.c \
									val2str.c \
									version.c \
									vertostr.c \
									wordwrap.c \
									xprintf.c \
									zerotrim.c

LIBS							=	${TARGET_LIBS}

${TARGET_LIBS}				:	${OBJS}
	@${AR} ${ARFLAGS} $@ ${OBJS}
	@ranlib $@
	@cp -p $@ ${LOCAL_LIB_DIR}/.

include ${THIS_HOME}/src/.MASCAPS/postmake.mk


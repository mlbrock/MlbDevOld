# ##########################################################################
# ##########################################################################
# Parse Configuration File Facility (PCFF) Library Makefile
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
#    File Description   :  This is the make file for the PCFF library.
#
#    Revision History   :  1993-04-12 --- Creation.
#                             Michael L. Brock
#
#       Copyright Michael L. Brock 1993 - 2018.
#       Distributed under the Boost Software License, Version 1.0.
#       (See accompanying file LICENSE_1_0.txt or copy at
#       http://www.boost.org/LICENSE_1_0.txt)
#
# ##########################################################################

.KEEP_STATE:

THIS_HOME:sh				=	echo $HOME

include ${THIS_HOME}/src/.MASCAPS/premake.mk

TARGET_LIBS					=	pcff.a

ADF_INCS						=  ${INCLUDE_DIR}/pcff.h

SRCS							=	\
									aditem.c \
									ckdelim.c \
									ckparam.c \
									ckparams.c \
									ckrequir.c \
									ckunknow.c \
									cmitem.c \
									cmlparam.c \
									cmparam.c \
									cpcfg.c \
									cpitem.c \
									cpiphsp.c \
									cpparam.c \
									cpparams.c \
									cpsrc.c \
									crparams.c \
									dlitem.c \
									doparams.c \
									emadf.c \
									emparamd.c \
									fditem.c \
									fixdelim.c \
									flatten.c \
									frcfg.c \
									fritem.c \
									friphsp.c \
									fromfile.c \
									fromlist.c \
									frparam.c \
									frparams.c \
									frsrc.c \
									getlong.c \
									getptext.c \
									gtunknow.c \
									incfg.c \
									initem.c \
									iniphsp.c \
									inparam.c \
									inparams.c \
									inparse.c \
									insrc.c \
									postproc.c \
									procfile.c \
									proclist.c \
									stcfg.c \
									stparam.c \
									tstdebug.c

LIBS							=	${TARGET_LIBS} ${LOCAL_LIBS}

${TARGET_LIBS}				:	${OBJS}
	@${AR} ${ARFLAGS} $@ ${OBJS}
	@ranlib $@
	@cp -p $@ ${LOCAL_LIB_DIR}/.

include ${THIS_HOME}/src/.MASCAPS/postmake.mk


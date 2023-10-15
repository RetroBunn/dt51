auxdir                  = $(top_srcdir)/plat/autotools/build
HELPER_PROGS                = $(auxdir)/compile \
                          $(auxdir)/config.guess \
                          $(auxdir)/config.sub \
                          $(auxdir)/depcomp \
                          $(auxdir)/install-sh \
                          $(auxdir)/ltmain.sh \
                          $(auxdir)/missing 
AUX_DIST_EXTRA          = $(auxdir)/ac_c_long_long.m4 \
                          $(auxdir)/ac_prog_sed.m4 \
                          $(auxdir)/acx_pthread.m4 \
                          $(auxdir)/soname.sed 
MOSTLYCLEANFILES=
CLEANFILES=
DISTCLEANFILES=
MAINTAINERCLEANFILES    = $(top_builddir)/Makefile.in $(top_builddir)/configure $(HELPER_PROGS)
EXTRA_DIST              = $(top_srcdir)/bootstrap $(HELPER_PROGS) $(AUX_DIST_EXTRA)
AUTOMAKE_OPTIONS        = 1.9 foreign
ACLOCAL_AMFLAGS         = -I plat/autotools/build

#install paths
examplecdir=$(datadir)/dectalk/examples/c

# these are added to by the included makefiles
lib_LTLIBRARIES=
noinst_LTLIBRARIES=
noinst_HEADERS=
dist_noinst_DATA=
PLAT_PROC_INCLUDES=-I$(top_srcdir)/plat/unix/include -I$(top_srcdir)/sdk/include/unix

# user-land headers
include_HEADERS = \
$(top_srcdir)/sdk/include/unix/dectalktypes.h \
$(top_srcdir)/sdk/include/unix/dtmmedefs.h \
$(top_srcdir)/sdk/include/ttsapi.h

DE_DE_DEFINES=-DGERMAN
EN_GB_DEFINES=-DENGLISH -DENGLISH_UK
EN_US_DEFINES=-DENGLISH -DENGLISH_US -DACNA
ES_ES_DEFINES=-DSPANISH -DSPANISH_SP
ES_LA_DEFINES=-DSPANISH -DSPANISH_LA
FR_FR_DEFINES=-DFRENCH
HE_IL_DEFINES=-DHEBREW
IT_IT_DEFINES=-DITALIAN
JA_JP_DEFINES=-DJAPANESE
KO_KR_DEFINES=-DKOREAN
ZH_CN_DEFINES=-DCHINESE

if OSYSTEM_LINUX
PLAT_PROC_INCLUDES += -I$(top_srcdir)/plat/Linux/include
endif

if OSYSTEM_QNX
PLAT_PROC_INCLUDES += -I$(top_srcdir)/plat/QNX/include
endif

noinst_LTLIBRARIES += libopthread.la
libopthread_la_CFLAGS = $(PTHREAD_CFLAGS) 
libopthread_la_LIBADD = $(PTHREAD_LIBS) 
libopthread_la_CPPFLAGS = $(DECTALK_DEFINES) $(PLAT_PROC_INCLUDES) \
-I$(top_srcdir)/DAPI -I$(top_srcdir)/shared/include 
libopthread_la_SOURCES = \
$(top_srcdir)/shared/include/opthread.h \
$(top_srcdir)/shared/src/opthread.c

noinst_LTLIBRARIES += libmmalloc.la
libmmalloc_la_CFLAGS = 
libmmalloc_la_LIBADD = 
libmmalloc_la_CPPFLAGS = $(DECTALK_DEFINES) $(PLAT_PROC_INCLUDES) \
-I$(top_srcdir)/DAPI -I$(top_srcdir)/shared/include 
libmmalloc_la_SOURCES = \
$(top_srcdir)/shared/include/mmalloc.h \
$(top_srcdir)/shared/src/mmalloc.c

include $(top_srcdir)/plat/autotools/dectalk.mk

if BUILD_DE_DE
include $(top_srcdir)/plat/autotools/dtalk_de_DE.mk
endif

if BUILD_EN_GB
include $(top_srcdir)/plat/autotools/dtalk_en_GB.mk
endif

if BUILD_EN_US
include $(top_srcdir)/plat/autotools/dtalk_en_US.mk
endif

if BUILD_ES_ES
include $(top_srcdir)/plat/autotools/dtalk_es_ES.mk
endif

if BUILD_ES_LA
include $(top_srcdir)/plat/autotools/dtalk_es_LA.mk
endif

if BUILD_FR_FR
include $(top_srcdir)/plat/autotools/dtalk_fr_FR.mk
endif

if BUILD_HE_IL
include $(top_srcdir)/plat/autotools/dtalk_he_IL.mk
endif

if BUILD_IT_IT
include $(top_srcdir)/plat/autotools/dtalk_it_IT.mk
endif

if BUILD_JA_JP
include $(top_srcdir)/plat/autotools/dtalk_ja_JP.mk
endif

if BUILD_KO_KR
include $(top_srcdir)/plat/autotools/dtalk_ko_KR.mk
endif

if BUILD_ZH_CN
include $(top_srcdir)/plat/autotools/dtalk_zh_CN.mk
endif

# make sure libtool gets updated
libtool: $(LIBTOOL_DEPS)
	$(SHELL) ./config.status --recheck

# End of Makefile.am

#
# dectalk_zh_CN.mk -- makefile fragment for the Chinese lib
#

LIBDTALK_ZH_CN_CPPFLAGS_FLAGS = -DBUILD_LTS \
$(PLAT_PROC_INCLUDES) \
-I$(top_srcdir)/DAPI \
-I$(top_srcdir)/dapicore/CMD \
-I$(top_srcdir)/dapicore/LTS \
-I$(top_srcdir)/dapicore/LTS/chinese \
-I$(top_srcdir)/dapicore/INCLUDE \
-I$(top_srcdir)/dapicore/PH \
-I$(top_srcdir)/sdk/include \
-I$(top_srcdir)/shared/include 

# for easier comparison with project files
LIBDTALK_ZH_CN_SOURCE_FILES = \
$(top_srcdir)/dapicore/LTS/chinese/CHWalkerLinear.c \
$(top_srcdir)/dapicore/LTS/chinese/pinyinparse.c \
$(top_srcdir)/dapicore/LTS/l_ch_ad1.c \
$(top_srcdir)/dapicore/LTS/l_ch_con.c \
$(top_srcdir)/dapicore/LTS/l_ch_ma1.c \
$(top_srcdir)/dapicore/LTS/l_ch_pr1.c \
$(top_srcdir)/dapicore/LTS/l_ch_ru1.c \
$(top_srcdir)/dapicore/LTS/l_ch_sp1.c \
$(top_srcdir)/dapicore/LTS/l_us_cha.c \
$(top_srcdir)/dapicore/LTS/loaddict.c \
$(top_srcdir)/dapicore/LTS/ls_adju.c \
$(top_srcdir)/dapicore/LTS/ls_dict.c \
$(top_srcdir)/dapicore/LTS/ls_homo.c \
$(top_srcdir)/dapicore/LTS/ls_math.c \
$(top_srcdir)/dapicore/LTS/ls_rule.c \
$(top_srcdir)/dapicore/LTS/ls_rule2.c \
$(top_srcdir)/dapicore/LTS/ls_spel.c \
$(top_srcdir)/dapicore/LTS/ls_suff.c \
$(top_srcdir)/dapicore/LTS/ls_task.c \
$(top_srcdir)/dapicore/LTS/ls_util.c \
$(top_srcdir)/dapicore/LTS/lsw_main.c 

LIBDTALK_ZH_CN_HEADER_FILES = \
$(top_srcdir)/dapicore/LTS/chinese/chin_bachdata.h \
$(top_srcdir)/dapicore/LTS/chinese/chin_bachus.h \
$(top_srcdir)/dapicore/LTS/ls_char.h \
$(top_srcdir)/dapicore/LTS/ls_cons.h \
$(top_srcdir)/dapicore/LTS/ls_data.h \
$(top_srcdir)/dapicore/LTS/ls_def.h \
$(top_srcdir)/dapicore/LTS/ls_defs.h \
$(top_srcdir)/dapicore/LTS/ls_dict.h \
$(top_srcdir)/dapicore/LTS/ls_homo.h \
$(top_srcdir)/dapicore/LTS/ls_prot.h \
$(top_srcdir)/dapicore/LTS/ls_rule.h 

LIBDTALK_ZH_CN_SRCS = \
$(LIBDTALK_ZH_CN_SOURCE_FILES) \
$(LIBDTALK_ZH_CN_HEADER_FILES) \
$(top_srcdir)/DAPI/tts.h \
$(top_srcdir)/dapicore/PH/ph_def.h \
$(top_srcdir)/shared/include/dectalkf.h \
$(top_srcdir)/shared/include/mmalloc.h \
$(top_srcdir)/shared/include/opthread.h \
$(top_srcdir)/dapicore/CMD/cm_def.h \
$(top_srcdir)/dapicore/INCLUDE/minpath.h \
$(top_srcdir)/dapicore/INCLUDE/kernel.h 

LIBDTALK_ZH_CN_LDFLAGS_FLAGS = -version-info 0:0:0 -export-symbols $(top_srcdir)/plat/unix/sym/language.sym
LIBDTALK_ZH_CN_LIBADD_FLAGS = libopthread.la libmmalloc.la $(PTHREAD_LIBS) $(LIBDL)

if BUILD_INTEGER_ENGINE
lib_LTLIBRARIES += libdtalk-integer-zh_CN.la
libdtalk_integer_zh_CN_la_LDFLAGS = $(LIBDTALK_ZH_CN_LDFLAGS_FLAGS)
libdtalk_integer_zh_CN_la_LIBADD = $(LIBDTALK_ZH_CN_LIBADD_FLAGS)
libdtalk_integer_zh_CN_la_CPPFLAGS = $(DECTALK_DEFINES) -DINTEGER $(ZH_CN_DEFINES) $(LIBDTALK_ZH_CN_CPPFLAGS_FLAGS)
libdtalk_integer_zh_CN_la_SOURCES = $(LIBDTALK_ZH_CN_SRCS)
endif

if BUILD_HLSYN_ENGINE
lib_LTLIBRARIES += libdtalk-hlsyn-zh_CN.la
libdtalk_hlsyn_zh_CN_la_LDFLAGS = $(LIBDTALK_ZH_CN_LDFLAGS_FLAGS)
libdtalk_hlsyn_zh_CN_la_LIBADD = $(LIBDTALK_ZH_CN_LIBADD_FLAGS)
libdtalk_hlsyn_zh_CN_la_CPPFLAGS = $(DECTALK_DEFINES) -DHLSYN $(ZH_CN_DEFINES) $(LIBDTALK_ZH_CN_CPPFLAGS_FLAGS)
libdtalk_hlsyn_zh_CN_la_SOURCES = $(LIBDTALK_ZH_CN_SRCS)
endif

# End of dectalk_zh_CN.mk

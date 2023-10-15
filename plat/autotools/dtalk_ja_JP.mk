#
# dectalk_ja_JP.mk -- makefile fragment for the Japanese lib
#

LIBDTALK_JA_JP_CPPFLAGS_FLAGS = -DBUILD_LTS \
$(PLAT_PROC_INCLUDES) \
-I$(top_srcdir)/DAPI \
-I$(top_srcdir)/dapicore/CMD \
-I$(top_srcdir)/dapicore/LTS \
-I$(top_srcdir)/dapicore/LTS/CodePageConv \
-I$(top_srcdir)/dapicore/LTS/chinese \
-I$(top_srcdir)/dapicore/LTS/japan \
-I$(top_srcdir)/dapicore/INCLUDE \
-I$(top_srcdir)/dapicore/PH \
-I$(top_srcdir)/sdk/include \
-I$(top_srcdir)/shared/include 

# for easier comparison with project files
LIBDTALK_JA_JP_SOURCE_FILES = \
$(top_srcdir)/dapicore/LTS/japan/acc_000x.c \
$(top_srcdir)/dapicore/LTS/japan/acc_1000.c \
$(top_srcdir)/dapicore/LTS/japan/acc_2000.c \
$(top_srcdir)/dapicore/LTS/japan/acc_22xx.c \
$(top_srcdir)/dapicore/LTS/japan/acc_24xx.c \
$(top_srcdir)/dapicore/LTS/japan/acc_3000.c \
$(top_srcdir)/dapicore/LTS/japan/acc_5000.c \
$(top_srcdir)/dapicore/LTS/japan/dsp_roma.c \
$(top_srcdir)/dapicore/LTS/japan/ile_accd.c \
$(top_srcdir)/dapicore/LTS/japan/ile_accp.c \
$(top_srcdir)/dapicore/LTS/japan/ile_bufc.c \
$(top_srcdir)/dapicore/LTS/japan/ile_bunc.c \
$(top_srcdir)/dapicore/LTS/japan/ile_data.c \
$(top_srcdir)/dapicore/LTS/japan/ile_dbgc.c \
$(top_srcdir)/dapicore/LTS/japan/ile_edic.c \
$(top_srcdir)/dapicore/LTS/japan/ile_envc.c \
$(top_srcdir)/dapicore/LTS/japan/ile_errc.c \
$(top_srcdir)/dapicore/LTS/japan/ile_hnkc.c \
$(top_srcdir)/dapicore/LTS/japan/ile_idic.c \
$(top_srcdir)/dapicore/LTS/japan/ile_jknc.c \
$(top_srcdir)/dapicore/LTS/japan/ile_kana.c \
$(top_srcdir)/dapicore/LTS/japan/ile_kkhc.c \
$(top_srcdir)/dapicore/LTS/japan/ile_mruc.c \
$(top_srcdir)/dapicore/LTS/japan/ile_numc.c \
$(top_srcdir)/dapicore/LTS/japan/ile_nydc.c \
$(top_srcdir)/dapicore/LTS/japan/ile_othc.c \
$(top_srcdir)/dapicore/LTS/japan/ile_rnsc.c \
$(top_srcdir)/dapicore/LTS/japan/ile_rtgc.c \
$(top_srcdir)/dapicore/LTS/japan/ile_rtkc.c \
$(top_srcdir)/dapicore/LTS/japan/ile_sskc.c \
$(top_srcdir)/dapicore/LTS/japan/ile_stcc.c \
$(top_srcdir)/dapicore/LTS/japan/ile_stzc.c \
$(top_srcdir)/dapicore/LTS/japan/ile_suhc.c \
$(top_srcdir)/dapicore/LTS/japan/ile_tdic.c \
$(top_srcdir)/dapicore/LTS/japan/ile_v5cc.c \
$(top_srcdir)/dapicore/LTS/japan/lib_genc.c \
$(top_srcdir)/dapicore/LTS/japan/lib_shdc.c \
$(top_srcdir)/dapicore/LTS/japan/mkhatu.c \
$(top_srcdir)/dapicore/LTS/japan/stdonsei.c \
$(top_srcdir)/dapicore/LTS/l_jp_ad1.c \
$(top_srcdir)/dapicore/LTS/l_jp_con.c \
$(top_srcdir)/dapicore/LTS/l_jp_ma1.c \
$(top_srcdir)/dapicore/LTS/l_jp_pr1.c \
$(top_srcdir)/dapicore/LTS/l_jp_ru1.c \
$(top_srcdir)/dapicore/LTS/l_jp_sp1.c \
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

LIBDTALK_JA_JP_HEADER_FILES = \
$(top_srcdir)/dapicore/LTS/japan/dustytypes.h \
$(top_srcdir)/dapicore/LTS/japan/entrypt.h \
$(top_srcdir)/dapicore/LTS/japan/ile_accd.h \
$(top_srcdir)/dapicore/LTS/japan/ile_acch.h \
$(top_srcdir)/dapicore/LTS/japan/ile_bunh.h \
$(top_srcdir)/dapicore/LTS/japan/ile_dbgh.h \
$(top_srcdir)/dapicore/LTS/japan/ile_edic.h \
$(top_srcdir)/dapicore/LTS/japan/ile_envh.h \
$(top_srcdir)/dapicore/LTS/japan/ile_errh.h \
$(top_srcdir)/dapicore/LTS/japan/ile_fddh.h \
$(top_srcdir)/dapicore/LTS/japan/ile_func.h \
$(top_srcdir)/dapicore/LTS/japan/ile_idic.h \
$(top_srcdir)/dapicore/LTS/japan/ile_jknh.h \
$(top_srcdir)/dapicore/LTS/japan/ile_kkhh.h \
$(top_srcdir)/dapicore/LTS/japan/ile_mjzh.h \
$(top_srcdir)/dapicore/LTS/japan/ile_mruh.h \
$(top_srcdir)/dapicore/LTS/japan/ile_nydh.h \
$(top_srcdir)/dapicore/LTS/japan/ile_rnsc.h \
$(top_srcdir)/dapicore/LTS/japan/ile_shdh.h \
$(top_srcdir)/dapicore/LTS/japan/ile_sskh.h \
$(top_srcdir)/dapicore/LTS/japan/ile_stch.h \
$(top_srcdir)/dapicore/LTS/japan/ile_stzh.h \
$(top_srcdir)/dapicore/LTS/japan/ile_tdic.h \
$(top_srcdir)/dapicore/LTS/japan/ile_v5ch.h \
$(top_srcdir)/dapicore/LTS/japan/onsei.h \
$(top_srcdir)/dapicore/LTS/japan/onsei_s.h \
$(top_srcdir)/dapicore/LTS/japan/onseiapi.h \
$(top_srcdir)/dapicore/LTS/japan/pkind.h \
$(top_srcdir)/dapicore/LTS/japan/stdonsei.h \
$(top_srcdir)/dapicore/LTS/ls_char.h \
$(top_srcdir)/dapicore/LTS/ls_cons.h \
$(top_srcdir)/dapicore/LTS/ls_data.h \
$(top_srcdir)/dapicore/LTS/ls_def.h \
$(top_srcdir)/dapicore/LTS/ls_defs.h \
$(top_srcdir)/dapicore/LTS/ls_dict.h \
$(top_srcdir)/dapicore/LTS/ls_homo.h \
$(top_srcdir)/dapicore/LTS/ls_prot.h \
$(top_srcdir)/dapicore/LTS/ls_rule.h 

LIBDTALK_JA_JP_SRCS = \
$(LIBDTALK_JA_JP_SOURCE_FILES) \
$(LIBDTALK_JA_JP_HEADER_FILES) \
$(top_srcdir)/DAPI/tts.h \
$(top_srcdir)/dapicore/PH/ph_def.h \
$(top_srcdir)/shared/include/dectalkf.h \
$(top_srcdir)/shared/include/mmalloc.h \
$(top_srcdir)/shared/include/opthread.h \
$(top_srcdir)/dapicore/CMD/cm_def.h \
$(top_srcdir)/dapicore/INCLUDE/minpath.h \
$(top_srcdir)/dapicore/INCLUDE/kernel.h 

LIBDTALK_JA_JP_LDFLAGS_FLAGS = -version-info 0:0:0 -export-symbols $(top_srcdir)/plat/unix/sym/language.sym
LIBDTALK_JA_JP_LIBADD_FLAGS = libopthread.la libmmalloc.la $(PTHREAD_LIBS) $(LIBDL)

if BUILD_INTEGER_ENGINE
lib_LTLIBRARIES += libdtalk-integer-ja_JP.la
libdtalk_integer_ja_JP_la_LDFLAGS = $(LIBDTALK_JA_JP_LDFLAGS_FLAGS)
libdtalk_integer_ja_JP_la_LIBADD = $(LIBDTALK_JA_JP_LIBADD_FLAGS)
libdtalk_integer_ja_JP_la_CPPFLAGS = $(DECTALK_DEFINES) -DINTEGER $(JA_JP_DEFINES) $(LIBDTALK_JA_JP_CPPFLAGS_FLAGS)
libdtalk_integer_ja_JP_la_SOURCES = $(LIBDTALK_JA_JP_SRCS)
endif

if BUILD_HLSYN_ENGINE
lib_LTLIBRARIES += libdtalk-hlsyn-ja_JP.la
libdtalk_hlsyn_ja_JP_la_LDFLAGS = $(LIBDTALK_JA_JP_LDFLAGS_FLAGS)
libdtalk_hlsyn_ja_JP_la_LIBADD = $(LIBDTALK_JA_JP_LIBADD_FLAGS)
libdtalk_hlsyn_ja_JP_la_CPPFLAGS = $(DECTALK_DEFINES) -DHLSYN $(JA_JP_DEFINES) $(LIBDTALK_JA_JP_CPPFLAGS_FLAGS)
libdtalk_hlsyn_ja_JP_la_SOURCES = $(LIBDTALK_JA_JP_SRCS)
endif

# End of dectalk_ja_JP.mk

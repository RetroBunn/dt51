#
# dectalk_it_IT.mk -- makefile fragment for the Italian lib
#

LIBDTALK_IT_IT_CPPFLAGS_FLAGS = -DBUILD_LTS \
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
LIBDTALK_IT_IT_SOURCE_FILES = \
$(top_srcdir)/dapicore/LTS/GtWalkerlinear.c \
$(top_srcdir)/dapicore/LTS/execrules.c \
$(top_srcdir)/dapicore/LTS/l_it_ad1.c \
$(top_srcdir)/dapicore/LTS/l_it_con.c \
$(top_srcdir)/dapicore/LTS/l_it_ma1.c \
$(top_srcdir)/dapicore/LTS/l_it_pr1.c \
$(top_srcdir)/dapicore/LTS/l_it_ru1.c \
$(top_srcdir)/dapicore/LTS/l_it_sp1.c \
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
$(top_srcdir)/dapicore/LTS/lsw_main.c \
$(top_srcdir)/dapicore/LTS/userules.c \
$(top_srcdir)/dapicore/LTS/walkerit.c 

LIBDTALK_IT_IT_HEADER_FILES = \
$(top_srcdir)/dapicore/LTS/ls_char.h \
$(top_srcdir)/dapicore/LTS/ls_cons.h \
$(top_srcdir)/dapicore/LTS/ls_data.h \
$(top_srcdir)/dapicore/LTS/ls_def.h \
$(top_srcdir)/dapicore/LTS/ls_defs.h \
$(top_srcdir)/dapicore/LTS/ls_dict.h \
$(top_srcdir)/dapicore/LTS/ls_homo.h \
$(top_srcdir)/dapicore/LTS/ls_prot.h \
$(top_srcdir)/dapicore/LTS/ls_rule.h 

LIBDTALK_IT_IT_SRCS = \
$(LIBDTALK_IT_IT_SOURCE_FILES) \
$(LIBDTALK_IT_IT_HEADER_FILES) \
$(top_srcdir)/DAPI/tts.h \
$(top_srcdir)/dapicore/PH/ph_def.h \
$(top_srcdir)/shared/include/dectalkf.h \
$(top_srcdir)/shared/include/mmalloc.h \
$(top_srcdir)/shared/include/opthread.h \
$(top_srcdir)/dapicore/CMD/cm_def.h \
$(top_srcdir)/dapicore/INCLUDE/minpath.h \
$(top_srcdir)/dapicore/INCLUDE/kernel.h 

LIBDTALK_IT_IT_LDFLAGS_FLAGS = -version-info 0:0:0 -export-symbols $(top_srcdir)/plat/unix/sym/language.sym
LIBDTALK_IT_IT_LIBADD_FLAGS = libopthread.la libmmalloc.la $(PTHREAD_LIBS) $(LIBDL)

if BUILD_INTEGER_ENGINE
lib_LTLIBRARIES += libdtalk-integer-it_IT.la
libdtalk_integer_it_IT_la_LDFLAGS = $(LIBDTALK_IT_IT_LDFLAGS_FLAGS)
libdtalk_integer_it_IT_la_LIBADD = $(LIBDTALK_IT_IT_LIBADD_FLAGS)
libdtalk_integer_it_IT_la_CPPFLAGS = $(DECTALK_DEFINES) -DINTEGER $(IT_IT_DEFINES) $(LIBDTALK_IT_IT_CPPFLAGS_FLAGS)
libdtalk_integer_it_IT_la_SOURCES = $(LIBDTALK_IT_IT_SRCS)
endif

if BUILD_HLSYN_ENGINE
lib_LTLIBRARIES += libdtalk-hlsyn-it_IT.la
libdtalk_hlsyn_it_IT_la_LDFLAGS = $(LIBDTALK_IT_IT_LDFLAGS_FLAGS)
libdtalk_hlsyn_it_IT_la_LIBADD = $(LIBDTALK_IT_IT_LIBADD_FLAGS)
libdtalk_hlsyn_it_IT_la_CPPFLAGS = $(DECTALK_DEFINES) -DHLSYN $(IT_IT_DEFINES) $(LIBDTALK_IT_IT_CPPFLAGS_FLAGS)
libdtalk_hlsyn_it_IT_la_SOURCES = $(LIBDTALK_IT_IT_SRCS)
endif

# End of dectalk_it_IT.mk

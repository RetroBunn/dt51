#
# cmd.mk -- uninstalled part of individual libs
#

LIBCMD_INCLUDE_FLAGS = \
-I$(top_srcdir)/DAPI \
-I$(top_srcdir)/dapicore/CMD \
-I$(top_srcdir)/dapicore/INCLUDE \
-I$(top_srcdir)/dapicore/LTS/chinese \
-I$(top_srcdir)/plat/unix/include \
-I$(top_srcdir)/sdk/include \
-I$(top_srcdir)/shared/include \
-I$(top_srcdir)/shared/include/osf 

LIBCMD_SRCS = \
$(top_srcdir)/DAPI/tts.h \
$(top_srcdir)/dapicore/CMD/cm_char.c \
$(top_srcdir)/dapicore/CMD/cm_cmd.c \
$(top_srcdir)/dapicore/CMD/cm_copt.c \
$(top_srcdir)/dapicore/CMD/cm_data.h \
$(top_srcdir)/dapicore/CMD/cm_def.h \
$(top_srcdir)/dapicore/CMD/cm_defs.h \
$(top_srcdir)/dapicore/CMD/cm_main.c \
$(top_srcdir)/dapicore/CMD/cm_pars.c \
$(top_srcdir)/dapicore/CMD/cm_phon.c \
$(top_srcdir)/dapicore/CMD/cm_prot.h \
$(top_srcdir)/dapicore/CMD/cm_text.c \
$(top_srcdir)/dapicore/CMD/cm_util.c \
$(top_srcdir)/dapicore/CMD/cmd_init.c \
$(top_srcdir)/dapicore/CMD/cmd_wav.c \
$(top_srcdir)/dapicore/CMD/par_ambi.c \
$(top_srcdir)/dapicore/CMD/par_bin.h \
$(top_srcdir)/dapicore/CMD/par_char.c \
$(top_srcdir)/dapicore/CMD/par_def.h \
$(top_srcdir)/dapicore/CMD/par_def1.h \
$(top_srcdir)/dapicore/CMD/par_dict.c \
$(top_srcdir)/dapicore/CMD/par_pars.c \
$(top_srcdir)/dapicore/CMD/par_rule.c \
$(top_srcdir)/plat/unix/include/DTFnxExStdlib.h \
$(top_srcdir)/plat/unix/include/port.h \
$(top_srcdir)/shared/include/DTFnxStdlib.h 

LIBCMD_LDFLAGS_FLAGS=
LIBCMD_LIBADD_FLAGS=

if BUILD_MULTILANGUAGE_ENGINE
if BUILD_INTEGER_ENGINE
noinst_LTLIBRARIES += libcmd-integer-mul.la
libcmd_integer_mul_la_LDFLAGS = $(LIBCMD_LDFLAGS_FLAGS)
libcmd_integer_mul_la_LIBADD = $(LIBCMD_LIBADD_FLAGS)
libcmd_integer_mul_la_CPPFLAGS = $(DECTALK_DEFINES) -DINTEGER $(LIBCMD_INCLUDE_FLAGS)
libcmd_integer_mul_la_SOURCES = $(LIBCMD_SRCS)
endif

if BUILD_HLSYN_ENGINE
noinst_LTLIBRARIES += libcmd-hlsyn-mul.la
libcmd_hlsyn_mul_la_LDFLAGS = $(LIBCMD_LDFLAGS_FLAGS)
libcmd_hlsyn_mul_la_LIBADD = $(LIBCMD_LIBADD_FLAGS)
libcmd_hlsyn_mul_la_CPPFLAGS = $(DECTALK_DEFINES) -DHLSYN $(LIBCMD_INCLUDE_FLAGS)
libcmd_hlsyn_mul_la_SOURCES = $(LIBCMD_SRCS)
endif
else

# US English
if BUILD_INTEGER_ENGINE
noinst_LTLIBRARIES += libcmd-integer-en_US.la
libcmd_integer_en_US_la_LDFLAGS = $(LIBCMD_LDFLAGS_FLAGS)
libcmd_integer_en_US_la_LIBADD = $(LIBCMD_LIBADD_FLAGS)
libcmd_integer_en_US_la_CPPFLAGS = $(DECTALK_DEFINES) -DINTEGER $(EN_US_DEFINES) $(LIBCMD_INCLUDE_FLAGS)
libcmd_integer_en_US_la_SOURCES = $(LIBCMD_SRCS)
endif

if BUILD_HLSYN_ENGINE
noinst_LTLIBRARIES += libcmd-hlsyn-en_US.la
libcmd_hlsyn_en_US_la_LDFLAGS = $(LIBCMD_LDFLAGS_FLAGS)
libcmd_hlsyn_en_US_la_LIBADD = $(LIBCMD_LIBADD_FLAGS)
libcmd_hlsyn_en_US_la_CPPFLAGS = $(DECTALK_DEFINES) -DHLSYN $(EN_US_DEFINES) $(LIBCMD_INCLUDE_FLAGS)
libcmd_hlsyn_en_US_la_SOURCES = $(LIBCMD_SRCS)
endif

# UK English
if BUILD_INTEGER_ENGINE
noinst_LTLIBRARIES += libcmd-integer-en_GB.la
libcmd_integer_en_GB_la_LDFLAGS = $(LIBCMD_LDFLAGS_FLAGS)
libcmd_integer_en_GB_la_LIBADD = $(LIBCMD_LIBADD_FLAGS)
libcmd_integer_en_GB_la_CPPFLAGS = $(DECTALK_DEFINES) -DINTEGER $(EN_GB_DEFINES) $(LIBCMD_INCLUDE_FLAGS)
libcmd_integer_en_GB_la_SOURCES = $(LIBCMD_SRCS)
endif

if BUILD_HLSYN_ENGINE
noinst_LTLIBRARIES += libcmd-hlsyn-en_GB.la
libcmd_hlsyn_en_GB_la_LDFLAGS = $(LIBCMD_LDFLAGS_FLAGS)
libcmd_hlsyn_en_GB_la_LIBADD = $(LIBCMD_LIBADD_FLAGS)
libcmd_hlsyn_en_GB_la_CPPFLAGS = $(DECTALK_DEFINES) -DHLSYN $(EN_GB_DEFINES) $(LIBCMD_INCLUDE_FLAGS)
libcmd_hlsyn_en_GB_la_SOURCES = $(LIBCMD_SRCS)
endif

# Iberian Spanish
if BUILD_INTEGER_ENGINE
noinst_LTLIBRARIES += libcmd-integer-es_ES.la
libcmd_integer_es_ES_la_LDFLAGS = $(LIBCMD_LDFLAGS_FLAGS)
libcmd_integer_es_ES_la_LIBADD = $(LIBCMD_LIBADD_FLAGS)
libcmd_integer_es_ES_la_CPPFLAGS = $(DECTALK_DEFINES) -DINTEGER $(ES_ES_DEFINES) $(LIBCMD_INCLUDE_FLAGS)
libcmd_integer_es_ES_la_SOURCES = $(LIBCMD_SRCS)
endif

if BUILD_HLSYN_ENGINE
noinst_LTLIBRARIES += libcmd-hlsyn-es_ES.la
libcmd_hlsyn_es_ES_la_LDFLAGS = $(LIBCMD_LDFLAGS_FLAGS)
libcmd_hlsyn_es_ES_la_LIBADD = $(LIBCMD_LIBADD_FLAGS)
libcmd_hlsyn_es_ES_la_CPPFLAGS = $(DECTALK_DEFINES) -DHLSYN $(ES_ES_DEFINES) $(LIBCMD_INCLUDE_FLAGS)
libcmd_hlsyn_es_ES_la_SOURCES = $(LIBCMD_SRCS)
endif

# Latin American Spanish
if BUILD_INTEGER_ENGINE
noinst_LTLIBRARIES += libcmd-integer-es_LA.la
libcmd_integer_es_LA_la_LDFLAGS = $(LIBCMD_LDFLAGS_FLAGS)
libcmd_integer_es_LA_la_LIBADD = $(LIBCMD_LIBADD_FLAGS)
libcmd_integer_es_LA_la_CPPFLAGS = $(DECTALK_DEFINES) -DINTEGER $(ES_LA_DEFINES) $(LIBCMD_INCLUDE_FLAGS)
libcmd_integer_es_LA_la_SOURCES = $(LIBCMD_SRCS)
endif

if BUILD_HLSYN_ENGINE
noinst_LTLIBRARIES += libcmd-hlsyn-es_LA.la
libcmd_hlsyn_es_LA_la_LDFLAGS = $(LIBCMD_LDFLAGS_FLAGS)
libcmd_hlsyn_es_LA_la_LIBADD = $(LIBCMD_LIBADD_FLAGS)
libcmd_hlsyn_es_LA_la_CPPFLAGS = $(DECTALK_DEFINES) -DHLSYN $(ES_LA_DEFINES) $(LIBCMD_INCLUDE_FLAGS)
libcmd_hlsyn_es_LA_la_SOURCES = $(LIBCMD_SRCS)
endif

# German
if BUILD_INTEGER_ENGINE
noinst_LTLIBRARIES += libcmd-integer-de_DE.la
libcmd_integer_de_DE_la_LDFLAGS = $(LIBCMD_LDFLAGS_FLAGS)
libcmd_integer_de_DE_la_LIBADD = $(LIBCMD_LIBADD_FLAGS)
libcmd_integer_de_DE_la_CPPFLAGS = $(DECTALK_DEFINES) -DINTEGER $(DE_DE_DEFINES) $(LIBCMD_INCLUDE_FLAGS)
libcmd_integer_de_DE_la_SOURCES = $(LIBCMD_SRCS)
endif

if BUILD_HLSYN_ENGINE
noinst_LTLIBRARIES += libcmd-hlsyn-de_DE.la
libcmd_hlsyn_de_DE_la_LDFLAGS = $(LIBCMD_LDFLAGS_FLAGS)
libcmd_hlsyn_de_DE_la_LIBADD = $(LIBCMD_LIBADD_FLAGS)
libcmd_hlsyn_de_DE_la_CPPFLAGS = $(DECTALK_DEFINES) -DHLSYN $(DE_DE_DEFINES) $(LIBCMD_INCLUDE_FLAGS)
libcmd_hlsyn_de_DE_la_SOURCES = $(LIBCMD_SRCS)
endif

# French
if BUILD_INTEGER_ENGINE
noinst_LTLIBRARIES += libcmd-integer-fr_FR.la
libcmd_integer_fr_FR_la_LDFLAGS = $(LIBCMD_LDFLAGS_FLAGS)
libcmd_integer_fr_FR_la_LIBADD = $(LIBCMD_LIBADD_FLAGS)
libcmd_integer_fr_FR_la_CPPFLAGS = $(DECTALK_DEFINES) -DINTEGER $(FR_FR_DEFINES) $(LIBCMD_INCLUDE_FLAGS)
libcmd_integer_fr_FR_la_SOURCES = $(LIBCMD_SRCS)
endif

if BUILD_HLSYN_ENGINE
noinst_LTLIBRARIES += libcmd-hlsyn-fr_FR.la
libcmd_hlsyn_fr_FR_la_LDFLAGS = $(LIBCMD_LDFLAGS_FLAGS)
libcmd_hlsyn_fr_FR_la_LIBADD = $(LIBCMD_LIBADD_FLAGS)
libcmd_hlsyn_fr_FR_la_CPPFLAGS = $(DECTALK_DEFINES) -DHLSYN $(FR_FR_DEFINES) $(LIBCMD_INCLUDE_FLAGS)
libcmd_hlsyn_fr_FR_la_SOURCES = $(LIBCMD_SRCS)
endif

# Italian
if BUILD_INTEGER_ENGINE
noinst_LTLIBRARIES += libcmd-integer-it_IT.la
libcmd_integer_it_IT_la_LDFLAGS = $(LIBCMD_LDFLAGS_FLAGS)
libcmd_integer_it_IT_la_LIBADD = $(LIBCMD_LIBADD_FLAGS)
libcmd_integer_it_IT_la_CPPFLAGS = $(DECTALK_DEFINES) -DINTEGER $(IT_IT_DEFINES) $(LIBCMD_INCLUDE_FLAGS)
libcmd_integer_it_IT_la_SOURCES = $(LIBCMD_SRCS)
endif

if BUILD_HLSYN_ENGINE
noinst_LTLIBRARIES += libcmd-hlsyn-it_IT.la
libcmd_hlsyn_it_IT_la_LDFLAGS = $(LIBCMD_LDFLAGS_FLAGS)
libcmd_hlsyn_it_IT_la_LIBADD = $(LIBCMD_LIBADD_FLAGS)
libcmd_hlsyn_it_IT_la_CPPFLAGS = $(DECTALK_DEFINES) -DHLSYN $(IT_IT_DEFINES) $(LIBCMD_INCLUDE_FLAGS)
libcmd_hlsyn_it_IT_la_SOURCES = $(LIBCMD_SRCS)
endif
endif # BUILD_MULTILANGUAGE_ENGINE

# End of cmd.mk

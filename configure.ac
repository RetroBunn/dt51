#
# configure.ac 
#

AC_PREREQ(2.59)
AC_INIT([DECtalk], [5.1.0], [support@fonix.com], [DECtalk])
AC_CONFIG_SRCDIR([DAPI/ttsapi.c])
AC_CONFIG_AUX_DIR([plat/autotools/build])
AC_CONFIG_MACRO_DIR([plat/autotools/build])
#AC_CONFIG_HEADER([config.h])
AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CC
AC_PROG_CC_C_O
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL
AC_PROG_SED

# let user choose engines to build
AC_ARG_ENABLE(hlsyn, [  --enable-hlsyn=yes|no       build the DECtalk HLSYN TTS engine (default yes)],
                  build_hdt_engine="$enableval", build_hdt_engine="yes")

AC_ARG_ENABLE(integer, [  --enable-integer=yes|no       build the DECtalk integer TTS engine (default yes)],
                  build_idt_engine="$enableval", build_idt_engine="yes")

AC_ARG_ENABLE(demo, [  --enable-demo=yes|no       build the DECtalk demo libs (default yes)],
                  build_demo_libs="$enableval", build_demo_libs="yes")

AC_ARG_ENABLE(de_DE, [  --enable-es_LA=yes|no       build the DECtalk German library (default yes)],
                  build_de_DE="$enableval", build_de_DE="yes")

AC_ARG_ENABLE(en_GB, [  --enable-en_GB=yes|no       build the DECtalk GB English library (default yes)],
                  build_en_GB="$enableval", build_en_GB="yes")

AC_ARG_ENABLE(en_US, [  --enable-en_US=yes|no       build the DECtalk US English library (default yes)],
                  build_en_US="$enableval", build_en_US="yes")

AC_ARG_ENABLE(es_ES, [  --enable-es_ES=yes|no       build the DECtalk Iberian Spanish library (default yes)],
                  build_es_ES="$enableval", build_es_ES="yes")

AC_ARG_ENABLE(es_LA, [  --enable-es_LA=yes|no       build the DECtalk Latin American Spanish library (default yes)],
                  build_es_LA="$enableval", build_es_LA="yes")

AC_ARG_ENABLE(fr_FR, [  --enable-fr_FR=yes|no       build the DECtalk French library (default yes)],
                  build_fr_FR="$enableval", build_fr_FR="yes")

AC_ARG_ENABLE(he_IL, [  --enable-he_IL=yes|no       build the DECtalk Hebrew library (default yes)],
                  build_he_IL="$enableval", build_he_IL="yes")

AC_ARG_ENABLE(it_IT, [  --enable-it_IT=yes|no       build the DECtalk Italian library (default yes)],
                  build_it_IT="$enableval", build_it_IT="yes")

AC_ARG_ENABLE(ja_JP, [  --enable-ja_JP=yes|no       build the DECtalk Japanese library (default yes)],
                  build_ja_JP="$enableval", build_ja_JP="yes")

AC_ARG_ENABLE(ko_KR, [  --enable-ko_KR=yes|no       build the DECtalk Korean library (default yes)],
                  build_ko_KR="$enableval", build_ko_KR="yes")

AC_ARG_ENABLE(zh_CN, [  --enable-zh_CN=yes|no       build the DECtalk Chinese library (default yes)],
                  build_zh_CN="$enableval", build_zh_CN="yes")


# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_VOLATILE
AC_C_LONG_LONG

# Set up defines for machine dependent stuff
DECTALK_DEFINES="-DLTSSIM -DTTSSIM -DANSI -DBLD_DECTALK_DLL -DACCESS32 -DTYPING_MODE -DNEW_MULTI_LANG_ARCH -DNO_INCLUDED_C_FILES"
LICENSE_DEFINES=""
AC_C_BIGENDIAN([DECTALK_DEFINES="$DECTALK_DEFINES -D_BIGENDIAN_"; LICENSE_DEFINES="$LICENSE_DEFINES -D_BIGENDIAN_"])

IS_CHIP_SPARC="no"
AC_MSG_CHECKING([target CPU])
case "$target_cpu" in
    i[[3456]]86*)
          AC_DEFINE([WORDS_LITTLEENDIAN])
    ;;
    powerpc*)
          AC_DEFINE([WORDS_BIGENDIAN])
    ;;
    sh*)
          AC_DEFINE([WORDS_LITTLEENDIAN])
    ;;
    arm*)
          AC_DEFINE([WORDS_LITTLEENDIAN])
    ;;
    sparc*)
        AC_DEFINE([WORDS_BIGENDIAN])
        IS_CHIP_SPARC="yes"
    ;;
esac
AC_MSG_RESULT($target_cpu)

AC_MSG_CHECKING([target OS])
case "$target_os" in
    linux*)
        DECTALK_DEFINES="$DECTALK_DEFINES -DNOMME"
	PLAT_DIR="Linux"        
    ;;
    sun*)
        if test "$IS_CHIP_SPARC" = "yes"; then
                DECTALK_DEFINES="$DECTALK_DEFINES -D_SPARC_SOLARIS_"
                LICENSE_DEFINES="$LICENSE_DEFINES -D_SPARC_SOLARIS_"
        fi      
	PLAT_DIR="Sun"        
    ;;
    apple*)
        DECTALK_DEFINES="$DECTALK_DEFINES -D_APPLE_MAC_"
	PLAT_DIR="Apple"        
    ;;
    ipaq*)
        DECTALK_DEFINES="$DECTALK_DEFINES -DNOMME -D__ipaq__"
	PLAT_DIR="ipaq"        
    ;;
    nto-qnx*)
        DECTALK_DEFINES="$DECTALK_DEFINES -DNOMME"
	PLAT_DIR="QNX"        
    ;;
esac
AC_MSG_RESULT($target_os)
AC_SUBST([DECTALK_DEFINES])
AC_SUBST([LICENSE_DEFINES])

# build these engines
if test "$build_hdt_engine" != "yes" -a "$build_idt_engine" != "yes" ; then
    AC_MSG_ERROR("neither hlsyn or integer are enabled")
fi

AM_CONDITIONAL([OSYSTEM_LINUX], [test "$PLAT_DIR" = "Linux"])
AM_CONDITIONAL([OSYSTEM_QNX], [test "$PLAT_DIR" = "QNX"])
AM_CONDITIONAL([BUILD_HLSYN_ENGINE], [test "$build_hdt_engine" = "yes"])
AM_CONDITIONAL([BUILD_INTEGER_ENGINE], [test "$build_idt_engine" = "yes"])
AM_CONDITIONAL([BUILD_DEMO_LIBS], [test "$build_demo_libs" = "yes"])
AM_CONDITIONAL([BUILD_DE_DE], [test "$build_de_DE" = "yes"])
AM_CONDITIONAL([BUILD_EN_GB], [test "$build_en_GB" = "yes"])
AM_CONDITIONAL([BUILD_EN_US], [test "$build_en_US" = "yes"])
AM_CONDITIONAL([BUILD_ES_ES], [test "$build_es_ES" = "yes"])
AM_CONDITIONAL([BUILD_ES_LA], [test "$build_es_LA" = "yes"])
AM_CONDITIONAL([BUILD_FR_FR], [test "$build_fr_FR" = "yes"])
AM_CONDITIONAL([BUILD_HE_IL], [test "$build_he_IL" = "yes"])
AM_CONDITIONAL([BUILD_IT_IT], [test "$build_it_IT" = "yes"])
AM_CONDITIONAL([BUILD_JA_JP], [test "$build_ja_JP" = "yes"])
AM_CONDITIONAL([BUILD_KO_KR], [test "$build_ko_KR" = "yes"])
AM_CONDITIONAL([BUILD_ZH_CN], [test "$build_zh_CN" = "yes"])

# Checks for library functions.
ACX_PTHREAD
AC_CHECK_LIB(c, dlopen, LIBDL="", [AC_CHECK_LIB(dl, dlopen, LIBDL="-ldl")])
AC_SUBST([LIBDL])

# write out makefile
AC_CONFIG_FILES([Makefile])

AC_OUTPUT

# End of configure.ac

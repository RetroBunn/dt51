#
# dectalk.mk -- part for libdectalk.la
#

LIBDECTALK_INCLUDE_FLAGS = \
$(PLAT_PROC_INCLUDES) \
-I$(top_srcdir)/DAPI \
-I$(top_srcdir)/dapicore/CMD \
-I$(top_srcdir)/dapicore/hlsyn \
-I$(top_srcdir)/dapicore/INCLUDE \
-I$(top_srcdir)/dapicore/LTS \
-I$(top_srcdir)/dapicore/LTS/CodePageConv \
-I$(top_srcdir)/dapicore/LTS/chinese \
-I$(top_srcdir)/dapicore/PH \
-I$(top_srcdir)/dapicore/VTM \
-I$(top_srcdir)/sdk/include \
-I$(top_srcdir)/shared/include 

LIBDECTALK_SRCS = \
$(top_srcdir)/DAPI/coop.h \
$(top_srcdir)/DAPI/crypt2.c \
$(top_srcdir)/DAPI/decstd97.c \
$(top_srcdir)/DAPI/setltslanguage.h \
$(top_srcdir)/DAPI/tts.h \
$(top_srcdir)/DAPI/ttsapi.c \
$(top_srcdir)/DAPI/ttserr.h \
$(top_srcdir)/dapicore/CMD/c_us_cde.h \
$(top_srcdir)/dapicore/CMD/cm_cdef.h \
$(top_srcdir)/dapicore/CMD/cm_char.c \
$(top_srcdir)/dapicore/CMD/cm_cmd.c \
$(top_srcdir)/dapicore/CMD/cm_cmd.h \
$(top_srcdir)/dapicore/CMD/cm_cons.h \
$(top_srcdir)/dapicore/CMD/cm_copt.c \
$(top_srcdir)/dapicore/CMD/cm_copt.h \
$(top_srcdir)/dapicore/CMD/cm_data.h \
$(top_srcdir)/dapicore/CMD/cm_def.h \
$(top_srcdir)/dapicore/CMD/cm_defs.h \
$(top_srcdir)/dapicore/CMD/cm_main.c \
$(top_srcdir)/dapicore/CMD/cm_pars.c \
$(top_srcdir)/dapicore/CMD/cm_phon.c \
$(top_srcdir)/dapicore/CMD/cm_phon.h \
$(top_srcdir)/dapicore/CMD/cm_prot.h \
$(top_srcdir)/dapicore/CMD/cm_text.c \
$(top_srcdir)/dapicore/CMD/cm_text.h \
$(top_srcdir)/dapicore/CMD/cm_util.c \
$(top_srcdir)/dapicore/CMD/cm_util.h \
$(top_srcdir)/dapicore/CMD/cmd_init.c \
$(top_srcdir)/dapicore/CMD/cmd_wav.c \
$(top_srcdir)/dapicore/CMD/comp_dum.h \
$(top_srcdir)/dapicore/CMD/compnoun.h \
$(top_srcdir)/dapicore/CMD/par_ambi.c \
$(top_srcdir)/dapicore/CMD/par_bin.h \
$(top_srcdir)/dapicore/CMD/par_char.c \
$(top_srcdir)/dapicore/CMD/par_def.h \
$(top_srcdir)/dapicore/CMD/par_def1.h \
$(top_srcdir)/dapicore/CMD/par_dict.c \
$(top_srcdir)/dapicore/CMD/par_pars1.c \
$(top_srcdir)/dapicore/CMD/par_rule.c \
$(top_srcdir)/dapicore/CMD/par_rule2.h \
$(top_srcdir)/dapicore/INCLUDE/186.h \
$(top_srcdir)/dapicore/INCLUDE/cmd.h \
$(top_srcdir)/dapicore/INCLUDE/dectalk.h \
$(top_srcdir)/dapicore/INCLUDE/defs.h \
$(top_srcdir)/dapicore/INCLUDE/dt_abort.h \
$(top_srcdir)/dapicore/INCLUDE/esc.h \
$(top_srcdir)/dapicore/INCLUDE/fr_def.h \
$(top_srcdir)/dapicore/INCLUDE/ger_def.h \
$(top_srcdir)/dapicore/INCLUDE/iso_char.h \
$(top_srcdir)/dapicore/INCLUDE/it_def.h \
$(top_srcdir)/dapicore/INCLUDE/jp_def.h \
$(top_srcdir)/dapicore/INCLUDE/kernel.h \
$(top_srcdir)/dapicore/INCLUDE/l_all_ph.h \
$(top_srcdir)/dapicore/INCLUDE/l_com_ph.h \
$(top_srcdir)/dapicore/INCLUDE/la_def.h \
$(top_srcdir)/dapicore/INCLUDE/mulawi.h \
$(top_srcdir)/dapicore/INCLUDE/pcport.h \
$(top_srcdir)/dapicore/INCLUDE/phonlist.h \
$(top_srcdir)/dapicore/INCLUDE/pipe.h \
$(top_srcdir)/dapicore/INCLUDE/samprate.h \
$(top_srcdir)/dapicore/INCLUDE/spa_def.h \
$(top_srcdir)/dapicore/INCLUDE/spc.h \
$(top_srcdir)/dapicore/INCLUDE/uk_def.h \
$(top_srcdir)/dapicore/INCLUDE/usa_def.h \
$(top_srcdir)/dapicore/KERNEL/Usa_init.c \
$(top_srcdir)/dapicore/KERNEL/services.c \
$(top_srcdir)/dapicore/LTS/CodePageConv/CodePageConv.h \
$(top_srcdir)/dapicore/LTS/CodePageConv/CodePageConv.c \
$(top_srcdir)/dapicore/LTS/ls_acna.h \
$(top_srcdir)/dapicore/LTS/ls_char.h \
$(top_srcdir)/dapicore/LTS/ls_cons.h \
$(top_srcdir)/dapicore/LTS/ls_data.h \
$(top_srcdir)/dapicore/LTS/ls_def.h \
$(top_srcdir)/dapicore/LTS/ls_defs.h \
$(top_srcdir)/dapicore/LTS/ls_dict.h \
$(top_srcdir)/dapicore/LTS/ls_prot.h \
$(top_srcdir)/dapicore/LTS/lsa_cons.h \
$(top_srcdir)/dapicore/LTS/lsa_prot.h \
$(top_srcdir)/dapicore/PH/Ph_drwt02.c \
$(top_srcdir)/dapicore/PH/Ph_fr_inton2.c \
$(top_srcdir)/dapicore/PH/Ph_inton2.c \
$(top_srcdir)/dapicore/PH/Ph_intonnew.c \
$(top_srcdir)/dapicore/PH/hlsynapi.h \
$(top_srcdir)/dapicore/PH/p_all_ph.h \
$(top_srcdir)/dapicore/PH/p_ch_rom.h \
$(top_srcdir)/dapicore/PH/p_ch_sr1.c \
$(top_srcdir)/dapicore/PH/p_ch_st1.c \
$(top_srcdir)/dapicore/PH/p_ch_sy1.c \
$(top_srcdir)/dapicore/PH/p_ch_tim.c \
$(top_srcdir)/dapicore/PH/p_fr_rom.h \
$(top_srcdir)/dapicore/PH/p_fr_sr1.c \
$(top_srcdir)/dapicore/PH/p_fr_st1.c \
$(top_srcdir)/dapicore/PH/p_fr_sy1.c \
$(top_srcdir)/dapicore/PH/p_fr_tim.c \
$(top_srcdir)/dapicore/PH/p_gr_rom.h \
$(top_srcdir)/dapicore/PH/p_gr_sr1.c \
$(top_srcdir)/dapicore/PH/p_gr_st1.c \
$(top_srcdir)/dapicore/PH/p_gr_tim.c \
$(top_srcdir)/dapicore/PH/p_hb_rom.h \
$(top_srcdir)/dapicore/PH/p_he_st1.c \
$(top_srcdir)/dapicore/PH/p_he_tim.c \
$(top_srcdir)/dapicore/PH/p_it_rom.h \
$(top_srcdir)/dapicore/PH/p_it_st1.c \
$(top_srcdir)/dapicore/PH/p_it_sy1.c \
$(top_srcdir)/dapicore/PH/p_it_tim.c \
$(top_srcdir)/dapicore/PH/p_jp_rom.h \
$(top_srcdir)/dapicore/PH/p_jp_sr1.c \
$(top_srcdir)/dapicore/PH/p_jp_st1.c \
$(top_srcdir)/dapicore/PH/p_jp_sy1.c \
$(top_srcdir)/dapicore/PH/p_jp_tim.c \
$(top_srcdir)/dapicore/PH/p_kr_rom.h \
$(top_srcdir)/dapicore/PH/p_kr_sr1.c \
$(top_srcdir)/dapicore/PH/p_kr_st1.c \
$(top_srcdir)/dapicore/PH/p_kr_sy1.c \
$(top_srcdir)/dapicore/PH/p_kr_tim.c \
$(top_srcdir)/dapicore/PH/p_krnew_tim.c \
$(top_srcdir)/dapicore/PH/p_la_rom.h \
$(top_srcdir)/dapicore/PH/p_la_sr1.c \
$(top_srcdir)/dapicore/PH/p_la_st1.c \
$(top_srcdir)/dapicore/PH/p_la_sy1.c \
$(top_srcdir)/dapicore/PH/p_la_tim.c \
$(top_srcdir)/dapicore/PH/p_sp_rom.h \
$(top_srcdir)/dapicore/PH/p_sp_sr1.c \
$(top_srcdir)/dapicore/PH/p_sp_st1.c \
$(top_srcdir)/dapicore/PH/p_sp_sy1.c \
$(top_srcdir)/dapicore/PH/p_sp_tim.c \
$(top_srcdir)/dapicore/PH/p_uk_rom.h \
$(top_srcdir)/dapicore/PH/p_uk_sr1.c \
$(top_srcdir)/dapicore/PH/p_uk_st1.c \
$(top_srcdir)/dapicore/PH/p_uk_sy1.c \
$(top_srcdir)/dapicore/PH/p_uk_tim.c \
$(top_srcdir)/dapicore/PH/p_us_rom.h \
$(top_srcdir)/dapicore/PH/p_us_sr1.c \
$(top_srcdir)/dapicore/PH/p_us_st1.c \
$(top_srcdir)/dapicore/PH/p_us_sy1.c \
$(top_srcdir)/dapicore/PH/p_us_tim.c \
$(top_srcdir)/dapicore/PH/p_us_vdf1.h \
$(top_srcdir)/dapicore/PH/ph_aloph.c \
$(top_srcdir)/dapicore/PH/ph_claus.c \
$(top_srcdir)/dapicore/PH/ph_data.h \
$(top_srcdir)/dapicore/PH/ph_def.h \
$(top_srcdir)/dapicore/PH/ph_defs.h \
$(top_srcdir)/dapicore/PH/ph_draw.c \
$(top_srcdir)/dapicore/PH/ph_main.c \
$(top_srcdir)/dapicore/PH/ph_prot.h \
$(top_srcdir)/dapicore/PH/ph_romi.c \
$(top_srcdir)/dapicore/PH/ph_setar.c \
$(top_srcdir)/dapicore/PH/ph_sort.c \
$(top_srcdir)/dapicore/PH/ph_sort2.c \
$(top_srcdir)/dapicore/PH/ph_sttr2.c \
$(top_srcdir)/dapicore/PH/ph_syl.c \
$(top_srcdir)/dapicore/PH/ph_task.c \
$(top_srcdir)/dapicore/PH/ph_timng.c \
$(top_srcdir)/dapicore/PH/ph_vdefi.c \
$(top_srcdir)/dapicore/PH/ph_vset.c \
$(top_srcdir)/dapicore/PH/phinit.c \
$(top_srcdir)/dapicore/PH/phlog.c \
$(top_srcdir)/dapicore/PH/phprint.c \
$(top_srcdir)/dapicore/VTM/playtone.c \
$(top_srcdir)/dapicore/VTM/sinetab.h \
$(top_srcdir)/dapicore/VTM/sync.c \
$(top_srcdir)/dapicore/VTM/syncmain.h \
$(top_srcdir)/dapicore/VTM/tunecheck.h \
$(top_srcdir)/dapicore/VTM/vtm3.c \
$(top_srcdir)/dapicore/VTM/vtmfunc.h \
$(top_srcdir)/dapicore/VTM/vtminst.h \
$(top_srcdir)/dapicore/VTM/vtmiont.c \
$(top_srcdir)/dapicore/VTM/vtmtable.h \
$(top_srcdir)/dapicore/hlsyn/acxf1c.c \
$(top_srcdir)/dapicore/hlsyn/brent.c \
$(top_srcdir)/dapicore/hlsyn/circuit.c \
$(top_srcdir)/dapicore/hlsyn/flavor.h \
$(top_srcdir)/dapicore/hlsyn/hlframe.c \
$(top_srcdir)/dapicore/hlsyn/hlsyn.h \
$(top_srcdir)/dapicore/hlsyn/inithl.c \
$(top_srcdir)/dapicore/hlsyn/log10table.c \
$(top_srcdir)/dapicore/hlsyn/nasalf1x.c \
$(top_srcdir)/dapicore/hlsyn/sqrttable.c \
$(top_srcdir)/plat/unix/include/DTFnxExStdlib.h \
$(top_srcdir)/plat/unix/include/port.h \
$(top_srcdir)/plat/unix/src/DTFnxExStdlib.c \
$(top_srcdir)/sdk/include/ttsapi.h \
$(top_srcdir)/sdk/include/ttsfeat.h \
$(top_srcdir)/sdk/include/unix/dectalktypes.h \
$(top_srcdir)/sdk/include/unix/dtmmedefs.h \
$(top_srcdir)/shared/include/DTFnxStdlib.h \
$(top_srcdir)/shared/include/dectalkf.h \
$(top_srcdir)/shared/include/mmalloc.h \
$(top_srcdir)/shared/include/opatype.h \
$(top_srcdir)/shared/include/opmmsys.h \
$(top_srcdir)/shared/include/opthread.h \
$(top_srcdir)/shared/include/playaud.h \
$(top_srcdir)/shared/include/playaudd.h \
$(top_srcdir)/shared/include/shmalloc.h \
$(top_srcdir)/shared/src/pipe.c \
$(top_srcdir)/shared/src/playaud.c \
$(top_srcdir)/shared/src/spc.c 

LIBDECTALK_LDFLAGS_FLAGS = -version-info 0:0:0 -export-symbols $(top_srcdir)/plat/unix/sym/dectalk.sym
LIBDECTALK_LIBADD_FLAGS = libopthread.la libmmalloc.la $(PTHREAD_LIBS) $(LIBDL)

if BUILD_INTEGER_ENGINE
lib_LTLIBRARIES += libdectalk-integer.la
libdectalk_integer_la_LDFLAGS = $(LIBDECTALK_LDFLAGS_FLAGS)
libdectalk_integer_la_LIBADD = $(LIBDECTALK_LIBADD_FLAGS)
libdectalk_integer_la_CPPFLAGS = $(DECTALK_DEFINES) -DINTEGER $(EN_US_DEFINES) $(LIBDECTALK_INCLUDE_FLAGS)
libdectalk_integer_la_SOURCES = $(LIBDECTALK_SRCS)
endif

if BUILD_HLSYN_ENGINE
lib_LTLIBRARIES += libdectalk-hlsyn.la
libdectalk_hlsyn_la_LDFLAGS = $(LIBDECTALK_LDFLAGS_FLAGS)
libdectalk_hlsyn_la_LIBADD = $(LIBDECTALK_LIBADD_FLAGS)
libdectalk_hlsyn_la_CPPFLAGS = $(DECTALK_DEFINES) -DHLSYN $(EN_US_DEFINES) $(LIBDECTALK_INCLUDE_FLAGS)
libdectalk_hlsyn_la_SOURCES = $(LIBDECTALK_SRCS)
endif

# End of dectalk.mk

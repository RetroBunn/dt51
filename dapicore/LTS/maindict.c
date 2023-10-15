#include "dectalkf.h"

#if defined EPSON_ARM7 || defined MULTIPLE_LANGUAGES_LOADED
#include "ltsnames.h"
#endif

//included dictionaries are compressed - MAKE SURE CHEESY_DICT_COMPRESSION is defined
#ifdef FRENCH
#ifdef CASIO_SH3
#ifdef _BIGENDIAN
#include "maindict_fr_casio_big.h"
#else
#include "maindict_fr_casio.h"
#endif //_BIGENDIAN
#else //CASIO_SH3
#ifdef _BIGENDIAN_
#ifdef CHEESY_DICT_COMPRESSION
#include "maindict_fr_big_compress.h"
#else
#include "maindict_fr_big.h"
#endif
#else
#ifdef CHEESY_DICT_COMPRESSION
#include "maindict_fr_compress.h"
#else
#include "maindict_fr.h"
#endif //CHEESY_DICT_COMPRESSION
#endif //_BIGENDIAN
#endif //CASIO_SH3
#endif //FRENCH

#ifdef GERMAN
#ifdef CASIO_SH3
#ifdef _BIGENDIAN
#include "maindict_gr_casio_big.h"
#else
#include "maindict_gr_casio.h"
#endif //_BIGENDIAN
#else //CASIO_SH3
#ifdef _BIGENDIAN_
#ifdef CHEESY_DICT_COMPRESSION
#include "maindict_gr_big_compress.h"
#else
#include "maindict_gr_big.h"
#endif
#else
#ifdef CHEESY_DICT_COMPRESSION
#include "maindict_gr_compress.h"
#else
#include "maindict_gr.h"
#endif //CHEESY_DICT_COMPRESSION
#endif //_BIGENDIAN
#endif //CASIO_SH3
#endif

#ifdef SPANISH_SP
#ifdef CASIO_SH3
#ifdef _BIGENDIAN
#include "maindict_sp_casio_big.h"
#else
#include "maindict_sp_casio.h"
#endif //_BIGENDIAN
#else //CASIO_SH3
#ifdef _BIGENDIAN_
#ifdef CHEESY_DICT_COMPRESSION
#include "maindict_sp_big_compress.h"
#else
#include "maindict_sp_big.h"
#endif
#else
#ifdef CHEESY_DICT_COMPRESSION
#include "maindict_sp_compress.h"
#else
#include "maindict_sp.h"
#endif //CHEESY_DICT_COMPRESSION
#endif //_BIGENDIAN
#endif //CASIO_SH3
#endif

#ifdef SPANISH_LA
#ifdef CASIO_SH3
#ifdef _BIGENDIAN
#include "maindict_la_casio_big.h"
#else
#include "maindict_la_casio.h"
#endif //_BIGENDIAN
#else //CASIO_SH3
#ifdef _BIGENDIAN_
#ifdef CHEESY_DICT_COMPRESSION
#include "maindict_la_big_compress.h"
#else
#include "maindict_la_big.h"
#endif
#else
#ifdef CHEESY_DICT_COMPRESSION
#include "maindict_la_compress.h"
#else
#include "maindict_la.h"
#endif //CHEESY_DICT_COMPRESSION
#endif //_BIGENDIAN
#endif //CASIO_SH3
#endif

#ifdef ENGLISH_UK
#ifdef CASIO_SH3
#ifdef _BIGENDIAN
#include "maindict_uk_casio_big.h"
#else
#include "maindict_uk_casio.h"
#endif //_BIGENDIAN
#else //CASIO_SH3
#ifdef _BIGENDIAN_
#ifdef CHEESY_DICT_COMPRESSION
#ifdef DICT_COMPLETE
#include "maindict_uk_comp_big_compress.h"
#else
#include "maindict_uk_big_compress.h"
#endif
#else
#ifdef DICT_COMPLETE
#include "maindict_uk_comp_big.h"
#else
#include "maindict_uk_big.h"
#endif
#endif
#else
#ifdef CHEESY_DICT_COMPRESSION
#ifdef DICT_COMPLETE
#include "maindict_uk_comp_compress.h"
#else
#include "maindict_uk_compress.h"
#endif
#else
#ifdef DICT_COMPLETE
#include "maindict_uk_comp.h"
#else
#include "maindict_uk.h"
#endif
#endif //CHEESY_DICT_COMPRESSION
#endif //_BIGENDIAN
#endif //CASIO_SH3
#endif //ENGLISH_UK

#ifdef ENGLISH_US
#ifdef CASIO_SH3
#ifdef _BIGENDIAN
#include "maindict_us_casio_big.h"
#else
#include "maindict_us_casio.h"
#endif //_BIGENDIAN
#else //CASIO_SH3
#ifdef _BIGENDIAN_
#ifdef CHEESY_DICT_COMPRESSION
#ifdef DICT_COMPLETE
#include "maindict_us_comp_big_compress.h"
#else
#include "maindict_us_big_compress.h"
#endif
#else
#ifdef DICT_COMPLETE
#include "maindict_us_comp_big.h"
#else
#include "maindict_us_big.h"
#endif
#endif
#else
#ifdef CHEESY_DICT_COMPRESSION
#ifdef DICT_COMPLETE
#include "maindict_us_comp_compress.h"
#else
#include "maindict_us_compress.h"
#endif
#else
#ifdef DICT_COMPLETE
#include "maindict_us_comp.h"
#else
#include "maindict_us.h"
#endif
#endif //CHEESY_DICT_COMPRESSION
#endif //_BIGENDIAN
#endif //CASIO_SH3
#endif //ENGLISH_US

#ifdef ITALIAN
#ifdef CASIO_SH3
#ifdef _BIGENDIAN
#include "maindict_it_casio_big.h"
#else
#include "maindict_it_casio.h"
#endif //_BIGENDIAN
#else //CASIO_SH3
#ifdef _BIGENDIAN_
#ifdef CHEESY_DICT_COMPRESSION
#include "maindict_it_big_compress.h"
#else
#include "maindict_it_big.h"
#endif
#else
#ifdef CHEESY_DICT_COMPRESSION
#include "maindict_it_compress.h"
#else
#include "maindict_it.h"
#endif //CHEESY_DICT_COMPRESSION
#endif //_BIGENDIAN
#endif //CASIO_SH3
#endif

//============================================================================================================
//!
//! The software is protected by copyright of Oxford Technical Solutions.
//! Copyright (C) 2018 Oxford Technical Solutions - http://www.oxts.com
//!
//! Redistribution and use in source and binary forms, with or without modification, are only permitted with
//! the specific prior written permission of Oxford Technical Solutions.
//!
//! $LastChangedDate: 2019-04-18 15:57:11 +0100 (Thu, 18 Apr 2019) $
//! $LastChangedRevision: 28052 $
//! $LastChangedBy: alambert $
//!
//! \file Lib_Compiler.h
//!
//! \brief Cross compiler support for everything other than basic types.
//!
//============================================================================================================


#ifndef LIB__COMPILER_H
#define LIB__COMPILER_H


#define LIB__COMPILER_DEV_ID "190418"  //!< Development Identification.


#include "oxts/common/Lib_Detect.h"


#if (__cplusplus)
#include <cfloat>
#include <cmath>
#include <cstring>
#else
#include <float.h>
#include <math.h>
#include <string.h>
#endif


//============================================================================================================
// MAX_PATH.

#if (OXTS_OS_QNX || OXTS_OS_TI || OXTS_OS_LINUX || OXTS_OS_XDEV)
#define OXTS_MAX_PATH 500
#else
#define OXTS_MAX_PATH _MAX_PATH
#endif


//============================================================================================================
// isnan, isinf, isfinite.

#if (OXTS_CC_MSVC)
#define oxts_isnan(x)    (_isnan((x)))
#define oxts_isfinite(x) (_finite((x)))
#define oxts_isinf(x)    (!(oxts_isfinite((x))) && !(oxts_isnan((x))))
#elif (OXTS_CC_BORLAND)
#define OXTS_COMPILER_fallback_isnan
#define OXTS_COMPILER_fallback_isinf
#define OXTS_COMPILER_fallback_isfinite
#define oxts_isnan    fallback_isnan
#define oxts_isinf    fallback_isinf
#define oxts_isfinite fallback_isfinite
#else
#if (__cplusplus && !OXTS_CC_QCC)
#define oxts_isnan(x)    (std::isnan((x)))
#define oxts_isinf(x)    (std::isinf((x)))
#else
#define oxts_isnan(x)    (isnan((x)))
#define oxts_isinf(x)    (isinf((x)))
#endif
#define oxts_isfinite(x) (!(oxts_isinf((x))) && !(oxts_isnan((x))))
#endif


//============================================================================================================
// strtok_r, gmtime_r, localtime_r.
//
// Both gmtime_s and localtime_s return zero if successful. The return value is an error code if there is a
// failure. We map this back to the pointer to the tm struct to recover gmtime_r and localtime_r behaviour.
//
// For MinGW gmtime_r and localtime_r seem to be avaliable in time.h if pthread.h has been included. Macros
// below can be used but are only thread safe if runtime uses thread-local buffer, and GCC 5.1 does not like
// them. Include string.h for strtok_r.
//
// Borland functions not greatly tested.

#if OXTS_OS_WINDOWS
	#if OXTS_CC_MSVC
		#define strtok_r(x,y,z)      strtok_s((x),(y),(z))
		#define gmtime_r(x,y)       (gmtime_s((y),(x)) ? 0 : y)
		#define localtime_r(x,y) (localtime_s((y),(x)) ? 0 : y)
	#endif
	#if OXTS_CC_BORLAND
		#define OXTS_COMPILER_fallback_strtok_r
		#define strtok_r      fallback_strtok_r
		#define gmtime_r(x,y)       (gmtime_s((y),(x)) ? 0 : y)
		#define localtime_r(x,y) (localtime_s((y),(x)) ? 0 : y)
	#endif
	#if OXTS_CC_MINGW
		#if 1
			#include "pthread.h"
		#else
		 	#ifndef strtok_r
		 		#define OXTS_COMPILER_fallback_strtok_r
		 		#define strtok_r      fallback_strtok_r
		 	#endif
		 	#ifndef gmtime_r
		 		#define gmtime_r(x,y)       (gmtime(x) ? (*(y) =    *gmtime(x),(y)) : 0)
		 	#endif
		 	#ifndef localtime_r
		 		#define localtime_r(x,y) (localtime(x) ? (*(y) = *localtime(x),(y)) : 0)
		 	#endif
		#endif
	#endif
	#if OXTS_CC_CYGWIN
		#define OXTS_COMPILER_fallback_strtok_r
		#define strtok_r      fallback_strtok_r
	#endif
#endif
#if OXTS_OS_TI
	#if OXTS_CC_TI
		#define OXTS_COMPILER_fallback_strtok_r
		#define strtok_r      fallback_strtok_r
		#define gmtime_r(x,y)       (gmtime(x) ? (*(y) =    *gmtime(x),(y)) : 0)
		#define localtime_r(x,y) (localtime(x) ? (*(y) = *localtime(x),(y)) : 0)
	#endif
#endif

#if OXTS_OS_TI
	#define OXTS_GPS_GMTIME_OFFSET_HOURS ((25567+3657)*24-6) // 1900-01-01 TI time (GMT-6 h) to 1980-01-06
#else
	#define OXTS_GPS_GMTIME_OFFSET_HOURS (3657*24)  // 1970-01-01 to 1980-01-06
#endif



//============================================================================================================
// snprintf, snscanf.

#if (OXTS_OS_WINDOWS)
#if (OXTS_CC_MSVC)
#if (_MSC_VER < 1900)
#define snprintf     _snprintf
#endif
#define snscanf      _snscanf
#endif
#endif


//============================================================================================================
// stricmp, strnicmp, strcasecmp, strncasecmp.

#if (OXTS_OS_WINDOWS)
#if (OXTS_CC_MSVC)
#define stricmp      _stricmp
#define strnicmp     _strnicmp
#define strcasecmp   _stricmp
#define strncasecmp  _strnicmp
#endif
#if (OXTS_CC_BORLAND)
#define strcasecmp    stricmp
#define strncasecmp   strnicmp
#endif
#if (OXTS_CC_MINGW)
#ifndef strcasecmp
#define OXTS_COMPILER_fallback_strcasecmp
#define stricmp       fallback_strcasecmp
#define strcasecmp    fallback_strcasecmp
#endif
#ifndef strncasecmp
#define OXTS_COMPILER_fallback_strncasecmp
#define strnicmp      fallback_strncasecmp
#define strncasecmp   fallback_strncasecmp
#endif
#endif
#endif

#if (OXTS_OS_LINUX)
#include <strings.h>
#define stricmp       strcasecmp
#define strnicmp      strncasecmp
#endif

#if (OXTS_OS_TI)
#define OXTS_COMPILER_fallback_strcasecmp
#define OXTS_COMPILER_fallback_strncasecmp
#define stricmp       fallback_strcasecmp
#define strnicmp      fallback_strncasecmp
#define strcasecmp    fallback_strcasecmp
#define strncasecmp   fallback_strncasecmp
#endif


//============================================================================================================
// strupr, strlwr.

#if (OXTS_OS_WINDOWS)
#if (OXTS_CC_MSVC)
#define strupr        _strupr
#define strlwr        _strlwr
#endif
#endif

#if (OXTS_OS_LINUX || OXTS_OS_TI)
#define OXTS_COMPILER_fallback_strupr
#define OXTS_COMPILER_fallback_strlwr
#define strupr        fallback_strupr
#define strlwr        fallback_strlwr
#endif


//============================================================================================================
// access, timezone.

#if (OXTS_OS_WINDOWS)
#if (OXTS_CC_MSVC)
#define access        _access
#define timezone      _timezone
#endif
#elif (OXTS_OS_TI || OXTS_OS_XDEV)
#define timezone _timezone
#endif


//============================================================================================================
// Actual function fallbacks rather than just macros

#if (defined __cplusplus)
extern "C" {
#endif

#ifdef OXTS_COMPILER_fallback_isnan
int   fallback_isnan(double x);
#endif

#ifdef OXTS_COMPILER_fallback_isinf
int   fallback_isinf(double x);
#endif

#ifdef OXTS_COMPILER_fallback_isfinite
int   fallback_isfinite(double);
#endif

#ifdef OXTS_COMPILER_fallback_strtok_r
char *fallback_strtok_r(char *s, const char *delim, char **last);
#endif

#ifdef OXTS_COMPILER_fallback_strcasecmp
int   fallback_strcasecmp(const char *s1, const char *s2);
#endif

#ifdef OXTS_COMPILER_fallback_strncasecmp
int   fallback_strncasecmp(const char *s1, const char *s2, unsigned n);
#endif

#ifdef OXTS_COMPILER_fallback_strupr
char *fallback_strupr(char *string);
#endif

#ifdef OXTS_COMPILER_fallback_strlwr
char *fallback_strlwr(char *string);
#endif

#if (defined __cplusplus)
}
#endif

#endif

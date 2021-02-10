//============================================================================================================
//!
//! The software is protected by copyright of Oxford Technical Solutions.
//! Copyright (C) 2018 Oxford Technical Solutions - http://www.oxts.com
//!
//! Redistribution and use in source and binary forms, with or without modification, are only permitted with
//! the specific prior written permission of Oxford Technical Solutions.
//!
//! $LastChangedDate: 2019-02-26 11:25:06 +0000 (Tue, 26 Feb 2019) $
//! $LastChangedRevision: 27721 $
//! $LastChangedBy: icleju $
//!
//! \file BasicTypes.h
//!
//! \brief Provide multiple compiler support for standard integer types for 8, 16, 32, and 64 bit quantities.
//!
//! Wish to use standard integer types for 8, 16, 32, and 64 bit quantities. Not all compilers support these
//! types. Our aim is to use (u)intN_t for low level byte conversions and counters, i.e. places where the size
//! of the type is very important. In more general code the regular types are used, where it is assumed that
//! {char, short, int, long long} <--> {8, 16, 32, 64} bit types for both 32 and 64 bit x86 systems.
//!
//! For x86 systems long can either be 32 or 64 bits so its (direct) use is avoided. The definitions below
//! should be modified according to compiler, but with preference to include cstdint for C++ or stdint.h for
//! C if provided.
//!
//! \warning It seems that MSVC does not support the usage of 8 bit integers in printf and scanf.
//!
//! By default BasicTypes detects C or C++ and includes needed files accordingly. When used in a mixed C/C++
//! project is can be desirable to force it to use either the C or the C++ includes. This feature can be used
//! by defining OXTS_FORCE_C or OXTS_FORCE_CPP.
//!
//============================================================================================================


#ifndef BASIC_TYPES_H
#define BASIC_TYPES_H

#define BASIC_TYPES_DEV_ID "130618"  //!< Development Identification.


//============================================================================================================
// Strongly recommend these are defined by a compiler option. This is because they are used to configure
// certain system headers. Having them defined only here may be to late!

#ifndef __STDC_LIMIT_MACROS
#define __STDC_LIMIT_MACROS
#endif

#ifndef __STDC_FORMAT_MACROS
#define	__STDC_FORMAT_MACROS
#endif

#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS
#endif


//============================================================================================================
#ifdef __cplusplus
 #define OXTS_FORCE_CPP
#else
#ifndef OXTS_FORCE_C
 #define OXTS_FORCE_C
#endif
#endif

#if   (defined OXTS_FORCE_C)
#define BASIC_TYPES_USE_CPP 0
#elif (defined OXTS_FORCE_CPP)
#define BASIC_TYPES_USE_CPP 1
#elif (defined __cplusplus)
#define BASIC_TYPES_USE_CPP 1
#else
#define BASIC_TYPES_USE_CPP 0
#endif


//============================================================================================================

#if(_MSC_VER)
#if(BASIC_TYPES_USE_CPP)
#include <climits>
#else
#include <limits.h>
#endif
#if(_MSC_VER < 1300)
	typedef signed   char     int8_t;
	typedef signed   short    int16_t;
	typedef signed   int      int32_t;
	typedef signed   __int64  int64_t;
	typedef unsigned char     uint8_t;
	typedef unsigned short    uint16_t;
	typedef unsigned int      uint32_t;
	typedef unsigned __int64  uint64_t;
#elif(_MSC_VER < 1600)
	typedef signed   __int8   int8_t;          //!< Standard signed integer basic type of 8 bits.
	typedef signed   __int16  int16_t;         //!< Standard signed integer basic type of 16 bits.
	typedef signed   __int32  int32_t;         //!< Standard signed integer basic type of 32 bits.
	typedef signed   __int64  int64_t;         //!< Standard signed integer basic type of 64 bits.
	typedef unsigned __int8   uint8_t;         //!< Standard unsigned integer basic type of 8 bits.
	typedef unsigned __int16  uint16_t;        //!< Standard unsigned integer basic type of 16 bits.
	typedef unsigned __int32  uint32_t;        //!< Standard unsigned integer basic type of 32 bits.
	typedef unsigned __int64  uint64_t;        //!< Standard unsigned integer basic type of 64 bits.
	#define INT8_MIN      ((int8_t)  _I8_MIN)  //!< Limit macro for the most negative value of the standard signed integer type of 8 bits.
	#define INT16_MIN     ((int16_t) _I16_MIN) //!< Limit macro for the most negative value of the standard signed integer type of 16 bits.
	#define INT32_MIN     ((int32_t) _I32_MIN) //!< Limit macro for the most negative value of the standard signed integer type of 32 bits.
	#define INT64_MIN     ((int64_t) _I64_MIN) //!< Limit macro for the most negative value of the standard signed integer type of 64 bits.
	#define INT8_MAX      (_I8_MAX)            //!< Limit macro for the most positive value of the standard signed integer type of 8 bits.
	#define INT16_MAX     (_I16_MAX)           //!< Limit macro for the most positive value of the standard signed integer type of 16 bits.
	#define INT32_MAX     (_I32_MAX)           //!< Limit macro for the most positive value of the standard signed integer type of 32 bits.
	#define INT64_MAX     (_I64_MAX)           //!< Limit macro for the most positive value of the standard signed integer type of 64 bits.
	#define UINT8_MAX     (_UI8_MAX)           //!< Limit macro for the most positive value of the standard unsigned integer type of 8 bits.
	#define UINT16_MAX    (_UI16_MAX)          //!< Limit macro for the most positive value of the standard unsigned integer type of 16 bits.
	#define UINT32_MAX    (_UI32_MAX)          //!< Limit macro for the most positive value of the standard unsigned integer type of 32 bits.
	#define UINT64_MAX    (_UI64_MAX)          //!< Limit macro for the most positive value of the standard unsigned integer type of 64 bits.
	#define INT8_C(val)   val##i8              //!< Literal constant macro for the standard signed integer type of 8 bits.
	#define INT16_C(val)  val##i16             //!< Literal constant macro for the standard signed integer type of 16 bits.
	#define INT32_C(val)  val##i32             //!< Literal constant macro for the standard signed integer type of 32 bits.
	#define INT64_C(val)  val##i64             //!< Literal constant macro for the standard signed integer type of 64 bits.
	#define UINT8_C(val)  val##ui8             //!< Literal constant macro for the standard unsigned integer type of 8 bits.
	#define UINT16_C(val) val##ui16            //!< Literal constant macro for the standard unsigned integer type of 16 bits.
	#define UINT32_C(val) val##ui32            //!< Literal constant macro for the standard unsigned integer type of 32 bits.
	#define UINT64_C(val) val##ui64            //!< Literal constant macro for the standard unsigned integer type of 64 bits.
#else
#if(BASIC_TYPES_USE_CPP)
#include <cstdint>
#else
#include <stdint.h>
#endif
#endif
	#define PRId8         #error               //!< Printing signed decimal format macro for the standard signed integer type of 8 bits.
	#define PRId16        "hd"                 //!< Printing signed decimal format macro for the standard signed integer type of 16 bits.
	#define PRId32        "I32d"               //!< Printing signed decimal format macro for the standard signed integer type of 32 bits.
	#define PRId64        "I64d"               //!< Printing signed decimal format macro for the standard signed integer type of 64 bits.
	#define PRIu8         #error               //!< Printing unsigned decimal format macro for the standard unsigned integer type of 8 bits.
	#define PRIu16        "hu"                 //!< Printing unsigned decimal format macro for the standard unsigned integer type of 16 bits.
	#define PRIu32        "I32u"               //!< Printing unsigned decimal format macro for the standard unsigned integer type of 32 bits.
	#define PRIu64        "I64u"               //!< Printing unsigned decimal format macro for the standard unsigned integer type of 64 bits.
	#define PRIo8         #error               //!< Printing unsigned octal format macro for the standard unsigned integer type of 8 bits.
	#define PRIo16        "ho"                 //!< Printing unsigned octal format macro for the standard unsigned integer type of 16 bits.
	#define PRIo32        "I32o"               //!< Printing unsigned octal format macro for the standard unsigned integer type of 32 bits.
	#define PRIo64        "I64o"               //!< Printing unsigned octal format macro for the standard unsigned integer type of 64 bits.
	#define PRIx8         #error               //!< Printing unsigned lower case hexadecimal format macro for the standard unsigned integer type of 8 bits.
	#define PRIx16        "hx"                 //!< Printing unsigned lower case hexadecimal format macro for the standard unsigned integer type of 16 bits.
	#define PRIx32        "I32x"               //!< Printing unsigned lower case hexadecimal format macro for the standard unsigned integer type of 32 bits.
	#define PRIx64        "I64x"               //!< Printing unsigned lower case hexadecimal format macro for the standard unsigned integer type of 64 bits.
	#define PRIX8         #error               //!< Printing unsigned upper case hexadecimal format macro for the standard unsigned integer type of 8 bits.
	#define PRIX16        "hX"                 //!< Printing unsigned upper case hexadecimal format macro for the standard unsigned integer type of 16 bits.
	#define PRIX32        "I32X"               //!< Printing unsigned upper case hexadecimal format macro for the standard unsigned integer type of 32 bits.
	#define PRIX64        "I64X"               //!< Printing unsigned upper case hexadecimal format macro for the standard unsigned integer type of 64 bits.
	#define SCNd8         #error               //!< Scanning signed decimal format macro for the standard signed integer type of 8 bits.
	#define SCNd16        "hd"                 //!< Scanning signed decimal format macro for the standard signed integer type of 16 bits.
	#define SCNd32        "ld"    /* CHECK */  //!< Scanning signed decimal format macro for the standard signed integer type of 32 bits. \todo Investigate this.
	#define SCNd64        "I64d"               //!< Scanning signed decimal format macro for the standard signed integer type of 64 bits.
	#define SCNu8         #error               //!< Scanning unsigned decimal format macro for the standard unsigned integer type of 8 bits.
	#define SCNu16        "hu"                 //!< Scanning unsigned decimal format macro for the standard unsigned integer type of 16 bits.
	#define SCNu32        "lu"    /* CHECK */  //!< Scanning unsigned decimal format macro for the standard unsigned integer type of 32 bits. \todo Investigate this.
	#define SCNu64        "I64u"               //!< Scanning unsigned decimal format macro for the standard unsigned integer type of 64 bits.
	#define SCNo8         #error               //!< Scanning unsigned octal format macro for the standard unsigned integer type of 8 bits.
	#define SCNo16        "ho"                 //!< Scanning unsigned octal format macro for the standard unsigned integer type of 16 bits.
	#define SCNo32        "lo"    /* CHECK */  //!< Scanning unsigned octal format macro for the standard unsigned integer type of 32 bits. \todo Investigate this.
	#define SCNo64        "I64o"               //!< Scanning unsigned octal format macro for the standard unsigned integer type of 64 bits.
	#define SCNx8         #error               //!< Scanning unsigned lower case hexadecimal format macro for the standard unsigned integer type of 8 bits.
	#define SCNx16        "hx"                 //!< Scanning unsigned lower case hexadecimal format macro for the standard unsigned integer type of 16 bits.
	#define SCNx32        "lx"    /* CHECK */  //!< Scanning unsigned lower case hexadecimal format macro for the standard unsigned integer type of 32 bits. \todo Investigate this.
	#define SCNx64        "I64x"               //!< Scanning unsigned lower case hexadecimal format macro for the standard unsigned integer type of 64 bits.
	#define SCNX8         #error               //!< Scanning unsigned upper case hexadecimal format macro for the standard unsigned integer type of 8 bits.
	#define SCNX16        "hX"                 //!< Scanning unsigned upper case hexadecimal format macro for the standard unsigned integer type of 16 bits.
	#define SCNX32        "lX"    /* CHECK */  //!< Scanning unsigned upper case hexadecimal format macro for the standard unsigned integer type of 32 bits. \todo Investigate this.
	#define SCNX64        "I64X"               //!< Scanning unsigned upper case hexadecimal format macro for the standard unsigned integer type of 64 bits.
	#define PRIzd         "Id"                 //!< ...
	#define PRIzu         "Iu"                 //!< ...
	#define PRIzx         "Ix"                 //!< ...


#elif __BORLANDC__
#include <stdint.h>
	#define PRId8         "I8d"
	#define PRId16        "I16d"
	#define PRId32        "I32d"
	#define PRId64        "I64d"
	#define PRIu8         "I8u"
	#define PRIu16        "I16u"
	#define PRIu32        "I32u"
	#define PRIu64        "I64u"
	#define SCNd8         "I8d"
	#define SCNd16        "I16d"
	#define SCNd32        "I32d"
	#define SCNd64        "I64d"
	#define SCNu8         "I8u"
	#define SCNu16        "I16u"
	#define SCNu32        "I32u"
	#define SCNu64        "I64u"


#elif __MINGW32__
	#define PRIzd         "Id"                 //!< ...
	#define PRIzu         "Iu"                 //!< ...
	#define PRIzx         "Ix"                 //!< ...
#if(BASIC_TYPES_USE_CPP)
#include <cstdint>
#include <cinttypes>
	using std::int8_t;
	using std::int16_t;
	using std::int32_t;
	using std::int64_t;
	using std::uint8_t;
	using std::uint16_t;
	using std::uint32_t;
	using std::uint64_t;
#else
#include <stdint.h>
#include <inttypes.h>
#endif


#else
	#define PRIzd         "zd"                 //!< ...
	#define PRIzu         "zu"                 //!< ...
	#define PRIzx         "zx"                 //!< ...
#if(BASIC_TYPES_USE_CPP)
#include <cstdint>
#include <cinttypes>
	using std::int8_t;
	using std::int16_t;
	using std::int32_t;
	using std::int64_t;
	using std::uint8_t;
	using std::uint16_t;
	using std::uint32_t;
	using std::uint64_t;
#else
#include <stdint.h>
#include <inttypes.h>
#endif
#endif


#ifndef SCNX8
#define SCNX8  SCNx8
#endif
#ifndef SCNX16
#define SCNX16 SCNx16
#endif
#ifndef SCNX32
#define SCNX32 SCNx32
#endif
#ifndef SCNX64
#define SCNX64 SCNx64
#endif


typedef long double real80_t;  //!< Floating-point real of 80 bits
typedef      double real64_t;  //!< Floating-point real of 64 bits
typedef       float real32_t;  //!< Floating-point real of 32 bits


#undef BASIC_TYPES_USE_CPP


#endif

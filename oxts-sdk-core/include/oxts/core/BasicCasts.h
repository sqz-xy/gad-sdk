//============================================================================================================
//!
//! The software is protected by copyright of Oxford Technical Solutions.
//! Copyright (C) 2018 Oxford Technical Solutions - http://www.oxts.com
//!
//! Redistribution and use in source and binary forms, with or without modification, are only permitted with
//! the specific prior written permission of Oxford Technical Solutions.
//!
//! $LastChangedDate: 2018-07-02 16:57:28 +0100 (Mon, 02 Jul 2018) $
//! $LastChangedRevision: 26649 $
//! $LastChangedBy: icleju $
//!
//! \file BasicCasts.h
//!
//! \brief Header file for BasicCasts.cpp.
//!
//============================================================================================================


#ifndef LIBRARY_BASIC_CASTS_H
#define LIBRARY_BASIC_CASTS_H


#define BASIC_CASTS_DEV_ID "110928"  //!< Development Identification.


#include "oxts/core/BasicTypes.h"


//============================================================================================================
//! \name Unsigned largest representable value
//!
//! Largest representable value of an unsigned X-byte number represented by the Y-bit standard unsigned integer type.

#define OXTS_1BYTE_UINT8_MAX  ((uint8_t)   UINT8_C(0xFF))
#define OXTS_1BYTE_UINT16_MAX ((uint16_t) UINT16_C(0x00FF))
#define OXTS_2BYTE_UINT16_MAX ((uint16_t) UINT16_C(0xFFFF))
#define OXTS_1BYTE_UINT32_MAX ((uint32_t) UINT32_C(0x000000FF))
#define OXTS_2BYTE_UINT32_MAX ((uint32_t) UINT32_C(0x0000FFFF))
#define OXTS_3BYTE_UINT32_MAX ((uint32_t) UINT32_C(0x00FFFFFF))
#define OXTS_4BYTE_UINT32_MAX ((uint32_t) UINT32_C(0xFFFFFFFF))
#define OXTS_1BYTE_UINT64_MAX ((uint64_t) UINT64_C(0x00000000000000FF))
#define OXTS_2BYTE_UINT64_MAX ((uint64_t) UINT64_C(0x000000000000FFFF))
#define OXTS_3BYTE_UINT64_MAX ((uint64_t) UINT64_C(0x0000000000FFFFFF))
#define OXTS_4BYTE_UINT64_MAX ((uint64_t) UINT64_C(0x00000000FFFFFFFF))
#define OXTS_5BYTE_UINT64_MAX ((uint64_t) UINT64_C(0x000000FFFFFFFFFF))
#define OXTS_6BYTE_UINT64_MAX ((uint64_t) UINT64_C(0x0000FFFFFFFFFFFF))
#define OXTS_7BYTE_UINT64_MAX ((uint64_t) UINT64_C(0x00FFFFFFFFFFFFFF))
#define OXTS_8BYTE_UINT64_MAX ((uint64_t) UINT64_C(0xFFFFFFFFFFFFFFFF))


//============================================================================================================
//! \name Unsigned largest communication value
//!
//! Largest communication value of an unsigned X-byte number represented by the Y-bit standard unsigned integer type.

#define OXTS_1BYTE_UINT8_POS  ((uint8_t)   UINT8_C(0xFE))
#define OXTS_1BYTE_UINT16_POS ((uint16_t) UINT16_C(0x00FE))
#define OXTS_2BYTE_UINT16_POS ((uint16_t) UINT16_C(0xFFFE))
#define OXTS_1BYTE_UINT32_POS ((uint32_t) UINT32_C(0x000000FE))
#define OXTS_2BYTE_UINT32_POS ((uint32_t) UINT32_C(0x0000FFFE))
#define OXTS_3BYTE_UINT32_POS ((uint32_t) UINT32_C(0x00FFFFFE))
#define OXTS_4BYTE_UINT32_POS ((uint32_t) UINT32_C(0xFFFFFFFE))
#define OXTS_1BYTE_UINT64_POS ((uint64_t) UINT64_C(0x00000000000000FE))
#define OXTS_2BYTE_UINT64_POS ((uint64_t) UINT64_C(0x000000000000FFFE))
#define OXTS_3BYTE_UINT64_POS ((uint64_t) UINT64_C(0x0000000000FFFFFE))
#define OXTS_4BYTE_UINT64_POS ((uint64_t) UINT64_C(0x00000000FFFFFFFE))
#define OXTS_5BYTE_UINT64_POS ((uint64_t) UINT64_C(0x000000FFFFFFFFFE))
#define OXTS_6BYTE_UINT64_POS ((uint64_t) UINT64_C(0x0000FFFFFFFFFFFE))
#define OXTS_7BYTE_UINT64_POS ((uint64_t) UINT64_C(0x00FFFFFFFFFFFFFE))
#define OXTS_8BYTE_UINT64_POS ((uint64_t) UINT64_C(0xFFFFFFFFFFFFFFFE))


//============================================================================================================
//! \name Unsigned invalid communication value
//!
//! Invalid communication value of an unsigned X-byte number represented by the Y-bit standard unsigned integer type.

#define OXTS_1BYTE_UINT8_INV  OXTS_1BYTE_UINT8_MAX
#define OXTS_1BYTE_UINT16_INV OXTS_1BYTE_UINT16_MAX
#define OXTS_2BYTE_UINT16_INV OXTS_2BYTE_UINT16_MAX
#define OXTS_1BYTE_UINT32_INV OXTS_1BYTE_UINT32_MAX
#define OXTS_2BYTE_UINT32_INV OXTS_2BYTE_UINT32_MAX
#define OXTS_3BYTE_UINT32_INV OXTS_3BYTE_UINT32_MAX
#define OXTS_4BYTE_UINT32_INV OXTS_4BYTE_UINT32_MAX
#define OXTS_1BYTE_UINT64_INV OXTS_1BYTE_UINT64_MAX
#define OXTS_2BYTE_UINT64_INV OXTS_2BYTE_UINT64_MAX
#define OXTS_3BYTE_UINT64_INV OXTS_3BYTE_UINT64_MAX
#define OXTS_4BYTE_UINT64_INV OXTS_4BYTE_UINT64_MAX
#define OXTS_5BYTE_UINT64_INV OXTS_5BYTE_UINT64_MAX
#define OXTS_6BYTE_UINT64_INV OXTS_6BYTE_UINT64_MAX
#define OXTS_7BYTE_UINT64_INV OXTS_7BYTE_UINT64_MAX
#define OXTS_8BYTE_UINT64_INV OXTS_8BYTE_UINT64_MAX


//============================================================================================================
//! \name Signed smallest representable value
//!
//! Smallest representable value of a signed X-byte number represented by the Y-bit standard signed integer type.

#define OXTS_1BYTE_INT8_MIN    ((int8_t)   UINT8_C(0x80))
#define OXTS_1BYTE_INT16_MIN   ((int16_t) UINT16_C(0xFF80))
#define OXTS_2BYTE_INT16_MIN   ((int16_t) UINT16_C(0x8000))
#define OXTS_1BYTE_INT32_MIN   ((int32_t) UINT32_C(0xFFFFFF80))
#define OXTS_2BYTE_INT32_MIN   ((int32_t) UINT32_C(0xFFFF8000))
#define OXTS_3BYTE_INT32_MIN   ((int32_t) UINT32_C(0xFF800000))
#define OXTS_4BYTE_INT32_MIN   ((int32_t) UINT32_C(0x80000000))
#define OXTS_1BYTE_INT64_MIN   ((int64_t) UINT64_C(0xFFFFFFFFFFFFFF80))
#define OXTS_2BYTE_INT64_MIN   ((int64_t) UINT64_C(0xFFFFFFFFFFFF8000))
#define OXTS_3BYTE_INT64_MIN   ((int64_t) UINT64_C(0xFFFFFFFFFF800000))
#define OXTS_4BYTE_INT64_MIN   ((int64_t) UINT64_C(0xFFFFFFFF80000000))
#define OXTS_5BYTE_INT64_MIN   ((int64_t) UINT64_C(0xFFFFFF8000000000))
#define OXTS_6BYTE_INT64_MIN   ((int64_t) UINT64_C(0xFFFF800000000000))
#define OXTS_7BYTE_INT64_MIN   ((int64_t) UINT64_C(0xFF80000000000000))
#define OXTS_8BYTE_INT64_MIN   ((int64_t) UINT64_C(0x8000000000000000))


//============================================================================================================
//! \name Signed largest representable value
//!
//! Largest representable value of a signed X-byte number represented by the Y-bit standard signed integer type.

#define OXTS_1BYTE_INT8_MAX    ((int8_t)   UINT8_C(0x7F))
#define OXTS_1BYTE_INT16_MAX   ((int16_t) UINT16_C(0x007F))
#define OXTS_2BYTE_INT16_MAX   ((int16_t) UINT16_C(0x7FFF))
#define OXTS_1BYTE_INT32_MAX   ((int32_t) UINT32_C(0x0000007F))
#define OXTS_2BYTE_INT32_MAX   ((int32_t) UINT32_C(0x00007FFF))
#define OXTS_3BYTE_INT32_MAX   ((int32_t) UINT32_C(0x007FFFFF))
#define OXTS_4BYTE_INT32_MAX   ((int32_t) UINT32_C(0x7FFFFFFF))
#define OXTS_1BYTE_INT64_MAX   ((int64_t) UINT64_C(0x000000000000007F))
#define OXTS_2BYTE_INT64_MAX   ((int64_t) UINT64_C(0x0000000000007FFF))
#define OXTS_3BYTE_INT64_MAX   ((int64_t) UINT64_C(0x00000000007FFFFF))
#define OXTS_4BYTE_INT64_MAX   ((int64_t) UINT64_C(0x000000007FFFFFFF))
#define OXTS_5BYTE_INT64_MAX   ((int64_t) UINT64_C(0x0000007FFFFFFFFF))
#define OXTS_6BYTE_INT64_MAX   ((int64_t) UINT64_C(0x00007FFFFFFFFFFF))
#define OXTS_7BYTE_INT64_MAX   ((int64_t) UINT64_C(0x007FFFFFFFFFFFFF))
#define OXTS_8BYTE_INT64_MAX   ((int64_t) UINT64_C(0x7FFFFFFFFFFFFFFF))


//============================================================================================================
//! \name Signed smallest communication value
//!
//! Smallest communication value of a signed X-byte number represented by the Y-bit standard signed integer type.

#define OXTS_1BYTE_INT8_NEG    ((int8_t)   UINT8_C(0x81))
#define OXTS_1BYTE_INT16_NEG   ((int16_t) UINT16_C(0xFF81))
#define OXTS_2BYTE_INT16_NEG   ((int16_t) UINT16_C(0x8001))
#define OXTS_1BYTE_INT32_NEG   ((int32_t) UINT32_C(0xFFFFFF81))
#define OXTS_2BYTE_INT32_NEG   ((int32_t) UINT32_C(0xFFFF8001))
#define OXTS_3BYTE_INT32_NEG   ((int32_t) UINT32_C(0xFF800001))
#define OXTS_4BYTE_INT32_NEG   ((int32_t) UINT32_C(0x80000001))
#define OXTS_1BYTE_INT64_NEG   ((int64_t) UINT64_C(0xFFFFFFFFFFFFFF81))
#define OXTS_2BYTE_INT64_NEG   ((int64_t) UINT64_C(0xFFFFFFFFFFFF8001))
#define OXTS_3BYTE_INT64_NEG   ((int64_t) UINT64_C(0xFFFFFFFFFF800001))
#define OXTS_4BYTE_INT64_NEG   ((int64_t) UINT64_C(0xFFFFFFFF80000001))
#define OXTS_5BYTE_INT64_NEG   ((int64_t) UINT64_C(0xFFFFFF8000000001))
#define OXTS_6BYTE_INT64_NEG   ((int64_t) UINT64_C(0xFFFF800000000001))
#define OXTS_7BYTE_INT64_NEG   ((int64_t) UINT64_C(0xFF80000000000001))
#define OXTS_8BYTE_INT64_NEG   ((int64_t) UINT64_C(0x8000000000000001))


//============================================================================================================
//! \name Signed largest communication value
//!
//! Largest communication value of a signed X-byte number represented by the Y-bit standard signed integer type.

#define OXTS_1BYTE_INT8_POS     OXTS_1BYTE_INT8_MAX
#define OXTS_1BYTE_INT16_POS    OXTS_1BYTE_INT16_MAX
#define OXTS_2BYTE_INT16_POS    OXTS_2BYTE_INT16_MAX
#define OXTS_1BYTE_INT32_POS    OXTS_1BYTE_INT32_MAX
#define OXTS_2BYTE_INT32_POS    OXTS_2BYTE_INT32_MAX
#define OXTS_3BYTE_INT32_POS    OXTS_3BYTE_INT32_MAX
#define OXTS_4BYTE_INT32_POS    OXTS_4BYTE_INT32_MAX
#define OXTS_1BYTE_INT64_POS    OXTS_1BYTE_INT64_MAX
#define OXTS_2BYTE_INT64_POS    OXTS_2BYTE_INT64_MAX
#define OXTS_3BYTE_INT64_POS    OXTS_3BYTE_INT64_MAX
#define OXTS_4BYTE_INT64_POS    OXTS_4BYTE_INT64_MAX
#define OXTS_5BYTE_INT64_POS    OXTS_5BYTE_INT64_MAX
#define OXTS_6BYTE_INT64_POS    OXTS_6BYTE_INT64_MAX
#define OXTS_7BYTE_INT64_POS    OXTS_7BYTE_INT64_MAX
#define OXTS_8BYTE_INT64_POS    OXTS_8BYTE_INT64_MAX


//============================================================================================================
//! \name Signed invalid communication value
//!
//! Invalid communication value of a signed X-byte number represented by the Y-bit standard signed integer type.

#define OXTS_1BYTE_INT8_INV     OXTS_1BYTE_INT8_MIN
#define OXTS_1BYTE_INT16_INV    OXTS_1BYTE_INT16_MIN
#define OXTS_2BYTE_INT16_INV    OXTS_2BYTE_INT16_MIN
#define OXTS_1BYTE_INT32_INV    OXTS_1BYTE_INT32_MIN
#define OXTS_2BYTE_INT32_INV    OXTS_2BYTE_INT32_MIN
#define OXTS_3BYTE_INT32_INV    OXTS_3BYTE_INT32_MIN
#define OXTS_4BYTE_INT32_INV    OXTS_4BYTE_INT32_MIN
#define OXTS_1BYTE_INT64_INV    OXTS_1BYTE_INT64_MIN
#define OXTS_2BYTE_INT64_INV    OXTS_2BYTE_INT64_MIN
#define OXTS_3BYTE_INT64_INV    OXTS_3BYTE_INT64_MIN
#define OXTS_4BYTE_INT64_INV    OXTS_4BYTE_INT64_MIN
#define OXTS_5BYTE_INT64_INV    OXTS_5BYTE_INT64_MIN
#define OXTS_6BYTE_INT64_INV    OXTS_6BYTE_INT64_MIN
#define OXTS_7BYTE_INT64_INV    OXTS_7BYTE_INT64_MIN
#define OXTS_8BYTE_INT64_INV    OXTS_8BYTE_INT64_MIN


//============================================================================================================
//! \name ...

#define OXTS_ufix8_INV     OXTS_1BYTE_UINT8_INV
#define OXTS_ufix16_INV    OXTS_2BYTE_UINT16_INV
#define OXTS_ufix24_INV    OXTS_3BYTE_UINT32_INV
#define OXTS_ufix32_INV    OXTS_4BYTE_UINT32_INV
#define OXTS_ufix40_INV    OXTS_5BYTE_UINT64_INV
#define OXTS_ufix48_INV    OXTS_6BYTE_UINT64_INV
#define OXTS_ufix56_INV    OXTS_7BYTE_UINT64_INV
#define OXTS_ufix64_INV    OXTS_8BYTE_UINT64_INV

#define OXTS_ufix8_POS     OXTS_1BYTE_UINT8_POS
#define OXTS_ufix16_POS    OXTS_2BYTE_UINT16_POS
#define OXTS_ufix24_POS    OXTS_3BYTE_UINT32_POS
#define OXTS_ufix32_POS    OXTS_4BYTE_UINT32_POS
#define OXTS_ufix40_POS    OXTS_5BYTE_UINT64_POS
#define OXTS_ufix48_POS    OXTS_6BYTE_UINT64_POS
#define OXTS_ufix56_POS    OXTS_7BYTE_UINT64_POS
#define OXTS_ufix64_POS    OXTS_8BYTE_UINT64_POS

#define OXTS_fix8_INV      OXTS_1BYTE_INT8_INV
#define OXTS_fix16_INV     OXTS_2BYTE_INT16_INV
#define OXTS_fix24_INV     OXTS_3BYTE_INT32_INV
#define OXTS_fix32_INV     OXTS_4BYTE_INT32_INV
#define OXTS_fix40_INV     OXTS_5BYTE_INT64_INV
#define OXTS_fix48_INV     OXTS_6BYTE_INT64_INV
#define OXTS_fix56_INV     OXTS_7BYTE_INT64_INV
#define OXTS_fix64_INV     OXTS_8BYTE_INT64_INV

#define OXTS_fix8_POS      OXTS_1BYTE_INT8_POS
#define OXTS_fix16_POS     OXTS_2BYTE_INT16_POS
#define OXTS_fix24_POS     OXTS_3BYTE_INT32_POS
#define OXTS_fix32_POS     OXTS_4BYTE_INT32_POS
#define OXTS_fix40_POS     OXTS_5BYTE_INT64_POS
#define OXTS_fix48_POS     OXTS_6BYTE_INT64_POS
#define OXTS_fix56_POS     OXTS_7BYTE_INT64_POS
#define OXTS_fix64_POS     OXTS_8BYTE_INT64_POS

#define OXTS_fix8_NEG      OXTS_1BYTE_INT8_NEG
#define OXTS_fix16_NEG     OXTS_2BYTE_INT16_NEG
#define OXTS_fix24_NEG     OXTS_3BYTE_INT32_NEG
#define OXTS_fix32_NEG     OXTS_4BYTE_INT32_NEG
#define OXTS_fix40_NEG     OXTS_5BYTE_INT64_NEG
#define OXTS_fix48_NEG     OXTS_6BYTE_INT64_NEG
#define OXTS_fix56_NEG     OXTS_7BYTE_INT64_NEG
#define OXTS_fix64_NEG     OXTS_8BYTE_INT64_NEG


#ifdef __cplusplus
extern "C"
{
#endif


//============================================================================================================
//! \name Little endian bytes to real
//!
//! Convert a little endian X-byte representation of a real to a basic Y-bit real type.

real32_t cast_4_byte_LE_to_real32(const uint8_t *b);
real64_t cast_8_byte_LE_to_real64(const uint8_t *b);


//============================================================================================================
//! \name Big endian bytes to real
//!
//! Convert a little endian X-byte representation of a real to a basic Y-bit real type.

real32_t cast_4_byte_BE_to_real32(const uint8_t *b);
real64_t cast_8_byte_BE_to_real64(const uint8_t *b);


//============================================================================================================
//! \name Real to little endian bytes
//!
//! Convert a little endian X-byte representation of a real to a basic Y-bit real type.

void cast_real32_to_4_byte_LE(uint8_t *b, real32_t v);
void cast_real64_to_8_byte_LE(uint8_t *b, real64_t v);


//============================================================================================================
//! \name Real to big endian bytes
//!
//! Convert a little endian X-byte representation of a real to a basic Y-bit real type.

void cast_real32_to_4_byte_BE(uint8_t *b, real32_t v);
void cast_real64_to_8_byte_BE(uint8_t *b, real64_t v);


//============================================================================================================
//! \name Signed little endian bytes to integer
//!
//! Convert a little endian X-byte representation of a signed integer to a basic signed Y-bit integer type.

int8_t  cast_1_byte_LE_to_int8 (const uint8_t *b);
int16_t cast_1_byte_LE_to_int16(const uint8_t *b);
int16_t cast_2_byte_LE_to_int16(const uint8_t *b);
int32_t cast_1_byte_LE_to_int32(const uint8_t *b);
int32_t cast_2_byte_LE_to_int32(const uint8_t *b);
int32_t cast_3_byte_LE_to_int32(const uint8_t *b);
int32_t cast_4_byte_LE_to_int32(const uint8_t *b);
int64_t cast_1_byte_LE_to_int64(const uint8_t *b);
int64_t cast_2_byte_LE_to_int64(const uint8_t *b);
int64_t cast_3_byte_LE_to_int64(const uint8_t *b);
int64_t cast_4_byte_LE_to_int64(const uint8_t *b);
int64_t cast_5_byte_LE_to_int64(const uint8_t *b);
int64_t cast_6_byte_LE_to_int64(const uint8_t *b);
int64_t cast_7_byte_LE_to_int64(const uint8_t *b);
int64_t cast_8_byte_LE_to_int64(const uint8_t *b);


//============================================================================================================
//! \name Signed big endian bytes to integer
//!
//! Convert a big endian X-byte representation of a signed integer to a basic signed Y-bit integer type.

int8_t  cast_1_byte_BE_to_int8 (const uint8_t *b);
int16_t cast_1_byte_BE_to_int16(const uint8_t *b);
int16_t cast_2_byte_BE_to_int16(const uint8_t *b);
int32_t cast_1_byte_BE_to_int32(const uint8_t *b);
int32_t cast_2_byte_BE_to_int32(const uint8_t *b);
int32_t cast_3_byte_BE_to_int32(const uint8_t *b);
int32_t cast_4_byte_BE_to_int32(const uint8_t *b);
int64_t cast_1_byte_BE_to_int64(const uint8_t *b);
int64_t cast_2_byte_BE_to_int64(const uint8_t *b);
int64_t cast_3_byte_BE_to_int64(const uint8_t *b);
int64_t cast_4_byte_BE_to_int64(const uint8_t *b);
int64_t cast_5_byte_BE_to_int64(const uint8_t *b);
int64_t cast_6_byte_BE_to_int64(const uint8_t *b);
int64_t cast_7_byte_BE_to_int64(const uint8_t *b);
int64_t cast_8_byte_BE_to_int64(const uint8_t *b);


//============================================================================================================
//! \name Unsigned little endian bytes to integer
//!
//! Convert a little endian X-byte representation of an unsigned integer to a basic unsigned Y-bit integer type.

uint8_t  cast_1_byte_LE_to_uint8 (const uint8_t *b);
uint16_t cast_1_byte_LE_to_uint16(const uint8_t *b);
uint16_t cast_2_byte_LE_to_uint16(const uint8_t *b);
uint32_t cast_1_byte_LE_to_uint32(const uint8_t *b);
uint32_t cast_2_byte_LE_to_uint32(const uint8_t *b);
uint32_t cast_3_byte_LE_to_uint32(const uint8_t *b);
uint32_t cast_4_byte_LE_to_uint32(const uint8_t *b);
uint64_t cast_1_byte_LE_to_uint64(const uint8_t *b);
uint64_t cast_2_byte_LE_to_uint64(const uint8_t *b);
uint64_t cast_3_byte_LE_to_uint64(const uint8_t *b);
uint64_t cast_4_byte_LE_to_uint64(const uint8_t *b);
uint64_t cast_5_byte_LE_to_uint64(const uint8_t *b);
uint64_t cast_6_byte_LE_to_uint64(const uint8_t *b);
uint64_t cast_7_byte_LE_to_uint64(const uint8_t *b);
uint64_t cast_8_byte_LE_to_uint64(const uint8_t *b);


//============================================================================================================
//! \name Unsigned big endian bytes to integer
//!
//! Convert a big endian X-byte representation of an unsigned integer to a basic unsigned Y-bit integer type.

uint8_t  cast_1_byte_BE_to_uint8 (const uint8_t *b);
uint16_t cast_1_byte_BE_to_uint16(const uint8_t *b);
uint16_t cast_2_byte_BE_to_uint16(const uint8_t *b);
uint32_t cast_1_byte_BE_to_uint32(const uint8_t *b);
uint32_t cast_2_byte_BE_to_uint32(const uint8_t *b);
uint32_t cast_3_byte_BE_to_uint32(const uint8_t *b);
uint32_t cast_4_byte_BE_to_uint32(const uint8_t *b);
uint64_t cast_1_byte_BE_to_uint64(const uint8_t *b);
uint64_t cast_2_byte_BE_to_uint64(const uint8_t *b);
uint64_t cast_3_byte_BE_to_uint64(const uint8_t *b);
uint64_t cast_4_byte_BE_to_uint64(const uint8_t *b);
uint64_t cast_5_byte_BE_to_uint64(const uint8_t *b);
uint64_t cast_6_byte_BE_to_uint64(const uint8_t *b);
uint64_t cast_7_byte_BE_to_uint64(const uint8_t *b);
uint64_t cast_8_byte_BE_to_uint64(const uint8_t *b);


//============================================================================================================
//! \name Signed integer to little endian bytes
//!
//! Convert a basic signed Y-bit integer type to a little endian X-byte representation of a signed integer.

void   cast_int8_to_1_byte_LE(uint8_t *b,   int8_t v);
void  cast_int16_to_1_byte_LE(uint8_t *b,  int16_t v);
void  cast_int16_to_2_byte_LE(uint8_t *b,  int16_t v);
void  cast_int32_to_1_byte_LE(uint8_t *b,  int32_t v);
void  cast_int32_to_2_byte_LE(uint8_t *b,  int32_t v);
void  cast_int32_to_3_byte_LE(uint8_t *b,  int32_t v);
void  cast_int32_to_4_byte_LE(uint8_t *b,  int32_t v);
void  cast_int64_to_1_byte_LE(uint8_t *b,  int64_t v);
void  cast_int64_to_2_byte_LE(uint8_t *b,  int64_t v);
void  cast_int64_to_3_byte_LE(uint8_t *b,  int64_t v);
void  cast_int64_to_4_byte_LE(uint8_t *b,  int64_t v);
void  cast_int64_to_5_byte_LE(uint8_t *b,  int64_t v);
void  cast_int64_to_6_byte_LE(uint8_t *b,  int64_t v);
void  cast_int64_to_7_byte_LE(uint8_t *b,  int64_t v);
void  cast_int64_to_8_byte_LE(uint8_t *b,  int64_t v);


//============================================================================================================
//! \name Signed integer to big endian bytes
//!
//! Convert a basic signed Y-bit integer type to a big endian X-byte representation of a signed integer.

void   cast_int8_to_1_byte_BE(uint8_t *b,   int8_t v);
void  cast_int16_to_1_byte_BE(uint8_t *b,  int16_t v);
void  cast_int16_to_2_byte_BE(uint8_t *b,  int16_t v);
void  cast_int32_to_1_byte_BE(uint8_t *b,  int32_t v);
void  cast_int32_to_2_byte_BE(uint8_t *b,  int32_t v);
void  cast_int32_to_3_byte_BE(uint8_t *b,  int32_t v);
void  cast_int32_to_4_byte_BE(uint8_t *b,  int32_t v);
void  cast_int64_to_1_byte_BE(uint8_t *b,  int64_t v);
void  cast_int64_to_2_byte_BE(uint8_t *b,  int64_t v);
void  cast_int64_to_3_byte_BE(uint8_t *b,  int64_t v);
void  cast_int64_to_4_byte_BE(uint8_t *b,  int64_t v);
void  cast_int64_to_5_byte_BE(uint8_t *b,  int64_t v);
void  cast_int64_to_6_byte_BE(uint8_t *b,  int64_t v);
void  cast_int64_to_7_byte_BE(uint8_t *b,  int64_t v);
void  cast_int64_to_8_byte_BE(uint8_t *b,  int64_t v);


//============================================================================================================
//! \name Unsigned integer to little endian bytes
//!
//! Convert a basic unsigned Y-bit integer type to a little endian X-byte representation of an unsigned integer.

void  cast_uint8_to_1_byte_LE(uint8_t *b,  uint8_t v);
void cast_uint16_to_1_byte_LE(uint8_t *b, uint16_t v);
void cast_uint16_to_2_byte_LE(uint8_t *b, uint16_t v);
void cast_uint32_to_1_byte_LE(uint8_t *b, uint32_t v);
void cast_uint32_to_2_byte_LE(uint8_t *b, uint32_t v);
void cast_uint32_to_3_byte_LE(uint8_t *b, uint32_t v);
void cast_uint32_to_4_byte_LE(uint8_t *b, uint32_t v);
void cast_uint64_to_1_byte_LE(uint8_t *b, uint64_t v);
void cast_uint64_to_2_byte_LE(uint8_t *b, uint64_t v);
void cast_uint64_to_3_byte_LE(uint8_t *b, uint64_t v);
void cast_uint64_to_4_byte_LE(uint8_t *b, uint64_t v);
void cast_uint64_to_5_byte_LE(uint8_t *b, uint64_t v);
void cast_uint64_to_6_byte_LE(uint8_t *b, uint64_t v);
void cast_uint64_to_7_byte_LE(uint8_t *b, uint64_t v);
void cast_uint64_to_8_byte_LE(uint8_t *b, uint64_t v);


//============================================================================================================
//! \name Unsigned integer to big endian bytes
//!
//! Convert a basic unsigned Y-bit integer type to a big endian X-byte representation of an unsigned integer.

void  cast_uint8_to_1_byte_BE(uint8_t *b,  uint8_t v);
void cast_uint16_to_1_byte_BE(uint8_t *b, uint16_t v);
void cast_uint16_to_2_byte_BE(uint8_t *b, uint16_t v);
void cast_uint32_to_1_byte_BE(uint8_t *b, uint32_t v);
void cast_uint32_to_2_byte_BE(uint8_t *b, uint32_t v);
void cast_uint32_to_3_byte_BE(uint8_t *b, uint32_t v);
void cast_uint32_to_4_byte_BE(uint8_t *b, uint32_t v);
void cast_uint64_to_1_byte_BE(uint8_t *b, uint64_t v);
void cast_uint64_to_2_byte_BE(uint8_t *b, uint64_t v);
void cast_uint64_to_3_byte_BE(uint8_t *b, uint64_t v);
void cast_uint64_to_4_byte_BE(uint8_t *b, uint64_t v);
void cast_uint64_to_5_byte_BE(uint8_t *b, uint64_t v);
void cast_uint64_to_6_byte_BE(uint8_t *b, uint64_t v);
void cast_uint64_to_7_byte_BE(uint8_t *b, uint64_t v);
void cast_uint64_to_8_byte_BE(uint8_t *b, uint64_t v);


//============================================================================================================
//! \name Signed integer to OxTS signed integer.

int8_t  cast_int8_to_fix8   (int8_t  x);
int8_t  cast_int16_to_fix8  (int16_t x);
int8_t  cast_int32_to_fix8  (int32_t x);
int8_t  cast_int64_to_fix8  (int64_t x);
int16_t cast_int8_to_fix16  (int8_t  x);
int16_t cast_int16_to_fix16 (int16_t x);
int16_t cast_int32_to_fix16 (int32_t x);
int16_t cast_int64_to_fix16 (int64_t x);
int32_t cast_int8_to_fix24  (int8_t  x);
int32_t cast_int16_to_fix24 (int16_t x);
int32_t cast_int32_to_fix24 (int32_t x);
int32_t cast_int64_to_fix24 (int64_t x);
int32_t cast_int8_to_fix32  (int8_t  x);
int32_t cast_int16_to_fix32 (int16_t x);
int32_t cast_int32_to_fix32 (int32_t x);
int32_t cast_int64_to_fix32 (int64_t x);
int64_t cast_int8_to_fix40  (int8_t  x);
int64_t cast_int16_to_fix40 (int16_t x);
int64_t cast_int32_to_fix40 (int32_t x);
int64_t cast_int64_to_fix40 (int64_t x);
int64_t cast_int8_to_fix48  (int8_t  x);
int64_t cast_int16_to_fix48 (int16_t x);
int64_t cast_int32_to_fix48 (int32_t x);
int64_t cast_int64_to_fix48 (int64_t x);
int64_t cast_int8_to_fix56  (int8_t  x);
int64_t cast_int16_to_fix56 (int16_t x);
int64_t cast_int32_to_fix56 (int32_t x);
int64_t cast_int64_to_fix56 (int64_t x);
int64_t cast_int8_to_fix64  (int8_t  x);
int64_t cast_int16_to_fix64 (int16_t x);
int64_t cast_int32_to_fix64 (int32_t x);
int64_t cast_int64_to_fix64 (int64_t x);


//============================================================================================================
//! \name Unsigned integer to OxTS signed integer.

int8_t  cast_uint8_to_fix8   (uint8_t  x);
int8_t  cast_uint16_to_fix8  (uint16_t x);
int8_t  cast_uint32_to_fix8  (uint32_t x);
int8_t  cast_uint64_to_fix8  (uint64_t x);
int16_t cast_uint8_to_fix16  (uint8_t  x);
int16_t cast_uint16_to_fix16 (uint16_t x);
int16_t cast_uint32_to_fix16 (uint32_t x);
int16_t cast_uint64_to_fix16 (uint64_t x);
int32_t cast_uint8_to_fix24  (uint8_t  x);
int32_t cast_uint16_to_fix24 (uint16_t x);
int32_t cast_uint32_to_fix24 (uint32_t x);
int32_t cast_uint64_to_fix24 (uint64_t x);
int32_t cast_uint8_to_fix32  (uint8_t  x);
int32_t cast_uint16_to_fix32 (uint16_t x);
int32_t cast_uint32_to_fix32 (uint32_t x);
int32_t cast_uint64_to_fix32 (uint64_t x);
int64_t cast_uint8_to_fix40  (uint8_t  x);
int64_t cast_uint16_to_fix40 (uint16_t x);
int64_t cast_uint32_to_fix40 (uint32_t x);
int64_t cast_uint64_to_fix40 (uint64_t x);
int64_t cast_uint8_to_fix48  (uint8_t  x);
int64_t cast_uint16_to_fix48 (uint16_t x);
int64_t cast_uint32_to_fix48 (uint32_t x);
int64_t cast_uint64_to_fix48 (uint64_t x);
int64_t cast_uint8_to_fix56  (uint8_t  x);
int64_t cast_uint16_to_fix56 (uint16_t x);
int64_t cast_uint32_to_fix56 (uint32_t x);
int64_t cast_uint64_to_fix56 (uint64_t x);
int64_t cast_uint8_to_fix64  (uint8_t  x);
int64_t cast_uint16_to_fix64 (uint16_t x);
int64_t cast_uint32_to_fix64 (uint32_t x);
int64_t cast_uint64_to_fix64 (uint64_t x);


//============================================================================================================
//! \name Signed integer to OxTS unsigned integer.

uint8_t  cast_int8_to_ufix8  (int8_t  x);
uint8_t  cast_int16_to_ufix8 (int16_t x);
uint8_t  cast_int32_to_ufix8 (int32_t x);
uint8_t  cast_int64_to_ufix8 (int64_t x);
uint16_t cast_int8_to_ufix16 (int8_t  x);
uint16_t cast_int16_to_ufix16(int16_t x);
uint16_t cast_int32_to_ufix16(int32_t x);
uint16_t cast_int64_to_ufix16(int64_t x);
uint32_t cast_int8_to_ufix24 (int8_t  x);
uint32_t cast_int16_to_ufix24(int16_t x);
uint32_t cast_int32_to_ufix24(int32_t x);
uint32_t cast_int64_to_ufix24(int64_t x);
uint32_t cast_int8_to_ufix32 (int8_t  x);
uint32_t cast_int16_to_ufix32(int16_t x);
uint32_t cast_int32_to_ufix32(int32_t x);
uint32_t cast_int64_to_ufix32(int64_t x);
uint64_t cast_int8_to_ufix40 (int8_t  x);
uint64_t cast_int16_to_ufix40(int16_t x);
uint64_t cast_int32_to_ufix40(int32_t x);
uint64_t cast_int64_to_ufix40(int64_t x);
uint64_t cast_int8_to_ufix48 (int8_t  x);
uint64_t cast_int16_to_ufix48(int16_t x);
uint64_t cast_int32_to_ufix48(int32_t x);
uint64_t cast_int64_to_ufix48(int64_t x);
uint64_t cast_int8_to_ufix56 (int8_t  x);
uint64_t cast_int16_to_ufix56(int16_t x);
uint64_t cast_int32_to_ufix56(int32_t x);
uint64_t cast_int64_to_ufix56(int64_t x);
uint64_t cast_int8_to_ufix64 (int8_t  x);
uint64_t cast_int16_to_ufix64(int16_t x);
uint64_t cast_int32_to_ufix64(int32_t x);
uint64_t cast_int64_to_ufix64(int64_t x);


//============================================================================================================
//! \name Unsigned integer to OxTS Unsigned integer.

uint8_t  cast_uint8_to_ufix8  (uint8_t  x);
uint8_t  cast_uint16_to_ufix8 (uint16_t x);
uint8_t  cast_uint32_to_ufix8 (uint32_t x);
uint8_t  cast_uint64_to_ufix8 (uint64_t x);
uint16_t cast_uint8_to_ufix16 (uint8_t  x);
uint16_t cast_uint16_to_ufix16(uint16_t x);
uint16_t cast_uint32_to_ufix16(uint32_t x);
uint16_t cast_uint64_to_ufix16(uint64_t x);
uint32_t cast_uint8_to_ufix24 (uint8_t  x);
uint32_t cast_uint16_to_ufix24(uint16_t x);
uint32_t cast_uint32_to_ufix24(uint32_t x);
uint32_t cast_uint64_to_ufix24(uint64_t x);
uint32_t cast_uint8_to_ufix32 (uint8_t  x);
uint32_t cast_uint16_to_ufix32(uint16_t x);
uint32_t cast_uint32_to_ufix32(uint32_t x);
uint32_t cast_uint64_to_ufix32(uint64_t x);
uint64_t cast_uint8_to_ufix40 (uint8_t  x);
uint64_t cast_uint16_to_ufix40(uint16_t x);
uint64_t cast_uint32_to_ufix40(uint32_t x);
uint64_t cast_uint64_to_ufix40(uint64_t x);
uint64_t cast_uint8_to_ufix48 (uint8_t  x);
uint64_t cast_uint16_to_ufix48(uint16_t x);
uint64_t cast_uint32_to_ufix48(uint32_t x);
uint64_t cast_uint64_to_ufix48(uint64_t x);
uint64_t cast_uint8_to_ufix56 (uint8_t  x);
uint64_t cast_uint16_to_ufix56(uint16_t x);
uint64_t cast_uint32_to_ufix56(uint32_t x);
uint64_t cast_uint64_to_ufix56(uint64_t x);
uint64_t cast_uint8_to_ufix64 (uint8_t  x);
uint64_t cast_uint16_to_ufix64(uint16_t x);
uint64_t cast_uint32_to_ufix64(uint32_t x);
uint64_t cast_uint64_to_ufix64(uint64_t x);


//============================================================================================================
//! \name Signed real to OxTS integer.

int8_t  cast_real64_to_fix8 (double x);
int16_t cast_real64_to_fix16(double x);
int32_t cast_real64_to_fix24(double x);
int32_t cast_real64_to_fix32(double x);
int64_t cast_real64_to_fix40(double x);
int64_t cast_real64_to_fix48(double x);
int64_t cast_real64_to_fix56(double x);
int64_t cast_real64_to_fix64(double x);


//============================================================================================================
//! \name Unsigned real to OxTS integer.

uint8_t  cast_real64_to_ufix8 (double x);
uint16_t cast_real64_to_ufix16(double x);
uint32_t cast_real64_to_ufix24(double x);
uint32_t cast_real64_to_ufix32(double x);
uint64_t cast_real64_to_ufix40(double x);
uint64_t cast_real64_to_ufix48(double x);
uint64_t cast_real64_to_ufix56(double x);
uint64_t cast_real64_to_ufix64(double x);


//============================================================================================================
//! \name Signed real to integer to little endian bytes

void cast_real64_to_fixed_to_1_byte_LE(uint8_t *b, double v);
void cast_real64_to_fixed_to_2_byte_LE(uint8_t *b, double v);
void cast_real64_to_fixed_to_3_byte_LE(uint8_t *b, double v);
void cast_real64_to_fixed_to_4_byte_LE(uint8_t *b, double v);
void cast_real64_to_fixed_to_5_byte_LE(uint8_t *b, double v);
void cast_real64_to_fixed_to_6_byte_LE(uint8_t *b, double v);
void cast_real64_to_fixed_to_7_byte_LE(uint8_t *b, double v);
void cast_real64_to_fixed_to_8_byte_LE(uint8_t *b, double v);


//============================================================================================================
//! \name Signed real to integer to big endian bytes

void cast_real64_to_fixed_to_1_byte_BE(uint8_t *b, double v);
void cast_real64_to_fixed_to_2_byte_BE(uint8_t *b, double v);
void cast_real64_to_fixed_to_3_byte_BE(uint8_t *b, double v);
void cast_real64_to_fixed_to_4_byte_BE(uint8_t *b, double v);
void cast_real64_to_fixed_to_5_byte_BE(uint8_t *b, double v);
void cast_real64_to_fixed_to_6_byte_BE(uint8_t *b, double v);
void cast_real64_to_fixed_to_7_byte_BE(uint8_t *b, double v);
void cast_real64_to_fixed_to_8_byte_BE(uint8_t *b, double v);


//============================================================================================================
//! \name Unsigned real to integer to little endian bytes

void cast_real64_to_ufixed_to_1_byte_LE(uint8_t *b, double v);
void cast_real64_to_ufixed_to_2_byte_LE(uint8_t *b, double v);
void cast_real64_to_ufixed_to_3_byte_LE(uint8_t *b, double v);
void cast_real64_to_ufixed_to_4_byte_LE(uint8_t *b, double v);
void cast_real64_to_ufixed_to_5_byte_LE(uint8_t *b, double v);
void cast_real64_to_ufixed_to_6_byte_LE(uint8_t *b, double v);
void cast_real64_to_ufixed_to_7_byte_LE(uint8_t *b, double v);
void cast_real64_to_ufixed_to_8_byte_LE(uint8_t *b, double v);


//============================================================================================================
//! \name Unsigned real to integer to big endian bytes

void cast_real64_to_ufixed_to_1_byte_BE(uint8_t *b, double v);
void cast_real64_to_ufixed_to_2_byte_BE(uint8_t *b, double v);
void cast_real64_to_ufixed_to_3_byte_BE(uint8_t *b, double v);
void cast_real64_to_ufixed_to_4_byte_BE(uint8_t *b, double v);
void cast_real64_to_ufixed_to_5_byte_BE(uint8_t *b, double v);
void cast_real64_to_ufixed_to_6_byte_BE(uint8_t *b, double v);
void cast_real64_to_ufixed_to_7_byte_BE(uint8_t *b, double v);
void cast_real64_to_ufixed_to_8_byte_BE(uint8_t *b, double v);


//============================================================================================================
//! \name Unsigned from bytes incrementors
//!
//! Converts.

uint32_t incr_1_byte_LE_to_uint32(const uint8_t *b, uint32_t z);
uint32_t incr_2_byte_LE_to_uint32(const uint8_t *b, uint32_t z);
uint64_t incr_2_byte_LE_to_uint64(const uint8_t *b, uint64_t z);


//============================================================================================================
//! \name Swap byte order.

uint16_t swap_uint16_byte_order(uint16_t v);
uint32_t swap_uint32_byte_order(uint32_t v);
uint64_t swap_uint64_byte_order(uint64_t v);


//============================================================================================================
//! \name Cast to network byte order.

uint16_t cast_uint16_to_network_byte_order(uint16_t v);
uint32_t cast_uint32_to_network_byte_order(uint32_t v);
uint64_t cast_uint64_to_network_byte_order(uint64_t v);


#ifdef __cplusplus
}
#endif


#endif

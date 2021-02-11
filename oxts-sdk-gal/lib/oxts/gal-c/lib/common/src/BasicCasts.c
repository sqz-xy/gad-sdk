//============================================================================================================
//!
//! The software is protected by copyright of Oxford Technical Solutions.
//! Copyright (C) 2018 Oxford Technical Solutions - http://www.oxts.com
//!
//! Redistribution and use in source and binary forms, with or without modification, are only permitted with
//! the specific prior written permission of Oxford Technical Solutions.
//!
//! $LastChangedDate: 2018-11-30 15:31:49 +0000 (Fri, 30 Nov 2018) $
//! $LastChangedRevision: 27365 $
//! $LastChangedBy: kpalamartchouk $
//!
//! \file BasicCasts.c
//!
//! \brief Casting functions from byte arrays to standard integer and well defined real types.
//!
//! - There may be better ways to implement these functions.
//! - Unique function name for each to make this very explicit and also hopefully aid code inlining.
//! - Use byte copying to assure that word alignment occurs.
//! - Does not use (reinterpret) cast of pointer to pointer due to possible issues with optimisation aliasing.
//!
//! \todo Write big endian versions.
//! \todo Write reverse casts.
//!
//============================================================================================================


#include <math.h>
#include "oxts/common/Lib_Compiler.h"
#include "oxts/common/BasicCasts.h"


//============================================================================================================

real64_t cast_8_byte_LE_to_real64(const uint8_t *b)
{
	volatile union { real64_t x; uint8_t c[8]; } u;
	u.c[0] = b[0];
	u.c[1] = b[1];
	u.c[2] = b[2];
	u.c[3] = b[3];
	u.c[4] = b[4];
	u.c[5] = b[5];
	u.c[6] = b[6];
	u.c[7] = b[7];
	return u.x;
}

void cast_real64_to_8_byte_LE(uint8_t *b, real64_t v)
{
	volatile union { real64_t x; uint8_t c[8]; } u;
	u.x = v;
	b[0] = u.c[0];
	b[1] = u.c[1];
	b[2] = u.c[2];
	b[3] = u.c[3];
	b[4] = u.c[4];
	b[5] = u.c[5];
	b[6] = u.c[6];
	b[7] = u.c[7];
}


//============================================================================================================

real64_t cast_8_byte_BE_to_real64(const uint8_t *b)
{
	volatile union { real64_t x; uint8_t c[8]; } u;
	u.c[0] = b[7];
	u.c[1] = b[6];
	u.c[2] = b[5];
	u.c[3] = b[4];
	u.c[4] = b[3];
	u.c[5] = b[2];
	u.c[6] = b[1];
	u.c[7] = b[0];
	return u.x;
}

void cast_real64_to_8_byte_BE(uint8_t *b, real64_t v)
{
	volatile union { real64_t x; uint8_t c[8]; } u;
	u.x = v;
	b[7] = u.c[0];
	b[6] = u.c[1];
	b[5] = u.c[2];
	b[4] = u.c[3];
	b[3] = u.c[4];
	b[2] = u.c[5];
	b[1] = u.c[6];
	b[0] = u.c[7];
}


//============================================================================================================

real32_t cast_4_byte_LE_to_real32(const uint8_t *b)
{
	volatile union { real32_t x; uint8_t c[4]; } u;
	u.c[0] = b[0];
	u.c[1] = b[1];
	u.c[2] = b[2];
	u.c[3] = b[3];
	return u.x;
}

void cast_real32_to_4_byte_LE(uint8_t *b, real32_t v)
{
	volatile union { real32_t x; uint8_t c[4]; } u;
	u.x = v;
	b[0] = u.c[0];
	b[1] = u.c[1];
	b[2] = u.c[2];
	b[3] = u.c[3];
}


//============================================================================================================

real32_t cast_4_byte_BE_to_real32(const uint8_t *b)
{
	volatile union { real32_t x; uint8_t c[4]; } u;
	u.c[0] = b[3];
	u.c[1] = b[2];
	u.c[2] = b[1];
	u.c[3] = b[0];
	return u.x;
}

void cast_real32_to_4_byte_BE(uint8_t *b, real32_t v)
{
	volatile union { real32_t x; uint8_t c[4]; } u;
	u.x = v;
	b[3] = u.c[0];
	b[2] = u.c[1];
	b[1] = u.c[2];
	b[0] = u.c[3];
}


//============================================================================================================

int64_t cast_1_byte_LE_to_int64(const uint8_t *b)
{
	volatile union { int64_t x; uint8_t c[8]; } u;
	u.c[7] = b[0];
	return u.x >> 56;
}

void cast_int64_to_1_byte_LE(uint8_t *b, int64_t v)
{
	volatile union { int64_t x; uint8_t c[8]; } u;
	u.x = v;
	b[0] = u.c[0];
}


//============================================================================================================

int64_t cast_2_byte_LE_to_int64(const uint8_t *b)
{
	volatile union { int64_t x; uint8_t c[8]; } u;
	u.c[6] = b[0];
	u.c[7] = b[1];
	return u.x >> 48;
}

void cast_int64_to_2_byte_LE(uint8_t *b, int64_t v)
{
	volatile union { int64_t x; uint8_t c[8]; } u;
	u.x = v;
	b[0] = u.c[0];
	b[1] = u.c[1];
}


//============================================================================================================

int64_t cast_3_byte_LE_to_int64(const uint8_t *b)
{
	volatile union { int64_t x; uint8_t c[8]; } u;
	u.c[5] = b[0];
	u.c[6] = b[1];
	u.c[7] = b[2];
	return u.x >> 40;
}

void cast_int64_to_3_byte_LE(uint8_t *b, int64_t v)
{
	volatile union { int64_t x; uint8_t c[8]; } u;
	u.x = v;
	b[0] = u.c[0];
	b[1] = u.c[1];
	b[2] = u.c[2];
}


//============================================================================================================

int64_t cast_4_byte_LE_to_int64(const uint8_t *b)
{
	volatile union { int64_t x; uint8_t c[8]; } u;
	u.c[4] = b[0];
	u.c[5] = b[1];
	u.c[6] = b[2];
	u.c[7] = b[3];
	return u.x >> 32;
}

void cast_int64_to_4_byte_LE(uint8_t *b, int64_t v)
{
	volatile union { int64_t x; uint8_t c[8]; } u;
	u.x = v;
	b[0] = u.c[0];
	b[1] = u.c[1];
	b[2] = u.c[2];
	b[3] = u.c[3];
}


//============================================================================================================

int64_t cast_5_byte_LE_to_int64(const uint8_t *b)
{
	volatile union { int64_t x; uint8_t c[8]; } u;
	u.c[3] = b[0];
	u.c[4] = b[1];
	u.c[5] = b[2];
	u.c[6] = b[3];
	u.c[7] = b[4];
	return u.x >> 24;
}

void cast_int64_to_5_byte_LE(uint8_t *b, int64_t v)
{
	volatile union { int64_t x; uint8_t c[8]; } u;
	u.x = v;
	b[0] = u.c[0];
	b[1] = u.c[1];
	b[2] = u.c[2];
	b[3] = u.c[3];
	b[4] = u.c[4];
}


//============================================================================================================

int64_t cast_6_byte_LE_to_int64(const uint8_t *b)
{
	volatile union { int64_t x; uint8_t c[8]; } u;
	u.c[2] = b[0];
	u.c[3] = b[1];
	u.c[4] = b[2];
	u.c[5] = b[3];
	u.c[6] = b[4];
	u.c[7] = b[5];
	return u.x >> 16;
}

void cast_int64_to_6_byte_LE(uint8_t *b, int64_t v)
{
	volatile union { int64_t x; uint8_t c[8]; } u;
	u.x = v;
	b[0] = u.c[0];
	b[1] = u.c[1];
	b[2] = u.c[2];
	b[3] = u.c[3];
	b[4] = u.c[4];
	b[5] = u.c[5];
}


//============================================================================================================

int64_t cast_7_byte_LE_to_int64(const uint8_t *b)
{
	volatile union { int64_t x; uint8_t c[8]; } u;
	u.c[1] = b[0];
	u.c[2] = b[1];
	u.c[3] = b[2];
	u.c[4] = b[3];
	u.c[5] = b[4];
	u.c[6] = b[5];
	u.c[7] = b[6];
	return u.x >> 8;
}

void cast_int64_to_7_byte_LE(uint8_t *b, int64_t v)
{
	volatile union { int64_t x; uint8_t c[8]; } u;
	u.x = v;
	b[0] = u.c[0];
	b[1] = u.c[1];
	b[2] = u.c[2];
	b[3] = u.c[3];
	b[4] = u.c[4];
	b[5] = u.c[5];
	b[6] = u.c[6];
}


//============================================================================================================

int64_t cast_8_byte_LE_to_int64(const uint8_t *b)
{
	volatile union { int64_t x; uint8_t c[8]; } u;
	u.c[0] = b[0];
	u.c[1] = b[1];
	u.c[2] = b[2];
	u.c[3] = b[3];
	u.c[4] = b[4];
	u.c[5] = b[5];
	u.c[6] = b[6];
	u.c[7] = b[7];
	return u.x;
}

void cast_int64_to_8_byte_LE(uint8_t *b, int64_t v)
{
	volatile union { int64_t x; uint8_t c[8]; } u;
	u.x = v;
	b[0] = u.c[0];
	b[1] = u.c[1];
	b[2] = u.c[2];
	b[3] = u.c[3];
	b[4] = u.c[4];
	b[5] = u.c[5];
	b[6] = u.c[6];
	b[7] = u.c[7];
}

int64_t cast_8_byte_BE_to_int64(const uint8_t *b)
{
	volatile union { int64_t x; uint8_t c[8]; } u;
	u.c[0] = b[7];
	u.c[1] = b[6];
	u.c[2] = b[5];
	u.c[3] = b[4];
	u.c[4] = b[3];
	u.c[5] = b[2];
	u.c[6] = b[1];
	u.c[7] = b[0];
	return u.x;
}

void cast_int64_to_8_byte_BE(uint8_t *b, int64_t v)
{
	volatile union { int64_t x; uint8_t c[8]; } u;
	u.x = v;
	b[7] = u.c[0];
	b[6] = u.c[1];
	b[5] = u.c[2];
	b[4] = u.c[3];
	b[3] = u.c[4];
	b[2] = u.c[5];
	b[1] = u.c[6];
	b[0] = u.c[7];
}


//============================================================================================================

int32_t cast_1_byte_LE_to_int32(const uint8_t *b)
{
	volatile union { int32_t x; uint8_t c[4]; } u;
	u.c[3] = b[0];
	return u.x >> 24;
}

void cast_int32_to_1_byte_LE(uint8_t *b, int32_t v)
{
	volatile union { int32_t x; uint8_t c[4]; } u;
	u.x = v;
	b[0] = u.c[0];
}


//============================================================================================================

int32_t cast_2_byte_LE_to_int32(const uint8_t *b)
{
	volatile union { int32_t x; uint8_t c[4]; } u;
	u.c[2] = b[0];
	u.c[3] = b[1];
	return u.x >> 16;
}

void cast_int32_to_2_byte_LE(uint8_t *b, int32_t v)
{
	volatile union { int32_t x; uint8_t c[4]; } u;
	u.x = v;
	b[0] = u.c[0];
	b[1] = u.c[1];
}


//============================================================================================================

int32_t cast_3_byte_LE_to_int32(const uint8_t *b)
{
	volatile union { int32_t x; uint8_t c[4]; } u;
	u.c[1] = b[0];
	u.c[2] = b[1];
	u.c[3] = b[2];
	return u.x >> 8;
}

void cast_int32_to_3_byte_LE(uint8_t *b, int32_t v)
{
	volatile union { int32_t x; uint8_t c[4]; } u;
	u.x = v;
	b[0] = u.c[0];
	b[1] = u.c[1];
	b[2] = u.c[2];
}


//============================================================================================================

int32_t cast_4_byte_LE_to_int32(const uint8_t *b)
{
	volatile union { int32_t x; uint8_t c[4]; } u;
	u.c[0] = b[0];
	u.c[1] = b[1];
	u.c[2] = b[2];
	u.c[3] = b[3];
	return u.x;
}

void cast_int32_to_4_byte_LE(uint8_t *b, int32_t v)
{
	volatile union { int32_t x; uint8_t c[4]; } u;
	u.x = v;
	b[0] = u.c[0];
	b[1] = u.c[1];
	b[2] = u.c[2];
	b[3] = u.c[3];
}

int32_t cast_4_byte_BE_to_int32(const uint8_t *b)
{
	volatile union { int32_t x; uint8_t c[4]; } u;
	u.c[0] = b[3];
	u.c[1] = b[2];
	u.c[2] = b[1];
	u.c[3] = b[0];
	return u.x;
}

void cast_int32_to_4_byte_BE(uint8_t *b, int32_t v)
{
	volatile union { int32_t x; uint8_t c[4]; } u;
	u.x = v;
	b[3] = u.c[0];
	b[2] = u.c[1];
	b[1] = u.c[2];
	b[0] = u.c[3];
}


//============================================================================================================

int16_t cast_1_byte_LE_to_int16(const uint8_t *b)
{
	volatile union { int16_t x; uint8_t c[2]; } u;
	u.c[1] = b[0];
	return u.x >> 8;
}

void cast_int16_to_1_byte_LE(uint8_t *b, int16_t v)
{
	volatile union { int16_t x; uint8_t c[2]; } u;
	u.x = v;
	b[0] = u.c[0];
}


//============================================================================================================

int16_t cast_2_byte_LE_to_int16(const uint8_t *b)
{
	volatile union { int16_t x; uint8_t c[2]; } u;
	u.c[0] = b[0];
	u.c[1] = b[1];
	return u.x;
}

void cast_int16_to_2_byte_LE(uint8_t *b, int16_t v)
{
	volatile union { int16_t x; uint8_t c[2]; } u;
	u.x = v;
	b[0] = u.c[0];
	b[1] = u.c[1];
}

int16_t cast_2_byte_BE_to_int16(const uint8_t *b)
{
	volatile union { int16_t x; uint8_t c[2]; } u;
	u.c[0] = b[1];
	u.c[1] = b[0];
	return u.x;
}

void cast_int16_to_2_byte_BE(uint8_t *b, int16_t v)
{
	volatile union { int16_t x; uint8_t c[2]; } u;
	u.x = v;
	b[1] = u.c[0];
	b[0] = u.c[1];
}


//============================================================================================================

int8_t cast_1_byte_LE_to_int8(const uint8_t *b)
{
	return ((int8_t)(b[0]));
}

void cast_int8_to_1_byte_LE(uint8_t *b, int8_t v)
{
	b[0] = ((int8_t)(v));
}

int8_t cast_1_byte_BE_to_int8(const uint8_t *b)
{
	return ((int8_t)(b[0]));
}

void cast_int8_to_1_byte_BE(uint8_t *b, int8_t v)
{
	b[0] = ((int8_t)(v));
}


//============================================================================================================

uint64_t cast_1_byte_LE_to_uint64(const uint8_t *b)
{
	volatile union { uint64_t x; uint8_t c[8]; } u;
	u.x = 0;
	u.c[0] = b[0];
	return u.x;
}

void cast_uint64_to_1_byte_LE(uint8_t *b, uint64_t v)
{
	volatile union { uint64_t x; uint8_t c[8]; } u;
	u.x = v;
	b[0] = u.c[0];
}


//============================================================================================================

uint64_t cast_2_byte_LE_to_uint64(const uint8_t *b)
{
	volatile union { uint64_t x; uint8_t c[8]; } u;
	u.x = 0;
	u.c[0] = b[0];
	u.c[1] = b[1];
	return u.x;
}

void cast_uint64_to_2_byte_LE(uint8_t *b, uint64_t v)
{
	volatile union { uint64_t x; uint8_t c[8]; } u;
	u.x = v;
	b[0] = u.c[0];
	b[1] = u.c[1];
}


//============================================================================================================

uint64_t cast_3_byte_LE_to_uint64(const uint8_t *b)
{
	volatile union { uint64_t x; uint8_t c[8]; } u;
	u.x = 0;
	u.c[0] = b[0];
	u.c[1] = b[1];
	u.c[2] = b[2];
	return u.x;
}

void cast_uint64_to_3_byte_LE(uint8_t *b, uint64_t v)
{
	volatile union { uint64_t x; uint8_t c[8]; } u;
	u.x = v;
	b[0] = u.c[0];
	b[1] = u.c[1];
	b[2] = u.c[2];
}


//============================================================================================================

uint64_t cast_4_byte_LE_to_uint64(const uint8_t *b)
{
	volatile union { uint64_t x; uint8_t c[8]; } u;
	u.x = 0;
	u.c[0] = b[0];
	u.c[1] = b[1];
	u.c[2] = b[2];
	u.c[3] = b[3];
	return u.x;
}

void cast_uint64_to_4_byte_LE(uint8_t *b, uint64_t v)
{
	volatile union { uint64_t x; uint8_t c[8]; } u;
	u.x = v;
	b[0] = u.c[0];
	b[1] = u.c[1];
	b[2] = u.c[2];
	b[3] = u.c[3];
}


//============================================================================================================

uint64_t cast_5_byte_LE_to_uint64(const uint8_t *b)
{
	volatile union { uint64_t x; uint8_t c[8]; } u;
	u.x = 0;
	u.c[0] = b[0];
	u.c[1] = b[1];
	u.c[2] = b[2];
	u.c[3] = b[3];
	u.c[4] = b[4];
	return u.x;
}

void cast_uint64_to_5_byte_LE(uint8_t *b, uint64_t v)
{
	volatile union { uint64_t x; uint8_t c[8]; } u;
	u.x = v;
	b[0] = u.c[0];
	b[1] = u.c[1];
	b[2] = u.c[2];
	b[3] = u.c[3];
	b[4] = u.c[4];
}


//============================================================================================================

uint64_t cast_6_byte_LE_to_uint64(const uint8_t *b)
{
	volatile union { uint64_t x; uint8_t c[8]; } u;
	u.x = 0;
	u.c[0] = b[0];
	u.c[1] = b[1];
	u.c[2] = b[2];
	u.c[3] = b[3];
	u.c[4] = b[4];
	u.c[5] = b[5];
	return u.x;
}

void cast_uint64_to_6_byte_LE(uint8_t *b, uint64_t v)
{
	volatile union { uint64_t x; uint8_t c[8]; } u;
	u.x = v;
	b[0] = u.c[0];
	b[1] = u.c[1];
	b[2] = u.c[2];
	b[3] = u.c[3];
	b[4] = u.c[4];
	b[5] = u.c[5];
}


//============================================================================================================

uint64_t cast_7_byte_LE_to_uint64(const uint8_t *b)
{
	volatile union { uint64_t x; uint8_t c[8]; } u;
	u.x = 0;
	u.c[0] = b[0];
	u.c[1] = b[1];
	u.c[2] = b[2];
	u.c[3] = b[3];
	u.c[4] = b[4];
	u.c[5] = b[5];
	u.c[6] = b[6];
	return u.x;
}

void cast_uint64_to_7_byte_LE(uint8_t *b, uint64_t v)
{
	volatile union { uint64_t x; uint8_t c[8]; } u;
	u.x = v;
	b[0] = u.c[0];
	b[1] = u.c[1];
	b[2] = u.c[2];
	b[3] = u.c[3];
	b[4] = u.c[4];
	b[5] = u.c[5];
	b[6] = u.c[6];
}


//============================================================================================================

uint64_t cast_8_byte_LE_to_uint64(const uint8_t *b)
{
	volatile union { uint64_t x; uint8_t c[8]; } u;
	u.c[0] = b[0];
	u.c[1] = b[1];
	u.c[2] = b[2];
	u.c[3] = b[3];
	u.c[4] = b[4];
	u.c[5] = b[5];
	u.c[6] = b[6];
	u.c[7] = b[7];
	return u.x;
}

void cast_uint64_to_8_byte_LE(uint8_t *b, uint64_t v)
{
	volatile union { uint64_t x; uint8_t c[8]; } u;
	u.x = v;
	b[0] = u.c[0];
	b[1] = u.c[1];
	b[2] = u.c[2];
	b[3] = u.c[3];
	b[4] = u.c[4];
	b[5] = u.c[5];
	b[6] = u.c[6];
	b[7] = u.c[7];
}

uint64_t cast_8_byte_BE_to_uint64(const uint8_t *b)
{
	volatile union { uint64_t x; uint8_t c[8]; } u;
	u.c[0] = b[7];
	u.c[1] = b[6];
	u.c[2] = b[5];
	u.c[3] = b[4];
	u.c[4] = b[3];
	u.c[5] = b[2];
	u.c[6] = b[1];
	u.c[7] = b[0];
	return u.x;
}

void cast_uint64_to_8_byte_BE(uint8_t *b, uint64_t v)
{
	volatile union { uint64_t x; uint8_t c[8]; } u;
	u.x = v;
	b[7] = u.c[0];
	b[6] = u.c[1];
	b[5] = u.c[2];
	b[4] = u.c[3];
	b[3] = u.c[4];
	b[2] = u.c[5];
	b[1] = u.c[6];
	b[0] = u.c[7];
}


//============================================================================================================

uint32_t cast_1_byte_LE_to_uint32(const uint8_t *b)
{
	volatile union { uint32_t x; uint8_t c[4]; } u;
	u.x = 0;
	u.c[0] = b[0];
	return u.x;
}

void cast_uint32_to_1_byte_LE(uint8_t *b, uint32_t v)
{
	volatile union { uint32_t x; uint8_t c[4]; } u;
	u.x = v;
	b[0] = u.c[0];
}


//============================================================================================================

uint32_t cast_2_byte_LE_to_uint32(const uint8_t *b)
{
	volatile union { uint32_t x; uint8_t c[4]; } u;
	u.x = 0;
	u.c[0] = b[0];
	u.c[1] = b[1];
	return u.x;
}

void cast_uint32_to_2_byte_LE(uint8_t *b, uint32_t v)
{
	volatile union { uint32_t x; uint8_t c[4]; } u;
	u.x = v;
	b[0] = u.c[0];
	b[1] = u.c[1];
}


//============================================================================================================

uint32_t cast_3_byte_LE_to_uint32(const uint8_t *b)
{
	volatile union { uint32_t x; uint8_t c[4]; } u;
	u.x = 0;
	u.c[0] = b[0];
	u.c[1] = b[1];
	u.c[2] = b[2];
	return u.x;
}

void cast_uint32_to_3_byte_LE(uint8_t *b, uint32_t v)
{
	volatile union { uint32_t x; uint8_t c[4]; } u;
	u.x = v;
	b[0] = u.c[0];
	b[1] = u.c[1];
	b[2] = u.c[2];
}


//============================================================================================================

uint32_t cast_4_byte_LE_to_uint32(const uint8_t *b)
{
	volatile union { uint32_t x; uint8_t c[4]; } u;
	u.c[0] = b[0];
	u.c[1] = b[1];
	u.c[2] = b[2];
	u.c[3] = b[3];
	return u.x;
}

void cast_uint32_to_4_byte_LE(uint8_t *b, uint32_t v)
{
	volatile union { uint32_t x; uint8_t c[4]; } u;
	u.x = v;
	b[0] = u.c[0];
	b[1] = u.c[1];
	b[2] = u.c[2];
	b[3] = u.c[3];
}

uint32_t cast_4_byte_BE_to_uint32(const uint8_t *b)
{
	volatile union { uint32_t x; uint8_t c[4]; } u;
	u.c[0] = b[3];
	u.c[1] = b[2];
	u.c[2] = b[1];
	u.c[3] = b[0];
	return u.x;
}

void cast_uint32_to_4_byte_BE(uint8_t *b, uint32_t v)
{
	volatile union { uint32_t x; uint8_t c[4]; } u;
	u.x = v;
	b[3] = u.c[0];
	b[2] = u.c[1];
	b[1] = u.c[2];
	b[0] = u.c[3];
}


//============================================================================================================

uint16_t cast_1_byte_LE_to_uint16(const uint8_t *b)
{
	volatile union { uint16_t x; uint8_t c[2]; } u;
	u.x = 0;
	u.c[0] = b[0];
	return u.x;
}

void cast_uint16_to_1_byte_LE(uint8_t *b, uint16_t v)
{
	volatile union { uint16_t x; uint8_t c[2]; } u;
	u.x = v;
	b[0] = u.c[0];
}


//============================================================================================================

uint16_t cast_2_byte_LE_to_uint16(const uint8_t *b)
{
	volatile union { uint16_t x; uint8_t c[2]; } u;
	u.c[0] = b[0];
	u.c[1] = b[1];
	return u.x;
}

void cast_uint16_to_2_byte_LE(uint8_t *b, uint16_t v)
{
	volatile union { uint16_t x; uint8_t c[2]; } u;
	u.x = v;
	b[0] = u.c[0];
	b[1] = u.c[1];
}

uint16_t cast_2_byte_BE_to_uint16(const uint8_t *b)
{
	volatile union { uint16_t x; uint8_t c[2]; } u;
	u.c[0] = b[1];
	u.c[1] = b[0];
	return u.x;
}

void cast_uint16_to_2_byte_BE(uint8_t *b, uint16_t v)
{
	volatile union { uint16_t x; uint8_t c[2]; } u;
	u.x = v;
	b[1] = u.c[0];
	b[0] = u.c[1];
}


//============================================================================================================

uint8_t cast_1_byte_LE_to_uint8(const uint8_t *b)
{
	return b[0];
}

void cast_uint8_to_1_byte_LE(uint8_t *b, uint8_t v)
{
	b[0] = v;
}

uint8_t cast_1_byte_BE_to_uint8(const uint8_t *b)
{
	return b[0];
}

void cast_uint8_to_1_byte_BE(uint8_t *b, uint8_t v)
{
	b[0] = v;
}


//============================================================================================================
// Signed integer to OxTS signed integer.

int8_t   cast_int8_to_fix8 (int8_t  x) { return x <= OXTS_1BYTE_INT8_NEG  ? OXTS_fix8_NEG  : x >= OXTS_1BYTE_INT8_POS   ? OXTS_fix8_POS  : ( int8_t) x; }
int8_t  cast_int16_to_fix8 (int16_t x) { return x <= OXTS_1BYTE_INT16_NEG ? OXTS_fix8_NEG  : x >= OXTS_1BYTE_INT16_POS  ? OXTS_fix8_POS  : ( int8_t) x; }
int8_t  cast_int32_to_fix8 (int32_t x) { return x <= OXTS_1BYTE_INT32_NEG ? OXTS_fix8_NEG  : x >= OXTS_1BYTE_INT32_POS  ? OXTS_fix8_POS  : ( int8_t) x; }
int8_t  cast_int64_to_fix8 (int64_t x) { return x <= OXTS_1BYTE_INT64_NEG ? OXTS_fix8_NEG  : x >= OXTS_1BYTE_INT64_POS  ? OXTS_fix8_POS  : ( int8_t) x; }
int16_t  cast_int8_to_fix16(int8_t  x) { return                                                                                            (int16_t) x; }
int16_t cast_int16_to_fix16(int16_t x) { return x <= OXTS_2BYTE_INT16_NEG ? OXTS_fix16_NEG : x >= OXTS_2BYTE_INT16_POS  ? OXTS_fix16_POS : (int16_t) x; }
int16_t cast_int32_to_fix16(int32_t x) { return x <= OXTS_2BYTE_INT32_NEG ? OXTS_fix16_NEG : x >= OXTS_2BYTE_INT32_POS  ? OXTS_fix16_POS : (int16_t) x; }
int16_t cast_int64_to_fix16(int64_t x) { return x <= OXTS_2BYTE_INT64_NEG ? OXTS_fix16_NEG : x >= OXTS_2BYTE_INT64_POS  ? OXTS_fix16_POS : (int16_t) x; }
int32_t  cast_int8_to_fix24(int8_t  x) { return                                                                                            (int32_t) x; }
int32_t cast_int16_to_fix24(int16_t x) { return                                                                                            (int32_t) x; }
int32_t cast_int32_to_fix24(int32_t x) { return x <= OXTS_3BYTE_INT32_NEG ? OXTS_fix24_NEG : x >= OXTS_3BYTE_INT32_POS  ? OXTS_fix24_POS : (int32_t) x; }
int32_t cast_int64_to_fix24(int64_t x) { return x <= OXTS_3BYTE_INT64_NEG ? OXTS_fix24_NEG : x >= OXTS_3BYTE_INT64_POS  ? OXTS_fix24_POS : (int32_t) x; }
int32_t  cast_int8_to_fix32(int8_t  x) { return                                                                                            (int32_t) x; }
int32_t cast_int16_to_fix32(int16_t x) { return                                                                                            (int32_t) x; }
int32_t cast_int32_to_fix32(int32_t x) { return x <= OXTS_4BYTE_INT32_NEG ? OXTS_fix32_NEG : x >= OXTS_4BYTE_INT32_POS  ? OXTS_fix32_POS : (int32_t) x; }
int32_t cast_int64_to_fix32(int64_t x) { return x <= OXTS_4BYTE_INT64_NEG ? OXTS_fix32_NEG : x >= OXTS_4BYTE_INT64_POS  ? OXTS_fix32_POS : (int32_t) x; }
int64_t  cast_int8_to_fix40(int8_t  x) { return                                                                                            (int64_t) x; }
int64_t cast_int16_to_fix40(int16_t x) { return                                                                                            (int64_t) x; }
int64_t cast_int32_to_fix40(int32_t x) { return                                                                                            (int64_t) x; }
int64_t cast_int64_to_fix40(int64_t x) { return x <= OXTS_5BYTE_INT64_NEG ? OXTS_fix40_NEG : x >= OXTS_5BYTE_INT64_POS  ? OXTS_fix40_POS : (int64_t) x; }
int64_t  cast_int8_to_fix48(int8_t  x) { return                                                                                            (int64_t) x; }
int64_t cast_int16_to_fix48(int16_t x) { return                                                                                            (int64_t) x; }
int64_t cast_int32_to_fix48(int32_t x) { return                                                                                            (int64_t) x; }
int64_t cast_int64_to_fix48(int64_t x) { return x <= OXTS_6BYTE_INT64_NEG ? OXTS_fix48_NEG : x >= OXTS_6BYTE_INT64_POS  ? OXTS_fix48_POS : (int64_t) x; }
int64_t  cast_int8_to_fix56(int8_t  x) { return                                                                                            (int64_t) x; }
int64_t cast_int16_to_fix56(int16_t x) { return                                                                                            (int64_t) x; }
int64_t cast_int32_to_fix56(int32_t x) { return                                                                                            (int64_t) x; }
int64_t cast_int64_to_fix56(int64_t x) { return x <= OXTS_7BYTE_INT64_NEG ? OXTS_fix56_NEG : x >= OXTS_7BYTE_INT64_POS  ? OXTS_fix56_POS : (int64_t) x; }
int64_t  cast_int8_to_fix64(int8_t  x) { return                                                                                            (int64_t) x; }
int64_t cast_int16_to_fix64(int16_t x) { return                                                                                            (int64_t) x; }
int64_t cast_int32_to_fix64(int32_t x) { return                                                                                            (int64_t) x; }
int64_t cast_int64_to_fix64(int64_t x) { return x <= OXTS_8BYTE_INT64_NEG ? OXTS_fix64_NEG : x >= OXTS_8BYTE_INT64_POS  ? OXTS_fix64_POS : (int64_t) x; }


//============================================================================================================
// Unsigned integer to OxTS signed integer.

int8_t   cast_uint8_to_fix8 (uint8_t  x) { return x >= ((uint8_t ) OXTS_1BYTE_INT8_POS ) ? OXTS_fix8_POS  : ( int8_t) x; }
int8_t  cast_uint16_to_fix8 (uint16_t x) { return x >= ((uint16_t) OXTS_1BYTE_INT16_POS) ? OXTS_fix8_POS  : ( int8_t) x; }
int8_t  cast_uint32_to_fix8 (uint32_t x) { return x >= ((uint32_t) OXTS_1BYTE_INT32_POS) ? OXTS_fix8_POS  : ( int8_t) x; }
int8_t  cast_uint64_to_fix8 (uint64_t x) { return x >= ((uint64_t) OXTS_1BYTE_INT64_POS) ? OXTS_fix8_POS  : ( int8_t) x; }
int16_t  cast_uint8_to_fix16(uint8_t  x) { return                                                           (int16_t) x; }
int16_t cast_uint16_to_fix16(uint16_t x) { return x >= ((uint16_t) OXTS_2BYTE_INT16_POS) ? OXTS_fix16_POS : (int16_t) x; }
int16_t cast_uint32_to_fix16(uint32_t x) { return x >= ((uint32_t) OXTS_2BYTE_INT32_POS) ? OXTS_fix16_POS : (int16_t) x; }
int16_t cast_uint64_to_fix16(uint64_t x) { return x >= ((uint64_t) OXTS_2BYTE_INT64_POS) ? OXTS_fix16_POS : (int16_t) x; }
int32_t  cast_uint8_to_fix24(uint8_t  x) { return                                                           (int32_t) x; }
int32_t cast_uint16_to_fix24(uint16_t x) { return                                                           (int32_t) x; }
int32_t cast_uint32_to_fix24(uint32_t x) { return x >= ((uint32_t) OXTS_3BYTE_INT32_POS) ? OXTS_fix24_POS : (int32_t) x; }
int32_t cast_uint64_to_fix24(uint64_t x) { return x >= ((uint64_t) OXTS_3BYTE_INT64_POS) ? OXTS_fix24_POS : (int32_t) x; }
int32_t  cast_uint8_to_fix32(uint8_t  x) { return                                                           (int32_t) x; }
int32_t cast_uint16_to_fix32(uint16_t x) { return                                                           (int32_t) x; }
int32_t cast_uint32_to_fix32(uint32_t x) { return x >= ((uint32_t) OXTS_4BYTE_INT32_POS) ? OXTS_fix32_POS : (int32_t) x; }
int32_t cast_uint64_to_fix32(uint64_t x) { return x >= ((uint64_t) OXTS_4BYTE_INT64_POS) ? OXTS_fix32_POS : (int32_t) x; }
int64_t  cast_uint8_to_fix40(uint8_t  x) { return                                                           (int64_t) x; }
int64_t cast_uint16_to_fix40(uint16_t x) { return                                                           (int64_t) x; }
int64_t cast_uint32_to_fix40(uint32_t x) { return                                                           (int64_t) x; }
int64_t cast_uint64_to_fix40(uint64_t x) { return x >= ((uint64_t) OXTS_5BYTE_INT64_POS) ? OXTS_fix40_POS : (int64_t) x; }
int64_t  cast_uint8_to_fix48(uint8_t  x) { return                                                           (int64_t) x; }
int64_t cast_uint16_to_fix48(uint16_t x) { return                                                           (int64_t) x; }
int64_t cast_uint32_to_fix48(uint32_t x) { return                                                           (int64_t) x; }
int64_t cast_uint64_to_fix48(uint64_t x) { return x >= ((uint64_t) OXTS_6BYTE_INT64_POS) ? OXTS_fix48_POS : (int64_t) x; }
int64_t  cast_uint8_to_fix56(uint8_t  x) { return                                                           (int64_t) x; }
int64_t cast_uint16_to_fix56(uint16_t x) { return                                                           (int64_t) x; }
int64_t cast_uint32_to_fix56(uint32_t x) { return                                                           (int64_t) x; }
int64_t cast_uint64_to_fix56(uint64_t x) { return x >= ((uint64_t) OXTS_7BYTE_INT64_POS) ? OXTS_fix56_POS : (int64_t) x; }
int64_t  cast_uint8_to_fix64(uint8_t  x) { return                                                           (int64_t) x; }
int64_t cast_uint16_to_fix64(uint16_t x) { return                                                           (int64_t) x; }
int64_t cast_uint32_to_fix64(uint32_t x) { return                                                           (int64_t) x; }
int64_t cast_uint64_to_fix64(uint64_t x) { return x >= ((uint64_t) OXTS_8BYTE_INT64_POS) ? OXTS_fix64_POS : (int64_t) x; }


//============================================================================================================
// Signed integer to OxTS unsigned integer.

uint8_t   cast_int8_to_ufix8 (int8_t  x) { return x < 0 ? OXTS_ufix8_INV  : ((uint8_t ) x) >= OXTS_1BYTE_UINT8_POS  ? OXTS_ufix8_POS  : ( uint8_t) x; }
uint8_t  cast_int16_to_ufix8 (int16_t x) { return x < 0 ? OXTS_ufix8_INV  : ((uint16_t) x) >= OXTS_1BYTE_UINT16_POS ? OXTS_ufix8_POS  : ( uint8_t) x; }
uint8_t  cast_int32_to_ufix8 (int32_t x) { return x < 0 ? OXTS_ufix8_INV  : ((uint32_t) x) >= OXTS_1BYTE_UINT32_POS ? OXTS_ufix8_POS  : ( uint8_t) x; }
uint8_t  cast_int64_to_ufix8 (int64_t x) { return x < 0 ? OXTS_ufix8_INV  : ((uint64_t) x) >= OXTS_1BYTE_UINT64_POS ? OXTS_ufix8_POS  : ( uint8_t) x; }
uint16_t  cast_int8_to_ufix16(int8_t  x) { return x < 0 ? OXTS_ufix16_INV :                                                             (uint16_t) x; }
uint16_t cast_int16_to_ufix16(int16_t x) { return x < 0 ? OXTS_ufix16_INV : ((uint16_t) x) >= OXTS_2BYTE_UINT16_POS ? OXTS_ufix16_POS : (uint16_t) x; }
uint16_t cast_int32_to_ufix16(int32_t x) { return x < 0 ? OXTS_ufix16_INV : ((uint32_t) x) >= OXTS_2BYTE_UINT32_POS ? OXTS_ufix16_POS : (uint16_t) x; }
uint16_t cast_int64_to_ufix16(int64_t x) { return x < 0 ? OXTS_ufix16_INV : ((uint64_t) x) >= OXTS_2BYTE_UINT64_POS ? OXTS_ufix16_POS : (uint16_t) x; }
uint32_t  cast_int8_to_ufix24(int8_t  x) { return x < 0 ? OXTS_ufix24_INV :                                                             (uint32_t) x; }
uint32_t cast_int16_to_ufix24(int16_t x) { return x < 0 ? OXTS_ufix24_INV :                                                             (uint32_t) x; }
uint32_t cast_int32_to_ufix24(int32_t x) { return x < 0 ? OXTS_ufix24_INV : ((uint32_t) x) >= OXTS_3BYTE_UINT32_POS ? OXTS_ufix24_POS : (uint32_t) x; }
uint32_t cast_int64_to_ufix24(int64_t x) { return x < 0 ? OXTS_ufix24_INV : ((uint64_t) x) >= OXTS_3BYTE_UINT64_POS ? OXTS_ufix24_POS : (uint32_t) x; }
uint32_t  cast_int8_to_ufix32(int8_t  x) { return x < 0 ? OXTS_ufix32_INV :                                                             (uint32_t) x; }
uint32_t cast_int16_to_ufix32(int16_t x) { return x < 0 ? OXTS_ufix32_INV :                                                             (uint32_t) x; }
uint32_t cast_int32_to_ufix32(int32_t x) { return x < 0 ? OXTS_ufix32_INV : ((uint32_t) x) >= OXTS_4BYTE_UINT32_POS ? OXTS_ufix32_POS : (uint32_t) x; }
uint32_t cast_int64_to_ufix32(int64_t x) { return x < 0 ? OXTS_ufix32_INV : ((uint64_t) x) >= OXTS_4BYTE_UINT64_POS ? OXTS_ufix32_POS : (uint32_t) x; }
uint64_t  cast_int8_to_ufix40(int8_t  x) { return x < 0 ? OXTS_ufix40_INV :                                                             (uint64_t) x; }
uint64_t cast_int16_to_ufix40(int16_t x) { return x < 0 ? OXTS_ufix40_INV :                                                             (uint64_t) x; }
uint64_t cast_int32_to_ufix40(int32_t x) { return x < 0 ? OXTS_ufix40_INV :                                                             (uint64_t) x; }
uint64_t cast_int64_to_ufix40(int64_t x) { return x < 0 ? OXTS_ufix40_INV : ((uint64_t) x) >= OXTS_5BYTE_UINT64_POS ? OXTS_ufix40_POS : (uint64_t) x; }
uint64_t  cast_int8_to_ufix48(int8_t  x) { return x < 0 ? OXTS_ufix48_INV :                                                             (uint64_t) x; }
uint64_t cast_int16_to_ufix48(int16_t x) { return x < 0 ? OXTS_ufix48_INV :                                                             (uint64_t) x; }
uint64_t cast_int32_to_ufix48(int32_t x) { return x < 0 ? OXTS_ufix48_INV :                                                             (uint64_t) x; }
uint64_t cast_int64_to_ufix48(int64_t x) { return x < 0 ? OXTS_ufix48_INV : ((uint64_t) x) >= OXTS_6BYTE_UINT64_POS ? OXTS_ufix48_POS : (uint64_t) x; }
uint64_t  cast_int8_to_ufix56(int8_t  x) { return x < 0 ? OXTS_ufix56_INV :                                                             (uint64_t) x; }
uint64_t cast_int16_to_ufix56(int16_t x) { return x < 0 ? OXTS_ufix56_INV :                                                             (uint64_t) x; }
uint64_t cast_int32_to_ufix56(int32_t x) { return x < 0 ? OXTS_ufix56_INV :                                                             (uint64_t) x; }
uint64_t cast_int64_to_ufix56(int64_t x) { return x < 0 ? OXTS_ufix56_INV : ((uint64_t) x) >= OXTS_7BYTE_UINT64_POS ? OXTS_ufix56_POS : (uint64_t) x; }
uint64_t  cast_int8_to_ufix64(int8_t  x) { return x < 0 ? OXTS_ufix64_INV :                                                             (uint64_t) x; }
uint64_t cast_int16_to_ufix64(int16_t x) { return x < 0 ? OXTS_ufix64_INV :                                                             (uint64_t) x; }
uint64_t cast_int32_to_ufix64(int32_t x) { return x < 0 ? OXTS_ufix64_INV :                                                             (uint64_t) x; }
uint64_t cast_int64_to_ufix64(int64_t x) { return x < 0 ? OXTS_ufix64_INV : ((uint64_t) x) >= OXTS_8BYTE_UINT64_POS ? OXTS_ufix64_POS : (uint64_t) x; }


//============================================================================================================
// Unsigned integer to OxTS Unsigned integer.

uint8_t   cast_uint8_to_ufix8 (uint8_t  x) { return x >= OXTS_1BYTE_UINT8_POS  ? OXTS_ufix8_POS  : ( uint8_t) x; }
uint8_t  cast_uint16_to_ufix8 (uint16_t x) { return x >= OXTS_1BYTE_UINT16_POS ? OXTS_ufix8_POS  : ( uint8_t) x; }
uint8_t  cast_uint32_to_ufix8 (uint32_t x) { return x >= OXTS_1BYTE_UINT32_POS ? OXTS_ufix8_POS  : ( uint8_t) x; }
uint8_t  cast_uint64_to_ufix8 (uint64_t x) { return x >= OXTS_1BYTE_UINT64_POS ? OXTS_ufix8_POS  : ( uint8_t) x; }
uint16_t  cast_uint8_to_ufix16(uint8_t  x) { return                                                (uint16_t) x; }
uint16_t cast_uint16_to_ufix16(uint16_t x) { return x >= OXTS_2BYTE_UINT16_POS ? OXTS_ufix16_POS : (uint16_t) x; }
uint16_t cast_uint32_to_ufix16(uint32_t x) { return x >= OXTS_2BYTE_UINT32_POS ? OXTS_ufix16_POS : (uint16_t) x; }
uint16_t cast_uint64_to_ufix16(uint64_t x) { return x >= OXTS_2BYTE_UINT64_POS ? OXTS_ufix16_POS : (uint16_t) x; }
uint32_t  cast_uint8_to_ufix24(uint8_t  x) { return                                                (uint32_t) x; }
uint32_t cast_uint16_to_ufix24(uint16_t x) { return                                                (uint32_t) x; }
uint32_t cast_uint32_to_ufix24(uint32_t x) { return x >= OXTS_3BYTE_UINT32_POS ? OXTS_ufix24_POS : (uint32_t) x; }
uint32_t cast_uint64_to_ufix24(uint64_t x) { return x >= OXTS_3BYTE_UINT64_POS ? OXTS_ufix24_POS : (uint32_t) x; }
uint32_t  cast_uint8_to_ufix32(uint8_t  x) { return                                                (uint32_t) x; }
uint32_t cast_uint16_to_ufix32(uint16_t x) { return                                                (uint32_t) x; }
uint32_t cast_uint32_to_ufix32(uint32_t x) { return x >= OXTS_4BYTE_UINT32_POS ? OXTS_ufix32_POS : (uint32_t) x; }
uint32_t cast_uint64_to_ufix32(uint64_t x) { return x >= OXTS_4BYTE_UINT64_POS ? OXTS_ufix32_POS : (uint32_t) x; }
uint64_t  cast_uint8_to_ufix40(uint8_t  x) { return                                                (uint64_t) x; }
uint64_t cast_uint16_to_ufix40(uint16_t x) { return                                                (uint64_t) x; }
uint64_t cast_uint32_to_ufix40(uint32_t x) { return                                                (uint64_t) x; }
uint64_t cast_uint64_to_ufix40(uint64_t x) { return x >= OXTS_5BYTE_UINT64_POS ? OXTS_ufix40_POS : (uint64_t) x; }
uint64_t  cast_uint8_to_ufix48(uint8_t  x) { return                                                (uint64_t) x; }
uint64_t cast_uint16_to_ufix48(uint16_t x) { return                                                (uint64_t) x; }
uint64_t cast_uint32_to_ufix48(uint32_t x) { return                                                (uint64_t) x; }
uint64_t cast_uint64_to_ufix48(uint64_t x) { return x >= OXTS_6BYTE_UINT64_POS ? OXTS_ufix48_POS : (uint64_t) x; }
uint64_t  cast_uint8_to_ufix56(uint8_t  x) { return                                                (uint64_t) x; }
uint64_t cast_uint16_to_ufix56(uint16_t x) { return                                                (uint64_t) x; }
uint64_t cast_uint32_to_ufix56(uint32_t x) { return                                                (uint64_t) x; }
uint64_t cast_uint64_to_ufix56(uint64_t x) { return x >= OXTS_7BYTE_UINT64_POS ? OXTS_ufix56_POS : (uint64_t) x; }
uint64_t  cast_uint8_to_ufix64(uint8_t  x) { return                                                (uint64_t) x; }
uint64_t cast_uint16_to_ufix64(uint16_t x) { return                                                (uint64_t) x; }
uint64_t cast_uint32_to_ufix64(uint32_t x) { return                                                (uint64_t) x; }
uint64_t cast_uint64_to_ufix64(uint64_t x) { return x >= OXTS_8BYTE_UINT64_POS ? OXTS_ufix64_POS : (uint64_t) x; }


//============================================================================================================

int8_t cast_real64_to_fix8(double x)
{
	if (oxts_isnan(x)) return OXTS_1BYTE_INT8_INV;
	if (x >=  126.5)   return OXTS_1BYTE_INT8_POS;
	if (x <  -126.5)   return OXTS_1BYTE_INT8_NEG;
	                   return (int8_t)(floor(x + 0.5));
}

int16_t cast_real64_to_fix16(double x)
{
	if (oxts_isnan(x)) return OXTS_2BYTE_INT16_INV;
	if (x >=  32766.5) return OXTS_2BYTE_INT16_POS;
	if (x <  -32766.5) return OXTS_2BYTE_INT16_NEG;
	                   return (int16_t)(floor(x + 0.5));
}

int32_t cast_real64_to_fix24(double x)
{
	if (oxts_isnan(x))   return OXTS_3BYTE_INT32_INV;
	if (x >=  8388606.5) return OXTS_3BYTE_INT32_POS;
	if (x <  -8388606.5) return OXTS_3BYTE_INT32_NEG;
	                     return (int32_t)(floor(x + 0.5));
}

int32_t cast_real64_to_fix32(double x)
{
	if (oxts_isnan(x))      return OXTS_4BYTE_INT32_INV;
	if (x >=  2147483646.5) return OXTS_4BYTE_INT32_POS;
	if (x <  -2147483646.5) return OXTS_4BYTE_INT32_NEG;
	                        return (int32_t)(floor(x + 0.5));
}

int64_t cast_real64_to_fix40(double x)
{
	if (oxts_isnan(x))        return OXTS_5BYTE_INT64_INV;
	if (x >=  549755813886.5) return OXTS_5BYTE_INT64_POS;
	if (x <  -549755813886.5) return OXTS_5BYTE_INT64_NEG;
	                          return (int64_t)(floor(x + 0.5));
}

int64_t cast_real64_to_fix48(double x)
{
	if (oxts_isnan(x))           return OXTS_6BYTE_INT64_INV;
	if (x >=  140737488355326.5) return OXTS_6BYTE_INT64_POS;
	if (x <  -140737488355326.5) return OXTS_6BYTE_INT64_NEG;
	                             return (int64_t)(floor(x + 0.5));
}
/*
int64_t cast_real64_to_fix56(double x)
{
}

int64_t cast_real64_to_fix64(double x)
{
}
*/

//============================================================================================================

uint8_t cast_real64_to_ufix8(double x)
{
	if (oxts_isnan(x)) return OXTS_1BYTE_UINT8_INV;
	if (x <    0.0)    return OXTS_1BYTE_UINT8_INV;
	if (x >= 253.5)    return OXTS_1BYTE_UINT8_POS;
	                   return (uint8_t)(floor(x + 0.5));
}

uint16_t cast_real64_to_ufix16(double x)
{
	if (oxts_isnan(x)) return OXTS_2BYTE_UINT16_INV;
	if (x <      0.0)  return OXTS_2BYTE_UINT16_INV;
	if (x >= 65533.5)  return OXTS_2BYTE_UINT16_POS;
	                   return (uint16_t)(floor(x + 0.5));
}

uint32_t cast_real64_to_ufix24(double x)
{
	if (oxts_isnan(x))   return OXTS_3BYTE_UINT32_INV;
	if (x <         0.0) return OXTS_3BYTE_UINT32_INV;
	if (x >= 16777213.5) return OXTS_3BYTE_UINT32_POS;
	                     return (uint32_t)(floor(x + 0.5));
}

uint32_t cast_real64_to_ufix32(double x)
{
	if (oxts_isnan(x))     return OXTS_4BYTE_UINT32_INV;
	if (x <           0.0) return OXTS_4BYTE_UINT32_INV;
	if (x >= 4294967293.5) return OXTS_4BYTE_UINT32_POS;
	                       return (uint32_t)(floor(x + 0.5));
}

uint64_t cast_real64_to_ufix40(double x)
{
	if (oxts_isnan(x))        return OXTS_5BYTE_UINT64_INV;
	if (x <              0.0) return OXTS_5BYTE_UINT64_INV;
	if (x >= 1099511627773.5) return OXTS_5BYTE_UINT64_POS;
	                          return (uint64_t)(floor(x + 0.5));
}

uint64_t cast_real64_to_ufix48(double x)
{
	if (oxts_isnan(x))          return OXTS_6BYTE_UINT64_INV;
	if (x <                0.0) return OXTS_6BYTE_UINT64_INV;
	if (x >= 281474976710653.5) return OXTS_6BYTE_UINT64_POS;
	                            return (uint64_t)(floor(x + 0.5));
}
/*
uint64_t cast_real64_to_ufix56(double x)
{
}

uint64_t cast_real64_to_ufix64(double x)
{
}
*/

//============================================================================================================

void cast_real64_to_fixed_to_1_byte_LE(uint8_t *b, double v) {  cast_int8_to_1_byte_LE(b,  cast_real64_to_fix8(v)); }
void cast_real64_to_fixed_to_2_byte_LE(uint8_t *b, double v) { cast_int16_to_2_byte_LE(b, cast_real64_to_fix16(v)); }
void cast_real64_to_fixed_to_3_byte_LE(uint8_t *b, double v) { cast_int32_to_3_byte_LE(b, cast_real64_to_fix24(v)); }
void cast_real64_to_fixed_to_4_byte_LE(uint8_t *b, double v) { cast_int32_to_4_byte_LE(b, cast_real64_to_fix32(v)); }
void cast_real64_to_fixed_to_5_byte_LE(uint8_t *b, double v) { cast_int64_to_5_byte_LE(b, cast_real64_to_fix40(v)); }
void cast_real64_to_fixed_to_6_byte_LE(uint8_t *b, double v) { cast_int64_to_6_byte_LE(b, cast_real64_to_fix48(v)); }
//id cast_real64_to_fixed_to_7_byte_LE(uint8_t *b, double v) { cast_int64_to_7_byte_LE(b, cast_real64_to_fix56(v)); }
//id cast_real64_to_fixed_to_8_byte_LE(uint8_t *b, double v) { cast_int64_to_8_byte_LE(b, cast_real64_to_fix64(v)); }


//============================================================================================================

void cast_real64_to_fixed_to_1_byte_BE(uint8_t *b, double v) {  cast_int8_to_1_byte_BE(b,  cast_real64_to_fix8(v)); }
void cast_real64_to_fixed_to_2_byte_BE(uint8_t *b, double v) { cast_int16_to_2_byte_BE(b, cast_real64_to_fix16(v)); }
//id cast_real64_to_fixed_to_3_byte_BE(uint8_t *b, double v) { cast_int32_to_3_byte_BE(b, cast_real64_to_fix24(v)); }
void cast_real64_to_fixed_to_4_byte_BE(uint8_t *b, double v) { cast_int32_to_4_byte_BE(b, cast_real64_to_fix32(v)); }
//id cast_real64_to_fixed_to_5_byte_BE(uint8_t *b, double v) { cast_int64_to_5_byte_BE(b, cast_real64_to_fix40(v)); }
//id cast_real64_to_fixed_to_6_byte_BE(uint8_t *b, double v) { cast_int64_to_6_byte_BE(b, cast_real64_to_fix48(v)); }
//id cast_real64_to_fixed_to_7_byte_BE(uint8_t *b, double v) { cast_int64_to_7_byte_BE(b, cast_real64_to_fix56(v)); }
//id cast_real64_to_fixed_to_8_byte_BE(uint8_t *b, double v) { cast_int64_to_8_byte_BE(b, cast_real64_to_fix64(v)); }


//============================================================================================================

void cast_real64_to_ufixed_to_1_byte_LE(uint8_t *b, double v) {  cast_uint8_to_1_byte_LE(b,  cast_real64_to_ufix8(v)); }
void cast_real64_to_ufixed_to_2_byte_LE(uint8_t *b, double v) { cast_uint16_to_2_byte_LE(b, cast_real64_to_ufix16(v)); }
void cast_real64_to_ufixed_to_3_byte_LE(uint8_t *b, double v) { cast_uint32_to_3_byte_LE(b, cast_real64_to_ufix24(v)); }
void cast_real64_to_ufixed_to_4_byte_LE(uint8_t *b, double v) { cast_uint32_to_4_byte_LE(b, cast_real64_to_ufix32(v)); }
void cast_real64_to_ufixed_to_5_byte_LE(uint8_t *b, double v) { cast_uint64_to_5_byte_LE(b, cast_real64_to_ufix40(v)); }
void cast_real64_to_ufixed_to_6_byte_LE(uint8_t *b, double v) { cast_uint64_to_6_byte_LE(b, cast_real64_to_ufix48(v)); }
//id cast_real64_to_ufixed_to_7_byte_LE(uint8_t *b, double v) { cast_uint64_to_7_byte_LE(b, cast_real64_to_ufix56(v)); }
//id cast_real64_to_ufixed_to_8_byte_LE(uint8_t *b, double v) { cast_uint64_to_8_byte_LE(b, cast_real64_to_ufix64(v)); }


//============================================================================================================

void cast_real64_to_ufixed_to_1_byte_BE(uint8_t *b, double v) {  cast_uint8_to_1_byte_BE(b,  cast_real64_to_ufix8(v)); }
void cast_real64_to_ufixed_to_2_byte_BE(uint8_t *b, double v) { cast_uint16_to_2_byte_BE(b, cast_real64_to_ufix16(v)); }
//id cast_real64_to_ufixed_to_3_byte_BE(uint8_t *b, double v) { cast_uint32_to_3_byte_BE(b, cast_real64_to_ufix24(v)); }
void cast_real64_to_ufixed_to_4_byte_BE(uint8_t *b, double v) { cast_uint32_to_4_byte_BE(b, cast_real64_to_ufix32(v)); }
//id cast_real64_to_ufixed_to_5_byte_BE(uint8_t *b, double v) { cast_uint64_to_5_byte_BE(b, cast_real64_to_ufix40(v)); }
//id cast_real64_to_ufixed_to_6_byte_BE(uint8_t *b, double v) { cast_uint64_to_6_byte_BE(b, cast_real64_to_ufix48(v)); }
//id cast_real64_to_ufixed_to_7_byte_BE(uint8_t *b, double v) { cast_uint64_to_7_byte_BE(b, cast_real64_to_ufix56(v)); }
//id cast_real64_to_ufixed_to_8_byte_BE(uint8_t *b, double v) { cast_uint64_to_8_byte_BE(b, cast_real64_to_ufix64(v)); }


//============================================================================================================
//! \brief Converts.
//!
//! \todo Investigate optimal code.

uint32_t incr_1_byte_LE_to_uint32(const uint8_t *b, uint32_t z)
{
//	uint8_t lsb = *b - z;
//	return z - lsb;

	uint32_t x, y;

	x = *b;
	y = z & 0x000000FF; // low part
	z = z & 0xFFFFFF00; // high part
	if (y > x)
		return (z + x + 0x100);
	else
		return (z + x);
}


//============================================================================================================
//! \brief Converts.
//!
//! \todo Investigate optimal code.

uint32_t incr_2_byte_LE_to_uint32(const uint8_t *b, uint32_t z)
{
//	uint16_t lsb = cast_2_byte_LE_to_uint16(b) - z;
//	return z - lsb;

	uint32_t x, y;

	x = cast_2_byte_LE_to_uint16(b);
	y = z & 0x0000FFFF; // low part
	z = z & 0xFFFF0000; // high part
	if (y > x)
		return (z + x + 0x10000);
	else
		return (z + x);
}


//============================================================================================================
//! \brief Converts.
//!
//! \todo Investigate optimal code.

uint64_t incr_2_byte_LE_to_uint64(const uint8_t *b, uint64_t z)
{
//	uint16_t lsb = cast_2_byte_LE_to_uint16(b) - z;
//	return z - lsb;

	uint64_t x, y;

	x = cast_2_byte_LE_to_uint16(b);
	y = z & UINT64_C(0x000000000000FFFF); // low part
	z = z & UINT64_C(0xFFFFFFFFFFFF0000); // high part
	if (y > x)
		return (z + x + 0x10000);
	else
		return (z + x);
}


//============================================================================================================
//! \brief Swap byte order.

uint16_t swap_uint16_byte_order(uint16_t v)
{
	return  (v << 8) |
	        (v >> 8);
}


//============================================================================================================
//! \brief Swap byte order.

uint32_t swap_uint32_byte_order(uint32_t v)
{
	return  (v << 24)                         |
           ((v <<  8) & UINT32_C(0x00FF0000)) |
           ((v >>  8) & UINT32_C(0x0000FF00)) |
            (v >> 24);
}


//============================================================================================================
//! \brief Swap byte order.

uint64_t swap_uint64_byte_order(uint64_t v)
{
	return  (v << 56)                                 |
	       ((v << 40) & UINT64_C(0x00FF000000000000)) |
	       ((v << 24) & UINT64_C(0x0000FF0000000000)) |
	       ((v <<  8) & UINT64_C(0x000000FF00000000)) |
	       ((v >>  8) & UINT64_C(0x00000000FF000000)) |
	       ((v >> 24) & UINT64_C(0x0000000000FF0000)) |
	       ((v >> 40) & UINT64_C(0x000000000000FF00)) |
	        (v >> 56);
}


//============================================================================================================
//! \brief Cast to network byte order assuming little endian host.

uint16_t cast_uint16_to_network_byte_order(uint16_t v)
{
	return swap_uint16_byte_order(v);
}


//============================================================================================================
//! \brief Cast to network byte order assuming little endian host.

uint32_t cast_uint32_to_network_byte_order(uint32_t v)
{
	return swap_uint32_byte_order(v);
}


//============================================================================================================
//! \brief Cast to network byte order assuming little endian host.

uint64_t cast_uint64_to_network_byte_order(uint64_t v)
{
	return swap_uint64_byte_order(v);
}

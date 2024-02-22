//============================================================================================================
//!
//! The software is protected by copyright of Oxford Technical Solutions.
//! Copyright (C) 2018 Oxford Technical Solutions - http://www.oxts.com
//!
//! Redistribution and use in source and binary forms, with or without modification, are only permitted with
//! the specific prior written permission of Oxford Technical Solutions.
//!
//! LastChangedDate: 2018-11-30 15:31:49 +0000 (Fri, 30 Nov 2018) 
//! LastChangedRevision: 27365 
//! LastChangedBy: kpalamartchouk 
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
#include "oxts/gal-c/Lib_Compiler.h" /*PRQA S 0857 # ISO:C90 */ /*PRQA S 0816 # ISO:C90*/
#include "oxts/gal-c/BasicCasts.h" /*PRQA S 0816 # ISO:C90*/

typedef union 
{ /*PRQA S 0750 # Use of union. */ 
	double_t a; 
	uint8_t c[8];
} DBL_8BYTES;

//============================================================================================================

double_t cast_8_byte_LE_to_real64(const uint8_t *b)
{
	volatile DBL_8BYTES u; /* PRQA S 0759 # Use of union. */
	u.c[0] = b[0];
	u.c[1] = b[1];
	u.c[2] = b[2];
	u.c[3] = b[3];
	u.c[4] = b[4];
	u.c[5] = b[5];
	u.c[6] = b[6];
	u.c[7] = b[7];
	return u.a;

}

void cast_double_to_8_byte_LE(uint8_t *b, const double_t v)
{
	volatile DBL_8BYTES u; /* PRQA S 0759 # Use of union. */
	u.a = v;
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

uint32_t cast_4_byte_LE_to_uint32(const uint8_t *b)
{
	uint32_t r = b[0] +
		(((uint32_t)b[1]) << 8U) +
		(((uint32_t)b[2]) << 16U) +
		(((uint32_t)b[3]) << 24U);
	return r;
}

//============================================================================================================

void cast_uint16_to_2_byte_LE(uint8_t *b, const uint16_t v)
{
	b[0] = (uint8_t)(v & 0xFFU);
	b[1] = (uint8_t)(((uint16_t)(v & 0xFF00U)) >> 8U);
}

//============================================================================================================

uint8_t cast_1_byte_LE_to_uint8(const uint8_t *b)
{
	return b[0];
}

void cast_uint8_to_1_byte_LE(uint8_t *b, const uint8_t v)
{
	b[0] = v;
}

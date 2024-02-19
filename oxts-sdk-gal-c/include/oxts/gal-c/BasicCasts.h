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

#include "oxts/gal-c/BasicTypes.h" /*PRQA S 0816 # ISO:C90*/


//============================================================================================================
//! \name Little endian bytes to real
//!
//! Convert a little endian X-byte representation of a real to a basic Y-bit real type.

double_t cast_8_byte_LE_to_real64(const uint8_t *b);


//============================================================================================================
//! \name Real to little endian bytes
//!
//! Convert a little endian X-byte representation of a real to a basic Y-bit real type.

void cast_double_to_8_byte_LE(uint8_t *b, const double_t v);


//============================================================================================================
//! \name Unsigned little endian bytes to integer
//!
//! Convert a little endian X-byte representation of an unsigned integer to a basic unsigned Y-bit integer type.

uint8_t  cast_1_byte_LE_to_uint8 (const uint8_t *b);
uint32_t cast_4_byte_LE_to_uint32(const uint8_t* b);


//============================================================================================================
//! \name Unsigned integer to little endian bytes
//!
//! Convert a basic unsigned Y-bit integer type to a little endian X-byte representation of an unsigned integer.

void  cast_uint8_to_1_byte_LE(uint8_t *b,  const uint8_t v);
void cast_uint16_to_2_byte_LE(uint8_t *b, const uint16_t v); /*PRQA S 0776 # Assume compiler does not have 6-character limit on unique identifiers. */


#endif

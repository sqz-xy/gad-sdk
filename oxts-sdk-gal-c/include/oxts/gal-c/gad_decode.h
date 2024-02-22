//============================================================================================================
//!
//! The software is protected by copyright of Oxford Technical Solutions.
//! Copyright (C) 2020 Oxford Technical Solutions - http://www.oxts.com
//!
//! Redistribution and use in source and binary forms, with or without modification, are only permitted with
//! the specific prior written permission of Oxford Technical Solutions.
//!
//! LastChangedDate: 2019-10-10 17:01:45 +0100 (Thu, 10 Oct 2019)
//! LastChangedRevision: 28591
//! LastChangedBy: smccarthy
//!
//! \file decode_genaid.h
//!
//! \brief Header file for decode_genaid.c
//!
//============================================================================================================


#ifndef GNS__DECODE_GENAID_H
#define GNS__DECODE_GENAID_H

#include "oxts/gal-c/gad_defines.h"
#include "oxts/gal-c/gad_struct.h"

//============================================================================================================
//! \brief A private data structure for the generic Aiding Decoder Memory.

extern int32_t update_genaid_from_bin(GEN_AIDING_DATA* gad, const uint8_t* data, const size_t len);
extern int32_t genaid_basic_checks_bin(const uint8_t* data, const size_t len); /*PRQA S 0776 # Assume compiler has greater than 6-character limit for identifier uniqueness. */


#endif

#ifndef GAD_ENCODING
#define GAD_ENCODING

//============================================================================================================
//!
//! The software is protected by copyright of Oxford Technical Solutions.
//! Copyright (C) 2020 Oxford Technical Solutions - http://www.oxts.com
//!
//! Redistribution and use in source and binary forms, with or without modification, are only permitted with
//! the specific prior written permission of Oxford Technical Solutions.
//!
//! LastChangedDate: 2019-10-07 15:14:42 +0100 (Mon, 07 Oct 2019)
//! LastChangedRevision: 28566
//! LastChangedBy: smccarthy
//!
//! \file gad_encode.h
//!
//! \brief Header file for gad_encode.c
//!  
//============================================================================================================

#include "oxts/gal-c/gad_defines.h"
#include "oxts/gal-c/gad_struct.h"

/*
    This is responsible for encoding the generic aiding data structure (GENERIC_AIDING_DATA) into a buffer, has safety which stops
    the program execution if the next packet section written to the buffer is larger than the buffer max size

    Arguments:
    * gad - the generic aiding data structure, this holds the data which will be used when encoding
    * buffer - this is a pointer to the start of a buffer which will hold all the encoded data
    * size_of_buffer - size of the buffer which is being written to
    * packet_size - the amount of bytes of the buffer which have been populated by the payload
*/
extern int32_t encode_gen_aid(const GEN_AIDING_DATA* gad, uint8_t* const buffer, const size_t buffer_size, size_t* packet_size);

#endif

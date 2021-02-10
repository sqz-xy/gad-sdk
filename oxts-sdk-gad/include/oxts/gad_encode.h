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
//! $LastChangedDate: 2019-10-07 15:14:42 +0100 (Mon, 07 Oct 2019) $
//! $LastChangedRevision: 28566 $
//! $LastChangedBy: smccarthy $
//!
//! \file gad_encode.h
//!
//! \brief Header file for gad_encode.c
//!  
//============================================================================================================

#include "gad_defines.h"
#include "gad_struct.h"

#ifdef __cplusplus
extern "C"
{
#endif
   /*
      associated the file handler to the gad engine file handler and prints the header to the csv gad file

      params:
      * file_ptr - pointer to file you're writing csv to 
   */
   int init_gad_output_file(FILE* file_ptr);


   /*
     writes the generic aiding data in data to file at file_ptr

     params:
     * file_ptr - pointer to file you're writing csv to 
     * data - generic aiding data being written
   */
   int write_gad_to_csv(FILE* file_ptr, GEN_AIDING_DATA* data);



   /*
      This is responsible for encoding the generic aiding data structure (GENERIC_AIDING_DATA) into a buffer, has safety which stops
      the program execution if the next packet section written to the buffer is larger than the buffer max size

      Arguments:
      * gad - the generic aiding data structure, this holds the data which will be used when encoding
      * buffer - this is a pointer to the start of a buffer which will hold all the encoded data
      * size_of_buffer - size of the buffer which is being written to
      * payload_size - the amount of byte sof the buffer which have been populated by the payload
   */
   int encode_gen_aid(GEN_AIDING_DATA* gad, unsigned char* buffer, size_t buffer_size, size_t* packet_size);

   /*
      Encodes an instance of the GEN_3D struct to binary and places it in a buffer

      params:
      * field - this is the inbound data, it is the struct which holds the data
      * data - buffer the data si copied into
      * offset - this is the offset into the data buffer the data is being written to.
   */
   int encode_gen_3d(GEN_3D field, unsigned char* data, size_t* offset, size_t buffer_size);
   
    /*
      Encodes the variance of an instance of the GEN_3D struct to binary and places it in the buffer.
	  The variance is different to the rest of the struct since it has a variable size when encoded to binary.

      params:
      * field - this is the inbound data, it is the struct which holds the data
      * data - buffer the data si copied into
      * offset - this is the offset into the data buffer the data is being written to.
   */
   int encode_gen_3d_var(GEN_3D field, unsigned char *data, size_t *offset, size_t buffer_size);
   
    /*
      Basic check function used before encoding a piece of data to ensure we do not overrun the buffer.

      params:
      * buffer_size - amount of memory (bytes) allocated to the buffer.
      * expected_data_size - amount of memory which will be required to encode the packet + the additional piece.
   */
   int buffer_overrun_chk(size_t buffer_size, size_t expected_data_size);

#ifdef __cplusplus
}
#endif

#endif

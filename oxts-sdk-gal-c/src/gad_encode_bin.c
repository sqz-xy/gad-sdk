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
//! \file gad_encode.c
//!
//! \brief Functions for managing Generic Aiding information.
//!
//============================================================================================================


#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "oxts/gal-c/BasicCasts.h" /*PRQA S 0857 # ISO:C90 */ /*PRQA S 0816 # ISO:C90*/
#include "oxts/gal-c/gad_encode_bin.h" /*PRQA S 0816 # ISO:C90*/
#include "oxts/gal-c/oxts_pointers.h" /*PRQA S 0816 # ISO:C90*/

#ifdef OXTS_DEBUG
#define OXTS_GNSS_DEBUG
#endif

#ifdef OXTS_GNSS_DEBUG
// define EXTRA_CHECKS to get additional checks on passed parameters
#define EXTRA_CHECKS
// define DEBUG_INFO provides additional debugging information while running
#define DEBUG_INFO
#endif // OXTS_GNSS_DEBUG

////////////////////////////////
// Forward declarations
////////////////////////////////

/*
    Encodes an instance of the GEN_3D struct to binary and places it in a buffer

    params:
    * field - this is the inbound data, it is the struct which holds the data
    * data - buffer the data is copied into
    * offset - this is the offset into the data buffer the data is being written to.
*/
static int32_t encode_gen_3d(GEN_3D field, uint8_t* const data, size_t* offset, const size_t buffer_size); /*PRQA S 0776 # Assume compiler has greater than 6-character limit for identifier uniqueness. */
   
/*
    Encodes the variance of an instance of the GEN_3D struct to binary and places it in the buffer.
	The variance is different to the rest of the struct since it has a variable size when encoded to binary.

    params:
    * field - this is the inbound data, it is the struct which holds the data
    * data - buffer the data si copied into
    * offset - this is the offset into the data buffer the data is being written to.
*/
static int32_t encode_gen_3d_var(GEN_3D field, uint8_t * const data, size_t *offset, const size_t buffer_size); /*PRQA S 0776 # Assume compiler has greater than 6-character limit for identifier uniqueness. */
   
/*
    Basic check function used before encoding a piece of data to ensure we do not overrun the buffer.

    params:
    * buffer_size - amount of memory (bytes) allocated to the buffer.
    * expected_data_size - amount of memory which will be required to encode the packet + the additional piece.
*/
static int32_t buffer_overrun_chk(const size_t buffer_size, const size_t expected_data_size);

/////////////////////////////////////////////////

int32_t encode_gen_aid(const GEN_AIDING_DATA* gad, uint8_t* const buffer, const size_t buffer_size, size_t* packet_size) /*PRQA S 1503 # function is used in gad_test.cpp. */ /*PRQA S 1505  # function is used in gad_test.cpp.*/
{
   /*
      holds return errors for each step. 0 means no error occured and
      execution can continue, sets a pointer to the last position of the buffer
   */
   int32_t error_code = 0;

   /*
      Sets two pointers:
      h - the start of the data buffer which will contain the header of the GA packet
      b - part way into the buffer which is the start of the payload data of the GA packet

      Sets two offset trackers:
      h_offset - tracks offset from pointer h
      b_offset - tracks offset from pointer b
   */
   uint8_t* const h = buffer;
   int32_t h_offset = 0;

   uint8_t* b = get_uint8_from_uint8(h, (int32_t)GEN_AID_HEADER_MIN_SIZE);
   size_t b_offset = 0;
   
   /*
      The bitmask collects the information which will be filled in as the rest
      of the payload is formed, it is initialised to 0 so if the specific if
      statement isn't reached, the bit representing each field is left as 0.
   */
   uint16_t bitmask = 0U;
   
   /*
      The available payload space is the difference between the size of the
      buffer and the size of the packet header.
   */
   const size_t available_payload_space = buffer_size - GEN_AID_HEADER_MIN_SIZE;

   /*
      Populate the header portion of the data buffer with the version and type.

      TODO: stop encoding if the gad->type is > 15 as this starts writing to first 4 bits of the byte
   */
   const uint8_t ver_type = (uint8_t)gad->type;
   cast_uint8_to_1_byte_LE(get_uint8_from_uint8(h, h_offset), ver_type);
   h_offset++;

   /*
      This sets the first xDEV_ACQ.. bytes to 0 and advances the
      offset into the payload by xDEV_ACQ. This is safety incase
      the user doesn't pass a pointer to a zero'ed buffer.
   */
   if (buffer_overrun_chk(available_payload_space, GEN_AID_HEADER_MIN_SIZE + b_offset + 8U) != 0) {}
   else
   {
	b_offset += XDEV_ACQUISTION_TIMESTAMP_SIZE;
      (void)memset((void *)b, 0, b_offset);
   }

   /*
      Encode stream ID
   */
   if (buffer_overrun_chk(available_payload_space, GEN_AID_HEADER_MIN_SIZE + b_offset) != 0) {}
   else
   {
      cast_uint8_to_1_byte_LE(get_uint8_from_uint8(b, (int32_t)b_offset), gad->stream_id);
      b_offset++;
   }

   /*
      This encodes the data from the struct into the buffer for each component
      of the generic aiding struct
   */

   if (gad->val_valid != 0U)
   {
       error_code = encode_gen_3d(gad->val, b, &b_offset, available_payload_space);
       if (error_code == 0)
       {
           bitmask |= ValueBit;
       }
   }
   if ((error_code == 0) && (gad->time_valid != 0U))
   {
       error_code = encode_gen_3d(gad->time, b, &b_offset, available_payload_space);
       if (error_code == 0)
       {
           bitmask |= TimeBit;
       }
   }
   if ((error_code == 0) && (gad->loc_valid != 0U))
   {
       error_code = encode_gen_3d(gad->loc, b, &b_offset, available_payload_space);
       if (error_code == 0)
       {
           bitmask |= LocationBit;
       }
   }
   if ((error_code == 0) && (gad->res1_valid != 0U))
   {
       error_code = encode_gen_3d(gad->res1, b, &b_offset, available_payload_space);
       if (error_code == 0)
       {
           bitmask |= Res1Bit;
       }
   }
   if ((error_code == 0) && (gad->res2_valid != 0U))
   {
       error_code = encode_gen_3d(gad->res2, b, &b_offset, available_payload_space);
       if (error_code == 0)
       {
           bitmask |= Res2Bit;
       }
   }
   cast_uint16_to_2_byte_LE(get_uint8_from_uint8(h, h_offset), bitmask);
   h_offset += (int32_t)sizeof(int16_t); // move buffer past two reserved bytes (remove when we use these bytes) 
   *packet_size = ((size_t)h_offset) + 1U + b_offset; // this version reflects where the offsets ended up, could be a better method for debugging?

   return error_code;
}

//============================================================================================================

static int32_t encode_gen_3d(GEN_3D field, uint8_t* const data, size_t* offset, const size_t buffer_size)
{
   int32_t ec = 0;
   const size_t dims = 3;

   if (buffer_overrun_chk(buffer_size, *offset + (dims * sizeof(double_t)) + 3U) != 0)		// this checks that there is enough space for all fixed-size elements of GEN_3D
   {
       ec = -1;
   }
   else
   {
      size_t d;
      cast_uint8_to_1_byte_LE(get_uint8_from_uint8(data, (int32_t)*offset), field.mode);
      (*offset)++;
      cast_uint8_to_1_byte_LE(get_uint8_from_uint8(data, (int32_t)*offset), field.x_type);
      (*offset)++;
      if (field.mode == 0U)
      {
         for (d = 0; d < dims; ++d)
         {
            cast_double_to_8_byte_LE(get_uint8_from_uint8(data, (int32_t)*offset), field.x[d]);
            *offset += sizeof(double_t);
         }
         cast_uint8_to_1_byte_LE(get_uint8_from_uint8(data, (int32_t)*offset), field.v_type);
         (*offset)++;
         ec = encode_gen_3d_var(field, data, offset, buffer_size);
      }
   }

   return ec;
}

//============================================================================================================
//! \brief -- Encodes the variance of an instance of the GEN_3D struct to binary   

static int32_t encode_gen_3d_var(GEN_3D field, uint8_t* const data, size_t* offset, const size_t buffer_size)
{
   uint32_t d;
   uint32_t var_size;
   const uint32_t dims = 3;
   int32_t ec = 0;

   switch (field.v_type)
   {
   case GEN_VAR_VOID:		// If the variance is void, there is nothing to encode.
   {
       break;
   }
   case GEN_VAR_SINGLE:
   {
       if (buffer_overrun_chk(buffer_size, *offset + sizeof(double_t)) != 0)
       {
           ec = -1;
       }
       else
       {
           cast_double_to_8_byte_LE(get_uint8_from_uint8(data, (int32_t)*offset), field.v[0]);
           *offset += sizeof(double_t);
       }
       break;
   }
   case GEN_VAR_DIAG:		// Diagonal of a 3x3 matrix => 3 values
   {
       var_size = dims;
       if (buffer_overrun_chk(buffer_size, *offset + (var_size * sizeof(double_t))) != 0)
       {
           ec = -1;
       }
       else
       {
           for (d = 0; d < var_size; ++d)
           {
               cast_double_to_8_byte_LE(get_uint8_from_uint8(data, (int32_t)*offset), field.v[d]);
               *offset += sizeof(double_t);
           }
       }
       break;
   }
   case GEN_VAR_HMAT:			// Full symmetric 3x3 matrix can be encoded as 6 values
   {
       var_size = dims * (dims + 1U) / 2U;
       if (buffer_overrun_chk(buffer_size, *offset + (var_size * sizeof(double_t))) != 0)
       {
           ec = -1;
       }
       else
       {
           for (d = 0; d < var_size; ++d)
           {
               cast_double_to_8_byte_LE(get_uint8_from_uint8(data, (int32_t)*offset), field.v[d]);
               *offset += sizeof(double_t);
           }
       }
       break;
   }
   default:
   {
       ec = -1;
       break;
   }
   }

   return ec;
}

//============================================================================================================
//! \brief -- basic check function, used to ensure we do not overrun the buffer

static int32_t buffer_overrun_chk(const size_t buffer_size, const size_t expected_data_size)
{
    int32_t ec;
   if (buffer_size > (expected_data_size - 1U)) { ec = 0; }
   else
   {
#ifdef OXTS_ENABLE_STDIO
      printf("Not enough space in the buffer to hold all data, packet is at least: %ld bytes longer than the allocated buffer space \n",
         (int32_t)(expected_data_size - buffer_size));
#endif
      ec = -1;
   }
   return ec;
}

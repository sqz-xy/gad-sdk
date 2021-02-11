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
//! \file gad_encode.c
//!
//! \brief Functions for managing Generic Aiding information.
//!
//============================================================================================================


#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

#include "oxts/common/errors.h"
#include "oxts/common/BasicCasts.h"

#include "oxts/gal-c/gad_encode.h"
#include "oxts/gal-c/gad_defines.h"
#include "oxts/gal-c/gad_struct.h"

#if OXTS_EXE_PP
#include "FileUtils.h"
#endif

#ifdef OXTS_DEBUG
#define OXTS_GNSS_DEBUG
#endif

#ifdef OXTS_GNSS_DEBUG
// define EXTRA_CHECKS to get additional checks on passed parameters
#define EXTRA_CHECKS
// define DEBUG_INFO provides additional debugging information while running
#define DEBUG_INFO
#endif // OXTS_GNSS_DEBUG

#ifdef __cplusplus
extern "C"
{
#endif

   //============================================================================================================
   int print_gen_3d_header(FILE* file_ptr)
   {
#ifdef EXTRA_CHECKS
      if (file_ptr == NULL)
      {
         oxts_error(1, "NULL encountered instead of pointer to file");
         return -1;
      }
#endif

      int i = 0;
      if (fprintf(file_ptr, "mode,x_type,x[0],x[1],x[2],v_type,v[0],v[1],v[2],v[3],v[4],v[5],") < 0)
         i = -1;

      return i;
   }



   int init_gad_output_file(FILE* gad_engine_file_ptr)
   {
#ifdef EXTRA_CHECKS
      if (gad_engine_file_ptr == NULL)
      {
         oxts_error(1, "NULL encountered instead of pointer to file");
         return -1;
      }
#endif
      int i = 0;

      // write generic aiding struct header to csv file
      if (i);
      else if ((fprintf(gad_engine_file_ptr, "#ver,type,stream ID,") < 0))
         i = -1;
      else if (fprintf(gad_engine_file_ptr, "val_valid,") < 0)
         i = -1;
      else if ((i = print_gen_3d_header(gad_engine_file_ptr)));
      else if (fprintf(gad_engine_file_ptr, "time_valid,") < 0)
         i = -1;
      else if ((i = print_gen_3d_header(gad_engine_file_ptr)));
      else if (fprintf(gad_engine_file_ptr, "acq_valid,") < 0)
         i = -1;
      else if (fprintf(gad_engine_file_ptr, "acq_time,") < 0)
         i = -1;
      else if (fprintf(gad_engine_file_ptr, "loc_valid,") < 0)
         i = -1;
      else if ((i = print_gen_3d_header(gad_engine_file_ptr)));
      else if (fprintf(gad_engine_file_ptr, "res1_valid,") < 0)
         i = -1;
      else if ((i = print_gen_3d_header(gad_engine_file_ptr)));
      else if (fprintf(gad_engine_file_ptr, "res2_valid,") < 0)
         i = -1;
      else if ((i = print_gen_3d_header(gad_engine_file_ptr)));
      else if (fprintf(gad_engine_file_ptr, "\n") < 0);
      else if (fflush(gad_engine_file_ptr) != 0)
         i = -1;

      return i;
   }

   //============================================================================================================
   //! \brief writes the contents of the GEN_3D to csv

   int write_gen_3d(FILE* file_ptr, GEN_3D* gen_3d_data)
   {
      int i = 0;

      if (fprintf(file_ptr, "%d,%d,%.12f,%.12f,%.12f,%d,%.12f,%.12f,%.12f,%.12f,%.12f,%.12f,",
         gen_3d_data->mode,
         gen_3d_data->x_type,
         gen_3d_data->x[0], gen_3d_data->x[1], gen_3d_data->x[2],
         gen_3d_data->v_type,
         gen_3d_data->v[0], gen_3d_data->v[1], gen_3d_data->v[2], gen_3d_data->v[3], gen_3d_data->v[4], gen_3d_data->v[5])
         < 0)
      {
         i = -1;
      }
      return i;
   }


   /*

   */
   int write_gad_to_csv(FILE* file_ptr, GEN_AIDING_DATA* data)
   {
#ifdef EXTRA_CHECKS
      if (file_ptr == NULL)
      {
         oxts_error(1, "NULL encountered instead of pointer to file");
         return -1;
      }
      if (data == NULL)
      {
         oxts_error(1, "NULL encountered instead of pointer to generic aiding structure");
         return -1;
      }
#endif

      int i = 0; // 0 means no errors encountered

      // fprintf() returns a negative number if it fails, no guarantee if it fails
      // the negative number is -1 so set i = -1 manually

      if (i);
      // write ver
      else if (fprintf(file_ptr, "%d,", 0) < 0)
         i = -1;
      // write type
      else if (fprintf(file_ptr, "%d,", data->type) < 0)
         i = -1;

      // write stream ID
      if (fprintf(file_ptr, "%d,", data->stream_id) < 0)
         i = -1;

      // write val
      if (fprintf(file_ptr, "%d,", data->val_valid) < 0)
         i = -1;

      if (!i && data->val_valid)
         i = write_gen_3d(file_ptr, &data->val);
      else if (!i && !data->val_valid)
         i = (fprintf(file_ptr, ",,,,,,,,,,,,") < 0) ? -1 : 0;

      // write time
      if (fprintf(file_ptr, "%d,", data->time_valid) < 0)
         i = -1;

      if (!i)// && data->time_valid)
         i = write_gen_3d(file_ptr, &data->time);
      else if (!i && !data->time_valid)
         i = (fprintf(file_ptr, ",,,,,,,,,,,,") < 0) ? -1 : 0;

      // write acq_time
      if (fprintf(file_ptr, "%d,", data->acq_valid) < 0)
         i = -1;

      if (!i && data->acq_valid)
         i = (fprintf(file_ptr, "%u,", data->acq) < 0);
      else if (!i && !data->acq_valid)
         i = (fprintf(file_ptr, ",") < 0) ? -1 : 0;

      // write loc
      if (fprintf(file_ptr, "%d,", data->loc_valid) < 0)
         i = -1;

      if (!i && data->loc_valid)
         i = write_gen_3d(file_ptr, &data->loc);
      else if (!i && !data->loc_valid)
         i = (fprintf(file_ptr, ",,,,,,,,,,,,") < 0) ? -1 : 0;


      // write res1
      if (fprintf(file_ptr, "%d,", data->res1_valid) < 0)
         i = -1;

      if (!i && data->res1_valid)
         i = write_gen_3d(file_ptr, &data->res1);
      else if (!i && !data->res1_valid)
         i = (fprintf(file_ptr, ",,,,,,,,,,,,") < 0) ? -1 : 0;


      // write res2
      if (fprintf(file_ptr, "%d,", data->res2_valid) < 0)
         i = -1;

      if (!i && data->res2_valid)
         i = write_gen_3d(file_ptr, &data->res2);
      else if (!i && !data->res2_valid)
         i = (fprintf(file_ptr, ",,,,,,,,,,,,") < 0) ? -1 : 0;

      fprintf(file_ptr, "\n");
      fflush(file_ptr);

      return i;
   }


   int encode_gen_aid(GEN_AIDING_DATA* gad, unsigned char* buffer, size_t buffer_size, size_t* packet_size)
   {
      /*
         holds return errors for each step. 0 means no error occured and
         execution can continue, sets a pointer to the last position of the buffer
      */
      int error_code = 0;

      /*
         Sets two pointers:
         h - the start of the data buffer which will contain the header of the GA packet
         b - part way into the buffer which is the start of the payload data of the GA packet

         Sets two offset trackers:
         h_offset - tracks offset from pointer h
         b_offset - tracks offset from pointer b
      */
      unsigned char* h = buffer;
      size_t h_offset = 0;

      unsigned char* b = h + GEN_AID_HEADER_MIN_SIZE;
      size_t b_offset = 0;

      /*
         Populate the header portion of the data buffer with the version and type.

         TODO: stop encoding if the gad->type is > 15 as this starts writing to first 4 bits of the byte
      */
      uint8_t ver_type = (0 << 4) + gad->type;
      cast_uint8_to_1_byte_LE(h + h_offset++, ver_type);

      /*
         The bitmask collects the information which will be filled in as the rest
         of the payload is formed, it is initialised to 0 so if the specific if
         statement isn't reached, the bit representing each field is left as 0.
      */
      uint16_t bitmask = 0;

      /*
         The available payload space is the difference between the size of the
       buffer and the size of the packet header.
      */
      size_t available_payload_space = buffer_size - GEN_AID_HEADER_MIN_SIZE;

      /*
         This sets the first xDEV_ACQ.. bytes to 0 and advances the
         offset into the payload by xDEV_ACQ. This is safety incase
         the user doesn't pass a pointer to a zero'ed buffer.
      */
      if (error_code || buffer_overrun_chk(available_payload_space, GEN_AID_HEADER_MIN_SIZE + b_offset + 8));
      else
      {
         memset(b, 0, b_offset += XDEV_ACQUISTION_TIMESTAMP_SIZE);
      }

      /*
         Encode stream ID
      */
      if (error_code || buffer_overrun_chk(available_payload_space, GEN_AID_HEADER_MIN_SIZE + b_offset));
      else
      {
         cast_uint8_to_1_byte_LE(b + b_offset++, gad->stream_id);
      }

      /*
         This encodes the data from the struct into the buffer for each component
         of the generic aiding struct
      */

      if (!error_code && gad->val_valid && !(error_code = encode_gen_3d(gad->val, b, &b_offset, available_payload_space)))
      {
         bitmask |= ValueBit;
      }
      if (!error_code && gad->time_valid && !(error_code = encode_gen_3d(gad->time, b, &b_offset, available_payload_space)))
      {
         bitmask |= TimeBit;
      }
      if (!error_code && gad->loc_valid && !(error_code = encode_gen_3d(gad->loc, b, &b_offset, available_payload_space)))
      {
         bitmask |= LocationBit;
      }
      if (!error_code && gad->res1_valid && !(error_code = encode_gen_3d(gad->res1, b, &b_offset, available_payload_space)))
      {
         bitmask |= Res1Bit;
      }
      if (!error_code && gad->res2_valid && !(error_code = encode_gen_3d(gad->res2, b, &b_offset, available_payload_space)))
      {
         bitmask |= Res2Bit;
      }
      cast_int16_to_2_byte_LE((h + h_offset), bitmask);
      h_offset += sizeof(int16_t); // move buffer past two reserved bytes (remove when we use these bytes) 
      //*packet_size = GEN_AID_HEADER_MIN_SIZE + ((b + b_offset) - b);
      *packet_size = (h_offset + 1) + b_offset; // this version reflects where the offsets ended up, could be a better method for debugging?

      return error_code;
   }

   //============================================================================================================

   int encode_gen_3d(GEN_3D field, unsigned char* data, size_t* offset, size_t buffer_size)
   {
      int i = 0;
      int dims = 3;

      if (i || buffer_overrun_chk(buffer_size, *offset + (dims * sizeof(real64_t)) + 3))		// this checks that there is enough space for all fixed-size elements of GEN_3D
         i = -1;
      else
      {
         int d = 0;
         cast_int8_to_1_byte_LE((data + (*offset)++), field.mode);
         cast_int8_to_1_byte_LE((data + (*offset)++), field.x_type);

         if (field.mode == 0)
         {
            for (d = 0; d < dims; ++d)
            {
               cast_real64_to_8_byte_LE(data + *offset, field.x[d]);
               *offset += sizeof(real64_t);
            }
            cast_int8_to_1_byte_LE((data + (*offset)++), field.v_type);

            i = encode_gen_3d_var(field, data, offset, buffer_size);
         }
      }

      return i;
   }

   //============================================================================================================
   //! \brief -- Encodes the variance of an instance of the GEN_3D struct to binary   

   int encode_gen_3d_var(GEN_3D field, unsigned char* data, size_t* offset, size_t buffer_size)
   {
      int d = 0;
      int var_size = 0;
      int dims = 3;

      switch (field.v_type)
      {
      case GEN_VAR_VOID:		// If the variance is void, there is nothing to encode.
         break;
      case GEN_VAR_SINGLE:
         var_size = 1;
         if (buffer_overrun_chk(buffer_size, *offset + sizeof(real64_t)))
            return -1;
         else
         {
            cast_real64_to_8_byte_LE(data + *offset, field.v[0]);
            *offset += sizeof(real64_t);
         }
         break;
      case GEN_VAR_DIAG:		// Diagonal of a 3x3 matrix => 3 values
         var_size = dims;
         if (buffer_overrun_chk(buffer_size, *offset + (var_size * sizeof(real64_t))))
            return -1;
         else
         {
            for (d = 0; d < var_size; ++d)
            {
               cast_real64_to_8_byte_LE(data + *offset, field.v[d]);
               *offset += sizeof(real64_t);
            }
         }
         break;
      case GEN_VAR_HMAT:			// Full symmetric 3x3 matrix can be encoded as 6 values
         var_size = dims * (dims + 1) / 2;
         if (buffer_overrun_chk(buffer_size, *offset + (var_size * sizeof(real64_t))))
            return -1;
         else
         {
            for (d = 0; d < var_size; ++d)
            {
               cast_real64_to_8_byte_LE(data + *offset, field.v[d]);
               *offset += sizeof(real64_t);
            }
         }
         break;
      default:
         return -1;
      }

      return 0;
   }

   //============================================================================================================
   //! \brief -- basic check function, used to ensure we do not overrun the buffer

   int buffer_overrun_chk(size_t buffer_size, size_t expected_data_size)
   {
      if (buffer_size > expected_data_size - 1) { return 0; }
      else
      {
         printf("Not enough space in the buffer to hold all data, packet is at least: %ld bytes longer than the allocated buffer space \n",
            expected_data_size - buffer_size);

         return -1;
      }
   }



#ifdef __cplusplus
}
#endif

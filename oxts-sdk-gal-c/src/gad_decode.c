//============================================================================================================
//!
//! The software is protected by copyright of Oxford Technical Solutions.
//! Copyright (C) 2020 Oxford Technical Solutions - http://www.oxts.com
//!
//! Redistribution and use in source and binary forms, with or without modification, are only permitted with
//! the specific prior written permission of Oxford Technical Solutions.
//!
//! LastChangedDate: 2019-10-11 11:56:46 +0100 (Fri, 11 Oct 2019)
//! LastChangedRevision: 28597
//! LastChangedBy: smccarthy
//!
//! \file decode_genaid.c
//!
//! \brief Functions for extracting Generic Aiding information.
//!
//============================================================================================================

#include <stdlib.h>
#include <string.h>

#include "oxts/gal-c/gad_decode.h" /*PRQA S 0857 # ISO:C90 */ /*PRQA S 0816 # ISO:C90*/
#include "oxts/gal-c/errors.h" /*PRQA S 0816 # ISO:C90*/
#include "oxts/gal-c/BasicCasts.h" /*PRQA S 0816 # ISO:C90*/
#include "oxts/gal-c/oxts_pointers.h" /*PRQA S 0816 # ISO:C90*/


#ifdef OXTS_DEBUG
#define OXTS_GNSS_DEBUG
#endif

#ifdef OXTS_GNSS_DEBUG
// define EXTRA_CHECKS to get additional checks on passed parameters
#define EXTRA_CHECKS
// define DEBUG_INFO provides additional debugging information while running
#define DEBUG_INFO
#endif // OXTS_DEBUG

// Checks bitfield for indication of presence of data fields.
static uint8_t ValueFieldPresent(const uint8_t b) {
	return ((b) & (ValueBit));
}
static uint8_t  TimeFieldPresent(const uint8_t b) {
	return ((b) & (TimeBit));
}
static uint8_t  LocationFieldPresent(const uint8_t b) {
	return ((b) & (LocationBit));
}
static uint8_t  Res1Present(const uint8_t b) {
	return ((b) & (Res1Bit));
}
static uint8_t  Res2Present(const uint8_t b) {
	return ((b) & (Res2Bit));
}
static uint8_t  AdditionalBitmaskPresent(const uint8_t b) {
	return ((b) & (AdditionalBitmaskBit));
}

///////////////////////////////////////////////////////
// Forward declarations
///////////////////////////////////////////////////////
static int32_t decode_gen3d_bin(GEN_3D* field, const uint8_t* b, size_t* b_offset);
static int32_t decode_gen3d_var_bin(GEN_3D* field, const uint8_t* b, size_t* b_offset);  /*PRQA S 0776 # Assume compiler has greater than 6-character limit for identifier uniqueness. */
static int32_t decode_acq_timestamp_bin(uint32_t* acq_time, const uint8_t* b, size_t *b_offset); /*PRQA S 0776 # Assume compiler has greater than 6-character limit for identifier uniqueness. */

///////////////////////////////////////////////////////
// Generic Aiding parsing and decoding functions
///////////////////////////////////////////////////////

//============================================================================================================
//! \brief Decode a generic aiding binary packet

int32_t update_genaid_from_bin(GEN_AIDING_DATA *gad, const uint8_t *data, const size_t len) /*PRQA S 1503 */ /*PRQA S 1505  # function is used in gad_test.cpp, but is commented out.*/
{

	const uint8_t* h = data;
	const uint8_t *b = get_cuint8_from_cuint8(h, (int32_t)GEN_AID_HEADER_MIN_SIZE);
	int32_t ec = 0;
	size_t h_offset = 0;
	size_t b_offset_from_h = GEN_AID_HEADER_MIN_SIZE;		// This is b - h, to avoid pointer arithmetic later
	size_t b_offset = 0;
	uint8_t ver_type;

#ifdef EXTRA_CHECKS
	if (gad == NULL)
	{
		oxts_error(2, "NULL encountered instead of pointer to generic aiding data");
		return 2;
	}

#endif // EXTRA_CHECKS

	gad->type = (int8_t)GEN_VOID;
	gad->val_valid = 0;
	gad->time_valid = 0;
	gad->loc_valid = 0;
	gad->res1_valid = 0;
	gad->res2_valid = 0;
   gad->acq_valid = 0;

	ver_type = cast_1_byte_LE_to_uint8(h);

	// Check version is 0
   //! 15 generic aiding types too limiting? 7 or 8 bits more appropriate?
   //! e.g. 1 byte for version (4 bits reserved) and one byte for type entirely (1 bit reserved?)
	if ((ver_type & 0xF0U) != 0U) {
#ifdef oxts_warn
		oxts_warn(8, "Unrecognised generic aiding version");
#endif
		ec = -1;
	}
	else {
		// No need for ver_type & 0x0FU here, as we have already verified that ver_type & 0xF0U == 0.
		gad->type = (int8_t)(ver_type);
		if (gad->type >= ((int8_t)GEN_NUM))
		{
#ifdef oxts_warn
			oxts_warn(8, "Unrecognised generic aiding packet type.");
#endif
			ec = -1;
		}
		++h_offset;
	}
	// If we do not have the second byte of the gad header, do nothing
	if (h_offset >= (size_t)len) {
		ec = -1;
	}

   // If the additional bitmask is present, the header is 2 bytes longer than normal. Shift back the pointer to the payload
	if (ec != 0) {}
	else if (AdditionalBitmaskPresent(h[h_offset]) != 0U) {
		b = get_cuint8_from_cuint8(b, 2);
		b_offset_from_h += 2U;
	}
	else { ec = -1; }

	// Decode acquisition timestamp provided by xDEV
	if (ec != 0) {}
	else if (get_cuint8_value_from_cuint8(b, (int32_t)b_offset) == 0U)			// Check acquisition timestamp version -- when new versions are created, this can be extended with more cases -- ENUM?
	{
		if ((b_offset_from_h + b_offset + 8U) > len)     // checks that the offset is not greater than the length of the packet
		{
			ec = -1;
		}
		else 
		{
			ec = decode_acq_timestamp_bin(&(gad->acq), b, &b_offset);
			if (ec == 0)
			{
				gad->acq_valid = 1;
			}
		}
	}
	else
	{
		ec = -1;
	}

   if (ec == 0)
   {
	   gad->stream_id = cast_1_byte_LE_to_uint8(get_cuint8_from_cuint8(b, (int32_t)b_offset));
       b_offset++;
   }
   if (ec != 0) {}
	else if (ValueFieldPresent(get_cuint8_value_from_cuint8(h, (int32_t)h_offset)) != 0U)
   {
	   ec = decode_gen3d_bin(&(gad->val), b, &b_offset);
	   if (ec == 0)
	   {
		   gad->val_valid = 1;
	   }
		// b_offset is the new offset in the data packet after decoding the structure
		// If there was some corruption, b_offset might point outside the data
		// and if that is the case, we will drop this packet
	   if ((b_offset_from_h + b_offset) > len)
	   {
		   ec = -1;
	   }
	}
	else { ec = -1; }

   if (ec != 0) {}
	else if (TimeFieldPresent(get_cuint8_value_from_cuint8(h, (int32_t)h_offset)) != 0U)
	{
	   ec = decode_gen3d_bin(&(gad->time), b, &b_offset);
	   if (ec == 0)
	   {
		   gad->time_valid = 1;
	   }
		if ((b_offset_from_h + b_offset) > len)		// checks that the offset is not greater than the length of the packet
		{
			ec = -1;
		}
	}
	else { ec = -1; }

   if (ec != 0) {}
	else if (LocationFieldPresent(get_cuint8_value_from_cuint8(h, (int32_t)h_offset)) != 0U)
   {
	   ec = decode_gen3d_bin(&(gad->loc), b, &b_offset);
	   if (ec == 0)
	   {
		   gad->loc_valid = 1;
	   }
	   if ((b_offset_from_h + b_offset) > len)		// checks that the offset is not greater than the length of the packet
	   {
		   ec = -1;
	   }
	}
	else { ec = -1; }

	if (ec != 0) { }
	else if (Res1Present(get_cuint8_value_from_cuint8(h, (int32_t)h_offset)) != 0U)
	{
		ec = decode_gen3d_bin(&(gad->res1), b, &b_offset);
		if (ec == 0)
		{
			gad->res1_valid = 1;
		}
		if ((b_offset_from_h + b_offset) > len)		// checks that the offset is not greater than the length of the packet
		{
			ec = -1;
		}
	}
	else { ec = -1; }

	if (ec != 0) {}
	else if (Res2Present(get_cuint8_value_from_cuint8(h, (int32_t)h_offset)) != 0U)
	{
		ec = decode_gen3d_bin(&(gad->res2), b, &b_offset);
		if (ec == 0)
		{
			gad->res2_valid = 1;
		}
		if ((b_offset_from_h + b_offset) > len)		// checks that the offset is not greater than the length of the packet
		{
			ec = -1;
		}
	}
	else { ec = 0; }

	if ((b_offset + GEN_AID_HEADER_MIN_SIZE) > ((size_t)len))
	{
		ec = -1;
	}

   return ec;
}

//============================================================================================================
//! \brief Parse acquisition timestamp (xDEV PPS relative) data field from binary stream and place into a uint32_t

static int32_t decode_acq_timestamp_bin(uint32_t *acq_time, const uint8_t *b, size_t *b_offset)
{
   int32_t ec = 0;
   // 1st byte already been checked before calling this function
   (*b_offset)++;

   // Check timestamp type (2nd byte)
   if (get_cuint8_value_from_cuint8(b, (int32_t)*b_offset) == (uint8_t)TIME_PPS_RELATIVE)
   {
      (*b_offset) += 3U;									// Move past type byte (2), skip the reserved bytes (3,4)
      (*acq_time) = cast_4_byte_LE_to_uint32(get_cuint8_from_cuint8(b, (int32_t)(*b_offset))) * 1000U;			// x1000 to convert from microseconds to nanoseconds
   }
   /*
      It is not strictly an error for there to not be an aquisition timestamp if there is a valid external timestamp in the packet
   */
   else
   {
      (*b_offset) += 3U;
	  ec = 0;
   }
   
   (*b_offset) += sizeof(uint32_t);					// Advance offset past timestamp to allow decoding of the rest of the packet

   return ec;
}

//============================================================================================================
//! \brief Parse generic aiding data field from binary stream

static int32_t decode_gen3d_bin(GEN_3D *field, const uint8_t *b, size_t *b_offset) 
{
	int32_t ec;
	int32_t d;

	field->mode = cast_1_byte_LE_to_uint8(get_cuint8_from_cuint8(b, (int32_t)*b_offset));
	(*b_offset)++;
	field->x_type = cast_1_byte_LE_to_uint8(get_cuint8_from_cuint8(b, (int32_t)*b_offset));
	(*b_offset)++;

   // mode=0 -> a 3D-based structure will be decoded
   if (field->mode == 0U)
   {
      for (d = 0; d < 3; ++d)
      {
         field->x[d] = cast_8_byte_LE_to_real64(get_cuint8_from_cuint8(b, (int32_t)*b_offset));
         (*b_offset) += sizeof(double_t);
      }

      field->v_type = cast_1_byte_LE_to_uint8(get_cuint8_from_cuint8(b, (int32_t)*b_offset));
      (*b_offset)++;

	  ec = decode_gen3d_var_bin(field, b, b_offset);
   }
   // ID=1 to MAX_ID_GEN3D: symbolic link to a value defined in a configuration file, but the values are not transmitted in the data
   else if (field->mode < MAX_ID_GEN3D)
   {
	   ec = 0;
   }
   // ID higher or equal to MAX_ID_GEN3D: - not recognised, the format may be newer so we will return -1
   else
   {
	   ec = -1;
   }

	return ec;
}

static int32_t decode_gen3d_var_bin(GEN_3D *field, const uint8_t *b, size_t *b_offset)
{
	int32_t ec = 0;
	int32_t d;
	int32_t var_size;
	int32_t dims = 3;

	switch (field->v_type)
	{
	case GEN_VAR_VOID:		               // If the variance is void, there is nothing to encode.
	{
		var_size = 0;
		break;
	}
	case GEN_VAR_SINGLE:
	{
		var_size = 1;
		break;
	}
	case GEN_VAR_DIAG:		               // Diagonal of a 3x3 matrix => 3 values
	{
		var_size = dims;
		break;
	}
	case GEN_VAR_HMAT:			            // Full symmetric 3x3 matrix can be encoded as 6 values
	{
		var_size = (dims * (dims + 1)) / 2; 	/*PRQA S 3103 # ISO:C90 - assume ISO:C99 implementation of signed division. */	
		break;
	}
	default:
	{
		var_size = 0;
		break;
	}
	}

   for (d = 0; d < var_size; ++d)
	{
		field->v[d] = cast_8_byte_LE_to_real64(get_cuint8_from_cuint8(b, (int32_t) *b_offset));
		*b_offset += sizeof(double_t);
	}

	return ec;
}


//============================================================================================================
//! \brief Perform basic checks on the binary genaid packet before sending for acquisition timestamping
//!
//! Returns 0 on success, -1 if the format is not accepted

int32_t genaid_basic_checks_bin(const uint8_t *data, const size_t len) /*PRQA S 1503 */ /*PRQA S 1505  # function is used in gad_test.cpp, but is commented out.*/
{
	int32_t ec = 0;
	const uint8_t 		*h = 		data;
	size_t 				h_offset = 	0;
	uint8_t 			ver_type;

	if ((data == NULL) || (len < (GEN_AID_HEADER_MIN_SIZE + 8U)))
	{
		ec = -1;
	}
	else
	{
		// Check whether this is not an extended header
		h_offset++;
		if (AdditionalBitmaskPresent(get_cuint8_value_from_cuint8(h, (int32_t)h_offset)) != 0U) 
		{
			if (len < (GEN_AID_HEADER_MIN_SIZE + 8U + 2U))
			{
				ec = -1;
			}
		}
	}
	// By this time we have made sure that the data has enough size to contain the header (4 or 6 bytes) + acquisition time stamp (8 bytes)
	if (ec == 0)
	{
		// Decode version type
		ver_type = cast_1_byte_LE_to_uint8(h);
		ver_type = (ver_type & 0xF0U) >> 4;

		// Check version is 0
		if (ver_type != 0U)
		{
#ifdef oxts_warn
			oxts_warn(8, "Generic aiding version not supported");
#endif
			ec = -1;
		}
	}
	return ec;
}


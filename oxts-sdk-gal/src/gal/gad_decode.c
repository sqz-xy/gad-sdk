//============================================================================================================
//!
//! The software is protected by copyright of Oxford Technical Solutions.
//! Copyright (C) 2020 Oxford Technical Solutions - http://www.oxts.com
//!
//! Redistribution and use in source and binary forms, with or without modification, are only permitted with
//! the specific prior written permission of Oxford Technical Solutions.
//!
//! $LastChangedDate: 2019-10-11 11:56:46 +0100 (Fri, 11 Oct 2019) $
//! $LastChangedRevision: 28597 $
//! $LastChangedBy: smccarthy $
//!
//! \file decode_genaid.c
//!
//! \brief Functions for extracting Generic Aiding information.
//!
//============================================================================================================

#include <stdlib.h>
#include <string.h>

#include "oxts/gal/decode_genaid.h"

// #include "errors.h"
// #include "BasicCasts.h"
// #include "EnumHardware.h"


#ifdef OXTS_DEBUG
#define OXTS_GNSS_DEBUG
#endif

#ifdef OXTS_GNSS_DEBUG
// define EXTRA_CHECKS to get additional checks on passed parameters
#define EXTRA_CHECKS
// define DEBUG_INFO provides additional debugging information while running
#define DEBUG_INFO
//#define DEBUG_LOCK       // define DEBUG_LOCK to test heading lock
#endif // OXTS_DEBUG


//============================================================================================================
//! \brief A private data structure for the generic Aiding Decoder Memory.

#if OXTS_EXE_PP
typedef struct
{
   char           filename[MAX_FILENAME];       //!< where applicable
   FILE          *fp;                           //!< 
} DecoderMemoryGenAidCSV;
#endif

typedef struct
{
   unsigned char raw[MAX_GENAID_PKT_SIZE];
} DecoderMemoryGenAidBin;


#ifdef __cplusplus
extern "C" {
#endif


///////////////////////////////////////////////////////
// Generic Aiding parsing and decoding functions
///////////////////////////////////////////////////////

#if OXTS_EXE_PP

int skip_to_next_char(char** tokens, int* cur_t, int max_tokens)
{
   int i = 0;
   int not_found_char = 1;
   int i_t;

   if (i);
   // Check that we have not exceeded the known number of tokens.
   while (not_found_char && !i)
   {
      (*cur_t)++;
      if (!(*cur_t < (max_tokens - 1)))
      {
         i = -1;
         break;
      }
      not_found_char = (sscanf(tokens[*cur_t], "%d", &i_t) < 0) ? 1 : 0;
   }

   return i;
}



//============================================================================================================
//! \brief Parse validity tags. If field is invalid, skip through blank tokens
int validity_parse(GEN_BOOL* field_valid, char** tokens, int* cur_t, int max_tokens)
{

   if (field_valid == NULL)
      return -1;
   if (tokens == NULL)
      return -1;
   if (cur_t == NULL)
      return -1;

   int i = 0;
   int i_t = 0;
   if (i);
   // Check that we have not exceeded the known number of tokens.
   else if (*cur_t < (max_tokens - 1))
   {
      // checks if validity flag is missing
      if (sscanf(tokens[*cur_t], "%d", &i_t) != 1)    // returns 1 unless NULL.
      {
         //oxts_stdout("Generic aiding .gad data is missing a validity flag", NULL);
         i = -1;
      }
      else
      {
         *field_valid = i_t;
      }
      (*cur_t)++;
   }
   else
      return -1;
   return i;
}

//============================================================================================================
//! \brief Read in GAD from csv

int update_genaid_from_csv(GEN_AIDING_DATA *gad, unsigned char *data, int len)
{
   int i=0;
   char sep = ',';
   char *tokens[MAX_TOKENS];
   int num_tokens = 0;
   int i_t;
   int cur_token = 0;
   char *ptr;
   char *end_ptr;

#ifdef EXTRA_CHECKS
   if (gad == NULL)
   {
      oxts_error(2, "NULL encountered instead of pointer to generic aiding data");
      return 2;
   }
   if (data == NULL)
   {
      oxts_error(2, "NULL encountered instead of pointer to CSV data");
   }
#endif // EXTRA_CHECKS

   gad->type      = GEN_VOID;
   gad->val_valid = 0;
   gad->time_valid= 0;
   gad->loc_valid = 0;
   gad->res1_valid = 0;
   gad->res2_valid = 0;

   num_tokens = 0;
   ptr = (char*)data;
   end_ptr = (char*)data+len;

   // Comment -- this allows the first line to be ignored, and therefore used for headers or whatever takes your fancy.
   if (len>0 && (data[0]=='#' || data[0]=='%') )
      return -1;

   // Whilst we have not reached the end of the string and have not exceeded the maximum number of tokens,
   // search though the c string for the separator character. When we find one, we save a ptr 
   // to its position into the array of tokens and change the separator to a null character (\0)
   while ( (ptr <= end_ptr) && (num_tokens < MAX_TOKENS) )
   {
      tokens[num_tokens++] = ptr;
      if ((ptr = (char *)strchr((char *)ptr, (int)sep)) == NULL)
         break;
      else
         *(ptr++) = '\0';
   }

   // If too many items
   if (num_tokens==MAX_TOKENS)
   {
      oxts_warn (8,"Generic aiding string too long");
      i = -1;
   }
   else if (num_tokens==0)
      i = -1;

   // Reserved/version - read but don't check
   if (i);
   else if ( cur_token<(num_tokens-1) )
   {
      if (sscanf(tokens[cur_token], "%d", &i_t) != 1)
         i = -1;
      else
         cur_token ++;
   }
   else
      return -1;

   // TYPE
   if (i);
   else if ( cur_token<(num_tokens-1) )
   {
      if (sscanf(tokens[cur_token], "%d", &i_t) != 1)
         i = -1;
      else
      {
         gad->type = i_t;
         cur_token ++;
      }
   }
   else
      return -1;

   // Stream ID
   if (i);
   else if (cur_token < (num_tokens - 1))
   {
      if (sscanf(tokens[cur_token], "%d", &i_t) != 1)
         i = -1;
      else
      {
         gad->stream_id = i_t;
         cur_token++;
      }
   }
   else
      return -1;

   // Start parsing the sub-structures, in sequence
   if (i);
   // Sub-struct VALUE
   if (i > 0);
   else if (i = validity_parse(&gad->val_valid, tokens, &cur_token, num_tokens));
   else if (!i && !gad->val_valid)
      return -1; // failed to parse val packet invalid so return -1
   else if ((i = genaid_gen3d_parse(&gad->val, tokens, &cur_token, num_tokens)) > 0);
   else if (i != 0)
   {
      gad->val_valid = 0;
      gad->type = GEN_VOID;
      return -1;
   }

   // Sub-struct TIME
   if (i > 0);
   else if (i = validity_parse(&gad->time_valid, tokens, &cur_token, num_tokens));
   else if (!i && !gad->time_valid)
      return -1; // failed to parse time or time invalid - xDev timestamps data on reciept and sets flag to 1, if this has failed, then packet has no time and cannot be used
   else if ((i = genaid_gen3d_parse(&gad->time, tokens, &cur_token, num_tokens)) > 0);
   else if (i != 0)
   {
      gad->time_valid = 0;
      gad->type = GEN_VOID;
      return -1;
   }

   // ACQUISITION TIME
   if (i > 0);
   else if (i = validity_parse(&gad->acq_valid, tokens, &cur_token, num_tokens));
   else if (!i && !gad->acq_valid)
      cur_token++; // No error but acquisition timestamp invalid. Move on.
   else if (!i && (cur_token < (num_tokens - 1)))
   {
      if (sscanf(tokens[cur_token], "%d", &i_t) != 1)
         i = -1;
      else
      {
         gad->acq = i_t;
         cur_token++;
      }
   }

   // Sub-struct LOCATION ACTIVE - location/position where aiding is active (lever arm - in IMU coords, or in some other frames)
   if (i > 0);
   else if (i = validity_parse(&gad->loc_valid, tokens, &cur_token, num_tokens));
   // check if validity was parsed succesfully and that the flag is false
   else if (!i && !gad->loc_valid)
   {
      i = skip_to_next_char(tokens, &cur_token, num_tokens); // advance cur_token to the next position where theres a char
      i = 0; // set error state back to 0
   }
   else if ((i = genaid_gen3d_parse(&gad->loc, tokens, &cur_token, num_tokens)) > 0);
   else if (i != 0)
      gad->loc_valid = 0;

   // Sub-struct LOCATION SOURCE - a second location/position such as the aiding source (beacon position or something)
   if (i > 0);
   else if (i = validity_parse(&gad->res1_valid, tokens, &cur_token, num_tokens));
   else if (!i && !gad->res1_valid)
   {
      i = skip_to_next_char(tokens, &cur_token, num_tokens); // advance cur_token to the next position where theres a char
      i = 0; // set error state back to 0
   }
   else if ((i = genaid_gen3d_parse(&gad->res1, tokens, &cur_token, num_tokens)) > 0);
   else if (i != 0)
      gad->res1_valid = 0;

   // Sub-struct ANGLE OF ARRIVAL - angle of arrival/other orientation information about source/receiver
   if (i > 0);
   else if (i = validity_parse(&gad->res2_valid, tokens, &cur_token, num_tokens));
   else if (!i && !gad->res2_valid)
   {
      i = skip_to_next_char(tokens, &cur_token, num_tokens); // advance cur_token to the next position where theres a char
      i = 0; // set error state back to 0
   }
   else if ((i = genaid_gen3d_parse(&gad->res2, tokens, &cur_token, num_tokens)) > 0);
   else if (i != 0)
      gad->res2_valid = 0;

   return i; /* Indicate success */
}


//============================================================================================================
//! \brief Parse the values, without the ID

int genaid_gen3d_parse(GEN_3D* val, char** tokens, int* cur_t, int max_tokens)
{
   // Temp store for individual decoded values (double)
   double d_t;
   // Temp store for individual decoded values (int)
   int i_t;
   // Iterator
   int k;

   int var_size = 0;

   int dim = 3;

#ifdef EXTRA_CHECKS
   if (val == NULL)
   {
      oxts_error(2, "NULL encountered instead of pointer to GEN_3D");
      return 2;
   }
   if (tokens == NULL)
   {
      oxts_error(2, "NULL encountered instead of pointer to token vector");
      return 2;
   }
   if (cur_t == NULL)
   {
      oxts_error(2, "NULL encountered instead of pointer to token index");
      return 2;
   }
#endif // EXTRA_CHECKS


   if ((*cur_t) < (max_tokens))        // Check we haven't overrun the current line
   {
      if (sscanf(tokens[*cur_t], "%d", &i_t) != 1)    // 1 => failure
         return -1;
      else
      {
         // Write stream id into val->id
         val->mode = i_t;
         (*cur_t)++;
      }
   }

   // If the ID is invalid
   if (val->mode == Enum__AID_STREAM_UNKNOWN)     // 255! - id is unsigned
      return -1;
   /// else - Interpretation depends on field: for VALUE the ID is stream_id, for other fields it means other things (e.g. for location on pos/vel type is means use configured lever arm)

   // Type
   if ((*cur_t) < max_tokens)
   {
      if (sscanf(tokens[*cur_t], "%d", &i_t) != 1)
         return -1;
      else
         val->x_type = i_t;
      (*cur_t)++;
   }
   else
      return -1;

   // Values (3)
   for (k = 0; k < dim; k++)
   {
      if ((*cur_t) < max_tokens)
      {
         if (sscanf(tokens[*cur_t], "%lf", &d_t) != 1)
            return -1;
         else
            val->x[k] = d_t;
         (*cur_t)++;
      }
      else
         return -1;
   }

   // Variance Type
   if ((*cur_t) < max_tokens)
   {
      if (sscanf(tokens[*cur_t], "%d", &i_t) != 1)
         return -1;
      else
         val->v_type = i_t;
      (*cur_t)++;
   }
   else
      return -1;

   // Variance values (var_size)
   for (k = 0; k < dim * (dim + 1) / 2; k++)
   {
      if (*cur_t < max_tokens)
      {
         if (sscanf(tokens[*cur_t], "%lf", &d_t) != 1)
            return -1;
         else
            val->v[k] = d_t;
         (*cur_t)++;
      }
      else
         return -1;
   }

   return 0;
}


//============================================================================================================
//! \brief 

int set_csv_filename(void *dm, const char * filename)
{
   DecoderMemoryGenAidCSV *p = (DecoderMemoryGenAidCSV *)dm;
#ifdef EXTRA_CHECKS
   if (dm == NULL)
   {
      oxts_error(2, "NULL encountered instead of pointer to decoder memory");
      return 2;
   }
#endif // EXTRA_CHECKS

   if (filename==NULL)
      return -1;
   else if  (strlen (filename)>MAX_FILENAME)
      return -1;
   else if (strcpy (p->filename, filename) ==NULL)
      return -1;

   return 0;
}


//============================================================================================================
//! \brief 

int read_next_csv_line (void *dm, signed char *data, int max_len, uint32_t *len)
{
   DecoderMemoryGenAidCSV *p = (DecoderMemoryGenAidCSV *)dm;
#ifdef EXTRA_CHECKS
   if (dm == NULL)
   {
      oxts_error(2, "NULL encountered instead of dbl pointer to decoder memory");
      return 2;
   }
#endif // EXTRA_CHECKS

   if (p->fp==NULL)
      return -1;

   if ( fscanf(p->fp, "%[^\n\r]", data) != EOF)
   {
      if (len)
         *len = strlen((const char*)data);
      fscanf(p->fp, "%*[\n\r]");
      return 0;
   }

   // Skip any sequence of \n, \r
   if ( fscanf(p->fp, "%*[\n\r]") == EOF)
      return -1;

   return -1;
}


//============================================================================================================
//! \brief 

int open_csv(void *dm)
{
   DecoderMemoryGenAidCSV *p = (DecoderMemoryGenAidCSV *)dm;

#ifdef EXTRA_CHECKS
   if (dm == NULL)
   {
      oxts_error(2, "NULL encountered instead of pointer to decoder memory");
      return 2;
   }
#endif // EXTRA_CHECKS

   if (p->fp)
   {
      fclose (p->fp);
      p->fp = NULL;
   }
   if (p->filename==NULL || !strlen(p->filename) )
      return -1;
   else
      p->fp=fopen(p->filename, "rt");

   if (p->fp==NULL)
      return -1;
   else
      return 0;
}


//============================================================================================================
//! \brief 

int close_csv(void *dm)
{
   DecoderMemoryGenAidCSV *p = (DecoderMemoryGenAidCSV *)dm;

#ifdef EXTRA_CHECKS
   if (dm == NULL)
   {
      oxts_error(2, "NULL encountered instead of pointer to decoder memory");
      return 2;
   }
#endif // EXTRA_CHECKS

   if (p->fp)
   {
      fclose (p->fp);
      p->fp = NULL;
   }
   return 0;
}

#endif

//============================================================================================================
//! \brief Decode a generic aiding binary packet

int update_genaid_from_bin(GEN_AIDING_DATA *gad, unsigned char *data, int len)
{

	unsigned char *h = data;
	unsigned char *b = h + GEN_AID_HEADER_MIN_SIZE;
	int i = 0;
	size_t h_offset = 0;
	size_t b_offset = 0;
	uint8_t ver_type;

#ifdef EXTRA_CHECKS
	if (gad == NULL)
	{
		oxts_error(2, "NULL encountered instead of pointer to generic aiding data");
		return 2;
	}

#endif // EXTRA_CHECKS

	gad->type = GEN_VOID;
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
	if ((ver_type & 0xF0) != 0) {
		oxts_warn(8, "Unrecognised generic aiding version");
		i = -1;
	}
	else {
		gad->type = (ver_type & 0x0F);
		if (gad->type >= GEN_NUM)
		{
			oxts_warn(8, "Unrecognised generic aiding packet type.");
			i = -1;
		}
		++h_offset;
	}
	// If we do not have the second byte of the gad header, do nothing
	if (h_offset >= (size_t)len) {
		i = -1;
	}

   // If the additional bitmask is present, the header is 2 bytes longer than normal. Shift back the pointer to the payload
	if (i);
	else if (AdditionalBitmaskPresent(*(h + h_offset))) {
		b += 2;
	}

	// Decode acquisition timestamp provided by xDEV
	if (i);
	else if (*(b + b_offset) == 0)			// Check acquisition timestamp version -- when new versions are created, this can be extended with more cases -- ENUM?
	{
		if (b + b_offset + 8 - h > len)     // checks that the offset is not greater than the length of the packet
			i = -1;
      else if (!(i = decode_acq_timestamp_bin(&(gad->acq), b, &b_offset)))
         gad->acq_valid = 1;
      else
         i = 0;
   }

   if (i);
   else
      gad->stream_id = cast_1_byte_LE_to_uint8((b + b_offset++));

	if (i);
	else if (ValueFieldPresent(*(h + h_offset))) {
		if (!(i = decode_gen3d_bin(&(gad->val), b, &b_offset)))
			gad->val_valid = 1;
		// b_offset is the new offset in the data packet after decoding the structure
		// If there was some corruption, b_offset might point outside the data
		// and if that is the case, we will drop this packet
		if (b + b_offset - h > len)
			i = -1;
	}

	if (i);
	else if (TimeFieldPresent(*(h + h_offset))) {
		if (!(i = decode_gen3d_bin(&(gad->time), b, &b_offset)))
			gad->time_valid = 1;
		if (b + b_offset - h > len)		// checks that the offset is not greater than the length of the packet
			i = -1;
	}

	if (i);
	else if (LocationFieldPresent(*(h + h_offset))) {
		if (!(i = decode_gen3d_bin(&(gad->loc), b, &b_offset)))
			gad->loc_valid = 1;
		if (b + b_offset - h > len)		// checks that the offset is not greater than the length of the packet
			i = -1;
	}

	if (i);
	else if (Res1Present(*(h + h_offset))) {
		if (!(i = decode_gen3d_bin(&(gad->res1), b, &b_offset)))
			gad->res1_valid = 1;
		if(b + b_offset - h > len)		// checks that the offset is not greater than the length of the packet
			i = -1;
	}

	if (i);
	else if (Res2Present(*(h + h_offset))) {
		if (!(i = decode_gen3d_bin(&(gad->res2), b, &b_offset)))
			gad->res2_valid = 1;
		if(b + b_offset - h > len)		// checks that the offset is not greater than the length of the packet
			i = -1;
	}

	if (i);
	else if ((uint32_t)(b - h) > GEN_AID_HEADER_MIN_SIZE) {
		// Decode fields indicated in the additional bitmask here.
		;
	}

	if (b_offset + GEN_AID_HEADER_MIN_SIZE > (size_t)len)
	   i = -1;


   return i;
}

//============================================================================================================
//! \brief Parse acquisition timestamp (xDEV PPS relative) data field from binary stream and place into a uint32_t

int decode_acq_timestamp_bin(uint32_t *acq_time, unsigned char *b, size_t *b_offset)
{
   int i = 0;
   // 1st byte already been checked before calling this function
   (*b_offset)++;

   // Check timestamp type (2nd byte)
   if (*(b + (*b_offset)) == TIME_PPS_RELATIVE)
   {
      (*b_offset) += 3;									// Move past type byte (2), skip the reserved bytes (3,4)
      (*acq_time) = cast_4_byte_LE_to_uint32(b + (*b_offset)) * 1000;			// x1000 to convert from microseconds to nanoseconds
   }
   /*
      It is not strictly an error for there to not be an aquisition timestamp if there is a valid external timestamp in the packet
   */
   else
   {
      (*b_offset) += 3;
      i = 0;
   }
   
   (*b_offset) += sizeof(uint32_t);					// Advance offset past timestamp to allow decoding of the rest of the packet

   return i;
}

//============================================================================================================
//! \brief Parse generic aiding data field from binary stream

int decode_gen3d_bin(GEN_3D *field, unsigned char *b, size_t *b_offset) 
{
	int i = 0;
	int d;

	field->mode = cast_1_byte_LE_to_int8(b + (*b_offset)++);
	field->x_type = cast_1_byte_LE_to_int8(b + (*b_offset)++);

   // mode=0 -> a 3D-based structure will be decoded
   if (field->mode == 0)
   {
      for (d = 0; d < 3; ++d)
      {
         field->x[d] = cast_8_byte_LE_to_real64(b + *(b_offset));
         (*b_offset) += sizeof(real64_t);
      }

      field->v_type = cast_1_byte_LE_to_int8(b + (*b_offset)++);

      i = decode_gen3d_var_bin(field, b, b_offset);
   }
   // ID=1 to MAX_ID_GEN3D: symbolic link to a value defined in a configuration file, but the values are not transmitted in the data
   else if (field->mode < MAX_ID_GEN3D);
   // ID higher or equal to MAX_ID_GEN3D: - not recognised, the format may be newer so we will return -1
   else
   {
      i = -1;
   }

	return i;
}

int decode_gen3d_var_bin(GEN_3D *field, unsigned char *b, size_t *b_offset)
{
	int i = 0;
	int d;
	int var_size = 0;
	int dims = 3;

	switch (field->v_type)
	{
	case GEN_VAR_VOID:		               // If the variance is void, there is nothing to encode.
		var_size = 0;
		break;
	case GEN_VAR_SINGLE:
		var_size = 1;
		break;
	case GEN_VAR_DIAG:		               // Diagonal of a 3x3 matrix => 3 values
		var_size = dims;
		break;
	case GEN_VAR_HMAT:			            // Full symmetric 3x3 matrix can be encoded as 6 values
		var_size = dims * (dims + 1) / 2;
		break;
	default:
		return -1;
	}

   for (d = 0; d < var_size; ++d)
	{
		field->v[d] = cast_8_byte_LE_to_real64(b + *(b_offset));
		*b_offset += sizeof(real64_t);
	}

	return i;
}


//============================================================================================================
//! \brief Perform basic checks on the binary genaid packet before sending for acquisition timestamping
//!
//! Returns 0 on success, -1 if the format is not accepted

int genaid_basic_checks_bin(unsigned char *data, int len)
{
	unsigned char 		*h = 		data;
	size_t 				h_offset = 	0;
	uint8_t 			ver_type;

	if (data==NULL)
		return -1;
	if (len<GEN_AID_HEADER_MIN_SIZE+8)
		return -1;
	else
	{
		// Check whether this is not an extended header
		h_offset++;
		if (AdditionalBitmaskPresent(*(h + h_offset))) {
			if (len<GEN_AID_HEADER_MIN_SIZE+8+2)
				return -1;
		}
	}
	// By this time we have made sure that the data has enough size to contain the header (4 or 6 bytes) + acquisition time stamp (8 bytes)

	// Decode version type
	ver_type = cast_1_byte_LE_to_uint8(h);
	ver_type = (ver_type & 0xF0)>>4;

	// Check version is 0
	if (ver_type != 0)
	{
		oxts_warn(8, "Generic aiding version not supported");
		return -1;
	}

	return 0;
}


/*********************************************************************************/
/* Generic Aiding Decoder Memory data structure allocation, freeing and checking functions */
/*********************************************************************************/

#if OXTS_EXE_PP
//============================================================================================================
//! \brief Allocates the space required for the Generic Aiding decoder memory.

int initialise_genaidcsv_decodermemory(void **dm, int time_arrow_fwd)
{
   int            i = 0;

#ifdef EXTRA_CHECKS
   if (dm == NULL)
   {
      oxts_error(2, "NULL encountered instead of pointer to Decoder Memory");
      return 2;
   }
#endif // EXTRA_CHECKS

   // 1) allocate the Decoder Memory data structure (if required)
   if (*dm != NULL)
      memset(*dm, 0, sizeof(DecoderMemoryGenAidCSV));
   // calloc() is used to initialise all the memory to NULL
   else if ((*dm = calloc(1, sizeof(DecoderMemoryGenAidCSV))) == NULL)
   {
      oxts_error(1, "Unable to allocate decoder memory data structure");
      return 1;
   }

   // Clean up if an error occurred
   if (i)
      kill_genaidcsv_decodermemory(dm, 1);

   return i;
}


//============================================================================================================
//! \brief Frees the memory space allocated for the Generic Aiding Decoder Memory.

int kill_genaidcsv_decodermemory(void **dm, int free_base)
{
   int            j = 0;
   DecoderMemoryGenAidCSV *pt;

#ifdef EXTRA_CHECKS
   if (dm == NULL)
   {
      oxts_error(2, "NULL encountered instead of pointer to Decoder Memory");
      return 2;
   }
#endif // EXTRA_CHECKS

   if ((pt = *(DecoderMemoryGenAidCSV **)dm) == NULL)  /* the GPS model does not need freeing */
      return 0;

   // Free the subcomponents of the Decoder Memory

   // Free the base data structure (if required)
   if (free_base)
   {
      free(pt);
      *dm = NULL;
   }
   else
      /* indicate that all the subcomponents have been freed */
      memset(*dm, 0, sizeof(DecoderMemoryGenAidCSV));

   return j;
}


//============================================================================================================
//! \brief Verifies that the GRIL Decoder Memory passed to it is valid.

int invalid_genaidcsv_decodermemory(void *dm)
{
#ifdef EXTRA_CHECKS
	if (dm == NULL)
	{
		oxts_error(2, "NULL encountered instead of pointer to Decoder Memory");
		return 2;
	}
#endif // EXTRA_CHECKS

	// otherwise all is fine
	return 0;
}


#endif


//============================================================================================================
//! \brief Allocates the space required for the Generic Aiding decoder memory.

int initialise_genaidbin_decodermemory(void **dm)
{
   int            i = 0;

#ifdef EXTRA_CHECKS
   if (dm == NULL)
   {
      oxts_error(2, "NULL encountered instead of pointer to Decoder Memory");
      return 2;
   }
#endif // EXTRA_CHECKS

   // 1) allocate the Decoder Memory data structure (if required)
   if (*dm != NULL)
      memset(*dm, 0, sizeof(DecoderMemoryGenAidBin));
   // calloc() is used to initialise all the memory to NULL
   else if ((*dm = calloc(1, sizeof(DecoderMemoryGenAidBin))) == NULL)
   {
      oxts_error(1, "Unable to allocate decoder memory data structure");
      return 1;
   }

   // Clean up if an error occurred
   if (i)
      kill_genaidbin_decodermemory(dm, 1);

   return i;
}

//============================================================================================================
//! \brief Frees the memory space allocated for the Generic Aiding Decoder Memory.

int kill_genaidbin_decodermemory(void **dm, int free_base)
{
   int            j = 0;
   DecoderMemoryGenAidBin *pt;

#ifdef EXTRA_CHECKS
   if (dm == NULL)
   {
      oxts_error(2, "NULL encountered instead of pointer to Decoder Memory");
      return 2;
   }
#endif // EXTRA_CHECKS

   if ((pt = *(DecoderMemoryGenAidBin **)dm) == NULL)  /* the GPS model does not need freeing */
      return 0;

   // Free the subcomponents of the Decoder Memory

   // Free the base data structure (if required)
   if (free_base)
   {
      free(pt);
      *dm = NULL;
   }
   else
      /* indicate that all the subcomponents have been freed */
      memset(*dm, 0, sizeof(DecoderMemoryGenAidBin));

   return j;
}

#ifdef __cplusplus
}
#endif


//============================================================================================================
//!
//! The software is protected by copyright of Oxford Technical Solutions.
//! Copyright (C) 2020 Oxford Technical Solutions - http://www.oxts.com
//!
//! Redistribution and use in source and binary forms, with or without modification, are only permitted with
//! the specific prior written permission of Oxford Technical Solutions.
//!
//! $LastChangedDate: 2019-10-10 17:01:45 +0100 (Thu, 10 Oct 2019) $
//! $LastChangedRevision: 28591 $
//! $LastChangedBy: smccarthy $
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


#ifdef __cplusplus
extern "C"
{
#endif

#if OXTS_EXE_PP
   // Functions for extracting generic aiding from text format (csv)
   extern int update_genaid_from_csv(GEN_AIDING_DATA* gad, unsigned char* data, int len);
   extern int set_csv_filename(void* dm, const char* filename);
   extern int read_next_csv_line(void* dm, signed char* data, int max_len, uint32_t* len);
   extern int open_csv(void* dm);
   extern int close_csv(void* dm);
   int genaid_gen3d_parse(GEN_3D* val, char** tokens, int* cur_token, int max_tokens);
#endif

   extern int update_genaid_from_bin(GEN_AIDING_DATA* gad, unsigned char* data, int len);

   int decode_gen3d_bin(GEN_3D* field, unsigned char* b, size_t* b_offset);
   int decode_gen3d_var_bin(GEN_3D* field, unsigned char* b, size_t* b_offset);
   int decode_acq_timestamp_bin(uint32_t* acq_time, unsigned char* b, size_t *b_offset);
   int genaid_basic_checks_bin(unsigned char* data, int len);

#if OXTS_EXE_PP
   // Functions related to the generic aiding decoder memory
   extern int initialise_genaidcsv_decodermemory(void** dm, int time_arrow_fwd);
   extern int kill_genaidcsv_decodermemory(void** dm, int free_base);
   extern int invalid_genaidcsv_decodermemory(void* dm);
#endif

   extern int kill_genaidbin_decodermemory(void** dm, int free_base);

   //int update_genaid_decodermemory_options (void *dm, RTBNS_OPTIONS)


#ifdef __cplusplus
}
#endif


#endif

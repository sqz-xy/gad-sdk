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
//! \file gad_struct.c
//!
//! \brief Struct to contain generic aiding data 
//!  
//============================================================================================================

#include "oxts/gal/gad_struct.h"


//============================================================================================================

int reset_genaid_data(GEN_AIDING_DATA* gad)
{
   gad->type = GEN_VOID;
   gad->stream_id = 0;
   gad->time_valid = 0;
   gad->res1_valid = 0;
   gad->loc_valid = 0;
   gad->res1_valid = 0;
   gad->val_valid = 0;
   gad->acq_valid = 0;
   memset(gad, 0, sizeof(*gad));

   return 0;
}

//============================================================================================================

int reset_gen3d(GEN_3D* d)
{
   int i = 0;
   d->mode = 255;
   d->v_type = 0;
   d->x_type = 0;

   for (i = 0; i < 3 * (3 + 1) / 2; ++i)
   {
      d->v[i] = 0;
   }
   for (i = 0; i < 3; ++i)
   {
      d->x[i] = 0;
   }
   return 0;
}


//============================================================================================================

int initialise_genaid(void** gad)
{
#ifdef EXTRA_CHECKS
   if (gad == NULL)
   {
      oxts_error(2, "NULL encountered instead of dbl-pointer to generic aiding");
      return 2;
   }
#endif // EXTRA_CHECKS

   if (*gad != NULL)
      memset(*gad, 0, sizeof(GEN_AIDING_DATA));
   else if ((*gad = calloc(1, sizeof(GEN_AIDING_DATA))) == NULL)    // calloc() is used to initialise all the memory to NULL
   {
      oxts_error(1, "Unable to allocate generic aiding data");
      return 1;
   }

   return 0;
}


//============================================================================================================

int kill_genaid(void** gad, int free_base)
{
   int i = 0;
   GEN_AIDING_DATA* pt;

#ifdef EXTRA_CHECKS
   if (gad == NULL)
   {
      oxts_error(2, "NULL encountered instead of pointer to generic aiding");
      return 2;
   }
#endif

   if ((pt = *(GEN_AIDING_DATA**)gad) == NULL)
      return 0;

   if (free_base)
   {
      free(pt);
      *gad = NULL;
   }
   else
      // indicate that all the subcomponents have been freed
      memset(*gad, 0, sizeof(GEN_AIDING_DATA));

   return i;
}


//============================================================================================================

int genaid_copy(void* dst, void* src)
{
#ifdef EXTRA_CHECKS
   if (dst == NULL)
   {
      oxts_error(2, "NULL encountered instead of pointer to Generic Aiding dst");
      return 2;
   }
   else if (src == NULL)
   {
      oxts_error(2, "NULL encountered instead of pointer to Generic Aiding src");
      return 2;
   }
#endif // EXTRA_CHECKS

   memcpy((void*)dst, src, sizeof(GEN_AIDING_DATA));

   return 0;
}



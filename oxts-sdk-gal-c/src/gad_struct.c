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
//! \file gad_struct.c
//!
//! \brief Struct to contain generic aiding data 
//!  
//============================================================================================================

#include "oxts/gal-c/gad_struct.h" /*PRQA S 0857 # ISO:C90 */ /*PRQA S 0816 # ISO:C90*/

//============================================================================================================

int32_t reset_genaid_data(GEN_AIDING_DATA* gad)  /*PRQA S 1505 # Function is intended for external consumption. */
{
    int32_t ec;
    gad->type = (int8_t)GEN_VOID;
    gad->stream_id = 0;
    gad->time_valid = 0;
    ec = reset_gen3d(&(gad->time));
    if (ec == 0)
    {
        gad->res1_valid = 0;
        ec = reset_gen3d(&(gad->res1));
    }
    if (ec == 0)
    {
        gad->loc_valid = 0;
        ec = reset_gen3d(&(gad->loc));
    }
    if (ec == 0)
    {
        gad->res2_valid = 0;
        ec = reset_gen3d(&(gad->res2));
    }
    if (ec == 0)
    {
        gad->val_valid = 0;
        ec = reset_gen3d(&(gad->val));
    }
    if (ec == 0)
    {
        gad->acq_valid = 0;
        gad->acq = 0;
    }
    return ec;
}

//============================================================================================================

int32_t reset_gen3d(GEN_3D* d) /*PRQA S 1505 # Function is intended for external consumption. */
{
    int32_t i;
    d->mode = 255;
    d->v_type = 0;
    d->x_type = 0;

    for (i = 0; i < ((3 * (3 + 1)) / 2); ++i)
    {
        d->v[i] = 0.0;
    }
    for (i = 0; i < 3; ++i)
    {
        d->x[i] = 0.0;
    }
    return 0;
}


//============================================================================================================


int32_t initialise_genaid(GEN_AIDING_DATA* gad) /*PRQA S 1505 # Function is intended for external consumption. */ /*PRQA S 1503 # Function is intended for external consumption. */
{
   int32_t ec = 0;
#ifdef EXTRA_CHECKS
   if (gad == NULL)
   {
      oxts_error(2, "NULL encountered instead of pointer to generic aiding");
      ec = 2;
   }
   else
   {
#endif // EXTRA_CHECKS
  
   if (gad != NULL)
   {
      ec = reset_genaid_data(gad);
   }
#ifdef EXTRA_CHECKS
   }
#endif
   return ec;
}

//============================================================================================================

int32_t genaid_copy(GEN_AIDING_DATA* dst, const GEN_AIDING_DATA* src) /*PRQA S 1505 # Function is intended for external consumption. */ /*PRQA S 1503 # Function is intended for external consumption. */
{
   int32_t ec = 0;
#ifdef EXTRA_CHECKS
   if (dst == NULL)
   {
      oxts_error(2, "NULL encountered instead of pointer to Generic Aiding dst");
      ec = 2;
   }
   else if (src == NULL)
   {
      oxts_error(2, "NULL encountered instead of pointer to Generic Aiding src");
      ec = 2;
   }
   else
   {
#endif // EXTRA_CHECKS

   (void)memcpy(dst, src, sizeof(GEN_AIDING_DATA));

#ifdef EXTRA_CHECKS
   }
#endif

   return ec;
}

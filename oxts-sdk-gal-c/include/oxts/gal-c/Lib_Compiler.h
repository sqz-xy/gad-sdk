//============================================================================================================
//!
//! The software is protected by copyright of Oxford Technical Solutions.
//! Copyright (C) 2018 Oxford Technical Solutions - http://www.oxts.com
//!
//! Redistribution and use in source and binary forms, with or without modification, are only permitted with
//! the specific prior written permission of Oxford Technical Solutions.
//!
//! $LastChangedDate: 2019-04-18 15:57:11 +0100 (Thu, 18 Apr 2019) $
//! $LastChangedRevision: 28052 $
//! $LastChangedBy: alambert $
//!
//! \file Lib_Compiler.h
//!
//! \brief Cross compiler support for everything other than basic types.
//!
//============================================================================================================


#ifndef LIB__COMPILER_H
#define LIB__COMPILER_H

#include "oxts/gal-c/Lib_Detect.h" 

#include <stdint.h>
#include <float.h>
#include <math.h>
#include <string.h>

//============================================================================================================
// isnan, isinf, isfinite.
int32_t oxts_isnan(const double_t num);
int32_t oxts_isfinite(const double_t num); /*PRQA S 0776 # Assume compiler does not have 6-character limit on unique identifiers. */
int32_t oxts_isinf(const double_t num); /*PRQA S 0776 # Assume compiler does not have 6-character limit on unique identifiers. */

#endif

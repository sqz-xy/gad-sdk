//============================================================================================================
//!
//! The software is protected by copyright of Oxford Technical Solutions.
//! Copyright (C) 2017 Oxford Technical Solutions - http://www.oxts.com
//!
//! Redistribution and use in source and binary forms, with or without modification, are only permitted with
//! the specific prior written permission of Oxford Technical Solutions.
//!
//! LastChangedDate: 2019-04-18 15:57:11 +0100 (Thu, 18 Apr 2019) 
//! LastChangedRevision: 28052 
//! LastChangedBy: alambert 
//!
//! \file Lib_Compiler.c
//!
//! \brief Cross compiler support for everything other than basic types.
//!
//============================================================================================================

#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>

#include "oxts/gal-c/Lib_Compiler.h" /*PRQA S 0857 # ISO:C90 */ /*PRQA S 0816 # ISO:C90*/

#ifdef OXTS_CC_MSVC
int32_t oxts_isnan(const double_t num) /*PRQA S 1503 # Is a library, and thus intended for external consumption. */
{
	return _isnan(num);
}
int32_t oxts_isfinite(const double_t num) /*PRQA S 1503 # Is a library, and thus intended for external consumption. */
{
	return _finite(num);
}
int32_t oxts_isinf(const double_t num) /*PRQA S 1503 # Is a library, and thus intended for external consumption. */
{
	int32_t return_val = 0;
	if (_finite(num) == 0)
	{
		// Written this way to conform to M3CM Rule 13.5 regarding operations with persistent side-effects on right-hand side of && or ||
		if (_isnan(num) != 0)
		{
			return_val = 1;
		}
	}
	return return_val;
}
#elif (defined(OXTS_CC_BORLAND))

//============================================================================================================
//! \brief ...
//!
//! \note Borland only defines IsInfinite in C++. To beable to use it from a C source linked into a C++
//! project we need to introduce this C wrapper.

int32_t oxts_isnan(double_t x)
{
	return IsNan(x);
}

int32_t oxts_isinf(double_t x)
{
	return IsInfinite(x);
}

//============================================================================================================
//! \brief ...
//!
//! \note Borland only defines IsInfinite and IsNan in C++. To beable to use it from a C source linked into a
//! C++ project we need to introduce this C wrapper.

int32_t oxts_isfinite(double_t x)
{
	return !IsInfinite(x) && !IsNan(x);
}

#define OXTS_COMPILER_fallback_isnan
#define OXTS_COMPILER_fallback_isinf
#define OXTS_COMPILER_fallback_isfinite
#define oxts_isnan    fallback_isnan
#define oxts_isinf    fallback_isinf
#define oxts_isfinite fallback_isfinite

#else
int32_t oxts_isnan(const double_t num)
{
	return isnan(num);
}
int32_t oxts_isinf(const double_t num)
{
	return isinf(num);
}
int32_t oxts_isfinite(double_t num)
{
	return !oxts_isinf(num) && !oxts_isnan(num);
}
#endif

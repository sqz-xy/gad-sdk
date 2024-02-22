//============================================================================================================
//!
//! The software is protected by copyright of Oxford Technical Solutions.
//! Copyright (C) 2023 Oxford Technical Solutions - http://www.oxts.com
//!
//! Redistribution and use in source and binary forms, with or without modification, are only permitted with
//! the specific prior written permission of Oxford Technical Solutions.
//!
//! \file oxts_misra.hpp
//!
//! \brief Handles MISRA compliance options.
//!
//============================================================================================================

#ifndef OXTS_MISRA_H
#define OXTS_MISRA_H

#include <cmath>


#include <array>
#include "oxts/gal-cpp/oxts_arrays.hpp"
namespace OxTS
{
	typedef std::array<std::double_t, 3> container_double3_t;
	typedef std::array<std::double_t, 6> container_double6_t;
}

#ifdef OXTS_ENABLE_CPP11
#define ENUM enum class
#else
#define ENUM enum
#endif

#endif

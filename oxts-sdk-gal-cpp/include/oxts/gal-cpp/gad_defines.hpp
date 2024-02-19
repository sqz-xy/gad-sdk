//============================================================================================================
//!
//! The software is protected by copyright of Oxford Technical Solutions.
//! Copyright (C) 2020 Oxford Technical Solutions - http://www.oxts.com
//!
//! Redistribution and use in source and binary forms, with or without modification, are only permitted with
//! the specific prior written permission of Oxford Technical Solutions.
//!
//! $LastChangedDate: $
//! $LastChangedRevision:  $
//! $LastChangedBy: ljones $
//!
//! \file gad_defines.hpp
//!
//! \brief C++ definitions relevant to Generic Aiding
//!
//============================================================================================================

#ifndef GA_DEFINES_HPP
#define GA_DEFINES_HPP

#include <cstdint>
#include <cstddef>
#include <cmath>
#include "oxts/gal-cpp/oxts_misra.hpp"

namespace OxTS
{
	namespace Gal_Cpp
	{
		static const std::uint32_t MAX_CSV_LINE = (128U * 64U);  // max length of a line

		static const std::uint8_t AdditionalBitmaskBit = 0x80U;
		static const std::uint8_t ValueBit = 0x40U;
		static const std::uint8_t TimeBit = 0x20U;
		static const std::uint8_t LocationBit = 0x10U;
		static const std::uint8_t Res1Bit = 0x08U;
		static const std::uint8_t Res2Bit = 0x04U;

		static const std::size_t GEN_AID_HEADER_MIN_SIZE	= 4U;	  //!< Size of basic header in generic aiding binary packet
		static const std::size_t XDEV_ACQUISTION_TIMESTAMP_SIZE = 8U; //!< The size in bits of the acquisition timestamp appended to the generic aiding payload on receipt.

		static const std::size_t REALTIME_GENAID_RX_START_IDX = 0U;
		static const std::size_t MAX_NUM_REALTIME_GENAID_RX = 1U;
		static const std::size_t PP_GENAID_RX_START_IDX = (REALTIME_GENAID_RX_START_IDX + MAX_NUM_REALTIME_GENAID_RX);
		static const std::size_t MAX_NUM_PP_GENAID_RX = 8U;

				// Size of time interval during which genaid updates will override the GPS output status
		static const std::double_t GENAID_POS_STATUS_AGE_THRESHOLD = 2.0;
		static const std::double_t GENAID_VEL_STATUS_AGE_THRESHOLD = 2.0;

		static const std::size_t MAX_GENAID_PKT_SIZE = 2048U;

		static const std::size_t MAX_ID_GEN3D = 16U; // Max value accepted for mode in Gen3D structures

		// How late a GAD timestamp can be compared to internal time before it is rejected. (s) 
		static const std::double_t GAD_LATE_THRESH =           -1.0; /*PRQA S 3708 # Required to define -1.0 */
		static const std::double_t GAD_EARLY_WARN_THRESH =      0.1;    // How early a GAD timestamp can be compared to internal time before it a warning is output (in debug). (s)
		static const std::double_t GAD_EARLY_REJECT_THRESH =    0.3;    // How early a GAD timestamp can be compared to internal time before it is rejected. (s)

		/*
		   <!> DECODER DEFINES <!>
		*/
		static const std::size_t GAD_MAX_BUF =       1U;        //!< max number of parallel buffers (e.g., files/streams)
		static const std::size_t GAD_BUF_MAX_SIZE =  256U;       //!< max number of data in a buffer
	}
}

#endif

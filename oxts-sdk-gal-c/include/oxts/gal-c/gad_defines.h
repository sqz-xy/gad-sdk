//============================================================================================================
//!
//! The software is protected by copyright of Oxford Technical Solutions.
//! Copyright (C) 2020 Oxford Technical Solutions - http://www.oxts.com
//!
//! Redistribution and use in source and binary forms, with or without modification, are only permitted with
//! the specific prior written permission of Oxford Technical Solutions.
//!
//! LastChangedDate: 2019-10-10 17:01:45 +0100 (Thu, 10 Oct 2019
//! LastChangedRevision: 28591
//! LastChangedBy: smccarthy
//!
//! \file gad_defines.h
//!
//! \brief Macro definitions relevant to Generic Aiding
//!
//============================================================================================================

#ifndef GA_DEFINES
#define GA_DEFINES

#include "oxts/gal-c/oxts_misra.h"

#define AdditionalBitmaskBit 0x80U
#define ValueBit 0x40U
#define TimeBit 0x20U
#define LocationBit 0x10U
#define Res1Bit 0x08U
#define Res2Bit 0x04U

#define GEN_AID_HEADER_MIN_SIZE	  4U	  //!< Size of basic header in generic aiding binary packet
#define XDEV_ACQUISTION_TIMESTAMP_SIZE 8U //!< The size in bits of the acquisition timestamp appended to the generic aiding payload on receipt.


#define MAX_ID_GEN3D                (16U)  // Max value accepted for mode in Gen3D structures


#endif

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
//! \file gad_defines.h
//!
//! \brief Macro definitions relevant to Generic Aiding
//!
//============================================================================================================

#ifndef GA_DEFINES
#define GA_DEFINES

#define MAX_CSV_LINE      (128*64)  // max length of a line

#define AdditionalBitmaskBit (0x0080)
#define ValueBit (0x0040)
#define TimeBit (0x0020)
#define LocationBit (0x0010)
#define Res1Bit (0x0008)
#define Res2Bit (0x0004)
#define PassthroughBit (0x0002)

// Checks bitfield for indication of presence of data fields.
#define ValueFieldPresent(b)        (b & ValueBit)
#define TimeFieldPresent(b)         (b & TimeBit)
#define LocationFieldPresent(b)     (b & LocationBit)
#define Res1Present(b)              (b & Res1Bit)
#define Res2Present(b)              (b & Res2Bit)
#define AdditionalBitmaskPresent(b) (b & AdditionalBitmaskBit)
#define PassthroughPresent(b)       (b & PassthroughBit)

#define GEN_AID_HEADER_MIN_SIZE	  4U	  //!< Size of basic header in generic aiding binary packet
#define XDEV_ACQUISTION_TIMESTAMP_SIZE 8U //!< The size in bits of the acquisition timestamp appended to the generic aiding payload on receipt.

#define REALTIME_GENAID_RX_START_IDX 0
#define MAX_NUM_REALTIME_GENAID_RX 1
#define PP_GENAID_RX_START_IDX (REALTIME_GENAID_RX_START_IDX + MAX_NUM_REALTIME_GENAID_RX)
#define MAX_NUM_PP_GENAID_RX 8

// Size of time interval during which genaid updates will override the GPS output status
#define GENAID_POS_STATUS_AGE_THRESHOLD (2.0)
#define GENAID_VEL_STATUS_AGE_THRESHOLD (2.0)

#define MAX_GENAID_PKT_SIZE 2048

#define MAX_ID_GEN3D                (16)  // Max value accepted for mode in Gen3D structures

#define GAD_LATE_THRESH             (-1.0)    // How late a GAD timestamp can be compared to internal time before it is rejected. (s)
#define GAD_EARLY_WARN_THRESH       (0.1)    // How early a GAD timestamp can be compared to internal time before it a warning is output (in debug). (s)
#define GAD_EARLY_REJECT_THRESH     (0.3)    // How early a GAD timestamp can be compared to internal time before it is rejected. (s)

/*
   <!> DECODER DEFINES <!>
*/
#ifdef OXTS_EXE_PP
#define MAX_FILENAME       256      //!< Max 256 characters for filename
#define MAX_TOKENS         128      // a large number of tokens supported
#define GAD_MAX_BUF        4        //!< max number of parallel buffers (e.g., files/streams)
#define GAD_BUF_MAX_SIZE   4096      //!< max number of data in a buffer
#else
#define GAD_MAX_BUF        1        //!< max number of parallel buffers (e.g., files/streams)
#define GAD_BUF_MAX_SIZE   256       //!< max number of data in a buffer
#endif


#endif

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
//! \file gad_struct.h
//!
//! \brief Header for gad_struct.c
//!  
//============================================================================================================

#ifndef GAD_STRUCT
#define GAD_STRUCT

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//#include "errors.h"
#include "oxts/gal/gad_defines.h"
#include "oxts/lib/BasicTypes.h"

typedef uint8_t   GEN_BOOL;

//============================================================================================================
//! \brief Decoder types

typedef enum
{
   DECODER_VOID,                    //!< not set
   DECODER_CSV,                     //!< text data
   DECODER_BIN                      //!< binary data
} DECODER_TYPE;


//============================================================================================================
//! \brief Variance formats

typedef enum
{
   GEN_VAR_VOID,                            //!< missing
   GEN_VAR_SINGLE,                          //!< single value (variance)
   GEN_VAR_DIAG,                            //!< diagonal variance matrix
   GEN_VAR_HMAT                             //!< half-matrix (full co-variance matrix)
} GEN_VAR_TYPE;

//============================================================================================================
//! \brief 3-dimensional structure (vector real) with storage for full variance

typedef struct
{
   uint8_t        mode;             //!< ID
   uint8_t        x_type;           //!< Type of value x, e.g. coord system
   real64_t       x[3];             //!< Values
   uint8_t        v_type;           //!< Variance type see GEN_VAR_TYPE
   real64_t       v[3*(3+1)/2];     //!< Space for covariance matrix (diag+upper diag)
} GEN_3D;

//============================================================================================================
//! \brief Time systems
typedef enum
{
   TIME_VOID,
   TIME_GPS,            // standard GPS time format
   TIME_PPS_RELATIVE,   // time since PPS (seconds)
   TIME_EST_LATENCY,    // Not a timestamp, just an estimate of latency
   TIME_SDN,			// This is internal timing for xbns
}TIME_SYS;

//============================================================================================================
//! \brief Generic Aiding types

typedef enum
{
   GEN_VOID,
   GEN_POS,          // Position 3D
   GEN_RANGE,        // Range, 1D value, can contain angle of arrival as additional info
   GEN_VEL,          // Velocity 3D
   GEN_SPEED,        // Speed, e.g. wheel speed
   GEN_ATT,          // Attitude
   GEN_HEADING,      // Heading   //! to be merged in GEN_ATT, with ATT specifying in type wherer only heading, or heading+pitch, or heading+pitch+roll are present
   GEN_TIMETRIG,     // Time trigger, used for indoor segment navigation
   GEN_NUM
} GEN_TYPE;

//============================================================================================================
//! \brief Position coordinate systems

typedef enum
{
   POS_SYS_VOID,         // position coord system
   POS_SYS_WGS84,        // position, WGS84 - lat/lon/depth
} POS_SYS_TYPE;


//============================================================================================================
//! \brief Velocity types

typedef enum
{
   VEL_SYS_VOID,
   VEL_SYS_NEU             // North East Upwards
} VEL_SYS_TYPE;

//============================================================================================================
//! \brief Speed types 

typedef enum
{
   SPEED_SYS_VOID,
   SPEED_SYS_FW_VEL,        // speed at sensor fixed wrt IMU, speed angle wrt IMU given
} SPEED_SYS_TYPE;

//============================================================================================================
//! \brief Location types. (lever arm)
typedef enum
{
   LOC_FIXED = 0,			    // Lever arm specified explicitly.
   LOC_KF = 1,              // Take lever arm from kalman filter. -- lever arm is specified in the .gap file.
   LOC_CONFIG = 2           // Take lever arm from a configured lever arm in the config
}LOC_SYS;


//============================================================================================================
//! \brief Generic aiding data structure 
//!
//! The data is streamed in the sequence of data members
//! The dimension of the data is defined by type, if variable, we will need to define a new sub-structure
//! The sequence of data items is fixed (e.g. as given in this structure)

typedef struct
{
   // aiding value
   int8_t         type;                // GEN_TYPE - type of data 

   // stream ID
   uint8_t        stream_id;           // Identifies the source device

   // Sub-struct VALUE
   GEN_3D         val;                 // Navigation data
   GEN_BOOL       val_valid;

   // Sub-struct TIME
   GEN_3D         time;                // Time data was recorded
   GEN_BOOL       time_valid;

   // Sub-struct LOCATION 
   GEN_3D         loc;                 // Location/Position of Generic Aiding Device (lever arm)
   GEN_BOOL       loc_valid;

   // Sub-struct RESERVED
   GEN_3D         res1;
   GEN_BOOL       res1_valid;          

   // Sub-struct RESERVED
   GEN_3D         res2;
   GEN_BOOL       res2_valid;          

   // Acquisition Time Stamp 
   uint32_t       acq;                 // Timestamp from INS. Leave empty.
   GEN_BOOL       acq_valid;

} GEN_AIDING_DATA;



#ifdef __cplusplus
extern "C"
{
#endif

//============================================================================================================
//! \brief Functions to initialise/destroy/copy
   /*
      sets all the valid flags to 0

      params:
      gad - pointer to GEN_AIDING_DATA

      TODO:
      * make safe to user passing a NULL pointer
   */
int reset_genaid_data(GEN_AIDING_DATA* gad);


   int reset_gen3d(GEN_3D* d);

   /*
      used to initialise a block of memory for generic_aiding_data

      params:
      gad - pointer to the a pointer to start of GEN_AIDING_DATA
   */
   int initialise_genaid(void** gad);


   /*
      frees generic aiding resource
   */
   int kill_genaid(void** gad, int free_base);


   /*
      copies the data from one pointer to the other. not safe to dst pointer buffer < sizeof(GEN_AIDING_DATA)

      params:
      * dst - pointer to the location the data is being copied to
      * src - pointer to the location of the start of the gen_aiding_data struct
   */
   int genaid_copy(void* dst, void* src);

#ifdef __cplusplus
}
#endif

#endif

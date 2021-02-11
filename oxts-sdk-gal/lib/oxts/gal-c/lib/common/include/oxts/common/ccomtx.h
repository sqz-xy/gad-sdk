/*********************************************************************
* FileName:        ccom_tx.h
* Description:     Header file for ccom_tx.c
********************************************************************/
#ifndef CCOMTX_H
#define CCOMTX_H

#include "oxts/common/BasicTypes.h"

/************************************************************************************/
/*                              CCom packet definitions                             */
/************************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

#define CCOM_SYNC   (0x40)
#define CCOM_RES    (0x00)
#define CCOM_SHORT  (0x80)      //short header type (4-bytes)

#define CCOM_BUFF_SIZE     (65536)

   typedef struct
   {
      // input parameters
      uint16_t       type;
      unsigned char  version;

      // output 
      size_t         msg_len;
      unsigned char  msg_valid;           //!< encoded message valid
      unsigned char  msg[CCOM_BUFF_SIZE]; //!< encoded message
   } CCOM_MSG;

   int BuildCComPkt(CCOM_MSG *ccom_msg, const unsigned char* data, const unsigned int length);
#ifdef __cplusplus
}
#endif
#endif

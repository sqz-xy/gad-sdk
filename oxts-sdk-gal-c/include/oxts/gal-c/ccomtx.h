/*********************************************************************
* FileName:        ccom_tx.h
* Description:     Header file for ccom_tx.c
********************************************************************/
#ifndef CCOMTX_H
#define CCOMTX_H

#include "oxts/gal-c/BasicTypes.h" /*PRQA S 0816 # ISO:C90*/

/************************************************************************************/
/*                              CCom packet definitions                             */
/************************************************************************************/

#define CCOM_SYNC   (0x40U)
#define CCOM_RES    (0x00U)
//short header type (4-bytes) 
#define CCOM_SHORT  (0x80U)      /*PRQA S 1534 # Macro is intended for external consumption. */

#define CCOM_BUFF_SIZE     (65536U)

typedef struct
{
    // input parameters
    uint16_t       type;
    uint8_t        version;

    // output 
    size_t         msg_len;
    uint8_t        msg_valid;           //!< encoded message valid
    uint8_t        msg[CCOM_BUFF_SIZE]; //!< encoded message
} CCOM_MSG; 

int32_t BuildCComPkt(CCOM_MSG *cmsg, const uint8_t* data, const size_t length);

#endif

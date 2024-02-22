/*********************************************************************
* FileName:        ccomtx.c
* Description:     Functions to construct, store and send packets.
********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "oxts/gal-c/ccomtx.h" /*PRQA S 0857 # ISO:C90 */ /*PRQA S 0816 # ISO:C90*/
#include "oxts/gal-c/BasicTypes.h" /*PRQA S 0816 # ISO:C90*/
#include "oxts/gal-c/oxts_pointers.h" /*PRQA S 0816 # ISO:C90*/


int32_t BuildCComPkt(CCOM_MSG *cmsg, const uint8_t* data, const size_t length) /*PRQA S 1503 # Function is intended for external consumption. */
{
   int32_t ec;

   uint8_t checksum_header = 0U;
   uint8_t checksum_packet = 0U;
   uint32_t i_count;

   if ((cmsg == NULL) || (data == NULL) || ((length + 8U) > CCOM_BUFF_SIZE) || (cmsg->version != CCOM_RES))
   {
       ec = -1;
   }
   else
   {
       //! \todo check type
       cmsg->msg_len = (size_t)(length) + 8U;

       // Finalise the header
       cmsg->msg[0] = CCOM_SYNC;
       cmsg->msg[1] = CCOM_RES;
       cmsg->msg[2] = 0U;// will be filled with the header checksum
       cmsg->msg[3] = 0U;// will be filled with the packet checksum
       cmsg->msg[4] = (uint8_t)(cmsg->msg_len & 0xFFU);
       cmsg->msg[5] = (uint8_t)((cmsg->msg_len & 0xFF00U) >> 8);
       cmsg->msg[6] = (uint8_t)(cmsg->type & 0xFFU);
       cmsg->msg[7] = (uint8_t)((cmsg->type & 0xFF00U) >> 8);

       // Copy the data
       (void)memcpy(get_uint8_from_uint8(cmsg->msg, 8), data, (size_t)length);

       // Calculate the first part of the packet checksum from the end of the header
       for (i_count = 4U; i_count < 8U; i_count++)
       {
           checksum_packet += cmsg->msg[i_count];
       }
       // Calculate the remaining part of the packet checksum on the data
       for (i_count = 0U; i_count < length; i_count++)
       {
           checksum_packet += data[i_count];
       }
       cmsg->msg[3] = (uint8_t)((uint8_t)(~checksum_packet) + 1U);

       // Calculate the header checksum
       for (i_count = 0U; i_count < 8U; i_count++)
       {
           checksum_header += cmsg->msg[i_count];
       }
       cmsg->msg[2] = (uint8_t)((uint8_t)(~checksum_header) + 1U);

       cmsg->msg_valid = 1U;

       ec = 0;
   }

   return ec;
}


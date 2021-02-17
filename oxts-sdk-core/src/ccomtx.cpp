/*********************************************************************
* FileName:        ccomtx.c
* Description:     Functions to construct, store and send packets.
********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "oxts/core/ccomtx.h"
#include "oxts/core/BasicTypes.h"


int BuildCComPkt(CCOM_MSG *ccom_msg, const unsigned char* data, const unsigned int length)
{
   unsigned char checksum_header = 0;
   unsigned char checksum_packet = 0;
   uint16_t i_count = 0;

   if (ccom_msg == NULL)
      return -1;

   ccom_msg->msg_valid = 0;

   if (data == NULL || (length + 8) > CCOM_BUFF_SIZE || ccom_msg->version != CCOM_RES)
      return -1;
   //! \todo check type
   //else if (((ccom_msg->type & 0xFF) == Enum__CCOM_CAT_INVALID) || ((ccom_msg->type & 0xFF00) >> 8) >= Enum__CCOM_CAT_TYPE_UNKNOWN)
   //   return -1;

   ccom_msg->msg_len = length + 8;

   // Finalise the header
   ccom_msg->msg[0] = CCOM_SYNC;
   ccom_msg->msg[1] = CCOM_RES;
   ccom_msg->msg[2] = 0;// will be filled with the header checksum
   ccom_msg->msg[3] = 0;// will be filled with the packet checksum
   ccom_msg->msg[4] = (unsigned char)(ccom_msg->msg_len & 0xFF);
   ccom_msg->msg[5] = (unsigned char)((ccom_msg->msg_len & 0xFF00) >> 8);
   ccom_msg->msg[6] = (unsigned char)(ccom_msg->type & 0xFF);
   ccom_msg->msg[7] = (unsigned char)((ccom_msg->type & 0xFF00) >> 8);

   // Copy the data
   memcpy(ccom_msg->msg + 8, data, length);

   // Calculate the first part of the packet checksum from the end of the header
   for (i_count = 4; i_count < 8; i_count++)
      checksum_packet += ccom_msg->msg[i_count];

   // Calculate the remaining part of the packet checksum on the data
   for (i_count = 0; i_count < length; i_count++)
      checksum_packet += data[i_count];
   ccom_msg->msg[3] = (~checksum_packet) + 1;

   // Calculate the header checksum
   for (i_count = 0; i_count < 8; i_count++)
      checksum_header += ccom_msg->msg[i_count];
   ccom_msg->msg[2] = (~checksum_header) + 1;

   ccom_msg->msg_valid = 1;

   return 0;
}


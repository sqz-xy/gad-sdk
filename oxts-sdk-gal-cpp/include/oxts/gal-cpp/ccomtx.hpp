/*********************************************************************
* FileName:        ccom_tx.h
* Description:     Header file for ccom_tx.c
********************************************************************/
#ifndef CCOMTX_HPP
#define CCOMTX_HPP

#include <cstdint>
#include <cstddef>
#include "oxts/gal-cpp/oxts_arrays.hpp"

namespace OxTS
{
    namespace Gal_Cpp
    {
        /************************************************************************************/
        /*                              CCom packet definitions                             */
        /************************************************************************************/

        static const std::uint8_t CComSync = 0x40U;
        static const std::uint8_t CComRes = 0x00U;
        static const std::uint8_t CComShort = 0x80U;

        static const std::size_t CComBuffSize = 65536U;

        class CComMsg /*PRQA S 2213 # Ignore QAC*//*PRQA S 2211 # Ignore QAC*/
        {
        private:
            // input parameters
            std::uint16_t       m_msg_type;
            std::uint8_t        m_version;

            // output 
            std::size_t         m_msg_len;
            std::uint8_t        m_msg_valid;           //!< encoded message valid
            std::array<std::uint8_t, CComBuffSize>        m_msg; //!< encoded message
        public:
            /** Constructor. */
            CComMsg();
            /** Copy contructor. */
            CComMsg(const CComMsg& other);
            /** Copy assignment operator. */
            CComMsg& operator=(const CComMsg& other);
#ifdef OXTS_ENABLE_CPP11
            /** Move contructor. */
            CComMsg(CComMsg&& other); 	/*PRQA S 1127 # Assume C++11. */
            /** Move assignment operator. */
            CComMsg& operator=(CComMsg&& other);	/*PRQA S 1127 # Assume C++11. */
#endif
            /** Encode from data */
            template<std::size_t SRC_BUFFER_SIZE>
            std::int32_t encode(const std::array<std::uint8_t, SRC_BUFFER_SIZE> &data, const std::size_t length)
            {
                int32_t ec;

                if (((length + 8U) > CComBuffSize) || (m_version != CComRes))
                {
                    ec = -1;
                }
                else
                {
                    uint8_t checksum_header = 0U;
                    uint8_t checksum_packet = 0U;
                    std::size_t i_count;

                    //! \todo check type
                    m_msg_len = static_cast<size_t>(length) + 8U;

                    // Finalise the header
                    m_msg[0U] = CComSync;
                    m_msg[1U] = CComRes;
                    m_msg[2U] = 0U;// will be filled with the header checksum
                    m_msg[3U] = 0U;// will be filled with the packet checksum
                    m_msg[4U] = static_cast<std::uint8_t>(m_msg_len & 0xFFU);
                    m_msg[5U] = static_cast<std::uint8_t>((m_msg_len & 0xFF00U) >> 8);
                    m_msg[6U] = static_cast<std::uint8_t>(m_msg_type & 0xFFU);
                    m_msg[7U] = static_cast<std::uint8_t>((m_msg_type & 0xFF00U) >> 8);

                    // Copy the data
                    std::array<uint8_t, CComBuffSize>::iterator msg_it = m_msg.begin() + 8;
                    const std::size_t items_copied = copy_array<uint8_t, SRC_BUFFER_SIZE, CComBuffSize>(data.begin(), data.end(), msg_it, m_msg.end(), length);
                    msg_it += static_cast<ptrdiff_t>(items_copied);

                    // Calculate the first part of the packet checksum from the end of the header
                    for (i_count = 4U; i_count < 8U; i_count++)
                    {
                        checksum_packet += m_msg[i_count];
                    }
                    // Calculate the remaining part of the packet checksum on the data
                    for (i_count = 0U; i_count < length; i_count++)
                    {
                        if (i_count < SRC_BUFFER_SIZE)
                        {
                            checksum_packet += data[i_count];
                        }
                    }
                    m_msg[3U] = static_cast<unsigned char>(static_cast<unsigned char>(~checksum_packet) + 1U);

                    // Calculate the header checksum
                    for (i_count = 0U; i_count < 8U; i_count++)
                    {
                        checksum_header += m_msg[i_count];
                    }
                    m_msg[2U] = static_cast<unsigned char>(static_cast<unsigned char>(~checksum_header) + 1U);

                    m_msg_valid = 1U;

                    ec = 0;
                }

                return ec;
            }

            /** Access reference to type (non-const). */
            inline std::uint16_t& msg_type() { return m_msg_type; }

            /** Access reference to msg_len (non-const). */
            inline std::size_t& msg_len() { return m_msg_len; }

            /** Access pointer to msg (const). */
            inline const std::uint8_t* msg() const { return m_msg.data(); }
        };
    }
}
#endif

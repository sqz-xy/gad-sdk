#include "oxts/gal-cpp/gad_encoders/gad_encoder_bin.hpp"
#include "oxts/gal-cpp/gad_defines.hpp"
#include "oxts/gal-cpp/basic_casts.hpp"
#include "oxts/gal-cpp/oxts_arrays.hpp"
#include <iostream>

namespace OxTS
{
	namespace Gal_Cpp
	{
        const uint16_t CCOM_PKT_GEN_AIDING = 0x0b01U;

		/** Constructor */
		GadEncoderBin::GadEncoderBin() : GadEncoder(), m_buffer_offset(0U), m_gad_size(0U),
            m_ccom_gad()
		{
            		(void)fill_array<uint8_t, MAX_BUFF>(m_buffer.begin(), m_buffer.end(), 0U);
		}

		/** Override of EncodePacket function to encode data from Gad class to a
		 *  binary CCom packet for transmission to an OxTS INS.
		 */
		void GadEncoderBin::EncodePacket(const Gad& g)
		{
			// Encode Gad
			std::int32_t ec = EncodeGadBin(g);
			// Encode CCom
            m_ccom_gad.msg_type() = CCOM_PKT_GEN_AIDING;
			(void)m_ccom_gad.encode<MAX_BUFF>(m_buffer, m_gad_size);
		}

		/** Override of the GetPacket function to retrieve the CCom message to be
		 *  sent to an INS.
		 */
		const std::uint8_t* GadEncoderBin::GetPacket()
		{
			return m_ccom_gad.msg();
		}

		/** Override of the GetPacketSize function, to retrieve the size of the
		 * generic aiding packet (wrapped in CCom) to be transmitted to an INS.
		 */
		std::size_t GadEncoderBin::GetPacketSize()
		{
			return m_ccom_gad.msg_len();
		}

        /* Private method for checking for buffer overruns. */
        bool GadEncoderBin::BufferOverrunCheck(BufferType::iterator &it, const size_t expected_data_size)
        {
            bool good;
            if ((m_buffer.end() - it) >= static_cast<ptrdiff_t>(expected_data_size)) { good = true; }
            else
            {
                std::cout << "Not enough space in the buffer to hold all data, packet is at least: " <<
                    (expected_data_size - static_cast<size_t>(m_buffer.end() - it)) << " bytes longer than the allocated buffer space" << std::endl;
                good = false;
            }
            return good;
        }

		/** Encode Gad Binary */
		int32_t GadEncoderBin::EncodeGadBin(const Gad& g)
		{
            // Clear array first of all
            (void)fill_array<uint8_t, MAX_BUFF>(m_buffer.begin(), m_buffer.end(), 0U);

            /*
              holds return errors for each step. 0 means no error occured and
              execution can continue, sets a pointer to the last position of the buffer
           */
            int32_t error_code = 0;

            /*
               Sets two pointers:
               h - the start of the data buffer which will contain the header of the GA packet
               b - part way into the buffer which is the start of the payload data of the GA packet

               Sets two offset trackers:
               h_offset - tracks offset from pointer h
               b_offset - tracks offset from pointer b
            */
            BufferType::iterator h = m_buffer.begin();

            BufferType::iterator b = h + 4; // static_cast<ptrdiff_t>(GEN_AID_HEADER_MIN_SIZE);

            /*
               Populate the header portion of the data buffer with the version and type.

               TODO: stop encoding if the gad->type is > 15 as this starts writing to first 4 bits of the byte
            */
            const uint8_t ver_type = static_cast<uint8_t>((0 << 4) | g.GetType());
            BasicCasts::cast_uint8_to_1_byte_LE<MAX_BUFF>(h, m_buffer.end(), ver_type);

            /*
               The bitmask collects the information which will be filled in as the rest
               of the payload is formed, it is initialised to 0 so if the specific if
               statement isn't reached, the bit representing each field is left as 0.
            */
            std::uint16_t bitmask = 0;

            /*
               This sets the first xDEV_ACQ.. bytes to 0 and advances the
               offset into the payload by xDEV_ACQ. This is safety incase
               the user doesn't pass a pointer to a zero'ed buffer.
               Since available_payload_size = 1024 - 4 = 1020 and b_offset = 0, no need to check overflow.
            */ 
 
            (void)fill_array<uint8_t, MAX_BUFF>(b, b + static_cast<ptrdiff_t>(XDEV_ACQUISTION_TIMESTAMP_SIZE), 0U);
            b += 8;// static_cast<ptrdiff_t>(XDEV_ACQUISTION_TIMESTAMP_SIZE);

            /*
               Encode stream ID
               Again, since available_payload_size = 1024 - 4 = 1020, and GEN_AID_HEADER_MIN_SIZE + b_offset = 4 + 8 = 12, then no need to check overflow.
            */
            BasicCasts::cast_uint8_to_1_byte_LE<MAX_BUFF>(b, m_buffer.end(), g.GetStreamId());

            /*
               This encodes the data from the struct into the buffer for each component
               of the generic aiding struct
            */

            if (error_code == 0 && g.GetValValid())
            {
                error_code = EncodeGen3d(g.GetVal(), b);
                if (error_code == 0)
                {
                    bitmask = ValueBit;
                }
            }
            if (error_code == 0 && g.GetTimeValid())
            {
                error_code = EncodeGen3d(g.GetTime(), b);
                if (error_code == 0)
                {
                    bitmask |= TimeBit;
                }
            }
            if (error_code == 0 && g.GetLocValid())
            {
                error_code = EncodeGen3d(g.GetLoc(), b);
                if (error_code == 0)
                {
                    bitmask |= LocationBit;
                }
            }
            if (error_code == 0 && g.GetRes1Valid())
            {
                error_code = EncodeGen3d(g.GetRes1(), b);
                if (error_code == 0)
                {
                    bitmask |= Res1Bit;
                }
            }
            if (error_code == 0 && g.GetRes2Valid())
            {
                error_code = EncodeGen3d(g.GetRes2(), b);
                if (error_code == 0)
                {
                    bitmask |= Res2Bit;
                }
            }
            BasicCasts::cast_uint16_to_2_byte_LE<MAX_BUFF>(h, m_buffer.end(), bitmask);
            error_code = (b != m_buffer.end()) ? 0 : 1;     // Need to check output parameter
            m_gad_size = static_cast<size_t>(b - m_buffer.begin());

            return error_code;
		}

        /* Private method to encode a specific GAD_3D part. */
        int32_t GadEncoderBin::EncodeGen3d(const Gen3d& field, BufferType::iterator &it)
        {
            int32_t i = 0;
            const size_t dims = 3U;

            if (!BufferOverrunCheck(it, (dims * sizeof(double_t)) + 3U))		// this checks that there is enough space for all fixed-size elements of GEN_3D
            {
                std::cout << "EncodeGen3d: BufferOverrunCheck failed" << std::endl;
                i = -1;
            }
            else
            {
                BasicCasts::cast_uint8_to_1_byte_LE<MAX_BUFF>(it, m_buffer.end(), field.GetMode());
                BasicCasts::cast_uint8_to_1_byte_LE<MAX_BUFF>(it, m_buffer.end(), field.GetValType());
                if (field.GetMode() == 0U)
                {
		            const container_double3_t& val = field.GetVal();
                    for (size_t d = 0U; d < dims; ++d)
                    {
			            if (d < val.size())
                       	{
				            BasicCasts::cast_double_to_8_byte_LE<MAX_BUFF>(it, m_buffer.end(), val[d]); 
			            }
			            else
			            {
				            BasicCasts::cast_double_to_8_byte_LE<MAX_BUFF>(it, m_buffer.end(), 0.0);
			            }
                    }
                    BasicCasts::cast_uint8_to_1_byte_LE<MAX_BUFF>(it, m_buffer.end(), field.GetVarType());
		            i = EncodeGen3dVar(field, it);
                }
            }

            return i;
        }

        /* Private method to encode a GEN_3D Variance. */
        int32_t GadEncoderBin::EncodeGen3dVar(const Gen3d& field, BufferType::iterator& it)
     	{
            int32_t ec = 0;

            const GEN_VAR_TYPE var_type = static_cast<GEN_VAR_TYPE>(field.GetVarType());
            const container_double6_t& field_var = field.GetVar();
            size_t var_size = 0;

            switch (var_type)
            {
#ifdef OXTS_ENABLE_CPP11
                case GEN_VAR_TYPE::GEN_VAR_VOID:		// If the variance is void, there is nothing to encode.
#else
		case GEN_VAR_VOID:				// If the variance is void, there is nothing to encode.
#endif
                {
                    break;
                }
                case GEN_VAR_SINGLE:
                {
                    var_size = 1;
                    break;
                }
                case GEN_VAR_DIAG:
                {
                    var_size = 3;
                    break;
                }
                case GEN_VAR_HMAT:
                {
                    var_size = 6;
                    break;
                }
            }
            if (var_size > 0)
            {
                if (!BufferOverrunCheck(it, (var_size * sizeof(double_t))))
                {
                    ec = -1;
                }
                else
                {
                    for (size_t d = 0U; d < var_size; ++d)
                    {
                        if ((it != m_buffer.end()) && (d < var_size))	// Second condition is to convince Helix-QAC that there is no overflow in the next line when accessing field_var
                        {
                            BasicCasts::cast_double_to_8_byte_LE<MAX_BUFF>(it, m_buffer.end(), field_var[d]);
                        }
                    }
                }
            }
            return ec;
        }
	}
}
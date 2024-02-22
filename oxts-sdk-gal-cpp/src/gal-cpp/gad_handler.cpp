#include <iostream>

#include "oxts/gal-cpp/gad_handler.hpp"

namespace OxTS
{
	namespace Gal_Cpp
	{
		/**  Constructor */


#ifdef OXTS_ENABLE_CPP11
		GadHandler::GadHandler() : m_encoder_type(ENCODER_TYPE::ENCODER_VOID), m_output_type(OUTPUT_TYPE::OUTPUT_VOID)
#else
		GadHandler::GadHandler() : m_encoder_type(ENCODER_VOID), m_output_type(OUTPUT_VOID)
#endif
		{

		}
		/** Set the output encoder to binary. */
		void GadHandler::SetEncoderToBin() 
		{ 
#ifdef OXTS_ENABLE_CPP11
			m_encoder_type = ENCODER_TYPE::ENCODER_BIN;
#else
			m_encoder_type = ENCODER_BIN;
#endif
		}
		/** Set the output encoder to csv. */
		void GadHandler::SetEncoderToCsv() 
		{ 
#ifdef OXTS_ENABLE_CPP11
			m_encoder_type = ENCODER_TYPE::ENCODER_CSV;
#else
			m_encoder_type = ENCODER_CSV;
#endif
		}

		/** Set Generic Aiding output to file
		 *  @param file_path Absolute path to the file to output the data to. Will be
		 *  created if it does not already exist.
		*/
		void GadHandler::SetOutputModeToFile(const std::string& file_path) 
		{ 
#ifdef OXTS_ENABLE_CPP11
			m_output_type = OUTPUT_TYPE::OUTPUT_FILE;
#else
			m_output_type = OUTPUT_FILE;
#endif
			m_output_file.SetFileName(file_path);
		}	
		/** Set Generic Aiding output to UDP.
		 *  @param ip The IPv4 address of the OxTS INS to send the data to.
		 */
		void GadHandler::SetOutputModeToUdp(const std::string& ip) 
		{ 
#ifdef OXTS_ENABLE_CPP11
			m_output_type = OUTPUT_TYPE::OUTPUT_UDP;
#else
			m_output_type = OUTPUT_UDP;
#endif
			m_output_udp.SetRemoteEndpoint(ip);
		}

		GadEncoder* GadHandler::get_encoder()
		{
			GadEncoder* encoder;
			switch (m_encoder_type)
			{
#ifdef OXTS_ENABLE_CPP11
				case ENCODER_TYPE::ENCODER_CSV:
				{
					encoder = &m_encoder_csv;
					break;
				}
				case ENCODER_TYPE::ENCODER_BIN:
				{
					encoder = &m_encoder_bin;
					break;
				}
#else
				case ENCODER_CSV:
				{
					encoder = &m_encoder_csv;
					break;
				}
				case ENCODER_BIN:
				{
					encoder = &m_encoder_bin;
					break;
				}
#endif // OXTS_ENABLE_CPP11
				default:
				{
					encoder = NULL;
					break;
				}
			}
			return encoder;
		}
		GadOutput* GadHandler::get_output()
		{
			GadOutput* output;
			switch (m_output_type)
			{
#ifdef OXTS_ENABLE_CPP11
				case OUTPUT_TYPE::OUTPUT_FILE:
				{
					output = &m_output_file;
					break;
				}
				case OUTPUT_TYPE::OUTPUT_UDP:
				{
					output = &m_output_udp;
					break;
				}
#else
				case OUTPUT_FILE:
				{
					output = &m_output_file;
					break;
				}
				case OUTPUT_UDP:
				{
					output = &m_output_udp;
					break;
				}
#endif // OXTS_ENABLE_CPP11
				default:
				{
					output = NULL;
					break;
				}
			}
			return output;
		}

		void GadHandler::SendPacket(const Gad& g)
		{
			//check encoder has been set
			GadEncoder* const m_encoder = get_encoder();
			GadOutput* const m_output = get_output();
			if ((m_encoder != NULL) && (m_output != NULL))
			{
				m_encoder->EncodePacket(g);
				// Send packet
				const uint8_t* const packet = m_encoder->GetPacket();
				const std::size_t packet_size = m_encoder->GetPacketSize();
				m_output->OutputPacket(packet, packet_size);
			}
			else
			{
				std::cerr << "Error encoder not set!" << std::endl;
				std::cerr << "Use SetEncoderTo... functions before attempting to send packets" << std::endl;
			}
		}
	}
}
#ifndef GAD_OUTPUT_UDP_HPP
#define GAD_OUTPUT_UDP_HPP
/** @file gad_output_udp.hpp */
#include "oxts/gal-cpp/config.h"
#include "oxts/gal-cpp/gad_output/gad_output.hpp"

#include "oxts/gal-cpp/udp_server_client.hpp"

namespace OxTS
{
	namespace Gal_Cpp
	{
		const uint16_t GAD_PORT = 50485U;

		class GadOutputUdp : public GadOutput
		{
		private:
			/** Constants. */
			static const std::size_t UDP_BUFFER_SIZE = 1024U;
			static const std::size_t ETHERNET_MTU = 1000U;
			/** Temporary buffer. */
			std::array<uint8_t, UDP_BUFFER_SIZE> m_buffer;
			/** Server to receive the GAD. */
			networking_udp::server<ETHERNET_MTU> m_udpServer;
			/** Port on the INS to recieve GAD. */
			uint16_t unitGaPort;
		public:
			/** Constructor */
			GadOutputUdp() : GadOutput(), m_buffer(), m_udpServer(), unitGaPort(GAD_PORT)
			{

			}
			void SetRemoteEndpoint(const std::string& ip)
			{
				m_udpServer.set_endpoint(ip, unitGaPort);
			}
			GadOutputUdp(const std::string& ip) : GadOutput(), m_buffer(), m_udpServer(), unitGaPort(GAD_PORT)
			{
				m_udpServer.set_endpoint(ip, unitGaPort);
			}
			/** Send the packet over UDP to the configured endpoint.
			 * @param packet Encoded data to be sent.
			 * @param packet_size Size of the packet in bytes.
			 */
			virtual void OutputPacket(const uint8_t* const packet, const std::size_t packet_size) override
			{
				(void)memcpy(m_buffer.data(), packet, packet_size);
				(void)m_udpServer.send_to_endpoint<UDP_BUFFER_SIZE>(m_buffer, packet_size);
			}
		};
	}
} // OxTS


#endif // GAD_OUTPUT_UDP_HPP
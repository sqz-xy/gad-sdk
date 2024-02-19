/**
* \file udp_server_client.h
* Simple UDP networking implementation for servers and clients.
*/
#ifndef UDP_SERVER_CLIENT
#define UDP_SERVER_CLIENT

#include "oxts/gal-cpp/Lib_Detect.hpp"
#include "oxts/gal-cpp/oxts_sockets.hpp"

#include <iostream>
#include <string>

#ifndef OXTS_CC_MSVC
#include <arpa/inet.h>
#endif

/**
* Simple UDP networking implementation for servers and clients.
*/
namespace networking_udp
{
	struct endpoint_t
	{
		std::uint32_t ip_address;
		std::uint16_t port;
	};
	/**
		---CLIENT---
		Simple UDP client program which receives data on a given port

		TODO: Boost-less code.
	*/
	class client /*PRQA S 1755 # Rule-0_1_5 should not apply as this can be consumed by 3rd party. */
	{
	private:
		// TODO
		uint16_t m_port;
	public:
		/**
		  default constructor to defer setting the local endpoint to a later time.
		  Not safe to use this constructor and not specific local port with
		*/
		client() 
			: m_port(0U)
		{}
		/**
		  \fn client
		  \brief Constructor requires a port. This will be the local port a
				  socket is opened on
		  param:
		  * port - the port on the local machine the socket will be opened on
			when receiving data
		*/
		explicit client(const uint16_t local_port) 
			: m_port(local_port)
		{}

		/**
		  sets the local port of the client which is what will be used when receiving data.

		  params:
		  * local_port - this specifies the port which incoming data will be received on when receive_from
		  and receive are called.
		*/
		void set_local_port(const uint16_t local_port)
		{
			m_port = local_port;
		}
	};

	///-------------------------------------------------------------------------------------------
	/**
		---SERVER---

		This sends a datagram over ethernet to the endpoint specified
	*/
	template<std::size_t ETHERNET_MTU>
	class server
	{
	private:
		OxTS::Lib::SimpleEthernetImpl m_ethernet;
		endpoint_t m_endpoint;
	public:
		// constructor
		explicit server() :
			m_ethernet(false),
			m_endpoint()
		{}
		/**
		  sents the remote endpoint if the server class will send a large volume of data to a single endpoint

		  params:
		  * dest_ip - the ip of the destination endpoint
		  * dest_port - port of the destination endpoint
		*/
		void set_endpoint(const std::string& dest_ip, const uint16_t dest_port)
		{
			// Set port and IP address
			m_endpoint.ip_address = inet_addr(dest_ip.c_str());
			m_endpoint.port = dest_port;
		}

		/**
		  sends what is passed in the buffer to the endpoint specified in the set_remote_endpoint function

		  params:
		  * buffer - pointer to a buffer of data which is being sent
		  * buffer_size - the amount of data in buffer to send

		  return:
		  * the number of bytes sent to the endpoint
		*/
		template<std::size_t SRC_BUFFER_SIZE>
		std::size_t send_to_endpoint(const std::array<uint8_t, SRC_BUFFER_SIZE> buffer, const std::size_t packet_size)
		{
			return send_to<SRC_BUFFER_SIZE>(buffer, packet_size, m_endpoint);
		}

		/**
		  sends what is passed in the buffer to the endpoint specified in remote_endpoint

		  params:
		  * buffer - pointer to a buffer of data which is being sent
		  * buffer_size - the amount of data in buffer to send
		  * remote_endpoint - the endpoint to send the data to

		  return:
		  * the number of bytes sent to the endpoint
		*/
		template<std::size_t SRC_BUFFER_SIZE>
		std::size_t send_to(
			const std::array<uint8_t, SRC_BUFFER_SIZE> buffer,
			const std::size_t packet_size,
			const endpoint_t &remote_endpoint)
		{
			std::size_t sent = 0U;
			try
			{
				if (m_ethernet.open(remote_endpoint.port))
				{
					sent = static_cast<std::size_t>(m_ethernet.send_to_address<SRC_BUFFER_SIZE, ETHERNET_MTU>(remote_endpoint.ip_address, buffer, packet_size));
					(void)m_ethernet.close();
				}
#ifdef EXTRA_DETAIL
				std::cout << "Sent Payload --- " << sent << "\n";
#endif
			}
			catch (const std::exception& ex)
			{
				std::cout << ex.what() << std::endl;
			}
			return sent;
		}

		/**
		  sends what is passed in the buffer to the endpoint specified in
		  remote_endpoint allowing the user to specify a specific port to send the
		  data to.

		  params:
		  * buffer - pointer to a buffer of data which is being sent
		  * buffer_size - the amount of data in buffer to send
		  * port - the port of the endpoint already specified

		  return:
		  * the number of bytes sent to the endpoint
		*/
		template<std::size_t SRC_BUFFER_SIZE>
		std::size_t send_to_port(
			const std::array<uint8_t, SRC_BUFFER_SIZE> buffer,
			const std::size_t packet_size,
			const uint16_t port)
		{
			std::size_t sent = 0U;
			try
			{
				if (m_ethernet.open(port))
				{
					sent = m_ethernet.send_to_address< SRC_BUFFER_SIZE, ETHERNET_MTU>(m_endpoint.ip_address, buffer, packet_size);
#ifdef EXTRA_DETAIL
					std::cout << "Sent Payload --- " << sent << "\n";
#endif
					(void)m_ethernet.close();
				}
			}
			catch (const std::exception& ex)
			{
				std::cout << ex.what() << std::endl;
			}
			return sent;
		}
	};
} // namespace networking_udp

#endif // UDP_SERVER_CLIENT
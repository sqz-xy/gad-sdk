#ifndef OXTS_SOCKETS_HPP
#define OXTS_SOCKETS_HPP
/** @file oxts_sockets.hpp */

#include "oxts/gal-cpp/Lib_Detect.hpp"

#ifdef OXTS_OS_WINDOWS
#define WIN32_LEAN_AND_MEAN /*PRQA S 1534 # Used by windows.h */
#include <windows.h>
#include <process.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib") /*PRQA S 1040 # Pragma is needed here. */
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#endif

#include <cstddef>
#include <cstdint>
#include "oxts/gal-cpp/oxts_arrays.hpp"

#ifndef OXTS_CC_MSVC
typedef sa_family_t ADDRESS_FAMILY;
#endif

namespace OxTS
{
	namespace Lib
	{
		//============================================================================================================
		//! \brief Windows requires a socket startup and cleanup.

		class SocketSystem
		{
		private:
			std::size_t m_ref_count;

		public:
			//!
			//! \brief Constructor.
			SocketSystem();

			//!
			//! \brief Starts up the socket system if required, and increments reference count.
			bool startup();

			//!
			//! \brief Decrements the reference count, and cleans up the socket system if no more references exist.
			bool cleanup();
		};

		//============================================================================================================
		//! \brief A very simple class to send datagram packets to a given IP address.
		class SimpleEthernetImpl /*PRQA S 2211 # Ignore QAC*//*PRQA S 2213 # Ignore QAC*//*PRQA S 2216 # Ignore QAC*//*PRQA S 2218 # Ignore QAC*/
		{
		private:
			bool     m_broadcast;
			bool     m_is_good;
			bool     m_active;
#ifdef OXTS_OS_WINDOWS
			WSADATA  m_wsaData;
			UINT_PTR m_handle;
#else
			// Perhaps unnecessary
			int32_t m_handle;
#endif
			uint16_t m_my_port;
			uint16_t m_my_given_port;
			uint16_t m_their_port;

		public:
			//--------------------------------------------------------------------------------------------------------
			//! \brief Default constructor.

			explicit SimpleEthernetImpl(const bool broadcast_);

			//--------------------------------------------------------------------------------------------------------
			//! \brief Destructor.

#ifdef OXTS_ENABLE_CPP11
			~SimpleEthernetImpl() noexcept; /*PRQA S 1130 # Assume C++11*/
#else
			~SimpleEthernetImpl();
#endif
			//--------------------------------------------------------------------------------------------------------
			//! \brief Declare all copy/move constructors and assignment operators as invalid.
#ifdef OXTS_ENABLE_CPP11
			SimpleEthernetImpl(const SimpleEthernetImpl&) = delete;  /*PRQA S 1125 # Assume C++11*/
			SimpleEthernetImpl(SimpleEthernetImpl&&) = delete;  /*PRQA S 1125 # Assume C++11*/ /*PRQA S 1127 # Assume C++11*/
			SimpleEthernetImpl &operator=(const SimpleEthernetImpl&) = delete;  /*PRQA S 1125 # Assume C++11*/
			SimpleEthernetImpl& operator=(SimpleEthernetImpl&&) = delete;  /*PRQA S 1125 # Assume C++11*/ /*PRQA S 1127 # Assume C++11*/
#endif
			//--------------------------------------------------------------------------------------------------------
			//! \brief Open.

			bool open(const uint16_t their_port_, const uint16_t my_port_ = 0U);

			//--------------------------------------------------------------------------------------------------------
			//! \brief Close.

			bool close();

			//--------------------------------------------------------------------------------------------------------
			//! \brief Send data.
			template<std::size_t SRC_BUFFER_SIZE, std::size_t MTU>
			size_t send_to_endpoint(const std::array<uint8_t, SRC_BUFFER_SIZE>& buffer, const std::size_t packet_size)
			{
				return send_to_address<SRC_BUFFER_SIZE, MTU>(UINT32_C(0xFFFFFFFF), buffer, packet_size);
			}

			//--------------------------------------------------------------------------------------------------------
			//! \brief Send data.
			template<std::size_t SRC_BUFFER_SIZE, std::size_t MTU>
			std::size_t send_to_address(const uint32_t ip, const std::array<uint8_t, SRC_BUFFER_SIZE> &buffer, const std::size_t packet_size)
			{
				size_t total_sent_bytes = 0U;
				if (m_is_good && m_active)
				{
					sockaddr_in address;
					address.sin_family = static_cast<ADDRESS_FAMILY>(AF_INET);
					address.sin_port = htons(m_their_port);
					address.sin_addr.s_addr = ip;

					// Convert to int so that MISRA is satisfied (as sendto() expects ints).
					const std::size_t len_size_t = (packet_size < SRC_BUFFER_SIZE) ? packet_size : SRC_BUFFER_SIZE;
					const std::int32_t len_i32 = static_cast<std::int32_t>(len_size_t);
					const std::int32_t mtu_i32 = static_cast<std::int32_t>(MTU);
					typename std::array<uint8_t, SRC_BUFFER_SIZE>::const_iterator src_it = buffer.begin();
					bool success = true;
					for (std::int32_t i = 0; (i < len_i32) && success; i += mtu_i32)
					{
						// Copy to temporary array
						std::array<uint8_t, MTU> this_array;
						std::int32_t send_bytes_i32 = len_i32 - i;
						if (send_bytes_i32 > mtu_i32) { send_bytes_i32 = mtu_i32; }
						std::size_t send_bytes = static_cast<std::size_t>(send_bytes_i32);
						send_bytes = copy_array<uint8_t, SRC_BUFFER_SIZE,MTU>(src_it, buffer.end(), this_array.begin(), this_array.end(), send_bytes);
						send_bytes_i32 = static_cast<int32_t>(send_bytes);
						const std::int32_t sent_bytes = sendto(
							m_handle,
							reinterpret_cast<char *>(this_array.data()),
							send_bytes_i32,
							0,
							reinterpret_cast<sockaddr*>(&address),
							static_cast<std::int32_t>(sizeof(sockaddr_in))
						);

						if (sent_bytes != send_bytes_i32)
						{
							m_is_good = false;
							success = false;		// And breaks the loop
						}
						else
						{
							src_it += static_cast<ptrdiff_t>(send_bytes_i32);
							total_sent_bytes = static_cast<std::size_t>(sent_bytes);
						}
					}
				}

				return total_sent_bytes;
			}

			//--------------------------------------------------------------------------------------------------------
			//! \brief Are we good?.

			bool good() const;

			//--------------------------------------------------------------------------------------------------------
			//! \brief Are we live?.

			bool live() const;
		};
	}
}

#endif
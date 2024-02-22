
#include "oxts/gal-cpp/oxts_sockets.hpp"

namespace OxTS
{
	namespace Lib
	{
		//!
		//! \brief Constructor.
		SocketSystem::SocketSystem() : m_ref_count(0UL)
		{
		
		}

		//!
		//! \brief Starts up the socket system if required, and increments reference count.
		bool SocketSystem::startup()
		{
			bool success = true;
#ifdef OXTS_OS_WINDOWS
			if (m_ref_count == 0UL)
			{
				WSADATA WsaData;

				if (WSAStartup(0x22U, &WsaData) != 0)
				{
					success = false;
				}
				else
				{
					success = (WsaData.wVersion > 0U);
				}
			}
#endif
			if (success)
			{
				++m_ref_count;
			}
			return success;
		}

		//!
		//! \brief Decrements the reference count, and cleans up the socket system if no more references exist.
		bool SocketSystem::cleanup()
		{
			bool success = true;
			if (m_ref_count > 0UL)
			{
				m_ref_count--;

#ifdef OXTS_OS_WINDOWS
				if (m_ref_count == 0UL)
				{
					if (WSACleanup() != 0)
					{
						success = false;
					}
				}
#endif
			}

			return success;
		}

		//!
		//! \brief Define a global socket system for use by sockets.
		static SocketSystem global_socket_system;

		//============================================================================================================
		//! \brief A very simple class to send datagram packets to a given IP address.

		//--------------------------------------------------------------------------------------------------------
		//! \brief Default constructor.

		SimpleEthernetImpl::SimpleEthernetImpl(const bool broadcast_)
			:
			m_broadcast(broadcast_),
			m_active(false),
#ifdef OXTS_OS_WINDOWS
			m_wsaData(),
			m_handle(0UL),
#else
			m_handle(0U),
#endif
			m_my_port(0U),
			m_my_given_port(0U),
			m_their_port(0U)
		{
			m_is_good = global_socket_system.startup();
		}

		//--------------------------------------------------------------------------------------------------------
		//! \brief Destructor.

#ifdef OXTS_ENABLE_CPP11
		SimpleEthernetImpl::~SimpleEthernetImpl() noexcept
#else
		SimpleEthernetImpl::~SimpleEthernetImpl()
#endif
		{
			try
			{
				(void)global_socket_system.cleanup();
				(void)close();
			}
			catch (...)
			{
				// Do nothing
			}
		}

		//--------------------------------------------------------------------------------------------------------
		//! \brief Open.

		bool SimpleEthernetImpl::open(const uint16_t their_port_, const uint16_t my_port_)
		{
			bool success = true;
			if ((!m_is_good) || m_active)
			{
				success = false;
			}
			else
			{
				m_their_port = their_port_;
				m_my_port = my_port_;

				m_handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

				if (m_handle <= 0U)
				{
					m_is_good = false;
					success = false;
				}

				if (success && m_broadcast)
				{
					const int32_t opt = 1;

					if (setsockopt(m_handle, SOL_SOCKET, SO_BROADCAST, reinterpret_cast<const char*>(&opt), static_cast<int32_t>(sizeof(opt))) < 0)
					{

					}
				}

				// Bind
				if (success)
				{
					sockaddr_in address;
					address.sin_family = static_cast<ADDRESS_FAMILY>(AF_INET);
					address.sin_port = htons(m_my_port);
					address.sin_addr.s_addr = htonl(0x0U);	// INADDR_ANY

					if (bind(m_handle, reinterpret_cast<const sockaddr*>(&address), static_cast<int32_t>(sizeof(sockaddr_in))) != 0)
					{
						m_is_good = false;
						success = false;
					}
				}

				// Find my port
				if (success)
				{
					sockaddr_in address;
#ifdef OXTS_CC_MSVC
					std::int32_t len = static_cast<int32_t>(sizeof(sockaddr_in));
					if ((getsockname(m_handle, reinterpret_cast<struct sockaddr*>(&address), &len) != 0) || (len == 0))
#else

					std::uint32_t len = static_cast<uint32_t>(sizeof(sockaddr_in));
					if ((getsockname(m_handle, reinterpret_cast<struct sockaddr*>(&address), &len) != 0) || (len == 0))
#endif
					{
						m_is_good = false;
						success = false;
					}

					if (success)
					{
						m_my_given_port = ntohs(address.sin_port);
					}
				}

				if (success)
				{
					m_active = true;
				}
			}

			return success;
		}

		//--------------------------------------------------------------------------------------------------------
		//! \brief Close.

		bool SimpleEthernetImpl::close()
		{
			bool success = true;
			if (!m_active)
			{
				success = false;
			}
			else
			{
#ifdef OXTS_OS_WINDOWS
				if (closesocket(m_handle) == SOCKET_ERROR)
				{
					m_is_good = false;
					success = false;
				}
				else
				{
					m_active = false;
				}
#else
				::close(m_handle);
				m_active = false;
#endif
			}
			return success;
		}

		//--------------------------------------------------------------------------------------------------------
		//! \brief Are we good?.

		bool SimpleEthernetImpl::good() const
		{
			return m_is_good;
		}

		//--------------------------------------------------------------------------------------------------------
		//! \brief Are we live?.

		bool SimpleEthernetImpl::live() const
		{
			return m_is_good && m_active;
		}
	}
}
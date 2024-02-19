/*********************************************************************
* FileName:        ccomtx.c
* Description:     Functions to construct, store and send packets.
********************************************************************/

#include <cstdlib>
#include <memory>

#include "oxts/gal-cpp/ccomtx.hpp"

namespace OxTS
{
    namespace Gal_Cpp
    {
        /** Constructor */
        CComMsg::CComMsg() :
            m_msg_type(0U),
            m_version(0U),
            m_msg_len(0U),
            m_msg_valid(0U),
            m_msg()
        {

        }
        /** Copy contructor. */
        CComMsg::CComMsg(const CComMsg& other) :
            m_msg_type(other.m_msg_type),
            m_version(other.m_version),
            m_msg_len(other.m_msg_len),
            m_msg_valid(other.m_msg_valid),
            m_msg(other.m_msg)
        {
            
        }

        /** Copy assignment operator. */
        CComMsg& CComMsg::operator=(const CComMsg& other)
        {
            if (this != &other)
            {
                m_msg_type = other.m_msg_type;
                m_version = other.m_version;
                m_msg_len = other.m_msg_len;
                m_msg_valid = other.m_msg_valid;
                m_msg = other.m_msg;
            }
            return *this;
        }

#ifdef OXTS_ENABLE_CPP11
        /** Move contructor. */
        CComMsg::CComMsg(CComMsg&& other) : /*PRQA S 1127 # Assume C++11 in use. */
            m_msg_type(std::move(other.m_msg_type)),
            m_version(std::move(other.m_version)),
            m_msg_len(std::move(other.m_msg_len)),
            m_msg_valid(std::move(other.m_msg_valid)),
            m_msg(other.m_msg)
        {

        }

        /** Move assignment operator. */
        CComMsg& CComMsg::operator=(CComMsg&& other)	/*PRQA S 1127 # Assume C++11 in use. */
        {
            if (this != &other)
            {
                m_msg_type = std::move(other.m_msg_type);
                m_version = std::move(other.m_version);
                m_msg_len = std::move(other.m_msg_len);
                m_msg_valid = std::move(other.m_msg_valid);
                m_msg = std::move(other.m_msg);
            }
            return *this;
        }
#endif
    }
}


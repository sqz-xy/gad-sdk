#ifndef GAD_ENCODE_HPP
#define GAD_ENCODE_HPP

#include <cstddef>
#include <cstdlib>

#include "oxts/gal-cpp/gad.hpp"

namespace OxTS
{
	namespace Gal_Cpp
	{
		static const std::size_t MAX_BUFF = 1024U;

		/**
		 * Interface class to bring together GAD encoding to binary (for UDP output) and
		 * string (for csv output).
		 */
		class GadEncoder /*PRQA S 2211 # Ignore QAC */ /*PRQA S 2218 # Ignore QAC */ /*PRQA S 2216 # Ignore QAC *//*PRQA S 2213 # Ignore QAC */
		{
		public:
			/** Virtual Destructor. */
			virtual ~GadEncoder() { }
			/** Encode data in the Gad class to either binary or csv string */
			virtual void EncodePacket(const Gad& g) = 0;
			/** Get the encoded packet.
			 * @return The packet as an unsigned char array
			 */
			virtual const uint8_t* GetPacket() = 0;
			/** Get the size of the encoded packet (bytes).
			 * @return Size of the packet.
			 */
			virtual std::size_t  GetPacketSize() = 0;
		};
	}
}

#endif // GAD_ENCODE_HPP
#ifndef GAD_ENCODE_HPP
#define GAD_ENCODE_HPP

#include <cstddef>
#include <iostream>
#include <cstdlib>

#include "oxts/core/ccomtx.h"
#include "oxts/gal-c/gad_encode_bin.h"
#include "oxts/gal-c/gad_encode_csv.h"
#include "oxts/gal-cpp/gad.hpp"

const uint16_t CCOM_PKT_GEN_AIDING = 0x0b01;

namespace OxTS
{
	const int MAX_BUFF = 1024;

	/**
	 * Interface class to bring together GAD encoding to binary (for UDP output) and
	 * string (for csv output).
	 */
	class GadEncoder
	{
	protected:
		static const std::size_t buffer_size = MAX_BUFF;
		unsigned char buffer[buffer_size];
		std::size_t buffer_offset;
		std::size_t gad_size;
	public:
		GadEncoder()
		{
			buffer_offset = 0;
			gad_size = 0;
		}
		/** Virtual Destructor. */
		virtual ~GadEncoder() = default;
		/** Encode data in the Gad class to either binary or csv string */
		virtual void EncodePacket(Gad& g) = 0;
		/** Get the encoded packet.
		 * @return The packet as an unsigned char array
		 */
		virtual unsigned char* GetPacket() = 0;
		/** Get the size of the encoded packet (bytes).
		 * @return Size of the packet.
		 */
		virtual std::size_t  GetPacketSize() = 0;

	};
}

#endif // GAD_ENCODE_HPP
#ifndef GAD_OUTPUT_HPP
#define GAD_OUTPUT_HPP

#include <cstddef>
#include <cstdint>
#include "oxts/gal-cpp/basic_types.hpp"

namespace OxTS
{
	namespace Gal_Cpp
	{
		/**
		 * Virtual interface class for different methods of outputting GAD.
		 */
		class GadOutput /*PRQA S 2216 # Ignore QAC*//*PRQA S 2213 # Ignore QAC*//*PRQA S 2218 # Ignore QAC*//*PRQA S 2211# Ignore QAC*/
		{
		private:

		public:
			/** Virtual destructor. */
			virtual ~GadOutput() { }

			/**
			 * Output a GAD packet
			 */
			virtual void OutputPacket(const std::uint8_t* const packet, const std::size_t packet_size) = 0;
		};
	}
}

#endif //GAD_OUTPUT_HPP
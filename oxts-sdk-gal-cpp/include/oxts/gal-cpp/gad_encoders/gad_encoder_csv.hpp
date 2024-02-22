#ifndef GAD_ENCODER_CSV_HPP
#define GAD_ENCODER_CSV_HPP
/** @file gad_encoder_csv.hpp */

#include "oxts/gal-cpp/gad_encoders/gad_encoder.hpp"

#include <sstream>
#include <string>
#include <iomanip>

namespace OxTS
{
	namespace Gal_Cpp
	{
		/**
		 * Wrapper for C Generic Aiding csv encoding functionality.
		 *
		 * @todo Implement this csv encoding wrapper.
		 */
		class GadEncoderCsv : public GadEncoder
		{
		private:
			std::stringstream m_str_stream;
			/** Storage for the string produced by m_str_stream. */
			std::string m_str;

			/** Private templated method to write a string to the CSV file. */
			template<typename T>
			bool Write(const T& val, const bool end_comma=true)
			{
				if (m_str_stream.good())
				{
					m_str_stream << val; /*PRQA S 3840 # Seems to think it's using an array type? */
					if  (m_str_stream.good() && end_comma)
					{
						m_str_stream << ",";
					}
				}
				return m_str_stream.good();
			}

			/** Private templated method to write a string to the CSV file. */
			template<typename T>
			bool WriteWithDecimalPlaces(const T& val, const uint32_t decimal_places, const bool end_comma=true)
			{
				if (m_str_stream.good())
				{
					if (decimal_places > 0U)
					{
						m_str_stream << std::fixed << std::setprecision(static_cast<std::streamsize>(decimal_places));
					}
					m_str_stream << val;
					if (m_str_stream.good() && end_comma)
					{
						m_str_stream << ",";
					}
				}
				return m_str_stream.good();
			}

			/** Private method to write a flag and value (or blank if flag false) to CSV. */
			template<typename T>
			bool WriteFlagAndValue(const bool flag, const T& val)
			{
				bool i = false;
				const std::int32_t flag_value = (flag ? 1 : 0);
				if (Write<std::int32_t>(flag_value))
				{
					if (flag)
					{
						i = Write<T>(val);
					}
					else
					{
						i = Write("");	// Comma gets added
					}
				}
				return i;
			}

			/** Private method to write Gen3D header to CSV. */
			bool WriteGen3dHeader(const bool end_comma=true);

			/** Private method to write header to CSV. */
			int32_t WriteHeader();

			/** Private method to write Gen3D to file. */
			bool WriteGen3d(const bool valid_flag, const Gen3d& gen_3d_data, const bool end_comma=true);

			/** Private method to encode GAD to CSV. */
			void EncodeGadCsv(const Gad& g);
		public:

			/** Constructor */
			GadEncoderCsv();
			/** Encode the generic aiding packet to csv format.
				* @param g Reference to the Gad data to be encoded.
				*/
			virtual void EncodePacket(const Gad& g) override;
			/** Retrieve the encoded packet
			 * @return Char array containing the packet encoded in csv form.
			*/
			virtual const uint8_t* GetPacket() override;
			/**
			 * @return The encoded packet size (bytes)
			*/
			virtual std::size_t GetPacketSize() override;
		};
	}
}


#endif // GAD_ENCODER_CSV_HPP

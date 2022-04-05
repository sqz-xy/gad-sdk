#ifndef GAD_ENCODER_CSV_HPP
#define GAD_ENCODER_CSV_HPP
/** @file gad_encoder_csv.hpp */

#include "oxts/gal-cpp/gad_encoders/gad_encoder.hpp"

namespace OxTS
{
	/**
	 * Wrapper for C Generic Aiding csv encoding functionality.
	 *
	 * @todo Implement this csv encoding wrapper.
	 */
	class GadEncoderCsv : public GadEncoder
	{

	private:
		inline void EncodeGadCsv(Gad& g)
		{
			GEN_AIDING_DATA genaid = g.getCStruct();
			encode_gad_to_csv(out_string, offset_ptr, &genaid);
		}

		char* out_string;
		int offset;
		int* offset_ptr;
	public:

		/** Constructor */
		GadEncoderCsv()
		{
			offset = 0;
			offset_ptr = &offset;
			buffer_offset = 0;
			gad_size = 0;
			out_string = (char*)malloc(MAX_BUFF);
		}

		/** Encode the generic aiding packet to csv format.
		 * @param g Reference to the Gad data to be encoded.
		 */
		void EncodePacket(Gad& g) override
		{
			memset(buffer, 0, MAX_BUFF);    // Clear buffer
			offset = 0;                     // Set offset to 0
			EncodeGadCsv(g);                      // Encode Gad
		}
		/** Retrieve the encoded packet
		 * @return Char array containing the packet encoded in csv form.
		*/
		unsigned char* GetPacket() override
		{
			return reinterpret_cast<unsigned char*>(out_string);
		}
		/**
		 * @return The encoded packet size (bytes)
		*/
		std::size_t GetPacketSize() override
		{
			return offset;
		}
	};
}


#endif // GAD_ENCODER_CSV_HPP
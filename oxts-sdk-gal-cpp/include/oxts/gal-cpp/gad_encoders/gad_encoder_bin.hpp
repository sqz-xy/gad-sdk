#ifndef GAD_ENCODER_BIN_HPP
#define GAD_ENCODER_BIN_HPP
/** @file gad_encoder_bin.hpp */

#include "oxts/gal-cpp/gad_encoders/gad_encoder.hpp"
#include "oxts/gal-cpp/ccomtx.hpp"

namespace OxTS
{
	namespace Gal_Cpp
	{
	/**
	 * Wrapper for C Generic Aiding binary encoding functionality.
	 */
		class GadEncoderBin : public GadEncoder
		{
		private:
			typedef std::array<std::uint8_t, MAX_BUFF> BufferType;
			static const std::size_t m_buffer_size = MAX_BUFF;
			BufferType m_buffer;
			std::size_t m_buffer_offset;
			std::size_t m_gad_size;
			CComMsg m_ccom_gad;

			/* Private method to encode the GAD portion. */
			int32_t EncodeGadBin(const Gad& g);

			/* Private method to encode a specific GEN_3D part. */
			int32_t EncodeGen3d(const Gen3d& field, BufferType::iterator &it);

			/* Private method to encode a GEN_3D Variance. */
			int32_t EncodeGen3dVar(const Gen3d& field, BufferType::iterator &it);

			/* Private method for checking for buffer overruns. */
			bool BufferOverrunCheck(BufferType::iterator &it, const size_t expected_data_size);
		public:
			/** Constructor */
			GadEncoderBin();

			/** Override of EncodePacket function to encode data from Gad class to a
			 *  binary CCom packet for transmission to an OxTS INS.
			 */
			virtual void EncodePacket(const Gad& g) override;

			/** Override of the GetPacket function to retrieve the CCom message to be
			 *  sent to an INS.
			 */
			virtual const std::uint8_t* GetPacket()  override;

			/** Override of the GetPacketSize function, to retrieve the size of the
			 * generic aiding packet (wrapped in CCom) to be transmitted to an INS.
			 */
			virtual std::size_t GetPacketSize() override;
		};
	}
}

#endif // GAD_ENCODER_BIN

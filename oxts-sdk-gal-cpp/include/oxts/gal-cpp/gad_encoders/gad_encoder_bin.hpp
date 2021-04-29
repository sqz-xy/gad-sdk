#ifndef GAD_ENCODER_BIN_HPP
#define GAD_ENCODER_BIN_HPP
/** @file gad_encoder_bin.hpp */

#include "oxts/gal-cpp/gad_encoders/gad_encoder.hpp"

namespace OxTS
{

/**
 * Wrapper for C Generic Aiding binary encoding functionality.
 */
class GadEncoderBin : public GadEncoder 
{
private:

  auto EncodeGen3d(Gen3d& g) -> int
  {
    return encode_gen_3d(GEN_3D(g), this->buffer, &this->buffer_offset, OxTS::GadEncoderBin::buffer_size);
  }

  auto EncodeGen3dVar(Gen3d& g) -> int
  {
    return encode_gen_3d_var(GEN_3D(g), this->buffer, &this->buffer_offset, OxTS::GadEncoderBin::buffer_size);
  }

  auto BufferOverrunCheck(size_t expected_data_size) -> int const
  {
    return buffer_overrun_chk(OxTS::GadEncoderBin::buffer_size, expected_data_size);
  }

  auto EncodeGadBin(Gad& g ) -> int
  {
    // Copy Gad -> GEN_AIDING_DATA
    GEN_AIDING_DATA genaid = g.getCStruct();
    return encode_gen_aid(&genaid, this->buffer, OxTS::GadEncoderBin::buffer_size,&this->gad_size);
  }

  CCOM_MSG ccom_gad;
public:
  /** Constructor */
  GadEncoderBin()
  {
    this->buffer_offset = 0;
    this->gad_size = 0;
  }
  /** Override of EncodePacket function to encode data from Gad class to a 
   *  binary CCom packet for transmission to an OxTS INS.
   */
  void EncodePacket(Gad& g) override
  {
    // Encode Gad
    EncodeGadBin(g);
    // Encode CCom
    memset(&this->ccom_gad, 0, sizeof(CCOM_MSG));
    this->ccom_gad.type = (CCOM_PKT_GEN_AIDING);
    BuildCComPkt(&this->ccom_gad, this->buffer, this->gad_size);
  }
  /** Override of the GetPacket function to retrieve the CCom message to be 
   *  sent to an INS.
   */
  auto GetPacket() -> unsigned char * override
  {
    return this->ccom_gad.msg;
  }
  /** Override of the GetPacketSize function, to retrieve the size of the 
   * generic aiding packet (wrapped in CCom) to be transmitted to an INS.
   */
  auto GetPacketSize() -> std::size_t override
  {
    return this->ccom_gad.msg_len;
  }


};

}

#endif // GAD_ENCODER_BIN
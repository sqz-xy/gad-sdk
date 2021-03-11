#ifndef GAD_ENCODER_BIN_HPP
#define GAD_ENCODER_BIN_HPP
/** @file gad_encoder_bin.hpp */

#include "oxts/gal-cpp/gad_encoder.hpp"

namespace OxTS
{

/**
 * Wrapper for C Generic Aiding binary encoding functionality.
 */
class GadEncoderBin : public GadEncoder 
{
private:

  inline int EncodeGen3d(Gen3d& g)
  {
    return encode_gen_3d(*g, this->buffer, &this->buffer_offset, this->buffer_size);
  }

  inline int EncodeGen3dVar(Gen3d& g)
  {
    return encode_gen_3d_var(*g, this->buffer, &this->buffer_offset, this->buffer_size);
  }

  inline int BufferOverrunCheck(size_t expected_data_size)
  {
    return buffer_overrun_chk(this->buffer_size, expected_data_size);
  }

  inline int EncodeGadBin(Gad& g )
  {
    // Copy Gad -> GEN_AIDING_DATA
    GEN_AIDING_DATA genaid = g.getCStruct();
    return encode_gen_aid(&genaid, this->buffer, this->buffer_size,&this->gad_size);
  }

public:

  GadEncoderBin()
  {
    this->buffer_offset = 0;
    this->gad_size = 0;
  }

  inline void EncodePacket(Gad& g) override
  {
    // Encode Gad
    EncodeGadBin(g);
    // Encode CCom
    memset(&this->ccom_gad, 0, sizeof(CCOM_MSG));
    this->ccom_gad.type = (CCOM_PKT_GEN_AIDING);
    BuildCComPkt(&this->ccom_gad, this->buffer, this->gad_size);
  }

  inline virtual unsigned char * GetPacket() override
  {
    return this->ccom_gad.msg;
  }

  inline virtual std::size_t GetPacketSize() override
  {
    return this->ccom_gad.msg_len;
  }


  CCOM_MSG ccom_gad;
};

}

#endif // GAD_ENCODER_BIN
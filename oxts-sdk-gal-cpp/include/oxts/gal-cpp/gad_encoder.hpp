#ifndef GAD_ENCODE_HPP
#define GAD_ENCODE_HPP

#include <cstddef>

#include "oxts/core/ccomtx.h"
#include "oxts/gal-c/gad_encode_bin.h"
#include "oxts/gal-cpp/gad.hpp"

#define CCOM_PKT_GEN_AIDING  (0x0b01)

/**
 * Interface class to bring together GAD encoding to binary (for UDP output) and
 * string (for csv output).
 */
class GadEncoder
{
private:

public:
  /** Virtual Destructor. */
  virtual ~GadEncoder() {}
  /** Encode data in the Gad class to either binary or csv string */
  virtual void EncodePacket(Gad& g) = 0;

  virtual unsigned char * GetPacket() = 0;

  virtual std::size_t GetPacketSize() = 0;
};



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
    return encode_gen_aid(&genaid, this->buffer, this->buffer_size,&current_packet_size);
  }

public:

  GadEncoderBin()
  {
    buffer_offset = 0;
    current_packet_size = 0;
  }

  inline void EncodePacket(Gad& g) override
  {
    // Encode Gad
    EncodeGadBin(g);
    // Encode CCom
    memset(&ccom_gad, 0, sizeof(CCOM_MSG));
    ccom_gad.type = (CCOM_PKT_GEN_AIDING);
    BuildCComPkt(&ccom_gad, buffer, current_packet_size);
  }

  inline virtual unsigned char * GetPacket() override
  {
    return this->buffer;
  }

  virtual std::size_t GetPacketSize() override
  {
    return current_packet_size;
  }

  static const std::size_t buffer_size = 1024;
  unsigned char buffer[buffer_size];
  std::size_t buffer_offset;
  std::size_t current_packet_size;
  CCOM_MSG ccom_gad;
};

/**
 * Wrapper for C Generic Aiding csv encoding functionality.
 * 
 * @todo Implement this csv encoding wrapper.
 */
class GadEncoderCsv : public GadEncoder
{
  /** Constructor */
  GadEncoderCsv(){}
};




#endif // GAD_ENCODE_HPP
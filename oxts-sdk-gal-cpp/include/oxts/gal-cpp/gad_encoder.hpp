#ifndef GAD_ENCODE_HPP
#define GAD_ENCODE_HPP

#include <cstddef>

#include "oxts/core/ccomtx.h"
#include "oxts/gal-c/gad_encode_bin.h"
#include "oxts/gal-cpp/gad.hpp"

/**
 * Interface class to bring together GAD encoding to binary (for UDP output) and
 * string (for csv output).
 */
class GadEncoder
{
private:


public:
  /** Constructor */
  GadEncoder(); 
  /** Virtual Destructor. */
  virtual ~GadEncoder() {}
  /** Encode data in the Gad class to either binary or csv string */
  virtual int EncodePacket(Gad g) = 0;
};



/**
 * Wrapper for C Generic Aiding binary encoding functionality.
 */
class GadEncoderBin : GadEncoder
{
private:

  int EncodeGen3d(Gen3d& g)
  {
    return encode_gen_3d(*g, *this->data, &this->buffer_offset, this->buffer_size);
  }

  int EncodeGen3dVar(Gen3d& g)
  {
    return encode_gen_3d_var(*g, *this->data, &this->buffer_offset, this->buffer_size);
  }

  int BufferOverrunCheck(size_t expected_data_size)
  {
    return buffer_overrun_chk(this->buffer_size, expected_data_size);
  }

public:

  int EncodeGad(Gad g )
  {
    //return encode_gen_aid(GEN_AIDING_DATA* gad, unsigned char* buffer, size_t buffer_size, size_t* packet_size);
  }

  virtual int EncodePacket()
  {
    // Encode Gad

    // Encode CCom

    return 0;
  }

  static const std::size_t buffer_size = 1024;
  unsigned char * data[buffer_size];
  std::size_t buffer_offset = 0;
};






#endif // GAD_ENCODE_HPP
#ifndef GAD_ENCODE_HPP
#define GAD_ENCODE_HPP

#include <cstddef>
#include <iostream>
#include <stdlib.h>

#include "oxts/core/ccomtx.h"
#include "oxts/gal-c/gad_encode_bin.h"
#include "oxts/gal-c/gad_encode_csv.h"
#include "oxts/gal-cpp/gad.hpp"

#define CCOM_PKT_GEN_AIDING  (0x0b01)

namespace OxTS
{


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
  /** Get the encoded packet.
   * @return The packet as an unsigned char array
   */
  virtual unsigned char * GetPacket() = 0;
  /** Get the size of the encoded packet (bytes).
   * @return Size of the packet.
   */
  virtual std::size_t GetPacketSize() = 0;

  static const std::size_t buffer_size = 1024;
  unsigned char buffer[buffer_size];
  std::size_t buffer_offset;
  std::size_t gad_size;
};

}



#endif // GAD_ENCODE_HPP
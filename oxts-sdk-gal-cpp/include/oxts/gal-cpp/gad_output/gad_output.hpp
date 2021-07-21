#ifndef GAD_OUTPUT_HPP
#define GAD_OUTPUT_HPP

namespace OxTS
{

/**
 * Virtual interface class for different methods of outputting GAD.
 */
class GadOutput
{
private:

public:
  /**
   * Output a GAD packet
   */
  void virtual OutputPacket(unsigned char * packet, int packet_size) = 0;
};


}

#endif //GAD_OUTPUT_HPP
#ifndef GAD_OUTPUT_HPP
#define GAD_OUTPUT_HPP

class GadOutput
{
private:

public:
  void virtual OutputPacket(unsigned char * packet, int packet_size) = 0;
};



#endif //GAD_OUTPUT_HPP
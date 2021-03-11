#ifndef GAD_OUTPUT_UDP_HPP
#define GAD_OUTPUT_UDP_HPP

#include "oxts/gal-cpp/gad_output.hpp"
#include "oxts/gal-cpp/udp_server_client.h"

namespace OxTS
{

class GadOutputUdp : public GadOutput
{
private:

public:
  /** Constructor */
  GadOutputUdp(std::string ip)
  {
    this->udpServer_.reset(new networking_udp::server());
    udpServer_->set_remote_endpoint(ip, unitGaPort);
  }
  /** Send the packet over UDP to the configured endpoint.
   * @param packet Encoded data to be sent.
   * @param packet_size Size of the packet in bytes.
   */
  void virtual OutputPacket(unsigned char * packet, int packet_size) override
  {
    udpServer_->send(packet, packet_size);
  }

  /** Server to receive the GAD. */
  std::shared_ptr<networking_udp::server> udpServer_;
  /** Port on the INS to recieve GAD. */
  short unitGaPort = 50485;
};

}


#endif // GAD_OUTPUT_UDP_HPP
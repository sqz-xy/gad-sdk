#ifndef GAD_OUTPUT_UDP_HPP
#define GAD_OUTPUT_UDP_HPP
/** @file gad_output_udp.hpp */
#include "oxts/gal-cpp/config.h"
#include "oxts/gal-cpp/gad_output/gad_output.hpp"

#ifndef OXTS_SDK_DISABLE_BOOST
#include "oxts/gal-cpp/udp_server_client.h"
#endif

namespace OxTS
{
#ifndef OXTS_SDK_DISABLE_BOOST
class GadOutputUdp : public GadOutput
{
private:
  /** Server to receive the GAD. */

  std::shared_ptr<networking_udp::server> udpServer_;
  /** Port on the INS to recieve GAD. */
  short unitGaPort = 50485;
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
  void OutputPacket(unsigned char * packet, int packet_size) override
  {
    udpServer_->send(packet, packet_size);
  }
};
#else
class GadOutputUdp : public GadOutput
{
private:

  short unitGaPort = 50485;
public:
  /** Constructor */
  GadOutputUdp(std::string ip){  }
  /** Send the packet over UDP to the configured endpoint.
   * @param packet Encoded data to be sent.
   * @param packet_size Size of the packet in bytes.
   */
  void virtual OutputPacket(unsigned char * packet, int packet_size) override
  {
    // Send Packet to unit endpoint (Unit IP, Port 50485)
  }
};
#endif // OXTS_SDK_DISABLE_BOOST

} // OxTS


#endif // GAD_OUTPUT_UDP_HPP
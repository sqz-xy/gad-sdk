#ifndef GAD_HANDLER_HPP
#define GAD_HANDLER_HPP

#include <memory>

#include "oxts/gal-cpp/gad_encoder.hpp"
#include "oxts/gal-cpp/gad_output_udp.hpp"
#include "oxts/gal-cpp/gad_output_file.hpp"

namespace OxTS
{

class GadHandler
{
private:

public:
  /**  Constructor */
  GadHandler(GadEncoder *encoder_strategy = nullptr) : encoder_(encoder_strategy){ }
  /** Generic Aiding encoder. Can be to binary or csv */
  std::shared_ptr<GadEncoder> encoder_;
  /** Set the output encoder to binary. */
  void SetEncoderToBin() { this->encoder_.reset(new GadEncoderBin()); }
  /** Set the output encoder to csv. */
  void SetEncoderToCsv() { this->encoder_.reset(new GadEncoderCsv()); }
  /** Generic Aiding output. Can be to file or UDP */
  std::shared_ptr<GadOutput> output_;
  void SetOutputModeToFile(std::string file_path) { this->output_.reset(new GadOutputFile(file_path));}
  void SetOutputModeToUdp(std::string ip)  { this->output_.reset(new GadOutputUdp(ip)); }

  /** Send packet */
  void SendPacket(Gad g)
  {
    this->encoder_->EncodePacket(g);
    // Send packet
    this->output_->OutputPacket(this->encoder_->GetPacket(), 
                                this->encoder_->GetPacketSize()
                                );
  }
};

}

#endif // GAD_HANDLER_HPP
#ifndef GAD_HANDLER_HPP
#define GAD_HANDLER_HPP
/** @file gad_handler.hpp */
#include <memory>

#include "oxts/gal-cpp/gad_encoders/gad_encoder.hpp"
#include "oxts/gal-cpp/gad_encoders/gad_encoder_bin.hpp"
#include "oxts/gal-cpp/gad_encoders/gad_encoder_csv.hpp"
#include "oxts/gal-cpp/gad_output/gad_output_udp.hpp"
#include "oxts/gal-cpp/gad_output/gad_output_file.hpp"

namespace OxTS
{

/** Class to handle encoding and sending Generic Aiding packets. This can be to 
 *  an INS in real time via UDP or to a .gad csv file.
 */
class GadHandler
{
private:
  std::shared_ptr<GadEncoder> encoder_;
  std::shared_ptr<GadOutput> output_;

public:
  /**  Constructor */
  GadHandler(GadEncoder *encoder_strategy = nullptr) : encoder_(encoder_strategy){ }
  
  /** Set the output encoder to binary. */
  void SetEncoderToBin() { this->encoder_.reset(new GadEncoderBin()); }
  /** Set the output encoder to csv. */
  void SetEncoderToCsv() { this->encoder_.reset(new GadEncoderCsv()); }

  /** Set Generic Aiding output to file 
   *  @param file_path Absolute path to the file to output the data to. Will be 
   *  created if it does not already exist.
  */
  void SetOutputModeToFile(std::string file_path) { this->output_.reset(new GadOutputFile(file_path));}
  /** Set Generic Aiding output to UDP.
   *  @param ip The IPv4 address of the OxTS INS to send the data to.
   */
  void SetOutputModeToUdp(std::string ip)  { this->output_.reset(new GadOutputUdp(ip)); }

  /** Send packet via pre-configured output method.
   *  @param g Generic Aiding data to be encoded and sent 
  */
  void SendPacket(Gad g);
};

} // OxTS

#endif // GAD_HANDLER_HPP
#ifndef GAD_HANDLER_HPP
#define GAD_HANDLER_HPP

#include <memory>

#include "oxts/gal-cpp/gad_encoder.hpp"

// 


namespace OxTS
{


class GadOutput
{
private:

public:
  void virtual OutputPacket(unsigned char * packet) = 0;

};


class GadOutputFile : public GadOutput
{
private:

public:
  /** Constructor */
  GadOutputFile(std::string file_path) : source_id(file_path)
  {
    this->file_ptr  = fopen(source_id.c_str(), "w+");
  }

  ~GadOutputFile()
  {
    fclose(file_ptr);
  }

  /** Output the packet to file */
  void virtual OutputPacket(unsigned char * packet) override
  {
    fprintf(file_ptr, "%s", packet);
    fflush(file_ptr);
  }

  std::string source_id; /** Path to file (include .gad extension) */
  FILE * file_ptr;       /** Pointer to file handler object */
};

// class GadOutputUdp : public GadOutput
// {
// private:

// public:
//   /** Constructor */
//   GadOutputUdp()
//   {

//   }

//   void virtual OutputPacket(unsigned char * packet) override
//   {

//   }

//   networking_udp::server udpServer;
//   short unitGaPort = 50485;
//   udpServer.set_remote_endpoint(unitIp, unitGaPort);
// };


class GadHandler
{
private:


public:
  GadHandler(GadEncoder *encoder_strategy = nullptr) : encoder_(encoder_strategy){ }

  /** Destructor */
  // ~GadHandler();


  /** Generic Aiding encoder. Can be to binary or csv */
  std::shared_ptr<GadEncoder> encoder_;
  /** Set the output encoder to binary. */
  void SetEncoderToBin() { this->encoder_.reset(new GadEncoderBin()); }
  /** Set the output encoder to csv. */
  void SetEncoderToCsv() { this->encoder_.reset(new GadEncoderCsv()); }

  /** Generic Aiding output. Can be to file or UDP */
  std::shared_ptr<GadOutput> output_;
  void SetOutputModeToFile(std::string file_path) { this->output_.reset(new GadOutputFile(file_path));}
  // void SetOutputModeToUdp()  { this->output_.reset(new GadOutputUdp()); }


};

}

#endif // GAD_HANDLER_HPP
#ifndef GAD_OUTPUT_HPP
#define GAD_OUTPUT_HPP

#include <memory>

#include "oxts/gal-cpp/gad_encoder.hpp"


class GadOutput
{
private:


public:
  GadOutput(GadEncoder *encoder_strategy = nullptr) : encoder_(encoder_strategy){ }

  /** Destructor */
  ~GadOutput(){ }


  /** Generic Aiding encoder. Can be to binary or csv */
  std::shared_ptr<GadEncoder> encoder_;
  /** Set the output encoder to binary. */
  void SetEncoderToBin() { this->encoder_.reset(new GadEncoderBin()); }
  // void SetEncoderToCsv() {this->encoder_.reset(new GadEncoderCsv());}

  /** Sending */
};


#endif // GAD_OUTPUT_HPP
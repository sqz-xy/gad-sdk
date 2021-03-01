#ifndef GAD_OUTPUT_HPP
#define GAD_OUTPUT_HPP

#include <memory>

#include "oxts/gal-cpp/gad_encoder.hpp"


class GadOutput
{
private:


public:
  GadOutput(GadEncoder *encoder_strategy = nullptr) : encoder_(encoder_strategy){ }

  /** Generic Aiding encoder. Can be to binary or csv */
  std::shared_ptr<GadEncoder> encoder_;

  /** Destructor */
  ~GadOutput(){ }

  // Ability to change encoder functionality is provided by .reset() from smart
  // pointer class. 

};


#endif // GAD_OUTPUT_HPP
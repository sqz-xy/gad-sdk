#ifndef GAD_OUTPUT_FILE_HPP
#define GAD_OUTPUT_FILE_HPP
/** @file gad_output_file.hpp */

#include "oxts/gal-cpp/gad_output/gad_output.hpp"

namespace OxTS
{

class GadOutputFile : public GadOutput
{
private:

public:
  /** Constructor */
  GadOutputFile(std::string file_path) : file_out(file_path)
  {
    this->file_ptr  = fopen(file_out.c_str(), "w+");
  }
  /** Destructor */
  ~GadOutputFile()
  {
    fclose(file_ptr);
  }

  /** Output the packet to file */
  void virtual OutputPacket(unsigned char * packet, int packet_size) override
  {
    fprintf(file_ptr, "%s", packet);
    fflush(file_ptr);
  }

  std::string file_out; /** Path to file (include .gad extension) */
  FILE * file_ptr;       /** Pointer to file handler object */
};

}


#endif // GAD_OUTPUT_FILE_HPP
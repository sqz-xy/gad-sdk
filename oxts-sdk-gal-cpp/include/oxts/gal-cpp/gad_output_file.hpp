#ifndef GAD_OUTPUT_FILE_HPP
#define GAD_OUTPUT_FILE_HPP
/** @file gad_output_file.hpp */

#include "oxts/gal-cpp/gad_output.hpp"

namespace OxTS
{

class GadOutputFile : public GadOutput
{
private:

public:
  /** Constructor */
  GadOutputFile(std::string file_path) : source_id(file_path)
  {
    this->file_ptr  = fopen(source_id.c_str(), "w+");
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

  std::string source_id; /** Path to file (include .gad extension) */
  FILE * file_ptr;       /** Pointer to file handler object */
};

}


#endif // GAD_OUTPUT_FILE_HPP
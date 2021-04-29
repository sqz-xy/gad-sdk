#ifndef GAD_OUTPUT_FILE_HPP
#define GAD_OUTPUT_FILE_HPP
/** @file gad_output_file.hpp */

#include <string>

#include "oxts/gal-cpp/gad_output/gad_output.hpp"

namespace OxTS
{

class GadOutputFile : public GadOutput
{
private:
  std::string file_out; /** Path to file (include .gad extension) */
  FILE * file_ptr;      /** Pointer to file handler object */
public:
  /** Constructor */
  GadOutputFile(std::string file_path) : file_out(file_path)
  {
    SetOutputFile(fopen(file_out.c_str(), "w+"));
  }
  /** Destructor */
  ~GadOutputFile()
  {
    fclose(file_ptr);
  }
  /** Output the packet to file */
  void OutputPacket(unsigned char * packet, int packet_size) override
  {
    fprintf(file_ptr, "%s", packet);
    fflush(file_ptr);
  }
  /** Set the output file pointer */ 
  void SetOutputFile(FILE* file_ptr)
  {
    this->file_ptr = file_ptr;
  }
  /** Get the output file pointer */ 
  auto GetOutputFile() -> FILE*
  {
    return this->file_ptr;
  }
  /** Set the output file path */
  void SetOutputFilePath(std::string file_path) 
  {
    this->file_out = file_path;
  }
  /** Set the output file path */
  auto GetOutputFilePath() -> std::string 
  {
    return this->file_out;
  }
};

} // namespace OxTS


#endif // GAD_OUTPUT_FILE_HPP
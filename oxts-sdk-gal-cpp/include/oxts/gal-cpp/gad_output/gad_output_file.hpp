#ifndef GAD_OUTPUT_FILE_HPP
#define GAD_OUTPUT_FILE_HPP
/** @file gad_output_file.hpp */

#include <string>
#include <ostream>
#include <fstream>
#include "oxts/gal-cpp/gad_output/gad_output.hpp"

namespace OxTS
{
	namespace Gal_Cpp
	{
		class GadOutputFile : public GadOutput
		{
		private:
			std::string m_file_out; /** Path to file (include .gad extension) */
			std::ofstream m_file_stream;      /** Output file stream */
		public:
			/** Constructor */
			GadOutputFile() : GadOutput(), m_file_stream()
			{

			}

			void SetFileName(const std::string& file_path)
			{
				m_file_stream.open(file_path);
			}

			GadOutputFile(const std::string& file_path) : GadOutput(), m_file_stream(file_path.c_str())
			{
				
			}

			/** Destructor */
			virtual ~GadOutputFile()
			{
				try
				{
					(void)m_file_stream.flush(); /*PRQA S 4631 # This will not throw an exception.*/
				}
				catch (...)
				{

				}
			}
			/** Output the packet to file */
			virtual void OutputPacket(const uint8_t* const packet, const std::size_t packet_size) override
			{
				const std::string str(reinterpret_cast<const char *>(packet), packet_size, std::allocator<char>());
				m_file_stream << str;
				(void)m_file_stream.flush();
			}
			/** Set the output file path */
			std::string GetOutputFilePath() const
			{
				return m_file_out;
			}
		};
	}
} // namespace OxTS


#endif // GAD_OUTPUT_FILE_HPP
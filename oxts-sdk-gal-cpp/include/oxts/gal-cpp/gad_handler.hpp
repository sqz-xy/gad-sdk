#ifndef GAD_HANDLER_HPP
#define GAD_HANDLER_HPP
/** @file gad_handler.hpp */

#include "oxts/gal-cpp/gad_encoders/gad_encoder.hpp"
#include "oxts/gal-cpp/gad_output/gad_output.hpp"

#include "oxts/gal-cpp/gad_encoders/gad_encoder_bin.hpp"
#include "oxts/gal-cpp/gad_encoders/gad_encoder_csv.hpp"
#include "oxts/gal-cpp/gad_output/gad_output_udp.hpp"
#include "oxts/gal-cpp/gad_output/gad_output_file.hpp"

namespace OxTS
{
	namespace Gal_Cpp
	{
		/** Class to handle encoding and sending Generic Aiding packets. This can be to
		 *  an INS in real time via UDP or to a .gad csv file.
		 */
		class GadHandler /*PRQA S 1755 # Rule-0_1_5 should not apply as this is to be consumed by 3rd party. */
		{
		private:
			ENCODER_TYPE m_encoder_type;
			OUTPUT_TYPE m_output_type;

			GadEncoderBin m_encoder_bin;
			GadEncoderCsv m_encoder_csv;

			GadOutputFile m_output_file;
			GadOutputUdp m_output_udp;

			GadEncoder *get_encoder();
			GadOutput *get_output();

		public:
			/**  Constructor */
			GadHandler();
			/** Set the output encoder to binary. */
			void SetEncoderToBin();
			/** Set the output encoder to csv. */
			void SetEncoderToCsv();

			/** Set Generic Aiding output to file
			 *  @param file_path Absolute path to the file to output the data to. Will be
			 *  created if it does not already exist.
			*/
			void SetOutputModeToFile(const std::string& file_path);
			/** Set Generic Aiding output to UDP.
			 *  @param ip The IPv4 address of the OxTS INS to send the data to.
			 */
			void SetOutputModeToUdp(const std::string& ip);

			/** Send packet via pre-configured output method.
			 *  @param g Generic Aiding data to be encoded and sent
			*/
			void SendPacket(const Gad& g);
		};
	}
} // OxTS

#endif // GAD_HANDLER_HPP
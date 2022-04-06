#include <iostream>

#include "oxts/gal-cpp/gad_handler.hpp"

using namespace OxTS;

void GadHandler::SendPacket(Gad g)
{
	//check encoder has been set
	if (encoder_)
	{
		encoder_->EncodePacket(g);
		// Send packet
		output_->OutputPacket(encoder_->GetPacket(), encoder_->GetPacketSize());
	}
	else
	{
		std::cerr << "Error encoder not set!"<<std::endl;
		std::cerr << "Use SetEncoderTo... functions before attempting to send packets" << std::endl;
	}
}
#include "oxts/gal-cpp/gad_handler.hpp"

using namespace OxTS;

void GadHandler::SendPacket(Gad g)
{
  this->encoder_->EncodePacket(g);
  // Send packet
  this->output_->OutputPacket(this->encoder_->GetPacket(), 
                              this->encoder_->GetPacketSize()
                              );
}
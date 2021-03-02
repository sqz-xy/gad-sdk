#include <iostream>
#include <string>

#include "oxts/gal-cpp/gad.hpp"
#include "oxts/gal-cpp/gad_encoder.hpp"
#include "oxts/gal-cpp/gad_output.hpp"

#include "udp_server_client.h"

int main(int argc, char * argv[])
{

  int sendPackets = 1000; // Total number of packets to send

  //============================================================================
  // Construct the position aiding class with stream ID 128.
  GadPosition gp = GadPosition(128);
  // Set the aiding position
  gp.SetWgs84Pos(0.0,0.0,0.0); 
  // Set the estimated variance on this position
  gp.SetWgs84PosVar(0.1,0.1,0.1); 
  // Set the time mode to Void, since we are not timestamping the aiding data.
  // With no timestamp, the INS will timestamp the data upon arrival.
  gp.SetTimeVoid(); 
  // Set the lever arm between the aiding source and the IMU, in the IMU frame.
  gp.SetAidingLeverArmOptimising(0.5,0.5,1.0);
  gp.SetAidingLeverArmVar(0.1,0.1,0.1);
  //============================================================================
  // Construct the velocity aiding class with stream ID 129.
  GadVelocity gv = GadVelocity(129);
  // Set the aiding velocity
  gv.SetVelNeu(0.0,0.0,0.0);
  // Set the estimated variance on this velocity
  gv.SetVelNeuVar(0.1,0.1,0.1);
  // Set the time mode to Void, since we are not timestamping the aiding data.
  // With no timestamp, the INS will timestamp the data upon arrival.
  gv.SetTimeVoid(); 
  // Set the lever arm between the aiding source and the IMU, in the IMU frame.
  // In this example, the velocity is coming from the same source as the 
  // position.
  gv.SetAidingLeverArmOptimising(0.5,0.5,1.0);
  gv.SetAidingLeverArmVar(0.1,0.1,0.1);
  //============================================================================
  // Construct the attitude aiding class with stream ID 130.
  GadAttitude ga = GadAttitude(130);
  // Set the aiding attitude
  ga.SetAtt(180.0,0.0,0.0);
  // Set the estimated variance on this attitude
  ga.SetAttVar(0.1,0.1,0.1); 
  // Set the time mode to Void
  ga.SetTimeVoid(); 
  // Set the aiding source -> IMU frame alignment with the frames aligned.
  ga.SetAidingAlignmentOptimising(0.0,0.0,0.0);
  // Set the variance on the alignment to 5.0 deg in HPR.
  ga.SetAidingAlignmentVar(5.0,5.0,5.0);
  //============================================================================

  // Initialise the output class
  GadOutput go = GadOutput();
  // Set encoding strategy
  go.SetEncoderToBin();


  /** UDP Client to receive data from the device */
  networking_udp::server udpServer;
  std::string unitIp = "192.168.25.10";
  udpServer.set_remote_endpoint(unitIp, 40785);

  


  //============================================================================
  for (int i = 0; i < sendPackets; ++i)
  {
    // Encode packet
    go.encoder_->EncodePacket(ga);
    // Send packet
    udpServer.send(go.encoder_->GetPacket(), go.encoder_->GetPacketSize()); 

  }


  return 0;
}
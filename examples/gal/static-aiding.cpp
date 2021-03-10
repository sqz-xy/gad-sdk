#include <iostream>
#include <string>

#include "oxts/gal-c/gad_encode_csv.h"

#include "oxts/gal-cpp/gad.hpp"
#include "oxts/gal-cpp/gad_encoder.hpp"
#include "oxts/gal-cpp/gad_handler.hpp"

#include "udp_server_client.h"

#ifdef _WIN32
#include <windows.h>
#elseif __linux__
#include <unistd.h>
#endif

namespace OxTS
{
void Sleep(int sleepMs)
{
#ifdef __linux__
    usleep(sleepMs * 1000);   // usleep takes sleep time in us (1 millionth of a second)
#endif
#ifdef _WIN32
    Sleep(sleepMs);    // Sleep takes sleep time in ms.
#endif
}
}



int main(int argc, char * argv[])
{

  int sendPackets = 30; // Total number of packets to send
  std::string unitIp = "192.168.25.22"; // Unit to send GAD to

  //============================================================================
  // Construct the position aiding class with stream ID 129.
  OxTS::GadPosition gp = OxTS::GadPosition(129);
  // Set the aiding position
  gp.SetWgs84Pos(51.91520330,-1.24479140,111.525);
  // Set the estimated variance on this position
  gp.SetWgs84PosVar(1,1,1);
  // Set the time mode to Void, since we are not timestamping the aiding data.
  // With no timestamp, the INS will timestamp the data upon arrival.
  gp.SetTimeVoid();
  // Set the lever arm between the aiding source and the IMU, in the IMU frame.
  gp.SetAidingLeverArmFixed(0.0,0.0,0.1);
  gp.SetAidingLeverArmVar(0.1,0.1,0.1);
  //============================================================================
  // Construct the velocity aiding class with stream ID 130.
  OxTS::GadVelocity gv = OxTS::GadVelocity(130);
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
  gv.SetAidingLeverArmFixed(0.5,0.5,1.0);
  gv.SetAidingLeverArmVar(0.1,0.1,0.1);
  //============================================================================
  // Construct the attitude aiding class with stream ID 131.
  OxTS::GadAttitude ga = OxTS::GadAttitude(131);
  // Set the aiding attitude
  ga.SetAtt(0.0,0.0,0.0);
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
  OxTS::GadHandler gh = OxTS::GadHandler();
  // Set encoding strategy
  // gh.SetEncoderToBin();
  gh.SetEncoderToCsv();
  // Set output strategy

  /** UDP Client to receive data from the device */
  networking_udp::server udpServer;
  short unitGaPort = 50485;
  udpServer.set_remote_endpoint(unitIp, unitGaPort);


  //============================================================================
  // CSV
  std::string source_id = "out";
  OxTS::GadEncoderCsv gec = OxTS::GadEncoderCsv(); 
  OxTS::GadOutputFile gof = OxTS::GadOutputFile((source_id + ".gad").c_str()); 

  //============================================================================
  for (int i = 0; i < sendPackets; ++i)
  {
    // Encode packet
    gp.SetWgs84Pos(i,0,0);
    gh.encoder_->EncodePacket(gp);
    // Send packet
    // udpServer.send(gec.GetPacket(), gec.GetPacketSize());
    // udpServer.send(gh.encoder_->GetPacket(), gh.encoder_->GetPacketSize());


    gof.OutputPacket(gh.encoder_->GetPacket());

    // gh.encoder_->EncodePacket(gv);
    // udpServer.send(gh.encoder_->GetPacket(), gh.encoder_->GetPacketSize());

    // gh.encoder_->EncodePacket(ga);
    // udpServer.send(gh.encoder_->GetPacket(), gh.encoder_->GetPacketSize());

    if(i % 10 == 0)
      std::cout << i << " packets sent" << std::endl;

    OxTS::Sleep(100);
  }
  // fclose(file_ptr);

  return 0;
}
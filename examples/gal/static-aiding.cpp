#include <iostream>
#include <string>

// #include "oxts/gal-cpp/gad.hpp"
#include "oxts/core/BasicCasts.h"
#include "oxts/gal-c/gad_struct.h"
#include "oxts/gal-cpp/gad.hpp"


int main(int argc, char * argv[])
{

  int sendPackets = 1000; // Total number of packets to send
  std::string ip = "192.168.25.44"; // IP address to send the data to

  GenBool b = true;
  // // Construct the position aiding class.
  //GadPosition gp = GadPosition();
  // // Set the aiding position
  // gp.SetWgs84Pos(0.0,0.0,0.0); 
  // // Set the estimated variance on this position
  // gp.SetWgs84PosVar(0.1,0.1,0.1); 
  // // Set the time mode to Void, since we are not timestamping the aiding data.
  // // With no timestamp, the INS will timestamp the data upon arrival.
  // gp.SetTimeVoid(); 
  // // Set the lever arm between the aiding source and the IMU, in the IMU frame.
  // gp.SetAidingLeverArmOptimising(0.5,0.5,1.0);

  // // Construct the velocity aiding class.
  // GadVelocity gv = GadVelocity();
  // // Set the aiding velocity
  // gv.SetVelNeu(0.0,0.0,0.0);
  // // Set the estimated variance on this velocity
  // gv.SetVelNeuVar(0.1,0.1,0.1);
  // // Set the time mode to Void, since we are not timestamping the aiding data.
  // // With no timestamp, the INS will timestamp the data upon arrival.
  // gp.SetTimeVoid(); 
  // // Set the lever arm between the aiding source and the IMU, in the IMU frame.
  // // In this example, the velocity is coming from the same source as the 
  // // position.
  // gp.SetAidingLeverArmOptimising(0.5,0.5,1.0);

  // // Construct the attitude aiding class
  // GadAttitude ga = GadAttitude();
  // // Set the aiding attitude
  // ga.SetAtt(180.0,0.0,0.0);
  // // Set the estimated variance on this attitude
  // ga.SetAttVar(0.1,0.1,0.1); 


  for (int i = 0; i < sendPackets; ++i)
  {
    // Send packets
  }


  return 0;
}
#include <iostream>
#include <string>

#include "oxts/gal-cpp/gad.hpp"
#include "oxts/gal-cpp/gad_handler.hpp"

#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <unistd.h>
#endif
// This is a basic cross-platform sleep function
namespace OxTS
{
void sleep(int sleepMs)
{
#ifdef __linux__
    usleep(sleepMs * 1000);   // usleep takes sleep time in us (1 millionth of a second)
#endif
#ifdef _WIN32
    Sleep(sleepMs);    // Sleep takes sleep time in ms.
#endif
}
} // OxTS


int main(int argc, char * argv[])
{
  std::string unit_ip   = argv[1]; // Unit to send GAD to
  int num_packets       = std::stoi(argv[2]); // Number of packets to send.

  // Construct the speed aiding with stream ID 130.
  OxTS::GadSpeed gs = OxTS::GadSpeed(130);
  // Set the required values for the data
  gs.SetSpeedFw(0.0);
  gs.SetSpeedFwVar(0.0001);
  gs.SetTimeVoid();
  gs.SetAidingLeverArmOptimising();
  // Initialise the handler
  OxTS::GadHandler gh = OxTS::GadHandler();
  gh.SetEncoderToBin();
  gh.SetOutputModeToUdp(unit_ip);

  // Send the packets
  for (int i = 0; i < num_packets; ++i)
  {
    gh.SendPacket(gs);
    OxTS::sleep(50);
  }

  return 0;
}
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
using namespace std::literals::chrono_literals;

#include "oxts/gal-cpp/gad.hpp"
#include "oxts/gal-cpp/gad_handler.hpp"


int main(int argc, char* argv[])
{
        if (argc < 3)
        {
                std::cout<<"Invalid number of command line arguments, requires: <IP> <number of packets>";
                return 1;
        }

        std::string unit_ip   = argv[1]; // Unit to send GAD to
        int num_packets       = std::stoi(argv[2]); // Number of packets to send.

                // Initialise the handler
        OxTS::Gal_Cpp::GadHandler gh;
        gh.SetEncoderToBin();
        gh.SetOutputModeToUdp(unit_ip);
        // Construct the velocity aiding with stream ID 130.
        OxTS::Gal_Cpp::GadVelocity gv(130);
        // Loop through packets
        for (int i = 0; i < num_packets; ++i)
        {
                // Set the required data
                gv.SetVelNed(0.0,0.0,0.0);
                gv.SetVelNedVar(0.1,0.1,0.1);
                gv.SetTimeVoid();
                gv.SetAidingLeverArmFixed(0.0,0.0,1.0);
                gv.SetAidingLeverArmVar(0.01,0.01,0.01);
                // Send packet
                gh.SendPacket(gv);
                std::cout << "packet " << i << " sent" << std::endl;
                std::this_thread::sleep_for(100ms);

        }

        return 0;
}
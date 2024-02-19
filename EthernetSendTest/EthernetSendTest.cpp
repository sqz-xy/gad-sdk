// EthernetSendTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include "oxts/gal-cpp/gad_handler.hpp"

int main()
{
    std::cout << "Testing sockets...\n";
    OxTS::Gal_Cpp::GadHandler handler;
    handler.SetEncoderToBin();
    handler.SetOutputModeToUdp("192.168.25.224");
    OxTS::Gal_Cpp::Gad gad;
    for (std::int32_t i = 0; i < 10; ++i)
    {
        // Create a GAD update
        gad.SetTimeUTCUnix(10000);
        std::cout << "Sending packet..." << std::endl;
        // Send it
        handler.SendPacket(gad);
        // Sleep until send of next packet
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
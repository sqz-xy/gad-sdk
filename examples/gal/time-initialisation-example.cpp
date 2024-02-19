#include <iostream>
#include <string>

#include "oxts/gal-cpp/gad.hpp"
#include "oxts/gal-cpp/gad_handler.hpp"

#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <unistd.h>
#endif

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

enum OUTPUT_TYPE
{
    UDP = 0,
    CSV = 1
};

int main(int argc, char* argv[])
{
    int sendPackets = 30; // Total number of packets to send
    std::string unit_ip = "192.168.25.22"; // Unit to send GAD to
    std::string file_out = "out.gad";    // File to send GAD to
    int output_type = OUTPUT_TYPE::UDP;   // Set output to UDP or CSV

    //============================================================================
    // Construct the position aiding class with stream ID 129.
    OxTS::Gal_Cpp::GadPosition gp(129);
    // Set the time from external source (Week 2191 - January 2022)
    gp.SetTimeExternal(2191.0, 0.0);
    // Set the aiding position
    gp.SetPosGeodetic(51.91520330, -1.24479140, 111.525);
    // Set the estimated variance on this position
    gp.SetPosGeodeticVar(1.0, 1.0, 1.0);
    // Set the lever arm between the aiding source and the IMU, in the IMU frame.
    gp.SetAidingLeverArmFixed(0.5, 0.5, 1.0);
    gp.SetAidingLeverArmVar(0.1, 0.1, 0.1);
    //============================================================================
    // Initialise the handler
    OxTS::Gal_Cpp::GadHandler gh

    // This switch case sets up the GadHandler to either output binary to UDP or 
    // CSV to file.
    switch (output_type)
    {
    case OUTPUT_TYPE::UDP:
        gh.SetEncoderToBin();
        gh.SetOutputModeToUdp(unit_ip);
        break;
    case OUTPUT_TYPE::CSV:
        gh.SetEncoderToCsv();
        gh.SetOutputModeToFile(file_out);
        break;
    default:
        std::cout << "Output type not known." << std::endl;
        break;
    }

    //============================================================================
    for (int i = 0; i < sendPackets; ++i)
    {
        gh.SendPacket(gp);

        if (i % 10 == 0)
            std::cout << i << " packets sent" << std::endl;

        OxTS::sleep(100);
    }

    return 0;
}
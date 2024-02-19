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
    // Set the aiding position
    gp.SetPosGeodetic(51.91520330, -1.24479140, 111.525);
    // Set the estimated variance on this position
    gp.SetPosGeodeticVar(1.0, 1.0, 1.0);
    // Set the time mode to Void, since we are not timestamping the aiding data.
    // With no timestamp, the INS will timestamp the data upon arrival.
    gp.SetTimeVoid();
    // Set the lever arm between the aiding source and the IMU, in the IMU frame.
    gp.SetAidingLeverArmFixed(0.5, 0.5, 1.0);
    gp.SetAidingLeverArmVar(0.1, 0.1, 0.1);
    //============================================================================
    // Construct the velocity aiding class with stream ID 130.
    OxTS::Gal_Cpp::GadVelocity gv(130);
    // Set the aiding velocity
    gv.SetVelNeu(0.0, 0.0, 0.0);
    // Set the estimated variance on this velocity
    gv.SetVelNeuVar(0.1, 0.1, 0.1);
    // Set the time mode to Void, since we are not timestamping the aiding data.
    gv.SetTimeVoid();
    // Set the lever arm between the aiding source and the IMU, in the IMU frame.
    // In this example, the velocity is coming from the same source as the
    // position.
    gv.SetAidingLeverArmFixed(0.5, 0.5, 1.0);
    gv.SetAidingLeverArmVar(0.1, 0.1, 0.1);
    //============================================================================
    // Construct the attitude aiding class with stream ID 131.
    OxTS::Gal_Cpp::GadAttitude ga(131);
    // Set the aiding attitude
    ga.SetAtt(0.0, 0.0, 0.0);
    // Set the estimated variance on this attitude
    ga.SetAttVar(0.1, 0.1, 0.1);
    // Set the time mode to Void
    ga.SetTimeVoid();
    // Set the aiding source -> IMU frame alignment with the frames aligned.
    ga.SetAidingAlignmentOptimising();
    // Set the variance on the alignment to 5.0 deg in HPR.
    ga.SetAidingAlignmentVar(5.0, 5.0, 5.0);
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
        gh.SendPacket(gv);
        gh.SendPacket(ga);

        if (i % 10 == 0)
            std::cout << i << " packets sent" << std::endl;

        OxTS::sleep(100);
    }

    return 0;
}
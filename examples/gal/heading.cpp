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
	int output_type = OUTPUT_TYPE::CSV;   // Set output to UDP or CSV

	//============================================================================
	// Construct the heading aiding class with stream ID 131.
	OxTS::GadHeading gh = OxTS::GadHeading(132);
	// Set the aiding attitude
	gh.SetHeading(180.0);
	// Set the estimated variance on this heading
	gh.SetHeadingVar(0.1);
	// Set the time mode to Void
	gh.SetTimeVoid();
	// Set the aiding source -> IMU frame alignment with the frames aligned.
	gh.SetAidingAlignmentFixed(0.0,0.0,0.0);
	// Set the variance on the alignment to 5.0 deg in HPR.
	gh.SetAidingAlignmentVar(5.0, 5.0, 5.0);
	//============================================================================
	// Initialise the handler
	OxTS::GadHandler handler = OxTS::GadHandler();

	// This switch case sets up the GadHandler to either output binary to UDP or 
	// CSV to file.
	switch (output_type)
	{
	case OUTPUT_TYPE::UDP:
		handler.SetEncoderToBin();
		handler.SetOutputModeToUdp(unit_ip);
		break;
	case OUTPUT_TYPE::CSV:
		handler.SetEncoderToCsv();
		handler.SetOutputModeToFile(file_out);
		break;
	default:
		std::cout << "Output type not known." << std::endl;
		break;
	}

	//============================================================================
	for (int i = 0; i < sendPackets; ++i)
	{
		handler.SendPacket(gh);

		if (i % 10 == 0)
			std::cout << i << " packets sent" << std::endl;

		OxTS::sleep(100);
	}

	return 0;
}
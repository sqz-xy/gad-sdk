.. _staticaiding:


Static-aiding
#############

In this example, position, velocity, and attitude data is sent to an OxTS INS in real time or saved as a GAD file for postprocessing. The full source code for the GAD SDK in both C++ and Python can be found below.

Requirements
************

•	An OxTS INS with the relevant Generic Aiding Feature Codes enabled. If you are not sure whether you have the right Feature Codes or are unfamiliar with them, contact support@oxts.com.
•	A PC, connected to the INS via ethernet.
•	The `GAD SDK <https://github.com/OxfordTechnicalSolutions/gad-sdk/tree/main#readme>`_ has been built on this machine / pre-built binaries have been downloaded (not currently available).

How to run the executable
-------------------------

.. tabs::
	
	.. tab:: Linux

		1.	Navigate to the relevant project configuration directory in the build folder: cd <build_dir>/examples/gal.
		2.	Run the executable: ./static-aiding-example. This will begin sending Generic Aiding packets. There are four possible optional arguments that can be provided:
		
		•	Device IP address
		•	Number of packets
		•	Output type (csv)
		•	Output file (if outputting to csv)
		
		For example: `./static-aiding-example 192.168.25.10 70 csv debug_out.csv` will output 70 packets of data to debug_out.csv. To output to a live device omit the final 2 arguments: `./static-aiding-example 192.168.25.10 70`

	.. tab:: Windows

		1.	Navigate to the relevant directory in the build folder: cd <build_dir>/examples/gal/Debug.
		2.	From the command line run the executable: static-aiding-example.exe. This will begin sending Generic Aiding packets. There are four possible optional arguments that can be provided:
		
		•	Device IP address
		•	Number of packets
		•	Output type (csv)
		•	Output file (if outputting to csv)
		
		For example: `static-aiding-example.exe 192.168.25.10 70 csv debug_out.csv` will output 70 packets of data to debug_out.csv. To output to a live device omit the final 2 arguments: `static-aiding-example.exe 192.168.25.10 70`

Source code
***********

.. tabs::

	.. code-tab:: c++
	
		#include <iostream>
		#include <string>
		#include <chrono>
		#include <thread>
		using namespace std::chrono_literals;
		
		#include "oxts/gal-cpp/gad.hpp"
		#include "oxts/gal-cpp/gad_handler.hpp"
		
		
		enum class OUTPUT_TYPE
		{
			UDP = 0,
			CSV = 1
		};
		
		int main(int argc, char* argv[])
		{
			//defaults
			int num_packets = 30; // Total number of packets to send
			std::string unit_ip = "192.168.25.22"; // Unit to send GAD to, change to IP address of your unit
			std::string file_out = "out.gad";    // File to send GAD to
			OUTPUT_TYPE output_type = OUTPUT_TYPE::UDP;   // Set output to UDP or CSV
			//Get from user input if provided
			if (argc > 1)
			{
				unit_ip = argv[1];
			}
			if (argc > 2)
			{
				num_packets = std::stoi(argv[2]);
			}
			if (argc > 3)
			{
				if (!strcmp(argv[3], "csv"))
				{
					output_type = OUTPUT_TYPE::CSV;
				}
			}
			if (argc > 4)
			{
				file_out = argv[4];
			}
			//==========================================================================
			// Construct the position aiding class with stream ID 129.
			OxTS::Gal_Cpp::GadPosition gp(129);
			// Set the aiding position
			gp.SetPosGeodetic(51.91520330,-1.24479140,111.525); // Change these lat, long, alti values to your location
			// Set the estimated variance on this position
			gp.SetPosGeodeticVar(1.0,1.0,1.0);
			// Set the time mode to Void, since we are not timestamping the aiding data.
			// With no timestamp, the INS will timestamp the data upon arrival.
			gp.SetTimeVoid();
			// Set the lever arm between the aiding source and the IMU, in the IMU frame.
			gp.SetAidingLeverArmFixed(0.5,0.5,1.0);
			gp.SetAidingLeverArmVar(0.1,0.1,0.1);
			//==========================================================================
			// Construct the velocity aiding class with stream ID 130.
			OxTS::Gal_Cpp::GadVelocity gv(130);
			// Set the aiding velocity
			gv.SetVelNed(0.0,0.0,0.0);
			// Set the estimated variance on this velocity
			gv.SetVelNedVar(0.1,0.1,0.1);
			// Set the time mode to Void, since we are not timestamping the aiding data.
			gv.SetTimeVoid();
			// Set the lever arm between the aiding source and the IMU, in the IMU frame.
			// In this example, the velocity is coming from the same source as the
			// position.
			gv.SetAidingLeverArmFixed(0.5,0.5,1.0);
			gv.SetAidingLeverArmVar(0.1,0.1,0.1);
			//==========================================================================
			// Construct the attitude aiding class with stream ID 131.
			OxTS::Gal_Cpp::GadAttitude ga(131);
			// Set the aiding attitude
			ga.SetAtt(0.0,0.0,0.0);
			// Set the estimated variance on this attitude
			ga.SetAttVar(0.1,0.1,0.1);
			// Set the time mode to Void
			ga.SetTimeVoid();
			// Set the aiding source -> IMU frame alignment with the frames aligned.
			ga.SetAidingAlignmentOptimising();
			// Set the variance on the alignment to 5.0 deg in HPR.
			ga.SetAidingAlignmentVar(5.0,5.0,5.0);
			//==========================================================================
			// Initialise the handler
			OxTS::Gal_Cpp::GadHandler gh;
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
			//==========================================================================
			for (int i = 0; i < num_packets; ++i)
			{
				gh.SendPacket(gp);
				gh.SendPacket(gv);
				gh.SendPacket(ga);
				if (i % 10 == 0) // Message is printed for every 10th pack sent
				{
					std::cout << i << " packets sent" << std::endl;
				}
		
				std::this_thread::sleep_for(100ms);
			}
		return 0;
		}

	.. code-tab:: python
	
		import sys
		import time
		import oxts_sdk
		from enum import Enum
		
		class OUTPUT_TYPE(Enum):
			UDP = 0
			CSV = 1
			
		if __name__ == "__main__":
			# defaults
			num_packets = 30 # Total number of packets to send
			unit_ip = "192.168.25.22" # Unit to send GAD to, change to IP address of your unit
			file_out = "out.gad"      # File to send GAD to
			output_type = OUTPUT_TYPE.UDP   # Set output to UDP
			if len(sys.argv) > 1:
				unit_ip = sys.argv[1]
			if len(sys.argv) > 2:
				num_packets = sys.argv[2]
			if len(sys.argv) > 3:
				if sys.argv[3].lower()== 'csv':
					output_type = OUTPUT_TYPE.CSV
			if len(sys.argv) > 4:
				file_out = sys.argv[4]
				
			#============================================================================
			# Construct the position aiding class with stream ID 129.
			gp = oxts_sdk.GadVPosition(129)
			# Set the aiding position
			gp.pos_geodetic = [51.91520330,-1.24479140,111.525] #Change these lat, long, alti values to your location
			# Set the estimated variance on this position
			gp.pos_geodetic_var =[ 1.0,1.0,1.0]
			# Set the time mode to Void, since we are not timestamping the aiding data.
			# With no timestamp, the INS will timestamp the data upon arrival.
			gp.set_time_void()
			# Set the lever arm between the aiding source and the IMU, in the IMU frame.
			gp.aiding_lever_arm_fixed = [0.5,0.5,1.0]
			gp.aiding_lever_arm_var = [0.1,0.1,0.1]
			#============================================================================
			# Construct the velocity aiding class with stream ID 130.
			gv = oxts_sdk.GadVelocity(129)  # Set the aiding velocity
			gv.vel_ned = [0.0,0.0,0.0]
			# Set the estimated variance on this velocity
			gv.vel_ned_var = [0.1,0.1,0.1]
			# Set the time mode to Void, since we are not timestamping the aiding data.
			gv.set_time_void()
			# Set the lever arm between the aiding source and the IMU, in the IMU frame.
			# In this example, the velocity is coming from the same source as the
			# position.
			gv.aiding_lever_arm_fixed = [0.5,0.5,1.0]
			gv.aiding_lever_arm_var = [0.5,0.5,1.0]
			#============================================================================
			# Construct the attitude aiding class with stream ID 131.
			ga= oxts_sdk.GadAttitude(131)
			# Set the aiding attitude
			ga.att = [0.0,0.0,0.0]
			# Set the estimated variance on this attitude
			ga.att_var = [0.1,0.1,0.1]
			# Set the time mode to Void
			ga.set_time_void()
			# Set the aiding source -> IMU frame alignment with the frames aligned.
			ga.aiding_alignment_fixed = [90.0, 1.0, 0.0]
			# Set the variance on the alignment to 5.0 deg in HPR.
			ga.aiding_alignment_var = [5.0,5.0,5.0]
			#============================================================================
			gh = oxts_sdk.GadHandler()
			if output_type == OUTPUT_TYPE.UDP:
				gh.set_encoder_to_bin()
				gh.set_output_mode_to_udp(unit_ip)
			elif output_type == OUTPUT_TYPE.CSV:
				gh.set_encoder_to_csv()
				gh.set_output_mode_to_to_file(file_out)
			else:
				print("Output type not known.")
				sys.exit(1)
				
			for i in range(0,num_packets,1):
				# Send the packets
				gh.send_packet(gp)
				gh.send_packet(gv)
				gh.send_packet(ga)
				if (i % 10 == 0): # Message is printed for every 10th pack sent.
					print("packet " + str(i) + " sent")
				
				time.sleep(0.1)
			
		sys.exit(0)


Code breakdown
**************

Since a lot of the code seen here is the same as shown previously, we will concentrate on specific sections that show new functionality.

.. tabs::

	.. code-tab:: c++
		
		enum class OUTPUT_TYPE
		{
			UDP = 0,
			CSV = 1
		};
	
	.. code-tab:: python
	
		class OUTPUT_TYPE(Enum):
		UDP = 0
		CSV = 1
	

This is a simple enum, to allow switching between UDP (via ethernet) and CSV (file) output.

.. tabs::	
	
	.. code-tab:: c++
		
		//defaults
		int num_packets = 30; // Total number of packets to send
		std::string unit_ip = "192.168.25.22"; // Unit to send GAD to, change to IP address of your unit
		std::string file_out = "out.gad";    // File to send GAD to
		OUTPUT_TYPE output_type = OUTPUT_TYPE::UDP;   // Set output to UDP or CSV
		//Get from user input if provided
		if (argc > 1)
		{
			unit_ip = argv[1];
		}
		if (argc > 2)
		{
			num_packets = std::stoi(argv[2]);
		}
		if (argc > 3)
		{
			if (!strcmp(argv[3], "csv"))
			{
				output_type = OUTPUT_TYPE::CSV;
			}
		}
		if (argc > 4)
		{
			file_out = argv[4];
		}

	.. code-tab:: python
	
		# defaults
		num_packets = 30 # Total number of packets to send
		unit_ip = "192.168.25.22" # Unit to send GAD to, change to IP address of your unit
		file_out = "out.gad"      # File to send GAD to
		output_type = OUTPUT_TYPE.UDP   # Set output to UDP
		if len(sys.argv) > 1:
			unit_ip = sys.argv[1]
		if len(sys.argv) > 2:
			num_packets = sys.argv[2]
		if len(sys.argv) > 3:
			if sys.argv[3].lower()== 'csv':
				output_type = OUTPUT_TYPE.CSV
		if len(sys.argv) > 4:
			file_out = sys.argv[4]

	
This first half of this section sets the default values for the four input arguments of the main function. The four input arguments are (in order):

1.	IP address of the INS unit
2.	Number of measurement packets to be converted into GAD packets (default = 30).
3.	Type of output to be sent. If this is “csv” or “CSV” then the output will be saved as a GAD file. Otherwise, it will be sent to the unity via UDP.
4.	If the output is to be saved as a GAD file, this is the name of GAD file. (default is “out.gad”).

The second half of this section reads in and sets the input arguments listed above.

.. tabs::	
	
	.. code-tab:: c++
	
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

	.. code-tab:: python
	
		Python
		gh = oxts_sdk.GadHandler()
		if output_type == OUTPUT_TYPE.UDP:
			gh.set_encoder_to_bin()
			gh.set_output_mode_to_udp(unit_ip)
		elif output_type == OUTPUT_TYPE.CSV:
			gh.set_encoder_to_csv()
			gh.set_output_mode_to_to_file(file_out)
		else:
			print("Output type not known.")
			sys.exit(1)

This block of code initialises an instance of the GadHandler and sets it up to either send Generic Aiding data via UDP or to CSV file, based on the configuration option at the start of the file.

Exercise
********

•	Set-up the equipment on a work bench; remember that for this example, no sensor is needed.
•	Configure and initialise the INS. How will you initialise the INS if it is mounted on a work bench?
•	Enter in the position given by the navigation engine into the GAD SDK program.
•	Start the executable, then start the GAD SDK program with the output as UDP.
•	Observe the output of the Navigation engine with NAVDisplay. Remember that the GAD SDK is feeding the navigation engine that give no movement. So, what happens when you move the INS across the work desk?
•	Now try to the output type to csv and rerun the GAD SDK. After the program has finished (run out of packets to send), look at the GAD file with a spreadsheet program such as Excel. Do you understand the information given in this GAD file? See here for more information on the format of gad files.
•	You will notice that in the GAD SDK code, the different update types are made outside of the packet loop. Move the code for one of the update types, e.g. velocity, into the packet loop section. Now write a function that varies the input value, e.g. the velocity could be the square root of the packet number. Run the GAD SDK program again (output type = csv), study the GAD file. Do you see where the values in the gad file have changed?

.. _myfirstgad:

My first GAD
############

In this example, velocity data is sent to an OxTS INS in real time. Instead of using an actual sensor, the velocity is hard coded.
The full source code for the GAD SDK in both C++ and Python can be found below. 
Since this is the same code as discussed in :ref:`Getting Started <gettingstarted>` , a full breakdown of the code will not be given here.

Requirements
************

•	An OxTS INS with the relevant Generic Aiding Feature Codes enabled. If you are not sure whether you have the right Feature Codes or are unfamiliar with them, contact support@oxts.com.
•	A PC, connected to the INS via ethernet.
•	The GAD SDK has been built on this machine (`see here for instructions <https://github.com/OxfordTechnicalSolutions/gad-sdk/tree/main#readme>`_).

How to run the executable
-------------------------

If you are using C++, then the GAD SDK code needs to be run via an executable. 
The executable for this example is created when building the GAD SDK. 

.. tabs::
	
	.. tab:: Linux
		1.	Navigate to the relevant directory in the GAD-SDK build folder: `cd <build_dir>/examples/gal`.
		2.	Run the executable: `./my-first-gad-example <IP> <Packets>`. This will begin sending Generic Aiding packets to the specified IP address, which should be set as the IP address of the INS, e.g. `./my-first-gad-example 192.168.25.10 1000`.

	.. tab:: Windows

		1.	Navigate to the relevant configuration type directory in the GAD-SDK build folder: `cd <build_dir>/examples/gal/Debug`.
		2.	From the command line run the executable: `my-first-gad-example.exe <IP> <Packets>`. This will begin sending Generic Aiding packets to the specified IP address, which should be set as the IP address of the INS, e.g. `my-first-gad-example.exe 192.168.25.10 1000`.

Source code
***********

.. tabs::

	.. code-tab:: c++
	
		#include <iostream>
		#include <string>

		#include "oxts/gal-cpp/gad.hpp"
		#include "oxts/gal-cpp/gad_handler.hpp"
		#include "oxts_sleep.hpp"
		
		
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
				OxTS::sleep_milliseconds(100);
		
			}
		
			return 0;
		}

	.. code-tab:: python
			
		import sys
		import time
		import oxts_sdk
		
		if __name__ == "__main__":
			if len(sys.argv) < 3:
				print("Invalid number of command line arguments, requires: <IP> <number of packets>")
				sys.exit(1)
			
			unit_ip =  sys.argv[1]
			num_packets = sys.argv[2]
		
			# Initialise the handler
			gh = oxts_sdk.GadHandler()
			gh.set_encoder_to_bin()
			gh.set_output_mode_to_udp(unit_ip)
			# Construct the velocity aiding with stream ID 130.
			gv = oxts_sdk.GadVelocity(130)
			for i in range(0,num_packets,1):
				# Set the required data
				gv.vel_ned = [0.0,0.0,0.0]
				gv.vel_ned_var = [0.1,0.1,0.1]
				gv.set_time_void()
				gv.aiding_lever_arm_fixed = [0.0,0.0,1.0]
				gv.aiding_lever_arm_var = [0.01,0.01,0.01]
				# Send the packets
				gh.send_packet(gv)
				print("packet " + str(i) + " sent")
				time.sleep(0.1)
		
			sys.exit(0)
		

Exercise
********

*	Set-up the equipment on a work bench; remember that for this example, no sensor is needed.
*	Configure and initialise the INS. How will you initialise the INS if it is mounted on a work bench?
*	Run the executable (C++) or run the code from the Python command line.
*	Observe the output of the navigation engine with NAVDisplay. Remember that the GAD SDK is feeding the navigation engine with velocity updates that give no movement. So what happens when you move the INS across the work desk?
*	Stop the GAD SDK program and change the velocity of the packets to a value such as (5.0,0.0,0.0) and restart. What happens to the Navigation engines solution? What are the velocity innovations?
*	Stop the GAD SDK program and reset the velocity of the packets to (0.0,0.0,0.0). Now increase the covariance of the packets to something like (1.0,1.0,1.0). What is the navigations solution while the INS is stationary on the bench? Now, try moving the INS across the table. How does changing the covariance value affect the navigation engines solution when the INS is moving? Can you explain these changes?

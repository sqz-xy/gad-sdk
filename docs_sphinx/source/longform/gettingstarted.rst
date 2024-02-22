.. _gettingstarted:

Getting Started
###############

Prerequisites
*************

There are four things you need to start using this SDK:

**An OxTS INS device**

All OxTS INS devices currently for sale support GAD. If you have a legacy OxTS 
INS contact `OxTS <support@oxts.com>`__ to see if it supports GAD. It will also 
be useful to have a PC with the latest 
`NAVsuite <https://support.oxts.com/hc/en-us/sections/115000789105-NAVsuite>`__ 
software installed.

**Feature Codes**

Generic Aiding is an optional extra for your INS device that needs to be 
enabled using the right Feature Codes. To purchase the feature codes for your INS, 
please contact support@oxts.com.

**An aiding device**

An aiding device is an external sensor which provides additional information 
on a vehicle's dynamics and/or pose. This information is then used to aid the navigation solution.
The device must be rigidly mounted to the same vehicle as your INS.

Generic Aiding is supported by an ethernet interface on the INS, to allow for aiding in real time. 
To make use of this, the aiding device must either encode and send GAD over ethernet via 
UDP itself or must pass its data to an intermediate processor which is capable 
of encoding GAD. 


**The GAD SDK**

The GAD Software Development Kit (SDK) is a set of development tools 
that allows for the interface between an external aiding source and an 
OxTS INS.
You can download it from our 
`GitHub <https://github.com/OxfordTechnicalSolutions/gad-sdk/tree/main>`__. 
The SDK needs to be installed on the device that will be generating the GAD 
packets. Installation instructions can be found 
`here <https://github.com/OxfordTechnicalSolutions/gad-sdk/blob/main/README.md>`__. 

.. _s3_example_code:

What does the code look like?
*****************************

The SDK exists in C, C++ or Python, but this documentation will focus on C++ and Python only. 
It is assumed that the reader has a basic understanding of at least one of these languages, preferably C++ or Python. 
Here we go through an example which will introduce the basic concepts involved in creating GAD packets and 
sending them to an INS. 

.. tabs::

	.. tab:: C++

		.. code-block:: c++
			
			#include <iostream>
			#include <string>
			#include <chrono>
			#include <thread>
			using namespace std::chrono_literals;

			#include "oxts/gal-cpp/gad.hpp"
			#include "oxts/gal-cpp/gad_handler.hpp"
					
			
			int main(int argc, char* argv[])
			{
				if (argc != 3)
				{
					std::cout << "Usage: \n";
					std::cout << "       ./my-first-gad <INS IP> <number of packets>\n";
					std::cout << "       e.g. ./my-first-gad 192.168.25.100 100"
							  << std::endl;
					return 1;
				}
			
				std::string unit_ip   = argv[1];
				int num_packets       = std::stoi(argv[2]);
				
				OxTS::Gal_Cpp::GadHandler gh;
				gh.SetEncoderToBin();
				gh.SetOutputModeToUdp(unit_ip);

				OxTS::Gal_Cpp::GadVelocity gv(130);
				for (int i = 0; i < num_packets; ++i)
				{
					gv.SetVelNed(0.0,0.0,0.0);
					gv.SetVelNedVar(0.1,0.1,0.1);
					gv.SetTimeVoid();
					gv.SetAidingLeverArmFixed(0.0,0.0,1.0);
					gv.SetAidingLeverArmVar(0.01,0.01,0.01);
					
					gh.SendPacket(gv);
					std::cout << "packet " << i << " sent" << std::endl;	
					
					std::this_thread::sleep_for(100ms);
				}
				return 0;
			}
		
		We will now break down the parts of the code which make use of the GAD 
		SDK.
		
		.. code-block:: c++
		
			#include "oxts/gal-cpp/gad.hpp"
			#include "oxts/gal-cpp/gad_handler.hpp"
		
		Includes from the GAD SDK.

		* :code:`gad.hpp` contains the Gad classes required to construct our GAD 
		  packets of all aiding types. In this case we will be making use of 
		  :code:`GadVelocity`. 
		* :code:`gad_handler.hpp` contains the GadHandler class, which provides 
		  functionality to encode and send the data packets.	
			
		.. code-block:: c++
			
			OxTS::Gal_Cpp::GadHandler gh;
			gh.SetEncoderToBin();
			gh.SetOutputModeToUdp(unit_ip);
			
		
		These three lines of code construct and configure the GAD handler, 
		indicating that we will be sending binary encoded packets to the IP 
		address of the INS.
					
		.. code-block:: c++
			
			OxTS::Gal_Cpp::GadVelocity gv(130);
			
		This constructs a GAD Velocity packet with stream ID 130. Stream IDs must be 
		between 129 and 254.
		
		.. code-block:: c++	
			
				gv.SetVelNed(0.0,0.0,0.0);
				gv.SetVelNedVar(0.01,0.01,0.01);
				gv.SetTimeVoid();
				gv.SetAidingLeverArmFixed(1.0,0.0,0.0);
				gv.SetAidingLeverArmVar(0.01,0.01,0.01);

				gh.SendPacket(gv);

		* The first line sets the velocity measurement, which we have taken in 
		  the North, East, Down :ref:`frame <Frames>`. Since we are assuming the INS is 
		  stationary, the measurement is zero.
		* The second line sets the covariance of our measurement. Typically, 
		  this is modelled based on the sensor providing the measurements. 
		  Since we do not have a real sensor for this example, we assume our 
		  "measurement" is reasonably accurate, with a standard deviation of 
		  10cm in all axes. For more information on covariance, see :ref:`cov`.
		* Line three sets the timestamp for this GAD packet. Since we have not 
		  synchronised time between the PC that is running this example and 
		  the INS, it would not be reliable to use a full timestamp. Instead, 
		  we make use of a Void timestamp which flags to the INS that it should 
		  be timestamped on arrival. For more information on timestamping your 
		  data, see :ref:`time_stamp` .  
		* The fourth line sets the lever arm of the aiding device, i.e., the 
		  displacement (in IMU frame) between the sensor and INS. Here, we 
		  suppose that our "sensor" is one metre ahead of the INS in the 
		  vehicle. For more information on lever arms, see :ref:`lever_arms`. 
		* The fifth line sets the lever arm's covariance, again this is in the 
		  IMU frame. This reflects the accuracy with which the lever arm has 
		  been measured. 
		
		Since our example is entirely static, none of these measurement values 
		are updated as we loop through sending packets. Of course, if we had a 
		real sensor, these values would be updated to reflect incoming 
		measurements.
		
		After the relevant data for the GAD packet has been stored, the next 
		line of code instructs the GadHandler to send the packet to the INS.

		Also, one should note the sleep function at the end of the code block.
		This is to ensure that the GAD packets are sent at a frequency of 10 Hz.
		In general, a GAD packet frequency between 10 and 1 Hz is recommended.
		

	.. tab:: Python

		.. code-block:: python
			
			import sys
			import time
			import oxts_sdk as ox
			
			if __name__ == "__main__":
				if len(sys.argv) < 3:
					print("Invalid number of command line arguments, requires: <IP> <number of packets>")
					sys.exit(1)
				
				unit_ip =  sys.argv[1]
				num_packets = sys.argv[2]
			
				gh = ox.GadHandler()
				gh.set_encoder_to_bin()
				gh.set_output_mode_to_udp(unit_ip)
				
				gv = ox.GadVelocity(130)
				for i in range(0,num_packets,1):
					gv.vel_ned = [0.0,0.0,0.0]
					gv.vel_ned_var = [0.01,0.01,0.01]
					gv.set_time_void()
					gv.aiding_lever_arm_fixed = [1.0,0.0,0.1]
					gv.aiding_lever_arm_var = [0.01,0.01,0.01]
					
					gh.send_packet(gv)
					print("packet " + str(i) + " sent")
					time.sleep(0.1)
			
				sys.exit(0)
		
		
		We will now break down the parts of the code which make use of the GAD 
		SDK.
		
		
		:code:`oxts_sdk` contains the all the code need for the GAD SDK, so we 
		import the module with the shortened name :code:`ox`, for convenience.
		
		.. code-block:: python
		
			import oxts_sdk as ox
			
		
		.. code-block:: python
		
			gh = ox.GadHandler()
			gh.set_encoder_to_bin()
			gh.set_output_mode_to_udp()
			
		These three lines of code construct and configure the GAD handler, 
		indicating that we will be sending binary encoded packets to the IP 
		address of the INS.
		
		.. code-block:: python
		
			gv = ox.GadVelocity(130)
		
		
		This constructs a GAD Velocity packet with stream ID 130. Stream IDs must be 
		between 129 and 254.
		
		.. code-block:: python
		
				gv.vel_ned = [0.0,0.0,0.0]
				gv.vel_ned_var = [0.01,0.01,0.01]
				gv.set_time_void()
				gv.aiding_lever_arm_fixed = [1.0,0.0,0.0]
				gv.aiding_lever_arm_var = [0.01,0.01,0.01]
				
				gh.send_packet(gv)
				print("packet " + str(i) + " sent")
				time.sleep(0.1)
		
				
		* The first line sets the velocity measurement, which we have taken in 
		  the North, East, Down :ref:`frame <Frames>`. Since we are assuming the INS is 
		  stationary, the measurement is zero.
		* The second line sets the covariance of our measurement. Typically, 
		  this is modelled based on the sensor providing the measurements. 
		  Since we do not have a real sensor for this example, we assume our 
		  "measurement" is reasonably accurate, with a standard deviation of 
		  10cm in all axes. For more information on covariance, see :ref:`cov`.
		* Line three sets the timestamp for this GAD packet. Since we have not 
		  synchronised time between the PC that is running this example and 
		  the INS, it would not be reliable to use a full timestamp. Instead, 
		  we make use of a Void timestamp which flags to the INS that it should 
		  be timestamped on arrival. For more information on timestamping your 
		  data, see :ref:`time_stamp` .  
		* The fourth line sets the lever arm of the aiding device, i.e., the 
		  displacement (in IMU frame) between the sensor and INS. Here, we 
		  suppose that our "sensor" is one metre ahead of the INS in the 
		  vehicle. For more information on lever arms, see :ref:`lever_arms`. 
		* The fifth line sets the lever arm's covariance, again this is in the 
		  IMU frame. This reflects the accuracy with which the lever arm has 
		  been measured. 
		
		Since our example is entirely static, none of these measurement values 
		are updated as we loop through sending packets. Of course, if we had a 
		real sensor, these values would be updated to reflect incoming 
		measurements.
		
		After the relevant data for the GAD packet has been stored, the next 
		line of code instructs the GadHandler to send the packet to the INS.

		Also, one should note the sleep function at the end of the code block.
		This is to ensure that the GAD packets are sent at a frequency of 10 Hz.
		In general, a GAD packet frequency between 10 and 1 Hz is recommended.
		

.. _hardware_setup:

Hardware setup and Initialisation
*********************************

Once you have written the GAD SDK code, and if necessary, compiled it and created an executable.
The next step is to configure your hardware.

* Install and configure the INS into your vehicle, as you would for aiding with 
  GNSS. (Note, you can have the GNSS antenna connected while using GAD).
* Mount your aiding sensor(s) onto the vehicle, the sensor should be securely 
  attached to the vehicle.
* Connect your sensor to the PC that will be running the GAD SDK program. Then 
  connect the PC via 
  `UDP <https://support.oxts.com/hc/en-us/articles/360009611120-Connecting-to-an-OxTS-INS-using-Ethernet>`_.
* Once connected, power on the INS, then configure the INS using 
  `NavConfig <https://support.oxts.com/hc/en-us/sections/115000630029-NAVconfig>`_. 
  If needed, extract the config file (.cfg) and make any necessary changes 
  (see :ref:`aidingtypes` & :ref:`section5`). After this, upload the edited file 
  onto the INS.
* Power on your sensor(s) and ensure that they are working correctly using the 
  appropriate third-party software.
* Initialise the INS, see :ref:`section5` for advanced initialisation options. In 
  certain environments it might be difficult to initialise the INS, if this is the case, 
  please contact `OxTS support <support@oxts.com>`_ .
* Start your GAD SDK script. You should now be ready to take your measurements!


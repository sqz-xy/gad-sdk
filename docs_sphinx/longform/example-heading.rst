.. _headingexample:

Heading Update Example
######################

This is the example illustrates how to use heading only updates. The full source code for this 
example can be found in `/examples/gal/heading.cpp`.

In this example, heading data is outputed to a csv but could also be sent to an OxTS INS in real time. 

Recommended prior reading:

- Building the SDK (README.md)
- :ref:`introduction`


Requirements
============

- An OxTS INS with the relevant Generic Aiding Feature Codes enabled. If you 
  are not sure whether you have the right Feature Codes or are unfamiliar with 
  them, contact support@oxts.com.
- A PC, connected to the INS via ethernet (if sending data to an OXTS INS).
- The GAD SDK has been built on this machine / pre-built binaries have been 
  downloaded (not currently available).

Method
============

How to run the executable.

Linux 
-----

1. Navigate to the relevant project confiugration directory in the build folder: 
   `cd <build_dir>/examples/gal`.
2. Run the executable: `./heading-example`. This will begin sending 
   Generic Aiding packets.  There are four possible optional argumnts that can be provided:   
   
   * Device IP address
   * Number of packets
   * Output type (csv)
   * Output file (if outputting to csv)
   
   For example: `./heading-example 192.168.25.10 70 csv debug_out.csv` will output 70 packets of data to debug_out.csv.
   To output to a live device omit the final 2 arguments: `./heading-example 192.168.25.10 70`

Windows
-------
1. Navigate to the relevant directory in the build folder: 
   `cd <build_dir>/examples/gal/Debug`.
2. From the command line run the executable: `heading-example.exe`. This will begin sending 
   Generic Aiding packets.  There are four possible optional argumnts that can be provided:   
   
   * Device IP address
   * Number of packets
   * Output type (csv)
   * Output file (if outputting to csv)
   
   For example: `heading-example.exe 192.168.25.10 70 csv debug_out.csv` will output 70 packets of data to debug_out.csv.
   To output to a live device omit the final 2 arguments: `heading-example.exe 192.168.25.10 70`


Source Code Breakdown
=====================

Here we run through the source code, explaining the purpose of each of the lines.

.. code-block:: c++

   #include "oxts/gal-cpp/gad.hpp"
   #include "oxts/gal-cpp/gad_handler.hpp"


These are the two includes required for most users of Generic Aiding. `gad.hpp` 
contains the `Gad` class used to form the basis of all Generic Aiding Data. 
`gad_handler.hpp` contains the `GadHandler` class, which provides functionality 
to encode and send the data packets.

Now we enter the `main()` function:

.. code-block:: c++

   int main(int argc, char * argv[])
   {
     int sendPackets = 30; 
	 std::string unit_ip = "192.168.25.22"; 
	 std::string file_out = "out.gad";    
	 int output_type = OUTPUT_TYPE::CSV;

Here we set the number of packets to send, the IPv4 adress of the unit recieving data or if we are instead outputing to csv. 
To send to the INS instead of a CSV change output_type to OUTPUT_TYPE::UDP.  These variables are also set form user input if provided.

.. code-block:: c++

	OxTS::GadHeading gh = OxTS::GadHeading(132);
	gh.SetHeading(180.0);
	gh.SetHeadingVar(0.1);
	gh.SetTimeVoid();
	gh.SetAidingAlignmentFixed(0.0,0.0,0.0);
	gh.SetAidingAlignmentVar(5.0, 5.0, 5.0);


Next, we set up the heading data with stream ID 132.   The heading is set to 180 degress,
with a variance of 0.1.  The alignment offsets are all set to 0.0 with an associated variance of 5.0. 

.. note::
Note that the offsets between the sensor and IMU should be given in the navigation frame.

The function :cpp:`SetTimeVoid()` indicates that the data will be sent with no 
timestamp, making it the simplest way to handle timing when working with 
Generic Aiding. In this setup, the INS will timestamp the packet upon receipt. 

.. code-block:: c++

   OxTS::GadHandler handler = OxTS::GadHandler();

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

This block of code sets up the 'GadHandler' and determines if the data is to be sent via
UDP or outputted to CSV.

.. code-block:: c++

   for (int i = 0; i < sendPackets; ++i)
	{
		handler.SendPacket(gh);

		if (i % 10 == 0)
			std::cout << i << " packets sent" << std::endl;

		OxTS::sleep(100);
	}



This final code block creates a `for` loop in which the heading data is 
encoded and sent via UDP to the INS or outputted to CSV as specified. With :cpp:`OxTS::Sleep(100)`, 
the data will be sent at a rate of ~10Hz.


Is my data being received by the INS?
=====================================

If you are unsure whether the INS is using the GAD, see 
:ref:`ismydatabeingreceived`.
 

Recommended next steps:

- Read more on creating aiding for each type: :ref:`aidingtypestoc`.

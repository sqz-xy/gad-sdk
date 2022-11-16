.. _staticaidingexample:

Static Aiding
#############

This example of Generic Aiding is designed to be used with a stationary INS. The 
full source code for this example can be found in 
`/examples/gal/static-aiding.cpp`.

In this example, position, velocity, and attitude data is sent to an OxTS INS 
in real time. 

Recommended prior reading:

- Building the SDK (README.md)
- :ref:`introduction`


Requirements
============

- An OxTS INS with the relevant Generic Aiding Feature Codes enabled. If you 
  are not sure whether you have the right Feature Codes or are unfamiliar with 
  them, contact support@oxts.com.
- A PC, connected to the INS via ethernet.
- The GAD SDK has been built on this machine / pre-built binaries have been 
  downloaded (not currently available).


Method
======

How to run the executable.

Linux 
-----

1. Navigate to the relevant project confiugration directory in the build folder: 
   `cd <build_dir>/examples/gal`.
2. Run the executable: `./static-aiding-example`. This will begin sending 
   Generic Aiding packets.  There are four possible optional argumnts that can be provided:   
   
   * Device IP address
   * Number of packets
   * Output type (csv)
   * Output file (if outputting to csv)
   
   For example: `./static-aiding-example 192.168.25.10 70 csv debug_out.csv` will output 70 packets of data to debug_out.csv.
   To output to a live device omit the final 2 arguments: `./static-aiding-example 192.168.25.10 70`

Windows
-------
1. Navigate to the relevant directory in the build folder: 
   `cd <build_dir>/examples/gal/Debug`.
2. From the command line run the executable: `static-aiding-example.exe`. This will begin sending 
   Generic Aiding packets.  There are four possible optional argumnts that can be provided:   
   
   * Device IP address
   * Number of packets
   * Output type (csv)
   * Output file (if outputting to csv)
   
   For example: `static-aiding-example.exe 192.168.25.10 70 csv debug_out.csv` will output 70 packets of data to debug_out.csv.
   To output to a live device omit the final 2 arguments: `static-aiding-example.exe 192.168.25.10 70`

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

.. code-block:: c++

   #ifdef _WIN32
   #include <windows.h>
   #elif __linux__
   #include <unistd.h>
   #endif
   
   namespace OxTS
   {
   void Sleep(int sleepMs)
   {
   #ifdef __linux__
       usleep(sleepMs * 1000);   // usleep takes sleep time in us (1 millionth of a second)
   #endif
   #ifdef _WIN32
       Sleep(sleepMs);    // Sleep takes sleep time in ms.
   #endif
   }
   } // OxTS


This code is not exclusive to Generic Aiding. It is a basic implementation of a 
cross-platform sleep function, which will make the system wait a set period of 
time before continuing execution.

.. code-block:: c++

   enum class OUTPUT_TYPE
   {
     UDP = 0,
     CSV = 1
   };


Extremely simple enum, to allow switching between CSV (file) and UDP (via 
ethernet) output in this example.

Now we enter the `main()` function:

.. code-block:: c++

   int sendPackets = 30; 
   std::string unit_ip = "192.168.25.22";
   std::string file_out = "out.gad";
   int output_type = OUTPUT_TYPE::UDP;


These variables determine some of the setup of the example, including the 
number of packets to send, the IP address to send the packets to, the output 
file, and whether to output to CSV or UDP. Naturally, only one of the IP 
address and output file are actually used on a given run.  These variables are also set form user input if provided.

.. code-block:: c++

   OxTS::GadPosition gp = OxTS::GadPosition(129);
   gp.SetPosGeodetic(51.91520330,-1.24479140,111.525);
   gp.SetPosVar(1,1,1);
   gp.SetTimeVoid();
   gp.SetAidingLeverArmFixed(0.5,0.5,1.0);
   gp.SetAidingLeverArmVar(0.1,0.1,0.1);


This portion of code sets up the static Generic Aiding Position data. Each 
Generic Aiding type has its own `Gad<type>` class which inherits from the `Gad` 
superclass. These subclasses are designed to simplify the process of setting 
data for users when working with the different data types. 

When initialising an instance of any `Gad` class, it is necessary to assign it 
a unique stream Id. These can take values in the range 128-254, and each one 
must be unique. See :ref:`streamiddefinition` for more details on stream Ids.

This particular position data is set in the WGS84 coordinate frame, using 
Latitude, Longitude, Altitude. The default values here correspond to the OxTS 
offices - users will need to change this to match their location. The 
covariance values are then set for this data. More information on how 
covariances should be estimated can be found in :ref:`estimatingerrors` . 

The Generic Aiding interface allows a few ways to timestamp data being sent to 
an INS. In this example, we choose to send no timestamp, or "Void". This 
indicates to the INS that the data should be timestamped by the system upon 
receipt. 

Finally, the lever arm and the variance on these values are set. The lever arm 
is the linear offset from the INS to the aiding device, in the IMU frame. The 
variance indicates how accurately these values are known. By setting the lever 
arm to "Fixed", it is indicated to the INS that this lever arm is not to be 
optimised. This is the most common setup.

.. code-block:: c++

   OxTS::GadVelocity gv = OxTS::GadVelocity(130);
   gv.SetVelNeu(0.0,0.0,0.0);
   gv.SetVelNeuVar(0.1,0.1,0.1);
   gv.SetTimeVoid();
   gv.SetAidingLeverArmFixed(0.5,0.5,1.0);
   gv.SetAidingLeverArmVar(0.1,0.1,0.1);


Next, we set up the velocity data, which follows a similar pattern to the 
position data. This aiding data is given stream ID 130.

The velocity is set in the North, East, Up (left-handed) coordinate system. 
Since we are creating *static* data, the velocity is zero in all axes. 

The lever arm for the velocity data is set to the same values as the position 
data for this example. This might suggest that the data is coming from the 
same source which is capable of calculating both types of measurement; perhaps 
a GNSS receiver. 

.. code-block:: c++

   OxTS::GadAttitude ga = OxTS::GadAttitude(131);
   ga.SetAtt(0.0,0.0,0.0);
   ga.SetAttVar(0.1,0.1,0.1);
   ga.SetTimeVoid();
   ga.SetAidingAlignmentOptimising(0.0,0.0,0.0);
   ga.SetAidingAlignmentVar(5.0,5.0,5.0);


The attitude data differs slightly from the two previous aiding types since it 
has an alignment, instead of a lever arm. This is due to the fact that when 
providing orientation aiding data to an INS, it is not the linear displacement 
between the aiding device and the INS which is relevant. Rather, it is the 
angular offsets between the two frames of reference which is important. In 
addition, this alignment is "Optimising" where the lever arms for the previous 
two datums were "Fixed". The "Optimising" tag indicates a couple of things to 
the INS:

- This alignment should be taken from the mobile.att file on the INS. The 
  accuracy for the alignment should be taken from mobile.ata
- This alignment should be optimised by the INS during operation, in order to 
  find the angles more accurately and therefore improve the quality of the aiding.

.. note:: 
   When the alignment for a Generic Aiding attitude device is set to 
   "Optimising", alignment for GNSS Dual Antenna must be reassigned. For more 
   information, see :ref:`reassigningtraditionaldatasources` .

.. code-block:: c++

   OxTS::GadHandler gh = OxTS::GadHandler();

   switch (output_type)
   {
     case OUTPUT_TYPE::UDP : 
       gh.SetEncoderToBin();
       gh.SetOutputModeToUdp(unit_ip);
       break;
     case OUTPUT_TYPE::CSV :
       gh.SetEncoderToCsv();
       gh.SetOutputModeToFile(file_out);
       break;
     default :
       std::cout << "Output type not known." << std::endl;
       break;
   }


This block of code initialises an instance of the `GadHandler` and sets it up 
to either send Generic Aiding data via UDP or to CSV file, based on the 
configuration option at the start of the file. 

.. code-block:: c++

   for (int i = 0; i < sendPackets; ++i)
   {
     gh.SendPacket(gp);
     gh.SendPacket(gv);
     gh.SendPacket(ga);

     if(i % 10 == 0)
       std::cout << i << " packets sent" << std::endl;

     OxTS::Sleep(100);
   }


This final code block creates a for loop in which the Generic Aiding data is 
encoded and sent to its configured destination (file or UDP). With 
`OxTS::Sleep(100)`, the data will be sent at a rate of ~10Hz.



That's it! This is all of the code necessary to send the three main types of 
aiding to an OxTS INS. For many applications, three additional sources of 
aiding across three types of aiding is more than is required. The kind 
of setup which would require this number of aiding sources would be one in 
which GNSS performance is heavily degraded.  

Recommended next steps:

- Read more on creating aiding for each type: :ref:`aidingtypestoc`.

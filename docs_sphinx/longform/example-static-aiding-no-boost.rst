.. _staticaidingexamplenoboost:

Static Aiding (No Boost)
########################

The is a simplified version of :ref:`staticaidingexample`, which can be used 
when Boost is not available. Since the socket functionality in this SDK is based 
on Boost, the socket functionality must be replaced by users with their chosen 
socket implementation. The full source code for this example can be found in 
`/examples/gal/static-aiding-no-boost.cpp`.

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

1. Navigate to the relevant directory in the build folder: 
   `cd <build_dir>/examples/gal`.
2. Run the executable: `./static-aiding-no-boost-example`. This will begin sending 
   Generic Aiding packets. You can also provide the number of packets to send: `./static-aiding-no-boost-example 100`

Windows
-------
1. Navigate to the relevant configuration directory in the build folder: 
   `cd <build_dir>/examples/gal/Debug`.
2. Run the executable: `./static-aiding-no-boost-example.exe`. This will begin sending 
   Generic Aiding packets.  You can also provide the number of packets to send: `./static-aiding-no-boost-example.exe 100`
   

Source Code Breakdown
=====================

Here we run through the source code, explaining the purpose of each of the lines.

.. code-block:: c++

   #include "oxts/gal-cpp/gad.hpp"
   #include "oxts/gal-cpp/gad_encoders/gad_encoder_bin.hpp"


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


Now we enter the `main()` function:

.. code-block:: c++

   int num_packets = 1000; 

This variable determines how many packets to send before exiting the program. This can also be provided as a command line argument.

.. code-block:: c++

   OxTS::GadPosition gp = OxTS::GadPosition(129);
   gp.SetWgs84Pos(51.91520330,-1.24479140,111.525);
   gp.SetPosVar(1,1,1);
   gp.SetTimeVoid();
   gp.SetAidingLeverArmFixed(0.5,0.5,1.0);
   gp.SetAidingLeverArmVar(0.1,0.1,0.1);


This portion of code sets up the static Generic Aiding Position data. Each 
Generic Aiding type has its own `Gad<type>` class which inherits from the `Gad` 
superclass. These subclasses are designed to simplify the process of setting 
data for users when working with the different data types. 

When initialising an instance of any `Gad` class, it is necessary to assign it 
a unique stream ID. These can take values in the range 128-254, and each one 
must be unique. 

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
arm to "Fixed" (see :ref:`positionlvafixed`), it is indicated to the INS that 
this lever arm is not to be optimised. This is the most common setup.

.. code-block:: c++

   OxTS::GadEncoderBin geb = OxTS::GadEncoderBin();


This block of code initialises an instance of the `GadEncoderBin`. This will 
provide the functionality to encode a Generic Aiding packet to binary.

.. code-block:: c++

   for (int i = 0; i < num_packets; ++i)
   {
     gh.EncodePacket(gp);

     // Add your code here for interacting with the static aiding packets.
     // Use accessor functions geb.GetPacket() and geb.GetPacketSize() to send 
     // the packet via chosen UDP socket library to the INS IP address and port 
     // 50485.

     if(i % 10 == 0)
       std::cout << i << " packets sent" << std::endl;
       std::cout << "packet size: " << geb.GetPacketSize() << std::endl;

     OxTS::Sleep(100);
   }


This final code block creates a for loop in which the Generic Aiding data is 
encoded. The comment indicates where users are required to add their socket 
implementation in order to send the Generic Aiding data to the INS. With 
`OxTS::Sleep(100)`, the data will be sent at a rate of ~10Hz.


Recommended next steps:

- Read more on creating the aiding types relevant for your system: 
  :ref:`aidingtypestoc`.


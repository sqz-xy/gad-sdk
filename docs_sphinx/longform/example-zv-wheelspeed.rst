.. _zvwheelspeedexample:

Zero Velocity Wheelspeed
########################

This is the simplest example of Generic Aiding. The full source code for this 
example can be found in `/examples/gal/zero-velocity-wheelspeed.cpp`.

In this example, zero speed data is sent to an OxTS INS in real time. 

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
2. Run the executable: `./zv-wheelspeed-example <IP> <Packets>`. This will begin 
   sending Generic Aiding packets to the specified IP address, which should be 
   set as the IP address of the INS, 
   e.g. `./zv-wheelspeed-example 192.168.25.10 1000`. 
   
Windows 
-------

1. Navigate to the relevant configuration type directory in the build folder: cd 
   <build_dir>/examples/gal/Debug.
2. Run the executable: `zv-wheelspeed-example.exe <IP> <Packets>`. This will begin 
   sending Generic Aiding packets to the specified IP address, which should be 
   set as the IP address of the INS, 
   e.g. `zv-wheelspeed-example.exe 192.168.25.10 1000`. 
   

INS configuration
=================

There is a small amount of setup required in the INS config for this example.
First, wheelspeed should be enabled through NAVconfig with a Pulses Per Metre 
(PPM) of 1000 and accuracy of this value of 1%. (Results in command 
`-wheelspeed1000_1` in the config). Additionally, the advanced command 
`-aid_wspeed_off` should be added.

Since this is a zero velocity update to confirm operation the zero velocity innovations 
should be inspected.

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
      std::string unit_ip   = argv[1]; // Unit to send GAD to
      int num_packets       = std::stoi(argv[2]); // Number of packets to send.

There are two input arguments for this executable: the IPv4 address of 
the INS which will be receiving the data, and the number of packets to send. 
Note that there is no advanced parsing or error handling to check that the 
argument has been inputted correctly. The other variable here sets the number 
of packets to send.

.. code-block:: c++

   OxTS::GadSpeed gs = OxTS::GadSpeed(130);
   gs.SetSpeedFw(0.0);
   gs.SetSpeedFwVar(0.0001);
   gs.SetTimeVoid();
   gs.SetAidingLeverArmOptimising();

Next, we set up the wheelspeed data with stream ID 130. 

Since we are creating zero wheelspeed data, the speed is set to zero in the 
forward axis. The covariance value for this data is set using the function 
:cpp:`SetSpeedFwVar()`. For more information on covariances, see 
:ref:`estimatingerrors` or :ref:`speedcovariancematrix`. For this case we are 
assuming we know very confidently that the speed is zero, so we can set the 
covariance pretty tight.

The function :cpp:`SetTimeVoid()` indicates that the data will be sent with no 
timestamp, making it the simplest way to handle timing when working with 
Generic Aiding. In this setup, the INS will timestamp the packet upon receipt. 

The final step to fill out the data packet is to indicate that the lever arm 
should be optimised by the INS. The lever-arm is a 3D translation in the IMU frame 
from the IMU (marked on the case of the INS) to the aiding device, measured in 
metres. The covariance values on this lever-arm are then set according to how 
accurately each translation could be measured. This part of the configuration should
be done in NAVconfig.

.. code-block:: c++

   OxTS::GadHandler gh = OxTS::GadHandler();
   gh.SetEncoderToBin();
   gh.SetOutputModeToUdp(unit_ip);

This block of code initialises an instance of the `GadHandler` and sets it up 
to send binary Generic Aiding data via UDP. 

.. code-block:: c++

   for (int i = 0; i < num_packets; ++i)
   {
     gh.SendPacket(gs);
     OxTS::Sleep(100);
   }


This final code block creates a `for` loop in which the Generic Aiding data is 
encoded and sent via UDP to the INS. With :cpp:`OxTS::Sleep(100)`, the data 
will be sent at a rate of ~10Hz.


Is my data being received by the INS?
=====================================

The INS should be initialised before sending the Generic Aiding data. To see 
if the INS is using the data you can check the measurments Innovation Zero 
VelocityUpdate [Xi, Yi, Zi] in NAVdisplay. If these are updating, the aiding 
is working. For an extra check, you can detach the GNSS antenna cable from the 
INS and you should see the velocity accuracy remain green. 
 

Recommended next steps:

- Read more on creating aiding for each type: :ref:`aidingtypestoc`.
- See a more complex example: :ref:`staticaidingexample`.

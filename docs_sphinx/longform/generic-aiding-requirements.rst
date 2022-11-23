.. _genericaidingrequirements:

Generic Aiding Requirements
###########################

This page outlines everything necessary to use the Generic Aiding interface.

OxTS INS
********

Generic Aiding is designed to be sent to OxTS INS devices, so it is only 
natural that an INS is required. More specifically though, units which support 
this functionality include:

- RT3000 v3
- AV200
- xNAV650
- xNAV550
- xNAV500
- RT1003
- ADK
- Anything else xbns and xDEV based


Feature Codes
*************

Generic Aiding is a Feature Code protected piece of OxTS functionality. As 
such, before getting started it is necessary to acquire the necessary Feature 
Codes for your OxTS INS. This can be done by contacting support@oxts.com. 
Temporary Feature Codes can be acquired for development purposes.

The Generic Aiding Feature Code is an optional extra that needs to be enabled before generic aiding will work. Please contact OxTS for further information.

An Aiding Device
****************

An aiding device is a piece of hardware which outputs generic aiding data to be input into the OxTS INS. Some examples include:

- Wheelspeed sensors
- LiDAR (SLAM output)
- Camera
- Radar device
- Ultra-wideband (UWB)

There are some requirements for aiding devices:

- A rigid mounting relative to the INS.
- The ability to send data over ethernet (UDP)

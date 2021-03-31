.. _timestamps:

Timestamping Data
#################

When sending aiding data to an OxTS, a decision must be made about how this 
data is timestamped. 

Some methods of timestamping are more complex than others, requiring 
synchronisation of devices. These methods are often more accurate and robust. 

Void
****

Void timestamps are the simplest to set up for users, since there is no need to 
calculate any time or synchronise time between devices. When data is sent with 
a Void timestamp, the INS will apply a timestamp upon receipt of the data. 

For this setup to work optimally, there must be a negligible transport latency 
between the aiding device and the INS. 


Latency
*******

This is not a full timestamp, but rather an estimate of the latency on the 
transport between the aiding device and the INS. The INS then applies a 
timestamp to the data upon receipt, accounting for the latency. 


PPS Relative
************

This is a timestamp relative to a PPS signal. The main thing to consider when 
using this timestamp type are where the PPS is coming from for the external 
system. 

- In the case that the INS and the aiding source both have access to PPS from 
  GPS, PPS relative timestamps can be used easily. 
- If the aiding source does not have access to PPS from GPS, it must receive a 
  PPS from somewhere else. OxTS devices can be configured to output a PPS.



GPS time
********

This is a full timestamp containing GPS week and Seconds from midnight Sunday. 
Obtaining this time from a GNSS receiver is the natural setup because it 
ensures synchronisation between the INS and aiding device, but it is not the 
only way to synchronise devices.

Not having access to time from a GNSS receiver does not preclude users the use 
of this timestamp type. The key factor is being able to synchronise the clocks 
betwen the INS and the aiding device. OxTS devices offer a number of options 
for clock synchronisation:

- Precision Time Protocol (PTP)
- Network Time Protocol (NTP)
- PPS output from the INS







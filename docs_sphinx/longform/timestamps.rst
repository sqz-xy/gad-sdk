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



External (in development)
*************************

.. warning::

  * This timestamp type is still in development and is therefore not fully 
    supported or recommended for use. It is not guaranteed that this feature 
    will make it to a full release.
  * Synchronsing the INS *output* time to the externa time currently causes GPS 
    data to be rejected, and can only be consequently used for indoor 
    applications.
  * Known bug: The external time must be greater than the internal INS time 
    (counts up from 0 at power on) in order to synchronise output times. 

The external timestamp allows users to stamp data with time from an external 
clock. The INS will then attempt to track the offset between its own internal 
time and the time of the external clock. If the offset is stable, the data will 
be used.

The following advanced commands are are relevant for this aiding type:

-gad_time_sync_id[x]
  [x] = The Generic Aiding stream ID which will be considered the external 
  time leader. Currently only one lead stream is available.
-gad_time_min_stable_pkts[x]
  [x] = Minimum number of packets from the lead stream with a stable time offset 
  before external time is considered synchronised. (Default: 5)
-gad_time_min_stable_secs[x.xx]
  [x.xx] = Minimum number of seconds from the lead stream with a stable time offset 
  before external time is considered synchronised. (Default: 5.0)
-gad_time_out
  This configures the INS to use the external clock time for output data. This 
  is not required for basic use of the synchronisation.
-time_sync_int
  Configures the INS to synchronise to its own internal PPS. This is required 
  in order to allow output time synchronisation.

The time can be set in the :cpp:`Gad` class by the function 
:cpp:`SetTimeExternal(week, secs)`.


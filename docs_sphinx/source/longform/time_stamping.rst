.. _time_stamp:
 
Timestamping
************

Knowing the epoch that a measurement was taken is crucial to being able to use it effectively in a sensor fusion algorithm. For example, a centimetre-level position measurement taken on a vehicle when travelling at 10 m/s (22 mph). An error on the timestamp of only 0.1s can look like an error of 1m to the INS.

The GAD SDK supports a few timestamp modes for users, aiming to cater to as many cases as possible. Some require almost no effort from the user (Void), whilst some require the INS and aiding device to be fully time synchronised (GPS time). 
Generally, lower effort approaches can work well for initial measurements, but the most accurate navigation data require fully synchronised timestamps.

Types of timestamp
------------------

There are two categories of timestamps you can give your data:

•	A timestamp in a specific format
•	An instruction for the INS to apply its own timestamp to the data when it receives it

It’s much simpler to instruct the INS to apply its own timestamp from a setup perspective, though not as accurate or robust. Which option you choose will depend on your appetite for synchronising time across devices, and how confident you are that all the devices in your setup are synchronised properly.
		
**Void**

If data is sent with a void timestamp, the INS applies a timestamp when it receives the data. Because you don’t have to synchronise time across any devices, void timestamps are the simplest to set up. However, you do need to ensure that there is negligible transport latency between the aiding device and the INS.
Using a void timestamp is not a viable choice if you are outputting your data to a GAD file and want to use it in post-processing. This is because the post-processing software will have no way of knowing what time the data should be applied at.

.. tabs::

   .. code-tab:: c++

	gv.SetTimeVoid(); // Just use void time
	
   .. code-tab:: py
		
	gv.set_time_void() # Just use void time

	
**Latency**

The latency timestamp is the same as the void timestamp, but you also specify the latency on the transfer of data between the aiding device and INS. When the INS receives data, it applies the timestamp accounting for that latency. 
If you are aware that your data latency is likely to fluctuate, then you will get much better results using the timestamp formats below, rather than using latency or void mode. This can often be relevant if data is being passed over a busy network. 
As with the void timestamp, the latency timestamp is not viable if you are outputting data to a GAD file and want to use it in post-processing.

Note that the latency is measured in seconds.

.. tabs::

	.. code-tab:: c++

		gv.SetTimeLatency(0.1); // Latency of 0.1s
	
	.. code-tab:: py
		
		gv.time_latency = 0.1 # Latency of 0.1s


	.. note::
	
		To measure the latency, collect some data under good GNSS conditions (so you know that the INS is calculating time accurately). 
		Then, compare the GAD with the INS only output. You should see the data follows the same shape, but with a time-offset between the two data sets. This offset is the latency.
		

**GPS time**

If your device’s clock has been synchronised with the INS, this command will provide the timestamp in the GPS format. I.e., the GPS week and the number of seconds from midnight on Sunday. 

.. tabs::

	.. code-tab:: c++

		gv.SetTimeGps(gps_week, gps_seconds); // Packet timestamped with GPS time
	
	.. code-tab:: py
		
		gv.time_gps = [gps_week, gps_seconds] # Packet timestamped with GPS time


**UNIX time**

If your device’s clock has been synchronised with the INS, this command will provide the timestamp in UNIX time format, encoded as the number of seconds from the UNIX epoch.

.. tabs::

	.. code-tab:: c++

		gv.SetTimeUTCUnix(unix_seconds); // Packet timestamped with Unix time
	
	.. code-tab:: py
		
		gv.time_utc_unix = unix_seconds # Packet timestamped with Unix time


**TAI time**

If your device’s clock has been synchronised with the INS, this command will provide the timestamp in the International Atomic Time format.

.. tabs::

	.. code-tab:: c++

		gv.SetTimeTAI(tai_seconds); // Packet timestamped with TAI time
	
	.. code-tab:: py
		
		gv.time_tai = tai_seconds # Packet timestamped with TAI time


**PPS relative**

If your device’s clock has been synchronised with the INS, this command will provide a timestamp relative to the pulses per second (PPS) signal from your INS.

.. tabs::

	.. code-tab:: c++

		gv.SetTimePpsRelative(pps_relative); // Packet timestamped with PPS relative time
	
	.. code-tab:: py
		
		gv.pps_relative= pps_relative_seconds # Packet timestamped with PPS relative time

.. _syn_clocks:

Synchronising clocks
--------------------

To use GPS, UNIX, TAI, or PPS timestamps, you need to first synchronise the clocks of the INS and sensor device. At present, when you synchronise your INS to any other device, the INS will always assert that its time is the correct one (it is the PTP master). Since your INS is usually getting its time from the GNSS signal, it’s a pretty reliable source of time for your system.
If you don’t have access to time from a GNSS receiver, though, you can still synchronise time between your devices. In this situation, the INS will either use the last GPS time it received via GNSS to continue calculating time, or it will use its internal system time if it didn’t get GPS time since being initialised. 

You can synchronise your devices’ clocks via:

*	`Precision Time Protocol (PTP) <https://support.oxts.com/hc/en-us/articles/360016515759-PTP-Quick-Start-Guide>`_
*	Network Time Protocol (NTP)
*	Pulses Per Second output from the INS (PPS)

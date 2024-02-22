.. _canws_example:

CAN wheel speed
###############

In this example we show how wheel speed data from a vehicle’s `CAN (Control Area Network) bus <https://en.wikipedia.org/wiki/CAN_bus>`_ can be used as a GAD source. 

When using the CAN data, we recommend that you write the GAD SDK program in Python; as this will allow you to make use of Python’s `CAN library <https://python-can.readthedocs.io/en/stable/index.html>`_. 
To our knowledge, a similar library does not exist for C++.

It should be noted that the code shown here serves to illustrate that it is possible to use the CAN bus's data as a GAD update.
In order to use CAN data for your vehicle/device, significant changes to the CAN reader's configuration will be needed. 
Consult the `python-can library <https://python-can.readthedocs.io/en/stable/index.html>`_ and your device/vehicle's CAN documentation (see note below) on how to do this.


	**A note about CAN messages**
	
	If you are using an independent aiding device that produces CAN messages, you can refer to the device’s documentation for the message IDs. 
	However, if you are plugging into the CAN bus of a vehicle, it will be harder to identify the message ID you want. 
	If you are an OEM employee then you should have full access to all the message IDs your vehicle uses, but if you are not, then you can refer to these `open-source <https://en.wikipedia.org/wiki/OBD-II_PIDs>`_ lists that tell you some IDs to look out for. 


For the specfic vehicle used in this example, the wheel speed data transmitted by its CAN bus is in miles per hour and is a scalar, i.e. it does not give information on whether the motion is in the forwards or backwards direction.
Therefore, the unsigned aiding frame is used for the GAD speed update. Furthermore, the data needs to be converted into metres per second.

Source code
***********

.. code-block:: python

	import oxts_sdk # Used to create and transmit GAD packets
	import can # Used to request, receive and decode CAN packets
	import time
	
	unit_ip = "192.168.25.11"
	stream_id = 157
	
	# Set up the reader to receive CAN messages
	bus = can.interface.Bus(bustype='pcan', channel='PCAN_USBBUS1', bitrate=1000000)
	
	# Set up the handler to create and send GAD packets
	gad_hand = oxts_sdk.GadHandler()
	gad_hand.set_encoder_to_bin()
	gad_hand.set_output_mode_to_udp(unit_ip)
	
	# Cycle through the message bus, looking for a relevant message
	for msg in bus:
		if msg.arbitration_id == 1540:
			# Forward is 1st set of 2 bytes, little endian, signed
			ws = (1609.34/(60*60))*0.01*int.from_bytes(msg.data[0:2], "little", signed=False)
			gad_spe = oxts_sdk.GadSpeed(stream_id)
			gad_spe.speed_un_ms = ws
			gad_spe.speed_ms_var = 0.01*ws*ws # Just an estimate
			gad_spe.time_latency = 0.1 # Just an estimate, could measure for better results
			gad_spe.set_aiding_lever_arm_config()
			gad_hand.send_packet(gad_spe)
			time.sleep(0.1)

CAN-specific code
*****************

You should be familiar with most of the code shown above. However, there is some CAN-specific code that we shall explain.

.. code-block:: python
	
	bus = can.interface.Bus(bustype='pcan', channel='PCAN_USBBUS1', bitrate=1000000)


The first step in extracting the wheel speed aiding data is to configure the CAN bus reader. 
The line of code above shows how the reader was configured for this specific example. 
Again, refer to the Python CAN library and your device/vehicle's CAN documentation for the correct configurations.
Once configured correctly, the CAN bus reader will extract all CAN messages.


The CAN bus will send a large number of messages each second, the majority of which will not be useful in providing wheelspeed aiding. 
Therefore, one needs to filter through all the messages to find the specific messages that contains the correct type of aiding data. 
The correct messages are identified by the message ID number, which can be found in the device/vehicle's CAN documentation.

.. code-block:: python

	for msg in bus:
		if msg.arbitration_id == 1540:
			ws = (1609.34/(60*60))*0.01*int.from_bytes(msg.data[0:2], "little", signed=False) 


In the lines of code shown above, the first line cycles through all the messages extracted from the CAN bus. 

The second line identifies the messages with the correct ID. In the case given here, the message ID for wheel speed is 1540.

The third line converts the data from the ID = 1540 messages into speed in metres per second. Specifically, the code converts the first two 
bytes (msg.data[0:2]) of the message data into an integer (int.from_bytes). Here the "little" argument means `little-endian <https://en.wikipedia.org/wiki/Endianness>`_,
i.e., this specific CAN bus stores the least-significant byte at the smallest address.
In order to reduce memory usage, this **specific** CAN bus encodes the speed message as integer. Where the integer is equal to 100 times the real value of the speed.
Hence to extract the correct value of the speed in miles per hour, the decoded integer needs to be multiplied by 0.01. 

Finally, the multiplication by (1609.34/(60*60)) is used to convert from miles per hour to metres per second.



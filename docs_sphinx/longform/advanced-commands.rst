.. _advancedcommands:

Advanced Commands
#################

Advanced commands are options that can be set on the INS to allow different 
functionality or change the behaviour of the INS. They are set in the mobile.cfg file which can be found by
using FTP to a device.

The easiest way to set these advanced commands is on the Commands tab inside the Advanced Tools page in NAVconfig. 
NAVconfig is available for Windows as part of NAVsuite, which is OxTS' proprietary suite of applications for configuring and interacting with OxTS devices.
It is downloadable from the OxTS website https://support.oxts.com/hc/en-us/sections/115000789105-NAVsuite

Commands specific for GAD applications
########

.. code-block::

   -gad_lrf[lrf_id]_[lat]_[lon]_[alt]_[yaw]_[pitch]_[roll]
   
Angles are expected in degrees. This command sets a new GAD local reference frame with a specified Id.
The `lrf_id` is a unique identifier for each local reference frame. Up to 32 reference frames can be defined in this way. 
Once the local refence frame has been defined, it must be associated to the stream Id of the relevant aiding so that the INS knows which local reference 
frame to use for a particular aiding source.

.. code-block::

   -gad_lrf_id[stream_id]_[lrf_id]

This command sets a specific GAD `stream_id` to use the `lrf_id`. 


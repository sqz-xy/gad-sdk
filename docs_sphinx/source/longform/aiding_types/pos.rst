.. _pos_aidingtype:

Position
********

If you have a sensor that produces data on a unit’s position, whether in absolute terms or relative to some known point, you can provide that to an OxTS INS via the ‘position’ aiding type. 
Each of the fields for the Position data type can be set using functions from the GadPosition class.


Aiding frames
-------------

Position data can be provided to the INS in one of two coordinate frames, based on whether your system provides a global position on Earth — such as that produced by GNSS — or a position relative to another known point, such as to track devices inside a warehouse:

•	**Geodetic - Latitude, longitude, altitude.** For precise global positioning, you’d use this frame, which expects data in the WGS84 global coordinate format. Measurements in this frame are expected in degrees (latitude and longitude) and metres (altitude). 

•	**User-defined local frame.** Position relative to a local reference frame defined by the user. More information on how to define the frame itself can be found in the :ref:`user-defined local frame section <Frames>`. Position measurements in this frame are expected in metres.

Learn more about frames

Covariance
----------

Covariance is used as an estimate of the accuracy of a measurement.  Measurements with a smaller covariance will be given greater weight in the navigation solution, and any obvious outliers will be rejected by the navigation engine. Whatever frame you’re using, position covariance is expected in m\ :sup:`2`.
In your code, you can either add a diagonal covariance matrix, or a full covariance matrix. Note that you will need to add covariance for both your data, and for your lever arm.

To learn more about covariance and how to derive the values you need, see :ref:`here <cov>`.

Lever arm
---------

Position measurements must be provided with a lever arm (X,Y,Z) which defines the translation from the IMU to the aiding device, in the IMU frame. You can use the following lever arms with position data:

**Fixed**

A fixed lever arm is the simplest to set up, as it requires no external configuration. It is set within the generic aiding packet itself.

**Config**

A Config lever arm is functionally equivalent to a fixed lever arm. The difference is that the lever arm is set in the config file of the INS instead of within the data packet.

:ref:`Learn more about lever arms. <lever_arms>`

Code examples
-------------

Here are two examples of how you might configure the GadHandler to transmit position data.

**Example 1: Latitude, longitude, altitude frame, using a diagonal covariance matrix and a config lever arm.**

.. tabs::

   .. code-tab:: c++

		OxTS::Gal_Cpp::GadPosition gp(132); // Sets the GAD position update to stream #132
		gp.SetPosGeodetic(latitude, longitude, altitude); // Measurement in WGS84, lat, long, alt
		gp.SetPosGeodeticVar(var_lat, var_long, var_alt); // Diagonal covariance matrix
		gp.SetAidingLeverArmConfig(); // Set lever arm to 'config', i.e. set in the configuration file
		
   .. code-tab:: py
		
		gp = oxts_sdk.GadPosition(132) #Sets the GAD position update to stream #132
		gp.pos_geodetic = [latitude, longitude, altitude] # Measurement in WGS84, lat, long, alt
		gp.pos_geodetic_var = [var_lat, var_long, var_alt] # Diagonal covariance matrix
		gp.set_aiding_lever_arm_config() # Set lever arm to 'config', i.e. set in the configuration file


Note that, for the config lever arm to work, you will need to add the following commands to the config file of your INS:

.. code-block:: c

	-location4_0.0_0.0_0.1_0.01 // Set a lever arm with ID '4' to values 0.0, 0.0, 0.1, diagonal variance 0.01 for all
	-gad_loc_id132_4 // Match the aiding stream with ID '132' with lever arm ID '4'

**Example 2: User-defined local frame, using a full covariance matrix and a fixed lever arm.**


.. tabs::

   .. code-tab:: c++

		OxTS::Gal_Cpp::GadPosition gp(132); //Sets the GAD position update to stream #132
		gp.SetPosLocal(data_x, data_y, data_z); // Set a measurement in x, y and z relative to the local reference frame origin
		gp.SetPosLocalVar(var_x, var_y, var_z, covar_xy, covar_xz, covar_yz); // Set a full covariance matrix, with data as measured for the sensor
		gp.SetAidingLeverArmFixed(0.0, 0.0, 0.1); // Lever arm sent in packet, measuring device is 0.1m vertically above the INS
		gp.SetAidingLeverArmVar(0.01, 0.01, 0.01); // Lever arm variance, diagonal matrix with 0.1m standard deviation on each direction

   .. code-tab:: py
		
		gp = oxts_sdk.GadPosition(132) #Sets the GAD position update to stream #132
		gp.pos_local = [data_x, data_y, data_z] # Set a measurement in x, y and z relative to the local reference frame origin
		gp.pos_local_var = [var_x, var_y, var_z, covar_xy, covar_xz, covar_yz] # Set a full covariance matrix, with data as measured for the sensor
		gp.aiding_lever_arm_fixed = [0.0, 0.0, 0.1] # Lever arm sent in packet, measuring device is 0.1m vertically above the INS
		gp.aiding_lever_arm_fixed_var = [0.01, 0.01, 0.01] # Lever arm variance, diagonal matrix with 0.1m standard deviation on each direction

Note that, to make use of the local frame, you must define the local coordinate frame in the configuration of the INS. To do this, add the following commands to the config file of your INS:

.. code-block:: c

		-gad_lrf2_51.915_-1.244_94.597_-90.0_180.0_0.0 // This sets the lrf ID '1' with an example lat, long, alt, yaw, pitch, roll.
		-gad_lrf_id132_2 // Match the aiding stream with ID '132' with lrf ID '1'


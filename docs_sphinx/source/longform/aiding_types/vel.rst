.. _vel_aidingtype:

Velocity
********

You can use the generic aiding interface to send velocity data to your INS. Use the GadVelocity class to set the fields for this data type. 

Aiding frames
-------------

Velocity aiding can be provided to the INS in one of three coordinate frames:

•	**Odometry frame** Velocity data measured in the coordinate frame of the sensor itself. An example of a device that might use the odometry frame is a camera mounted to the front of a car measuring velocity — it knows its velocity compared to objects around it, but not relative to Earth.  
•	**North East Down (NED)** The NED frame is the simplest way to provide velocity aiding to the INS, as it requires no other configuration (the INS itself uses NED). This frame is ideal for any sensors that provide data in a global frame, such as GNSS, and a use-case example would be to track an object’s velocity under open skies. It is important to note that the NED frame is curvilinear, in that the frame origin moves with the vehicle’s global position but is always oriented to NED at that point.
•	**User-defined local frame** This works in a very similar way to NED, except that the velocity measurement is relative to a fixed reference frame on Earth. A use case would be an indoor positioning system with a fixed local frame defined by the physical setup of the system. .

Regardless of the frame used, velocity data is expected in m/s.


Covariance
----------

Covariance  is used as an estimate of the accuracy of a measurement.  Measurements with a smaller covariance will be given greater weight in the navigation solution, and any obvious outliers will be rejected by the navigation engine.
Whether using the NED, user-defined local or odometry frame, velocity covariance is expected in m/s squared. In your code, you can either add a diagonal covariance matrix, or a full covariance matrix. Note that you will need to add covariance for both your data, and for your lever arm.

To learn more about covariance and how to derive the values you need, see :ref:`here <cov>`. 

Lever arm
---------

Velocity measurements must be provided with a lever arm (X,Y,Z) which defines the translation from the IMU to the aiding device, in the IMU frame. Note that odometry-frame velocity must also be provided with an orientation relative to the IMU frame. You can use the following lever arms with velocity data:

**Fixed**

A fixed lever arm is the simplest to set up, as it requires no external configuration. It is set within the generic aiding packet itself.

**Config**

A Config lever arm is functionally equivalent to a fixed lever arm. The difference is that the lever arm is set in the config file of the INS, instead of within the data packet.

:ref:`Learn more about lever arms. <lever_arms>`

Code examples
-------------

Here are two examples of how to configure the GadHandler to transmit velocity data:

**Example 1: Odometry frame, using a full covariance matrix and a config lever arm.**

.. tabs::

   .. code-tab:: c++

		OxTS::Gal_Cpp::GadVelocity gv(133); // Sets velocity aiding data to GAD stream ID 133
		gv.SetVelOdom(vx, vy, vz); // Set a measurement in the odometry frame, coming from your aiding device
		gv.SetVelOdomVar(var_x, var_y, var_z, covar_xy, covar_xz, covar_yz); //Full covariance matrix, in (m/s)^2
		gv.SetAidingLeverArmConfig(); //Set lever arm to 'config', i.e. set in the configuration file

   .. code-tab:: py
		
		gp = oxts_sdk.GadVelocity(133) # Sets velocity aiding data to GAD stream ID 133
		gv.vel_odom = [vx,  vy,  vx] # Set a measurement in the odometry frame, coming from your aiding device
		gv.vel_odom_var = [var_x, var_y, var_z, covar_xy, covar_xz, covar_yz] # Full covariance matrix, in (m/s)^2
		gv.aiding_lever_arm_config() # Set lever arm to 'config', i.e. set in the configuration file

Note that, in order for the config lever arm to work, you will need to add the following code to the config file of your INS. For example:

.. code-block:: c

		-location4_0.0_0.0_0.1_0.01 // Set a lever arm with ID '4' to values 0.0m, 0.0m, 0.1m, diagonal variance 0.01m^2 for all
		-gad_loc_id133_4 // Match the aiding stream with ID '133' with lever arm ID '4'

Furthermore, if you are using the odometry frame, you need to provided the orientation of the sensor in the IMU frame. 
This is done by adding the `-attitude...` command to the INS' config file. For example:

.. code-block:: c

		-attitude3_3.0_15.0_0.0_1.0 // Set an alignment with ID '3' and values 3, 15 and 0 degrees from the IMU axes respectively, variance 1.0 deg^2 for all
		-gad_att_id133_3 // Match the aiding stream with ID '133' with alignment ID '3'
		
**Example 2: NED frame, using a diagonal covariance matrix and a fixed lever arm.**

.. tabs::

   .. code-tab:: c++

		OxTS::Gal_Cpp::GadVelocity gv(133); // Sets velocity aiding data to GAD stream ID 133
		gv.SetVelNed(v_north, v_east, v_down); // Set a velocity measurement using the NED frame
		gv.SetVelNedVar(var_n, var_e, var_d); // Diagonal covariance matrix, in (m/s)^2
		gv.SetAidingLeverArmFixed(0.0, 0.0, 0.1); // Lever arm sent in packet, measuring device is 0.1m vertically above the INS
		gv.SetAidingLeverArmVar(0.01, 0.01, 0.01); // Lever arm variance, diagonal matrix with 0.1m standard deviation on each direction


   .. code-tab:: py
		
		gv = oxts_sdk.GadVelocity(133) # Sets velocity aiding data to GAD stream ID 133
		gv.vel_ned = [v_north, v_east, v_down] # Set a velocity measurement using the NED frame
		gv.vel_ned_var = [var_n, var_e, var_d] # Diagonal covariance matrix, in (m/s)^2
		gv.aiding_lever_arm_fixed = [0.0, 0.0, 0.1] # Lever arm sent in packet, measuring device is 0.1m vertically above the INS
		gv.aiding_lever_arm_fixed_var = [0.01, 0.01, 0.01] # Lever arm variance, diagonal matrix with 0.1m standard deviation on each direction

Note for this example, the config file does not require any extra commands.

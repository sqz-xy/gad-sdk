
.. _hea_aidingtype:

Heading
*******

The Heading update is effectively a one-dimensional version of the Attitude update.

You can set the fields for this data type using functions from the GadHeading class.



Aiding frames
-------------
The heading angle is the projection of the vehicle’s body x-axis in the navigation frame’s north-east plane. You can use the following frames for heading:

*	**NED frame** This is the standard frame for supplying heading updates and moves in line with the vehicle.
*	**User-defined Local Frame** Heading aiding also supports a user-defined local frame.

Heading measurements in both frames are expected in degrees (0–360°).

:ref:`Learn more about frames. <Frames>`

Variance
----------

Covariance is used as an estimate of the accuracy of a measurement. 
Measurements with a smaller covariance will be given greater weight in the navigation solution, and any obvious outliers will be rejected by the navigation engine. 

Because only one value is provided for this update, only one variance value is needed. The Heading variance is expected in degrees squared. 
Note that a normal covariance is needed for the alignment. 

To learn more about covariance and how to derive the values you need, see :ref:`here <cov>`. 

Alignment
---------
As for the Attitude aiding type, heading measurements have an associated alignment, as opposed to a lever arm. This is because the linear offset between the attitude sensor and the IMU does not affect the measurements; you only need to account for the angular offset between the two.

**Fixed**

A fixed alignment is the simplest to set up, as it requires no external configuration. It is set within the generic aiding packet itself.

**Config**

A Config alignment is functionally equivalent to a fixed alignment. The difference is that the lever arm is set in the config file of the INS, instead of within the data packet.

Code examples
-------------

Here are two examples of how to configure the GadHandler to transmit heading data.

**Example 1: NED frame, with a fixed alignment.**

.. tabs::

   .. code-tab:: c++
   
		OxTS::Gal_Cpp::GadHeading ghe(135); // Sets heading aiding data to GAD stream ID 135
		ghe.SetHeading(heading); // Set a heading measurement in NED frame
		ghe.SetHeadingVar(var_hea); // Only one measurement, so covariance matrix is only one value!
		ghe.SetAidingAlignmentFixed(3.0, 0.0, 0.0); // Set an alignment in the packet of 3 degrees from the IMU heading
		ghe. SetAidingAlignmentVar(1.0, 0.0, 0.0); // Set alignment covariance of 1 degree 

   .. code-tab:: py
   
		ghe = oxts_sdk.GadHeading(135) # Sets heading aiding data to GAD stream ID 135
		ghe.heading = heading # Set a heading measurement in NED frame
		ghe.heading_var = var_hea # Only one measurement, so covariance matrix is only one value!
		ghe.aiding_alignment_fixed = [3.0, 0.0, 0.0] # Set an alignment in the packet of 3 degrees from the IMU heading
		ghe.aiding_alignment_var = [1.0, 0.0, 0.0] # Set alignment covariance of 1 degree 

**Example 2: User-defined Local Frame, with an alignment from the config file.**

.. tabs::

   .. code-tab:: c++
   
		OxTS::Gal_Cpp::GadHeading ghe(135); // Sets heading aiding data to GAD stream ID 135
		ghe.SetHeadingLocal(heading); // Set a heading measurement in a user defined local frame
		ghe.SetHeadingVar(var_hea); // Only one measurement, so covariance matrix is only one value!
		SetAidingAlignmentConfig(); // Set aligment to 'config', i.e. set in the configuration file


   .. code-tab:: py
   
		ghe = oxts_sdk.GadHeading(135) # Sets heading aiding data to GAD stream ID 135
		ghe.heading_local = heading # Set a heading measurement in a user defined local frame
		ghe.heading_var = var_hea # Only one measurement, so covariance matrix is only one value!
		ghe.set_aiding_alignment_config() # Set aligment to 'config', i.e. set in the configuration file

Note that, to make use of the local frame, you must define the local coordinate frame in the configuration of the INS. 
To do this, add the similar commands to the config file of your INS:

.. code-block:: c

		-gad_lrf2_51.915_-1.244_94.597_-90.0_180.0_0.0 // This sets the lrf ID '1' with an example lat, long, alt, yaw, pitch, roll.
		-gad_lrf_id135_1 // Match the aiding stream with ID '135' with lrf ID '1'
		-rotation1_3.0_0.0_0.0_1.0_0.0_0.0 // # Set an alignment in the packet of 3, 0 and 0 degrees respectively from the INS axes. Also Set alignment covariance matrix to a diagonal matrix

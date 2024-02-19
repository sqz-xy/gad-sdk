
.. _spe_aidingtype:

Speed
*****

The speed aiding type allows you to give a one-dimensional velocity measurement to the INS and is, therefore, a special case of Velocity. 
Each of the fields for this data type can be set using functions from the GadSpeed class.

Aiding Frames
-------------

Speed updates can only be provided in the vehicle frame. However, there are six variations on that frame. 
First, you can provide speed updates in three directions:

**fw** interprets any positive values as forward motion.

**bw** interprets any negative values as forward motion.

**un** does not specify whether the motion is forwards or backwards. The direction of the motion is determind using the other data available.

Second, each direction can be combined with one of two types of speed type:

**ms** provides a speed value in m/s..

**pulsed** is designed for pulsed wheelspeed sensors, its input arguments are the number pulses per second, a scale factor, and a period to measure over.
The scale factor gives the metres per pulse. Both period and scale factor are mandatory inputs.

So, for example:

.. tabs::

   .. code-tab:: c++
   
		gs.SetSpeedBwMS
	
   .. code-tab:: py
   
		gs.speed_bw_ms

   
Represents a wheel speed sensor where backwards motion (speed_ms) is given by a positive value in m/s.

.. tabs::

   .. code-tab:: c++
   
		gs.SetSpeedUnPulsed
	
   .. code-tab:: py
   
		gs.speed_un_pulsed 


Represents a pulsed wheel speed sensor, that does not specify it’s direction of motion.


Measurement values
------------------

If the speed update is provided in m/s, then no other information is required. However, if this is not the case, then additional information will be needed. 
For example, if the speed sensor provides data in mph, code to convert it into metres per second will be needed. 

For pulsed speed updates additional inputs may also be required:

1.	A frequency. This is mandatory and is usually just the pulses per second outputted by the sensor.
2.	A scale factor. This is optional and is used to convert the frequency into speed. It is usually the circumference of the vehicle’s wheel in metres.
3.	A period. This is optional and represents a time window in which the measurement was recorded.


Covariance
----------

Covariance is used as an estimate of the accuracy of a measurement. Measurements with a smaller covariance will be given greater weight in the navigation solution, and any obvious outliers will be rejected by the navigation engine. 
For the speed update, covariance works a little differently. 
This is because, unlike other update types, the three values you provide are completely independent of each other, i.e. they are variances, and the covariances are zero. Each variance is still expected in the same unit as the corresponding measurement – but squared.

The are two options:

*	If you are providing a m/s speed update, you simply provide a variance for the speed value.
*	If you are providing a pulsed update, you need to provide a variance for your frequency and scale factor; the variance for the period is optional.

Note that for any speed update you will need to provide variance for both your data, and for your lever arm.


Lever Arm
---------

Speed measurements must be provided with a lever arm (X,Y,Z) which defines the translation from the IMU to the aiding device, in the IMU frame. You can use the following lever arms with speed data:

**Fixed**

A fixed lever arm is the simplest to set up, as it requires no external configuration. It is set within the generic aiding packet itself.

**Config**

A Config lever arm is functionally equivalent to a fixed lever arm. The difference is that the lever arm is set in the config file of the INS instead of within the data packet.

:ref:`Learn more about lever arms. <lever_arms>`

Code examples
-------------

Here’s how you might code GadHandler to transmit speed data:

**Example 1: Forward-positive speed only measurement, with a fixed lever arm.**

.. tabs::

   .. code-tab:: c++
   
		OxTS::Gal_Cpp::GadSpeed gs(136); // Sets speed aiding data to GAD stream ID 136.
		gs.SetSpeedFw(speed_ms); // Set a forwards-positive speed measurement in m/s. 
		gs.SetSpeedFwVar(var_speed); // Covariance on speed, in (m/s)^2.
		gs.SetAidingLeverArmFixed(0.0, 0.0, 0.1); // Lever arm sent in packet, measuring device is 0.1m vertically above the INS.
		gs.SetAidingLeverArmVar(0.01, 0.01, 0.01); // Lever arm variance, diagonal matrix with 0.1m standard deviation on each direction.

	
   .. code-tab:: py
   
		gs = oxts_sdk.GadSpeed(136) # Sets speed aiding data to GAD stream ID 136.
		gs.speed_fw_ms = [speed_ms] # Set a forwards-positive speed measurement in m/s. 
		gs.speed_ms_var = var_speed # Covariance on speed, in (m/s)^2. 
		gs.aiding_lever_arm_fixed = [0.0, 0.0, 0.1] # Lever arm sent in packet, measuring device is 0.1m vertically above the INS.
		gs.aiding_lever_arm_fixed_var = [0.01, 0.01, 0.01] # Lever arm variance, diagonal matrix with 0.1m standard deviation on each direction. 


**Example 2: Unsigned pulsed speed measurement, with no period variance, with a fixed lever arm.**

.. tabs::

   .. code-tab:: c++
   
		OxTS::Gal_Cpp::GadSpeed gs(137); // Sets speed aiding data to GAD stream ID 137.
		gs.SetSpeedUnPulsed(frequency, scale_factor, period); // Set an unsigned pulsed speed measurement in pulses per second, with a scale factor in meters and a period in seconds.
		gs.SetSpeedPulsedVar(var_frequency, var_scale_factor); // Variance on pulse frequency and scale factor respectively.
		gs.SetAidingLeverArmFixed(0.0, 0.0, 0.1); // Lever arm sent in packet, measuring device is 0.1m vertically above the INS.
		gs.SetAidingLeverArmVar(0.01, 0.01, 0.01); // Lever arm variance, diagonal matrix with 0.1m standard deviation on each direction.


	
   .. code-tab:: py
   
		gs = oxts_sdk.GadSpeed(137) # Sets speed aiding data to GAD stream ID 137.
		gs.speed_un_pulsed = [frequency, scale_factor, period] # Set an unsigned pulsed speed measurement in pulses per second, with a scale factor in meters and a period in seconds. 
		gs.speed_pulsed_var = [var_frequency, var_scale_factor] # Variance on pulse frequency and scale factor respectively.
		gs.aiding_lever_arm_fixed = [0.0, 0.0, 0.1] # Lever arm sent in packet, measuring device is 0.1m vertically above the INS.
		gs.aiding_lever_arm_fixed_var = [0.01, 0.01, 0.01] # Lever arm variance, diagonal matrix with 0.1m standard deviation on each direction.

**Example 3: Backwards-positive pulsed speed measurement, with a config lever arm.**

.. tabs::

   .. code-tab:: c++
   
		OxTS::Gal_Cpp::GadSpeed gs(137); // Sets speed aiding data to GAD stream ID 137.
		gs.SetSpeedBwPulsedPeriod(frequency, scale_factor, period); // Set a backwards-positive pulsed speed measurement in pulses per second, with a scale factor in meters and a period in seconds.
		gs.SetSpeedBwPulsedPeriodVar(var_frequency, var_scale_factor, var_period); // Variance on pulse frequency, scale factor and period respectively
		gs.SetAidingLeverArmConfig(); // Set the lever arm to ‘config’, ie set in the configuration file.

	
   .. code-tab:: py
   
		gs = oxts_sdk.GadSpeed(137) # Sets speed aiding data to GAD stream ID 137.
		gs.speed_bw_pulsed = [frequency, scale_factor, period] # Set a backwards-positive pulsed speed measurement in pulses per second, with a scale factor in meters and a period in seconds. 
		gs.speed_pulsed_var_period = [var_frequency, var_scale_factor, var_period] # Variance on pulse frequency, scale factor and period respectively
		gs.aiding_lever_arm_config() # Set the lever arm to ‘config’, ie set in the configuration file.

Note that, in order for the config lever arm to work, you will need to add the following code to the config file of your INS:

.. code-block:: c

		-location4_0.0_0.0_0.1_0.01 // Set a lever arm with ID '4' to values 0.0m, 0.0m, 0.1m, diagonal variance 0.01m^2 for all
		-gad_loc_id137_4 // Match the aiding stream with ID '137' with lever arm ID '4'

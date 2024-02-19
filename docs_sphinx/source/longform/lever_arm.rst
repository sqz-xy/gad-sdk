.. _lever_arms:
	
Lever arms and Alignments
#########################

To be able to use aiding data from a device that is not in the frame of the 
IMU, the INS must be told the offset between its IMU frame and the frame of the 
sensor.

Offsets come in two forms: lever arms (linear displacement) and alignments 
(rotational displacement). Which of these is required depends on the data being 
provided. Most aiding types will require one or the other, some require both.
Guides for each aiding type can be found in :ref:`aidingtypes`.

The exact origin point of the IMU frame is indicated on the casing of all OxTS INS units. 
Though a well-measured lever arm (or alignment) is needed to achieve the highest accuracy 
for a system, the most important thing is that the accuracy to which the 
measurement is taken is reflected in the lever arm (or alignment) variance - an overly 
constrained lever arm (or alignment) can cause issues with the navigation solution.

Note for lever arms and aligments the covariance terms are zero.

Lever arms
**********

A lever arm is a set of measurements that describe the distance from the INS to 
your aiding device, from the perspective of the INS. It's expressed as (X, Y, Z) 
measurements in metres.
	
There are two methods to set a lever arm and its corresponding variance:

Directly via the SDK
--------------------

The lever arm and variances can be set directly via SDL with the following code:

.. tabs::

   .. code-tab:: c++
   
        SetAidingLeverArmFixed(X, Y, Z);
        SetAidingLeverArmVar(Cx, Cy, Cz);
	
   .. code-tab:: py
   
        aiding_lever_arm_fixed = [X, Y, Z] 
        aiding_lever_arm_fixed_var = [Cx, Cy, Cz]


Where `X, Y, Z` are the lever arm values in metres, and `Cx, Cy , Cz` are individual varaince values for the X, Y, Z axes respectively.

Indirectly via the config file
------------------------------

The lever arm and variances can set via config file of the INS. This requires two sets of commands.

The first set need to be placed in the SDK code:

.. tabs::

   .. code-tab:: c++
   
	    SetAidingLeverArmConfig();
	
   .. code-tab:: py
   
        set_aiding_lever_arm_config()

The second set of code needs to placed in the INS's config (.cfg) file:

.. code-block:: C

    -gad_loc_id[S]_[L]
    -location[L]_[X]_[Y]_[Z]_[C]

or

.. code-block:: C

    -gad_loc_id[S]_[L]
    -location[L]_[X]_[Y]_[Z]_[Cx]_[Cy]_[Cz]

Where [S] and [L] are the stream and lever arm IDs respectively.  [X],[Y],[Z] are the lever arm values in metres. 
[C] is a common variance for all three axes. While [Cx],[Cy],[Cz] are individual varaince values for the X, Y, Z axes respectively. 
The values for the variance are in metres squared. 

Alignment
**********

An alignment is a measure of the relative rotation between the IMU frame and 
the frame of the aiding device. These rotations are specified by three angles (:math:`{\psi}`, :math:`{\theta}`, :math:`{\phi}`)
following the Tait-Bryan ZYX convention found 
`here <https://en.wikipedia.org/wiki/Euler_angles>`_. 

Again there are two method to set an alignment and its corresponding variance:

Directly via the SDK
--------------------

The alignment and variances can be set directly via SDL with the following code:

.. tabs::

   .. code-tab:: c++
   
        SetAidingAlignmentFixed(A, B, G);
        SetAidingAlignmentVar(Ca, Cb, Cg);
	
   .. code-tab:: py
   
        aiding_alignment_fixed = [A, B, G] 
        aiding_alignment_var = [Ca, Cb, Cg]


Where `A, B, G` are the lever arm values in metres, and `Ca, Cb, Cg` are the individual varaince values for the 
:math:`{\psi}`, :math:`{\theta}`, :math:`{\phi}` rotations respectively. 


Indirectly via the config file
------------------------------

The alignment and variances can set via config file of the INS. This requires two sets of commands.

The first set need to be placed in the SDK code:

.. tabs::

   .. code-tab:: c++
   
	    SetAidingAlignmentArmConfig();
	
   .. code-tab:: py
   
        set_aiding_alignment_config()

The second set of code needs to placed in the INS's config (.cfg) file:

.. code-block:: C

    -gad_rot_id[S]_[L]
    -rotation[L]_[A]_[B]_[G]_[C]

or

.. code-block:: C

    -gad_rot_id[S]_[L]
    -rotation[L]_[A]_[B]_[G]_[Ca]_[Cb]_[Cg]

Where [S] and [L] are the stream and aligment IDs respectively.  [A],[B],[G] are the aligment rotations in degrees. 
[C] is a common variance for all three axes. While [Ca],[Cb],[Cg] are the individual varaince values for the :math:`{\psi}`, :math:`{\theta}`, :math:`{\phi}` rotations respectively. 
The values for the variance are in degrees squared. 


To see the specific code needed to set each lever arm or alignment for different aiding 
types, refer to :ref:`aidingtypes`.

The choice of where to set the lever arm/alignment is up to the user, and will have no performance impact on the system. 
However, it should be noted one can use the config file option to overwrite the level arm(s)/aligment(s) that are already in a gad packet.


Setting both linear and rotational displacements
************************************************

When measuring in an body aiding frame, i.e. one that is moving with the vehicle, both a linear and a rotation displacement are required for the GAD aiding.
An example of such a case would be a velocity update being mesured in the odometry frame.

In order to set both types of displacemets, do the following:

- Set the lever-arm (linear displacement) using one options given on this page.
- Set the attitude (rotation displacement) in the config file, using the **attitude** command:

.. code-block:: C

    -gad_att_id[S]_[L]
    -attitude[L]_[A]_[B]_[G]_[C]

or

.. code-block:: C

    -gad_att_id[S]_[L]
    -attitude[L]_[A]_[B]_[G]_[Ca]_[Cb]_[Cg]

Where [S] and [L] are the stream and attitude IDs respectively. Make sure [L] is a different value to lever arm ID. [A],[B],[G] are the aligment rotations in degrees. 
[C] is a common variance for all three axes. While [Ca],[Cb],[Cg] are the individual varaince values for the :math:`{\psi}`, :math:`{\theta}`, :math:`{\phi}` rotations respectively. 
The values for the variance are in degrees squared. 

.. note::

    **Attiude vs Rotation**

    While the attitude and rotation .cfg commands essentially contain the same information, i.e. 
    the rotational displacement between the sensor and IMU, they are not interchangable.
    Therefore it is important to know when to use each command:

    - Use the rotation command when you are REPLACING the lever arm command. E.g. with attitude or heading GAD updates.
    - Use the attitude command when you are USING the lever arem command, but need to use a rotational displacement to 
      align aiding frames. E.g. when using the odometry frame for a velocity GAD update.





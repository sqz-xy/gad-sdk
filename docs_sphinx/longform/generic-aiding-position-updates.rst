Position
********

The GA interface allows users to send a number of measurement updates to an OxTS Inertial Navigation System (INS) from external devices/ sensors, including position estimates. Position aiding can currently be accepted in a few different coordinate frames, explained in detail below. 


Aiding Frames
=============

Position aiding can be provided to the INS in more than one coordinate frame, based on the needs of the user. 

Latitude, Longitude, Altitude
-----------------------------

For this coordinate frame, data is expected in the WGS84 global coordinate frame. 

User-defined Local Frame
------------------------

Position aiding is one of the aiding types which supports a user-defined local frame. More information on how to define the frame itself can be found in the relevant document.

Position measurements in this frame are expected in metres. 

Covariance matrix
=================

All aiding provided to the INS must come with a covariance matrix. This is necessary to give the Kalman Filter some indication of confidence in the data being provided, which it can then use to inform its decision to use / reject the data.

For position aiding, the values in covariance matrices are currently expected with units :math:`m^2` . For example, a covariance matrix where position in all axes is found to be (or assumed to be) independent might look like this:

.. math::

   \begin{bmatrix}
   0.01 & 0.0  & 0.0  \\
   0.0  & 0.01 & 0.0  \\
   0.0  & 0.0  & 0.01 \\
   \end{bmatrix}
   \label{CovExampleMatrix}

This matrix shows that 

.. math:: 

   \sigma_x \sigma_x = \sigma_y \sigma_y = \sigma_z \sigma_z = 0.01 m^2

Lever Arm
=========

Position measurements must be provided with a lever arm :math:`(x,y,z)` which defines the translation from the IMU to the aiding sensor, in the IMU frame. 

References
==========

[1]: https://en.wikipedia.org/wiki/Euler_angles "Information on Tait-Bryan angles"
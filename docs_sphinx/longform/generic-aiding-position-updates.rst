.. _gadpositionpage:

Position
########

The GA interface allows users to send a number of measurement updates to an 
OxTS Inertial Navigation System (INS) from external devices / sensors, 
including position estimates. Position aiding can currently be accepted in a 
few different coordinate frames, explained in detail below. Each of the fields 
for this data type can be set using functions from the 
:ref:`gadpositionclass` class.

.. _positionaidingframes:

Aiding Frames
*************

Position aiding can be provided to the INS in more than one coordinate frame, 
based on the needs of the user. 

.. _positionaidingframeslla:

Latitude, Longitude, Altitude
=============================

For this coordinate frame, data is expected in the WGS84 global coordinate 
frame. 

.. _positionaidingframeslocal:

User-defined Local Frame
========================

Position aiding is one of the aiding types which supports a user-defined local 
frame. More information on how to define the frame itself can be found here: 
:ref:`definingalocalreferenceframe`.

Position measurements in this frame are expected in metres. 

.. _positioncovariancematrix:

Covariance matrix
*****************

All aiding provided to the INS must come with a covariance matrix. This is 
necessary to give the Kalman Filter some indication of confidence in the data 
being provided, which it can then use to inform its decision to use / 
reject the data. More information on covariance matrices can be found at 
:ref:`estimatingerrors`

For position aiding, the values in covariance matrices are  expected with units 
:math:`m^2` . For example, a covariance matrix where position in all axes is 
found to be (or assumed to be) independent might look like this:

.. _positioncovariancematrix:

.. math::

   \begin{bmatrix}
   0.01 & 0.0  & 0.0  \\
   0.0  & 0.01 & 0.0  \\
   0.0  & 0.0  & 0.01 \\
   \end{bmatrix}


This matrix shows that 

.. math:: 

   \sigma_x \sigma_x = \sigma_y \sigma_y = \sigma_z \sigma_z = 0.01 m^2

.. _positionlva:

Lever Arm
*********

Position measurements must be provided with a lever arm :math:`(x,y,z)` which 
defines the translation from the IMU to the aiding sensor, in the IMU frame. 

.. _positionlvafixed:

Fixed
=====

A fixed lever-arm is the simplest to set up, since it requires no external 
configuration. It is set within the Generic Aiding packet itself, using the 
function: ... 

.. _positionlvaconfig:

Config
======

A Config lever-arm is functionally equivalent to a Fixed lever-arm. The 
difference is that the lever-arm is set in the configuration of the INS instead 
of within the data packet itself. 

.. _positionlvaoptimising:

Optimising
==========

An Optimising lever-arm differs slightly from the other two types of lever-arm. 

- The lever-arm will be taken from the .gap file on the INS (accuracy set in 
  .gpa file). This can be set using NAVconfig in the Primary GNSS Antenna 
  configuration.
- The lever-arm will be optimised by the Kalman Filter during operation, 
  increasing its accuracy and therefore improving the quality of data provided 
  to the system.

.. warning::
   If an optimising lever-arm is used for a Generic Aiding source alongside a 
   GNSS Antenna, it will create a conflict in the optimisation of the 
   lever-arm. This can be avoided by reassigning the dual antenna lever-arm. 
   See :ref:`reassigningtraditionaldatasources` for more details.



References
**********

[1]: https://en.wikipedia.org/wiki/Euler_angles "Information on Tait-Bryan angles"
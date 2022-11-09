.. _gadpositionpage:

Position
########

The generic aiding data (GAD) interface allows users to send a number of measurement updates to an 
OxTS Inertial Navigation System (INS) from external devices / sensors, 
including position estimates. Position aiding can currently be accepted in a 
few different coordinate frames, explained in detail below. Each of the fields 
for this data type can be set using functions from the 
:ref:`gadpositionclass` class.

.. _positionaidingframes:

Aiding frames
*************

Position aiding can be provided to the INS in more than one coordinate frame, 
based on the needs of the user. 

.. _positionaidingframeslla:

Latitude, longitude, altitude
=============================

For this coordinate frame, data is expected in the WGS84 global coordinate 
frame. 

.. _positionaidingframeslocal:

User-defined local frame
========================

Position aiding is one of the aiding types which supports a user-defined local 
frame. More information on how to define the frame itself can be found here: 
:ref:`definingalocalreferenceframe`.

Position measurements in this frame are expected in metres. 

.. _positioncovariancematrix:


Converting between frames
*************

Euler angles are used to output the heading, pitch and roll, and these have singularities at two orientations. The RT has rules to avoid problems when operating close to the singularities; if you regenerate the rotation matrices given below then they will be correct.


The Euler angles output are three consecutive rotations (first heading, then pitch and finally roll) that transform a vector measured in the navigation co-ordinate frame to the body co-ordinate frame. The navigation co-ordinate frame is the orientation on the earth at your current location with axes of north, east and down.


If :math:`V_n` is vector :math:`V` measured in the navigation co-ordinate frame and :math:`V_b` is the same vector measured in the body co-ordinate frame the two vectors are related by:

.. math::

   V_n = C_bn V_b

.. math::

   V_n = 
   \begin{bmatrix}
   cos(Ψ) & -sin(Ψ)  & 0  \\
   sin(Ψ)  & cos(Ψ) & 0  \\
   0  & 0  & 1 \\
   \end{bmatrix}\begin{bmatrix}
   cos(θ) & 0 & sin(θ) \\
   0  & 1 & 0  \\
   -sin(θ) & 0 & cos(θ) \\
   \end{bmatrix}\begin{bmatrix}
   1 & 0 & 0 \\
   0  & cos(ϕ) & -sin(ϕ)  \\
   0 & sin(ϕ) & cos(ϕ) \\
   \end{bmatrix} V_b

where:

Ψ is the heading angle;

θ is the pitch angle and 

ϕ is the roll angle.


Covariance matrix
*****************

All aiding provided to the INS must come with a covariance matrix. This is 
necessary to give the Kalman Filter some indication of confidence in the data 
being provided, which it can then use to inform its decision to use / 
reject the data. 

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

Lever arm
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


Optimising (advanced-level information for internal users)
==========

An optimising lever-arm differs slightly from the other two types of lever-arm. 

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

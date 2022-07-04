.. _gadheadingpage:

Heading
########

Updates using heading measurements only. Each of the fields for this data 
type can be set using functions from the :ref:`gadheadingclass` class.

.. _headingaidingframes:

Aiding Frames
*************

Currently, heading aiding can only be provided in the navigation frame. 

.. _headingaidingframesnavigation:

Navigation frame
================

This is the standard frame for supplying heading updates and moves inline with the vehicle

.. _headingaidingframeslocal:

User-defined Local Frame
========================

Heading aiding suports a user-definied local frame.  More information on how to define the frame 
can be found here: 
:ref:`definingalocalreferenceframe`.

Heading measurements in this frame are expected in degrees.

.. _headingvariance:

Heading Variance
*****************

The heading variance provides an estimate of the error on the measurements 
being provided to the INS. 

.. _headingalignment:

Alignment
*********

Simimilarly to attitude measurements, heading measurements have an 
associated alignment, as opposed to a lever-arm. This is because the linear 
offset between the attitude sensor and the IMU does not affect the 
measurements, it is only the angular offset between the two which must be 
accounted for. 

.. _headingfixedlva:

Fixed
=====

A fixed heading allignment is set within the Generic Aiding packet itself, 
using: SetAidingAllignmentFixed. 

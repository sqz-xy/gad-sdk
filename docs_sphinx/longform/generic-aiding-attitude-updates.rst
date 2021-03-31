.. _gadattitudepage:

Attitude
########

Attitude (otherwise known as orientation). Each of the fields for this data 
type can be set using functions from the :ref:`gadattitudeclass` class.

.. _attitudeaidingframes:

Aiding Frames
*************

Currently, attitude aiding can only be provided in the vehicle frame. 

.. _attitudeaidingframesvehicle:

Vehicle frame
=============

This frame matches the one seen in NAVconfig when setting the IMU-vehicle 
alignment (.vat file). Units are degrees.

.. _attitudecovariancematrix:

Covariance Matrix
*****************

The covariance matrix provides an estimate of the error on the measurements 
being provided to the INS. Below we show an example for attitude:

.. math::

    \begin{bmatrix}
    0.01 & 0.0  & 0.0  \\
    0.0  & 0.01 & 0.0  \\
    0.0  & 0.0  & 0.01 \\
    \end{bmatrix}


This matrix is formed from the covariances: 

.. math:: 

   \sigma_h \sigma_h = \sigma_p \sigma_p = \sigma_r \sigma_r = 0.01^{\circ^2}

Which implies a standard deviation of :math:`0.1^{\circ}` on each measurement, 
and that each measurement is independent (two independent measurements have 
covariance of 0).

.. _attitudealignment:

Alignment
*********

Attitude measurements differ from other update types in that they have an 
associated alignment, as opposed to a lever-arm. This is because the linear 
offset between the attitude sensor and the IMU does not affect the 
measurements, it is only the angular offset between the two which must be 
accounted for. 

.. _attitudefixedlva:

Fixed
=====

A fixed alignment is the simplest to set up, since it requires no external 
configuration. It is set within the Generic Aiding packet itself, using the 
function: ... 

.. _attitudeconfiglva:

Config
======

A Config alignment is functionally equivalent to a Fixed alignment. The 
difference is that the alignment is set in the configuration of the INS instead 
of within the data packet itself. 

.. _attitudeoptimisinglva:

Optimising
==========

An Optimising alignment differs slightly from the other two types of alignment. 

- The alignment will be taken from the .att file on the INS (accuracy set in 
  .ata file). This can be set using NAVconfig in the Dual Antenna configuration.
- The alignment will be optimised by the Kalman Filter during operation, 
  increasing its accuracy and therefore improving the quality of data provided 
  to the system.

.. warning::
    If an optimising alignment is used alongside GNSS Dual Antenna, it will 
    create a conflict in the optimisation of the alignment. This can be avoided 
    by reassigning the dual antenna alignment. See 
    :ref:`reassigningtraditionaldatasources` for more details.

Calculating alignment HPR angles
********************************

TBC
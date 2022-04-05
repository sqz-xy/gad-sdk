.. _gadspeedpage:

Speed
#####

Speed / Wheelspeed Updates. This update type allows for a 1D speed measurement 
to be provided to the INS as aiding. Each of the fields for this data 
type can be set using functions from the :ref:`gadspeedclass` class.

.. warning::
    When using Generic Aiding wheelspeed, it is necessary to disable an 
    internal mechanism in order to avoid interference. Use config option 
    :code:`-aid_wspeed_off` to do this.

.. warning::
    If zero velocity is sent then the update type will internally be changed to a "zero velocity update".
    Therefore to check the INS is receiving the update the zero velocity innovations should be inspected.

Aiding Frames
*************

Wheelspeed does not have different aiding frames in the same way as other 
updates. It does however have the option to provide speed or wheelspeed.

Wheelspeed
==========

OxTS has been using wheelspeed encoders as aiding sources for a number of 
years. They are a very simple and highly effective form of aiding.

Wheelspeed encoders must be placed on a non-steered, non-driven axis for best 
performance. If either of these conditions are not met, it can reduce the 
accuracy of the data provided to the system. This can result in the data being 
rejected or in some cases degrading the performance of the overall system.

Generic Aiding wheelspeed expects two values: 

- **Pulses** (A.K.A count) The number of pulses recorded in a given period.
- **Period** The time window in which the number of pulses was recorded.

These two values alone cannot provide a full speed measurement. The additional 
piece of information required is the Pulses Per Metre (PPM), which is set in 
the configuration of the INS. 

`-wheelspeed[X]_[Y]`  
    [X] = PPM (unitless), [Y] = % accuracy of the PPM value.

The INS will attempt to optimise the PPM value during operation. The accuracy 
set here will determine how much this value is allowed to deviate from its 
initial value in search of the optimum.


Speed (beta)
============

This is a 1-Dimensional speed measurement in the forward direction of the 
vehicle frame. 

This update is still in development and is currently a special case of the 
wheelspeed measurement. As a consequence, it is still a little rough around the 
edges. When using this update type, users must configure 
:code:`-wheelspeed1000_10` on the INS, despite the fact that this is not 
"wheel"speed. 

.. _speedcovariancematrix:

Covariance Matrix
*****************

Since speed is a 1-dimensional measurement, the covariance matrix for speed 
updates is actually a scalar value. Expected units are :math:`pulses^2`

Lever Arm
*********

The lever arm for speed updates should always be set to Optimising. To 
configure the lever-arm (and PPM), users should navigate to the wheelspeed tab 
of NAVconfig. Alternatively, this can be done in the mobile.wsp file (and 
mobile.wsa for accuracies).
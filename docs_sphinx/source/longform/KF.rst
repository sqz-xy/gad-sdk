.. _KF:

The Kalman Filter
*****************

You may often see references to the Kalman Filter (KF) in OxTS or general INS documentation. A Kalman Filter is an algorithm that is used to estimate a set of variables or “states” based on a series of measurements over time. Essentially, it combines data from the IMUs and aiding devices into accurate navigation data. 

Kalman filters can also be used to estimate variables which have not been measured, using ones that have been measured. In fact, the INS does this a lot – for example, estimating gyro and accelerometer biases and scale factors which we have no way of directly measuring.

The OxTS navigation engine will create a prediction of its internal state based on previous information it has been provided. When it received an aiding update - be it from the internal GNSS receiver or from an external GAD source - it will compare the measurement to its predicted state. As it does this, it will take into account the estimated covariance for the measurement and its own internal predicted state, which will inform the weight given to the measurement. If a measurement differs too greatly from the internal state of the KF, it will be rejected as an anomalous update. 

.. _KFdelay:

The Kalman Filter delay
-----------------------

By default, the generic aiding updates need to arrive within 0.5 seconds of their epoch of creation. 
Updates that arrive later than that will be discarded as too old to be relevant. You’ll have to run tests to ensure that your data arrives fast enough; if it doesn’t, then you can either:

•	Try to reduce network traffic to improve latency
•	Invest in more powerful hardware to speed up processing time

While inadvisable (see warning below), the Kalman filter’s delay can be adjusted by adding the following line to the advanced options in NAVconfig:

.. code-block:: c

	-bns_delay[X]

Where [X] is the Kalman filter delay in seconds. 

.. warning::

	OxTS does not test KF delays longer than 1.0 seconds, as they tend to have an adverse effect on the accuracy of your Kalman Filter’s calculations (essentially, the longer the delay, the further into the future the Kalman Filter has to calculate in order to compensate, decreasing its accuracy). 


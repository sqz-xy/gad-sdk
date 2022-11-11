.. _Sensorcharacterisation:

Sensor characterisation
##########

Estimating errors
==========

One of the most important aspects of providing any aiding data to the INS is error estimation. When performing sensor fusion, it is necessary for the system to have some idea of the confidence in the data it is using. This allows the system to give weight to aiding sources with higher confidence, which in turn produces a better (more accurate) navigation data.

The error which should be estimated and provided to the system is the **measurement error**.

Data rates
========

A key question when providing aiding to any sensor fusion algorithm is: what 
data rate will produce the best results?

Generally speaking, the ideal rate for an OxTS INS to receive data from an 
aiding source will lie in the range of 1-10Hz. GNSS receivers like those found 
in OxTS devices typically output in this range, and they are excellent sources 
of aiding.

Stream Id
========

The generic aiding interface supports multiple sensors and it is useful to be able to see the effect each sensor has on the navigation solution. To track each update an identification number should be associated with each sensor. This identification number is known as the “GAD packet stream Id”, or simply “stream Id”. Together with the time, it allows users to identify each individual sensor’s update.

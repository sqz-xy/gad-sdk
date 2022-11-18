.. _estimatingerrors:

Estimating errors
#################

One of the most important aspects of providing any aiding data to the INS is error 
estimation. When performing sensor fusion, it is necessary for the system to 
have some idea of the confidence in the data it is using. This allows the 
system to give weight to aiding sources with higher confidence, which in turn 
produces a better (more accurate) navigation data. 

The error which should be estimated and provided to the system is the 
**measurement error**. 
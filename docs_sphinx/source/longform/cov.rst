.. _cov:

Covariance
**********
All aiding data provided to the INS must come with a (co)variance estimate. This gives the Kalman Filter some indication of the estimated accuracy of the data being provided, which it can then use to decide whether to use the data, and if so, how strongly the data should be weighted.

The information contained within a covariance matrix can be separated into two parts. 

First, the diagonal matrix elements give estimations of the accuracy along each axis. This is known as the variance. 

Second, the off-diagonal matrix elements give estimations of any correlations in the accuracies between the different axes. This is known as the covariance.
It’s quite rare for the accuracy of one axis to influence another, but it can happen.

For the most part, however, we can assume that the errors for X, Y and Z are independent of each other. Assuming also that these values are the same, the very simplest covariance matrix might look like this:

	.. math::
	
		\begin{bmatrix}
		0.01 & 0.0 & 0.0\\
		0.0 & 0.01 & 0.0\\
		0.0 & 0.0 & 0.01\\
		\end{bmatrix}
		\label{CovMatrix}
		
	
In this example, we have set our variance (:math:`{\sigma}`\ :sup:`2`) in each axis to be `0.01 m` \ :sup:`2`. This implies a standard deviation (:math:`{\sigma}`) of 0.1 `m`.

I.e.

			:math:`\sigma_{x}\sigma_{x} = \sigma_{y}\sigma_{y} = \sigma_{z}\sigma_{z} = 0.01 m^{2}`
	

For other aiding types, the units differ:

•	Velocity is expected in (m/s)\ :sup:`2` — not to be confused with acceleration (m/s\ :sup:`2`).

•	Attitude is expected in :math:`{\circ}`\ :sup:`2` .

•	There are two variance options for the speed update. Refer to the :ref:`Speed aiding data type <spe_aidingtype>` section for more information.

In the example above, we have a single value of covariance for all three axes, which we can use to set the covariance aiding position in the coordinate frame as follows:

.. tabs::

   .. code-tab:: c++

	gp.SetPosLocalVar(0.01, 0.01, 0.01); // Diagonal variance matrix, standard deviation 0.1m, 0.1m, 0.1m in x, y, z

   .. code-tab:: py
		
	gp.pos_local_var = [0.01, 0.01, 0.01] # Diagonal variance matrix, standard deviation 0.1m, 0.1m, 0.1m in x, y, z


If the variances for X, Y and Z were different, we would need to enter three different values. 
In the example below, we have an estimated standard deviation of 0.1 in the X axis, 0.3 in the Y axis, and 0.2 in the Z axis:


	.. math::
	
		\begin{bmatrix}
		0.01 & 0.0 & 0.0\\
		0.0 & 0.09 & 0.0\\
		0.0 & 0.0 & 0.04\\
		\end{bmatrix}
		\label{CovMatrix2}
		
In the code, you could represent that as:

.. tabs::

   .. code-tab:: c++

	gp.SetPosLocalVar(0.01, 0.09, 0.04);

   .. code-tab:: py
		
	gp.pos_local_var = [0.01, 0.09, 0.04]
	

Remember earlier when we said that sometimes your variables in one axis can affect your variables in another axis? In a scenario where we have covariance between the X, Y and Z axes, our matrix might end up with six different values. 
The reason we don’t have nine is that the matrix produces three identical pairs of values:

	.. math::
	
		\begin{bmatrix}
		0.01 & 0.25 & 0.02\\
		0.25 & 0.09 & 0.25\\
		0.02 & 0.25 & 0.04\\
		\end{bmatrix}
		\label{CovMatrix3}
		
So you can see, for instance, that :math:`\sigma_{x}\sigma_{y}` would produce the same answer as :math:`\sigma_{y}\sigma_{x}` .

In the code, you could represent this covariance matrix as: 

.. tabs::

   .. code-tab:: c++

	gv.SetVelOdomVar(0.01, 0.09, 0.04, 0.25, 0.02, 0.25); // Full covariance matrix, in (m/s)^2

   .. code-tab:: py
		
	gv.vel_odom_var = [0.01, 0.09, 0.04, 0.25, 0.02, 0.25] # Full covariance matrix, in (m/s)^2


The order of variables in the command above is the variance in X, Y, then Z, followed by the covariance of XY, then XZ, and finally YZ.

Where do I find covariance figures for my aiding sensor?
--------------------------------------------------------

The first place to start is the documentation that comes with the sensor. Often, it will include covariance data, 
or information on how it can be extracted.

Since the quality of measurement from a sensor can vary significantly from one measurement to the next,  
the best scenario is one where the sensor's software calculates the covariance for each measurement.
Consult your sensor's documentation to see if this information is outputted.

Even if covariances are not directly provided by the sensor, a measurement with even basic variance estimations can often be used as an effective aiding update. 
A good starting point for this would be to calculate the variance when the sensor is stationary. For example, with a sensor that measures velocity, 
one could record the velocity output over a period of time. It can be assumed that the mean value of the velocity is zero in X, Y and Z. Thus, the variances along
X, Y and Z can be calculated using the standard formula:

	.. math::

		\sigma^2 = \frac{\sum (x_i - \bar{x})^2}{n-1}

Where :math:`x_{i}` is the value of one measurement, :math:`\bar{x}` is the mean value of all measurements (in the case of velocity this will be zero), 
and :math:`n` is the number of observations.

While it is unlikely that the variance will be the same when the sensor is moving, the estimate provided by this method can still be surprisingly useful.
To further improve the variance, one can scale the variances based on the corresponding innovations when the sensor and INS are moving. 
For more information on the innovations provided by the OxTS INS, see :ref:`here <Data_used>`.

A more complete method for calculating the variance would be to take a set of test measurements in an environment with good GNSS coverage.
Thus, the GNSS and INS data could then be used to produce an NCOM file that acts as a reference measurement.
One can then compare this reference NCOM to the GAD data produced by the sensor.


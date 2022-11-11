Introduction
############

OxTS Inertial Navigation Systems (INS) have historically used inertial 
measurement units (IMU) as the basis of their navigation, and combined this 
with data from GNSS receivers. 

IMUs alone are incredibly useful, since they can provide data at much 
higher rates than many other sensors (>100 Hz). The drawback is that they have 
limited means of providing an absolute position relative to any global system 
beyond the pose at the time they were powered on. Additionally, measurements of
acceleration and angular rate must be integrated to produce velocity and 
position data, meaning they accumulate errors over time and consequently are 
prone to drift. Using inertial sensors in this way is often referred to as 
"dead reckoning".

In contrast, GNSS receivers alone have much lower update rates, often in the 
region of 1-10 Hz. However, they are capable of providing position in a global 
reference system up to ~2 cm RMS in open sky conditions (with assistance from 
Ground Based Augmentation Services (GBAS)). Since these are measurements of 
position in a global frame, they are not prone to drift.

Bringing these two types of sensor together in one device using sensor fusion 
makes for an excellent combination. The resulting navigation solution benefits 
from the high update rate of inertial sensors whilst being able to correct 
errors which would accumulate over time by "aiding" the system with data from 
the receivers.

However, GNSS is far from the only aiding source available. As technology 
improves, an ever-increasing number of sensors are capable of producing 
measurement data which can be used to improve navigation solutions. These 
include, but are not limited to: 

- LiDAR
- Cameras
- Ultra-wideband (UWB)
- RADAR

This is where the Generic Aiding Interface comes in. This interface has been 
designed to accept multiple forms of aiding data and pass them to the INS to 
be used in the navigation solution. As long as the data is in this format, the 
sensor used to obtain it is irrelevant to the system. The types of aiding data 
which can be provided to the system are:

- :ref:`gadpositionpage`
- :ref:`gadvelocitypage`
- :ref:`gadattitudepage`
- :ref:`gadspeedpage`


Reasons to use Generic Aiding
*****************************

There are a number of different reasons why Generic Aiding might be effective 
for your application. 


Combining users' data
=====================

No one technology provides reliable pose (position and orientation) estimation in all conditions. It makes sense to combine technologies and gain the advantage that each one has. The problems of combining several sensors include getting a common measurement time and common co-ordinate frame, weighing different measurements when combining them and arbitrating between conflicting measurements.

Inertial navigation is ideal as the central “core” where other sensors with different measurement times, different accuracies and different measurement frames can be fused to give improved results. Inertial measurements are always available. They have a high, regular, update rate with low latency (delay). Their error model is very well known and deterministic. They provide robust solutions by rejecting unreliable measurements from other sensors. Through sensor fusion they can deliver a full pose (position and orientation) even if the additional sensors only provide a partial pose. Perhaps the most important point is that they provide an excellent statistical framework for combining other sensors.

Other sensors are added to inertial navigation to overcome its deficiencies, mostly long-term error growth. Sensors that measure position mitigate long term drift best, though velocity and orientation sensors can also help.

OxTS has more than 20 years’ experience in combining inertial measurements with other sensors. Primarily we used GNSS but have experience with road vehicle models, wheel speed, Ultra-wide band (UWB) positioning, timing strips, cameras and compasses. We are opening our sensor fusion framework (GAD) to users who want to combine sensors that are suitable for their applications.


Increasing robustness in challenging environments
=================================================

Sensor fusion is a popular technique because a solution created from multiple 
data sources is often more accurate and more robust in challenging environments 
than a solution from any individual sensor.

One of the simplest examples of an additional aiding source is a wheelspeed 
encoder. OxTS has been using these devices for years to improve navigation in 
more challenging GNSS environments.

Generic Aiding opens the door to a large array of alternative sensors which can 
provide measurement data to the INS and help it to maintain its performance in 
a wider array of environments and applications.


Indoor / GNSS denied
====================

In GNSS-denied environments, such as multi-storey car parks and enclosed test centres, OxTS' Poyzx 2GAD (ie. to Generic Aiding) solution enables Pozyx Ultra-wideband (UWB) to aid your INS.


Next steps
**********

- :ref:`genericaidingrequirements`
- :ref:`estimatingerrors`



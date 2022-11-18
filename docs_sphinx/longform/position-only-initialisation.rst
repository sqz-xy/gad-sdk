.. _positiononlyinitialisation:

Position Only Initialisation
############################

Whilst the system is perfectly capable of operating with just position information
from GAD, initialisation of the unit requires information for velocity and
heading.
In lieu of providing an estimate of velocity and heading in the case of only
having position information from GAD, two options can be used to dynamically
initialise the unit.

Velocity
========

-gad_init_vel_from_pos_[X]
    [X] = on/off

This command allows the system to create its own estimate of velocity from a GAD
position stream, meaning the system can initialise.
For initialisation to occur, the velocity in a straight line must exceed the
'motion speed' option (default 5m/s) for a few seconds.
This may be changed using the below command, although reducing this speed is
not recommended.

-motion_speed[X]
    [X] = Speed for dynamic initialisation, in m/s (default 5.0)

It is important to note that the position updates (from a single stream) must
be more regular than 1Hz for velocity to be calculated.
More than 5Hz is highly recommended.
Furthermore, if there are any available velocity streams, the system will use
these for initialisation, rather than the position streams, regardless of this
option being set.

Heading (coming soon)
=====================

-gad_init_hea_from_pos_[X]
    [X] = on/off

If the velocity initialisation is being performed from position data, this
option can also be set to allow the heading to be dynamically initialised from
this velocity.
As with the velocity from position aiding, if an actual heading stream is
available, the system will use that for initialisation, assuming it reaches the
usual thresholds for variance level.

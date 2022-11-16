.. _positiononlyinitialisation:


Initialisation
##############

To successfully use GAD updates, the INS must be initalised. To initalise requires time, position, velocity and orientation.

Position-only initialisation
############################

It is possible to operate the system using just position information from GAD.  
In lieu of providing an estimate of velocity and heading in the case of only
having position information from GAD, two options can be used to dynamically
initialise the unit.
Time must be provided separately whether via command or input by the system. Care should be taken to make sure that time is consistent across all devices.

Velocity
========

-gad_init_vel_from_pos_[X]
    [X] = on/off


-motion_speed[X]
    [X] = Speed for dynamic initialisation, in m/s (default 5.0)


Heading (coming soon)
=====================

-gad_init_hea_from_pos_[X]
    [X] = on/off


For more information on using these commands, see :ref'advancedcommands'.

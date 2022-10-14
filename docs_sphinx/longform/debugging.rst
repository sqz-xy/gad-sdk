.. _debugging:

Debugging
#########

When trying to integrate an aiding source to an INS,

Two key questions when sending data to an INS are: 

- Is my data being received?
- Is my data being used?

Is my data being received?
==========================

This can be checked using status messages output in NCOM. NCOM contains 
measurements for GAD characters received, packets received, and characters
skipped.

Naturally, GAD is being received by the unit, the characters received will
increment accordingly. If these characters are successfully decoded to full 
packets, this will lead to a corresponding increment in the packets received.
If packets are corrupt, the characters skipped measurement will be incremented 
accordingly. 

If none of these measurements are increasing, this suggests that the data is 
not reaching the navigation firmware. One of the most common causes of this 
is networking issues, so it can be worth checking IP addresses and other parts 
of a device's networking configuration.


Is my data being used?
======================

Since the INS is selective about which data it trusts to use in updates, it is 
entirely possible for GAD to be rejected by the system either because it is 
deemed inaccurate or inferior to another source of aiding (think providing SPS 
quality position when RTK position is available from another source). In this 
case, there is currently limited real time feedback from the INS to determine 
whether the data has been received. 

The first measurements to check are the innovations. These can be plotted in a 
histogram in NAVdisplay, which can provide feedback on how generic aiding 
measurements compare to the INS predictions of its states. Large innovations 
are an indicator of disagreement between predictions and measurements, which 
suggests that there is an issue with one of the two.

If there are no innovations present in the histogram, this can suggest that 
GAD is not making it to the navigation engine. This can happen when the data 
does not pass a series of checks in the data pipeline to the navigation engine.
This can be checked using the configuration option :code:`-gad_debug_streamX`. 
The option enables an additional piece of debug information for a specified 
stream ID. This debug information provides an error code (interpreted by 
NAVdisplay) which can be used to narrow down the reason for the rejection of 
the aiding.

If the system is receiving and accepting the aiding data, this will be 
reflected in the aiding mode of the relevant aiding type for position, 
velocity, or heading which will move to :code:`Gen Aid (34)`. The reported 
accuracies for these measurements should also reflect those provided by the 
aiding source. 

There are cases when the aiding mode will move to :code:`Gen Aid (34)` but the 
system is not using the Generic Aiding data. This can be identified by the 
reported accuracies not reflecting the accuracies of the aiding data.

GAD packets are logged in the RD file like all other data, provided they are 
not corrupt. This data can be extracted from the RD file to CSV in 
post-process, which can be a useful tool for debugging issues with the data. To 
find out more, see :ref:`extractinggadfiles`.

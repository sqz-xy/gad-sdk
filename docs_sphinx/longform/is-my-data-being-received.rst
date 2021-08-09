.. _ismydatabeingreceived:

Is my data being received?
##########################

When trying to integrate an aiding source to an INS,

Two key questions when sending data to an INS are: 

- Is my data being received?
- Is my data being used?

Since the INS is selective about which data it trusts to use in updates, it is 
entirely possible for GAD to be rejected by the system either because it is 
deemed inaccurate or inferior to another source of aiding (think providing SPS 
quality position when RTK position is available from another source). In this 
case, there is currently limited real time feedback from the INS to determine 
whether the data has been received. 

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

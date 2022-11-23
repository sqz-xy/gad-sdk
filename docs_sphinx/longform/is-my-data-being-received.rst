.. _ismydatabeingreceived:

Is my data being received?
##########################

When trying to integrate an aiding source to an INS, two key questions when sending data to an INS are: 

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
velocity, or heading. 

NAVdisplay can be used to view the aiding modes of the relevant aiding type. This can be done by simply adding a digital widget and selecting the appropriate aiding mode you wish to view.  

Outside of NAVdisplay, this information can be found within the NCOM stream, which is the default real-time output format for OxTS INS devices. Information on NCOM can be found here: https://www.oxts.com/wp-content/uploads/2022/09/OxTS-NCOM-Manual.pdf

The associated mode will change to :code:`Gen Aid (34)`. The reported 
accuracies for these measurements should also reflect those provided by the 
aiding source. 

There are cases when the aiding mode will change to :code:`Gen Aid (34)` but the 
system is not using the Generic Aiding data. This is due to only one mode being processed at a time. When GAD is input into the system, this mode will supercede all others. This can be identified by the reported accuracies not reflecting the accuracies of the aiding data.

GAD packets are logged in the RD file like all other data, provided they are 
not corrupt. This data can be extracted from the RD file to CSV in 
post-process, which can be a useful tool for debugging issues with the data. To 
find out more, see :ref:`extractinggadfiles`.

Innovations are available for each aiding stream. For more information, see :ref:`ncomupdates`.



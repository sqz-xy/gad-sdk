.. _reassigningtraditionaldatasources:

Reassigning Traditional Data Sources
####################################

There can only be one Optimising lever-arm and one Optimising Alignment 
configured on an INS at any one time. Traditionally, this has always been the 
lever-arm to the primary GNSS antenna and the angular offset between the 
primary and secondary antennae. When using Generic Aiding, it may be desirable 
to change this formula, and instead optimise a lever-arm or alignment from 
another aiding source.

.. note::
    Setting the traditional data sources to fixed lever-arms will limit the 
    quality of aiding they are able to provide, unless the lever-arms are known 
    to a high accuracy.

Creating the configuration
**************************

The first step is to create a replacement lever-arm for the traditional aiding 
source to make use of. This can be done with the following configuration 
option:

-location[A]_[B]_[C]_[D]_[X]_[Y]_[Z]  
    Create loc ID [A] for Lever Arm ([B],[C],[D]), with variance ([X],[Y],[Z])

Then, either:

-aid_gpsint1_loc_id[X]  
    Associate Leverarm ID [X] to primary GPS antenna

for the primary antenna location, or:

-aid_gpsatt_loc_id[X]  
    Associate a heading angular offset ID [X] to the primary GPS antenna

for the dual antenna alignment.
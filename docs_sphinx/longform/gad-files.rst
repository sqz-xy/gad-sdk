.. _gadfiles:

.gad files
##########

These files contain Generic Aiding data packets in CSV format (UTF-8 encoding). 
They can be exported from blended as a debug tool, or created from other data 
and used in post-processing. These files are often the simplest way to test how 
aiding data from a particular source might be able to improve the navigation 
solution of the INS.

.. _extractinggadfiles:

Extracting .gad files
*********************

If Generic Aiding Data (GAD) is sent to an OxTS INS in real-time, the unit will 
log this data in the RD file like any data on the INS. Blended.exe can be used 
to extract this data from the RD file and place it into a CSV formatted file.

There are two main purposes for this:

- To check the data is good
- To edit the data and then feed the edited data back to the system in post-
  process. This can be useful to experiment with certain values or fix values 
  which were set incorrectly in real-time.

.. csv-table:: .gad file extraction options from blended
   :file: assets/gad-file-blended-options.csv
   :widths: 30, 30, 50 
   :header-rows: 1


.. _generatinggadfiles:

Generating .gad files
*********************

As well as extracting the CSV files from blended, they can also be created from 
other data using this SDK. This is demonstrated in the 
:ref:`staticaidingexample` example, which can create Generic Aiding packets and 
then send them either to an INS in real time or save the packets to CSV file. 

.. _gadfileformat:

File format
***********

The .gad CSV file is undeniably large. Since this is primarily a debugging / 
experimentation tool, it has been designed for human readability more than 
efficiency. Most users will find it easier to generate theses files using the 
CSV encoding functionality in the SDK, though they can be created manually.

.. csv-table:: CSV File Format
   :file: assets/gad-file-format.csv
   :widths: 30, 30, 30, 100 
   :header-rows: 1


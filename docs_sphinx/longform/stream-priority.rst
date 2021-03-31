.. _streampriority:

Stream Priority
###############

Typically, the INS will decide which data to use based on the estimated error 
on each measurement (:ref:`estimatingerrors`). However, in some use cases it 
can be useful to be able to set priority of relative streams. This can be done 
with a single advanced command:

-stream_priority_[X]_[Y]_[Z]
    [X] = high priority stream ID, [Y] = low priority stream ID, [Z] = period 
    (s) after using data from stream [X] to block stream [Y].

It is possible to use this option on the internal GNSS streams, using the 
following stream IDs:

.. csv-table:: Internal streams
    :header: "Data type", "Stream ID"
    :widths: 20, 20

    "GNSS Position", "1"
    "GNSS Velocity", "2"
    "GNSS Attitude", "3"


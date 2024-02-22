import sys
import time
import oxts_sdk
from enum import Enum

class OUTPUT_TYPE(Enum):
        UDP = 0
        CSV = 1

if __name__ == "__main__":
        # defaults
        num_packets = 30 # Total number of packets to send
        unit_ip = "192.168.25.22" # Unit to send GAD to, change to IP address of your unit
        file_out = "out.gad"      # File to send GAD to
        output_type = OUTPUT_TYPE.UDP   # Set output to UDP
        if len(sys.argv) > 1:
                unit_ip = sys.argv[1]
        if len(sys.argv) > 2:
                num_packets = sys.argv[2]
        if len(sys.argv) > 3:
                if sys.argv[3].lower()== 'csv':
                        output_type = OUTPUT_TYPE.CSV
        if len(sys.argv) > 4:
                file_out = sys.argv[4]

        #============================================================================
        # Construct the position aiding class with stream ID 129.
        gp = oxts_sdk.GadVPosition(129)
        # Set the aiding position
        gp.pos_geodetic = [51.91520330,-1.24479140,111.525] #Change these lat, long, alti values to your location
        # Set the estimated variance on this position
        gp.pos_geodetic_var =[ 1.0,1.0,1.0]
        # Set the time mode to Void, since we are not timestamping the aiding data.
        # With no timestamp, the INS will timestamp the data upon arrival.
        gp.set_time_void()
        # Set the lever arm between the aiding source and the IMU, in the IMU frame.
        gp.aiding_lever_arm_fixed = [0.5,0.5,1.0]
        gp.aiding_lever_arm_var = [0.1,0.1,0.1]
        #============================================================================
        # Construct the velocity aiding class with stream ID 130.
        gv = oxts_sdk.GadVelocity(129)  # Set the aiding velocity
        gv.vel_ned = [0.0,0.0,0.0]
        # Set the estimated variance on this velocity
        gv.vel_ned_var = [0.1,0.1,0.1]
        # Set the time mode to Void, since we are not timestamping the aiding data.
        gv.set_time_void()
        # Set the lever arm between the aiding source and the IMU, in the IMU frame.
        # In this example, the velocity is coming from the same source as the
        # position.
        gv.aiding_lever_arm_fixed = [0.5,0.5,1.0]
        gv.aiding_lever_arm_var = [0.5,0.5,1.0]
        #============================================================================
        # Construct the attitude aiding class with stream ID 131.
        ga= oxts_sdk.GadAttitude(131)
        # Set the aiding attitude
        ga.att = [0.0,0.0,0.0]
        # Set the estimated variance on this attitude
        ga.att_var = [0.1,0.1,0.1]
        # Set the time mode to Void
        ga.set_time_void()
        # Set the aiding source -> IMU frame alignment with the frames aligned.
        ga.aiding_alignment_fixed = [90.0, 1.0, 0.0]
        # Set the variance on the alignment to 5.0 deg in HPR.
        ga.aiding_alignment_var = [5.0,5.0,5.0]
        #============================================================================
        gh = oxts_sdk.GadHandler()
        if output_type == OUTPUT_TYPE.UDP:
                gh.set_encoder_to_bin()
                gh.set_output_mode_to_udp(unit_ip)
        elif output_type == OUTPUT_TYPE.CSV:
                gh.set_encoder_to_csv()
                gh.set_output_mode_to_to_file(file_out)
        else:
                print("Output type not known.")
                sys.exit(1)

        for i in range(0,num_packets,1):
                # Send the packets
                gh.send_packet(gp)
                gh.send_packet(gv)
                gh.send_packet(ga)
                if (i % 10 == 0): # Message is printed for every 10th pack sent.
                        print("packet " + str(i) + " sent")

                time.sleep(0.1)

sys.exit(0)
import sys
import time
import oxts_sdk

if __name__ == "__main__":
        if len(sys.argv) < 3:
                print("Invalid number of command line arguments, requires: <IP> <number of packets>")
                sys.exit(1)

        unit_ip =  sys.argv[1]
        num_packets = sys.argv[2]

        # Initialise the handler
        gh = oxts_sdk.GadHandler()
        gh.set_encoder_to_bin()
        gh.set_output_mode_to_udp(unit_ip)
        # Construct the velocity aiding with stream ID 130.
        gv = oxts_sdk.GadVelocity(130)
        for i in range(0,num_packets,1):
                # Set the required data
                gv.vel_ned = [0.0,0.0,0.0]
                gv.vel_ned_var = [0.1,0.1,0.1]
                gv.set_time_void()
                gv.aiding_lever_arm_fixed = [0.0,0.0,1.0]
                gv.aiding_lever_arm_var = [0.01,0.01,0.01]
                # Send the packets
                gh.send_packet(gv)
                print("packet " + str(i) + " sent")
                time.sleep(0.1)

        sys.exit(0)
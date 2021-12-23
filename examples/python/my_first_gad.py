import oxts_sdk
import time


gh = oxts_sdk.GadHandler()
gh.set_encoder_to_bin()
gh.set_output_mode_to_udp("195.0.0.185")

gv = oxts_sdk.GadVelocity(130)
gv.vel_neu = [0.0,0.0,0.0]
gv.vel_neu_var = [0.1,0.1,0.1]
gv.set_time_void()
gv.aiding_lever_arm_fixed = [0.0,0.0,1.0]
gv.aiding_lever_arm_var = [0.01,0.01,0.01]

num_packets = 100
# Send the packets
for i in range(0, num_packets):
    gh.send_packet(gv)
    time.sleep(0.1)


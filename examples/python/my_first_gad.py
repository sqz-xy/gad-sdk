import oxts_sdk


gh = oxts_sdk.GadHandler()
gh.set_encoder_to_csv()
gh.set_output_mode_to_file("my_first.gad")

gv = oxts_sdk.GadVelocity(123)
gv.vel_neu = [0.0,0.0,0.0]
gv.vel_neu_var = [0.1,0.1,0.1]
gv.time_gps = [10, 0]
gv.aiding_lever_arm_fixed = [0.0,0.0,1.0]
gv.aiding_lever_arm_var = [0.01,0.01,0.01]

gs = oxts_sdk.GadSpeed(124)
gs.wheelspeed_count = [3, 32]
gs.wheelspeed_var = 0.5
gv.time_gps = [10, 0]
gs.aiding_lever_arm_fixed = [0.0,0.0,1.0]
gs.aiding_lever_arm_var = [0.01,0.01,0.01]

num_packets = 100
# Send the packets
for i in range(0, num_packets):
    gh.send_packet(gv)
    gh.send_packet(gs)
    gv.time_gps = [10, i]
    gs.time_gps = [10, i]
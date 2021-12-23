import oxts_sdk


gh = oxts_sdk.GadHandler()
gh.set_encoder_to_csv()
gh.set_output_mode_to_file("my_first.gad")

gp = oxts_sdk.GadPosition(130)
gp.pos_local = [0.5,0.6,0.7]
gp.pos_local_var = [0.11,0.12,0.13,0.01,0.02,0.04]
gp.time_gps = [10, 0]
gp.aiding_lever_arm_fixed = [0.0,0.0,1.0]
gp.aiding_lever_arm_var = [0.01,0.01,0.01]

gv = oxts_sdk.GadVelocity(131)
gv.vel_neu = [0.0,0.0,0.0]
gv.vel_neu_var = [0.1,0.2,0.3]
gv.time_gps = [10, 0]
gv.aiding_lever_arm_fixed = [0.0,0.0,1.0]
gv.aiding_lever_arm_var = [0.01,0.01,0.01]

ga = oxts_sdk.GadAttitude(132)
ga.att = [0.0, 0.0, 0.0]
ga.att_var = 0.5
ga.time_gps = [10, 0]
ga.set_aiding_alignment_optimising()

gs = oxts_sdk.GadSpeed(133)
gs.wheelspeed_count = [0.0, 1.0]
gs.wheelspeed_var = 0.1
gs.time_gps = [10, 0]
gs.aiding_lever_arm_fixed = [0.0,0.0,1.0]
gs.aiding_lever_arm_var = [0.01,0.01,0.01]

num_packets = 100
# Send the packets
for i in range(0, num_packets):
    gh.send_packet(gp)
    gh.send_packet(gv)
    gh.send_packet(ga)
    gh.send_packet(gs)
    gp.time_gps = [2137, i]
    gv.time_gps = [2137, i]
    ga.time_gps = [2137, i]
    gs.time_gps = [2137, i]

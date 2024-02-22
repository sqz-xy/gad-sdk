import oxts_sdk
import unittest
import pytest

######################################### GAD POSITION #############################################
# Local pos - good input
def test_GP_pos_local_3 ():
    gp = oxts_sdk.GadPosition(132)
    gp.pos_local = [0.5,0.6,0.7]
    assert(gp.pos_local == [0.5,0.6,0.7])
# Local pos - bad input
def test_GP_pos_local_2 ():
    gp = oxts_sdk.GadPosition(132)
    gp.pos_local = [0.5,0.6]
    assert(gp.pos_local == pytest.approx([0.0,0.0,0.0]))
 
# Local pos variance - good input
def test_GP_pos_local_var_3 ():
    gp = oxts_sdk.GadPosition(132)
    gp.pos_local_var = [0.11,0.12,0.13]
    assert(gp.pos_local_var[0:3] == [0.11,0.12,0.13])
# Local pos variance - good input
def test_GP_pos_local_var_6 ():
    gp = oxts_sdk.GadPosition(132)
    gp.pos_local_var = [0.11,0.12,0.13,0.21,0.22,0.23]
    assert(gp.pos_local_var == [0.11,0.12,0.13,0.21,0.22,0.23])
# Local pos variance - bad input
def test_GP_pos_local_var_4 ():
    gp = oxts_sdk.GadPosition(132)
    gp.pos_local_var = [0.11,0.12,0.13,0.21]
    assert(gp.pos_local_var == [0.0, 0.0, 0.0, 0.0, 0.0, 0.0])

# Geodetic - good input
def test_GP_pos_geodetic_3 ():
    gp = oxts_sdk.GadPosition(132)
    gp.pos_geodetic = [0.5,0.6,0.7]
    assert(gp.pos_geodetic == [0.5,0.6,0.7])
# Geodetic - bad input
def test_GP_pos_geodetic_2 ():
   gp = oxts_sdk.GadPosition(132)
   gp.pos_geodetic = [0.5,0.6]
   assert(gp.pos_geodetic == pytest.approx([0.0,0.0,0.0]))

# Geodetic variance - good input
def test_GP_pos_geodetic_var_3 ():
    gp = oxts_sdk.GadPosition(132)
    gp.pos_geodetic_var = [0.5,0.6,0.7]
    assert(gp.pos_geodetic_var[0:3] == [0.5,0.6,0.7])
# Geodetic variance - good input
def test_GP_pos_geodetic_var_6 ():
    gp = oxts_sdk.GadPosition(132)
    gp.pos_geodetic_var = [0.5,0.6,0.7,0.8,0.9,1.0]
    assert(gp.pos_geodetic_var == [0.5,0.6,0.7,0.8,0.9,1.0])
# Geodetic variance - bad input
def test_GP_pos_geodetic_var_4 ():
    gp = oxts_sdk.GadPosition(132)
    gp.pos_geodetic_var = [0.5,0.6,0.7,0.8]
    assert(gp.pos_geodetic_var == pytest.approx([0.0, 0.0, 0.0, 0.0, 0.0, 0.0]))

# GPS Time - good input  
def test_GP_time_gps_2 ():
    gp = oxts_sdk.GadPosition(132)
    gp.time_gps = [10, 0]
    assert(gp.time_gps[0:2] == [10, 0])
# GPS Time - bad input
def test_GP_time_gps_1 ():
    gp = oxts_sdk.GadPosition(132)
    gp.time_gps = [10]
    assert(gp.time_gps[0:2] == pytest.approx([0.0, 0.0]))

# Aiding lever arm fixed - good input
def test_GP_aiding_lever_arm_fixed_3 ():
    gp = oxts_sdk.GadPosition(132)
    gp.aiding_lever_arm_fixed = [0.5,0.6,0.7]
    assert(gp.aiding_lever_arm_fixed == [0.5,0.6,0.7])
# Aiding lever arm fixed - bad input
def test_GP_aiding_lever_arm_fixed_2 ():
    gp = oxts_sdk.GadPosition(132)
    gp.aiding_lever_arm_fixed = [0.5,0.6]
    assert(gp.aiding_lever_arm_fixed == pytest.approx([0.0,0.0,0.0]))

# Aiding lever arm variance - good input
def test_GP_pos_aiding_lever_arm_var_3 ():
    gp = oxts_sdk.GadPosition(132)
    gp.aiding_lever_arm_var = [0.5,0.6,0.7]
    assert(gp.aiding_lever_arm_var[0:3] == [0.5,0.6,0.7])
# Aiding lever arm variance - bad input
def test_GP_pos_aiding_lever_arm_var_2 ():
    gp = oxts_sdk.GadPosition(132)
    gp.aiding_lever_arm_var = [0.5,0.6]
    assert(gp.aiding_lever_arm_var[0:3] == pytest.approx([0.0,0.0,0.0]))
################################################################################


######################################### GAD VELOCITY #############################################

# ned velocity frame - good input
def test_GV_vel_ned_3 ():
    gv = oxts_sdk.GadVelocity(133)
    gv.vel_ned = [0.0,0.4,0.1]
    assert(gv.vel_ned == [0.0,0.4,0.1])
# ned velocity frame - bad input
def test_GV_vel_ned_2 ():
    gv = oxts_sdk.GadVelocity(133)
    gv.vel_ned = [0.0,0.4]
    assert(gv.vel_ned == pytest.approx([0.0,0.0,0.0]))

# ned variance - good input
def test_GV_pos_ned_var_3 ():
    gv = oxts_sdk.GadVelocity(133)
    gv.vel_ned_var = [0.11,0.12,0.13]
    assert(gv.vel_ned_var[0:3] == [0.11,0.12,0.13])
# ned variance - good input
def test_GV_pos_ned_var_6 ():
    gv = oxts_sdk.GadVelocity(133)
    gv.vel_ned_var = [0.11,0.12,0.13,0.21,0.22,0.23]
    assert(gv.vel_ned_var == [0.11,0.12,0.13,0.21,0.22,0.23])
# ned variance - bad input
def test_GV_vel_ned_var_4 ():
    gv = oxts_sdk.GadVelocity(133)
    gv.vel_ned_var = [0.11,0.12,0.13,0.21]
    assert(gv.vel_ned_var == pytest.approx([0.0, 0.0, 0.0, 0.0, 0.0, 0.0])) 

# Odom velocity frame - good input
def test_GV_vel_odom_3 ():
    gv = oxts_sdk.GadVelocity(133)
    gv.vel_odom = [0.1,0.2,0.3]
    assert(gv.vel_odom == [0.1,0.2,0.3])
# Odom velocity frame - bad input
def test_GV_vel_odom_2 ():
    gv = oxts_sdk.GadVelocity(133)
    gv.vel_odom = [0.1,0.2]
    assert(gv.vel_odom == pytest.approx([0.0,0.0,0.0]))

# Odom variance - good input
def test_GV_pos_odom_var_3 ():
    gv = oxts_sdk.GadVelocity(133)
    gv.vel_odom_var = [0.11,0.12,0.13]
    assert(gv.vel_odom_var[0:3] == [0.11,0.12,0.13])
# Odom variance - good input
def test_GV_pos_odom_var_6 ():
    gv = oxts_sdk.GadVelocity(133)
    gv.vel_odom_var = [0.11,0.12,0.13,0.21,0.22,0.23]
    assert(gv.vel_odom_var == [0.11,0.12,0.13,0.21,0.22,0.23])
# Odom variance - bad input
def test_GV_vel_odom_var_4 ():
    gv = oxts_sdk.GadVelocity(133)
    gv.vel_odom_var = [0.11,0.12,0.13,0.21]
    assert(gv.vel_odom_var == pytest.approx([0.0, 0.0, 0.0, 0.0, 0.0, 0.0])) 

# Local velocity frame - good input
def test_GV_vel_local_3 ():
    gv = oxts_sdk.GadVelocity(133)
    gv.vel_local = [0.1,0.2,0.3]
    assert(gv.vel_local == [0.1,0.2,0.3])
# Local velocity frame - bad input
def test_GV_vel_local_2 ():
    gv = oxts_sdk.GadVelocity(133)
    gv.vel_local = [0.1,0.2]
    assert(len(gv.vel_local) == 3)

# Local variance - good input
def test_GV_pos_local_var_3 ():
    gv = oxts_sdk.GadVelocity(133)
    gv.vel_local_var = [0.11,0.12,0.13]
    assert(gv.vel_local_var[0:3] == [0.11,0.12,0.13])
# Local variance - good input
def test_GV_pos_local_var_6 ():
    gv = oxts_sdk.GadVelocity(133)
    gv.vel_local_var = [0.11,0.12,0.13,0.21,0.22,0.23]
    assert(gv.vel_local_var == [0.11,0.12,0.13,0.21,0.22,0.23])
# Local variance - bad input
def test_GV_vel_local_var_4 ():
    gv = oxts_sdk.GadVelocity(133)
    gv.vel_local_var = [0.11,0.12,0.13,0.21]
    assert(gv.vel_local_var == pytest.approx([0.0, 0.0, 0.0, 0.0, 0.0, 0.0]))

# Aiding lever arm fixed - good input
def test_GV_aiding_lever_arm_fixed_3 ():
    gv = oxts_sdk.GadVelocity(133)
    gv.aiding_lever_arm_fixed = [0.5,0.6,0.7]
    assert(gv.aiding_lever_arm_fixed == [0.5,0.6,0.7])
# Aiding lever arm fixed - bad input
def test_GV_aiding_lever_arm_fixed_2 ():
    gv = oxts_sdk.GadVelocity(133)
    gv.aiding_lever_arm_fixed = [0.5,0.6]
    assert(gv.aiding_lever_arm_fixed == pytest.approx([0.0, 0.0, 0.0]))

# Aiding lever arm variance - good input
def test_GV_pos_aiding_lever_arm_var_3 ():
    gv = oxts_sdk.GadVelocity(133)
    gv.aiding_lever_arm_var = [0.5,0.6,0.7]
    assert(gv.aiding_lever_arm_var[0:3] == [0.5,0.6,0.7])
# Aiding lever arm variance - bad input
def test_GV_pos_aiding_lever_arm_var_2 ():
    gv = oxts_sdk.GadVelocity(133)
    gv.aiding_lever_arm_var = [0.5,0.6]
    assert(gv.aiding_lever_arm_var[0:3] == pytest.approx([0.0, 0.0, 0.0]))

######################################### GAD WHEEL SPEED #############################################
# Speed forwards - good inputs
def test_GWS_speed_fw_1 ():
    gs = oxts_sdk.GadWheelSpeed(134)
    gs.speed_fw = 5.4321
    assert(gs.speed_fw == 5.4321)
# Speed forwards - bad inputs
def test_GWS_speed_fw_0 ():
    gs = oxts_sdk.GadWheelSpeed(134)
    gs.speed_fw
    assert(gs.speed_fw == pytest.approx(0.0))

# Speed forwards variance - good input
def test_GWS_speed_fw_var_1 ():
    gs = oxts_sdk.GadWheelSpeed(134)
    gs.speed_fw_var = 6.54321
    assert(gs.speed_fw_var == 6.54321)
# Speed forwards variance - bad input
def test_GWS_speed_fw_var_0 ():
    gs = oxts_sdk.GadWheelSpeed(134)
    gs.speed_fw_var
    assert(gs.speed_fw_var == pytest.approx(0.0))

# Wheelspeed count - good input
def test_GWS_wheelspeed_count_2 ():
    gs = oxts_sdk.GadWheelSpeed(134)
    gs.wheelspeed_count = [10.54321, 0.6789]
    assert(gs.wheelspeed_count[0:2] == [10.54321, 0.6789])
# Wheelspeed count - bad input
def test_GWS_wheelspeed_count_1 ():
    gs = oxts_sdk.GadWheelSpeed(134)
    gs.wheelspeed_count = [10.54321]
    assert(gs.wheelspeed_count == pytest.approx([0.0, 0.0, 0.0]))

# Wheelspeed variance - good input
def test_GWS_wheelspeed_var_1 ():
    gs = oxts_sdk.GadWheelSpeed(134)
    gs.wheelspeed_var = 10.54321
    assert(gs.wheelspeed_var == 10.54321)
# Wheelspeed variance - bad input
def test_GWS_wheelspeed_var_0 ():
    gs = oxts_sdk.GadWheelSpeed(134)
    gs.wheelspeed_var
    assert(gs.wheelspeed_var == pytest.approx(0.0))

# Aiding lever arm fixed - good input
def test_GWS_aiding_lever_arm_fixed_3 ():
    gs = oxts_sdk.GadWheelSpeed(134)
    gs.aiding_lever_arm_fixed = [0.00, 1.01, 2.02]
    assert(gs.aiding_lever_arm_fixed == [0.00, 1.01, 2.02])
# Aiding lever arm fixed - bad input
def test_GWS_aiding_lever_arm_fixed_2 ():
    gs = oxts_sdk.GadWheelSpeed(134)
    gs.aiding_lever_arm_fixed = [0.00, 1.01]
    assert(gs.aiding_lever_arm_fixed == pytest.approx([0.0, 0.0, 0.0]))

# Aiding lever arm variance - good input
def test_GWS_aiding_lever_arm_var_3 ():
    gs = oxts_sdk.GadWheelSpeed(134)
    gs.aiding_lever_arm_var = [0.00, 1.01, 2.02]
    assert(gs.aiding_lever_arm_var[0:3] == [0.00, 1.01, 2.02])
# Aiding lever arm variance - bad input
def test_GWS_aiding_lever_arm_var_2 ():
    gs = oxts_sdk.GadWheelSpeed(134)
    gs.aiding_lever_arm_var = [0.00, 1.01]
    assert(gs.aiding_lever_arm_var[0:3] == pytest.approx([0.0, 0.0, 0.0]))

######################################### GAD SPEED #############################################
# Speed m/s forwards - good inputs
def test_GS_speed_fw_1 ():
    gs = oxts_sdk.GadSpeed(135)
    gs.speed_fw_ms = 13.258
    assert(gs.speed_fw_ms[0] == 13.258)
# Speed m/s forwards - bad inputs
def test_GS_speed_fw_0 ():
    gs = oxts_sdk.GadSpeed(135)
    gs.speed_fw_ms
    assert(gs.speed_fw_ms[0] == pytest.approx(0.0))

# Speed m/s backwards - good inputs
def test_GS_speed_bw_1 ():
    gs = oxts_sdk.GadSpeed(135)
    gs.speed_bw_ms = 13.258
    assert(gs.speed_bw_ms[0] == 13.258)
# Speed m/s forwards - bad inputs
def test_GS_speed_bw_0 ():
    gs = oxts_sdk.GadSpeed(135)
    gs.speed_bw_ms
    assert(gs.speed_bw_ms[0] == pytest.approx(0.0))

# Speed m/s unidirection - good inputs
def test_GS_speed_un_1 ():
    gs = oxts_sdk.GadSpeed(135)
    gs.speed_un_ms = 13.258
    assert(gs.speed_un_ms[0] == 13.258)
# Speed m/s unidirection - bad inputs
def test_GS_speed_un_0 ():
    gs = oxts_sdk.GadSpeed(135)
    gs.speed_un_ms
    assert(gs.speed_un_ms[0] == pytest.approx(0.0))

# Speed m/s variance - good input
def test_GS_speed_fw_var_1 ():
    gs = oxts_sdk.GadSpeed(135)
    gs.speed_ms_var= 7.654321
    assert(gs.speed_ms_var[0] == 7.654321)
# Speed m/s variance - bad input
def test_GS_speed_fw_var_0 ():
    gs = oxts_sdk.GadSpeed(135)
    gs.speed_ms_var
    assert(gs.speed_ms_var[0] == pytest.approx(0.0))

# Speed fw pulsed - good inputs
def test_GS_speed_fw_pulse_1 ():
    gs = oxts_sdk.GadSpeed(135)
    gs.speed_fw_pulsed = [5.4321, 0.9, 1.1]
    assert(gs.speed_fw_pulsed == [5.4321, 0.9, 1.1])

# Speed bw pulsed - good inputs
def test_GS_speed_bw_pulse_1 ():
    gs = oxts_sdk.GadSpeed(135)
    gs.speed_bw_pulsed = [1.4321, 0.8, 1.2]
    assert(gs.speed_bw_pulsed == [1.4321, 0.8, 1.2])

# Speed un pulsed - good inputs
def test_GS_speed_un_pulse_1 ():
    gs = oxts_sdk.GadSpeed(135)
    gs.speed_un_pulsed = [2.4321, 0.85, 1.21]
    assert(gs.speed_un_pulsed == [2.4321, 0.85, 1.21])

# Speed pulse variance - good input
def test_GS_speed_pulsed_var_1 ():
    gs = oxts_sdk.GadSpeed(135)
    gs.speed_pulsed_var= [1.654321, 1.05] 
    assert(gs.speed_pulsed_var[0:3] == [1.654321, 1.05, 0.0])
# Speed pulse variance - bad input
def test_GS_speed_pulsed_var_0 ():
    gs = oxts_sdk.GadSpeed(135)
    gs.speed_pulsed_var
    assert(gs.speed_pulsed_var[0] == pytest.approx(0.0))

def test_GS_speed_pulsed_var_period_1 ():
    gs = oxts_sdk.GadSpeed(135)
    gs.speed_pulsed_var_period= [1.654321, 1.05, 1.23] 
    assert(gs.speed_pulsed_var_period[0:3] == [1.654321, 1.05, 1.23])

def test_GS_speed_pulsed_var_period_1 ():
    gs = oxts_sdk.GadSpeed(135)
    gs.speed_pulsed_var_period= [1.654321, 1.05, 1.23] 
    assert(gs.speed_pulsed_var_period[0:3] == [1.654321, 1.05, 1.23])

# Aiding lever arm fixed - good input
def test_GS_aiding_lever_arm_fixed_3 ():
    gs = oxts_sdk.GadSpeed(135)
    gs.aiding_lever_arm_fixed = [0.00, 1.01, 2.02]
    assert(gs.aiding_lever_arm_fixed == [0.00, 1.01, 2.02])
# Aiding lever arm fixed - bad input
def test_GS_aiding_lever_arm_fixed_2 ():
    gs = oxts_sdk.GadSpeed(135)
    gs.aiding_lever_arm_fixed = [0.00, 1.01]
    assert(gs.aiding_lever_arm_fixed == pytest.approx([0.0, 0.0, 0.0]))

# Aiding lever arm variance - good input
def test_GS_aiding_lever_arm_var_3 ():
    gs = oxts_sdk.GadSpeed(135)
    gs.aiding_lever_arm_var = [0.00, 1.01, 2.02]
    assert(gs.aiding_lever_arm_var[0:3] == [0.00, 1.01, 2.02])
# Aiding lever arm variance - bad input
def test_GS_aiding_lever_arm_var_2 ():
    gs = oxts_sdk.GadSpeed(135)
    gs.aiding_lever_arm_var = [0.00, 1.01]
    assert(gs.aiding_lever_arm_var[0:3] == pytest.approx([0.0, 0.0, 0.0]))

######################################### GAD ATTITUDE #############################################)
# Global att - good input
def test_GA_att_global_3 ():
    ga = oxts_sdk.GadAttitude(136)
    ga.att = [10.0,45.0,5.0]
    assert(ga.att == [10.0,45.0,5.0])
# Global att - bad input
def test_GA_att_global_2 ():
    ga = oxts_sdk.GadAttitude(136)
    ga.att = [0.5,0.6]
    assert(ga.att == pytest.approx([0.0,0.0,0.0]))
 
# Global att variance - good input
def test_GA_att_global_var_3 ():
    ga = oxts_sdk.GadAttitude(136)
    ga.att_var = [0.11,0.12,0.13]
    assert(ga.att_var[0:3] == [0.11,0.12,0.13])
# Global att variance - bad input
def test_GA_att_global_var_4 ():
    ga = oxts_sdk.GadAttitude(136)
    ga.att_var = [0.11,0.12,0.13,0.21]
    assert(ga.att_var == [0.0, 0.0, 0.0, 0.0, 0.0, 0.0])

# local att - good input
def test_GA_att_local_3 ():
    ga = oxts_sdk.GadAttitude(136)
    ga.att_local = [10.0,45.0,5.0]
    assert(ga.att_local == [10.0,45.0,5.0])
# local att - bad input
def test_GA_att_local_2 ():
    ga = oxts_sdk.GadAttitude(136)
    ga.att_local = [0.5,0.6]
    assert(ga.att_local == pytest.approx([0.0,0.0,0.0]))

# Aiding lever arm fixed - good input
def test_GA_aiding_alignment_fixed_3 ():
    ga = oxts_sdk.GadAttitude(136)
    ga.aiding_alignment_fixed = [0.5,0.6,0.7]
    assert(ga.aiding_alignment_fixed == [0.5,0.6,0.7])
# Aiding lever arm fixed - bad input
def test_GA_aiding_alignment_fixed_2 ():
    ga = oxts_sdk.GadAttitude(136)
    ga.aiding_alignment_fixed = [0.5,0.6]
    assert(ga.aiding_alignment_fixed == pytest.approx([0.0,0.0,0.0]))

# Aiding lever arm variance - good input
def test_GA_pos_aiding_alignment_var_3 ():
    ga = oxts_sdk.GadAttitude(136)
    ga.aiding_alignment_var = [0.5,0.6,0.7]
    assert(ga.aiding_alignment_var[0:3] == [0.5,0.6,0.7])
# Aiding lever arm variance - bad input
def test_GA_pos_aiding_alignment_var_2 ():
    ga = oxts_sdk.GadAttitude(136)
    ga.aiding_alignment_var = [0.5,0.6]
    assert(ga.aiding_alignment_var[0:3] == pytest.approx([0.0,0.0,0.0]))
################################################################################
    
######################################### GHD HEADING #############################################)
# Global hea - good input
def test_GH_hea_global_3 ():
    ghe = oxts_sdk.GadHeading(137)
    ghe.heading = 33.5
    assert(ghe.heading == 33.5)

# Global hea variance - good input
def test_GH_hea_global_var_3 ():
    ghe = oxts_sdk.GadHeading(137)
    ghe.heading_var = 0.11
    assert(ghe.heading_var == 0.11)

# local hea - good input
def test_GH_hea_local_3 ():
    ghe = oxts_sdk.GadHeading(137)
    ghe.heading_local = 10.5
    assert(ghe.heading_local == 10.5)

# Aiding lever arm fixed - good input
def test_GH_aiding_alignment_fixed_3 ():
    ghe = oxts_sdk.GadHeading(137)
    ghe.aiding_alignment_fixed = [0.5,0.6,0.7]
    assert(ghe.aiding_alignment_fixed == [0.5,0.6,0.7])
# Aiding lever arm fixed - bad input
def test_GH_aiding_alignment_fixed_2 ():
    ghe = oxts_sdk.GadHeading(137)
    ghe.aiding_alignment_fixed = [0.5,0.6]
    assert(ghe.aiding_alignment_fixed == pytest.approx([0.0,0.0,0.0]))

# Aiding lever arm variance - good input
def test_GH_pos_aiding_alignment_var_3 ():
    ghe = oxts_sdk.GadHeading(137)
    ghe.aiding_alignment_var = [0.5,0.6,0.7]
    assert(ghe.aiding_alignment_var[0:3] == [0.5,0.6,0.7])
# Aiding lever arm variance - bad input
def test_GH_pos_aiding_alignment_var_2 ():
    ghe = oxts_sdk.GadHeading(137)
    ghe.aiding_alignment_var = [0.5,0.6]
    assert(ghe.aiding_alignment_var[0:3] == pytest.approx([0.0,0.0,0.0]))
################################################################################

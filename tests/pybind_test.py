import oxts_sdk
import unittest
import pytest

######################################### GAD POSITION #############################################
# Local pos - good input
def test_GP_pos_local_3 ():
    gp = oxts_sdk.GadPosition(122)
    gp.pos_local = [0.5,0.6,0.7]
    assert(gp.pos_local == [0.5,0.6,0.7])
# Local pos - bad input
def test_GP_pos_local_2 ():
    gp = oxts_sdk.GadPosition(122)
    gp.pos_local = [0.5,0.6]
    assert(len(gp.pos_local) == 3)
 
# Local pos variance - good input
def test_GP_pos_local_var_3 ():
    gp = oxts_sdk.GadPosition(122)
    gp.pos_local_var = [0.11,0.12,0.13]
    assert(gp.pos_local_var == [0.11,0.12,0.13])
# Local pos variance - good input
def test_GP_pos_local_var_6 ():
    gp = oxts_sdk.GadPosition(122)
    gp.pos_local_var = [0.11,0.12,0.13,0.21,0.22,0.23]
    assert(gp.pos_local_var == [0.11,0.12,0.13,0.21,0.22,0.23])
# Local pos variance - bad input
def test_GP_pos_local_var_4 ():
    gp = oxts_sdk.GadPosition(122)
    gp.pos_local_var = [0.11,0.12,0.13,0.21]
    assert(gp.pos_local_var == [0.0, 0.0, 0.0, 0.0, 0.0, 0.0])

# Geodetic - good input
def test_GP_pos_geodetic_3 ():
    gp = oxts_sdk.GadPosition(122)
    gp.pos_geodetic = [0.5,0.6,0.7]
    assert(gp.pos_geodetic == [0.5,0.6,0.7])
# Geodetic - bad input
def test_GP_pos_geodetic_2 ():
   gp = oxts_sdk.GadPosition(122)
   gp.pos_geodetic = [0.5,0.6]
   assert(len(gp.pos_geodetic) == 3)

# Geodetic variance - good input
def test_GP_pos_geodetic_var_3 ():
    gp = oxts_sdk.GadPosition(122)
    gp.pos_geodetic_var = [0.5,0.6,0.7]
    assert(gp.pos_geodetic_var == [0.5,0.6,0.7])
# Geodetic variance - good input
def test_GP_pos_geodetic_var_6 ():
    gp = oxts_sdk.GadPosition(122)
    gp.pos_geodetic_var = [0.5,0.6,0.7,0.8,0.9,1.0]
    assert(gp.pos_geodetic_var == [0.5,0.6,0.7,0.8,0.9,1.0])
# Geodetic variance - bad input
def test_GP_pos_geodetic_var_4 ():
    gp = oxts_sdk.GadPosition(122)
    gp.pos_geodetic_var.clear()
    gp.pos_geodetic_var = [0.5,0.6,0.7,0.8]
    assert(gp.pos_geodetic_var == [0.0, 0.0, 0.0, 0.0, 0.0, 0.0])

# GPS Time - good input  
def test_GP_time_gps_2 ():
    gp = oxts_sdk.GadPosition(122)
    gp.time_gps = [10, 0]
    assert(gp.time_gps == [10, 0])
# GPS Time - bad input
def test_GP_time_gps_1 ():
    gp = oxts_sdk.GadPosition(122)
    gp.time_gps = [10]
    assert(gp.time_gps == pytest.approx([10, 0.0]))

# Aiding lever arm fixed - good input
def test_GP_aiding_lever_arm_fixed_3 ():
    gp = oxts_sdk.GadPosition(122)
    gp.aiding_lever_arm_fixed = [0.5,0.6,0.7]
    assert(gp.aiding_lever_arm_fixed == [0.5,0.6,0.7])
# Aiding lever arm fixed - bad input
def test_GP_aiding_lever_arm_fixed_2 ():
    gp = oxts_sdk.GadPosition(122)
    gp.aiding_lever_arm_fixed.clear()
    gp.aiding_lever_arm_fixed = [0.5,0.6]
    assert(len(gp.aiding_lever_arm_fixed) == 3)

# Aiding lever arm variance - good input
def test_GP_pos_aiding_lever_arm_var_3 ():
    gp = oxts_sdk.GadPosition(122)
    gp.aiding_lever_arm_var = [0.5,0.6,0.7]
    assert(gp.aiding_lever_arm_var == [0.5,0.6,0.7])
# Aiding lever arm variance - bad input
def test_GP_pos_aiding_lever_arm_var_2 ():
    gp = oxts_sdk.GadPosition(122)
    gp.aiding_lever_arm_var.clear()
    gp.aiding_lever_arm_var = [0.5,0.6]
    assert(gp.aiding_lever_arm_var == pytest.approx([0.5,0.6,0.0]))
################################################################################


######################################### GAD VELOCITY #############################################

# NEU velocity frame - good input
def test_GV_vel_neu_3 ():
    gv = oxts_sdk.GadVelocity(123)
    gv.vel_neu = [0.0,0.4,0.1]
    assert(gv.vel_neu == [0.0,0.4,0.1])
# NEU velocity frame - bad input
def test_GV_vel_neu_2 ():
    gv = oxts_sdk.GadVelocity(123)
    gv.vel_neu = [0.0,0.4]
    assert(len(gv.vel_neu) == 3)

# NEU variance - good input
def test_GV_pos_neu_var_3 ():
    gv = oxts_sdk.GadVelocity(123)
    gv.vel_neu_var = [0.11,0.12,0.13]
    assert(gv.vel_neu_var == [0.11,0.12,0.13])
# NEU variance - good input
def test_GV_pos_neu_var_6 ():
    gv = oxts_sdk.GadVelocity(123)
    gv.vel_neu_var = [0.11,0.12,0.13,0.21,0.22,0.23]
    assert(gv.vel_neu_var == [0.11,0.12,0.13,0.21,0.22,0.23])
# NEU variance - bad input
def test_GV_vel_neu_var_4 ():
    gv = oxts_sdk.GadVelocity(123)
    gv.vel_neu_var = [0.11,0.12,0.13,0.21]
    assert(gv.vel_neu_var == [0.0, 0.0, 0.0, 0.0, 0.0, 0.0]) 

# Odom velocity frame - good input
def test_GV_vel_odom_3 ():
    gv = oxts_sdk.GadVelocity(123)
    gv.vel_odom = [0.1,0.2,0.3]
    assert(gv.vel_odom == [0.1,0.2,0.3])
# Odom velocity frame - bad input
def test_GV_vel_odom_2 ():
    gv = oxts_sdk.GadVelocity(123)
    gv.vel_odom = [0.1,0.2]
    assert(len(gv.vel_odom) == 3)

# Odom variance - good input
def test_GV_pos_odom_var_3 ():
    gv = oxts_sdk.GadVelocity(123)
    gv.vel_odom_var = [0.11,0.12,0.13]
    assert(gv.vel_odom_var == [0.11,0.12,0.13])
# Odom variance - good input
def test_GV_pos_odom_var_6 ():
    gv = oxts_sdk.GadVelocity(123)
    gv.vel_odom_var = [0.11,0.12,0.13,0.21,0.22,0.23]
    assert(gv.vel_odom_var == [0.11,0.12,0.13,0.21,0.22,0.23])
# Odom variance - bad input
def test_GV_vel_odom_var_4 ():
    gv = oxts_sdk.GadVelocity(123)
    gv.vel_odom_var = [0.11,0.12,0.13,0.21]
    assert(gv.vel_odom_var == [0.0, 0.0, 0.0, 0.0, 0.0, 0.0]) 

# Local velocity frame - good input
def test_GV_vel_local_3 ():
    gv = oxts_sdk.GadVelocity(123)
    gv.vel_local = [0.1,0.2,0.3]
    assert(gv.vel_local == [0.1,0.2,0.3])
# Local velocity frame - bad input
def test_GV_vel_local_2 ():
    gv = oxts_sdk.GadVelocity(123)
    gv.vel_local = [0.1,0.2]
    assert(len(gv.vel_local) == 3)

# Local variance - good input
def test_GV_pos_local_var_3 ():
    gv = oxts_sdk.GadVelocity(123)
    gv.vel_local_var = [0.11,0.12,0.13]
    assert(gv.vel_local_var == [0.11,0.12,0.13])
# Local variance - good input
def test_GV_pos_local_var_6 ():
    gv = oxts_sdk.GadVelocity(123)
    gv.vel_local_var = [0.11,0.12,0.13,0.21,0.22,0.23]
    assert(gv.vel_local_var == [0.11,0.12,0.13,0.21,0.22,0.23])
# Local variance - bad input
def test_GV_vel_local_var_4 ():
    gv = oxts_sdk.GadVelocity(123)
    gv.vel_local_var = [0.11,0.12,0.13,0.21]
    assert(gv.vel_local_var == [0.0, 0.0, 0.0, 0.0, 0.0, 0.0]) 

# Aiding lever arm fixed - good input
def test_GV_aiding_lever_arm_fixed_3 ():
    gv = oxts_sdk.GadVelocity(123)
    gv.aiding_lever_arm_fixed = [0.5,0.6,0.7]
    assert(gv.aiding_lever_arm_fixed == [0.5,0.6,0.7])
# Aiding lever arm fixed - bad input
def test_GV_aiding_lever_arm_fixed_2 ():
    gv = oxts_sdk.GadVelocity(123)
    gv.aiding_lever_arm_fixed = [0.5,0.6]
    assert(len(gv.aiding_lever_arm_fixed) == 3)

# Aiding lever arm variance - good input
def test_GV_pos_aiding_lever_arm_var_3 ():
    gv = oxts_sdk.GadVelocity(123)
    gv.aiding_lever_arm_var = [0.5,0.6,0.7]
    assert(gv.aiding_lever_arm_var == [0.5,0.6,0.7])
# Aiding lever arm variance - bad input
def test_GV_pos_aiding_lever_arm_var_2 ():
    gv = oxts_sdk.GadVelocity(123)
    gv.aiding_lever_arm_var = [0.5,0.6]
    assert(len(gv.aiding_lever_arm_var) == 3)

######################################### GAD SPEED #############################################
# Speed forwards - good inputs
def test_GS_speed_fw_1 ():
    gs = oxts_sdk.GadSpeed(124)
    gs.speed_fw = 5.4321
    assert(gs.speed_fw == 5.4321)
# Speed forwards - bad inputs
def test_GS_speed_fw_0 ():
    gs = oxts_sdk.GadSpeed(124)
    gs.speed_fw
    assert(gs.speed_fw == pytest.approx(0.0))

# Speed forwards variance - good input
def test_GS_speed_fw_var_1 ():
    gs = oxts_sdk.GadSpeed(124)
    gs.speed_fw_var = 6.54321
    assert(gs.speed_fw_var == 6.54321)
# Speed forwards variance - bad input
def test_GS_speed_fw_var_0 ():
    gs = oxts_sdk.GadSpeed(124)
    gs.speed_fw_var
    assert(gs.speed_fw_var == pytest.approx(0.0))

# Wheelspeed count - good input
def test_GS_wheelspeed_count_2 ():
    gs = oxts_sdk.GadSpeed(124)
    gs.wheelspeed_count = [10.54321, 0.6789]
    assert(gs.wheelspeed_count == [10.54321, 0.6789])
# Wheelspeed count - bad input
def test_GS_wheelspeed_count_1 ():
    gs = oxts_sdk.GadSpeed(124)
    gs.wheelspeed_count = [10.54321]
    assert(gs.wheelspeed_count == pytest.approx([10.54321, 0.0]))

# Wheelspeed variance - good input
def test_GS_wheelspeed_var_1 ():
    gs = oxts_sdk.GadSpeed(124)
    gs.wheelspeed_var = 10.54321
    assert(gs.wheelspeed_var == 10.54321)
# Wheelspeed variance - bad input
def test_GS_wheelspeed_var_0 ():
    gs = oxts_sdk.GadSpeed(124)
    gs.wheelspeed_var
    assert(gs.wheelspeed_var == 0.0)

# Aiding lever arm fixed - good input
def test_GS_aiding_lever_arm_fixed_3 ():
    gs = oxts_sdk.GadSpeed(124)
    gs.aiding_lever_arm_fixed = [0.00, 1.01, 2.02]
    assert(gs.aiding_lever_arm_fixed == [0.00, 1.01, 2.02])
# Aiding lever arm fixed - bad input
def test_GS_aiding_lever_arm_fixed_2 ():
    gs = oxts_sdk.GadSpeed(124)
    gs.aiding_lever_arm_fixed = [0.00, 1.01]
    assert(len(gs.aiding_lever_arm_fixed) == 3)

# Aiding lever arm variance - good input
def test_GS_aiding_lever_arm_var_3 ():
    gs = oxts_sdk.GadSpeed(124)
    gs.aiding_lever_arm_var = [0.00, 1.01, 2.02]
    assert(gs.aiding_lever_arm_var == [0.00, 1.01, 2.02])
# Aiding lever arm variance - bad input
def test_GS_aiding_lever_arm_var_2 ():
    gs = oxts_sdk.GadSpeed(124)
    gs.aiding_lever_arm_var = [0.00, 1.01]
    assert(len(gs.aiding_lever_arm_var) == 3)

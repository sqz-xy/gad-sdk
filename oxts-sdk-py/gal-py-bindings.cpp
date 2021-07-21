#include <pybind11/pybind11.h>
#include <string>

#include "oxts/gal-cpp/gad.hpp"
#include "oxts/gal-cpp/gad_handler.hpp"
#include "oxts/gal-cpp/gad_output/gad_output_file.hpp"
#include "oxts/gal-cpp/gad_output/gad_output_udp.hpp"
#include "oxts/gal-cpp/gad_encoders/gad_encoder_csv.hpp"
#include "oxts/gal-cpp/gad_encoders/gad_encoder_bin.hpp"

namespace py = pybind11;

PYBIND11_MODULE(oxts_sdk, m) {
    m.doc() = "OxTS SDK"; // optional module docstring

    py::class_<OxTS::Gad>(m, "Gad")
        // Constructors
        .def(py::init<>())
        .def(py::init<uint8_t, int8_t>())
        // General Accessors
        .def("set_stream_id", &OxTS::Gad::SetStreamId)
        .def("get_stream_id", &OxTS::Gad::GetStreamId)
        // Time accessors
        .def("set_time_invalid", &OxTS::Gad::SetTimeInvalid)
        .def("set_time_valid", &OxTS::Gad::SetTimeValid)
        .def("set_time_external", &OxTS::Gad::SetTimeExternal)
        .def("get_time_external_week", &OxTS::Gad::GetTimeExternalWeek)
        .def("get_time_external_seconds_from_sunday", &OxTS::Gad::GetTimeExternalSecondsFromSunday)
        .def("set_time_gps", &OxTS::Gad::SetTimeGps)
        .def("get_time_gps_week", &OxTS::Gad::GetTimeGpsWeek)
        .def("get_time_gps_seconds_from_sunday", &OxTS::Gad::GetTimeGpsSecondsFromSunday)
        .def("set_time_pps_relative", &OxTS::Gad::SetTimePpsRelative)
        .def("get_time_pps_relative", &OxTS::Gad::GetTimePpsRelative)
        .def("set_time_latency", &OxTS::Gad::SetTimeLatency)
        .def("get_time_latency", &OxTS::Gad::GetTimeLatency)
        .def("set_time_void", &OxTS::Gad::SetTimeVoid)
        // Acquisiton time accessors.
        .def("set_acq_invalid", &OxTS::Gad::SetAcqInvalid)
        .def("set_acq_valid", &OxTS::Gad::SetAcqValid)
        .def("set_acq_timestamp", &OxTS::Gad::SetAcqTimestamp)
        .def("get_acq_timestamp", &OxTS::Gad::GetAcqTimestamp);

    py::class_<OxTS::GadPosition, OxTS::Gad>(m, "GadPosition")
        .def(py::init<uint8_t>())
        .def("set_pos_geodetic", &OxTS::GadPosition::SetPosGeodetic)
        .def("set_pos_local", &OxTS::GadPosition::SetPosLocal)
        .def("set_pos_geodetic_var", &OxTS::GadPosition::SetPosGeodeticVar)
        .def("set_pos_local_var", &OxTS::GadPosition::SetPosLocalVar)
        .def("set_aiding_lever_arm_fixed", &OxTS::GadPosition::SetAidingLeverArmFixed)
        .def("set_aiding_lever_arm_optimising", &OxTS::GadPosition::SetAidingLeverArmOptimising)
        .def("set_aiding_lever_arm_config", &OxTS::GadPosition::SetAidingLeverArmConfig)
        .def("set_aiding_lever_arm_var", &OxTS::GadPosition::SetAidingLeverArmVar);

    py::class_<OxTS::GadVelocity, OxTS::Gad>(m, "GadVelocity")
        .def(py::init<uint8_t>())
        .def("set_vel_neu", &OxTS::GadVelocity::SetVelNeu)
        .def("set_vel_odom", &OxTS::GadVelocity::SetVelOdom)
        .def("set_vel_local", &OxTS::GadVelocity::SetVelLocal)
        .def("set_vel_neu_var", &OxTS::GadVelocity::SetVelNeuVar)
        .def("set_vel_odom_var", &OxTS::GadVelocity::SetVelOdomVar)
        .def("set_vel_local_var", &OxTS::GadVelocity::SetVelLocalVar)
        .def("set_aiding_lever_arm_fixed", &OxTS::GadVelocity::SetAidingLeverArmFixed)
        .def("set_aiding_lever_arm_optimising", &OxTS::GadVelocity::SetAidingLeverArmOptimising)
        .def("set_aiding_lever_arm_config", &OxTS::GadVelocity::SetAidingLeverArmConfig)
        .def("set_aiding_lever_arm_var", &OxTS::GadVelocity::SetAidingLeverArmVar);

    py::class_<OxTS::GadSpeed, OxTS::Gad>(m, "GadSpeed")
        .def(py::init<uint8_t>())
        .def("set_speed_fw", &OxTS::GadSpeed::SetSpeedFw)
        .def("set_speed_fw_var", &OxTS::GadSpeed::SetSpeedFwVar)
        .def("set_wheelspeed_count", &OxTS::GadSpeed::SetWheelspeedCount)
        .def("set_wheelspeed_var", &OxTS::GadSpeed::SetWheelspeedVar)
        .def("set_aiding_lever_arm_fixed", &OxTS::GadSpeed::SetAidingLeverArmFixed)
        .def("set_aiding_lever_arm_optimising", &OxTS::GadSpeed::SetAidingLeverArmOptimising)
        .def("set_aiding_lever_arm_config", &OxTS::GadSpeed::SetAidingLeverArmConfig)
        .def("set_aiding_lever_arm_var", &OxTS::GadSpeed::SetAidingLeverArmVar);

    py::class_<OxTS::GadAttitude, OxTS::Gad>(m, "GadAttitude")
        .def(py::init<uint8_t>())
        .def("set_att", &OxTS::GadAttitude::SetAtt)
        .def("set_att_var", &OxTS::GadAttitude::SetAttVar)
        .def("set_aiding_alignment_fixed", &OxTS::GadAttitude::SetAidingAlignmentFixed)
        .def("set_aiding_alignment_optimising", &OxTS::GadAttitude::SetAidingAlignmentOptimising)
        .def("set_aiding_alignment_var", &OxTS::GadAttitude::SetAidingAlignmentVar);

    py::class_<OxTS::GadHandler>(m, "GadHandler")
        .def(py::init<>())
        .def(py::init<OxTS::GadEncoder*>(), py::arg("encoder_strategy"))
        .def("set_encoder_to_bin", &OxTS::GadHandler::SetEncoderToBin)
        .def("set_encoder_to_csv", &OxTS::GadHandler::SetEncoderToCsv)
        .def("set_output_mode_to_file", &OxTS::GadHandler::SetOutputModeToFile, py::arg("file_path"))
        .def("set_output_mode_to_udp", &OxTS::GadHandler::SetOutputModeToUdp, py::arg("ip"))
        .def("send_packet", &OxTS::GadHandler::SendPacket, py::arg("g"));

    py::class_<OxTS::GadEncoderCsv>(m,"GadEncoderCsv")
        .def(py::init<>())
        .def("EncodePacket", &OxTS::GadEncoderCsv::EncodePacket)
        .def("GetPacket", &OxTS::GadEncoderCsv::GetPacket)
        .def("GetPacketSize", &OxTS::GadEncoderCsv::GetPacketSize);

    py::class_<OxTS::GadEncoderBin>(m,"GadEncoderBin")
        .def(py::init<>())
        .def("EncodePacket", &OxTS::GadEncoderBin::EncodePacket)
        .def("GetPacket", &OxTS::GadEncoderBin::GetPacket)
        .def("GetPacketSize", &OxTS::GadEncoderBin::GetPacketSize);

    py::class_<OxTS::GadOutputUdp>(m,"GadOutputUdp")
        .def(py::init<std::string>())
        .def("output_packet", &OxTS::GadOutputUdp::OutputPacket);

    py::class_<OxTS::GadOutputFile>(m,"GadOutputFile")
        .def(py::init<std::string>())
        .def("output_packet", &OxTS::GadOutputFile::OutputPacket)
        .def("set_output_file", &OxTS::GadOutputFile::SetOutputFile)
        .def("get_output_file", &OxTS::GadOutputFile::GetOutputFile)
        .def("set_output_file_path", &OxTS::GadOutputFile::SetOutputFilePath)
        .def("get_output_file_path", &OxTS::GadOutputFile::GetOutputFilePath);
}
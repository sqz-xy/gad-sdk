#include <iostream>
#include <string>

#include "oxts/gal-cpp/gad.hpp"
#include "oxts/gal-cpp/gad_handler.hpp"
#include "oxts_sleep.hpp"

enum class OUTPUT_TYPE
{
        UDP = 0,
        CSV = 1
};

int main(int argc, char* argv[])
{
        int num_packets = 30;
        std::string unit_ip = "192.168.25.22"; 
        std::string file_out = "out.gad";
        OUTPUT_TYPE output_type = OUTPUT_TYPE::UDP;
        if (argc > 1)
        {
                unit_ip = argv[1];
        }
        if (argc > 2)
        {
                num_packets = std::stoi(argv[2]);
        }
        if (argc > 3)
        {
                if (!strcmp(argv[3], "csv"))
                {
                        output_type = OUTPUT_TYPE::CSV;
                }
        }
        if (argc > 4)
        {
                file_out = argv[4];
        }
        OxTS::Gal_Cpp::GadPosition gp(129);
        gp.SetPosGeodetic(51.91520330,-1.24479140,111.525);
        gp.SetPosGeodeticVar(1.0,1.0,1.0);
        gp.SetTimeVoid();
        gp.SetAidingLeverArmFixed(0.5,0.5,1.0);
        gp.SetAidingLeverArmVar(0.1,0.1,0.1);

        OxTS::Gal_Cpp::GadVelocity gv(130);
        gv.SetVelNed(0.0,0.0,0.0);
        gv.SetVelNedVar(0.1,0.1,0.1);
        gv.SetTimeVoid();
        gv.SetAidingLeverArmFixed(0.5,0.5,1.0);
        gv.SetAidingLeverArmVar(0.1,0.1,0.1);

        OxTS::Gal_Cpp::GadAttitude ga(131);
        ga.SetAtt(0.0,0.0,0.0);
        ga.SetAttVar(0.1,0.1,0.1);
        ga.SetTimeVoid();
        ga.SetAidingAlignmentOptimising();
        ga.SetAidingAlignmentVar(5.0,5.0,5.0);
        
        OxTS::Gal_Cpp::GadHandler gh;
        switch (output_type)
        {
        case OUTPUT_TYPE::UDP:
                gh.SetEncoderToBin();
                gh.SetOutputModeToUdp(unit_ip);
                break;
        case OUTPUT_TYPE::CSV:
                gh.SetEncoderToCsv();
                gh.SetOutputModeToFile(file_out);
                break;
        default:
                std::cout << "Output type not known." << std::endl;
                break;
        }

        int sleep_interval = 100;
        for (int i = 0; i < num_packets; ++i)
        {
                gh.SendPacket(gp);
                gh.SendPacket(gv);
                gh.SendPacket(ga);
                if (i % 10 == 0) 
                {
                        std::cout << i << " packets sent" << std::endl;
                }

                OxTS::sleep_millisecods(sleep_interval);        
        }
        return 0;
}
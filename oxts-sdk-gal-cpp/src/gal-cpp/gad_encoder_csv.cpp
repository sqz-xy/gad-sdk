#include "oxts/gal-cpp/gad_encoders/gad_encoder_csv.hpp"

#include <ostream>
#include <fstream>
#include <iostream> //TF added

namespace OxTS
{
	namespace Gal_Cpp
	{
		/** Constructor */
		GadEncoderCsv::GadEncoderCsv() : GadEncoder(),
			m_str_stream(),
			m_str()
		{
			WriteHeader();
		}

		/** Encode the generic aiding packet to csv format.
			* @param g Reference to the Gad data to be encoded.
			*/
		void GadEncoderCsv::EncodePacket(const Gad& g)
		{
			m_str = std::string();
			EncodeGadCsv(g);                      // Encode Gad
		}

		/** Retrieve the encoded packet
		 * @return Char array containing the packet encoded in csv form.
		*/
		const uint8_t* GadEncoderCsv::GetPacket()
		{
			m_str = m_str_stream.str();
			m_str_stream.str("");
			m_str_stream.clear();
			return reinterpret_cast<const uint8_t *>(m_str.c_str());
		}
		/**
		 * @return The encoded packet size (bytes)
		*/
		std::size_t GadEncoderCsv::GetPacketSize()
		{
			return m_str.length();
		}

		/** Private method to encode GAD to CSV. */
		void GadEncoderCsv::EncodeGadCsv(const Gad& g)
		{
			bool i;
			i = Write<std::int32_t>(0U);
			if (i) { i = Write<std::int32_t>(static_cast<std::int32_t>(g.GetType())); }
			if (i) { i = Write<std::int32_t>(static_cast<std::int32_t>(g.GetStreamId())); }
			if (i) { i = WriteGen3d(g.GetValValid(), g.GetVal()); }
			if (i) { i = WriteGen3d(g.GetTimeValid(), g.GetTime()); }
			if (i) { i = WriteFlagAndValue(g.GetAcqValid(), g.GetAcqTimestamp()); }
			if (i) { i = WriteGen3d(g.GetLocValid(), g.GetLoc()); }
			if (i) { i = WriteGen3d(g.GetRes1Valid(), g.GetRes1()); }
			if (i) { i = WriteGen3d(g.GetRes2Valid(), g.GetRes2(), false); }
			if (i) { m_str_stream << "\n"; }
		}
		
		/** Private method to write Gen3d header to CSV. */
		bool GadEncoderCsv::WriteGen3dHeader(const bool end_comma)
		{
			return Write("mode,x_type,x[0],x[1],x[2],v_type,v[0],v[1],v[2],v[3],v[4],v[5]", end_comma);
		}


		/** Private method to write header to CSV. */
		int32_t GadEncoderCsv::WriteHeader()
		{
			int32_t i;
			if (!Write("#ver,type,stream ID,val_valid"))
			{
				i = -1;
			}
			else if (!WriteGen3dHeader())
			{
				i = -1;
			}
			else if (!Write("time_valid"))
			{
				i = -1;
			}
			else if (!WriteGen3dHeader())
			{
				i = -1;
			}
			else if (!Write("acq_valid,acq_time,loc_valid"))
			{
				i = -1;
			}
			else if (!WriteGen3dHeader())
			{
				i = -1;
			}
			else if (!Write("res1_valid"))
			{
				i = -1;
			}
			else if (!WriteGen3dHeader())
			{
				i = -1;
			}
			else if (!Write("res2_valid"))
			{
				i = -1;
			}
			else if (!WriteGen3dHeader(false)) 
			{
				i = -1;
			}
			else if (!Write("\n", false)) 
			{
				i = -1;
			}
			else
			{
				(void)m_str_stream.flush();
				i = (m_str_stream.good()) ? 0 : -1;
			}
			return i;
		}

		/** Private method to write Gen3D to file. */
		bool GadEncoderCsv::WriteGen3d(const bool valid_flag, const Gen3d& gen_3d_data, const bool end_comma)
		{
			bool i;
			if (!Write<std::int32_t>(valid_flag ? 1U : 0U))
			{
				i = false;
			}
			else
			{
				if (valid_flag)
				{
					i = Write<std::int32_t>(static_cast<std::int32_t>(gen_3d_data.GetMode()));
					if (i) { i = Write<std::int32_t>(static_cast<std::int32_t>(gen_3d_data.GetValType())); }
					if (i) { i = WriteWithDecimalPlaces(gen_3d_data.GetValX(), 12U); }
					if (i) { i = WriteWithDecimalPlaces(gen_3d_data.GetValY(), 12U); }
					if (i) { i = WriteWithDecimalPlaces(gen_3d_data.GetValZ(), 12U); }
					if (i) { i = Write<std::int32_t>(static_cast<std::int32_t>(gen_3d_data.GetVarType())); }
					if (i) 
					{ 
						const container_double6_t& var = gen_3d_data.GetVar();
						if (var.size() > 0U) { i = WriteWithDecimalPlaces(var[0U], 12U); }
						if (i && (var.size() > 1U)) { i = WriteWithDecimalPlaces(var[1U], 12U); }
						if (i && (var.size() > 2U)) { i = WriteWithDecimalPlaces(var[2U], 12U); }
						if (i && (var.size() > 3U)) { i = WriteWithDecimalPlaces(var[3U], 12U); }
						if (i && (var.size() > 4U)) { i = WriteWithDecimalPlaces(var[4U], 12U); } 
						if (i && (var.size() > 5U)) { i = WriteWithDecimalPlaces(var[5U], 12U, end_comma); } 
					}
				}
				else
				{
					i = Write(",,,,,,,,,,,", false);
					if (end_comma)
					{
						i = Write(",", false);
					}
				}
			}
			return i;
		}
	}
}

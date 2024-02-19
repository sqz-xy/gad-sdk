#include "oxts/gal-cpp/basic_casts.hpp"
#include "oxts/gal-c/oxts_pointers.h"

namespace OxTS
{
	void BasicCasts::cast_int8_to_1_byte_LE(uint8_t* const b, const int8_t v)
	{
		
	}

	void BasicCasts::cast_uint16_to_2_byte_LE(uint8_t* const b, const uint16_t v)
	{
		set_value_at(b, 0U, static_cast<uint8_t>(v >> 8));
		set_value_at(b, 1U, static_cast<uint8_t>(v & 0xFFU));
	}

	void BasicCasts::cast_double_to_8_byte_LE(uint8_t* const b, const double_t v)
	{
		
	}
}


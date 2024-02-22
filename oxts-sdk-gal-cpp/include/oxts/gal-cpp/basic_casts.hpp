#ifndef BASIC_CASTS_HPP
#define BASIC_CASTS_HPP

#include <cstdint>
#include <cmath>
#include <array>

namespace OxTS
{
	namespace BasicCasts
	{
		template<std::size_t N>
		static void cast_uint8_to_1_byte_LE(typename std::array<uint8_t, N>::iterator &start, const typename std::array<uint8_t, N>::iterator &end, const uint8_t v)
		{
			if (start != end)
			{
				*start = v;
				++start;
			}
		}

		template<std::size_t N>
		static void cast_uint16_to_2_byte_LE(typename std::array<uint8_t, N>::iterator &start, const typename std::array<uint8_t, N>::iterator &end, const uint16_t v)
		{
			if (start != end)
			{
				*start = static_cast<uint8_t>(v & 0xFFU);
			}
			++start;
			if (start != end)
			{
				*start = static_cast<uint8_t>(v >> 8);
			}
			++start;
		}

		template<std::size_t N>
		static void cast_int16_to_2_byte_LE(typename std::array<uint8_t, N>::iterator& start, const typename std::array<uint8_t, N>::iterator& end, const std::int16_t v)
		{
			volatile union { int16_t x; uint16_t c[2]; } u;
			u.x = v;
			if (start != end)
			{
				*start = static_cast<uint8_t>(u.c[0]);
			}
			++start;
			if (start != end)
			{
				*start = static_cast<uint8_t>(u.c[1]);
			}
			++start;
		}

		template<std::size_t N>
		static void  cast_int8_to_1_byte_LE(typename std::array<uint8_t, N>::iterator &start, const typename std::array<uint8_t, N>::iterator &end, const int8_t v)
		{
			if (start != end)
			{
				*start = static_cast<uint8_t>(v);
				++start;
			}
		}

		template<std::size_t N>
		static void cast_double_to_8_byte_LE(typename std::array<uint8_t, N>::iterator &start, const typename std::array<uint8_t, N>::iterator &end, const double_t v)
		{
			volatile union { double_t x; uint8_t c[8]; } u; /*PRQA S 2407 # Require union to manipulate floating point bits. */ /* PRQA S 2176 # Require union to manipulate floating point bits. */
			u.x = v;
			bool should_continue = (start != end);
			std::size_t d = 0U;
			while (should_continue)
			{
				// Assign
				*start = u.c[d];
				// Increment
				++start;
				++d;
				// Check whether we should continue
				should_continue = ((start != end) && (d < 8U));
			}
		}
	}
}

#endif

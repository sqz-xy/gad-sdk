#ifndef OXTS_ARRAYS_HPP
#define OXTS_ARRAYS_HPP

#include <cstddef>
#include <array>
#include "oxts_misra.hpp"

namespace OxTS
{
	template<typename TArray, std::size_t N>
	std::size_t fill_array(const typename std::array<TArray, N>::iterator& start, const typename std::array<TArray, N>::iterator& end, const TArray v) /*PRQA S 1505 # Templated function is used directly by cpp file. */
	{
		std::size_t items_filled = 0U;
		for (typename std::array<TArray, N>::iterator it = start; it != end; ++it)
		{
			*it = v;
			++items_filled;
		}
		return items_filled;
	}

	template<typename TArray, std::size_t SrcSize, std::size_t DstSize>
	std::size_t copy_array( /*PRQA S 1505 # Templated function is used directly by cpp file. */
		const typename std::array<TArray, SrcSize>::const_iterator& src_start,
		const typename std::array<TArray, SrcSize>::const_iterator& src_end,
		const typename std::array<TArray, DstSize>::iterator& dst_start,
		const typename std::array<TArray, DstSize>::iterator& dst_end,
		const std::size_t items_to_copy)
	{
		std::size_t items_copied = 0U;
		typename std::array<TArray, SrcSize>::const_iterator src_it = src_start;
		typename std::array<TArray, DstSize>::iterator dst_it = dst_start;
		// Use single flag to avoid violating rules MCPP 6_5_1 and 6_5_6   
		// MCPP 5_14_1 insists that (dst_it != dst_end) contains side-effects, so must do it this way.
		bool should_continue = (items_copied < items_to_copy);
		if (src_it == src_end) { should_continue = false; }
		if (dst_it == dst_end) { should_continue = false; }
		while (should_continue)
		{
			*dst_it = *src_it;
			++src_it;
			++dst_it;
			++items_copied;
			should_continue = (items_copied < items_to_copy);
			if (src_it == src_end) { should_continue = false; }
			if (dst_it == dst_end) { should_continue = false; }
		}
		return items_copied;
	}
		
}

#endif

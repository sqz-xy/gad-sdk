#ifndef OXTS_POINTERS_H
#define OXTS_POINTERS_H

#include <stdint.h>

//!
//! \brief Return a char pointer from a uint8_t pointer, at the given offset.
char* get_char_ptr_from_uint8(uint8_t* const base, const int32_t offset);

//!
//! \brief Return a char pointer from a char pointer, at the given offset.
char* get_char_ptr_from_char(char* const base, const int32_t offset); /*PRQA S 0776 # Assume compiler has greater than 6-character limit for identifier uniqueness. */

//!
//! \brief Return a uint8_t pointer from a const uint8_t pointer, at the given offset.
uint8_t* get_uint8_from_uint8(uint8_t* const base, const int32_t offset);

//!
//! \brief Return a const uint8_t pointer from a const uint8_t pointer, at the given offset.
const uint8_t* get_cuint8_from_cuint8(const uint8_t* const base, const int32_t offset);

//!
//! \brief Returns the value at the given offset of the const uint8_t address.
uint8_t get_cuint8_value_from_cuint8(const uint8_t* const base, const int32_t offset); /*PRQA S 0776 # Assume compiler has greater than 6-character limit for identifier uniqueness. */

#endif

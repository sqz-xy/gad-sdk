#include "oxts/gal-c/oxts_pointers.h" /*PRQA S 0857 # ISO:C90 */ /*PRQA S 0816 # ISO:C90*/


//============================================================================================================

//!
//! \brief Return a char pointer from a uint8_t pointer, at the given offset.
char* get_char_ptr_from_uint8(uint8_t* const base, const int32_t offset) /*PRQA S 1503 */ /*PRQA S 1505  # function is used in gad_encode_csv.c, so Helix is wrong.*/
{
	return (char*)(&(base[offset]));
}

//============================================================================================================

//!
//! \brief Return a const char pointer from a const uint8_t pointer, at the given offset.
const char* get_cchar_ptr_from_cuint8(const uint8_t* const base, const int32_t offset)
{
	return (const char*)(&(base[offset]));
}

//============================================================================================================

//!
//! \brief Return a char pointer from a char pointer, at the given offset.
char* get_char_ptr_from_char(char* const base, const int32_t offset) /*PRQA S 1503 */ /*PRQA S 1505  # function is used in errors.c, so Helix is wrong.*/
{
	return (char*)(&(base[offset]));
}

//============================================================================================================

//!
//! \brief Return a uint8_t pointer from a const uint_ut pointer, at the given offset.
const uint8_t* get_cuint8_from_cuint8(const uint8_t* const base, const int32_t offset)
{
	return (const uint8_t*)(&(base[offset]));
}

//============================================================================================================

//!
//! \brief Return a uint8_t pointer from a const uint8_t pointer, at the given offset.
uint8_t* get_uint8_from_uint8(uint8_t* const base, const int32_t offset)
{
	return (uint8_t*)(&(base[offset]));
}

//============================================================================================================

//!
//! \brief Returns the value at the given offset of the const uint8_t address.
uint8_t get_cuint8_value_from_cuint8(const uint8_t* const base, const int32_t offset)
{
	return base[offset];
}

//============================================================================================================

//!
//! \brief Return a void pointer from a uint8_t pointer, at the given offset.
void* get_void_from_cuint8(uint8_t* const base, const int32_t offset)
{
	return (void*)(&base[offset]);
}

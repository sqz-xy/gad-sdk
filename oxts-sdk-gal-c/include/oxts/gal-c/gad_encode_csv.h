#ifndef GAD_ENCODE_CSV_H
#define GAD_ENCODE_CSV_H

#include "oxts/gal-c/gad_defines.h"
#include "oxts/gal-c/gad_struct.h"

#ifdef OXTS_ENABLE_STDIO

/** Opens the .gad file and prints the header to the csv gad file.
 * param file_ptr Pointer to the file to be written t
 */
int32_t init_gad_output_file(FILE* file_ptr);

/** Encode data from GEN_3D to csv format for writing to file.
 * param out_string Char array to be populated with GEN_3D data
 * param offset Current offset into output buffer
 * param gen_3d_data Data to be written to the output string.
 */
int32_t encode_gen_3d_to_csv(uint8_t* out_string, int32_t * offset_ptr, const GEN_3D* gen_3d_data);
/** Encode data from GEN_AIDING_DATA to csv format for writing to file. 
 * param out_string Char array to be populated with GEN_AIDING_DATA.
 * param data GEN_AIDING_DATA to be written to the output string.
*/
int32_t encode_gad_to_csv(uint8_t * out_string, int32_t * offset_ptr, const GEN_AIDING_DATA* data);

/** Writes the generic aiding data in data to file at file_ptr
 * param file_ptr Pointer to the file to write data to. 
 * param data Generic aiding data to be written.
 */
int32_t write_gad_to_csv(FILE* file_ptr, const GEN_AIDING_DATA* data);

#endif

#endif // GAD_ENCODE_CSV_H

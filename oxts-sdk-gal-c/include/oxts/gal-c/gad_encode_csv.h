#ifndef GAD_CSV_H
#define GAD_CSV_H

#include "oxts/gal-c/gad_defines.h"
#include "oxts/gal-c/gad_struct.h"


#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*
    associated the file handler to the gad engine file handler and prints the header to the csv gad file

    params:
    * file_ptr - pointer to file you're writing csv to 
*/
int init_gad_output_file(FILE* file_ptr);


int encode_gen_3d_to_csv(unsigned char * out_string, GEN_3D* gen_3d_data);

/*
    writes the generic aiding data in data to file at file_ptr

    params:
    * file_ptr - pointer to file you're writing csv to 
    * data - generic aiding data being written
*/
int write_gad_to_csv(FILE* file_ptr, GEN_AIDING_DATA* data);


#ifdef __cplusplus
}
#endif // __cplusplus
#endif // GAD_CSV_H
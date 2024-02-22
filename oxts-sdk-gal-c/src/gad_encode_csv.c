#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "oxts/gal-c/gad_encode_csv.h" /*PRQA S 0857 # ISO:C90 */ /*PRQA S 0816 # ISO:C90*/
#include "oxts/gal-c/BasicCasts.h" /*PRQA S 0816 # ISO:C90*/
#include "oxts/gal-c/oxts_pointers.h" /*PRQA S 0816 # ISO:C90*/

#ifdef OXTS_ENABLE_STDIO

#define MAX_BUFF 1024U

//=====================================
// Forward Declarations
int32_t print_gen_3d_header(FILE* file_ptr);
int32_t write_gen_3d(FILE* file_ptr, const GEN_3D* gen_3d_data);

//============================================================================================================
int32_t print_gen_3d_header(FILE* file_ptr)
{
#ifdef EXTRA_CHECKS
    if (file_ptr == NULL)
    {
        oxts_error(1, "NULL encountered instead of pointer to file");
        return -1;
    }
#endif

    int32_t ec = 0;
    if (fprintf(file_ptr, "mode,x_type,x[0],x[1],x[2],v_type,v[0],v[1],v[2],v[3],v[4],v[5],") < 0) /*PRQA S 5124 # Standard I/O*/
    {
        ec = -1;
    }
    return ec;
}



int32_t init_gad_output_file(FILE* file_ptr)
{
#ifdef EXTRA_CHECKS
    if (gad_engine_file_ptr == NULL)
    {
        oxts_error(1, "NULL encountered instead of pointer to file");
        return -1;
    }
#endif
    int32_t ec;

    // write generic aiding struct header to csv file
    if ((fprintf(file_ptr, "#ver,type,stream ID,") < 0)) /*PRQA S 5124 # Standard I/O*/
    {   ec = -1; }
    else if (fprintf(file_ptr, "val_valid,") < 0) /*PRQA S 5124 # Standard I/O*/
    {   ec = -1; }
    else
    {
        ec = print_gen_3d_header(file_ptr);
        if (ec != 0) { }
        else if (fprintf(file_ptr, "time_valid,") < 0) /*PRQA S 5124 # Standard I/O*/
        {   ec = -1; }
        else
        {
            ec = print_gen_3d_header(file_ptr);
            if (ec != 0) { }
            else if (fprintf(file_ptr, "acq_valid,") < 0) /*PRQA S 5124 # Standard I/O*/
            {   ec = -1; }
            else if (fprintf(file_ptr, "acq_time,") < 0) /*PRQA S 5124 # Standard I/O*/
            {   ec = -1; }
            else if (fprintf(file_ptr, "loc_valid,") < 0) /*PRQA S 5124 # Standard I/O*/
            {   ec = -1; }
            else
            {
                ec = print_gen_3d_header(file_ptr);
                if (ec != 0) { }
                else if (fprintf(file_ptr, "res1_valid,") < 0) /*PRQA S 5124 # Standard I/O*/
                {   ec = -1; }
                else 
                {
                    ec = print_gen_3d_header(file_ptr);
                    if (ec != 0) { }
                    else if (fprintf(file_ptr, "res2_valid,") < 0) /*PRQA S 5124 # Standard I/O*/
                    {   ec = -1; }
                    else 
                    {
                        ec = print_gen_3d_header(file_ptr);
                        if (ec != 0) { }
                        else if (fprintf(file_ptr, "\n") < 0) { } /*PRQA S 5124 # Standard I/O*/
                        else if (fflush(file_ptr) != 0) /*PRQA S 5124 # Standard I/O*/
                        {   ec = -1; }
                        else { ec = 0; }
                    }
                }
            }
        }
    }
    return ec;
}
//============================================================================================================
//! \brief writes the contents of the GEN_3D to csv

int32_t encode_gen_3d_to_csv(uint8_t * out_string, int32_t * offset_ptr, const GEN_3D* gen_3d_data)
{
    int32_t ec = 0;
    *offset_ptr += sprintf(get_char_ptr_from_uint8(out_string, *offset_ptr), 
        "%d,%d,%.12f,%.12f,%.12f,%d,%.12f,%.12f,%.12f,%.12f,%.12f,%.12f,",
        gen_3d_data->mode,
        gen_3d_data->x_type,
        gen_3d_data->x[0], gen_3d_data->x[1], gen_3d_data->x[2],
        gen_3d_data->v_type,
        gen_3d_data->v[0], gen_3d_data->v[1], gen_3d_data->v[2], gen_3d_data->v[3], gen_3d_data->v[4], gen_3d_data->v[5]);
    if (*offset_ptr < 0)
    {
        ec = -1;
    }
    return ec;
}


int32_t write_gen_3d(FILE* file_ptr, const GEN_3D* gen_3d_data)
{
    uint8_t out_string[MAX_BUFF];
    int32_t offset = 0;
    int32_t * offset_ptr = &offset;
    int32_t ec;
    (void)memset(out_string, 0, MAX_BUFF);
    ec = encode_gen_3d_to_csv(out_string,offset_ptr,gen_3d_data);
    if (ec == 0)
    {
        (void)fputs(get_char_ptr_from_uint8(out_string, 0),file_ptr); /*PRQA S 5124 # Standard I/O*/
    }
    return ec;
}


/*

*/
int32_t encode_gad_to_csv(uint8_t * out_string, int32_t * offset_ptr, const GEN_AIDING_DATA* data)
{
#ifdef EXTRA_CHECKS
    if (out_string == NULL)
    {
        oxts_error(1, "NULL encountered instead of pointer to array");
        return -1;
    }
    if (data == NULL)
    {
        oxts_error(1, "NULL encountered instead of pointer to generic aiding structure");
        return -1;
    }
#endif

    int32_t ec = 0; // 0 means no errors encountered

    // write ver
    *offset_ptr +=sprintf(get_char_ptr_from_uint8(out_string, *offset_ptr), "%d,", 0);
    if (*offset_ptr < 0)
    {   ec = -1; }
    // write type
    if (ec == 0)
    {
        *offset_ptr +=sprintf(get_char_ptr_from_uint8(out_string, *offset_ptr), "%d,", data->type);
	    if (*offset_ptr < 0) { ec = -1; }
    }
    // write stream ID
    if (ec == 0)
    {
        *offset_ptr +=sprintf(get_char_ptr_from_uint8(out_string, *offset_ptr), "%d,", data->stream_id);
        if (*offset_ptr < 0) { ec = -1; }
    }
    // write val
    if (ec == 0)
    {
        *offset_ptr +=sprintf(get_char_ptr_from_uint8(out_string, *offset_ptr), "%d,", data->val_valid);
        ec = (*offset_ptr < 0) ? -1 : 0;
    }
    if (ec == 0)
    {
        if (data->val_valid != 0U) {
            ec = encode_gen_3d_to_csv(out_string, offset_ptr, &data->val);
        }
        else {
            *offset_ptr += sprintf(get_char_ptr_from_uint8(out_string, *offset_ptr), ",,,,,,,,,,,,");
            ec = (*offset_ptr < 0) ? -1 : 0;
        }
    }
    // write time
    if (ec == 0)
    {
        *offset_ptr += sprintf(get_char_ptr_from_uint8(out_string, *offset_ptr), "%d,", data->time_valid);
        if (*offset_ptr < 0) {
            ec = -1;
        }
    }
    if (ec == 0)
    {
        ec = encode_gen_3d_to_csv(out_string, offset_ptr, &data->time);
        if ((ec == 0) && (data->time_valid != 0U))
        {
            *offset_ptr += sprintf(get_char_ptr_from_uint8(out_string, *offset_ptr), ",,,,,,,,,,,,");
            ec = (*offset_ptr < 0) ? -1 : 0;
        }
    }
    // write acq_time
    if (ec == 0)
    {
        *offset_ptr += sprintf(get_char_ptr_from_uint8(out_string, *offset_ptr), "%d,", data->acq_valid);
        if (*offset_ptr < 0)
        {
            ec = -1;
        }
    }
    if (ec == 0)
    {
        if (data->acq_valid != 0U)
        {
            *offset_ptr += sprintf(get_char_ptr_from_uint8(out_string, *offset_ptr), "%u,", data->acq);
            ec = (*offset_ptr < 0) ? -1 : 0;
        }
        else
        {
            *offset_ptr += sprintf(get_char_ptr_from_uint8(out_string, *offset_ptr), ",");
            ec = (*offset_ptr < 0) ? -1 : 0;
        }
    }
    // write loc
    if (ec == 0)
    {
        *offset_ptr += sprintf(get_char_ptr_from_uint8(out_string, *offset_ptr), "%d,", data->loc_valid);
        if (*offset_ptr < 0) {
            ec = -1;
        }
    }
    if (ec == 0)
    {
        if (data->loc_valid != 0U) {
            ec = encode_gen_3d_to_csv(out_string, offset_ptr, &data->loc);
        }
        else
        {
            *offset_ptr += sprintf(get_char_ptr_from_uint8(out_string, *offset_ptr), ",,,,,,,,,,,,");
            ec = (*offset_ptr < 0) ? -1 : 0;
        }
    }
    // write res1
    if (ec == 0)
    {
        *offset_ptr += sprintf(get_char_ptr_from_uint8(out_string, *offset_ptr), "%d,", data->res1_valid);
        if (*offset_ptr < 0)
        {
            ec = -1;
        }
    }
    if (ec == 0)
    {
        if (data->res1_valid != 0U)
        {
            ec = encode_gen_3d_to_csv(out_string, offset_ptr, &data->res1);
        }
        else
        {
            *offset_ptr += sprintf(get_char_ptr_from_uint8(out_string, *offset_ptr), ",,,,,,,,,,,,");
            ec = (*offset_ptr < 0) ? -1 : 0;
        }
    }
    // write res2
    if (ec == 0)
    {
        *offset_ptr += sprintf(get_char_ptr_from_uint8(out_string, *offset_ptr), "%d,", data->res2_valid);
        if (*offset_ptr < 0)
        {
            ec = -1;
        }
    }
    if (ec == 0)
    {
        if (data->res2_valid != 0U) {
            ec = encode_gen_3d_to_csv(out_string, offset_ptr, &data->res2);
        }
        else
        {
            *offset_ptr += sprintf(get_char_ptr_from_uint8(out_string, *offset_ptr), ",,,,,,,,,,,,");
            ec = (*offset_ptr < 0) ? -1 : 0;
        }
    }
    if (ec == 0)
    {
        *offset_ptr += sprintf(get_char_ptr_from_uint8(out_string, *offset_ptr), "\n");
        if (*offset_ptr < 0)
        {
            ec = -1;
        }
    }
    return ec;
}


int32_t write_gad_to_csv(FILE* file_ptr, const GEN_AIDING_DATA* data)
{
    int32_t ec;
    uint8_t out_string[MAX_BUFF];
    int32_t offset = 0;
#ifdef EXTRA_CHECKS
    if (file_ptr == NULL)
    {
        oxts_error(1, "NULL encountered instead of pointer to file");
        ec = -1;
    }
    else if (data == NULL)
    {
        oxts_error(1, "NULL encountered instead of pointer to generic aiding structure");
        ec = -1;
    }
    else
    {
#endif 
        (void)memset(out_string, 0, MAX_BUFF);
        ec = encode_gad_to_csv(out_string, &offset, data);
        if (ec != 0) {}
        else
        {
            (void)fputs(get_char_ptr_from_uint8(out_string, 0), file_ptr); /*PRQA S 5124 # Standard I/O*/
            (void)fflush(file_ptr); /*PRQA S 5124 # Standard I/O*/
        }
#ifdef EXTRA_CHECKS
    }
#endif
   return ec;
}

#endif

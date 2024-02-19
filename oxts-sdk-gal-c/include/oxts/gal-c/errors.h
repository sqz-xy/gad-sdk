//============================================================================================================
//!
//! The software is protected by copyright of Oxford Technical Solutions.
//! Copyright (C) 2017 Oxford Technical Solutions - http://www.oxts.com
//!
//! Redistribution and use in source and binary forms, with or without modification, are only permitted with
//! the specific prior written permission of Oxford Technical Solutions.
//!
//! $LastChangedDate: 2017-04-26 14:43:57 +0100 (Wed, 26 Apr 2017) $
//! $LastChangedRevision: 23461 $
//! $LastChangedBy: sgratrix $
//!
//! \file errors.h
//!
//! Header file for errors.c
//!
//============================================================================================================


#ifndef LIBRARY_ERRORS_H
#define LIBRARY_ERRORS_H

#include <stdlib.h>
#include <stdint.h>

#if (defined DLL_VERSION)
#define FP_IS_DEFINED 0
#define SP_IS_DEFINED 1
char sp[1000];
#elif (defined OXTS_ENABLE_STDIO)
#define FP_IS_DEFINED 1
#define SP_IS_DEFINED 0
//fp = stderr;
#else
#define FP_IS_DEFINED 0
#define SP_IS_DEFINED 0
#endif

#if(FP_IS_DEFINED || SP_IS_DEFINED)

#define oxts_notice(num, level, msg) (void)report_notice(num, level, __FILE__, __LINE__, __FUNCTION__, msg)
#define oxts_warn(num, msg)          (void)report_notice(num,     0, __FILE__, __LINE__, __FUNCTION__, msg)
#define oxts_error(num, msg)         (void)report_notice(num,     1, __FILE__, __LINE__, __FUNCTION__, msg)
#define oxts_fatal(num, msg)         (void)report_notice(num,     2, __FILE__, __LINE__, __FUNCTION__, msg)
#define oxts_kill(num, msg)          (void)report_notice(num,     3, __FILE__, __LINE__, __FUNCTION__, msg)

extern int32_t  report_error        (int32_t err_num, int32_t err_level, const char *file_id,              const char *func_id, const char *err_msg);
extern int32_t  report_debug_notice (int32_t err_num, int32_t err_level, const char *file_id, int32_t line_id, const char *func_id, const char *err_msg);
extern int32_t  report_notice       (int32_t err_num, int32_t err_level, const char *file_id, int32_t line_id, const char *func_id, const char *err_msg);

#endif

#ifdef DLL_VERSION
#include <windows.h>
extern int32_t error_set_windows_handle(HWND handle);
#define  WM_POST_PROCESSING_ERROR		(0x05ff)
#endif

#endif

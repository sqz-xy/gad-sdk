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


#define ERRORS_DEV_ID "110413"  //!< Development identification.


#include <stdlib.h>
#ifdef LIB__RUNNER_FEATURE_THREADS
#include "Lib_Runner.h"
#else
#define LIB__RUNNER_TLS(TYPE, VAR, VAL) TYPE VAR = VAL;
#endif


#define OXTS_MESSAGE_CAPACITY 128
#define OXTS_MESSAGE_LENGTH   1024
typedef struct
{
	         int  buffered;
	volatile int  head;
	volatile int  tail;
	         char buffer[OXTS_MESSAGE_CAPACITY][OXTS_MESSAGE_LENGTH];

} OXTS_MESSAGE;

#define oxts_stdout(format, ...)     report_message(0, format, __VA_ARGS__)
#define oxts_stderr(format, ...)     report_message(1, format, __VA_ARGS__)

#define oxts_notice(num, level, msg) report_notice(num, level, __FILE__, __LINE__, __FUNCTION__, msg)
#define oxts_warn(num, msg)          report_notice(num,     0, __FILE__, __LINE__, __FUNCTION__, msg)
#define oxts_error(num, msg)         report_notice(num,     1, __FILE__, __LINE__, __FUNCTION__, msg)
#define oxts_fatal(num, msg)         report_notice(num,     2, __FILE__, __LINE__, __FUNCTION__, msg)
#define oxts_kill(num, msg)          report_notice(num,     3, __FILE__, __LINE__, __FUNCTION__, msg)

#define oxts_append(file, format, ...)                                 \
	do {                                                               \
		static LIB__RUNNER_TLS(const char *, mode, "wt")               \
		report_append(mode, file, format, __VA_ARGS__);                \
		mode = "at";                                                   \
	} while (0)

#define oxts_append_prefix(prefix, file, format, ...)                  \
	do {                                                               \
		static LIB__RUNNER_TLS(const char *, mode, "wt")               \
		report_append_prefix(mode, prefix, file, format, __VA_ARGS__); \
		mode = "at";                                                   \
	} while (0)

#define oxts_appendb_prefix(prefix, ptr, size, count, file)            \
	do {                                                               \
		static LIB__RUNNER_TLS(const char *, mode, "wb")               \
		FILE *fp = NULL;                                               \
		char fn[512] = "";                                             \
		size_t plen = prefix ? strlen(prefix) : 0;                     \
		if (plen) strcat(fn, prefix);                                  \
		strcat(fn, file);                                              \
		if ((fp = fopen(fn, mode)))                                    \
		{                                                              \
			fwrite (ptr, size, count, fp);                             \
			fclose (fp);                                               \
		}                                                              \
		mode = "ab";                                                   \
	} while (0)

#ifdef __cplusplus
extern "C"
{
#endif

extern void          oxts_message_reset(OXTS_MESSAGE *oxts_message);
extern OXTS_MESSAGE *oxts_message_current();
extern OXTS_MESSAGE *oxts_message_lookup(int id);
extern int           oxts_message_get(OXTS_MESSAGE *m, char *buffer, size_t length);

extern int  report_error        (int err_num, int err_level, const char *file_id,              const char *func_id, const char *err_msg);
extern int  report_debug_notice (int err_num, int err_level, const char *file_id, int line_id, const char *func_id, const char *err_msg);
extern int  report_notice       (int err_num, int err_level, const char *file_id, int line_id, const char *func_id, const char *err_msg);
extern int  report_message      (int type, const char *format, ...);
extern void report_append       (const char *mode,                     const char *file, const char *format, ...);
extern void report_append_prefix(const char *mode, const char *prefix, const char *file, const char *format, ...);

#ifdef __cplusplus
}
#endif


#ifdef DLL_VERSION
#include <windows.h>
extern int error_set_windows_handle(HWND handle);
#define  WM_POST_PROCESSING_ERROR		(0x05ff)
#endif


#endif

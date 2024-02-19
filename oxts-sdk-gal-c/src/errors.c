//============================================================================================================
//!
//! The software is protected by copyright of Oxford Technical Solutions.
//! Copyright (C) 2017 Oxford Technical Solutions - http://www.oxts.com
//!
//! Redistribution and use in source and binary forms, with or without modification, are only permitted with
//! the specific prior written permission of Oxford Technical Solutions.
//!
//! LastChangedDate: 2017-04-26 14:43:57 +0100 (Wed, 26 Apr 2017)
//! LastChangedRevision: 23461
//! LastChangedBy: sgratrix
//!
//! \file errors.c
//!
//! \brief Functions for the handling and reporting of errors.
//!
//============================================================================================================


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include "oxts/gal-c/errors.h" /*PRQA S 0857 # ISO:C90 */ /*PRQA S 0816 # ISO:C90*/
#include "oxts/gal-c/oxts_pointers.h" /*PRQA S 0816 # ISO:C90*/


#ifdef OXTS_DEBUG
#define EXTRA_CHECKS
#endif


#ifdef DLL_VERSION
static HWND error_handle = NULL;  //!< The error message handle is a static variable.
#endif

#if (FP_IS_DEFINED || SP_IS_DEFINED)

#define NUM_KNOWN_ERRORS   12
#define NUM_ERROR_LEVELS   4

//============================================================================================================
//! \brief Report error function (backwards compatibility).
//!
//! \warning Depreciated.

int32_t report_error(int32_t err_num, int32_t err_level, const char *file_id, const char *func_id, const char *err_msg)
{
	return report_notice(err_num, err_level, file_id, -1, func_id, err_msg);
}


//============================================================================================================
//! \brief Calls report notice only on debug builds (e.g., to be called from third party source code such as GNSS toolkit).
//!

int32_t report_debug_notice(int32_t err_num, int32_t err_level, const char *file_id, int32_t line_id, const char *func_id, const char *err_msg) /*PRQA S 3206 # Unused parameter. */
{
#ifdef OXTS_DEBUG
   return report_notice (err_num, err_level, file_id, line_id, func_id, err_msg);
#else
   return 0;
#endif
}


//============================================================================================================
//! \brief Report error function.
//!
//! For now we don't care if line is negative because for backwards compatibility this may occur often.
int32_t report_notice(int32_t err_num, int32_t err_level, const char *file_id, int32_t line_id, const char *func_id, const char *err_msg)
{
	//============================================================================================================
	//! \brief Error messages.

	static const char * const error_messages[NUM_KNOWN_ERRORS+1] =
	{
		"successful operation",                                 // 0
		"unable to allocate required memory space",             // 1
		"NULL pointer encountered",                             // 2
		"numerical argument out of range",                      // 3
		"insufficient memory space allocated",                  // 4
		"ill-conditioned operation",                            // 5
		"unable to open file",                                  // 6
		"incorrect file format",                                // 7
		"internal inconsistency",                               // 8
		"protocol error",                                       // 9
		"file system error",                                    // 10
		"code not written yet",                                 // 11
		"hardware error",                                       // 12
	};
	//============================================================================================================
	//! \brief Error levels.

	static const char * const error_levels[NUM_ERROR_LEVELS] =
	{
		"Warning",             // 0
		"Error",               // 1
		"Fatal error",         // 2
		"Killed"               // 3
	};
#ifdef EXTRA_CHECKS
	if ((err_num < 0)||(err_num > NUM_KNOWN_ERRORS))
	{
		oxts_warn(3, "unknown error number reported");
		if (err_msg == NULL)
		{
			oxts_error(2, "missing error message string");
			return 2;
		}
	}

	if ((err_level < 0)||(err_level >= NUM_ERROR_LEVELS))
		oxts_warn(3, "unknown error level");
	if (file_id == NULL)
		oxts_warn(2, "no file identifier specified");
	if (func_id == NULL)
		oxts_warn(2, "no function identifier specified");
#endif
	const char *file_id_without_path = file_id;
	// if error level is out of range, set it to value in range
	int32_t correct_err_level = err_level;
 	if ((err_level < 0)||(err_level >= NUM_ERROR_LEVELS))
	{
		correct_err_level = 1; // assume a standard error
	}
	// Strip the path from the file_id string
	if (file_id != NULL)
	{
		size_t off, file_id_off = 0;
		for (off = 0; file_id[off] != '\0'; ++off)
		{
			if ((file_id[off] == '\\') || (file_id[off] == '/')) { ++file_id_off; }
		}
		file_id_without_path = &(file_id[file_id_off]);
	}

	{
		// Note: FP_IS_DEFINED, SP_IS_DEFINED used rather than checking pointers as they will violate MISRA's "Dead Code" rule.
#if FP_IS_DEFINED
		FILE *fp = stderr;
		(void)fprintf(fp, "*** %s ", error_levels[correct_err_level]); /*PRQA S 5124 # Standard I/O*/

		if ((func_id == NULL) || (func_id[0] == '\0')) { (void)fprintf(fp, "in unknown function "); } /*PRQA S 5124 # Standard I/O*/
		else                                       { (void)fprintf(fp, "in function %s() ", func_id); } /*PRQA S 5124 # Standard I/O*/

		if (line_id < 0)                           { (void)fprintf(fp, "at unknown line "); } /*PRQA S 5124 # Standard I/O*/
		else                                       { (void)fprintf(fp, "at line %d ", line_id); } /*PRQA S 5124 # Standard I/O*/

		if ((file_id_without_path == NULL) || (file_id_without_path[0] == '\0')) { (void)fprintf(fp, "of unknown file ***\n"); } /*PRQA S 5124 # Standard I/O*/
		else                                       { (void)fprintf(fp, "of file %s ***\n", file_id_without_path); } /*PRQA S 5124 # Standard I/O*/

		if (err_msg == NULL)                       { (void)fprintf(fp, "--> %s\n", error_messages[err_num]); } /*PRQA S 5124 # Standard I/O*/
		else                                       { (void)fprintf(fp, "--> %s\n", err_msg); } /*PRQA S 5124 # Standard I/O*/
#endif
#if SP_IS_DEFINED
		char sp[1000];
		(void)sprintf(sp, "%s ", error_levels[correct_err_level]);

		if ((func_id == NULL) || (func_id[0] == '\0')) { (void)sprintf(get_char_ptr_from_char(sp, (int32_t)strlen(sp)), "in unknown function "); }
		else                                       { (void)sprintf(get_char_ptr_from_char(sp, (int32_t)strlen(sp)), "in function %s() ", func_id); }

		if (line_id < 0)                           { (void)sprintf(get_char_ptr_from_char(sp, (int32_t)strlen(sp)), "at unknown line "); }
		else                                       { (void)sprintf(get_char_ptr_from_char(sp, (int32_t)strlen(sp)), "at line %d ", line_id); }

		if ((file_id_without_path == NULL) || (file_id_without_path[0] == '\0')) { (void)sprintf(get_char_ptr_from_char(sp, (int32_t)strlen(sp)), "of unknown file: "); }
		else                                       { (void)sprintf(get_char_ptr_from_char(sp, (int32_t)strlen(sp)), "of file %s: ", file_id_without_path); }

		if (err_msg == NULL)                       { (void)sprintf(get_char_ptr_from_char(sp, (int32_t)strlen(sp)), "%s", error_messages[err_num]); }
		else                                       { (void)sprintf(get_char_ptr_from_char(sp, (int32_t)strlen(sp)), "%s", err_msg); }
#endif
#if (defined DLL_VERSION)
		if (error_handle != NULL)
		{
			SendMessage(error_handle, WM_POST_PROCESSING_ERROR, (WPARAM)(strlen(sp)), (LPARAM)sp);
		}
#elif (defined OXTS_ENABLE_STDIO)
		(void)fflush(stderr); /*PRQA S 5124 # Standard I/O*/
		(void)fflush(stdout); /*PRQA S 5124 # Standard I/O*/
#endif
	}

	return 0;
}
#endif

#ifdef DLL_VERSION

//============================================================================================================
//! \brief This function is only available when Windows messaging is possible.

int32_t error_set_windows_handle(HWND handle)
{
   // Update my error handle
   error_handle = handle;
   // Indicate success
   return 0;
}

#endif

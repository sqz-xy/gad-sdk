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
//! \file errors.c
//!
//! \brief Functions for the handling and reporting of errors.
//!
//============================================================================================================


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>
#include "oxts/core/errors.h"
#ifdef LIB__RUNNER_FEATURE_THREADS
#include "Lib_Runner.h"
#endif


#ifdef OXTS_DEBUG
#define EXTRA_CHECKS
#endif


#ifdef DLL_VERSION
static HWND error_handle = NULL;  //!< The error message handle is a static variable.
#endif

#ifdef LIB__RUNNER_FEATURE_THREADS
#define OXTS_MESSAGE_CONTEXT_TOTAL 5
static OXTS_MESSAGE oxts_message_contexts[OXTS_MESSAGE_CONTEXT_TOTAL];
#endif


#define NUM_KNOWN_ERRORS   12
#define NUM_ERROR_LEVELS   4


//============================================================================================================
//! \brief Error messages.

const char *error_messages[NUM_KNOWN_ERRORS+1] =
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

const char *error_levels[NUM_ERROR_LEVELS] =
{
	"Warning",             // 0
	"Error",               // 1
	"Fatal error",         // 2
	"Killed"               // 3
};


//============================================================================================================
//! \brief Reset the messages.
//!
//! \todo Upgrade this to the standard blended coding style.

void oxts_message_reset(OXTS_MESSAGE *oxts_message)
{
	if (oxts_message)
	{
		oxts_message->buffered = 0;  // Default is not to use the bufferes
		oxts_message->head = 0;
		oxts_message->tail = 0;
	}
}


//============================================================================================================
//! \brief Get the current message context.

OXTS_MESSAGE *oxts_message_current()
{
#ifdef LIB__RUNNER_FEATURE_THREADS
	int id = get_context();

	if (id >= 0 && id <= OXTS_MESSAGE_CONTEXT_TOTAL)
	{
		return &oxts_message_contexts[id];
	}
#endif

	return NULL;
}


//============================================================================================================
//! \brief Get a message context.

OXTS_MESSAGE *oxts_message_lookup(int id)
{
#ifdef LIB__RUNNER_FEATURE_THREADS
	if (id >= 0 && id <= OXTS_MESSAGE_CONTEXT_TOTAL)
	{
		return &oxts_message_contexts[id];
	}
#endif

	return NULL;
}


//============================================================================================================
//! \brief Get the next error message out.

int oxts_message_get(OXTS_MESSAGE *m, char *buffer, size_t length)
{
	if (m)
	{
		int t = m->tail;  // hope atomic
		int h = m->head;  // hope atomic

		assert(t                         <= h);   // equal means empty, less mean non-empty.
		assert(t + OXTS_MESSAGE_CAPACITY >= h);   // equal means full, greater means non-full.

		if (t < h)
		{
			if (buffer && length)
			{
				strncpy(buffer, m->buffer[t % OXTS_MESSAGE_CAPACITY], length-1);
				buffer[length-1] = '\0';
			}

			t++;

			m->tail = t;  // hope atomic

			return 1;
		}

		return 0;
	}
	else
	{
		if (buffer && length) buffer[0] = '\0';

		return 0;
	}
}


//============================================================================================================
//! \brief Report error function (backwards compatibility).
//!
//! \warning Depreciated.

int report_error(int err_num, int err_level, const char *file_id, const char *func_id, const char *err_msg)
{
	return report_notice(err_num, err_level, file_id, -1, func_id, err_msg);
}


//============================================================================================================
//! \brief Calls report notice only on debug builds (e.g., to be called from third party source code such as GNSS toolkit).
//!

int report_debug_notice(int err_num, int err_level, const char *file_id, int line_id, const char *func_id, const char *err_msg)
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

int report_notice(int err_num, int err_level, const char *file_id, int line_id, const char *func_id, const char *err_msg)
{
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

	// if error level is out of range, set it to value in range
 	if ((err_level < 0)||(err_level >= NUM_ERROR_LEVELS))
		err_level = 1; // assume a standard error

	// Strip the path from the file_id string
	if (file_id != NULL)
	{
		const char *f;
		for (f = file_id; *f != '\0'; ++f)
		{
			if (*f == '\\' || *f == '/') file_id = f+1;
		}
	}

	{
#if (defined LIB__RUNNER_FEATURE_THREADS)
		char  buffer[1000];
		OXTS_MESSAGE *m = oxts_message_current();
		FILE *fp = (m && m->buffered) ? NULL   : stderr;     // If we cannot get a message context then
		char *sp = (m && m->buffered) ? buffer : NULL;       // simply default to printing to standard error.
#elif (defined DLL_VERSION)
		FILE *fp = NULL;
		char sp[1000];
#else
		FILE *fp = stderr;
		char *sp = NULL;
#endif

		if (fp)
		{
			fprintf(fp, "*** %s ", error_levels[err_level]);

			if (func_id == NULL || func_id[0] == '\0') fprintf(fp, "in unknown function ");
			else                                       fprintf(fp, "in function %s() ", func_id);

			if (line_id < 0)                           fprintf(fp, "at unknown line ");
			else                                       fprintf(fp, "at line %d ", line_id);

			if (file_id == NULL || file_id[0] == '\0') fprintf(fp, "of unknown file ***\n");
			else                                       fprintf(fp, "of file %s ***\n", file_id);

			if (err_msg == NULL)                       fprintf(fp, "--> %s\n", error_messages[err_num]);
			else                                       fprintf(fp, "--> %s\n", err_msg);
		}

		if (sp)
		{
			sprintf(sp, "%s ", error_levels[err_level]);

			if (func_id == NULL || func_id[0] == '\0') sprintf(sp + strlen(sp), "in unknown function ");
			else                                       sprintf(sp + strlen(sp), "in function %s() ", func_id);

			if (line_id < 0)                           sprintf(sp + strlen(sp), "at unknown line ");
			else                                       sprintf(sp + strlen(sp), "at line %d ", line_id);

			if (file_id == NULL || file_id[0] == '\0') sprintf(sp + strlen(sp), "of unknown file: ");
			else                                       sprintf(sp + strlen(sp), "of file %s: ", file_id);

			if (err_msg == NULL)                       sprintf(sp + strlen(sp), "%s", error_messages[err_num]);
			else                                       sprintf(sp + strlen(sp), "%s", err_msg);
		}

#if (defined LIB__RUNNER_FEATURE_THREADS)
		if (m && sp)
		{
			int j, t, h;

			for (j=0; j<100; ++j)
			{
				t = m->tail;  // hope atomic
				h = m->head;  // hope atomic

				assert(t                         <= h);   // equal means empty, less mean non-empty.
				assert(t + OXTS_MESSAGE_CAPACITY >= h);   // equal means full, greater means non-full.

				if (h - t < OXTS_MESSAGE_CAPACITY) break;

				sleeps(10);
			}

			if (h - t < OXTS_MESSAGE_CAPACITY)
			{
				strcpy(m->buffer[h % OXTS_MESSAGE_CAPACITY], sp);
				h++;

				m->head = h;  // hope atomic
			}
			else
			{
				// Drop message
				// printf("drop\n");
				// assert(0);
			}
		}
		if (err_level == 3)
		{
			exit(EXIT_FAILURE);
		}
#elif (defined DLL_VERSION)
		if (error_handle != NULL)
		{
			SendMessage(error_handle, WM_POST_PROCESSING_ERROR, (WPARAM)(strlen(sp)), (LPARAM)sp);
		}
#else
		fflush(stderr);
		fflush(stdout);
		if (err_level == 3)
		{
			exit(EXIT_FAILURE);
		}
#endif
	}

	return 0;
}


//============================================================================================================
//! \brief Report message function.

int report_message(int type, const char *format, ...)
{
	if (format)
	{
#if (defined LIB__RUNNER_FEATURE_THREADS)
		char  buffer[OXTS_MESSAGE_LENGTH];
		OXTS_MESSAGE *m = oxts_message_current();
		FILE *fp = (m && m->buffered) ? NULL   : (type ? stderr : stdout);  // If we can not get an message context then
		char *sp = (m && m->buffered) ? buffer : NULL;                      // simply default to printing to std err/out.
#else
		FILE *fp = stderr;
		char *sp = NULL;
#endif
		if (fp)
		{
			va_list args;
			va_start(args, format);
			vfprintf(fp, format, args);
			va_end(args);
			fprintf(fp, "\n");
			fflush(fp);
		}

		if (sp)
		{
			va_list args;
			va_start(args, format);
			vsnprintf(sp, OXTS_MESSAGE_LENGTH-1, format, args);
			sp[OXTS_MESSAGE_LENGTH-1] = '\0';
			va_end(args);
		}

#if (defined LIB__RUNNER_FEATURE_THREADS)
		if (m && sp)
		{
			int j, t, h;

			for (j=0; j<100; ++j)
			{
				t = m->tail;  // hope atomic
				h = m->head;  // hope atomic

				assert(t                         <= h);   // equal means empty, less mean non-empty.
				assert(t + OXTS_MESSAGE_CAPACITY >= h);   // equal means full, greater means non-full.

				if (h - t < OXTS_MESSAGE_CAPACITY) break;

				sleeps(10);
			}

			if (h - t < OXTS_MESSAGE_CAPACITY)
			{
				// strcpy should be fine here but we'll use strncpy anyway
				strncpy(m->buffer[h % OXTS_MESSAGE_CAPACITY], sp, OXTS_MESSAGE_LENGTH-1);
				m->buffer[h % OXTS_MESSAGE_CAPACITY][OXTS_MESSAGE_LENGTH-1] = '\0';
				h++;

				m->head = h;  // hope atomic
			}
			else
			{
				// Drop message
				// printf("drop\n");
				// assert(0);
			}
		}
#endif
	}

	return 0;
}


//============================================================================================================
//! \brief ...

void report_append(const char *mode, const char *file, const char *format, ...)
{
	if (mode && format)
	{
		if (file && file[0] != '\0')
		{
			FILE *fp = NULL;
			if ((fp = fopen(file, mode)))
			{
				va_list args;
				va_start(args, format);
				vfprintf(fp, format, args);
				va_end(args);
				fclose(fp);
			}
		}
	}
}


//============================================================================================================
//! \brief ...

void report_append_prefix(const char *mode, const char *prefix, const char *file, const char *format, ...)
{
	if (mode && format)
	{
		size_t plen = prefix ? strlen(prefix) : 0;
		size_t flen = file   ? strlen(file)   : 0;
		if (flen && (plen + flen) < 512)
		{
			FILE *fp = NULL;
			char fn[512] = "";
			if (plen) strcat(fn, prefix);
			strcat(fn, file);
			if ((fp = fopen(fn, mode)))
			{
				va_list args;
				va_start(args, format);
				vfprintf(fp, format, args);
				va_end(args);
				fclose(fp);
			}
		}
	}
}


#ifdef DLL_VERSION

//============================================================================================================
//! \brief This function is only available when Windows messaging is possible.

int error_set_windows_handle(HWND handle)
{
   // Update my error handle
   error_handle = handle;
   // Indicate success
   return 0;
}

#endif

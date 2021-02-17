//============================================================================================================
//!
//! The software is protected by copyright of Oxford Technical Solutions.
//! Copyright (C) 2017 Oxford Technical Solutions - http://www.oxts.com
//!
//! Redistribution and use in source and binary forms, with or without modification, are only permitted with
//! the specific prior written permission of Oxford Technical Solutions.
//!
//! $LastChangedDate: 2019-04-18 15:57:11 +0100 (Thu, 18 Apr 2019) $
//! $LastChangedRevision: 28052 $
//! $LastChangedBy: alambert $
//!
//! \file Lib_Compiler.c
//!
//! \brief Cross compiler support for everything other than basic types.
//!
//============================================================================================================


#if (defined __cplusplus)
#include <cstdlib>
#include <cctype>
#else
#include <stdlib.h>
#include <ctype.h>
#endif

#include "oxts/core/Lib_Compiler.h"

#if ((defined __cplusplus) && (OXTS_CC_BORLAND))
#include <math.hpp>
#endif


#if ((defined __cplusplus) && (OXTS_CC_BORLAND) && (defined OXTS_COMPILER_fallback_isnan))
//============================================================================================================
//! \brief ...
//!
//! \note Borland only defines IsNan in C++. To beable to use it from a C source linked into a C++ project we
//! need to introduce this C wrapper.

int fallback_isnan(double x)
{
	return IsNan(x);
}
#endif


#if ((defined __cplusplus) && (OXTS_CC_BORLAND) && (defined OXTS_COMPILER_fallback_isinf))
//============================================================================================================
//! \brief ...
//!
//! \note Borland only defines IsInfinite in C++. To beable to use it from a C source linked into a C++
//! project we need to introduce this C wrapper.

int fallback_isinf(double x)
{
	return IsInfinite(x);
}
#endif


#if ((defined __cplusplus) && (OXTS_CC_BORLAND) && (defined OXTS_COMPILER_fallback_isfinite))
//============================================================================================================
//! \brief ...
//!
//! \note Borland only defines IsInfinite and IsNan in C++. To beable to use it from a C source linked into a
//! C++ project we need to introduce this C wrapper.

int fallback_isfinite(double x)
{
	return !IsInfinite(x) && !IsNan(x);
}
#endif


#ifdef OXTS_COMPILER_fallback_strcasecmp
//============================================================================================================
//! \brief ...

int fallback_strcasecmp(const char *s1, const char *s2)
{
	while (tolower(*(unsigned char *) s1) == tolower(*(unsigned char *) s2))
	{
		if (*s1 == '\0' || *s2 == '\0') break;

		s1++;
		s2++;
	}

	return tolower(*(unsigned char *) s1) - tolower(*(unsigned char *) s2);
}
#endif


#ifdef OXTS_COMPILER_fallback_strncasecmp
//============================================================================================================
//! \brief ...

int fallback_strncasecmp(const char *s1, const char *s2, unsigned n)
{
	if (n == 0) return 0;

	while ((n-- != 0) && (tolower(*(unsigned char *) s1) == tolower(*(unsigned char *) s2)))
	{
		if(n == 0) return 0;
		else if (*s1 == '\0' || *s2 == '\0') break;

		s1++;
		s2++;
	}

	return tolower(*(unsigned char *) s1) - tolower(*(unsigned char *) s2);
}
#endif


#ifdef OXTS_COMPILER_fallback_strtok_r
//============================================================================================================
//! \brief A reentrant version of strtok.
//!
//! It gets the next token from string s, where tokens are strings separated by characters from delim. To get
//! the first token from s, strtok_r is called with s as its first parameter. Remaining tokens from s are
//! obtained by calling strtok_r with a null pointer for the first parameter. The string of delimiters, delim,
//! can differ from call to call.

char *fallback_strtok_r(char *s, const char *delim, char **last)
{
	char *spanp, *tok;
	int c, sc;

	if (s == NULL && (s = *last) == NULL) return (NULL);

cont:
	c = *s++;
	for (spanp = (char *)delim; (sc = *spanp++) != 0;)
	{
		if (c == sc) goto cont;
	}

	if (c == 0)
	{
		*last = NULL;
		return (NULL);
	}
	tok = s - 1;

	for (;;)
	{
		c = *s++;
		spanp = (char *)delim;
		do
		{
			if ((sc = *spanp++) == c)
			{
				if (c == 0) s = NULL; else s[-1] = '\0';
				*last = s;
				return (tok);
			}
		}
		while (sc != 0);
	}
}
#endif


#ifdef OXTS_COMPILER_fallback_strupr
//============================================================================================================
//! \brief Convert a string into upper case.

char *fallback_strupr(char *string)
{
	char *s;

	if (string) for (s = string; *s; ++s) *s = toupper((int)*s);

	return string;
}
#endif


#ifdef OXTS_COMPILER_fallback_strlwr
//============================================================================================================
//! \brief Convert a string into lower case.

char *fallback_strlwr(char *string)
{
	char *s;

	if (string) for (s = string; *s; ++s) *s = tolower((int)*s);

	return string;
}
#endif

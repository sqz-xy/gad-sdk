//============================================================================================================
//!
//! The software is protected by copyright of Oxford Technical Solutions.
//! Copyright (C) 2017 Oxford Technical Solutions - http://www.oxts.com
//!
//! Redistribution and use in source and binary forms, with or without modification, are only permitted with
//! the specific prior written permission of Oxford Technical Solutions.
//!
//! $LastChangedDate: 2018-08-10 14:12:02 +0100 (Fri, 10 Aug 2018) $
//! $LastChangedRevision: 26913 $
//! $LastChangedBy: alambert $
//!
//! \file Lib_Detect.h
//!
//! \brief Macros to detect which compiler and operating system.
//!
//============================================================================================================


#ifndef LIB__DETECT_HPP
#define LIB__DETECT_HPP


//============================================================================================================
// OXTS_CC: OXTS_CC_MSVC OXTS_CC_MINGW OXTS_CC_CYGWIN OXTS_CC_GCC OXTS_CC_QCC OXTS_CC_BORLAND OXTS_CC_TI

#if (_MSC_VER)
#if (defined(OXTS_CC_BORLAND) || defined(OXTS_CC_MINGW) || defined(OXTS_CC_CYGWIN) || defined(OXTS_CC_QCC) || defined(OXTS_CC_TI) || defined(OXTS_CC_GCC))
#error "Detected MSVC but you say something else"
#endif
#define OXTS_CC_MSVC
#elif __BORLANDC__
#if (defined(OXTS_CC_MSVC) || defined(OXTS_CC_MINGW) || defined(OXTS_CC_CYGWIN) || defined(OXTS_CC_QCC) || defined(OXTS_CC_TI) || defined(OXTS_CC_GCC))
#error "Detected BORLAND but you say something else"
#endif
#define OXTS_CC_BORLAND
#elif (__MINGW32__ || __MINGW64__)
#if (defined(OXTS_CC_MSVC) || defined(OXTS_CC_BORLAND) || defined(OXTS_CC_CYGWIN) || defined(OXTS_CC_QCC) || defined(OXTS_CC_TI) || defined(OXTS_CC_GCC))
#error "Detected MINGW but you say something else"
#endif
#define OXTS_CC_MINGW
#elif __CYGWIN32__
#if (defined(OXTS_CC_MSVC) || defined(OXTS_CC_BORLAND) || defined(OXTS_CC_MINGW) || defined(OXTS_CC_QCC) || defined(OXTS_CC_TI) || defined(OXTS_CC_GCC))
#error "Detected CYGWIN but you say something else"
#endif
#define OXTS_CC_CYGWIN
#elif defined(__QNX__)
#if (defined(OXTS_CC_MSVC) || defined(OXTS_CC_BORLAND) || defined(OXTS_CC_MINGW) || defined(OXTS_CC_CYGWIN) || defined(OXTS_CC_TI) || defined(OXTS_CC_GCC))
#error "Detected QCC but you say something else"
#endif
#define OXTS_CC_QCC
#elif defined(__TI_COMPILER_VERSION__)
#if (defined(OXTS_CC_MSVC) || defined(OXTS_CC_BORLAND) || defined(OXTS_CC_MINGW) || defined(OXTS_CC_CYGWIN) || defined(OXTS_CC_QCC) || defined(OXTS_CC_GCC))
#error "Detected TI but you say something else"
#endif
#define OXTS_CC_TI
#elif __GNUC__
#if (defined(OXTS_CC_MSVC) || defined(OXTS_CC_BORLAND) || defined(OXTS_CC_MINGW) || defined(OXTS_CC_CYGWIN) || defined(OXTS_CC_QCC) || defined(OXTS_CC_TI))
#error "Detected GCC but you say something else"
#endif
#define OXTS_CC_GCC
#else
#error "Compiler not understood"
#endif


#ifdef OXTS_CC_MSVC
#ifdef __CLR_VER
#define OXTS_CC_MSVC_CLR
#endif
#endif


//============================================================================================================
// OXTS_OS: OXTS_OS_WINDOWS OXTS_OS_QNX OXTS_OS_TI OXTS_OS_LINUX

#if defined(WIN32) || defined(_WIN32)
		#if (defined(OXTS_OS_QNX) || defined(OXTS_OS_TI) || defined(OXTS_OS_LINUX) || defined(OXTS_OS_XDEV))
		#error "Detected OXTS_OS_WINDOWS but you say something else"
		#endif
	#define OXTS_OS_WINDOWS
#elif defined(__QNX__)
		#if (defined(OXTS_OS_WINDOWS) || defined(OXTS_OS_TI) || defined(OXTS_OS_LINUX) || defined(OXTS_OS_XDEV))
		#error "Detected OXTS_OS_QNX but you say something else"
		#endif
	#define OXTS_OS_QNX
#elif defined(__TI_COMPILER_VERSION__)
		#if (defined(OXTS_OS_WINDOWS) || defined(OXTS_OS_QNX) || defined(OXTS_OS_LINUX) || defined(OXTS_OS_XDEV))
		#error "Detected OXTS_OS_TI but you say something else"
		#endif
	#define OXTS_OS_TI
#elif defined(xDev)
		#if (defined(OXTS_OS_WINDOWS) || defined(OXTS_OS_QNX) || defined(OXTS_OS_LINUX) || defined(OXTS_OS_XDEV))
		#error "Detected OXTS_OS_TI but you say something else"
		#endif
	#define OXTS_OS_XDEV
#else
#if (defined(OXTS_OS_WINDOWS) || defined(OXTS_OS_QNX) || defined(OXTS_OS_TI) || defined(OXTS_OS_XDEV))
#error "Detected OXTS_OS_LINUX but you say something else"
#endif
#define OXTS_OS_LINUX
#endif


#endif

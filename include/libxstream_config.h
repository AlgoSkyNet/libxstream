/******************************************************************************
** Copyright (c) 2014-2015, Intel Corporation                                **
** All rights reserved.                                                      **
**                                                                           **
** Redistribution and use in source and binary forms, with or without        **
** modification, are permitted provided that the following conditions        **
** are met:                                                                  **
** 1. Redistributions of source code must retain the above copyright         **
**    notice, this list of conditions and the following disclaimer.          **
** 2. Redistributions in binary form must reproduce the above copyright      **
**    notice, this list of conditions and the following disclaimer in the    **
**    documentation and/or other materials provided with the distribution.   **
** 3. Neither the name of the copyright holder nor the names of its          **
**    contributors may be used to endorse or promote products derived        **
**    from this software without specific prior written permission.          **
**                                                                           **
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS       **
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT         **
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR     **
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT      **
** HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    **
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED  **
** TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR    **
** PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF    **
** LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING      **
** NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS        **
** SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.              **
******************************************************************************/
/* Hans Pabst (Intel Corp.)
******************************************************************************/
#ifndef LIBXSTREAM_CONFIG_H
#define LIBXSTREAM_CONFIG_H

#ifndef LIBXSTREAM_MACROS_H
# error Do not include <libxstream_config.h> directly (use <libxstream_macros.h>)!
#endif


/**
 * Debug-time error checks are usually disabled for production code (NDEBUG).
 * The LIBXSTREAM_DEBUG symbol ultimately controls this (see libxstream_macros.h).
 */
#define LIBXSTREAM_ERROR_DEBUG

/**
 * Runtime error checks and error handling code is usually enabled.
 * The LIBXSTREAM_CHECK symbol ultimately controls this (see libxstream_macros.h).
 */
#define LIBXSTREAM_ERROR_CHECK

/**
 * Enables asynchronous offloads.
 * Valid selections:
 * - #define LIBXSTREAM_ASYNC: enables default (1) behavior
 * - #define LIBXSTREAM_ASYNC 0: synchronous offloads
 * - #define LIBXSTREAM_ASYNC 1: compiler offload
 * - #define LIBXSTREAM_ASYNC 2: compiler streams
 */
#define LIBXSTREAM_ASYNC

/**
 * Selects the API used to create the heler thread as well as some lock support.
 * Valid selections:
 * - #define LIBXSTREAM_THREAD_API: default API (1)
 * - #define LIBXSTREAM_THREAD_API 0: Unspecified (Pthreads or C++11)
 * - #define LIBXSTREAM_THREAD_API 1: OpenMP
 */
#define LIBXSTREAM_THREAD_API

/** SIMD width in Byte (actual alignment might be smaller). */
#define LIBXSTREAM_MAX_SIMD 64

/** Alignment in Byte (actual alignment might be smaller). */
#define LIBXSTREAM_MAX_ALIGN (2 * 1024 * 1024)

/** Maximum number of devices. */
#define LIBXSTREAM_MAX_DEVICES 8

/** Maximum number of streams per device. */
#define LIBXSTREAM_MAX_STREAMS 16

/** Maximum number of arguments in offload structure. */
#define LIBXSTREAM_MAX_NARGS 16

/** Maximum number of executions in the queue. */
#define LIBXSTREAM_MAX_QSIZE 1024


/**
 * Below preprocessor symbols fixup some platform specifics.
 */
#if !defined(_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES)
# define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#endif
#if !defined(_CRT_SECURE_NO_DEPRECATE)
# define _CRT_SECURE_NO_DEPRECATE 1
#endif
#if !defined(_USE_MATH_DEFINES)
# define _USE_MATH_DEFINES 1
#endif
#if !defined(WIN32_LEAN_AND_MEAN)
# define WIN32_LEAN_AND_MEAN 1
#endif
#if !defined(NOMINMAX)
# define NOMINMAX 1
#endif

#endif // LIBXSTREAM_CONFIG_H

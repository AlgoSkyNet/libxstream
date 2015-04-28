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

#if !defined(LIBXSTREAM_CONFIG_EXTERNAL)


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
 * Enables printing trace information.
 * Valid selections:
 * - #define LIBXSTREAM_TRACE: enables default (1) behavior
 * - #define LIBXSTREAM_TRACE 0: disables trace information
 * - #define LIBXSTREAM_TRACE 1: enabled for debug builds
 * - #define LIBXSTREAM_TRACE 2: enabled
 * If the trace information is enabled, the environment variable
 * LIBXSTREAM_VERBOSITY can be used to adjust the verbosity level.
 */
#define LIBXSTREAM_TRACE 2

/**
 * Enables asynchronous offloads.
 * Valid selections:
 * - #define LIBXSTREAM_ASYNC: enables default (1) behavior
 * - #define LIBXSTREAM_ASYNC 0: synchronous offloads
 * - #define LIBXSTREAM_ASYNC 1: compiler offload
 * - #define LIBXSTREAM_ASYNC 2: compiler streams
 * - #define LIBXSTREAM_ASYNC 3: native (KNL) - not implemented yet / must be disabled
 */
#define LIBXSTREAM_ASYNC 0

/** Not implemented yet. Must be disabled. */
/*#define LIBXSTREAM_ASYNCHOST*/

/** Not implemented yet. Must be disabled. */
/*#define LIBXSTREAM_ALLOC_PINNED*/

/** SIMD width in Byte (actual alignment might be smaller). */
#define LIBXSTREAM_MAX_SIMD 64

/** Alignment in Byte (actual alignment might be smaller). */
#define LIBXSTREAM_MAX_ALIGN (2 * 1024 * 1024)

/** Maximum number of devices. */
#define LIBXSTREAM_MAX_NDEVICES 4

/** Maximum number of streams per device. */
#define LIBXSTREAM_MAX_NSTREAMS 32

/** Maximum dimensionality of arrays. */
#define LIBXSTREAM_MAX_NDIMS 4

/** Maximum number of arguments in offload structure. */
#define LIBXSTREAM_MAX_NARGS 16

/** Maximum number of executions in the queue (POT). */
#define LIBXSTREAM_MAX_QSIZE 1024

/** Maximum number of host threads. */
#define LIBXSTREAM_MAX_NTHREADS 512

/** Maximum number of locks (POT). */
#define LIBXSTREAM_MAX_NLOCKS 16

/** Enables non-recursive locks. */
#define LIBXSTREAM_LOCK_NONRECURSIVE

/** Number of cycles to actively wait (server). */
#define LIBXSTREAM_WAIT_ACTIVE_CYCLES 10000

/** Wait using spin loop (client side). */
#define LIBXSTREAM_WAIT_SPIN

/** Wait for each work item when enqueued. */
/*#define LIBXSTREAM_WAIT*/

/** Prefers OpenMP based locking primitives. */
/*#define LIBXSTREAM_PREFER_OPENMP*/

#endif /*LIBXSTREAM_CONFIG_EXTERNAL*/
#endif /*LIBXSTREAM_CONFIG_H*/

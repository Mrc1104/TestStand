/*
 * File:
 *    gefcmn_common.h
 *
 * Description:
 *    This is a common header file for the Common API.
 *
 * Copyright:
 *    Copyright 2007-2011 GE Intelligent Platforms Embedded Systems, Inc.
 *
 * License:
 *    This file is proprietary to GE Intelligent Platforms Embedded Systems, Inc.
 */
/*
 * $Date$
 * $Rev$
 */

#ifndef	_GEFCMN_COMMON_H_
#define	_GEFCMN_COMMON_H_

#include "gef/gefcmn_types.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * Title: SBC Common API Header
 *
 * Description:
 *    This is a common header file for the Common API Library.
 *
 * Include Files:
 *    gefcmn_types.h
 *
 * Libraries:
 *    N/A
 *
 * Kernel Modules:
 *    N/A
 */

/**
 * Group: Types and Constants
 */

/**
 * Type: GEF_ENDIAN
 *
 * Description:
 *    An enumeration to set Endianness of the processor:
 *
 *
 *        GEF_ENDIAN_LITTLE               - The Processor is Little Endian.
 *
 *        GEF_ENDIAN_BIG                  - The Processor is Big Endian.
 */

typedef enum
{
  GEF_ENDIAN_LITTLE,
  GEF_ENDIAN_BIG,
} GEF_ENDIAN;

/**
 * Type: GEF_MAP_HDL
 *
 * Description:
 *    A handle to private structure GEF_MAP.
 *
 */
typedef struct _GEF_MAP*    GEF_MAP_HDL;

/**
 * Type: GEF_CALLBACK_HDL
 *
 * Description:
 *    A handle to private structure GEF_CALLBACK.
 *
 */
typedef struct _GEF_CALLBACK*    GEF_CALLBACK_HDL;

/**
 * Type: GEF_VERSION
 *
 * Description:
 *    A structure that holds version info.
 *
 *  major - Major version.
 *  minor - Minor version.
 *  build - Build version.
 */
typedef struct _GEF_VERSION
{
   GEF_UINT32 major;
   GEF_UINT32 minor;
   GEF_UINT32 build;
} GEF_VERSION;

/* A handy macro for suppressing compiler warnings regarding
   unreferenced formal parameters in a function call */
#ifndef UNREFERENCED_PARAMETER
#ifdef WIN32
#  define UNREFERENCED_PARAMETER(P) (P)
#else
#  define UNREFERENCED_PARAMETER(P)
#endif
#endif


/* The following is for Natural Docs to have a entry, the actual type is defined by the OS */

/**
 * Type: struct timeval
 *
 * Description:
 *    A structure that holds time info.
 *
 * tv_sec  - seconds.
 * tv_usec - microseconds
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _GEFCMN_COMMON_H_ */


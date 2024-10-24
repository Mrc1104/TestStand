/*
 * File:
 *    gefcmn_osa_defs.h
 *
 * Description:
 *    OSA interface for the common API.
 *
 * Copyright:
 *    Copyright 2007-2011 GE Intelligent Platforms Embedded Systems, Inc.
 *
 * License:
 *    This file is proprietary to GE Intelligent Platforms Embedded Systems, Inc.
 */
/*
 *  $Date$
 *  $Rev$
 */
#ifndef __GEFCMN_OSA_DEFS_H
#define __GEFCMN_OSA_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * Title: SBC Common API OS Abstraction Definitions
 *
 * Description:
 *    This is a common header file for the OS Abstraction.  
 *
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

typedef void* (*GEF_OSA_THREAD_FUNCTION)(void* arg);

#define GEF_MAX_MESSAGELEN 256

#define GEF_SEM_WAIT_INFINITE 0xFFFFFFFF
#define GEF_SEM_NO_WAIT 0

typedef enum
{
    GEF_OSA_PROC_SHARING_INTRA = 0, /* Sharing within a process  */
    GEF_OSA_PROC_SHARING_INTER = 1, /* Sharing between processes */
    GEF_OSA_PROC_SHARING_LAST = 2
} GEF_OSA_PROC_SHARING;

/*
 * Private data structures
 */
typedef struct _GEF_OSA*        GEF_OSA_HDL;
typedef struct _GEF_OSA_INTF*   GEF_OSA_INTF_HDL;
typedef struct _GEF_OSA_THREAD* GEF_OSA_THREAD_HDL;
typedef struct _GEF_OSA_SEM*    GEF_OSA_SEM_HDL;
typedef struct _GEF_OSA_NET*    GEF_OSA_NET_HDL;
typedef struct hostent          GEF_OSA_NET_HOSTENT;
typedef struct _GEF_OSA_SHM*    GEF_OSA_SHM_HDL;
typedef struct _GEF_OSA_SHM_MAP*  GEF_OSA_SHM_MAP_HDL;
typedef GEF_INT32               GEF_OSA_PROC_HDL;

/* Debug print macro */
#define GEF_OSA_DEBUG(flag, ...) if (GEF_WHEN_DEBUG((flag), gef_osa_debug_flags))  {GEF_DEBUG_PRINT(__VA_ARGS__);}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __GEFCMN_OSA_DEFS_H */


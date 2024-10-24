/*
 * File:
 *    gefcmn_osa_errno.h
 *
 * Description:
 *    Error definitions for the common API.
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
#ifndef __GEFCMN_OSA_ERRNO_H
#define __GEFCMN_OSA_ERRNO_H

#include "gef/gefcmn_errno.h"

/**
 * Type: GEF_STATUS_OSA_ENUM
 *
 * Description:
 *      Enumeration to set the error status.
 *        
 *   GEF_STATUS_OSA_ERROR              - OSA Specific Error
 *   GEF_STATUS_OSA_TIMEDOUT           - OSA Timeout Error
 *   GEF_STATUS_OSA_SYSTEM_ERROR       - OSA System Error
 *   GEF_STATUS_OSA_USER_NOT_PERMITTED - OSA User Not Permitted Error
 *   GEF_STATUS_OSA_THRD_NOT_FOUND     - OSA Thread Not Found Error
 *   GEF_STATUS_OSA_THRD_NOT_JOINABLE  - OSA Thread Not Joinable Error
 *   GEF_STATUS_OSA_INVALID_SEMAPHORE  - OSA Invalid Semaphore Error
 */
typedef enum 
{
    GEF_STATUS_OSA_ERROR       = GEF_STATUS_FACIL_ERROR_FIRST,
    GEF_STATUS_OSA_TIMEDOUT,
    GEF_STATUS_OSA_SYSTEM_ERROR,
    GEF_STATUS_OSA_USER_NOT_PERMITTED,
    GEF_STATUS_OSA_THRD_NOT_FOUND,
    GEF_STATUS_OSA_THRD_NOT_JOINABLE,
    GEF_STATUS_OSA_INVALID_SEMAPHORE,
    GEF_STATUS_OSA_NET_CONNECT_FAILED,
    GEF_STATUS_OSA_NET_ACCEPT_FAILED,
    GEF_STATUS_OSA_NET_LISTEN_FAILED,
    GEF_STATUS_OSA_NET_BIND_FAILED,
    GEF_STATUS_OSA_NET_SOCKOPT_ERR,
    GEF_STATUS_OSA_NET_CLOSE_ERR,
    GEF_STATUS_OSA_NET_SOCKET_ERR,
    GEF_STATUS_OSA_NET_NOACCES,
    GEF_STATUS_OSA_NET_ADDR_INUSE,
    GEF_STATUS_OSA_NET_CONNREFUSED,
    GEF_STATUS_OSA_LAST
    
} GEF_STATUS_OSA_ENUM;

#define GEF_SET_OSA_ERROR(error) GEF_SET_ERROR(GEF_FACIL_OSA, error)

#endif /* __GEFCMN_OSA_ERRNO_H */

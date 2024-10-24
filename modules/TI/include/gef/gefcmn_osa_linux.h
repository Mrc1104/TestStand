/*
 * File:
 *    gefcmn_osa_linux.h
 *
 * Description:
 *    Linux specific OSA interface for the common API.
 *
 * Copyright:
 *    Copyright 2007-2009 GE Intelligent Platforms Intelligent Platforms Embedded Systems, Inc.
 *
 * License:
 *    This file is proprietary to GE Intelligent Platforms Intelligent Platforms Embedded Systems, Inc.
 */
/*
 *  $Date$
 *  $Rev$
 */
#ifndef __GEFCMN_OSA_LINUX_H
#define __GEFCMN_OSA_LINUX_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef __KERNEL__
#include <linux/ioctl.h>
#else
#include <sys/ioctl.h>
#endif

#include "gef/gefcmn_osa_framework.h"
    
/**
 * Title: SBC Common API OS Abstraction Definitions
 *
 * Description:
 *    This is a linux header file for the OS Abstraction.  This file 
 *    is included by both the OSA Library and drivers, be careful!
 *
 * Include Files:
 *    linux/ioctl.h 
 *
 * Libraries:
 *    N/A
 *
 * Kernel Modules:
 *    N/A
 */

#define GEF_OSA_IOCTL_XFER_DATA  _IOWR(0x00, 0x00, GEF_OSA_INTF_DATA)
#define GEF_OSA_IOCTL_CHANGE_MAP _IOWR(0x00, 0x01, GEF_OSA_MAP_DATA)

typedef struct in_addr GEF_OSA_IN_ADDR;
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __GEFCMN_OSA_LINUX_H */


/*
 * File:
 *    gefcmn_vme_osspec.h
 *
 * Description:
 *    OS Specific VME Type Specifications for the Common API Library for
 *    Linux platform.
 *
 * Copyright:
 *    Copyright 2007-2009 GE Intelligent Platforms Intelligent Platforms Embedded Systems, Inc.
 *
 * License:
 *    This file is proprietary to GE Intelligent Platforms Intelligent Platforms Embedded Systems, Inc.
 */
/*
 * $Date$
 * $Rev$
 *
 * DESCRIPTION  This file 
 * 1) defines GEF_VME_DEVICE
 *
 * This file is OS specific for Linux
 *
 *         gefcmn_vme_osspec.h (This file)
 *               |
 *         gefcmn_drv_vme.h (Shared File)
 *               |
 *         Driver Interface and the Driver Framework 
 *
 *--------------------------------------------------------------------------
*/
#ifndef	GEFCMN_VME_OSSPEC_H
#define	GEFCMN_VME_OSSPEC_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "gefcmn_vme_defs.h"
#include "gefcmn_vme_errno.h"
#include "gefcmn_osspec.h"

/* GEF_VME_DEVICE is OS specific */
#define GEF_VME_DEVICE "/dev/vme_ctl"

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* GEFCMN_VME_OSSPEC_H */

/*
 * File:
 *    gefcmn_osa_framework.h
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

#ifndef __GEFCMN_OSA_FRAMEWORK_H
#define __GEFCMN_OSA_FRAMEWORK_H

#include "gef/gefcmn_types.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * Title: SBC Common API OS Abstraction Definitions
 *
 * Description:
 *    This is a common header file for the OS Abstraction.  This file
 *    is not exposed to the user, but must be available for test
 *    applications.
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

typedef struct _GEF_OSA_INTF_DATA
{
  GEF_UINT32  command;
  GEF_UINT32  sizeToDriver;
  GEF_UINT32  sizeFromDriver;
  GEF_UINT32  result;
  void       *dataToDriver;
  void       *dataFromDriver;
} __attribute__((packed))GEF_OSA_INTF_DATA;
/*
typedef struct _GEF_OSA_MAP_DATA
{
  GEF_UINT32  map_index;
  GEF_UINT32  result;
} GEF_OSA_MAP_DATA;
*/
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __GEFCMN_OSA_FRAMEWORK_H */


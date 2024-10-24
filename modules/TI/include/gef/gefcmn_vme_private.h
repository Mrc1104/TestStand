/*
 * File:
 *    gefcmn_vme_private.h
 *
 * Description:
 *    Linux specific type definition for VME framework.  
 *
 * Copyright:
 *    Copyright 2007-2011 GE Intelligent Platforms Intelligent Platforms Embedded Systems, Inc.
 *
 * License:
 *    This file is proprietary to GE Intelligent Platforms Intelligent PlatformsEmbedded Systems, Inc.
 */
/*
 * $Date$
 * $Rev$
 */
/*
Header File include structure
Shared = Shared across OS's, otherwise OS specific.
Kernel = File that can be included by Kernel driver in addition to user library.
User   = File delivered to user for user apps to include.

            gefcmn_types.h
            (Kernel, User)
                   |        
         gefcmn_vme_defs.h  
        (Shared,Kernel,User)
                   |                                 
          gefcmn_vme_private.h  
               (Kernel)          
*/


#ifndef	_GEFCMN_VME_PRIVATE_H_
#define	_GEFCMN_VME_PRIVATE_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "gefcmn_vme_defs.h"

#define GEF_VME_LIB_VER_BUILD 0
#define GEF_VME_DRV_VER_BUILD 3
#define GEF_VME_DRV_VER_MINOR 9
#define GEF_VME_LIB_VER_MINOR 1    

#define SWAP16(data)   (((GEF_UINT16)(data) & 0x00ff) << 8 | \
                        ((GEF_UINT16)(data) & 0xff00) >> 8   )

#define SWAP32(data)   (((GEF_UINT32)(data) & 0x000000ff) << 24 | \
                        ((GEF_UINT32)(data) & 0x0000ff00) << 8  | \
                        ((GEF_UINT32)(data) & 0x00ff0000) >> 8  | \
                        ((GEF_UINT32)(data) & 0xff000000) >> 24   )

#define SWAP64(data)   (((GEF_UINT64)(data) & 0x00000000000000ff) << 56 | \
                        ((GEF_UINT64)(data) & 0x000000000000ff00) << 40 | \
                        ((GEF_UINT64)(data) & 0x0000000000ff0000) << 24 | \
                        ((GEF_UINT64)(data) & 0x00000000ff000000) << 8  | \
                        ((GEF_UINT64)(data) & 0x000000ff00000000) >> 8  | \
                        ((GEF_UINT64)(data) & 0x0000ff0000000000) >> 24 | \
                        ((GEF_UINT64)(data) & 0x00ff000000000000) >> 40 | \
                        ((GEF_UINT64)(data) & 0xff00000000000000) >> 56   )

/* 
   This gets rid of compiler warnings when we are compiling for 32 bits 
   but have the 64 bit placeholders for pointers
*/
#define GEF_OS_CAST GEF_UINT_ADDR


typedef GEF_UINT64 GEF_VME_BUS_OSSPEC_HDL;
typedef GEF_UINT64 GEF_VME_INT_OSSPEC_HDL;
typedef GEF_UINT64 GEF_VME_SLAVE_OSSPEC_HDL;
typedef GEF_UINT64 GEF_VME_MASTER_OSSPEC_HDL;
typedef GEF_UINT64 GEF_VME_VRAI_OSSPEC_HDL;
typedef GEF_UINT64 GEF_VME_LM_OSSPEC_HDL;
typedef GEF_UINT64 GEF_VME_DMA_OSSPEC_HDL;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _GEFCMN_VME_PRIVATE_H_ */

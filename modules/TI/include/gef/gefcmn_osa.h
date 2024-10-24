/*
 * File:
 *    gefcmn_osa.h
 *
 * Description:
 *    OSA interface for the common API.
 *
 * Copyright:
 *    Copyright 2009-2011 GE Intelligent Platforms Embedded Systems, Inc.
 *
 * License:
 *    This file is proprietary to GE Intelligent Platforms Embedded Systems, Inc.
 */
/*
 *  $Date$
 *  $Rev$
 */
#ifndef __GEFCMN_OSA_H
#define __GEFCMN_OSA_H

#include "gef/gefcmn_osa_errno.h"
#include <gef/gefcmn_osa_framework.h>
#include "gef/gefcmn_osa_defs.h"
#include "gef/gefcmn_osspec.h"
#include "gef/gefcmn_osa_framework_ver.h"

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

/*
 * Public interfaces
 */

GEF_STATUS GEF_STD_CALL gefOsaOpen (GEF_OSA_HDL *osa_hdl);

GEF_STATUS GEF_STD_CALL gefOsaClose (GEF_OSA_HDL osa_hdl);


GEF_STATUS GEF_STD_CALL gefOsaThreadCreate (GEF_OSA_HDL              osa_hdl,
                                            GEF_OSA_THREAD_HDL      *thread_hdl, 
                                            GEF_OSA_THREAD_FUNCTION  threadFunction, 
                                            void                    *threadFunctionArg);

GEF_STATUS GEF_STD_CALL gefOsaThreadDelete (GEF_OSA_THREAD_HDL thread_hdl);

GEF_STATUS GEF_STD_CALL gefOsaThreadJoin (GEF_OSA_THREAD_HDL thread_hdl);

GEF_STATUS GEF_STD_CALL gefOsaGetThreadTaskId (GEF_OSA_THREAD_HDL  thread_hdl, 
                                               GEF_UINT32         *taskId);

GEF_STATUS GEF_STD_CALL gefOsaGetMyTaskId (GEF_OSA_HDL  osa_hdl, 
                                           GEF_UINT32  *taskId);

GEF_STATUS GEF_STD_CALL gefOsaSemOpenByName (GEF_OSA_HDL         osa_hdl, 
                                             GEF_INT32           count,
                                             char                *name,
                                             GEF_OSA_SEM_HDL     *sem_hdl);

GEF_STATUS GEF_STD_CALL gefOsaSemCreate (GEF_OSA_HDL          osa_hdl, 
                                         GEF_UINT32           count,
                                         GEF_OSA_PROC_SHARING process_shared,
                                         GEF_OSA_SEM_HDL     *sem_hdl);

GEF_STATUS GEF_STD_CALL gefOsaSemTake (GEF_OSA_SEM_HDL    sem_hdl, 
                                       GEF_UINT32         maxWaitInMsecs);

GEF_STATUS GEF_STD_CALL gefOsaSemGive (GEF_OSA_SEM_HDL  sem_hdl);

GEF_STATUS GEF_STD_CALL gefOsaSemClose (GEF_OSA_SEM_HDL sem_hdl);

GEF_STATUS GEF_STD_CALL gefOsaSemDestroy (GEF_OSA_SEM_HDL sem_hdl);

GEF_STATUS GEF_STD_CALL gefOsaIntfOpen (GEF_OSA_HDL       osa_hdl,
                                        GEF_OSA_INTF_HDL *intf_hdl,
                                        const char       *intfName);

GEF_STATUS GEF_STD_CALL gefOsaIntfCommunicate (GEF_OSA_INTF_HDL  intf_hdl,
                                               GEF_UINT32        command,
                                               void             *dataToDriver,
                                               GEF_UINT32        sizeToDriver,
                                               void             *dataFromDriver,
                                               GEF_UINT32       *sizeFromDriver,
                                               GEF_UINT32       *result);

GEF_STATUS GEF_STD_CALL gefOsaIntfRead (GEF_OSA_INTF_HDL  intf_hdl,
                                        char             *buffer,
                                        GEF_UINT32        numOfBytesToRead,
                                        GEF_UINT32       *numOfBytesRead);

GEF_STATUS GEF_STD_CALL gefOsaIntfWrite (GEF_OSA_INTF_HDL  intf_hdl,
                                         char             *buffer,
                                         GEF_UINT32        numOfBytesToWrite,
                                         GEF_UINT32       *numOfBytesWritten);

GEF_STATUS GEF_STD_CALL gefOsaMap (GEF_OSA_INTF_HDL  intf_hdl,  
                                   GEF_MAP_HDL      *map_hdl,
                                   char**            map_addr,
                                   GEF_UINT32        offset, 
                                   GEF_UINT32        size);

GEF_STATUS GEF_STD_CALL gefOsaUnMap (GEF_MAP_HDL map_hdl);

GEF_STATUS GEF_STD_CALL gefOsaIntfClose (GEF_OSA_INTF_HDL intf_hdl);

GEF_STATUS GEF_STD_CALL gefOsaVersion (GEF_OSA_HDL    osa_hdl, 
                                       GEF_VERSION   *version);

GEF_STATUS GEF_STD_CALL gefOsaNetOpen (GEF_OSA_HDL osa_hdl, GEF_OSA_NET_HDL *handle) ;

GEF_STATUS GEF_STD_CALL gefOsaNetListen (GEF_OSA_NET_HDL handle, GEF_UINT16 port);

GEF_STATUS GEF_STD_CALL gefOsaNetConnect (GEF_OSA_NET_HDL handle, const char *dest, GEF_UINT16 port);

GEF_STATUS GEF_STD_CALL gefOsaNetTx (GEF_OSA_NET_HDL handle, void *data, GEF_UINT32 len);

GEF_STATUS GEF_STD_CALL gefOsaNetRx (GEF_OSA_NET_HDL handle, void *data, GEF_UINT32 len);

GEF_STATUS GEF_STD_CALL gefOsaNetClose (GEF_OSA_NET_HDL handle);

GEF_STATUS GEF_STD_CALL gefOsaNetSetDebug(GEF_OSA_NET_HDL handle, GEF_UINT32 debug);

GEF_STATUS GEF_STD_CALL gefOsaSleep (struct timeval *timeout);

GEF_STATUS GEF_STD_CALL gefOsaShmOpen( GEF_OSA_HDL osa_hdl,
                                       char* name,
                                       GEF_OSA_SHM_HDL* osa_shm_hdl );

GEF_STATUS GEF_STD_CALL  gefOsaShmClose(GEF_OSA_SHM_HDL osa_shm_hdl, GEF_BOOL unlink);

GEF_STATUS GEF_STD_CALL  gefOsaShmMap ( GEF_OSA_SHM_HDL osa_shm_hdl, 
                                        GEF_OSA_SHM_MAP_HDL* map_hdl, 
                                        char** map_addr, 
                                        GEF_UINT32 offset, 
                                        GEF_UINT32 size);

GEF_STATUS GEF_STD_CALL  gefOsaShmUnMap(GEF_OSA_SHM_MAP_HDL map_hdl);

GEF_STATUS GEF_STD_CALL gefOsaProcessCreate( GEF_OSA_HDL osa_hdl, GEF_OSA_PROC_HDL* osa_proc_hdl);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __GEFCMN_OSA_H */


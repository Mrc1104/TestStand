/*
 * File:
 *    gefcmn_vme_framework.h
 *
 * Description:
 *    This interface file defines the framework definitions for the VME facility.
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
/*
Header File include structure
Shared = Shared across OS's, otherwise OS specific.
Kernel = File that can be included by Kernel driver in addition to user library.
User   = File delivered to user for user apps to include.

     gefcmn_types.h
     (Kernel, User)
            |
    gefcmn_common.h  
  (Shared,Kernel,User)
            |        
  gefcmn_vme_defs.h  
 (Shared,Kernel,User)
            |                                 
     gefcmn_vme_private.h  gefcmn_osa_defs.h   gefcmn_vme_framework_ver.h
         (Kernel)          (Shared, Kernel)         (Shared, Kernel)
            |                    |                        |
            -----------------------------------------------
                                 |
                       gefcmn_vme_framework.h
                          (Shared, Kernel)
*/
#ifndef __GEFCMN_VME_FRAMEWORK_H
#define __GEFCMN_VME_FRAMEWORK_H			

#include <gef/gefcmn_vme_private.h>
#include "gef/gefcmn_osa_defs.h"
#include "gef/gefcmn_vme_framework_ver.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern GEF_UINT32 gef_vme_debug_flags;

#if defined(WIN32) 
#define GEF_CONDITIONALLY_PACKED_STRUCT  
#else 
#define GEF_CONDITIONALLY_PACKED_STRUCT  __attribute__((packed)) 
#endif 

struct _GEF_VME_BUS
{
    GEF_OSA_HDL               osa_hdl;
    GEF_OSA_INTF_HDL          osa_intf_hdl;
    GEF_UINT32                magic;
    GEF_VME_BUS_OSSPEC_HDL    bus_osspec_hdl;
    GEF_CALLBACK_HDL          callback_hdl_list;
    GEF_OSA_SEM_HDL           callback_sem_hdl;
};

struct _GEF_VME_WAIT
{
    GEF_VME_BUS_HDL           bus_hdl;
    GEF_UINT32                magic;
    GEF_VME_INT_OSSPEC_HDL    int_osspec_hdl;
    GEF_VME_INT_INFO          int_info; 
    struct timeval            timeout;
};

/* This structure defines the per-process allocation of slave windows */
struct _GEF_VME_SLAVE
{
    GEF_VME_BUS_HDL           bus_hdl;
    GEF_UINT32                magic;
    GEF_VME_SLAVE_OSSPEC_HDL  slave_osspec_hdl;
    GEF_UINT32                size;
    GEF_UINT32                map_count;
};

struct _GEF_VME_MAP_SLAVE
{
    GEF_VME_SLAVE_HDL         slave_hdl; 
    GEF_UINT64                phys_addr;
    GEF_UINT64                virt_addr;
    GEF_UINT64                drv_map_hdl;
    GEF_MAP_HDL               osa_map_hdl;
    GEF_UINT32                magic;
    GEF_UINT32                size;
};

struct _GEF_VME_MASTER
{
    GEF_VME_BUS_HDL           bus_hdl;
    GEF_UINT32                magic;
    GEF_VME_MASTER_OSSPEC_HDL master_osspec_hdl;
    GEF_UINT32                size;
};

struct _GEF_VME_MAP_MASTER
{
    GEF_VME_MASTER_HDL        master_hdl; 
    GEF_UINT32                magic;
    GEF_MAP_HDL               osa_map_hdl;
    GEF_UINT64                drv_map_hdl;
    GEF_UINT64                phys_addr;
    GEF_UINT64                virt_addr;
    GEF_UINT32                size;
};

struct _GEF_VME_VRAI
{
    GEF_VME_BUS_HDL           bus_hdl;
    GEF_UINT32                magic;
    GEF_VME_VRAI_OSSPEC_HDL   vrai_osspec_hdl; 
};

struct _GEF_VME_LM
{
    GEF_VME_BUS_HDL           bus_hdl;
    GEF_UINT32                magic;
    GEF_VME_LM_OSSPEC_HDL     lm_osspec_hdl; 
};

struct _GEF_VME_DMA
{
    GEF_VME_BUS_HDL           bus_hdl;
    GEF_UINT32                magic;
    GEF_VME_DMA_OSSPEC_HDL    dma_osspec_hdl; 
    GEF_MAP_HDL               osa_map_hdl;
    GEF_UINT64                phys_addr;
    GEF_UINT64                virt_addr;
    GEF_UINT32                size;
};

typedef enum 
{
  GEF_VME_FRAMEWORK_CODE_READ = 1,
  GEF_VME_FRAMEWORK_CODE_WRITE,
  GEF_VME_FRAMEWORK_CODE_CREATE_MASTER_WINDOW,
  GEF_VME_FRAMEWORK_CODE_RELEASE_MASTER_WINDOW,
  GEF_VME_FRAMEWORK_CODE_TRANSLATE_MASTER_WINDOW,
  GEF_VME_FRAMEWORK_CODE_READ_MODIFY_WRITE,
  GEF_VME_FRAMEWORK_CODE_CREATE_SLAVE_WINDOW,
  GEF_VME_FRAMEWORK_CODE_REMOVE_SLAVE_WINDOW,
  GEF_VME_FRAMEWORK_CODE_READ_DMA,
  GEF_VME_FRAMEWORK_CODE_WRITE_DMA,
  GEF_VME_FRAMEWORK_CODE_ALLOC_DMA_BUF,
  GEF_VME_FRAMEWORK_CODE_FREE_DMA_BUF,
  GEF_VME_FRAMEWORK_CODE_READ_DMA_BUF,
  GEF_VME_FRAMEWORK_CODE_WRITE_DMA_BUF,
  GEF_VME_FRAMEWORK_CODE_GENERATE_IRQ,
  GEF_VME_FRAMEWORK_CODE_WAIT_FOR_INTERRUPT,
  GEF_VME_FRAMEWORK_CODE_WAIT_ACK,
  GEF_VME_FRAMEWORK_CODE_RELEASE_WAIT,
  GEF_VME_FRAMEWORK_CODE_SET_BUS_REL_MODE,
  GEF_VME_FRAMEWORK_CODE_GET_BUS_REL_MODE,
  GEF_VME_FRAMEWORK_CODE_SET_BUS_REQ_MODE,
  GEF_VME_FRAMEWORK_CODE_GET_BUS_REQ_MODE,
  GEF_VME_FRAMEWORK_CODE_SET_BUS_REQ_LEVEL,
  GEF_VME_FRAMEWORK_CODE_GET_BUS_REQ_LEVEL,
  GEF_VME_FRAMEWORK_CODE_SET_BUS_TIMEOUT,
  GEF_VME_FRAMEWORK_CODE_GET_BUS_TIMEOUT,
  GEF_VME_FRAMEWORK_CODE_SET_BUS_ARB_MODE,
  GEF_VME_FRAMEWORK_CODE_GET_BUS_ARB_MODE,
  GEF_VME_FRAMEWORK_CODE_SET_ARB_TIMEOUT,
  GEF_VME_FRAMEWORK_CODE_GET_ARB_TIMEOUT,
  GEF_VME_FRAMEWORK_CODE_SET_BROADCAST_ID,
  GEF_VME_FRAMEWORK_CODE_GET_BROADCAST_ID,
  GEF_VME_FRAMEWORK_CODE_SET_SYSFAIL,
  GEF_VME_FRAMEWORK_CODE_GET_SYSFAIL,
  GEF_VME_FRAMEWORK_CODE_CREATE_LOCATION_MON,
  GEF_VME_FRAMEWORK_CODE_RELEASE_LOCATION_MON,
  GEF_VME_FRAMEWORK_CODE_QUERY_LOCATION_MON,
  GEF_VME_FRAMEWORK_CODE_CREATE_VRAI,
  GEF_VME_FRAMEWORK_CODE_REMOVE_VRAI,
  GEF_VME_FRAMEWORK_CODE_QUERY_VRAI,
  GEF_VME_FRAMEWORK_CODE_SYS_RESET,
  GEF_VME_FRAMEWORK_CODE_ACQUIRE_BUS_OWNERSHIP,
  GEF_VME_FRAMEWORK_CODE_RELEASE_BUS_OWNERSHIP,
  GEF_VME_FRAMEWORK_CODE_QUERY_BUS_OWNERSHIP,
  GEF_VME_FRAMEWORK_CODE_SET_MAX_RETRY,
  GEF_VME_FRAMEWORK_CODE_GET_MAX_RETRY,
  GEF_VME_FRAMEWORK_CODE_SET_POST_WRITE_COUNT,
  GEF_VME_FRAMEWORK_CODE_GET_POST_WRITE_COUNT,
  GEF_VME_FRAMEWORK_CODE_SET_DEBUG_FLAGS,
  GEF_VME_FRAMEWORK_CODE_GET_DEBUG_FLAGS,
  GEF_VME_FRAMEWORK_CODE_READ_REG,
  GEF_VME_FRAMEWORK_CODE_WRITE_REG,
  GEF_VME_FRAMEWORK_CODE_SET_RD_WR_BYTESWAP,
  GEF_VME_FRAMEWORK_CODE_GET_RD_WR_BYTESWAP,
  GEF_VME_FRAMEWORK_CODE_MAP_MASTER,
  GEF_VME_FRAMEWORK_CODE_MAP_SLAVE,
  GEF_VME_FRAMEWORK_CODE_UNMAP_SLAVE,
  GEF_VME_FRAMEWORK_CODE_GET_DRV_VERSION, 
  GEF_VME_FRAMEWORK_CODE_UNMAP_MASTER,
  GEF_VME_FRAMEWORK_CODE_SET_MASTER_HW_BYTESWAP,
  GEF_VME_FRAMEWORK_CODE_GET_MASTER_HW_BYTESWAP,
  GEF_VME_FRAMEWORK_CODE_SET_SLAVE_HW_BYTESWAP,
  GEF_VME_FRAMEWORK_CODE_GET_SLAVE_HW_BYTESWAP,
  GEF_VME_FRAMEWORK_CODE_SET_TIME_ON_BUS,
  GEF_VME_FRAMEWORK_CODE_GET_TIME_ON_BUS,
  GEF_VME_FRAMEWORK_CODE_GET_TIME_OFF_BUS,
  GEF_VME_FRAMEWORK_CODE_SET_TIME_OFF_BUS,
  GEF_VME_FRAMEWORK_CODE_PEEK,
  GEF_VME_FRAMEWORK_CODE_POKE,
  GEF_VME_FRAMEWORK_CODE_LAST,
} GEF_VME_FRAMEWORK_CODE;

/**
 * Type: GEF_VME_DATA_WIDTH
 *
 * Description:
 *   An enumeration to set VME data width
 * 
 * GEF_VME_DATA_WIDTH_DIRECT - Direct transfer of data for unspecified width
 * GEF_VME_DWIDTH_D8 -  1 Byte
 * GEF_VME_DWIDTH_D16 - 2 Bytes
 * GEF_VME_DWIDTH_D32 - 4 Bytes
 * GEF_VME_DWIDTH_D64 - 8 Bytes
 */
typedef enum
{
    GEF_VME_DATA_WIDTH_DIRECT  = 0,   /* Direct  */
    GEF_VME_DATA_WIDTH_8       = 1,   /* 1 Byte  */
    GEF_VME_DATA_WIDTH_16      = 2,   /* 2 Bytes */
    GEF_VME_DATA_WIDTH_32      = 4,   /* 4 Bytes */
    GEF_VME_DATA_WIDTH_64      = 8,   /* 8 Bytes */
    GEF_VME_DATA_WIDTH_LAST    = 5    /* Keep as number of elements */
} GEF_VME_DATA_WIDTH;

/**
 * Type: GEF_VME_DRV_READ_WRITE_INFO
 *
 * Description:
 *   VME Read/Write info structure.
 *   Supported OSA Calls:
 *     GEF_VME_FRAMEWORK_CODE_READ
 *     GEF_VME_FRAMEWORK_CODE_WRITE
 *
 * master_osspec_hdl - returned by create master window.
 * width             - device optimized, 1,2,4,8.
 * offset            - offset into master window, width aligned.
 * length            - Number of width items to transfer.
 * buffer            - user memory pointer.
 *
 */
typedef struct
{
  GEF_VME_MASTER_OSSPEC_HDL  master_osspec_hdl;
  GEF_VME_DATA_WIDTH         width;        /* device optimized, 0,1,2,4,8 */
  GEF_UINT32                 offset;       /* offset into master window */
  GEF_UINT32                 num_elements; /* Number of width items to transfer */
  GEF_UINT64                 buffer;       /* user memory pointer stored in GEF_UINT64 */
}GEF_CONDITIONALLY_PACKED_STRUCT GEF_VME_DRV_READ_WRITE_INFO;

/**
 * Type: GEF_VME_DRV_CREATE_MASTER_WINDOW_INFO
 *
 * Description:
 *   VME Create Master Window info structure.
 *   Supported OSA Calls:
 *     GEF_VME_FRAMEWORK_CODE_CREATE_MASTER_WINDOW,
 *
 * master_osspec_hdl - Handle to <GEF_VME_MASTER_OSSPEC_HDL>.
 * addr              - VMEbus address structure of type <GEF_VME_ADDR>. 
 * size              - Minimum size of the window in bytes.
 *
 */
typedef struct
{
  GEF_VME_MASTER_OSSPEC_HDL  master_osspec_hdl;
  GEF_VME_ADDR               addr;
  GEF_UINT32                 size;
}GEF_CONDITIONALLY_PACKED_STRUCT GEF_VME_DRV_CREATE_MASTER_WINDOW_INFO;

/**
 * Type: GEF_VME_DRV_TRANSLATE_MASTER_WINDOW_INFO
 *
 * Description:
 *   VME Translate Master Window info structure.
 *   Supported OSA Calls:
 *     GEF_VME_FRAMEWORK_CODE_TRANSLATE_MASTER_WINDOW,
 *
 * master_osspec_hdl - Handle to <GEF_VME_MASTER_OSSPEC_HDL>.
 * addr              - VMEbus address structure of type <GEF_VME_ADDR>.
 *
 */
typedef struct
{
  GEF_VME_MASTER_OSSPEC_HDL  master_osspec_hdl;
  GEF_VME_ADDR               addr;
}GEF_CONDITIONALLY_PACKED_STRUCT GEF_VME_DRV_TRANSLATE_MASTER_WINDOW_INFO;

/**
 * Type: GEF_VME_DRV_RELEASE_MASTER_WINDOW_HDL_INFO
 *
 * Description:
 *   VME Release Master Window info structure.
 *   Supported OSA Calls:
 *     GEF_VME_FRAMEWORK_CODE_RELEASE_MASTER_WINDOW,
 *
 * master_osspec_hdl - Handle to <GEF_VME_MASTER_OSSPEC_HDL>.
 *
 */
typedef struct
{
  GEF_VME_MASTER_OSSPEC_HDL  master_osspec_hdl;
}GEF_CONDITIONALLY_PACKED_STRUCT GEF_VME_DRV_RELEASE_MASTER_WINDOW_HDL_INFO;

/**
 * Type: GEF_VME_DRV_READ_MODIFY_WRITE_INFO
 *
 * Description:
 *   VME Read/Modify/Write info structure.
 *   Supported OSA Calls:
 *     GEF_VME_FRAMEWORK_CODE_READ
 *     GEF_VME_FRAMEWORK_CODE_WRITE
 *
 * master_osspec_hdl - Handle to <GEF_VME_MASTER_OSSPEC_HDL>.
 * offset            - offset into master window, width aligned.
 * dw                - data width structure <GEF_VME_DWIDTH>.
 * cmp               - compare mask
 * swap              - swap 
 *
 */
typedef struct
{
  GEF_VME_MASTER_OSSPEC_HDL master_osspec_hdl;
  GEF_UINT32                offset;
  GEF_VME_DWIDTH            dw;
  GEF_UINT32                mask;
  GEF_UINT32                cmp;
  GEF_UINT32                swap;
}GEF_CONDITIONALLY_PACKED_STRUCT GEF_VME_DRV_READ_MODIFY_WRITE_INFO;

/**
 * Type: GEF_VME_DRV_CREATE_SLAVE_WINDOW_INFO
 *
 * Description:
 *   VME Create Slave Window info structure.
 *   Supported OSA Calls:
 *     GEF_VME_FRAMEWORK_CODE_CREATE_MASTER_WINDOW,
 *
 * slave_osspec_hdl - Handle to <GEF_VME_SLAVE_OSSPEC_HDL>.
 * addr             - VMEbus address structure of type <GEF_VME_ADDR>. 
 * size             - Minimum size of the window in bytes.
 *
 */
typedef struct
{
  GEF_VME_SLAVE_OSSPEC_HDL  slave_osspec_hdl;
  GEF_VME_ADDR              addr;
  GEF_UINT32                size;
}GEF_CONDITIONALLY_PACKED_STRUCT GEF_VME_DRV_CREATE_SLAVE_WINDOW_INFO;

/**
 * Type: GEF_VME_DRV_RELEASE_SLAVE_WINDOW_HDL_INFO
 *
 * Description:
 *   VME Release Slave Window info structure.
 *   Supported OSA Calls:
 *     GEF_VME_FRAMEWORK_CODE_RELEASE_SLAVE_WINDOW,
 *
 * slave_osspec_hdl - Handle to <GEF_VME_SLAVE_OSSPEC_HDL>.
 *
 */
typedef struct
{
  GEF_VME_SLAVE_OSSPEC_HDL  slave_osspec_hdl;
}GEF_CONDITIONALLY_PACKED_STRUCT GEF_VME_DRV_RELEASE_SLAVE_WINDOW_HDL_INFO;

/**
 * Type: GEF_VME_DRV_READ_WRITE_DMA_INFO
 *
 * Description:
 *   VME Read/Write DMA info structure.
 *   Supported OSA Calls:
 * GEF_VME_FRAMEWORK_CODE_READ_DMA
 * GEF_VME_FRAMEWORK_CODE_WRITE_DMA
 *
 * addr          - VMEbus address structure of type <GEF_VME_ADDR>. 
 * virt_addr     - Virtual address of buffer for DMA.
 * length        - Number of bytes to transfer.
 *
 */
typedef struct
{
  GEF_VME_ADDR        vme_addr;  
  GEF_UINT64          virt_addr; /* user address */
  GEF_UINT32          length;
  GEF_BOOL            libPerformIo; /* GEF_TRUE - library makes IO call, otherwise driver performs DMA */
}GEF_CONDITIONALLY_PACKED_STRUCT GEF_VME_DRV_READ_WRITE_DMA_INFO;

/**
 * Type: GEF_VME_DRV_FREE_DMA_BUF_INFO
 *
 * Description:
 *   VME Free DMA Buffer info structure.
 *   Supported OSA Calls:
 *     GEF_VME_DRV_FREE_DMA_BUF
 *
 * dma_osspec_hdl - Handle to <GEF_VME_DMA_OSSPEC_HDL>.
 *
 */
typedef struct
{
  GEF_VME_DMA_OSSPEC_HDL dma_osspec_hdl;
}GEF_CONDITIONALLY_PACKED_STRUCT GEF_VME_DRV_FREE_DMA_BUF_INFO;

/**
 * Type: GEF_VME_DRV_READ_WRITE_DMA_BUF_INFO
 *
 * Description:
 *   VME Register Access Image info structure.
 *   Supported OSA Calls:
 *     GEF_VME_FRAMEWORK_CODE_READ_DMA_BUF
 *     GEF_VME_FRAMEWORK_CODE_WRITE_DMA_BUF
 *
 * dma_osspec_hdl - Handle to <GEF_VME_DMA_OSSPEC_HDL>.
 * offset         - byte offset into buffer
 * addr           - VMEbus address structure of type <GEF_VME_ADDR>. 
 * length         - length of transfer
 */
typedef struct
{
  GEF_VME_DMA_OSSPEC_HDL dma_osspec_hdl;
  GEF_UINT32       offset;
  GEF_VME_ADDR     addr;
  GEF_UINT32       length;
}GEF_CONDITIONALLY_PACKED_STRUCT GEF_VME_DRV_READ_WRITE_DMA_BUF_INFO;
 
/**
 * Type: GEF_VME_DRV_VIRQ_INFO
 *
 * Description:
 *   VME bus virq info structure.
 *   Supported OSA Calls:
 *     GEF_VME_FRAMEWORK_CODE_GENERATE_IRQ
 *     GEF_VME_FRAMEWORK_CODE_RELEASE_WAIT
 *
 * level    - interrupt level.
 * vector   - interrupt vector.
 * timeout  - timeout value to wait for IACK
 *
 */
typedef	struct
{
  GEF_VME_INT_LEVEL level;
  GEF_UINT32        vector;
  struct timeval    timeout;
}GEF_CONDITIONALLY_PACKED_STRUCT GEF_VME_DRV_VIRQ_INFO;


/**
 * Type: GEF_VME_DRV_WAIT_INFO
 *
 * Description:
 *   VME bus virq info structure.
 *   Supported OSA Calls:
 *     GEF_VME_FRAMEWORK_CODE_WAIT_FOR_INTERRUPT 
 *     GEF_VME_FRAMEWORK_CODE_WAIT_ACK
 *
 * wait_hdl  - returned handle.
 *
 */
typedef	struct
{
    GEF_VME_INT_OSSPEC_HDL  int_osspec_hdl;
    GEF_VME_INT_INFO        int_info; 
    struct timeval          timeout;
}GEF_CONDITIONALLY_PACKED_STRUCT GEF_VME_DRV_WAIT_INFO;

/**
 * Type: GEF_VME_DRV_BUS_REL_MODE_INFO
 *
 * Description:
 *   VME bus release mode info structure.
 *   Supported OSA Calls:
 *     GEF_VME_FRAMEWORK_CODE_SET_BUS_REL_MODE
 *     GEF_VME_FRAMEWORK_CODE_GET_BUS_REL_MODE
 *
 * release_mode    - bus release mode.
 *
 */
typedef struct
{
  GEF_VME_BUS_RELEASE_MODE release_mode;
}GEF_CONDITIONALLY_PACKED_STRUCT GEF_VME_DRV_BUS_REL_MODE_INFO;

/**
 * Type: GEF_VME_DRV_BUS_REQ_MODE_INFO
 *
 * Description:
 *   VME bus request mode info structure.
 *   Supported OSA Calls:
 *     GEF_VME_FRAMEWORK_CODE_SET_BUS_REQ_MODE
 *     GEF_VME_FRAMEWORK_CODE_GET_BUS_REQ_MODE
 *
 * request_mode    - bus request mode.
 *
 */
typedef struct
{
  GEF_VME_BUS_REQUEST_MODE request_mode;
}GEF_CONDITIONALLY_PACKED_STRUCT GEF_VME_DRV_BUS_REQ_MODE_INFO;

/**
 * Type: GEF_VME_DRV_BUS_REQ_LEVEL_INFO
 *
 * Description:
 *   VME bus request level info structure.
 *   Supported OSA Calls:
 *     GEF_VME_FRAMEWORK_CODE_SET_BUS_REQ_LEVEL
 *     GEF_VME_FRAMEWORK_CODE_GET_BUS_REQ_LEVEL
 *
 * request_level    - bus request level.
 *
 */
typedef struct
{
  GEF_VME_BUS_REQUEST_LEVEL request_level;
}GEF_CONDITIONALLY_PACKED_STRUCT GEF_VME_DRV_BUS_REQ_LEVEL_INFO;

/**
 * Type: GEF_VME_DRV_BUS_TIMEOUT_INFO
 *
 * Description:
 *   VME bus timeout info structure.
 *   Supported OSA Calls:
 *     GEF_VME_FRAMEWORK_CODE_SET_BUS_TIMEOUT
 *     GEF_VME_FRAMEWORK_CODE_GET_BUS_TIMEOUT
 *
 * timeout    - bus timeout.
 *
 */
typedef struct
{
  GEF_VME_BUS_TIMEOUT timeout;
}GEF_CONDITIONALLY_PACKED_STRUCT GEF_VME_DRV_BUS_TIMEOUT_INFO;

/**
 * Type: GEF_VME_DRV_BUS_ARB_INFO
 *
 * Description:
 *   VME bus arbitration mode info structure.
 *   Supported OSA Calls:
 *     GEF_VME_FRAMEWORK_CODE_SET_BUS_ARB_MODE
 *     GEF_VME_FRAMEWORK_CODE_GET_BUS_ARB_MODE
 *
 * arbitration_mode    - bus arbitration mode.
 *
 */
typedef struct
{
  GEF_VME_BUS_ARB_MODE arbitration_mode;
}GEF_CONDITIONALLY_PACKED_STRUCT GEF_VME_DRV_BUS_ARB_INFO;

/**
 * Type: GEF_VME_ARB_TIMEOUT_INFO
 *
 * Description:
 *   VME bus arbitration timeout info structure.
 *   Supported OSA Calls:
 *     GEF_VME_FRAMEWORK_CODE_SET_ARB_TIMEOUT
 *     GEF_VME_FRAMEWORK_CODE_GET_ARB_TIMEOUT
 *
 * arb_timeout    - bus arbibration timeout.
 *
 */
typedef struct
{
  GEF_VME_ARB_TIMEOUT arb_timeout;
}GEF_CONDITIONALLY_PACKED_STRUCT GEF_VME_DRV_ARB_TIMEOUT_INFO;

/**
 * Type: GEF_VME_BUS_BROADCAST_INFO
 *
 * Description:
 *   VME bus arbitration timeout info structure.
 *   Supported OSA Calls:
 *     GEF_VME_FRAMEWORK_CODE_SET_BROADCAST_ID
 *     GEF_VME_FRAMEWORK_CODE_GET_BROADCAST_ID
 *
 * broadcast_id    - bus broadcast id.
 *
 */
typedef struct
{
  GEF_VME_BROADCAST_ID broadcast_id;
}GEF_CONDITIONALLY_PACKED_STRUCT GEF_VME_DRV_BUS_BROADCAST_INFO;

/**
 * Type: GEF_VME_SYSFAIL_INFO
 *
 * Description:
 *   VME bus sysfail info structure.
 *   Supported OSA Calls:
 *     GEF_VME_FRAMEWORK_CODE_SET_SYSFAIL
 *     GEF_VME_FRAMEWORK_CODE_GET_SYSFAIL
 *
 * sysfail    - sysfail status.
 *
 */
typedef struct
{
  GEF_BOOL sysfail;
}GEF_CONDITIONALLY_PACKED_STRUCT GEF_VME_DRV_SYSFAIL_INFO;

/**
 * Type: GEF_VME_DRV_LOCATION_MONITOR_INFO
 *
 * Description:
 *   VME location monitor info structure.
 *   Supported OSA Calls:
 *     GEF_VME_FRAMEWORK_CODE_CREATE_LOCATION_MON
 *     GEF_VME_FRAMEWORK_CODE_RELEASE_LOCATION_MON
 *     GEF_VME_FRAMEWORK_CODE_QUERY_LOCATION_MON
 *
 * addr               - VMEbus address structure of type <GEF_VME_ADDR>. 
 * lm_osspec_hdl      - Handle to <GEF_VME_LM_OSSPEC_HDL>.
 *
 */
typedef struct
{
  GEF_VME_ADDR           addr;
  GEF_VME_LM_OSSPEC_HDL  lm_osspec_hdl;
}GEF_CONDITIONALLY_PACKED_STRUCT GEF_VME_DRV_LOCATION_MONITOR_INFO;

/**
 * Type: GEF_VME_DRV_VRAI_INFO
 *
 * Description:
 *   VME Register Access Image info structure.
 *   Supported OSA Calls:
 *     GEF_VME_FRAMEWORK_CODE_CREATE_VRAI
 *     GEF_VME_FRAMEWORK_CODE_REMOVE_VRAI
 *     GEF_VME_FRAMEWORK_CODE_QUERY_VRAI
 *
 * addr               - VMEbus address structure of type <GEF_VME_ADDR>. 
 *
 */
typedef struct
{
  GEF_VME_ADDR addr;
}GEF_CONDITIONALLY_PACKED_STRUCT GEF_VME_DRV_VRAI_INFO;

/**
 * Type: GEF_VME_MAX_RETRY_INFO
 *
 * Description:
 *   VME bus arbitration timeout info structure.
 *   Supported OSA Calls:
 *     GEF_VME_FRAMEWORK_CODE_SET_MAX_RETRY
 *     GEF_VME_FRAMEWORK_CODE_GET_MAX_RETRY
 *
 * max_retry    - max PCI retry.
 *
 */
typedef struct
{
  GEF_VME_MAX_RETRY max_retry;
}GEF_CONDITIONALLY_PACKED_STRUCT GEF_VME_MAX_RETRY_INFO;

/**
 * Type: GEF_VME_POST_WRITE_COUNT_INFO
 *
 * Description:
 *   VME bus arbitration timeout info structure.
 *   Supported OSA Calls:
 *     GEF_VME_FRAMEWORK_CODE_SET_POST_WRITE_COUNT
 *     GEF_VME_FRAMEWORK_CODE_GET_POST_WRITE_COUNT
 *
 * max_retry    - posted write count.
 *
 */
typedef struct
{
  GEF_VME_PWON pwon;
}GEF_CONDITIONALLY_PACKED_STRUCT GEF_VME_POST_WRITE_COUNT_INFO;

/**
 * Type: GEF_VME_DRV_READ_WRITE_REG_INFO
 *
 * Description:
 *   VME bridge device register access info structure.
 *   Supported OSA Calls:
 *     GEF_VME_FRAMEWORK_CODE_READ_REG
 *     GEF_VME_FRAMEWORK_CODE_WRITE_REG
 *
 * offset    - register offset to access.
 * width     - width of transfer.
 * value     - value read or to be written.
 *
 */
typedef struct
{
  GEF_UINT32                 offset; /* offset into register space */
  GEF_VME_DATA_WIDTH         width;  /* device optimized, 0,1,2,4,8 */
  GEF_UINT32                 value;
}GEF_CONDITIONALLY_PACKED_STRUCT GEF_VME_DRV_READ_WRITE_REG_INFO;

/**
 * Type: GEF_VME_MAP_MASTER_INFO
 *
 * Description:
 *   VME Master Map info structure.
 *   Supported OSA Calls:
 *     GEF_VME_FRAMEWORK_CODE_MAP_MASTER_WINDOW,
 *
 * master_osspec_hdl - Handle to os specific handle.
 * phys_addr         - Physical address
 * virt_addr         - Virtual address
 * size              - size requested
 *
 */
typedef struct
{
    GEF_VME_MASTER_OSSPEC_HDL  master_osspec_hdl; 
    GEF_UINT64                 phys_addr;
    GEF_UINT64                 virt_addr;
    GEF_UINT64                 drv_map_hdl;
    GEF_UINT32                 size;
    GEF_UINT32                 offset;
}GEF_CONDITIONALLY_PACKED_STRUCT GEF_VME_MAP_MASTER_INFO;

/**
 * Type: GEF_VME_MAP_SLAVE_INFO
 *
 * Description:
 *   VME Slave Map info structure.
 *   Supported OSA Calls:
 *     GEF_VME_FRAMEWORK_CODE_MAP_SLAVE,
 *
 * slave_osspec_hdl  - Handle to os specific handle.
 * phys_addr         - Physical address
 * virt_addr         - Virtual address
 * size              - size requested
 *
 */
typedef struct
{
    GEF_VME_SLAVE_OSSPEC_HDL   slave_osspec_hdl; 
    GEF_UINT64                 phys_addr;
    GEF_UINT64                 virt_addr;
    GEF_UINT64                 drv_map_hdl;
    GEF_UINT32                 size;
    GEF_UINT32                 offset;
}GEF_CONDITIONALLY_PACKED_STRUCT GEF_VME_MAP_SLAVE_INFO;

/**
 * Type: GEF_VME_UNMAP_SLAVE_INFO
 *
 * Description:
 *   VME Slave UnMap info structure.
 *   Supported OSA Calls:
 *     GEF_VME_FRAMEWORK_CODE_UNMAP_SLAVE,
 *
 * slave_osspec_hdl  - Handle to os specific handle.
 * phys_addr         - Physical address
 * virt_addr         - Virtual address
 * size              - size requested
 *
 */
typedef struct
{
    GEF_VME_SLAVE_OSSPEC_HDL   slave_osspec_hdl; 
    GEF_UINT64                 drv_map_hdl;
}GEF_CONDITIONALLY_PACKED_STRUCT GEF_VME_UNMAP_SLAVE_INFO;

/**
 * Type: GEF_VME_UNMAP_MASTER_INFO
 *
 * Description:
 *   VME Slave UnMap info structure.
 *   Supported OSA Calls:
 *     GEF_VME_FRAMEWORK_CODE_UNMAP_MASTER,
 *
 * master_osspec_hdl - Handle to os specific handle.
 * phys_addr         - Physical address
 * virt_addr         - Virtual address
 * size              - size requested
 *
 */
typedef struct
{
    GEF_VME_MASTER_OSSPEC_HDL  master_osspec_hdl; 
    GEF_UINT64                 drv_map_hdl;
}GEF_CONDITIONALLY_PACKED_STRUCT GEF_VME_UNMAP_MASTER_INFO;

/**
 * Type: GEF_VME_DRV_ALLOC_DMA_BUF_INFO
 *
 * Description:
 *   VME Allocate DMA Buffer info structure.
 *   Supported OSA Calls:
 *     GEF_VME_FRAMEWORK_CODE_ALLOC_DMA_BUF
 *
 * dma_osspec_hdl - Handle to <GEF_VME_DMA_OSSPEC_HDL>.
 * size           - Size of kernel mapped memory
 * phys_addr      - physical address
 * virt_addr      - virtual address
 *
 */
typedef struct
{
    GEF_VME_DMA_OSSPEC_HDL  dma_osspec_hdl;
    GEF_UINT64              phys_addr;
    GEF_UINT64              virt_addr;
    GEF_UINT32              size;
}GEF_CONDITIONALLY_PACKED_STRUCT GEF_VME_DRV_ALLOC_DMA_BUF_INFO;

/**
 * Type: GEF_VME_DRV_VERSION_INFO
 *
 * Description:
 *   VME Driver Version info structure.
 *   Supported OSA Calls:
 *     GEF_VME_FRAMEWORK_CODE_GET_DRV_VERSION
 *
 * version        - Driver version structure.
 *
 */
typedef struct
{
    GEF_VERSION version;
}GEF_CONDITIONALLY_PACKED_STRUCT GEF_VME_DRV_VERSION_INFO;

/**
 * Type: GEF_VME_DRV_VOWN_INFO
 *
 * Description:
 *   VME Driver VOWN info structure.
 *   Supported OSA Calls:
 *     GEF_VME_FRAMEWORK_CODE_ACQUIRE_BUS_OWNERSHIP
 *     
 *
 * timeout           - timeout for acquiring bus ownership.
 *
 */
typedef struct
{
    struct timeval    timeout;
}GEF_CONDITIONALLY_PACKED_STRUCT GEF_VME_DRV_VOWN_INFO;

/**
 * Type: GEF_VME_DRV_BYTESWAP_INFO
 *
 * Description:
 *   VME Byte Swap info structure.
 *   Supported OSA Calls:
 *     GEF_VME_FRAMEWORK_CODE_SET_RD_WR_BYTESWAP,
 *     GEF_VME_FRAMEWORK_CODE_GET_RD_WR_BYTESWAP
 *
 * master_osspec_hdl - Handle to <GEF_VME_MASTER_OSSPEC_HDL>.
 * endian            - Endianess of the type <GEF_ENDIAN>.
 *
 */
typedef struct
{
  GEF_VME_MASTER_OSSPEC_HDL  master_osspec_hdl;
  GEF_ENDIAN                 endian;
}GEF_CONDITIONALLY_PACKED_STRUCT GEF_VME_DRV_BYTESWAP_INFO;

/**
 * Type: GEF_VME_HW_BYTESWAP_INFO
 *
 * Description:
 *   VME hardware Byte Swap info structure.
 *   Supported OSA Calls:
 *     GEF_VME_FRAMEWORK_CODE_SET_MASTER_HW_BYTESWAP,
 *     GEF_VME_FRAMEWORK_CODE_GET_MASTER_HW_BYTESWAP,
 *     GEF_VME_FRAMEWORK_CODE_SET_SLAVE_HW_BYTESWAP,
 *     GEF_VME_FRAMEWORK_CODE_GET_SLAVE_HW_BYTESWAP
 *
 * byteswap         - Byte swap of the type <GEF_HW_BYTESWAP>.
 *
 */
typedef struct
{
  GEF_HW_BYTESWAP            byteswap;
}GEF_CONDITIONALLY_PACKED_STRUCT GEF_VME_HW_BYTESWAP_INFO;


/**
 * Type: GEF_VME_DRV_TIME_OFF_BUS_INFO
 *
 * Description:
 *   VME bus controller min time off bus info structure.
 *   Supported OSA Calls:
 *     GEF_VME_FRAMEWORK_CODE_SET_TIME_OFF_BUS
 *     GEF_VME_FRAMEWORK_CODE_GET_TIME_OFF_BUS
 *
 * time_off    - min time off bus.
 *
 */
typedef struct
{
  GEF_VME_TIME_OFF_BUS time_off;
}GEF_CONDITIONALLY_PACKED_STRUCT GEF_VME_DRV_TIME_OFF_BUS_INFO;

/**
 * Type: GEF_VME_DRV_TIME_ON_BUS_INFO
 *
 * Description:
 *   VME bus controller max time on bus info structure.
 *   Supported OSA Calls:
 *     GEF_VME_FRAMEWORK_CODE_SET_TIME_ON_BUS
 *     GEF_VME_FRAMEWORK_CODE_GET_TIME_ON_BUS
 *
 * time_on    - max time on bus.
 *
 */
typedef struct
{
  GEF_VME_TIME_ON_BUS time_on;
}GEF_CONDITIONALLY_PACKED_STRUCT GEF_VME_DRV_TIME_ON_BUS_INFO;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __GEFCMN_VME_FRAMEWORK_H */

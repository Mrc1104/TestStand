/*
 * File:
 *    gefcmn_vme_defs.h
 *
 * Description:
 *    This interface file defines the common defines for the VME facility.
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

#ifndef __GEFCMN_VME_DEFS_H
#define __GEFCMN_VME_DEFS_H		

/**
 * Title: SBC VME Common API Definitions
 *
 * Description:
 *    This is a common header file for the Common API Library.
 *
 * Include Files:
 *    gefcmn_common.h
 *
 * Libraries:
 *    N/A
 *
 * Kernel Modules:
 *    N/A
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
*/

#include "gef/gefcmn_common.h"   

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * Group: Types and Constants
 */	
 
/* private structures */

/**
 * Type: GEF_VME_BUS_HDL
 *
 * Description:
 *      This private structure is used to hold the bus_hdl.
 *        
 */
typedef struct _GEF_VME_BUS     *GEF_VME_BUS_HDL;

/**
 * Type: GEF_VME_MASTER_HDL
 *
 * Description:
 *      This private structure is used to hold the master_hdl.
 *        
 */
typedef struct _GEF_VME_MASTER  *GEF_VME_MASTER_HDL;

/**
 * Type: GEF_VME_SLAVE_HDL
 *
 * Description:
 *      This private structure is used to hold the slave_hdl.
 *        
 */
typedef struct _GEF_VME_SLAVE   *GEF_VME_SLAVE_HDL;

/**
 * Type: GEF_VME_WAIT_HDL
 *
 * Description:
 *      This private structure is used to hold the wait_hdl.
 *        
 */
typedef struct _GEF_VME_WAIT    *GEF_VME_WAIT_HDL;

/**
 * Type: GEF_VME_DMA_HDL
 *
 * Description:
 *      This private structure is used to hold the dma_hdl.
 *        
 */
typedef struct _GEF_VME_DMA     *GEF_VME_DMA_HDL;

/**
 * Type: GEF_VME_LM_HDL
 *
 * Description:
 *      This private structure is used to hold the lm_hdl.
 *        
 */
typedef struct _GEF_VME_LM      *GEF_VME_LM_HDL;

/**
 * Type: GEF_VME_VRAI_HDL
 *
 * Description:
 *      This private structure is used to hold the vrai_hdl.
 *        
 */
typedef struct _GEF_VME_VRAI    *GEF_VME_VRAI_HDL;

/* Enumerations */
/**
 * Type: GEF_VME_ADDR_MOD
 *
 * Description:
 *      Enumerations to define the VME address modes.   
 *        
 * GEF_VME_ADDR_MOD_A64MB - A64 multiplex block transfer
 * GEF_VME_ADDR_MOD_A64S  - A64 single cycle access
 * GEF_VME_ADDR_MOD_A64B  - A64 block transfer
 * GEF_VME_ADDR_MOD_A64LK - A64 lock command
 * GEF_VME_ADDR_MOD_A32LK  - A32 lock command
 * GEF_VME_ADDR_MOD_A32UMB - A32 nonprivileged multiplex block transfer
 * GEF_VME_ADDR_MOD_A32UD  - A32 nonprivileged data access
 * GEF_VME_ADDR_MOD_A32UP  - A32 nonprivileged program access
 * GEF_VME_ADDR_MOD_A32UB  - A32 nonprivileged block transfer
 * GEF_VME_ADDR_MOD_A32SMB  - A32 supervisory multiplex block transfer
 * GEF_VME_ADDR_MOD_A32SD  - A32 supervisory data access
 * GEF_VME_ADDR_MOD_A32SP  - A32 supervisory program access
 * GEF_VME_ADDR_MOD_A32SB  - A32 supervisory block transfer
 * GEF_VME_ADDR_MOD_A2eVME_6U  - 2eVME for 6U bus modules (address size in XAM code)
 * GEF_VME_ADDR_MOD_A2eVME_3U  -  2eVME for 3U bus modules (address size in XAM code)
 * GEF_VME_ADDR_MOD_A16U  - A16 nonprivileged access
 * GEF_VME_ADDR_MOD_A16LK  - A16 lock cycle
 * GEF_VME_ADDR_MOD_A16S  - A16 supervisory access
 * GEF_VME_ADDR_MOD_CR_CSR  - Configuration ROM/Control & status register access
 * GEF_VME_ADDR_MOD_A24LK  - A24 lock command
 * GEF_VME_ADDR_MOD_A40  - A40 single cycle access
 * GEF_VME_ADDR_MOD_A40LK  - A40 lock command
 * GEF_VME_ADDR_MOD_A40B  - A40 block transfer
 * GEF_VME_ADDR_MOD_A24UMB  - A24 nonprivileged multiplex block transfer
 * GEF_VME_ADDR_MOD_A24UD  - A24 nonprivileged data access
 * GEF_VME_ADDR_MOD_A24UP  - A24 nonprivileged program access
 * GEF_VME_ADDR_MOD_A24UB  - A24 nonprivileged block transfer
 * GEF_VME_ADDR_MOD_A24SMB  - A24 supervisory multiplex block transfer
 * GEF_VME_ADDR_MOD_A24SD  - A24 supervisory data access
 * GEF_VME_ADDR_MOD_A24SP  - A24 supervisory program access
 * GEF_VME_ADDR_MOD_A24SB  - A24 supervisory block transfer
 */
typedef enum
{
  GEF_VME_ADDR_MOD_A64MB     = 0x00, /* A64 multiplex block transfer */
  GEF_VME_ADDR_MOD_A64S      = 0x01, /* A64 single cycle access */
  GEF_VME_ADDR_MOD_A64B      = 0x03, /* A64 block transfer */
  GEF_VME_ADDR_MOD_A64LK     = 0x04, /* A64 lock command */
  GEF_VME_ADDR_MOD_A32LK     = 0x05, /* A32 lock command */
  GEF_VME_ADDR_MOD_A32UMB    = 0x08, /* A32 nonprivileged multiplex block transfer */
  GEF_VME_ADDR_MOD_A32UD     = 0x09, /* A32 nonprivileged data access */
  GEF_VME_ADDR_MOD_A32UP     = 0x0A, /* A32 nonprivileged program access */
  GEF_VME_ADDR_MOD_A32UB     = 0x0B, /* A32 nonprivileged block transfer */
  GEF_VME_ADDR_MOD_A32SMB    = 0x0C, /* A32 supervisory multiplex block transfer */
  GEF_VME_ADDR_MOD_A32SD     = 0x0D, /* A32 supervisory data access */
  GEF_VME_ADDR_MOD_A32SP     = 0x0E, /* A32 supervisory program access */
  GEF_VME_ADDR_MOD_A32SB     = 0x0F, /* A32 supervisory block transfer */
  GEF_VME_ADDR_MOD_A2eVME_6U = 0x20, /* 2eVME for 6U bus modules (address size in XAM code) */
  GEF_VME_ADDR_MOD_A2eVME_3U = 0x21, /* 2eVME for 3U bus modules (address size in XAM code) */
  GEF_VME_ADDR_MOD_A16U      = 0x29, /* A16 nonprivileged access */
  GEF_VME_ADDR_MOD_A16LK     = 0x2C, /* A16 lock cycle */
  GEF_VME_ADDR_MOD_A16S      = 0x2D, /* A16 supervisory access */
  GEF_VME_ADDR_MOD_CR_CSR    = 0x2F, /* Configuration ROM/Sontrol & status register access */
  GEF_VME_ADDR_MOD_A24LK     = 0x32, /* A24 lock command */
  GEF_VME_ADDR_MOD_A40       = 0x34, /* A40 single cycle access */
  GEF_VME_ADDR_MOD_A40LK     = 0x35, /* A40 lock command */
  GEF_VME_ADDR_MOD_A40B      = 0x37, /* A40 block transfer */
  GEF_VME_ADDR_MOD_A24UMB    = 0x38, /* A24 nonprivileged multiplex block transfer */
  GEF_VME_ADDR_MOD_A24UD     = 0x39, /* A24 nonprivileged data access */
  GEF_VME_ADDR_MOD_A24UP     = 0x3A, /* A24 nonprivileged program access */
  GEF_VME_ADDR_MOD_A24UB     = 0x3B, /* A24 nonprivileged block transfer */
  GEF_VME_ADDR_MOD_A24SMB    = 0x3C, /* A24 supervisory multiplex block transfer */
  GEF_VME_ADDR_MOD_A24SD     = 0x3D, /* A24 supervisory data access */
  GEF_VME_ADDR_MOD_A24SP     = 0x3E, /* A24 supervisory program access */
  GEF_VME_ADDR_MOD_A24SB     = 0x3F, /* A24 supervisory block transfer */
  GEF_VME_ADDR_MOD_LAST      = 31    /* Keep as number of elements */
} GEF_VME_ADDR_MOD;
/**
 * Type: GEF_VME_EXTENDED_ADDR_MOD
 *
 * Description:
 *      Enumerations to define the VME extended address modes.   
 *        
 * GEF_VME_EXTENDED_ADDR_MOD_A32_D64_2eVME - A32/D64 2eVME Transfer.
 * GEF_VME_EXTENDED_ADDR_MOD_A64_D64_2eVME - A64/D64 2eVME Transfer.
 * GEF_VME_EXTENDED_ADDR_MOD_A32_D64_2eSST - A32/D64 2eSST Transfer.
 * GEF_VME_EXTENDED_ADDR_MOD_A64_D64_2eSST - A64/D64 2eSST Transfer.
 * GEF_VME_EXTENDED_ADDR_MOD_A32_D64_BROADCAST_2eSST - A32/D64 2eSST broadcast Transfer.
 * GEF_VME_EXTENDED_ADDR_MOD_A64_D64_BROADCAST_2eVME - A32/D64 2eVME broadcast Transfer.
 */
typedef enum
{
  GEF_VME_EXTENDED_ADDR_MOD_A32_D64_2eVME           = 0x01, /* A32 2eVME */
  GEF_VME_EXTENDED_ADDR_MOD_A64_D64_2eVME           = 0x02, /* A64 2eVME */
  GEF_VME_EXTENDED_ADDR_MOD_A32_D64_2eSST           = 0x11, /* A32/D64 2eSST */
  GEF_VME_EXTENDED_ADDR_MOD_A64_D64_2eSST           = 0x12, /* A64/D64 2eSST */
  GEF_VME_EXTENDED_ADDR_MOD_A32_D64_BROADCAST_2eSST = 0x21, /* A32/D64, Broadcast 2eSST */
  GEF_VME_EXTENDED_ADDR_MOD_A64_D64_BROADCAST_2eVME = 0x22, /* A64/D64, Broadcast 2eSST */
  GEF_VME_EXTENDED_ADDR_MOD_LAST                    = 6     /* Keep as number of elements */
} GEF_VME_EXTENDED_ADDR_MOD;

/**
 * Type: GEF_VME_2ESST_RATE
 *
 * Description:
 *      This enumeration defines the 2eSST Transfer Rate
 *        
 * GEF_VME_2ESST_RATE_INVALID - Default value for non 2eSST transfer mode.
 * GEF_VME_2ESST_RATE_160 - 160 MB/s 2eSST Transfer Rate.
 * GEF_VME_2ESST_RATE_267 - 267 MB/s 2eSST Transfer Rate.
 * GEF_VME_2ESST_RATE_320 - 320 MB/s 2eSST Transfer Rate.
 * GEF_VME_2ESST_RATE_LAST - Number of elements in enumeration.
 */
typedef enum 
{
  GEF_VME_2ESST_RATE_INVALID = 0x0,
  GEF_VME_2ESST_RATE_160,
  GEF_VME_2ESST_RATE_267,
  GEF_VME_2ESST_RATE_320,
  GEF_VME_2ESST_RATE_LAST,
} GEF_VME_2ESST_RATE;


/**
 * Type: GEF_VME_ADDR_SPACE
 *
 * Description:
 *    An enumeration to set VME Address space
 *
 * GEF_VME_ADDR_SPACE_A16 - A16 Address space.
 * GEF_VME_ADDR_SPACE_A24 - A24 Address space.
 * GEF_VME_ADDR_SPACE_A32 - A32 Address space.
 * GEF_VME_ADDR_SPACE_A64 - A64 Address space.
 * GEF_VME_ADDR_SPACE_CRCSR - Configuration ROM/Control&Status Register Address space.
 * GEF_VME_ADDR_SPACE_USER1 - User Defined Address space.
 * GEF_VME_ADDR_SPACE_USER2 - User Defined Address space.
 * GEF_VME_ADDR_SPACE_USER3 - User Defined Address space.
 * GEF_VME_ADDR_SPACE_USER4 - User Defined Address space.
 * GEF_VME_ADDR_SPACE_LAST - Number of elements in enumeration.
 */
typedef enum
{
  GEF_VME_ADDR_SPACE_A16,     /* Short VMEbus address space */
  GEF_VME_ADDR_SPACE_A24,     /* Standard VMEbus address space */
  GEF_VME_ADDR_SPACE_A32,     /* Extended VMEbus address space */
  GEF_VME_ADDR_SPACE_A64,
  GEF_VME_ADDR_SPACE_CRCSR,
  GEF_VME_ADDR_SPACE_USER1,
  GEF_VME_ADDR_SPACE_USER2,
  GEF_VME_ADDR_SPACE_USER3,
  GEF_VME_ADDR_SPACE_USER4,
  GEF_VME_ADDR_SPACE_LAST,
} GEF_VME_ADDR_SPACE;

/**
 * Type: GEF_VME_DWIDTH
 *
 * Description:
 *   An enumeration to set VME data width
 *
 * GEF_VME_DWIDTH_D8 - 1 Byte 
 * GEF_VME_DWIDTH_D16 - 2 Bytes 
 * GEF_VME_DWIDTH_D32 - 4 Bytes 
 * GEF_VME_DWIDTH_D64 - 8 Bytes 
 */
typedef enum
{
  GEF_VME_DWIDTH_D8   = 1,   /* 1 Byte  */
  GEF_VME_DWIDTH_D16  = 2,   /* 2 Bytes */
  GEF_VME_DWIDTH_D32  = 4,   /* 4 Bytes */
  GEF_VME_DWIDTH_D64  = 8,   /* 8 Bytes */
  GEF_VME_DWIDTH_LAST = 4    /* Keep as number of elements */
} GEF_VME_DWIDTH;

/**
 * Type: GEF_VME_ADDR_MODE
 *
 * Description:
 *   An enumeration to set VME address mode
 *
 * GEF_VME_ADDR_MODE_DEFAULT - set to default address mode.
 * GEF_VME_ADDR_MODE_USER - set to user memory address mode.
 * GEF_VME_ADDR_MODE_SUPER - set to super user address mode.
 * GEF_VME_ADDR_MODE_DATA - set to data memory address mode.
 * GEF_VME_ADDR_MODE_PROGRAM - set to program address mode.
 */
typedef enum
{
  /* These may be ored, keep as power of 2 */
  GEF_VME_ADDR_MODE_DEFAULT = 0x00000000,
  GEF_VME_ADDR_MODE_USER    = 0x00000001,         
  GEF_VME_ADDR_MODE_SUPER   = 0x00000002,
  GEF_VME_ADDR_MODE_DATA    = 0x00000004,
  GEF_VME_ADDR_MODE_PROGRAM = 0x00000008,
  GEF_VME_ADDR_MODE_LAST    = 5 /* Keep as number of elements */
} GEF_VME_ADDR_MODE;

/**
 * Type: GEF_VME_TRANSFER_MODE
 *
 * Description:
 *   An enumeration to set VME Transfer mode
 *
 * GEF_VME_TRANSFER_MODE_SCT - Single Cycle Transaction
 * GEF_VME_TRANSFER_MODE_BLT - BLock Transfer (BLT).
 * GEF_VME_TRANSFER_MODE_MBLT - Multiplexed BLock Transfer (MBLT).
 * GEF_VME_TRANSFER_MODE_2eVME - Dual edge VME protocol
 * GEF_VME_TRANSFER_MODE_2eSST - Dual edge Source Synchronous data Transfer 
 * GEF_VME_TRANSFER_MODE_2eSSTB - Dual edge Source Synchronous data Transfer Broadcast
 */
typedef enum
{
  /* These may be ored, keep as power of 2 */
  GEF_VME_TRANSFER_MODE_SCT     = 0x00000001,
  GEF_VME_TRANSFER_MODE_BLT     = 0x00000002,
  GEF_VME_TRANSFER_MODE_MBLT    = 0x00000004,
  GEF_VME_TRANSFER_MODE_2eVME   = 0x00000008,
  GEF_VME_TRANSFER_MODE_2eSST   = 0x00000010,
  GEF_VME_TRANSFER_MODE_2eSSTB  = 0x00000020,
  GEF_VME_TRANSFER_MODE_LAST    = 6 /* Keep as number of elements */
} GEF_VME_TRANSFER_MODE;

/**
 * Type: GEF_VME_BROADCAST_ID
 *
 * Description:
 *   An enumeration to set broadcast id.(Tempe only)
 *
 * GEF_VME_BROADCAST_ID_DISABLE - Disable broadcast id
 * GEF_VME_BROADCAST_ID_1       - Broadcast id set to 1 
 * GEF_VME_BROADCAST_ID_2       - Broadcast id set to 2
 * GEF_VME_BROADCAST_ID_3       - Broadcast id set to 3
 * GEF_VME_BROADCAST_ID_4       - Broadcast id set to 4
 * GEF_VME_BROADCAST_ID_5       - Broadcast id set to 5
 * GEF_VME_BROADCAST_ID_6       - Broadcast id set to 6
 * GEF_VME_BROADCAST_ID_7       - Broadcast id set to 7
 * GEF_VME_BROADCAST_ID_8       - Broadcast id set to 8
 * GEF_VME_BROADCAST_ID_9       - Broadcast id set to 9
 * GEF_VME_BROADCAST_ID_10      - Broadcast id set to 10
 * GEF_VME_BROADCAST_ID_11      - Broadcast id set to 11
 * GEF_VME_BROADCAST_ID_12      - Broadcast id set to 12
 * GEF_VME_BROADCAST_ID_13      - Broadcast id set to 13
 * GEF_VME_BROADCAST_ID_14      - Broadcast id set to 14
 * GEF_VME_BROADCAST_ID_15      - Broadcast id set to 15
 * GEF_VME_BROADCAST_ID_16      - Broadcast id set to 16
 * GEF_VME_BROADCAST_ID_17      - Broadcast id set to 17
 * GEF_VME_BROADCAST_ID_18      - Broadcast id set to 18
 * GEF_VME_BROADCAST_ID_19      - Broadcast id set to 19
 * GEF_VME_BROADCAST_ID_20      - Broadcast id set to 20
 * GEF_VME_BROADCAST_ID_21      - Broadcast id set to 21
 */
typedef enum
{
  GEF_VME_BROADCAST_ID_DISABLE = 0x00000000,   /* Tempe Only */
  GEF_VME_BROADCAST_ID_1       = 0x00000001,   /* Tempe Only */
  GEF_VME_BROADCAST_ID_2       = 0x00000002,   /* Tempe Only */
  GEF_VME_BROADCAST_ID_3       = 0x00000004,   /* Tempe Only */
  GEF_VME_BROADCAST_ID_4       = 0x00000008,   /* Tempe Only */
  GEF_VME_BROADCAST_ID_5       = 0x00000010,   /* Tempe Only */
  GEF_VME_BROADCAST_ID_6       = 0x00000020,   /* Tempe Only */
  GEF_VME_BROADCAST_ID_7       = 0x00000040,   /* Tempe Only */
  GEF_VME_BROADCAST_ID_8       = 0x00000080,   /* Tempe Only */
  GEF_VME_BROADCAST_ID_9       = 0x00000100,   /* Tempe Only */
  GEF_VME_BROADCAST_ID_10      = 0x00000200,   /* Tempe Only */
  GEF_VME_BROADCAST_ID_11      = 0x00000400,   /* Tempe Only */
  GEF_VME_BROADCAST_ID_12      = 0x00000800,   /* Tempe Only */
  GEF_VME_BROADCAST_ID_13      = 0x00001000,   /* Tempe Only */
  GEF_VME_BROADCAST_ID_14      = 0x00002000,   /* Tempe Only */
  GEF_VME_BROADCAST_ID_15      = 0x00004000,   /* Tempe Only */
  GEF_VME_BROADCAST_ID_16      = 0x00008000,   /* Tempe Only */
  GEF_VME_BROADCAST_ID_17      = 0x00010000,   /* Tempe Only */
  GEF_VME_BROADCAST_ID_18      = 0x00020000,   /* Tempe Only */
  GEF_VME_BROADCAST_ID_19      = 0x00040000,   /* Tempe Only */
  GEF_VME_BROADCAST_ID_20      = 0x00080000,   /* Tempe Only */
  GEF_VME_BROADCAST_ID_21      = 0x00100000,   /* Tempe Only */
  GEF_VME_BROADCAST_ID_LAST    = 22, /* Keep as number of elements */
} GEF_VME_BROADCAST_ID;

/**
 * Type: GEF_VME_TRANSFER_MAX_DWIDTH
 *
 * Description:
 *   An enumeration to set maximum data width for VME transfer
 *
 * GEF_VME_TRANSFER_MAX_DWIDTH_8 - 1 Byte
 * GEF_VME_TRANSFER_MAX_DWIDTH_16 - 2 Byte
 * GEF_VME_TRANSFER_MAX_DWIDTH_32 - 4 Byte
 * GEF_VME_TRANSFER_MAX_DWIDTH_64 - 8 Byte
 */
typedef enum
{
  GEF_VME_TRANSFER_MAX_DWIDTH_8,
  GEF_VME_TRANSFER_MAX_DWIDTH_16,
  GEF_VME_TRANSFER_MAX_DWIDTH_32,
  GEF_VME_TRANSFER_MAX_DWIDTH_64,
  GEF_VME_TRANSFER_MAX_DWIDTH_LAST,
} GEF_VME_TRANSFER_MAX_DWIDTH;

/**
 * Type: GEF_VME_WND_FLAGS
 *
 * Description:
 *   An enumeration to set VME window flags. These flags may be ored, keep as power of 2.
 *
 * GEF_VME_WND_PCI_IO_SPACE - PCI_IO_SPACE window (Master and Slave - Universe Only)
 * GEF_VME_WND_EXCLUSIVE    - Exclusive access ( Master )
 * GEF_VME_WND_PWEN         - Posted write enable (Master and Slave - Universe Only)
 * GEF_VME_WND_PCI_CONFIG   - PCI config space (Slave - Universe Only)
 * GEF_VME_WND_RMW          - Read/Write/Modify window (Slave - Universe Only)
 * GEF_VME_WND_64_BIT       - 64 bit window (Slave - Universe Only)
 * GEF_VME_WND_PREN         - PRead Eable (Slave - Universe Only)
 * GEF_VME_WND_TH           - This field sets a threshold for when read-ahead prefetching resumes. 
 *                            If set, prefetching resumes once the FIFO is half empty. If cleared prefetching resumes once  
 *                             the FIFO is completely empty (Slave  Tempe Only).
 *                            
 *                            
 *                            
 * GEF_VME_WND_VFS1         - VFS (Virtual FIFO Size)is used to set the FIFO size for inbound prefetch reads.
 *                            The selection of a virtual FIFO size affects the number of initial prefetch read cycles and the
 *                            number of subsequent prefetch read cycles.(Slave  Tempe Only).
 * GEF_VME_WND_VFS0         - VFS (Virtual FIFO Size)is used to set the FIFO size for inbound prefetch reads.
 *                            The selection of a virtual FIFO size affects the number of initial prefetch read cycles and the
 *                            number of subsequent prefetch read cycles.(Slave  Tempe Only).
 *  > Virtual FIFO Size
 *  >
 *  > _______________________________________________________
 *  >|  VFS  |  FIFO Size | Initial Read | Subsequent Reads |
 *  >|       |   Bytes    |      Bytes   |   Bytes          |
 *	>|_______|____________|______________|__________________|
 *  >|   00b |   64       |      64      |   32             |
 *  >|   01b |   128      |      128     |   64             |
 *  >|   10b |   256      |      256     |   128            |
 *  >|   11b |   512      |      512     |   256            |
 *  >|_______|____________|______________|__________________|
 */
typedef enum
{
  /* These may be ored, keep as power of 2 */
  GEF_VME_WND_PCI_IO_SPACE  = 0x00000001, /* Master and Slave - Universe Only */
  GEF_VME_WND_EXCLUSIVE     = 0x10000000, /* Master */
  GEF_VME_WND_PWEN          = 0x40000000, /* Master and Slave - Universe Only */
  GEF_VME_WND_PCI_CONFIG    = 0x00000002, /* Slave - Universe Only */
  GEF_VME_WND_RMW           = 0x00000040, /* Slave - Universe Only */
  GEF_VME_WND_64_BIT        = 0x00000080, /* Slave - Universe Only */
  GEF_VME_WND_PREN          = 0x20000000, /* Slave - Universe Only */
  GEF_VME_WND_TH            = 0x00040000, /* Slave - Tempe Only */
  GEF_VME_WND_VFS1          = 0x00020000, /* Slave - Tempe Only */
  GEF_VME_WND_VFS0          = 0x00010000, /* Slave - Tempe Only */
  GEF_VME_WND_FLAGS_LAST    = 10
} GEF_VME_WND_FLAGS;

/**
 * Type: GEF_VME_BUS_REQUEST_MODE
 *
 * Description:
 *   An enumeration to set VME bus request modes.
 *
 *  GEF_VME_BUS_REQUEST_DEMAND - VMEbus request demand mode
 *  GEF_VME_BUS_REQUEST_FAIR   - VMEbus request fair mode
 *
 */
typedef enum
{
  GEF_VME_BUS_REQUEST_DEMAND,    /* VMEbus request mode demand */
  GEF_VME_BUS_REQUEST_FAIR,      /* VMEbus request mode fair */
  GEF_VME_BUS_REQUEST_MODE_LAST,
} GEF_VME_BUS_REQUEST_MODE;

/**
 * Type: GEF_VME_BUS_RELEASE_MODE
 *
 * Description:
 *   An enumeration to set VME bus release modes.
 *
 * GEF_VME_BUS_RELEASE_WHEN_DONE            - VMEbus release when done.
 * GEF_VME_BUS_RELEASE_ON_REQUEST           - VMEbus release on request.
 * GEF_VME_BUS_RELEASE_WHEN_DONE_OR_REQUEST - release when done or request.
 * GEF_VME_BUS_RELEASE_WHEN_DONE_OR_BCLR    - release when done or BCLR.
 *
 */
typedef enum
{
  GEF_VME_BUS_RELEASE_WHEN_DONE,            /* VMEbus release when done     */
  GEF_VME_BUS_RELEASE_ON_REQUEST,           /* VMEbus release on request    */
  GEF_VME_BUS_RELEASE_WHEN_DONE_OR_REQUEST, /* release when done or request */
  GEF_VME_BUS_RELEASE_WHEN_DONE_OR_BCLR,    /* release when done or BCLR    */
  GEF_VME_BUS_RELEASE_MODE_LAST,
} GEF_VME_BUS_RELEASE_MODE;

/**
 * Type: GEF_VME_BUS_REQUEST_LEVEL
 *
 * Description:
 *   An enumeration to set VME bus request level.
 *
 * GEF_VME_BUS_REQUEST_LEVEL_0	- Request level set to 0.    
 * GEF_VME_BUS_REQUEST_LEVEL_1	- Request level set to 1.           
 * GEF_VME_BUS_REQUEST_LEVEL_2	- Request level set to 2. 
 * GEF_VME_BUS_REQUEST_LEVEL_3	- Request level set to 3.   
 *
 */
typedef enum
{
  GEF_VME_BUS_REQUEST_LEVEL_0	= 0,    
  GEF_VME_BUS_REQUEST_LEVEL_1	= 1,           
  GEF_VME_BUS_REQUEST_LEVEL_2	= 2, 
  GEF_VME_BUS_REQUEST_LEVEL_3	= 3,     
  GEF_VME_BUS_REQUEST_LEVEL_LAST,
} GEF_VME_BUS_REQUEST_LEVEL;

/**
 * Type: GEF_VME_BUS_ARB_MODE
 *
 * Description:
 *   An enumeration to set VME bus arbitration mode.
 *
 * GEF_VME_BUS_ARB_ROUND_ROBIN - VMEbus round-robin mode arbitration
 * GEF_VME_BUS_ARB_PRIORITY    - VMEbus priority mode arbitration
 *
 */
typedef enum
{
  GEF_VME_BUS_ARB_ROUND_ROBIN,   /* VMEbus round-robin mode arbitration */
  GEF_VME_BUS_ARB_PRIORITY,      /* VMEbus priority mode arbitration */
  GEF_VME_BUS_ARB_MODE_LAST,
} GEF_VME_BUS_ARB_MODE;

/**
 * Type: GEF_VME_DMA_FLAGS
 *
 * Description:
 *   An enumeration to set VME DMA flags.  Some flags are only supported by 
 *   SBC's with a specific PCI->VME bridge.  See flag description for any 
 *   restrictions.
 *
 * GEF_VME_DMA_DEFAULT      - Default value for DMA transfer flags.
 * GEF_VME_DMA_64_BIT       - Universe Only, 64 bit DMA transfer.
 * GEF_VME_DMA_VON_32       - Tempe
 * GEF_VME_DMA_VON_64       - Tempe
 * GEF_VME_DMA_VON_128      - Tempe
 * GEF_VME_DMA_VON_256      - Universe and Tempe
 * GEF_VME_DMA_VON_512      - Universe and Tempe
 * GEF_VME_DMA_VON_1024     - Universe and Tempe
 * GEF_VME_DMA_VON_2048     - Universe and Tempe
 * GEF_VME_DMA_VON_4096     - Universe and Tempe
 * GEF_VME_DMA_VON_8192     - Universe
 * GEF_VME_DMA_VON_16384    - Universe
 * GEF_VME_DMA_VOFF_0us     - Universe and Tempe
 * GEF_VME_DMA_VOFF_1us     - Tempe 
 * GEF_VME_DMA_VOFF_2us     - Universe and Tempe
 * GEF_VME_DMA_VOFF_4us     - Universe and Tempe
 * GEF_VME_DMA_VOFF_8us     - Universe and Tempe
 * GEF_VME_DMA_VOFF_16us    - Universe and Tempe
 * GEF_VME_DMA_VOFF_32us    - Universe and Tempe
 * GEF_VME_DMA_VOFF_64us    - Universe and Tempe
 * GEF_VME_DMA_VOFF_128us   - Universe
 * GEF_VME_DMA_VOFF_256us   - Universe
 * GEF_VME_DMA_VOFF_512us   - Universe
 * GEF_VME_DMA_VOFF_1024us  - Universe
 * GEF_VME_DMA_MODE_NON_INC - Universe
 * GEF_VME_DMA_VFAR         - Tempe Only, If this flag is set and a VMEbus cycle is terminated
 *                            with an exception, any data remaining in the FIFO is transferred 
 *                            to the destination, otherwise the data is discarded.
 * GEF_VME_DMA_PFAR         - Tempe Only, If this flag is set and a PCI/X bus cycle is terminated
 *                            with an exception, any data remaining in the FIFO is transferred to 
 *                            the destination, otherwise the data is discarded.  
 */
typedef enum
{
  GEF_VME_DMA_DEFAULT      = 0x00000000, /* Universe and Tempe */
  GEF_VME_DMA_64_BIT       = 0x00000001, /* Universe */

  /* VON nibble */
  GEF_VME_DMA_VON_0        = 0x00000000, /* Universe */
  GEF_VME_DMA_VON_32       = 0x00000010, /* Tempe */
  GEF_VME_DMA_VON_64       = 0x00000020, /* Tempe */
  GEF_VME_DMA_VON_128      = 0x00000030, /* Tempe */
  GEF_VME_DMA_VON_256      = 0x00000040, /* Universe and Tempe */
  GEF_VME_DMA_VON_512      = 0x00000050, /* Universe and Tempe */
  GEF_VME_DMA_VON_1024     = 0x00000060, /* Universe and Tempe */
  GEF_VME_DMA_VON_2048     = 0x00000070, /* Universe and Tempe */
  GEF_VME_DMA_VON_4096     = 0x00000080, /* Universe and Tempe */
  GEF_VME_DMA_VON_8192     = 0x00000090, /* Universe */
  GEF_VME_DMA_VON_16384    = 0x000000A0, /* Universe */

  /* VOFF nibble */
  GEF_VME_DMA_VOFF_0us     = 0x00000000, /* Universe and Tempe */
  GEF_VME_DMA_VOFF_1us     = 0x00000100, /* Tempe */
  GEF_VME_DMA_VOFF_2us     = 0x00000200, /* Universe and Tempe */
  GEF_VME_DMA_VOFF_4us     = 0x00000300, /* Universe and Tempe */
  GEF_VME_DMA_VOFF_8us     = 0x00000400, /* Universe and Tempe */
  GEF_VME_DMA_VOFF_16us    = 0x00000500, /* Universe and Tempe */
  GEF_VME_DMA_VOFF_32us    = 0x00000600, /* Universe and Tempe */
  GEF_VME_DMA_VOFF_64us    = 0x00000700, /* Universe and Tempe */
  GEF_VME_DMA_VOFF_128us   = 0x00000800, /* Universe */
  GEF_VME_DMA_VOFF_256us   = 0x00000900, /* Universe */
  GEF_VME_DMA_VOFF_512us   = 0x00000A00, /* Universe */
  GEF_VME_DMA_VOFF_1024us  = 0x00000B00, /* Universe */

  /* DMA Mode nibble */
  GEF_VME_DMA_MODE_NON_INC = 0x00001000, /* Universe Only */

  /* DMA exception handling */
  GEF_VME_DMA_VFAR         = 0x00010000, /* Tempe */
  GEF_VME_DMA_PFAR         = 0x00020000, /* Tempe */

  /* Number of entries */
  GEF_VME_DMA_FLAGS_LAST  = 28           /* Keep as number of elements */
} GEF_VME_DMA_FLAGS;

/**
 * Type: GEF_VME_INT_LEVEL
 *
 * Description:
 *   An enumeration to set VME interrupt level.
 *
 * GEF_VME_INT_VOWN      -    Universe Only 
 * GEF_VME_INT_VIRQ1     -    VME interrupt level1 
 * GEF_VME_INT_VIRQ2     -    VME interrupt level2 
 * GEF_VME_INT_VIRQ3     -    VME interrupt level3 
 * GEF_VME_INT_VIRQ4     -    VME interrupt level4 
 * GEF_VME_INT_VIRQ5     -    VME interrupt level5 
 * GEF_VME_INT_VIRQ6     -    VME interrupt level6 
 * GEF_VME_INT_VIRQ7     -    VME interrupt level7 
 * GEF_VME_INT_DMA0      -    DMA interrupt on Universe, DMA0 on Tempe 
 * GEF_VME_INT_LERR      -    PCI Error 
 * GEF_VME_INT_BERR      -    VME Error 
 * GEF_VME_INT_IRQ_EDGE  -    Edge interrupt source (Tempe Only). 
 * GEF_VME_INT_SW_IACK   -    This interrupt level is for the VMEbus Interrupt Acknowledge. 
 * GEF_VME_INT_SW_INT    -    Software interrupt (Universe Only) 
 * GEF_VME_INT_SYSFAIL   -    Sysfail interrupt
 * GEF_VME_INT_ACFAIL    -    This interrupt level is for the VMEbus ACFAILI_ signal.
 * GEF_VME_INT_MBOX0     -    Mailbox interrupt0
 * GEF_VME_INT_MBOX1     -    Mailbox interrupt1
 * GEF_VME_INT_MBOX2     -    Mailbox interrupt2
 * GEF_VME_INT_MBOX3     -    Mailbox interrupt3
 * GEF_VME_INT_LM0       -    Location monitor interrupt0
 * GEF_VME_INT_LM1       -    Location monitor interrupt1
 * GEF_VME_INT_LM2       -    Location monitor interrupt2
 * GEF_VME_INT_LM3       -    Location monitor interrupt3
 * GEF_VME_INT_DMA1      -    DMA1 interrupt (Tempe Only) 
 *
 */
typedef enum
{
  GEF_VME_INT_VOWN       = 0,  /* Universe Only */
  GEF_VME_INT_VIRQ1      = 1,
  GEF_VME_INT_VIRQ2      = 2,
  GEF_VME_INT_VIRQ3      = 3,
  GEF_VME_INT_VIRQ4      = 4,
  GEF_VME_INT_VIRQ5      = 5,
  GEF_VME_INT_VIRQ6      = 6,
  GEF_VME_INT_VIRQ7      = 7,
  GEF_VME_INT_DMA0       = 8,  /* DMA on Universe, DMA0 on Tempe */
  GEF_VME_INT_LERR       = 9,  /* PCI Error */
  GEF_VME_INT_BERR       = 10, /* VME Error */
  GEF_VME_INT_IRQ_EDGE   = 11, /* Tempe Only */
  GEF_VME_INT_SW_IACK    = 12,
  GEF_VME_INT_SW_INT     = 13, /* Universe Only */
  GEF_VME_INT_SYSFAIL    = 14,
  GEF_VME_INT_ACFAIL     = 15,
  GEF_VME_INT_MBOX0      = 16,
  GEF_VME_INT_MBOX1      = 17,
  GEF_VME_INT_MBOX2      = 18,
  GEF_VME_INT_MBOX3      = 19,
  GEF_VME_INT_LM0        = 20,
  GEF_VME_INT_LM1        = 21,
  GEF_VME_INT_LM2        = 22,
  GEF_VME_INT_LM3        = 23,
  GEF_VME_INT_DMA1       = 24, /* Tempe Only */
  GEF_VME_INT_LEVEL_LAST
} GEF_VME_INT_LEVEL;

/**
 * Type: GEF_VME_MAX_RETRY
 *
 * Description:
 *   An enumeration to set the number of retries before the PCI master 
 *   interface returns an error.
 *
 * GEF_VME_MAX_RETRY_INFINITE   -   Enable the retry (Universe and Tempe)   
 * GEF_VME_MAX_RETRY_COUNT_TEST -   Enable the Maximum Retry Count Test (Tempe Only)
 * GEF_VME_MAX_RETRY_64         -   Number of retries for Universe is 64, 2^24 times for Tempe  
 * GEF_VME_MAX_RETRY_128        -   Number of retries for Universe is 128, 2^24 times for Tempe 
 * GEF_VME_MAX_RETRY_192        -   Number of retries for Universe is 192, 2^24 times for Tempe 
 * GEF_VME_MAX_RETRY_256        -   Number of retries for Universe is 256, 2^24 times for Tempe 
 * GEF_VME_MAX_RETRY_320        -   Number of retries for Universe is 320, 2^24 times for Tempe 
 * GEF_VME_MAX_RETRY_384        -   Number of retries for Universe is 384, 2^24 times for Tempe 
 * GEF_VME_MAX_RETRY_448        -   Number of retries for Universe is 448, 2^24 times for Tempe 
 * GEF_VME_MAX_RETRY_512        -   Number of retries for Universe is 512, 2^24 times for Tempe 
 * GEF_VME_MAX_RETRY_576        -   Number of retries for Universe is 576, 2^24 times for Tempe 
 * GEF_VME_MAX_RETRY_640        -   Number of retries for Universe is 640, 2^24 times for Tempe 
 * GEF_VME_MAX_RETRY_704        -   Number of retries for Universe is 704, 2^24 times for Tempe 
 * GEF_VME_MAX_RETRY_768        -   Number of retries for Universe is 768, 2^24 times for Tempe 
 * GEF_VME_MAX_RETRY_832        -   Number of retries for Universe is 832, 2^24 times for Tempe 
 * GEF_VME_MAX_RETRY_896        -   Number of retries for Universe is 896, 2^24 times for Tempe 
 * GEF_VME_MAX_RETRY_960        -   Number of retries for Universe is 960, 2^24 times for Tempe 
 * GEF_VME_MAX_RETRY_MAX        -   Number of retries for Tempe Only 2^24 times           
 *
 */
typedef enum
{
  GEF_VME_MAX_RETRY_INFINITE   = -1,  /* Universe and Tempe                 */
  GEF_VME_MAX_RETRY_COUNT_TEST = 16,  /* Tempe Only                         */
  GEF_VME_MAX_RETRY_64         = 64,  /* Universe 64, 2^24 times for Tempe  */
  GEF_VME_MAX_RETRY_128        = 128, /* Universe 128, 2^24 times for Tempe */
  GEF_VME_MAX_RETRY_192        = 192, /* Universe 192, 2^24 times for Tempe */
  GEF_VME_MAX_RETRY_256        = 256, /* Universe 256, 2^24 times for Tempe */
  GEF_VME_MAX_RETRY_320        = 320, /* Universe 320, 2^24 times for Tempe */
  GEF_VME_MAX_RETRY_384        = 384, /* Universe 384, 2^24 times for Tempe */
  GEF_VME_MAX_RETRY_448        = 448, /* Universe 448, 2^24 times for Tempe */
  GEF_VME_MAX_RETRY_512        = 512, /* Universe 512, 2^24 times for Tempe */
  GEF_VME_MAX_RETRY_576        = 576, /* Universe 576, 2^24 times for Tempe */
  GEF_VME_MAX_RETRY_640        = 640, /* Universe 640, 2^24 times for Tempe */
  GEF_VME_MAX_RETRY_704        = 704, /* Universe 704, 2^24 times for Tempe */
  GEF_VME_MAX_RETRY_768        = 768, /* Universe 768, 2^24 times for Tempe */
  GEF_VME_MAX_RETRY_832        = 832, /* Universe 832, 2^24 times for Tempe */
  GEF_VME_MAX_RETRY_896        = 896, /* Universe 896, 2^24 times for Tempe */
  GEF_VME_MAX_RETRY_960        = 960, /* Universe 960, 2^24 times for Tempe */
  GEF_VME_MAX_RETRY_MAX        = 16777216, /* Tempe Only 2^24 times         */  
  GEF_VME_MAX_RETRY_LAST       = 19   /* Keep as number of elements */
} GEF_VME_MAX_RETRY;

/**
 * Type: GEF_VME_BUS_TIMEOUT
 *
 * Description:
 *   An enumeration to set the Bus timeout
 *
 *  GEF_VME_BUS_TIMEOUT_DISABLE  -   Timer Disabled                (Universe and Tempe)
 *  GEF_VME_BUS_TIMEOUT_8us      -   Timer set to 8microseconds    (Tempe Only) 
 *  GEF_VME_BUS_TIMEOUT_16us     -   Timer set to 16microseconds   (Universe and Tempe) 
 *  GEF_VME_BUS_TIMEOUT_32us     -   Timer set to 32microseconds   (Universe and Tempe) 
 *  GEF_VME_BUS_TIMEOUT_64us     -   Timer set to 64microseconds   (Universe and Tempe) 
 *  GEF_VME_BUS_TIMEOUT_128us    -   Timer set to 128microseconds  (Universe and Tempe) 
 *  GEF_VME_BUS_TIMEOUT_256us    -   Timer set to 256microseconds  (Universe and Tempe) 
 *  GEF_VME_BUS_TIMEOUT_512us    -   Timer set to 512microseconds  (Universe and Tempe) 
 *  GEF_VME_BUS_TIMEOUT_1024us   -   Timer set to 1024microseconds (Universe and Tempe) 
 *  GEF_VME_BUS_TIMEOUT_2048us   -   Timer set to 2048microseconds (Tempe Only)            
 *
 */
typedef enum
{
  GEF_VME_BUS_TIMEOUT_DISABLE  = 0,    /* Universe and Tempe */
  GEF_VME_BUS_TIMEOUT_8us      = 8,    /* Tempe Only */
  GEF_VME_BUS_TIMEOUT_16us     = 16,   /* Universe and Tempe */
  GEF_VME_BUS_TIMEOUT_32us     = 32,   /* Universe and Tempe */
  GEF_VME_BUS_TIMEOUT_64us     = 64,   /* Universe and Tempe */
  GEF_VME_BUS_TIMEOUT_128us    = 128,  /* Universe and Tempe */
  GEF_VME_BUS_TIMEOUT_256us    = 256,  /* Universe and Tempe */
  GEF_VME_BUS_TIMEOUT_512us    = 512,  /* Universe and Tempe */
  GEF_VME_BUS_TIMEOUT_1024us   = 1024, /* Universe and Tempe */
  GEF_VME_BUS_TIMEOUT_2048us   = 2048, /* Tempe Only         */
  GEF_VME_BUS_TIMEOUT_LAST     = 10    /* Keep as number of elements */
} GEF_VME_BUS_TIMEOUT;

/**
 * Type: GEF_VME_ARB_TIMEOUT
 *
 * Description:
 *   An enumeration to set the VME arbitration timeout
 *
 *  GEF_VME_ARB_TIMEOUT_DISABLE  -  Timer disabled (Universe and Tempe)
 *  GEF_VME_ARB_TIMEOUT_16us     -  Timer set to 16microseconds (Universe and Tempe) 
 *  GEF_VME_ARB_TIMEOUT_256us    -  Timer set to 256microseconds (Universe Only)             
 *
 */
typedef enum
{
  GEF_VME_ARB_TIMEOUT_DISABLE  = 0,   /* Universe and Tempe */
  GEF_VME_ARB_TIMEOUT_16us     = 16,  /* Universe and Tempe */
  GEF_VME_ARB_TIMEOUT_256us    = 256, /* Universe Only */
  GEF_VME_ARB_TIMEOUT_LAST     = 3    /* Keep as number of elements */
} GEF_VME_ARB_TIMEOUT;

/**
 * Type: GEF_VME_PWON
 *
 * Description:
 *   Posted Write Transfer Count in bytes.  These values
 *    are only valid on Universe based SBC's.  
 *
 *   Given below are Transfer count in bytes at which the PCI Slave Channel Posted Writes 
 *   FIFO gives up the VME Master Interface.
 *
 *  GEF_VME_PWON__EARLY_RELEASE  -   Early release of BBSY*
 *  GEF_VME_PWON_128             -   128 byte
 *  GEF_VME_PWON_256             -   256 bytes
 *  GEF_VME_PWON_512             -   512 bytes
 *  GEF_VME_PWON_1024            -   1024 bytes
 *  GEF_VME_PWON_2048            -   2048 bytes
 *  GEF_VME_PWON_4096            -   4096 bytes
 *
 */
typedef enum
{
  GEF_VME_PWON__EARLY_RELEASE  = 0,    /* Universe Only */
  GEF_VME_PWON_128             = 128,  /* Universe Only */
  GEF_VME_PWON_256             = 256,  /* Universe Only */
  GEF_VME_PWON_512             = 512,  /* Universe Only */
  GEF_VME_PWON_1024            = 1024, /* Universe Only */
  GEF_VME_PWON_2048            = 2048, /* Universe Only */
  GEF_VME_PWON_4096            = 4096, /* Universe Only */
  GEF_VME_PWON_LAST            = 7     /* Keep as number of elements */
} GEF_VME_PWON;

/**
 * Type: GEF_VME_TIME_ON_BUS
 *
 * Description:
 *   An enumeration to set the VME time on bus.
 *
 *  GEF_VME_TIME_ON_BUS_4us   -  4 microseconds or 128 Bytes for 2eSST/2eVME
 *  GEF_VME_TIME_ON_BUS_8us   -  8 microseconds or 128 Bytes for 2eSST/2eVME
 *  GEF_VME_TIME_ON_BUS_8us   -  16 microseconds or 128 Bytes for 2eSST/2eVME
 *  GEF_VME_TIME_ON_BUS_8us   -  32 microseconds or 256 Bytes for 2eSST/2eVME
 *  GEF_VME_TIME_ON_BUS_8us   -  64 microseconds or 512 Bytes for 2eSST/2eVME
 *  GEF_VME_TIME_ON_BUS_8us   -  128 microseconds or 1024 Bytes for 2eSST/2eVME
 *  GEF_VME_TIME_ON_BUS_8us   -  256 microseconds or 2048 Bytes for 2eSST/2eVME
 *  GEF_VME_TIME_ON_BUS_8us   -  512 microseconds or 4096 Bytes for 2eSST/2eVME
 *
 */
typedef enum
{
  GEF_VME_TIME_ON_BUS_4us     = 4,     /* Tempe only */
  GEF_VME_TIME_ON_BUS_8us     = 8,     /* Tempe only */
  GEF_VME_TIME_ON_BUS_16us    = 16,    /* Tempe only */
  GEF_VME_TIME_ON_BUS_32us    = 32,    /* Tempe only */
  GEF_VME_TIME_ON_BUS_64us    = 64,    /* Tempe only */
  GEF_VME_TIME_ON_BUS_128us   = 128,   /* Tempe only */
  GEF_VME_TIME_ON_BUS_256us   = 256,   /* Tempe only */
  GEF_VME_TIME_ON_BUS_512us   = 512,   /* Tempe only */
  GEF_VME_TIME_ON_BUS_LAST    = 8      /* Keep as number of elements */
} GEF_VME_TIME_ON_BUS;

/**
 * Type: GEF_VME_TIME_OFF_BUS
 *
 * Description:
 *   An enumeration to set the VME time off the bus before 
 *   re-requesting the VMEbus.
 *
 *  GEF_VME_TIME_OFF_BUS_0us   -  0 microseconds 
 *  GEF_VME_TIME_OFF_BUS_1us   -  1 microseconds 
 *  GEF_VME_TIME_OFF_BUS_2us   -  2 microseconds
 *  GEF_VME_TIME_OFF_BUS_4us   -  4 microseconds
 *  GEF_VME_TIME_OFF_BUS_8us   -  8 microseconds 
 *  GEF_VME_TIME_OFF_BUS_16us  -  16 microseconds 
 *  GEF_VME_TIME_OFF_BUS_32us  -  32 microseconds 
 *  GEF_VME_TIME_OFF_BUS_64us  -  64 microseconds
 *
 */
typedef enum
{
  GEF_VME_TIME_OFF_BUS_0us    = 0,    /* Tempe only */
  GEF_VME_TIME_OFF_BUS_1us    = 1,    /* Tempe only */
  GEF_VME_TIME_OFF_BUS_2us    = 2,    /* Tempe only */
  GEF_VME_TIME_OFF_BUS_4us    = 4,    /* Tempe only */
  GEF_VME_TIME_OFF_BUS_8us    = 8,    /* Tempe only */
  GEF_VME_TIME_OFF_BUS_16us   = 16,   /* Tempe only */
  GEF_VME_TIME_OFF_BUS_32us   = 32,   /* Tempe only */
  GEF_VME_TIME_OFF_BUS_64us   = 64,   /* Tempe only */
  GEF_VME_TIME_OFF_BUS_LAST   = 8     /* Keep as number of elements */
} GEF_VME_TIME_OFF_BUS;

/* Structures */

/**
 * Type: GEF_VME_BERR_INFO
 *
 * Description:
 *   VME Bus Error info structure.
 *
 *  upper             - Upper 32bits of VME Address
 *  lower             - Lower 32bits of VME Address
 *  addr_mod          - Address Modifier
 *  extended_addr_mod - Extended address modifier
 *  iack_signal       - This bit captures the state of the VMEbus IACK_ signal when the Tsi148 is
 *                      VME Master and an exception occurs. This bit is set when the IACK_ signal is asserted.This
 *                      bit is only updated when the VES bit is clear.
 *  ds1_signal        - This bit captures the state of the VMEbus DS1_ signal when the Tsi148 is VME
 *                      Master and an exception occurs.
 *  ds0_signal        - This bit captures the state of the VMEbus DS0_ signal when the Tsi148 is VME
 *                      Master and an exception occurs. 
 *  lword_signal      - This bit captures the state of the VMEbus LWORD_ signal when the Tsi148 is 
 *                      VME Master and an exception occurs. 
 *
 *  vme_2eOT          -  2e Odd Termination 
 *  vme_2eST          -  2e Slave Terminated             
 *
 */
typedef struct _GEF_VME_BERR_INFO
{
  GEF_UINT32                 upper;
  GEF_UINT32                 lower;
  GEF_VME_ADDR_MOD           addr_mod;
  GEF_VME_EXTENDED_ADDR_MOD  extended_addr_mod;
  GEF_BOOL                   iack_signal;
  GEF_BOOL                   ds1_signal;
  GEF_BOOL                   ds0_signal;
  GEF_BOOL                   lword_signal;
  GEF_BOOL                   vme_2eOT; /* 2e Odd Termination */
  GEF_BOOL                   vme_2eST; /* 2e Slave Terminated */
} GEF_VME_BERR_INFO;

/**
 * Type: GEF_VME_INT_INFO
 *
 * Description:
 *   Interrupt info structure.
 *
 *  int_level  - interrupt level
 *  int_vector - interrupt vector
 *  berr_info  - bus error info
 *
 */
typedef struct _GEF_VME_INT_INFO
{
  GEF_VME_INT_LEVEL  int_level;
  GEF_UINT32         int_vector; /* Tempe supports 8, 16 and 32 bit IACK */
  GEF_VME_BERR_INFO  berr_info;
} GEF_VME_INT_INFO;

/**
 * Type: GEF_VME_ADDR
 *
 * Description:
 *   Structure to fill in the VME address parameters.
 *
 *  upper - Upper 4 bytes of the Address(4-7 bytes).
 *  lower - lower 4 bytes of the address(0-3 bytes).
 *  addr_space - Address space of type <GEF_VME_ADDR_SPACE>.
 *  vme_2esst_rate - Address space of type <GEF_VME_2ESST_RATE>.
 *  addr_mode - Address mode using <GEF_VME_ADDR_MODE>.
 *  transfer_mode - Transfer mode using <GEF_VME_TRANSFER_MODE>.
 *  broadcast_id - Broadcast id using <GEF_VME_BROADCAST_ID>.
 *  transfer_max_dwidth - Transfer mode data width of type <GEF_VME_TRANSFER_MAX_DWIDTH>.
 *  flags - Flags for <GEF_VME_WND_FLAGS> or <GEF_VME_DMA_FLAGS>.
 *
 */
typedef struct _GEF_VME_ADDR
{
  GEF_UINT32                  upper;
  GEF_UINT32                  lower;
  GEF_VME_ADDR_SPACE          addr_space;
  GEF_VME_2ESST_RATE          vme_2esst_rate;
  GEF_UINT32                  addr_mode;     /* use GEF_VME_ADDR_MODE values */
  GEF_UINT32                  transfer_mode; /* use GEF_VME_TRANSFER_MODE values */
  GEF_UINT32                  broadcast_id;  /* use GEF_VME_BROADCAST_ID values */
  GEF_VME_TRANSFER_MAX_DWIDTH transfer_max_dwidth;
  GEF_UINT32                  flags; /* use GEF_VME_WND_FLAGS or GEF_VME_DMA_FLAGS values */
} GEF_VME_ADDR;

/* Debug print macro, works in both kernel and user mode. */
#define GEF_VME_DEBUG(flag, ...) if (GEF_WHEN_DEBUG((flag), gef_vme_debug_flags))  {GEF_DEBUG_PRINT(__VA_ARGS__);}

/**
 * Type: GEF_HW_BYTESWAP
 *
 * Description:
 *   The byte swap types.  These values
 *   are only valid on Universe based SBC's.  
 *
 *   Given below are byte swap types.
 *
 *  GEF_BYTESWAP_NO_SWAP        -   No byte swap              
 *  GEF_BYTESWAP_SWAP_D32       -   Swap VME D32 transfers only
 *  GEF_BYTESWAP_SWAP_D16       -   Swap VME D16 transfers only
 *  GEF_BYTESWAP_SWAP_ON_SIZE   -   Swap based on transfer size 
 *
 */
typedef enum
{
  GEF_BYTESWAP_NO_SWAP,     /* No byte swap                */
  GEF_BYTESWAP_SWAP_D32,    /* Swap VME D32 transfers only */
  GEF_BYTESWAP_SWAP_D16,    /* Swap VME D16 transfers only */
  GEF_BYTESWAP_SWAP_ON_SIZE /* Swap based on transfer size */ 
} GEF_HW_BYTESWAP;

/**
* Type: GEF_VME_DIR
*
* Description:
* An enumeration to set VME data direction
*
* GEF_VME_DIR_READ - Read
* GEF_VME_DIR_WRITE- Write
*/
typedef enum
{
    GEF_VME_DIR_READ  = 1, 
    GEF_VME_DIR_WRITE = 2, 
    GEF_VME_DIR_LAST  = 3 /* Keep as number of elements */
} GEF_VME_DIR;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __GEFCMN_VME_DEFS_H */


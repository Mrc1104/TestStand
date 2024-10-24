/*
 * File:
 *    gefcmn_types.h
 *
 * Description:
 *    Type Specifications for the Common API Library for
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
 */

#ifndef __GEFCMN_TYPES_H
#define __GEFCMN_TYPES_H

#ifdef __KERNEL__
#include <linux/time.h>
#include <linux/types.h>
#else
#include <sys/time.h>
#include <stdint.h>
#include <stdio.h>
#endif

/* phys_addr_t is unavailable in userspace and 
 * in older 2.6.x kernels for 32-bit targets.
 */
#if !defined (phys_addr_t)
#define phys_addr_t unsigned long
#endif

/*****************************************************************************/
/**
 * Title: SBC Common API Types
 *
 * Description:
 *    This header file provides type definitions for basic portable types
 *
 *
 */

/* Provide Type Definitions for basic portable types*/
/**
 * Group: Types and Constants
 */

/**
 * Type: GEF_UINT8
 *
 * Description:
 *    Corresponding basic date type refers to unsigned 1 byte. Eg.unsigned char
 *
 */
typedef unsigned char		GEF_UINT8;
/**
 * Type: GEF_UINT16
 *
 * Description:
 *    Corresponding basic date type refers to unsigned 2 bytes. Eg.unsigned short
 *
 */
typedef unsigned short int	GEF_UINT16;
/**
 * Type: GEF_UINT32
 *
 * Description:
 *    Corresponding basic date type refers to unsigned 4 bytes. Eg.unsigned long
 *
 */
typedef unsigned int		GEF_UINT32;
/**
 * Type: GEF_UINT64
 *
 * Description:
 *    Corresponding basic date type refers to unsigned 8 bytes. Eg.unsigned __int64
 *
 */
typedef unsigned long long int	GEF_UINT64; 
/**
 * Type: GEF_INT8
 *
 * Description:
 *    Corresponding basic date type refers to signed 1 byte. Eg. signed char.
 *
 */
typedef signed char		GEF_INT8;
/**
 * Type: GEF_INT16
 *
 * Description:
 *    Corresponding basic date type refers to signed 2 bytes. Eg. signed short
 *
 */
typedef signed short int	GEF_INT16;
/**
 * Type: GEF_INT32
 *
 * Description:
 *    Corresponding basic date type refers to signed 4 bytes. Eg. unsigned long
 *
 */
typedef signed int		GEF_INT32;
/**
 * Type: GEF_INT64
 *
 * Description:
 *    Corresponding basic date type refers to signed 8 bytes. Eg."unsigned __int64"
 *
 */
typedef signed long long int	GEF_INT64;
/**
 * Type: GEF_BOOL
 *
 * Description:
 *    Standard boolean enumeration.
 *
 *
 */
typedef unsigned char		GEF_BOOL;

/**
 * Type: GEF_MAP_PTR
 *
 * Description:
 *    A volatile void pointer type used to point to memory that can change
 * outside of the control of the program in which it appears.
 *
 */
typedef volatile void*      GEF_MAP_PTR;

/**
 * Type: GEF_UINT_ADDR
 *
 * Description:
 *    Pointer address length for 32 & 64 bit systems, sizeof(long) is 
 *	8 in 64bit and 4 in 32bit systems.
 */
typedef unsigned long       GEF_UINT_ADDR;
#define GEF_UINT_ADDR32		GEF_UINT32
#define GEF_UINT_ADDR64		GEF_UINT64

/**
 * Type: GEF_UINTPTR_T
 *
 * Description:
 *    Corresponding basic date type refers to unsigned integer type of the
 * size of a pointer.
 */
#ifndef uintptr_t
typedef void *		GEF_UINTPTR_T;
#else
typedef uintptr_t           GEF_UINTPTR_T;
#endif

/**
 * Type: GEF_UINT_PADDR
 *
 * Description:
 *      32-Bit systems can be equipped with more than 2^32 memory.
 *      This memory can be mapped, if PAE is enabled.
 *      Pointers for 32-Bit PAE systems will remain 32-Bit, but
 *      physical addressable memory will be handled with 64-Bit int.
 */
typedef phys_addr_t         GEF_UINT_PADDR;
/*****************************************************************************/

/* Add base constants for the Boolean */
/**
 * Type: GEF_TRUE
 *
 * Description:
 *     Standard boolean enumeration of type <GEF_BOOL>.
 * True(1)
 *
*/
#define GEF_TRUE  ((GEF_BOOL) 1)
/**
 * Type: GEF_FALSE
 *
 * Description:
 *     Standard boolean enumeration of type <GEF_BOOL>.
 * False(0) 
 *
*/
#define GEF_FALSE ((GEF_BOOL) 0)

/*****************************************************************************/

/**
 * Type: GEF_INFINITE_TIMEOUT
 *
 * Description:
 *     Declaration for infinite timeout.
 *
*/
#define GEF_INFINITE_TIMEOUT { 0xFFFFFFFF, 0 }

/**
 * Type: GEF_NO_WAIT_TIMEOUT
 *
 * Description:
 *     Declaration for a zero timeout.
 *
*/
#define GEF_NO_WAIT_TIMEOUT { 0, 0 }

/*****************************************************************************/

/**
 * Group: Debug macros defined for both kernel and user space.
 */

/**
 * Macro: GEF_WHEN_DEBUG
 *
 * Description:
 *     Return whether a given flag is set.
 *
 */
#define GEF_WHEN_DEBUG(debug_flag, flags) (debug_flag & flags)

/**
 * Macro: GEF_DEBUG_PRINT
 *
 * Description:
 *     Specific print function to use for debugging.
 *
 */

#ifdef __KERNEL__
    #define GEF_DEBUG_PRINT(arg...) printk(arg)
#else
    #define GEF_DEBUG_PRINT(arg...) fprintf(stderr, arg)
#endif

#endif  /* __GEFCMN_TYPES_H */

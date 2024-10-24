/*
 * File:
 *    gefcmn_errno.h
 *
 * Description:
 *    This file defines Error codes for the Common API.
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
#ifndef __GEFCMN_ERRNO_H
#define __GEFCMN_ERRNO_H

#include "gef/gefcmn_types.h"

/**
 * Title: SBC Common API error codes
 *
 * Description:
 *    This file defines Error codes for the Common API.
 *
 * Include Files:
 *    gefcmn_types.h
 *
 */

/*
Error codes for the common API

The return code is an unsigned 32 bit integer, with the following bit fields:

Bits 31-28 Severity Code. 
Bits 27-20 Facility Code. 
Bits 19-0  Error Descriptor.

The error descriptor contains the actual error code.
*/

typedef GEF_UINT32 GEF_STATUS;

#define GEF_STATUS_SEVERITY_MASK          ((GEF_UINT32) 0xF0000000)
#define GEF_STATUS_FACIL_MASK             ((GEF_UINT32) 0x0FF00000)
#define GEF_STATUS_ERROR_CODE_MASK        ((GEF_UINT32) 0x000FFFFF)
#define GEF_STATUS_FACIL_ERROR_FIRST      (256)

#define GEF_STATUS_FACIL_SHIFT            (20)


/**
 * Type: GEF_SEVERITY_ENUM
 *
 * Description:
 *      Severity enumerations returned in error status values.  
 *      Use the <GEF_GET_SEVERITY> (status) macro to extract the severity code
 *      from the value returned by a call to a Library API function.
 *
 *  GEF_SEVERITY_SUCCESS    - Success
 *  GEF_SEVERITY_INFO       - Informational
 *  GEF_SEVERITY_WARNING    - Warning
 *  GEF_SEVERITY_ERROR      - Error
 *
 * See Also:
 *    <GEF_GET_SEVERITY>
 */
typedef enum 
{
    GEF_SEVERITY_SUCCESS = 0x00000000,
    GEF_SEVERITY_INFO    = 0x10000000,
    GEF_SEVERITY_WARNING = 0x20000000,
    GEF_SEVERITY_ERROR   = 0x30000000,

    GEF_SEVERITY_LAST    = 0x40000000
} GEF_SEVERITY_ENUM;

/**
 * Type: GEF_FACIL_ENUM
 *
 * Description:
 *      Facility enumerations returned in error status values.  
 *      Use the <GEF_GET_FACIL> (status) macro to extract the facility code
 *      from the value returned by a call to a Library API function.
 *
 *  GEF_FACIL_VME               - VMEbus Facility
 *  GEF_FACIL_TEMP_SENSOR       - Temperature Sensor Facility
 *  GEF_FACIL_VOLTAGE_SENSOR    - Voltage Sensor Facility
 *  GEF_FACIL_RTC               - Real-time Clock Facility
 *  GEF_FACIL_NVRAM             - NVRAM Facility
 *  GEF_FACIL_TIMER             - Timer Facility
 *  GEF_FACIL_WATCHDOG_TIMER    - Watchdog Timer Facility
 *  GEF_FACIL_GPIO              - General Purpose I/O Facility
 *  GEF_FACIL_EEPROM            - EEPROM Facility
 *  GEF_FACIL_CPCI_HINT         - Compact PCI HINT Facility
 *  GEF_FACIL_ERR               - Error Library Facility
 *  GEF_FACIL_OSA               - Operating System Abstraction Facility
 *  GEF_FACIL_LED               - LED Facility
 *  GEF_FACIL_SMBUS             - SMBUS Facility
 *  GEF_FACIL_CPCI              - Compact PCI Facility 
 *  GEF_FACIL_WRPROT             - Write Protect Facility
 *
 * See Also:
 *    <GEF_GET_FACIL>
 */
typedef enum 
{
    GEF_FACIL_VME            = 0x00100000,
    GEF_FACIL_TEMP_SENSOR    = 0x00200000,
    GEF_FACIL_VOLTAGE_SENSOR = 0x00300000,
    GEF_FACIL_RTC            = 0x00400000,
    GEF_FACIL_NVRAM          = 0x00500000,
    GEF_FACIL_TIMER          = 0x00600000,
    GEF_FACIL_WATCHDOG_TIMER = 0x00700000,
    GEF_FACIL_GPIO           = 0x00800000,
    GEF_FACIL_EEPROM         = 0x00900000,
    GEF_FACIL_CPCI_HINT      = 0x00A00000,
    GEF_FACIL_ERR            = 0x00B00000,
    GEF_FACIL_OSA            = 0x00C00000,
    GEF_FACIL_LED            = 0x00D00000,
    GEF_FACIL_SMBUS          = 0x00E00000,
    GEF_FACIL_CPCI           = 0x00F00000,
    GEF_FACIL_WRPROT          = 0x01000000,

    GEF_FACIL_LAST           = 0x01000000
} GEF_FACIL_ENUM;

/**
 * Type: GEF_STATUS_ENUM
 *
 * Description:
 *      Status enumerations returned in error status values.  
 *      Use the <GEF_GET_ERROR> (status) macro to extract the status code
 *      from the value returned by a call to a Library API function.
 *
 *  GEF_STATUS_SUCCESS                    - Success
 *  GEF_STATUS_NOT_SUPPORTED              - Request not supported
 *  GEF_STATUS_NO_MEM                     - out of memory
 *  GEF_STATUS_INVAL_ADDR                 - Invalid argument
 *  GEF_STATUS_READ_ERR                   - Read Error
 *  GEF_STATUS_WRITE_ERR                  - Write error
 *  GEF_STATUS_DEVICE_NOT_INIT            - Device not initialized
 *  GEF_STATUS_NO_SUCH_DEVICE             - Device not found
 *  GEF_STATUS_DRIVER_ERR                 - Driver returned error
 *  GEF_STATUS_INTERRUPTED                - Request Interrupted
 *  GEF_STATUS_TIMED_OUT                  - Request Timeout 
 *  GEF_STATUS_EVENT_IN_USE               - Callback or Wait for alarm (blocking call) in use
 *  GEF_STATUS_THREAD_CREATION_FAILED     - Thread creation failed
 *  GEF_STATUS_CALLBACK_NOT_ATTACHED      - Callback is not registered
 *  GEF_STATUS_DEVICE_IN_USE              - Device is already in use  	
 *  GEF_STATUS_OPERATION_NOT_ALLOWED      - This operation is not allowed
 *  GEF_STATUS_BAD_PARAMETER_1            - Bad parameter 1
 *  GEF_STATUS_BAD_PARAMETER_2            - Bad parameter 2  
 *  GEF_STATUS_BAD_PARAMETER_3            - Bad parameter 3  
 *  GEF_STATUS_BAD_PARAMETER_4            - Bad parameter 4  
 *  GEF_STATUS_BAD_PARAMETER_5            - Bad parameter 5  
 *  GEF_STATUS_BAD_PARAMETER_6            - Bad parameter 6  
 *  GEF_STATUS_BAD_PARAMETER_7            - Bad parameter 7  
 *  GEF_STATUS_BAD_PARAMETER_8            - Bad parameter 8  
 *  GEF_STATUS_BAD_PARAMETER_9            - Bad parameter 9  
 *  GEF_STATUS_BAD_PARAMETER_10           - Bad parameter 10
 *  GEF_STATUS_BAD_PARAMETER_11           - Bad parameter 11 
 *  GEF_STATUS_INVALID_ERROR_CODE         - Invalid error code
 *  GEF_STATUS_NO_EVENT_PENDING			  - No event pending
 *  GEF_STATUS_EVENT_RELEASED			  - Event is released
 *  GEF_STATUS_LAST						  - Last Error
 * See Also:
 *    <GEF_GET_ERROR>
 */
typedef enum 
{
    GEF_STATUS_SUCCESS       = 0x00000000,
    GEF_STATUS_NOT_SUPPORTED,
    GEF_STATUS_NO_MEM,
    GEF_STATUS_INVAL_ADDR,
    GEF_STATUS_READ_ERR,
    GEF_STATUS_WRITE_ERR,
    GEF_STATUS_DEVICE_NOT_INIT,
    GEF_STATUS_NO_SUCH_DEVICE,
    GEF_STATUS_DRIVER_ERR,
    GEF_STATUS_INTERRUPTED,
    GEF_STATUS_TIMED_OUT,
    GEF_STATUS_EVENT_IN_USE,
    GEF_STATUS_THREAD_CREATION_FAILED,
    GEF_STATUS_CALLBACK_NOT_ATTACHED,
    GEF_STATUS_DEVICE_IN_USE,
    GEF_STATUS_OPERATION_NOT_ALLOWED,
    GEF_STATUS_BAD_PARAMETER_1,  /* Function Parameter  1 invalid  */
    GEF_STATUS_BAD_PARAMETER_2,  /* Function Parameter  2 invalid  */
    GEF_STATUS_BAD_PARAMETER_3,  /* Function Parameter  3 invalid  */
    GEF_STATUS_BAD_PARAMETER_4,  /* Function Parameter  4 invalid  */
    GEF_STATUS_BAD_PARAMETER_5,  /* Function Parameter  5 invalid  */
    GEF_STATUS_BAD_PARAMETER_6,  /* Function Parameter  6 invalid  */
    GEF_STATUS_BAD_PARAMETER_7,  /* Function Parameter  7 invalid  */
    GEF_STATUS_BAD_PARAMETER_8,  /* Function Parameter  8 invalid  */
    GEF_STATUS_BAD_PARAMETER_9,  /* Function Parameter  9 invalid  */
    GEF_STATUS_BAD_PARAMETER_10, /* Function Parameter 10 invalid  */
    GEF_STATUS_BAD_PARAMETER_11, /* Function Parameter 11 invalid  */
    GEF_STATUS_INVALID_ERROR_CODE,
    GEF_STATUS_NO_EVENT_PENDING,
    GEF_STATUS_EVENT_RELEASED,
	GEF_STATUS_CPCI_OFFSET_NOT_ALIGNED,
    GEF_STATUS_LAST,
} GEF_STATUS_ENUM;


#define GEF_SUCCESS                       (GEF_STATUS_SUCCESS)

#define GEF_SET_SEVERITY(SEVERITY, FACIL, STATUS) \
                        ((GEF_UINT32) (SEVERITY | FACIL | (GEF_UINT32) (STATUS & GEF_STATUS_ERROR_CODE_MASK)))

#define GEF_SET_INFO(FACIL,STATUS)        (GEF_SET_SEVERITY(GEF_SEVERITY_INFO,    FACIL, STATUS)) 
#define GEF_SET_WARNING(FACIL, STATUS)    (GEF_SET_SEVERITY(GEF_SEVERITY_WARNING, FACIL, STATUS)) 
#define GEF_SET_ERROR(FACIL, STATUS)      (GEF_SET_SEVERITY(GEF_SEVERITY_ERROR,   FACIL, STATUS))

/**
 * Macro: GEF_GET_ERROR
 *
 * Description:
 *      Extracts the <GEF_STATUS_ENUM> error code from the status value returned 
 *      by a call to a Library API function.
 *
 *      Example: 
 *               status = GefXxxx(y, z);
 *
 *               if ( GEF_GET_ERROR(status) == GEF_STATUS_BAD_PARAMETER_2 )    { ... }
 *
 * Parameters:
 *      <GEF_STATUS_ENUM> status - Value returned by a call to a Library API function.
 *
 * See Also:
 *    <GEF_STATUS_ENUM>
 */
#define GEF_GET_ERROR(STATUS)             ((GEF_UINT32) (STATUS & GEF_STATUS_ERROR_CODE_MASK))


/**
 * Macro: GEF_GET_SEVERITY
 *
 * Description:
 *      Extracts the <GEF_SEVERITY_ENUM> severity code from the status value returned 
 *      by a call to a Library API function.
 *
 *      Example: 
 *               status = GefXxxx(y, z);
 *
 *               if ( GEF_GET_SEVERITY(status) == GEF_SEVERITY_ERROR )    { ... }
 *
 * Parameters:
 *      <GEF_STATUS_ENUM> status - Value returned by a call to a Library API function.
 *
 * See Also:
 *    <GEF_SEVERITY_ENUM>
 */
#define GEF_GET_SEVERITY(STATUS)          ((GEF_UINT32) (STATUS & GEF_STATUS_SEVERITY_MASK))


/**
 * Macro: GEF_GET_FACIL
 *
 * Description:
 *      Extracts the <GEF_FACIL_ENUM> facility code from the status value returned 
 *      by a call to a Library API function.
 *
 *      Example: 
 *               status = GefXxxx(y, z);
 *
 *               if ( GEF_GET_FACIL(status) == GEF_FACIL_VME )    { ... }
 *
 * Parameters:
 *      <GEF_STATUS_ENUM> status - Value returned by a call to a Library API function.
 *
 * See Also:
 *    <GEF_FACIL_ENUM>
 */

#define GEF_GET_FACIL(STATUS)             ((GEF_UINT32) (STATUS & GEF_STATUS_FACIL_MASK))

/* GEF_DEBUG message class definitions                                           */
#define GEF_DEBUG_ERROR         (1<<0)   /* Report critical errors               */
#define GEF_DEBUG_INIT          (1<<1)   /* Trace device probing and search      */
#define GEF_DEBUG_INTR          (1<<2)   /* Trace interrupt service              */
#define GEF_DEBUG_IOCTL         (1<<3)   /* Trace ioctl system calls             */
#define GEF_DEBUG_MMAP          (1<<4)   /* Trace mmap system calls              */
#define GEF_DEBUG_OPEN          (1<<5)   /* Trace open system calls              */
#define GEF_DEBUG_CLOSE         (1<<6)   /* Trace close system calls             */
#define GEF_DEBUG_READ          (1<<7)   /* Trace read system calls              */ 
#define GEF_DEBUG_WRITE         (1<<8)   /* Trace write system calls             */
#define GEF_DEBUG_PEEK          (1<<9)   /* Trace peeks                          */
#define GEF_DEBUG_POKE          (1<<10)  /* Trace pokes                          */
#define GEF_DEBUG_STRAT         (1<<11)  /* Trace read/write strategy            */
#define GEF_DEBUG_TIMER         (1<<12)  /* Trace interval timer                 */
#define GEF_DEBUG_TRACE         (1<<13)  /* Trace subroutine entry/exit          */
#define GEF_DEBUG_MUTEX         (1<<14)  /* Trace synchronization and locking    */
#define GEF_DEBUG_DMA			(1<<15)  /* Trace DMA Calls					     */

#endif /* __GEFCMN_ERRNO_H */

/*
 * File:
 *    gefcmn_vme.h
 *
 * Description:
 *    This interface file defines the API interface for the VME facility.
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
#ifndef __GEFCMN_VME_H
#define __GEFCMN_VME_H

/**
 * Title: SBC VME Common API Header
 *
 * Description:
 *    This is a common header file for the VME API Library.
 *
 * Include Files:
 *    gefcmn_vme_osspec.h
 *
 * Error Code:
 *     The API's defined in this file return a generic error code of type <GEF_STATUS_ENUM>.
 *     Specific errors returned by the API's are listed in this document.   
 *
 * Libraries:
 *    N/A
 *
 * Kernel Modules:
 *    N/A
 */
/*****************************************************************************/

/* 
User Applications using the Common VME API shall include this header file.

Header File include structure
Shared = Shared across OS's, otherwise OS specific.
Kernel = File that can be included by Kernel driver in addition to user library.
User   = File delivered to user for user apps to include.

                                  gefcmn_types.h
                                  (Kernel, User)
                                        |
                   ---------------------------------------------           
                   |                 |                         |
          gefcmn_common.h   gefcmn_osa_framework.h     gefcmn_errno.h  
      (Shared, Kernel, User)    (Shared, Kernel)      (Shared, Kernel, User)
                   |                 |                         |
           ----------------          |                   -------------
           |              |          |                   |           |
 gefcmn_vme_defs.h   gefcmn_osspec.h |                   |  gefcmn_vme_errno.h
(Shared,Kernel,User)    (User)       |                   | (Shared,Kernel,User)
           |              |          |                   |           |
           |           -------       |            gefcmn_osa_errno.h |
           |           |     |       |             (Shared, Kernel)  |
           |           |     |       |                   |           |
           |           |     |       | gefcmn_osa_defs.h |           |
           |           |     |       | (Shared, Kernel)  |           |
           |           |     |       |      |            |           |
           |           |     -----------------------------           |
           |           |                  |                          |
           |           |             gefcmn_osa.h                    |
           |           |               (Shared)                      |
           |           |                                             | 
           -----------------------------------------------------------
                                        |
                               gefcmn_vme_osspec.h                  
                                     (User)      
                                        |         
                                  gefcmn_vme.h                        
                                 (Shared, User)                    
*/

#include "gef/gefcmn_vme_osspec.h"  

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define VME_BUS_MAGIC (GEF_UINT32) 0x014810e3

/**
 * Group: Types
 */
 
/**
 * Type: GEF_VME_INT_CALLBACK
 *
 * Description:
 *    A type defining the callback routine that can be attached to a
 *    VME interrupt.
 *
 * Parameters:
 *    <GEF_CALLBACK_HDL> callback_hdl - (I) An opaque data handle, returned
 *                                          from the function
 *                                          <gefVmeAttachCallback>,
 *                                          which refers to this callback.
 *                                          The VME bus handle this callback
 *                                          is associated with can be
 *                                          derived from this handle using
 *                                          the function
 *                                          <gefVmeCallbackGetBusHdl>.
 *    <GEF_VME_INT_INFO> int_info     - (I) A data structure that contains 
 *                                          information about the event.
 *    void *arg                       - (I) An argument supplied by the
 *                                          user at the time that the
 *                                          callback routine was attached.
 *
 * Returns:
 *     Nothing.
 *
 */

typedef void (*GEF_VME_INT_CALLBACK)(GEF_CALLBACK_HDL  callback_hdl,
                                     GEF_VME_INT_INFO  int_info, 
                                     void             *arg);

/**
 * Group: Public Functions
 */
/**
 * Function: gefVmeCallbackGetBusHdl
 *
 * Description:
 *    This function gets the VME bus handle from a given callback handle.
 *
 * Parameters:
 *    <GEF_CALLBACK_HDL> callback_hdl   - (I) An opaque data handle, returned
 *                                            from the function
 *                                            <gefVmeAttachCallback>,
 *                                            which refers to a particular
 *                                            callback.
 *    <GEF_VME_BUS_HDL> *bus_hdl        - (O) A pointer to the location to
 *                                            store the sensor handle that is
 *                                            associated with the given
 *                                            callback handle.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_BAD_PARAMETER_1 - The _callback_hdl_ parameter is not a valid 
 *                                 callback handle. 
 *    GEF_STATUS_BAD_PARAMETER_2 - The _bus_hdl_ parameter is not a valid
 *                                 pointer.
 *
 * See Also:
 *    <gefVmeAttachCallback>
 */

GEF_STATUS GEF_STD_CALL 
gefVmeCallbackGetBusHdl (GEF_CALLBACK_HDL  callback_hdl, 
                         GEF_VME_BUS_HDL  *bus_hdl);

/**
 * Function: gefVmeOpen
 *
 * Description:
 *    This function is used to open the VME device interface.  This function 
 *    must be called prior to all other functions in the VME API.
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> *bus_hdl - (O) A pointer to an opaque data handle for the
 *                                     framework.  At the end of a successful call
 *                                     to this function, this will point to a
 *                                     handle for the framework.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally, and
 *                                 _bus_hdl_ has been set to a valid
 *                                 framework handle.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle.
 *    GEF_STATUS_NO_SUCH_DEVICE  - The VME framework device driver is
 *                                 not present.
 *    GEF_STATUS_NO_MEM          - The function could not allocate memory
 *                                 required to successfully complete.
 *    GEF_STATUS_DRIVER_ERR      - An unexpected error from the driver was
 *                                 received.
 *
 * See Also:
 *    <gefVmeClose>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeOpen (GEF_VME_BUS_HDL *bus_hdl);

/**
 * Function: gefVmeClose
 *
 * Description:
 *    This function is used to close the VME device interface that was
 *    opened with <gefVmeOpen>.  Once this function is called, bus_hdl 
 *    is invalid, and should not be used.
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl - (I) An opaque data handle for the VME
 *                                    framework that the caller no longer wishes
 *                                    to use.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  The passed
 *                                 in handle is no longer valid.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_DRIVER_ERR      - An unexpected error from the driver was
 *                                 received.
 *
 * See Also:
 *    <gefVmeOpen>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeClose (GEF_VME_BUS_HDL bus_hdl);

/**
 * Function: gefVmeRead
 *
 * Description:
 *    Read from the VME device interface (Non-DMA transfer).  This function 
 *    will perform software byte swapping if configured to do so by the 
 *    <gefVmeSetReadWriteByteSwap> function.
 *
 * Parameters:
 *
 *    <GEF_VME_MASTER_HDL> master_hdl - (I) Handle to <GEF_VME_MASTER_HDL>.
 *    GEF_UINT32 offset               - (I) Offset from the master window base address. 
 *    GEF_UINT32 length               - (I) Length of the buffer.
 *    GEF_UINT8 *buffer               - (O) Pointer to the buffer.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _master_hdl_ parameter is not a valid
 *                                 master handle returned from <gefVmeCreateMasterWindow>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _offset_ parameter is not a valid offset.
 *    GEF_STATUS_BAD_PARAMETER_3 - The _length_ parameter is not a valid length.
 *    GEF_STATUS_BAD_PARAMETER_4 - The _buffer_ parameter is not a valid pointer.
 *
 * See Also:
 *    <gefVmeOpen>,
 *    <gefVmeCreateMasterWindow>,
 *    <gefVmeGetReadWriteByteSwap>,
 *    <gefVmeSetReadWriteByteSwap>,
 *    <gefVmeWrite>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeRead (GEF_VME_MASTER_HDL  master_hdl,
            GEF_UINT32          offset,
            GEF_UINT32          length,
            GEF_UINT8          *buffer);

/**
 * Function: gefVmeWrite
 *
 * Description:
 *    Write to the VME device interface (Non-DMA transfer).  This function 
 *    will perform software byte swapping if configured to do so by the 
 *    <gefVmeSetReadWriteByteSwap> function.
 *
 * Parameters:
 *    <GEF_VME_MASTER_HDL> master_hdl - (I) Handle to <GEF_VME_MASTER_HDL>.
 *    GEF_UINT32 offset               - (I) Offset from the master window base address. 
 *    GEF_UINT32 length               - (I) length of the buffer.
 *    GEF_UINT8  *buffer              - (I) Pointer to the buffer.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _master_hdl_ parameter is not a valid
 *                                 master handle returned from <gefVmeCreateMasterWindow>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _offset_ parameter is not a valid offset.
 *    GEF_STATUS_BAD_PARAMETER_3 - The _length_ parameter is not a valid length.
 *    GEF_STATUS_BAD_PARAMETER_4 - The _buffer_ parameter is not a valid pointer.
 *
 * See Also:
 *    <gefVmeOpen>,
 *    <gefVmeCreateMasterWindow>,
 *    <gefVmeGetReadWriteByteSwap>,
 *    <gefVmeSetReadWriteByteSwap>,
 *    <gefVmeRead>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeWrite (GEF_VME_MASTER_HDL  master_hdl, 
             GEF_UINT32          offset,
             GEF_UINT32          length, 
             GEF_UINT8          *buffer);

/**
 * Function: gefVmeRead8
 *
 * Description:
 *    Read from the VME device interface (Non-DMA transfer). This function
 *    attempts to read bytes from the VMEbus.
 *
 * Parameters:
 *    <GEF_VME_MASTER_HDL> master_hdl - (I) Handle to <GEF_VME_MASTER_HDL>.
 *    GEF_UINT32 offset               - (I) Offset from the master window base address. 
 *    GEF_UINT32 num_elements         - (I) Number of bytes to read.
 *    GEF_UINT8 *buffer               - (O) Pointer to the buffer.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _master_hdl_ parameter is not a valid
 *                                 master handle returned from <gefVmeCreateMasterWindow>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _offset_ parameter is not a valid offset.
 *    GEF_STATUS_BAD_PARAMETER_3 - The _num_elements_ parameter is not valid.
 *    GEF_STATUS_BAD_PARAMETER_4 - The _buffer_ parameter is not a valid pointer.
 *
 * See Also:
 *    <gefVmeOpen>,
 *    <gefVmeCreateMasterWindow>,
 *    <gefVmeWrite8>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeRead8 (GEF_VME_MASTER_HDL  master_hdl,
             GEF_UINT32          offset,
             GEF_UINT32          num_elements,
             GEF_UINT8          *buffer);

/**
 * Function: gefVmeWrite8
 *
 * Description:
 *    Read from the VME device interface (Non-DMA transfer). This function
 *    attempts to write bytes to the VMEbus.
 *
 * Parameters:
 *   <GEF_VME_MASTER_HDL> master_hdl - (I) Handle to <GEF_VME_MASTER_HDL>.
 *   GEF_UINT32 offset               - (I) Offset from the master window base address. 
 *   GEF_UINT32 num_elements         - (I) Number of bytes to write.
 *   GEF_UINT8 *buffer               - (I) Pointer to the buffer.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _master_hdl_ parameter is not a valid
 *                                 master handle returned from <gefVmeCreateMasterWindow>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _offset_ parameter is not a valid offset.
 *    GEF_STATUS_BAD_PARAMETER_3 - The _num_elements_ parameter is not valid.
 *    GEF_STATUS_BAD_PARAMETER_4 - The _buffer_ parameter is not a valid pointer.
 *
 * See Also:
 *    <gefVmeOpen>,
 *    <gefVmeCreateMasterWindow>,
 *    <gefVmeWrite>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeWrite8 (GEF_VME_MASTER_HDL  master_hdl, 
              GEF_UINT32          offset,
              GEF_UINT32          num_elements, 
              GEF_UINT8          *buffer);

/**
 * Function: gefVmeRead16
 *
 * Description:
 *    Read from the VME device interface (Non-DMA transfer). This function
 *    attempts to read 16-bit elements from the VMEbus.  This function 
 *    will perform software byte swapping if configured to do so by the 
 *    <gefVmeSetReadWriteByteSwap> function.
 *
 * Parameters:
 *   <GEF_VME_MASTER_HDL> master_hdl  - (I) Handle to <GEF_VME_MASTER_HDL>.
 *   GEF_UINT32 offset                - (I) Offset from the master window base address. 
 *   GEF_UINT32 num_elements          - (I) Number of 16-bit elements to read.
 *   GEF_UINT16 *buffer               - (O) Pointer to the buffer.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _master_hdl_ parameter is not a valid
 *                                 master handle returned from <gefVmeCreateMasterWindow>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _offset_ parameter is not a valid offset.
 *    GEF_STATUS_BAD_PARAMETER_3 - The _num_elements_ parameter is not valid.
 *    GEF_STATUS_BAD_PARAMETER_4 - The _buffer_ parameter is not a valid pointer.
 *
 * See Also:
 *    <gefVmeOpen>,
 *    <gefVmeCreateMasterWindow>,
 *    <gefVmeWrite>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeRead16 (GEF_VME_MASTER_HDL  master_hdl, 
              GEF_UINT32          offset, 
              GEF_UINT32          num_elements, 
              GEF_UINT16         *buffer);

/**
 * Function: gefVmeWrite16
 *
 * Description:
 *    Read from the VME device interface (Non-DMA transfer). This function
 *    attempts to write 16-bit elements to the VMEbus.  This function 
 *    will perform software byte swapping if configured to do so by the 
 *    <gefVmeSetReadWriteByteSwap> function.
 *
 * Parameters:
 *   <GEF_VME_MASTER_HDL> master_hdl - (I) Handle to <GEF_VME_MASTER_HDL>.
 *   GEF_UINT32 offset               - (I) Offset from the master window base address. 
 *   GEF_UINT32 num_elements         - (I) Number of 16-bit elements to write.
 *   GEF_UINT16 *buffer              - (I) Pointer to the buffer.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _master_hdl_ parameter is not a valid
 *                                 master handle returned from <gefVmeCreateMasterWindow>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _offset_ parameter is not a valid offset.
 *    GEF_STATUS_BAD_PARAMETER_3 - The _num_elements_ parameter is not valid.
 *    GEF_STATUS_BAD_PARAMETER_4 - The _buffer_ parameter is not a valid pointer.
 *
 * See Also:
 *    <gefVmeOpen>,
 *    <gefVmeCreateMasterWindow>,
 *    <gefVmeWrite>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeWrite16 (GEF_VME_MASTER_HDL  master_hdl, 
               GEF_UINT32          offset, 
               GEF_UINT32          num_elements, 
               GEF_UINT16         *buffer);

/**
 * Function: gefVmeRead32
 *
 * Description:
 *    Read from the VME device interface (Non-DMA transfer). This function
 *    attempts to read 32-bit elements from the VMEbus.  This function 
 *    will perform software byte swapping if configured to do so by the 
 *    <gefVmeSetReadWriteByteSwap> function.
 *
 * Parameters:
 *   <GEF_VME_MASTER_HDL> master_hdl - (I) Handle to <GEF_VME_MASTER_HDL>.
 *   GEF_UINT32 offset               - (I) Offset from the master window base address. 
 *   GEF_UINT32 num_elements         - (I) Number of 32-bit elements to read.
 *   GEF_UINT32 *buffer              - (O) Pointer to the buffer.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _master_hdl_ parameter is not a valid
 *                                 master handle returned from <gefVmeCreateMasterWindow>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _offset_ parameter is not a valid offset.
 *    GEF_STATUS_BAD_PARAMETER_3 - The _num_elements_ parameter is not valid.
 *    GEF_STATUS_BAD_PARAMETER_4 - The _buffer_ parameter is not a valid pointer.
 *
 * See Also:
 *    <gefVmeOpen>,
 *    <gefVmeCreateMasterWindow>,
 *    <gefVmeWrite>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeRead32 (GEF_VME_MASTER_HDL  master_hdl, 
              GEF_UINT32          offset, 
              GEF_UINT32          num_elements, 
              GEF_UINT32         *buffer);

/**
 * Function: gefVmeWrite32
 *
 * Description:
 *    Read from the VME device interface (Non-DMA transfer). This function
 *    attempts to write 32-bit elements to the VMEbus.  This function 
 *    will perform software byte swapping if configured to do so by the 
 *    <gefVmeSetReadWriteByteSwap> function.
 *
 * Parameters:
 *  <GEF_VME_MASTER_HDL> master_hdl   - (I) Handle to <GEF_VME_MASTER_HDL>.
 *  GEF_UINT32  offset                - (I) Offset from the master window base address. 
 *  GEF_UINT32  num_elements          - (I) Number of 32-bit elements to write.
 *  GEF_UINT32 *buffer                - (O) Pointer to the buffer.
 *  
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _master_hdl_ parameter is not a valid
 *                                 master handle returned from <gefVmeCreateMasterWindow>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _offset_ parameter is not a valid offset.
 *    GEF_STATUS_BAD_PARAMETER_3 - The _num_elements_ parameter is not valid.
 *    GEF_STATUS_BAD_PARAMETER_4 - The _buffer_ parameter is not a valid pointer.
 *
 * See Also:
 *    <gefVmeOpen>,
 *    <gefVmeCreateMasterWindow>,
 *    <gefVmeWrite>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeWrite32 (GEF_VME_MASTER_HDL  master_hdl, 
               GEF_UINT32          offset, 
               GEF_UINT32          num_elements, 
               GEF_UINT32         *buffer);

/**
 * Function: gefVmeRead64
 *
 * Description:
 *    Read from the VME device interface (Non-DMA transfer). This function
 *    attempts to read 64-bit elements from the VMEbus.  This function 
 *    will perform software byte swapping if configured to do so by the 
 *    <gefVmeSetReadWriteByteSwap> function.
 *
 * Parameters:
 *  <GEF_VME_MASTER_HDL> master_hdl - (I) Handle to <GEF_VME_MASTER_HDL>.
 *  GEF_UINT32 offset               - (I) Offset from the master window base address. 
 *  GEF_UINT32 num_elements         - (I) Number of 64-bit elements to read.
 *  GEF_UINT64 *buffer              - (O) Pointer to the buffer.
 *  
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _master_hdl_ parameter is not a valid
 *                                 master handle returned from <gefVmeCreateMasterWindow>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _offset_ parameter is not a valid offset.
 *    GEF_STATUS_BAD_PARAMETER_3 - The _num_elements_ parameter is not valid.
 *    GEF_STATUS_BAD_PARAMETER_4 - The _buffer_ parameter is not a valid pointer.
 *
 * See Also:
 *    <gefVmeOpen>,
 *    <gefVmeCreateMasterWindow>,
 *    <gefVmeWrite>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeRead64 (GEF_VME_MASTER_HDL  master_hdl, 
              GEF_UINT32          offset, 
              GEF_UINT32          num_elements, 
              GEF_UINT64         *buffer);

/**
 * Function: gefVmeWrite64
 *
 * Description:
 *    Write to the VME device interface (Non-DMA transfer). This function
 *    attempts to write 64-bit elements to the VMEbus.  This function 
 *    will perform software byte swapping if configured to do so by the 
 *    <gefVmeSetReadWriteByteSwap> function.
 *
 * Parameters:
 *  <GEF_VME_MASTER_HDL> master_hdl - (I) Handle to <GEF_VME_MASTER_HDL>.
 *  GEF_UINT32 offset               - (I) Offset from the master window base address. 
 *  GEF_UINT32 num_elements         - (I) Number of 64-bit elements to write.
 *  GEF_UINT64 *buffer              - (O) Pointer to the buffer.
 *  
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _master_hdl_ parameter is not a valid
 *                                 master handle returned from <gefVmeCreateMasterWindow>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _offset_ parameter is not a valid offset.
 *    GEF_STATUS_BAD_PARAMETER_3 - The _num_elements_ parameter is not valid.
 *    GEF_STATUS_BAD_PARAMETER_4 - The _buffer_ parameter is not a valid pointer.
 *
 * See Also:
 *    <gefVmeOpen>,
 *    <gefVmeCreateMasterWindow>,
 *    <gefVmeWrite>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeWrite64 (GEF_VME_MASTER_HDL  master_hdl, 
               GEF_UINT32          offset, 
               GEF_UINT32          num_elements, 
               GEF_UINT64         *buffer);


/**
 * Function:  gefVmeProbe
 *
 * Description:  
 *    Read from or write to an offset into an existing Master Window.  This function is useful
 *    for verifying the presence of an external board at the VMEbus address mapped by the Master Window.
 *    NOTE:  The gefVmeProbe() function is recommended for use during non-realtime initialization
 *    activities.  Erroneous results may occur if gefVmeProbe() is used while other threads or
 *    processes accessing the VMEbus encounter bus errors.
 *
 * Parameters:  
 *    <GEF_VME_MASTER_HDL> master_hdl   - (I) Handle to <GEF_VME_MASTER_HDL>.
 *    GEF_VME_DIR direction             - (I) Specifies a read or write probe.  
 *             Must be _GEF_VME_DIR_WRITE_ or _GEF_VME_DIR_READ_.
 *    GEF_UINT32 offset                 - (I) Offset from the master window base address.  
 *             Must be aligned according to _dwidth_.
 *    GEF_VME_DWIDTH dwidth             - (I) The width of the probe.  
 *            Must be _GEF_VME_DWIDTH_D8_, _GEF_VME_DWIDTH_D16_,
 *           _GEF_VME_DWIDTH_D32_, or _GEF_VME_DWIDTH_D64_.
 *    GEF_UINT8 *buffer                 - (IO) Where to store the value to be read or written.
 *
 * Returns:  
 *    GEF_STATUS_SUCCESS                - The probe indicates the presence of an external board at the VMEbus 
 *                address mapped by the Master Window.
 *    GEF_STATUS_BAD_PARAMETER_1        - The _master_hdl_ parameter is not a valid
 *                                 master handle returned from <gefVmeCreateMasterWindow>.
 *    GEF_STATUS_BAD_PARAMETER_2        - Invalid _direction_. 
 *    GEF_STATUS_BAD_PARAMETER_3        - The _offset_ parameter is too big for the Master Window size.
 *    GEF_STATUS_BAD_PARAMETER_4        - Invalid _dwidth_.
 *    GEF_STATUS_BAD_PARAMETER_5        - The _buffer_ parameter is NULL.
 *    GEF_STATUS_VME_OFFSET_NOT_ALIGNED - The _offset_ parameter is not aligned according to _dwidth_.
 *    GEF_STATUS_READ_ERR               - The _GEF_VME_DIR_READ_ probe resulted in Bus Error.  This indicates 
 *          the absence of an external board at the VMEbus address mapped by the Master Window.
 *    GEF_STATUS_WRITE_ERR              - The _GEF_VME_DIR_WRITE_ probe resulted in Bus Error.  This indicates 
 *          the absence of an external board at the VMEbus address mapped by the Master Window.
 *    GEF_STATUS_DRIVER_ERR             - (1) A Bus Error occurred, but not at the VMEbus address being probed;
 *          (2) a driver error occurred during the attempted read or write to the Master Window.
 *
 * See Also:  
 *    <gefVmeOpen>,
 *    <gefVmeCreateMasterWindow>
 *
 */
GEF_STATUS GEF_STD_CALL
gefVmeProbe(GEF_VME_MASTER_HDL master_hdl,
            GEF_VME_DIR        direction,
            GEF_UINT32         offset,                                     
            GEF_VME_DWIDTH     dwidth,
            GEF_UINT8         *buffer);


/**
 * Function: gefVmeCreateMasterWindow
 *
 * Description:
 *    Allocates a VMEbus Master Window handle.  This function opens a window 
 *    to the VME bus.  To access the VME bus, use the read and write functions
 *    and/or map the window to user space.  The VME bridge device has limited 
 *    resources, therefore try to optimize your usage of VME space.  If you
 *    make a call to this function that will fit within a previous call, then 
 *    no additional VME Bridge resources are used.  To create an exclusive window,
 *    then add VME_CTL_EXCLUSIVE to the flag parameter of <GEF_VME_ADDR>. 
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl        - (I) Handle allocated by <gefVmeOpen>.
 *    <GEF_VME_ADDR> *addr             - (I) VMEbus address structure of type GEF_VME_ADDR
 *    GEF_UINT32 size                  - (I) Minimum size of the window in bytes.
 *    <GEF_VME_MASTER_HDL> *master_hdl - (O) Handle to <GEF_VME_MASTER_HDL>.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _addr_ parameter is not a valid VMEbus address.
 *    GEF_STATUS_BAD_PARAMETER_3 - The _size_ parameter is not a valid size.
 *    GEF_STATUS_BAD_PARAMETER_4 - The _master_hdl_ parameter is not a valid
 *                                 master handle.
 *
 * See Also:
 *    <gefVmeOpen>,
 *    <gefVmeReleaseMasterWindow>, 
 *    <gefVmeFillMasterAddr>
 *    <gefVmeGetReadWriteByteSwap>,
 *    <gefVmeSetReadWriteByteSwap>,
 *    <gefVmeWrite>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeCreateMasterWindow (GEF_VME_BUS_HDL     bus_hdl,
                          GEF_VME_ADDR       *addr,
                          GEF_UINT32          size,
                          GEF_VME_MASTER_HDL *master_hdl);

/**
 * Function: gefVmeMapMasterWindow
 *
 * Description:
 *    Maps the VMEbus Master Window created by <gefVmeCreateMasterWindow> to the user process.
 *
 * Parameters:
 *    <GEF_VME_MASTER_HDL> master_hdl - (I) Handle to <GEF_VME_MASTER_HDL>.
 *    GEF_UINT32 offset               - (I) Offset from the buffer base address. 
 *    GEF_UINT32 size                 - (I) Size of the window.
 *    <GEF_MAP_HDL> *map_hdl          - (O) Handle to <GEF_MAP_HDL>.
 *    <GEF_MAP_PTR> *addr             - (O) Local address.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _master_hdl_ parameter is not a valid
 *                                 master handle returned from <gefVmeCreateMasterWindow>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _offset_ parameter is not a valid offset.
 *    GEF_STATUS_BAD_PARAMETER_3 - The _size_ parameter is not valid.
 *    GEF_STATUS_BAD_PARAMETER_4 - The _map_hdl_ parameter is not a valid pointer.
 *    GEF_STATUS_BAD_PARAMETER_5 - The _addr_ parameter is not a valid pointer.
 *
 * See Also:
 *    <gefVmeOpen>,
 *    <gefVmeCreateMasterWindow>,
 *    <gefVmeUnmapMasterWindow>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeMapMasterWindow (GEF_VME_MASTER_HDL   master_hdl,
                       GEF_UINT32           offset,
                       GEF_UINT32           size,
                       GEF_MAP_HDL         *map_hdl,
                       GEF_MAP_PTR         *addr);       

/**
 * Function: gefVmeUnmapMasterWindow
 *
 * Description:
 *    Unmaps the VMEbus Master Window that was mapped with <gefVmeMapMasterWindow> from the user process.
 *
 * Parameters:
 *    <GEF_MAP_HDL> map_hdl - (I) Handle to <GEF_MAP_HDL>.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _map_hdl_ parameter is not a valid
 *                                 master map handle returned from <gefVmeMapMasterWindow>.
 *
 * See Also:
 *    <gefVmeOpen>
 *    <gefVmeCreateMasterWindow>,
 *    <gefVmeMapMasterWindow>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeUnmapMasterWindow (GEF_MAP_HDL map_hdl);

/**
 * Function: gefVmeReleaseMasterWindow
 *
 * Description:
 *    Frees a previously allocated VMEbus Master Window handle that 
 *    was returned from <gefVmeCreateMasterWindow>.
 *
 * Parameters:
 *    <GEF_VME_MASTER_HDL> master_hdl - (I) Handle to <GEF_VME_MASTER_HDL>.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _master_hdl_ parameter is not a valid master 
 *                                 handle returned from <gefVmeCreateMasterWindow>.
 *
 * See Also:
 *    <gefVmeOpen>
 *    <gefVmeCreateMasterWindow>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeReleaseMasterWindow (GEF_VME_MASTER_HDL master_hdl);

/**
 * Function: gefVmeTranslateMasterWindow
 *
 * Description:
 *    Shifts the base VMEbus address of a VME Master Window. 
 *    The window must be created with the VME_CTL_EXCLUSIVE flag to use this function.
 *    The new VMEbus address must be aligned identically to the same 64-Kbyte boundary 
 *    as the original VMEbus address.
 *
 * Parameters:
 *    <GEF_VME_MASTER_HDL> master_hdl - (I) Handle to <GEF_VME_MASTER_HDL>.
 *    <GEF_VME_ADDR>       addr       - (I) VMEbus address structure of type <GEF_VME_ADDR>.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS                              - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED                        - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1                      - The _master_hdl_ parameter is not a valid
 *                                                      master handle returned from <gefVmeCreateMasterWindow>.
 *    GEF_STATUS_BAD_PARAMETER_2                      - The _addr_ parameter is not a valid 
 *                                                      pointer or does not point to a valid 
 *                                                      VME address.
 *    GEF_STATUS_VME_MASTER_WND_NOT_EXCLUSIVE         - The _addr_ parameter passed into 
 *                                                      <gefVmeCreateMasterWindow> did not 
 *                                                      have GEF_VME_WND_EXCLUSIVE flag set.
 *    GEF_STATUS_VME_MASTER_WND_TRANSLATE_NOT_ALIGNED - The _addr_ parameter is not aligned with _addr_ 
 *                                                      parameter passed into <gefVmeCreateMasterWindow>.
 *
 * See Also:
 *    <gefVmeOpen>
 *    <gefVmeCreateMasterWindow>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeTranslateMasterWindow (GEF_VME_MASTER_HDL  master_hdl,
                             GEF_VME_ADDR       *addr);

/**
 * Function: gefVmeReadModifyWrite
 *
 * Description:
 *    Performs a read/modify/write cycle on the VMEbus.
 *
 * Parameters:
 *    <GEF_VME_MASTER_HDL> master_hdl   - (I) Handle to <GEF_VME_MASTER_HDL>.
 *    GEF_UINT32 offset                 - (I) Offset from the window base.
 *    <GEF_VME_DWIDTH> dw               - (I) Access data width of the type <GEF_VME_DWIDTH>.
 *    GEF_UINT32 mask                   - (I) Mask of bits to be compared.
 *    GEF_UINT32 cmp                    - (I) Bit value to compare the read value against.
 *    GEF_UINT32 swap                   - (I) Bit values to write to bits that compared true.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _master_hdl_ parameter is not a valid
 *                                 master handle returned from <gefVmeCreateMasterWindow>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _offset_ parameter is not a valid offset.
 *    GEF_STATUS_BAD_PARAMETER_3 - The _dw_ parameter is not a valid data width.
 *
 * See Also:
 *    <gefVmeOpen>
 *    <gefVmeCreateMasterWindow>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeReadModifyWrite (GEF_VME_MASTER_HDL  master_hdl,
                       GEF_UINT32          offset,
                       GEF_VME_DWIDTH      dw,
                       GEF_UINT32          mask,
                       GEF_UINT32          cmp,
                       GEF_UINT32          swap);

/**
 * Function: gefVmeCreateSlaveWindow
 *
 * Description:
 *    This function allocates system memory that is then mapped to VME space.
 *    If this function is called with a <GEF_VME_ADDR>
 *    that is the same or a smaller window within a window on a previous call,
 *    then the slave_hdl will use resources that are a subset of the first 
 *    call.  In this case, the physical memory will be the same memory as no 
 *    new window will be opened on the device.  Try to avoid creating and 
 *    removing slave windows as the system memory would become 
 *    fragmented, eventually resulting in the call failing.  Because 
 *    slave windows use SBC system memory, try to avoid creating a window 
 *    larger than necessary for the application.  Since the VME bridge 
 *    device has a limited number of mapping windows, avoid calling this 
 *    function with many different window requests, instead make a larger 
 *    request that would include all the necessary memory to map, then make 
 *    additional calls that would fall within the same window.
 *
 * Parameters:
 *   <GEF_VME_BUS_HDL> bus_hdl      - (I) Handle allocated by <gefVmeOpen>.
 *   <GEF_VME_ADDR> *addr           - (I) Pointer to VMEbus address structure of type <GEF_VME_ADDR>.
 *   GEF_UINT32 size                - (I) Minimum size of the window, in bytes.
 *   <GEF_VME_SLAVE_HDL> *slave_hdl - (O) Handle to <GEF_VME_SLAVE_HDL>.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned by <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _addr_ parameter is not a valid pointer or
 *                                 does not point to a valid VME address.
 *    GEF_STATUS_BAD_PARAMETER_3 - The _size_ parameter is not a valid size.
 *    GEF_STATUS_BAD_PARAMETER_4 - The _slave_hdl_ parameter is not a valid pointer.
 *
 * See Also:
 *    <gefVmeOpen>
 *    <gefVmeCreateMasterWindow>
 *    <gefVmeFillSlvAddr>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeCreateSlaveWindow (GEF_VME_BUS_HDL    bus_hdl,
                         GEF_VME_ADDR      *addr,
                         GEF_UINT32         size,
                         GEF_VME_SLAVE_HDL *slave_hdl);

/**
 * Function: gefVmeMapSlaveWindow
 *
 * Description:
 *    This function maps the system memory that is mapped by 
 *    <gefVmeCreateSlaveWindow> to a VMEbus Slave Window.
 *
 * Parameters:
 *    <GEF_VME_SLAVE_HDL> slave_hdl - (I) Handle to <GEF_VME_SLAVE_HDL>.
 *    GEF_UINT32 offset             - (I) offset from the base address.
 *    GEF_UINT32 size               - (I) size of the window.
 *    <GEF_MAP_HDL> *map_hdl        - (O) Handle to <GEF_MAP_HDL>.
 *    <GEF_MAP_PTR> *addr           - (O) address to be mapped.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _slave_hdl_ parameter is not a valid
 *                                 slave handle returned from <gefVmeCreateSlaveWindow>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _offset_ parameter is not a valid offset.
 *    GEF_STATUS_BAD_PARAMETER_3 - The _size_ parameter is not a valid size.
 *    GEF_STATUS_BAD_PARAMETER_4 - The _map_hdl_ parameter is not a valid pointer.
 *    GEF_STATUS_BAD_PARAMETER_5 - The _addr_ parameter is not a valid pointer.
 *
 * See Also:
 *    <gefVmeOpen>
 *    <gefVmeCreateSlaveWindow>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeMapSlaveWindow (GEF_VME_SLAVE_HDL   slave_hdl,
                      GEF_UINT32          offset,
                      GEF_UINT32          size,
                      GEF_MAP_HDL        *map_hdl,
                      GEF_MAP_PTR        *addr);       

/**
 * Function: gefVmeRemoveSlaveWindow
 *
 * Description:
 *    This function releases the resources allocated by 
 *    <gefVmeCreateSlaveWindow>.  If no other process is using 
 *    the same slave resources, then the system memory is freed
 *    and the window is released on the VME Bridge device.
 *
 * Parameters:
 *    <GEF_VME_SLAVE_HDL> slave_hdl - (I) Handle to <GEF_VME_SLAVE_HDL>.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _slave_hdl_ parameter is not a valid
 *                                 slave handle returned from <gefVmeCreateSlaveWindow>.
 *
 * See Also:
 *    <gefVmeOpen>
 *    <gefVmeCreateSlaveWindow>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeRemoveSlaveWindow (GEF_VME_SLAVE_HDL  slave_hdl);

/**
 * Function: gefVmeUnmapSlaveWindow
 *
 * Description:
 *    This function unmaps the mapping returned from <gefVmeMapSlaveWindow>.
 *
 * Parameters:
 *    <GEF_MAP_HDL> map_hdl - (I) Handle to <GEF_MAP_HDL>.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _map_hdl_ parameter is not a valid
 *                                 map handle returned from <gefVmeMapSlaveWindow>.
 *
 * See Also:
 *    <gefVmeOpen>
 *    <gefVmeCreateSlaveWindow>
 *    <gefVmeMapSlaveWindow>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeUnmapSlaveWindow (GEF_MAP_HDL map_hdl);

/**
 * Function: gefVmeReadDma
 *
 * Description:
 *    Reads data from the VMEbus using DMA.  This function does not require
 *    any VME windows.
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl - (I) Handle allocated by <gefVmeOpen>.
 *    <GEF_VME_ADDR> *src_addr  - (I) Source VME address of type <GEF_VME_ADDR>.
 *    void *dst_addr            - (I) Destination address.
 *    GEF_UINT32 length         - (I) Number of bytes to be transferred.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned by <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _src_addr_ parameter is not a valid pointer or
 *                                 does not point to a valid VME address.
 *    GEF_STATUS_BAD_PARAMETER_3 - The _dst_addr_ parameter is not a valid pointer.
 *    GEF_STATUS_BAD_PARAMETER_4 - The _length_ parameter is not a supported length.
 *    GEF_STATUS_VME_DMA_BERR    - Bus error on VME access.
 *    GEF_STATUS_OPERATION_NOT_ALLOWED - DMA is not allowed with certain VME 
 *                                       address modifiers.
 *
 * See Also:
 *    <gefVmeOpen>,
 *    <gefVmeWriteDma>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeReadDma (GEF_VME_BUS_HDL  bus_hdl,
               GEF_VME_ADDR    *src_addr, 
               void            *dst_addr,
               GEF_UINT32       length);

/**
 * Function: gefVmeWriteDma
 *
 * Description:
 *    Writes data to the VMEbus using DMA.  This function does not require
 *    any VME windows. 
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl - (I) Handle allocated by <gefVmeOpen>.
 *    void *src_addr            - (I) source Address.
 *    <GEF_VME_ADDR> *dst_addr  - (I) destination address.VME address of type <GEF_VME_ADDR>.
 *    GEF_UINT32 length         - (I) Number of bytes to be transferred.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned by <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _src_addr_ parameter is not a valid pointer.
 *    GEF_STATUS_BAD_PARAMETER_3 - The _dst_addr_ parameter is not a valid pointer or
 *                                 does not point to a valid VME address.
 *    GEF_STATUS_BAD_PARAMETER_4 - The _length_ parameter is not a valid length.
 *    GEF_STATUS_VME_DMA_BERR    - Bus error on VME access.
 *    GEF_STATUS_OPERATION_NOT_ALLOWED - DMA is not allowed with certain VME 
 *                                       address modifiers.
 *
 * See Also:
 *    <gefVmeOpen>
 *    <gefVmeReadDma>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeWriteDma (GEF_VME_BUS_HDL  bus_hdl,
                void            *src_addr,
                GEF_VME_ADDR    *dst_addr,
                GEF_UINT32       length);

/**
 * Function: gefVmeAllocDmaBuf
 *
 * Description:
 *    Allocates a contiguous DMA buffer in system memory.  This function 
 *    is using limited system resources.  Try to avoid creating and 
 *    removing DMA buffers as the system memory would become 
 *    fragmented, eventually resulting in the call failing.  Because 
 *    DMA buffers use SBC system memory, try to avoid creating a buffer 
 *    larger than necessary for the application.  Using <gefVmeReadDma> 
 *    and/or <gefVmeWriteDma> avoids the use of system memory.
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl  - (I) Handle allocated by <gefVmeOpen>.
 *    GEF_UINT32 size            - (I) size of the buffer.
 *    <GEF_VME_DMA_HDL> *dma_hdl - (O) DMA handle of type <GEF_VME_DMA_HDL>.
 *    void **addr                - (O) User process address to allocated DMA Buffer.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned by <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _size_ parameter is not a supported size.
 *    GEF_STATUS_BAD_PARAMETER_3 - The _dma_hdl_ parameter is not a valid pointer.
 *    GEF_STATUS_BAD_PARAMETER_4 - The _addr_ parameter is not a valid pointer.
 *
 * See Also:
 *    <gefVmeOpen>,
 *    <gefVmeFreeDmaBuf>,
 *    <gefVmeReadDmaBuf>,
 *    <gefVmeWriteDmaBuf>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeAllocDmaBuf (GEF_VME_BUS_HDL   bus_hdl, 
                   GEF_UINT32        size, 
                   GEF_VME_DMA_HDL  *dma_hdl,
                   GEF_MAP_PTR      *addr);

/**
 * Function: gefVmeFreeDmaBuf
 *
 * Description:
 *    Frees the contiguous DMA buffer allocated by <gefVmeAllocDmaBuf>.   
 *
 * Parameters:
 *    <GEF_VME_DMA_HDL> dma_hdl - (I) Handle to <GEF_VME_DMA_HDL>.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _dma_hdl_ parameter is not a valid
 *                                 DMA handle returned from <gefVmeAllocDmaBuf>.
 *
 * See Also:
 *    <gefVmeOpen>,
 *    <gefVmeAllocDmaBuf>,
 *    <gefVmeReadDmaBuf>,
 *    <gefVmeWriteDmaBuf>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeFreeDmaBuf (GEF_VME_DMA_HDL dma_hdl);

/**
 * Function: gefVmeReadDmaBuf
 *
 * Description:
 *    Reads data from the VMEbus using DMA transfer to a DMA buffer allocated 
 *    by <gefVmeAllocDmaBuf>.  This function does not require any VME windows. 
 *
 * Parameters:
 *   <GEF_VME_DMA_HDL> dma_hdl - (I) DMA handle of type <GEF_VME_DMA_HDL>.
 *   <GEF_VME_ADDR> *src_addr  - (I) Source address. VME address of type <GEF_VME_ADDR>.
 *   GEF_UINT32 offset         - (I) Offset from the base address.
 *   GEF_UINT32 length         - (I) number of bytes.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _dma_hdl_ parameter is not a valid
 *                                 DMA handle returned from <gefVmeAllocDmaBuf>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _src_addr_ parameter is not a valid pointer or is
 *                                 not a valid value.
 *    GEF_STATUS_BAD_PARAMETER_3 - The _offset_ parameter is not a valid offset.
 *    GEF_STATUS_BAD_PARAMETER_4 - The _length_ parameter is not a valid length.
 *    GEF_STATUS_VME_DMA_BERR    - Bus error on VME access.
 *    GEF_STATUS_OPERATION_NOT_ALLOWED - DMA is not allowed with certain VME 
 *                                       address modifiers.
 *
 * See Also:
 *    <gefVmeOpen>
 *    <gefVmeAllocDmaBuf>, 
 *    <gefVmeFreeDmaBuf>,
 *    <gefVmeWriteDmaBuf>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeReadDmaBuf (GEF_VME_DMA_HDL  dma_hdl,
                  GEF_VME_ADDR    *src_addr, 
                  GEF_UINT32       offset,
                  GEF_UINT32       length);

/**
 * Function: gefVmeWriteDmaBuf
 *
 * Description:
 *    Writes data to the VMEbus using DMA transfer to a DMA buffer allocated 
 *    by <gefVmeAllocDmaBuf>.  This function does not require any VME windows.
 *
 * Parameters:
 *    <GEF_VME_DMA_HDL> dma_hdl - (I) DMA handle of type <GEF_VME_DMA_HDL>.
 *    GEF_UINT32 offset         - (I) Offset from the base address.
 *    <GEF_VME_ADDR> *dst_addr  - (I) Destination address. VME address of type <GEF_VME_ADDR>.
 *    GEF_UINT32 length         - (I) number of bytes.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _dma_hdl_ parameter is not a valid
 *                                 DMA handle returned from <gefVmeAllocDmaBuf>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _offset_ parameter is not a valid offset.
 *    GEF_STATUS_BAD_PARAMETER_3 - The _dst_addr_ parameter is not a valid pointer or is
 *                                 not a valid value.
 *    GEF_STATUS_BAD_PARAMETER_4 - The _length_ parameter is not a valid length.
 *    GEF_STATUS_VME_DMA_BERR    - Bus error on VME access.
 *    GEF_STATUS_OPERATION_NOT_ALLOWED - DMA is not allowed with certain VME 
 *                                       address modifiers.
 *
 * See Also:
 *    <gefVmeOpen>
 *    <gefVmeAllocDmaBuf>, 
 *    <gefVmeFreeDmaBuf>,
 *    <gefVmeReadDmaBuf>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeWriteDmaBuf (GEF_VME_DMA_HDL  dma_hdl,
                   GEF_UINT32       offset,
                   GEF_VME_ADDR    *dst_addr,
                   GEF_UINT32       length);

/**
 * Function: gefVmeAttachCallback
 *
 * Description:
 *    Attaches a user function to an interrupt.  An arbitrary thread invokes the handler.
 *    When the interrupt occurs the callback function is invoked with information about the
 *    interrupt, as well as a user supplied argument.  VME interrupts are registered by
 *    providing int_level and int_vector.  Once an int_level has a callback attached, the 
 *    VME Bridge device will respond to all interrupts at that level.  If an Interrupt
 *    Acknowledge returns a vector that does not match a registered callback, a
 *    spurious interrupt message will be logged in the system log.  If the spurious interrupt
 *    is generated by a device that is of the type Release on Register Access, it is possible 
 *    the system could appear locked up as the interrupt level is never released.
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl         - (I) Handle allocated by <gefVmeOpen>.
 *    <GEF_VME_INT_LEVEL> int_level     - (I) VMEbus interrupt level.
 *    GEF_UINT32 int_vector             - (I) Interrupt vector. Possible values
 *                                            are 0 to 255 for VIRQ[1-7], or 0 
 *                                            for all other interrupt levels.
 *    <GEF_VME_INT_CALLBACK> callback   - (I) Function pointer to user 
 *                                            supplied function of the 
 *                                            type <GEF_VME_INT_CALLBACK>.
 *    void *arg                         - (I) A user supplied argument for 
 *                                            the callback function supplied 
 *                                            by the user.
 *    <GEF_CALLBACK_HDL> *callback_hdl  - (O) Pointer to the callback handle 
 *                                            to allocate.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _int_level_ parameter is not a valid value.
 *    GEF_STATUS_BAD_PARAMETER_3 - The _int_vector_ parameter is not a supported value.
 *    GEF_STATUS_BAD_PARAMETER_4 - The _callback_ parameter is not a valid function pointer.
 *    GEF_STATUS_BAD_PARAMETER_6 - The _callback_hdl_ parameter is not a valid pointer. 
 *
 * See Also:
 *    <gefVmeOpen>,
 *    <gefVmeReleaseCallback>,
 *    <gefVmeCallbackGetBusHdl>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeAttachCallback (GEF_VME_BUS_HDL       bus_hdl,
                      GEF_VME_INT_LEVEL     int_level,
                      GEF_UINT32            int_vector,
                      GEF_VME_INT_CALLBACK  callback,
                      void                 *arg,
                      GEF_CALLBACK_HDL     *callback_hdl);

/**
 * Function: gefVmeReleaseCallback
 *
 * Description:
 *    Releases the callback attached with <gefVmeAttachCallback>. 
 *
 * Parameters:
 *    <GEF_CALLBACK_HDL> callback_hdl - (I) Pointer to the callback handle to release.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _callback_hdl_ parameter is not a valid
 *                                 callback handle returned by <gefVmeAttachCallback>.
 *
 * See Also:
 *    <gefVmeOpen>
 *    <gefVmeAttachCallback>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeReleaseCallback (GEF_CALLBACK_HDL callback_hdl);


/**
 * Function: gefVmeWait
 *
 * Description:
 *    Waits for a VME interrupt.  This call blocks until the event occurs, 
 *    the timeout expires or is released by <gefVmeReleaseWait>.  Once the
 *    user code is complete with the servicing of the event, the code must 
 *    call <gefVmeWaitAck> with the wait_hdl returned from this call.
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl      - (I) Handle allocated by <gefVmeOpen>.
 *    <GEF_VME_INT_LEVEL> int_level  - (I) VMEbus interrupt level.
 *    GEF_UINT32 int_vector          - (I) Interrupt vector. Possible values are 0 to 255.
 *    <struct timeval> *timeout      - (I) Timeout specified in seconds and microseconds.
 *    <GEF_VME_INT_INFO> *int_info   - (O) Pointer to <GEF_VME_INT_INFO> structure. 
 *    <GEF_VME_WAIT_HDL> *wait_hdl   - (O) handle for interrupt acknowledge
 *
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _int_level_ parameter is not a valid value.
 *    GEF_STATUS_BAD_PARAMETER_3 - The _int_vector_ parameter is not a supported value.
 *    GEF_STATUS_BAD_PARAMETER_4 - The _timeout_ parameter is not a valid pointer.
 *    GEF_STATUS_BAD_PARAMETER_5 - The _int_info_ parameter is not a valid pointer 
 *                                 or does not point to a valid int_info value.
 *    GEF_STATUS_BAD_PARAMETER_6 - The _wait_hdl_ parameter is not a valid pointer.
 *
 *
 * See Also:
 *    <gefVmeOpen>
 *    <gefVmeWaitAck>
 *    <gefReleaseWait>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeWait (GEF_VME_BUS_HDL    bus_hdl,
            GEF_VME_INT_LEVEL  int_level,
            GEF_UINT32         int_vector,
            struct timeval    *timeout,
            GEF_VME_INT_INFO  *int_info,
            GEF_VME_WAIT_HDL  *wait_hdl);

/**
 * Function: gefVmeWaitAck
 *
 * Description:
 *    Acknowledges a VME interrupt.  This function shall only be called 
 *    with a wait_hdl returned from a <gefVmeWait> that had a successful
 *    status return.
 *
 * Parameters:
 *    <GEF_VME_WAIT_HDL> wait_hdl - (I) handle for interrupt acknowledge.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _wait_hdl_ parameter is not a valid
 *                                 wait handle returned from <gefVmeWait>.
 *    GEF_STATUS_EVENT_RELEASED  - <gefVmeReleaseWait> was called prior to <gefVmeWaitAck>.
 *
 * See Also:
 *    <gefVmeOpen>
 *    <gefVmeWait>
 *    <gefVmeReleaseWait>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeWaitAck (GEF_VME_WAIT_HDL  wait_hdl);

/**
 * Function: gefVmeReleaseWait
 *
 * Description:
 *    Releases a thread waiting for a VME interrupt using the <gefVmeWait>.
 *    <gefVmeWait> will return GEF_STATUS_EVENT_RELEASED.  Use this function 
 *    only if the process has a thread waiting.  If a callback
 *    is attached for the same int_level and int_vector, the callback thread 
 *    will exit if this function is called.  Use <gefVmeReleaseCallback> 
 *    to release a callback instead of this function.
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl     - (I) Handle allocated by <gefVmeOpen>.
 *    <GEF_VME_INT_LEVEL> int_level - (I) VMEbus interrupt level.
 *    GEF_UINT32 int_vector         - (I) Interrupt vector. Possible values are 0 to 255.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _int_level_ parameter is not a valid value.
 *    GEF_STATUS_BAD_PARAMETER_3 - The _int_vector_ parameter is not a supported value.
 *
 * See Also:
 *    <gefVmeOpen>,
 *    <gefVmeWait>,
 *    <gefVmeWaitAck>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeReleaseWait (GEF_VME_BUS_HDL    bus_hdl,
                   GEF_VME_INT_LEVEL  int_level,
                   GEF_UINT32         int_vector);

/**
 * Function: gefVmeGenerateInt
 *
 * Description:
 *    Generates a VMEbus interrupt.  This function will block until the 
 *    interrupt acknowledge takes place or the timeout expires.  If the
 *    timeout expires, the interrupt level will no longer be asserted.
 *    Some bridge chips limit the vectors that can be generated.  See your
 *    SBC manual for VME bridge chip limitations.  Universe based SBC's can
 *    generate only even vectors through software interrupts.  Tempe based
 *    SBC's can generate any vector from 0 to 255.
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl - (I) Handle allocated by <gefVmeOpen>.
 *    GEF_UINT8 int_level       - (I) VMEbus interrupt level.
 *    GEF_UINT8 int_vector      - (I) Interrupt vector. Possible values are 0 to 255.
 *    <struct timeval> *timeout - (I) Timeout specified in seconds and microseconds.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _int_level_ parameter is not a valid value.
 *    GEF_STATUS_BAD_PARAMETER_3 - The _int_vector_ parameter is not a supported value.
 *				   (Tempe can generate any vector from 0 to 255, Universe can only generate
 *				   even vectors from 0 to 254).
 *    GEF_STATUS_BAD_PARAMETER_4 - The _timeout_ parameter is not a valid pointer.
 *    GEF_STATUS_TIMED_OUT       - Timeout occurred on the iack cycle.
 *
 * See Also:
 *    <gefVmeOpen>
 *    <gefVmeWait>
 *    <gefReleaseWait>
 *    <gefVmeAttachCallback>, 
 *    <gefVmeReleaseCallback>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeGenerateInt (GEF_VME_BUS_HDL    bus_hdl,
                   GEF_VME_INT_LEVEL  int_level,
                   GEF_UINT8          int_vector,
                   struct timeval    *timeout);   

/**
 * Function: gefVmeSetBusReleaseMode
 *
 * Description:
 *    Sets the VMEbus release mode which determines when the VME 
 *    Master releases the VMEbus.
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl               - (I) Handle allocated by <gefVmeOpen>.
 *    <GEF_VME_BUS_RELEASE_MODE> release_mode - (I) Sets the VMEbus release mode of the
 *                                                  type <GEF_VME_BUS_RELEASE_MODE>.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _release_mode_ parameter is not a valid value.
 *
 * See Also:
 *    <gefVmeOpen>,
 *    <gefVmeGetBusReleaseMode>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeSetBusReleaseMode (GEF_VME_BUS_HDL          bus_hdl,
                         GEF_VME_BUS_RELEASE_MODE release_mode);

/**
 * Function: gefVmeGetBusReleaseMode
 *
 * Description:
 *    Returns the VMEbus release mode set by <gefVmeSetBusReleaseMode>
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl               - (I) Handle allocated by <gefVmeOpen>.
 *    <GEF_VME_BUS_RELEASE_MODE> release_mode - (O) Returns the current 
 *                                                  VMEbus release mode of 
 *                                                  the type <GEF_VME_BUS_RELEASE_MODE>.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _release_mode_ parameter is not a valid pointer.
 *
 * See Also:
 *    <gefVmeOpen>
 *    <gefVmeSetBusReleaseMode>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeGetBusReleaseMode (GEF_VME_BUS_HDL           bus_hdl,
                         GEF_VME_BUS_RELEASE_MODE *release_mode);

/**
 * Function: gefVmeSetBusRequestMode
 *
 * Description:
 *    Set the current VMEbus request mode. 
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl                   - (I) Handle allocated by <gefVmeOpen>.
 *    <GEF_VME_BUS_REQUEST_MODE> bus_request_mode - (I) Sets the bus request 
 *                                                      mode of the type <GEF_VME_BUS_REQUEST_MODE>.  
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _bus_request_mode_ parameter is not a valid value.
 *
 * See Also:
 *    <gefVmeOpen>
 *    <gefVmeGetBusRequestMode>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeSetBusRequestMode (GEF_VME_BUS_HDL          bus_hdl,
                         GEF_VME_BUS_REQUEST_MODE bus_request_mode);

/**
 * Function: gefVmeGetBusRequestMode
 *
 * Description:
 *    Return the current VMEbus request mode set by <gefVmeSetBusRequestMode>. 
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl                    - (I) Handle allocated by <gefVmeOpen>.
 *    <GEF_VME_BUS_REQUEST_MODE> *bus_request_mode - (O) Returns the bus request mode
 *                                                       of the type <GEF_VME_BUS_REQUEST_MODE>. 
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _bus_request_mode_ parameter is not a valid pointer.
 *
 * See Also:
 *    <gefVmeOpen>
 *    <gefVmeSetBusRequestMode>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeGetBusRequestMode (GEF_VME_BUS_HDL           bus_hdl,
                         GEF_VME_BUS_REQUEST_MODE *bus_request_mode);

/**
 * Function: gefVmeSetBusRequestLevel
 *
 * Description:
 *    Set the current VMEbus request level for the VME Master.
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl                     - (I) Handle allocated by <gefVmeOpen>.
 *    <GEF_VME_BUS_REQUEST_LEVEL> bus_request_level - (I) Bus request level of the 
 *                                                        type <GEF_VME_BUS_REQUEST_LEVEL>.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _bus_request_level_ parameter is not a valid value.
 *
 * See Also:
 *    <gefVmeOpen>
 *    <gefVmeGetBusRequestLevel>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeSetBusRequestLevel (GEF_VME_BUS_HDL           bus_hdl,
                          GEF_VME_BUS_REQUEST_LEVEL bus_request_level);

/**
 * Function: gefVmeGetBusRequestLevel
 *
 * Description:
 *    Returns the current VMEbus request level. 
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl                      - (I) Handle allocated by <gefVmeOpen>.
 *    <GEF_VME_BUS_REQUEST_LEVEL> *bus_request_level - (O) Returns the bus request level
 *                                                         of the type <GEF_VME_BUS_REQUEST_LEVEL>. 
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _bus_request_level_ parameter is not a valid pointer.
 *
 * See Also:
 *    <gefVmeOpen>
 *    <gefVmeSetBusRequestLevel>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeGetBusRequestLevel (GEF_VME_BUS_HDL            bus_hdl,
                          GEF_VME_BUS_REQUEST_LEVEL *bus_request_level);

/**
 * Function: gefVmeSetBusTimeout
 *
 * Description:
 *    Sets the VMEbus timeout value. 
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl         - (I) Handle allocated by <gefVmeOpen>.
 *    <GEF_VME_BUS_TIMEOUT> bus_timeout - (I) VMEbus timeout value, in microseconds, 
 *                                            of the type <GEF_VME_BUS_TIMEOUT>. 
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _bus_timeout_ parameter is not a valid value.
 *
 * See Also:
 *    <gefVmeOpen>
 *    <gefVmeGetBusTimeout>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeSetBusTimeout (GEF_VME_BUS_HDL     bus_hdl,
                     GEF_VME_BUS_TIMEOUT bus_timeout);

/**
 * Function: gefVmeGetBusTimeout
 *
 * Description:
 *    Gets the VMEbus timeout value. 
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl          - (I) Handle allocated by <gefVmeOpen>.
 *    <GEF_VME_BUS_TIMEOUT> *bus_timeout - (O) Returns the VMEbus timeout value, in microseconds, 
 *                                             of the type <GEF_VME_BUS_TIMEOUT>. 
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _bus_timeout_ parameter is not a valid pointer.
 *
 * See Also:
 *    <gefVmeOpen>
 *    <gefVmeSetBusTimeout>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeGetBusTimeout (GEF_VME_BUS_HDL      bus_hdl,
                     GEF_VME_BUS_TIMEOUT *bus_timeout);

/**
 * Function: gefVmeSetArbitrationMode
 *
 * Description:
 *    Sets the VMEbus arbitration mode.
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl           - (I) Handle allocated by <gefVmeOpen>.
 *    <GEF_VME_BUS_ARB_MODE> bus_arb_mode - (I) Sets VMEbus arbitration mode 
 *                                              of the type <GEF_VME_BUS_ARB_MODE>. 
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _bus_arb_mode_ parameter is not a valid value.
 *
 * See Also:
 *    <gefVmeOpen>
 *    <gefVmeGetArbitrationMode>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeSetArbitrationMode (GEF_VME_BUS_HDL      bus_hdl,
                          GEF_VME_BUS_ARB_MODE bus_arb_mode);

/**
 * Function: gefVmeGetArbitrationMode
 *
 * Description:
 *    Returns the current VMEbus arbitration mode.
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl            - (I) Handle allocated by <gefVmeOpen>.
 *    <GEF_VME_BUS_ARB_MODE> *bus_arb_mode - (O) Returns the VMEbus arbitration 
 *                                               mode of the type <GEF_VME_BUS_ARB_MODE>. 
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _bus_arb_mode_ parameter is not a valid pointer.
 *
 * See Also:
 *    <gefVmeOpen>
 *    <gefVmeSetArbitrationMode>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeGetArbitrationMode (GEF_VME_BUS_HDL       bus_hdl,
                          GEF_VME_BUS_ARB_MODE *bus_arb_mode);

/**
 * Function: gefVmeSetArbitrationTimeout
 *
 * Description:
 *    Sets the VMEbus arbitration timeout value. 
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl            - (I) Handle allocated by <gefVmeOpen>.
 *    <GEF_VME_ARB_TIMEOUT> arb_timeout    - (I) 0,16us setting.ATOEN (Arbiter Time-out Enable): 
 *                   When this bit is set, the VMEbus arbiter time-out function is enabled.
 *                   When the time-out function is enabled, the arbiter asserts BBSY* 
 *                   if a bus grant out signal remains asserted for 16 microseconds.
 *                   This causes the arbiter to re-arbitrate.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _arb_timeout_ parameter is not a valid value.
 *
 * See Also:
 *    <gefVmeOpen>
 *    <gefVmeGetArbitrationTimeout>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeSetArbitrationTimeout (GEF_VME_BUS_HDL      bus_hdl,
                             GEF_VME_ARB_TIMEOUT  arb_timeout);

/**
 * Function: gefVmeGetArbitrationTimeout
 *
 * Description:
 *    Gets the VMEbus arbitration timeout value. 
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl          - (I) Handle allocated by <gefVmeOpen>.
 *    <GEF_VME_ARB_TIMEOUT> *arb_timeout - (O) Gets the value of the arbitration timeout value.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not valid.
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _arb_timeout_ parameter is not a valid pointer.
 *
 * See Also:
 *    <gefVmeOpen>
 *    <gefVmeSetArbitrationTimeout>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeGetArbitrationTimeout (GEF_VME_BUS_HDL      bus_hdl,
                             GEF_VME_ARB_TIMEOUT *arb_timeout);

/**
 * Function: gefVmeSetBusBroadcastId
 *
 * Description:
 *    Sets up the 2eSST broadcast id that slave windows will respond to.  
 *    If the broadcast id is set to GEF_VME_BROADCAST_ID_DISABLE the 
 *    VME Slave will not respond to a 2eSST broadcast transfer.  This 
 *    setting applies to all slave windows.  By default, the broadcast 
 *    id is set to GEF_VME_BROADCAST_ID_DISABLE.  On SBC's with the 
 *    Tundra Tempe this call configures the BID bits in the VCTRL register.  
 *    This function will return GEF_STATUS_NOT_SUPPORTED on Tundra Universe 
 *    based SBC's.  
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl           - (I) Handle allocated by <gefVmeOpen>.
 *    <GEF_VME_BROADCAST_ID> broadcast_id - (I) Value to be set.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _broadcast_id_ parameter is not a valid value.
 *
 * See Also:
 *    <gefVmeOpen>
 *    <gefVmeGetBusBroadcastId>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeSetBusBroadcastId (GEF_VME_BUS_HDL       bus_hdl,
                         GEF_VME_BROADCAST_ID  broadcast_id);

/**
 * Function: gefVmeGetBusBroadcastId
 *
 * Description:
 *    Returns the current setting of the 2eSST broadcast id set 
 *    by <gefVmeSetBusBroadcastId>.  By default, the broadcast 
 *    id is set to GEF_VME_BROADCAST_ID_DISABLE.  This function will return 
 *    GEF_STATUS_NOT_SUPPORTED on Tundra Universe based SBC's.
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl            - (I) Handle allocated by <gefVmeOpen>.
 *    <GEF_VME_BROADCAST_ID> *broadcast_id - (O) Gets the Broadcast Id of the type <GEF_VME_BROADCAST_ID>.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _broadcast_id_ parameter is not a valid pointer.
 *
 * See Also:
 *    <gefVmeOpen>
 *    <gefVmeSetBusBroadcastId>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeGetBusBroadcastId (GEF_VME_BUS_HDL       bus_hdl,
                         GEF_VME_BROADCAST_ID *broadcast_id);

/**
 * Function: gefVmeGetSysfail
 *
 * Description:
 *    Reads the system fail status register. 
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl - (I) Handle allocated by <gefVmeOpen>.
 *    GEF_BOOL *sysfail         - (O) Gets the sysfail status.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _sysfail_ parameter is not a valid pointer.
 *
 * See Also:
 *    <gefVmeOpen>
 *    <gefVmeSetSysfail>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeGetSysfail (GEF_VME_BUS_HDL  bus_hdl,
                  GEF_BOOL        *sysfail);

/**
 * Function: gefVmeSetSysfail
 *
 * Description:
 *    Writes to the system fail status register.
 *
 * Parameters:
 *     <GEF_VME_BUS_HDL> bus_hdl -  (I) Handle allocated by <gefVmeOpen>
 *     GEF_BOOL sysfail          -  (I) Sets the sysfail status.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *
 * See Also:
 *    <gefVmeOpen>
 *    <gefVmeGetSysfail>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeSetSysfail (GEF_VME_BUS_HDL  bus_hdl,
                  GEF_BOOL         sysfail);

/**
 * Function: gefVmeCreateLocationMonitor
 *
 * Description:
 *    This routinue is used to create a location monitor.  Location monitors 
 *    are used to support a VMEbus broadcast capability.  The vme_addr 
 *    specifies the start address of the location monitor.  When an access 
 *    to a location monitor is detected, an event is generated. You can 
 *    use <gefVmeAttachCallback> to attach a routine to the event, or 
 *    have a thread wait on the event using <gefVmeWait>.  VMEbus address 
 *    bits [4:3] determine which Location Monitor is used, and hence 
 *    which of four events are generated:
 * 
 * >         VMEbus Address   Location Monitor
 * >         Offset           Event
 * >         ---------------------------------
 * >         0-7              GEF_VME_INT_LM0  
 * >         8-F              GEF_VME_INT_LM1  
 * >         10-17            GEF_VME_INT_LM2
 * >         18-1F            GEF_VME_INT_LM3
 * 
 *     
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl - (I) Handle allocated by <gefVmeOpen>.
 *    <GEF_VME_ADDR> vme_addr   - (I) Pointer to structure allocated and initialized by user.
 *                                     upper - Upper 32 bit VME Address.
 *                                     lower - Lower 32 bit VME Address.
 *                                     as    - VME Address Space.
 *                                     flags - used to specify USER and/or SUPER and PROGRAM and/or
 *                                             DATA.
 *    <GEF_VME_LM_HDL> lm_hdl   - (O) Pointer to the location monitor handle to allocate.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS                    - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED              - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1            - The _bus_hdl_ parameter is not a valid
 *                                            vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2            - The _addr_ parameter is not a valid pointer.
 *    GEF_STATUS_BAD_PARAMETER_3            - The _lm_hdl_ parameter is not a valid pointer.
 *    GEF_STATUS_VME_LOCATION_MONITOR_INUSE - Location monitor already set up.  Call
 *                                            <gefVmeQueryLocationMonitor> to determine
 *                                            the location.
 *
 * See Also:
 *    <gefVmeOpen>
 *    <gefVmeReleaseLocationMonitor>,
 *    <gefVmeAttachCallback>,
 *    <gefVmeWait>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeCreateLocationMonitor (GEF_VME_BUS_HDL  bus_hdl,
                             GEF_VME_ADDR    *addr,
                             GEF_VME_LM_HDL  *lm_hdl);

/**
 * Function: gefVmeReleaseLocationMonitor
 *
 * Description:
 *    Releases a location monitor that was created by <gefVmeCreateLocationMonitor>. 
 *
 * Parameters:
 *    <GEF_VME_LM_HDL> lm_hdl - (I) Handle allocated by <gefVmeCreateLocationMonitor>.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _lm_hdl_ parameter is not a valid
 *                                 location monitor handle returned 
 *                                 from <gefVmeCreateLocationMonitor>.
 *
 * See Also:
 *    <gefVmeOpen>
 *    <gefVmeCreateLocationMonitor>
 *    <gefVmeQueryLocationMonitor>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeReleaseLocationMonitor (GEF_VME_LM_HDL  lm_hdl);

/**
 * Function: gefVmeQueryLocationMonitor
 *
 * Description:
 *    Reads the Location Monitor base address. 
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl - (I) Handle allocated by <gefVmeOpen>.
 *    <GEF_VME_ADDR> *addr      - (O) VMEbus address structure of type <GEF_VME_ADDR>.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _addr_ parameter is not a valid pointer.
 *
 * See Also:
 *    <gefVmeOpen>
 *    <gefVmeCreateLocationMonitor>, 
 *    <gefVmeReleaseLocationMonitor>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeQueryLocationMonitor (GEF_VME_BUS_HDL  bus_hdl,
                            GEF_VME_ADDR    *addr);

/**
 * Function: gefVmeCreateVRAImage
 *
 * Description:
 *    Creates a VRAI (VME register access) image. The VME registers will be 
 *    available on the VME bus at the location specified by the GEF_VME_ADDR 
 *    parameter.  This feature is available to allow writing to the mailbox
 *    registers and to allow other masters to see the Tundra programming.  
 *    Changing other registers will possibly cause the driver and/or
 *    system to fail.
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl - (I) Handle allocated by <gefVmeOpen>.
 *    <GEF_VME_ADDR> *addr      - (I) VMEbus address structure of type <GEF_VME_ADDR>.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS                       - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED                 - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1               - The _bus_hdl_ parameter is not a valid
 *                                               vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2               - The _addr_ parameter is not a valid pointer.
 *    GEF_STATUS_VME_VRA_IMAGE_ALREADY_CREATED - The VME Register Access Image has already been 
 *                                               created, call <gefVmeQueryVRAImage> to 
 *                                               determine the location of the image.
 *
 * See Also:
 *    <gefVmeOpen>
 *    <gefVmeQueryVRAImage>, 
 *    <gefVmeRemoveVRAImage>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeCreateVRAImage (GEF_VME_BUS_HDL  bus_hdl,
                      GEF_VME_ADDR    *addr);

/**
 * Function: gefVmeQueryVRAImage
 *
 * Description:
 *    Returns the VME address of the previously created VRAI image. 
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl - (I) Handle allocated by <gefVmeOpen>.
 *    <GEF_VME_ADDR> *addr      - (O) VMEbus address structure of type <GEF_VME_ADDR>.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS                   - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED             - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1           - The _bus_hdl_ parameter is not a valid
 *                                           vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2           - The _addr_ parameter is not a valid pointer.
 *    GEF_STATUS_VME_VRA_IMAGE_NOT_CREATED - VRAI image not created, call 
 *                                           <gefVmeCreateVRAImage> to create 
 *                                           the VRAI image.
 *
 * See Also:
 *    <gefVmeOpen>
 *    <gefVmeCreateVRAImage>, 
 *    <gefVmeRemoveVRAImage>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeQueryVRAImage (GEF_VME_BUS_HDL  bus_hdl,
                     GEF_VME_ADDR    *addr);

/**
 * Function: gefVmeRemoveVRAImage
 *
 * Description:
 *    Remove the VRAI image previously created. The VME registers will no 
 *    longer appear on the VME bus.
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl - (I) Handle allocated by <gefVmeOpen>.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS                   - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED             - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1           - The _bus_hdl_ parameter is not a valid
 *                                           vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_VME_VRA_IMAGE_NOT_CREATED - VRAI image not created, call 
 *                                           <gefVmeCreateVRAImage> to create 
 *                                           the VRAI image.
 *
 * See Also:
 *    <gefVmeOpen>
 *    <gefVmeCreateVRAImage>,
 *    <gefVmeQueryVRAImage>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeRemoveVRAImage (GEF_VME_BUS_HDL  bus_hdl);

/**
 * Function: gefVmeSysReset
 *
 * Description:
 *    Causes a VMEbus sysreset to be asserted. 
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl - (I) Handle allocated by <gefVmeOpen>.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *
 * See Also:
 *    <gefVmeOpen>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeSysReset (GEF_VME_BUS_HDL  bus_hdl);

/**
 * Function: gefVmeAcquireBusOwnership
 *
 * Description:
 *    Acquires ownership of the VMEbus.  For every call to <gefVmeAcquireBusOwnership> 
 *    there must be a corresponding call to <gefVmeReleaseBusOwnership>.  Failure 
 *    to do so will prevent all other traffic on the VMEbus.  
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl - (I) Handle allocated by <gefVmeOpen>.
 *    <struct timeval> *timeout - (I) Timeout specified in seconds and microseconds.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _timeout_ parameter is not a valid pointer.
 *    GEF_STATUS_TIMED_OUT       - Timeout occurred while waiting to acquire bus.
 *
 * See Also:
 *    <gefVmeOpen>,
 *    <gefVmeReleaseBusOwnership>, 
 *    <gefVmeQueryBusOwnership>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeAcquireBusOwnership (GEF_VME_BUS_HDL  bus_hdl,
                           struct timeval  *timeout);

/**
 * Function: gefVmeReleaseBusOwnership
 *
 * Description:
 *    Release ownership of the VMEbus.  If the VMEbus is not owned, this 
 *    function returns GEF_STATUS_SUCCESS.
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl - (I) Handle allocated by <gefVmeOpen>.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *
 * See Also:
 *    <gefVmeOpen>,
 *    <gefVmeAcquireBusOwnership>, 
 *    <gefVmeQueryBusOwnership>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeReleaseBusOwnership (GEF_VME_BUS_HDL  bus_hdl);

/**
 * Function: gefVmeQueryBusOwnership
 *
 * Description:
 *    Query the ownership status of the VMEbus.   
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl - (I) Handle allocated by <gefVmeOpen>.
 *    GEF_BOOL *vown            - (O) Pointer to variable to store the 
 *                                    current VMEbus ownership status.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _vown_ parameter is not a valid pointer.
 *
 * See Also:
 *    <gefVmeOpen>,
 *    <gefVmeAcquireBusOwnership>, 
 *    <gefVmeQueryBusOwnership>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeQueryBusOwnership (GEF_VME_BUS_HDL  bus_hdl, 
                         GEF_BOOL        *vown);

/**
 * Function: gefVmeSetMaxRetry
 *
 * Description:
 *    Sets the number of retries before the PCI master interface returns an 
 *    error.
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl     - (I) Handle allocated by <gefVmeOpen>.
 *    <GEF_VME_MAX_RETRY> max_retry - (I) Maximum number of retries.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _max_retry_ parameter is not a valid value.
 *
 * See Also:
 *    <gefVmeOpen>,
 *    <gefVmeGetMaxRetry>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeSetMaxRetry (GEF_VME_BUS_HDL   bus_hdl, 
                   GEF_VME_MAX_RETRY max_retry);

/**
 * Function: gefVmeGetMaxRetry
 *
 * Description:
 *    Gets the number of retries before the PCI master interface returns an 
 *    error.
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl      - (I) Handle allocated by <gefVmeOpen>.
 *    <GEF_VME_MAX_RETRY> *max_retry - (O) Read the Maximum number of retries previously set.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _max_retry_ parameter is not a valid pointer.
 *
 * See Also:
 *    <gefVmeOpen>,
 *    <gefVmeSetMaxRetry>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeGetMaxRetry (GEF_VME_BUS_HDL    bus_hdl, 
                   GEF_VME_MAX_RETRY *max_retry);

/**
 * Function: gefVmeSetPostedWriteCount
 *
 * Description:
 *    Sets the transfer count at which the PCI slave-channel-posted
 *    write FIFO releases the VMEbus master interface.   
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl - (I) Handle allocated by <gefVmeOpen>.
 *    <GEF_VME_PWON> pwon       - (I) Posted Write Transfer Count.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _pwon_ parameter is not a valid value.
 *
 * See Also:
 *    <gefVmeOpen>,
 *    <gefVmeGetPostedWriteCount>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeSetPostedWriteCount (GEF_VME_BUS_HDL bus_hdl, 
                           GEF_VME_PWON    pwon);

/**
 * Function: gefVmeGetPostedWriteCount
 *
 * Description:
 *    Gets the transfer count at which the PCI slave-channel-posted
 *    write FIFO releases the VMEbus master interface.   
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl - (I) Handle allocated by <gefVmeOpen>.
 *    <GEF_VME_PWON> *pwon      - (O) Posted Write Transfer Count.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _pwon_ parameter is not a valid pointer.
 *
 * See Also:
 *    <gefVmeOpen>,
 *    <gefVmeSetPostedWriteCount>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeGetPostedWriteCount (GEF_VME_BUS_HDL  bus_hdl, 
                           GEF_VME_PWON    *pwon);

/**
 * Function: gefVmeFillSlvAddr
 *
 * Description:
 *    Fill the VME Slave address information.   
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl                         - (I) Handle allocated by <gefVmeOpen>.
 *    GEF_UINT32 addr_upper                             - (I) Upper 32 Bit VME Address
 *    GEF_UINT32 addr_lower                             - (I) Lower 32 Bit VME Address
 *    <GEF_VME_ADDR_SPACE> addr_space                   - (I) Address space of type <GEF_VME_ADDR_SPACE>.
 *    GEF_UINT32 addr_mode                              - (I) Address mode.
 *    <GEF_VME_2ESST_RATE> vme_2esst_rate               - (I) VME 2esst rate of type <GEF_VME_2ESST_RATE>.
 *    GEF_UINT32 transfer_mode                          - (I) Transfer mode.
 *    <GEF_VME_TRANSFER_MAX_DWIDTH> transfer_max_dwidth - (I) VME maximum data width of type <GEF_VME_TRANSFER_MAX_DWIDTH>.
 *    <GEF_VME_WND_FLAGS> wnd_flags                     - (I) VME window flags of type <GEF_VME_WND_FLAGS>.
 *    <GEF_VME_ADDR> *addr                              - (O) VME address handle of type <GEF_VME_ADDR>.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS          - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED    - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1  - The _bus_hdl_ parameter is not a valid
 *                                  vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_10 - The _addr_ parameter is not a valid pointer.
 *
 * See Also:
 *    <gefVmeOpen>,
 *    <gefVmeFillMasterAddr>, 
 *    <gefVmeFillDMASrcAddr>, 
 *    <gefVmeFillDMADestAddr>, 
 *    <gefVmeFillLMAddr>, 
 *    <gefVmeFillVRAIAddr>, 
 *    <gefVmeFillAddrUsingAM>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeFillSlvAddr (GEF_VME_BUS_HDL              bus_hdl,     
                   GEF_UINT32                   addr_upper,
                   GEF_UINT32                   addr_lower,
                   GEF_VME_ADDR_SPACE           addr_space, 
                   GEF_UINT32                   addr_mode,
                   GEF_VME_2ESST_RATE           vme_2esst_rate,
                   GEF_UINT32                   transfer_mode,
                   GEF_VME_TRANSFER_MAX_DWIDTH  transfer_max_dwidth,
                   GEF_VME_WND_FLAGS            wnd_flags,
                   GEF_VME_ADDR                *addr);

/**
 * Function: gefVmeFillMasterAddr
 *
 * Description:
 *    Fill the VME Master address information.   
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl                         - (I) Handle allocated by <gefVmeOpen>.
 *    GEF_UINT32 addr_upper                             - (I) Upper 32 Bit VME Address
 *    GEF_UINT32 addr_lower                             - (I) Lower 32 Bit VME Address
 *    <GEF_VME_ADDR_SPACE> addr_space                   - (I) Address space of type <GEF_VME_ADDR_SPACE>.
 *    <GEF_VME_2ESST_RATE> vme_2esst_rate               - (I) VME 2esst rate of type <GEF_VME_2ESST_RATE>.
 *    GEF_UINT32 addr_mode                              - (I) Address mode.
 *    <GEF_VME_TRANSFER_MODE> transfer_mode             - (I) Transfer mode.
 *    GEF_UINT32 broadcast_id                           - (I) Broadcast Id.
 *    <GEF_VME_TRANSFER_MAX_DWIDTH> transfer_max_dwidth - (I) VME maximum data width of type <GEF_VME_TRANSFER_MAX_DWIDTH>.
 *    GEF_UINT32 wnd_flags                              - (I) VME window flags of type <GEF_VME_WND_FLAGS>.
 *    <GEF_VME_ADDR> *addr                              - (O) VME address handle of type <GEF_VME_ADDR>.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS          - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED    - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1  - The _bus_hdl_ parameter is not a valid
 *                                  vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_11 - The _addr_ parameter is not a valid pointer.
 *
 * See Also:
 *    <gefVmeOpen>,
 *    <gefVmeFillSlvAddr>, 
 *    <gefVmeFillDMASrcAddr>, 
 *    <gefVmeFillDMADestAddr>, 
 *    <gefVmeFillLMAddr>, 
 *    <gefVmeFillVRAIAddr>, 
 *    <gefVmeFillAddrUsingAM>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeFillMasterAddr (GEF_VME_BUS_HDL              bus_hdl,     
                      GEF_UINT32                   addr_upper,
                      GEF_UINT32                   addr_lower,
                      GEF_VME_ADDR_SPACE           addr_space, 
                      GEF_VME_2ESST_RATE           vme_2esst_rate,
                      GEF_VME_ADDR_MODE            addr_mode,
                      GEF_VME_TRANSFER_MODE        transfer_mode,
                      GEF_UINT32                   broadcast_id,
                      GEF_VME_TRANSFER_MAX_DWIDTH  transfer_max_dwidth,
                      GEF_UINT32                   wnd_flags,
                      GEF_VME_ADDR                *addr);

/**
 * Function: gefVmeFillDMASrcAddr
 *
 * Description:
 *    Fill the VME DMA source address information.   
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl                         - (I) Handle allocated by <gefVmeOpen>.
 *    GEF_UINT32 addr_upper                             - (I) Upper 32 Bit VME Address
 *    GEF_UINT32 addr_lower                             - (I) Lower 32 Bit VME Address
 *    <GEF_VME_ADDR_SPACE> addr_space                   - (I) Address space of type <GEF_VME_ADDR_SPACE>.
 *    <GEF_VME_ADDR_MODE> addr_mode                     - (I) Address mode.
 *    <GEF_VME_2ESST_RATE> vme_2esst_rate               - (I) VME 2esst rate of type <GEF_VME_2ESST_RATE>.
 *    <GEF_VME_TRANSFER_MODE> transfer_mode             - (I) Transfer mode.
 *    <GEF_VME_TRANSFER_MAX_DWIDTH> transfer_max_dwidth - (I) VME maximum data width of type <GEF_VME_TRANSFER_MAX_DWIDTH>.
 *    <GEF_VME_ADDR> *addr                              - (O) VME address handle of type <GEF_VME_ADDR>.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_9 - The _addr_ parameter is not a valid pointer.
 *
 * See Also:
 *    <gefVmeOpen>,
 *    <gefVmeFillSlvAddr>, 
 *    <gefVmeFillMasterAddr>, 
 *    <gefVmeFillDMADestAddr>, 
 *    <gefVmeFillLMAddr>, 
 *    <gefVmeFillVRAIAddr>, 
 *    <gefVmeFillAddrUsingAM>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeFillDMASrcAddr (GEF_VME_BUS_HDL              bus_hdl,     
                      GEF_UINT32                   addr_upper,
                      GEF_UINT32                   addr_lower,
                      GEF_VME_ADDR_SPACE           addr_space, 
                      GEF_VME_ADDR_MODE            addr_mode,
                      GEF_VME_2ESST_RATE           vme_2esst_rate,
                      GEF_VME_TRANSFER_MODE        transfer_mode,
                      GEF_VME_TRANSFER_MAX_DWIDTH  transfer_max_dwidth,
                      GEF_VME_ADDR                *addr);

/**
 * Function: gefVmeFillDMADestAddr
 *
 * Description:
 *    Fill the VME DMA destination address information.
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl                         - (I) Handle allocated by <gefVmeOpen>.
 *    GEF_UINT32 addr_upper                             - (I) Upper 32 Bit VME Address
 *    GEF_UINT32 addr_lower                             - (I) Lower 32 Bit VME Address
 *    <GEF_VME_ADDR_SPACE> addr_space                   - (I) Address space of type <GEF_VME_ADDR_SPACE>.
 *    <GEF_VME_ADDR_MODE> addr_mode                     - (I) Address mode.
 *    <GEF_VME_2ESST_RATE> vme_2esst_rate               - (I) VME 2esst rate of type <GEF_VME_2ESST_RATE>.
 *    <GEF_VME_TRANSFER_MODE> transfer_mode             - (I) Transfer mode.
 *    <GEF_VME_TRANSFER_MAX_DWIDTH> transfer_max_dwidth - (I) VME maximum data width of type <GEF_VME_TRANSFER_MAX_DWIDTH>.
 *    <GEF_VME_ADDR> *addr                              - (O) VME address handle of type <GEF_VME_ADDR>.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_9 - The _addr_ parameter is not a valid pointer.
 *
 * See Also:
 *    <gefVmeOpen>,
 *    <gefVmeFillSlvAddr>, 
 *    <gefVmeFillMasterAddr>, 
 *    <gefVmeFillDMASrcAddr>, 
 *    <gefVmeFillLMAddr>, 
 *    <gefVmeFillVRAIAddr>, 
 *    <gefVmeFillAddrUsingAM>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeFillDMADestAddr (GEF_VME_BUS_HDL              bus_hdl,     
                       GEF_UINT32                   addr_upper,
                       GEF_UINT32                   addr_lower,
                       GEF_VME_ADDR_SPACE           addr_space, 
                       GEF_VME_ADDR_MODE            addr_mode,
                       GEF_VME_2ESST_RATE           vme_2esst_rate,
                       GEF_VME_TRANSFER_MODE        transfer_mode,
                       GEF_VME_TRANSFER_MAX_DWIDTH  transfer_max_dwidth,
                       GEF_VME_ADDR                *addr);

/**
 * Function: gefVmeFillLMAddr
 *
 * Description:
 *    Fill the VME Location monitor address information.
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl       - (I) Handle allocated by <gefVmeOpen>.
 *    GEF_UINT32 addr_upper           - (I) Upper 32 Bit VME Address
 *    GEF_UINT32 addr_lower           - (I) Lower 32 Bit VME Address
 *    <GEF_VME_ADDR_SPACE> addr_space - (I) Address space of type <GEF_VME_ADDR_SPACE>.
 *    GEF_UINT32 addr_mode            - (I) Address mode.
 *    <GEF_VME_ADDR> *addr            - (O) VME address handle of type <GEF_VME_ADDR>.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_6 - The _addr_ parameter is not a valid pointer.
 *
 * See Also:
 *    <gefVmeOpen>,
 *    <gefVmeFillSlvAddr>, 
 *    <gefVmeFillMasterAddr>, 
 *    <gefVmeFillDMASrcAddr>, 
 *    <gefVmeFillDMASrcAddr>, 
 *    <gefVmeFillVRAIAddr>, 
 *    <gefVmeFillAddrUsingAM>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeFillLMAddr (GEF_VME_BUS_HDL              bus_hdl,     
                  GEF_UINT32                   addr_upper,
                  GEF_UINT32                   addr_lower,
                  GEF_VME_ADDR_SPACE           addr_space, 
                  GEF_UINT32                   addr_mode,
                  GEF_VME_ADDR                *addr);

/**
 * Function: gefVmeFillVRAIAddr
 *
 * Description:
 *    Fill the VME VRAI address information.
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl       - (I) Handle allocated by <gefVmeOpen>.
 *    GEF_UINT32 addr_upper           - (I) Upper 32 Bit VME Address
 *    GEF_UINT32 addr_lower           - (I) Lower 32 Bit VME Address
 *    <GEF_VME_ADDR_SPACE> addr_space - (I) Address space of type <GEF_VME_ADDR_SPACE>.
 *    GEF_UINT32 addr_mode            - (I) Address mode.
 *    <GEF_VME_ADDR> *addr            - (O) VME address handle of type <GEF_VME_ADDR>.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_6 - The _addr_ parameter is not a valid pointer.
 *
 * See Also:
 *    <gefVmeOpen>,
 *    <gefVmeFillSlvAddr>, 
 *    <gefVmeFillMasterAddr>, 
 *    <gefVmeFillDMASrcAddr>, 
 *    <gefVmeFillDMASrcAddr>, 
 *    <gefVmeFillLMAddr>, 
 *    <gefVmeFillAddrUsingAM>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeFillVRAIAddr (GEF_VME_BUS_HDL              bus_hdl,     
                    GEF_UINT32                   addr_upper,
                    GEF_UINT32                   addr_lower,
                    GEF_VME_ADDR_SPACE           addr_space, 
                    GEF_UINT32                   addr_mode,
                    GEF_VME_ADDR                *addr);

/**
 * Function: gefVmeFillAddrUsingAM
 *
 * Description:
 *    Fill the VME address using Address modifier.
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl                      - (I) Handle allocated by <gefVmeOpen>.
 *    GEF_UINT32 addr_upper                          - (I) Upper 32 Bit VME Address
 *    GEF_UINT32 addr_lower                          - (I) Lower 32 Bit VME Address
 *    <GEF_VME_ADDR_MOD> addr_mod                    - (I) Address modifier of type <GEF_VME_ADDR_MOD>.
 *    <GEF_VME_EXTENDED_ADDR_MOD> extended_addr_mode - (I) Address space of type <GEF_VME_EXTENDED_ADDR_MOD>.
 *    <GEF_VME_2ESST_RATE> vme_2esst_rate            - (I) VME 2esst rate of type <GEF_VME_2ESST_RATE>.
 *    <GEF_VME_ADDR> *addr                           - (O) VME address handle of type <GEF_VME_ADDR>.
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_7 - The _addr_ parameter is not a valid pointer.
 *
 * See Also:
 *    <gefVmeOpen>,
 *    <gefVmeFillSlvAddr>, 
 *    <gefVmeFillMasterAddr>, 
 *    <gefVmeFillDMASrcAddr>, 
 *    <gefVmeFillDMASrcAddr>, 
 *    <gefVmeFillLMAddr>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeFillAddrUsingAM (GEF_VME_BUS_HDL            bus_hdl,     
                       GEF_UINT32                 addr_upper,
                       GEF_UINT32                 addr_lower,
                       GEF_VME_ADDR_MOD           addr_mod, 
                       GEF_VME_EXTENDED_ADDR_MOD  extended_addr_mod,
                       GEF_VME_2ESST_RATE         vme_2esst_rate,
                       GEF_VME_ADDR              *addr);

/**
 * Function: gefVmeSetDebugFlags
 *
 * Description:
 *    Set the debug flags in the library and driver.  Application 
 *    programs should not use this function unless directed to do so 
 *    by GE Intelligent Platforms Embedded Systems, Inc. support 
 *    personnel. 
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl - (I) Handle allocated by <gefVmeOpen>.
 *    GEF_UINT32 debug_flag     - (I) The debug flag(s) to set
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _debug_flag_ parameter is not a valid value.
 *
 * See Also:
 *
 */
GEF_STATUS GEF_STD_CALL 
gefVmeSetDebugFlags (GEF_VME_BUS_HDL  bus_hdl, 
                     GEF_UINT32       debug_flag);

/**
 * Function: gefVmeGetDebugFlags
 *
 * Description:
 *    Get the global debug flags in the library and driver.  Application 
 *    programs should not use this function unless directed to do so by 
 *    GE Intelligent Platforms Embedded Systems, Inc. support personnel.
 *
 * Parameters:
 *    <GEF_VME_BUS_HDL> bus_hdl - (I) Handle allocated by <gefVmeOpen>.
 *    GEF_UINT32 *debug_flag    - (O) Returns the debug flags
 *
 * Returns:
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _debug_flag_ parameter is not a valid
 *                                 pointer.
 *
 * See Also:
 *
 */
GEF_STATUS GEF_STD_CALL 
gefVmeGetDebugFlags (GEF_VME_BUS_HDL  bus_hdl, 
                     GEF_UINT32      *debug_flag);

/**
 * Function: gefVmeSetReadWriteByteSwap
 *
 * Description:  
 *    This function sets the software byte swapping performed by the 
 *    <gefVmeRead> and <gefVmeWrite> functions.  The default is 
 *    big endian.    
 *
 * Parameters:  
 *    <GEF_VME_MASTER_HDL> master_hdl - (I) Handle to <GEF_VME_MASTER_HDL>. 
 *    <GEF_ENDIAN> endian             - (I) Endianess of the data on the VME bus 
 *                                          of the type <GEF_ENDIAN>.
 *    
 *
 * Returns:  
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _master_hdl_ parameter is not a valid
 *                                 master handle returned from <gefVmeCreateMasterWindow>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _endian_ parameter is not a valid value.
 *
 * See Also:  
 *    <gefVmeOpen>,
 *    <gefVmeCreateMasterWindow>,
 *    <gefVmeGetReadWriteByteSwap>,
 *    <gefVmeRead>,
 *    <gefVmeWrite>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeSetReadWriteByteSwap (GEF_VME_MASTER_HDL  master_hdl, 
                            GEF_ENDIAN          endian);

/**
 * Function: gefVmeGetReadWriteByteSwap
 *
 * Description:  
 *    This function gets the software byte swapping setting used by the 
 *    <gefVmeRead> and <gefVmeWrite> functions.  The default is 
 *    big endian.    
 *
 * Parameters:  
 *    <GEF_VME_MASTER_HDL> master_hdl - (I) Handle to <GEF_VME_MASTER_HDL>.
 *    <GEF_ENDIAN> *endian            - (O) A pointer to the location to
 *                                          store the result of the ReadWrite 
 *                                          ByteSwap setting of the type
 *                                          <GEF_ENDIAN> which represents the 
 *                                          endianess of the data on the VME 
 *                                          bus.
 *
 * Returns:  
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _master_hdl_ parameter is not a valid
 *                                 master handle returned from <gefVmeCreateMasterWindow>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _endian_ parameter is not a valid
 *                                 pointer.
 *
 * See Also:  
 *    <gefVmeOpen>,
 *    <gefVmeCreateMasterWindow>,
 *    <gefVmeSetReadWriteByteSwap>,
 *    <gefVmeRead>,
 *    <gefVmeWrite>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeGetReadWriteByteSwap (GEF_VME_MASTER_HDL  master_hdl, 
                            GEF_ENDIAN         *endian);

/**
 * Function: gefVmeRegisterDump
 *
 * Description:  
 *    This function gets the current state of the registers on the 
 *    underlying VME Bridge device.  Application  programs should 
 *    not use this function unless directed to do so by GE 
 *    Intelligent Platforms Embedded Systems, Inc. support personnel. 
 *    
 * Parameters:  
 *    <GEF_VME_BUS_HDL> bus_hdl  - (I) Handle allocated by <gefVmeOpen>.
 *    char *buffer               - (O) Pointer to char buffer to store the output.
 *    size_t buf_size            - (I) Size of buffer.
 *    
 *
 * Returns:  
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _buffer_ parameter is not a valid
 *                                 pointer.
 *
 * See Also:  
 *    <gefVmeOpen>
 *
 */
GEF_STATUS GEF_STD_CALL
gefVmeRegisterDump (GEF_VME_BUS_HDL  bus_hdl, 
                    char            *buffer, 
                    size_t           buf_size);

/**
 * Function: gefVmeMasterWindowsDump
 *
 * Description:  
 *    This function gets the current state of the master windows 
 *    settings on the underlying VME Bridge device.
 *    
 * Parameters:  
 *    <GEF_VME_BUS_HDL> bus_hdl  - (I) Handle allocated by <gefVmeOpen>.
 *    char *buffer               - (O) Pointer to char buffer to store the output.
 *    size_t buf_size            - (I) Size of buffer.
 *    
 * Returns:  
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _buffer_ parameter is not a valid
 *                                 pointer.
 *
 * See Also:  
 *    <gefVmeOpen>
 *    <gefVmeSlaveWindowsDump>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeMasterWindowsDump(GEF_VME_BUS_HDL  bus_hdl, 
                        char            *buffer, 
                        size_t           buf_size);

/**
 * Function: gefVmeSlaveWindowsDump
 *
 * Description:  
 *    This function gets the current state of the slave windows 
 *    settings on the underlying VME Bridge device.
 *
 * Parameters:  
 *    <GEF_VME_BUS_HDL> bus_hdl     - (I) Handle allocated by <gefVmeOpen>.
 *    char *buffer                  - (O) Pointer to char buffer to store the output.
 *    size_t buf_size               - (I) Size of buffer.
 *    
 * Returns:  
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _buffer_ parameter is not a valid
 *                                 pointer.
 *
 * See Also:  
 *    <gefVmeOpen>
 *    <gefVmeMasterWindowsDump>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeSlaveWindowsDump (GEF_VME_BUS_HDL  bus_hdl, 
                        char            *buffer, 
                        size_t           buf_size);

/**
 * Function: gefVmeVersion
 *
 * Description:  
 *    This function gets the version of the VME library and driver. 
 *
 * Parameters:  
 *    <GEF_VME_BUS_HDL> bus_hdl      - (I) Handle allocated by <gefVmeOpen>.
 *    <GEF_VERSION> *drv_version     - (O) Pointer to <GEF_VERSION> to store the driver version.
 *    <GEF_VERSION> *library_version - (O) Pointer to <GEF_VERSION> to store the library version.
 *    
 *
 * Returns:  
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _drv_version_ parameter is not a valid
 *                                 pointer.
 *    GEF_STATUS_BAD_PARAMETER_3 - The _library_version_ parameter is not a valid
 *                                 pointer.
 *
 * See Also:  
 *    <gefVmeOpen>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeVersion (GEF_VME_BUS_HDL  bus_hdl, 
               GEF_VERSION     *drv_version, 
               GEF_VERSION     *library_version);

/**
 * Function: gefVmeSetMasterHardwareByteSwap
 *
 * Description:  
 *    This function sets the Master Hardware byte swap of the VME library 
 *    and driver. 
 *
 * Parameters:  
 *    <GEF_VME_BUS_HDL> bus_hdl      - (I) Handle allocated by <gefVmeOpen>.
 *    <GEF_HW_BYTESWAP> hwbyteswap   - (I) The master hardware byte swap type 
 *                                         value sent to the driver.
 *    
 *
 * Returns:  
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *
 * See Also:  
 *    <gefVmeOpen>
 *    <gefVmeGetMasterHardwareByteSwap>
 */
GEF_STATUS GEF_STD_CALL
gefVmeSetMasterHardwareByteSwap (GEF_VME_BUS_HDL bus_hdl, 
                                 GEF_HW_BYTESWAP hwbyteswap);

/**
 * Function: gefVmeGetMasterHardwareByteSwap
 *
 * Description:  
 *    This function gets the Master Hardware byte swap of the VME library 
 *    and driver. 
 *
 * Parameters:  
 *    <GEF_VME_BUS_HDL> bus_hdl    - (I) Handle allocated by <gefVmeOpen>.
 *    <GEF_HW_BYTESWAP> hwbyteswap - (O) The master hardware byte swap type 
 *                                       value returned from the driver.
 *    
 *
 * Returns:  
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _hwbyteswap_ parameter is not a valid
 *                                 pointer.
 *
 * See Also:  
 *    <gefVmeOpen>
 *    <gefVmeSetMasterHardwareByteSwap>
 */
GEF_STATUS GEF_STD_CALL
gefVmeGetMasterHardwareByteSwap (GEF_VME_BUS_HDL  bus_hdl, 
                                 GEF_HW_BYTESWAP *hwbyteswap);

/**
 * Function: gefVmeSetSlaveHardwareByteSwap
 *
 * Description:  
 *    This function sets the Slave Hardware byte swap of the VME library 
 *    and driver. 
 *
 * Parameters:  
 *    <GEF_VME_BUS_HDL> bus_hdl    - (I) Handle allocated by <gefVmeOpen>.
 *    <GEF_HW_BYTESWAP> hwbyteswap - (I) The slave hardware byte swap type 
 *                                       value sent to the driver.
 *    
 *
 * Returns:  
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *
 * See Also:  
 *    <gefVmeOpen>
 *    <gefVmeGetSlaveHardwareByteSwap>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeSetSlaveHardwareByteSwap (GEF_VME_BUS_HDL bus_hdl, 
                                GEF_HW_BYTESWAP hwbyteswap);

/**
 * Function: gefVmeGetSlaveHardwareByteSwap
 *
 * Description:  
 *    This function gets the Slave Hardware byte swap of the VME library 
 *    and driver. 
 *
 * Parameters:  
 *    <GEF_VME_BUS_HDL> bus_hdl    - (I) Handle allocated by <gefVmeOpen>.
 *    <GEF_HW_BYTESWAP> hwbyteswap - (O) The slave hardware byte swap type 
 *                                       value returned from the driver.
 *    
 *
 * Returns:  
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _hwbyteswap_ parameter is not a valid
 *                                 pointer.
 *
 * See Also:  
 *    <gefVmeOpen>
 *    <gefVmeSetSlaveHardwareByteSwap>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeGetSlaveHardwareByteSwap (GEF_VME_BUS_HDL  bus_hdl, 
                                GEF_HW_BYTESWAP *hwbyteswap);

/**
 * Function: gefVmeGetTimeOnBus
 *
 * Description:  
 *    This function gets the setting for the maximum time the VME
 * controller will stay on the bus. 
 *
 * Parameters:  
 *    <GEF_VME_BUS_HDL> bus_hdl     - (I) Handle allocated by <gefVmeOpen>.
 *    <GEF_VME_TIME_ON_BUS> time_on - (O) The maximun time the VME
 *                                        controller will stay on the bus.
 *
 * Returns:  
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _time_on_ parameter is not a valid
 *                                 pointer.
 *
 * See Also:  
 *    <gefVmeOpen>
 *    <gefVmeSetTimeOnBus>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeGetTimeOnBus (GEF_VME_BUS_HDL      bus_hdl, 
                    GEF_VME_TIME_ON_BUS *time_on);

/**
 * Function: gefVmeSetTimeOnBus
 *
 * Description:  
 *    This function sets the maximum time the VME
 * controller will stay on the bus. 
 *
 * Parameters:  
 *    <GEF_VME_BUS_HDL> bus_hdl     - (I) Handle allocated by <gefVmeOpen>.
 *    <GEF_VME_TIME_ON_BUS> time_on - (O) The maximun time the VME
 *                                        controller will stay on the bus.
 *
 * Returns:  
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _time_on_ parameter is not a valid
 *                                 value.
 *
 * See Also:  
 *    <gefVmeOpen>
 *    <gefVmeSetTimeOnBus>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeSetTimeOnBus (GEF_VME_BUS_HDL     bus_hdl, 
                    GEF_VME_TIME_ON_BUS time_on);
/**
 * Function: gefVmeGetTimeOffBus
 *
 * Description:  
 *    This function gets the setting for the time the VME
 * controller must wait before re-requesting the VMEbus.
 *
 * Parameters:  
 *    <GEF_VME_BUS_HDL> bus_hdl       - (I) Handle allocated by <gefVmeOpen>.
 *    <GEF_VME_TIME_OFF_BUS> time_off - (O) The time the VME controller must 
 *                                          wait before re-requesting the VMEbus.
 *
 * Returns:  
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *                                 vme bus handle returned from <gefVmeOpen>.
 *    GEF_STATUS_BAD_PARAMETER_2 - The _time_off_ parameter is not a valid
 *                                 pointer.
 *
 * See Also:  
 *    <gefVmeOpen>
 *    <gefVmeSetTimeOnBus>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeGetTimeOffBus (GEF_VME_BUS_HDL       bus_hdl, 
                     GEF_VME_TIME_OFF_BUS *time_off);

/**
 * Function: gefVmeSetTimeOffBus
 *
 * Description:  
 *    This function sets the time the VME
 * controller must wait before re-requesting the VMEbus.
 *
 * Parameters:  
 *    <GEF_VME_BUS_HDL> bus_hdl       - (I) Handle allocated by <gefVmeOpen>.
 *    <GEF_VME_TIME_OFF_BUS> time_off - (O) The time the VME controller must 
 *                                          wait before re-requesting the VMEbus.
 *
 * Returns:  
 *    GEF_STATUS_SUCCESS         - The function completed normally.  
 *    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
 *    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
 *    GEF_STATUS_BAD_PARAMETER_2 - The _time_off_ parameter is not a valid
 *                                 value.
 *
 * See Also:  
 *    <gefVmeOpen>
 *    <gefVmeSetTimeOnBus>
 */
GEF_STATUS GEF_STD_CALL 
gefVmeSetTimeOffBus (GEF_VME_BUS_HDL      bus_hdl, 
                     GEF_VME_TIME_OFF_BUS time_off);
/**
* Function: gefVmeGetSlotID
*
* 
* Description:  
*    This function returns the slot id of the  underlying VME Bridge device.
*    
* 
* Parameters:  
*    <GEF_VME_BUS_HDL> bus_hdl     - (I) Handle allocated by <gefVmeOpen>.
*    GEF_UINT32 *slot_id                  - (O) Pointer to an unsigned int32 to store the output.
*    
*
* Returns:  
*    GEF_STATUS_SUCCESS         - The function completed normally.  
*    GEF_STATUS_NOT_SUPPORTED   - This function is not supported in this package.
*    GEF_STATUS_BAD_PARAMETER_1 - The _bus_hdl_ parameter is not a valid
*                                 vme bus handle returned from <gefVmeOpen>.
*    GEF_STATUS_BAD_PARAMETER_2 - The _buffer_ parameter is not a valid
*                                 pointer.
*
* See Also:  
*    <gefVmeOpen>
*
*/
GEF_STATUS GEF_STD_CALL
gefVmeGetSlotID(GEF_VME_BUS_HDL bus_hdl, GEF_UINT32 *slot_id);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __GEFCMN_VME_H */

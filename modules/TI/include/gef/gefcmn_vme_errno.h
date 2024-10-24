/*
 * File:
 *    gefcmn_vme_errno.h
 *
 * Description:
 *    VME Error definitions for the common API.
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
/*
Header File include structure
Shared = Shared across OS's, otherwise OS specific.
Kernel = File that can be included by Kernel driver in addition to user library.
User   = File delivered to user for user apps to include.

      gefcmn_types.h
      (Kernel, User)
            |             
      gefcmn_errno.h      
  (Shared, Kernel, User)  
            |             
     gefcmn_vme_errno.h   
    (Shared,Kernel,User) 
*/

#ifndef __GEFCMN_VME_ERRNO_H
#define __GEFCMN_VME_ERRNO_H

#include "gef/gefcmn_errno.h"

#define GEF_VME_SET_ERROR(error) GEF_SET_ERROR(GEF_FACIL_VME, error) 

/**
 * Group: VME Facility Error Codes
 *
 * Description:
 *      This section defines the error codes that are unique to the
 *      VME facility.  Currently, this consists of the
 *      following values:
 *
 *  GEF_STATUS_VME_VRA_IMAGE_ALREADY_CREATED        - VRAI image already created
 *  GEF_STATUS_VME_MASTER_WND_NOT_EXCLUSIVE         - Master window not exclusive 
 *  GEF_STATUS_VME_NO_FREE_MASTER_WINDOW            - Master window not available
 *  GEF_STATUS_VME_NO_FREE_SLAVE_WINDOW             - Slave window not available
 *  GEF_STATUS_VME_LOCATION_MONITOR_INUSE           - Location monitor in use
 *  GEF_STATUS_VME_MASTER_WND_TRANSLATE_NOT_ALIGNED - Translate window not aligned
 *  GEF_STATUS_VME_INTERRUPT_LEVEL_BUSY             - Interrupt level busy
 *  GEF_STATUS_VME_VRA_IMAGE_NOT_CREATED            - VRAI image not created
 *  GEF_STATUS_VME_INVALID_ADDRESS_SPACE            - Invalid Address space
 *  GEF_STATUS_VME_INVALID_ADDRESS_MODE             - Invalid Address mode
 *  GEF_STATUS_VME_INVALID_SIZE                     - Invalid size
 *  GEF_STATUS_VME_INVALID_TRANSFER_WIDTH           - Invalid transfer width
 *  GEF_STATUS_VME_INVALID_TRANSFER_MODE            - Invalid transfer mode
 *  GEF_STATUS_VME_INVALID_2eSST_RATE               - Invalid 2eSST rate
 *  GEF_STATUS_VME_INVALID_BROADCAST_ID             - Invalid broadcast id
 *  GEF_STATUS_VME_INVALID_VON_VALUE                - Invalid VON value
 *  GEF_STATUS_VME_INVALID_VOFF_VALUE               - Invalid VOFF value
 *  GEF_STATUS_VME_SLAVE_REQUEST_NOT_ALIGNED        - Address and/or size alignment not compatible with H/W
 *  GEF_STATUS_VME_OFFSET_NOT_ALIGNED               - Offset not aligned with size
 *  GEF_STATUS_VME_ADDRESS_OVERFLOW                 - Address overflow
 *  GEF_STATUS_VME_SLAVE_WND_MAPPED                 - Slave Window mapped to user space
 *  GEF_STATUS_VME_DMA_BERR                         - VME Bus Error occurred during DMA.
 *  GEF_STATUS_VME_MAJOR_VER_MISMATCH               - VME library major version does not match driver major version.  
 *                                                    Check the VME driver to confirm that you have the correct version 
 *                                                    installed.  Confirm that your application is linked to the correct 
 *                                                    library version.
 */
 /**
 * Type: GEF_STATUS_VME_ENUM
 *
 * Description:
 *      Enumeration to set the error status.
 *        
 *  GEF_STATUS_VME_VRA_IMAGE_ALREADY_CREATED        - VRAI image already created
 *  GEF_STATUS_VME_MASTER_WND_NOT_EXCLUSIVE         - Master window not exclusive 
 *  GEF_STATUS_VME_NO_FREE_MASTER_WINDOW            - Master window not available
 *  GEF_STATUS_VME_NO_FREE_SLAVE_WINDOW             - Slave window not available
 *  GEF_STATUS_VME_LOCATION_MONITOR_INUSE           - Location monitor in use
 *  GEF_STATUS_VME_MASTER_WND_TRANSLATE_NOT_ALIGNED - Translate window not aligned
 *  GEF_STATUS_VME_INTERRUPT_LEVEL_BUSY             - Interrupt level busy
 *  GEF_STATUS_VME_VRA_IMAGE_NOT_CREATED            - VRAI image not created
 *  GEF_STATUS_VME_INVALID_ADDRESS_SPACE            - Invalid Address space
 *  GEF_STATUS_VME_INVALID_ADDRESS_MODE             - Invalid Address mode
 *  GEF_STATUS_VME_INVALID_SIZE                     - Invalid size
 *  GEF_STATUS_VME_INVALID_TRANSFER_WIDTH           - Invalid transfer width
 *  GEF_STATUS_VME_INVALID_TRANSFER_MODE            - Invalid transfer mode
 *  GEF_STATUS_VME_INVALID_2eSST_RATE               - Invalid 2eSST rate
 *  GEF_STATUS_VME_INVALID_BROADCAST_ID             - Invalid broadcast id
 *  GEF_STATUS_VME_INVALID_VON_VALUE                - Invalid VON value
 *  GEF_STATUS_VME_INVALID_VOFF_VALUE               - Invalid VOFF value
 *  GEF_STATUS_VME_SLAVE_REQUEST_NOT_ALIGNED        - Address and/or size alignment not compatible with H/W
 *  GEF_STATUS_VME_OFFSET_NOT_ALIGNED               - Offset not aligned with size
 *  GEF_STATUS_VME_ADDRESS_OVERFLOW                 - Address overflow
 *  GEF_STATUS_VME_SLAVE_WND_MAPPED                 - Slave Window mapped to user space
 *  GEF_STATUS_VME_DMA_BERR                         - VME Bus Error occurred during DMA.
 *  GEF_STATUS_VME_MAJOR_VER_MISMATCH               - VME library major version does not match driver major version.  
 *                                                    Check the VME driver to confirm that you have the correct version 
 *                                                    installed.  Confirm that your application is linked to the correct 
 *                                                    library version.
 *
 */
typedef enum 
{
    GEF_STATUS_VME_VRA_IMAGE_ALREADY_CREATED = GEF_STATUS_FACIL_ERROR_FIRST,
    GEF_STATUS_VME_MASTER_WND_NOT_EXCLUSIVE,
    GEF_STATUS_VME_NO_FREE_MASTER_WINDOW,
    GEF_STATUS_VME_NO_FREE_SLAVE_WINDOW,
    GEF_STATUS_VME_LOCATION_MONITOR_INUSE,
    GEF_STATUS_VME_MASTER_WND_TRANSLATE_NOT_ALIGNED,
    GEF_STATUS_VME_INTERRUPT_LEVEL_BUSY,
    GEF_STATUS_VME_VRA_IMAGE_NOT_CREATED,
    GEF_STATUS_VME_INVALID_ADDRESS_SPACE,
    GEF_STATUS_VME_INVALID_ADDRESS_MODE,
    GEF_STATUS_VME_INVALID_SIZE,
    GEF_STATUS_VME_INVALID_TRANSFER_WIDTH,
    GEF_STATUS_VME_INVALID_TRANSFER_MODE,
    GEF_STATUS_VME_INVALID_2eSST_RATE,
    GEF_STATUS_VME_INVALID_BROADCAST_ID,
    GEF_STATUS_VME_INVALID_VON_VALUE,
    GEF_STATUS_VME_INVALID_VOFF_VALUE,
    GEF_STATUS_VME_SLAVE_REQUEST_NOT_ALIGNED,
    GEF_STATUS_VME_OFFSET_NOT_ALIGNED,
    GEF_STATUS_VME_ADDRESS_OVERFLOW,
    GEF_STATUS_VME_SLAVE_WND_MAPPED,
    GEF_STATUS_VME_DMA_BERR,
    GEF_STATUS_VME_MAJOR_VER_MISMATCH,
    GEF_STATUS_VME_LAST
    
} GEF_STATUS_VME_ENUM;

#endif

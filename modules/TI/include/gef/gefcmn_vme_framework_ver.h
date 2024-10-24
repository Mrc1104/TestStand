/*
 * File:
 *    gefcmn_vme_framework_ver.h
 *
 * Description:
 *    This interface file defines the framework version for the VME facility.
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
#ifndef __GEFCMN_VME_FRAMEWORK_VER_H
#define __GEFCMN_VME_FRAMEWORK_VER_H

/* 
 * Update when API changes, INFO passing structure 
 * changes, must change if driver will not work with older library, etc. 
 */
#define GEF_VME_LIB_VER_MAJOR     3

/* 
 * Driver and Library major version shall always agree as they both use this 
 * file which defines the communication between the two.
 */
#define GEF_VME_DRV_VER_MAJOR     3

#endif /* __GEFCMN_VME_FRAMEWORK_VER_H */

/*
 *
 ****************************************************************************
 * Copyright (C) 2016 GlobalMEMS, Inc. <www.globalmems.com>
 * All rights reserved.
 *
 * File : gSensor_autoNil.h
 *
 * Date : 2016/09/26
 *
 * Usage: g-Sensor AutoNil calibration header
 *
 ****************************************************************************
 * 
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 **************************************************************************/
 
/*! @file gSensor_autoNil.h
 *  @brief  g-sensor AutoNil calibration API
 *  @author Joseph FC Tseng
 */
 
 
#ifndef __GSENSOR_AUTONIL_H__
#define __GSENSOR_AUTONIL_H__

#include "type_support.h"

//AutoNil g-sensor data reading will be averaged
#define DATA_AVE_NUM 32

enum {AUTONIL_X = 0, AUTONIL_Y = 1, AUTONIL_Z = 2, AUTONIL_POSITIVE = 0x10, AUTONIL_NEGATIVE = 0x20, AUTONIL_AUTO = 0x40};

typedef s8(*read_data_xyz_fcn_t)(raw_data_xyzt_t*);

/*!
 * @brief Auto estimate the g-sensor offset. 
 * @brief It is assumed the g-sensor is positioned statically in level when executed this function with one of the axes
 * @brief aligned along the gravity.
 *
 * @param data_fcn The data function pointer to read the g-sensor XYZ datas
 * @param dir direction the g-sensor is aligned
 *            AUTONIL_POSITIVE/AUTONIL_NEGATIVE: specify the positive/negative axis direction that is aligned with the gravity
 *            AUTONIL_AUTO: automotic identify the positive/negative axis direction that is aligned with the gravity
 *            AUTONIL_X/Y/Z: specify the axis
 *            ex: AUTONIL_AUTO + AUTONIL_Z: Z-axis is aligned with the gravity, auto sign identification
 *                AUTONIL_POSITIVE + AUTONIL_Z: postive Z-axis is algined with the gravity
 *                AUTONIL_NEGATIVE + AUTONIL_Z: negative Z-axis is algined with the gravity
 * @param outputCodePerG sensor output code per 1g gravity (the sensitivity)
 * @param poffset The estimated sensor offset
 *
 * @return 0 for Success
 * @return 1 for other errors
 * @retval -1 Bus communication error
 * @retval -127 Error null bus
 */
s8 gSensorAutoNil(read_data_xyz_fcn_t data_fcn, u8 dir, s32 outputCodePerG, raw_data_xyzt_t* poffset);
 
#endif //__GSENSOR_AUTONIL_H__

 

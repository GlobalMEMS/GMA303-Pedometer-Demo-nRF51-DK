/*
 *
 ****************************************************************************
 * Copyright (C) 2016 GlobalMEMS, Inc. <www.globalmems.com>
 * All rights reserved.
 *
 * File : gSensor_autoNil.c
 *
 * Date : 2016/09/26
 *
 * Usage: g-Sensor AutoNil calibration
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

#include <stddef.h>
#include "gSensor_autoNil.h"

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
s8 gSensorAutoNil(read_data_xyz_fcn_t data_fcn, u8 dir, s32 outputCodePerG, raw_data_xyzt_t* poffset){
	
  s8 i, j, comRslt = -1;
  u8 index = dir & 0x03; //index to the XYZ axis
  s32 gCode;
  float v[] = {0.0, 0.0, 0.0};
	
  //make sure the function point to somewhere
  if(data_fcn == NULL){
    comRslt = 1;
    goto EXIT;
  }
	
  //get the gSensor readings
  for(i = 0; i < DATA_AVE_NUM; ++i){
			
    comRslt = data_fcn(poffset);
    if(comRslt < 0)
      goto EXIT;
		
    //accumulate the readout
    for(j = 0; j < 3; ++j)
      v[j] += poffset->v[j];
  }
	
  //Return 0 for success
  comRslt = 0;
	
  //The average
  for(i = 0; i < 3; ++i){
    v[i] = v[i] / DATA_AVE_NUM;
    poffset->v[i] = (v[i] < 0)?(s32)(v[i] - 0.5):(s32)(v[i] + 0.5);
  }
	
  //Check the directionality
  if(dir & AUTONIL_POSITIVE) //Positive axis toward the gravity, the reading is negative
    gCode = - outputCodePerG;
  else if( (dir & AUTONIL_AUTO) && poffset->v[index] < 0)
    gCode = - outputCodePerG;
  else
    gCode = outputCodePerG;
	
  poffset->v[index] -= gCode;
	
 EXIT:
  return comRslt;
}

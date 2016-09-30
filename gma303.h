/*
 *
 ****************************************************************************
 * Copyright (C) 2016 GlobalMEMS, Inc. <www.globalmems.com>
 * All rights reserved.
 *
 * File : gma303.h
 *
 * Date : 2016/09/26
 *
 * Usage: Sensor Driver file for GMA303 sensor
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

/*! @file gma303.h
 *  @brief  GMA303 Sensor Driver Header File 
 *  @author Joseph FC Tseng
 */
 
#ifndef __GMA303_H_
#define __GMA303_H_

#include "bus_support.h"

#define GMA303_7BIT_I2C_ADDR		0x18
#define MAX_MOTION_THRESHOLD            0x1F
#define GMA303_RAW_DATA_SENSITIVITY     512  //raw data 512 code/g

#define GMA1302_REG_PID 	        0x00
#define GMA1302_REG_PD 		        0x01
#define GMA1302_REG_ACTR 	        0x02
#define GMA1302_REG_MTHR 	        0x03
#define GMA1302_REG_STADR 	        0x04
#define GMA1302_REG_STATUS 	        0x05
#define GMA1302_REG_DX	 	        0x06
#define GMA1302_REG_INTCR 	        0x15
#define GMA1302_REG_CONTR1 	        0x16
#define GMA1302_REG_CONTR2 	        0x17
#define GMA1302_REG_CONTR3 	        0x18
#define GMA1302_REG_OSM	 	        0x38

/* PID */
#define GMA303_PID__REG         GMA1302_REG_PID
/* PD */
#define GMA303_PD__REG          GMA1302_REG_PD
/* Soft Rest bit */
#define GMA303_RST__REG		GMA1302_REG_PD
#define GMA303_RST__MSK		0x02
#define GMA303_RST__POS		1
/* PD LDO bit */
#define GMA303_PD_LDO__REG	GMA1302_REG_PD
#define GMA303_PD_LDO__MSK	0x01
#define GMA303_PD_LDO__POS	0
/* PD BG bit */
#define GMA303_PD_BG__REG	GMA1302_REG_PD
#define GMA303_PD_BG__MSK	0x04
#define GMA303_PD_BG__POS	2
/* ACTR */
#define GMA303_ACTR__REG	GMA1302_REG_ACTR
/* STADR */
#define GMA303_STADR__REG	GMA1302_REG_STADR
/* DRDY bit */
#define GMA303_DRDY__REG	GMA1302_REG_STATUS
#define GMA303_DRDY__MSK	0x01
#define GMA303_DRDY__POS	0
/* Low-pass filter, Continuous Mode, bit */
#define GMA303_LP_CM__REG       GMA1302_REG_CONTR1
#define GMA303_LP_CM__MSK       0x01
#define GMA303_LP_CM__POS       0
/* Low-pass filter, Non-Continuous Mode, bit */
#define GMA303_LP_NCM__REG      GMA1302_REG_CONTR1
#define GMA303_LP_NCM__MSK      0x08
#define GMA303_LP_NCM__POS      3
/* High-pass filter, Continuous Mode, bit */
#define GMA303_HP_CM__REG       GMA1302_REG_CONTR1
#define GMA303_HP_CM__MSK       0x02
#define GMA303_HP_CM__POS       1
/* High-pass filter, Non-Continuous Mode, bit */
#define GMA303_HP_NCM__REG      GMA1302_REG_CONTR1
#define GMA303_HP_NCM__MSK      0x10
#define GMA303_HP_NCM__POS      4
/* Data ready interrupt, Continuous Mode, bit */
#define GMA303_DRDY_CM__REG     GMA1302_REG_INTCR
#define GMA303_DRDY_CM__MSK     0x02
#define GMA303_DRDY_CM__POS     1
/* Data ready interrupt, Non-Continuous Mode, bit */
#define GMA303_DRDY_NCM__REG    GMA1302_REG_INTCR
#define GMA303_DRDY_NCM__MSK    0x20
#define GMA303_DRDY_NCM__POS    5
/* Motion interrupt, Continuous Mode, bit */
#define GMA303_MOTION_CM__REG   GMA1302_REG_INTCR
#define GMA303_MOTION_CM__MSK   0x04
#define GMA303_MOTION_CM__POS   2
/* Motion interrupt, Non-Continuous Mode, bit */
#define GMA303_MOTION_NCM__REG  GMA1302_REG_INTCR
#define GMA303_MOTION_NCM__MSK  0x40
#define GMA303_MOTION_NCM__POS  6
/* INT pin type, Continuous Mode, bit */
#define GMA303_INT_PIN_TYPE_CM__REG     GMA1302_REG_INTCR
#define GMA303_INT_PIN_TYPE_CM__MSK     0x01
#define GMA303_INT_PIN_TYPE_CM__POS     0
/* INT pin type, Non-Continuous Mode, bit */
#define GMA303_INT_PIN_TYPE_NCM__REG    GMA1302_REG_INTCR
#define GMA303_INT_PIN_TYPE_NCM__MSK    0x10
#define GMA303_INT_PIN_TYPE_NCM__POS    4
/* INT pin polarity bit */
#define GMA303_INT_PIN_POLARITY__REG    GMA1302_REG_INTCR
#define GMA303_INT_PIN_POLARITY__MSK    0x08
#define GMA303_INT_PIN_POLARITY__POS    3
/* NCM ODR */
#define GMA303_NCM_ODR__REG     GMA1302_REG_CONTR2
#define GMA303_NCM_ODR__MSK     0x0C
#define GMA303_NCM_ODR__POS     2
/* OSM */
#define GMA303_OSM__REG         GMA1302_REG_OSM
#define GMA303_OSM__MSK         0xC0
#define GMA303_OSM__POS         6

typedef enum {GMA303_LP, GMA303_HP} GMA303_FILTER_T;
typedef enum {GMA303_INT_DATA, GMA303_INT_MOTION} GMA303_INTERRUPT_T;
typedef enum {GMA303_INT_PIN_PP = 0x00, GMA303_INT_PIN_OD = 0x01, GMA303_INT_PIN_AL = 0x00, GMA303_INT_PIN_AH = 0x02} GMA303_INT_PIN_CFG_T;
typedef enum {GMA303_OP_MODE_STANDBY, GMA303_OP_MODE_SUSPEND, GMA303_OP_MODE_CM, GMA303_OP_MODE_NCM} GMA303_OP_MODE_T;
typedef enum {GMA303_ODR_NCM_1, GMA303_ODR_NCM_2, GMA303_ODR_NCM_4, GMA303_ODR_NCM_8, GMA303_ODR_NA} GMA303_ODR_T;
typedef enum {GMA303_OSM_64, GMA303_OSM_32, GMA303_OSM_16} GMA303_OSM_T;

#define GMA303_GET_BITSLICE(regvar, bitname)	\
  ((regvar & bitname##__MSK) >> bitname##__POS)

#define GMA303_SET_BITSLICE(regvar, bitname, val)			\
  ((regvar & ~bitname##__MSK) | ((val<<bitname##__POS)&bitname##__MSK))


/*!
 * @brief Read multiple data from the starting regsiter address
 *
 * @param u8Addr Starting register address
 * @param pu8Data The data array of values read
 * @param u8Len Number of bytes to read
 * 
 * @return Result from the burst read function
 * @retval >= 0 Success, number of bytes read
 * @retval -127 Error null bus
 * @retval -1   Bus communication error
 *
 */
s8 gma303_burst_read(u8 u8Addr, u8* pu8Data, u8 u8Len);

/*!
 * @brief Write multiple data to the starting regsiter address
 *
 * @param u8Addr Starting register address
 * @param pu8Data The data array of values to write
 * @param u8Len Number of bytes to write
 * 
 * @return Result from the burst write function
 * @retval >= 0 Success, number of bytes write
 * @retval -127 Error null bus
 * @retval -1   Communication error
 *
 */
s8 gma303_burst_write(u8 u8Addr, u8* pu8Data, u8 u8Len);


/*!
 * @brief GMA303 initialize communication bus
 *
 * @param pbus Pointer to the I2C/SPI read/write bus support struct
 * 
 * @return Result from bus communication function
 * @retval 0 Success
 * @retval -1 Bus communication error
 * @retval -127 Error null bus
 *
 */
s8 gma303_bus_init(bus_support_t* pbus);

/*!
 * @brief GMA303 soft reset
 *
 * @param None
 * 
 * @return Result from bus communication function
 * @retval -1 Bus communication error
 * @retval -127 Error null bus
 *
 */
s8 gma303_soft_reset(void);

/*!
 * @brief GMA303 set operation mode.
 *
 * @param opMode: operation mode
 * @param odr: output data rate
 * 
 * @return Result from bus communication function
 * @retval -1 Bus communication error
 * @retval -127 Error null bus
 *
 */
s8 gma303_set_operation_mode(GMA303_OP_MODE_T opMode, GMA303_ODR_T odr);

/*!
 * @brief GMA303 set motion threshold
 *
 * @param threshold: motion threshold, 1 threshold code = 0.25g, max 0x1F (31)
 * 
 * @return Result from bus communication function
 * @retval -1 Bus communication error
 * @retval -127 Error null bus
 *
 */
s8 gma303_set_motion_threshold(u8 threshold);

/*!
 * @brief GMA303 set oversampling ratio
 *
 * @param ratio: oversampling ratio to set
 * 
 * @return Result from bus communication function
 * @retval -1 Bus communication error
 * @retval -127 Error null bus
 *
 */
s8 gma303_set_osm(GMA303_OSM_T ratio);

/*!
 * @brief GMA303 initialization
 *        1. Soft reset
 *        2. Turn on offset temperature compensation
 *        3. Set to continuous mode
 *        4. Turn on low pass filter
 *
 * @param None
 * 
 * @return Result from bus communication function
 * @retval -1 Bus communication error
 * @retval -127 Error null bus
 *
 */
s8 gma303_initialization(void);

/*!
 * @brief GMA303 read data XYZ
 *
 * @param pxyzt Data buffer to store the values
 * 
 * @return Result from bus communication function
 * @retval -1 Bus communication error
 * @retval -127 Error null bus
 *
 */
s8 gma303_read_data_xyz(raw_data_xyzt_t* pxyzt);

/*!
 * @brief GMA303 read data XYZT
 *
 * @param pxyzt Data buffer to store the values
 * 
 * @return Result from bus communication function
 * @retval -1 Bus communication error
 * @retval -127 Error null bus
 *
 */
s8 gma303_read_data_xyzt(raw_data_xyzt_t* pxyzt);

/*!
 * @brief Set GMA303 filter
 *
 * @param filter: GMA303_LP for low pass filter
 *                GMA303_HP for high pass filter
 * @param turnOn: 1 to turn on
 *                0 to turn off
 *                When turn on low-pass filter, high-pass filter will be turn off automatically.
 *                Likewise when high-pass is turned on, low-pass filter will be turned off automatically.
 * 
 * @return Result from bus communication function
 * @retval -1 Bus communication error
 * @retval -127 Error null bus
 *
 */
s8 gma303_set_filter(GMA303_FILTER_T filter, u8 turnOn);

/*!
 * @brief Set GMA303 interrupt
 *
 * @param interrupt: GMA303_INT_DATA for data ready interrupt
 *                   GMA303_INT_MOTION for motion interrupt
 * @param turnOn: 1 to turn on
 *                0 to turn off
 * 
 * @return Result from bus communication function
 * @retval -1 Bus communication error
 * @retval -127 Error null bus
 *
 */
s8 gma303_set_interrupt(GMA303_INTERRUPT_T interrupt, u8 turnOn);

/*!
 * @brief Configure GMA303 interrupt pin configuration
 *
 * @param cfg: cfg[0]: 1'b0=>push-pull, 1'b1=>open-drain
 *             cfg[1]: 1'b0=>active low, 1'b1=>active high        
 * 
 * @return Result from bus communication function
 * @retval -1 Bus communication error
 * @retval -127 Error null bus
 *
 */
s8 gma303_config_INT_pin(u8 cfg);


#endif // __GMA303_H__

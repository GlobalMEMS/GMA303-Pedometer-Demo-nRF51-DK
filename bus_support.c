/*
 *
 ****************************************************************************
 * Copyright (C) 2016 GlobalMEMS, Inc. <www.globalmems.com>
 * All rights reserved.
 *
 * File : bus_support.c
 *
 * Date : 2016/09/20
 *
 * Usage: I2C/SPI bus read/write support file
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
 
/*!
 *  @file bus_support.c
 *  @brief I2C/SPI bus read write support 
 *  @author Joseph FC Tseng
 */
 
#include "bus_support.h"
#include "m_app_twi.h"
 
/*!
 * @brief Intialize to I2C bus. 
 * @brief Implementation dependent. Replace actual I2C function here.  
 *
 * @param pbus Pointer to the bus support type. Will be assigned the actual I2C R/W function and slave address
 * @param p_app_twi Pointer to the nRF51 TWI bus the the device sit on
 * @param u8DevAddr 7-bit I2C slave address of the device
 *
 * @return Always return 0
 */
s8 bus_init_I2C(bus_support_t* pbus, app_twi_t* p_app_twi, u8 u8DevAddr){
	 
  pbus->p_app_twi = p_app_twi;
  pbus->u8DevAddr = u8DevAddr;
  pbus->bus_read = app_twi_perform_multi_read; 
  pbus->bus_write = app_twi_perform_multi_write;
  return 0;

}

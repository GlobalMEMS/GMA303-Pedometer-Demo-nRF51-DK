

#ifndef __M_APP_TWI_H__
#define __M_APP_TWI_H__

#include "app_twi.h"

#define MAX_MULTI_DEVICE_NUM 5

void app_twi_schedule_multi_device_multi_read(app_twi_t *p_app_twi,
					      uint8_t ui8MultiDeviceI2cBase[],
					      uint8_t ui8MultiDeviceSlaveAddr[],
					      uint8_t ui8MultiDeviceRegStartAddr[],
					      uint8_t ui8MultiDeviceByteToRead[],
					      uint8_t ui8MultiDeviceNum,
					      uint8_t m_buffer[],
					      app_twi_callback_t cb_fcn,
					      void* p_user_data);

void app_twi_schedule_multi_read(app_twi_t *p_app_twi,
				 uint8_t dev_addr,
				 uint8_t reg_addr,
				 uint8_t m_buffer[],
				 uint8_t data_len,
				 app_twi_callback_t cb_fcn,
				 void* p_user_data);

void app_twi_schedule_multi_write(app_twi_t *p_app_twi,
				  uint8_t dev_addr,
				  uint8_t reg_addr,
				 uint8_t m_buffer[],
				  uint8_t data_len,
				  app_twi_callback_t cb_fcn,
				  void* p_user_data);

ret_code_t app_twi_perform_single_read(app_twi_t *p_app_twi,
				       uint8_t dev_addr,
				       uint8_t reg_addr,
				       uint8_t *p_reg_value);

ret_code_t app_twi_perform_multi_read(app_twi_t *p_app_twi,
				      uint8_t dev_addr,
				      uint8_t reg_addr,
				      uint8_t reg_values[],
				      uint8_t data_len);

ret_code_t app_twi_perform_single_write(app_twi_t *p_app_twi,
					uint8_t dev_addr,
					uint8_t reg_addr,
					uint8_t reg_value);

ret_code_t app_twi_perform_multi_write(app_twi_t *p_app_twi,
				       uint8_t dev_addr,
				       uint8_t reg_addr,
				       uint8_t reg_values[],
				       uint8_t data_len);


#endif //__M_APP_TWI_H__

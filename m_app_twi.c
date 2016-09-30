
#include "m_app_twi.h"
#include "app_error.h"

//Multi-device I2C multi read
//Schedule I2C multi read
void app_twi_schedule_multi_device_multi_read(app_twi_t *p_app_twi,
					      uint8_t ui8MultiDeviceI2cBase[],
					      uint8_t ui8MultiDeviceSlaveAddr[],
					      uint8_t ui8MultiDeviceRegStartAddr[],
					      uint8_t ui8MultiDeviceByteToRead[],
					      uint8_t ui8MultiDeviceNum,
					      uint8_t m_buffer[],
					      app_twi_callback_t cb_fcn,
					      void* p_user_data)
{

  // [these structures have to be "static" - they cannot be placed on stack
  //  since the transaction is scheduled and these structures most likely
  //  will be referred after this function returns]
  static app_twi_transfer_t transfers[2*MAX_MULTI_DEVICE_NUM];
  static app_twi_transaction_t transaction;
  uint8_t total;

  total = 0;
  for(int i = 0; i < ui8MultiDeviceNum; ++i){

    int j = 2*i;

    //transfer[j]: write register address
    transfers[j].operation = APP_TWI_WRITE_OP(ui8MultiDeviceSlaveAddr[i]);
    transfers[j].p_data = &ui8MultiDeviceRegStartAddr[i];
    transfers[j].length = 1;
    transfers[j].flags = APP_TWI_NO_STOP;

    //transfer[j+1]: read register values
    transfers[j+1].operation = APP_TWI_READ_OP(ui8MultiDeviceSlaveAddr[i]);
    transfers[j+1].p_data = &m_buffer[total];
    transfers[j+1].length = ui8MultiDeviceByteToRead[i];
    transfers[j+1].flags = 0;

    total += ui8MultiDeviceByteToRead[i];
  }

  //transaction
  transaction.callback = cb_fcn;
  transaction.p_user_data = p_user_data;
  transaction.p_transfers = transfers;
  transaction.number_of_transfers = 2*ui8MultiDeviceNum;

  APP_ERROR_CHECK(app_twi_schedule(p_app_twi, &transaction));

}

//Schedule I2C multi read
void app_twi_schedule_multi_read(app_twi_t *p_app_twi,
				 uint8_t dev_addr,
				 uint8_t reg_addr,
				 uint8_t m_buffer[],
				 uint8_t data_len,
				 app_twi_callback_t cb_fcn,
				 void* p_user_data)
{
  // [these structures have to be "static" - they cannot be placed on stack
  //  since the transaction is scheduled and these structures most likely
  //  will be referred after this function returns]
  static app_twi_transfer_t transfers[2];
  static app_twi_transaction_t transaction;
  static uint8_t staticRegAddr;

  staticRegAddr = reg_addr;

  //transfer[0]: write register address
  transfers[0].operation = APP_TWI_WRITE_OP(dev_addr);
  transfers[0].p_data = &staticRegAddr;
  transfers[0].length = 1;
  transfers[0].flags = APP_TWI_NO_STOP;

  //transfer[1]: read register values
  transfers[1].operation = APP_TWI_READ_OP(dev_addr);
  transfers[1].p_data = m_buffer;
  transfers[1].length = data_len;
  transfers[1].flags = 0;

  //transaction
  transaction.callback = cb_fcn;
  transaction.p_user_data = p_user_data;
  transaction.p_transfers = transfers;
  transaction.number_of_transfers = sizeof(transfers)/sizeof(transfers[0]);

  APP_ERROR_CHECK(app_twi_schedule(p_app_twi, &transaction));
}

//Schedule I2C multi write
void app_twi_schedule_multi_write(app_twi_t *p_app_twi,
				  uint8_t dev_addr,
				  uint8_t reg_addr,
				  uint8_t m_buffer[],
				  uint8_t data_len,
				  app_twi_callback_t cb_fcn,
				  void* p_user_data)
{
  // [these structures have to be "static" - they cannot be placed on stack
  //  since the transaction is scheduled and these structures most likely
  //  will be referred after this function returns]
  static app_twi_transfer_t transfers[2];
  static app_twi_transaction_t transaction;
  static uint8_t staticRegAddr;

  staticRegAddr = reg_addr;

  //transfer[0]: write register address
  transfers[0].operation = APP_TWI_WRITE_OP(dev_addr);
  transfers[0].p_data = &staticRegAddr;
  transfers[0].length = 1;
  transfers[0].flags = APP_TWI_NO_STOP;

  //transfer[1]: write register values
  transfers[1].operation = APP_TWI_WRITE_OP(dev_addr);
  transfers[1].p_data = m_buffer;
  transfers[1].length = data_len;
  transfers[1].flags = 0;

  //transaction
  transaction.callback = cb_fcn;
  transaction.p_user_data = p_user_data;
  transaction.p_transfers = transfers;
  transaction.number_of_transfers = sizeof(transfers)/sizeof(transfers[0]);

  APP_ERROR_CHECK(app_twi_schedule(p_app_twi, &transaction));
}

//Perform I2C single read
ret_code_t app_twi_perform_single_read(app_twi_t *p_app_twi,
					uint8_t dev_addr,
					uint8_t reg_addr,
					uint8_t *p_reg_value)
{

  app_twi_transfer_t transfers[] =
    {
      APP_TWI_WRITE(dev_addr, 
		    &reg_addr, 
		    1,
		    APP_TWI_NO_STOP),
      APP_TWI_READ(dev_addr,
		   p_reg_value,
		   1,
		   0)
    };

  return app_twi_perform(p_app_twi,
			 transfers,
			 sizeof(transfers)/sizeof(transfers[0]),
			 NULL);
}

//Perform I2C multi read
ret_code_t app_twi_perform_multi_read(app_twi_t *p_app_twi,
				      uint8_t dev_addr,
				      uint8_t reg_addr,
				      uint8_t reg_values[],
				      uint8_t data_len)
{

  app_twi_transfer_t transfers[] =
    {
      APP_TWI_WRITE(dev_addr, 
		    &reg_addr, 
		    1,
		    APP_TWI_NO_STOP),
      APP_TWI_READ(dev_addr,
		   reg_values,
		   data_len,
		   0)
    };

  return app_twi_perform(p_app_twi,
			 transfers,
			 sizeof(transfers)/sizeof(transfers[0]),
			 NULL);
}

//Perform I2C single write
ret_code_t app_twi_perform_single_write(app_twi_t *p_app_twi,
					uint8_t dev_addr,
					uint8_t reg_addr,
					uint8_t reg_value)
{

  app_twi_transfer_t transfers[] =
    {

      APP_TWI_WRITE(dev_addr, 
		    &reg_addr, 
		    1,
		    APP_TWI_NO_STOP),
      APP_TWI_WRITE(dev_addr, 
		    &reg_value, 
		    1,
		    0)
    };

  return app_twi_perform(p_app_twi,
			 transfers,
			 sizeof(transfers)/sizeof(transfers[0]),
			 NULL);
}

//Perform I2C multi write
ret_code_t app_twi_perform_multi_write(app_twi_t *p_app_twi,
				       uint8_t dev_addr,
				       uint8_t reg_addr,
				       uint8_t reg_values[],
				       uint8_t data_len)
{

  app_twi_transfer_t transfers[] =
    {
      APP_TWI_WRITE(dev_addr, 
		    &reg_addr, 
		    1,
		    APP_TWI_NO_STOP),
      APP_TWI_WRITE(dev_addr, 
		    reg_values, 
		    data_len,
		    0)
    };

  return app_twi_perform(p_app_twi,
			 transfers,
			 sizeof(transfers)/sizeof(transfers[0]),
			 NULL);
}

#ifndef AS7265X_h
#define AS7265X_h

#include "Arduino.h"
#include <Wire.h>

#define AS72651_DEVICE_TYPE         0x00
#define AS72651_HW_VERSION          0x01
#define AS72651_FW_VERSION_H        0x02
#define AS72651_FW_VERSION_L        0x03
#define AS72651_CONTROL_SETUP       0x04
#define AS72651_INT_TIME            0x05
#define AS72651_DEV_TEMP            0x06
#define AS72651_LED_CONFIG          0x07

#define AS72651_RAW_VALUE_0_H       0x08    // selection depends on register value of DEV_SEL
#define AS72651_RAW_VALUE_0_L       0x09
#define AS72651_RAW_VALUE_1_H       0x0A    
#define AS72651_RAW_VALUE_1_L       0x0B
#define AS72651_RAW_VALUE_2_H       0x0C    
#define AS72651_RAW_VALUE_2_L       0x0D
#define AS72651_RAW_VALUE_3_H       0x0E    
#define AS72651_RAW_VALUE_3_L       0x0F
#define AS72651_RAW_VALUE_4_H       0x10    
#define AS72651_RAW_VALUE_4_L       0x11
#define AS72651_RAW_VALUE_5_H       0x12    
#define AS72651_RAW_VALUE_5_L       0x13

#define AS72651_I2C_CAL_SELECT      0x3F

//I2C_CAL_SELECT == 0x00
#define AS72651_CAL_CHAN0_0         0x14
#define AS72651_CAL_CHAN0_1         0x15
#define AS72651_CAL_CHAN0_2         0x16
#define AS72651_CAL_CHAN0_3         0x17

#define AS72651_CAL_CHAN1_0         0x18
#define AS72651_CAL_CHAN1_1         0x19
#define AS72651_CAL_CHAN1_2         0x1A
#define AS72651_CAL_CHAN1_3         0x1B

#define AS72651_CAL_CHAN2_0         0x1C
#define AS72651_CAL_CHAN2_1         0x1D
#define AS72651_CAL_CHAN2_2         0x1E
#define AS72651_CAL_CHAN2_3         0x1F

#define AS72651_CAL_CHAN3_0         0x20
#define AS72651_CAL_CHAN3_1         0x21
#define AS72651_CAL_CHAN3_2         0x22
#define AS72651_CAL_CHAN3_3         0x23

#define AS72651_CAL_CHAN4_0         0x24
#define AS72651_CAL_CHAN4_1         0x25
#define AS72651_CAL_CHAN4_2         0x26
#define AS72651_CAL_CHAN4_3         0x27

#define AS72651_CAL_CHAN5_0         0x28
#define AS72651_CAL_CHAN5_1         0x29
#define AS72651_CAL_CHAN5_2         0x2A
#define AS72651_CAL_CHAN5_3         0x2B

#define AS72651_FW_CNTRL            0x48
#define AS72651_FW_BYTE_COUNT_H     0x49
#define AS72651_FW_BYTE_COUNT_L     0x4A
#define AS72651_DEV_SEL             0x4F

#define AS72651_COEF_DATA_0         0x50
#define AS72651_COEF_DATA_1         0x51
#define AS72651_COEF_DATA_2         0x52
#define AS72651_COEF_DATA_3         0x53
#define AS72651_COEF_READ           0x54
#define AS72651_COEF_WRITE          0x55

#define AS72651_FW_UPDATE_CONTROL   0x60
#define AS72651_FWBC_HIGH           0x61
#define AS72651_FWBC_LOW            0x62
#define AS72651_FW_LOAD             0x63

#define I2C_AS72XX_SLAVE_STATUS_REG 0x00
#define I2C_AS72XX_SLAVE_WRITE_REG  0x01
#define I2C_AS72XX_SLAVE_READ_REG   0x02
#define I2C_AS72XX_SLAVE_TX_VALID   0x02
#define I2C_AS72XX_SLAVE_RX_VALID   0x01

#define AS72651_ADDRESS             0x49

#define led_drv_12_5_mA  0x00
#define led_drv_25_mA    0x01
#define led_drv_50_mA    0x02
#define led_drv_100_mA   0x03

#define led_ind_1_mA     0x00
#define led_ind_2_mA     0x01
#define led_ind_4_mA     0x02
#define led_ind_8_mA     0x03

#define gain_1x          0x00
#define gain_4x          0x01
#define gain_16x         0x02
#define gain_64x         0x03

#define mode0            0x00 // Mode 0: S, U, V, T, I, H, K, G, C, B, E, A
#define mode1            0x01 // Mode 1: W, U, R, T, L, H, J, G, F, B, D, A
#define mode2            0x02 // default, all 18 channels
#define mode3            0x03 // one shotoperation of mode 2


class AS7265X
{
  public: 
  AS7265X(uint8_t intPin);
  void init(uint8_t gain, uint8_t mode, uint8_t intTime);
  uint8_t getDevType();
  uint8_t getHWVersion();
  uint16_t getFWMajorVersion();
  uint16_t getFWPatchVersion();
  uint16_t getFWBuildVersion();
  uint8_t getStatus();
  float getTemperature(uint8_t devNum);
  void configureLed(uint8_t ledIndCurrent, uint8_t ledDrvCurrent, uint8_t devNum);
  void enableIndLed(uint8_t devNum);
  void enableDrvLed(uint8_t devNum);
  void disableIndLed(uint8_t devNum);
  void disableDrvLed(uint8_t devNum);
  void readCalData(float * destination);
  void readRawData(int16_t * destination);
  void I2Cscan();
  void i2cm_AS72xx_write(uint8_t virtualReg, uint8_t d);
  uint8_t i2cm_AS72xx_read(uint8_t virtualReg);
  void writeByte(uint8_t address, uint8_t subAddress, uint8_t data);
  uint8_t readByte(uint8_t address, uint8_t subAddress);

  private:
  uint8_t _intPin;
};

#endif

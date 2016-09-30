nRF51-DK + GMA303 Pedometer Demo
================================

Requirements
-----------
- nRF51-DK
- nRF51 SDK: tested with Version 10.0.0
- GCC ARM embedded compiler: tested with gcc-arm-none-eabi-4_9-2015q1-20150306
- GMA303

I2C Connections
---------------
- Use I2C0
  - SCL: P0.07
  - SDA: P0.30
- I2C 7-bit slave address: 0x18

Makefile
--------
- Modify the location of the SDK to your actual directory
```
#
# The base directory for nRF51 SDK
#
nRF51_SDK_ROOT := /C/Data/nRF51_SDK/V10_0_0
```

- Modify the location of the GNU tools to your actual directory
```
GNU_INSTALL_ROOT := C:/Program Files (x86)/GNU Tools ARM Embedded/4.9 2015q1
```

- Execute `make all` to build and flash the program

- Exectute `make help` for available targets

Default gma303_initialization function in gma303.c
--------------------------------------------------
Default initialization steps:
 * Turn on offset temperature compensation
 * Set to continuous mode
 * Turn on low pass filter
 * Set data ready INT, ative high, push-pull

You may change the behavior of this initialization function to suit your purpose. Please refer to datasheet for more details on the register settings.

Usage of AutoNil
----------------
 * The program will do an offset AutoNil when executed. Hold the g-sensor steady and maintain in level, then press 'y' after the program prompt for input.
 * You may change the `DATA_AVE_NUM` macro in the gSensor_autoNil.h for the moving averae order for the offset estimation. Defautl is 32.

MSIG Pedometer
--------------
 * The pedometer demo library is adapted from [MEMS & Sensor Industry Group open source project](https://github.com/memsindustrygroup/Matlab-Open-Source-Pedometer-Algorithm).
 * Algorithm in brief:
   - The acceleration feeded to the algorithm should be reported in g
   - Increase step counts (walkStruct.HLI) when max of the X/Y/Z datas increasingly cross the LI thershold (walkStruct.LIthrW or walkStruct.LIthrA).
   - It will search for the peak when the cross occurs.
   - The time between peaks is checked againt walkStruct.timeThr (default 250ms). If the time is too short, then the counted step will be rewinded.
   - It will classify the peak by the HI threshold (walkStruct.HIthW or walkStruct.HIthA). It will store the counts to walkStruct.HIt/HIcnt when it is larger than HI, and to walkStruct.LIt/LIcnt if otherwise.

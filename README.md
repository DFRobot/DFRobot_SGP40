# DFRobot_SGP40
- [中文版](./README_CN.md)

The SGP40 Air Quality sensor adopts the new SGP40 digital VOC sensor chip launched by the well-known Sensirion. Based on the Sensirion’s CMOSens® technology, the SGP40 offers a complete sensor system on a single chip, a temperature-controlled micro-hotplate and a humidity-compensated indoor air quality signal. In combination with Sensirion’s powerful VOC algorithm, the sensor signal can be directly used to evaluate indoor air quality. It features low power(2.6mA), and fast response(2s). The data from the sensor can be directly used to evaluate air quality without calibration.

![](./resources/images/SEN0392.png)

## Product links.
[Fermion Version](https://www.dfrobot.com/product-2241.html) 
    SKU：SEN0392
    [Product wiki.](https://wiki.dfrobot.com/SGP40_Air_Quality_Sensor_SKU_SEN0392)
[Gravity Version](https://www.dfrobot.com/product-2251.html)
    SKU:SEN0394 
    [Product wiki.](https://wiki.dfrobot.com/Gravity_SGP40_Air_Quality_Sensor_SKU_SEN0394)
    
   



## DFRobot_SGP40 Library for Arduino

An Arduino library for the SGP40 module.

## Table of Contents

* [Summary](#summary)
* [Feature](#feature)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)
<snippet>
<content>

## Summary
VOC index can be read through SGP40's I2C interface. The data will be printed through a serial port.

## Feature

1.  Set ambient temperature and humidity for accurate calibration. Relative humidity unit: %RH, range: 0-100; Temperature unit: °C, range: -10~50
2.  Read VOC index , range 0-500

## Installation

To install this library open the library manager, search for DFrobot SGP40, and install it.

## Methods

```C++
  /**
   * @brief  Initialization function
   * @return return true succeed ;return false failed.
   */
  bool begin(uint32_t duration = 10000);
  
  /**
   * @brief  Set the temperature and humidity
   * @param  relativeHumidityRH  Current environmental relative humidity value, range 0-100, unit: %RH
   * @param  temperatureC  Current ambient temperature, range -10~50, unit: °C
   */
  void setRhT(float relativeHumidity = 50,float temperatureC=25);
  
  /**
   * @brief  Measure VOC index after humidity compensation
   * @note   VOC index can indicate the quality of the air directly. The larger the value, the worse the air quality.
   * @note       0-100，no need to ventilate, purify
   * @note       100-200，no need to ventilate, purify
   * @note       200-400，ventilate, purify
   * @note       400-500，ventilate, purify intensely
   * @return The VOC index measured, ranged from 0 to 500
   */
  uint16_t getVoclndex(void);

```


## Compatibility

MCU                | Works OK | Didn't Work  | Untested  | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino Uno |       ✅      |             |            | 
FireBeetle ESP32 |       ✅         |             |            | 
FireBeetle ESP8266 |       ✅         |             |            | 
FireBeetle M0 |       ✅         |             |            | 
Arduino Leonardo |       ✅         |             |            | 
MicroBit |       ✅         |             |            | 


## History

- data 2020-12-18
- version V1.0


## Credits

Written by yangfeng(feng.yang@dfrobot.com), 2021. (Welcome to our [website](https://www.dfrobot.com/))

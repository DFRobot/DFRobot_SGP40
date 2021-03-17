# DFRobot_SGP40
## 产品链接（https://www.dfrobot.com/）
    SKU：SEN0392

## DFRobot_SGP40 Library for Arduino
---------------------------------------------------------
Provide an Arduino library for the SGP40 modules.

## Table of Contents

* [Summary](#summary)
* [Feature](#feature)
* [Installation](#installation)
* [Methods](#methods)
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

To use this library, download the library file first, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods

```python
def set_envparams(relative_humidity,temperature_c):
    """ Set temperature and humidity
    
    :param relative_humidity:float Set to relative_humidity
    :param temperature_c:float Set to temperature
    """
    self.__temperature_c = temperature_c
    self.__relative_humidity = relative_humidity
    
def begin(self,duration = 10):
    """ start equipment
    
    :param duration:int Set to Warm-up time
    :return int equipment condition
      : 0 succeed
      : 1 failed 
    """
    self.__my_vocalgorithm.vocalgorithm_init()
    timeOne = int(time.time())
    while(int(time.time())-timeOne<duration):
        self.get_voc_index()
    return self.__measure_test()
    
def measure_raw(self):
    """ Get raw data
    
    : return int collect result
      :-1 collect failed
      :>0 the collection value
    """
    self.__data_transform()
    self.__i2cbus.write_i2c_block_data(self.__i2c_addr,self.CMD_MEASURE_RAW_H, [self.CMD_MEASURE_RAW_L,self.__rh_h,self.
    time.sleep(DURATION_READ_RAW_VOC)
    raw = self.__i2cbus.read_i2c_block_data(self.__i2c_addr,OFFSET,3)
    if self.__check__crc(raw) == 0:
      return raw[0]<<8 | raw[1]
    else:
      return -1
    
def get_voc_index(self):
    """ Measure VOC index after humidity compensation
    :note  VOC index can indicate the quality of the air directly. The larger the value, the worse the air quality.
    :note    0-100,no need to ventilate, purify
    :note    100-200,no need to ventilate, purify
    :note    200-400,ventilate, purify
    :note    00-500,ventilate, purify intensely
    :return int The VOC index measured, ranged from 0 to 500
    """
    raw = self.measure_raw()
    if raw<0:
        return -1
    else:
        vocIndex = self.__my_vocalgorithm.VocAlgorithm_process(raw)
        return vocIndex


```




## History

- data 2021-01-12
- version V1.0


## Credits

·Written by [yangfeng]<fary_young@outlook.com>,2020,(Welcome to our [website](https://www.dfrobot.com/))

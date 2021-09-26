# DFRobot_SGP40
- [中文版](./README_CN.md)

The SGP40 Air Quality sensor adopts the new SGP40 digital VOC sensor chip launched by the well-known Sensirion. Based on the Sensirion’s CMOSens® technology, the SGP40 offers a complete sensor system on a single chip, a temperature-controlled micro-hotplate and a humidity-compensated indoor air quality signal. In combination with Sensirion’s powerful VOC algorithm, the sensor signal can be directly used to evaluate indoor air quality. It features low power(2.6mA), and fast response(2s). The data from the sensor can be directly used to evaluate air quality without calibration.

![](../../resources/images/SEN0392.png)

## Product Link (https://www.dfrobot.com/product-2241.html)
    SKU：SEN0392

## DFRobot_SGP40 Library for Arduino
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

To use this library, first download the library to Raspberry Pi, then open the routines folder. To execute one routine, demox.py, type python demox.py on the command line. To execute the get_raw_value.py routine, for example, you need to type:

```
python get_raw_value.py
```
## Methods

```python
    '''
      @brief start equipment
      @param duration:int Set to Warm-up time
      @return equipment condition. 0: succeed  1: failed 
    '''
    begin(self,duration = 10)

    '''
      @brief Set temperature and humidity
      @param relative_humidity:float Set to relative_humidity
      @param temperature_c:float Set to temperature
    '''
    set_envparams(relative_humidity,temperature_c)

    '''
      @brief Get raw data
      @param duration:int Set to Warm-up time
      @return collect result. (-1 collect failed)  (>0 the collection value)
    '''
    measure_raw(self)

    '''
      @brief Measure VOC index after humidity compensation
      @n VOC index can indicate the quality of the air directly. The larger the value, the worse the air quality.
      @n   0-100,no need to ventilate, purify
      @n   100-200,no need to ventilate, purify
      @n   200-400,ventilate, purify
      @n   00-500,ventilate, purify intensely
      @param duration:int Set to Warm-up time
      @return The VOC index measured, ranged from 0 to 500
    '''
    get_voc_index(self)
```


## Compatibility

* RaspberryPi Version

| Board        | Work Well | Work Wrong | Untested | Remarks |
| ------------ | :-------: | :--------: | :------: | ------- |
| RaspberryPi2 |           |            |    √     |         |
| RaspberryPi3 |           |            |    √     |         |
| RaspberryPi4 |     √     |            |          |         |

* Python Version

| Python  | Work Well | Work Wrong | Untested | Remarks |
| ------- | :-------: | :--------: | :------: | ------- |
| Python2 |     √     |            |          |         |
| Python3 |     √     |            |          |         |


## History

- data 2021-01-12
- version V1.0


## Credits

Written by yangfeng(feng.yang@dfrobot.com), 2021. (Welcome to our [website](https://www.dfrobot.com/))

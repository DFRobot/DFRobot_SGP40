/**
*@file DFRobot_SGP40.h
*@brief Define the infrastructure for the DFRobot_SGP40 class
*@n This is a DFRobot_SGP40 sensor that supports IIC communication. The IIC address is immutable,0x59. The functions are as follows:
*@n Function 1: Set ambient temperature and humidity for accurate calibration. Relative humidity unit: %RH, range: 0-100; Temperature unit: °C, range: -10~50
*@n Function 2: Read VOC index , range 0-500
*@copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
*@SKU SEN0392
*@licence The MIT License (MIT)
*@author [yangfeng]<feng.yang@dfrobot.com>
*@version V1.0
*@date 2020-12-18
*@url  https://github.com/DFRobot/DFRobot_SGP40
*/
#ifndef _DFROBOT_SGP40_H_
#define _DFROBOT_SGP40_H_
#include <Arduino.h>
#include <Wire.h>
extern "C" {
#include "sensirion_arch_config.h"
#include "sensirion_voc_algorithm.h"
};

#define DFRobot_SGP40_ICC_ADDR                              0x59

class DFRobot_SGP40{
public:
  #define TEST_OK                                           0xD400

  #define CMD_HEATER_OFF_H                                  0x36
  #define CMD_HEATER_OFF_L                                  0x15
  #define CMD_HEATER_OFF_SIZE                               2
  
  #define CMD_MEASURE_TEST_H                                0x28
  #define CMD_MEASURE_TEST_L                                0x0E
  #define CMD_MEASURE_TEST_SIZE                             2
  
  #define CMD_SOFT_RESET_H                                  0x00
  #define CMD_SOFT_RESET_L                                  0x06
  #define CMD_SOFT_RESET_SIZE                               2
  
  #define CMD_MEASURE_RAW_H                                 0x26
  #define CMD_MEASURE_RAW_L                                 0x0F
  
  #define INDEX_MEASURE_RAW_H                               0
  #define INDEX_MEASURE_RAW_L                               1
  #define INDEX_RH_H                                        2
  #define INDEX_RH_L                                        3
  #define INDEX_RH_CHECK_CRC                                4
  #define INDEX_TEM_H                                       5
  #define INDEX_TEM_L                                       6
  #define INDEX_TEM_CHECK_CRC                               7
  
  #define DURATION_READ_RAW_VOC                             30
  #define DURATION_WAIT_MEASURE_TEST                        320
  
public:
   /**
   * @brief  constructed function
   * @param  pWire  When constructing a device, you can specify its twowire
   */
  DFRobot_SGP40(TwoWire *pWire=&Wire);
  ~DFRobot_SGP40(){
  };
  /**
   * @brief  Initialization function
   * @param duration Warm-up time
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

private:
  /**
   * @brief  Sensor self-test
   * @return true:all tests passed successfully; false：one or more tests have failed
   */
  bool sgp40MeasureTest(void);
  
  /**
   * @brief  Soft Reset, the SGP40 will restart entering the idle mode.
   */
  void softReset(void);
  
  /**
   * @brief  Get data through IIC
   * @return The raw data obtained
   */
  uint16_t readRawData(void);
  
  /**
   * @brief  CRC
   * @param  data1  High 8 bits data
   * @param  data2  LOW 8 bits data
   * @return Calibration value
   */
  uint8_t checkCrc(uint8_t data1,uint8_t data2);
  
  /**
   * @brief  Conversion of relative humidity in % and temperature in °C into ticks as the input parameters of the measurement command
   */
  void dataTransform(void);
  
  /**
   * @brief  spg40 Heater Off. Turn the hotplate off and stop the measurement. Subsequently, the sensor enters the idle mode.
   */
  void spg40HeaterOff(void);
  
  /**
   * @brief  Write commands through IIC
   * @param  Command  Command address
   * @param  len  Command length
   */
  void write(uint8_t* cmd,uint8_t len);
  
private:
  TwoWire* _pWire;
  float _relativeHumidity;
  float _temperatureC;
  uint8_t _rhTemData[8];
  uint8_t _deviceAddr;
  VocAlgorithmParams _vocaAgorithmParams;
};
#endif

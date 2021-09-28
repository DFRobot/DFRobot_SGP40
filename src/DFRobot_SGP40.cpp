/**
*@file DFRobot_SGP40.cpp
*@brief Define the DFRobot_SGP40 class infrastructure, the implementation of the underlying methods
*@copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
*@SKU SEN0392
*@licence The MIT License (MIT)
*@author [yangfeng]<feng.yang@dfrobot.com>
*@version V1.0
*@date 2020-12-18
*@url https://github.com/DFRobot/DFRobot_SGP40
*/
#include "DFRobot_SGP40.h"
#include "sensirion_arch_config.h"
#include "sensirion_voc_algorithm.h"
DFRobot_SGP40::DFRobot_SGP40(TwoWire *pWire):
_pWire(pWire),_temperatureC(25)
{
  _deviceAddr = DFRobot_SGP40_ICC_ADDR;
  _relativeHumidity = 50.0;
  _temperatureC=25.0;
}

bool DFRobot_SGP40::begin(uint32_t duration)
{
  _pWire->begin();
  VocAlgorithm_init(&_vocaAgorithmParams);
  unsigned long timestamp = millis();
  while(millis()-timestamp<duration){
    getVoclndex();
  }
  return sgp40MeasureTest();
}

uint8_t DFRobot_SGP40::checkCrc(uint8_t data1,uint8_t data2)
{
  uint8_t crc = 0xFF;
  uint8_t data[2];
  data[0]=data1;
  data[1]=data2;
  for(int i =0; i<2;i++){
    crc ^= data[i];
    for(uint8_t bit = 8;bit>0;--bit){
      if(crc & 0x80){
        crc = (crc << 1)^0x31u;
      }else{
        crc = (crc << 1);
      }
    }
  }
  return crc;
}

void DFRobot_SGP40::setRhT(float relativeHumidity, float temperatureC)
{
  _relativeHumidity = relativeHumidity;
  _temperatureC = temperatureC;
  dataTransform();
  write(_rhTemData,6);
}

void DFRobot_SGP40::dataTransform(void)
{
  uint16_t RH = (uint16_t)((_relativeHumidity*65535)/100+0.5);
  uint16_t TemC = (uint16_t)((_temperatureC+45)*(65535/175)+0.5);
  _rhTemData[INDEX_MEASURE_RAW_H]=CMD_MEASURE_RAW_H;
  _rhTemData[INDEX_MEASURE_RAW_L]=CMD_MEASURE_RAW_L;
  _rhTemData[INDEX_RH_H]=RH>>8;
  _rhTemData[INDEX_RH_L]=RH&0x00FF;
  _rhTemData[INDEX_RH_CHECK_CRC]=checkCrc(_rhTemData[INDEX_RH_H],_rhTemData[INDEX_RH_L]);
  _rhTemData[INDEX_TEM_H]=TemC>>8;
  _rhTemData[INDEX_TEM_L]=TemC&0x00FF;
  _rhTemData[INDEX_TEM_CHECK_CRC]=checkCrc(_rhTemData[INDEX_TEM_H],_rhTemData[INDEX_TEM_L]);
}

void DFRobot_SGP40::write(uint8_t* cmd,uint8_t len)
{
  _pWire->beginTransmission(_deviceAddr);
  for(uint8_t i=0;i<len;i++){
    _pWire->write(cmd[i]);
  }
  _pWire->endTransmission();
}

uint16_t DFRobot_SGP40::readRawData()
{
  uint8_t data[3]={0,0,0};
  uint16_t value=0;
  _pWire->requestFrom(_deviceAddr,(uint8_t)3);
  for(uint8_t i=0;i<3;i++){
    data[i]=_pWire->read();
  }
  value=(data[0]<<8)|data[1];
  return value;
}

uint16_t DFRobot_SGP40::getVoclndex(void)
{
  uint8_t data[3]={0,0,0};
  int32_t value;
  int32_t vocIndex=0;
  dataTransform();
  _pWire->beginTransmission(_deviceAddr);
  for(int i=0;i<8;i++){
    _pWire->write(_rhTemData[i]);
  }
  _pWire->endTransmission();
  delay(DURATION_READ_RAW_VOC);
  _pWire->requestFrom(_deviceAddr,(uint8_t)3);
  for(uint8_t i=0;i<3;i++){
    data[i]=_pWire->read();
  }
  value=(data[0]<<8)|data[1];
  VocAlgorithm_process(&_vocaAgorithmParams, value, &vocIndex);
  return vocIndex;
}


void DFRobot_SGP40::spg40HeaterOff()
{
  uint8_t testCommand[CMD_HEATER_OFF_SIZE]={CMD_HEATER_OFF_H,CMD_HEATER_OFF_L};
  write(testCommand,CMD_HEATER_OFF_SIZE);
}


bool DFRobot_SGP40::sgp40MeasureTest()
{
  uint8_t testCommand[CMD_MEASURE_TEST_SIZE]={CMD_MEASURE_TEST_H,CMD_MEASURE_TEST_L};
  write(testCommand,CMD_MEASURE_TEST_SIZE);
  delay(DURATION_WAIT_MEASURE_TEST);
  if(readRawData()==TEST_OK){
    return true;
  }
  return false;
}

void DFRobot_SGP40::softReset()
{
  uint8_t testCommand[CMD_SOFT_RESET_SIZE]={CMD_SOFT_RESET_H,CMD_SOFT_RESET_L};
  write(testCommand,CMD_SOFT_RESET_SIZE);
  _relativeHumidity = 50;
  _temperatureC = 25;
}












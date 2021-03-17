""" 
  @file DFRobot_SGP40.py
  @note DFRobot_SGP40 Class infrastructure, implementation of underlying methods
  @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @licence     The MIT License (MIT)
  @author      [yangfeng]<feng.yang@dfrobot.com> 
  version  V1.0
  date  2021-01-15
  @get from https://www.dfrobot.com
  @url https://github.com/DFRobot/DFRobot_SGP40
"""

import smbus
import time
from DFRobot_SGP40_VOCAlgorithm import DFRobot_VOCAlgorithm

class DFRobot_SGP40:
    DFRobot_SGP40_ICC_ADDR                           = 0x59
    TEST_OK_H                                        = 0xD4
    TEST_OK_L                                        = 0x00
    CMD_HEATER_OFF_H                                 = 0x36
    CMD_HEATER_OFF_L                                 = 0x15
                                                     
    CMD_MEASURE_TEST_H                               = 0x28
    CMD_MEASURE_TEST_L                               = 0x0E
                                                     
    CMD_SOFT__reset_H                                = 0x00
    CMD_SOFT__reset_L                                = 0x06
                                                     
    CMD_MEASURE_RAW_H                                = 0x26
    CMD_MEASURE_RAW_L                                = 0x0F

    DURATION_READ_RAW_VOC                            = 0.03
    DURATION_WAIT_MEASURE_TEST                       = 0.25
    OFFSET                                           = 0x00
        
    def __init__(self,bus = 1,relative_humidity = 50,temperature_c = 25):
        """ Module init
        
        :param bus:int Set to IICBus
        :param relative_humidity:float Set to relative_humidity
        :param temperature_c:float Set to temperature
        """
        self.__i2cbus = smbus.SMBus(bus)
        self.__my_vocalgorithm = DFRobot_VOCAlgorithm()
        self.__i2c_addr = self.DFRobot_SGP40_ICC_ADDR
        self.__temperature_c = temperature_c
        self.__relative_humidity = relative_humidity
        self.__rh = 0
        self.__temc = 0
        self.__rh_h = 0
        self.__rh_l = 0
        self.__temc_h = 0
        self.__temc_l = 0
        self.__temc__crc = 0
        self.__rh__crc = 0
        
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
        self.__i2cbus.write_i2c_block_data(self.__i2c_addr,self.CMD_MEASURE_RAW_H, [self.CMD_MEASURE_RAW_L,self.__rh_h,self.__rh_l,self.__rh__crc,self.__temc_h,self.__temc_l,self.__temc__crc])
        time.sleep(self.DURATION_READ_RAW_VOC)
        raw = self.__i2cbus.read_i2c_block_data(self.__i2c_addr,self.OFFSET,3)
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
            vocIndex = self.__my_vocalgorithm.vocalgorithm_process(raw)
            return vocIndex
          
    def __data_transform(self):
        """ Convert environment parameters

        """
        self.__rh = int(((self.__relative_humidity*65535)/100+0.5))
        self.__temc = int(((self.__temperature_c+45)*(65535/175)+0.5))
        self.__rh_h = int(self.__rh)>>8
        self.__rh_l = int(self.__rh)&0xFF
        self.__rh__crc = self.__crc(self.__rh_h,self.__rh_l)
        self.__temc_h = int(self.__temc)>>8
        self.__temc_l = int(self.__temc)&0xFF
        self.__temc__crc = self.__crc(self.__temc_h,self.__temc_l) 
        
    def __measure_test(self):
        """ Sensor self-test
        
        :return int self-test condition
          : 0 succeed
          : 1 failed 
        """
        self.__i2cbus.write_i2c_block_data(self.__i2c_addr,self.CMD_MEASURE_TEST_H, [self.CMD_MEASURE_TEST_L])
        time.sleep(self.DURATION_WAIT_MEASURE_TEST)
        raw = self.__i2cbus.read_i2c_block_data(self.__i2c_addr,self.OFFSET,2)
        if raw[0] == self.TEST_OK_H and raw[1] == self.TEST_OK_L :
            return 0
        else:
            return 1
            
    def __reset(self):
        """ Sensor reset
        
        """
        self.__i2cbus.write_i2c_block_data(self.__i2c_addr,self.CMD_SOFT__reset_H, [self.CMD_SOFT__reset_L])
    
    def __heater_off(self):
        """ spg40 Heater Off. Turn the hotplate off and stop the measurement. Subsequently, the sensor enters the idle mode.
        
        """
        self.__i2cbus.write_i2c_block_data(self.__i2c_addr,self.CMD_HEATER_OFF_H, [self.CMD_HEATER_OFF_L])

    def __check__crc(self, raw):
        """ Verify the calibration value of the sensor
        
        :param raw : list Parameter to check
        :return int Check result
          :-1 Check failed
          : 0 Check succeed
        """
        assert (len(raw) == 3)
        if self.__crc(raw[0], raw[1]) != raw[2]:
            return -1
        return 0

    def __crc(self,data_1,data_2):
        """ CRC
        
        :param  data1  High 8 bits data
        :param  data2  LOW 8 bits data
        :return int Calibration value
        """
        crc = 0xff
        list = [data_1,data_2]
        for i in range(0,2):
            crc = crc^list[i]
            for bit in range(0,8):
                if(crc&0x80):
                    crc = ((crc <<1)^0x31)
                else:
                    crc = (crc<<1)
            crc = crc&0xFF
        return crc

""" 
  @file SGP40_demo_get_voc_index.py
  @brief Getting VOC index
  @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @licence     The MIT License (MIT)
  @author      [yangfeng]<feng.yang@dfrobot.com> 
  version  V1.0
  date  2021-01-15
  @get from https://www.dfrobot.com
  @url https://github.com/DFRobot/DFRobot_SGP40
"""
import sys
sys.path.append('../')
import time
from DFRobot_SGP40 import DFRobot_SGP40

#set IICbus elativeHumidity(0-100%RH)  temperature(-10~50 centigrade)
sgp40=DFRobot_SGP40(bus = 1,relative_humidity = 50,temperature_c = 25)

#set Warm-up time
print 'Please wait 10 seconds...'
sgp40.begin(10)

#If you want to modify the environment parameters, you can do so
#elativeHumidity(0-100%RH)  temperature(-10~50 centigrade)
#sgp40.set_envparams(50,-2)

while True:
    print 'Voc index : %d'%(sgp40.get_voc_index())
    time.sleep(1)
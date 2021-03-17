  
/*!
 * @file getVocIndex.ino
 * @brief Read the environmental VOC index.  Range: 0-500;
 * @n Experimental phenomena: read environmental VOC index once per second and print the value in serial port
 *
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [yangfeng]<feng.yang@dfrobot.com>
 * @version  V1.0
 * @date  2020-12-18
 * @get from https://www.dfrobot.com
 * @url  https://github.com/DFRobot/DFRobot_SGP40
 */
#include <DFRobot_SGP40.h>

/* 
 * 方法一：传入指定的I2C对象地址
 * #include <Wire.h>
 * DFRobot_SGP40    mySgp40(&Wire);
 
 * 方法二：使用默认的I2C对象&Wire
 * I2C 默认地址：0x59
 */

//#include <Wire.h>
//DFRobot_SGP40    mySgp40(&Wire);
DFRobot_SGP40    mySgp40;


void setup() {
  Serial.begin(115200);
  Serial.println("sgp40 is starting, the reading can be taken after 10 seconds...");
  /*
   * 传感器预热时间为10s。
   * duration:初始化等待时间。单位：毫秒。建议duration>=10000ms
   */
  while(mySgp40.begin(/*duration = */10000) !=true){
    Serial.println("failed to init chip, please check if the chip connection is fine");
    delay(1000);
  }
  Serial.println("----------------------------------------------");
  Serial.println("sgp40 initialized successfully!");
  Serial.println("----------------------------------------------");
  /* 
   * 设置当前环境中的相对湿度和温度
   * 传感器内部已进行温湿度校准，若需要得到更精确的voc指数，请打开注释
   * relativeHumidity：环境相对湿度，指空气中的水汽含量。范围：0-100，单位：%RH，例如：50%
   * temperature：环境温度。范围：-10~50，单位：°C，例如：20°C
   */
  //mySgp40.setRhT(/*relativeHumidity = */ 50, /*temperature = */ 20);
  
}

void loop() {
  /* 
   * 获取voc指数
   * voc指数可直接指示空气质量的好坏。数值越大，空气质量越差
   *    0-100，no need to ventilate,purify
   *    100-200，no need to ventilate,purify
   *    200-400，ventilate,purify
   *    400-500，ventilate,purify intensely
   * 返回voc指数，范围：0-500
   */
  uint16_t index = mySgp40.getVoclndex();
  
  Serial.print("vocIndex = ");
  Serial.println(index);
  delay(1000);
}
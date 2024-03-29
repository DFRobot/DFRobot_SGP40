  
/*!
 * @file getVocIndex.ino
 * @brief Read the environmental VOC index.  Range: 0-500;
 * @n Experimental phenomena: read environmental VOC index once per second and print the value in serial port
 *
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [yangfeng]<feng.yang@dfrobot.com>
 * @version  V1.0
 * @date  2023-7-7
 * @get from https://www.dfrobot.com
 * @url  https://github.com/DFRobot/DFRobot_SGP40
 */
#include <DFRobot_SGP40.h>

/* 
 * Method 1: Pass in the address of the specified I2C object
 * #include <Wire.h>
 * DFRobot_SGP40    mySGP40(&Wire);
 
 * Method 2: Use the default I2C object &Wire
 *I2C Default address: 0x59
 */

//#include <Wire.h>
//DFRobot_SGP40    mySGP40(&Wire);
DFRobot_SGP40    mySGP40;//Declare SGP40.


void setup() {
  Serial.begin(115200); //Initialize Serial communication at 115200 baud(bits per second)
  Serial.println("DFrobot Gravity SGP40 VOC Sensor Example");
  Serial.println(F("Starting " __FILE__ " from " __DATE__ __TIME__));//Just to help tell you what sketch your board is running.
  Serial.println("SGP40 is booting up, sensor readings can be taken after 10 seconds...");
  /*
   * The preheating time of the sensor is 10s.
   * duration:Initialize the wait time. Unit: millisecond. Suggestion: duration > = 10000 ms
   */
  while(mySGP40.begin(/*duration = */10000) !=true){
    Serial.println("Failed to initialize SGP40, please check wiring and cable connections"); //You need to press the Gravity cable all the way in.
    delay(1000);
  }
  Serial.println("----------------------------------------------");
  Serial.println("SGP40 initialized successfully!");
  Serial.println("----------------------------------------------");
  /**
   * @brief  Set the temperature and humidity
   * @param  relativeHumidityRH  Current environmental relative humidity value, range 0-100, unit: %RH
   * @param  temperatureC  Current ambient temperature, range -10~50, unit: °C
   */
  //mySGP40.setRhT(/*relativeHumidity = */ 50, /*temperature = */ 20);
  
}

void loop() {
  /**
   * @brief  Measure VOC index after humidity compensation
   * @note   VOC index can indicate the quality of the air directly. The larger the value, the worse the air quality.
   * @note       0-100，no need to ventilate, purify
   * @note       100-200，no need to ventilate, purify
   * @note       200-400，ventilate, purify
   * @note       400-500，ventilate, purify intensely
   * @return The VOC index measured, ranged from 0 to 500
   */
  uint16_t index = mySGP40.getVoclndex();//Declare variable that is to be used to store VOC index.
  
  Serial.print("vocIndex = ");
  Serial.println(index);
  delay(1000);
}

# DFRobot_SGP40
- [English Version](./README.md)

SGP40空气质量传感器采用知名品牌Sensirion推出的新款SGP40数字VOC传感器芯片。基于Sensirion公司的CMOSens®技术，SGP40提供了一个完整的单芯片传感器系统，一个温控微热板和湿度补偿室内空气质量信号。结合Sensirion强大的VOC算法，传感器信号可以直接用于评价室内空气质量。低功耗(2.6mA)，响应速度快(2s)。来自传感器的数据可以直接用于评价空气质量，而无需校准。

![](./resources/images/SEN0392.png)

## 产品链接(https://www.dfrobot.com.cn/goods-3062.html)

    SKU：SEN0392

## 目录

* [概述](#概述)
* [库安装](#库安装)
* [方法](#方法)
* [兼容性](#兼容性)
* [历史](#历史)
* [创作者](#创作者)

## 概述

XYZ三刺激和红外数据的检测

## 库安装

使用此库前，请首先下载库文件，将其粘贴到\Arduino\libraries目录中，然后打开examples文件夹并在该文件夹中运行演示。

## 方法

```C++
  /**
   *  @brief 液晶屏以及主控IIC的初始化
   */ 
  void init();

  /**
   *  @brief 清除显示并将光标回到初始位置（0位置）
   */
  void clear();

  /**
   *  @brief 将光标回到初始位置（0,0）
   */
  void home();

    /**
     *  @brief Turn off the display
     */
  void noDisplay();

  /**
   *  @brief Turn on the display
   */
  void display();

  /**
   *  @brief Turn  off the blinking showCursor
   */
  void stopBlink();

  /**
   *  @brief Turn on  the blinking showCursor
   */
  void blink();

  /**
   *  @brief Turn off the underline showCursor 
   */
  void noCursor();

  /**
   *  @brief Turn on the underline showCursor 
   */
  void cursor();

  /**
   *  @brief 向左滚动显示
   */
  void scrollDisplayLeft();

  /**
   *  @brief 向右滚动显示
   */
  void scrollDisplayRight();
 
  /**
   *  @brief This is for text that flows Left to Right
   */
  void leftToRight();
 
  /**
   *  @brief This is for text that flows Right to Left
   */
  void rightToLeft();

  /**
   *  @brief This will 'left justify' text from the showCursor
   */
  void noAutoscroll();
 
  /**
   *  @brief This will 'right justify' text from the showCursor
   */
  void autoscroll();
   
  /**
   *  @brief Allows us to fill the first 8 CGRAM locations with custom characters
   *  @param location 代替字符 范围（0-7）
   *  @param charmap  字符数组 大小8个字节
   */
  void customSymbol(uint8_t location, uint8_t charmap[]);

  /**
   *  @brief 设置光标位置
   *  @param col 列数 可选范围 0-15
   *  @param row 行数 可选范围 0-1，0代表了第一行，1代表了第二行
   */
  void setCursor(uint8_t col, uint8_t row);
  
  /**
   *  @brief 设置RGB
   *  @param r  red   范围(0-255)
   *  @param g  green 范围(0-255)
   *  @param b  blue  范围(0-255)
   */
  void setRGB(uint8_t r, uint8_t g, uint8_t b);

  /**
   *  @brief 设置背光PWM输出
   *  @param color  背光颜色  参数选择：REG_RED\REG_GREEN\REG_BLUE
   *  @param pwm  颜色强度值   范围(0-255)
   */
  void setPWM(uint8_t color, uint8_t pwm);

  /**
   *  @brief 背光颜色
   *  @param color  背光颜色  参数选择： WHITE\RED\GREEN\BLUE
   */
  void setColor(uint8_t color);

  /**
   *  @brief 关闭背光
   */
  void closeBacklight();

  /**
   *  @brief 设置背光为白色
   */
  void setColorWhite();

  /**
   *  @brief blink the LED backlight
   */
  void blinkLED(void);

  /**
   *  @brief 不闪烁背光
   */
  void noBlinkLED(void);

  /**
   *  @brief write character
   *  @param data 写入的数据
   */
  virtual size_t write(uint8_t data);

  /**
   *  @brief send command
   *  @param data 发送的命令
   */
  void command(uint8_t data);

  /**
   *  @brief 设置背光
   *  @param mode  true代表开启背光并设置为白色，false代表关闭背光
   */
  void setBacklight(bool mode);
```

## 兼容性

| 主板          | 通过 | 未通过 | 未测试 | 备注 |
| ------------- | :--: | :----: | :----: | ---- |
| Arduino uno   |  √   |        |        |      |
| Mega2560      |  √   |        |        |      |
| Leonardo      |  √   |        |        |      |
| ESP32         |  √   |        |        |      |
| micro:bit     |  √   |        |        |      |
| FireBeetle M0 |  √   |        |        |      |


## 历史

- 日期 2021-9-26
- 版本 V1.0.0


## 创作者

Written by yangfeng(feng.yang@dfrobot.com), 2021. (Welcome to our [website](https://www.dfrobot.com/))


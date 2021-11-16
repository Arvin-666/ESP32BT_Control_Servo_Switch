/*
 * ESP32BLE控制舵机实现开关灯
 * Author:猿一
 * 2021.11.14
 */

#include "BluetoothSerial.h"
#include <Servo.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
Servo servo1;
static const int servoPin = 16;
static const int OpenParameter = 105;   //开启开关舵机的角度
static const int CloseParameter = 5; //关闭开关舵机的角度
static const int ResetParemeter = 45; //舵机复位角度
String readMsg = "";
void setup()
{
  Serial.begin(115200);
  SerialBT.begin("ESP32BLE_Servo"); //蓝牙设备名称
  delay(50);
  Serial.println("The device started, now you can pair it with bluetooth!");
  servo1.attach(
    servoPin,
    Servo::CHANNEL_NOT_ATTACHED,
    0,
    180
  );
}
/*
   蓝牙串口接收
*/
void ReceiverBleMessage()
{
  while (SerialBT.available() > 0)
  {
    readMsg += char(SerialBT.read());
    delay(2);
  }
}
void loop()
{
  ReceiverBleMessage();
  if (readMsg == "OPEN")
  {
    servo1.write(OpenParameter);
    delay(200);
    servo1.write(ResetParemeter);
    Serial.print("Receiver:");
    Serial.println(readMsg);
  }
  else if (readMsg == "CLOSE")
  {
    servo1.write(CloseParameter);
    delay(200);
    servo1.write(ResetParemeter);
    Serial.print("Receiver:");
    Serial.println(readMsg);
  }
  readMsg="";
}




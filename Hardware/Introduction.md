## Hardware Implementation  

The hardware system uses **ESP32 with MPU6050** and **Arduino Nano 33 BLE Sense** for real-time oversteering detection.  

### Arduino IDE Libraries Used  

Make sure the following libraries are installed in the **Arduino IDE**:  

```cpp
#include <Adafruit_MPU6050.h>   // For MPU6050 accelerometer + gyroscope
#include <Adafruit_Sensor.h>    // Adafruit unified sensor support
#include <Wire.h>               // I2C communication between ESP32 and MPU6050
#include <Arduino_LSM9DS1.h>    // For 9-axis IMU on Arduino Nano 33 BLE Sense

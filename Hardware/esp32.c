#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

// Define normal range thresholds
#define ACCEL_THRESHOLD_X_MIN -5.0   // Minimum threshold for accelerometer X axis (in m/s^2)
#define ACCEL_THRESHOLD_X_MAX 5.0    // Maximum threshold for accelerometer X axis (in m/s^2)
#define ACCEL_THRESHOLD_Y_MIN -3.0   // Minimum threshold for accelerometer Y axis (in m/s^2)
#define ACCEL_THRESHOLD_Y_MAX 3.0    // Maximum threshold for accelerometer Y axis (in m/s^2)
#define GYRO_THRESHOLD_Z_MIN -0.5    // Minimum threshold for gyroscope Z axis (in rad/s)
#define GYRO_THRESHOLD_Z_MAX 0.5     // Maximum threshold for gyroscope Z axis (in rad/s)

// Define LED pin for external LED (connected to GPIO19)
#define LED_PIN 19  // GPIO19 for external LED

void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize the sensor!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  // Initialize LED pin
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // Ensure LED is off initially

  Serial.println("MPU6050 Initialization complete");
  delay(100);
}

void loop() {

  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Get accelerometer values
  float accelX = a.acceleration.x;
  float accelY = a.acceleration.y;
  
  // Get gyroscope Z-axis value
  float gyroZ = g.gyro.z;

  // Print out the required values
  Serial.print("Accel X: ");
  Serial.print(accelX);
  Serial.print(" m/s^2, ");
  
  Serial.print("Accel Y: ");
  Serial.print(accelY);
  Serial.print(" m/s^2, ");
  
  Serial.print("Gyro Z: ");
  Serial.print(gyroZ);
  Serial.println(" rad/s");

  // Detect Oversteering or Normal Condition based on thresholds
  if (accelX < ACCEL_THRESHOLD_X_MIN || accelX > ACCEL_THRESHOLD_X_MAX ||
      accelY < ACCEL_THRESHOLD_Y_MIN || accelY > ACCEL_THRESHOLD_Y_MAX ||
      gyroZ < GYRO_THRESHOLD_Z_MIN || gyroZ > GYRO_THRESHOLD_Z_MAX) {
    Serial.println("Condition: Oversteering");

    // Blink the external LED for 0.5 seconds
    digitalWrite(LED_PIN, HIGH); // Turn on LED
    delay(250);                   // Wait for 250 milliseconds
    digitalWrite(LED_PIN, LOW);  // Turn off LED
    delay(250);                   // Wait for another 250 milliseconds
  } else {
    Serial.println("Condition: Normal");
    digitalWrite(LED_PIN, LOW); // Ensure LED is off
  }

  Serial.println("");  // Print a blank line for readability
  delay(500);  // Delay to make the output readable (adjustable)
}

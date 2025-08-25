#include <Arduino_LSM9DS1.h>

// Define the LED pin (connect the external LED to this pin)
#define LED_PIN 12  // Change this to GPIO12 (or any other GPIO pin)

// Define the gyroscope Y-axis threshold (in degrees/second)
#define GYRO_Y_THRESHOLD_MIN -100.0  // Lower limit of the threshold
#define GYRO_Y_THRESHOLD_MAX 100.0   // Upper limit of the threshold

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Started");

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  // Initialize the LED pin
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);  // Ensure the LED is off initially

  Serial.print("Gyroscope sample rate = ");
  Serial.print(IMU.gyroscopeSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Gyroscope in degrees/second");
  Serial.println("Y");
}

void loop() {
  float x, y, z;

  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(x, y, z);

    // Print the gyroscope Y value (steering angle)
    Serial.print("Gyro Y: ");
    Serial.println(y);

    // Check if the gyroscope Y value exceeds the threshold
    if (y < GYRO_Y_THRESHOLD_MIN || y > GYRO_Y_THRESHOLD_MAX) {
      Serial.println("OVERSTEERING! Blinking LED...");

      // Blink the external LED for 0.5 seconds (250ms on, 250ms off)
      digitalWrite(LED_PIN, HIGH); // Turn on LED
      delay(250);                   // Wait for 250 milliseconds
      digitalWrite(LED_PIN, LOW);  // Turn off LED
      delay(250);                   // Wait for another 250 milliseconds
    } else {
      // If within the threshold, keep the LED off
      digitalWrite(LED_PIN, LOW);
    }
  }

  delay(100); // Small delay to reduce serial print frequency
}

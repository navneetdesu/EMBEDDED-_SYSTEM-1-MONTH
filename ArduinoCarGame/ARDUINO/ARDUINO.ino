#include <Arduino_LSM9DS1.h>

void setup() {
  Serial.begin(115200);

  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("IMU failed!");
    while (1);
  }
}

void loop() {
  float x, y, z;

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);
    Serial.println(x);
    delay(20);
  }
}
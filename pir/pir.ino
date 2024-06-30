// Include necessary libraries
#include <Arduino.h>

// Define the GPIO pin where PIR sensor output is connected
const int pirSensor = 14;  // GPIO 14 on ESP32 (D14 on NodeMCU)

void setup() {
  Serial.begin(115200);
  
  // Initialize PIR sensor pin as input
  pinMode(pirSensor, INPUT);

  Serial.println("PIR Motion Sensor Test");
}

void loop() {
  // Read PIR sensor value
  int pirValue = digitalRead(pirSensor);

  // Check if motion is detected
  if (pirValue == HIGH) {
    Serial.println("Motion detected!");
  } else {
    Serial.println("No motion detected.");
  }

  delay(1000); // Delay for 1 second
}

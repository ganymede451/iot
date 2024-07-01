#include <SoftwareSerial.h>

#define BT_RX_PIN D2  // Connect to TX of HC-05
#define BT_TX_PIN D3  // Connect to RX of HC-05

SoftwareSerial bluetooth(BT_RX_PIN, BT_TX_PIN);

void setup() {
  Serial.begin(9600); // For serial monitor
  bluetooth.begin(9600); // HC-05 default baud rate
  
  Serial.println("Waiting for Bluetooth connection...");
}

void loop() {
  // If data is available from Bluetooth, read it and send it to Serial Monitor
  if (bluetooth.available()) {
    char btData = bluetooth.read();
    Serial.print(btData);
  }
  
  // If data is available from Serial Monitor, read it and send it to Bluetooth
  if (Serial.available()) {
    char serialData = Serial.read();
    Serial.print(serialData);
    bluetooth.print(serialData);
  }
}

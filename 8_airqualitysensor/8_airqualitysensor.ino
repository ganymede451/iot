const int mqPin = A0;


void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(mqPin); // Read analog value from MQ sensor
  
  Serial.print("Raw Sensor Value: ");
  Serial.println(sensorValue);

  float normalizedValue = sensorValue / 1023.0;

  // Print gas concentration
  Serial.print("Gas value:");
  Serial.println(normalizedValue);

  delay(1000); // Delay for stability
}


const int pirSensor = D10; 

void setup() {
  Serial.begin(9600);
  
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

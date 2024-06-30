
void setup() {
  pinMode(LED_BUILTIN, OUTPUT); 
  Serial.begin(9600);
  Serial.println("Enter 'ON' to turn the LED on and 'OFF' to turn the LED off.");
}
void loop() {
  if (Serial.available() > 0) { // Check if data is available to read
    String command = Serial.readStringUntil('\n'); 
    // Read the incoming string until newline
    if (command == "ON") {
      digitalWrite(LED_BUILTIN, LOW); // Turn the LED on
      Serial.println("LED is ON");
    } else if (command == "OFF") {
      digitalWrite(LED_BUILTIN, HIGH); // Turn the LED off
      Serial.println("LED is OFF");
    } else {
      Serial.println("Invalid command. Enter 'ON' or 'OFF'.");
    }
    }}

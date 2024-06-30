void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
}

void loop() {
  // Turn the LED on
  digitalWrite(LED_BUILTIN, LOW);
  // Wait for 5 second
  delay(5000);
  // Turn the LED off
  digitalWrite(LED_BUILTIN, HIGH);
  // Wait for 2 second
  delay(2000);
}

void s(){ 
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1500);
}

void o(){
  digitalWrite(LED_BUILTIN, LOW);
  delay(800);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(800);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(800);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
}

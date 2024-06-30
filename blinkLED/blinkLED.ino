void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}
void loop() {
  s();
  o();
  s();
}

void s(){
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1500);
}

void o(){
  digitalWrite(LED_BUILTIN, HIGH);
  delay(800);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(800);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(800);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
}

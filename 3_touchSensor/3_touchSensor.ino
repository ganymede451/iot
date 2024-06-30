void setup() {
Serial.begin(9600);
pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

if (touchRead(12)<60){
  digitalWrite(LED_BUILTIN,HIGH);
}
else  digitalWrite(LED_BUILTIN,LOW);

delay(100);
}

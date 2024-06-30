int count = 0;
void setup() {
Serial.begin(9600);
}

void loop() {
  Serial.print("count:");
  Serial.print(count++);
  Serial.print(",");  
  Serial.print("count+:");
  Serial.print(count +10);
  Serial.println();
  delay(1000);
}

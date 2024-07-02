#define BLYNK_TEMPLATE_ID "TMPL6acTZyyyG"
#define BLYNK_TEMPLATE_NAME "playground"
#define BLYNK_AUTH_TOKEN "5OUnF0boY2B55UmXUP83SLDRRVNm3H-e"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>


char auth[] = BLYNK_AUTH_TOKEN;

// Replace with your WiFi credentials
char ssid[] = "gyanimayatmg_fbnpa";
char pass[] = "mayatamang123";

const int ledPin = 2;
const int fan = D3;
const int mqPin = A0;
const int trigPin = D5;
const int echoPin = D6;
const int tankHeight=300;

bool eventTrigger;


#define DHTPIN D7   // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   

DHT dht(DHTPIN, DHTTYPE);

BLYNK_WRITE(V0)
{
  int buttonState = param.asInt(); // Get the state of the button

  if (buttonState == 1) {
    digitalWrite(ledPin, HIGH); // Turn the LED on
  } else {
    digitalWrite(ledPin, LOW); // Turn the LED off
  }
}

BLYNK_WRITE(V1)
{
  int buttonState = param.asInt(); // Get the state of the button

  if (buttonState == 1) {
    digitalWrite(fan, HIGH); // Turn the LED on
  } else {
    digitalWrite(fan, LOW); // Turn the LED off
  }
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  dht.begin();

  // Initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);
  pinMode(fan, OUTPUT);
  digitalWrite(ledPin, LOW);
  digitalWrite(fan, LOW);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  eventTrigger=false;
  // Connect to Blynk
  Blynk.begin(auth, ssid, pass);
}
void dhtData(){
//humidity sensor

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Blynk.virtualWrite(V2, humidity);
  Blynk.virtualWrite(V3, temperature);
  delay(3000);
}

void airquality(){
  int sensorValue = analogRead(mqPin); // Read analog value from MQ sensor
  
  Serial.print("Raw Sensor Value: ");
  Serial.println(sensorValue);

  float normalizedValue = sensorValue / 1023.0;

  // Print gas concentration
  Serial.print("Gas value:");
  Serial.println(normalizedValue);
  if (normalizedValue < 0.5 && eventTrigger==false) {
    eventTrigger=true;
  Blynk.logEvent("airquality","hazard");

  } else if (normalizedValue>0.5) {
    eventTrigger= false;

  }

  delay(1000); // Delay for stability
}

void tank(){
  // Send a 10 microsecond pulse to trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the time for the echo to return
  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm  ");
  int perc = (distance*100)/tankHeight;
   Serial.print(perc);
   Serial.println("%");
   Blynk.virtualWrite(V4, perc);
}


void loop()
{
  Blynk.run();
  tank();
  dhtData();
  delay(1000);

}
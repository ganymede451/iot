
  
#define BLYNK_TEMPLATE_ID "TMPL6vom39V5o"
#define BLYNK_TEMPLATE_NAME "playground"
#define BLYNK_AUTH_TOKEN ""


#define BLYNK_DEVICE_NAME "Playground"

#define BLYNK_PRINT Serial
#include <SPI.h>
#include <WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[]="";


char ssid[]="";
char pass[]= "";

#define DHTPIN 2          // Digital pin 4

#define DHTTYPE DHT11     // DHT 11

DHT dht(DHTPIN, DHTTYPE);

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  Blynk.virtualWrite(V5, h);  //V5 is for Humidity
  Blynk.virtualWrite(V6, t);  //V6 is for Temperature
}

void setup()
{
  Serial.begin(9600); 
  Blynk.begin(auth, ssid, pass);

  dht.begin();

  delay(1000);
  sendSensor();
}

void loop()
{
  Blynk.run(); // Initiates Blynk
}



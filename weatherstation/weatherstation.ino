#include <DHT.h>               // DHT sensor library
#include <WiFi.h>              // WiFi library
#include <Adafruit_Sensor.h>   // Sensor library
#include <Adafruit_BMP085_U.h> // BMP180 library

// ThingSpeak API key and WiFi credentials
String apiKey = "";
const char *ssid = "gyanimayatmg_fbnpa";
const char *pass = "mayatamang123";
const char* server = "api.thingspeak.com";

// DHT sensor pin and type
#define DHTPIN 22
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
WiFiClient client;
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

void setup() {
  Serial.begin(115200);
  delay(10);

  // Initialize DHT sensor
  dht.begin();

  // Initialize BMP180 sensor
  if (!bmp.begin()) {
    Serial.print("Could not find a valid BMP180 sensor, check wiring!");
    while (1);
  }

  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}

void loop() {
  // Read data from DHT11 sensor
  float h = dht.readHumidity();
  float tDHT = dht.readTemperature();

  // Read data from BMP180 sensor
  sensors_event_t event;
  bmp.getEvent(&event);

  float tBMP, pressure;
  if (event.pressure) {
    bmp.getTemperature(&tBMP); // Get temperature in Celsius
    pressure = event.pressure; // Get pressure in hPa
  } else {
    Serial.println("Failed to read from BMP180 sensor!");
    return;
  }

  // Check if any reads failed
  if (isnan(h) || isnan(tDHT) || isnan(tBMP) || isnan(pressure)) {
    Serial.println("Failed to read from sensors!");
    return;
  }

  // Send data to ThingSpeak
  if (client.connect(server, 80)) {
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(tDHT);
    postStr += "&field2=";
    postStr += String(h);
    postStr += "&field3=";
    postStr += String(tBMP);
    postStr += "&field4=";
    postStr += String(pressure);
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    Serial.print("DHT11 Temperature: ");
    Serial.print(tDHT);
    Serial.print(" °C, Humidity: ");
    Serial.print(h);
    Serial.print("%, BMP180 Temperature: ");
    Serial.print(tBMP);
    Serial.print(" °C, Pressure: ");
    Serial.print(pressure);
    Serial.println(" hPa. Sent to ThingSpeak.");

    // Check the HTTP response
    int timeout = 5000; // 5 seconds timeout
    long start = millis();
    while (client.connected() && millis() - start < timeout) {
      while (client.available()) {
        String line = client.readStringUntil('\n');
        Serial.println(line); // Print the HTTP response
      }
    }

  } else {
    Serial.println("Failed to connect to ThingSpeak");
  }

  client.stop();
  Serial.println("Waiting...");

  delay(15000); // ThingSpeak needs a minimum 15 sec delay between updates
}

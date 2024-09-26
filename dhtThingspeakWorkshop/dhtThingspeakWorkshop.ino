#include <ESP8266WiFi.h>
#include <DHT.h>
#include <ThingSpeak.h>

// WiFi settings
const char* ssid = "wifi SSID";
const char* password = "wifi password";

// ThingSpeak settings
unsigned long channelID = CHannelID;  // Your ThingSpeak Channel ID
const char* writeAPIKey = "apiKEY";  // Your ThingSpeak Write API Key

// DHT11 settings
#define DHTPIN D4        // GPIO pin connected to DHT11
#define DHTTYPE DHT11    // DHT11 sensor
DHT dht(DHTPIN, DHTTYPE);

// ThingSpeak settings
WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(10);

  // Initialize DHT sensor
  dht.begin();

  // Connect to WiFi
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
  Serial.println("Connected to WiFi.");

  // Initialize ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
  // Read temperature and humidity from DHT11 sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if readings are valid
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print readings to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Update ThingSpeak with temperature and humidity data
  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, humidity);

  // Write data to ThingSpeak
  int responseCode = ThingSpeak.writeFields(channelID, writeAPIKey);

  if (responseCode == 200) {
    Serial.println("Data sent to ThingSpeak successfully.");
  } else {
    Serial.println("Error sending data to ThingSpeak. Code: " + String(responseCode));
  }

  // Wait for 20 seconds before the next update (ThingSpeak allows updates every 15 seconds)
  delay(20000);
}

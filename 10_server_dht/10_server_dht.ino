#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT.h>

#define DHTPIN D7   // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);
ESP8266WebServer server(80);


const char* ssid = "YOUR SSID";
const char* password = "YOUR PASSWORD";

void setup() {
  Serial.begin(115200);
  delay(100);
  
  dht.begin();
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Start the server
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  
  if (isnan(humidity) || isnan(temperature)) {
    server.send(200, "text/html", "Failed to read from DHT sensor!");
    return;
  }
  
  String html = "<!DOCTYPE html><html>";
  html += "<head><meta http-equiv='refresh' content='2'>";  // Refresh every 2 seconds
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<title>ESP32 DHT Server</title></head>";
  html += "<body><h1>ESP32 DHT Server</h1>";
  html += "<p>Temperature: " + String(temperature) + " &deg;C</p>";
  html += "<p>Humidity: " + String(humidity) + " %</p>";
  html += "</body></html>";
  
  server.send(200, "text/html", html);
}

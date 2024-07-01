#include <ESP8266WiFi.h>

const char* ssid = "KURC";
const char* password = "KURC\\2014";
void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.println("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  unsigned long startAttemptTime = millis();

  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 30000) { 
     // Timeout after 30 seconds
    delay(500);
    Serial.print(".");
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("");
    Serial.println("Failed to connect to WiFi");
  }
}

void loop() {
  // Empty loop as connection is handled in setup()
}

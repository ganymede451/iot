  
#define BLYNK_TEMPLATE_ID "TMPL6vom39V5o"
#define BLYNK_TEMPLATE_NAME "playground"
#define BLYNK_AUTH_TOKEN "CeB6A9oIoLscb3athFr4eqOOFinv4jw9"


#define BLYNK_DEVICE_NAME "Playground"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[]="gyanimayatmg_fbnpa";
char pass[]= "mayatamang123";


char auth[]="CeB6A9oIoLscb3athFr4eqOOFinv4jw9";
  

const int ledPin = 2; 

void setup() {
  // Debug console
  Serial.begin(115200);
  
  
  Blynk.begin(auth, ssid, pass);
}


void loop() {
  Blynk.run(); // Run Blynk
}

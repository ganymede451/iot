#include <ESP8266WiFi.h>

const char* ssid = "gyanimayatmg_fbnpa";
const char* password = "mayatamang123";
WiFiServer server(80);

String header;
String output2State = "off";

const int output2 = 2;

void setup() {
  Serial.begin(115200);
  pinMode(output2, OUTPUT);
  digitalWrite(output2, LOW);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    unsigned long currentTime = millis();
    unsigned long previousTime = currentTime;
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected() && currentTime - previousTime <= 2000) {
      currentTime = millis();
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        header += c;
        if (c == '\n') {
          if (currentLine.length() == 0) {
            handleRequest(client);
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}

void handleRequest(WiFiClient client) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println("Connection: close");
  client.println();
  
  if (header.indexOf("GET /2/on") >= 0) {
    output2State = "on";
    digitalWrite(output2, HIGH);
  } else if (header.indexOf("GET /2/off") >= 0) {
    output2State = "off";
    digitalWrite(output2, LOW);
  }

client.println("<!DOCTYPE html>");
client.println("<html>");
client.println("<head>");
client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
client.println("<link rel=\"icon\" href=\"data:,\">");
client.println("<style>");
client.println("html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center; }");
client.print(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
client.println(" text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer; }");
client.println(".button2 { background-color: #555555; }");
client.println("</style>");
client.println("</head>");
client.println("<body>");
client.println("<h1>ESP32 Web Server</h1>");
client.println("<p>GPIO 2 - State " + output2State + "</p>");


  if (output2State == "off") {
    client.println("<p><a href=\"/2/on\"><button class=\"button\">ON</button></a></p>");
  } else {
    client.println("<p><a href=\"/2/off\"><button class=\"button button2\">OFF</button></a></p>");
  }

  client.println("</body></html>");
}

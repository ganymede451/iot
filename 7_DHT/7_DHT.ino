#include <DHT.h>

#define DHTPIN D7    // GPIO pin where the DHT sensor is connected
#define DHTTYPE DHT11 // the sensor we will be using is dht11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(2000); 

  float humidity = dht.readHumidity();      // Reads humidity
  float temperature = dht.readTemperature(); // Reads temperature in Celsius

  if (isnan(humidity) || isnan(temperature)) { //isnan = is not a number
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
}

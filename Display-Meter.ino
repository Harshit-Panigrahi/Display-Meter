#include <WiFi.h>

#define SSID "virusnet"
#define PASS "air@6999"
#define METER_PIN 5

void setup() {
  Serial.begin(115200);
  WiFi.begin(SSID, PASS);
  
  while (WiFi.status()  !=  WL_CONNECTED)  {
    Serial.print("*");
    delay(500);
  }
  Serial.println("Connected to WiFi");
  Serial.print("IP addr: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  int meter = analogRead(METER_PIN);
  Serial.print("Potentiometer: ");
  Serial.println(meter);
  delay(1000);
}

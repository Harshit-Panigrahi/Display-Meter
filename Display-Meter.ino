#include <WiFi.h>
#include <HTTPClient.h>

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
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    int meter = analogRead(METER_PIN);
    Serial.print("Potentiometer: ");
    Serial.println(meter);

    http.begin("http://127.0.0.1:5000/add");
    http.addHeader("Content-Type", "application/json");

    int httpRes = http.POST("{ 'value': " + String(meter) + " }");
    Serial.print("HTTP Response: ");
    Serial.println(httpRes);
    http.end();
  }
  else {
    Serial.println("WiFi disconnected");
  }
  delay(1000);
}

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoOTA.h>
#include <DHT.h>
#include "secrets.h"

#define DHTPIN 27
#define DHTTYPE DHT22

const char* DEVICE_ID = "esp32-name";
const unsigned long INTERVAL_MS = 30000; // 30 seconds

DHT dht(DHTPIN, DHTTYPE);
unsigned long lastSend = 0;

void connectWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.printf("\nConnected, IP: %s\n", WiFi.localIP().toString().c_str());
}

void setupOTA() {
  ArduinoOTA.setHostname(DEVICE_ID);
  ArduinoOTA.setPassword(OTA_PASS);
  ArduinoOTA.onStart([]() { Serial.println("OTA update starting..."); });
  ArduinoOTA.onEnd([]()   { Serial.println("\nOTA update done, rebooting"); });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("OTA error %u\n", error);
  });
  ArduinoOTA.begin();
  Serial.println("OTA ready");
}

void sendReading() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Sensor read failed");
    return;
  }

  char body[128];
  snprintf(body, sizeof(body),
           "{\"device\":\"%s\",\"temperature\":%.2f,\"humidity\":%.2f}",
           DEVICE_ID, t, h);

  HTTPClient http;
  http.begin(SERVER_URL);
  http.addHeader("Content-Type", "application/json");
  int code = http.POST(body);
  Serial.printf("%s -> HTTP %d\n", body, code);
  http.end();
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  connectWiFi();
  setupOTA();
}

void loop() {
  ArduinoOTA.handle(); 

  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }

  if (millis() - lastSend >= INTERVAL_MS) {
    lastSend = millis();
    sendReading();
  }
}

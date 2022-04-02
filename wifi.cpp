// WiFi doc: https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include "wifi.h"

#define TIMEOUT 16 // in seconds

ESP8266WiFiMulti wifiMulti;

bool connectToWiFi(String ssid, String password) {
  Serial.println("Connecting to " + ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  int connectionTimeout = TIMEOUT;
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000); // 1 second delay
    Serial.print("WiFi status: ");
    Serial.println(WiFi.status());
    
    if (--connectionTimeout <= 0) {
      Serial.println("WiFi connection timeout");
      return false;
    }
  }
  
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());
  return WiFi.status() == WL_CONNECTED;
}

bool connectToMultiWiFi(const String ssids[ARRAY_SIZE], const String passwords[ARRAY_SIZE]) {
  Serial.println("Connecting to multi WiFi");
  WiFi.mode(WIFI_STA);
  
  for(int i = 0; i < ARRAY_SIZE; i++) {
    Serial.println("Adding access point " + ssids[i]);
    wifiMulti.addAP(ssids[i].c_str(), passwords[i].c_str());
  }

  int status = wifiMulti.run(TIMEOUT * 1000);
  Serial.print("WiFi status: ");
  Serial.println(status);
  
  if (status == WL_CONNECTED) {
    Serial.print("Connected to ");
    Serial.println(WiFi.SSID());
  } else {
    Serial.println("WiFi connection error");
  }
  
  return WiFi.status() == WL_CONNECTED;
}

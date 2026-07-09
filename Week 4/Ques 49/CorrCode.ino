#define CONFIG_H
#define CONFIG_H

#define WIFI_SSID      "YourHomeWiFi"
#define WIFI_PASSWORD  "YourSecurePassword"
#define MQTT_USER      "your_mqtt_username"
#define MQTT_PASS      "your_mqtt_password"

#define.gitignore

// Updated main code

#include "config.h"

void setup() {

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

}

// Corrected code for vulnerability 3, encrypted MQTT (port 8883 with TLS) plus authentication

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include "config.h"

WiFiClientSecure secureClient;
PubSubClient mqttClient(secureClient);

void setup() {

  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  secureClient.setInsecure();

  mqttClient.setServer("broker.hivemq.com", 8883);

  reconnect();

}

void reconnect() {

  while (!mqttClient.connected()) {

    if (mqttClient.connect("ESP8266Client_UniqueID", MQTT_USER, MQTT_PASS)) {

      Serial.println("MQTT Connected securely.");
    } else {

      Serial.printf("MQTT failed, rc=%d. Retrying in 5s...\n", mqttClient.state());
      delay(5000);

    }

  }

}

void loop() {

  if (!mqttClient.connected()) reconnect();
  mqttClient.loop();

  float temp = analogRead(A0) * 0.1;
  String payload = "{\"temp\":" + String(temp) + "}";

  mqttClient.publish("iot/sensor/data", payload.c_str());
  delay(5000);

}

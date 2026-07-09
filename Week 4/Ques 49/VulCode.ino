#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid     = "PublicWiFi";
const char* password = "wifi12345";
const char* broker   = "broker.hivemq.com";
const char* topic    = "iot/sensor/data";

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void setup() {

  WiFi.begin(ssid, password);
  client.setServer(broker, 1883);
  client.connect("ESP8266Client");

}

void loop() {

  float temp = analogRead(A0) * 0.1;
  String payload = "temp=" + String(temp);
  client.publish(topic, payload.c_str());

  client.subscribe("iot/commands");
  delay(5000);

}


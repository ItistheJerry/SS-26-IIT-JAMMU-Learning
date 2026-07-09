# IoT Security Vulnerability Analysis & Hardening

An in-depth security analysis and mitigation guide for a common, vulnerable ESP8266 IoT implementation. This repository breaks down five critical security flaws found in typical amateur firmware layouts—ranging from plaintext credential leakage to remote code execution risk—and demonstrates how to harden the codebase using **TLS encryption**, **MQTT authentication**, and strict **credential isolation**.

---

## 🚫 The Vulnerable Architecture

Below is the baseline code layout frequently used during rapid prototyping. While functional, it exposes the device, its data, and its host network to severe exploitation vectors.

```cpp
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

```

---

## 🔍 Vulnerability Deep-Dive

### 1. Hardcoded Wi-Fi Credentials in Source Code

* **Impact:** Pushing scripts containing hardcoded credentials to code repositories (even private ones that could accidentally become exposed) risks immediate compromise. Automated bots continuously crawl source control networks looking for secrets.
* **Exploitation:** Attackers can breach the local Wi-Fi parameter boundary, sniff neighboring local traffic, launch mid-point network anomalies, or pivot cleanly across additional infrastructure shares utilizing common passphrases.
* **Severity:** 🔴 **HIGH**

### 2. Connecting to Unsecured/Public Wi-Fi Networks

* **Impact:** Public access points lack localized radio-layer encryption between client systems and the router node.
* **Exploitation:** Any machine within transmission range can passively capture payload frames using packet analyzers like Wireshark. Devices also become highly susceptible to "Evil Twin" hotspots broadcasting identical SSIDs (`PublicWiFi`) to capture upstream data pipelines.
* **Severity:** 🔴 **HIGH**

### 3. Unauthenticated MQTT via Plaintext Port 1883

* **Impact:** Direct connection calls targeting public MQTT brokers over standard port `1883` send information across the open internet without transport-layer encryption or token verification checks.
* **Exploitation:** Threat actors can listen onto systemic topics globally to monitor private structural operations or broadcast spoofed metrics directly into the broker stream to distort cloud processing tables.
* **Severity:** 🔥 **CRITICAL**

### 4. Unvalidated Data Transmission Payload Structure

* **Impact:** Appending raw data strings blindly (`"temp=" + String(temp)`) provides zero payload checking, data source authenticity, or verification.
* **Exploitation:** Malicious packet manipulation can modify sensory metrics downstream to forge catastrophic sensor events or perform replay operations using outdated cache sets to deceive control modules.
* **Severity:** 🟡 **MEDIUM-HIGH**

### 5. Blind Execution of Incoming MQTT Commands

* **Impact:** Subscribing to open topic trees and feeding arbitrary strings directly into system execution parameters creates a severe **Remote Code Execution (RCE)** vector.
* **Exploitation:** Because the command channel utilizes an unauthenticated transport layer, anyone on the internet can broadcast malicious strings to `iot/commands`. Threat actors could reset memory systems, bypass sensors, or draft the ESP8266 into a malicious DDoS botnet cluster (e.g., Mirai).
* **Severity:** 🔥 **CRITICAL**

---

## 🛠️ Hardening & Mitigations

To remedy these security flaws, the architecture was revised through two major isolation upgrades.

### Fix 1: Credential Decoupling via `.gitignore`

To completely insulate configuration keys from source tracking, credentials are abstracted into a local configuration header file (`config.h`):

```cpp
#ifndef CONFIG_H
#define CONFIG_H

#define WIFI_SSID      "YourHomeWiFi"
#define WIFI_PASSWORD  "YourSecurePassword"
#define MQTT_USER      "your_mqtt_username"
#define MQTT_PASS      "your_mqtt_password"

#endif

```

Your system **`.gitignore`** profile must be updated before executing tracking commits to keep the configuration file localized to your machine:

```text
config.h

```

### Fix 2: Secure Mqtt Transport Architecture (TLS + Port 8883)

The upgraded main firmware shifts away from unsecured protocols. It updates standard TCP classes to use `WiFiClientSecure` to leverage **TLS Encryption**, shifts communications to port **8883**, enforces explicit broker authentication via security tokens, and encapsulates structural metrics safely into JSON structures:

```cpp
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

  // Note: For absolute production environment hardening, 
  // replace setInsecure() with secureClient.setTrustAnchors() using a known root certificate authority.
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

```

---

## 📊 Security Assessment Summary

| ID | Vulnerability | Severity | Mitigation Strategy |
| --- | --- | --- | --- |
| **1** | Hardcoded passwords in plain source | 🔴 **HIGH** | Move variables to hidden `config.h`, exclude via `.gitignore`. |
| **2** | Tracking over open public Wi-Fi profiles | 🔴 **HIGH** | Only interface via closed, encrypted private WPA2/WPA3 access points. |
| **3** | Unauthenticated MQTT traffic over port 1883 | 🔥 **CRITICAL** | Target port **8883** utilizing **TLS** encryption and explicit credential hashes. |
| **4** | Unencrypted / unvalidated data transmissions | 🟡 **MEDIUM** | Apply end-to-end transport encryption combined with structural JSON schema checks. |
| **5** | Blind execution of inbound topic commands | 🔥 **CRITICAL** | Implement strict whitelist sanitization, token validation, and authorization profiles. |

# IoT River Flood Monitoring System & Web Dashboard

An ESP32-based real-time flood monitoring and early warning system. By measuring the distance down to a water surface using an ultrasonic sensor, the system calculates rising water levels, handles transient surface anomalies with a rolling-average filter, triggers multi-tiered local audio-visual alerts, and hosts an interactive web dashboard with live Chart.js graphing.

---

## 🔌 Hardware Configuration

| Component | ESP32 Pin | Type | Notes / Description |
| --- | --- | --- | --- |
| **HC-SR04 TRIG** | `GPIO 5` | Digital Output | Initiates the ultrasonic ping cycle |
| **HC-SR04 ECHO** | `GPIO 18` | Digital Input | Measures time-of-flight echo return pulse |
| **Green LED** | `GPIO 25` | Digital Output | Status OK indicator (`NORMAL` level) |
| **Yellow LED** | `GPIO 26` | Digital Output | Warning indicator (`WARNING` level) |
| **Red LED** | `GPIO 27` | Digital Output | Critical hazard indicator (`CRITICAL` level) |
| **Active Buzzer** | `GPIO 32` | Digital Output | Emits intermittent alert cadences based on risk |

---

## 📐 Inverted Distance Logic & Threat Escalation

The ultrasonic sensor is mounted overhead, pointing downward at the water surface. **Therefore, as the water level rises, the measured distance decreases.**

```text
  [ Sensor Mounted Overhead ]  | (MAX Distance)
             |                 v
             |     ~~~~~ NORMAL LAYER ~~~~~~  (Distance > 30 cm)
             v     ~~~~~ WARNING LAYER ~~~~~  (15 cm < Distance <= 30 cm)
         [ Water ] ~~~~~ CRITICAL LAYER ~~~~  (Distance <= 15 cm)

```

The system evaluates raw data every **500 ms** using a **10-sample rolling average** to filter out momentary wave crests, surface ripples, or acoustic echo reflections.

| Alert Level | Condition (Distance to Water) | Active Indicator | Local Buzzer Behavior | Dashboard Styling |
| --- | --- | --- | --- | --- |
| **NORMAL** | `> 30 cm` | Green LED Only | Completely Silent | Stable Green Box |
| **WARNING** | `15 cm` to `30 cm` | Yellow LED Only | Slow Intermittent Beep (2s intervals) | Stable Orange Box |
| **CRITICAL** | `≤ 15 cm` | Red LED Only | Rapid Intermittent Beep (300ms intervals) | Blinking Red Box Alert |

---

## 🌐 Embedded Web Dashboard Architecture

The ESP32 acts as a self-contained web server (`WebServer server(80)`). It hosts an interactive dashboard directly from program flash memory—eliminating the need for external cloud database servers.

* **Main Interface (`/`):** Serves the responsive HTML/CSS skeleton preloaded with `Chart.js` via CDN.
* **Data Endpoint (`/data`):** Returns a clean JSON payload representing state metrics asynchronously requested by the webpage client script every 2000 ms:
```json
{"distance": 14.2, "level": "CRITICAL"}

```


* **Reversed Chart Scale:** The dashboard line chart intentionally **reverses the Y-axis**. This ensures that as distance drops, the data point climbs upward visually, mimicking the physical rise of the river level.

---

## 📁 Local Environment Setup (`config.h`)

Create a local header file named `config.h` in the root of your project sketch folder to store your localized network credentials safely:

```cpp
#ifndef CONFIG_H
#define CONFIG_H

#define WIFI_SSID     "YourWiFiSSID"
#define WIFI_PASSWORD "YourWiFiPassword"

#endif

```

---

## 📊 Console Diagnostics & Setup Logs

Open your IDE Serial Monitor at **115200 Baud** to track local operational logs.

```text
Connecting to WiFi..........
Connected! Dashboard: http://192.168.1.144

[FLOOD] Distance: 34.2 cm (avg) | Level: NORMAL
[FLOOD] Distance: 22.5 cm (avg) | Level: WARNING
[FLOOD] Distance: 12.1 cm (avg) | Level: CRITICAL
[ERROR] Sensor timeout

```

> ⚙️ **Simulation Note:** When running this code inside a virtualizer like **Wokwi**, click on the **HC-SR04** component block and use the interactive distance slider tool to adjust the simulated target distance and verify status escalations.

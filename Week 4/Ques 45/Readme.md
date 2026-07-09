# IoT Greenhouse Climate Control & Monitoring System

An ESP32-based automated greenhouse environment management framework. The system actively monitors ambient temperature, relative humidity, and solar exposure metrics, utilizing automated relay logic to regulate microclimates via heaters, ventilation fans, and supplementary grow lights. Telemetry is displayed locally on an auto-cycling I2C LCD and broadcasted continuously to a public MQTT broker for remote analytics dashboards.

---

## 🔌 Hardware Configuration

| Component | ESP32 Pin | Type | Purpose / Description |
| --- | --- | --- | --- |
| **DHT11 Sensor** | `GPIO 4` | Digital Input | Captures temperature and humidity levels |
| **LDR Module** | `GPIO 34` | Analog Input | Reads ambient solar/light intensities |
| **Relay 1 (Heater LED)** | `GPIO 25` | Digital Output | Drives a localized heating element |
| **Relay 2 (Fan LED)** | `GPIO 26` | Digital Output | Drives an air circulation/exhaust fan |
| **Relay 3 (Grow Light LED)** | `GPIO 27` | Digital Output | Actuates artificial supplemental grow lights |
| **LCD SDA** | `GPIO 21` | I2C Data | Interfacing lines for the 16x2 screen |
| **LCD SCL** | `GPIO 22` | I2C Clock | Interfacing lines for the 16x2 screen |

---

## ⚙️ Core Algorithmic Engineering

### 1. Bang-Bang Control with Deadband Hysteresis

To prevent rapid relay oscillation (chattering) that can prematurely wear down mechanical components, the environmental thresholds implement a ±1.0°C hysteresis buffer (`TEMP_HYST`):

* **Heating Loop:** Turns **ON** when temperature drops below `17.0°C` ($18.0^\circ\text{C} - 1.0^\circ\text{C}$) and shuts **OFF** once it climbs safely back over `18.0°C`.
* **Ventilation Loop:** Turns **ON** when temperature exceeds `23.0°C` ($22.0^\circ\text{C} + 1.0^\circ\text{C}$) and shuts **OFF** when it cools down beneath `22.0°C`.

### 2. Moving Average Filtering for LDR

Momentary shadow disruptions or environmental light anomalies can result in false sensor data. The code runs a **10-sample rolling array average** buffer on `GPIO 34`. Artificial lighting triggers smoothly only when the systemic moving average registers a drop under the hardcoded `LDR_THRESHOLD` value of `500`.

---

## 📁 Environment Setup (`config.h`)

To configure network connectivity, place a separate `config.h` header script within the root of your executable workspace path:

```cpp
#ifndef CONFIG_H
#define CONFIG_H

#define WIFI_SSID     "YourWiFiSSID"
#define WIFI_PASSWORD "YourWiFiPassword"

#endif

```

---

## 📊 System Displays & Output Telemetry

### 1. Local 16x2 LCD Display Execution

The layout sweeps sequentially through four status windows on a non-blocking **3-second interval cycle**:

```text
PAGE 0: Temperature     PAGE 1: Humidity        PAGE 2: Light Level     PAGE 3: Relay Array
+----------------+      +----------------+      +----------------+      +----------------+
|Temperature:    |      |Humidity:       |      |Light Level:    |      |Status:         |
|24.5 C   [FAN]  |      |63 %   [OK]     |      |412  Light:ON   |      |F L             |
+----------------+      +----------------+      +----------------+      +----------------+

```

### 2. Remote MQTT Architecture Structure

The application interfaces via unencrypted TCP port `1883` targeting `broker.hivemq.com`. Metrics are pushed outward every **10 seconds** across the following ecosystem topics:

```text
broker.hivemq.com/
  └── greenhouse/
        ├── temp       -> Live temperature value (Float string)
        ├── humidity   -> Live humidity percentage (Float string)
        ├── light      -> Calculated rolling average LDR value
        ├── heater     -> State indicator ("1" = Active / "0" = Inactive)
        └── fan        -> State indicator ("1" = Active / "0" = Inactive)

```

> 💡 **Integration Vector:** These topics can be mapped out instantly as standard visualization targets in tracking modules like HiveMQ Dashboards, Node-RED UI paths, or structured metrics aggregators such as Grafana.

### 3. Native Debug Console Output (115200 Baud)

```text
Connecting WiFi...... Connected!
[GH] T:16.4C H:62% LDR:310 | Heater:ON Fan:OFF Light:ON
[MQTT] Published all parameters.
[GH] T:18.2C H:61% LDR:520 | Heater:OFF Fan:OFF Light:OFF

```

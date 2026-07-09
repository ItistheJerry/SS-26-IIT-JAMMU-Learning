# Smart Home Air Quality Monitor

An ESP32-based multi-sensor environmental safety system designed to track indoor air quality, ambient temperature, and humidity. It features active multi-level audio-visual alerting and transmits real-time telemetry over Bluetooth (HC-05) to a remote device or terminal.

The firmware prioritizes non-blocking execution (`millis()` timing loops) to ensure the safety buzzer acts predictably while executing sensor read operations.

---

## 🔌 Pin Mapping & Circuit Layout

Connect your hardware components to the ESP32 according to the table below. Ensure appropriate current-limiting resistors are used where specified.

| Component | ESP32 Pin | Notes / Requirements |
| --- | --- | --- |
| **MQ-2 AOUT** | `GPIO 34` | Analog Input (Requires 12-bit ADC mapping) |
| **DHT11 DATA** | `GPIO 4` | Digital I/O |
| **Green LED** | `GPIO 27` | Safe status indicator (Use 220Ω resistor) |
| **Yellow LED** | `GPIO 26` | Warning status indicator (Use 220Ω resistor) |
| **Red LED** | `GPIO 25` | Danger status indicator (Use 220Ω resistor) |
| **Buzzer (+)** | `GPIO 32` | Piezo or Active Buzzer output |
| **HC-05 TX** | `GPIO 16` | Connects to ESP32 Hardware Serial 2 RX (`RX2`) |
| **HC-05 RX** | `GPIO 17` | Connects to ESP32 Hardware Serial 2 TX (`TX2`) |

---

## 🚦 Severity Threshold Logic

The firmware interprets air quality values ranging between **0 and 4095** (due to the ESP32's native 12-bit Analog-to-Digital Converter). System behavior is categorized into three specific modes:

| Severity Level | MQ-2 Sensor Range | LED Status | Buzzer Pattern | Bluetooth Telemetry Output |
| --- | --- | --- | --- | --- |
| **SAFE** | `< 300` | Green Only | Completely Silent | `SAFE|Gas=[val]|Temp=[val]C|Humidity=[val]%` |
| **MODERATE** | `300` to `599` | Yellow Only | Double Beep (Every 3 seconds) | `WARNING|Moderate Smoke Detected|Gas=[val]|Check Fireplace` |
| **DANGER** | `≥ 600` | Red Only | High-Frequency Rapid Toggle | `DANGER!!|Smoke Level Critical|Gas=[val]|Open Windows|...` |

> 💡 **Calibration Tip:** Depending on ambient background air or localized testing configurations (such as Wokwi simulation profiles), you may modify `SAFE_THRESHOLD` and `MODERATE_THRESHOLD` definitions directly inside the code to tweak baseline sensitivity.

---

## 📚 Software Dependencies

Ensure the following library is installed via the **Arduino Library Manager**:

* `DHT sensor library` by Adafruit (along with its underlying dependency `Adafruit Unified Sensor library`).

---

## 💻 Expected System Outputs

### 1. Serial Monitor (115200 Baud)

Prints formatted, comma-separated diagnostic telemetry once every second (`logInterval = 1000ms`).

```text
Timestamp, MQ-2 Value, DHT11 Temp, DHT11 Humidity, Severity Level
00:01, 220 ppm, 23.4C, 49%, SAFE
00:02, 280 ppm, 23.5C, 50%, SAFE
00:03, 420 ppm, 23.6C, 49%, MODERATE
00:04, 710 ppm, 23.8C, 48%, DANGER

```

### 2. Bluetooth Terminal (HC-05 Serial)

Transmits standard pipe-delimited (`|`) strings parsed natively by custom smartphone dashboards or remote central computing hubs.

```text
SAFE|Gas=220|Temp=23.4C|Humidity=49%
MODERATE|Moderate Smoke Detected|Gas=420|Check Fireplace
DANGER!!|Smoke Level Critical|Gas=710|Open Windows|Leave Room if Necessary

```

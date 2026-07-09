# Secure Intrusion Detection System with Telegram Alerts

An ESP32-powered smart security system designed to safeguard spaces (e.g., shops or restricted areas) during defined time frames. The device uses a passive infrared (PIR) sensor to detect motion and features a potentiometer to adjust baseline operational variables.

When movement is logged within the active monitoring schedule, the system initiates an automated escalation matrix—driving local audio-visual alerts (LEDs and a buzzer) while pushing immediate event notifications to your smartphone via a custom **Telegram Bot**.

---

## 🔌 Hardware Circuit Mapping

| Component | ESP32 Pin | Type | Notes / Details |
| --- | --- | --- | --- |
| **PIR Sensor OUT** | `GPIO 34` | Digital Input | Tracks movement flags inside the environment |
| **Potentiometer** | `GPIO 35` | Analog Input | Maps physical twist to sensitivity thresholds (`0-100%`) |
| **LED 1 (Warning)** | `GPIO 25` | Digital Output | Cycles during low-tier security exceptions |
| **LED 2 (Alarm)** | `GPIO 26` | Digital Output | Cycles during medium-tier escalation |
| **LED 3 (Urgent)** | `GPIO 27` | Digital Output | Triggers rapid strobe along with all channels on critical level |
| **Active Buzzer** | `GPIO 32` | Digital Output | Emits non-blocking progressive tone alerts |

---

## ⏱️ Threat Escalation Matrix

If a target maintains physical activity within the sensor's perimeter during protected operational hours, the code automatically escalates the warning response based on duration:

```text
[0s of Motion]            [10s of Motion]           [20s of Motion]
  WARNING                   ALARM                     URGENT
  - LED 1 Intermittent      - LED 2 Added             - All LEDs Flashing Rapidly
  - Slow Buzzer Beep        - Medium Buzzer Speed    - High-Frequency Strobe Buzz
  - Telegram Alert 1        - Telegram Alert 2        - Telegram Emergency Alert

```

* **Level 1: WARNING (`0s - 10s`):** Intermittent flash on LED 1; localized buzzer sounds a slow cadence; dispatches introductory Telegram warning.
* **Level 2: ALARM (`10s - 20s`):** LED 2 added to sequence; buzzer cycle frequency matches medium priority thresholds; sends secondary tracking notification.
* **Level 3: URGENT (`> 20s`):** Rapid, synchronized strobe across all three LEDs; buzzer switches to high-frequency oscillation; pushes urgent emergency alert over Telegram.

---

## 📁 Environment Configuration (`config.h`)

Create a local `config.h` configuration header file inside your primary workspace subdirectory to handle your secure network variables:

```cpp
#ifndef CONFIG_H
#define CONFIG_H

#define WIFI_SSID       "YourWiFi"
#define WIFI_PASSWORD   "YourPass"
#define BOT_TOKEN       "YOUR_TELEGRAM_BOT_TOKEN"
#define CHAT_ID         "YOUR_CHAT_ID"

#endif

```

> ⚙️ **Telegram Core Prerequisite:** Ensure the secure root CA profile configuration variables line up properly to avoid SSL handshake issues when transmitting requests directly to the secure API servers (`api.telegram.org`).

---

## ⌨️ Serial Monitor Control & Logging

You can update the armed timeframe dynamically using the **Serial Monitor** at a baud rate of **115200**.

### Diagnostic Input Commands

To change the protected hours window, type the following pattern inside the input string box:

* `SET_HOURS 22 06` ➡️ Arms the framework between **10:00 PM** and **6:00 AM** (Handles cross-midnight rollover cleanly).
* `SET_HOURS 08 18` ➡️ Arms the framework between **8:00 AM** and **6:00 PM**.

### Console Activity Layout Examples

```text
Connecting to WiFi.....
WiFi Connected!
Security system ARMED.

[MOTION] Detected at 22:14 | Sensitivity: 75% | Level: WARNING
[ESCALATION] Level: ALARM
[ESCALATION] Level: URGENT
[CMD] Active window set: 23:00 - 05:00

```

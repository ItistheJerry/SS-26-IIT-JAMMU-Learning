# Automated Plant Watering & Monitoring System

An ESP8266-powered IoT irrigation system that monitors soil moisture levels and light conditions (to detect rain/darkness), automates a water pump relay, displays metrics on an I2C LCD, and logs real-time telemetry directly to Google Sheets using Google Apps Script.

The system incorporates a hard 30-minute logging/checking interval to conserve resources, alongside a physical override button that forces a 1-minute watering cycle followed by a safety lockout period.

---

## 🔌 Circuit Pin Mapping

| Component | ESP8266 Pin | Type | Notes / Details |
| --- | --- | --- | --- |
| **Soil Moisture AOUT** | `A0` | Analog Input | Measures raw analog value, mapped internally `0–100%` |
| **LDR Module** | `D1` (GPIO 5) | Digital Input | Voltage divider tracking ambient light threshold (LOW = Rain/Dark) |
| **Relay Module** | `D2` (GPIO 4) | Digital Output | Switches water pump or indicator LED |
| **Manual Button** | `D5` (GPIO 14) | Digital Input | Configured with `INPUT_PULLUP`, triggers manual override |
| **LCD SDA** | `D6` (GPIO 12) | I2C Data | For 16x2 Character LCD Display |
| **LCD SCL** | `D7` (GPIO 13) | I2C Clock | For 16x2 Character LCD Display |

---

## 🛠️ System Thresholds & Parameters

* **Dry Threshold (`< 30%`):** Automatically triggers a **30-second** watering cycle unless a lockout or rain state is active.
* **Wet Threshold (`> 70%`):** Skips auto-watering and reports soil condition as optimized/wet.
* **Auto Check Interval (`30 Minutes`):** Sensor checking and remote data logging cycle length.
* **Manual Override:** Pressing the button at `D5` runs the pump for **60 seconds**, immediately followed by a **5-minute safety lockout** to prevent over-saturation.

---

## 📁 File & Cloud Setup

### 1. Local Configuration (`config.h`)

Create a file named `config.h` in your project folder alongside your primary `.ino` sketch:

```cpp
#ifndef CONFIG_H
#define CONFIG_H

#define WIFI_SSID     "YourWiFiName"
#define WIFI_PASSWORD "YourWiFiPass"
#define SHEET_URL     "https://script.google.com/macros/s/YOUR_SCRIPT_ID/exec"

#endif

```

### 2. Cloud Logging Setup (Google Apps Script)

To log metrics securely to Google Sheets without needing external heavy MQTT brokers:

1. Create a new Google Sheet and copy its **Spreadsheet ID** from the URL bar.
2. Navigate to [script.google.com](https://script.google.com) and create a **New Project**.
3. Paste the following Google Apps Script into your editor, replacing `"YOUR_SHEET_ID"` with your actual spreadsheet ID:

```javascript
function doGet(e) {
  var sheet = SpreadsheetApp.openById("YOUR_SHEET_ID").getActiveSheet();
  var timestamp = new Date();
  var moisture  = e.parameter.moisture;
  var rain      = e.parameter.rain == "1" ? "YES" : "NO";
  var pump      = e.parameter.pump  == "1" ? "YES" : "NO";

  sheet.appendRow([timestamp, moisture + "%", rain, pump]);
  return ContentService.createTextOutput("OK");
}

```

4. Click **Deploy** ➡️ **New Deployment**.
5. Select **Web App** as the deployment type.
6. Configure execution permissions:
* **Execute as:** `Me`
* **Who has access:** `Anyone`


7. Authorize access, copy the generated **Web App URL**, and paste it into your `config.h` file.

---

## 📊 Output Behaviors

### LCD Display Output Format

The display shows live moisture content, operational logic mode, and calculated minutes since the pump last cycled.

```text
+----------------+
|M:28% AUTO-WATER|
|Last: 0min ago  |
+----------------+

```

### Remote Spreadsheet Logging Target

Data appended to your target Google Sheet profile appears in rows with chronological layout processing:

| Timestamp | Soil Moisture | Rain | Pump Activated |
| --- | --- | --- | --- |
| `09/07/2026 12:40:12` | 25% | NO | YES |
| `09/07/2026 13:10:15` | 65% | YES | NO |
| `09/07/2026 13:40:18` | 78% | NO | NO |

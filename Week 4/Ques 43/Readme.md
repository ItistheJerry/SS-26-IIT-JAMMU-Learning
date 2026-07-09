# Smart Door Lock with Two-Factor OTP Authentication

An ESP32-based secure access control system that implements two-factor authentication (2FA). Users enter a **4-digit ID** on a physical Matrix Keypad, which prompts the system to dynamically generate a **6-digit random One-Time Password (OTP)**. The OTP is transmitted wirelessly via Bluetooth (HC-05) to the user's authorized phone/terminal and must be typed in within a strict **30-second window** to actuate the door servo mechanism.

---

## 🔌 Hardware Circuit Mapping

Ensure your physical or simulated components are mapped to the ESP32 GPIO channels as defined below:

| Component | ESP32 Pin | Type | Notes / Details |
| --- | --- | --- | --- |
| **Keypad Row 1–4** | `GPIO 13`, `12`, `14`, `27` | Digital Input | Internal pull-ups configured by library |
| **Keypad Col 1–4** | `GPIO 26`, `25`, `33`, `32` | Digital Output | Scanned systematically for column state |
| **LCD SDA** | `GPIO 21` | I2C Data | Standard ESP32 I2C bus |
| **LCD SCL** | `GPIO 22` | I2C Clock | Standard ESP32 I2C bus |
| **HC-05 TX** | `GPIO 16` | Hardware Serial 2 RX | Connects to Bluetooth Transmit line (`RX2`) |
| **HC-05 RX** | `GPIO 17` | Hardware Serial 2 TX | Connects to Bluetooth Receive line (`TX2`) |
| **Servo Signal** | `GPIO 18` | PWM Output | Drives positional servo mechanism |

---

## ⚙️ Finite State Machine (FSM) Workflow

The control code relies on an explicit operational finite state machine architecture (`State` enum):

```text
       +---------------+
-----> |    WAIT_ID    | <------------------------------------+
       +---------------+                                      |
               |                                              |
               | [User enters 4-digit ID]                     | [OTP Expires OR Auth Finished]
               v                                              |
       +---------------+                                      |
       |   WAIT_OTP    | -------------------------------------+
       +---------------+

```

1. **`WAIT_ID` (Initialization State):** The system prompts the user to input a 4-digit ID. Each button press prints a masked symbol (`*`) onto the I2C LCD screen for localized visual privacy.
2. **OTP Generation & Dispersal:** Once the 4th digit is registered, the ESP32 samples noise via an unconnected analog pin (`analogRead(0)`) to generate a unique cryptographically pseudo-random 6-digit passcode. This is pushed immediately over the Bluetooth serial layer.
3. **`WAIT_OTP` (Verification State):** The display transitions into a countdown layout showing the 30-second remaining timeout window.
* **Success:** If the entered string completely matches the system variant, the servo sweeps cleanly from `0°` (Locked Position) to `90°` (Unlocked Position) for **5 seconds** before resetting.
* **Failure / Expiration:** If the timer reaches 0 or an invalid code configuration is confirmed, access is denied and the parameters wipe cleanly back to initialization constraints.



---

## 📚 Library Requirements

The software relies on standard ecosystem dependencies. Install these using your IDE library manager:

* **`Keypad`** by Mark Stanley, Alexander Brevig
* **`LiquidCrystal_I2C`** by Frank de Brabander
* **`ESP32Servo`** by Kevin Harrington (ensures stable hardware PWM timer maps across ESP32 cores)

---

## 📊 System Execution Output Formatting

### 1. Hardwired Serial Diagnostics (115200 Baud)

```text
[LOG] ID entered: 1234
[LOG] OTP generated: 847291
[LOG] OTP entered: 847291 | Expected: 847291 | Result: SUCCESS | ID: 1234
[LOG] OTP entered: 111111 | Expected: 847291 | Result: FAILURE | ID: 5678
[LOG] OTP expired, ACCESS DENIED

```

### 2. Bluetooth Terminal Output

```text
Your OTP: 847291 (valid 30s)

```

---

## ⌨️ Interface Utility Note

* Use the numbers `0–9` to log information into the buffer fields.
* The asterisk key (`*`) serves as a standard **Backspace** key across both programmatic states, allowing you to slice mistyped indices out of memory dynamically before final verification thresholds are breached.

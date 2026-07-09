# IoT & Embedded Systems Portfolio

This repository serves as a comprehensive, multi-module portfolio documenting my engineering journey from embedded systems theory to production-ready IoT implementations. It aggregates a series of distinct micro-controller applications that solve real-world problems in environmental monitoring, security, healthcare, and automation.

---

## 📁 What is inside this Folder?

The workspace is organized into separate development subdirectories, each containing fully documented source code (`.ino`), configuration files, and localized asset streams:

* **`01-smart-irrigation/`** – An automated crop watering node using soil moisture thresholds, an LDR rain-sensor override, and asynchronous telemetry logging directly to Google Sheets via Google Apps Script.
* **`02-smart-doorlock/`** – A responsive, state-machine-driven two-factor authentication (2FA) door lock that generates dynamic, random 6-digit OTPs and broadcasts them via Bluetooth (HC-05) to an authorized device.
* **`03-intrusion-detector/`** – A secure armed perimeter monitor using a PIR sensor, a calibration potentiometer, and a multi-tiered progressive alert system that routes instant warning messages over a Telegram Bot pipeline.
* **`04-greenhouse-control/`** – A climate-stabilizing environment manager utilizing a DHT11 sensor to actuate a 3-relay array (heater, fan, grow light) via stable bang-bang control logic.
* **`05-flood-monitor/`** – An overhead river water-level tracking node that hosts an internal, self-contained web server to render an interactive, real-time `Chart.js` dashboard for remote monitoring.
* **`06-medical-monitor/`** – A dual-mode vital tracking platform capable of toggling between live I2C medical hardware (MAX30102) and an analog LDR hardware-in-the-loop (HIL) simulation.
* **`07-security-hardening/`** – A production-hardened reference implementation demonstrating the migration of legacy, vulnerable IoT architecture over to encrypted MQTTS (Port 8883) with TLS mutual authentication.

---

## 🧠 Key Engineering Takeaways (What I Learnt)

Building this portfolio pushed me to shift from a high-level tinkerer to an intentional embedded systems programmer. The core architectural lessons include:

### 1. Asynchronous, Non-Blocking Architecture

* **The Lesson:** Relying on linear execution models like `delay()` is catastrophic for real-time systems. It blocks processor execution, drops sensor packets, and causes physical inputs (like a keypad or a web request) to freeze.
* **The Solution:** I mastered the use of clock comparisons via `millis()`. This allows separate tasks—such as monitoring countdown timers, scanning hardware matrices, sampling sensors, and updating LCDs—to run concurrently without interfering with one another.

### 2. Digital Signal Smoothing & Noise Filtering

* **The Lesson:** Real-world sensors are inherently noisy. Environmental vibrations, surface ripples on liquids, and transient shadows create erratic data spikes that cause false alarms in volatile logic structures.
* **The Solution:** I learned to implement **10-sample rolling average array filters** directly on analog and digital data streams to smoothly bridge transitions and ensure data integrity before execution.

### 3. Mechanical Component Insulation via Hysteresis

* **The Lesson:** Simple threshold boundaries (e.g., *turn fan on if temperature > 22°C*) introduce severe, high-frequency relay oscillation right at the critical boundary point, quickly ruining expensive mechanical actuators.
* **The Solution:** I integrated **deadband hysteresis buffers ($\pm1.0^\circ\text{C}$)** into control loops, effectively acting as an engineering dampener to stabilize activation and deactivation cycles.

### 4. Enterprise-Grade Security Hardening

* **The Lesson:** Treating credentials casually by hardcoding plain-text strings inside main files leaves production architectures deeply vulnerable to bot scrapers, man-in-the-middle sniffing, or remote code execution (RCE) takeovers.
* **The Solution:** I established strict credential decoupling by separating API tokens, Wi-Fi parameters, and private encryption keys into standalone `config.h` files completely omitted from version control tracking via `.gitignore`. Furthermore, I upgraded legacy pipelines from plaintext transport loops over to **TLS-encrypted communication channels (Port 8883)**.

### 5. Systematic Version Control & Documentation

* **The Lesson:** Dumping massive, monolithic chunks of code at the end of a long sprint makes codebases brittle and hard to debug when regression failures occur.
* **The Solution:** I adopted an atomic Git commit discipline—writing precise, descriptive commit summaries after implementing each localized feature block. This drastically accelerated system diagnostic routines and layout backtracking.

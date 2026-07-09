# Embedded IoT Systems & Micro-Climate Engineering Portfolio

Welcome to my comprehensive IoT Engineering portfolio. This repository documents a journey through the structural transition from embedded systems theory to practical, production-ready implementation.

The projects detailed below cover fundamental IoT concepts: from REST API consumption and non-blocking state machine design to dynamic data visualization, secure transport architecture, and edge-calculated mesh networking.

---

## 🚀 Projects Overview & Practical Realizations

Throughout this curriculum, I designed, built, and calibrated four distinct micro-controller applications targeting specific automation, tracking, and communication challenges.

### 1. Hybrid REST API & Physical DHT11 Weather Node

* **Objective:** Built a system to parse external live cloud weather metrics alongside local atmospheric data.
* **Engineering Takeaway:** Transitioning from theory to real-world deployment exposed the brittle nature of static JSON parsing. When external payloads changed dynamically at runtime, handling document buffers safely via `ArduinoJson` forced a strict reliance on explicit memory allocation schemas and conditional type-casting.

### 2. Live Chart.js Flood Detection Monitoring Node

* **Objective:** Implemented an overhead ultrasonic sensor (`HC-SR04`) matrix to measure water height profiles, featuring an asynchronous self-contained web server hosted directly on an ESP32.
* **Engineering Takeaway:** Learned to employ a **10-sample rolling average filter** directly on incoming ADC data streams. This cleanly mitigated systemic measurement spikes caused by mechanical vibration and surface ripples, preventing false telemetry triggers.

### 3. Responsive Bluetooth OTP Smart Door Lock

* **Objective:** Programmed a secure two-factor authentication (2FA) door actuator that couples physical keypad inputs with dynamically generated random 6-digit One-Time Passwords routed over Bluetooth.
* **Engineering Takeaway:** Standard blocking mechanisms (`delay()`) freeze input loop polling. Overhauling the system using asynchronous clock comparisons (`millis()`) allowed the system to smoothly run down a 30-second timeout window while remaining fully responsive to keypad entries.

### 4. Hysteresis-Driven Greenhouse Micro-Climate Controller

* **Objective:** Engineered a robust, automated climate environment controller running a triple-relay array to actuate ventilation fans, heating pads, and artificial grow lamps.
* **Engineering Takeaway:** Applied bang-bang control mechanisms stabilized by a **$\pm1.0^\circ\text{C}$ deadband hysteresis buffer**. This explicitly prevents high-frequency relay chatter, protecting sensitive mechanical power components from premature structural failure.

---

## 🧠 Core Engineering Principles Learned

* 📉 **Reliability Over "Happy-Path" Functionality:** True IoT design shines under failure states. Codebases must elegantly handle intermittent Wi-Fi drops, deep packet loss, noisy sensor data lines, and broker timeouts without throwing fatal hardware faults.
* 🛡️ **Defensive Credential Management:** Writing security vulnerability reports highlighted the risk of leaving configuration arrays hardcoded inside plain main files. Production setups require a dedicated, environment-isolated `config.h` configuration script protected by comprehensive `.gitignore` exclusions.
* 🔄 **Asynchronous Task Architecture:** Replacing linear execution models with non-blocking, interval-driven `millis()` loops ensures high-performance tracking and real-time execution across multiple peripheral interfaces simultaneously.
* 📦 **Git Commit Discipline:** Shifted from monolithic "end-of-project" code dumps to clear, atomized feature-based commits. This structured version control drastically reduces debugging times when tracing regressions.

---

## 🔮 Next-Generation Architecture: AWATS (Airborne Weather Analysis & Trail System)

Building upon these embedded milestones, my next project shifts toward atmospheric boundary-layer profiling via an active, low-altitude airborne sensor network.

### 1. The Core Problem & Value Proposition

Ground-based meteorological instrumentation arrays suffer from regional sparsity and a fundamental structural limitation: they are blind to hyper-local vertical atmospheric gradients. **AWATS** resolves this by establishing a continuous vertical trail of data nodes, capturing micro-climate variations (such as thermal inversions, wind shear, and pollution pockets) that standard terrestrial networks cannot detect.

### 2. Hardware Topology & Node Design

Because payload components operate under strict aerodynamic and buoyancy constraints, weight distribution and low power draws are highly optimized.

* **Airborne Platform:** Hybrid high-tensile helium *helikites* or tethered aerodynamic blimp envelopes. These platforms leverage static lift aerodynamics, requiring zero operating current to maintain persistent elevation.
* **Microcontroller:** `ESP32-S3` or `STM32WB` systems executing ultra-low-power sleep states, utilizing dual-core configurations to isolate sensor ingestion pipelines from data transmission threads.
* **Sensor Payload Array:**
* **BME280 / BME680:** Direct tracking for pressure, ambient humidity, temperature, and Volatile Organic Compounds ($VOCs$).
* **Solid-State Ultrasonic Anemometer:** Lightweight, non-mechanical wind speed and directional tracking to avoid mechanical wear at high altitudes.
* **OPT3001 Sensor:** Measures real-time solar irradiance profiles and micro-layer cloud density configurations.


* **Power Management Architecture:** Ultra-thin flexible solar film matrices wrapped along the upper surface of the envelope shell, governed by a specialized energy-harvesting IC to maintain a 3.7V LiPo reservoir indefinitely during day/night cycles.

### 3. Edge-Network & Communication Pipeline

```text
 [Airborne Node 3: 200m]
           |
     (LoRa P2P Link)
           v
 [Airborne Node 2: 100m]
           |
     (LoRa P2P Link)
           v
 [Airborne Node 1: 50m]  --(Line-of-Sight LoRa)-->  [Ground Base Gateway / Raspberry Pi]
                                                             |
                                                    (Mosquitto MQTT Broker)
                                                             |
                                                    (Secure TLS Bridge)
                                                             |
                                                             v
                                                    [AWS IoT Core Pipeline]
                                                             |
                                         +-------------------+-------------------+
                                         |                                       |
                                         v                                       v
                             [InfluxDB Time-Series]                     [Amazon S3 Cold Storage]
                                         |                                       |
                                         +-------------------+-------------------+
                                                             |
                                                             v
                                                 [Grafana 3D Vertical UI]

```

* **Air-to-Ground Link:** Transceivers run low-power, long-range **LoRa (868/915 MHz)** point-to-point connections. Direct line-of-sight conditions enable clear, reliable link ranges of 10–15 km at minimal power configurations ($<25\text{mW}$).
* **Topology:** A vertical daisy-chained "trail" network. High-altitude sensor arrays route payloads down through mid-level nodes to aggregate data at a centralized ground gateway.

### 4. Ground Station Analytics & Automated Alert Engine

* **Edge Processing:** A ground-based Raspberry Pi gateway intercepting raw LoRa packet data streams. The gateway decodes data frames locally, running real-time edge processing algorithms to calculate wind shear vectors and localized dew points before routing data upstream.
* **Cloud Ingestion:** Data packets are structured into compressed JSON schemas, passing over a local Mosquitto MQTT broker before bridging securely to **AWS IoT Core** using strict mutual TLS authentication.
* **Storage & Visualization Layers:**
* **InfluxDB:** Ingests real-time, time-series telemetry streams.
* **AWS S3:** Serves as a historical storage repository for long-term climate modeling.
* **Grafana Dashboard:** Renders interactive, 3D atmospheric gradient visualizations mapping environmental shifts against exact node altitudes.


* **Automated Alerting Engine:** If barometric pressure drops rapidly ($>3\text{ hPa}$ within a 3-hour window), an integrated edge service triggers automated alert frameworks via **Telegram/Discord Webhooks** to push immediate micro-climate warnings to regional drone pilots, agricultural managers, and emergency services.

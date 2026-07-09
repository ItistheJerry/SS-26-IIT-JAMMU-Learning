Heart Rate & SpO2 Medical Monitor (Simulation & Hardware)
An ESP32-based medical monitoring firmware designed to track Heart Rate (HR) and Blood Oxygen Saturation (SpO 
2
​
 ). It includes a conditional compile flag allowing users to toggle between standard medical hardware interaction or a hardware-free behavioral simulation using a Light Dependent Resistor (LDR).

The system computes a moving average over a 5-sample buffer to smooth signal transitions and triggers a physical alert LED whenever vitals cross clinical abnormality thresholds.

🔌 Circuit Pin Configurations
The firmware supports two mutually exclusive wiring topologies based on the definition of the SIMULATE_WITH_LDR compiler directive inside the main script.

Option A: Hardware Mode (MAX30102 Sensor)
Uncomment/remove #define SIMULATE_WITH_LDR to run live I2C sensor diagnostics.

Component	ESP32 Pin	Type	Notes / Details
MAX30102 SDA	GPIO 21	I2C Data	Hardware I2C bus pull-up recommended
MAX30102 SCL	GPIO 22	I2C Clock	Hardware I2C bus pull-up recommended
MAX30102 VIN	3.3V	Power	Connect to ultra-low-noise output pin if possible
MAX30102 GND	GND	Ground	Common ground
Red Alert LED	GPIO 25	Digital Output	Active HIGH visual alert indicator
Option B: Simulation Mode (LDR Module)
Keep #define SIMULATE_WITH_LDR active. Ideal for virtual environments like Wokwi.

Component	ESP32 Pin	Type	Notes / Details
LDR Pin	GPIO 34	Analog Input	Voltage divider to GND (ESP32 ADC1 channel)
Red Alert LED	GPIO 25	Digital Output	Active HIGH visual alert indicator
🩺 Clinical Thresholds & Patient Diagnostics
The monitoring software continuously parses the smoothed 5-sample moving average and classifies medical states according to standard triage indicators:

Patient Status	Heart Rate Condition	SpO 
2
​
  Condition	Alert LED	Clinical Interpretation
NORMAL	50≤HR≤120 bpm	≥94%	OFF	Stable patient baseline
BRADYCARDIA	<50 bpm	Any	ON	Abnormally slow resting heart rate
TACHYCARDIA	>120 bpm	Any	ON	Abnormally elevated resting heart rate
LOW SPO2	Any	<94%	ON	Hypoxia risk/Low blood oxygen level
🎮 Simulation Logic (Wokwi Context)
When operating under Option B (LDR Simulation Mode), the internal logic maps ambient light levels to mock biometric ranges:

Covering the LDR (Dark / Finger Placed): Simulates low analog input, mapping values toward bradycardia/hypoxia levels to test execution vectors.

Exposing the LDR (Bright): Generates steady, mathematically constrained standard biometric numbers.

Signal Noise Jitter: Minor random variations (±2 bpm HR / ±1% SpO 
2
​
 ) are injected programmatically to simulate organic real-world telemetry noise, which is stabilized cleanly by the 5-reading rolling average.

📚 Library Dependencies
When executing in Option A (Real Sensor) mode, ensure the following modules are added to your workspace compilation dependencies:

SparkFun MAX3010x Pulse Oximeter Library

📊 Console Diagnostics & CSV Data Logging
The system pushes structured comma-separated data to the console every 2 seconds alongside human-readable diagnostic layouts.

Exporting logs to health_log.csv
The raw lines printed to the console are fully CSV-compliant. You can easily highlight, copy the text out of the Serial Monitor terminal, paste it directly into an empty file, and save it as health_log.csv for analysis in Excel or Python.

Terminal Formatting Output Example
[MODE] LDR Simulation Mode
Move the LDR slider in Wokwi to simulate different readings.

Timestamp(ms), HR(bpm), SpO2(%), Status
2000, 78, 98, NORMAL
-----------------------------
  Heart Rate : 78 bpm
  SpO2       : 98 %
  Status     : NORMAL
-----------------------------
4000, 124, 96, TACHYCARDIA
-----------------------------
  Heart Rate : 124 bpm
  SpO2       : 96 %
  Status     : TACHYCARDIA
  ALERT! Red LED ON
-----------------------------
6000, 72, 91, LOW SPO2
-----------------------------
  Heart Rate : 72 bpm
  SpO2       : 91 %
  Status     : LOW SPO2
  ALERT! Red LED ON
-----------------------------
-----------------------------

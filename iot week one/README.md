# Week 1: 
**Course:** IoT & Drones(IIT Jammu Summer School 2026)  
**Student Name:** Apoorv Shivam  

---

## 📅 Weekly Overview
The first week of the program focused on setting up the core software foundations for the Arduino microcontroller platform, understanding digital output execution, designing dynamic multiplexed arrays, configuring basic analog sensor networks, and simulating multi-variable coordinate spaces. 

---

## 📂 Laboratory Subdirectories

### 1. 💡 LED Blink (`/led_blink`)
* **Project Type:** Hardware Core Output
* **Core Concepts:** Digital GPIO initialization, `pinMode()` declaration configurations, hardware current-limiting tracking, and fundamental processor delay blocks.
* **System Execution:** Operates as a foundational diagnostic test, toggling a physical digital load state high and low at explicit $1\text{ second}$ operational intervals.

### 2. 🔠 5x5 LED Matrix Display (`/led_matrix_5x5`)
* **Project Type:** Advanced Multiplexed Peripheral Layout
* **Core Concepts:** Common-anode row matrix architectures, 2D font mapping arrays, rapid microsecond row scanning sweeps, and high-speed multi-pin coordination.
* **System Execution:** Sequentially renders font characters A through Z via precise bitwise extractions from binary array data, incorporating microsecond state resets to prevent overlapping display artifacts.

### 3. 🗺️ Sensor Matrix Logic Simulation (`/sensor_matrix_logic`)
* **Project Type:** Core Computational Logic
* **Core Concepts:** Multi-dimensional tracking layout spaces, multi-index loop parameters, conditional bracket indexing offsets, and serial terminal printing layout structures.
* **System Execution:** Executes inside the processor setup envelope, printing a cleanly structured 4x3 multi-node IoT sensor array coordinate layout pattern down to the serial data bus monitor once upon initialization.

### 4. 🌙 Smart Street Light Controller (`/smart_street_light`)
* **Project Type:** Analog Sensor Threshold Automation
* **Core Concepts:** Photoresistor (LDR) sensor voltage divider networks, continuous analog stream polling (`analogRead`), real-time serial logging arrays, and hardware automated threshold triggers.
* **System Execution:** Samples ambient environmental lux changes. When local readings fall below or equal a constant threshold variable ($\le 300$), the processor triggers an automation pin to power an LED street light source.

---

## 🛠️ Hardware Stack & Circuit Layout Fundamentals

### Power Distribution
Every circuit this week links standard $5\text{V}$ and $\text{GND}$ output bus channels directly from the Arduino microcontroller board down across the primary breadboard common power rails.

### Component Implementations
* **Resistors:** Clean $220\,\Omega$ resistance configurations protect individual LED junctions against catastrophic thermal failures. Fixed $10\text{k}\Omega$ resistors act as pull-down elements in voltage divider sensor sub-circuits to avoid floating pin reads.
* **Sensors:** Cadmium-sulfide photoresistors vary their raw internal resistance parameters based on changing external lux concentrations, creating a shifting output voltage mapped by the internal Analog-to-Digital Converter (ADC).

---

## 🚀 General Execution Blueprint

### Running the Code in Tinkercad
1. Navigate inside any target sub-module folder above and copy the localized `.ino` hardware file text code.
2. Launch your web workspace, select the circuit module, and paste the code inside the Text Editor section.
3. Tap **Start Simulation** and click open the bottom **Serial Monitor** tab to monitor structural telemetry frames.

### Flashing Code to Desktop Hardware
1. Establish a secure interface line between your physical Arduino board and your laptop using an appropriate USB cable.
2. Launch the Arduino IDE desktop client and populate a empty project container sketch with the target source module.
3. Access **Tools** to set your board definition to **Arduino Uno** and configure your active tracking interface **COM Port**.
4. Press **Verify/Compile** to clear syntax errors, then click **Upload** to write the binary image to the microcontroller's flash memory.

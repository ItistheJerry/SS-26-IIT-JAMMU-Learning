IoT & Drones-IIT JAMMU SS Internship 2026
This repository contains my projects and code from the IoT & Drones SS Internship Program at IIT Jammu (2026).

About Me
My name is Samyak Jain.
I am a Recent BCA Graduate from the Mahaveer College Affiliated from Rajasthan University
Jaipur, Rajasthan.

# Repository Overview

Every project listed here features fully tested, working code along with clear circuit layouts that work perfectly on both real Arduino hardware and Tinkercad simulations.

## 📂 Understanding the Repository Structure

To navigate this portfolio easily, here is how my work is organized:

* **Root Directory (`/`):** This main landing page acts as the central index and syllabus guide.
* **Weekly Folders (`/week1`, `/week2`):** These hold the master summary reports for each specific week of the curriculum.
* **Project Sub-folders (e.g., `/led_blink`, `/traffic_light`):** Inside each weekly folder, every assignment has its own dedicated directory containing the raw working source code (`.ino` file) and a detailed step-by-step project report (`README.md`).

---

# Weekly Progress

## Week 1

* **Course:** IoT & Drones (IIT Jammu Summer School 2026)
* **Student Name:** Apoorv Shivam

### 📅 Weekly Overview
The first week of the program focused on setting up the core software foundations for the Arduino microcontroller platform, understanding digital output execution, designing dynamic multiplexed arrays, configuring basic analog sensor networks, and simulating multi-variable coordinate spaces.

### 📂 Laboratory Subdirectories

#### 1. 💡 LED Blink (`/led_blink`)
* **Project Type:** Hardware Core Output
* **Core Concepts:** Digital GPIO initialization, `pinMode()` declaration configurations, hardware current-limiting tracking, and fundamental processor delay blocks.
* **System Execution:** Operates as a foundational diagnostic test, toggling a physical digital load state high and low at explicit 1-second operational intervals.

#### 2. 🔠 5x5 LED Matrix Display (`/led_matrix_5x5`)
* **Project Type:** Advanced Multiplexed Peripheral Layout
* **Core Concepts:** Common-anode row matrix architectures, 2D font mapping arrays, rapid microsecond row scanning sweeps, and high-speed multi-pin coordination.
* **System Execution:** Sequentially renders font characters A through Z via precise bitwise extractions from binary array data, incorporating microsecond state resets to prevent overlapping display artifacts.

#### 3. 🗺️ Sensor Matrix Logic Simulation (`/sensor_matrix_logic`)
* **Project Type:** Core Computational Logic
* **Core Concepts:** Multi-dimensional tracking layout spaces, multi-index loop parameters, conditional bracket indexing offsets, and serial terminal printing layout structures.
* **System Execution:** Executes inside the processor setup envelope, printing a cleanly structured 4x3 multi-node IoT sensor array coordinate layout pattern down to the serial data bus monitor once upon initialization.

#### 4. 🌙 Smart Street Light Controller (`/smart_street_light`)
* **Project Type:** Analog Sensor Threshold Automation
* **Core Concepts:** Photoresistor (LDR) sensor voltage divider networks, continuous analog stream polling (`analogRead`), real-time serial logging arrays, and hardware automated threshold triggers.
* **System Execution:** Samples ambient environmental lux changes. When local readings fall below or equal a constant threshold variable ($\le 300$), the processor triggers an automation pin to power an LED street light source.

### 🛠️ Hardware Stack & Circuit Layout Fundamentals

#### Power Distribution
Every circuit this week links standard **5V** and **GND** output bus channels directly from the Arduino microcontroller board down across the primary breadboard common power rails.

#### Component Implementations
* **Resistors:** Clean **220 $\Omega$** resistance configurations protect individual LED junctions against catastrophic thermal failures. Fixed **10k $\Omega$** resistors act as pull-down elements in voltage divider sensor sub-circuits to avoid floating pin reads.
* **Sensors:** Cadmium-sulfide photoresistors vary their raw internal resistance parameters based on changing external lux concentrations, creating a shifting output voltage mapped by the internal Analog-to-Digital Converter (ADC).

### 🚀 General Execution Blueprint

#### Running the Code in Tinkercad
1. Navigate inside any target sub-module folder above and copy the localized `.ino` hardware file text code.
2. Launch your web workspace, select the circuit module, and paste the code inside the **Text Editor** section.
3. Tap **Start Simulation** and click open the bottom **Serial Monitor** tab to monitor structural telemetry frames.

#### Flashing Code to Desktop Hardware
1. Establish a secure interface line between your physical Arduino board and your laptop using an appropriate USB cable.
2. Launch the Arduino IDE desktop client and populate an empty project container sketch with the target source module.
3. Access **Tools** to set your board definition to **Arduino Uno** and configure your active tracking interface **COM Port**.
4. Press **Verify/Compile** to clear syntax errors, then click **Upload** to write the binary image to the microcontroller's flash memory.

---

## Week 2

### 📅 Weekly Overview
The second week of the curriculum shifted focus from core digital/analog primitives to advanced software architecture patterns, low-power processing frameworks, hardware protocol implementations (I2C, SPI), and maximizing hardware resource interfaces. The exercises focused on designing interactive loops, asynchronous event listening, state-machine tracking, and dual-node distributed tasks.

### 📂 Projects

#### 1. 🎹 Digital Piano (`/digital_piano`)
* **Project Type:** Interactive Audio Processing
* **Core Concepts:** Multi-button array interaction pooling, dynamic tone generation, frequency mapping vectors, and active buzzer hardware driving.
* **System Execution:** Scans a series of button inputs, outputting dedicated audio frequency pulse waveforms directly to a piezo transducer element when pressed.

#### 2. 💤 ESP32 Deep Sleep (`/esp32_deep_sleep`)
* **Project Type:** Advanced Low-Power Management
* **Core Concepts:** Hardware sleep timers, power rail shutdown profiles, and state preservation utilizing non-volatile `RTC_DATA_ATTR` memory blocks.
* **System Execution:** Developed inside the Velxio platform. Configures a 5-second sleep timer wakeup source, spinning down core execution arrays while securely incrementing a boot count variable inside fast RTC memory registers across reboots.

#### 3. 📺 I2C LCD Interfacing (`/i2c_lcd_display`)
* **Project Type:** Synchronous Bus Peripheral Control
* **Core Concepts:** Inter-Integrated Circuit (I2C) serial protocol, 2-wire data lines (SDA/SCL), device hexadecimal address configuration, and character liquid crystal rendering.
* **System Execution:** Routes strings cleanly over a shared 2-wire serial line to print string configurations on a $16 \times 2$ character visual panel without consuming standard digital pin lanes.

#### 4. ⚡ Reaction Time Game (`/reaction_game`)
* **Project Type:** Interactive Time & State Pacing
* **Core Concepts:** Floating analog entropy tracking via open pin A0, random range math configurations, active button polling loops, and millisecond time delta calculations (`millis()`).
* **System Execution:** Flashes an erratic multi-LED sequence for random periods to introduce chaos, fires an instantaneous green signal light, and calculates the exact millisecond delta time it takes for a player to strike an input switch.

#### 5. 💻 Serial Interface Controller (`/serial_interface`)
* **Project Type:** Interactive String Stream Parsing
* **Core Concepts:** Non-blocking hardware serial buffer checks (`Serial.available`), string accumulation, case-insensitive comparison engines, and terminal state toggling.
* **System Execution:** Polls incoming character arrays over the serial monitor line, parsing user input commands like `ON` or `OFF` to explicitly manipulate a discrete hardware asset.

#### 6. 👑 SPI Master-Slave Communication (`/spi_master_slave`)
* **Project Type:** Synchronous Serial Bus Architecture
* **Core Concepts:** Software Bit-Banging, Master Out Slave In (MOSI), Serial Clock (SCK), Slave Select (SS), and multi-node bit alignment tracking.
* **System Execution:** Manually clocks 8-bit character data paths across individual digital lines to bypass web simulator register limitations, allowing a Master board to explicitly blink a target LED sitting on a completely separate Slave board.

#### 7. 🚦 Smart Traffic Light Intersection (`/traffic_light`)
* **Project Type:** Finite State Machine Automation
* **Core Concepts:** State machine architectures, rigid condition phase timing, sequential timing logic, and structural safety transition intervals.
* **System Execution:** Executes an automated traffic management pattern, routing cross-way lane delays sequentially across Red, Yellow, and Green paths.

#### 8. 🔌 Point-to-Point UART Direct Signaling (`/uart`)
* **Project Type:** Core Point-to-Point Signaling
* **Core Concepts:** Common ground reference balancing, unmodulated single-wire lines, and raw asynchronous input-to-output mirroring loops.
* **System Execution:** Links two Arduinos via a single wire hookup from Pin 3 to Pin 2, allowing a Master button press to mirror logic states instantly across to a Slave indicator light.

#### 9. 🚪 9. Smart Password Door Lock (`/utilize_all_the_pins_of_arduino_uno`)
* **Project Type:** Full Scale Resource Maximization & Security Robotics
* **Core Concepts:** Multi-attempt security logic, progressive frequency/duration buzzer escalation, state machine tracking, servo-driven mechanical actuation, and non-blocking timing arrays.
* **System Execution:** Manages an access control portal allowing a maximum of three password authentication attempts. Each consecutive incorrect input triggers an escalated, louder, and longer
* acoustic buzzer alarm sequence. Upon valid credential entry, the processor plays a 2-second celebratory harmonic melody and commands a servo motor to actuate the physical locking mechanism.
### 🛠️ Unified Hardware Protocol Summary

| Protocol Name | Wire Count | Max Relative Speed | Multi-Device Support? | Key Application This Week |
| :--- | :--- | :--- | :--- | :--- |
| **Direct Signaling** | 1 Data Wire + GND | Low Speed (1-bit state) | No (Point-to-Point only) | Single-button relay transmission |
| **I2C (SDA/SCL)** | 2 Data Wires + GND | Standard (100kHz - 400kHz) | Yes (Using Hex addresses) | Interfacing $16 \times 2$ Character Display LCD panels |
| **SPI (Bit-Banged)** | 4 Data Wires + GND | High Speed (Synchronous) | Yes (Using Slave Select lines) | Dual-Arduino synchronized command busing |

### 🚀 General Execution Framework

#### Running the Sub-Modules inside Tinkercad / Velxio
1. Open any specific project subdirectory indexed above and copy its localized `.ino` firmware code.
2. Open your web simulator environment (**Tinkercad** for Arduino Uno layouts, **Velxio** for the ESP32 Deep Sleep lab).
3. Paste the code into the text editing workspace. For dual-board networks (SPI, UART, Car), ensure the code for the Master and Slave matches the respective target microcontrollers on screen.
4. Click **Start Simulation** and open the bottom data terminal configurations to evaluate real-time tracking streams.

#### Flashing Code to Physical Desktop Microcontrollers
1. Hook up your target microcontroller to your laptop computer using an appropriate USB communication cable.
2. Launch the desktop Arduino IDE program and paste the target folder's code directly inside an empty sketch window canvas.
3. Access **Tools > Board** to choose either **Arduino Uno** or the matching **ESP32 Dev Module** hardware signature.
4. Access **Tools > Port** to assign the active tracking COM Port location.
5. If a script depends on specialized external libraries (such as `LiquidCrystal_I2C` or `Adafruit_LiquidCrystal`), open the Library Manager (`Ctrl+Shift+I`) to search and download those additions before compilation.
6. Press **Verify/Compile** to clear any syntax bugs, then hit **Upload** to write the compiled image to the microcontroller's flash storage memory.

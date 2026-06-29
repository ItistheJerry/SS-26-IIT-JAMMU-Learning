# Week 2:
**Course:** IoT & Drones (IIT Jammu Summer School 2026)  
**Student Name:** Apoorv Shivam  

---

## 📅 Weekly Overview
The second week of the curriculum shifted focus from core digital/analog primitives to advanced software architecture patterns, low-power processing frameworks, hardware protocol implementations ($I^2C$, $SPI$), and maximizing hardware resource interfaces. The exercises focused on designing interactive loops, asynchronous event listening, state-machine tracking, and dual-node distributed tasks.

---

## 📂 Projects

### 1. 🎹 Digital Piano (`/digital_piano`)
* **Project Type:** Interactive Audio Processing
* **Core Concepts:** Multi-button array interaction pooling, dynamic tone generation, frequency mapping vectors, and active buzzer hardware driving.
* **System Execution:** Scans a series of button inputs, outputting dedicated audio frequency pulse waveforms directly to a piezo transducer element when pressed.

### 2. 💤 ESP32 Deep Sleep (`/esp32_deep_sleep`)
* **Project Type:** Advanced Low-Power Management
* **Core Concepts:** Hardware sleep timers, power rail shutdown profiles, and state preservation utilizing non-volatile `RTC_DATA_ATTR` memory blocks.
* **System Execution:** Developed inside the Velxio platform. Configures a 5-second sleep timer wakeup source, spinning down core execution arrays while securely incrementing a boot count variable inside fast RTC memory registers across reboots.

### 3. 📺 I2C LCD Interfacing (`/i2c_lcd_display`)
* **Project Type:** Synchronous Bus Peripheral Control
* **Core Concepts:** Inter-Integrated Circuit ($I^2C$) serial protocol, 2-wire data lines ($SDA$/$SCL$), device hexadecimal address configuration, and character liquid crystal rendering.
* **System Execution:** Routes strings cleanly over a shared 2-wire serial line to print string configurations on a $16 \times 2$ character visual panel without consuming standard digital pin lanes.

### 4. ⚡ Reaction Time Game (`/reaction_game`)
* **Project Type:** Interactive Time & State Pacing
* **Core Concepts:** Floating analog entropy tracking via open pin `A0`, random range math configurations, active button polling loops, and millisecond time delta calculations (`millis()`).
* **System Execution:** Flashes an erratic multi-LED sequence for random periods to introduce chaos, fires an instantaneous green signal light, and calculates the exact millisecond delta time it takes for a player to strike an input switch.

### 5. 💻 Serial Interface Controller (`/serial_interface`)
* **Project Type:** Interactive String Stream Parsing
* **Core Concepts:** Non-blocking hardware serial buffer checks (`Serial.available`), string accumulation, case-insensitive comparison engines, and terminal state toggling.
* **System Execution:** Polls incoming character arrays over the serial monitor line, parsing user input commands like `ON` or `OFF` to explicitly manipulate a discrete hardware asset.

### 6. 👑 SPI Master-Slave Communication (`/spi_master_slave`)
* **Project Type:** Synchronous Serial Bus Architecture
* **Core Concepts:** Software Bit-Banging, Master Out Slave In ($MOSI$), Serial Clock ($SCK$), Slave Select ($SS$), and multi-node bit alignment tracking.
* **System Execution:** Manually clocks 8-bit character data paths across individual digital lines to bypass web simulator register limitations, allowing a Master board to explicitly blink a target LED sitting on a completely separate Slave board.

### 🚦 7. Smart Traffic Light Intersection (`/traffic_light`)
* **Project Type:** Finite State Machine Automation
* **Core Concepts:** State machine architectures, rigid condition phase timing, sequential timing logic, and structural safety transition intervals.
* **System Execution:** Executes an automated traffic management pattern, routing cross-way lane delays sequentially across Red, Yellow, and Green paths.

### 🔌 8. Point-to-Point UART Direct Signaling (`/uart`)
* **Project Type:** Core Point-to-Point Signaling
* **Core Concepts:** Common ground reference balancing, unmodulated single-wire lines, and raw asynchronous input-to-output mirroring loops.
* **System Execution:** Links two Arduinos via a single wire hookup from Pin 3 to Pin 2, allowing a Master button press to mirror logic states instantly across to a Slave indicator light.

### 🏎️ 9. Pin-Maximized Self-Driving Car (`/utilize_all_the_pins_of_arduino_uno`)
* **Project Type:** Full Scale Resource Maximization & Robotics
* **Core Concepts:** Reallocating analog inputs (`A0`–`A1`) as digital GPIO paths, Software Serial cross-chatter, servo steering mechanics, PWM motor control driving, and 4-way ultrasonic sonar grid matrix processing.
* **System Execution:** Employs 100% of the main Arduino board's I/O pins to guide an autonomous rover around obstacles, while packaging and pushing real-time direction metadata letters down to a secondary display microcontroller chip.

---

## 🛠️ Unified Hardware Protocol Summary

| Protocol Name | Wire Count | Max Relative Speed | Multi-Device Support? | Key Application This Week |
| :--- | :--- | :--- | :--- | :--- |
| **Direct Signaling** | $1 \text{ Data Wire } + \text{GND}$ | Low Speed (1-bit state) | No (Point-to-Point only) | Single-button relay transmission |
| **I2C ($SDA$/$SCL$)**| $2 \text{ Data Wires } + \text{GND}$ | Standard (100kHz - 400kHz) | Yes (Using Hex addresses) | Interfacing $16\times2$ Character Display LCD panels |
| **SPI (Bit-Banged)** | $4 \text{ Data Wires } + \text{GND}$ | High Speed (Synchronous) | Yes (Using Slave Select lines)| Dual-Arduino synchronized command busing |

---

## 🚀 General Execution Framework

### Running the Sub-Modules inside Tinkercad / Velxio
1. Open any specific project subdirectory indexed above and copy its localized `.ino` firmware code.
2. Open your web simulator environment (**Tinkercad** for Arduino Uno layouts, **Velxio** for the ESP32 Deep Sleep lab).
3. Paste the code into the text editing workspace. For dual-board networks (SPI, UART, Car), ensure the code for the Master and Slave matches the respective target microcontrollers on screen.
4. Click **Start Simulation** and open the bottom data terminal configurations to evaluate real-time tracking streams.

### Flashing Code to Physical Desktop Microcontrollers
1. Hook up your target microcontroller to your laptop computer using an appropriate USB communication cable.
2. Launch the desktop **Arduino IDE** program and paste the target folder's code directly inside an empty sketch window canvas.
3. Access **Tools > Board** to choose either **Arduino Uno** or the matching **ESP32 Dev Module** hardware signature.
4. Access **Tools > Port** to assign the active tracking **COM Port** location.
5. If a script depends on specialized external libraries (such as `LiquidCrystal_I2C` or `Adafruit_LiquidCrystal`), open the Library Manager (**Ctrl+Shift+I**) to search and download those additions before compilation.
6. Press **Verify/Compile** to clear any syntax bugs, then hit **Upload** to write the compiled image to the microcontroller's flash storage memory.

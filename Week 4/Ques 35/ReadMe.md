REST API - Weather Data Fetcher
An ESP32-based IoT application that connects to Wi-Fi, fetches real-time localized weather data from the OpenWeatherMap REST API, and compares it with local microenvironment data read from a physical DHT11 sensor.

The firmware computes and prints the variance in temperature and humidity between the city-wide API data and your indoor sensor readings directly to the Serial Monitor.

🛠️ Hardware Requirements
Microcontroller: ESP32 (e.g., ESP32-WROOM-32)

Sensor: DHT11 Temperature and Humidity Sensor

Connections:

VCC ➡️ 3.3V / 5V

GND ➡️ GND

DATA ➡️ GPIO 4

📚 Libraries Required
Ensure you have the following libraries installed in your Arduino IDE via the Library Manager:

DHT sensor library by Adafruit (along with its dependency Adafruit Unified Sensor)

ArduinoJson by Benoit Blanchon (Version 6.x preferred)

Built-in ESP32 core libraries: WiFi.h and HTTPClient.h

📁 Project Structure & Setup
Plaintext
├── Q35_Weather_API.ino    # Main application firmware
├── config.h               # Sensitive credentials (SSID, Passwords, API Keys)
└── .gitignore             # Prevents tracking config.h in version control
1. Configuration (config.h)
Create a file named config.h in the exact same directory as your Q35_Weather_API.ino sketch. Populate it with your localized credentials:

C++
#ifndef CONFIG_H
#define CONFIG_H

#define WIFI_SSID     "YourWiFiName"
#define WIFI_PASSWORD "YourWiFiPassword"
#define API_KEY       "your_openweathermap_api_key_here"
#define CITY_NAME     "New Delhi"

#endif
⚠️ Note: Free OpenWeatherMap API keys can be obtained by registering at openweathermap.org/api. Please note that new API keys can take up to 10 minutes to activate.

2. Security (.gitignore)
To protect your network credentials and private API keys from being leaked to public repositories, ensure a .gitignore file exists in your project root containing:

Plaintext
config.h
Always create this file and add config.h before your first Git commit.

📋 Expected Serial Monitor Output
Set your Serial Monitor baud rate to 115200. Once running, you should expect output resembling the following format:

Plaintext
Connecting to Wi-Fi.....
Wi-Fi Connected! IP: 192.168.1.105

WEATHER DATA REPORT
City          : New Delhi
Description   : haze
API Temp      : 34.2 C
DHT11 Temp    : 33.6 C
Difference    : +0.6 C
API Humidity  : 62 %
DHT11 Humidity: 60 %
Difference    : +2 %

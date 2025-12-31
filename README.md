# Interfacing ESP32 with AHT20 (Non-blocking FSM)

This project implements reading temperature and humidity data from the **AHT20** sensor using an **ESP32** microcontroller. The system is built on a **Finite State Machine (FSM)** architecture to ensure smooth, non-blocking program execution.

## 🚀 Key Features
* **Non-blocking Architecture**: Utilizes `millis()` instead of `delay()`, allowing the ESP32 to handle multiple tasks simultaneously.
* **Object-Oriented Programming (OOP)**: Maintains a clear separation between the header declaration (`.h`) and the implementation file (`.cpp`).
* **Error Management**: Automatically transitions to an `ERROR` state if the sensor is not detected during initialization.

## 🛠 Hardware Connection

The AHT20 sensor connects to the ESP32 via the default I2C interface:

| AHT20 Pin | ESP32 Pin | Notes |
| :--- | :--- | :--- |
| VCC | 3.3V | Power Supply |
| GND | GND | Common Ground |
| SDA | GPIO 21 | Data Line |
| SCL | GPIO 22 | Clock Line |

## 🏗 Source Code Structure
* `AHTSensorManager.h`: Defines the Class and the FSM states (`INIT`, `IDLE`, `TRIGGER`, `WAITING`, `READ_DATA`, `ERROR`).
* `AHTSensorManager.cpp`: Implements the logic for transitioning between states and sensor interaction.
* `AHT20Sensor.ino`: The main control file that calls the `update()` function continuously within the `loop()`.

## 📊 Finite State Machine (FSM) Workflow
The system cycles through the following steps:
1. **INIT**: Initializes the `Adafruit_AHTX0` library and checks for sensor connectivity.
2. **IDLE**: A 2-second wait interval between measurements to manage polling frequency.
3. **TRIGGER**: Initiates the sampling cycle.
4. **WAITING**: A non-blocking 80ms wait to allow the sensor to prepare the data.
5. **READ_DATA**: Reads the data and updates the internal temperature and humidity variables.

## 💻 How to Use
1. Install the **Adafruit AHTX0** library via the Arduino IDE Library Manager.
2. Download the source code and open the `.ino` file.
3. Upload the code to your ESP32 and open the Serial Monitor at a baud rate of **115200**.

## 📝 Author Information
* **Author**: Nguyen Phu Huu
* **Affiliation**: AIoT Semiconductor Lab - Ho Chi Minh City University of Technology and Education (HCMUTE).
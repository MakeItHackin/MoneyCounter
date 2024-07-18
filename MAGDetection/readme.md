# Arduino Bill Validator and Magnetic Sensor Reader

This project is designed to use an Arduino to read and validate bills based on input from a magnetic tape head sensor. It uses an interrupt on pin 2 to trigger reading from a magnetic sensor on pin 10 and displays the results on an OLED display.

## Table of Contents

- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Wiring Diagram](#wiring-diagram)
- [Installation](#installation)
- [Usage](#usage)
- [Code Overview](#code-overview)
- [License](#license)

## Features

- Reads magnetic sensor values to validate bills
- Displays sensor readings and validation results on an OLED screen
- Uses hardware interrupts for efficient sensor reading
- Simple user interface with reset functionality

## Hardware Requirements

- Arduino Uno (or compatible)
- Magnetic tape head sensor connected to pin 10
- OLED display (128x64) connected via I2C
- LEDs connected to pins 7, 8, and 9
- Buttons connected to pins 4, 5, and 6
- Pull-up resistors for buttons (internal)

## Software Requirements

- [Arduino IDE](https://www.arduino.cc/en/software)
- [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)
- [Adafruit SSD1306 Library](https://github.com/adafruit/Adafruit_SSD1306)

## Wiring Diagram

The following wiring diagram describes the connections required for the Arduino Bill Validator and Magnetic Sensor Reader project.

| Component           | Arduino Pin |
|---------------------|-------------|
| **OLED Display**    |             |
| SDA                 | A4          |
| SCL                 | A5          |
| **Magnetic Sensor** |             |
| Signal              | 10          |
| **LEDs**            |             |
| Green LED           | 7           |
| Red LED             | 8           |
| Yellow LED          | 9           |
| **Buttons**         |             |
| Reset Button        | 6           |
| Counter signal      | 2           |


## Installation

1. **Connect the hardware:**
   - Connect the OLED display to the I2C pins (SDA to A4, SCL to A5).
   - Connect the magnetic sensor to pin 10.
   - Connect LEDs to pins 7, 8, and 9.
   - Connect buttons to pin 6 with internal pull-up resistors.

2. **Install the required libraries:**
   - Open the Arduino IDE.
   - Go to `Sketch` > `Include Library` > `Manage Libraries...`.
   - Search for and install `Adafruit GFX Library`.
   - Search for and install `Adafruit SSD1306`.

3. **Upload the code:**
   - Copy the code from this repository.
   - Open the Arduino IDE.
   - Paste the code into a new sketch.
   - Select the correct board and port from `Tools` menu.
   - Upload the sketch to your Arduino.

## Usage

- **Display Initialization:**
  - The OLED display initializes and shows "MAG COUNT" with initial sensor values.
- **Interrupt Handling:**
  - The system uses an interrupt on pin 2 to trigger magnetic sensor readings.
- **Reset Functionality:**
  - Press the reset button (pin 6) to reset counters.

## Code Overview

### Global Variables

- **Pin Definitions:**
  - `INTERRUPT_PIN1` (pin 2)
  - `MAG_INPUT_PIN` (pin 10)
  - LED pins: `GREEN_LED_PIN` (pin 7), `RED_LED_PIN` (pin 8), `YELLOW_LED_PIN` (pin 9)
  - Button pins: `BUTTON_RIGHT` (pin 5), `BUTTON_LEFT` (pin 4), `RESET_BUTTON` (pin 6)

- **Counters and Flags:**
  - `counter1` and `magCounter` for tracking interrupts and magnetic sensor readings.
  - `lastInterruptTime1` for debouncing.
  - `pinValue` and `interruptFlag` for storing sensor readings and interrupt state.
  - `magValue` and `minMagValue` for storing and comparing sensor values.

### Functions

- **`setup()`:**
  - Initializes pin modes, LEDs, and the OLED display.
  - Attaches interrupt to pin 2.

- **`loop()`:**
  - Reads button states and resets

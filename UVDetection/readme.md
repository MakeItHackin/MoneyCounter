# UV Bill Validator

## Description

The UV Bill Validator is an Arduino-based project designed to read UV light intensity using a UV sensor and determine the validity of a bill based on predefined thresholds. It provides visual feedback via an OLED display and LEDs indicating whether the bill is real, fake, or missing.

## Components

- Arduino Uno (or compatible board)
- Adafruit SSD1306 OLED display (128x64 pixels)
- UV Sensor (connected to analog pin A0)
- Green LED
- Red LED
- Yellow LED
- Resistors for LEDs (220 ohms recommended)
- Breadboard and jumper wires

## Features

- Reads UV light intensity from a UV sensor
- Displays UV sensor value on an OLED display
- Indicates bill status (real, fake, missing) using LEDs
- Formats UV sensor values as four-digit integers with leading zeros

## Schematic

(To be uploaded at a later date)

## Libraries Required

- [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)
- [Adafruit SSD1306 Library](https://github.com/adafruit/Adafruit_SSD1306)

## Pin Configuration

| Component     | Pin       |
| ------------- | --------- |
| UV Sensor     | A0        |
| Green LED     | 7         |
| Red LED       | 8         |
| Yellow LED    | 9         |
| OLED Display  | SDA (A4), SCL (A5) |

## Installation

1. **Install Required Libraries:**

   Install the required libraries via the Arduino Library Manager or download them from the provided links and install manually.

   - Open the Arduino IDE.
   - Go to `Sketch` -> `Include Library` -> `Manage Libraries...`.
   - Search for "Adafruit GFX Library" and install it.
   - Search for "Adafruit SSD1306" and install it.

## Usage

1. **Connect the Components:**

   Follow the schematic to connect the UV sensor, LEDs, and OLED display to the Arduino.

2. **Upload the Code:**

   Open the `moneyCounterUVDetection.ino` file in the Arduino IDE and upload it to your Arduino board.

3. **Run the Project:**

   After uploading the code, the OLED display will show the UV sensor reading. The LEDs will indicate the bill status:
   
   - **Green LED:** Bill is real.
   - **Red LED:** Bill is fake.
   - **Yellow LED:** No bill detected.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

Feel free to contribute to this project by submitting issues or pull requests. Happy tinkering!

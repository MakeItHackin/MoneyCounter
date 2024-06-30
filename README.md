# Arduino Money Counter with OLED Display

This Arduino project uses a 128x64 OLED display to show a formatted currency value on the screen. The project includes multiple buttons to adjust the currency denomination and reset button. The displayed values update in real-time.

## Components

- Arduino (e.g., Uno, Nano)
- 128x64 OLED Display
- Push Buttons
- 10kOhm Resistors (pull-down for counter signal lines)
- Breadboard and jumper wires

## Features

- Displays a formatted currency value on the OLED screen
- Supports multiple currency denominations
- Allows user to cycle through currency denominations
- Real-time counter updates

## Schematic

[Will upload picture of setup here]

## Code

### Libraries Required

- `Adafruit_GFX`
- `Adafruit_SSD1306`

### Pin Configuration

- **OLED Display:**
  - `VCC` to 5V
  - `GND` to GND
  - `SCL` to A5
  - `SDA` to A4
    
- **Buttons:**
  - `buttonDebounce`: Pin 5
  - `buttonDenomination`: Pin 4
  - `buttonReset`: Pin 6
  - `INTERRUPT_PIN1`: Pin 2
  - `INTERRUPT_PIN2`: Pin 3

### Installation

1. **Connect the components** as per the schematic/picture.
2. **Install the required libraries**:
   - Open Arduino IDE
   - Go to Sketch > Include Library > Manage Libraries...
   - Search for "Adafruit GFX" and "Adafruit SSD1306"
   - Install both libraries

3. **Upload the code** to your Arduino board:

## Usage

- **buttonDebounce (Pin 5):** Increases the debounce time.
- **buttonDenomination (Pin 4):** Cycles through different currency denominations.
- **buttonReset (Pin 6):** Resets the counters to zero.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

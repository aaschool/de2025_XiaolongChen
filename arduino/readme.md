# Adaptive Meditation Corner - Arduino Setup

This repository contains the Arduino code for the Adaptive Meditation Corner project. The Arduino microcontroller is used to control hardware components including DMX lighting, LED ambient effects, and audio output. This document explains the code functionality and provides a basic hardware wiring setup.

## Overview

The `AdaptiveMeditation.ino` sketch implements several key features:

- **DMX Lighting Control:**  
  Uses the Conceptinetics DMX library to control professional DMX lighting systems.  
  *Example Command:* `DMX 1 255` sets DMX channel 1 to full brightness.

- **LED Control:**  
  Controls LED brightness via PWM using `analogWrite()`.  
  *Example Command:* `LED 9 128` sets the LED on pin 9 to a medium brightness.

- **Audio Output:**  
  Generates audio tones using the built-in `tone()` function.  
  *Example Command:* `AUDIO 8 1000 500` plays a 1000 Hz tone on pin 8 for 500 ms.

- **Serial Communication:**  
  Listens for serial commands over USB to update DMX channels, LED levels, and audio outputs in real time.

## Hardware Components

- **Arduino Board (Uno, Mega, etc.)**
- **DMX Controller/Transceiver:**  
  - Uses the Conceptinetics DMX library.  
  - Connects the DMX signal to digital pin 3 (or as specified in the code).
- **LEDs:**  
  - Connected to a PWM pin (e.g., pin 9) for brightness control.
- **Audio Output Device:**  
  - A small speaker or buzzer connected to a digital pin (e.g., pin 8) for tone generation.
- **Power Supply:**  
  - Ensure your Arduino and peripherals are adequately powered according to their specifications.

## Wiring Diagram

Below is a basic guide for the wiring:

- **DMX Connection:**
  - DMX data output from the DMX transceiver connects to digital pin 3 on the Arduino.
- **LED Connection:**
  - Connect the LED’s anode (positive) to a PWM pin (e.g., pin 9) through an appropriate resistor.
  - Connect the LED’s cathode (negative) to the Arduino GND.
- **Audio Connection:**
  - Connect a speaker or buzzer to digital pin 8.
  - Use a resistor or amplifier as needed based on your component specifications.

*Note: The exact wiring may vary depending on your hardware. Please consult your DMX transceiver, LED, and speaker datasheets for detailed instructions.*

## Code Explanation

### DMX Lighting Control
- **Library Used:** Conceptinetics DMX Library  
- The code initializes a DMX master and sets all DMX channels to an initial state.  
- Serial commands in the format `DMX <channel> <value>` update the DMX channels.

### LED Control
- **Function:** Uses `analogWrite()` to adjust LED brightness.  
- Commands like `LED <pin> <value>` control the LED’s brightness.

### Audio Control
- **Function:** Uses the built-in `tone()` function to produce audio signals.  
- Commands such as `AUDIO <pin> <frequency> <duration>` trigger a tone on the specified pin.

### Serial Communication
- The Arduino listens on the Serial port for commands, terminated by a newline (`\n`).  
- Incoming commands are parsed and processed to control DMX, LED, or audio outputs.

## How to Upload

1. **Install Libraries:**  
   - Use the Arduino Library Manager to install the [Conceptinetics DMX Library](https://github.com/alfo/arduino-libraries-conceptinetics-dmx).

2. **Open the Sketch:**  
   - Open `AdaptiveMeditation.ino` in the Arduino IDE.

3. **Select Your Board and Port:**  
   - In the Tools menu, select your Arduino board type and the correct port.

4. **Upload the Code:**  
   - Click the Upload button in the Arduino IDE.

## Troubleshooting

- **Serial Issues:**  
  - Ensure your Arduino is properly connected via USB and the correct port is selected.
- **DMX Output:**  
  - Verify the wiring between the DMX transceiver and the Arduino.
  - Ensure the DMX channel values are within the correct range.
- **LED/Audio Problems:**  
  - Check that the correct pins are used.
  - Verify that the LED and speaker/buzzer are functioning and correctly wired.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Contact

For questions, contributions, or further information, please contact [your email address] or open an issue on GitHub.

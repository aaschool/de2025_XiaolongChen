# de2025_XiaolongChen
## Project Overview
The Adaptive Meditation Corner initiative aims to provide an immersive and adaptable setting for people who experience weariness and stress as a result of lengthy periods of concentrated focus.  The technology gathers real-time physiological data (such as heart rate and stress levels) from wearable devices like the Apple Watch.  A tablet interface serves as the primary front-end for data synchronization and user interaction, while the Arduino microcontrollers allow users to directly influence the lighting ambience.  The backend, which runs on a dedicated server or laptop, interprets the data with tools such as Python and TouchDesigner to generate graphics and control signals dynamically.  These signals are then sent to hardware controllers Arduino microcontrollers that handle professional DMX lighting, LED ambient lighting, and audio systems, as well as deliver immersive projections over HDMI. This integrated system aims to help users quickly relax and regain focus through a tailored, multi-sensory experience.

## Tech Stack

### Front-End:
p5.js: For interactive visualizations and user interface development on the tablet.
HTML/CSS/JavaScript: Core technologies for building and styling the web application.

### Back-End:
Python: For data processing and server-side logic.
Flask (or similar): To implement HTTP/REST APIs for data communication.
TouchDesigner: For generating dynamic, immersive visual content.

## Communication Protocols:

BLE (Bluetooth Low Energy): For collecting physiological data from the Apple Watch.
Wi-Fi (IEEE 802.11): For data transfer between the tablet and the backend server.
HTTP/REST (JSON): For standardized data exchange between front-end and back-end.
USB Serial Communication: For sending control commands from the backend to the Arduino.
DMX512: For controlling professional stage or architectural lighting systems.
HDMI: For delivering high-definition visuals to a projector.
GPIO/PWM Signals: For managing LED lighting and audio output from the Arduino.

## Hardware:

Apple Watch: To capture real-time physiological data.
Tablet: For user interface and data synchronization.
Laptop/Server: For data analysis, visualization generation, and overall system control.
Arduino Microcontroller: To control lighting, audio, and other environmental systems.
DMX Lighting, LED Lights, Projector, Audio System: To deliver the immersive sensory experience.

## Workflow
Data Collection:
The Apple Watch continuously monitors the user's physiological data (e.g., heart rate, stress level) and transmits it via BLE.
Data Synchronization:
The Tablet interface receives the BLE data and forwards it to the backend server over Wi-Fi using HTTP/REST APIs.

## Data Processing:
The Laptop/Server processes the incoming data using Python and TouchDesigner to assess the user's current state.
Control Signal Generation:
Based on the analysis, the server determines the appropriate relaxation mode and generates control signals.
## Hardware Communication:
The server sends these commands via USB Serial communication to the Arduino Microcontroller.
## Environmental Control:
The Arduino uses DMX512 and GPIO/PWM signals to adjust the DMX lighting systems, LED ambient lights, and audio output.
Simultaneously, the server outputs immersive visual content via HDMI to a projector.

## Feedback Loop:
The system continuously monitors the user's physiological state and adjusts the environment in real time to optimize relaxation and focus.

## Reference:
1. https://github.com/yetyeeter1337/p5.Modbuttons
2. https://github.com/FastLED/FastLED
3. https://github.com/bblanchon/ArduinoJson
4. https://github.com/adafruit/Adafruit_NeoPixel
5. https://github.com/processing/p5.js
6. https://github.com/LUSHDigital/LushRooms
7. https://github.com/brianlow/Rotary
8. https://github.com/p5-serial/p5.serialport
9. https://github.com/mathertel/DMXSerial

#include <Conceptinetics.h>

// Define DMX settings
#define DMX_MASTER_CHANNELS 8  // Adjust as needed
DMX_Master dmx_master(DMX_MASTER_CHANNELS, 3);  // DMX output on digital pin 3

// Define LED and Audio pins
const int LED_PIN = 9;      // Must be a PWM pin
const int AUDIO_PIN = 8;    // Digital pin for tone output

// Variables for serial command parsing
String inputString = "";
boolean stringComplete = false;

void setup() {
  Serial.begin(9600);
  while (!Serial) {}  // Wait for Serial connection

  // Initialize DMX Master
  dmx_master.enable();
  // Set all DMX channels to 0 initially
  for (int i = 1; i <= DMX_MASTER_CHANNELS; i++) {
    dmx_master.setChannelValue(i, 0);
  }

  // Initialize LED and AUDIO pins
  pinMode(LED_PIN, OUTPUT);
  pinMode(AUDIO_PIN, OUTPUT);

  inputString.reserve(200);
  Serial.println("Adaptive Meditation Arduino Controller Started");
}

void loop() {
  if (stringComplete) {
    processCommand(inputString);
    // Clear the string for the next command
    inputString = "";
    stringComplete = false;
  }
}

// This function is automatically called by the Arduino runtime when new data arrives on Serial.
void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\n') {
      stringComplete = true;
    } else {
      inputString += inChar;
    }
  }
}

// Process incoming serial commands.
// Expected command formats:
// DMX <channel> <value>      e.g., "DMX 1 255"
// LED <pin> <value>          e.g., "LED 9 128"
// AUDIO <pin> <frequency> <duration>  e.g., "AUDIO 8 1000 500"
void processCommand(String command) {
  command.trim();
  Serial.print("Received command: ");
  Serial.println(command);

  int firstSpace = command.indexOf(' ');
  if (firstSpace == -1) return; // Invalid command

  String cmdType = command.substring(0, firstSpace);
  cmdType.toUpperCase();

  if (cmdType == "DMX") {
    int secondSpace = command.indexOf(' ', firstSpace + 1);
    if (secondSpace == -1) return;
    String channelStr = command.substring(firstSpace + 1, secondSpace);
    String valueStr = command.substring(secondSpace + 1);
    int channel = channelStr.toInt();
    int value = valueStr.toInt();
    if (channel < 1 || channel > DMX_MASTER_CHANNELS) {
      Serial.println("Error: DMX channel out of range.");
      return;
    }
    value = constrain(value, 0, 255);
    dmx_master.setChannelValue(channel, value);
    Serial.print("Set DMX channel ");
    Serial.print(channel);
    Serial.print(" to ");
    Serial.println(value);
  }
  else if (cmdType == "LED") {
    int secondSpace = command.indexOf(' ', firstSpace + 1);
    if (secondSpace == -1) return;
    String pinStr = command.substring(firstSpace + 1, secondSpace);
    String valueStr = command.substring(secondSpace + 1);
    int pin = pinStr.toInt();
    int value = valueStr.toInt();
    value = constrain(value, 0, 255);
    analogWrite(pin, value);
    Serial.print("Set LED on pin ");
    Serial.print(pin);
    Serial.print(" to ");
    Serial.println(value);
  }
  else if (cmdType == "AUDIO") {
    int secondSpace = command.indexOf(' ', firstSpace + 1);
    if (secondSpace == -1) return;
    int thirdSpace = command.indexOf(' ', secondSpace + 1);
    if (thirdSpace == -1) return;
    String pinStr = command.substring(firstSpace + 1, secondSpace);
    String freqStr = command.substring(secondSpace + 1, thirdSpace);
    String durationStr = command.substring(thirdSpace + 1);
    int pin = pinStr.toInt();
    int frequency = freqStr.toInt();
    int duration = durationStr.toInt();
    tone(pin, frequency, duration);
    Serial.print("Playing tone on pin ");
    Serial.print(pin);
    Serial.print(" with frequency ");
    Serial.print(frequency);
    Serial.print(" Hz for ");
    Serial.print(duration);
    Serial.println(" ms");
  }
  else {
    Serial.println("Error: Unknown command type.");
  }
}

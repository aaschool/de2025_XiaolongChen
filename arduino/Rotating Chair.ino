#define ENC_A 2         // Rotary Encoder Channel A
#define ENC_B 3         // Rotary Encoder Channel B
#define SWITCH_PIN 4    // On/Off switch
#define MOTOR_DIR 5     // Motor direction control
#define MOTOR_PWM 6     // Motor speed control (PWM pin)

// Variables for encoder
volatile long encoderPosition = 0;   // Accumulated rotation
volatile bool lastA = false;         // Track last state of ENC_A
volatile bool lastB = false;         // Track last state of ENC_B

// User-defined max motor speed (0-255 for analogWrite)
int maxMotorSpeed = 180;  // Adjust as needed
// Motor speed offset to handle slow movement
int minMotorSpeed = 60;  

// Debounce/safety
bool rotationEnabled = false;

void setup() {
  Serial.begin(9600);

  // Pin modes
  pinMode(ENC_A, INPUT_PULLUP);
  pinMode(ENC_B, INPUT_PULLUP);
  pinMode(SWITCH_PIN, INPUT_PULLUP);   // On/Off switch
  pinMode(MOTOR_DIR, OUTPUT);
  pinMode(MOTOR_PWM, OUTPUT);

  // Attach interrupts for the encoder
  attachInterrupt(digitalPinToInterrupt(ENC_A), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_B), updateEncoder, CHANGE);

  // Read initial switch state
  rotationEnabled = (digitalRead(SWITCH_PIN) == LOW) ? true : false;

  // Initial motor off
  digitalWrite(MOTOR_DIR, LOW);
  analogWrite(MOTOR_PWM, 0);

  Serial.println("Arduino Chair Control Started.");
}

void loop() {
  // Check On/Off switch state
  bool currentSwitch = (digitalRead(SWITCH_PIN) == LOW);
  if (currentSwitch != rotationEnabled) {
    rotationEnabled = currentSwitch;
    if (!rotationEnabled) {
      // Turn off motor if switch is turned off
      analogWrite(MOTOR_PWM, 0);
      Serial.println("Rotation disabled.");
    } else {
      Serial.println("Rotation enabled.");
    }
  }

  // Calculate motor speed based on encoderPosition
  // (In a real system, you'd map 'encoderPosition' to a speed or position)
  long currentPos = encoderPosition; 
  // For demonstration, use absolute value to define speed
  int speedVal = abs(currentPos) % 255; // Quick example mapping
  speedVal = constrain(speedVal, minMotorSpeed, maxMotorSpeed);

  // Determine direction based on sign of encoderPosition
  // Positive = one direction, negative = the other
  bool dir = (currentPos >= 0);

  if (rotationEnabled) {
    // Set motor direction
    digitalWrite(MOTOR_DIR, dir ? HIGH : LOW);
    // Set motor speed (PWM)
    analogWrite(MOTOR_PWM, speedVal);
  }

  // Optional: If you want to send DMX or lighting triggers to the laptop,
  // you could do something like:
  // if (someCondition) {
  //   Serial.println("DMX 1 255"); // e.g., a command recognized by the laptop
  // }

  // Some small delay or do other tasks
  delay(50);
}

/*
  Interrupt Service Routine for the encoder.
  Reads ENC_A and ENC_B to update 'encoderPosition' accordingly.
*/
void updateEncoder() {
  bool A = digitalRead(ENC_A);
  bool B = digitalRead(ENC_B);

  // Determine direction
  if (A == lastA && B == lastB) return; // No change

  // If A changed first
  if (A != lastA && A == B) {
    encoderPosition++;
  } 
  // If B changed first
  else if (B != lastB && A != B) {
    encoderPosition--;
  }

  lastA = A;
  lastB = B;
}

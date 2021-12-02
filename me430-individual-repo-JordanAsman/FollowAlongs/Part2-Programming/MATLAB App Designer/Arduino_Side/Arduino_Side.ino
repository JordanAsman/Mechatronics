#include <Servo.h>

#define PIN_PUSHBUTTON 2
#define PIN_LED 3
#define PIN_JOYSTICK_X 0
#define PIN_JOYSTICK_Y 1
#define PIN_SERVO 9

String inputString = "";
bool stringComplete = false;
Servo myServo;

int joystickX;
int lastSentJoystickX;
int joystickY;
int lastSentJoystickY;
const int JOYSTICK_THRESHOLD = 15;

void setup() {
  Serial.begin(9600);
  inputString.reserve(200);
  pinMode(PIN_PUSHBUTTON, INPUT_PULLUP);
  pinMode(PIN_LED, OUTPUT);
  myServo.attach(PIN_SERVO);
}

void loop() {
  if (!digitalRead(PIN_PUSHBUTTON)) {
    Serial.println("B");
    delay(500);
  }
  
  // Joystick stuff goes here
  joystickX = analogRead(0);
  if (abs(joystickX - lastSentJoystickX) > JOYSTICK_THRESHOLD) {
    lastSentJoystickX = joystickX;
    Serial.println(String("X ") + lastSentJoystickX);
  }
  joystickY = analogRead(1);
  if (abs(joystickY - lastSentJoystickY) > JOYSTICK_THRESHOLD) {
    lastSentJoystickY = joystickY;
    Serial.println(String("Y ") + lastSentJoystickY);
  }
  if (stringComplete) {
    inputString.toUpperCase();
    inputString.trim();
    Serial.println(inputString); // Optional send to MATLAB
    if (inputString.equalsIgnoreCase("LED ON")) {
      digitalWrite(PIN_LED, HIGH);
    } else if (inputString.equalsIgnoreCase("LED OFF")) {
      digitalWrite(PIN_LED, LOW);
    } else if (inputString.startsWith("SERVO ")) {
      int degrees = inputString.substring(6).toInt();
      myServo.write(degrees);
    }
    inputString = "";
    stringComplete = false;
  }
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\n') { // Line feed. ASCII value 10
      stringComplete = true;
    } else {
      inputString += inChar;
    }
  }
}

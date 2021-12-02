// Part L - Servo motor
#include <Servo.h>

Servo myservo;
int potValue;
int degrees;

void setup()
{
  // Inputs
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  
  // Outputs for LEDS
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  
  // Outputs for servo
  myservo.attach(9);
}

void loop()
{
  // Outputs for LEDS
  digitalWrite(4, !digitalRead(2));
  digitalWrite(5, !digitalRead(3));
  analogWrite(6, analogRead(0)/4);

  if (!digitalRead(2)) {
    myservo.write(0);
  }
  else if (!digitalRead(3)) {
    myservo.write(180);
  }
  else {
    potValue = analogRead(0); // 0 to 1023
    degrees = map(potValue, 0, 1023, 0, 180);
    myservo.write(degrees);
  }
  
  delay(10);
}

#include <Stepper.h>

#define START_BEAM 0

const int stepsPerRevolution = 2048/4;
Stepper stepper1(stepsPerRevolution, 8, 10, 9, 11);  // Order is important!
Stepper stepper2(stepsPerRevolution, 22, 24, 23, 25);  // Order is important!
Stepper stepper3(stepsPerRevolution, 30, 32, 31, 33);  // Order is important!

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);

  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);

  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);

  stepper1.setSpeed(50);
  stepper2.setSpeed(50);
  stepper3.setSpeed(50);

  pinMode(START_BEAM, INPUT_PULLUP);

  Serial.begin(9600);
}
void loop() {
  motor();
  
  checkBeam();
}

void motor() {
  if(!digitalRead(2)) {
      stepper1.step(stepsPerRevolution);
      // delay(10);
    }
    else if (!digitalRead(3)){
       stepper1.step(-stepsPerRevolution);
       // delay(10);
    }

    if(!digitalRead(4)) {
      stepper2.step(stepsPerRevolution);
      // delay(10);
    }
    else if (!digitalRead(5)){
       stepper2.step(-stepsPerRevolution);
       // delay(10);
    }

    if(!digitalRead(6)) {
      stepper3.step(stepsPerRevolution);
      // delay(10);
    }
    else if (!digitalRead(7)){
       stepper3.step(-stepsPerRevolution);
       // delay(10);
    }
}

void checkBeam() {
  if (digitalRead(START_BEAM) == 1) {
    // All if good
    Serial.println("All good");
  }
  else if (digitalRead(START_BEAM) == 0) {
    // Beam broken
    Serial.println("Beam Broken!!!");
    
  }
}

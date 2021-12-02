// Part I - stepper motor
#include <Stepper.h>

//const int stepsPerRevolution = 2048;  // 32 steps * 64:1 gearhead
//const int stepsPerRevolution = 60;  // Tell a lie for now!
const int stepsPerRevolution = 2048/4;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);  // Order is important!

void setup() {
   // Inputs
   pinMode(2, INPUT_PULLUP);
   pinMode(3, INPUT_PULLUP);
  
   myStepper.setSpeed(5); // For later
  // set the speed at 1 rpm:
  // myStepper.setSpeed(1);
}

void loop() {
  if (!digitalRead(2)){
    myStepper.step(stepsPerRevolution);
    delay(1000);
  }
  else if (!digitalRead(3)){
    myStepper.step(-stepsPerRevolution);
    delay(1000);
  }
  
  // step one revolution  in one direction:
 // myStepper.step(stepsPerRevolution);
 // delay(500);

  // step one revolution in the other direction:
 // myStepper.step(-stepsPerRevolution);
 // delay(500);
}

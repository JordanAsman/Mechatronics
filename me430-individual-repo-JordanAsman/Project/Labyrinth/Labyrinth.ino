#include <Stepper.h>
#include <LiquidCrystal.h>

// Sensor pin declarations
#define START_BEAM 50
#define FAIL_BEAM 51
#define END_BEAM 52

// set LCD line variables
#define LINE_1 0
#define LINE_2 1

// motor speed is constant
// TODO: Maybe add more motor speeds to make fluid movement
#define MOTOR_SPEED 50

// set joystick ranges
#define X12_LOW 300
#define X12_HIGH 600
#define Y12_LOW 0
#define Y12_HIGH 300

#define X130_LOW 600
#define X130_HIGH 1030
#define Y130_LOW 0
#define Y130_HIGH 300

#define X3_LOW 600
#define X3_HIGH 1030
#define Y3_LOW 300
#define Y3_HIGH 600

#define X430_LOW 600
#define X430_HIGH 1030
#define Y430_LOW 600
#define Y430_HIGH 1030

#define X6_LOW 300
#define X6_HIGH 600
#define Y6_LOW 600
#define Y6_HIGH 1030

#define X730_LOW 0
#define X730_HIGH 300
#define Y730_LOW 600
#define Y730_HIGH 1030

#define X9_LOW 0
#define X9_HIGH 300
#define Y9_LOW 300
#define Y9_HIGH 600

#define X1030_LOW 0
#define X1030_HIGH 300
#define Y1030_LOW 0
#define Y1030_HIGH 300

// set point values
// TODO: Create point system
#define WIN_POINTS 100

/* Details about connections
 *  
 *  Front motor connected to pins 8, 9, 10, 11
 *  Back left motor connected to pins 22, 23, 24, 25
 *  Back right motor connected to pins 30, 31, 32, 33
 *  
 *  Start sensor is connected to pin 50
 *  Fail sensor is connected to pin 51
 *  End sensor is connected to pin 52
 *  
 *  LCD is connected to pins 2, 3, 4, 5, 6, 7
 *  
 *  Joystick x-position is connected to pin A0
 *  Joystick y-position is connected to pin A1
 *  Joystick button is connected to pin 40
 *  
 */
 
// front of board has single motor, back has 2 motors
// TODO: Add more stepsPerRevolution variables based on movement
const int stepsPerRevolution = 2048/8;
Stepper frontMotor(stepsPerRevolution, 8, 10, 9, 11);  // Order is important!
Stepper backLeftMotor(stepsPerRevolution, 22, 24, 23, 25);  // Order is important!
Stepper backRightMotor(stepsPerRevolution, 30, 32, 31, 33);  // Order is important!

// set up LCD
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// score variable to be updated as game is played
uint8_t score = 0;

/* motor counts
 *  increment based on the numebr of positive rotations
 *  decrement based on the number of negative rotations
 */
uint8_t frontMotorCount = 0;
uint8_t backLeftMotorCount = 0;
uint8_t backRightMotorCount = 0;

/* Details on state variables
 *  
 *  If the game has not been started, all variables will be set to 0
 *  Once the ball has passed the start beam, the game will be in the start state
 *  If the game is lost, the game will be in the lose state
 *  If the game is won, the game will be in the win state
 *  If the game is in progress, the game will be in the playing state
 *  
 *  These states impact how the LCD updates, what sensors are checked, and other functionality of the game
 *  Reset will put the game back into an unstarted state - all state variables are 0
 */
 
uint8_t start = 0;
uint8_t lose = 0;
uint8_t win = 0;
uint8_t playing = 0;

// time things
double time = 0;
double a = millis();
double c;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();

  // Joystick push button - reset
  pinMode(40, INPUT_PULLUP); 

  // Motor speeds are set
  frontMotor.setSpeed(MOTOR_SPEED);
  backLeftMotor.setSpeed(MOTOR_SPEED);
  backRightMotor.setSpeed(MOTOR_SPEED);

  pinMode(START_BEAM, INPUT_PULLUP);
  pinMode(FAIL_BEAM, INPUT_PULLUP);
  pinMode(END_BEAM, INPUT_PULLUP);
}
void loop() {    
  // TODO: Run functions to play game  
  checkBeam();

  gameTime();

  updateLCD();

  moveMotors();
  
  reset();
}

void moveMotors() {
  // TODO: Update motor movement based on joystick 
  if((X12_LOW <= analogRead(0) && X12_HIGH >= analogRead(0)) && (Y12_LOW <= analogRead(1) && Y12_HIGH >= analogRead(1))) {
    // TODO: move back left and right down
    backLeftMotor.step(-2);
    backRightMotor.step(-2);
    frontMotor.step(2);

    backLeftMotorCount = backLeftMotorCount - 2;
    backRightMotorCount = backRightMotorCount - 2;
    frontMotorCount = frontMotorCount + 2;
  }
  
  if ((X130_LOW <= analogRead(0) && X130_HIGH >= analogRead(0)) && (Y130_LOW <= analogRead(1) && Y130_HIGH >= analogRead(1))) {
    // TODO: move back right down
    backLeftMotor.step(2);
    backRightMotor.step(-2);
    frontMotor.step(2);

    backLeftMotorCount = backLeftMotorCount + 2;
    backRightMotorCount = backRightMotorCount - 2;
    frontMotorCount = frontMotorCount + 2;
  }

  if ((X1030_LOW <= analogRead(0) && X1030_HIGH >= analogRead(0)) && (Y1030_LOW <= analogRead(1) && Y1030_HIGH >= analogRead(1))) {
    // TODO: move back left down
    backLeftMotor.step(-2);
    backRightMotor.step(2);
    frontMotor.step(2);

    backLeftMotorCount = backLeftMotorCount - 2;
    backRightMotorCount = backRightMotorCount + 2;
    frontMotorCount = frontMotorCount + 2;
  }

  if ((X6_LOW <= analogRead(0) && X6_HIGH >= analogRead(0)) && (Y6_LOW <= analogRead(1) && Y6_HIGH >= analogRead(1))) {
    // TODO: move front down
    backLeftMotor.step(2);
    backRightMotor.step(2);
    frontMotor.step(-2);

    backLeftMotorCount = backLeftMotorCount + 2;
    backRightMotorCount = backRightMotorCount + 2;
    frontMotorCount = frontMotorCount - 2;
  }

  if ((X3_LOW <= analogRead(0) && X3_HIGH >= analogRead(0)) && (Y3_LOW <= analogRead(1) && Y3_HIGH >= analogRead(1))) {
    // TODO: move front down less, back right down more, back left up less
    backLeftMotor.step(1);
    backRightMotor.step(-2);
    frontMotor.step(-1);

    backLeftMotorCount = backLeftMotorCount + 1;
    backRightMotorCount = backRightMotorCount - 2;
    frontMotorCount = frontMotorCount - 1;
  }

  if ((X9_LOW <= analogRead(0) && X9_HIGH >= analogRead(0)) && (Y9_LOW <= analogRead(1) && Y9_HIGH >= analogRead(1))) {
    // TODO: move front down less, back right up less, back left down more
    backLeftMotor.step(-2);
    backRightMotor.step(1);
    frontMotor.step(-1);

    backLeftMotorCount = backLeftMotorCount - 2;
    backRightMotorCount = backRightMotorCount + 1;
    frontMotorCount = frontMotorCount - 1;
  }

  if ((X430_LOW <= analogRead(0) && X430_HIGH >= analogRead(0)) && (Y430_LOW <= analogRead(1) && Y430_HIGH >= analogRead(1))) {
    // TODO: move back left up
    backLeftMotor.step(2);
    backRightMotor.step(-2);
    frontMotor.step(-2);

    backLeftMotorCount = backLeftMotorCount + 2;
    backRightMotorCount = backRightMotorCount - 2;
    frontMotorCount = frontMotorCount - 2;
  }

  if ((X730_LOW <= analogRead(0) && X730_HIGH >= analogRead(0)) && (Y730_LOW <= analogRead(1) && Y730_HIGH >= analogRead(1))) {
    // TODO: move back right up
    backLeftMotor.step(-2);
    backRightMotor.step(2);
    frontMotor.step(-2);
    
    backLeftMotorCount = backLeftMotorCount - 2;
    backRightMotorCount = backRightMotorCount + 2;
    frontMotorCount = frontMotorCount - 2;
  }
}

void checkBeam() {
  if (playing == 0 && digitalRead(START_BEAM) == 1 && win == 0 && lose == 0) {
    // Game not started
    // TODO: Change state
    start = 1;
  }
  else if (playing == 1 || digitalRead(START_BEAM) == 0) {
    // Begin the game
    // TODO: start the timer, change state    
    start = 0;
    lose = 0;
    win = 0;
    playing = 1;
  }

  if (digitalRead(FAIL_BEAM) == 0) {
    // Game lost
    // TODO: stop time, update LCD time and score, change state
    start = 0;
    lose = 1;
    win = 0;
    playing = 0;
  }
  else if (digitalRead(FAIL_BEAM) == 1) {
    // Do nothing
  }

  if (digitalRead(END_BEAM) == 0) {
    // Game won
    // TODO: stop time, update score & LCD, change state
    start = 0;
    lose = 0;
    win = 1;
    playing = 0;

    score = WIN_POINTS;
  }
  else if (digitalRead(END_BEAM) == 1) {
    // Do nothing
  }
}

void gameTime() {
  if (playing) {
    c = millis();
    time = (c - a) / 1000;
  }
  else {
    // do nothing
  }
}

void updateLCD() {
  if (start) {
    lcd.setCursor(0, LINE_1);
    lcd.print("Play Game!   ");
  }
  else if (lose) {
    lcd.setCursor(0, LINE_1);
    lcd.print("Game Lost!   ");
  }
  else if (win) {
    lcd.setCursor(0, LINE_1);
    lcd.print("Game Won!    ");
  }
  else if (playing) {
    lcd.setCursor(0, LINE_1);
    lcd.print("Playing Game!");
  }
  else {
    lcd.setCursor(0, LINE_1);
    lcd.print("Labyrinth!");
  }
  
  lcd.setCursor(0, LINE_2);
  lcd.print("Score=");
  lcd.print(score);

  lcd.setCursor(10, LINE_2);
  lcd.print("T="); 
  // print the number of seconds since reset:
  lcd.print(time);
}

void reset() {
  if(!digitalRead(40)) {
    // TODO: reset motor positions
    // TODO: reset state variables
    backLeftMotor.step(-2*backLeftMotorCount);
    backRightMotor.step(-2*backRightMotorCount);
    frontMotor.step(-2*frontMotorCount);

    backLeftMotorCount = 0;
    backRightMotorCount = 0;
    frontMotorCount = 0;

    score = 0;

    start = 0;
    lose = 0;
    win = 0;
    playing = 0;

    lcd.clear();
    lcd.setCursor(0, LINE_1);
    lcd.print("Labyrinth!");
    lcd.setCursor(0, LINE_2);
    lcd.print("Score=");
    lcd.print(score);
    lcd.setCursor(10, LINE_2);
    lcd.print("T="); 
    // print the number of seconds since reset:
    //lcd.print(millis() / 1000);
    time = 0;
    a = millis();
    c = millis();
  }
}

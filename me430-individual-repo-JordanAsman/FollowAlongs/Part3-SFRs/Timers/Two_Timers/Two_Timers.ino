// include the library code:
#include <LiquidCrystal.h>

// LCD
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
#define LINE_1 0
#define LINE_2 1

// Timing planning
// Green Timer to have interrupts every 0.001 seconds via Timer 2
// Plan: Set TIMSK2 to have OCIE2A high - enable Timer 2 int
// Prescaller options: (must be less than 255 since Timer 2 is 8-bit)
// 1 -->    0.001 / (1/16000000) --> 16000 ticks for 0.001 seconds
// 8 -->    0.001 / (8/16000000) --> 2000 ticks for 0.001 seconds
// 32 -->   0.001 / (32/16000000) --> 500 ticks for 0.001 seconds
// 64 -->   0.001 / (64/16000000) --> 250 ticks for 0.001 seconds  -- Use this one!
// 128 -->  0.001 / (128/16000000) --> 125 ticks for 0.001 seconds
// 256 -->  0.001 / (256/16000000) --> 62.5 ticks for 0.001 seconds
// 1024 --> 0.001 / (1024/16000000) --> 31.25 ticks for 0.001 seconds
#define TIMER_2_START 0
#define TIMER_2_END 250

// Yellow Timer to have interrupts every 0.1 seconds via Timer 1
// Plan: Set TIMSK1 to have OCIE1A high - enable Timer 1 int
// Prescaller options: (must be less than 65535 since Timer 1 is 16-bit)
// Prescaller options: (must be less than 255 since Timer 2 is 8-bit)
// 1 -->    0.1 / (1/16000000) --> 1600000 ticks for 0.001 seconds
// 8 -->    0.1 / (8/16000000) --> 200000 ticks for 0.001 seconds
// 64 -->   0.1 / (64/16000000) --> 25000 ticks for 0.001 seconds  -- Use this one!
// 256 -->  0.1 / (256/16000000) --> 6250 ticks for 0.001 seconds
// 1024 --> 0.1 / (1024/16000000) --> 1562.5 ticks for 0.001 seconds
#define TIMER_1_START 0
#define TIMER_1_END 25000

// Mega

// Green Button on PD2 (INT2)
#define REG_DDR_PUSHBUTTON_GREEN DDRD
#define REG_PORT_PUSHBUTTON_GREEN PORTD
#define REG_PIN_PUSHBUTTON_GREEN PIND
#define BIT_PUSHBUTTON_GREEN 2

// Yellow Button on PD3 (INT3)
#define REG_DDR_PUSHBUTTON_YELLOW DDRD
#define REG_PORT_PUSHBUTTON_YELLOW PORTD
#define REG_PIN_PUSHBUTTON_YELLOW PIND
#define BIT_PUSHBUTTON_YELLOW 3

// Reset Button on PD0 (INT0)
#define REG_DDR_PUSHBUTTON_RESET DDRD
#define REG_PORT_PUSHBUTTON_RESET PORTD
#define REG_PIN_PUSHBUTTON_RESET PIND
#define BIT_PUSHBUTTON_RESET 0

// Green LED on PH3
#define REG_DDR_LED_GREEN DDRH
#define REG_PORT_LED_GREEN PORTH
#define REG_PIN_LED_GREEN PINH
#define BIT_LED_GREEN 3

// Yellow LED on PH4
#define REG_DDR_LED_YELLOW DDRH
#define REG_PORT_LED_YELLOW PORTH
#define REG_PIN_LED_YELLOW PINH
#define BIT_LED_YELLOW 4

// Use Timer 2 (green timer) with a 0.001 interrupts
bool isGreenTimerRunning = false;
volatile uint16_t greenCounterMilliSec = 0;

// Use Timer 1 (yellow timer) with a 0.1 interrupts
bool isYellowTimerRunning = false;
volatile uint16_t yellowCounterTenthSec = 0;

// Delay variables
#define DEBOUNCE_TIME_MS 20
volatile uint16_t delayCounter = 0;

/*** Interrupt Flags ***/
volatile uint8_t mainEventFlags = 0;
#define FLAG_PUSHBUTTON_GREEN 0x01
#define FLAG_PUSHBUTTON_YELLOW 0x02

void setup() {
  lcd.begin(16, 2);
  cli();
  
  // Pins as inputs
  REG_DDR_PUSHBUTTON_GREEN &= ~_BV(BIT_PUSHBUTTON_GREEN);
  REG_DDR_PUSHBUTTON_YELLOW &= ~_BV(BIT_PUSHBUTTON_YELLOW);
  REG_DDR_PUSHBUTTON_RESET &= ~_BV(BIT_PUSHBUTTON_RESET);
  
  // Enable pull up resistors
  REG_PORT_PUSHBUTTON_GREEN |= _BV(BIT_PUSHBUTTON_GREEN);
  REG_PORT_PUSHBUTTON_YELLOW |= _BV(BIT_PUSHBUTTON_YELLOW);
  REG_PORT_PUSHBUTTON_RESET |= _BV(BIT_PUSHBUTTON_RESET);
  
  // Set up LEDs
  REG_DDR_LED_YELLOW |= _BV(BIT_LED_YELLOW);
  REG_DDR_LED_GREEN |= _BV(BIT_LED_GREEN);
  
  // Setup the interrupt
  
  // Mega - 3 interrupts
  EICRA |= _BV(ISC01); // Part of FALL edge setup (set HIGH)
  EICRA &= ~ _BV(ISC00); // Part of FALL edge setup (set LOW)
  EIMSK |= _BV(INT0); // Turns on INT0 the external interrupt
 
  EICRA |= _BV(ISC21); // Part of FALL edge setup (set HIGH)
  EICRA &= ~ _BV(ISC20); // Part of FALL edge setup (set LOW)
  EIMSK |= _BV(INT2); // Turns on INT2 the external interrupt
  
  EICRA |= _BV(ISC31); // Part of FALL edge setup (set HIGH)
  EICRA &= ~ _BV(ISC30); // Part of FALL edge setup (set LOW)
  EIMSK |= _BV(INT3); // Turns on INT3 the external interrupt
  
  // Timer 2 interrupt setup
  TCCR2A = 0; // Clear things that Arduino did
  // Prescaller of 64
  TCCR2B |= _BV(CS22);
  TCCR2B &= ~_BV(CS21);
  TCCR2B &= ~_BV(CS20);
  TCNT2 = TIMER_2_START;
  OCR2A = TIMER_2_END;
  TIMSK2 |= _BV(OCIE2A);
  
  // Timer 1 interrupt setup
  TCCR1A = 0; // Clear things that Arduino did
  // Prescaller of 64
  TCCR1B &= ~_BV(CS12);
  TCCR1B |= _BV(CS11);
  TCCR1B |= _BV(CS10);
  TCNT1 = TIMER_1_START;
  OCR1A = TIMER_1_END;
  TIMSK1 |= _BV(OCIE1A);
  
  sei(); // Turn on interrupts! Do this last
}

void loop() {
  updateLCD();
  
  if (mainEventFlags & FLAG_PUSHBUTTON_GREEN) {
    blockingDelay(DEBOUNCE_TIME_MS);
    mainEventFlags &= ~FLAG_PUSHBUTTON_GREEN;
    if (bit_is_clear(REG_PIN_PUSHBUTTON_GREEN, BIT_PUSHBUTTON_GREEN)) {
    // Toggle the LED and the running or not of the timer
      isGreenTimerRunning = !isGreenTimerRunning;
      REG_PORT_LED_GREEN ^= _BV(BIT_LED_GREEN);
    }
  }  
  if (mainEventFlags & FLAG_PUSHBUTTON_YELLOW) {
    blockingDelay(DEBOUNCE_TIME_MS);
    mainEventFlags &= ~FLAG_PUSHBUTTON_YELLOW;
    if (bit_is_clear(REG_PIN_PUSHBUTTON_YELLOW, BIT_PUSHBUTTON_YELLOW)) {
      // Toggle the LED and the running or not of the timer
      isYellowTimerRunning = !isYellowTimerRunning;
      REG_PORT_LED_YELLOW ^= _BV(BIT_LED_YELLOW);
    }
  } 
}

void updateLCD() {
  lcd.setCursor(0, LINE_1);
  uint8_t greenSeconds = greenCounterMilliSec / 1000;
  uint8_t greenTenthSec = (greenCounterMilliSec / 100) % 10;
  lcd.print(greenSeconds);
  lcd.print(".");
  lcd.print(greenTenthSec);
  lcd.print("  ");
  
  lcd.setCursor(0, LINE_2);
  
  if (isYellowTimerRunning) {
    lcd.print("      ");
  } else {
      uint8_t yellowSeconds = yellowCounterTenthSec / 10;
      uint8_t yellowTenthSec = yellowCounterTenthSec % 10;
      lcd.print(yellowSeconds);
      lcd.print(".");
      lcd.print(yellowTenthSec);
      lcd.print("  ");
  }
}

void blockingDelay(uint16_t delayMs) {
  delayCounter = delayMs;
  while (delayCounter > 0) {
    // Do nothing!
  }
}

// Mega - Reset Button
ISR(INT0_vect) {
  REG_PORT_LED_GREEN &= ~_BV(BIT_LED_GREEN);
  REG_PORT_LED_YELLOW &= ~_BV(BIT_LED_YELLOW);
    
  isGreenTimerRunning = false;
  greenCounterMilliSec = 0;
    
  isYellowTimerRunning = false;
  yellowCounterTenthSec = 0;
}
// Mega - Green Button
ISR(INT2_vect) { 
  mainEventFlags |= FLAG_PUSHBUTTON_GREEN;
}
// Mega - Yellow Button
ISR(INT3_vect) {
  mainEventFlags |= FLAG_PUSHBUTTON_YELLOW;
}

// Timer stuff
ISR(TIMER1_COMPA_vect) {
  TCNT1 = TIMER_1_START;
  if (isYellowTimerRunning) {
    yellowCounterTenthSec++;
  }
  if (delayCounter > 0) {
    delayCounter--;
  }
}
ISR(TIMER2_COMPA_vect) {
  TCNT2 = TIMER_2_START;
  if (isGreenTimerRunning) {
    greenCounterMilliSec++;
  }
  if (delayCounter > 0) {
    delayCounter--;
  }
}

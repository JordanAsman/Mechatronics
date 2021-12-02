// include the library code:
#include <LiquidCrystal.h>

// LCD
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
#define LINE_1 0
#define LINE_2 1

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

// Green LED on PH3 (PIN 6)
#define REG_DDR_LED_GREEN DDRH
#define REG_PORT_LED_GREEN PORTH
#define REG_PIN_LED_GREEN PINH
#define BIT_LED_GREEN 3

// Yellow LED on PH4 (PIN 7)
#define REG_DDR_LED_YELLOW DDRH
#define REG_PORT_LED_YELLOW PORTH
#define REG_PIN_LED_YELLOW PINH
#define BIT_LED_YELLOW 4

uint16_t greenCounter = 0;
uint16_t yellowCounter = 0;

volatile uint8_t mainEventFlags = 0;
#define FLAG_PUSHBUTTON_GREEN 0x01
#define FLAG_PUSHBUTTON_YELLOW 0x02

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, LINE_1);
  lcd.print("Jordan Asman");
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

  // Mega - 3 interrupts (0, 2, 3)
  EICRA |= _BV(ISC01); // Part of FALL edge setup (set HIGH)
  EICRA &= ~ _BV(ISC00); // Part of FALL edge setup (set LOW)
  EIMSK |= _BV(INT0); // Turns on INT0 the external interrupt
  
  EICRA |= _BV(ISC21); // Part of FALL edge setup (set HIGH)
  EICRA &= ~ _BV(ISC20); // Part of FALL edge setup (set LOW)
  EIMSK |= _BV(INT2); // Turns on INT2 the external interrupt
  
  EICRA |= _BV(ISC31); // Part of FALL edge setup (set HIGH)
  EICRA &= ~ _BV(ISC30); // Part of FALL edge setup (set LOW)
  EIMSK |= _BV(INT3); // Turns on INT3 the external interrupt
  
  sei(); // Turn on interrupts! Do this last
}

void loop() {
  updateLCD();

  // Check green button press
  if (mainEventFlags & FLAG_PUSHBUTTON_GREEN) {
    delay(30); // Useful for debounce
    mainEventFlags &= ~FLAG_PUSHBUTTON_GREEN;
    if (bit_is_clear(REG_PIN_PUSHBUTTON_GREEN, BIT_PUSHBUTTON_GREEN)) {
      greenCounter++;
      REG_PORT_LED_YELLOW &= ~_BV(BIT_LED_YELLOW);
      REG_PORT_LED_GREEN |= _BV(BIT_LED_GREEN);
    }
  }  
  // Check yellow button press
  if (mainEventFlags & FLAG_PUSHBUTTON_YELLOW) {
    delay(30); // Useful for debounce
    mainEventFlags &= ~FLAG_PUSHBUTTON_YELLOW;
    if (bit_is_clear(REG_PIN_PUSHBUTTON_YELLOW, BIT_PUSHBUTTON_YELLOW)) {
      yellowCounter++;
      REG_PORT_LED_YELLOW |= _BV(BIT_LED_YELLOW);
      REG_PORT_LED_GREEN &= ~_BV(BIT_LED_GREEN);
    }
  } 
}

void updateLCD() {
  lcd.setCursor(0, LINE_2);
  lcd.print("G=");
  lcd.print(greenCounter);
    
  lcd.setCursor(5, LINE_2);
  lcd.print("Y=");
  lcd.print(yellowCounter);
  
  lcd.setCursor(10, LINE_2);
  lcd.print("T="); 
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
}

// Mega - Reset Button
ISR(INT0_vect) {
  greenCounter = 0;
  yellowCounter = 0;
  REG_PORT_LED_YELLOW &= ~_BV(BIT_LED_YELLOW);
  REG_PORT_LED_GREEN &= ~_BV(BIT_LED_GREEN);
  lcd.setCursor(0, LINE_2);
  lcd.print("G=0  Y=0  T=    ");
}
// Mega - Green Button
ISR(INT2_vect) { 
  mainEventFlags |= FLAG_PUSHBUTTON_GREEN;
}
// Mega - Yellow Button
ISR(INT3_vect) {
  mainEventFlags |= FLAG_PUSHBUTTON_YELLOW;
}

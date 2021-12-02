// Note: Pin 13 on Aurdino is PB7 on Mega2560
// Note: Pin 6 on Aurdino is PH3 on Mega2560

/*
// LED_BUILTIN is PB7
#define REG_DDR_LED DDRB
#define REG_PORT_LED PORTB
#define REG_PIN_LED PINB
#define BIT_LED 7
*/

// Pin 6 is PH3
#define REG_DDR_LED DDRH
#define REG_PORT_LED PORTH
#define BIT_LED 3

void setup()
{
  // Set up pin 13 
  REG_DDR_LED |= _BV(BIT_LED);
}

void loop()
{
  // writes pin 13 high
  REG_PORT_LED |= _BV(BIT_LED);
  
  delay(1000); // Wait for 1000 millisecond(s)
  
  // writes pin 13 low
  REG_PORT_LED &= ~_BV(BIT_LED);
  
  delay(1000); // Wait for 1000 millisecond(s)
}

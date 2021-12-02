/*
// Pin 8 on uno is PB0
#define REG_DDR_BUTTON DDRB
#define REG_PORT_BUTTON PORTB
#define REG_PIN_BUTTON PINB
#define BIT_BUTTON 0

// Pin 9 on uno is PB1
#define REG_DDR_RELAY DDRB
#define REG_PORT_RELAY PORTB
#define REG_PIN_RELAY PINB
#define BIT_RELAY 1
*/

// Pin 8 on Mega2560 is PH5
#define REG_DDR_BUTTON DDRH
#define REG_PORT_BUTTON PORTH
#define REG_PIN_BUTTON PINH
#define BIT_BUTTON 5

// Pin 9 on Mega2560 is PH6
#define REG_DDR_RELAY DDRH
#define REG_PORT_RELAY PORTH
#define REG_PIN_RELAY PINH
#define BIT_RELAY 6

void setup()
{
  REG_DDR_RELAY |= _BV(BIT_RELAY);
  
  REG_DDR_BUTTON &= ~_BV(BIT_BUTTON);
  REG_PORT_BUTTON |= _BV(BIT_BUTTON);
}

void loop()
{
  if (bit_is_clear(REG_PIN_BUTTON, BIT_BUTTON)) {
    REG_PORT_RELAY |= _BV(BIT_RELAY);
  }
  else {
    REG_PORT_RELAY &= ~_BV(BIT_RELAY);
  }
  
  delay(10); // Delay a little bit to improve simulation performance
}

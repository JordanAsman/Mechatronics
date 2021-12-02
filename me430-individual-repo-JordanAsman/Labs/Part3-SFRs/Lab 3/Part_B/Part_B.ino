/*
  Keyboard

  Plays a pitch that changes based on a changing
  input circuit:
  * 3 pushbuttons from +5V to analog in 0 through
  3
  * 3 10K resistors from analog in 0 through 3 to
  ground
  * 8-ohm speaker on digital pin 8
*/

// 2 on Mega2560 is PE4
#define REG_DDR_LEFTBUTTON DDRE
#define REG_PORT_LEFTBUTTON PORTE
#define REG_PIN_LEFTBUTTON PINE
#define BIT_LEFTBUTTON 4

// 3 on Mega2560 is PE5
#define REG_DDR_MIDDLEBUTTON DDRE
#define REG_PORT_MIDDLEBUTTON PORTE
#define REG_PIN_MIDDLEBUTTON PINE
#define BIT_MIDDLEBUTTON 5

// 4 on Mega2560 is PG5
#define REG_DDR_RIGHTBUTTON DDRG
#define REG_PORT_RIGHTBUTTON PORTG
#define REG_PIN_RIGHTBUTTON PING
#define BIT_RIGHTBUTTON 5

// Pin 42 on Mega2560 is PL7
#define REG_DDR_ADDEDBUTTON DDRL
#define REG_PORT_ADDEDBUTTON PORTL
#define REG_PIN_ADDEDBUTTON PINL
#define BIT_ADDEDBUTTON 7

// Pin 8 on Mega2560 is PH5
#define REG_DDR_SPEAKER DDRH
#define REG_PORT_SPEAKER PORTH
#define REG_PIN_SPEAKER PINH
#define BIT_SPEAKER 5

// Pin 43 on Mega2560 is PL6
#define REG_DDR_LED DDRL
#define REG_PORT_LED PORTL
#define REG_PIN_LED PINL
#define BIT_LED 6


int pos = 0;

void setup()
{
  REG_DDR_SPEAKER |= _BV(BIT_SPEAKER);
  REG_DDR_LED |= _BV(BIT_LED);
  
  REG_DDR_LEFTBUTTON &= ~_BV(BIT_LEFTBUTTON);
  REG_PORT_LEFTBUTTON |= _BV(BIT_LEFTBUTTON);
  
  REG_DDR_MIDDLEBUTTON &= ~_BV(BIT_MIDDLEBUTTON);
  REG_PORT_MIDDLEBUTTON |= _BV(BIT_MIDDLEBUTTON);
  
  REG_DDR_RIGHTBUTTON &= ~_BV(BIT_RIGHTBUTTON);
  REG_PORT_RIGHTBUTTON |= _BV(BIT_RIGHTBUTTON);
  
  REG_DDR_ADDEDBUTTON &= ~_BV(BIT_ADDEDBUTTON);
  REG_PORT_ADDEDBUTTON |= _BV(BIT_ADDEDBUTTON);
}

void loop()
{
  if (bit_is_clear(REG_PIN_LEFTBUTTON, BIT_LEFTBUTTON)) {
    tone(8, 523, 100); // play tone 60 (C5 = 523 Hz)
    //REG_PORT_LED &= ~_BV(BIT_LED);
  }
  
  if (bit_is_clear(REG_PIN_MIDDLEBUTTON, BIT_MIDDLEBUTTON)) {
    tone(8, 587, 100); // play tone 61 (D5 = 587 Hz)
    //REG_PORT_LED &= ~_BV(BIT_LED);
  }
  
  if (bit_is_clear(REG_PIN_RIGHTBUTTON, BIT_RIGHTBUTTON)) {
    tone(8, 659, 100); // play tone 62 (E5 = 659 Hz)
    //REG_PORT_LED &= ~_BV(BIT_LED);
  }
  
  if (bit_is_clear(REG_PIN_ADDEDBUTTON, BIT_ADDEDBUTTON)) {
    //tone(8, 784, 100); // play tone 63 (G5 = 784 Hz)
    // reverse of what you think because wired to power through resistor, not ground
    REG_PORT_LED &= ~_BV(BIT_LED);
  }
  else {
    // reverse of what you think because wired to power through resistor, not ground
    REG_PORT_LED |= _BV(BIT_LED);
  }
  
  REG_PORT_SPEAKER &= ~_BV(BIT_SPEAKER);
  
  
  delay(10); // Delay a little bit to improve simulation performance
}

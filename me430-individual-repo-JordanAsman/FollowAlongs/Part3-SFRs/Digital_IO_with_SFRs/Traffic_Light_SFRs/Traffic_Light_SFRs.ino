// Pin 6 on Aurdino is PH3 on Mega2560
#define REG_DDR_LED_RED DDRH
#define REG_PORT_LED_RED PORTH
#define REG_PIN_LED_RED PINH
#define BIT_LED_RED 3

// Pin 5 on Aurdino is PE3 on Mega2560
#define REG_DDR_LED_YELLOW DDRE
#define REG_PORT_LED_YELLOW PORTE
#define REG_PIN_LED_YELLOW PINE
#define BIT_LED_YELLOW 3

// Pin 4 on Aurdino is PG5 on Mega2560
#define REG_DDR_LED_GREEN DDRG
#define REG_PORT_LED_GREEN PORTG
#define REG_PIN_LED_GREEN PING
#define BIT_LED_GREEN 5

// Pin 2 on Aurdino is PE4 on Mega2560
#define REG_DDR_PUSHBUTTON DDRE
#define REG_PORT_PUSHBUTTON PORTE
#define REG_PIN_PUSHBUTTON PINE
#define BIT_PUSHBUTTON 4

void setup()
{  
  REG_DDR_LED_RED |= _BV(BIT_LED_RED);
  REG_DDR_LED_YELLOW |= _BV(BIT_LED_YELLOW);
  REG_DDR_LED_GREEN |= _BV(BIT_LED_GREEN);
  
  REG_DDR_PUSHBUTTON &= ~_BV(BIT_PUSHBUTTON); // This is aready the default
  REG_PORT_PUSHBUTTON |= _BV(BIT_PUSHBUTTON); // Turn on the internal pull up resistors
}

void loop()
{
  if (bit_is_clear(REG_PIN_PUSHBUTTON, BIT_PUSHBUTTON)) 
  {
    REG_PORT_LED_RED &= ~_BV(BIT_LED_RED);
    REG_PORT_LED_YELLOW &= ~_BV(BIT_LED_YELLOW);
    REG_PORT_LED_GREEN |= _BV(BIT_LED_GREEN);
    delay(1000);
    REG_PORT_LED_RED &= ~_BV(BIT_LED_RED);
    REG_PORT_LED_YELLOW |= _BV(BIT_LED_YELLOW);
    REG_PORT_LED_GREEN &= ~_BV(BIT_LED_GREEN);
    delay(500);
  }
  REG_PORT_LED_RED |= _BV(BIT_LED_RED);
  REG_PORT_LED_YELLOW &= ~_BV(BIT_LED_YELLOW);
  REG_PORT_LED_GREEN &= ~_BV(BIT_LED_GREEN);
 }

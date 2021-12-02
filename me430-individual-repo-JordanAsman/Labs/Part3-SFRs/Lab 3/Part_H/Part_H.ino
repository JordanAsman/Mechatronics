#include <LiquidCrystal.h>

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

void setup() {
  lcd.begin(16, 2);
  
  // TODO: Setup the ADC using ADCSRA and ADMUX
  // 1. Enable the ADC
  
  // ADEN - enable bit - logical 1
  // ADSC - start conversion bit - logical 0 (changes once conversion complete)
  // ADATE - auto trigger enable - logical 0
  // ADIF - interrupt flag - logical 0
  // ADIE - interrupt flag - logical 0
  // ADPS2 - prescaler
  // ADPS1 - prescaler
  // ADPS0 - prescaler
  // Prescaler of 128 to get 125kHz - 111
  // ADEN ADSC ADATE ADIF ADIE ADPS2 ADPS1 ADPS0
  // 0b10000111 - 0x87
  // ADCSRA = 0x87;
  ADCSRA |= _BV(ADEN);
  
  // ACME - Analog comparator - 0
  // ADTSx - ADC auto trigger source bits (free running - 000)
  // - ACME - - - ADTS2 ADTS1 ADTS0
  // 0b00000000 - 0x00
  // ADCSRB = 0x00;
  
  // 2. Set the reference voltage for what 1023 equals
  //    - Use the AVCC with external capacitor at AREF pin option.
  // Pin A0 -- ADC0 -- 0000
  // Pin A3 -- ADC3 -- 0011
  // AREF -- REFS0 - 1, REFS1 - 0 --> AMUX3-AMUX0 
  // ADLAR - 0
  // REFS1 REFS0 ADLAR - MUX3 MUX2 MUX1 MUX0
  // 0b01000000 (Pin A0) 0x40
  // 0b01000011 (Pin A3) 0x43
  // ADMUX = 0x40;
  ADMUX &= ~_BV(REFS1);
  ADMUX |= _BV(REFS0);
}

void loop() {  
  lcd.setCursor(0, 0);
  lcd.print("ADC 0 = ");
  lcd.print(getADC0());
  lcd.print("   ");
  
  lcd.setCursor(0, 1);
  lcd.print("ADC 15 = ");
  lcd.print(getADC15());
  lcd.print("   ");
  
  delay(100);
}

uint16_t getADC0() {
  //return analogRead(0);  // Comment out this line
  // TODO: Select which pin you want to read via ADMUX
  ADMUX &= ~_BV(MUX4);
  ADMUX &= ~_BV(MUX3);
  ADMUX &= ~_BV(MUX2);
  ADMUX &= ~_BV(MUX1);
  ADMUX &= ~_BV(MUX0);
  // Start the conversion by setting a certain bit 
  ADCSRA |= _BV(ADSC);
  // Do nothing in a while loop until the ADC convert is complete
  while (bit_is_set(ADCSRA, ADSC)) {
    // Do nothing!
  }
  // Read the result using the magic ADC register
  return ADC;
}

uint16_t getADC15() {
  //return analogRead(15);  // Comment out this line
  // TODO: Select which pin you want to read via ADMUX5 - 100111
  ADCSRB |= _BV(MUX5);
  ADMUX &= ~_BV(MUX4);
  ADMUX &= ~_BV(MUX3);
  ADMUX |= _BV(MUX2);
  ADMUX |= _BV(MUX1);
  ADMUX |= _BV(MUX0);
  // Start the conversion by setting a certain bit
  ADCSRA |= _BV(ADSC);
  // Do nothing in a while loop until the ADC convert is complete
  while (bit_is_set(ADCSRA, ADSC)) {
    // Do nothing!
  }
  // Read the result using the magic ADC register
  return ADC;
}

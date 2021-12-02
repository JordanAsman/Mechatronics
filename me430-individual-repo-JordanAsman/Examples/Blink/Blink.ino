/*
  Blink - Turns an LED on for one second, then off for one second, repeatedly.
  An LED is build onto the Arduino board, connected to Pin 13.
*/

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);  // Pin 13
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
 
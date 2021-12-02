// C++ code
//
void setup()
{
  // Setup the 3 LEDs and the push button
  pinMode(2, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop()
{
  if (digitalRead(2) == 0) {
    // Green
    digitalWrite(13, LOW);
    digitalWrite(11, HIGH);
    delay(2000); // Wait for 2000 millisecond(s)
    // Yellow
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);
  }
  delay(500); // Wait for 500 millisecond(s)
  // Red
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
}

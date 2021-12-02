// Part E
void setup()
{
  // Inputs
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  
  // Outputs for LEDS
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  
  // Outputs for other things
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop()
{
  // Outputs for LEDS
  digitalWrite(4, !digitalRead(2));
  digitalWrite(5, !digitalRead(3));
  analogWrite(6, analogRead(0)/4);

  // Outputs for other things
  digitalWrite(12, !digitalRead(2));
  digitalWrite(13, !digitalRead(3));
  analogWrite(11, analogRead(0)/4);
  
  delay(10);
}

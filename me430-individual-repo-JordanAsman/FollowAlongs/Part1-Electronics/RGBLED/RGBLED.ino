// These are global variables
int rPot = 0;
int bPot;

void setup()
{
  // Set-up serial communication
  // 9600 is the com. speed in bits per second
  Serial.begin(9600);
  
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  
  // Add the pull up resistor
  pinMode(2, INPUT_PULLUP);
  
  // k = k + 1 shorthand is k++
  
  // For loop example
  // for (int k = 0; k < 5; k = k + 1)
  // {
  //    Serial.println(k);
  //   delay(500);
  // }
}

void loop()
{
  // To read the red potentiometer
  rPot = analogRead(A0);
  Serial.print(" R=");
  Serial.print(rPot);
  // println makes sure end of line is after what it has to print
  
  bPot = analogRead(A1);
  Serial.print(" B=");
  Serial.println(bPot);
  
  // write to digital ports
  // digitalWrite(9, HIGH);
  
  // write to analog ports (if ~ then doubles as analog)
  // analogWrite(9, 255);
  // analogWrite(10, 0);
  // analogWrite(11, 0);

  
  // if(), else if(), and else() statements  
  // if statements assume that if 0 then false, if non-0 then true
  // High is 1, Low is 0
  if (digitalRead(2))
  {
    // Divide by 4 takes 10 bit number to 4 bit
    rgb(rPot/4, 0, bPot/4);
  }
  else 
  {
    off();
  }
  
  // delays in miliseconds
  delay(50);
}

// write own function
// start with return, then function name, then arguments
// variables in handle are local variables

void rgb(int r, int g, int b)
{
  // Parameters should be 0 to 255
  analogWrite(9, r);
  analogWrite(10, g);
  analogWrite(11, b);
  
}

void red()
{
  analogWrite(9, 255);
  analogWrite(10, 0);
  analogWrite(11, 0);
}

void green()
{
  analogWrite(9, 0);
  analogWrite(10, 255);
  analogWrite(11, 0);
}

void blue()
{
  analogWrite(9, 0);
  analogWrite(10, 0);
  analogWrite(11, 255);
}

void off()
{
  analogWrite(9, 0);
  analogWrite(10, 0);
  analogWrite(11, 0);
}

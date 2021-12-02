uint8_t speedCounter = 2;
int threshold = 512;
int sensorLeft;
int sensorRight;

void setup() {
  pinMode(2, INPUT_PULLUP);  // Push button increment
  pinMode(3, OUTPUT);        // Analog output
  pinMode(4, INPUT_PULLUP);  // Push button reset
  pinMode(5, OUTPUT);        // Analog output
  pinMode(A0, INPUT_PULLUP); // Analog reading
  pinMode(A1, INPUT_PULLUP); // Analog reading
  
  pinMode(6, OUTPUT);  // A
  pinMode(7, OUTPUT);  // B
  pinMode(8, OUTPUT);  // C
  pinMode(9, OUTPUT);  // D
  pinMode(10, OUTPUT); // E
  pinMode(11, OUTPUT); // F
  pinMode(12, OUTPUT); // G
  pinMode(13, OUTPUT); // DP

  // Serial.begin(9600);
}

void set7SegmentValue(uint8_t value) {
  switch (value) {
    case 0:
      digitalWrite7Segment(1, 1, 1, 1, 1, 1, 0);
      break;
    case 1:
      digitalWrite7Segment(0, 1, 1, 0, 0, 0, 0); // 0 is LOW, 1 is HIGH
      break;
    case 2:
      digitalWrite7Segment(1, 1, 0, 1, 1, 0, 1);
      break;
    case 3:
      digitalWrite7Segment(1, 1, 1, 1, 0, 0, 1);
      break;
    case 4:
      digitalWrite7Segment(0, 1, 1, 0, 0, 1, 1);
      break;
    case 5:
      digitalWrite7Segment(1, 0, 1, 1, 0, 1, 1);
      break;
    case 6:
      digitalWrite7Segment(1, 0, 1, 1, 1, 1, 1);
      break;
    case 7:
      digitalWrite7Segment(1, 1, 1, 0, 0, 0, 0);
      break;
    case 8:
      digitalWrite7Segment(1, 1, 1, 1, 1, 1, 1);
      break;
    case 9:
      digitalWrite7Segment(1, 1, 1, 1, 0, 1, 1);
      break;
    case 10:
      digitalWrite7Segment(1, 1, 1, 0, 1, 1, 1); // A (A = 10 in hex)
      break;
    default:
      digitalWrite7Segment(0, 0, 0, 0, 0, 0, 0);
      break;
  }
}

void digitalWrite7Segment(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e, uint8_t f, uint8_t g) {
  int x[7];
  x[0] = a;
  x[1] = b;
  x[2] = c;
  x[3] = d;
  x[4] = e;
  x[5] = f;
  x[6] = g;
  for (int j = 6; j <= 12; j++) {
    digitalWrite(j, x[j-6]);
  }
}

void loop() {  
  if (!digitalRead(2)) {
    if (speedCounter < 5) {
      speedCounter++;
      set7SegmentValue(speedCounter);
      delay(500);
    }
  }

  if (!digitalRead(4)) {
    speedCounter = 0;
    set7SegmentValue(speedCounter);
    delay(500);
  }
  
  sensorLeft = analogRead(0);
  set7SegmentValue(sensorLeft/100);
  if (sensorLeft < threshold) {
    digitalWrite(13, HIGH);
    analogWrite(3, speedCounter * 50);
    // Serial.println(String("Speed  Counter is ") + speedCounter);
    // Serial.println(String("Speed  Counter 50 is ") + speedCounter*50);
  }
  else {
    digitalWrite(13, LOW);
    analogWrite(3, 0);
  }
  
  sensorRight = analogRead(1);
  set7SegmentValue(sensorLeft/100);
  if (sensorRight < threshold) {
    digitalWrite(13, HIGH);
    analogWrite(5, speedCounter * 50);
  }
  else {
    digitalWrite(13, LOW);
    analogWrite(5, 0);
  }
}
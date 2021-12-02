#define START_BEAM 52

void setup() {
  // put your setup code here, to run once:
  pinMode(START_BEAM, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  checkBeam();
}

void checkBeam() {
  if (digitalRead(START_BEAM) == 1) {
    // All if good
    Serial.println("All good");
  }
  else if (digitalRead(START_BEAM) == 0) {
    // Beam broken
    Serial.println("Beam Broken!!!");
  }
}

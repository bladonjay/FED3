int irPin = 11;
bool reported = false;
bool hasFed = false;
bool lastState = HIGH;
long holdTime = 5000; // msec
unsigned long breakTime;

void setup() {

pinMode(irPin,INPUT_PULLUP);

Serial.begin(9600);
  while (!Serial) {
    delay(10); // wait for serial port to connect. Needed for native USB port only
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  if (digitalRead(irPin) == LOW){
    if (lastState == HIGH){
      breakTime = millis();
      Serial.println("Beam Broken");
    }
    lastState = LOW;
    if (((millis() - breakTime)>holdTime) && !hasFed) {
      Serial.println("Broke for 5 seconds");
      hasFed = true;
    }
  } else {
    if (lastState == LOW){
      Serial.println("Beam UN-Broken");
    }
    lastState = HIGH;
    hasFed = false;
  }
  
  
  long thistime = millis();
  if ((thistime & 1000) == 0) {
    if (reported == false) {
      Serial.println("One Second has Passed");
    }
    reported = true;
  }
  else {
    reported = false;
  }
}

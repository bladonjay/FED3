// include the library first
# include initLinear.h

#if defined(ARDUINO_SAMD_ZERO) && defined(SERIAL_PORT_USBVIRTUAL)
// Required for Serial on Zero based boards
#define Serial SERIAL_PORT_USBVIRTUAL
#endif

void setup() {
  // set up our I/O pins
  pinMode(rightBeam, INPUT_PULLUP);
  pinMode(leftBeam, INPUT_PULLUP);
  pinMode(centerBeam, INPUT_PULLUP);

  pinMode(rightFeed, OUTPUT);
  pinMode(leftFeed, OUTPUT);
  pinMode(centerFeed, OUTPUT);
  pinMode(ledPin, OUTPUT);

  // open serial port, or
  Serial.begin(9600);
  while (!Serial && iterator < 100) {
    ++iterator; // wait for serial port to connect. Needed for native USB port only
  }
  if (Serial) {
    Serial.println(F("Serial debug started"));
  }
  iterator = 0;
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  while (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C) && iterator < 100) { // Address 0x3C for 128x32
    ++iterator;
    if (iterator == 100) {
      Serial.println(F("SSD1306 allocation failed"));
    }
  }
  iterator = 0;
  Serial.println("SSD1306 initialized");
  // initialize sd card at pin 10
  if (!SD.begin(chipSelect)) {
    ++iterator;
    if (iterator == 100) {
      Serial.println(F("card initialization failed"));
    }
  }
  Serial.println("card initialized.");
  iterator = 0;
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(1000); // Pause for 2 seconds

  // Clear the buffer, set text parameters
  display.clearDisplay();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  // RunMouse();
  // delay(2000);
  // tone (BUZZER, 500, 500);
  optScreen();
  startScreen();
}

void loop() {

  RunLinTrack();

}


// imbed startup screen into a function
void startScreen() {

  display.clearDisplay();
  display.setCursor(30, 0);     // Start at top-left corner

  // create the home screen
  display.println(F("Linear Track"));
  display.fillRect(116, 4, 8, 6, SSD1306_WHITE);
  display.fillRect(124, 6, 4, 2, SSD1306_WHITE);

  display.fillCircle(123, 3, 2, SSD1306_BLACK); // centerx centery rad, color
  display.drawCircle(123, 3, 2, SSD1306_WHITE);

  display.fillCircle(116, 3, 2, SSD1306_BLACK); // centerx centery rad, color
  display.drawCircle(116, 3, 2, SSD1306_WHITE);

  display.drawCircle(31, 12, 3, SSD1306_WHITE);
  display.drawCircle(95, 12, 3, SSD1306_WHITE);
  display.drawFastHLine(34, 12, 58, SSD1306_WHITE);

  display.setCursor(16, 16);
  display.println(F("Lrew:"));
  display.setCursor(72, 16);
  display.println(F("Rrew:"));
  display.setCursor(0, 24);
  display.println(F("T=12:12"));
  display.setCursor(54, 24);
  display.println(F("File:test001"));


  display.display();
}


void RunLinTrack() {
  // check left beam, if its unbroken, turn off pin and open circle
  if (digitalRead(leftBeam) == HIGH) {
    digitalWrite(ledPin, LOW);
    display.fillCircle(31, 12, 3, SSD1306_BLACK); // centerx centery rad, color
  }
  else {
    // if left beam broken, and last well wasnt this one, feed, reset
    if (lastWell != 1) {
      ++Lrew;
      // update display settings
      display.fillRect(44, 16, 18, 8, SSD1306_BLACK);
      display.setCursor(44, 16);
      String Lstr = String(Lrew);
      display.println(Lstr);
    }
    lastWell = 1;
    digitalWrite(ledPin, HIGH);
    display.fillCircle(31, 12, 3, SSD1306_WHITE);
  }

  if (digitalRead(rightBeam) == HIGH) {
    digitalWrite(ledPin, LOW);
    display.fillCircle(95, 12, 3, SSD1306_BLACK); // centerx centery rad, color
  }
  else {
    if (lastWell != 2) {
      ++Rrew;
      display.fillRect(100, 16, 18, 8, SSD1306_BLACK);
      display.setCursor(100, 16);
      String Rstr = String(Rrew);
      display.println(Rstr);
    }
    lastWell = 2;
    digitalWrite(ledPin, HIGH);
    display.fillCircle(95, 12, 3, SSD1306_WHITE);
  }
  display.drawCircle(95, 12, 3, SSD1306_WHITE);
  display.drawCircle(31, 12, 3, SSD1306_WHITE);
  display.display();
}


void RunMouse() {
  display.clearDisplay();
  for (int i = -50; i < 200; i += 10) {
    display.setCursor(0, 16);
    //Draw animated mouse...
    display.fillRoundRect (i + 25, 17, 14, 10, 4, SSD1306_WHITE);  //head
    display.fillRoundRect (i + 35, 19, 2, 2, 1, SSD1306_WHITE);    //eye
    //movement of the mouse
    if ((i / 10) % 2 == 0) {
      display.fillRoundRect (i, 19, 32, 14, 10, SSD1306_WHITE);      //body
      display.drawFastHLine(i - 8, 20, 18, SSD1306_WHITE);        //tail
      display.drawFastHLine(i - 8, 21, 18, SSD1306_WHITE);
      display.drawFastHLine(i - 14, 19, 8, SSD1306_WHITE);
      display.drawFastHLine(i - 14, 20, 8, SSD1306_WHITE);

      display.fillRoundRect (i + 22, 30, 8, 4, 3, SSD1306_WHITE);  //front foot
      display.fillRoundRect (i , 30, 8, 6, 3, SSD1306_INVERSE); //back foot
    }
    else {
      display.fillRoundRect (i + 2, 18, 30, 12, 10, SSD1306_WHITE);    //body
      display.drawFastHLine(i - 6, 26, 18, SSD1306_WHITE);        //tail
      display.drawFastHLine(i - 6, 25, 18, SSD1306_WHITE);
      display.drawFastHLine(i - 12, 27, 8, SSD1306_WHITE);
      display.drawFastHLine(i - 12, 26, 8, SSD1306_WHITE);

      display.fillRoundRect (i + 15, 30, 8, 4, 3, SSD1306_WHITE);  //foot
      display.fillRoundRect (i + 8, 30, 8, 6, 3, SSD1306_INVERSE); //back foot
    }
    display.fillRoundRect (i + 22, 15, 8, 5, 3, SSD1306_INVERSE);    //ear
    display.display();
    delay (200);
    display.clearDisplay();
  }

  display.fillRoundRect (40, 17, 14, 10, 6, SSD1306_WHITE);  //head
  display.fillRoundRect (17, 18, 30, 12, 10, SSD1306_WHITE);    //body
  display.drawFastHLine(9, 26, 18, SSD1306_WHITE);        //tail
  display.drawFastHLine(9, 25, 18, SSD1306_WHITE);
  display.drawFastHLine(3, 27, 8, SSD1306_WHITE);
  display.drawFastHLine(3, 26, 8, SSD1306_WHITE);

  display.fillRoundRect (30, 30, 8, 4, 3, SSD1306_INVERSE);  //foot
  display.fillRoundRect (23, 30, 8, 6, 3, SSD1306_INVERSE);

  display.fillRoundRect (37, 15, 8, 5, 3, SSD1306_INVERSE);    //ear
  display.fillRoundRect (50, 19, 1, 1, 1, SSD1306_INVERSE);    //eye

  display.setCursor(62, 18);
  display.println(F("AdaptaMaze"));

  display.display();
}

void getParams() {

}

void optScreen() {
  // establish what wont change
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(16, 0);
  display.println ("Select Program");
  display.setCursor(0, 16);
  display.println("Use Right and Left Beams");
  display.display();
  delay(300);
  // if anything down, set the feedmode, otherwise count down
  while (iterator < 100) {

    bool upvalL = digitalRead(leftBeam);
    bool upvalR = digitalRead(rightBeam);
    if (upvalL == 1 && upvalR == 1) {
      display.drawFastHLine(iterator * 1.28, 30, 2, SSD1306_WHITE);
      display.display();
      ++iterator;

    }
    else {
      // first wipe the bottom screen
      display.fillRect(0, 8, 128, 24, SSD1306_BLACK);
      display.setCursor(16, 16);

      if (upvalL == 0) {
        iterator = 0;
        ++taskMode;
      }

      if (upvalR == 0) {
        iterator = 0;
        --taskMode;
      }

      if (taskMode < 1) {
        taskMode = 5;
      }

      if (taskMode > 5) {
        taskMode = 1;
      }
      // update screen
      if (taskMode == 1) {
        display.println("Linear Track");
      }
      if (taskMode == 2) {
        display.println("W-Maze Center");
      }
      if (taskMode == 3) {
        display.println("W-Maze Left");
      }
      if (taskMode == 4) {
        display.println("W-Maze Right");
      }
      if (taskMode == 5) {
        display.println("Social Task");
      }
      display.display();
    }
    delay(100);
  }

}

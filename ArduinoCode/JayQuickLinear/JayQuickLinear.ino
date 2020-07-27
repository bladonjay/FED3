// include the library first
# include "initLinear.h"

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

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
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

  RunMouse();
  delay(1000);
  // tone (BUZZER, 500, 500);
  // grab the date from our rtc.
  DateTime now = rtc.now();
  optScreen();
  saveScreen();
  makeFile();
  starttime = millis();
  startScreen();
}

void loop() {
  // update counters
  RunLinTrack();
  // and update the timer
  displayElapsedTime();
}

void RunLinTrack() {
  upvalL = digitalRead(leftBeam);
  upvalR = digitalRead(rightBeam);
  // if both are broken, lets break tot he next iteration, because this is basically a pause
  if (upvalL == 0 && upvalR == 0) {
    // this might be a good place to close the file and kill the loop
    //display.setCursor(64,24);
    //display.println(F("Stop Rec"));
    return;
  }
  // check left beam, if its unbroken, turn off pin and open circle
  if (upvalL == 1) {
    digitalWrite(ledPin, LOW);
    display.fillCircle(32, 12, 2, SSD1306_BLACK); // centerx centery rad, color
  }
  else {
    // if left beam broken, and last well wasnt this one, feed, reset
    if (lastWell != 1) {
      ++Lrew;
      // update display settings
      display.fillRect(34, 16, 18, 8, SSD1306_BLACK);
      display.setCursor(36, 16);
      String Lstr = String(Lrew);
      display.println(Lstr);
    }
    lastWell = 1;
    digitalWrite(ledPin, HIGH);
    display.fillCircle(32, 12, 2, SSD1306_WHITE);
  }

  // if right beam broken
  if (upvalR == 1) {
    digitalWrite(ledPin, LOW);
    display.fillCircle(94, 12, 2, SSD1306_BLACK); // centerx centery rad, color
  }
  else {
    if (lastWell != 2) {
      ++Rrew;
      display.fillRect(93, 16, 18, 8, SSD1306_BLACK);
      display.setCursor(94, 16);
      String Rstr = String(Rrew);
      display.println(Rstr);
    }
    lastWell = 2;
    digitalWrite(ledPin, HIGH);
    display.fillCircle(94, 12, 2, SSD1306_WHITE);
  }
  // draw outlines
  display.drawCircle(94, 12, 2, SSD1306_WHITE);
  display.drawCircle(32, 12, 2, SSD1306_WHITE);
  display.display();
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

    upvalL = digitalRead(leftBeam);
    upvalR = digitalRead(rightBeam);
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
  iterator = 0;
  display.clearDisplay();
  display.setCursor(16, 0);
  display.println("You Chose");

  // update screen
  if (taskMode == 1) {
    display.setCursor(16, 8);
    display.println("Linear Track");
  }
  if (taskMode == 2) {
    display.setCursor(16, 8);
    display.println("W-Maze Center");
  }
  if (taskMode == 3) {
    display.setCursor(16, 8);
    display.println("W-Maze Left");
  }
  if (taskMode == 4) {
    display.setCursor(16, 8);
    display.println("W-Maze Right");
  }
  if (taskMode == 5) {
    display.setCursor(16, 8);
    display.println("Social Task");
  }
  display.display();
  delay(1000);

}

void saveScreen() {
  // establish what wont change
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(16, 0);
  display.println ("Want to");
  display.setCursor(0, 8);
  display.println("Save your data?");
  display.setCursor(24, 16);
  display.println("Yes");
  display.setCursor(76, 16);
  display.println("No");
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
      display.fillRect(0, 24, 128, 8, SSD1306_BLACK);
      // wipe the two opt dots
      display.fillCircle(20, 20, 2, SSD1306_BLACK);
      display.fillCircle(90, 20, 2, SSD1306_BLACK);


      if (upvalL == 0) {
        iterator = 0;
        ++saveOpt;
        if (saveOpt > 2) {
          saveOpt = 1;
        }
      }

      if (upvalR == 0) {
        iterator = 0;
        --saveOpt;
        if (saveOpt < 1) {
          saveOpt = 2;
        }
      }

      if (saveOpt == 1) {
        display.fillCircle(20, 20, 2, SSD1306_WHITE);
      }

      if (saveOpt == 2) {
        display.fillCircle(90, 20, 2, SSD1306_WHITE);
      }
    }
    delay(200);
  }
  // done with the options loop,
  iterator = 0;  // reset, its just a placeholder for the prog bar anyways
  delay(400);
  display.clearDisplay();
  display.setCursor(0, 0);
  DateTime now = rtc.now();
  if (saveOpt = 1) {
    display.println(F("Will Save"));
    display.setCursor(8, 8);
    display.println(F("Naming file:"));
    // need to add here the filename and file generator function
  }
  if (saveOpt == 2) {
    display.println(F("Wont Save"));
    display.setCursor(8, 8);
    display.println(F("Today is: "));
    display.setCursor(16, 16);
    Serial.print(now.year(), DEC);
    Serial.print(' / ');
    Serial.print(now.month(), DEC);
    Serial.print(' / ');
    Serial.print(now.day(), DEC);
  }
  display.display();
  delay(1000);
}

void displayElapsedTime() {
  // this goes via millis as a counter, but i may try to double check it
  // you can either use millis() to gather your clock tics
  thistime = millis();
  strcpy(mydateHMS, "__:__:__");  // placeholder filename
  int thishour = (thistime - starttime) / 3600000;
  int thisminute = ((thistime - starttime) - (thishour * 3600000)) / 60000;
  int thissecond = ((thistime - starttime) - (thishour * 3600000) - (thisminute * 60000)) / 1000;

  mydateHMS[0] = thishour / 10 + '0';
  mydateHMS[1] = thishour % 10 + '0';

  mydateHMS[3] = thisminute / 10 + '0';
  mydateHMS[4] = thisminute % 10 + '0';

  mydateHMS[6] = thissecond / 10 + '0';
  mydateHMS[7] = thissecond % 10 + '0';
  display.setCursor(0, 24);
  display.fillRect(0, 24, 48, 8, SSD1306_BLACK);
  display.print(F(mydateHMS));
  display.display();


}



// or you can use the pcf8523 timer function to initiate a ~50 hz timer
// this works by asigning the timer to 'tic' on an interrupt pin, and the
// interrupt will save out those increments (with much higher accuracy)

// either way, i think its not that big a deal because we're going to jitter by ~1 - 5 %

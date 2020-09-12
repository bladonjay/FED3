
void ratSplashScreen() {
  display.clearDisplay();
  for (int i = -50; i < 200; i += 10) {
    display.setCursor(0, 16);
    //Draw animated mouse...
    display.fillRoundRect (i + 25, 17, 14, 10, 4, SSD1306_WHITE);  //head
    display.fillRoundRect (i + 37, 19, 2, 2, 1, SSD1306_BLACK);    //eye
    //movement of the mouse
    if ((i / 10) % 2 == 0) {
      display.fillRoundRect (i, 19, 32, 14, 10, SSD1306_WHITE);      //body
      display.drawFastHLine(i - 8, 20, 18, SSD1306_WHITE);        //tail
      display.drawFastHLine(i - 8, 21, 18, SSD1306_WHITE);
      display.drawFastHLine(i - 14, 19, 8, SSD1306_WHITE);
      display.drawFastHLine(i - 14, 20, 8, SSD1306_WHITE);

      display.fillRoundRect (i + 22, 30, 6, 4, 3, SSD1306_WHITE);  //front foot
      display.fillRoundRect (i     , 30, 8, 4, 3, SSD1306_WHITE); //back foot
    }
    else {
      display.fillRoundRect (i + 2, 18, 30, 12, 10, SSD1306_WHITE);    //body
      display.drawFastHLine(i - 6, 26, 18, SSD1306_WHITE);        //tail
      display.drawFastHLine(i - 6, 25, 18, SSD1306_WHITE);
      display.drawFastHLine(i - 12, 27, 8, SSD1306_WHITE);
      display.drawFastHLine(i - 12, 26, 8, SSD1306_WHITE);

      display.fillRoundRect (i + 15, 30, 6, 4, 3, SSD1306_WHITE);  //foot
      display.fillRoundRect (i + 6 , 30, 8, 4, 3, SSD1306_WHITE); //back foot
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

  display.fillRoundRect (36, 30, 6, 4, 3, SSD1306_INVERSE);  //front foot
  display.fillRoundRect (23, 30, 8, 4, 3, SSD1306_INVERSE);  // back foot

  display.fillRoundRect (37, 15, 8, 5, 3, SSD1306_INVERSE);    //ear
  display.fillRoundRect (50, 19, 1, 1, 1, SSD1306_INVERSE);    //eye

  display.setCursor(62, 18);
  display.println(F("AdaptaMaze"));
  display.display();
  delay(2000);
}


void optScreen() {
  // establish what wont change
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(16, 0);
  display.print(F("Select Program"));
  display.setCursor(8, 16);
  display.print(F("Use Right and Left")) ;
  display.setCursor(10, 24);
  display.print(F("beams to choose"));
  display.display();
  delay(300);
  // if anything down, set the feedmode, otherwise count down
  while (iterator < 100) {

    upvalL = digitalRead(leftBeam);
    upvalR = digitalRead(rightBeam);
    if (upvalL == 1 && upvalR == 1) {
      display.drawFastHLine(iterator * 1.28, 31, 2, SSD1306_WHITE);
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
  // start with no
  display.fillCircle(90, 20, 2, SSD1306_WHITE);
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
        saveOpt = !saveOpt;
      }

      if (upvalR == 0) {
        iterator = 0;
        saveOpt = !saveOpt;
      }
      // if saveOpt is 1, we save
      if (saveOpt == true) {
        display.fillCircle(20, 20, 2, SSD1306_WHITE);
      }
      // if saveOpt is false, we dont
      if (saveOpt == false) {
        display.fillCircle(90, 20, 2, SSD1306_WHITE);
      }
    }
    delay(100);
  }
  // done with the options loop,
  iterator = 0;  // reset, its just a placeholder for the prog bar anyways
  delay(400);
  display.clearDisplay();
  display.setCursor(0, 0);

  if (saveOpt == 1) {
    display.println(F("Will Save,"));
    display.setCursor(8, 8);
    display.println(F("Naming file:"));
    // need to add here the filename and file generator function
    makeFile();
  }
  if (saveOpt == 0) {
    display.println(F("Wont Save"));
    display.setCursor(8, 8);
    display.println(F("Today is: "));
    display.setCursor(16, 24);
    // just display a few times
    display.print(filename[0]);
    display.print(filename[1]);
    display.print(" / ");
    display.print(filename[2]);
    display.print(filename[3]);
    display.print(" / 20");
    display.print(filename[4]);
    display.print(filename[5]);
  }
  display.display();
}

void startScreen() {

  // here is where it would be a good idea to reset all the variables

  display.clearDisplay();
  display.setCursor(18, 16);
  display.print(F("Break a beam to"));
  display.setCursor(20, 24);
  display.print(F("start the task"));
  display.display();

  upvalL = digitalRead(leftBeam);
  upvalR = digitalRead(rightBeam);
  upvalC = digitalRead(centerBeam);

  // while no beams are broken, keep trying
  while (upvalL && upvalR  && upvalC) {
    upvalL = digitalRead(leftBeam);
    upvalR = digitalRead(rightBeam);
    upvalC = digitalRead(centerBeam);
  }
  
  attachInterrupt(digitalPinToInterrupt(timerInterruptPin), countdownOver, FALLING);

  display.clearDisplay();
  // this is the recording camera
  display.fillRect(116, 4, 8, 6, SSD1306_WHITE);
  display.fillRect(124, 6, 4, 2, SSD1306_WHITE);
  display.fillCircle(123, 3, 2, SSD1306_BLACK); // centerx centery rad, color
  display.drawCircle(123, 3, 2, SSD1306_WHITE);
  display.fillCircle(116, 3, 2, SSD1306_BLACK); // centerx centery rad, color
  display.drawCircle(116, 3, 2, SSD1306_WHITE);

  display.setCursor(12, 0);     // Start at top-left corner
  // create the home screen
  if (taskMode == 1) {
    display.println("Linear Track");
    // graphic for the track
    display.drawCircle(32, 12, 2, SSD1306_WHITE);
    display.drawCircle(94, 12, 2, SSD1306_WHITE);
    display.drawFastHLine(34, 12, 58, SSD1306_WHITE);
    display.setCursor(24, 16);
    display.println(F("L:0"));
    display.setCursor(84, 16);
    display.println(F("R:0"));
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
  if (taskMode > 1) {
    // draw the w track
    display.drawFastHLine(32, 8, 64, SSD1306_WHITE);

    display.drawFastVLine(32, 8, 3, SSD1306_WHITE);
    display.drawCircle(32, 12, 2, SSD1306_WHITE);

    display.drawFastVLine(64, 8, 3, SSD1306_WHITE);
    display.drawCircle(64, 12, 2, SSD1306_WHITE);

    display.drawFastVLine(96, 8, 3, SSD1306_WHITE);
    display.drawCircle(96, 12, 2, SSD1306_WHITE);
    display.setCursor(24, 16);
    // for three, we dont have room to label all of them...
    display.println(F("0/0"));
    display.setCursor(56, 16);
    display.println(F("0/0"));
    display.setCursor(88, 16);
    display.println(F("0/0"));
  }

  if (saveOpt) {
    display.setCursor(60, SCREEN_HEIGHT-8);
    display.print(F("Fn:"));
    display.print(F(filename));
  }
  else {
    // cross out the camera
    display.fillCircle(123, 3, 2, SSD1306_WHITE); // fix right reel
    display.drawLine(115, 10, 125, 0, SSD1306_INVERSE); // x out the camera
    display.drawLine(116, 10, 126, 0, SSD1306_INVERSE);
    // date, not file
    display.setCursor(60, SCREEN_HEIGHT-8);
    display.print("Dt:");
    display.print(filename[0]);
    display.print(filename[1]);
    display.print("/");
    display.print(filename[2]);
    display.print(filename[3]);
    display.print("/");
    display.print(filename[4]);
    display.print(filename[5]);
  }
  display.display();

  // reset all variables


  // start task
  if (taskMode == 1) {
    runLinTrack();
  }
  if (taskMode == 2) {
    runWMaze();
  }
  if (taskMode == 3) {

  }
  if (taskMode == 4) {

  }
  if (taskMode == 5) {

  }



}

void resetVars() {

  bool upvalL = false;
  bool upvalR = false;
  bool upvalC = false;
  bool wasupL = false;
  bool wasupC = false;
  bool wasupR = false;

  bool saveOpt = false;


  int lastWell = 0;
  int lastSideWell = 0;
  int Lrew = 0;
  int Rrew = 0;
  int Crew = 0;
  int Lhit = 0;
  int Rhit = 0;
  int Chit = 0;

  int taskMode = 1;
  int iterator = 0;

  float breakTime = 0;
  float thisTime = 0;
  float holdTime = 1000;

  // clock variables
  // Variables modified during an interrupt must be declared volatile
  volatile bool clockgoing = false;
  volatile int numCountdownInterrupts = 0;

  // file variables
  File logfile;
  char filename[] = "________.dat";
  char mydate[17];
  char elapsedHMS[8];
  char thisevent[] = "Task Start";
}

void finishScreen() {
  
  // save data
  elapsedTime();
  writeData("Session End");
  // stop clock
  detachInterrupt(digitalPinToInterrupt(timerInterruptPin));
  // say were done
  display.clearDisplay();
  display.setCursor(18, 0);
  display.print(F("Session Over"));
  display.setCursor(0, 8);
  display.print(F("Total time:"));
  display.print(F(elapsedHMS));
  
  display.display();
  delay(1000);
  display.setCursor(20, 16);
  display.print(F("Press restart"));
  display.setCursor(16, 24);
  display.print(F("button to start"));
  display.setCursor(18, 32);
  display.print(F("a new session"));
  display.display();
  // wait until one is broken
  while (true) {
    delay(100); // go forever
  }
}

void showElapsedTime() {
  int elapsed = numCountdownInterrupts *50;  // convert to msec
  display.fillRect(0, SCREEN_HEIGHT - 8, 48, 8, SSD1306_BLACK);
  display.setCursor(0, SCREEN_HEIGHT - 8);
  int elapsedhour = elapsed / 60 / 60 / 1000;
  int elapsedminute = (elapsed - (elapsedhour * 60 * 60 * 1000)) / 60 / 1000;
  int elapsedsecond = (elapsed - (elapsedhour * 60 * 60 * 1000) - (elapsedminute * 60 * 1000)) / 1000;
  String elapsedTime = "__:__:__.__";
  elapsedTime[0] = elapsedhour / 10 + '0';
  elapsedTime[1] = elapsedhour % 10 + '0';
  elapsedTime[3] = elapsedminute / 10 + '0';
  elapsedTime[4] = elapsedminute % 10 + '0';
  elapsedTime[6] = elapsedsecond / 1000 + '0';
  elapsedTime[7] = elapsedsecond % 1000 + '0';
  elapsedTime[9] = elapsedsecond / 100 + '0';
  elapsedTime[10] = elapsedsecond / 10 + '0';

  display.print(elapsedTime);
  display.display();
}

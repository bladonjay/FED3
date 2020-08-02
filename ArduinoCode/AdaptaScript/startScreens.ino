
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
    display.drawFastHLine(32, 9, 64, SSD1306_WHITE);

    display.drawFastVLine(32, 9, 3, SSD1306_WHITE);
    display.drawCircle(32, 14, 2, SSD1306_WHITE);

    display.drawFastVLine(64, 9, 3, SSD1306_WHITE);
    display.drawCircle(64, 14, 2, SSD1306_WHITE);

    display.drawFastVLine(96, 9, 3, SSD1306_WHITE);
    display.drawCircle(96, 14, 2, SSD1306_WHITE);
    display.setCursor(24, 16);
    // for three, we dont have room to label all of them...
    display.println(F("0/0"));
    display.setCursor(56, 16);
    display.println(F("0/0"));
    display.setCursor(88, 16);
    display.println(F("0/0"));
  }

  if (saveOpt) {
    display.setCursor(56, 24);
    display.print(F("File:"));
    display.print(F(filename));
  }
  else {
    // cross out the camera
    display.fillCircle(123, 3, 2, SSD1306_WHITE); // fix right reel
    display.drawLine(115, 10, 125, 0, SSD1306_INVERSE); // x out the camera
    display.drawLine(116, 10, 126, 0, SSD1306_INVERSE);
    // date, not file
    display.setCursor(48, 24);
    display.print("Date:");
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
}



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

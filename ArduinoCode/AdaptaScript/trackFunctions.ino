////////////////////////////////////////////////
//                                            //
//            LINEAR TRACK                    //
//                                            //
////////////////////////////////////////////////


void runLinTrack() {
  while (!(upvalL == 0 && upvalR == 0)) {
    upvalL = digitalRead(leftBeam);
    upvalR = digitalRead(rightBeam);
    elapsedTime(); // update thisTime

    // if both are broken, lets break tot he next iteration, because this is basically a pause
    if (upvalL == 0 && upvalR == 0) {
      // this might be a good place to close the file and kill the loop
      continue;
    }
    //
    //
    // left side
    //
    //
    // if from unbroken to broken
    if (upvalL == 0 && wasupL == 1) {
      breakTime = thisTime;
      writeData("poke left");
      display.fillCircle(32, 12, 2, SSD1306_WHITE);
    }
    // if from broken to unbroken
    if (upvalL == 1 && wasupL == 0) {
      long breakTime = 0;
      writeData("un-poke left");
      display.fillCircle(32, 12, 2, SSD1306_BLACK);
    }
    // if is broken and is first sample
    if (upvalL == 0 && breakTime > 0 && (thisTime - breakTime) > holdTime) {
      // check left beam, if its unbroken, turn off pin and open circle
      writeData("Full Sample Left");
      if (lastWell != 1) {
        //FeedRat();
        writeData("Fed Left");
        ++Lrew;
        // update reward counter
        display.fillRect(35, 16, 18, 8, SSD1306_BLACK);
        display.setCursor(36, 16);
        String Lstr = String(Lrew);
        display.println(Lstr);
        //
      }
      lastWell = 1;
      breakTime = 0;
    }
    //
    //
    // Right Side
    //
    //
    if (upvalR == 0 && wasupR == 1) {
      breakTime = thisTime;
      writeData("poke Right");
      display.fillCircle(94, 12, 2, SSD1306_WHITE);
    }

    // if from broken to unbroken
    if (upvalR == 1 && wasupR == 0) {
      long breakTime = 0;
      writeData("un-poke Right");
      display.fillCircle(94, 12, 2, SSD1306_BLACK);
    }
    // if is broken and has been broken...
    if (upvalR == 0 && breakTime > 0 && (thisTime - breakTime) > holdTime) {
      // check left beam, if its unbroken, turn off pin and open circle
      writeData("Full Sample Right");
      if (lastWell != 2) {
        //FeedRat();
        writeData("Fed Right");
        ++Rrew;
        display.fillRect(94, 16, 18, 8, SSD1306_BLACK);
        display.setCursor(94, 16);
        String Rstr = String(Rrew);
        display.println(Rstr);
        //
      }
      lastWell = 2;
      breakTime = 0;
    }
    // update recent values
    wasupL = upvalL;
    wasupR = upvalR;
    display.drawCircle(94, 12, 2, SSD1306_WHITE);
    display.drawCircle(32, 12, 2, SSD1306_WHITE);
    display.display();
  }
  finishScreen();
}

////////////////////////////////////////////////
//                                            //
//            W MAZE CENTER                   //
//                                            //
////////////////////////////////////////////////


void runWMaze() {
  // basically, while there is only one down continue
  while (upvalL + upvalR + upvalC > 1) {
    upvalL = digitalRead(leftBeam);
    upvalR = digitalRead(rightBeam);
    upvalC = digitalRead(centerBeam);
    elapsedTime(); // update thisTime

    if (upvalL + upvalC + upvalR < 2) {
      continue;
    }
    //
    //
    // center well
    //
    //
    if (upvalC == 0 && wasupC == 1) {
      breakTime = thisTime;
      writeData("poke Center");
      display.fillCircle(64, 12, 2, SSD1306_WHITE);
    }

    // if from broken to unbroken
    if (upvalC == 1 && wasupC == 0) {
      long breakTime = 0;
      writeData("un-poke Center");
      display.fillCircle(64, 12, 2, SSD1306_BLACK);

    }
    // if is broken and has been broken...
    if (upvalC == 0 && breakTime > 0 && (thisTime - breakTime) > holdTime) {
      // check left beam, if its unbroken, turn off pin and open circle
      writeData("Full Sample Center");
      if (lastWell != 2) {
        //FeedRat();
        ++Crew;
        writeData("Fed Center");
      }
      // every center visit will be rewarded anyways...
      ++Chit;
      display.fillRect(56, 16, 18, 8, SSD1306_BLACK);
      display.setCursor(56, 16);
      String CrewStr = String(Crew);
      display.print(CrewStr);
      display.print(F("/"));
      String ChitStr = String(Chit);
      display.print(ChitStr);
      lastWell = 2;
      breakTime = 0;

    }
    //
    //
    // Left well
    //
    //
    if (upvalL == 0 && wasupL == 1) {
      breakTime = thisTime;
      writeData("poke Left");
      display.fillCircle(32, 12, 2, SSD1306_WHITE);
    }

    // if from broken to unbroken
    if (upvalL == 1 && wasupL == 0) {
      long breakTime = 0;
      writeData("un-poke Left");
      display.fillCircle(32, 12, 2, SSD1306_BLACK);
    }
    // if is broken and has been broken...
    if (upvalL == 0 && breakTime > 0 && (thisTime - breakTime) > holdTime) {
      // check left beam, if its unbroken, turn off pin and open circle
      writeData("Full Sample Right");
      if (lastWell != 1) {
        if (lastSideWell != 1  && lastWell != 3) {
          //FeedRat();
          writeData("Fed Left");
          ++Lrew;
        }
        if (lastWell == 3) {
          ++Chit;
        }
        Lhit++;
        display.fillRect(24, 16, 18, 8, SSD1306_BLACK);
        display.setCursor(24, 16);
        String LrewStr = String(Lrew);
        display.print(LrewStr);
        display.print(F("/"));
        String LhitStr = String(Lhit);
        display.print(LhitStr);
      }
      lastWell = 1;
      lastSideWell = 1;
      breakTime = 0;

    }
    //
    //
    // Right well
    //
    //
    if (upvalR == 0 && wasupR == 1) {
      breakTime = thisTime;
      writeData("poke Right");
      display.fillCircle(96, 12, 2, SSD1306_WHITE);
    }

    // if from broken to unbroken
    if (upvalR == 1 && wasupR == 0) {
      long breakTime = 0;
      writeData("un-poke Right");
      display.fillCircle(96, 12, 2, SSD1306_BLACK);
    }
    // if is broken and has been broken...
    if (upvalR == 0 && breakTime > 0 && (thisTime - breakTime) > holdTime) {
      // check left beam, if its unbroken, turn off pin and open circle
      writeData("Full Sample Right");
      if (lastWell != 3) {
        if (lastSideWell != 3  && lastWell != 1) {
          //FeedRat();
          writeData("Fed Right");
          ++Rrew;
        }
        if (lastWell == 1) {
          ++Chit;
        }
        Rhit++;
        display.fillRect(88, 16, 18, 8, SSD1306_BLACK);
        display.setCursor(88, 16);
        String RrewStr = String(Rrew);
        display.print(RrewStr);
        display.print(F("/"));
        String RhitStr = String(Rhit);
        display.print(RhitStr);
      }
      lastWell = 3;
      lastSideWell = 3;
      breakTime = 0;

    }


    wasupL = upvalL;
    wasupR = upvalR;
    wasupC = upvalC;
    display.drawCircle(32, 12, 2, SSD1306_WHITE);
    display.drawCircle(64, 12, 2, SSD1306_WHITE);
    display.drawCircle(96, 12, 2, SSD1306_WHITE);
    display.display();
  }
  finishScreen();
}
////////////////////////////////////////////////
//                                            //
//            OLD LINEAR                      //
//                                            //
////////////////////////////////////////////////


void RunLinTrackOld() {
  // if right beam broken
  if (upvalR == 1) {
    digitalWrite(ledPin2, LOW);
    display.fillCircle(94, 12, 2, SSD1306_BLACK); // centerx centery rad, color
    if (wasupR == 0) {
      char thisevent[] = "Unpoke Right";
      writeData();
    }
  }
  else {
    if (wasupR == 1) {
      char thisevent[] = "Poke Right";
      writeData();
    }
    if (lastWell != 2) {
      ++Rrew;
      display.fillRect(93, 16, 18, 8, SSD1306_BLACK);
      display.setCursor(94, 16);
      String Rstr = String(Rrew);
      display.println(Rstr);
      digitalWrite(ledPin2, HIGH);
      char thisevent[] = "Fed Right";
      writeData();
    }
    lastWell = 2;
    display.fillCircle(94, 12, 2, SSD1306_WHITE);
  }
  // update our last values
  wasupL = upvalL;
  wasupR = upvalR;
  // draw outlines again
  display.drawCircle(94, 12, 2, SSD1306_WHITE);
  display.drawCircle(32, 12, 2, SSD1306_WHITE);
  display.display();


  if (upvalL == 1) {
    digitalWrite(ledPin1, LOW);
    display.fillCircle(32, 12, 2, SSD1306_BLACK); // centerx centery rad, color
    if (wasupL == 0) {
      char thisevent[] = "Unpoke Left";
      writeData();
    }
  }
  else {
    // if left beam broken, and last well wasnt this one, feed, reset
    if (wasupL == 1) {
      char thisevent[] = "Poke Left";
      writeData();
    }
    // if down its broken
    if (lastWell != 1) {
      ++Lrew;
      // update display settings
      display.fillRect(34, 16, 18, 8, SSD1306_BLACK);
      display.setCursor(36, 16);
      String Lstr = String(Lrew);
      display.println(Lstr);
      digitalWrite(ledPin1, HIGH);
      char thisevent[] = "Fed Left";
      writeData();
    }
    lastWell = 1;

  }
}

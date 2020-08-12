
void RunLinTrack() {
  upvalL = digitalRead(leftBeam);
  upvalR = digitalRead(rightBeam);
  // if both are broken, lets break tot he next iteration, because this is basically a pause
  if (upvalL == 0 && upvalR == 0) {
    // this might be a good place to close the file and kill the loop
    //display.setCursor(64,24);
    //display.println(F("Stop Rec"));
    // if both values are down, dont do anything, e.g. pause
    return;
  }


  // if left well is broken
  if (upvalL == 0) {
    // if this is an initiation
    if (wasupL == 1) {
      writeData("Poke Left");
      // grab the initiation time
      iterator = numCountdownInterrupts;
    }
    float hasheld = (numCountdownInterrupts - iterator) / 20;
    if ( hasheld > holdTime) {
      // if full poke and first poke here
      if (lastWell != 1) {
        ++Lrew;
        // update display settings
        display.fillRect(34, 16, 18, 8, SSD1306_BLACK); // write over the counter
        display.setCursor(36, 16);
        display.println(Lrew);
        digitalWrite(ledPin1, HIGH);
        writeData("Fed Left");
      }
      lastWell = 1; // sampled for real
    }
    wasupL = 0;
    display.fillCircle(32, 12, 2, SSD1306_WHITE);
  }
  // if left unbroken
  else {
    digitalWrite(ledPin1, LOW);
    display.fillCircle(32, 12, 2, SSD1306_BLACK); // centerx centery rad, color
    if (wasupL == 0) {
      writeData("Unpoke Left");
    }
    wasupL = 1;
  }
  ///////////////
  //////////////
  /////////////

  if (upvalR == 0) {
    // if left beam broken, and last well wasnt this one, feed, reset
    if (wasupR == 1) {
      writeData("Poke Right");
      iterator = numCountdownInterrupts;
    }
    float hasheld = (numCountdownInterrupts - iterator) / 20;
    if ( hasheld > holdTime) {
      // if down its broken
      if (lastWell != 2) {
        ++Rrew;
        // update display settings
        display.fillRect(90, 16, 18, 8, SSD1306_BLACK); // write over the counter
        display.setCursor(36, 16);
        display.println(Rrew);
        digitalWrite(ledPin2, HIGH);
        writeData("Fed Right");
      }
      lastWell = 2; // sampled for real
    }
    wasupR = 0;
    display.fillCircle(94, 12, 2, SSD1306_WHITE);
  }
  // if left unbroken
  else {
    digitalWrite(ledPin2, LOW);
    display.fillCircle(94, 12, 2, SSD1306_BLACK); // centerx centery rad, color
    if (wasupR == 0) {
      writeData("Unpoke Right");
    }
    wasupR = 1;
  }
  // draw outlines
  display.drawCircle(94, 12, 2, SSD1306_WHITE);
  display.drawCircle(32, 12, 2, SSD1306_WHITE);
  display.display();
}




/*
void RunWmaze() {
  upvalL = digitalRead(leftBeam);
  upvalR = digitalRead(rightBeam);
  upvalC = digitalRead(centerBeam);

  // if one is broken...
  if ((upvalL + upvalR + upvalC) == 2) {

    // left port broken...
    if (upvalL == 0) {
      // if it was unbroken, report its broken
      if (wasupL == 1) {
        thisevent = "Left Beam Broken";
        writeData();
        iterator = numCountdownInterrupts; // pull the press time

        // if this wasnt the last well
        if (lastwell != 1) {
          // if we need to give reward
          if (lastWell == 2 && twoBack == 3) {
            thisevent = "Left Well Rewarded";
            writeData();
          } // end reward
        twoBack = lastwell;
        lastwell = 2;
      } // end this wasnt last well
      wasupL = 0;
    } // end this wasnt a 'poke'
    else {
      wasupL = 1);
    }
  }
}
*/

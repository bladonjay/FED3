
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
    digitalWrite(ledPin1, LOW);
    display.fillCircle(32, 12, 2, SSD1306_BLACK); // centerx centery rad, color
    if (wasupL == 0) {
      char thisevent[] = "Unpoke Left";
      writeData();
    }
    wasupL = 1;
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
    lastWell = 1; wasupL = 0;

    display.fillCircle(32, 12, 2, SSD1306_WHITE);
  }

  // if right beam broken
  if (upvalR == 1) {
    digitalWrite(ledPin2, LOW);
    display.fillCircle(94, 12, 2, SSD1306_BLACK); // centerx centery rad, color
    if (wasupR == 0) {
      char thisevent[] = "Unpoke Right";
      writeData();
    }
    wasupL = 1;
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
    lastWell = 2; wasupR = 0;

    display.fillCircle(94, 12, 2, SSD1306_WHITE);
  }
  // draw outlines
  display.drawCircle(94, 12, 2, SSD1306_WHITE);
  display.drawCircle(32, 12, 2, SSD1306_WHITE);
  display.display();
}

void RunWmaze() {




}
}

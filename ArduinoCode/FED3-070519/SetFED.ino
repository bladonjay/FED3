/********************************************************
  Mode select on startup screen

  FEDmodes:
  0 Free feeding
  1 FR1
  2 FR3
  3 FR5
  4 Progressive Ratio
  5 Extinction
  6 Light tracking FR1 task
  7 FR1 (reversed)
  8 PR (reversed)
  9 Optogenetic stimulation
  10 Optogenetic stimulation (reversed)
********************************************************/
void SelectMode() {
  // Set FR based on FEDmode
  if (FEDmode == 0) FR = 0;  // free feeding
  if (FEDmode == 1 || FEDmode == 7) FR = 1; // FR1 spatial task
  if (FEDmode == 2) FR = 3;  // FR3
  if (FEDmode == 3) FR = 5; // FR5
  if (FEDmode == 4 || FEDmode == 8) FR = 99; // Progressive Ratio
  if (FEDmode == 5 || FEDmode == 9 || FEDmode == 10) { // Extinction or optogenetic
    FR = 1;
    ReleaseMotor ();
    digitalWrite (MOTOR_ENABLE, LOW);  //Disable motor driver
  }
  if (FEDmode == 6) FR = 1; // FR1 light tracking task

  previousFEDmode = FEDmode;
  // beep and wipe the colors if you break both beams
  if ((digitalRead(LEFT_POKE) == LOW) && (digitalRead(RIGHT_POKE) == LOW)) {
    tone (BUZZER, 3000, 500);
    colorWipe(strip.Color(2, 2, 2), 40); // Color wipe
    colorWipe(strip.Color(0, 0, 0), 20); // OFF
    EndTime = millis();
    SetFED = true;
    SetDeviceNumber();
  }

  //Set FEDMode go up
  else if (digitalRead(LEFT_POKE) == LOW) {
    EndTime = millis();
    FEDmode -= 1;
    tone (BUZZER, 2500, 200);
    colorWipe(strip.Color(2, 0, 2), 40); // Color wipe
    colorWipe(strip.Color(0, 0, 0), 20); // OFF
    if (FEDmode == -1) FEDmode = 10;
  }
  //Set FEDMode go down
  else if (digitalRead(RIGHT_POKE) == LOW) {
    EndTime = millis();
    FEDmode += 1;
    tone (BUZZER, 2500, 200);
    colorWipe(strip.Color(2, 2, 0), 40); // Color wipe
    colorWipe(strip.Color(0, 0, 0), 20); // OFF
    if (FEDmode == 11) FEDmode = 0;
  }
  // Go around the bend of you try
  if (FEDmode < 0) FEDmode = 10;
  if (FEDmode > 10) FEDmode = 0;

  display.setTextSize(1);
  display.setCursor(5, 20);
  display.println ("Select Program");
  display.fillRoundRect (0, 30, 160, 80, 1, WHITE);
  display.setCursor(10, 45);
  //Text to display selected FR ratio
  if (FEDmode == 0) display.print("Free feeding");
  if (FEDmode == 1 ||  FEDmode == 2 || FEDmode == 3) {
    display.print("Fixed Ratio:"); display.print(FR);
  }
  if (FEDmode == 4) display.print("Progressive Ratio");
  if (FEDmode == 5) display.print("Extinction");
  if (FEDmode == 6) display.print("Light tracking");
  if (FEDmode == 7) display.print("FR1");
  if (FEDmode == 8) display.print("Progressive Ratio");
  if (FEDmode == 9 || FEDmode == 10) display.print("Self-Stimulation");
  if (FEDmode == 8 || FEDmode == 7 || FEDmode ==10) display.setCursor(10, 65);
  if (FEDmode == 8 || FEDmode == 7 || FEDmode ==10) display.print("(reversed)");
  display.refresh();
  // while its been less than 2 seconds since last response, keep asking
  // if two seconds have passed of no responses, set the program
  while (millis() - EndTime < 2000) {
    SelectMode();
  }
  // will need to check this, but this is where it sets the cursor position
  // and then writes selected.  I wonder if this moves the cursor forward
  display.setCursor(5, 90);
  display.println("...Selected!");
  delay (500);
  display.refresh();

  writeFEDmode();
  delay (200);
  NVIC_SystemReset();      // processor software reset
}


/********************************************************
  Change device number
********************************************************/
void SetDeviceNumber() {
  while (SetFED == true) {
    //adjust FED device number
    display.fillRoundRect (0, 0, 200, 50, 0, WHITE);
    display.setCursor(5, 46);
    display.println("Set Device Number");

    display.fillRoundRect (36, 122, 30, 18, 0, WHITE);
    display.fillRoundRect (65, 122, 140, 18, 0, WHITE);

    delay (100);
    display.refresh();

    display.setCursor(35, 135);
    if (FED < 100 & FED >= 10) {
      display.print ("0");
    }
    if (FED < 10) {
      display.print ("00");
    }
    display.print (FED);

    delay (100);
    display.refresh();

    if (digitalRead(RIGHT_POKE) == LOW) {
      FED += 1;
      EndTime = millis();
      if (FED > 700) {
        FED = 700;
      }
    }

    if (digitalRead(LEFT_POKE) == LOW) {
      FED -= 1;
      EndTime = millis();
      if (FED < 1) {
        FED = 0;
      }
    }
    if (millis() - EndTime > 3000) {  // if 3 seconds passes confirm device #
      SetFED = false;
      display.setCursor(5, 70);
      display.println("...Set!");
      delay (500);
      display.refresh();
      writeConfigFile();
      NVIC_SystemReset();      // processor software reset
    }
  }
}

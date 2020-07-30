void startScreen() {

 display.clearDisplay();
 
  // this is the recording camera
  display.fillRect(116, 4, 8, 6, SSD1306_WHITE);
  display.fillRect(124, 6, 4, 2, SSD1306_WHITE);

  display.fillCircle(123, 3, 2, SSD1306_BLACK); // centerx centery rad, color
  display.drawCircle(123, 3, 2, SSD1306_WHITE);

  display.fillCircle(116, 3, 2, SSD1306_BLACK); // centerx centery rad, color
  display.drawCircle(116, 3, 2, SSD1306_WHITE);
  

 
  display.setCursor(24, 0);     // Start at top-left corner
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
    display.setCursor(24,16);
    // for three, we dont have room to label all of them...
    display.println(F("0/0"));
    display.setCursor(56,16);
    display.println(F("0/0"));
    display.setCursor(88,16);
    display.println(F("0/0")); 
  }

  if (saveOpt) {
    display.setCursor(80, 24);
    display.print(F("File:"));
    display.print(now.year(), DEC);
    display.print(' / ');
    display.print(now.month(), DEC);
    display.print(' / ');
    display.print(now.day(), DEC);
  }
  else {
    // cross out the camera
    display.fillCircle(123, 3, 2, SSD1306_WHITE); // fix right reel
    display.drawLine(115, 10, 125, 0, SSD1306_INVERSE); // x out the camera
    display.drawLine(116, 10, 126, 0, SSD1306_INVERSE);
    // date, not file
    display.setCursor(80, 24);
    display.print("Date:");
    display.setCursor(96, 24);
    display.print(now.year(), DEC);
    display.print(' / ');
    display.print(now.month(), DEC);
    display.print(' / ');
    display.print(now.day(), DEC);
  }

  display.display();
}

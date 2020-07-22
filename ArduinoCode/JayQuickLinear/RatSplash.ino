void RatSplashScreen() {
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

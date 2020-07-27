void makeFile() {
  Serial.print("Testfile will be named: ");
  // 6 is an underscore
  filename[0] = now.month() / 10 + '0';
  filename[1] = now.month() % 10 + '0';
  filename[2] = now.day() / 10 + '0';
  filename[3] = now.day() % 10 + '0';
  filename[4] = (now.year() - 2000) / 10 + '0';
  filename[5] = (now.year() - 2000) % 10 + '0';

  // check if htis filename exists, and if so increment last letters
  for (uint8_t i = 0; i < 100; i++) {
    filename[6] = '0' + i / 10; // this is clever, increment the ascii char
    filename[7] = '0' + i % 10;
    if (! SD.exists(filename)) {
      break; // e.g. break the for loop
    }
  }
  display.setCursor(16, 16);
  display.println(filename);
  Serial.println(filename);
  Serial.println("now trying to create the file");
  
  logfile = SD.open(filename, FILE_WRITE);
  if ( ! logfile ) {
    Serial.println("SDfile creation failed");
    saveOpt = 2;
    display.setCursor(0, 24);
    display.println("SD card Fail, Wont Save")
    display.display();
  }
else {
  display.setCursor(16,24);
  display.println("File Created");
  display.display();
  Serial.println("Success, building header");
  logfile.println("AdaptaMaze File created at, MM:DD:YYYY hh:mm:ss, Task Paradigm");
  logfile.print(" ,");
  logfile.print(filename[0 1]);
  logfile.print("/");
  logfile.print(filename[2 3]);
  logfile.print("/20");
  logfile.print(filename[4 5]);
  logfile.print(" ");
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
  logfile.print(mydateHMS);
  logfile.print(",");
  if (taskMode == 1) {
    logfile.println("Linear Track");
  }
  if (taskMode == 2) {
    logfile.println("W-Maze Center");
  }
  if (taskMode == 3) {
    logfile.println("W-Maze Left");
  }
  if (taskMode == 4) {
    logfile.println("W-Maze Right");
  }
  if (taskMode == 5) {
    logfile.println("Social Task");
  }
  display.fillRect(0,24,128,8,SSD1306_BLACK);
  display.setCursor(16,24);
  display.println("File Created With Header");
  display.display();
  logfile.close();
}
}

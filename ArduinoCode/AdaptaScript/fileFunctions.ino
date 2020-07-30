void makeFile() {
  if (saveOpt == true) {
    // check if htis filename exists, and if so increment last letters
    for (uint8_t i = 0; i < 100; i++) {
      filename[6] = '0' + i / 10; // this is clever, increment the ascii char
      filename[7] = '0' + i % 10;
      if (! SD.exists(filename)) {
        break; // e.g. break the for loop
      }
    }
    display.setCursor(16, 24);
    display.println(filename);
  

    logfile = SD.open(filename, FILE_WRITE);
    if ( ! logfile ) {
      saveOpt = 0;
      display.setCursor(0, 36);
      display.println("SD card Fail, Wont Save");
      display.display();
    }
    else {
      display.setCursor(0, 36);
      display.display();
      logfile.println("AdaptaMaze File ");
      logfile.println("date in MM:DD:YYYY hh:mm:ss, Task Paradigm");
      
      logfile.print(mydate); // from gatherdate
      logfile.print(", ");
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
      display.setCursor(0, 48);
      logfile.println("\n");
      logfile.println("Time, Event");
      display.println("File Created With Headers!");
      display.display();
      logfile.close();
    }
  }
}
// write the timestamp, then the event
void writeData() {
  logfile = SD.open(filename, FILE_WRITE);
  long thistime = numCountdownInterrupts; // 20 per second
  strcpy(mydateHMS, "__:__:__.__");  // placeholder filename
  int thishour = thistime / 60 / 60 / 20;
  int thisminute = (thistime - (thishour * 60 * 60 * 20)) / 60 / 20;
  int thissecond = (thistime - (thishour * 60 * 60 * 20) - (thisminute * 60 * 20));
  mydateHMS[0] = thishour / 10 + '0';
  mydateHMS[1] = thishour % 10 + '0';
  mydateHMS[3] = thisminute / 10 + '0';
  mydateHMS[4] = thisminute % 10 + '0';
  mydateHMS[6] = thissecond / 20 + '0';
  mydateHMS[7] = thissecond % 20 + '0';
  mydateHMS[8] = thissecond / 2 + '0';
  mydateHMS[9] = thissecond % 2 + '0';
  logfile.print(mydateHMS);
  logfile.print(",");
  logfile.println(thisevent);
}

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
      delay(1000);
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
      logfile.println("Time (mSec), Event");
      display.println("File Created With Headers!");
      display.display();
      logfile.close();
      delay(1000);
    }
  }
}
// write the timestamp, then the event
void writeData(char *thisevent) {
  // gather the elapsed time
  elapsedTime();
  if (saveOpt == true) {
    logfile = SD.open(filename, FILE_WRITE);
    logfile.print(thisTime);
    logfile.print(",");
    logfile.println(thisevent);
    logfile.close();
  }
}

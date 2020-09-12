// This script tests out generating a datafile using the date
// as the filename followed by 00-99 for 99 files per day
// need to use this to start generating files with headers


#include "RTClib.h"
#include <RTCZero.h>
#include <SPI.h>
#include <SD.h>
//#include <SdFat.h>
//SdFat SD;             //Quick way to make SdFat work with standard SD.h sketches

// SD chip select pin.  Be sure to disable any other SPI devices such as Enet.
const uint8_t chipSelect = 4;

RTCZero rtc2;
RTC_PCF8523 rtc;
File logfile;

void dateTime(uint16_t* date, uint16_t* time) {
  DateTime now = rtc.now();
  // return date using FAT_DATE macro to format fields
  *date = FAT_DATE(now.year(), now.month(), now.day());

  // return time using FAT_TIME macro to format fields
  *time = FAT_TIME(now.hour(), now.minute(), now.second());
}

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {
    delay(10); // wait for serial port to connect. Needed for native USB port only
  }

  rtc.begin();

  Serial.print("Initializing SD card...");
  // see if the card is present and can be initialized:
  //SdFile::dateTimeCallback(dateTime);
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");



  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
  }

  File logfile;         // Create file object
  char filename[13];    // Array for file name data logged to named in setup
  strcpy(filename, "________.CSV");  // placeholder filename (8 char and postfix)


  getFilename(filename);
  Serial.print("Testfile will be named: ");
  Serial.println(filename);

  Serial.println("now trying to create the file");
  SdFile::dateTimeCallback(dateTime);

  logfile = SD.open(filename, FILE_WRITE);
  if ( ! logfile ) {
    Serial.println("SDfile creation failed");
  } 
  else {
    Serial.println("SD File Success");
    Serial.print("File Named :");
    Serial.println(filename);
  }
}
void loop() {
  // put your main code here, to run repeatedly:


}



void getFilename(char *filename) {
  // get the file name: FED (device num) _ mmddyyNN (nn if the file exists, add another)
  DateTime now = rtc.now();
  //filename[3] = FED / 100 + '0';
  //filename[4] = FED / 10 + '0';
  //filename[5] = FED % 10 + '0';
  // 6 is an underscore
  filename[0] = now.month() / 10 + '0';
  filename[1] = now.month() % 10 + '0';
  filename[2] = now.day() / 10 + '0';
  filename[3] = now.day() % 10 + '0';
  filename[4] = (now.year() - 2000) / 10 + '0';
  filename[5] = (now.year() - 2000) % 10 + '0';
  // apparently 13 is an underscore too
  filename[8] = '.';
  filename[9] = 'C';
  filename[10] = 'S';
  filename[11] = 'V';
  // check if htis filename exists, and if so increment last letters
  for (uint8_t i = 0; i < 100; i++) {
    filename[6] = '0' + i / 10; // this is clever, increment the ascii char
    filename[7] = '0' + i % 10;
    if (! SD.exists(filename)) {
      break;
    }
  }
  return;
}

/*
  void WriteToSD() {
  DateTime now = rtc.now();

  logfile.print(now.month());
  logfile.print("/");
  logfile.print(now.day());
  logfile.print("/");
  logfile.print(now.year());
  logfile.print(" ");
  logfile.print(now.hour());
  logfile.print(":");
  if (now.minute() < 10)
    logfile.print('0');      // Trick to add leading zero for formatting
  logfile.print(now.minute());
  logfile.print(":");
  if (now.second() < 10)
    logfile.print('0');      // Trick to add leading zero for formatting
  logfile.print(now.second());
  logfile.print(",");

  logfile.print(FED); // Print device name
  logfile.print(",");

  logfile.print(measuredvbat); // Print battery voltage
  logfile.print(",");

  logfile.print((numJamClears * 10) + numMotorTurns); // Print the number of attempts to dispense a pellet, including through jam clears
  numMotorTurns = 0; //reset numMotorTurns
  numJamClears = 0; // reset numJamClears
  logfile.print(",");

  // this is the text for the task type
  if (FEDmode == 4) {
    logfile.print(round ((5 * exp (0.2 * PelletCount)) - 5)); // Print current PR ratio
    logfile.print(",");
  }

  else if (FEDmode == 0) {
    logfile.print("FED"); // Print trial type
    logfile.print(",");
  }

  else if (FEDmode == 5) {
    logfile.print("Extinction"); // Print trial type
    logfile.print(",");
  }

  else if (FEDmode == 6) {
    logfile.print("FR1_Light_tracking"); // Print trial type
    logfile.print(",");
  }

  else if (FEDmode == 7) {
    logfile.print("FR1_reversed"); // Print trial type
    logfile.print(",");
  }

  else if (FEDmode == 8) {
    logfile.print("PR_reversed"); // Print trial type
    logfile.print(",");
  }

  else if (FEDmode == 9) {
    logfile.print("Self_stim"); // Print trial type
    logfile.print(",");
  }

  else if (FEDmode == 10) {
    logfile.print("Self_stim_reversed"); // Print trial type
    logfile.print(",");
  }

  else {
    logfile.print(FR); // Print ratio
    logfile.print(",");
  }

  if (FEDmode == 6 || FEDmode == 7 || FEDmode == 8 || FEDmode == 10) {
    if (activePoke == 0)  logfile.print("Right"); //
    if (activePoke == 1)  logfile.print("Left"); //
  }
  else {
    logfile.print("Left"); // Print whether trial had aversive stimulus
  }
  logfile.print(",");

  logfile.print(LeftCount); // Print Left poke count
  logfile.print(",");

  logfile.print(RightCount); // Print Right poke count
  logfile.print(",");

  logfile.print(PelletCount); // print Pellet counts
  logfile.print(",");

  logfile.println(retInterval); // print interval between pellet dispensing and being taken

  Blink(GREEN_LED, 100, 2);
  logfile.flush();
  // logfile.close();
  }
*/

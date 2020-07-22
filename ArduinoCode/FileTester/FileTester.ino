// This script tests out generating a datafile using the date
// as the filename followed by 00-99 for 99 files per day
// need to use this to start generating files with headers


#include "RTClib.h"
#include <SPI.h>
#include <SD.h>
//#include "SdFat.h"
//SdFat SD;             //Quick way to make SdFat work with standard SD.h sketches

// SD chip select pin.  Be sure to disable any other SPI devices such as Enet.
const uint8_t chipSelect = 4;

RTC_PCF8523 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:

  SdFile::dateTimeCallback(dateTime);
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");

  #ifndef ESP8266
  while (!Serial); // wait for serial port to connect. Needed for native USB
  #endif

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
  }
  
  File logfile;         // Create file object
  char filename[15];    // Array for file name data logged to named in setup
  strcpy(filename, "________.CSV");  // placeholder filename
  getFilename(filename);
  Serial.print("Testfile will be named: ");
  Serial.println(filename);

  Serial.println("now trying to create the file");
  logfile = SD.open(filename, FILE_WRITE);
  if ( ! logfile ) {
    Serial.println("SDfile creation failed");
  }
  else {
    Serial.println("Success!?");
    logfile.close();
  }
}

void loop() {
  // put your main code here, to run repeatedly:


}



void getFilename(char *filename) {
  // get the file name: Data_ mmddyyNN (nn if the file exists, add another)
  DateTime now = rtc.now();
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
      break;
    }
  }
  return;
}

void writeHeader() {
  // print first file header, this will have a ton of information
  logfile.println("MM:DD:YYYY hh:mm:ss, Device_Number, Battery_Voltage, Motor_Turns, FR_Ratio, Active_Poke, Left_Poke_Count, Right_Poke_Count, Pellet_Count, Retrieval_Time");
  // im thinking of something like in words date and time
  // newline task definition
  // newline task duration, total visits to each,
  // newline, simple performance metrics (rewards gained at each)
  
  //
  logfile.println("MM:DD:YYYY hh:mm:ss, Device_Number, Battery_Voltage, Motor_Turns, FR_Ratio, Active_Poke, Left_Poke_Count, Right_Poke_Count, Pellet_Count, Retrieval_Time");

}

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

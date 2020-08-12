///////////////////////////////////////
//
// Declare constants and variables
//
//////////////////////////////////////

#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "RTClib.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET    4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
RTC_PCF8523 rtc;

//DateTime mytime = rtc.now();

void ratSplashScreen();
void optScreen();
void saveScreen();
void startScreen();

void makeFile();
void writeData();

//
bool upvalL;
bool upvalR;
bool upvalC;

bool wasupL = false;
bool wasupC = false;
bool wasupR = false;
bool saveOpt = false;

const int rightBeam = 11;
const int leftBeam = 12;
const int centerBeam = 6;

const int rightFeed = 2;
const int leftFeed = 3;
const int centerFeed = 15;

const int ledPin1 = 13;
const int ledPin2 = 8;
const int BUZZER = 0; // this is pin a0 for the buzzer (unnecessary)


int lastWell = 0;
int twoBack = 0;
int Lrew = 0;
int Rrew = 0;
int Crew = 0;
int taskMode = 1;
unsigned int iterator = 0; // this is going to be our interval counter
float holdTime = 0.5;



// clock variables
// Variables modified during an interrupt must be declared volatile
volatile bool clockgoing = false;
volatile int numCountdownInterrupts = 0;
const int timerInterruptPin = 5;  // Adafruit Feather M0/M4/nRF52840
// you can also use millis, its just less precise
// long starttime = 0;
// long thistime = 0;

// file variables
const int chipSelect = 4; // on this board its 4, could be 10
File logfile;
char filename[14] = "________.csv";
char mydatetime[17];
char mydateHMS[8];
char thisevent[] = "Task Start";
//////////////////////////
//                      //
//                      //
//      SETUP PERIOD    //
//                      //
//                      //
/////////////////////////

void setup() {

  // put your setup code here, to run once:
  // set up our I/O pins
  pinMode(rightBeam, INPUT_PULLUP);
  pinMode(leftBeam, INPUT_PULLUP);
  pinMode(centerBeam, INPUT_PULLUP);

  pinMode(rightFeed, OUTPUT);
  pinMode(leftFeed, OUTPUT);
  pinMode(centerFeed, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);

  // open serial port, or
  Serial.begin(9600);
  delay(1000);
  while (!Serial && iterator < 100) {
    delay(10);
    ++iterator;
    // wait for serial port to connect. Needed for native USB port only
  }
  if (Serial) {
    Serial.println("\nSerial debug started");
  }

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3D)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed, trying again"));
    delay(1000);
    while (!display.begin(SSD1306_SWITCHCAPVCC, 0x3D)) {
    }
  }

  // Start the timer, redo all the small timers, get the time
  while (! rtc.begin()) {
  }
  rtc.deconfigureAllTimers();
 
  gatherDate(); // gather date now, when the rtc is set (filename set and date set)
  rtc.start();
  
  
  // initialize sd card
  Serial.println("SSD1306 initialized");
  if (!SD.begin(chipSelect)) {
    ;
  }
  Serial.println("card initialized.");
  iterator = 0;


  
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(1000); // Pause for 2 seconds

  // Clear the buffer, set text parameters
  display.clearDisplay();
  display.setRotation(2);
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  display.display();
  display.setRotation(2);
  display.clearDisplay();



 
  ///////////////////////////
  //
  // run startup sequence
  //
  ///////////////////////////

  //ratSplashScreen();
  //optScreen(); // default is taskphase is 1
  delay(1000);
  //saveScreen(); // default is not to save
  delay(1000);
  startScreen();
  // last thing to do before running task is to initialize timer
  rtc.enableCountdownTimer(PCF8523_Frequency4kHz, 205); // start high at 50 msec (or 20 hz)
  // basically whenever this pin changes itll keep track
  attachInterrupt(digitalPinToInterrupt(timerInterruptPin), countdownOver, FALLING);
}

  ///////////////////////////
  //
  // loop
  //
  ///////////////////////////

void loop() {
  // put your main code here, to run repeatedly:
  if (taskMode == 1){
    RunLinTrack();
  }
  showElapsedTime();
}

// keep this timer function in this sketch
void countdownOver () {
  // Set a flag to run code in the loop():
  if (clockgoing == true) {
    ++numCountdownInterrupts;
  }
  // first tick doesnt count
  clockgoing = true;
}

void gatherDate(){
 // gather the date and save it
  DateTime now = rtc.now();
  // fill the date and time
  mydatetime[0] = now.month() / 10 + '0';
  mydatetime[1] = now.month() % 10 + '0';
  mydatetime[2] = '/';
  mydatetime[3] = now.day() / 10 + '0';
  mydatetime[4] = now.day() % 10 + '0';
  mydatetime[5] = '/';
  mydatetime[6] = (now.year() - 2000) / 10 + '0';
  mydatetime[7] = (now.year() - 2000) % 10 + '0';
  mydatetime[8] =' ';
  mydatetime[9] = now.hour() / 10 + '0';
  mydatetime[10] = now.hour() % 10 + '0';
  mydatetime[11] =':';
  mydatetime[12] = now.minute() / 10 + '0';
  mydatetime[13] = now.minute() % 10 + '0';
  mydatetime[14] =':';
  mydatetime[15] = now.second() / 10 + '0';
  mydatetime[16] = now.second() % 10 + '0';

  filename[0] = now.month() / 10 + '0';
  filename[1] = now.month() % 10 + '0';
  filename[2] = now.day() / 10 + '0';
  filename[3] = now.day() % 10 + '0';
  filename[4] = (now.year() - 2000) / 10 + '0';
  filename[5] = (now.year() - 2000) % 10 + '0';
}

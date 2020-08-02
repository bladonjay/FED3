#include <SPI.h>
#include <SD.h>
//#include "SdFat.h"
#include <Wire.h>
//#include <RTCZero.h>
#include "RTClib.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET    4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
RTC_PCF8523 rtc;

DateTime now = rtc.now();
  
// Declare our functions
void RatSplashScreen();
void OptScreen();
void startScreen();
void saveScreen();
void displayElapsedTime();

void RunLinTrack();
void RunWmazeCenter();
void RunWmazeLeft();
void RunWmazeRight();
void RunSocial();

void makeFile();
void writeData();

File logfile;



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
const int centerFeed = 5;

const int ledPin1 = 13;
const int ledPin2 = 8;
const int BUZZER = 0; // this is pin a0 for the buzzer (unnecessary)

const int chipSelect = 4; // on this board its 4, could be 10

int lastWell = 0;
int Lrew = 0;
int Rrew = 0;
int taskMode = 1;
int iterator = 0;


char filename[8];
char mydateHMS[8];
char thisevent[] = "Task Start";
long starttime = 0;
long thistime = 0;

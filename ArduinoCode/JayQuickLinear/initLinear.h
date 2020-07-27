#include <SPI.h>
#include <SD.h>
//#include "SdFat.h"
#include <Wire.h>
//#include <RTCZero.h>
#include "RTClib.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
RTC_PCF8523 rtc;
// Declare the RTC here

// Declare our functions
void RatSplashScreen();
void OptScreen();
void StartScreen();

void RunLinTrack();
void RunWmazeCenter();
void RunWmazeLeft();
void RunWmazeRight();
void RunSocial();

file logfile;



//
bool upvalL;
bool upvalR;
bool upvalC;

const int rightBeam = 11;
const int leftBeam = 12;
const int centerBeam = 6;

const int rightFeed = 2;
const int leftFeed = 3;
const int centerFeed = 5;

const int ledPin = 13;
const int BUZZER = 0; // this is pin a0 for the buzzer (unnecessary)

const int chipSelect = 4; // on this board its 4, could be 10

int lastWell = 0;
int Lrew = 0;
int Rrew = 0;
int taskMode = 1;
int iterator = 0;
int saveOpt = 2;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
char fileName[8];
char mydateHMS[8];

long starttime = 0;
long thistime = 0;

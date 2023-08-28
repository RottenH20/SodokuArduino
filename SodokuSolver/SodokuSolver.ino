#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

#include <SPI.h>
#include <Wire.h>
#include <stdlib.h>
#include "TouchScreen.h"

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

#define MINPRESSURE 10
#define MAXPRESSURE 1000

// These are the four touchscreen analog pins
#define YP A2  // must be an analog pin, use "An" notation!
#define XM A3  // must be an analog pin, use "An" notation!
#define YM 9   // can be any digital pin
#define XP 8   // can be any digital pin

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10
#define TFT_RST 8

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

// Global Variables, uses dynamic memory, might need to reduce depending on size of photo
short int counter = 0;
short int counter1 = 0;
uint16_t arr[] = {ILI9341_BLUE, ILI9341_RED, ILI9341_GREEN};
const int CS = 5;

int grid[8][8];

int currentNum = 0;

#define BOXSIZE 40
#define PENRADIUS 1

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void setup() {
  Serial.begin(9600);

  pinMode(TFT_CS, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(TFT_CS, HIGH);
  digitalWrite(7, HIGH);
 
  tft.begin();

  //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

  Serial.println(setupGrid());
  Serial.println(buttonSetup());
}

// Runs after Main is complete, constantly loops
void loop(void) {
  TS_Point p = ts.getPoint();

  if (p.z < MINPRESSURE || p.z > MAXPRESSURE)
    return;

  p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
  p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

  // Edit box here
}


// Have Method SetupButtons
unsigned long buttonSetup() {
  //tft.fillScreen(ILI9341_BLACK);
  unsigned long start = micros();
  tft.setRotation(3);
  
  //tft.setCursor(52, (tft.height() / 2) - 107);
  int h = tft.height() / 2 - 107;
  int w = 52;
  
  tft.setTextColor(ILI9341_RED);
  tft.setTextSize(2);
  for (int i = 1; i <= 9; i++)
  {
    for (int j = 1; j <= 9; j++)
    {
      tft.setCursor(w, h);
      tft.println(String(NULL));
      w += 25;
    }
    w = 52;
    h += 25;
  }
  tft.setRotation(2);
  tft.setCursor(tft.width() / 2 - 90, (tft.height() / 2) + 130);
  tft.setTextColor(ILI9341_WHITE);
  tft.println("Aaron's Project");
  return micros() - start;
}

// Sets up all the grids, (TODO, make it also set up a 2D array)
unsigned long setupGrid() {
  unsigned long start;
  int cx = 7;
  int cy = (tft.height() / 2) + 115;

  tft.fillScreen(ILI9341_BLACK);
  
  start = micros();
  
  for(int i=25; i<=225; i+=25) {
    for (int j = 25; j <= 225; j+=25)
    {
        tft.drawRect(cx, cy-j, 25, 25, colorChoice());
    }
    counter1++;
    if (counter1 == 3)
    {
      counter1 = 0;
      rotate();
    }
    cx += 25;
  }

  return micros() - start;
}

// For setting up grid using colors (cycles colors for visual clarity)
uint16_t colorChoice() {
  if (counter == 3)
  {
    rotate();
  }
  if (counter == 6)
  {
    rotate();
  }
  if (counter == 9)
  {
    counter = 0;
    rotate();
  }
  counter++;
  return arr[0];
}

// Where we will set up the 2D array, (Will pass photo through)
void SetUp2DArray() {
  
}

// Where we will get the picture
void GetPicture() {

}

void rotate() {
  int n = sizeof(arr) / sizeof(arr[0]);
  uint16_t x = arr[n - 1];
  for (int i = n - 1; i > 0; i--) {
    arr[i] = arr[i - 1];
  }
  arr[0] = x;
}

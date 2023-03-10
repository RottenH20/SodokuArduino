#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

#include <ArduCAM.h>
#include <SPI.h>
#include <Wire.h>
#include <stdlib.h>

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10
#define TFT_RST 8

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
// If using the breakout, change pins as desired
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);
int counter = 0;
int counter1 = 0;
uint16_t arr[] = {ILI9341_BLUE, ILI9341_RED, ILI9341_GREEN};
const int CS = 5;

//string grid[9][9];

int currentNum = 0;

void rotate() {
  int n = sizeof(arr) / sizeof(arr[0]);
  uint16_t x = arr[n - 1];
  for (int i = n - 1; i > 0; i--) {
    arr[i] = arr[i - 1];
  }
  arr[0] = x;
}

void setup() {
  Serial.begin(9600);

  pinMode(TFT_CS, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(TFT_CS, HIGH);
  digitalWrite(7, HIGH);
 
  tft.begin();

  //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

  //Serial.println(testText());
  //delay(3000);

  Serial.println(testRects());
  Serial.println(testText());
  delay(10000);

  //Serial.println(testFilledRects(ILI9341_YELLOW, ILI9341_MAGENTA));
  //delay(500);

}


void loop(void) {

}

unsigned long testText() {
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
      tft.println(String(genRandNum()));
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

int genRandNum()
{
  return rand()%9 + 1;
}

unsigned long testRects() {
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

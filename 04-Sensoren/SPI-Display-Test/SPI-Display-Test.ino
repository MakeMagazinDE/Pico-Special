#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>

// SPI-Pins
const int8_t SCLK_PIN = 10;
const int8_t MOSI_PIN = 11;
const int8_t DC_PIN = 12;
const int8_t CS_PIN = 13;
const int8_t RST_PIN = 14;

// Bildschirm-Konstanten
const uint16_t SCREEN_WIDTH = 128;
const uint16_t SCREEN_HEIGHT = 128;
const uint16_t BLACK = 0x0000;
const uint16_t YELLOW = 0xFFE0;

Adafruit_SSD1351 display = Adafruit_SSD1351(
  SCREEN_WIDTH, SCREEN_HEIGHT,
  CS_PIN, DC_PIN, MOSI_PIN, SCLK_PIN, RST_PIN);  

void setup() {
    display.begin();
    display.fillScreen(BLACK);
    display.setCursor(25, 64);
    display.setTextColor(YELLOW);
    display.setTextSize(1);
    display.println("Hello, world!");
}

void loop() {}

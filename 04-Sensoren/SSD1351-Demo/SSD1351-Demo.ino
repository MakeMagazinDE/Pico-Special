#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>

// SPI pins
const int8_t SCLK_PIN = 10;
const int8_t MOSI_PIN = 11;
const int8_t DC_PIN = 12;
const int8_t CS_PIN = 13;
const int8_t RST_PIN = 14;

// Screen dimensions
const uint16_t SCREEN_WIDTH = 128;
const uint16_t SCREEN_HEIGHT = 128;

// Color definitions
const uint16_t BLACK = 0x0000;
const uint16_t BLUE = 0x001F;
const uint16_t RED = 0xF800;
const uint16_t GREEN = 0x07E0;
const uint16_t CYAN = 0x07FF;
const uint16_t MAGENTA = 0xF81F;
const uint16_t YELLOW = 0xFFE0;
const uint16_t WHITE = 0xFFFF;

Adafruit_SSD1351 tft = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, CS_PIN, DC_PIN, MOSI_PIN, SCLK_PIN, RST_PIN);  

void setup() {
    tft.begin();
    // tft.setRotation(1);

    tft.fillRect(0, 0, 128, 128, BLACK);
    
    lcdTestPattern();
    delay(500);
    
    tft.invert(true);
    delay(100);
    tft.invert(false);
    delay(100);

    tft.fillScreen(BLACK);
    testdrawtext("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa, fringilla sed malesuada et, malesuada sit amet turpis. Sed porttitor neque ut ante pretium vitae malesuada nunc bibendum. Nullam aliquet ultrices massa eu hendrerit. Ut sed nisi lorem. In vestibulum purus a tortor imperdiet posuere. ", WHITE);
    delay(500);

    tftPrintTest();
    delay(500);
    
    tft.drawPixel(tft.width() / 2, tft.height() / 2, GREEN);
    delay(500);

    testlines(YELLOW);
    delay(500);    
  
    testfastlines(RED, BLUE);
    delay(500);    

    testdrawrects(GREEN);
    delay(1000);

    testfillrects(YELLOW, MAGENTA);
    delay(1000);

    tft.fillScreen(BLACK);
    testfillcircles(10, BLUE);
    testdrawcircles(10, WHITE);
    delay(1000);
    
    testroundrects();
    delay(500);
    
    testtriangles();
    delay(500);
}

void loop() {
}

void testlines(uint16_t color) {
    tft.fillScreen(BLACK);
    for (uint16_t x = 0; x < tft.width() - 1; x += 6) {
        tft.drawLine(0, 0, x, tft.height() - 1, color);
    }
    for (uint16_t y = 0; y < tft.height() - 1; y += 6) {
        tft.drawLine(0, 0, tft.width() - 1, y, color);
    }
   
    tft.fillScreen(BLACK);
    for (uint16_t x = 0; x < tft.width() - 1; x += 6) {
        tft.drawLine(tft.width() - 1, 0, x, tft.height() - 1, color);
    }
    for (uint16_t y = 0; y < tft.height() - 1; y += 6) {
        tft.drawLine(tft.width() - 1, 0, 0, y, color);
    }
   
    tft.fillScreen(BLACK);
    for (uint16_t x = 0; x < tft.width() - 1; x += 6) {
        tft.drawLine(0, tft.height() - 1, x, 0, color);
    }
    for (uint16_t y = 0; y < tft.height() - 1; y += 6) {
        tft.drawLine(0, tft.height() - 1, tft.width() - 1, y, color);
    }

    tft.fillScreen(BLACK);
    for (uint16_t x = 0; x < tft.width() - 1; x += 6) {
        tft.drawLine(tft.width() - 1, tft.height() - 1, x, 0, color);
    }
    for (uint16_t y = 0; y < tft.height() - 1; y += 6) {
        tft.drawLine(tft.width() - 1, tft.height() - 1, 0, y, color);
    }
}

void testdrawtext(char *text, uint16_t color) {
    tft.setCursor(0, 0);
    tft.setTextColor(color);
    tft.print(text);
}

void testfastlines(uint16_t color1, uint16_t color2) {
    tft.fillScreen(BLACK);
    for (uint16_t y = 0; y < tft.height() - 1; y += 5) {
        tft.drawFastHLine(0, y, tft.width() - 1, color1);
    }
    for (uint16_t x = 0; x < tft.width() - 1; x += 5) {
        tft.drawFastVLine(x, 0, tft.height() - 1, color2);
    }
}

void testdrawrects(uint16_t color) {
    tft.fillScreen(BLACK);
    for (uint16_t x = 0; x < tft.height() - 1; x += 6) {
       tft.drawRect((tft.width() - 1) / 2 - x / 2, (tft.height() - 1) / 2 - x / 2 , x, x, color);
    }
}

void testfillrects(uint16_t color1, uint16_t color2) {
    tft.fillScreen(BLACK);
    for (uint16_t x = tft.height() - 1; x > 6; x -= 6) {
        tft.fillRect((tft.width() -1) / 2 - x / 2, (tft.height() - 1) / 2 - x / 2 , x, x, color1);
        tft.drawRect((tft.width() -1) / 2 - x / 2, (tft.height() - 1) / 2 - x / 2 , x, x, color2);
    }
}

void testfillcircles(uint8_t radius, uint16_t color) {
    for (uint8_t x = radius; x < tft.width() - 1; x += radius * 2) {
      for (uint8_t y = radius; y < tft.height() - 1; y += radius * 2) {
          tft.fillCircle(x, y, radius, color);
      }
    }  
}

void testdrawcircles(uint8_t radius, uint16_t color) {
    for (uint8_t x = 0; x < tft.width() - 1 + radius; x += radius * 2) {
        for (uint8_t y = 0; y < tft.height() - 1 + radius; y += radius * 2) {
            tft.drawCircle(x, y, radius, color);
        }
    }  
}

void testtriangles() {
    tft.fillScreen(BLACK);
    int color = 0xF800;
    int t;
    int w = tft.width() / 2;
    int x = tft.height();
    int y = 0;
    int z = tft.width();
    for (t = 0 ; t <= 15; t += 1) {
        tft.drawTriangle(w, y, y, x, z, x, color);
        x -= 4;
        y += 4;
        z -= 4;
        color += 100;
    }
}

void testroundrects() {
    tft.fillScreen(BLACK);
    int color = 100;
  
    int x = 0;
    int y = 0;
    int w = tft.width();
    int h = tft.height();
    for (int i = 0 ; i <= 24; i++) {
        tft.drawRoundRect(x, y, w, h, 5, color);
        x += 2;
        y += 3;
        w -= 4;
        h -= 6;
        color += 1100;
    }
}

void tftPrintTest() {
    tft.fillScreen(BLACK);
    tft.setCursor(0, 5);
    tft.setTextColor(RED);  
    tft.setTextSize(1);
    tft.println("Hello World!");
    tft.setTextColor(YELLOW);
    tft.setTextSize(2);
    tft.println("Hello World!");
    tft.setTextColor(BLUE);
    tft.setTextSize(3);
    tft.print(1234.567);
    delay(1500);
    tft.setCursor(0, 5);
    tft.fillScreen(BLACK);
    tft.setTextColor(WHITE);
    tft.setTextSize(0);
    tft.println("Hello World!");
    tft.setTextSize(1);
    tft.setTextColor(GREEN);
    tft.print(PI, 6);
    tft.println(" Want pi?");
    tft.println(" ");
    tft.print(8675309, HEX);
    tft.println(" Print HEX!");
    tft.println(" ");
    tft.setTextColor(WHITE);
    tft.println("Sketch has been");
    tft.println("running for: ");
    tft.setTextColor(MAGENTA);
    tft.print(millis() / 1000);
    tft.setTextColor(WHITE);
    tft.print(" seconds.");
}

void lcdTestPattern() {
    static const uint16_t PROGMEM colors[] = { RED, YELLOW, GREEN, CYAN, BLUE, MAGENTA, BLACK, WHITE };

    for (uint8_t c = 0; c < 8; c++) {
        tft.fillRect(0, tft.height() * c / 8, tft.width(), tft.height() / 8, pgm_read_word(&colors[c]));
    }
}

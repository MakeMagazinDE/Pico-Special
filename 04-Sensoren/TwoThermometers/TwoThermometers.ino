#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>

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

Adafruit_BME280 sensor;

Adafruit_SSD1351 display = Adafruit_SSD1351(
  SCREEN_WIDTH, SCREEN_HEIGHT,
  CS_PIN, DC_PIN, MOSI_PIN, SCLK_PIN, RST_PIN);  

void setup() {
    if (!sensor.begin(0x76)) {
        Serial.println("BME280-Sensor wurde nicht gefunden!");
        while (1)
            delay(10);
    }
    display.begin();
}

void loop() {
    char message[10];
    display.fillScreen(BLACK);
    display.setCursor(8, 40);
    display.setTextColor(YELLOW);
    display.setTextSize(2);
    sprintf(message, "%+6.1f C", readAnalogTemperature());
    display.println(message);
    display.setCursor(8, 70);
    sprintf(message, "%+6.1f C", sensor.readTemperature());
    display.println(message);
    delay(1000 * 10);
}

float readAnalogTemperature() {
    const uint16_t NUM_READING = 100;

    uint32_t total = 0;
    for (uint16_t i = 0; i < NUM_READING; i++) {
        uint16_t reading = analogRead(A0);
        total += reading;
        delayMicroseconds(100);
    }
    float voltage = (float(total) / NUM_READING) * 3.3 / 1024;
    float temperatureC = (voltage - 0.5) * 100;
    return temperatureC;
}

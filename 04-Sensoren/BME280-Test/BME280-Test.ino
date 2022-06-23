#include <Adafruit_BME280.h>

const float SEA_LEVEL_PRESSURE_HPA = 1013.25;

Adafruit_BME280 sensor;

void setup() {
    Serial.begin(9600);
    while (!Serial);
    
    if (!sensor.begin(0x76)) {
        Serial.println("BME280-Sensor wurde nicht gefunden!");
        while (1)
            delay(10);
    }
}

void loop() { 
    printValues();
    delay(1000);
}

void printValues() {
    Serial.print("Temperatur = ");
    Serial.print(sensor.readTemperature());
    Serial.println(" °C");

    Serial.print("Luftdruck = ");
    Serial.print(sensor.readPressure() / 100.0F);
    Serial.println(" hPa");

    Serial.print("Geschätzte Höhe = ");
    Serial.print(sensor.readAltitude(SEA_LEVEL_PRESSURE_HPA));
    Serial.println(" m");

    Serial.print("Luftfeuchtigkeit = ");
    Serial.print(sensor.readHumidity());
    Serial.println(" %");

    Serial.println();
}

void setup() {
    Serial.begin(9600);
    while (!Serial);
}
 
void loop() {
    const uint16_t reading = analogRead(A0);
    const float voltage = reading * 3.3 / 1024;
    Serial.print(voltage);
    Serial.print(" V ~ ");
  
    const float temperatureC = (voltage - 0.5) * 100;
    Serial.print(temperatureC);
    Serial.println(" °C");
    delay(1000);
}

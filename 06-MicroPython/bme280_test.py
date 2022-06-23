from machine import Pin, I2C
from time import sleep
from bme280 import BME280

i2c = I2C(0, scl = Pin(5), sda = Pin(4), freq = 400000)
bme = BME280(i2c = i2c)

while True:
  print(bme.values)
  sleep(10)

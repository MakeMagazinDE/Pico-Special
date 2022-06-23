from machine import Pin, I2C
from time import sleep
from ds1307 import DS1307
from bme280 import BME280

def convert(data):
  t, p, h = data
  p = p // 256
  pi = p // 100
  pd = p - pi * 100
  hi = h // 1024
  hd = h * 100 // 1024 - hi * 100
  return ("{}".format(t / 100), "{}.{:02d}".format(pi, pd), "{}.{:02d}".format(hi, hd))

i2c = I2C(0, scl = Pin(5), sda = Pin(4), freq = 400000)
bme = BME280(i2c = i2c)
rtc = DS1307(i2c)
file = open("data.csv", "w")

while True:
  year, month, day, _, hour, minute, second, _ = rtc.datetime()
  file.write("{:04d}-{:02d}-{:02d},".format(year, month, day))
  file.write("{:02d}:{:02d}:{:02d},".format(hour, minute, second))
  data = bme.read_compensated_data()
  file.write(",".join(convert(data)) + "\n")
  file.flush
  sleep(60)

from machine import I2C, Pin, RTC
from ds1307 import DS1307
from utime import sleep

i2c = I2C(0, scl = Pin(5), sda = Pin(4), freq = 100000)
rtc = DS1307(i2c)
year = 2022
month = 4
date = 10
day = 0
hour = 22
minute = 19
second = 0
now = (year, month, date, day, hour, minute, second, 0)
rtc.datetime(now)
rtc.halt(False)

while True:
  print(rtc.datetime())
  sleep(1)

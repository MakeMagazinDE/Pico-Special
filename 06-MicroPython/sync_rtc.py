from machine import I2C, Pin, RTC
from utime import sleep
import ds1307

i2c = I2C(0, scl = Pin(5), sda = Pin(4))
pico_rtc = RTC()
ext_rtc = ds1307.DS1307(i2c)
ext_rtc.halt(False)

print("DS1307:   ", ext_rtc.datetime())
print("Pico-RTC: ", pico_rtc.datetime())
ts = pico_rtc.datetime()
ext_rtc.datetime((ts[0], ts[1], ts[2], (ts[3] + 1) % 7, ts[4], ts[5], ts[6], 0))

while True:
  print()
  print("DS1307:   ", ext_rtc.datetime())
  print("Pico-RTC: ", pico_rtc.datetime())
  sleep(1)

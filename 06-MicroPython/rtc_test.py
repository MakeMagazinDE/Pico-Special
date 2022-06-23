from machine import Pin, I2C
from ds1307 import DS1307

i2c = I2C(0, scl = Pin(5), sda = Pin(4), freq = 100000)

result = I2C.scan(i2c)
print(result)

rtc = DS1307(i2c)
print(rtc.datetime())

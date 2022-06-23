from machine import Pin, I2C

i2c = I2C(0, scl = Pin(5), sda = Pin(4), freq = 100000)
result = I2C.scan(i2c)
print(result)
print(list(map(lambda x: hex(x), result)))

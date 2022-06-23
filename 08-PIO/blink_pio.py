from rp2 import PIO, StateMachine, asm_pio
from machine import Pin
from utime import sleep

@asm_pio(set_init = PIO.OUT_LOW)
def led_half_brightness():
  set(pins, 0)
  set(pins, 1)
    
@asm_pio(set_init = PIO.OUT_LOW)
def led_quarter_brightness():
  set(pins, 0) [2]
  set(pins, 1)
    
sm1 = StateMachine(0, led_quarter_brightness, freq = 10000, set_base = Pin(25))
sm2 = StateMachine(1, led_half_brightness, freq = 10000, set_base = Pin(25))

while (True):
  sm1.active(1)
  sleep(1)
  sm1.active(0)
    
  sm2.active(1)
  sleep(1)
  sm2.active(0)
